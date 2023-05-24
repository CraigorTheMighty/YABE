#include <stdint.h>
#include <math.h>

#include "../inc/vecmat.h"
#include "../inc/dds_const.h"
#include "../inc/math.h"

#define FP32_MANTISSA_BITS	23
#define FP32_EXPONENT_BITS	8
#define FP32_EXPONENT_MASK	0x7F800000
#define FP32_MANTISSA_MASK	0x007FFFFF

#define FP64_MANTISSA_MASK	0x000FFFFFFFFFFFFFULL
#define FP64_MANTISSA_BITS	52
#define FP64_EXPONENT_BITS	11


static uint32_t g_dummy;

mat3x3f64_t DDS_BlockCovariance3D(double *pixel4x4_rgba, double *mean, double alpha_cutoff)
{
	int i, j, k, m;
	double val[3][3] = {0.0};
	double count = 0;

	mean[0] = 0.0;
	mean[1] = 0.0;
	mean[2] = 0.0;

	for (k = 0; k < 4; k++)
		for (m = 0; m < 4; m++)
		{
			if (pixel4x4_rgba[(k*4 + m)*4 + 3] < alpha_cutoff)
				continue;
			mean[0] += pixel4x4_rgba[(k*4 + m)*4 + 0];
			mean[1] += pixel4x4_rgba[(k*4 + m)*4 + 1];
			mean[2] += pixel4x4_rgba[(k*4 + m)*4 + 2];
			count++;
		}

	mean[0] /= count ? count : 1.0;
	mean[1] /= count ? count : 1.0;
	mean[2] /= count ? count : 1.0;

	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			for (k = 0; k < 4; k++)
				for (m = 0; m < 4; m++)
				{
					if (pixel4x4_rgba[(k*4 + m)*4 + 3] < alpha_cutoff)
						continue;
					val[i][j] += (pixel4x4_rgba[(k*4 + m)*4 + i] - mean[i]) * (pixel4x4_rgba[(k*4 + m)*4 + j] - mean[j]);
				}

	return Mat3x3f64_Mat(	val[0][0], val[0][1], val[0][2],
		val[1][0], val[1][1], val[1][2],
		val[2][0], val[2][1], val[2][2]);
}

