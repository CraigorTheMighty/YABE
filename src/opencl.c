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

#include "..\inc\timer.h"
#include "..\inc\system.h"
#include "..\inc\math.h"
#include "..\inc\memory.h"
#include "..\inc\image.h"
#include "..\inc\device_codec.h"
#include "..\inc\opencl.h"
#include "..\inc\etc.h"

#if TEST_PRINT_SOURCE
static int g_is_print = 0;
#endif

cl_instance_t g_etc_cl_instance = {0};
cl_instance_t g_bcn_cl_instance = {0};

char *OpenCL_ErrorString(int error)
{
	switch (error)
	{
		case CL_SUCCESS:									return "CL_SUCCESS";
		case CL_DEVICE_NOT_FOUND:							return "CL_DEVICE_NOT_FOUND";
		case CL_DEVICE_NOT_AVAILABLE:						return "CL_DEVICE_NOT_AVAILABLE";
		case CL_COMPILER_NOT_AVAILABLE:						return "CL_COMPILER_NOT_AVAILABLE";
		case CL_MEM_OBJECT_ALLOCATION_FAILURE:				return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
		case CL_OUT_OF_RESOURCES:							return "CL_OUT_OF_RESOURCES";
		case CL_OUT_OF_HOST_MEMORY:							return "CL_OUT_OF_HOST_MEMORY";
		case CL_PROFILING_INFO_NOT_AVAILABLE:				return "CL_PROFILING_INFO_NOT_AVAILABLE";
		case CL_MEM_COPY_OVERLAP:							return "CL_MEM_COPY_OVERLAP";
		case CL_IMAGE_FORMAT_MISMATCH:						return "CL_IMAGE_FORMAT_MISMATCH";
		case CL_IMAGE_FORMAT_NOT_SUPPORTED:					return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
		case CL_BUILD_PROGRAM_FAILURE:						return "CL_BUILD_PROGRAM_FAILURE";
		case CL_MAP_FAILURE:								return "CL_MAP_FAILURE";
		case CL_MISALIGNED_SUB_BUFFER_OFFSET:				return "CL_MISALIGNED_SUB_BUFFER_OFFSET";
		case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST:	return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
		case CL_COMPILE_PROGRAM_FAILURE:					return "CL_COMPILE_PROGRAM_FAILURE";
		case CL_LINKER_NOT_AVAILABLE:						return "CL_LINKER_NOT_AVAILABLE";
		case CL_LINK_PROGRAM_FAILURE:						return "CL_LINK_PROGRAM_FAILURE";
		case CL_DEVICE_PARTITION_FAILED:					return "CL_DEVICE_PARTITION_FAILED";
		case CL_KERNEL_ARG_INFO_NOT_AVAILABLE:				return "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";
		case CL_INVALID_VALUE:								return "CL_INVALID_VALUE";
		case CL_INVALID_DEVICE_TYPE:						return "CL_INVALID_DEVICE_TYPE";
		case CL_INVALID_PLATFORM:							return "CL_INVALID_PLATFORM";
		case CL_INVALID_DEVICE:								return "CL_INVALID_DEVICE";
		case CL_INVALID_CONTEXT:							return "CL_INVALID_CONTEXT";
		case CL_INVALID_QUEUE_PROPERTIES:					return "CL_INVALID_QUEUE_PROPERTIES";
		case CL_INVALID_COMMAND_QUEUE:						return "CL_INVALID_COMMAND_QUEUE";
		case CL_INVALID_HOST_PTR:							return "CL_INVALID_HOST_PTR";
		case CL_INVALID_MEM_OBJECT:							return "CL_INVALID_MEM_OBJECT";
		case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:			return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
		case CL_INVALID_IMAGE_SIZE:							return "CL_INVALID_IMAGE_SIZE";
		case CL_INVALID_SAMPLER:							return "CL_INVALID_SAMPLER";
		case CL_INVALID_BINARY:								return "CL_INVALID_BINARY";
		case CL_INVALID_BUILD_OPTIONS:						return "CL_INVALID_BUILD_OPTIONS";
		case CL_INVALID_PROGRAM:							return "CL_INVALID_PROGRAM";
		case CL_INVALID_PROGRAM_EXECUTABLE:					return "CL_INVALID_PROGRAM_EXECUTABLE";
		case CL_INVALID_KERNEL_NAME:						return "CL_INVALID_KERNEL_NAME";
		case CL_INVALID_KERNEL_DEFINITION:					return "CL_INVALID_KERNEL_DEFINITION";
		case CL_INVALID_KERNEL:								return "CL_INVALID_KERNEL";
		case CL_INVALID_ARG_INDEX:							return "CL_INVALID_ARG_INDEX";
		case CL_INVALID_ARG_VALUE:							return "CL_INVALID_ARG_VALUE";
		case CL_INVALID_ARG_SIZE:							return "CL_INVALID_ARG_SIZE";
		case CL_INVALID_KERNEL_ARGS:						return "CL_INVALID_KERNEL_ARGS";
		case CL_INVALID_WORK_DIMENSION:						return "CL_INVALID_WORK_DIMENSION";
		case CL_INVALID_WORK_GROUP_SIZE:					return "CL_INVALID_WORK_GROUP_SIZE";
		case CL_INVALID_WORK_ITEM_SIZE:						return "CL_INVALID_WORK_ITEM_SIZE";
		case CL_INVALID_GLOBAL_OFFSET:						return "CL_INVALID_GLOBAL_OFFSET";
		case CL_INVALID_EVENT_WAIT_LIST:					return "CL_INVALID_EVENT_WAIT_LIST";
		case CL_INVALID_EVENT:								return "CL_INVALID_EVENT";
		case CL_INVALID_OPERATION:							return "CL_INVALID_OPERATION";
		case CL_INVALID_GL_OBJECT:							return "CL_INVALID_GL_OBJECT";
		case CL_INVALID_BUFFER_SIZE:						return "CL_INVALID_BUFFER_SIZE";
		case CL_INVALID_MIP_LEVEL:							return "CL_INVALID_MIP_LEVEL";
		case CL_INVALID_GLOBAL_WORK_SIZE:					return "CL_INVALID_GLOBAL_WORK_SIZE";
		case CL_INVALID_PROPERTY:							return "CL_INVALID_PROPERTY";
		case CL_INVALID_IMAGE_DESCRIPTOR:					return "CL_INVALID_IMAGE_DESCRIPTOR";
		case CL_INVALID_COMPILER_OPTIONS:					return "CL_INVALID_COMPILER_OPTIONS";
		case CL_INVALID_LINKER_OPTIONS:						return "CL_INVALID_LINKER_OPTIONS";
		case CL_INVALID_DEVICE_PARTITION_COUNT:				return "CL_INVALID_DEVICE_PARTITION_COUNT";
		case CL_INVALID_PIPE_SIZE:							return "CL_INVALID_PIPE_SIZE";
		case CL_INVALID_DEVICE_QUEUE:						return "CL_INVALID_DEVICE_QUEUE";
#ifdef CL_VERSION_2_2
		case CL_INVALID_SPEC_ID:							return "CL_INVALID_SPEC_ID";
		case CL_MAX_SIZE_RESTRICTION_EXCEEDED:				return "CL_MAX_SIZE_RESTRICTION_EXCEEDED";
#endif
		default:											return "<UNKNOWN_ERROR>";
	}
}
char *CL_DeviceTypeToString(cl_device_type type)
{
	char *string = Mem_Malloc(32768);

	if (!string)
	{
		LOG_PRINT("malloc failure\n");
		return 0;
	}

	memset(string, 0, 32768);

	if (type & CL_DEVICE_TYPE_DEFAULT)
	{
		if (strlen(string))
			strcat_s(string, 16384, ", ");
		strcat_s(string, 16384, "CL_DEVICE_TYPE_DEFAULT");
	}
	if (type & CL_DEVICE_TYPE_CPU)
	{
		if (strlen(string))
			strcat_s(string, 16384, ", ");
		strcat_s(string, 16384, "CL_DEVICE_TYPE_CPU");
	}
	if (type & CL_DEVICE_TYPE_GPU)
	{
		if (strlen(string))
			strcat_s(string, 16384, ", ");
		strcat_s(string, 16384, "CL_DEVICE_TYPE_GPU");
	}
	if (type & CL_DEVICE_TYPE_ACCELERATOR)
	{
		if (strlen(string))
			strcat_s(string, 16384, ", ");
		strcat_s(string, 16384, "CL_DEVICE_TYPE_ACCELERATOR");
	}
	if (type & CL_DEVICE_TYPE_CUSTOM)
	{
		if (strlen(string))
			strcat_s(string, 16384, ", ");
		strcat_s(string, 16384, "CL_DEVICE_TYPE_CUSTOM");
	}
	if (!strlen(string))
	{
		strcat_s(string, 16384, "<UNKNOWN DEVICE TYPE>");
	}
	return string;
}

