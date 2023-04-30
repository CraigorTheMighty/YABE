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

#include <cl\cl.h>

#include "..\inc\math.h"
#include "..\inc\memory.h"
#include "..\inc\system.h"
#include "..\inc\image.h"
#include "..\inc\device_codec.h"
#include "..\inc\opencl.h"
#include "..\inc\timer.h"
#include "..\inc\cpu_codec.h"

int g_codec_to_group[CODEC_NUM_CODECS] = 
{
	/*CODEC_ETC1*/			CODEC_GROUP_ETC,
	/*CODEC_ETC2_RGB*/		CODEC_GROUP_ETC,
	/*CODEC_ETC2_RGBA1*/	CODEC_GROUP_ETC,
	/*CODEC_ETC2_RGBA8*/	CODEC_GROUP_ETC,

	/*CODEC_BC1_RGB*/		CODEC_GROUP_BCN,
	/*CODEC_BC1_RGBA*/		CODEC_GROUP_BCN,
	/*CODEC_BC2_RGBA*/		CODEC_GROUP_BCN,
	/*CODEC_BC3_RGBA*/		CODEC_GROUP_BCN,
	/*CODEC_BC4_RED*/		CODEC_GROUP_BCN,
	/*CODEC_BC5_RG*/		CODEC_GROUP_BCN,
};

int g_codec_group_num_codecs[] = 
{
	4,
	6
};
int g_codec_group_first_codec[] = 
{
	CODEC_ETC1,
	CODEC_BC1_RGB
};

char *Codec_GroupAsString(codec_group_e codec_group)
{
	switch (codec_group)
	{
		case CODEC_GROUP_ETC: return "ETC";
		case CODEC_GROUP_BCN: return "BCN";
		default: return "<UNKNOWN>";
	}
}

