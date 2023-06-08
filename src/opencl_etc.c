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

#define ETC_BINARY_FILE_TARGET_ELEMENTS_NO_UUID (28)

#define ETC_BINARY_FILE_TARGET_BYTES  (16 + 8 * sizeof(double) + 8 * sizeof(int) + 12 * sizeof(int))
#define ETC_BINARY_FILE_TARGET_ELEMENTS (16 + ETC_BINARY_FILE_TARGET_ELEMENTS_NO_UUID)

#include <cl\cl.h>

#include "..\inc\timer.h"
#include "..\inc\system.h"
#include "..\inc\math.h"
#include "..\inc\memory.h"
#include "..\inc\image.h"
#include "..\inc\device_codec.h"
#include "..\inc\opencl.h"
#include "..\inc\etc.h"

static char *g_etc_function[] = 
{
	"ETC_EncodeETC",
	"ETC_EncodeETC",
	"ETC_EncodeETC",
	"ETC_EncodeETC"
};

extern char *g_etc_kernel_source;

int CL_ETC_TestCodecGroup(device_t *device)
{
	int macro_size;
	codec_options_etc_t options[4];
	int codec_id[4] = {CODEC_ETC1, CODEC_ETC2_RGB, CODEC_ETC2_RGBA1, CODEC_ETC2_RGBA8};
	int test_kernel[4][4];
	int i;
	int ret = 0;

	for (i = 0; i < 4; i++)
	{
		int j;
		for (j = 0; j < 4; j++)
			test_kernel[i][j] = 1;
	}

	options[0].common.alpha_cutoff = 127;
	options[0].common.is_srgb = 1;
	options[0].common.is_ypbpr = 1;
	options[0].alpha_error = 0.0f;
	options[0].colour_error = 0.0f;
	options[0].common.quality = 0;
	options[1] = options[0];
	options[2] = options[0];
	options[3] = options[0];
	options[1].common.quality = 1;
	options[2].common.quality = 2;
	options[3].common.quality = 3;

	System_StartProgressThread(0, 12);

	for (macro_size = 1; macro_size < (1 << 12); macro_size <<= 1) 
	{
		int image_id;
		image_t image[4];
		int test_count = 0;

		for (i = 0; i < 4; i++)
			image[i] = Image_Create(macro_size * 4, macro_size * 4, 0, codec_id[i]);

		for (image_id = 0; image_id < 4; image_id++)
		{
#pragma omp parallel for private(i)
			for (i = 0; i < macro_size * 4 * macro_size * 4 * 4; i++)
				image[image_id].src_rgba_0_255[0][i] = (float)(rand() % 256);
		}

		for (i = 0; i < 4; i++) // codec id
		{	
			int k;
			for (k = 0; k < 4; k++) // quality
			{
				if (test_kernel[i][k])
				{
					uint64_t total_ticks = 0;
					double total_sec;

					test_count++;

					if (Codec_Encode(device->device_group, Device_DeviceIndexFromDevice(device), &image[i], codec_id[i], 0, macro_size, 0, &total_ticks, &options[k]))
					{
						ret = -1;
						test_count = 0;
						goto ON_ERROR;
					}

					if (total_ticks == 0)
						total_ticks = 1;

					total_sec = Timer_TicksToSecondsf64(total_ticks);

					LOG_PRINT("Parameters for %s quality %i: macroblock %i x %i took %.2f ms\n", Codec_AsString(codec_id[i]), k, macro_size, macro_size, 1000.0 * total_sec);

					if (total_sec > 0.25)
						test_kernel[i][k] = 0;
					else
					{
						device->codec[codec_id[i]].macroblock_size[k] = macro_size;
						device->codec[codec_id[i]].pixels_per_second[k] = (macro_size * 4 * macro_size * 4) / total_sec;
					}
				}
			}
		}
ON_ERROR:
		for (i = 0; i < 4; i++)
			Image_Destroy(&image[i]);
		System_AddProgress(0, 1);
		if (!test_count)
			break;
	}
	System_EndProgressThread();
	for (i = 0; i < 4; i++)
	{
		/*
		int j;
		for (j = 0; j < 2; j++)
			LOG_PRINT("Optimal paramters for %s quality %s: macroblock %i x %i, %.2f MP/s, %.2f ms/block\n", Codec_AsString(codec_id[i]), j == 0 ? "Normal" : "Turbo",
				device->codec[codec_id[i]].macroblock_size[j], device->codec[codec_id[i]].macroblock_size[j], device->codec[codec_id[i]].pixels_per_second[j] / 1000000.0, 1000.0 * (device->codec[codec_id[i]].macroblock_size[j] * device->codec[codec_id[i]].macroblock_size[j] * 16.0) / device->codec[codec_id[i]].pixels_per_second[j]);
				*/
		int j;
		for (j = 0; j < 4; j++)
			LOG_PRINT("Optimal paramters for %s quality %s: macroblock %i x %i, %.2f MP/s, %.2f ms/block\n", Codec_AsString(codec_id[i]), BCN_QualityAsString(options[j].common.quality),
				device->codec[codec_id[i]].macroblock_size[j], device->codec[codec_id[i]].macroblock_size[j], device->codec[codec_id[i]].pixels_per_second[j] / 1000000.0, 1000.0 * (device->codec[codec_id[i]].macroblock_size[j] * device->codec[codec_id[i]].macroblock_size[j] * 16.0) / device->codec[codec_id[i]].pixels_per_second[j]);
	}
	return ret;
}