wchar_t *CL_GetBinaryPath(int device_index, char *suffix)
{
	wchar_t *path = Mem_Malloc(sizeof(wchar_t) * 65536);
	int len;
	unsigned char uuid[16];

	if (!path)
	{
		LOG_PRINT("malloc failure\n");
		return 0;
	}

	System_GetBIOSUUID(uuid);

	len = GetModuleFileNameEx(GetCurrentProcess(), NULL, path, 32768);	// get the path and filename of the executable of this process
	wchar_t *sptr = wcsrchr(path, L'\\');
	*sptr = 0;
	*sptr++ = L'\\';
	for (int i = 0; i < 16; i++)
	{
		if (i == 4 || i == 6 || i == 8 || i == 10)
		{
			swprintf(sptr, 16384, L"-");
			sptr++;
		}
		swprintf(sptr, 16384, L"%02X", uuid[i]);
		sptr+=2;
	}
	if (device_index != -1)
		swprintf(sptr, 16384, L"_DEVICE_%i_%S_CL.clb", device_index, suffix);
	else
		swprintf(sptr, 16384, L"_DEVICE_CPU_%S.clb", suffix);

	return path;
}

int CL_DeviceCVersion(cl_device_info_t *device_info, int *major_version, int *minor_version)
{
	char *ptr = device_info->opencl_c_version + strlen("OpenCL C ");
	
	*major_version = 0;
	*minor_version = 0;

	if (strlen(device_info->opencl_c_version) <= strlen("OpenCL C "))
	{
		return -1;
	}

	*major_version = atoi(ptr);
	ptr = strchr(ptr, '.');

	if (!ptr)
		return 0;

	*minor_version = atoi(ptr + 1);

	return 0;
}
int CL_DeviceCLVersion(cl_device_info_t *device_info, int *major_version, int *minor_version)
{
	char *ptr = device_info->version + strlen("OpenCL ");

	*major_version = 0;
	*minor_version = 0;

	if (strlen(device_info->version) <= strlen("OpenCL "))
	{
		return -1;
	}

	*major_version = atoi(ptr);
	ptr = strchr(ptr, '.');

	if (!ptr)
		return 0;

	*minor_version = atoi(ptr + 1);

	return 0;
}
void CL_FreeDeviceInfo(cl_device_info_t *device_info)
{
	Mem_Free(device_info->name);
	Mem_Free(device_info->vendor);
	Mem_Free(device_info->version);
	Mem_Free(device_info->profile);
	Mem_Free(device_info->opencl_c_version);
	Mem_Free(device_info->extensions);
	Mem_Free(device_info->driver_version);
	memset(device_info, 0, sizeof(cl_device_info_t));
}