int Codec_SaveCodecGroupData(device_t *device, codec_group_e codec_group)
{
	cl_int err;
	int text_size = 0;
	int text_offset;
	int binary_offset;
	int binary_size = 0;
	int name_offset;
	int name_size = 0;
	int driver_offset;
	int driver_size = 0;
	int build_log_offset;
	int build_log_size = 0;
	size_t programBinarySizes = 0;
	unsigned char *program_binary = 0;
	char *buildlog = 0;
	size_t blen = 0;
	FILE *f = 0;
	wchar_t *path = 0;
	char *binary_version_string = device->device_group->binary_version_string[codec_group];
	int binary_version_len = (int)strlen(binary_version_string);
	int error = -1;
	unsigned char uuid[16];
	int elements_written = 0;
	int i;
	int base_bytes;
	int num_elements = 0;
	char *reference_source = device->device_group->cl_source[codec_group];

	if (!device->is_opencl)
		reference_source = "";

	if (device->is_opencl)
	{
		err = clGetProgramInfo(device->cl_program[codec_group], CL_PROGRAM_BINARY_SIZES, sizeof(size_t), &programBinarySizes, NULL);
		COND_PRINT(err, "clGetProgramInfo result: %i (%s)\n", err, OpenCL_ErrorString(err));
		LOG_PRINT("Binary size: %i\n", (int)programBinarySizes);
		if (err != CL_SUCCESS)
			goto FINAL_STAGE;

		program_binary = Mem_Malloc(programBinarySizes);
		err = clGetProgramInfo(device->cl_program[codec_group], CL_PROGRAM_BINARIES, sizeof(unsigned char*), &program_binary, NULL);
		COND_PRINT(err, "clGetProgramInfo result: %i (%s)\n", err, OpenCL_ErrorString(err));
		if (err != CL_SUCCESS)
			goto FINAL_STAGE;

		err = clGetProgramBuildInfo(device->cl_program[codec_group], device->cl_device_info.id, CL_PROGRAM_BUILD_LOG, 0, 0, &blen);
		if (err != CL_SUCCESS)
			goto FINAL_STAGE;
		COND_PRINT(err, "clGetProgramBuildInfo result: %i (%s)\n", err, OpenCL_ErrorString(err));
		buildlog = Mem_Malloc(blen + 1);
		err = clGetProgramBuildInfo(device->cl_program[codec_group], device->cl_device_info.id, CL_PROGRAM_BUILD_LOG, blen, buildlog, 0);
		if (err != CL_SUCCESS)
			goto FINAL_STAGE;
		COND_PRINT(err, "clGetProgramBuildInfo result: %i (%s)\n", err, OpenCL_ErrorString(err));
		if (blen > 2 && g_system.opts.enable_log)
			ALWAYS_PRINT("Build log:\n==========\nLength: %i\n\n%s\n", (int)blen, buildlog);
		goto FINAL_STAGE;
	}
	else
	{
		program_binary = 0;
		programBinarySizes = 0;
		blen = 0;
		buildlog = 0;
	}

FINAL_STAGE:

	if (device->is_opencl)
		path = CL_GetBinaryPath(device->cl_index, Codec_GroupAsString(codec_group));
	else
		path = CL_GetBinaryPath(-1, Codec_GroupAsString(codec_group));

	LOG_PRINT("Binary path: \"%ls\"\n", path);

	System_GetBIOSUUID(uuid);

	_wfopen_s(&f, path, L"wb");

	if (!f)
	{
		error = -1;
		ALWAYS_PRINT("Could not open file \"%ls\" for writing\n", path);
		goto CLEANUP;
	}

	base_bytes = 16 + sizeof(int) * 12;
	for (i = 0; i < g_codec_group_num_codecs[codec_group]; i++)
		base_bytes += device->codec[g_codec_group_first_codec[codec_group] + i].num_modes * (sizeof(int) + sizeof(double));
	num_elements = 28;
	for (i = 0; i < g_codec_group_num_codecs[codec_group]; i++)
		num_elements += device->codec[g_codec_group_first_codec[codec_group] + i].num_modes * 2;

	text_size = (int)strlen(reference_source);
	text_offset = base_bytes + binary_version_len;
	binary_offset = base_bytes + binary_version_len + text_size;
	binary_size = (int)programBinarySizes;
	name_offset = base_bytes + binary_version_len + text_size + binary_size;
	if (device->is_opencl)
		name_size = (int)strlen(device->cl_device_info.name);
	else
		name_size = (int)strlen("CPU");
	driver_offset = base_bytes + binary_version_len + text_size + binary_size + name_size;
	if (device->is_opencl)
		driver_size = (int)strlen(device->cl_device_info.driver_version);
	else
		driver_size = (int)strlen("Version 1.0");
	build_log_offset = base_bytes + binary_version_len + text_size + binary_size + name_size + driver_size;
	build_log_size = (int)blen;

	elements_written += (int)fwrite(&binary_version_len, sizeof(int), 1, f);
	elements_written += (int)fwrite(binary_version_string, sizeof(char), binary_version_len, f);
	elements_written += (int)fwrite(uuid, 1, 16, f);
	elements_written += (int)fwrite(&device->is_valid, sizeof(int), 1, f);
	elements_written += (int)fwrite(&text_size, sizeof(int), 1, f);
	elements_written += (int)fwrite(&text_offset, sizeof(int), 1, f);
	elements_written += (int)fwrite(&binary_size, sizeof(int), 1, f);
	elements_written += (int)fwrite(&binary_offset, sizeof(int), 1, f);
	elements_written += (int)fwrite(&name_size, sizeof(int), 1, f);
	elements_written += (int)fwrite(&name_offset, sizeof(int), 1, f);
	elements_written += (int)fwrite(&driver_size, sizeof(int), 1, f);
	elements_written += (int)fwrite(&driver_offset, sizeof(int), 1, f);
	elements_written += (int)fwrite(&build_log_size, sizeof(int), 1, f);
	elements_written += (int)fwrite(&build_log_offset, sizeof(int), 1, f);
	for (i = 0; i < g_codec_group_num_codecs[codec_group]; i++)
		elements_written += (int)fwrite(device->codec[g_codec_group_first_codec[codec_group] + i].macroblock_size, sizeof(int), device->codec[g_codec_group_first_codec[codec_group] + i].num_modes, f);
	for (i = 0; i < g_codec_group_num_codecs[codec_group]; i++)
		elements_written += (int)fwrite(device->codec[g_codec_group_first_codec[codec_group] + i].pixels_per_second, sizeof(double), device->codec[g_codec_group_first_codec[codec_group] + i].num_modes, f);
	elements_written += (int)fwrite(reference_source, 1, text_size, f);
	elements_written += (int)fwrite(program_binary, 1, binary_size, f);
	if (device->is_opencl)
		elements_written += (int)fwrite(device->cl_device_info.name, 1, name_size, f);
	else
		elements_written += (int)fwrite("CPU", 1, name_size, f);
	if (device->is_opencl)
		elements_written += (int)fwrite(device->cl_device_info.driver_version, 1, driver_size, f);
	else
		elements_written += (int)fwrite("Version 1.0", 1, driver_size, f);
	if (buildlog)
		elements_written += (int)fwrite(buildlog, 1, build_log_size, f);

CLEANUP:
	Mem_Free(buildlog);
	Mem_Free(program_binary);
	Mem_Free(path);
	if (f)
		fclose(f);

	if (f && (elements_written != num_elements + binary_version_len + text_size + binary_size + name_size + driver_size + build_log_size))
	{
		error = -1;
		ALWAYS_PRINT("Error in writing compiled binary (expected %i, got %i)\n", num_elements + binary_version_len + text_size + binary_size + name_size, elements_written);
		return error;
	}
	return 0;
}

