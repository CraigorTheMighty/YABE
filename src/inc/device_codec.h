#define DEVICE_SOFTWARE	0
#define DEVICE_CL_START	1

#define CODEC_BCN_QUALITY_OPTIONS_WALK_PATH            (1 << 0)    // expensive
#define CODEC_BCN_QUALITY_OPTIONS_EXTEND_ENDPOINTS     (1 << 1)    // only valid with CODEC_BCN_QUALITY_WALK_PATH, potentially very expensive
#define CODEC_BCN_QUALITY_OPTIONS_REFINE_ENDPOINTS     (1 << 2)
#define CODEC_BCN_QUALITY_OPTIONS_TEST 			       (1 << 15)

#define CODEC_BCN_QUALITY_FAST_BITFIELD       (0) // this will always be faster than "normal"
#define CODEC_BCN_QUALITY_NORMAL_BITFIELD     (CODEC_BCN_QUALITY_OPTIONS_WALK_PATH) // this will always be faster than "high"
#define CODEC_BCN_QUALITY_HIGH_BITFIELD       (CODEC_BCN_QUALITY_OPTIONS_WALK_PATH | CODEC_BCN_QUALITY_OPTIONS_REFINE_ENDPOINTS)    // for images that are random noise, this mode tends to degenerate into "best"
#define CODEC_BCN_QUALITY_BEST_BITFIELD       (CODEC_BCN_QUALITY_OPTIONS_WALK_PATH | CODEC_BCN_QUALITY_OPTIONS_EXTEND_ENDPOINTS | CODEC_BCN_QUALITY_OPTIONS_REFINE_ENDPOINTS)

#define CODEC_QUALITY_FAST                    (0) // this will always be faster than "normal"
#define CODEC_QUALITY_NORMAL                  (1) // this will always be faster than "high"
#define CODEC_QUALITY_HIGH                    (2) // for images that are random noise, this mode tends to degenerate into "best"
#define CODEC_QUALITY_BEST                    (3)

#define CODEC_BCN_QUALITY_TEST                (CODEC_BCN_QUALITY_OPTIONS_WALK_PATH | CODEC_BCN_QUALITY_OPTIONS_EXTEND_ENDPOINTS | CODEC_BCN_QUALITY_OPTIONS_REFINE_ENDPOINTS | CODEC_BCN_QUALITY_OPTIONS_TEST)

typedef enum
{
	CODEC_ETC1,
	CODEC_ETC2_RGB,
	CODEC_ETC2_RGBA1,
	CODEC_ETC2_RGBA8,

	CODEC_BC1_RGB,
	CODEC_BC1_RGBA,
	CODEC_BC2_RGBA,
	CODEC_BC3_RGBA,
	CODEC_BC4_RED,
	CODEC_BC5_RG,

	CODEC_NUM_CODECS,

	CODEC_RGBA32F
}codec_e;

typedef enum
{
	CODEC_GROUP_ETC,
	CODEC_GROUP_BCN,
	CODEC_GROUP_NUM_GROUPS
}codec_group_e;

typedef struct cl_device_info_s
{
	cl_device_id id;

	cl_device_type type;
	cl_uint max_work_group_size;
	cl_uint max_compute_units;
	cl_uint max_clock_frequency;
	BOOL available;
	BOOL compiler_available;
	BOOL linker_available;
	cl_device_exec_capabilities execution_capabilities;
	cl_platform_id platform;
	cl_ulong memory;
	char *name;
	char *vendor;
	char *version;
	char *profile;
	char *opencl_c_version;
	char *extensions;
	char *driver_version;
}cl_device_info_t;

typedef struct codec_s
{
	int					num_modes;			// e.g. fast, normal, high, etc

	double				*pixels_per_second;
	int					*macroblock_size;

	struct device_s		*device;			// pointer to parent struct
	cl_program			*cl_program;		// pointer to parent program

	cl_kernel			cl_kernel;
	int					local_group_size;
}codec_t;

typedef struct device_s
{
	struct device_group_s	*device_group;
	int						is_opencl;
	int						cl_index;
	int						is_valid;
	int						is_context_and_queue_valid;
	codec_t					codec[CODEC_NUM_CODECS];

	cl_program				cl_program[CODEC_GROUP_NUM_GROUPS];
	cl_context				cl_context;
	cl_command_queue		cl_queue;
	size_t					cl_mem_in_size;
	cl_mem					cl_mem_in;
	size_t					cl_mem_out_size;
	cl_mem					cl_mem_out;

	cl_device_info_t		cl_device_info;
}device_t;

typedef struct device_group_s
{
	int				num_devices;
	device_t		*device;
	char			*cl_source[CODEC_GROUP_NUM_GROUPS];
	char			**cl_kernel_function[CODEC_GROUP_NUM_GROUPS];
	char			*binary_version_string[CODEC_GROUP_NUM_GROUPS];
	int				num_modes[CODEC_GROUP_NUM_GROUPS];

	int				(*cl_test_codec_group_fp[CODEC_GROUP_NUM_GROUPS])(device_t *device);

	int				(*cl_set_kernel_args_fp[CODEC_GROUP_NUM_GROUPS])(device_t *device, image_t *image, codec_e codec, int mip_level, int macro_size, int macro_block_src_x, int macro_block_src_y, int width, int height, void *context);

}device_group_t;

typedef struct codec_options_common_s
{
	int		is_ypbpr;
	int		is_srgb;
	int		alpha_cutoff;
	int		quality;
}codec_options_common_t;

typedef struct codec_options_etc_s
{
	codec_options_common_t	common;
	float					colour_error;
	float					alpha_error;

}codec_options_etc_t;

typedef struct codec_options_bcn_s
{
	codec_options_common_t	common;
	int						is_test;
	int						output_dds;
	int						output_ktx;
}codec_options_bcn_t;

typedef struct codec_options_generic_s
{
	int		is_ypbpr;
	int		is_srgb;
	int		alpha_cutoff;
	int		quality;
}codec_options_generic_t;


int Codec_SaveCodecGroupData(device_t *device, codec_group_e codec_group);
char *Codec_AsString(codec_e codec);
void Codec_Init(codec_t *codec, int num_modes);
int Codec_Create(codec_t *codec, char *function);
void Codec_Destroy(codec_t *codec);
void Codec_DestroyGroup(device_t *device, codec_group_e group);
int Codec_Encode(device_group_t *device_group, int device_index, image_t *image, codec_e codec, int mip_level, int override_macro_size, uint64_t *kernel_ticks, uint64_t *total_ticks, void *context);
int Codec_Decode(device_group_t *device_group, int device_index, image_t *image, codec_e codec, int mip_level, int override_macro_size, uint64_t *kernel_ticks, uint64_t *total_ticks, void *context);
int Codec_LoadGroup(device_group_t *device_group, int device_index, codec_group_e group_index);
int Codec_InspectGroup(device_group_t *device_group, int device_index, codec_group_e group_index);
void Codec_DeInspectGroup(device_t *device, codec_group_e group);
int Codec_SaveGroup(device_group_t *device_group, int device_index, codec_group_e group_index);
int Codec_GroupFromCodec(codec_e codec);

void Device_Destroy(device_t *device);
int Device_DeviceIndexFromDevice(device_t *device);

device_group_t *DeviceGroup_New();
void DeviceGroup_Destroy(device_group_t *device_group);
int Codec_GetEncodeChunks(device_group_t *device_group, int device_index, image_t *image, codec_e codec, int mip_level, int override_macro_size, void *context);
double Codec_GetPerformance(device_group_t *device_group, int device_index, codec_e codec, void *context);