void CL_PrintDeviceInfo(cl_device_info_t *device_info, int prefix)
{
	char *device_type;
	int major_c_version;
	int minor_c_version;
	int major_cl_version;
	int minor_cl_version;

	CL_DeviceCLVersion(device_info, &major_cl_version, &minor_cl_version);
	CL_DeviceCVersion(device_info, &major_c_version, &minor_c_version);

	ALWAYS_PRINT_NODEC("\tCL device %i:\n\n", prefix);
	ALWAYS_PRINT_NODEC("\t\tID: %I64u\n", (uint64_t)device_info->id);
	device_type = CL_DeviceTypeToString(device_info->type);
	ALWAYS_PRINT_NODEC("\t\tTYPE: %s\n", device_type);
	Mem_Free(device_type);
	ALWAYS_PRINT_NODEC("\t\tMAX_WORK_GROUP_SIZE: %u\n", device_info->max_work_group_size);
	ALWAYS_PRINT_NODEC("\t\tMAX_COMPUTE_UNITS: %u\n", device_info->max_compute_units);
	ALWAYS_PRINT_NODEC("\t\tMAX_CLOCK_FREQUENCY: %u\n", device_info->max_clock_frequency);
	ALWAYS_PRINT_NODEC("\t\tAVAILABLE: %i\n", device_info->available);
	ALWAYS_PRINT_NODEC("\t\tCOMPILER_AVAILABLE: %i\n", device_info->compiler_available);
	ALWAYS_PRINT_NODEC("\t\tLINKER_AVAILABLE: %i\n", device_info->linker_available);
	ALWAYS_PRINT_NODEC("\t\tEXECUTION_CAPABILITIES: %I64u\n", (uint64_t)device_info->execution_capabilities);
	ALWAYS_PRINT_NODEC("\t\tPLATFORM: %I64u\n", (uint64_t)device_info->platform);
	ALWAYS_PRINT_NODEC("\t\tMEMORY: %I64u (%.2f GB)\n", (uint64_t)device_info->memory, device_info->memory / 1073741824.0f);
	ALWAYS_PRINT_NODEC("\t\tNAME: %s\n", device_info->name);
	ALWAYS_PRINT_NODEC("\t\tVENDOR: %s\n", device_info->vendor);
	ALWAYS_PRINT_NODEC("\t\tVERSION: %s (%i.%i)\n", device_info->version, major_cl_version, minor_cl_version);
	ALWAYS_PRINT_NODEC("\t\tPROFILE: %s\n", device_info->profile);
	ALWAYS_PRINT_NODEC("\t\tOPENCL_C_VERSION: %s (%i.%i)\n", device_info->opencl_c_version, major_c_version, minor_c_version);
	ALWAYS_PRINT_NODEC("\t\tCL_DRIVER_VERSION: %s\n", device_info->driver_version);
	ALWAYS_PRINT_NODEC("\t\tEXTENSIONS: %s\n\n", device_info->extensions);
}