vec3f64_t DDS_BlockPrincipalEigenVector3D(mat3x3f64_t cvmat)
{
	vec3f64_t vec[3];
	vec3f64_t tvec[3];
	int i;
	int index = 0;

	vec[0] = Vec3f64_Vec(1.0, 0.0, 0.0);
	vec[1] = Vec3f64_Vec(0.0, 1.0, 0.0);
	vec[2] = Vec3f64_Vec(0.0, 0.0, 1.0);

	tvec[0] = Mat3x3f64_MulVecR(cvmat, vec[0]);
	tvec[1] = Mat3x3f64_MulVecR(cvmat, vec[1]);
	tvec[2] = Mat3x3f64_MulVecR(cvmat, vec[2]);

	for (i = 1; i < 3; i++)
		if (Vec3f64_LenSq(tvec[i]) > Vec3f64_LenSq(tvec[index]))
			index = i;

	vec[0] = vec[index];

	for (i = 0; i < 16; i++)
	{
		tvec[0] = vec[0];
		vec[0] = Mat3x3f64_MulVecR(cvmat, vec[0]);
		vec[0] = Vec3f64_Normalise(vec[0]);

		if (Vec3f64_Dot(tvec[0], vec[0]) > 0.99999)
			break;
	}

	return vec[0];
}
void DDS_UnpackTof64(uint32_t x, uint8_t r_bits, uint8_t g_bits, uint8_t b_bits, uint8_t a_bits, double *rgba)
{
	rgba[0] = ((x >> (g_bits + b_bits + a_bits)) & ((1 << r_bits) - 1)) << (8 - r_bits);
	if (g_bits)
		rgba[1] = ((x >> (b_bits + a_bits)) & ((1 << g_bits) - 1)) << (8 - g_bits);
	if (b_bits)
		rgba[2] = ((x >> (a_bits)) & ((1 << b_bits) - 1)) << (8 - b_bits);
	if (a_bits)
		rgba[3] = ((x >> (0)) & ((1 << a_bits) - 1)) << (8 - a_bits);
}
uint32_t *DDS_BC6HMemberToP(bc6h_header_t *header, int member)
{
	switch (member)
	{
	case BC6H_M:	return (uint32_t*)&header->real_mode;
	case BC6H_D:	return (uint32_t*)&header->shape_index;
	case BC6H_RW:	return (uint32_t*)&header->endpoint[0][0][0];
	case BC6H_RX:	return (uint32_t*)&header->endpoint[0][1][0];
	case BC6H_RY:	return (uint32_t*)&header->endpoint[1][0][0];
	case BC6H_RZ:	return (uint32_t*)&header->endpoint[1][1][0];
	case BC6H_GW:	return (uint32_t*)&header->endpoint[0][0][1];
	case BC6H_GX:	return (uint32_t*)&header->endpoint[0][1][1];
	case BC6H_GY:	return (uint32_t*)&header->endpoint[1][0][1];
	case BC6H_GZ:	return (uint32_t*)&header->endpoint[1][1][1];
	case BC6H_BW:	return (uint32_t*)&header->endpoint[0][0][2];
	case BC6H_BX:	return (uint32_t*)&header->endpoint[0][1][2];
	case BC6H_BY:	return (uint32_t*)&header->endpoint[1][0][2];
	case BC6H_BZ:	return (uint32_t*)&header->endpoint[1][1][2];
	default:		return (uint32_t*)&g_dummy;
	}
}
void DDS_GenBC3_4Alphau8(int mode, float *alpha, uint8_t alpha0, uint8_t alpha1)
{
	int i;

	if (mode == BC3_4_ALPHA_ENCODE_FULL)
	{
		if (alpha0 < alpha1)
		{
			uint8_t temp = alpha0;

			alpha0 = alpha1;
			alpha1 = temp;

		}
		else if (alpha0 == alpha1)
		{
			if (alpha0 != 255)
				alpha0++;
			else
				alpha1--;
		}

		alpha[0] = alpha0;
		alpha[1] = alpha1;

		for (i = 0; i < 6; i++)
			alpha[i + 2] = floorf(((6.0f - i) * (uint16_t)alpha0) / 7.0f + ((i + 1) * (uint16_t)alpha1) / 7.0f + 0.5f);
	}
	else
	{
		if (alpha0 > alpha1)
		{
			uint8_t temp = alpha0;

			alpha0 = alpha1;
			alpha1 = temp;
		}
		alpha[0] = alpha0;
		alpha[1] = alpha1;

		for (i = 0; i < 4; i++)
			alpha[i + 2] = floorf(((4 - i) * (uint16_t)alpha0) / 5.0f + ((i + 1) * (uint16_t)alpha1) / 5.0f + 0.5f);

		alpha[6] = 0;
		alpha[7] = 255;
	}
}
void DDS_BlockCovariancePartition3DPreCalcMeanf32(int max_partitions, mat3x3f32_t *mat, float *pixel4x4_rgba, vec3f32_t *mean, bc6h7_shape_index_t *shape_index)
{
	int i, j, k, m;
	float val[3][3][3] = {0.0f};

	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			for (k = 0; k < 4; k++)
				for (m = 0; m < 4; m++)
				{
					int id = shape_index->index[k*4 + m];
					val[id][i][j] += ((float)pixel4x4_rgba[(k*4 + m)*4 + i] - mean[id].v[i]) * ((float)pixel4x4_rgba[(k*4 + m)*4 + j] - mean[id].v[j]);
				}

	for (i = 0; i < max_partitions; i++)
		mat[i] = Mat3x3f32_Mat(	val[i][0][0], val[i][0][1], val[i][0][2],
			val[i][1][0], val[i][1][1], val[i][1][2],
			val[i][2][0], val[i][2][1], val[i][2][2]);
}
vec3f32_t DDS_BlockPrincipalEigenVector3Df32(mat3x3f32_t cvmat)
{
	vec3f32_t vec[3];
	vec3f32_t tvec[3];
	int i;
	int index = 0;

	vec[0] = Vec3f32_Vec(1.0, 0.0, 0.0);
	vec[1] = Vec3f32_Vec(0.0, 1.0, 0.0);
	vec[2] = Vec3f32_Vec(0.0, 0.0, 1.0);

	tvec[0] = Mat3x3f32_MulVecR(cvmat, vec[0]);
	tvec[1] = Mat3x3f32_MulVecR(cvmat, vec[1]);
	tvec[2] = Mat3x3f32_MulVecR(cvmat, vec[2]);

	for (i = 1; i < 3; i++)
		if (Vec3f32_LenSq(tvec[i]) > Vec3f32_LenSq(tvec[index]))
			index = i;

	vec[0] = vec[index];

	for (i = 0; i < 16; i++)
	{
		tvec[0] = vec[0];
		vec[0] = Mat3x3f32_MulVecR(cvmat, vec[0]);
		vec[0] = Vec3f32_Normalise(vec[0]);

		if (Vec3f32_Dot(tvec[0], vec[0]) > 0.99999f)
			break;
	}

	return vec[0];
}
void DDS_BC6HQuantiseIntEndpoints(int num_partitions, int source_bits, int *target_bits, int *src_endpoint00, int *src_endpoint01, int *src_endpoint10, int *src_endpoint11, int *q_endpoint00, int *q_endpoint01, int *q_endpoint10, int *q_endpoint11)
{
	int *q_endpoint[2][2];
	int *src_endpoint[2][2];
	int i, j, k;

	src_endpoint[0][0] = src_endpoint00;
	src_endpoint[0][1] = src_endpoint01;
	src_endpoint[1][0] = src_endpoint10;
	src_endpoint[1][1] = src_endpoint11;

	q_endpoint[0][0] = q_endpoint00;
	q_endpoint[0][1] = q_endpoint01;
	q_endpoint[1][0] = q_endpoint10;
	q_endpoint[1][1] = q_endpoint11;

	for (i = 0; i < num_partitions; i++)
		for (j = 0; j < 2; j++)
			for (k = 0; k < 3; k++)
			{
				int mul = src_endpoint[i][j][k] < 0 ? -1 : 1;
				int shift = source_bits - target_bits[k];
				q_endpoint[i][j][k] = mul * ((mul * src_endpoint[i][j][k]) >> shift);
			}
}
void DDS_BC6HInvTransformNoWrap(int num_partitions, int endpoint00, int *endpoint01, int *endpoint10, int *endpoint11)
{
	(*endpoint01) -= endpoint00;
	if (num_partitions > 1)
	{
		(*endpoint10) -= endpoint00;
		(*endpoint11) -= endpoint00;
	}
}
int DDS_BC6HGetAllowedSubMode(int mode, int *q_endpoint00, int *q_endpoint01, int *q_endpoint10, int *q_endpoint11, int is_transformed, int is_signed)
{
	int i, j, k, m;
	int ep_mins[3];
	int ep_maxs[3];

	if (mode < 10)
	{
		for (i = 0; i < 3; i++)
		{
			ep_mins[i] = q_endpoint01[i];
			ep_mins[i] = Math_Mini32(ep_mins[i], q_endpoint10[i]);
			ep_mins[i] = Math_Mini32(ep_mins[i], q_endpoint11[i]);

			ep_maxs[i] = q_endpoint01[i];
			ep_maxs[i] = Math_Maxi32(ep_maxs[i], q_endpoint10[i]);
			ep_maxs[i] = Math_Maxi32(ep_maxs[i], q_endpoint11[i]);
		}
	}
	else
	{
		for (i = 0; i < 3; i++)
		{
			ep_mins[i] = q_endpoint01[i];
			ep_maxs[i] = q_endpoint01[i];
		}
	}

	for (m = 0; m < (int)g_bc6h_desc[mode].mode_group_count; m++)
	{
		for (i = 0; i < (((mode + m) < 10) ? 2 : 1); i++)
		{
			for (j = 0; j < 2; j++)
			{
				int match_count = 0;

				if ((i == 0) && (j == 0))
					continue;

				for (k = 0; k < 3; k++)
				{
					int mins;
					int maxs;

					if (is_signed || is_transformed)
					{
						mins = -(1 << (g_bc6h_desc[mode + m].endpoint_bits[i][j][k] - 1));
						maxs = (1 << (g_bc6h_desc[mode + m].endpoint_bits[i][j][k] - 1)) - 1;
					}
					else
					{
						mins = 0;
						maxs = (1 << g_bc6h_desc[mode + m].endpoint_bits[i][j][k]) - 1;
					}
					if (ep_mins[k] >= mins && ep_maxs[k] <= maxs)
						match_count++;
				}
				if (match_count == 3)
					return mode + m;
			}
		}
	}

	return -1;
}
int F16_FinishQuantise(int x, int bits, int is_signed)
{
	int s = x < 0 ? -1 : 1;

	if (bits >= 16)
		return x;
	else if (bits >= 15 && !is_signed)
		return s * ((s * x) >> (15 - bits));
	else
		return s * ((s * x) >> (16 - bits));
}
int F16_StartQuantise(int comp, int bits, int is_signed)
{
	if (comp == 0)
		return 0;
	else if (is_signed)
	{
		int s;

		if (comp == 0xFBFF)
			return 0xFFFF8001;

		s = comp > 32768 ? -1 : 1;

		if (s == -1)
			comp -= 32768;

		comp = (s * (comp << 5)) / 31;

		if (bits >= 11)
			comp += s;
		else if (comp == 32766)
			comp++;

		return comp;
	}
	else
	{
		if (comp == 0x7BFF)
			return 0x0000FFFF;
		else
		{
			comp = (comp << 6) / 31;

			if (bits >= 10 && comp)
				comp += (comp & 1) ? 1 : 2;

			return comp;
		}
	}
}
uint32_t MiniFloat_From32F(float x, uint8_t is_signed, uint8_t exponent_bits, uint8_t mantissa_bits, int clamp_to_range)
{
	uint32_t	f32_u = *(uint32_t*)&x;
	uint32_t	s = f32_u >> (FP32_MANTISSA_BITS + FP32_EXPONENT_BITS);
	uint32_t	e = (f32_u & FP32_EXPONENT_MASK) >> FP32_MANTISSA_BITS;
	uint32_t	m = f32_u & FP32_MANTISSA_MASK;
	float		maxval;
	float		minval;
	float		min_normal;

	if (exponent_bits == 0)
	{
		// no bitcodes for signed infinity or NaNs

		if (fabsf(x) > (1 << (mantissa_bits)) - 1)
			return (s << mantissa_bits) | ((1 << mantissa_bits) - 1); // clamp to maximum signed value
		else
			return (s << mantissa_bits) | (uint32_t)fabsf(x);
	}
	maxval = (float)(powf(2.0f, (float)((1 << (exponent_bits - 1)) - 1))) * (1.0f + ((float)((1 << mantissa_bits) - 1)) / (float)(1 << mantissa_bits));
	minval = powf(2.0f, -((float)((1 << (exponent_bits - 1)) - 2 + mantissa_bits)));
	min_normal = powf(2.0f, -(float)((1 << (exponent_bits - 1)) - 2));

	if (e == FP32_EXPONENT_MASK >> FP32_MANTISSA_BITS) // signed infinity or NaN
	{
		if (m != 0)	// NaN
		{
			return (s << (exponent_bits + mantissa_bits)) | (((1 << exponent_bits) - 1) << mantissa_bits) | (m >> (FP32_MANTISSA_BITS - mantissa_bits)); // signed infinity
		}
		else // signed infinity
		{
			if (clamp_to_range)
				return (s << (exponent_bits + mantissa_bits)) | (((1 << exponent_bits) - 2) << mantissa_bits) | ((1 << mantissa_bits) - 1); // clamp to maximum signed value
			else
				return (s << (exponent_bits + mantissa_bits)) | (((1 << exponent_bits) - 1) << mantissa_bits); // signed infinity
		}
	}
	else if (fabsf(x) < minval)	// signed zero
	{
		return s << (exponent_bits + mantissa_bits);
	}
	else if (fabsf(x) > maxval)
	{
		if (clamp_to_range)
			return (s << (exponent_bits + mantissa_bits)) | (((1 << exponent_bits) - 2) << mantissa_bits) | ((1 << mantissa_bits) - 1); // clamp to maximum signed value
		else
			return (s << (exponent_bits + mantissa_bits)) | (((1 << exponent_bits) - 1) << mantissa_bits); // signed infinity
	}
	else if (fabsf(x) < min_normal) // subnormal
	{
		int shift = ((1 << (FP32_EXPONENT_BITS - 1)) + 1) - (1 << (exponent_bits - 1)) - mantissa_bits;
		int mtemp = (1 << (e - shift));
		if (shift < 0)
			m = m >> (FP32_MANTISSA_BITS + shift - 1);
		else
			m = mtemp | (m >> (FP32_MANTISSA_BITS - e + shift));
		m &= ((1 << mantissa_bits) - 1);
		e = 0;
		return (s << (exponent_bits + mantissa_bits)) | (e << mantissa_bits) | m;
	}
	else // normal
	{
		e = e + (((1 << (exponent_bits - 1)) - 1) - ((1 << (FP32_EXPONENT_BITS - 1)) - 1));
		m = m >> (FP32_MANTISSA_BITS - mantissa_bits);

		return (s << (exponent_bits + mantissa_bits)) | (e << mantissa_bits) | m;
	}
}

