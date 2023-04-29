#include <windows.h>
#include <stdint.h>
#include <math.h>

#include "../inc/system.h"
#include "../inc/math.h"
#include "../inc/vecmat.h"
#include "../inc/dds_const.h"
#include "../inc/dds_util.h"
#include "../inc/dds.h"

void DDS_EncodeBC2Block(uint8_t *block, double *pixel4x4_rgba, int is_premultiplied, int is_srgb, int is_signed, int block_x, int block_y)
{
	DDS_EncodeBC1Block(&block[8], pixel4x4_rgba, is_premultiplied, is_srgb, is_signed, block_x, block_y, 0, 1);

	block[0] = ((((uint8_t)pixel4x4_rgba[ 0 + 3]) >> 4) << 0) | ((((uint8_t)pixel4x4_rgba[ 4 + 3]) >> 4) << 4);
	block[1] = ((((uint8_t)pixel4x4_rgba[ 8 + 3]) >> 4) << 0) | ((((uint8_t)pixel4x4_rgba[12 + 3]) >> 4) << 4);
	block[2] = ((((uint8_t)pixel4x4_rgba[16 + 3]) >> 4) << 0) | ((((uint8_t)pixel4x4_rgba[20 + 3]) >> 4) << 4);
	block[3] = ((((uint8_t)pixel4x4_rgba[24 + 3]) >> 4) << 0) | ((((uint8_t)pixel4x4_rgba[28 + 3]) >> 4) << 4);
	block[4] = ((((uint8_t)pixel4x4_rgba[32 + 3]) >> 4) << 0) | ((((uint8_t)pixel4x4_rgba[36 + 3]) >> 4) << 4);
	block[5] = ((((uint8_t)pixel4x4_rgba[40 + 3]) >> 4) << 0) | ((((uint8_t)pixel4x4_rgba[44 + 3]) >> 4) << 4);
	block[6] = ((((uint8_t)pixel4x4_rgba[48 + 3]) >> 4) << 0) | ((((uint8_t)pixel4x4_rgba[52 + 3]) >> 4) << 4);
	block[7] = ((((uint8_t)pixel4x4_rgba[56 + 3]) >> 4) << 0) | ((((uint8_t)pixel4x4_rgba[60 + 3]) >> 4) << 4);
}
	
void DDS_DecodeBC2Block(uint8_t *block, float *pixel4x4_rgba, int is_premultiplied, int is_srgb, int is_signed, int block_x, int block_y)
{
	uint8_t colour[4][3];
	uint8_t alpha[16];
	int i, j;

	for (i = 0; i < 8; i++)
	{
		alpha[i * 2 + 0]  = (uint8_t)(((uint32_t)((block[i] >> 0) & 0x0F) * 255) / 15);
		alpha[i * 2 + 1]  = (uint8_t)(((uint32_t)((block[i] >> 4) & 0x0F) * 255) / 15);
	}

	colour[0][0] = (uint8_t)((*((uint16_t*)&block[8]) & 0xF800) >> 8);
	colour[0][1] = (uint8_t)((*((uint16_t*)&block[8]) & 0x07E0) >> 3);
	colour[0][2] = (uint8_t)((*((uint16_t*)&block[8]) & 0x001F) << 3);

	colour[1][0] = (uint8_t)((*((uint16_t*)&block[10]) & 0xF800) >> 8);
	colour[1][1] = (uint8_t)((*((uint16_t*)&block[10]) & 0x07E0) >> 3);
	colour[1][2] = (uint8_t)((*((uint16_t*)&block[10]) & 0x001F) << 3);

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
			pixel4x4_rgba[i * 16 + j * 4 + 3] = (float)alpha[i * 4 + j];
		}
	}
}