int CL_EnumDevices(cl_platform_id platform, cl_device_type device_hw_type, cl_device_info_t **device_info)
{
	int j, k;
	cl_uint num_devices;
	cl_device_id *device_id;
	size_t param_value_size_ret;
	cl_int err;

	err = clGetDeviceIDs(platform, device_hw_type, 0, NULL, &num_devices);
	LOG_PRINT("clGetDeviceIDs result: %i (%s)\n", err, OpenCL_ErrorString(err));
	LOG_PRINT("Platform has %u %s devices\n", num_devices, (device_hw_type == CL_DEVICE_TYPE_GPU) ? "GPU" : "CPU");
	if (num_devices && (err == CL_SUCCESS))
	{
		device_id = Mem_Malloc(sizeof(cl_device_id) * num_devices);
		err = clGetDeviceIDs(platform, device_hw_type, num_devices, device_id, NULL);
		COND_PRINT(err, "clGetDeviceIDs result: %i (%s)\n", err, OpenCL_ErrorString(err));
		*device_info = Mem_Malloc(sizeof(cl_device_info_t) * num_devices);

		for (j = 0; j < (int)num_devices; j++)
		{
			cl_device_info device_info_id[] = 
			{
				CL_DEVICE_TYPE,
				CL_DEVICE_MAX_WORK_GROUP_SIZE,
				CL_DEVICE_MAX_COMPUTE_UNITS,
				CL_DEVICE_MAX_CLOCK_FREQUENCY,
				CL_DEVICE_AVAILABLE,
				CL_DEVICE_COMPILER_AVAILABLE,
				CL_DEVICE_LINKER_AVAILABLE,
				CL_DEVICE_EXECUTION_CAPABILITIES,
				CL_DEVICE_PLATFORM,
				CL_DEVICE_GLOBAL_MEM_SIZE,
				CL_DEVICE_NAME,
				CL_DEVICE_VENDOR,
				CL_DEVICE_VERSION,
				CL_DEVICE_PROFILE,
				CL_DEVICE_OPENCL_C_VERSION,
				CL_DEVICE_EXTENSIONS,
				CL_DRIVER_VERSION,
			};
			void *device_info_ptr[sizeof(device_info_id) / sizeof(cl_device_info)];
			LOG_PRINT("Device %i: %I64u\n", j, (uint64_t)device_id[j]);

			for (k = 0; k < sizeof(device_info_ptr) / sizeof(void*); k++)
			{
				clGetDeviceInfo(device_id[j], device_info_id[k], 0, NULL, &param_value_size_ret);
				device_info_ptr[k] = Mem_Malloc(param_value_size_ret);
				clGetDeviceInfo(device_id[j], device_info_id[k], param_value_size_ret, device_info_ptr[k], NULL);
			}
			(*device_info)[j].id = device_id[j];
			(*device_info)[j].type = *(cl_device_type*)device_info_ptr[0];
			(*device_info)[j].max_work_group_size = *(cl_uint*)device_info_ptr[1];
			(*device_info)[j].max_compute_units = *(cl_uint*)device_info_ptr[2];
			(*device_info)[j].max_clock_frequency = *(cl_uint*)device_info_ptr[3];
			(*device_info)[j].available = *(cl_bool*)device_info_ptr[4];
			(*device_info)[j].compiler_available = *(cl_bool*)device_info_ptr[5];
			(*device_info)[j].linker_available = *(cl_bool*)device_info_ptr[6];
			(*device_info)[j].execution_capabilities = *(cl_device_exec_capabilities*)device_info_ptr[7];
			(*device_info)[j].platform = *(cl_platform_id*)device_info_ptr[8];
			(*device_info)[j].memory = *(cl_ulong*)device_info_ptr[9];
			(*device_info)[j].name = (char*)device_info_ptr[10];
			(*device_info)[j].vendor = (char*)device_info_ptr[11];
			(*device_info)[j].version = (char*)device_info_ptr[12];
			(*device_info)[j].profile = (char*)device_info_ptr[13];
			(*device_info)[j].opencl_c_version = (char*)device_info_ptr[14];
			(*device_info)[j].extensions = (char*)device_info_ptr[15];
			(*device_info)[j].driver_version = (char*)device_info_ptr[16];

			for (k = 0; k < 10; k++)
				Mem_Free(device_info_ptr[k]);
		}

		Mem_Free(device_id);
	}
	return num_devices;
}

