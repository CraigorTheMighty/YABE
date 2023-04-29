#include <windows.h>
#include <stdint.h>
#include <math.h>

#include "../inc/math.h"
#include "../inc/vecmat.h"
#include "../inc/dds_const.h"
#include "../inc/dds_util.h"
#include "../inc/dds.h"
#include "../inc/system.h"

float DDS_BC45FindBestIndexes(
	int channel,
	float *pixel4x4_rgba,
	float alpha[8],
	int index[4][4])
{
	int i;
	int j;
	int k;
	float err = 0.0f;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			int indexl = 0;
			float len = (pixel4x4_rgba[(i*4 + j)*4 + channel] - alpha[0])*(pixel4x4_rgba[(i*4 + j)*4 + channel] - alpha[0]);
			for (k = 1; k < 8; k++)
			{
				float lenl = (pixel4x4_rgba[(i*4 + j)*4 + channel] - alpha[k])*(pixel4x4_rgba[(i*4 + j)*4 + channel] - alpha[k]);
				if (lenl < len)
				{
					len = lenl;
					indexl = k;
				}
			}
			err += len;
			index[i][j] = indexl;
		}
	return err;
}

void DDS_EncodeBC4Blockf32(int channel, uint8_t *block, float *pixel4x4_rgba, int is_premultiplied, int is_srgb, int is_signed, int block_x, int block_y)
{
	int i, j;
	float alpha_val[8];
	//int has_alpha_0_255[2];
	int alpha_index[4][4];
	uint32_t temp32;
	float best_alpha_val[2];
	float best_err = DDS_MAX_INIT_ERROR;
	float minerr[2][256];
	int mins, maxs;
	int best_mode;

	alpha_val[0] = pixel4x4_rgba[0];
	alpha_val[1] = pixel4x4_rgba[0];

	for (i = 1; i < 16; i++)
	{
		alpha_val[0] = Math_Minf32(alpha_val[0], (uint8_t)pixel4x4_rgba[i*4 + channel]);
		alpha_val[1] = Math_Maxf32(alpha_val[1], (uint8_t)pixel4x4_rgba[i*4 + channel]);
	}

	mins = (int)alpha_val[0];
	maxs = (int)alpha_val[1];

	best_alpha_val[0] = alpha_val[0];
	best_alpha_val[1] = alpha_val[1];
	best_mode = BC3_4_ALPHA_ENCODE_FULL;

	if (g_system.opts.dds_quality & DDS_ENCODE_WALK_PATH)	// normal/high/best
	{
		int temp_maxs;
		int step = 1;

		if (g_system.opts.dds_quality & DDS_ENCODE_EXTEND_ENDPOINTS)	//best
		{
			mins = 0;
			maxs = 255;
		}
		temp_maxs = maxs;
		if ((g_system.opts.dds_quality & ~DDS_ENCODE_TEST) == DDS_QUALITY_NORMAL)
		{
			temp_maxs = mins + ((maxs - mins + 1) / 2) * 2;
			step = 2;
		}
		for (i = mins; i <= maxs; i++)
		{
			minerr[0][i] = 0.0f;
			minerr[1][i] = 0.0f;
			for (j = 0; j < 16; j++)
			{
				if (pixel4x4_rgba[j*4 + channel] < i)
					minerr[0][i] += (pixel4x4_rgba[j*4 + channel] - i)*(pixel4x4_rgba[j*4 + channel] - i);
				if (pixel4x4_rgba[j*4 + channel] > i)
					minerr[1][i] += (pixel4x4_rgba[j*4 + channel] - i)*(pixel4x4_rgba[j*4 + channel] - i);
			}
		}
		for (i = mins; i <= temp_maxs; i += step)
		{
			int ireal = (i == temp_maxs ? maxs : i);
			if (!(g_system.opts.dds_quality & DDS_ENCODE_TEST))
				if (minerr[0][ireal] >= best_err)
					break;
			for (j = i; j <= temp_maxs; j += step)
			{
				int jreal = (j == temp_maxs ? maxs : j);
				//if (DDS_DEBUG_BLOCK)
					//printf("%3i %3i: %f %f\n", i, j, minerr[0][ireal], minerr[1][ireal]);
				if (!(g_system.opts.dds_quality & DDS_ENCODE_TEST))
					if (minerr[0][ireal] + minerr[1][jreal] >= best_err)
						continue;

				alpha_val[0] = (float)ireal;
				alpha_val[1] = (float)jreal;

				DDS_GenBC3_4Alphau8(BC3_4_ALPHA_ENCODE_FULL, alpha_val, (uint8_t)alpha_val[0], (uint8_t)alpha_val[1]);

				float err = DDS_BC45FindBestIndexes(
					channel,
					pixel4x4_rgba,
					alpha_val,
					alpha_index);

				if (err < best_err)
				{
					best_alpha_val[0] = alpha_val[0];
					best_alpha_val[1] = alpha_val[1];
					best_err = err;
					best_mode = BC3_4_ALPHA_ENCODE_FULL;
				}

				DDS_GenBC3_4Alphau8(BC3_4_ALPHA_ENCODE_0_255, alpha_val, (uint8_t)alpha_val[0], (uint8_t)alpha_val[1]);

				err = DDS_BC45FindBestIndexes(
					channel,
					pixel4x4_rgba,
					alpha_val,
					alpha_index);

				if (err < best_err)
				{
					best_alpha_val[0] = alpha_val[0];
					best_alpha_val[1] = alpha_val[1];
					best_err = err;
					best_mode = BC3_4_ALPHA_ENCODE_0_255;
				}
			}
		}
	}
	if ((g_system.opts.dds_quality & ~DDS_ENCODE_TEST) != DDS_QUALITY_BEST)
	{
		int min_mins = (int)best_alpha_val[0];
		int max_mins = (int)best_alpha_val[0];
		int min_maxs = (int)best_alpha_val[1];
		int max_maxs = (int)best_alpha_val[1];
		
		min_mins = (min_mins == 0 ? 0 : min_mins - 1);
		max_mins = (max_mins == 255 ? 255 : max_mins + 1);

		min_maxs = (min_maxs == 0 ? 0 : min_maxs - 1);
		max_maxs = (max_maxs == 255 ? 255 : max_maxs + 1);

		//printf("%i x %i\n", max_mins - min_mins + 1, max_maxs - min_maxs + 1);

		for (i = min_mins; i <= max_mins; i++)
			for (j = min_maxs; j <= max_maxs; j++)
			{
				alpha_val[0] = (float)i;
				alpha_val[1] = (float)j;

				DDS_GenBC3_4Alphau8(BC3_4_ALPHA_ENCODE_FULL, alpha_val, (uint8_t)alpha_val[0], (uint8_t)alpha_val[1]);

				float err = DDS_BC45FindBestIndexes(
					channel,
					pixel4x4_rgba,
					alpha_val,
					alpha_index);

				if (err < best_err)
				{
					best_alpha_val[0] = alpha_val[0];
					best_alpha_val[1] = alpha_val[1];
					best_err = err;
					best_mode = BC3_4_ALPHA_ENCODE_FULL;
				}

				DDS_GenBC3_4Alphau8(BC3_4_ALPHA_ENCODE_0_255, alpha_val, (uint8_t)alpha_val[0], (uint8_t)alpha_val[1]);

				err = DDS_BC45FindBestIndexes(
					channel,
					pixel4x4_rgba,
					alpha_val,
					alpha_index);

				if (err < best_err)
				{
					best_alpha_val[0] = alpha_val[0];
					best_alpha_val[1] = alpha_val[1];
					best_err = err;
					best_mode = BC3_4_ALPHA_ENCODE_0_255;
				}
			}
	}

	alpha_val[0] = best_alpha_val[0];
	alpha_val[1] = best_alpha_val[1];

	DDS_GenBC3_4Alphau8(best_mode, alpha_val, (uint8_t)alpha_val[0], (uint8_t)alpha_val[1]);

	DDS_BC45FindBestIndexes(
		channel,
		pixel4x4_rgba,
		alpha_val,
		alpha_index);

	block[0] = (uint8_t)(alpha_val[0] - (is_signed ? 128 : 0));
	block[1] = (uint8_t)(alpha_val[1] - (is_signed ? 128 : 0));

	temp32 =	(alpha_index[0][0] >> 0) | 
		(alpha_index[0][1] << 3) | 
		(alpha_index[0][2] << 6) | 
		(alpha_index[0][3] << 9) | 
		(alpha_index[1][0] << 12) | 
		(alpha_index[1][1] << 15) | 
		(alpha_index[1][2] << 18) | 
		(alpha_index[1][3] << 21);

	block[2] = (temp32 >> 0) & 0xFF;
	block[3] = (temp32 >> 8) & 0xFF;
	block[4] = (temp32 >> 16) & 0xFF;

	temp32 =	(alpha_index[2][0] >> 0) | 
		(alpha_index[2][1] << 3) | 
		(alpha_index[2][2] << 6) | 
		(alpha_index[2][3] << 9) | 
		(alpha_index[3][0] << 12) | 
		(alpha_index[3][1] << 15) | 
		(alpha_index[3][2] << 18) | 
		(alpha_index[3][3] << 21);

	block[5] = (temp32 >> 0) & 0xFF;
	block[6] = (temp32 >> 8) & 0xFF;
	block[7] = (temp32 >> 16) & 0xFF;
}

