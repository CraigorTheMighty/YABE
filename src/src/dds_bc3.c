#include <windows.h>
#include <stdint.h>
#include <math.h>

#include "../inc/system.h"
#include "../inc/math.h"
#include "../inc/vecmat.h"
#include "../inc/dds_const.h"
#include "../inc/dds_util.h"
#include "../inc/dds.h"

void DDS_EncodeBC3Block(uint8_t *block, double *pixel4x4_rgba, int is_premultiplied, int is_srgb, int is_signed, int block_x, int block_y)
{
	float pixel[64];
	int i;
	for (i = 0; i < 64; i++)
		pixel[i] = (float)pixel4x4_rgba[i];

	DDS_EncodeBC1Block(&block[8], pixel4x4_rgba, is_premultiplied, is_srgb, is_signed, block_x, block_y, 0, 1);
	//DDS_EncodeBC4Block(&block[0], pixel4x4_rgba, is_premultiplied, is_srgb, is_signed, block_x, block_y);
	DDS_EncodeBC4Blockf32(3, &block[0], pixel, is_premultiplied, is_srgb, is_signed, block_x, block_y);
#if 0
	float pixel[64];
	int i, j, k;
	int alpha_index[4][4];
	uint8_t alpha_val[8];
	uint32_t temp32;

	for (i = 0; i < 64; i++)
		pixel[i] = (float)pixel4x4_rgba[i];

	DDS_EncodeBC1BlockNormalf32(g_system.opts.turbo, &block[8], pixel, 0, 0, 0, block_x, block_y, 0);

	alpha_val[0] = (uint8_t)pixel4x4_rgba[3];
	alpha_val[1] = (uint8_t)pixel4x4_rgba[3];

	for (i = 1; i < 16; i++)
	{
		alpha_val[0] = Math_Minu8(alpha_val[0], (uint8_t)pixel4x4_rgba[i*4 + 3]);
		alpha_val[1] = Math_Maxu8(alpha_val[1], (uint8_t)pixel4x4_rgba[i*4 + 3]);
	}

	DDS_GenBC3_4Alphau8(BC3_4_ALPHA_ENCODE_FULL, alpha_val, (uint8_t)alpha_val[0], (uint8_t)alpha_val[1]);

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			int indexl = 0;
			double len = fabs(pixel4x4_rgba[(i*4 + j)*4 + 3] - (double)alpha_val[0]);
			for (k = 1; k < 8; k++)
			{
				double lenl = fabs(pixel4x4_rgba[(i*4 + j)*4 + 3] - (double)alpha_val[k]);
				if (lenl < len)
				{
					len = lenl;
					indexl = k;
				}
			}
			alpha_index[i][j] = indexl;
		}
	block[0] = alpha_val[0];
	block[1] = alpha_val[1];
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
#endif
}

void DDS_DecodeBC3Block(uint8_t *block, float *pixel4x4_rgba, int is_premultiplied, int is_srgb, int is_signed, int block_x, int block_y)
{
	uint8_t colour[4][3];
	uint8_t alpha[8];
	int alpha_index[16];
	int i, j;
	uint32_t alpha_block[2];

	alpha[0] = block[0];
	alpha[1] = block[1];

	if (alpha[0] > alpha[1])
	{
		alpha[2] = (uint8_t)(alpha[0] * 6.0 / 7.0 + alpha[1] * 1.0 / 7.0);
		alpha[3] = (uint8_t)(alpha[0] * 5.0 / 7.0 + alpha[1] * 2.0 / 7.0);
		alpha[4] = (uint8_t)(alpha[0] * 4.0 / 7.0 + alpha[1] * 3.0 / 7.0);
		alpha[5] = (uint8_t)(alpha[0] * 3.0 / 7.0 + alpha[1] * 4.0 / 7.0);
		alpha[6] = (uint8_t)(alpha[0] * 2.0 / 7.0 + alpha[1] * 5.0 / 7.0);
		alpha[7] = (uint8_t)(alpha[0] * 1.0 / 7.0 + alpha[1] * 6.0 / 7.0);
	}
	else
	{
		alpha[2] = (uint8_t)(alpha[0] * 4.0 / 5.0 + alpha[1] * 1.0 / 5.0);
		alpha[3] = (uint8_t)(alpha[0] * 3.0 / 5.0 + alpha[1] * 2.0 / 5.0);
		alpha[4] = (uint8_t)(alpha[0] * 2.0 / 5.0 + alpha[1] * 3.0 / 5.0);
		alpha[5] = (uint8_t)(alpha[0] * 1.0 / 5.0 + alpha[1] * 4.0 / 5.0);
		alpha[6] = 0;
		alpha[7] = 255;
	}

	alpha_block[0] = block[2];
	alpha_block[0] |= block[3] << 8;
	alpha_block[0] |= block[4] << 16;
	alpha_block[1] = block[5];
	alpha_block[1] |= block[6] << 8;
	alpha_block[1] |= block[7] << 16;

	for (i = 0; i < 2; i++)
	{
		alpha_index[0 + i * 8] = (alpha_block[i] >> 0) & 0x07;
		alpha_index[1 + i * 8] = (alpha_block[i] >> 3) & 0x07;
		alpha_index[2 + i * 8] = (alpha_block[i] >> 6) & 0x07;
		alpha_index[3 + i * 8] = (alpha_block[i] >> 9) & 0x07;
		alpha_index[4 + i * 8] = (alpha_block[i] >> 12) & 0x07;
		alpha_index[5 + i * 8] = (alpha_block[i] >> 15) & 0x07;
		alpha_index[6 + i * 8] = (alpha_block[i] >> 18) & 0x07;
		alpha_index[7 + i * 8] = (alpha_block[i] >> 21) & 0x07;
	}

	colour[0][0] = (*((uint16_t*)&block[8]) & 0xF800) >> 8;
	colour[0][1] = (*((uint16_t*)&block[8]) & 0x07E0) >> 3;
	colour[0][2] = (*((uint16_t*)&block[8]) & 0x001F) << 3;

	colour[1][0] = (*((uint16_t*)&block[10]) & 0xF800) >> 8;
	colour[1][1] = (*((uint16_t*)&block[10]) & 0x07E0) >> 3;
	colour[1][2] = (*((uint16_t*)&block[10]) & 0x001F) << 3;

	for (i = 0; i < 3; i++)
	{
		colour[2][i] = (uint8_t)(colour[0][i] * (2.0/3.0) + colour[1][i] * (1.0 / 3.0));
		colour[3][i] = (uint8_t)(colour[0][i] * (1.0/3.0) + colour[1][i] * (2.0 / 3.0));
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			int index = (block[12 + i] >> (j * 2)) & 0x03;

			pixel4x4_rgba[i * 16 + j * 4 + 0] = (float)colour[index][0];
			pixel4x4_rgba[i * 16 + j * 4 + 1] = (float)colour[index][1];
			pixel4x4_rgba[i * 16 + j * 4 + 2] = (float)colour[index][2];
			pixel4x4_rgba[i * 16 + j * 4 + 3] = (float)alpha[alpha_index[i * 4 + j]];
		}
	}
}