int CL_InitState(cl_device_info_t **device_info)
{
	cl_int err;
	int i;
	cl_platform_id *cpPlatform;
	cl_uint num_platforms;
	int device_info_num = 0;

	err = clGetPlatformIDs(0, 0, &num_platforms);
	if (num_platforms && err == CL_SUCCESS)
	{
		cpPlatform = Mem_Malloc(sizeof(cl_platform_id) * num_platforms);
		LOG_PRINT("Number of platforms: %i\n", num_platforms);
		err = clGetPlatformIDs(num_platforms, cpPlatform, NULL);

		for (i = 0; i < (int)num_platforms; i++)
		{
			int k;
			size_t param_value_size_ret;
			int dev_num[2];
			cl_device_info_t *local_dev_info[2] = {0};
			cl_platform_info platform_info_id[] = 
			{
				CL_PLATFORM_EXTENSIONS,
				CL_PLATFORM_VERSION,
				CL_PLATFORM_NAME,
				CL_PLATFORM_VENDOR,
				CL_PLATFORM_PROFILE,
			};
			void *platform_info_ptr[sizeof(platform_info_id) / sizeof(cl_platform_info)];

			LOG_PRINT("Platform %i: %I64u\n", i, (uint64_t)cpPlatform[i]);

			for (k = 0; k < sizeof(platform_info_ptr) / sizeof(void*); k++)
			{
				clGetPlatformInfo(cpPlatform[i], platform_info_id[k], 0, NULL, &param_value_size_ret);
				platform_info_ptr[k] = Mem_Malloc(param_value_size_ret);
				clGetPlatformInfo(cpPlatform[i], platform_info_id[k], param_value_size_ret, platform_info_ptr[k], NULL);
			}

			LOG_PRINT("platform_extensions: \"%s\"\n", (char*)platform_info_ptr[0]);
			LOG_PRINT("platform_version: \"%s\"\n", (char*)platform_info_ptr[1]);
			LOG_PRINT("platform_vendor: \"%s\"\n", (char*)platform_info_ptr[2]);
			LOG_PRINT("platform_name: \"%s\"\n", (char*)platform_info_ptr[3]);
			LOG_PRINT("platform_profile: \"%s\"\n", (char*)platform_info_ptr[4]);

			for (k = 0; k < sizeof(platform_info_ptr) / sizeof(void*); k++)
				Mem_Free(platform_info_ptr[k]);

			dev_num[0] = CL_EnumDevices(cpPlatform[i], CL_DEVICE_TYPE_CPU, &local_dev_info[0]);
			dev_num[1] = CL_EnumDevices(cpPlatform[i], CL_DEVICE_TYPE_GPU, &local_dev_info[1]);

			if ((dev_num[0] + dev_num[1]) != 0)
			{
				if (device_info)
				{
					*device_info = Mem_Realloc(*device_info, sizeof(cl_device_info_t) * (device_info_num + dev_num[0] + dev_num[1]));
					memcpy(&(*device_info)[device_info_num], local_dev_info[0], sizeof(cl_device_info_t) * dev_num[0]);
				}
				
				device_info_num += dev_num[0];
				
				if (device_info)
					memcpy(&(*device_info)[device_info_num], local_dev_info[1], sizeof(cl_device_info_t) * dev_num[1]);

				device_info_num += dev_num[1];
			}
			if (!device_info)
			{
				for (k = 0; k < dev_num[0]; k++)
					CL_FreeDeviceInfo(&local_dev_info[0][k]);
				for (k = 0; k < dev_num[1]; k++)
					CL_FreeDeviceInfo(&local_dev_info[1][k]);
			}
			Mem_Free(local_dev_info[0]);
			Mem_Free(local_dev_info[1]);
		}
		Mem_Free(cpPlatform);
	}
	return device_info_num;
}


int CL_ListCLDevices(int print)
{
	int i;
	cl_device_info_t *device_info = 0;
	int device_info_num;

	device_info_num = CL_InitState(&device_info);

	if (device_info_num == 0)
	{
		ALWAYS_PRINT_NODEC("\tNo OpenCL compatible devices\n");
		return 0;
	}
	else
		ALWAYS_PRINT_NODEC("\tFound %i OpenCL device%s.\n\n", device_info_num, device_info_num > 1 ? "s" : "");

	for (i = 0; i < device_info_num; i++)
	{
		if (print)
			CL_PrintDeviceInfo(&device_info[i], i);
		CL_FreeDeviceInfo(&device_info[i]);
	}

	Mem_Free(device_info);

	return device_info_num;
}