void DDS_WriteBits(uint8_t *block, uint32_t x, int start_bit, int num_bits)
{
	int i = 0;

	if (num_bits == 0)
		return;

	for (i = 0; i < num_bits; i++)
	{
		block[(start_bit + i) >> 3] &= ~(1 << ((start_bit + i) & 0x07));
		block[(start_bit + i) >> 3] |= ((x >> i) & 1) << ((start_bit + i) & 0x07);
	}
}
void DDS_BC6H_FitPartition(
	int max_partitions, 
	int partition_id,
	bc6h7_shape_index_t *partition,
	int *tmodes,
	int num_tmodes,
	float *pixel4x4_rgba_half, 
	vec3f32_t *trans_pixel, 
	vec3f32_t *mean,
	int is_signed,
	int *partition_indexes,
	int *mode_endpoint_quant00,
	int *mode_endpoint_quant01,
	int *mode_endpoint_quant10,
	int *mode_endpoint_quant11,
	int *best_header_mode,
	float *err,
	int *is_flipped)
{
	int m, i, j;
	vec3f32_t eigen[2];
	float mins[2] = {9999999999999.0f, 9999999999999.0f};
	float maxs[2] = {-9999999999999.0f, -9999999999999.0f};
	mat3x3f32_t cvmat[3];
	int q;
	int pmode;
	int partition_endpoints[2][2][3];
	vec3f32_t mode_endpoint[2][2];
	int *mode_endpoint_quant[2][2];
	float minval = is_signed ? -32768.0f : 0.0f;

	mode_endpoint_quant[0][0] = mode_endpoint_quant00;
	mode_endpoint_quant[0][1] = mode_endpoint_quant01;
	mode_endpoint_quant[1][0] = mode_endpoint_quant10;
	mode_endpoint_quant[1][1] = mode_endpoint_quant11;

	/*
	for tmodes, we can exit at the first valid mode we come across, as we're guaranteed that error will be >= for subsequent modes.
	similar for extmodes, but we MUST check these even if we have a valid result from tmodes, as the error can be smaller.
	*/

	DDS_BlockCovariancePartition3DPreCalcMeanf32(max_partitions, cvmat, pixel4x4_rgba_half, mean, partition);
	eigen[0] = DDS_BlockPrincipalEigenVector3Df32(cvmat[0]);
	if (max_partitions > 1)
		eigen[1] = DDS_BlockPrincipalEigenVector3Df32(cvmat[1]);

	// TODO: this should happen after adjusting endpoints to fit in [0, 65504] range
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			vec3f32_t transformed;
			int id = partition->index[i*4 + j];

			transformed = Vec3f32_Sub(trans_pixel[i*4 + j], mean[id]);

			mins[id] = Math_Minf32(mins[id], Vec3f32_Dot(eigen[id], transformed));
			maxs[id] = Math_Maxf32(maxs[id], Vec3f32_Dot(eigen[id], transformed));
		}
	}

	mode_endpoint[0][0] = Vec3f32_MA(mean[0], eigen[0], mins[0]);
	mode_endpoint[0][1] = Vec3f32_MA(mean[0], eigen[0], maxs[0]);
	if (max_partitions > 1)
	{
		mode_endpoint[1][0] = Vec3f32_MA(mean[1], eigen[1], mins[1]);
		mode_endpoint[1][1] = Vec3f32_MA(mean[1], eigen[1], maxs[1]);
	}

	// TODO: project backward to intersection of closest plane before clamping!
	mode_endpoint[0][0] = Vec3f32_ClampS(mode_endpoint[0][0], minval, 65535.0f);
	mode_endpoint[0][1] = Vec3f32_ClampS(mode_endpoint[0][1], minval, 65535.0f);
	if (max_partitions > 1)
	{
		mode_endpoint[1][0] = Vec3f32_ClampS(mode_endpoint[1][0], minval, 65535.0f);
		mode_endpoint[1][1] = Vec3f32_ClampS(mode_endpoint[1][1], minval, 65535.0f);
	}

	for (i = 0; i < 3; i++)
	{
		partition_endpoints[0][0][i] = (int)mode_endpoint[0][0].v[i];
		partition_endpoints[0][1][i] = (int)mode_endpoint[0][1].v[i];
		if (max_partitions > 1)
		{
			partition_endpoints[1][0][i] = (int)mode_endpoint[1][0].v[i];
			partition_endpoints[1][1][i] = (int)mode_endpoint[1][1].v[i];
		}
	}

	float minminerr = 0.0f;
	float invdiff[2] = {maxs[0] - mins[0], maxs[1] - mins[1]};
	float diff[2] = {maxs[0] - mins[0], maxs[1] - mins[1]};
	float invscale = max_partitions == 1 ? 1.0f / 15.0f : 1.0f / 7.0f;
	float scale = max_partitions == 1 ? 15.0f : 7.0f;

	invdiff[0] = invdiff[0] != 0.0f ? 1.0f / diff[0] : 0.0f;
	invdiff[1] = invdiff[1] != 0.0f ? 1.0f / diff[1] : 0.0f;

	// TODO: this should actually be inside the pmode loop as the endpoints will be further quantised
	if ((diff[0] != 0.0f) || (diff[1] != 0.0f))
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				int id;
				float len;
				float d;
				vec3f32_t temp;
				vec3f32_t on_line;

				id = partition->index[i*4 + j];
				if(diff[id] == 0.0f)
					continue;
				temp = Vec3f32_Sub(trans_pixel[i*4 + j], mean[id]);
				d = Vec3f32_Dot(temp, eigen[id]);
				d = (d - mins[id]) * invdiff[id];
				d = Math_Clampf32(d, 0.0f, 1.0f);
				d = floorf(d * scale + 0.5f);
				partition_indexes[i*4 + j] = (int)d;
				d = (d * invscale) * diff[id] + mins[id];
				on_line = Vec3f32_Scale(eigen[id], d);
				len = Vec3f32_LenSq(Vec3f32_Sub(temp, on_line));
				minminerr += len;
			}
		}

	for (pmode = 0; pmode < num_tmodes; pmode++)
	{
		q = tmodes[pmode];
		int index0[2];
		int index1[2];
		//float lerr = 0.0f;
		int is_transformed = ((q == 9) || (q == 10)) ? 0 : 1;
		int best_sub_mode;
		int local_endpoints[2][2][3];

		index0[0] = partition_indexes[0] > (q < 10 ? 3 : 7) ? 1 : 0;
		index0[1] = partition_indexes[0] > (q < 10 ? 3 : 7) ? 0 : 1;
		if (max_partitions > 1)
		{
			index1[0] = partition_indexes[g_bc6h_fixup[partition_id]] > (q < 10 ? 3 : 7) ? 1 : 0;
			index1[1] = partition_indexes[g_bc6h_fixup[partition_id]] > (q < 10 ? 3 : 7) ? 0 : 1;
		}

		if ((index0[0] == 1) || ((max_partitions > 1) && (index1[0] == 1)))
		{
			DDS_BC6HQuantiseIntEndpoints(max_partitions, 16, (int*)g_bc6h_desc[q].endpoint_bits[0][0], partition_endpoints[0][index0[0]], partition_endpoints[0][index0[1]], partition_endpoints[1][index1[0]], partition_endpoints[1][index1[1]], &local_endpoints[0][0][0], &local_endpoints[0][1][0], &local_endpoints[1][0][0], &local_endpoints[1][1][0]);

			if (is_transformed)
				for (m = 0; m < 3; m++)
					DDS_BC6HInvTransformNoWrap(max_partitions, local_endpoints[0][0][m], &local_endpoints[0][1][m], &local_endpoints[1][0][m], &local_endpoints[1][1][m]);

			best_sub_mode = DDS_BC6HGetAllowedSubMode(q, &local_endpoints[0][0][0], &local_endpoints[0][1][0], &local_endpoints[1][0][0], &local_endpoints[1][1][0], is_transformed, is_signed);

			if (best_sub_mode == -1)
				continue;

			*is_flipped = 1;
		}
		else
		{
			DDS_BC6HQuantiseIntEndpoints(max_partitions, 16, (int*)g_bc6h_desc[q].endpoint_bits[0][0], partition_endpoints[0][0], partition_endpoints[0][1], partition_endpoints[1][0], partition_endpoints[1][1], &local_endpoints[0][0][0], &local_endpoints[0][1][0], &local_endpoints[1][0][0], &local_endpoints[1][1][0]);

			if (is_transformed)
				for (m = 0; m < 3; m++)
					DDS_BC6HInvTransformNoWrap(max_partitions, local_endpoints[0][0][m], &local_endpoints[0][1][m], &local_endpoints[1][0][m], &local_endpoints[1][1][m]);

			best_sub_mode = DDS_BC6HGetAllowedSubMode(q, &local_endpoints[0][0][0], &local_endpoints[0][1][0], &local_endpoints[1][0][0], &local_endpoints[1][1][0], is_transformed, is_signed);

			if (best_sub_mode == -1)
				continue;

			*is_flipped = 0;
		}

		for (i = 0; i < max_partitions; i++)
			for (j = 0; j < 2; j++)
				for (m = 0; m < 3; m++)
					mode_endpoint_quant[i][j][m] = local_endpoints[i][j][m];

		*best_header_mode = best_sub_mode;
		*err = minminerr;
		break;
	}
}

