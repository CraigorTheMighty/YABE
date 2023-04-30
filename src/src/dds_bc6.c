#include <stdint.h>
#include <math.h>

#include "../inc/math.h"
#include "../inc/vecmat.h"
#include "../inc/dds_const.h"
#include "../inc/dds_util.h"

void DDS_EncodeBC6HBlockf32(uint8_t *block, double *pixel4x4_rgba, int is_premultiplied, int is_srgb, int is_signed, int block_x, int block_y)
{
	int i, j, k, m;
	int best_mode;
	float err[32];
	float minerr;
	bc6h_header_t header = {0};
	int total_bits;
	int start_bit;
	int best_header_mode[32] = {0};
	int	mode_endpoint_quant[32][2][2][3];
	int partition_indexes[32][16];
	int ext_partition_indexes[16];
	int *partition_index_p = partition_indexes[0];
	float pixel4x4_rgbaf32[64];
	vec3f32_t mean[32][3];
	int r;
	bc6h7_shape_index_t *partition = &g_bc6h_shape_index[0];
	float mins[2] = {9999999999999.0f, 9999999999999.0f};
	float maxs[2] = {-9999999999999.0f, -9999999999999.0f};
	int is_transformed;
	int is_flipped[32];
	int is_flipped_final;
	int count[3] = {0};
	int ext_mode_found = 0;
	int bits;
	int offset;
	vec3f32_t trans_pixel[16];
	int superblock;
	float superblock_error;
	int best_superblock;

	for (i = 0; i < 64; i++)
		pixel4x4_rgbaf32[i] = (float)F16_FinishQuantise(F16_StartQuantise(MiniFloat_From32F((float)pixel4x4_rgba[i], 1, 5, 10, 1), 16, is_signed), 16, is_signed);

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			for (k = 0; k < 3; k++)
				trans_pixel[i*4 + j] = *(vec3f32_t*)&pixel4x4_rgbaf32[(i*4 + j)*4 + 0];


	mean[0][0] = Vec3f32_Zero();
	mean[0][1] = Vec3f32_Zero();
	mean[0][2] = Vec3f32_Zero();

	for (i = 0; i < 16; i++)
	{
		int id = partition->index[i];
		mean[0][id] = Vec3f32_Add(trans_pixel[i], mean[0][id]);
		count[id]++;
	}
	for (i = 0; i < 3; i++)
	{
		count[i] = count[i] ? count[i] : 1;
		mean[0][i] = Vec3f32_DivScale(mean[0][i], (float)count[i]);
	}
	for (r = 0; r < 31; r++)
	{
		vec3f32_t temp_mean[3];
		vec3f32_t temp_diff;
		int from = g_bc6h_partition_order[r].from_to[0];
		int to = g_bc6h_partition_order[r].from_to[1];
		bc6h7_shape_index_t *partition = &g_bc6h_shape_index[to];

		temp_diff = Vec3f32_Zero();

		for (i = 0; i < g_bc6h7_partition_delta[r].num_diff; i++)
		{
			if (partition->index[g_bc6h7_partition_delta[r].diff[i]] == 0)
				temp_diff = Vec3f32_Add(temp_diff, trans_pixel[g_bc6h7_partition_delta[r].diff[i]]);
			else
				temp_diff = Vec3f32_Sub(temp_diff, trans_pixel[g_bc6h7_partition_delta[r].diff[i]]);
		}

		temp_mean[0] = Vec3f32_Scale(mean[from][0], g_bc6h7_partition_delta[r].set_a0_count);
		temp_mean[1] = Vec3f32_Scale(mean[from][1], g_bc6h7_partition_delta[r].set_a1_count);

		temp_mean[0] = Vec3f32_Add(temp_mean[0], temp_diff);
		temp_mean[1] = Vec3f32_Sub(temp_mean[1], temp_diff);

		temp_mean[0] = Vec3f32_Scale(temp_mean[0], g_bc6h7_partition_delta[r].set_b0_count);
		temp_mean[1] = Vec3f32_Scale(temp_mean[1], g_bc6h7_partition_delta[r].set_b1_count);

		mean[to][0] = temp_mean[0];
		mean[to][1] = temp_mean[1];
	}

	for (k = 0; k < 32; k++)
	{
		best_header_mode[k] = -1;
		err[k] = 99999999999999999999999999.0f;
	}
#ifndef BC6H_EXHAUSTIVE
	for (superblock = 0; superblock < BC6H_NUM_SUPERBLOCKS; superblock++)
	{
		int tmodes[6] = {2, 0, 5, 6, 1, 9}; // in order of decreasing quality: error should be strictly increasing using this mode order

		k = g_bc6h_superblock_desc[superblock].parent;

		DDS_BC6H_FitPartition(
			2, 
			k,
			&g_bc6h_shape_index[k],
			tmodes,
			6,
			pixel4x4_rgbaf32, 
			trans_pixel, 
			&mean[k][0],
			is_signed,
			partition_indexes[k],
			&mode_endpoint_quant[k][0][0][0],
			&mode_endpoint_quant[k][0][1][0],
			&mode_endpoint_quant[k][1][0][0],
			&mode_endpoint_quant[k][1][1][0],
			&best_header_mode[k],
			&err[k],
			&is_flipped[k]);
#ifdef BC6H_EARLY_EXIT
		if (err[k] <= BC6H_MIN_ERROR)
			break;
#endif
	}

#ifndef BC6H_SUPERBLOCKS_ONLY
	superblock_error = err[g_bc6h_superblock_desc[0].parent];
	best_superblock = 0;

	for (k = 1; k < BC6H_NUM_SUPERBLOCKS; k++)
	{
		if (err[g_bc6h_superblock_desc[k].parent] < superblock_error)
		{
			best_superblock = k;
			superblock_error = err[g_bc6h_superblock_desc[k].parent];
		}
	}

	if(superblock_error > BC6H_MIN_ERROR)
		for (superblock = 0; superblock < (int)g_bc6h_superblock_desc[best_superblock].num_children; superblock++)
		{
			int tmodes[6] = {2, 0, 5, 6, 1, 9}; // in order of decreasing quality: error should be strictly increasing using this mode order
			k = g_bc6h_superblock_desc[best_superblock].children[superblock];
			DDS_BC6H_FitPartition(
				2, 
				k,
				&g_bc6h_shape_index[k],
				tmodes,
				6,
				pixel4x4_rgbaf32, 
				trans_pixel, 
				&mean[k][0],
				is_signed,
				partition_indexes[k],
				&mode_endpoint_quant[k][0][0][0],
				&mode_endpoint_quant[k][0][1][0],
				&mode_endpoint_quant[k][1][0][0],
				&mode_endpoint_quant[k][1][1][0],
				&best_header_mode[k],
				&err[k],
				&is_flipped[k]);
#ifdef BC6H_EARLY_EXIT
			if (err[k] <= BC6H_MIN_ERROR)
				break;
#endif
		}
#else
	minerr = err[0];
	header.mode = best_header_mode[0];
	best_mode = 0;

	for (k = 1; k < 32; k++)
	{
		if (err[k] < minerr)
		{
			best_mode = k;
			minerr = err[k];
			header.mode = best_header_mode[k];
		}
	}
#endif
#else
	for (k = 0; k < 32; k++)
	{
		int tmodes[6] = {2, 0, 5, 6, 1, 9}; // in order of decreasing quality: error should be strictly increasing using this mode order

		DDS_BC6H_FitPartition(
			2, 
			k,
			&g_bc6h_shape_index[k],
			tmodes,
			6,
			pixel4x4_rgbaf32, 
			trans_pixel, 
			&mean[k][0],
			is_signed,
			partition_indexes[k],
			&mode_endpoint_quant[k][0][0][0],
			&mode_endpoint_quant[k][0][1][0],
			&mode_endpoint_quant[k][1][0][0],
			&mode_endpoint_quant[k][1][1][0],
			&best_header_mode[k],
			&err[k],
			&is_flipped[k]);
#ifdef BC6H_EARLY_EXIT
		if (err[k] <= BC6H_MIN_ERROR)
			break;
#endif
	}
#endif

	minerr = err[0];
	header.mode = best_header_mode[0];
	best_mode = 0;

	for (k = 1; k < 32; k++)
	{
		if (err[k] < minerr)
		{
			best_mode = k;
			minerr = err[k];
			header.mode = best_header_mode[k];
		}
	}

	if (minerr > BC6H_MIN_ERROR)
	{
		float ext_err = 99999999999999999999999999.0f;
		bc6h7_shape_index_t *ext_partition = &g_bc6h7_shape_index1[0];
		int extmodes[2] = {11, 10}; // in order of decreasing quality: error should be strictly increasing using this mode order
		vec3f32_t ext_mean;
		int ext_is_flipped;
		int ext_best_header_mode = -1;
		int	ext_mode_endpoint_quant[2][3];

		ext_mean = Vec3f32_Zero();

		for (k = 0; k < 16; k++)
			ext_mean = Vec3f32_Add(ext_mean, trans_pixel[k]);

		ext_mean = Vec3f32_Scale(ext_mean, 1.0f/16.0f);

		DDS_BC6H_FitPartition(
			1, 
			0,
			&g_bc6h7_shape_index1[0],
			extmodes,
			2,
			pixel4x4_rgbaf32, 
			trans_pixel, 
			&ext_mean,
			is_signed,
			ext_partition_indexes,
			&ext_mode_endpoint_quant[0][0],
			&ext_mode_endpoint_quant[1][0],
			0,
			0,
			&ext_best_header_mode,
			&ext_err,
			&ext_is_flipped);
		if (ext_err < minerr)
		{
			ext_mode_found = 1;
			partition = &g_bc6h7_shape_index1[0];
			header.mode = ext_best_header_mode;
			header.shape_index = -1;
			partition_index_p = ext_partition_indexes;
			is_flipped_final = ext_is_flipped;
			for (j = 0; j < 2; j++)
				for (m = 0; m < 3; m++)
					header.endpoint[0][j][m] = ext_mode_endpoint_quant[j][m];
		}
	}
	if (!ext_mode_found)
	{
		partition_index_p = partition_indexes[best_mode];
		is_flipped_final = is_flipped[best_mode];
		partition = &g_bc6h_shape_index[best_mode];

		for (i = 0; i < (header.mode < 10 ? 2 : 1); i++)
			for (j = 0; j < 2; j++)
				for (m = 0; m < 3; m++)
					header.endpoint[i][j][m] = mode_endpoint_quant[best_mode][i][j][m];

		header.shape_index = best_mode;
	}

	is_transformed = ((header.mode == 9) || (header.mode == 10)) ? 0 : 1;

	start_bit = header.mode < 2 ? 2 : 5;
	total_bits = header.mode < 10 ? 82 : 65;
	DDS_WriteBits(block, g_bc6h_desc[header.mode].mode, 0, start_bit);

	if (is_flipped_final)
	{
		int bits = ext_mode_found ? 4 : 3;
		int mask0 = (1 << (ext_mode_found ? 4 : 3)) - 1;
		int mask1 = (1 << (ext_mode_found ? 3 : 2)) - 1;

		if (partition_index_p[0] > 3)
		{
			for (i = 0; i < 16; i++)
				if (partition->index[i] == 0)
					partition_index_p[i] = (~partition_index_p[i]) & mask0;
			partition_index_p[0] &= mask1;
		}
		if (header.mode < 10)
			if (partition_index_p[g_bc6h_fixup[header.shape_index]] > 3)
			{
				for (i = 0; i < 16; i++)
					if (partition->index[i] == 1)
						partition_index_p[i] = (~partition_index_p[i]) & mask0;
				partition_index_p[g_bc6h_fixup[header.shape_index]] &= mask1;
			}
	}

	for (i = start_bit; i < total_bits; i++)
		DDS_WriteBits(block, (*DDS_BC6HMemberToP(&header, g_bc6h_desc[header.mode].entry[i].member)) >> g_bc6h_desc[header.mode].entry[i].bit, i, 1);

	start_bit = total_bits;

	bits = ext_mode_found ? 4 : 3;
	offset = 0;

	for (i = 0; i < 16; i++)
	{
		if ((i == 0) || ((header.mode < 10) && (i == g_bc6h_fixup[header.shape_index])))
		{
			DDS_WriteBits(block, partition_index_p[i], start_bit + offset, bits - 1);
			offset += bits - 1;
		}
		else
		{
			DDS_WriteBits(block, partition_index_p[i], start_bit + offset, bits);
			offset += bits;
		}
	}
}