int CL_CreateContextAndQueueDirect(cl_context *cl_context, cl_command_queue *cl_queue, cl_device_info_t *device_info)
{
	cl_int err;
	cl_context_properties prop[3];

	prop[0] = CL_CONTEXT_PLATFORM;
	prop[1] = (cl_context_properties)device_info->platform;
	prop[2] = 0;

	LOG_PRINT("Create context\n");
	*cl_context = clCreateContext(&prop[0], 1, &device_info->id, NULL, NULL, &err);
	COND_PRINT(err, "clCreateContext result: %i (%s)\n", err, OpenCL_ErrorString(err));
	if (err != CL_SUCCESS)
		return -1;

	*cl_queue = clCreateCommandQueueWithProperties(*cl_context, device_info->id, 0, &err);
	COND_PRINT(err, "clCreateCommandQueueWithProperties result: %i (%s)\n", err, OpenCL_ErrorString(err));
	if (err != CL_SUCCESS)
	{
		*cl_queue = clCreateCommandQueue(*cl_context, device_info->id, 0, &err);
		COND_PRINT(err, "clCreateCommandQueue result: %i (%s)\n", err, OpenCL_ErrorString(err));
		if (err != CL_SUCCESS)
			return -1;
	}
	return 0;
}

int CL_CompileCodec(device_t *device, cl_program *program, char *source, int *is_valid)
{
	uint64_t timer[2];
	cl_int err;
	char *buildlog = 0;
	size_t blen = 0;
	int error = -1;

	*is_valid = 0;

	LOG_PRINT("Create program\n");
	timer[0] = Timer_GetTicks();
	*program = clCreateProgramWithSource(device->cl_context, 1, (const char **)&source, NULL, &err);
	timer[1] = Timer_GetTicks();
	LOG_PRINT("clCreateProgramWithSource() took %.2fms\n", 1000.0f * Timer_TicksToSecondsf32(timer[1] - timer[0]));
	COND_PRINT(err, "clCreateProgramWithSource result: %i (%s)\n", err, OpenCL_ErrorString(err));
	if (err != CL_SUCCESS)
		goto FINAL_STAGE;

	ALWAYS_PRINT_NODEC("Building CL program for device \"%s\", this may take several minutes.\n", device->cl_device_info.name);
	timer[0] = Timer_GetTicks();
	err = clBuildProgram(*program, 0, NULL, OPENCL_BUILD_OPTS, NULL, NULL);
	timer[1] = Timer_GetTicks();
	ALWAYS_PRINT_NODEC("clBuildProgram() took %.2fms\n", 1000.0f * Timer_TicksToSecondsf32(timer[1] - timer[0]));
	COND_PRINT(err, "clBuildProgram result: %i (%s)\n", err, OpenCL_ErrorString(err));
	if (err)
	{
		err = clBuildProgram(*program, 0, NULL, NULL, NULL, NULL);
		ALWAYS_PRINT_NODEC("clBuildProgram() took %.2fms\n", 1000.0f * Timer_TicksToSecondsf32(timer[1] - timer[0]));
		COND_PRINT(err, "clBuildProgram result: %i (%s)\n", err, OpenCL_ErrorString(err));
	}

	if (err)
	{
		err = clGetProgramBuildInfo(*program, device->cl_device_info.id, CL_PROGRAM_BUILD_LOG, 0, 0, &blen);
		if (err != CL_SUCCESS)
			goto FINAL_STAGE;
		COND_PRINT(err, "clGetProgramBuildInfo result: %i (%s)\n", err, OpenCL_ErrorString(err));
		buildlog = Mem_Malloc(blen + 1);
		err = clGetProgramBuildInfo(*program, device->cl_device_info.id, CL_PROGRAM_BUILD_LOG, blen, buildlog, 0);
		if (err != CL_SUCCESS)
			goto FINAL_STAGE;
		COND_PRINT(err, "clGetProgramBuildInfo result: %i (%s)\n", err, OpenCL_ErrorString(err));
		if (blen > 2 && g_system.opts.enable_log)
			ALWAYS_PRINT("Build log:\n==========\nLength: %i\n\n%s\n", (int)blen, buildlog);
		goto FINAL_STAGE;
	}

	error = 0;
	*is_valid = 1;

FINAL_STAGE:

	return error;
}

