typedef struct cl_instance_s
{
	cl_context			context;
	cl_command_queue	queue;
}cl_instance_t;

typedef struct cl_program_data_s
{
	int			num_kernels;
	cl_program	program;
	cl_kernel	kernel[32];
	int			local_group_size[32];
}cl_program_data_t;


int CL_InitETCGPUCodec(int load_full, int device_index, int print);
void CL_DestroyETCGPUCodec();
int CL_EncodeETCGPU(
	uint8_t **block, 
	float *pixel4x4_rgba, 
	int width, 
	int height, 
	int is_ypbpr,
	int is_etc2, 
	int is_alpha, 
	int is_punchthrough,
	float alpha_cutoff,
	float rgb_error_target,
	float alpha_error_target);
int CL_TestEncodeETCGPU(char *type, cl_device_info_t *device_info, int is_etc2, int is_alpha, int turbo, int *best_macroblock_size, float *estimated_pixels_per_second);
int CL_FindBestDevice();

char *OpenCL_ErrorString(int error);
char *CL_DeviceTypeToString(cl_device_type type);
wchar_t *CL_GetBinaryPathString(char *device_name, char *suffix);
wchar_t *CL_GetBinaryPath(int device_index, char *suffix);
int CL_DeviceCVersion(cl_device_info_t *device_info, int *major_version, int *minor_version);
int CL_DeviceCLVersion(cl_device_info_t *device_info, int *major_version, int *minor_version);
void CL_FreeDeviceInfo(cl_device_info_t *device_info);
void CL_PrintDeviceInfo(cl_device_info_t *device_info, int prefix);
int CL_EnumDevices(cl_platform_id platform, cl_device_type device_hw_type, cl_device_info_t **device_info);
int CL_InitState(cl_device_info_t **device_info);
int CL_CreateContextAndQueue(cl_instance_t *instance, cl_device_info_t *device_info);
int CL_ListCLDevices(int print);

int CL_CreateContextAndQueueDirect(cl_context *cl_context, cl_command_queue *cl_queue, cl_device_info_t *device_info);
int CL_CompileCodec(device_t *device, cl_program *program, char *source, int *is_valid);
int CL_LoadBinaryCodec(device_t *device, cl_program *program, char *data, size_t data_len);
int CL_Encode(device_t *device, image_t *image, codec_e codec, int mip_level, int override_macro_size, uint64_t *kernel_ticks, uint64_t *total_ticks, void *context);

void CL_ETC_Init(device_group_t *device_group);

char *BCN_QualityAsString(int quality);