mat3x3f32_t DDS_BlockCovariance3Df32(float *pixel4x4_rgba, float *mean, float alpha_cutoff)
{
	int i, j, k, m;
	double val[3][3] = {0.0};
	double count = 0;

	mean[0] = 0.0f;
	mean[1] = 0.0f;
	mean[2] = 0.0f;

	for (k = 0; k < 4; k++)
		for (m = 0; m < 4; m++)
		{
			if (pixel4x4_rgba[(k*4 + m)*4 + 3] < alpha_cutoff)
				continue;
			mean[0] += pixel4x4_rgba[(k*4 + m)*4 + 0];
			mean[1] += pixel4x4_rgba[(k*4 + m)*4 + 1];
			mean[2] += pixel4x4_rgba[(k*4 + m)*4 + 2];
			count++;
		}

	mean[0] /= (float)(count ? count : 1.0);
	mean[1] /= (float)(count ? count : 1.0);
	mean[2] /= (float)(count ? count : 1.0);

	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			for (k = 0; k < 4; k++)
				for (m = 0; m < 4; m++)
				{
					if (pixel4x4_rgba[(k*4 + m)*4 + 3] < alpha_cutoff)
						continue;
					val[i][j] += (pixel4x4_rgba[(k*4 + m)*4 + i] - mean[i]) * (pixel4x4_rgba[(k*4 + m)*4 + j] - mean[j]);
				}

	return Mat3x3f32_Mat(	(float)val[0][0], (float)val[0][1], (float)val[0][2],
							(float)val[1][0], (float)val[1][1], (float)val[1][2],
							(float)val[2][0], (float)val[2][1], (float)val[2][2]);
}