int CL_LoadBinaryCodec(device_t *device, cl_program *program, char *data, size_t data_len)
{
	uint64_t timer[2];
	cl_int err;
	char *buildlog = 0;
	size_t blen = 0;

	timer[0] = Timer_GetTicks();
	cl_int binary_status;
	*program = clCreateProgramWithBinary(device->cl_context, 1, &device->cl_device_info.id, &data_len, (const unsigned char**)&data, &binary_status, &err);
	timer[1] = Timer_GetTicks();
	LOG_PRINT("clCreateProgramWithBinary() took %.2fms\n", 1000.0f * Timer_TicksToSecondsf32(timer[1] - timer[0]));
	COND_PRINT(err, "clCreateProgramWithBinary result: %i (%s)\n", err, OpenCL_ErrorString(err));
	if (err != CL_SUCCESS)
		return -1;

	LOG_PRINT("Building CL program for device \"%s\"\n", device->cl_device_info.name);
	timer[0] = Timer_GetTicks();
	err = clBuildProgram(*program, 0, NULL, OPENCL_BUILD_OPTS, NULL, NULL);
	timer[1] = Timer_GetTicks();
	LOG_PRINT("clBuildProgram() took %.2fms\n", 1000.0f * Timer_TicksToSecondsf32(timer[1] - timer[0]));
	COND_PRINT(err, "clBuildProgram result: %i (%s)\n", err, OpenCL_ErrorString(err));

	if (err)
	{
		err = clBuildProgram(*program, 0, NULL, NULL, NULL, NULL);
		LOG_PRINT("clBuildProgram() took %.2fms\n", 1000.0f * Timer_TicksToSecondsf32(timer[1] - timer[0]));
		COND_PRINT(err, "clBuildProgram result: %i (%s)\n", err, OpenCL_ErrorString(err));
	}

	if (err != CL_SUCCESS)
		return -1;

	if (err || g_system.opts.enable_log)
	{
		clGetProgramBuildInfo(*program, device->cl_device_info.id, CL_PROGRAM_BUILD_LOG, 0, 0, &blen);
		buildlog = Mem_Malloc(blen + 1);
		if (!buildlog)
		{
			ALWAYS_PRINT("malloc failure\n");
			return -1;
		}
		clGetProgramBuildInfo(*program, device->cl_device_info.id, CL_PROGRAM_BUILD_LOG, blen, buildlog, 0);
		if (blen > 2)
			ALWAYS_PRINT("Build log:\n==========\nLength: %i\n\n%s\n", (int)blen, buildlog);
		Mem_Free(buildlog);
		if (err != CL_SUCCESS)
			return -1;
	}
	return 0;
}



