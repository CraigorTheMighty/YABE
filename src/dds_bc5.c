#include <stdint.h>
#include <math.h>

#include "../inc/math.h"
#include "../inc/vecmat.h"
#include "../inc/dds_const.h"
#include "../inc/dds_util.h"
#include "../inc/dds.h"

void DDS_EncodeBC5Block(uint8_t *block, double *pixel4x4_rgba, int is_premultiplied, int is_srgb, int is_signed, int block_x, int block_y)
{
	float pixel[64];
	int i;
	for (i = 0; i < 64; i++)
		pixel[i] = (float)pixel4x4_rgba[i];
	//	for (i = 0; i < 64; i++)
	//		pixel[i] = (float)(rand()%256);
	//	for (i = 0; i < 64; i++)
	//		pixel[i] = Math_Clampf32(64, 0.0f, 255.0f);

	DDS_EncodeBC4Blockf32(0, &block[0], pixel, is_premultiplied, is_srgb, is_signed, block_x, block_y);
	DDS_EncodeBC4Blockf32(1, &block[8], pixel, is_premultiplied, is_srgb, is_signed, block_x, block_y);
}

void DDS_DecodeBC5Block(uint8_t *block, float *pixel4x4_rgba, int is_premultiplied, int is_srgb, int is_signed, int block_x, int block_y)
{
	int16_t red[8];
	int16_t green[8];
	int red_index[16];
	int green_index[16];
	int i, j;
	uint32_t red_block[2];
	uint32_t green_block[2];

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

	if (is_signed)
	{
		green[0] = (int8_t)block[8];
		green[1] = (int8_t)block[9];
	}
	else
	{
		green[0] = (uint8_t)block[8];
		green[1] = (uint8_t)block[9];
	}

	if (green[0] > green[1])
	{
		green[2] = (int16_t)floorf(green[0] * 6.0f / 7.0f + green[1] * 1.0f / 7.0f + 0.5f);
		green[3] = (int16_t)floorf(green[0] * 5.0f / 7.0f + green[1] * 2.0f / 7.0f + 0.5f);
		green[4] = (int16_t)floorf(green[0] * 4.0f / 7.0f + green[1] * 3.0f / 7.0f + 0.5f);
		green[5] = (int16_t)floorf(green[0] * 3.0f / 7.0f + green[1] * 4.0f / 7.0f + 0.5f);
		green[6] = (int16_t)floorf(green[0] * 2.0f / 7.0f + green[1] * 5.0f / 7.0f + 0.5f);
		green[7] = (int16_t)floorf(green[0] * 1.0f / 7.0f + green[1] * 6.0f / 7.0f + 0.5f);
	}
	else
	{
		green[2] = (int16_t)floorf(green[0] * 4.0f / 5.0f + green[1] * 1.0f / 5.0f + 0.5f);
		green[3] = (int16_t)floorf(green[0] * 3.0f / 5.0f + green[1] * 2.0f / 5.0f + 0.5f);
		green[4] = (int16_t)floorf(green[0] * 2.0f / 5.0f + green[1] * 3.0f / 5.0f + 0.5f);
		green[5] = (int16_t)floorf(green[0] * 1.0f / 5.0f + green[1] * 4.0f / 5.0f + 0.5f);
		if (is_signed)
		{
			green[6] = -128;
			green[7] = 127;
		}
		else
		{
			green[6] = 0;
			green[7] = 255;
		}
	}

	green_block[0] = block[10];
	green_block[0] |= block[11] << 8;
	green_block[0] |= block[12] << 16;

	green_block[1] = block[13];
	green_block[1] |= block[14] << 8;
	green_block[1] |= block[15] << 16;

	for (i = 0; i < 2; i++)
	{
		green_index[0 + i * 8] = (green_block[i] >> 0) & 0x07;
		green_index[1 + i * 8] = (green_block[i] >> 3) & 0x07;
		green_index[2 + i * 8] = (green_block[i] >> 6) & 0x07;
		green_index[3 + i * 8] = (green_block[i] >> 9) & 0x07;
		green_index[4 + i * 8] = (green_block[i] >> 12) & 0x07;
		green_index[5 + i * 8] = (green_block[i] >> 15) & 0x07;
		green_index[6 + i * 8] = (green_block[i] >> 18) & 0x07;
		green_index[7 + i * 8] = (green_block[i] >> 21) & 0x07;
	}
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (is_signed)
			{
				pixel4x4_rgba[i * 16 + j * 4 + 0] = (float)(red[red_index[i * 4 + j]] + 128);
				pixel4x4_rgba[i * 16 + j * 4 + 1] = (float)(green[green_index[i * 4 + j]] + 128);
				pixel4x4_rgba[i * 16 + j * 4 + 2] = (float)128;
			}
			else
			{
				pixel4x4_rgba[i * 16 + j * 4 + 0] = (float)red[red_index[i * 4 + j]];
				pixel4x4_rgba[i * 16 + j * 4 + 1] = (float)green[green_index[i * 4 + j]];
				pixel4x4_rgba[i * 16 + j * 4 + 2] = (float)0;
			}
			pixel4x4_rgba[i * 16 + j * 4 + 3] = 255;
		}
	}
}