void DDS_UnpackTof32(uint32_t x, uint8_t r_bits, uint8_t g_bits, uint8_t b_bits, uint8_t a_bits, float *rgba)
{
	uint8_t temp[4];

	temp[0] = ((x >> (g_bits + b_bits + a_bits)) & ((1 << r_bits) - 1)) << (8 - r_bits);
	if (g_bits)
		temp[1] = ((x >> (b_bits + a_bits)) & ((1 << g_bits) - 1)) << (8 - g_bits);
	if (b_bits)
		temp[2] = ((x >> (a_bits)) & ((1 << b_bits) - 1)) << (8 - b_bits);
	if (a_bits)
		temp[3] = ((x >> (0)) & ((1 << a_bits) - 1)) << (8 - a_bits);

	rgba[0] = (float)(temp[0] | (temp[0] >> r_bits));
	rgba[1] = (float)(temp[1] | (temp[1] >> g_bits));
	rgba[2] = (float)(temp[2] | (temp[2] >> b_bits));
	if (a_bits)
		rgba[3] = (float)(temp[3] | (temp[3] >> a_bits));
}
int DDS_BresenhamPath16Bit(vec3u8_t path_quantised[64], vec3u8_t start_quantised, vec3u8_t end_quantised)
{
	int x1 = Vec3u8_GetComponent(start_quantised, 0);
	int y1 = Vec3u8_GetComponent(start_quantised, 1);
	int z1 = Vec3u8_GetComponent(start_quantised, 2);
	int x2 = Vec3u8_GetComponent(end_quantised, 0);
	int y2 = Vec3u8_GetComponent(end_quantised, 1);
	int z2 = Vec3u8_GetComponent(end_quantised, 2);
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int dz = abs(z2 - z1);
	int xs;
	int ys;
	int zs;
	int count = 0;

	if (x2 > x1)
		xs = 1;
	else
		xs = -1;
	if (y2 > y1)
		ys = 1;
	else
		ys = -1;
	if (z2 > z1)
		zs = 1;
	else
		zs = -1;

	path_quantised[count] = start_quantised;

	// Driving axis is X-axis"
	if (dx >= dy && dx >= dz) 
	{
		int p1 = 2 * dy - dx;
		int p2 = 2 * dz - dx;
		while (!((x1 == x2) && (y1 == y2) && (z1 == z2)))
		{
			x1 += xs;
			if (p1 >= 0) 
			{
				y1 += ys;
				p1 -= 2 * dx;
			}
			if (p2 >= 0) 
			{
				z1 += zs;
				p2 -= 2 * dx;
			}
			p1 += 2 * dy;
			p2 += 2 * dz;

			//printf("%i, %i, %i,\n", x1, y1, z1);
			count++;
			path_quantised[count] = Vec3u8_Vec((uint8_t)x1, (uint8_t)y1, (uint8_t)z1);
			// x1, y1, z1
		}
		// Driving axis is Y-axis"
	}
	else if (dy >= dx && dy >= dz) 
	{
		int p1 = 2 * dx - dy;
		int p2 = 2 * dz - dy;
		while (!((x1 == x2) && (y1 == y2) && (z1 == z2)))
		{
			y1 += ys;
			if (p1 >= 0) 
			{
				x1 += xs;
				p1 -= 2 * dy;
			}
			if (p2 >= 0) 
			{
				z1 += zs;
				p2 -= 2 * dy;
			}
			p1 += 2 * dx;
			p2 += 2 * dz;

			//printf("%i, %i, %i,\n", x1, y1, z1);
			count++;
			path_quantised[count] = Vec3u8_Vec((uint8_t)x1, (uint8_t)y1, (uint8_t)z1);
		}

		// Driving axis is Z-axis"
	}
	else 
	{
		int p1 = 2 * dy - dz;
		int p2 = 2 * dx - dz;
		while (!((x1 == x2) && (y1 == y2) && (z1 == z2)))
		{
			z1 += zs;
			if (p1 >= 0) 
			{
				y1 += ys;
				p1 -= 2 * dz;
			}
			if (p2 >= 0) 
			{
				x1 += xs;
				p2 -= 2 * dz;
			}
			p1 += 2 * dy;
			p2 += 2 * dx;

			//printf("%i, %i, %i,\n", x1, y1, z1);
			count++;
			path_quantised[count] = Vec3u8_Vec((uint8_t)x1, (uint8_t)y1, (uint8_t)z1);
		}
	}
	//printf("count: %i\n", count);
	return count + 1;
}
int DDS_BresenhamPath16BitVisitAll(vec3u8_t path_quantised[128], vec3u8_t start_quantised, vec3u8_t end_quantised)
{
	int x1 = Vec3u8_GetComponent(start_quantised, 0);
	int y1 = Vec3u8_GetComponent(start_quantised, 1);
	int z1 = Vec3u8_GetComponent(start_quantised, 2);
	int x2 = Vec3u8_GetComponent(end_quantised, 0);
	int y2 = Vec3u8_GetComponent(end_quantised, 1);
	int z2 = Vec3u8_GetComponent(end_quantised, 2);
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int dz = abs(z2 - z1);
	int xs;
	int ys;
	int zs;
	int count = 0;

	if (x2 > x1)
		xs = 1;
	else
		xs = -1;
	if (y2 > y1)
		ys = 1;
	else
		ys = -1;
	if (z2 > z1)
		zs = 1;
	else
		zs = -1;

	path_quantised[count] = start_quantised;

	// Driving axis is X-axis"
	if (dx >= dy && dx >= dz) 
	{
		int p1 = 2 * dy - dx;
		int p2 = 2 * dz - dx;
		while (!((x1 == x2) && (y1 == y2) && (z1 == z2)))
		{
			if (p1 >= 0) 
			{
				y1 += ys;
				p1 -= 2 * dx;
			}
			else if (p2 >= 0) 
			{
				z1 += zs;
				p2 -= 2 * dx;
			}
			else
			{
				x1 += xs;
				p1 += 2 * dy;
				p2 += 2 * dz;
			}

			//printf("%i, %i, %i, (%i)\n", x1, y1, z1, count);
			count++;
			path_quantised[count] = Vec3u8_Vec((uint8_t)x1, (uint8_t)y1, (uint8_t)z1);
			// x1, y1, z1
		}
		// Driving axis is Y-axis"
	}
	else if (dy >= dx && dy >= dz) 
	{
		int p1 = 2 * dx - dy;
		int p2 = 2 * dz - dy;
		while (!((x1 == x2) && (y1 == y2) && (z1 == z2)))
		{
			if (p1 >= 0) 
			{
				x1 += xs;
				p1 -= 2 * dy;
			}
			else if (p2 >= 0) 
			{
				z1 += zs;
				p2 -= 2 * dy;
			}
			else
			{
				y1 += ys;
				p1 += 2 * dx;
				p2 += 2 * dz;
			}

			//printf("%i, %i, %i, (%i)\n", x1, y1, z1, count);
			count++;
			path_quantised[count] = Vec3u8_Vec((uint8_t)x1, (uint8_t)y1, (uint8_t)z1);
		}

		// Driving axis is Z-axis"
	}
	else 
	{
		int p1 = 2 * dy - dz;
		int p2 = 2 * dx - dz;
		while (!((x1 == x2) && (y1 == y2) && (z1 == z2)))
		{
			if (p1 >= 0) 
			{
				y1 += ys;
				p1 -= 2 * dz;
			}
			else if (p2 >= 0) 
			{
				x1 += xs;
				p2 -= 2 * dz;
			}
			else
			{
				z1 += zs;
				p1 += 2 * dy;
				p2 += 2 * dx;
			}

			//printf("%i, %i, %i, (%i)\n", x1, y1, z1, count);
			count++;
			path_quantised[count] = Vec3u8_Vec((uint8_t)x1, (uint8_t)y1, (uint8_t)z1);
		}
	}
		//printf("count: %i\n", count);
	return count + 1;
}
vec3u8_t DDS_BresenhamPath16BitVisitLastSphere(vec3u8_t start_quantised, vec3u8_t end_quantised, int half_sphere_reverse_map[11*11*11][2])
{
	int x1 = Vec3u8_GetComponent(start_quantised, 0);
	int y1 = Vec3u8_GetComponent(start_quantised, 1);
	int z1 = Vec3u8_GetComponent(start_quantised, 2);
	int x2 = Vec3u8_GetComponent(end_quantised, 0);
	int y2 = Vec3u8_GetComponent(end_quantised, 1);
	int z2 = Vec3u8_GetComponent(end_quantised, 2);
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int dz = abs(z2 - z1);
	int xs;
	int ys;
	int zs;

	vec3u8_t last_point = start_quantised;

	if (x2 > x1)
		xs = 1;
	else
		xs = -1;
	if (y2 > y1)
		ys = 1;
	else
		ys = -1;
	if (z2 > z1)
		zs = 1;
	else
		zs = -1;

	// Driving axis is X-axis"
	if (dx >= dy && dx >= dz) 
	{
		int p1 = 2 * dy - dx;
		int p2 = 2 * dz - dx;
		while (!((x1 == x2) && (y1 == y2) && (z1 == z2)))
		{
			if (p1 >= 0) 
			{
				y1 += ys;
				p1 -= 2 * dx;
			}
			else if (p2 >= 0) 
			{
				z1 += zs;
				p2 -= 2 * dx;
			}
			else
			{
				x1 += xs;
				p1 += 2 * dy;
				p2 += 2 * dz;
			}
			if ((x1 - start_quantised.v[0])*(x1 - start_quantised.v[0]) >= 25)
				break;
			if ((y1 - start_quantised.v[1])*(y1 - start_quantised.v[1]) >= 25)
				break;
			if ((z1 - start_quantised.v[2])*(z1 - start_quantised.v[2]) >= 25)
				break;
			if (half_sphere_reverse_map[(x1 - start_quantised.v[0] + 5)*11*11 + (y1 - start_quantised.v[1] + 5)*11 + z1 - start_quantised.v[2] + 5][0] == -1)
				break;

			//printf("%i, %i, %i, (%i)\n", x1, y1, z1, count);
			last_point = Vec3u8_Vec((uint8_t)x1, (uint8_t)y1, (uint8_t)z1);
			// x1, y1, z1
		}
		// Driving axis is Y-axis"
	}
	else if (dy >= dx && dy >= dz) 
	{
		int p1 = 2 * dx - dy;
		int p2 = 2 * dz - dy;
		while (!((x1 == x2) && (y1 == y2) && (z1 == z2)))
		{
			if (p1 >= 0) 
			{
				x1 += xs;
				p1 -= 2 * dy;
			}
			else if (p2 >= 0) 
			{
				z1 += zs;
				p2 -= 2 * dy;
			}
			else
			{
				y1 += ys;
				p1 += 2 * dx;
				p2 += 2 * dz;
			}
			if ((x1 - start_quantised.v[0])*(x1 - start_quantised.v[0]) >= 25)
				break;
			if ((y1 - start_quantised.v[1])*(y1 - start_quantised.v[1]) >= 25)
				break;
			if ((z1 - start_quantised.v[2])*(z1 - start_quantised.v[2]) >= 25)
				break;
			if (half_sphere_reverse_map[(x1 - start_quantised.v[0] + 5)*11*11 + (y1 - start_quantised.v[1] + 5)*11 + z1 - start_quantised.v[2] + 5][0] == -1)
				break;

			//printf("%i, %i, %i, (%i)\n", x1, y1, z1, count);
			last_point = Vec3u8_Vec((uint8_t)x1, (uint8_t)y1, (uint8_t)z1);
		}

		// Driving axis is Z-axis"
	}
	else 
	{
		int p1 = 2 * dy - dz;
		int p2 = 2 * dx - dz;
		while (!((x1 == x2) && (y1 == y2) && (z1 == z2)))
		{
			if (p1 >= 0) 
			{
				y1 += ys;
				p1 -= 2 * dz;
			}
			else if (p2 >= 0) 
			{
				x1 += xs;
				p2 -= 2 * dz;
			}
			else
			{
				z1 += zs;
				p1 += 2 * dy;
				p2 += 2 * dx;
			}
			if ((x1 - start_quantised.v[0])*(x1 - start_quantised.v[0]) >= 25)
				break;
			if ((y1 - start_quantised.v[1])*(y1 - start_quantised.v[1]) >= 25)
				break;
			if ((z1 - start_quantised.v[2])*(z1 - start_quantised.v[2]) >= 25)
				break;
			if (half_sphere_reverse_map[(x1 - start_quantised.v[0] + 5)*11*11 + (y1 - start_quantised.v[1] + 5)*11 + z1 - start_quantised.v[2] + 5][0] == -1)
				break;

			//printf("%i, %i, %i, (%i)\n", x1, y1, z1, count);
			last_point = Vec3u8_Vec((uint8_t)x1, (uint8_t)y1, (uint8_t)z1);
		}
	}
	//printf("count: %i\n", count);
	return last_point;
}