int Codec_LoadCodecGroupData(device_t *device, codec_group_e codec_group, int inspect_only)
{
	wchar_t *path;
	FILE *f = 0;
	int require_compile = 1;
	unsigned char uuid[16];
	unsigned char current_uuid[16];
	int text_size = 0;
	int binary_size = 0;
	int name_size = 0;
	int driver_size = 0;
	int build_log_size = 0;
	int text_offset;
	int binary_offset;
	int name_offset;
	int driver_offset;
	int build_log_offset;
	int read_elements = 0;
	char *data = 0;
	char *name = 0;
	char *driver = 0;
	int binary_version_len;
	char *binary_version_string = 0;
	char *build_log = 0;
	char *source = 0;
	int i;
	int base_bytes;
	int num_elements;
	char *reference_source = device->device_group->cl_source[codec_group];

	if (!device->is_opencl)
		reference_source = "";

	for (i = 0; i < g_codec_group_num_codecs[codec_group]; i++)
		Codec_Init(&device->codec[g_codec_group_first_codec[codec_group] + i], device->device_group->num_modes[codec_group]);

	if (!device->is_context_and_queue_valid && device->is_opencl)
	{
		ALWAYS_PRINT("Invalid context and queue for device %i\n", device->cl_index);
		return -1;
	}
	if (device->is_opencl)
		path = CL_GetBinaryPath(device->cl_index, Codec_GroupAsString(codec_group));
	else
		path = CL_GetBinaryPath(-1, Codec_GroupAsString(codec_group));

	LOG_PRINT("Loading binary from path \"%ls\"\n", path); 

	_wfopen_s(&f, path, L"rb");

	if (!f)
	{
		ALWAYS_PRINT("No precompiled binary.\n");
		goto FINAL_STAGE;
	}

	base_bytes = 16 + sizeof(int) * 12;
	for (i = 0; i < g_codec_group_num_codecs[codec_group]; i++)
		base_bytes += device->codec[g_codec_group_first_codec[codec_group] + i].num_modes * (sizeof(int) + sizeof(double));
	num_elements = 28;
	for (i = 0; i < g_codec_group_num_codecs[codec_group]; i++)
		num_elements += device->codec[g_codec_group_first_codec[codec_group] + i].num_modes * 2;

	read_elements += (int)fread(&binary_version_len, sizeof(int), 1, f);

	if (binary_version_len != strlen(device->device_group->binary_version_string[codec_group]))
	{
		ALWAYS_PRINT("Binary version does not match.\n");
		goto FINAL_STAGE;
	}
	binary_version_string = Mem_Malloc(binary_version_len);
	read_elements += (int)fread(binary_version_string, sizeof(char), binary_version_len, f);
	read_elements += (int)fread(uuid, sizeof(char), 16, f);
	read_elements += (int)fread(&device->is_valid, sizeof(int), 1, f);
	read_elements += (int)fread(&text_size, sizeof(int), 1, f);
	read_elements += (int)fread(&text_offset, sizeof(int), 1, f);
	read_elements += (int)fread(&binary_size, sizeof(int), 1, f);
	read_elements += (int)fread(&binary_offset, sizeof(int), 1, f);
	read_elements += (int)fread(&name_size, sizeof(int), 1, f);
	read_elements += (int)fread(&name_offset, sizeof(int), 1, f);
	read_elements += (int)fread(&driver_size, sizeof(int), 1, f);
	read_elements += (int)fread(&driver_offset, sizeof(int), 1, f);
	read_elements += (int)fread(&build_log_size, sizeof(int), 1, f);
	read_elements += (int)fread(&build_log_offset, sizeof(int), 1, f);
	for (i = 0; i < g_codec_group_num_codecs[codec_group]; i++)
		read_elements += (int)fread(device->codec[g_codec_group_first_codec[codec_group] + i].macroblock_size, sizeof(int), device->codec[g_codec_group_first_codec[codec_group] + i].num_modes, f);
	for (i = 0; i < g_codec_group_num_codecs[codec_group]; i++)
		read_elements += (int)fread(device->codec[g_codec_group_first_codec[codec_group] + i].pixels_per_second, sizeof(double), device->codec[g_codec_group_first_codec[codec_group] + i].num_modes, f);

	for (i = 0; i < g_codec_group_num_codecs[codec_group]; i++)
		for (int j = 0; j < device->codec[g_codec_group_first_codec[codec_group] + i].num_modes; j++)
		{
			LOG_PRINT("Codec %i macroblock size: %i x %i, megapixels per second: %.2f\n", i, device->codec[g_codec_group_first_codec[codec_group] + i].macroblock_size[j], device->codec[g_codec_group_first_codec[codec_group] + i].macroblock_size[j], device->codec[g_codec_group_first_codec[codec_group] + i].pixels_per_second[j] / 1000000.0);
		}

	System_GetBIOSUUID(current_uuid);

	if (memcmp(binary_version_string, device->device_group->binary_version_string[codec_group], binary_version_len))
	{
		ALWAYS_PRINT("Binary version does not match.\n");
		goto FINAL_STAGE;
	}
	if (memcmp(current_uuid, uuid, 16))
	{
		ALWAYS_PRINT("UUID of binary does not match.\n");
		goto FINAL_STAGE;
	}
	if (read_elements != num_elements + binary_version_len)
	{
		ALWAYS_PRINT("Corrupted binary (read %i elements, expected %i).\n", read_elements, num_elements + binary_version_len);
		goto FINAL_STAGE;
	}
	if (strlen(reference_source) != text_size)
	{
		ALWAYS_PRINT("CL source code does not match binary (%i vs %i).\n", (int)strlen(reference_source), text_size);
		goto FINAL_STAGE;
	}
	source = Mem_Malloc(text_size);
	fseek(f, text_offset, SEEK_SET);
	read_elements = (int)fread(source, 1, text_size, f);

	if (read_elements != text_size)
	{
		ALWAYS_PRINT("Corrupted binary.\n");
		goto FINAL_STAGE;
	}
	if (memcmp(source, reference_source, text_size))
	{
		ALWAYS_PRINT("CL source code does not match binary.\n");
		goto FINAL_STAGE;
	}

	data = Mem_Malloc(binary_size);
	fseek(f, binary_offset, SEEK_SET);
	read_elements = (int)fread(data, 1, binary_size, f);

	if (read_elements != binary_size)
	{
		ALWAYS_PRINT("Corrupted binary.\n");
		goto FINAL_STAGE;
	}

	name = Mem_Malloc(name_size);
	fseek(f, name_offset, SEEK_SET);
	read_elements = (int)fread(name, 1, name_size, f);

	if (read_elements != name_size)
	{
		ALWAYS_PRINT("Corrupted binary.\n");
		goto FINAL_STAGE;
	}
	if (device->is_opencl)
	{
		if (strlen(device->cl_device_info.name) != name_size)
		{
			ALWAYS_PRINT("Device name mismatch in binary.\n");
			goto FINAL_STAGE;
		}
		if (memcmp(device->cl_device_info.name, name, name_size))
		{
			ALWAYS_PRINT("Device name mismatch in binary.\n");
			goto FINAL_STAGE;
		}
	}
	else
	{
		if (strlen("CPU") != name_size)
		{
			ALWAYS_PRINT("Device name mismatch in binary.\n");
			goto FINAL_STAGE;
		}
		if (memcmp("CPU", name, name_size))
		{
			ALWAYS_PRINT("Device name mismatch in binary.\n");
			goto FINAL_STAGE;
		}
	}

	driver = Mem_Malloc(driver_size);
	fseek(f, driver_offset, SEEK_SET);
	read_elements = (int)fread(driver, 1, driver_size, f);

	if (read_elements != driver_size)
	{
		ALWAYS_PRINT("Corrupted binary.\n");
		goto FINAL_STAGE;
	}
	if (device->is_opencl)
	{
		if (strlen(device->cl_device_info.driver_version) != driver_size)
		{
			ALWAYS_PRINT("Device driver version mismatch in binary.\n");
			goto FINAL_STAGE;
		}
		if (memcmp(device->cl_device_info.driver_version, driver, driver_size))
		{
			ALWAYS_PRINT("Device driver version mismatch in binary.\n");
			goto FINAL_STAGE;
		}
	}
	else
	{
		if (strlen("Version 1.0") != driver_size)
		{
			ALWAYS_PRINT("Device driver version mismatch in binary.\n");
			goto FINAL_STAGE;
		}
		if (memcmp("Version 1.0", driver, driver_size))
		{
			ALWAYS_PRINT("Device driver version mismatch in binary.\n");
			goto FINAL_STAGE;
		}
	}

	build_log = Mem_Malloc(build_log_size + 1);
	fseek(f, build_log_offset, SEEK_SET);
	read_elements = (int)fread(build_log, 1, build_log_size, f);
	build_log[build_log_size] = '\0';

	if (read_elements != build_log_size)
	{
		ALWAYS_PRINT("Corrupted binary.\n");
		goto FINAL_STAGE;
	}

	if (inspect_only)
	{
		Mem_Free(source);
		Mem_Free(data);
		Mem_Free(name);
		Mem_Free(driver);
		Mem_Free(binary_version_string);
		Mem_Free(build_log);
		Mem_Free(path);

		if (device->is_valid && device->is_opencl)
			return 0;
		else if (!device->is_valid && device->is_opencl)
			return -1;
		else
			return 0;
	}

	if (device->is_valid && device->is_opencl)
	{
		CL_LoadBinaryCodec(device, &device->cl_program[codec_group], data, binary_size);

		for (i = 0; i < g_codec_group_num_codecs[codec_group]; i++)
			Codec_Create(&device->codec[g_codec_group_first_codec[codec_group] + i], device->device_group->cl_kernel_function[codec_group][i]);
	}

	require_compile = 0;

	if (!device->is_valid)
	{
		int j;
		for (i = 0; i < g_codec_group_num_codecs[codec_group]; i++)
			for (j = 0; j < device->codec[g_codec_group_first_codec[codec_group] + i].num_modes; j++)
				device->codec[g_codec_group_first_codec[codec_group] + i].macroblock_size[j] = 1;
		for (i = 0; i < g_codec_group_num_codecs[codec_group]; i++)
			for (j = 0; j < device->codec[g_codec_group_first_codec[codec_group] + i].num_modes; j++)
				device->codec[g_codec_group_first_codec[codec_group] + i].pixels_per_second[j] = 1.0;
	}

FINAL_STAGE:

	Mem_Free(source);
	Mem_Free(data);
	Mem_Free(name);
	Mem_Free(driver);
	Mem_Free(binary_version_string);

	if(f)
		fclose(f);

	if (require_compile || TEST_OPENCL_ONLY)
	{
		int local_is_valid;

		if (device->is_opencl)
		{
			if (CL_CompileCodec(device, &device->cl_program[codec_group], reference_source, &local_is_valid))
			{
				int j;

				device->is_valid = local_is_valid;

				for (i = 0; i < g_codec_group_num_codecs[codec_group]; i++)
					for (j = 0; j < device->codec[g_codec_group_first_codec[codec_group] + i].num_modes; j++)
						device->codec[g_codec_group_first_codec[codec_group] + i].macroblock_size[j] = 1;
				for (i = 0; i < g_codec_group_num_codecs[codec_group]; i++)
					for (j = 0; j < device->codec[g_codec_group_first_codec[codec_group] + i].num_modes; j++)
						device->codec[g_codec_group_first_codec[codec_group] + i].pixels_per_second[j] = 1.0;

				Codec_SaveGroup(device->device_group, Device_DeviceIndexFromDevice(device), codec_group);

				Mem_Free(build_log);
				Mem_Free(path);
				return -1;
			}
			device->is_valid = local_is_valid;
		}
		else
			device->is_valid = 1;

		if (device->is_valid)
		{
			ALWAYS_PRINT_NODEC("Finding optimal parameters for device \"%s\", this should take less than a minute.\n", device->is_opencl ? device->cl_device_info.name : "CPU");
			for (i = 0; i < g_codec_group_num_codecs[codec_group]; i++)
				Codec_Create(&device->codec[g_codec_group_first_codec[codec_group] + i], device->device_group->cl_kernel_function[codec_group][i]);
			if (device->device_group->cl_test_codec_group_fp[codec_group](device) && device->is_opencl)
				device->is_valid = 0;
			Codec_SaveGroup(device->device_group, Device_DeviceIndexFromDevice(device), codec_group);
		}
	}


	Mem_Free(build_log);
	Mem_Free(path);

	if (!device->is_valid)
	{
		ALWAYS_PRINT("Compilation errors during last build.\n");
		if (build_log)
			LOG_PRINT("Build log:\n==========\nLength: %i\n\n%s\n", (int)build_log_size, build_log);
		else
			LOG_PRINT("No build log.\n");
		return -1;
	}

	return 0;
}



