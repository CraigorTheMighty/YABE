#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <conio.h>
#include <commctrl.h>
#include <math.h>
#include <psapi.h>
#include <Dbghelp.h>
#include <inttypes.h>

#define CL_TARGET_OPENCL_VERSION	200
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS

#define BCN_BINARY_FILE_TARGET_ELEMENTS_NO_UUID (60)

#define BCN_BINARY_FILE_TARGET_BYTES  (16 + 24 * sizeof(double) + 24 * sizeof(int) + 12 * sizeof(int))
#define BCN_BINARY_FILE_TARGET_ELEMENTS (16 + BCN_BINARY_FILE_TARGET_ELEMENTS_NO_UUID)

#include <cl\cl.h>

#include "..\inc\timer.h"
#include "..\inc\system.h"
#include "..\inc\math.h"
#include "..\inc\memory.h"
#include "..\inc\image.h"
#include "..\inc\device_codec.h"
#include "..\inc\opencl.h"
#include "..\inc\etc.h"
#include "..\inc\dds.h"
#include "..\inc\opencl_bcn.h"

char *g_bcn_kernel_source;

static char *g_bcn_function[] = 
{
	"BCN_EncodeBC1",
	"BCN_EncodeBC2",
	"BCN_EncodeBC3",
	"BCN_EncodeBC4",
	"BCN_EncodeBC5"
};

int BCN_QualityToQualityBitfield(int quality)
{
	switch (quality)
	{
		case CODEC_QUALITY_FAST:	return CODEC_BCN_QUALITY_FAST_BITFIELD;
		case CODEC_QUALITY_NORMAL:	return CODEC_BCN_QUALITY_NORMAL_BITFIELD;
		case CODEC_QUALITY_HIGH:	return CODEC_BCN_QUALITY_HIGH_BITFIELD;
		case CODEC_QUALITY_BEST:	return CODEC_BCN_QUALITY_BEST_BITFIELD;
		default: return CODEC_BCN_QUALITY_FAST_BITFIELD;
	}
}

char *BCN_QualityAsString(int quality)
{
	if (quality == CODEC_QUALITY_BEST)
		return "QUALITY_BEST";
	else if (quality == (CODEC_QUALITY_BEST | CODEC_BCN_QUALITY_OPTIONS_TEST))
		return "QUALITY_BEST | TEST";
	if (quality == CODEC_QUALITY_HIGH)
		return "QUALITY_HIGH";
	else if (quality == (CODEC_QUALITY_HIGH | CODEC_BCN_QUALITY_OPTIONS_TEST))
		return "QUALITY_HIGH | TEST";
	if (quality == CODEC_QUALITY_NORMAL)
		return "QUALITY_NORMAL";
	else if (quality == (CODEC_QUALITY_NORMAL | CODEC_BCN_QUALITY_OPTIONS_TEST))
		return "QUALITY_NORMAL | TEST";
	if (quality == CODEC_QUALITY_FAST)
		return "QUALITY_FAST";
	else if (quality == (CODEC_QUALITY_FAST | CODEC_BCN_QUALITY_OPTIONS_TEST))
		return "QUALITY_FAST | TEST";
	else
		return "<UNKNOWN>";
}