int CL_Encode(device_t *device, image_t *image, codec_e codec, int mip_level, int override_macro_size, uint64_t *kernel_ticks, uint64_t *total_ticks, void *context)
{
	codec_options_generic_t *options = (codec_options_generic_t*)context;
	int blocks_x;
	int blocks_y;
	cl_int err = CL_SUCCESS;
	int macroblock_size;
	int chunks_x;
	int chunks_y;
	int x;
	int y;
	float *input_block = 0;
	uint8_t *output_block = 0;
	size_t output_block_bytes;
	size_t input_block_bytes;
	uint64_t t[2][2];
	int largest_dimension;

	if (kernel_ticks)
		*kernel_ticks = 0;
	if (total_ticks)
		*total_ticks = 0;

	if (override_macro_size)
		macroblock_size = override_macro_size;
	else
		macroblock_size = device->codec[codec].macroblock_size[options->quality];

	blocks_x = (image->src_width[mip_level] + 3) >> 2;
	blocks_y = (image->src_height[mip_level] + 3) >> 2;
	
	if (blocks_x >= blocks_y)
		largest_dimension = blocks_x;
	else
		largest_dimension = blocks_y;

	if (largest_dimension < macroblock_size)
		macroblock_size = Math_CeilPow2u32(largest_dimension);

	input_block_bytes = Image_GetRequiredBytes(macroblock_size * 4, macroblock_size * 4, CODEC_RGBA32F);
	output_block_bytes = Image_GetRequiredBytes(macroblock_size * 4, macroblock_size * 4, codec);

	if (output_block_bytes > device->cl_mem_out_size)
	{
		device->cl_mem_out_size = output_block_bytes;
		device->cl_mem_out = clCreateBuffer(device->cl_context, CL_MEM_WRITE_ONLY, output_block_bytes, NULL, &err);
		COND_PRINT(err, "clCreateBuffer WRITE result: %i on %I64i bytes (%s) 0x%016"PRIX64"\n", err, output_block_bytes, OpenCL_ErrorString(err), (uint64_t)device->cl_mem_out);
		if (err)
		{
			device->cl_mem_out_size = 0;
			goto ENCODE_CLEANUP;
		}
	}
	if (input_block_bytes > device->cl_mem_in_size)
	{
		device->cl_mem_in_size = input_block_bytes;
		device->cl_mem_in = clCreateBuffer(device->cl_context, CL_MEM_READ_ONLY, input_block_bytes, NULL, &err);
		COND_PRINT(err, "clCreateBuffer READ result: %i on %I64i bytes (%s) 0x%016"PRIX64"\n", err, input_block_bytes, OpenCL_ErrorString(err), (uint64_t)device->cl_mem_in);
		if (err)
		{
			device->cl_mem_in_size = 0;
			goto ENCODE_CLEANUP;
		}
	}

	chunks_x = (blocks_x + macroblock_size - 1) / macroblock_size;
	chunks_y = (blocks_y + macroblock_size - 1) / macroblock_size;

	LOG_PRINT("Encoding %i x %i chunks of size %i x %i\n", chunks_x, chunks_y, macroblock_size * 4, macroblock_size * 4);

	//LOG_PRINT("Encoding %i x %i chunks\n", chunks_x, chunks_y);

	input_block = Mem_Malloc(input_block_bytes);
	output_block = Mem_Malloc(output_block_bytes);

	t[0][0] = Timer_GetTicks();
	for (y = 0; y < chunks_y; y++)
		for (x = 0; x < chunks_x; x++)
		{
			size_t local[2];
			size_t global[2];
			int local_width = image->src_width[mip_level] - x * macroblock_size * 4 < macroblock_size * 4 ? image->src_width[mip_level] - x * macroblock_size * 4 : macroblock_size * 4;
			int local_height = image->src_height[mip_level] - y * macroblock_size * 4 < macroblock_size * 4 ? image->src_height[mip_level] - y * macroblock_size * 4 : macroblock_size * 4;

			local[0] = device->codec[codec].local_group_size < macroblock_size ? device->codec[codec].local_group_size : macroblock_size;
			local[1] = device->codec[codec].local_group_size < macroblock_size ? device->codec[codec].local_group_size : macroblock_size;

			global[0] = macroblock_size;
			global[1] = macroblock_size;

			Image_ExtractSubImageRGBAf32(input_block, image, mip_level, local_width, local_height, x * macroblock_size * 4, y * macroblock_size * 4);

			err = clEnqueueWriteBuffer(device->cl_queue, device->cl_mem_in, CL_TRUE, 0, input_block_bytes, input_block, 0, NULL, NULL);
			COND_ERR_PRINT(err, "clEnqueueWriteBuffer result on %I64i bytes: %i (%s)\n", input_block_bytes, err, OpenCL_ErrorString(err));
			if (err)
				goto ENCODE_CLEANUP;

			err = device->device_group->cl_set_kernel_args_fp[Codec_GroupFromCodec(codec)](device, image, codec, mip_level, macroblock_size, x, y, local_width, local_height, context);
			COND_ERR_PRINT(err, "clSetKernelArgs result: %i (%s)\n", err, OpenCL_ErrorString(err));
			if (err)
				goto ENCODE_CLEANUP;

			t[1][0] = Timer_GetTicks();
			err = clEnqueueNDRangeKernel(device->cl_queue, device->codec[codec].cl_kernel, 2, NULL, global, local, 0, NULL, NULL);
			COND_ERR_PRINT(err, "clEnqueueNDRangeKernel result: %i (%s)\n", err, OpenCL_ErrorString(err));
			if (err)
				goto ENCODE_CLEANUP;
			err = clFinish(device->cl_queue);
			COND_ERR_PRINT(err, "clFinish result on chunk (%5i, %5i): %i (%s)\n", x, y, err, OpenCL_ErrorString(err));
			if (err)
				goto ENCODE_CLEANUP;
			t[1][1] = Timer_GetTicks();

			if (kernel_ticks)
				*kernel_ticks += t[1][1] - t[1][0];

			err = clEnqueueReadBuffer(device->cl_queue, device->cl_mem_out, CL_TRUE, 0, output_block_bytes, output_block, 0, NULL, NULL);
			COND_ERR_PRINT(err, "clEnqueueReadBuffer result on %I64i bytes: %i (%s)\n", output_block_bytes, err, OpenCL_ErrorString(err));
			if (err)
				goto ENCODE_CLEANUP;

			err = clFinish(device->cl_queue);
			COND_ERR_PRINT(err, "clFinish result on chunk (%5i, %5i): %i (%s)\n", x, y, err, OpenCL_ErrorString(err));
			if (err)
				goto ENCODE_CLEANUP;

			Image_CopyEncodedToImage(image, output_block, mip_level, local_width, local_height, x * macroblock_size * 4, y * macroblock_size * 4);
			System_AddProgress(1, 1);
		}
	t[0][1] = Timer_GetTicks();

	if (total_ticks)
		*total_ticks = t[0][1] - t[0][0];

ENCODE_CLEANUP:

	Mem_Free(input_block);
	Mem_Free(output_block);

	if (err)
		return -1;

	return 0;
}