char *Codec_AsString(codec_e codec)
{
	switch (codec)
	{
		case CODEC_ETC1: return "ETC1";
		case CODEC_ETC2_RGB: return "ETC2_RGB";
		case CODEC_ETC2_RGBA1: return "ETC2_RGBA1";
		case CODEC_ETC2_RGBA8: return "ETC2_RGBA8";
		case CODEC_BC1_RGB: return "BC1_RGB";
		case CODEC_BC1_RGBA: return "BC1_RGBA";
		case CODEC_BC2_RGBA: return "BC2_RGBA";
		case CODEC_BC3_RGBA: return "BC3_RGBA";
		case CODEC_BC4_RED: return "BC4_RED";
		case CODEC_BC5_RG: return "BC5_RG";
		default: return "<UNKNOWN>";
	}
}

void Codec_Init(codec_t *codec, int num_modes)
{
	int i;

	codec->num_modes = num_modes;
	codec->macroblock_size = Mem_Malloc(num_modes * sizeof(int));
	codec->pixels_per_second = Mem_Malloc(num_modes * sizeof(double));

	for (i = 0; i < num_modes; i++)
	{
		codec->macroblock_size[i] = 1;
		codec->pixels_per_second[i] = 1.0;
	}
}

int Codec_Create(codec_t *codec, char *function)
{
	cl_int err = CL_SUCCESS;
	size_t work_group_size = 0;

	if (codec->device->is_opencl)
	{
		codec->cl_kernel = clCreateKernel(*(codec->cl_program), function, &err);

		COND_PRINT(err, "clCreateKernel result: %i (%s), kernel ID %I64u, function \"%s\"\n", err, OpenCL_ErrorString(err), (uint64_t)codec->cl_kernel, function);
		if (err != CL_SUCCESS)
			goto FINAL_STAGE;

		clGetKernelWorkGroupInfo(codec->cl_kernel, codec->device->cl_device_info.id, CL_KERNEL_WORK_GROUP_SIZE, sizeof(size_t), &work_group_size, NULL);

		codec->local_group_size = (int)Math_FloorPow2u64(work_group_size);

		while(((size_t)codec->local_group_size) * ((size_t)codec->local_group_size) > work_group_size)
			codec->local_group_size >>= 1;
	}
	else
		codec->local_group_size = 0;


FINAL_STAGE:
	if (err != CL_SUCCESS)
		return -1;
	return 0;
}

