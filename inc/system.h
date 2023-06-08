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
#define BINARY_VERSION_STRING		"version 1.87" OPENCL_VERSION_SUFFIX
#define BINARY_VERSION_STRING_BCN	"version 1.07" OPENCL_VERSION_SUFFIX
#define BINARY_VERSION_STRING_ETC	"version 1.87" OPENCL_VERSION_SUFFIX
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
	MODE_BC1_RGB,
	MODE_BC1_RGBA,
	MODE_BC2_RGBA,
	MODE_BC3_RGBA,
	MODE_BC4_RED,
	MODE_BC5_RG,
	MODE_ETC1,
	MODE_ETC2_RGB,
	MODE_ETC2_RGBA1,
	MODE_ETC2_RGBA8,
}etc_mode_e;

typedef enum
{
	MACRO_INPUT_FOLDER,
	MACRO_OUTPUT_FOLDER,
	MACRO_INPUT_NAME,
	MACRO_INPUT_EXT,
	MACRO_OUTPUT_EXT,
	MACRO_NUM_CONTEXT,
}macro_context_e;

typedef enum
{
	APP_MAIN_WINDOW,
	APP_INPUT_FILE,
	APP_OUTPUT_FOLDER,
	APP_DEVICE_TEXT,
	APP_DEVICE,
	APP_QUALITY_TEXT,
	APP_QUALITY,
	APP_OUTPUT_BC1RGB_TEXT,
	APP_OUTPUT_BC1RGB_SRGB,
	APP_OUTPUT_BC1RGB_SAVEKTX,
	APP_OUTPUT_BC1RGB_MACROS,
	APP_OUTPUT_BC1RGB,
	APP_OUTPUT_BC1RGBA_TEXT,
	APP_OUTPUT_BC1RGBA_SRGB,
	APP_OUTPUT_BC1RGBA_SAVEKTX,
	APP_OUTPUT_BC1RGBA_SAVEDDS,
	APP_OUTPUT_BC1RGBA_MACROS,
	APP_OUTPUT_BC1RGBA,
	APP_OUTPUT_BC2RGBA_TEXT,
	APP_OUTPUT_BC2RGBA_SRGB,
	APP_OUTPUT_BC2RGBA_SAVEKTX,
	APP_OUTPUT_BC2RGBA_SAVEDDS,
	APP_OUTPUT_BC2RGBA_MACROS,
	APP_OUTPUT_BC2RGBA,
	APP_OUTPUT_BC3RGBA_TEXT,
	APP_OUTPUT_BC3RGBA_SRGB,
	APP_OUTPUT_BC3RGBA_SAVEKTX,
	APP_OUTPUT_BC3RGBA_SAVEDDS,
	APP_OUTPUT_BC3RGBA_MACROS,
	APP_OUTPUT_BC3RGBA,
	APP_OUTPUT_BC4RED_TEXT,
	APP_OUTPUT_BC4RED_SAVEKTX,
	APP_OUTPUT_BC4RED_SAVEDDS,
	APP_OUTPUT_BC4RED_MACROS,
	APP_OUTPUT_BC4RED,
	APP_OUTPUT_BC5RG_TEXT,
	APP_OUTPUT_BC5RG_SAVEKTX,
	APP_OUTPUT_BC5RG_SAVEDDS,
	APP_OUTPUT_BC5RG_MACROS,
	APP_OUTPUT_BC5RG,
	APP_OUTPUT_ETC1RGB_TEXT,
	APP_OUTPUT_ETC1RGB_SAVEKTX,
	APP_OUTPUT_ETC1RGB_MACROS,
	APP_OUTPUT_ETC1RGB,
	APP_OUTPUT_ETC2RGB_TEXT,
	APP_OUTPUT_ETC2RGB_SRGB,
	APP_OUTPUT_ETC2RGB_SAVEKTX,
	APP_OUTPUT_ETC2RGB_MACROS,
	APP_OUTPUT_ETC2RGB,
	APP_OUTPUT_ETC2RGBA1_TEXT,
	APP_OUTPUT_ETC2RGBA1_SRGB,
	APP_OUTPUT_ETC2RGBA1_SAVEKTX,
	APP_OUTPUT_ETC2RGBA1_MACROS,
	APP_OUTPUT_ETC2RGBA1,
	APP_OUTPUT_ETC2RGBA8_TEXT,
	APP_OUTPUT_ETC2RGBA8_SRGB,
	APP_OUTPUT_ETC2RGBA8_SAVEKTX,
	APP_OUTPUT_ETC2RGBA8_MACROS,
	APP_OUTPUT_ETC2RGBA8,
	APP_ENCODE,
	APP_CANCEL,
	APP_PROGRESS_TEXT,
	APP_PROGRESS_BAR,
	APP_OUTPUT_BC1RGB_TOOLTIP,
	APP_OUTPUT_BC1RGBA_TOOLTIP,
	APP_OUTPUT_BC2RGBA_TOOLTIP,
	APP_OUTPUT_BC3RGBA_TOOLTIP,
	APP_OUTPUT_BC4RED_TOOLTIP,
	APP_OUTPUT_BC5RG_TOOLTIP,
	APP_OUTPUT_ETC1RGB_TOOLTIP,
	APP_OUTPUT_ETC2RGB_TOOLTIP,
	APP_OUTPUT_ETC2RGBA1_TOOLTIP,
	APP_OUTPUT_ETC2RGBA8_TOOLTIP,
	APP_OUTPUT_BC1RGB_MIPMAPS,
	APP_OUTPUT_BC1RGBA_MIPMAPS,
	APP_OUTPUT_BC2RGBA_MIPMAPS,
	APP_OUTPUT_BC3RGBA_MIPMAPS,
	APP_OUTPUT_BC4RED_MIPMAPS,
	APP_OUTPUT_BC5RG_MIPMAPS,
	APP_OUTPUT_ETC1RGB_MIPMAPS,
	APP_OUTPUT_ETC2RGB_MIPMAPS,
	APP_OUTPUT_ETC2RGBA1_MIPMAPS,
	APP_OUTPUT_ETC2RGBA8_MIPMAPS,
	APP_NUM
}window_id_e;