int CL_ETC_KernelSetArgs(device_t *device, image_t *image, codec_e codec, int mip_level, int macro_size, int macro_block_src_x, int macro_block_src_y, int width, int height, void *context)
{
	codec_options_etc_t *options = (codec_options_etc_t*)context;
	unsigned int n[11];
	float err_targ[3];
	cl_int err;

	n[0] = ETC_ALLOWED_MODES;
	n[1] = options->common.is_ypbpr;
	n[2] = codec == CODEC_ETC1 ? 0 : 1;	// is_etc2
	n[3] = ((codec == CODEC_ETC2_RGBA1) || (codec == CODEC_ETC2_RGBA8)) ? 1 : 0;	// is_alpha
	n[4] = codec == CODEC_ETC2_RGBA1 ? 1 : 0; // is_punchthrough
	n[5] = 0;
	n[6] = 1;
	n[7] = 1;
	//n[8] = width * ((rand() % 2) + 1); // TODO: REMOVEME, force CL crash
	n[8] = width;
	n[9] = height;
	n[10] = options->common.quality;

	err_targ[0] = (float)options->common.alpha_cutoff;
	err_targ[1] = options->colour_error;
	err_targ[2] = options->alpha_error;

	err = clSetKernelArg(device->codec[codec].cl_kernel, 0, sizeof(unsigned int), &n[0]);COND_ERR_PRINT(err, "clSetKernelArg result: %i (%s)\n", err, OpenCL_ErrorString(err));		if (err){goto ENCODE_CLEANUP;}
	err = clSetKernelArg(device->codec[codec].cl_kernel, 1, sizeof(float), &err_targ[0]);COND_ERR_PRINT(err, "clSetKernelArg result: %i (%s)\n", err, OpenCL_ErrorString(err));		if (err){goto ENCODE_CLEANUP;}
	err = clSetKernelArg(device->codec[codec].cl_kernel, 2, sizeof(float), &err_targ[1]);COND_ERR_PRINT(err, "clSetKernelArg result: %i (%s)\n", err, OpenCL_ErrorString(err));		if (err){goto ENCODE_CLEANUP;}
	err = clSetKernelArg(device->codec[codec].cl_kernel, 3, sizeof(float), &err_targ[2]);COND_ERR_PRINT(err, "clSetKernelArg result: %i (%s)\n", err, OpenCL_ErrorString(err));		if (err){goto ENCODE_CLEANUP;}
	err = clSetKernelArg(device->codec[codec].cl_kernel, 4, sizeof(unsigned int), &n[1]);COND_ERR_PRINT(err, "clSetKernelArg result: %i (%s)\n", err, OpenCL_ErrorString(err));		if (err){goto ENCODE_CLEANUP;}
	err = clSetKernelArg(device->codec[codec].cl_kernel, 5, sizeof(unsigned int), &n[2]);COND_ERR_PRINT(err, "clSetKernelArg result: %i (%s)\n", err, OpenCL_ErrorString(err));		if (err){goto ENCODE_CLEANUP;}
	err = clSetKernelArg(device->codec[codec].cl_kernel, 6, sizeof(unsigned int), &n[3]);COND_ERR_PRINT(err, "clSetKernelArg result: %i (%s)\n", err, OpenCL_ErrorString(err));		if (err){goto ENCODE_CLEANUP;}
	err = clSetKernelArg(device->codec[codec].cl_kernel, 7, sizeof(unsigned int), &n[4]);COND_ERR_PRINT(err, "clSetKernelArg result: %i (%s)\n", err, OpenCL_ErrorString(err));		if (err){goto ENCODE_CLEANUP;}
	err = clSetKernelArg(device->codec[codec].cl_kernel, 8, sizeof(unsigned int), &n[5]);COND_ERR_PRINT(err, "clSetKernelArg result: %i (%s)\n", err, OpenCL_ErrorString(err));		if (err){goto ENCODE_CLEANUP;}
	err = clSetKernelArg(device->codec[codec].cl_kernel, 9, sizeof(unsigned int), &n[6]);COND_ERR_PRINT(err, "clSetKernelArg result: %i (%s)\n", err, OpenCL_ErrorString(err));		if (err){goto ENCODE_CLEANUP;}
	err = clSetKernelArg(device->codec[codec].cl_kernel, 10, sizeof(unsigned int), &n[7]);COND_ERR_PRINT(err, "clSetKernelArg result: %i (%s)\n", err, OpenCL_ErrorString(err));	if (err){goto ENCODE_CLEANUP;}
	err = clSetKernelArg(device->codec[codec].cl_kernel, 11, sizeof(unsigned int), &n[8]);COND_ERR_PRINT(err, "clSetKernelArg result: %i (%s)\n", err, OpenCL_ErrorString(err));	if (err){goto ENCODE_CLEANUP;}
	err = clSetKernelArg(device->codec[codec].cl_kernel, 12, sizeof(unsigned int), &n[9]);COND_ERR_PRINT(err, "clSetKernelArg result: %i (%s)\n", err, OpenCL_ErrorString(err));	if (err){goto ENCODE_CLEANUP;}
	err = clSetKernelArg(device->codec[codec].cl_kernel, 13, sizeof(cl_mem), &device->cl_mem_in);COND_ERR_PRINT(err, "clSetKernelArg result: %i (%s)\n", err, OpenCL_ErrorString(err));			if (err){goto ENCODE_CLEANUP;}
	err = clSetKernelArg(device->codec[codec].cl_kernel, 14, sizeof(cl_mem), &device->cl_mem_out);COND_ERR_PRINT(err, "clSetKernelArg result: %i (%s)\n", err, OpenCL_ErrorString(err));			if (err){goto ENCODE_CLEANUP;}
	err = clSetKernelArg(device->codec[codec].cl_kernel, 15, sizeof(unsigned int), &n[10]);COND_ERR_PRINT(err, "clSetKernelArg result: %i (%s)\n", err, OpenCL_ErrorString(err));	if (err){goto ENCODE_CLEANUP;}

ENCODE_CLEANUP:

	return err;
}