void Codec_Destroy(codec_t *codec)
{
	Mem_Free(codec->pixels_per_second);
	Mem_Free(codec->macroblock_size);

	if (codec->device->is_opencl)
	{
		if (codec->cl_kernel)
			clReleaseKernel(codec->cl_kernel);
	}

	memset(codec, 0, sizeof(codec_t));
}
double Codec_GetPerformance(device_group_t *device_group, int device_index, codec_e codec, void *context)
{
	device_t *device = &device_group->device[device_index];
	codec_options_generic_t *options = (codec_options_generic_t*)context;

	return device->codec[codec].pixels_per_second[options->quality];
}
int Codec_GetEncodeChunks(device_group_t *device_group, int device_index, image_t *image, codec_e codec, int mip_level, int override_macro_size, void *context)
{
	device_t *device = &device_group->device[device_index];

	if (device->is_opencl)
	{
		codec_options_generic_t *options = (codec_options_generic_t*)context;
		int blocks_x = (image->src_width[mip_level] + 3) >> 2;
		int blocks_y = (image->src_height[mip_level] + 3) >> 2;
		int chunks_x;
		int chunks_y;
		int macroblock_size;

		if (override_macro_size)
			macroblock_size = override_macro_size;
		else
			macroblock_size = device->codec[codec].macroblock_size[options->quality];

		chunks_x = (blocks_x + macroblock_size - 1) / macroblock_size;
		chunks_y = (blocks_y + macroblock_size - 1) / macroblock_size;

		return chunks_x * chunks_y;
	}
	else
	{
		int blocks_x = (image->src_width[mip_level] + 3) >> 2;
		int blocks_y = (image->src_height[mip_level] + 3) >> 2;

		if (g_codec_to_group[codec] == CODEC_GROUP_ETC)
		{
			codec_options_generic_t *options = (codec_options_generic_t*)context;

			int chunks_x;
			int chunks_y;
			int macroblock_size;

			if (override_macro_size)
				macroblock_size = override_macro_size;
			else
				macroblock_size = device->codec[codec].macroblock_size[options->quality];

			chunks_x = (blocks_x + macroblock_size - 1) / macroblock_size;
			chunks_y = (blocks_y + macroblock_size - 1) / macroblock_size;

			return chunks_x * chunks_y;
		}
		else
			return blocks_x * blocks_y;
	}
}
int Codec_Encode(device_group_t *device_group, int device_index, image_t *image, codec_e codec, int mip_level, int override_macro_size, uint64_t *kernel_ticks, uint64_t *total_ticks, void *context)
{
	device_t *device = &device_group->device[device_index];

	if (device->is_opencl)
		return CL_Encode(device, image, codec, mip_level, override_macro_size, kernel_ticks, total_ticks, context);
	else
		return CPU_Encode(device, image, codec, mip_level, override_macro_size, kernel_ticks, total_ticks, context);
}
int Codec_Decode(device_group_t *device_group, int device_index, image_t *image, codec_e codec, int mip_level, int override_macro_size, uint64_t *kernel_ticks, uint64_t *total_ticks, void *context)
{
	return -1;
}
int Codec_LoadGroup(device_group_t *device_group, int device_index, codec_group_e group_index)
{
	device_t *device = &device_group->device[device_index];

	return Codec_LoadCodecGroupData(device, group_index, 0);
}
int Codec_InspectGroup(device_group_t *device_group, int device_index, codec_group_e group_index)
{
	device_t *device = &device_group->device[device_index];

	return Codec_LoadCodecGroupData(device, group_index, 1);
}
int Codec_SaveGroup(device_group_t *device_group, int device_index, codec_group_e group_index)
{
	device_t *device = &device_group->device[device_index];

	return Codec_SaveCodecGroupData(device, group_index);
}