void DDS_DecodeBC4Block(uint8_t *block, float *pixel4x4_rgba, int is_premultiplied, int is_srgb, int is_signed, int block_x, int block_y)
{
	int16_t red[8];
	int red_index[16];
	int i, j;
	uint32_t red_block[2];

	if (is_signed)
	{
		red[0] = (int8_t)block[0];
		red[1] = (int8_t)block[1];
	}
	else
	{
		red[0] = (uint8_t)block[0];
		red[1] = (uint8_t)block[1];
	}

	if (red[0] > red[1])
	{
		red[2] = (int16_t)floorf(red[0] * 6.0f / 7.0f + red[1] * 1.0f / 7.0f + 0.5f);
		red[3] = (int16_t)floorf(red[0] * 5.0f / 7.0f + red[1] * 2.0f / 7.0f + 0.5f);
		red[4] = (int16_t)floorf(red[0] * 4.0f / 7.0f + red[1] * 3.0f / 7.0f + 0.5f);
		red[5] = (int16_t)floorf(red[0] * 3.0f / 7.0f + red[1] * 4.0f / 7.0f + 0.5f);
		red[6] = (int16_t)floorf(red[0] * 2.0f / 7.0f + red[1] * 5.0f / 7.0f + 0.5f);
		red[7] = (int16_t)floorf(red[0] * 1.0f / 7.0f + red[1] * 6.0f / 7.0f + 0.5f);
	}
	else
	{
		red[2] = (int16_t)floorf(red[0] * 4.0f / 5.0f + red[1] * 1.0f / 5.0f + 0.5f);
		red[3] = (int16_t)floorf(red[0] * 3.0f / 5.0f + red[1] * 2.0f / 5.0f + 0.5f);
		red[4] = (int16_t)floorf(red[0] * 2.0f / 5.0f + red[1] * 3.0f / 5.0f + 0.5f);
		red[5] = (int16_t)floorf(red[0] * 1.0f / 5.0f + red[1] * 4.0f / 5.0f + 0.5f);
		if (is_signed)
		{
			red[6] = -128;
			red[7] = 127;
		}
		else
		{
			red[6] = 0;
			red[7] = 255;
		}
	}

	red_block[0] = block[2];
	red_block[0] |= block[3] << 8;
	red_block[0] |= block[4] << 16;
	red_block[1] = block[5];
	red_block[1] |= block[6] << 8;
	red_block[1] |= block[7] << 16;

	for (i = 0; i < 2; i++)
	{
		red_index[0 + i * 8] = (red_block[i] >> 0) & 0x07;
		red_index[1 + i * 8] = (red_block[i] >> 3) & 0x07;
		red_index[2 + i * 8] = (red_block[i] >> 6) & 0x07;
		red_index[3 + i * 8] = (red_block[i] >> 9) & 0x07;
		red_index[4 + i * 8] = (red_block[i] >> 12) & 0x07;
		red_index[5 + i * 8] = (red_block[i] >> 15) & 0x07;
		red_index[6 + i * 8] = (red_block[i] >> 18) & 0x07;
		red_index[7 + i * 8] = (red_block[i] >> 21) & 0x07;
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (is_signed)
			{
				pixel4x4_rgba[i * 16 + j * 4 + 0] = (float)(red[red_index[i * 4 + j]] + 128);
				pixel4x4_rgba[i * 16 + j * 4 + 1] = (float)128;
				pixel4x4_rgba[i * 16 + j * 4 + 2] = (float)128;
			}
			else
			{
				pixel4x4_rgba[i * 16 + j * 4 + 0] = (float)red[red_index[i * 4 + j]];
				pixel4x4_rgba[i * 16 + j * 4 + 1] = (float)0;
				pixel4x4_rgba[i * 16 + j * 4 + 2] = (float)0;
			}
			pixel4x4_rgba[i * 16 + j * 4 + 3] = 255;
		}
	}
}
void DDS_EncodeBC4Block(uint8_t *block, double *pixel4x4_rgba, int is_premultiplied, int is_srgb, int is_signed, int block_x, int block_y)
{
	float pixel[64];
	int i;
	for (i = 0; i < 64; i++)
		pixel[i] = (float)pixel4x4_rgba[i];
//	for (i = 0; i < 64; i++)
	//	pixel[i] = (float)(rand()%256);
//	for (i = 0; i < 64; i++)
//		pixel[i] = Math_Clampf32(64, 0.0f, 255.0f);

	DDS_EncodeBC4Blockf32(0, block, pixel, is_premultiplied, is_srgb, is_signed, block_x, block_y);
}
