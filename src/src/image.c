#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <conio.h>
#include <commctrl.h>
#include <math.h>
#include <psapi.h>
#include <Dbghelp.h>

#define CL_TARGET_OPENCL_VERSION	200
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS

#include <cl\cl.h>

#include "..\inc\math.h"
#include "..\inc\memory.h"
#include "..\inc\system.h"
#include "..\inc\image.h"
#include "..\inc\device_codec.h"
#include "..\inc\opencl.h"
#include "..\inc\timer.h"

static void Image_DownSampleTexelsRGBA(float *src_image, int src_width, int src_height, float *dst_image, int dst_width, int dst_height, int dst_x, int dst_y)
{
	int x;
	int y;
	int xstart = (dst_x * src_width) / dst_width;
	int ystart = (dst_y * src_height) / dst_height;
	int xend = ((dst_x + 1) * src_width + dst_width - 1) / dst_width;
	int yend = ((dst_y + 1) * src_height + dst_height - 1) / dst_height;
	float xstart_fract = (dst_x * src_width) / (float)dst_width;
	float ystart_fract = (dst_y * src_height) / (float)dst_height;
	float xend_fract = ((dst_x + 1) * src_width) / (float)dst_width;
	float yend_fract = ((dst_y + 1) * src_height) / (float)dst_height;
	float inv_area = (xend_fract - xstart_fract) * (yend_fract - ystart_fract);
	float rgba[4];

	xstart_fract = 1.0f - (xstart_fract - floorf(xstart_fract));
	ystart_fract = 1.0f - (ystart_fract - floorf(ystart_fract));

	xend_fract = xend_fract - floorf(xend_fract);
	yend_fract = yend_fract - floorf(yend_fract);

	xend_fract = xend_fract == 0.0f ? 1.0f : xend_fract;
	yend_fract = yend_fract == 0.0f ? 1.0f : yend_fract;

	rgba[0] = 0.0f;
	rgba[1] = 0.0f;
	rgba[2] = 0.0f;
	rgba[3] = 0.0f;

	inv_area = inv_area == 0.0f ? 1.0f : 1.0f / inv_area;

	for (y = ystart; y < yend; y++)
		for (x = xstart; x < xend; x++)
		{
			float scale = 1.0f;
			
			if (x == xstart)
				scale *= xstart_fract;
			else if (x == xend - 1)
				scale *= xend_fract;

			if (y == ystart)
				scale *= ystart_fract;
			else if (y == yend - 1)
				scale *= yend_fract;

			rgba[0] += src_image[(y * src_width + x) * 4 + 0] * scale;
			rgba[1] += src_image[(y * src_width + x) * 4 + 1] * scale;
			rgba[2] += src_image[(y * src_width + x) * 4 + 2] * scale;
			rgba[3] += src_image[(y * src_width + x) * 4 + 3] * scale;
		}
	rgba[0] *= inv_area;
	rgba[1] *= inv_area;
	rgba[2] *= inv_area;
	rgba[3] *= inv_area;

	dst_image[(dst_y * dst_width + dst_x) * 4 + 0] = rgba[0];
	dst_image[(dst_y * dst_width + dst_x) * 4 + 1] = rgba[1];
	dst_image[(dst_y * dst_width + dst_x) * 4 + 2] = rgba[2];
	dst_image[(dst_y * dst_width + dst_x) * 4 + 3] = rgba[3];
}

void Image_GenMipMaps()
{
	int i;
	int x;
	int y;

	for (i = 1; i < g_system.num_mipmap_levels; i++)
	{
		g_system.image[i].width = g_system.image[i - 1].width;
		g_system.image[i].height = g_system.image[i - 1].height;
		g_system.image[i].width >>= g_system.image[i].width > 1 ? 1 : 0;
		g_system.image[i].height >>= g_system.image[i].height > 1 ? 1 : 0;
		g_system.image[i].rgba = Mem_Malloc(g_system.image[i].width * g_system.image[i].height * 4 * sizeof(float));

		LOG_PRINT("Generating mipmap level %i (%i x %i)\n", i, g_system.image[i].width, g_system.image[i].height);

		for (y = 0; y < g_system.image[i].height; y++)
			for (x = 0; x < g_system.image[i].width; x++)
				Image_DownSampleTexelsRGBA(g_system.image[i - 1].rgba, g_system.image[i - 1].width, g_system.image[i - 1].height, g_system.image[i].rgba, g_system.image[i].width, g_system.image[i].height, x, y);
	}
}

static int Image_BlockSize(int format)
{
	switch (format)
	{
		case CODEC_ETC1:
		case CODEC_ETC2_RGB:
		case CODEC_ETC2_RGBA1:
		case CODEC_BC1_RGB:
		case CODEC_BC1_RGBA:
		case CODEC_BC4_RED:
			return 8;
		case CODEC_ETC2_RGBA8:
		case CODEC_BC2_RGBA:
		case CODEC_BC3_RGBA:
		case CODEC_BC5_RG:
			return 16;
		default:
			return 16;
	}
}