int Codec_GroupFromCodec(codec_e codec)
{
	return g_codec_to_group[codec];
}
void Codec_DeInspectGroup(device_t *device, codec_group_e group)
{
	int i;
	for (i = 0; i < g_codec_group_num_codecs[group]; i++)
	{
		Mem_Free(device->codec[g_codec_group_first_codec[group] + i].macroblock_size);
		Mem_Free(device->codec[g_codec_group_first_codec[group] + i].pixels_per_second);
		device->codec[g_codec_group_first_codec[group] + i].macroblock_size = 0;
		device->codec[g_codec_group_first_codec[group] + i].pixels_per_second = 0;
	}
}








void Device_Destroy(device_t *device)
{
	int i;

	if (device->is_opencl)
	{
		CL_FreeDeviceInfo(&device->cl_device_info);
	}

	for (i = 0; i < CODEC_GROUP_NUM_GROUPS; i++)
	{
		if (device->is_opencl)
		{
			if (device->cl_program[i])
				clReleaseProgram(device->cl_program[i]);
		}
	}

	for (i = 0; i < CODEC_NUM_CODECS; i++)
	{
		Codec_Destroy(&device->codec[i]);
	}

	if (device->is_opencl)
	{
		LOG_PRINT("Releasing context, queue, mem objects\n");
		if (device->cl_queue)
			clReleaseCommandQueue(device->cl_queue);
		if (device->cl_context)
			clReleaseContext(device->cl_context);
		if (device->cl_mem_in)
			clReleaseMemObject(device->cl_mem_in);
		if (device->cl_mem_out)
			clReleaseMemObject(device->cl_mem_out);
	}

	memset(device, 0, sizeof(device_t));
}

