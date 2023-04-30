#define BCN_ENCODE_BC1_KERNEL_INDEX	0
#define BCN_ENCODE_BC2_KERNEL_INDEX	1
#define BCN_ENCODE_BC3_KERNEL_INDEX	2
#define BCN_ENCODE_BC4_KERNEL_INDEX	3
#define BCN_ENCODE_BC5_KERNEL_INDEX	4

int CL_InitBCNGPUCodec(int load_full, int device_index, int print);
int CL_FindBestBCNDevice(int mode);
int CL_EncodeBCNGPU(
	int options,
	int mode,
	uint8_t **block,
	float *pixel_rgba,
	int width, 
	int height,
	uint8_t alpha_cutoff,
	float *execution_time_kernel,
	int override_macro_size,
	float *execution_time_total);
void CL_GetBCNPixelRate(int options, int mode, float *lower_expected, float *upper_expected);
int CL_GetBCNMacroBlockSize(int options, int mode);
void CL_DestroyBCNGPUCodec();
int CL_InitBCNGPUCodec(int load_full, int device_index, int print);
void CL_BCN_Init(device_group_t *device_group);

int BCN_QualityToQualityBitfield(int quality);