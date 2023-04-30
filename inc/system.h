//#define OPENCL_DEBUG
//#define OPENCL_SKIP_RATE_TEST
//#define TRACK_OPENCL_RANGE

//#define USE_RGBCX_ENCODER
#define RGBCX_QUALITY_VALUE		18

#define DUMP_RAW_IMAGE	0

#define USE_OPENMP					1

#ifdef OPENCL_DEBUG
#define OPENCL_VERSION_SUFFIX		"NOOPT"
#define OPENCL_BUILD_OPTS			"-cl-opt-disable"
#else
#define OPENCL_VERSION_SUFFIX		""
#define OPENCL_BUILD_OPTS			"-cl-mad-enable -cl-unsafe-math-optimizations -cl-fast-relaxed-math"
//#define OPENCL_BUILD_OPTS			NULL
#endif

#ifdef ETC_TEST_SINGLE_MACROBLOCK_EXTENSIVE
#define TEST_OPENCL_ONLY			1
#define TRACK_OPENCL_TEST_PRINTS	1
#define BINARY_VERSION_STRING		"version 0.0 DEBUG"
#define BINARY_VERSION_STRING_BCN	"version 0.0 DEBUG"
#define BINARY_VERSION_STRING_ETC	"version 0.0 DEBUG"
#else
#define TEST_OPENCL_ONLY			0
#define TRACK_OPENCL_TEST_PRINTS	0
#define BINARY_VERSION_STRING		"version 1.86" OPENCL_VERSION_SUFFIX
#define BINARY_VERSION_STRING_BCN	"version 1.04" OPENCL_VERSION_SUFFIX
#define BINARY_VERSION_STRING_ETC	"version 1.86" OPENCL_VERSION_SUFFIX
#endif
#define TEST_PRINT_SOURCE			0

#define ETC_ALLOWED_MODES			(ETC_MODE_ANY)
//#define ETC_ALLOWED_MODES			((ETC_MODE_NODELTA | ETC_MODE_DELTA | ETC_MODE_PLANAR))

//#define ETC_ALLOWED_MODES			(ETC_MODE_ANY & (~ETC_MODE_NODELTA))
//#define ETC_ALLOWED_MODES			(ETC_MODE_ANY & (~(ETC_MODE_NODELTA | ETC_MODE_DELTA | ETC_MODE_T)))

//#define ETC_TEST_H

#ifdef ETC_TEST_DELTANODELTA
#undef ETC_ALLOWED_MODES
#define ETC_ALLOWED_MODES			(ETC_MODE_ETC1)
#endif
#ifdef ETC_TEST_T
#undef ETC_ALLOWED_MODES
#define ETC_ALLOWED_MODES			(ETC_MODE_T)
#endif
#ifdef ETC_TEST_H
#undef ETC_ALLOWED_MODES
#define ETC_ALLOWED_MODES			(ETC_MODE_H)
#endif
#ifdef ETC_TEST_PLANAR
#undef ETC_ALLOWED_MODES
#define ETC_ALLOWED_MODES			(ETC_MODE_PLANAR)
#endif







#define ETC_MODE_DELTA      1
#define ETC_MODE_NODELTA    2
#define ETC_MODE_T          4
#define ETC_MODE_H          8
#define ETC_MODE_PLANAR     16

#define ETC_MODE_ANY		(ETC_MODE_DELTA | ETC_MODE_NODELTA | ETC_MODE_T | ETC_MODE_H | ETC_MODE_PLANAR)
#define ETC_MODE_ETC1		(ETC_MODE_DELTA | ETC_MODE_NODELTA)
#define ETC_MODE_ETC2RGBA1	(ETC_MODE_DELTA | ETC_MODE_T | ETC_MODE_H | ETC_MODE_PLANAR)

// print if log
#define LOG_PRINT(...)		do { if (g_system.opts.enable_log) {printf("%.2fms:%s():%i: ", 1000.0 * Timer_TicksToSecondsf64(Timer_GetTicks() - g_system.info.time_start), __FUNCTION__, __LINE__); printf(__VA_ARGS__);} }while(0)

// always print
#define ALWAYS_PRINT(...)	do { printf("%.2fms:%s():%i: ", 1000.0 * Timer_TicksToSecondsf64(Timer_GetTicks() - g_system.info.time_start), __FUNCTION__, __LINE__); printf(__VA_ARGS__); }while(0)

// always print as raw printf
#define ALWAYS_PRINT_NODEC(...)	do { printf(__VA_ARGS__); }while(0)

// conditional print / print if log enabled
#define COND_PRINT(condition, ...)	do { if ((condition) || g_system.opts.enable_log) {printf("%.2fms:%s():%i: ", 1000.0 * Timer_TicksToSecondsf64(Timer_GetTicks() - g_system.info.time_start), __FUNCTION__, __LINE__); printf(__VA_ARGS__);} }while(0)

// conditional print
#define COND_ERR_PRINT(condition, ...)	do { if (condition) {printf("%.2fms:%s():%i: ", 1000.0 * Timer_TicksToSecondsf64(Timer_GetTicks() - g_system.info.time_start), __FUNCTION__, __LINE__); printf(__VA_ARGS__);} }while(0)

typedef enum
{
	MODE_INVALID,
	MODE_ETC1,
	MODE_ETC2_RGB,
	MODE_ETC2_RGBA1,
	MODE_ETC2_RGBA8,
	MODE_BC1_RGB,
	MODE_BC1_RGBA,
	MODE_BC2_RGBA,
	MODE_BC3_RGBA,
	MODE_BC4_RED,
	MODE_BC5_RG,
}etc_mode_e;

typedef struct sys_opts_s
{
	int		enable_log;
	int		enable_mipmap;
	int		output_mode;
	int		is_ypbpr;
	char	*in_filename;
	char	*out_filename;
	char	*out_filename_dds;
	float	alpha_cutoff;
	float	colour_error_target;
	float	alpha_error_target;
	int		encode_mode;
	int		cl_device;
	int		srgb;
	int		cl_macroblock_size;
	int		force_cpu;
	int		override_macroblock;
	int		turbo;
	int		save_ktx;
	int		save_dds;
	int		dds_quality;
}sys_opts_t;

typedef struct sys_image_s
{
	int		width;
	int		height;
	float	*rgba;
	uint8_t	*encoded;
}sys_image_t;
typedef struct sys_info_s
{
	uint64_t	time_start;
}sys_info_t;
typedef struct system_s
{
	sys_opts_t		opts;
	sys_info_t		info;
	sys_image_t		*image;
	int				num_mipmap_levels;
	volatile int	progress_complete;
	volatile int	is_running;
	int				total_blocks;
	volatile int	current_block;
	uintptr_t		progress_thread_h;
	unsigned int	progress_thread_id;
	int				is_encode_progress;
}system_t;

extern system_t g_system;

BOOL System_GetBIOSUUID(unsigned char *uuid);
int System_CodecToGLFormat(int codec, int is_srgb);
void System_StartProgressThread(int is_encode_progrss, int total_iterations);
void System_EndProgressThread();
void System_AddProgress(int is_encode_progress, int iterations);