int CL_BCN_TestCodecGroup(device_t *device)
{
	int data_type;	// rand % 256, rand % 64 + 96
	int macro_size;
	codec_options_bcn_t options[2][4];
	int codec_id[6] = {CODEC_BC1_RGB, CODEC_BC1_RGBA, CODEC_BC2_RGBA, CODEC_BC3_RGBA, CODEC_BC4_RED, CODEC_BC5_RG};
	int test_kernel[6][4];		// codec_id, data_type, is_test
	int i;
	int ret = 0;

	for (i = 0; i < 6; i++)
	{
		int j;
		for (j = 0; j < 4; j++)
		{
			test_kernel[i][j] = 1;
		}
	}

	options[0][0].common.alpha_cutoff = 127;
	options[0][0].common.is_srgb = 1;
	options[0][0].common.is_ypbpr = 0;
	options[0][0].output_dds = 1;
	options[0][0].output_ktx = 1;
	options[0][1] = options[0][0];
	options[0][2] = options[0][0];
	options[0][3] = options[0][0];
	options[1][1] = options[0][0];
	options[1][2] = options[0][0];
	options[1][3] = options[0][0];
	options[0][0].common.quality = CODEC_QUALITY_FAST;
	options[0][1].common.quality = CODEC_QUALITY_NORMAL;
	options[0][2].common.quality = CODEC_QUALITY_HIGH;
	options[0][3].common.quality = CODEC_QUALITY_BEST;
	options[1][0].common.quality = CODEC_QUALITY_FAST;
	options[1][1].common.quality = CODEC_QUALITY_NORMAL;
	options[1][2].common.quality = CODEC_QUALITY_HIGH;
	options[1][3].common.quality = CODEC_QUALITY_BEST;
	options[1][0].is_test = 1;
	options[1][1].is_test = 1;
	options[1][2].is_test = 1;
	options[1][3].is_test = 1;

	System_StartProgressThread(0, 12);

	for (i = 0; i < 6; i++)
	{
		int j;
		for (j = 0; j < 4; j++)
		{
			device->codec[codec_id[i]].pixels_per_second[j] = 0.0;
			device->codec[codec_id[i]].macroblock_size[j] = 1;
		}
	}

	for (macro_size = 1; macro_size < (1 << 12); macro_size <<= 1) 
	{
		int image_id;
		image_t image[6];
		int test_count = 0;
		double perf[2][6][4][2];
		double elapsed[2][6][4][2];

		for (i = 0; i < 2; i++)
		{
			int j;
			for (j = 0; j < 6; j++)
			{
				int k;
				for (k = 0; k < 4; k++)
				{
					int m;
					for (m = 0; m < 2; m++)
					{
						perf[i][j][k][m] = 0.0f;
						elapsed[i][j][k][m] = 99999999999.0f;
					}
				}
			}
		}

		for (i = 0; i < 6; i++)
			image[i] = Image_Create(macro_size * 4, macro_size * 4, 0, codec_id[i]);

		for (data_type = 0; data_type < 2; data_type++)
		{

			for (image_id = 0; image_id < 6; image_id++)
			{
				if (data_type == 0)
				{
#pragma omp parallel for private(i)
					for (i = 0; i < macro_size * 4 * macro_size * 4 * 4; i++)
						image[image_id].src_rgba_0_255[0][i] = (float)(rand() % 256);
				}
				else
				{
#pragma omp parallel for private(i)
					for (i = 0; i < macro_size * 4 * macro_size * 4 * 4; i++)
						image[image_id].src_rgba_0_255[0][i] = (float)(rand() % 64) + 96.0f;
				}
			}

			for (i = 0; i < 6; i++) // codec id
			{	
				int j;
				for (j = 0; j < 4; j++) // quality 
				{
					if (test_kernel[i][j])
					{
						int k;
						for (k = 1; k < 2; k++) // is_test
						{
							uint64_t total_ticks = 0;
							double total_sec;

							test_count++;

							//LOG_PRINT("Testing codec %s quality %s on macro size %i x %i\n", Codec_AsString(codec_id[i]), BCN_QualityAsString(options[k][j].quality), macro_size, macro_size);
							if (Codec_Encode(device->device_group, Device_DeviceIndexFromDevice(device), &image[i], codec_id[i], 0, macro_size, 0, &total_ticks, &options[k][j]))
							{
								ret = -1;
								test_count = 0;
								goto ON_ERROR;
							}

							if (total_ticks == 0)
								total_ticks = 1;

							total_sec = Timer_TicksToSecondsf64(total_ticks);
							LOG_PRINT("Codec %s quality %s is_test %i macro size %i x %i took %.2fms\n", Codec_AsString(codec_id[i]), BCN_QualityAsString(options[k][j].common.quality), options[k][j].is_test, macro_size, macro_size, total_sec * 1000.0);

							if (total_sec > 0.25)
								test_kernel[i][j] = 0;

							perf[data_type][i][j][k] = (macro_size * 4 * macro_size * 4) / total_sec;
							elapsed[data_type][i][j][k] = total_sec;
						}
					}
				}
			}
		}
		int j;
		for (j = 0; j < 6; j++)
		{
			int k;
			for (k = 0; k < 4; k++)
			{
				int local_worst;

				if (elapsed[0][j][k][1] > elapsed[1][j][k][1])
					local_worst = 0;
				else
					local_worst = 1;

				if (elapsed[local_worst][j][k][1] > 0.25)
					continue;

				if (perf[local_worst][j][k][1] > device->codec[codec_id[j]].pixels_per_second[k])
				{
					device->codec[codec_id[j]].pixels_per_second[k] = perf[local_worst][j][k][1];
					device->codec[codec_id[j]].macroblock_size[k] = macro_size;
				}
			}
		}

ON_ERROR:
		for (i = 0; i < 6; i++)
			Image_Destroy(&image[i]);
		System_AddProgress(0, 1);
		if (!test_count)
			break;
	}
	System_EndProgressThread();
	for (i = 0; i < 6; i++)
	{
		int j;
		for (j = 0; j < 4; j++)
			LOG_PRINT("Optimal paramters for %s quality %s: macroblock %i x %i, %.2f MP/s, %.2f ms/block\n", Codec_AsString(codec_id[i]), BCN_QualityAsString(options[0][j].common.quality),
				device->codec[codec_id[i]].macroblock_size[j], device->codec[codec_id[i]].macroblock_size[j], device->codec[codec_id[i]].pixels_per_second[j] / 1000000.0, 1000.0 * (device->codec[codec_id[i]].macroblock_size[j] * device->codec[codec_id[i]].macroblock_size[j] * 16.0) / device->codec[codec_id[i]].pixels_per_second[j]);
	}
	return ret;
}