int CL_ETC_Decode(device_t *device, image_t *image, codec_e codec, int mip_level, int override_macro_size, uint64_t *kernel_ticks, uint64_t *total_ticks, void *context)
{
	return 0;
}

void CL_ETC_Init(device_group_t *device_group)
{
	device_group->num_modes[CODEC_GROUP_ETC] = 4;

	device_group->cl_kernel_function[CODEC_GROUP_ETC] = Mem_Malloc(sizeof(char*) * 4);
	device_group->cl_kernel_function[CODEC_GROUP_ETC][0] = g_etc_function[0];
	device_group->cl_kernel_function[CODEC_GROUP_ETC][1] = g_etc_function[1];
	device_group->cl_kernel_function[CODEC_GROUP_ETC][2] = g_etc_function[2];
	device_group->cl_kernel_function[CODEC_GROUP_ETC][3] = g_etc_function[3];

	device_group->binary_version_string[CODEC_GROUP_ETC] = BINARY_VERSION_STRING_ETC;

	device_group->cl_source[CODEC_GROUP_ETC] = g_etc_kernel_source;
	device_group->cl_test_codec_group_fp[CODEC_GROUP_ETC] = CL_ETC_TestCodecGroup;

	device_group->cl_set_kernel_args_fp[CODEC_GROUP_ETC] = CL_ETC_KernelSetArgs;
}