int Device_DeviceIndexFromDevice(device_t *device)
{
	return (int)(device - device->device_group->device);
}









device_group_t *DeviceGroup_New()
{
	device_group_t *device_group = 0;
	cl_device_info_t *cl_device_info_p = 0;
	int i;

	device_group = Mem_Malloc(sizeof(device_group_t));
	memset(device_group, 0, sizeof(device_group_t));

	device_group->num_devices = CL_InitState(&cl_device_info_p);

	device_group->device = Mem_Malloc(sizeof(device_t) * (device_group->num_devices + 1));
	
	memset(device_group->device, 0, sizeof(device_t) * (device_group->num_devices + 1));

	for (i = 0; i < device_group->num_devices; i++)
	{
		device_group->device[i + DEVICE_CL_START].is_opencl = 1;
		device_group->device[i + DEVICE_CL_START].is_context_and_queue_valid = 1;
		device_group->device[i + DEVICE_CL_START].cl_device_info = cl_device_info_p[i];

		if (CL_CreateContextAndQueueDirect(&device_group->device[i + DEVICE_CL_START].cl_context, &device_group->device[i + DEVICE_CL_START].cl_queue, &device_group->device[i + DEVICE_CL_START].cl_device_info))
			device_group->device[i + DEVICE_CL_START].is_context_and_queue_valid = 0;
	}

	Mem_Free(cl_device_info_p);

	device_group->num_devices++;

	for (i = 0; i < device_group->num_devices; i++)
	{
		int j;

		for (j = 0; j < CODEC_NUM_CODECS; j++)
		{
			device_group->device[i].device_group = device_group;
			device_group->device[i].codec[j].device = &device_group->device[i];
			device_group->device[i].codec[j].cl_program = &device_group->device[i].cl_program[Codec_GroupFromCodec(j)];
		}
	}

	return device_group;
}

void DeviceGroup_Destroy(device_group_t *device_group)
{
	int i;
	LOG_PRINT("Freeing %i devices\n", device_group->num_devices);
	for (i = 0; i < device_group->num_devices; i++)
		Device_Destroy(&device_group->device[i]);

	Mem_Free(device_group->device);
	for (i = 0; i < CODEC_GROUP_NUM_GROUPS; i++)
		Mem_Free(device_group->cl_kernel_function[i]);

	memset(device_group, 0, sizeof(device_group_t));
}