image_t Image_FromSysImage(sys_image_t *sys_image, int num_mipmap_levels, int encoded_format)
{
	image_t image;
	int i;

	image.dst_format = encoded_format;
	image.dst_block_size = Image_BlockSize(encoded_format);
	image.num_mipmaps = num_mipmap_levels;
	image.src_rgba_0_255 = Mem_Malloc(sizeof(float*) * image.num_mipmaps);
	image.dst_encoded = Mem_Malloc(sizeof(uint8_t*) * image.num_mipmaps);
	image.src_width = Mem_Malloc(sizeof(int) * image.num_mipmaps);
	image.src_height = Mem_Malloc(sizeof(int) * image.num_mipmaps);

	for (i = 0; i < image.num_mipmaps; i++)
	{
		image.src_width[i] = sys_image[i].width;
		image.src_height[i] = sys_image[i].height;
		
		image.src_rgba_0_255[i] = Mem_Malloc(image.src_width[i] * image.src_height[i] * sizeof(float) * 4);
		memcpy(image.src_rgba_0_255[i], sys_image[i].rgba, image.src_width[i] * image.src_height[i] * sizeof(float) * 4);

		image.dst_encoded[i] = Mem_Malloc(((image.src_width[i] + 3) >> 2) * ((image.src_height[i] + 3) >> 2) * Image_BlockSize(encoded_format));
	}
	return image;
}
image_t Image_Create(int width, int height, int mipmaps, int encoded_format)
{
	image_t image;
	int i;
	int w = width;
	int h = height;
	int num_mipmap_levels = 1;

	if (mipmaps)
		while ((w > 1) || (h > 1))
		{
			w >>= w > 1 ? 1 : 0;
			h >>= h > 1 ? 1 : 0;
			num_mipmap_levels++;
		}

	image.dst_format = encoded_format;
	image.dst_block_size = Image_BlockSize(encoded_format);
	image.num_mipmaps = num_mipmap_levels;
	image.src_rgba_0_255 = Mem_Malloc(sizeof(float*) * image.num_mipmaps);
	image.dst_encoded = Mem_Malloc(sizeof(uint8_t*) * image.num_mipmaps);
	image.src_width = Mem_Malloc(sizeof(int) * image.num_mipmaps);
	image.src_height = Mem_Malloc(sizeof(int) * image.num_mipmaps);

	for (i = 0; i < image.num_mipmaps; i++)
	{
		image.src_width[i] = width >> i;
		image.src_height[i] = height >> i;

		image.src_width[i] = image.src_width[i] == 0 ? 1 : image.src_width[i];
		image.src_height[i] = image.src_height[i] == 0 ? 1 : image.src_height[i];

		image.src_rgba_0_255[i] = Mem_Malloc(image.src_width[i] * image.src_height[i] * sizeof(float) * 4);

		image.dst_encoded[i] = Mem_Malloc(((image.src_width[i] + 3) >> 2) * ((image.src_height[i] + 3) >> 2) * Image_BlockSize(encoded_format));
	}
	return image;
}
void Image_Destroy(image_t *image)
{
	int i;

	for (i = 0; i < image->num_mipmaps; i++)
	{
		Mem_Free(image->src_rgba_0_255[i]);
		Mem_Free(image->dst_encoded[i]);
	}
	
	Mem_Free(image->src_width);
	Mem_Free(image->src_height);
	Mem_Free(image->src_rgba_0_255);
	Mem_Free(image->dst_encoded);

	memset(image, 0, sizeof(image_t));
}

void Image_ExtractSubImageRGBAf32(float *dst, image_t *image, int mip_level, int width, int height, int x, int y)
{
	int yl;

	for (yl = 0; yl < height; yl++)
	{
		int y_offset = (y + yl) * image->src_width[mip_level] * 4;
		int x_offset = x * 4;
		int src_offset = y_offset + x_offset;
		int dst_offset = (int)(yl * width * 4);
		int bytes = 4 * sizeof(float) * width;
		memcpy(&dst[dst_offset], &(image->src_rgba_0_255[mip_level][src_offset]), bytes);
	}
}
void Image_CopyEncodedToImage(image_t *image, uint8_t *src, int mip_level, int width, int height, int x, int y)
{
	int yl;
	int blocks_x = (image->src_width[mip_level] + 3) >> 2;
	int block_extents_x = (width + 3) >> 2;
	int block_extents_y = (height + 3) >> 2;
	int block_dst_x = (x + 3) >> 2;
	int block_dst_y = (y + 3) >> 2;

	for (yl = 0; yl < block_extents_y; yl++)
	{
		int src_offset = yl * block_extents_x * image->dst_block_size;
		int y_offset = (yl + block_dst_y) * blocks_x;
		int x_offset = block_dst_x;
		int dst_offset = (y_offset + x_offset) * image->dst_block_size;
		int bytes = block_extents_x * image->dst_block_size;
		memcpy(&image->dst_encoded[mip_level][dst_offset], &src[src_offset], bytes);
	}
}
int Image_GetRequiredBytes(int width, int height, int format)
{
	if (format != CODEC_RGBA32F)
		return ((width + 3) >> 2) * ((height + 3) >> 2) * Image_BlockSize(format);
	else
		return width * height * 4 * sizeof(float);
}