typedef enum
{
	APP_GROUP_BC1RGB,
	APP_GROUP_BC1RGBA,
	APP_GROUP_BC2RGBA,
	APP_GROUP_BC3RGBA,
	APP_GROUP_BC4RED,
	APP_GROUP_BC5RG,
	APP_GROUP_ETC1RGB,
	APP_GROUP_ETC2RGB,
	APP_GROUP_ETC2RGBA1,
	APP_GROUP_ETC2RGBA8,
	APP_GROUP_NUM
}window_group_id_e;

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

typedef struct gui_element_s
{
	wchar_t						*classname;
	wchar_t						*text;
	int							shorten_text;
	int							win_style;
	int							win_ex_style;
	int							x;
	int							y;
	int							width;
	int							height;
	struct gui_element_s		*parent_p;
	HWND						hwnd;
}gui_element_t;

typedef struct win_group_encode_options_s
{
	int		srgb;
	int		save_ktx;
	int		save_dds;
	int		output_path_control_id;
}win_group_encode_options_t;

typedef struct window_interface_s
{
	int							is_gui;
	int							progress;
	int							*device_index_map_from_cb;
	int							num_cl_devices;
	struct device_group_s		*device_group;
	gui_element_t				*gui_element;
	int							num_gui_element;
	char						**input_file;
	char						*input_path;
	int							num_input_files;
	char						*output_folder;
	int							device;
	int							quality;
	win_group_encode_options_t	encode_options[APP_GROUP_NUM];
	int							encoding;
	HANDLE						worker_thread_h;
	unsigned int				worker_thread_id;
	int							pending_cancel;
}window_interface_t;

extern system_t g_system;
extern window_interface_t g_win_system;

BOOL System_GetBIOSUUID(unsigned char *uuid);
int System_CodecToGLFormat(int codec, int is_srgb);
void System_StartProgressThread(int is_encode_progrss, int total_iterations);
void System_EndProgressThread();
void System_AddProgress(int is_encode_progress, int iterations);
int System_ParseOptions(int argc, char **argv);
void System_UpdateGUIProgressBar(double x);
char *System_ModeToString(int encode_mode);
int System_ModeToCodecID(int mode);