int CL_BCN_KernelSetArgs(device_t *device, image_t *image, codec_e codec, int mip_level, int macro_size, int macro_block_src_x, int macro_block_src_y, int width, int height, void *context)
{
	codec_options_bcn_t *options = (codec_options_bcn_t*)context;
	unsigned int n[4];
	cl_int err;

	n[0] = BCN_QualityToQualityBitfield(options->common.quality);
	//n[1] = width * ((rand() % 2) + 1); // TODO: REMOVEME, force CL crash
	n[1] = width;
	n[2] = height;
	if (codec == CODEC_BC1_RGB)
		n[3] = 0;
	else
		n[3] = options->common.alpha_cutoff;

	if (options->is_test)
		n[0] |= CODEC_BCN_QUALITY_OPTIONS_TEST;

	err = clSetKernelArg(device->codec[codec].cl_kernel, 0, sizeof(unsigned int), &n[0]);COND_ERR_PRINT(err, "clSetKernelArg result: %i (%s)\n", err, OpenCL_ErrorString(err));		if (err){goto ENCODE_CLEANUP;}
	err = clSetKernelArg(device->codec[codec].cl_kernel, 1, sizeof(unsigned int), &n[1]);COND_ERR_PRINT(err, "clSetKernelArg result: %i (%s)\n", err, OpenCL_ErrorString(err));		if (err){goto ENCODE_CLEANUP;}
	err = clSetKernelArg(device->codec[codec].cl_kernel, 2, sizeof(unsigned int), &n[2]);COND_ERR_PRINT(err, "clSetKernelArg result: %i (%s)\n", err, OpenCL_ErrorString(err));		if (err){goto ENCODE_CLEANUP;}
	err = clSetKernelArg(device->codec[codec].cl_kernel, 3, sizeof(unsigned int), &n[3]);COND_ERR_PRINT(err, "clSetKernelArg result: %i (%s)\n", err, OpenCL_ErrorString(err));		if (err){goto ENCODE_CLEANUP;}
	err = clSetKernelArg(device->codec[codec].cl_kernel, 4, sizeof(cl_mem), &device->cl_mem_in);COND_ERR_PRINT(err, "clSetKernelArg result: %i (%s)\n", err, OpenCL_ErrorString(err));			if (err){goto ENCODE_CLEANUP;}
	err = clSetKernelArg(device->codec[codec].cl_kernel, 5, sizeof(cl_mem), &device->cl_mem_out);COND_ERR_PRINT(err, "clSetKernelArg result: %i (%s)\n", err, OpenCL_ErrorString(err));			if (err){goto ENCODE_CLEANUP;}

ENCODE_CLEANUP:

	return err;
}

void CL_BCN_Init(device_group_t *device_group)
{
	/*
	// TODO: remove me when source is static
	FILE *f;
	int len;
	fopen_s(&f, "E:\\Craig\\Programming\\New Stuff\\ImageCompressor\\ImageCompressor\\src\\bcn.cl", "rb");
	fseek(f, 0, SEEK_END);
	len = ftell(f);
	fseek(f, 0, SEEK_SET);
	g_bcn_kernel_source = Mem_Malloc(len + 1);
	fread(g_bcn_kernel_source, 1, len, f);
	g_bcn_kernel_source[len] = 0;
	fclose(f);
	*/

	device_group->num_modes[CODEC_GROUP_BCN] = 4;
	device_group->cl_kernel_function[CODEC_GROUP_BCN] = Mem_Malloc(sizeof(char*) * 6);
	device_group->cl_kernel_function[CODEC_GROUP_BCN][0] = g_bcn_function[0];
	device_group->cl_kernel_function[CODEC_GROUP_BCN][1] = g_bcn_function[0];
	device_group->cl_kernel_function[CODEC_GROUP_BCN][2] = g_bcn_function[1];
	device_group->cl_kernel_function[CODEC_GROUP_BCN][3] = g_bcn_function[2];
	device_group->cl_kernel_function[CODEC_GROUP_BCN][4] = g_bcn_function[3];
	device_group->cl_kernel_function[CODEC_GROUP_BCN][5] = g_bcn_function[4];

	device_group->binary_version_string[CODEC_GROUP_BCN] = BINARY_VERSION_STRING_BCN;
	device_group->cl_source[CODEC_GROUP_BCN] = g_bcn_kernel_source;

	device_group->cl_test_codec_group_fp[CODEC_GROUP_BCN] = CL_BCN_TestCodecGroup;

	device_group->cl_set_kernel_args_fp[CODEC_GROUP_BCN] = CL_BCN_KernelSetArgs;
}