void DDS_RoundEndpointsToRGB565(vec3f32_t *colour)
{
	colour[0].v[0] = (float)((int)(31 * (colour[0].v[0] + 4.0f)) / 255);
	colour[0].v[1] = (float)((int)(63 * (colour[0].v[1] + 2.0f)) / 255);
	colour[0].v[2] = (float)((int)(31 * (colour[0].v[2] + 4.0f)) / 255);

	colour[1].v[0] = (float)((int)(31 * (colour[1].v[0] + 4.0f)) / 255);
	colour[1].v[1] = (float)((int)(63 * (colour[1].v[1] + 2.0f)) / 255);
	colour[1].v[2] = (float)((int)(31 * (colour[1].v[2] + 4.0f)) / 255);
	
	colour[0] = Vec3f32_ClampS(colour[0], 0.0f, 255.0f);
	colour[1] = Vec3f32_ClampS(colour[1], 0.0f, 255.0f);

}

int DDS_BresenhamPath16BitVisitAllClamp(vec3u8_t path_quantised[128], vec3f32_t start_quantisedf32, vec3f32_t end_quantisedf32)
{
	int x1 = (int)Vec3f32_GetComponent(start_quantisedf32, 0);
	int y1 = (int)Vec3f32_GetComponent(start_quantisedf32, 1);
	int z1 = (int)Vec3f32_GetComponent(start_quantisedf32, 2);
	int x2 = (int)Vec3f32_GetComponent(end_quantisedf32, 0);
	int y2 = (int)Vec3f32_GetComponent(end_quantisedf32, 1);
	int z2 = (int)Vec3f32_GetComponent(end_quantisedf32, 2);
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int dz = abs(z2 - z1);
	int xs;
	int ys;
	int zs;
	int count = 0;

	if (x2 > x1)
		xs = 1;
	else
		xs = -1;
	if (y2 > y1)
		ys = 1;
	else
		ys = -1;
	if (z2 > z1)
		zs = 1;
	else
		zs = -1;

	if (dx >= dy && dx >= dz) 
	{
		int p1 = 2 * dy - dx;
		int p2 = 2 * dz - dx;
		while (!((x1 == x2) && (y1 == y2) && (z1 == z2)))
		{
			//printf("xyz: %5i %5i %5i\n", x1, y1, z1);
			if ((x1 <= 31 && x1 >= 0) || (y1 <= 63 && y1 >= 0) || (z1 <= 31 && z1 >= 0))
				break;
			if (p1 >= 0) 
			{
				y1 += ys;
				p1 -= 2 * dx;
			}
			else if (p2 >= 0) 
			{
				z1 += zs;
				p2 -= 2 * dx;
			}
			else
			{
				x1 += xs;
				p1 += 2 * dy;
				p2 += 2 * dz;
			}
		}
	}
	else if (dy >= dx && dy >= dz) 
	{
		int p1 = 2 * dx - dy;
		int p2 = 2 * dz - dy;
		while (!((x1 == x2) && (y1 == y2) && (z1 == z2)))
		{
			//printf("xyz: %5i %5i %5i\n", x1, y1, z1);
			if ((x1 <= 31 && x1 >= 0) || (y1 <= 63 && y1 >= 0) || (z1 <= 31 && z1 >= 0))
				break;
			if (p1 >= 0) 
			{
				x1 += xs;
				p1 -= 2 * dy;
			}
			else if (p2 >= 0) 
			{
				z1 += zs;
				p2 -= 2 * dy;
			}
			else
			{
				y1 += ys;
				p1 += 2 * dx;
				p2 += 2 * dz;
			}
		}
	}
	else 
	{
		int p1 = 2 * dy - dz;
		int p2 = 2 * dx - dz;
		while (!((x1 == x2) && (y1 == y2) && (z1 == z2)))
		{
			//printf("xyz: %5i %5i %5i\n", x1, y1, z1);
			if ((x1 <= 31 && x1 >= 0) || (y1 <= 63 && y1 >= 0) || (z1 <= 31 && z1 >= 0))
				break;
			if (p1 >= 0) 
			{
				y1 += ys;
				p1 -= 2 * dz;
			}
			else if (p2 >= 0) 
			{
				x1 += xs;
				p2 -= 2 * dz;
			}
			else
			{
				z1 += zs;
				p1 += 2 * dy;
				p2 += 2 * dx;
			}
		}
	}

	path_quantised[count] = Vec3i32_ToVec3u8(Vec3i32_Clamp(Vec3i32_Vec(x1, y1, z1), Vec3i32_Vec(0, 0, 0), Vec3i32_Vec(31, 63, 31)));

	// Driving axis is X-axis"
	if (dx >= dy && dx >= dz) 
	{
		int p1 = 2 * dy - dx;
		int p2 = 2 * dz - dx;
		while (!((x1 == x2) && (y1 == y2) && (z1 == z2)))
		{
			vec3u8_t newpos;
			if (p1 >= 0) 
			{
				y1 += ys;
				p1 -= 2 * dx;
			}
			else if (p2 >= 0) 
			{
				z1 += zs;
				p2 -= 2 * dx;
			}
			else
			{
				x1 += xs;
				p1 += 2 * dy;
				p2 += 2 * dz;
			}

			if (((x1 > 31 || x1 < 0) && (y1 > 63 || y1 < 0) && (z1 > 31 || z1 < 0)))
				break;

			newpos = Vec3i32_ToVec3u8(Vec3i32_Clamp(Vec3i32_Vec(x1, y1, z1), Vec3i32_Vec(0, 0, 0), Vec3i32_Vec(31, 63, 31)));

			//printf("count = %i (x1/y1/z1 = %i %i %i, x2/y2/z2 = %i %i %i)\n", count, newpos.v[0], newpos.v[1], newpos.v[2], x2, y2, z2);
			if (newpos.v[0] == path_quantised[count].v[0] && 
				newpos.v[1] == path_quantised[count].v[1] &&
				newpos.v[2] == path_quantised[count].v[2])
				continue;
			//printf("%i, %i, %i, (%i)\n", x1, y1, z1, count);
			count++;

			path_quantised[count] = Vec3i32_ToVec3u8(Vec3i32_Clamp(Vec3i32_Vec(x1, y1, z1), Vec3i32_Vec(0, 0, 0), Vec3i32_Vec(31, 63, 31)));
			// x1, y1, z1
		}
		// Driving axis is Y-axis"
	}
	else if (dy >= dx && dy >= dz) 
	{
		int p1 = 2 * dx - dy;
		int p2 = 2 * dz - dy;
		while (!((x1 == x2) && (y1 == y2) && (z1 == z2)))
		{
			vec3u8_t newpos;
			if (p1 >= 0) 
			{
				x1 += xs;
				p1 -= 2 * dy;
			}
			else if (p2 >= 0) 
			{
				z1 += zs;
				p2 -= 2 * dy;
			}
			else
			{
				y1 += ys;
				p1 += 2 * dx;
				p2 += 2 * dz;
			}

			if (((x1 > 31 || x1 < 0) && (y1 > 63 || y1 < 0) && (z1 > 31 || z1 < 0)))
				break;

			newpos = Vec3i32_ToVec3u8(Vec3i32_Clamp(Vec3i32_Vec(x1, y1, z1), Vec3i32_Vec(0, 0, 0), Vec3i32_Vec(31, 63, 31)));

			//printf("count = %i (x1/y1/z1 = %i %i %i, x2/y2/z2 = %i %i %i)\n", count, newpos.v[0], newpos.v[1], newpos.v[2], x2, y2, z2);
			if (newpos.v[0] == path_quantised[count].v[0] && 
				newpos.v[1] == path_quantised[count].v[1] &&
				newpos.v[2] == path_quantised[count].v[2])
				continue;

			//printf("%i, %i, %i, (%i)\n", x1, y1, z1, count);
			count++;
			path_quantised[count] = Vec3i32_ToVec3u8(Vec3i32_Clamp(Vec3i32_Vec(x1, y1, z1), Vec3i32_Vec(0, 0, 0), Vec3i32_Vec(31, 63, 31)));
		}

		// Driving axis is Z-axis"
	}
	else 
	{
		int p1 = 2 * dy - dz;
		int p2 = 2 * dx - dz;
		while (!((x1 == x2) && (y1 == y2) && (z1 == z2)))
		{
			vec3u8_t newpos;
			if (p1 >= 0) 
			{
				y1 += ys;
				p1 -= 2 * dz;
			}
			else if (p2 >= 0) 
			{
				x1 += xs;
				p2 -= 2 * dz;
			}
			else
			{
				z1 += zs;
				p1 += 2 * dy;
				p2 += 2 * dx;
			}

			if (((x1 > 31 || x1 < 0) && (y1 > 63 || y1 < 0) && (z1 > 31 || z1 < 0)))
				break;

			newpos = Vec3i32_ToVec3u8(Vec3i32_Clamp(Vec3i32_Vec(x1, y1, z1), Vec3i32_Vec(0, 0, 0), Vec3i32_Vec(31, 63, 31)));

			//printf("count = %i (x1/y1/z1 = %i %i %i, x2/y2/z2 = %i %i %i)\n", count, newpos.v[0], newpos.v[1], newpos.v[2], x2, y2, z2);
			if (newpos.v[0] == path_quantised[count].v[0] && 
				newpos.v[1] == path_quantised[count].v[1] &&
				newpos.v[2] == path_quantised[count].v[2])
				continue;

			//printf("%i, %i, %i, (%i)\n", x1, y1, z1, count);
			count++;
			path_quantised[count] = Vec3i32_ToVec3u8(Vec3i32_Clamp(Vec3i32_Vec(x1, y1, z1), Vec3i32_Vec(0, 0, 0), Vec3i32_Vec(31, 63, 31)));
		}
	}
	//printf("count: %i\n", count);
	return count + 1;
}
