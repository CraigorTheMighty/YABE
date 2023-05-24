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

#define ETC_EPILOG		"void ETC_EncodeETC4x4(\n"\
"    int allowed_modes,                              // bitfield of allowed modes for encoder, mostly for debugging. see MODE preprocessor definitions. suggested default: ETC_MODE_ANY. should never be set to \"ETC_MODE_DELTA\" only.\n"\
"    float alpha_cutoff,                             // valid range 0 - 255, used in RGBA1 mode. (x <= cutoff) = transparent pixel.\n"\
"    float rgb_error_target,                 // MSE error target for colour channels. 0 for max quality, 256 for approximately PVRTexTool \"slow\" quality. high performance impact for lower values. suggested default: 0\n"\
"    float alpha_error_target,               // MSE error target for alpha in RGBA8 mode. 0 for max quality. moderate performance impact. suggested default: 0\n"\
"    int is_ypbpr,                                   // measure MSE in YPbPr space instead of RGB space? moderate performance impact if enabled\n"\
"    int is_etc2,                                    // is ETC1 or ETC2?\n"\
"    int is_alpha,                                   // has an alpha channel?\n"\
"    int is_punchthrough,                    // is alpha channel 1-bit?\n"\
"    int refine_rgb_search,                  // search for best minimum in local neighbourhood to improve quality for RGB. high performance impact. suggested default: 0\n"\
"    int refine_alpha_search,                // search for better \"base alpha\" instead of using simple estimate. moderate performance impact. suggested default: 1\n"\
"    int alpha_search_radius,                // valid range 0 - 7. search radius for better alpha multiplier. moderate performance impact. suggested default: 1\n"\
"    int width,                                              // image width in pixels\n"\
"    int height,                                             // image height in pixels\n"\
"    __global float *pixel_rgba,             // pixel RGBA in R, G, B, A order, (width x height) entries\n"\
"    __global uchar *block,                  // output data\n"\
"    int fast_mode)                          // low-quality, high-speed\n"\
"{\n"\
"    float4 pixel[16];\n"\
"    float weight[16];\n"\
"    int block_x = get_global_id(0);\n"\
"    int block_y = get_global_id(1);\n"\
"    int i;\n"\
"    int j;\n"\
"    int line_out_blocks = (width + 3) >> 2;\n"\
"\n"\
"        for (i = 0; i < 16; i++)\n"\
"            weight[i] = 1.0f;\n"\
"    for (i = 0; i < 4; i++)\n"\
"        for (j = 0; j < 4; j++)\n"\
"        {\n"\
"            pixel[(i*4 + j)MEMBER(], X) = pixel_rgba[((i + block_y*4)*width + (j + block_x*4))*4 + 0];\n"\
"            pixel[(i*4 + j)MEMBER(], Y) = pixel_rgba[((i + block_y*4)*width + (j + block_x*4))*4 + 1];\n"\
"            pixel[(i*4 + j)MEMBER(], Z) = pixel_rgba[((i + block_y*4)*width + (j + block_x*4))*4 + 2];\n"\
"            pixel[(i*4 + j)MEMBER(], W) = pixel_rgba[((i + block_y*4)*width + (j + block_x*4))*4 + 3];\n"\
"\n"\
"        }\n"\
"\n"\
"        if (is_alpha && is_etc2)\n"\
"        {\n"\
"            if (!is_punchthrough)\n"\
"            {\n"\
"                    ETC_EncodeRGB(fast_mode, allowed_modes, rgb_error_target, refine_rgb_search, is_etc2, is_ypbpr, pixel, &block[(block_x * 8 * 2) + (block_y) * line_out_blocks * 8 * 2 + 8]);\n"\
"                    ETC_EncodeAlpha(alpha_error_target, refine_alpha_search, alpha_search_radius, pixel, &block[(block_x * 8 * 2) + (block_y) * line_out_blocks * 8 * 2 + 0]);\n"\
"            }\n"\
"            else\n"\
"            {\n"\
"                int transparent_count = 0;\n"\
"\n"\
"                for (i = 0; i < 16; i++)\n"\
"                    if (MEMBER(pixel[i], W) <= alpha_cutoff)\n"\
"                    {\n"\
"                        transparent_count++;\n"\
"                        break;\n"\
"                    }\n"\
"\n"\
"                if (transparent_count == 0)\n"\
"                    ETC_EncodeRGB(fast_mode, allowed_modes, rgb_error_target, refine_rgb_search, is_etc2, is_ypbpr, pixel, &block[(block_x * 8) + (block_y) * line_out_blocks * 8 + 0]);\n"\
"                else\n"\
"                    ETC_EncodeRGBA1Weighted(fast_mode, allowed_modes, rgb_error_target, refine_rgb_search, is_ypbpr, alpha_cutoff, pixel, weight, &block[(block_x * 8) + (block_y) * line_out_blocks * 8 + 0]);\n"\
"            }\n"\
"        }\n"\
"        else\n"\
"        {\n"\
"            ETC_EncodeRGB(fast_mode, allowed_modes, rgb_error_target, refine_rgb_search, is_etc2, is_ypbpr, pixel, &block[(block_x * 8) + (block_y) * line_out_blocks * 8 + 0]);\n"\
"        }\n"\
"}\n"\
"\n"\
"void ETC_EncodeETCN4x4(\n"\
"    int allowed_modes,                              // bitfield of allowed modes for encoder, mostly for debugging. see MODE preprocessor definitions. suggested default: ETC_MODE_ANY. should never be set to \"ETC_MODE_DELTA\" only.\n"\
"    float alpha_cutoff,                             // valid range 0 - 255, used in RGBA1 mode. (x <= cutoff) = transparent pixel.\n"\
"    float rgb_error_target,                 // MSE error target for colour channels. 0 for max quality, 256 for approximately PVRTexTool \"slow\" quality. high performance impact for lower values. suggested default: 0\n"\
"    float alpha_error_target,               // MSE error target for alpha in RGBA8 mode. 0 for max quality. moderate performance impact. suggested default: 0\n"\
"    int is_ypbpr,                                   // measure MSE in YPbPr space instead of RGB space? moderate performance impact if enabled\n"\
"    int is_etc2,                                    // is ETC1 or ETC2?\n"\
"    int is_alpha,                                   // has an alpha channel?\n"\
"    int is_punchthrough,                    // is alpha channel 1-bit?\n"\
"    int refine_rgb_search,                  // search for best minimum in local neighbourhood to improve quality for RGB. high performance impact. suggested default: 0\n"\
"    int refine_alpha_search,                // search for better \"base alpha\" instead of using simple estimate. moderate performance impact. suggested default: 1\n"\
"    int alpha_search_radius,                // valid range 0 - 7. search radius for better alpha multiplier. moderate performance impact. suggested default: 1\n"\
"    int width,                                              // image width in pixels\n"\
"    int height,                                             // image height in pixels\n"\
"    __global float *pixel_rgba,             // pixel RGBA in R, G, B, A order, (width x height) entries\n"\
"    __global uchar *block,                      // output data\n"\
"    int fast_mode)\n"\
"{\n"\
"    float4 pixel[16];\n"\
"    float weight[16];\n"\
"    int block_x = get_global_id(0);\n"\
"    int block_y = get_global_id(1);\n"\
"    int i;\n"\
"    int j;\n"\
"    int max_x;\n"\
"    int max_y;\n"\
"    int line_out_blocks = (width + 3) >> 2;\n"\
"\n"\
"    max_x = clamp(width - block_x*4, 1, 4);\n"\
"    max_y = clamp(height - block_y*4, 1, 4);\n"\
"\n"\
"    for (i = 0; i < 16; i++)\n"\
"    {\n"\
"        pixel[i] = VFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);\n"\
"        weight[i] = 0.0f;\n"\
"    }\n"\
"\n"\
"    for (i = 0; i < max_y; i++)\n"\
"        for (j = 0; j < max_x; j++)\n"\
"        {\n"\
"            MEMBER(pixel[(i*4 + j)], X) = pixel_rgba[((i + block_y*4)*width + (j + block_x*4))*4 + 0];\n"\
"            MEMBER(pixel[(i*4 + j)], Y) = pixel_rgba[((i + block_y*4)*width + (j + block_x*4))*4 + 1];\n"\
"            MEMBER(pixel[(i*4 + j)], Z) = pixel_rgba[((i + block_y*4)*width + (j + block_x*4))*4 + 2];\n"\
"            MEMBER(pixel[(i*4 + j)], W) = pixel_rgba[((i + block_y*4)*width + (j + block_x*4))*4 + 3];\n"\
"\n"\
"            weight[(i*4 + j)] = 1.0f;\n"\
"\n"\
"        }\n"\
"\n"\
"    if (is_alpha && is_etc2)\n"\
"    {\n"\
"        if (!is_punchthrough)\n"\
"        {\n"\
"            ETC_EncodeRGBWeighted(allowed_modes, rgb_error_target, refine_rgb_search, is_etc2, is_ypbpr, pixel, weight, &block[(block_x * 8 * 2) + (block_y) * line_out_blocks * 8 * 2 + 8]);\n"\
"            ETC_EncodeAlphaWeighted(alpha_error_target, refine_alpha_search, alpha_search_radius, pixel, weight, &block[(block_x * 8 * 2) + (block_y) * line_out_blocks * 8 * 2 + 0]);\n"\
"        }\n"\
"        else\n"\
"        {\n"\
"            int transparent_count = 0;\n"\
"\n"\
"            for (i = 0; i < 16; i++)\n"\
"                if (MEMBER(pixel[i], W) <= alpha_cutoff)\n"\
"                {\n"\
"                    transparent_count++;\n"\
"                    break;\n"\
"                }\n"\
"\n"\
"            if (transparent_count == 0)\n"\
"                ETC_EncodeRGBWeighted(allowed_modes, rgb_error_target, refine_rgb_search, is_etc2, is_ypbpr, pixel, weight, &block[(block_x * 8) + (block_y) * line_out_blocks * 8 + 0]);\n"\
"            else\n"\
"                ETC_EncodeRGBA1Weighted(fast_mode, allowed_modes, rgb_error_target, refine_rgb_search, is_ypbpr, alpha_cutoff, pixel, weight, &block[(block_x * 8) + (block_y) * line_out_blocks * 8 + 0]);\n"\
"        }\n"\
"    }\n"\
"    else\n"\
"    {\n"\
"        ETC_EncodeRGBWeighted(allowed_modes, rgb_error_target, refine_rgb_search, is_etc2, is_ypbpr, pixel, weight, &block[(block_x * 8) + (block_y) * line_out_blocks * 8 + 0]);\n"\
"    }\n"\
"}\n"\
"\n"\
"\n"\
"__kernel void ETC_EncodeETC(\n"\
"    int allowed_modes,                              // bitfield of allowed modes for encoder, mostly for debugging. see MODE preprocessor definitions. suggested default: ETC_MODE_ANY. should never be set to \"ETC_MODE_DELTA\" only.\n"\
"    float alpha_cutoff,                             // valid range 0 - 255, used in RGBA1 mode. (x <= cutoff) = transparent pixel.\n"\
"    float rgb_error_target,                 // MSE error target for colour channels. 0 for max quality, 256 for approximately PVRTexTool \"slow\" quality. high performance impact for lower values. suggested default: 0\n"\
"    float alpha_error_target,               // MSE error target for alpha in RGBA8 mode. 0 for max quality. moderate performance impact. suggested default: 0\n"\
"    int is_ypbpr,                                   // measure MSE in YPbPr space instead of RGB space? moderate performance impact if enabled\n"\
"    int is_etc2,                                    // is ETC1 or ETC2?\n"\
"    int is_alpha,                                   // has an alpha channel?\n"\
"    int is_punchthrough,                    // is alpha channel 1-bit?\n"\
"    int refine_rgb_search,                  // search for best minimum in local neighbourhood to improve quality for RGB. high performance impact. suggested default: 0\n"\
"    int refine_alpha_search,                // search for better \"base alpha\" instead of using simple estimate. moderate performance impact. suggested default: 1\n"\
"    int alpha_search_radius,                // valid range 0 - 7. search radius for better alpha multiplier. moderate performance impact. suggested default: 1\n"\
"    int width,                                              // image width in pixels\n"\
"    int height,                                             // image height in pixels\n"\
"    __global float *pixel_rgba,             // pixel RGBA in R, G, B, A order, (width x height) entries\n"\
"    __global uchar *block,                       // output data\n"\
"    int fast_mode)\n"\
"{\n"\
"    int block_x = get_global_id(0);\n"\
"    int block_y = get_global_id(1);\n"\
"    int max_x;\n"\
"    int max_y;\n"\
"    int is_4x4;\n"\
"        if ((block_x * 4 >= width) || (block_y * 4 >= height))\n"\
"            return;\n"\
"        if (!is_etc2)\n"\
"            allowed_modes &= ETC_MODE_ETC1;\n"\
"        else if (is_etc2 && is_alpha && is_punchthrough)\n"\
"            allowed_modes &= ETC_MODE_ETC2RGBA1;\n"\
"        else\n"\
"            allowed_modes &= ETC_MODE_ANY;\n"\
"        max_x = clamp(width - block_x*4, 1, 4);\n"\
"    max_y = clamp(height - block_y*4, 1, 4);\n"\
"        is_4x4 = (max_x + max_y == 8) ? 1 : 0;\n"\
"        if (is_4x4)\n"\
"            ETC_EncodeETC4x4(\n"\
"                allowed_modes,\n"\
"                alpha_cutoff,\n"\
"                rgb_error_target,\n"\
"                alpha_error_target,\n"\
"                is_ypbpr,\n"\
"                is_etc2,\n"\
"                is_alpha,\n"\
"                is_punchthrough,\n"\
"                refine_rgb_search,\n"\
"                refine_alpha_search,\n"\
"                alpha_search_radius,\n"\
"                width,\n"\
"                height,\n"\
"                pixel_rgba,\n"\
"                block,\n"\
"                fast_mode);\n"\
"        else\n"\
"            ETC_EncodeETCN4x4(\n"\
"                allowed_modes,\n"\
"                alpha_cutoff,\n"\
"                rgb_error_target,\n"\
"                alpha_error_target,\n"\
"                is_ypbpr,\n"\
"                is_etc2,\n"\
"                is_alpha,\n"\
"                is_punchthrough,\n"\
"                refine_rgb_search,\n"\
"                refine_alpha_search,\n"\
"                alpha_search_radius,\n"\
"                width,\n"\
"                height,\n"\
"                pixel_rgba,\n"\
"                block,\n"\
"                fast_mode);\n"\
"}\n";

#if TRACK_OPENCL_TEST_PRINTS
#define OPENCL_TEST_PRINTS	"#define DEBUG_PRINT_LINE		printf(\"%s():%i\\n\", __func__, __LINE__);\n"
#define OPENCL_TEST_PRINTF	"#define DEBUG_PRINTF(arg)		{printf(\"%s():%i: \", __func__, __LINE__);printf arg;}\n"
#else
#define OPENCL_TEST_PRINTS	"#define DEBUG_PRINT_LINE\n"
#define OPENCL_TEST_PRINTF	"#define DEBUG_PRINTF(arg)		;\n"
#endif





char *g_etc_kernel_source = \
OPENCL_TEST_PRINTS\
"\n"\
OPENCL_TEST_PRINTF\
"\n"\
"#define MEMBER2X(a)			a.x\n"\
"#define MEMBER2Y(a)			a.y\n"\
"#define MEMBER2Z(a)			a.z\n"\
"#define MEMBER2W(a)			a.w\n"\
"#define MEMBER(a, b)			MEMBER2##b(a)\n"\
"#define VFLOAT4(a, b, c, d)	(float4)((float)a, (float)b, (float)c, (float)d)\n"\
"#define VFLOAT3(a, b, c)		(float3)((float)a, (float)b, (float)c)\n"\
"#define UCHAR3(a, b, c)		(uchar3)((uchar)a, (uchar)b, (uchar)c)\n"\
"#define UCHAR(a)				(uchar)((uchar)a)\n"\
"#define SHORT3(a, b, c)		(short3)((short)a, (short)b, (short)c)\n"\
"#define INT3(a, b, c)			(int3)((int)a, (int)b, (int)c)\n"\
"\n"\
"#pragma OPENCL EXTENSION cl_khr_byte_addressable_store : enable\n"\
"\n"\
"#define ASSERT_RANGE(x, min, max)\n"\
"#define CODEC_QUALITY_FAST                    (0) // this will always be faster than \"normal\"\n"\
"#define CODEC_QUALITY_NORMAL                  (1) // this will always be faster than \"high\"\n"\
"#define CODEC_QUALITY_HIGH                    (2) // for images that are random noise, this mode tends to degenerate into \"best\"\n"\
"#define CODEC_QUALITY_BEST                    (3)\n"\
"\n"\
"#define MAX_ERROR_DIFF_MUL              16.0f   // highest multiple that current value of the cost function can be to the current best value during pathing before aborting search\n"\
"#define MAX_INIT_ERROR                  9999999999999999999999999999999999.0f\n"\
"#define SAMPLE_LIST_SIZE0       2               // must be 2+\n"\
"#define SAMPLE_LIST_SIZE1       8               // must be 8+\n"\
"#define SAMPLE_LIST_SIZE2       8               // used in delta mode pathing, performance vs quality trade-off\n"\
"#define MAX_KMEANS_ITERATIONS   16\n"\
"#define M_INV_GOLDEN_F                  0.618033988749894848204586834365638f\n"\
"\n"\
"#define ETC_MODE_DELTA      1\n"\
"#define ETC_MODE_NODELTA    2\n"\
"#define ETC_MODE_T          4\n"\
"#define ETC_MODE_H          8\n"\
"#define ETC_MODE_PLANAR     16\n"\
"\n"\
"#define ETC_MODE_ANY            (ETC_MODE_DELTA | ETC_MODE_NODELTA | ETC_MODE_T | ETC_MODE_H | ETC_MODE_PLANAR)\n"\
"#define ETC_MODE_ETC1           (ETC_MODE_DELTA | ETC_MODE_NODELTA)\n"\
"#define ETC_MODE_ETC2RGBA1      (ETC_MODE_DELTA | ETC_MODE_T | ETC_MODE_H | ETC_MODE_PLANAR)\n"\
"\n"\
"#define ETC_RGBEXPANDVECTO4BIT  0\n"\
"#define ETC_RGBEXPANDVECTO5BIT  1\n"\
"\n"\
"#define ETC_EVALUATEDELTAERRORGENERIC   0\n"\
"#define ETC_EVALUATETSINGLEERRORGENERIC 1\n"\
"#define ETC_EVALUATETTRIPLEERRORGENERIC 2\n"\
"#define ETC_EVALUATEHERRORGENERIC               3\n"\
"\n"\
"#define ETC_EVALUATEDELTAERRORGENERICWEIGHTED   4\n"\
"#define ETC_EVALUATETSINGLEERRORGENERICWEIGHTED 5\n"\
"#define ETC_EVALUATETTRIPLEERRORGENERICWEIGHTED 6\n"\
"#define ETC_EVALUATEHERRORGENERICWEIGHTED               7\n"\
"\n"\
"#define ETC_EVALUATEDELTAERRORGENERICA1         8\n"\
"#define ETC_EVALUATETSINGLEERRORGENERICA1       9\n"\
"#define ETC_EVALUATETTRIPLEERRORGENERICA1       10\n"\
"#define ETC_EVALUATEHERRORGENERICA1                     11\n"\
"\n"\
"enum\n"\
"{\n"\
"    ETC_ENC_MODE_DELTA = 0,\n"\
"    ETC_ENC_MODE_NODELTA = 1,\n"\
"    ETC_ENC_MODE_T = 2,\n"\
"    ETC_ENC_MODE_H = 3,\n"\
"    ETC_ENC_MODE_PLANAR = 4,\n"\
"};\n"\
"\n"\
"typedef struct etc_sample_s\n"\
"{\n"\
"    uchar3      pos_quantised;\n"\
"    float       error;\n"\
"}etc_sample_t;\n"\
"\n"\
"typedef struct etc_partition_mode_params_s\n"\
"{\n"\
"    uchar3      rgb[2];\n"\
"    int     is_flipped;\n"\
"    int     indexes[16];\n"\
"    int     table[2];\n"\
"}etc_partition_mode_params_t;\n"\
"\n"\
"typedef struct etc_th_mode_params_s\n"\
"{\n"\
"    uchar3      rgb[2];\n"\
"    int     indexes[16];\n"\
"    int     table;\n"\
"}etc_th_mode_params_t;\n"\
"\n"\
"typedef struct etc_pathing_params_s\n"\
"{\n"\
"    __constant const int    *partition_indexes;\n"\
"    int                     *indexes;\n"\
"    int                     num_indexes;\n"\
"    int                     mode;\n"\
"    int                     h_index;\n"\
"}etc_pathing_params_t;\n"\
"\n"\
"typedef struct etc_planar_mode_params_s\n"\
"{\n"\
"    uchar3      rgb[3];\n"\
"}etc_planar_mode_params_t;\n"\
"\n"\
"__constant const int g_partition_indexes[2][2][8] =\n"\
"{\n"\
"    {\n"\
"        {0, 1, 4, 5, 8, 9, 12, 13},\n"\
"    {2, 3, 6, 7, 10, 11, 14, 15}\n"\
"    },\n"\
"    {\n"\
"        {0, 1, 2, 3, 4, 5, 6, 7},\n"\
"    {8, 9, 10, 11, 12, 13, 14, 15}\n"\
"    }\n"\
"};\n"\
"\n"\
"__constant const int g_table[8][4] =\n"\
"{\n"\
"    {  2,  8,   -2,   -8 },\n"\
"    {  5, 17,   -5,  -17 },\n"\
"    {  9, 29,   -9,  -29 },\n"\
"    { 13, 42,  -13,  -42 },\n"\
"    { 18, 60,  -18,  -60 },\n"\
"    { 24, 80,  -24,  -80 },\n"\
"    { 33, 106, -33, -106 },\n"\
"    { 47, 183, -47, -183 }\n"\
"};\n"\
"\n"\
"__constant const int g_etc2_tmode_distance[8] =\n"\
"{\n"\
"    3, 6, 11, 16, 23, 32, 41, 64\n"\
"};\n"\
"\n"\
"__constant const int g_alpha[16][8] =\n"\
"{\n"\
"    { -3, -6,  -9, -15, 2, 5, 8, 14 },\n"\
"    { -3, -7, -10, -13, 2, 6, 9, 12 },\n"\
"    { -2, -5,  -8, -13, 1, 4, 7, 12 },\n"\
"    { -2, -4,  -6, -13, 1, 3, 5, 12 },\n"\
"    { -3, -6,  -8, -12, 2, 5, 7, 11 },\n"\
"    { -3, -7,  -9, -11, 2, 6, 8, 10 },\n"\
"    { -4, -7,  -8, -11, 3, 6, 7, 10 },\n"\
"    { -3, -5,  -8, -11, 2, 4, 7, 10 },\n"\
"    { -2, -6,  -8, -10, 1, 5, 7,  9 },\n"\
"    { -2, -5,  -8, -10, 1, 4, 7,  9 },\n"\
"    { -2, -4,  -8, -10, 1, 3, 7,  9 },\n"\
"    { -2, -5,  -7, -10, 1, 4, 6,  9 },\n"\
"    { -3, -4,  -7, -10, 2, 3, 6,  9 },\n"\
"    { -1, -2,  -3, -10, 0, 1, 2,  9 },\n"\
"    { -4, -6,  -8,  -9, 3, 5, 7,  8 },\n"\
"    { -3, -5,  -7,  -9, 2, 4, 6,  8 }\n"\
"};\n"\
"__constant const int g_alpha_range[16] =\n"\
"{\n"\
"    14 + 15,\n"\
"    12 + 13,\n"\
"    12 + 13,\n"\
"    12 + 13,\n"\
"    11 + 12,\n"\
"    10 + 11,\n"\
"    10 + 11,\n"\
"    10 + 11,\n"\
"    9 + 10,\n"\
"    9 + 10,\n"\
"    9 + 10,\n"\
"    9 + 10,\n"\
"    9 + 10,\n"\
"    9 + 10,\n"\
"    8 + 9,\n"\
"    8 + 9\n"\
"};\n"\
"\n"\
"float3 ETC_ConvertToRGBf3(float3 v)\n"\
"{\n"\
"    float3 rgb;\n"\
"    MEMBER(rgb, X) = MEMBER(v, X) + 1.402f * MEMBER(v, Z);\n"\
"    MEMBER(rgb, Y) = MEMBER(v, X) - 0.344136f * MEMBER(v, Y) - 0.714136f * MEMBER(v, Z);\n"\
"    MEMBER(rgb, Z) = MEMBER(v, X) + 1.772f * MEMBER(v, Y);\n"\
"    return rgb;\n"\
"}\n"\
"\n"\
"float3 ETC_ConvertToYPBPRf3(float3 v)\n"\
"{\n"\
"    float3 ypbpr;\n"\
"    MEMBER(ypbpr, X) = 0.299f * MEMBER(v, X) + 0.587f * MEMBER(v, Y) + 0.114f * MEMBER(v, Z);\n"\
"    MEMBER(ypbpr, Y) = 0.5f * (MEMBER(v, Z) - MEMBER(ypbpr, X)) / (1.0f - 0.114f);\n"\
"    MEMBER(ypbpr, Z) = 0.5f * (MEMBER(v, X) - MEMBER(ypbpr, X)) / (1.0f - 0.299f);\n"\
"    return ypbpr;\n"\
"}\n"\
"float3 ETC_ConvertToYPBPRu3(uchar3 v)\n"\
"{\n"\
"    float3 ypbpr;\n"\
"    MEMBER(ypbpr, X) = 0.299f * (float)MEMBER(v, X) + 0.587f * (float)MEMBER(v, Y) + 0.114f * (float)MEMBER(v, Z);\n"\
"    MEMBER(ypbpr, Y) = 0.5f * ((float)MEMBER(v, Z) - MEMBER(ypbpr, X)) / (1.0f - 0.114f);\n"\
"    MEMBER(ypbpr, Z) = 0.5f * ((float)MEMBER(v, X) - MEMBER(ypbpr, X)) / (1.0f - 0.299f);\n"\
"    return ypbpr;\n"\
"}\n"\
"float3 ETC_ConvertToYPBPRs3(short3 v)\n"\
"{\n"\
"    float3 ypbpr;\n"\
"    MEMBER(ypbpr, X) = 0.299f * (float)MEMBER(v, X) + 0.587f * (float)MEMBER(v, Y) + 0.114f * (float)MEMBER(v, Z);\n"\
"    MEMBER(ypbpr, Y) = 0.5f * ((float)MEMBER(v, Z) - MEMBER(ypbpr, X)) / (1.0f - 0.114f);\n"\
"    MEMBER(ypbpr, Z) = 0.5f * ((float)MEMBER(v, X) - MEMBER(ypbpr, X)) / (1.0f - 0.299f);\n"\
"    return ypbpr;\n"\
"}\n"\
"static int MemCmp(void *a, void *b, int size)\n"\
"{\n"\
"    int i;\n"\
"    uchar *ac = (uchar*)a;\n"\
"    uchar *bc = (uchar*)b;\n"\
"    for (i = 0; i < size; i++)\n"\
"    {\n"\
"        if (ac[i] != bc[i])\n"\
"        {\n"\
"            return 1;\n"\
"        }\n"\
"    }\n"\
"    return 0;\n"\
"}\n"\
"static int Vec3f32Cmp(float3 a, float3 b)\n"\
"{\n"\
"    if ((MEMBER(a, X) != MEMBER(b, X)) || (MEMBER(a, Y) != MEMBER(b, Y)) || (MEMBER(a, Z) != MEMBER(b, Z)))\n"\
"        return 1;\n"\
"    else\n"\
"        return 0;\n"\
"}\n"\
"\n"\
"static void ETC_PackBlockSwapOrder(__global uchar *out_block, uchar *in_block)\n"\
"{\n"\
"    out_block[0] = in_block[3];\n"\
"    out_block[1] = in_block[2];\n"\
"    out_block[2] = in_block[1];\n"\
"    out_block[3] = in_block[0];\n"\
"    out_block[4] = in_block[7];\n"\
"    out_block[5] = in_block[6];\n"\
"    out_block[6] = in_block[5];\n"\
"    out_block[7] = in_block[4];\n"\
"}\n"\
"static void ETC_PackBlockReverseOrder(__global uchar *out_block, uchar *in_block)\n"\
"{\n"\
"    out_block[0] = in_block[7];\n"\
"    out_block[1] = in_block[6];\n"\
"    out_block[2] = in_block[5];\n"\
"    out_block[3] = in_block[4];\n"\
"    out_block[4] = in_block[3];\n"\
"    out_block[5] = in_block[2];\n"\
"    out_block[6] = in_block[1];\n"\
"    out_block[7] = in_block[0];\n"\
"}\n"\
"static void ETC_WriteBits(uchar *block, uint x, int start_bit, int num_bits)\n"\
"{\n"\
"    int i = 0;\n"\
"    int lmask = (1 << (start_bit & 0x07));\n"\
"    int umask = (1 << (num_bits & 0x07));\n"\
"\n"\
"    DEBUG_PRINTF((\"writing %u of len %i to %i\\n\", x, num_bits, start_bit));\n"\
"\n"\
"    if (num_bits == 0)\n"\
"    {\n"\
"        return;\n"\
"    }\n"\
"        for (i = 0; i < num_bits; i++)\n"\
"        {\n"\
"            block[(start_bit + i) >> 3] &= ~(1 << ((start_bit + i) & 0x07));\n"\
"            block[(start_bit + i) >> 3] |= ((x >> i) & 1) << ((start_bit + i) & 0x07);\n"\
"        }\n"\
"}\n"\
"\n"\
"uchar ETC_RGBRoundTo7Bit(uchar v)\n"\
"{\n"\
"    uint temp = v;\n"\
"    temp = ((temp + 1) * 127) >> 7;\n"\
"    temp >>= 1;\n"\
"    temp <<= 1;\n"\
"    temp |= temp >> 7;\n"\
"    v = temp;\n"\
"\n"\
"    return v;\n"\
"}\n"\
"uchar ETC_RGBRoundTo6Bit(uchar v)\n"\
"{\n"\
"    uint temp = v;\n"\
"    temp = ((temp + 3) * 63) >> 6;\n"\
"    temp >>= 2;\n"\
"    temp <<= 2;\n"\
"    temp |= temp >> 6;\n"\
"    v = temp;\n"\
"\n"\
"    return v;\n"\
"}\n"\
"uchar ETC_RGBRoundTo5Bit(uchar v)\n"\
"{\n"\
"    uint temp = v;\n"\
"    temp = ((temp + 5) * 31) >> 5;\n"\
"    temp >>= 3;\n"\
"    temp <<= 3;\n"\
"    temp |= temp >> 5;\n"\
"    v = temp;\n"\
"\n"\
"    return v;\n"\
"}\n"\
"uchar ETC_RGBRoundTo4Bit(uchar v)\n"\
"{\n"\
"    uint temp = v;\n"\
"    temp = ((temp + 9) * 15) >> 4;\n"\
"    temp >>= 4;\n"\
"    temp <<= 4;\n"\
"    temp |= temp >> 4;\n"\
"    v = temp;\n"\
"\n"\
"    return v;\n"\
"}\n"\
"uchar3 ETC_RGBRoundVecTo7Bit(uchar3 v)\n"\
"{\n"\
"    MEMBER(v, X) = ETC_RGBRoundTo7Bit(MEMBER(v, X));\n"\
"    MEMBER(v, Y) = ETC_RGBRoundTo7Bit(MEMBER(v, Y));\n"\
"    MEMBER(v, Z) = ETC_RGBRoundTo7Bit(MEMBER(v, Z));\n"\
"\n"\
"    return v;\n"\
"}\n"\
"uchar3 ETC_RGBRoundVecTo6Bit(uchar3 v)\n"\
"{\n"\
"    MEMBER(v, X) = ETC_RGBRoundTo6Bit(MEMBER(v, X));\n"\
"    MEMBER(v, Y) = ETC_RGBRoundTo6Bit(MEMBER(v, Y));\n"\
"    MEMBER(v, Z) = ETC_RGBRoundTo6Bit(MEMBER(v, Z));\n"\
"\n"\
"    return v;\n"\
"}\n"\
"uchar3 ETC_RGBRoundVecTo5Bit(uchar3 v)\n"\
"{\n"\
"    MEMBER(v, X) = ETC_RGBRoundTo5Bit(MEMBER(v, X));\n"\
"    MEMBER(v, Y) = ETC_RGBRoundTo5Bit(MEMBER(v, Y));\n"\
"    MEMBER(v, Z) = ETC_RGBRoundTo5Bit(MEMBER(v, Z));\n"\
"\n"\
"    return v;\n"\
"}\n"\
"uchar3 ETC_RGBRoundVecTo4Bit(uchar3 v)\n"\
"{\n"\
"    MEMBER(v, X) = ETC_RGBRoundTo4Bit(MEMBER(v, X));\n"\
"    MEMBER(v, Y) = ETC_RGBRoundTo4Bit(MEMBER(v, Y));\n"\
"    MEMBER(v, Z) = ETC_RGBRoundTo4Bit(MEMBER(v, Z));\n"\
"\n"\
"    return v;\n"\
"}\n"\
"\n"\
"uchar ETC_ExpandTo7Bit(uchar v)\n"\
"{\n"\
"    int temp = v;\n"\
"    temp <<= 1;\n"\
"    temp |= temp >> 7;\n"\
"    v = temp;\n"\
"    return v;\n"\
"}\n"\
"uchar ETC_ExpandTo6Bit(uchar v)\n"\
"{\n"\
"    int temp = v;\n"\
"    temp <<= 2;\n"\
"    temp |= temp >> 6;\n"\
"    v = temp;\n"\
"    return v;\n"\
"}\n"\
"uchar ETC_ExpandTo5Bit(uchar v)\n"\
"{\n"\
"    int temp = v;\n"\
"    temp <<= 3;\n"\
"    temp |= temp >> 5;\n"\
"    v = temp;\n"\
"    return v;\n"\
"}\n"\
"uchar ETC_ExpandTo4Bit(uchar v)\n"\
"{\n"\
"    int temp = v;\n"\
"    temp <<= 4;\n"\
"    temp |= temp >> 4;\n"\
"    v = temp;\n"\
"    return v;\n"\
"}\n"\
"\n"\
"uchar3 ETC_RGBExpandVecTo7Bit(uchar3 v)\n"\
"{\n"\
"    MEMBER(v, X) = ETC_ExpandTo7Bit(MEMBER(v, X));\n"\
"    MEMBER(v, Y) = ETC_ExpandTo7Bit(MEMBER(v, Y));\n"\
"    MEMBER(v, Z) = ETC_ExpandTo7Bit(MEMBER(v, Z));\n"\
"\n"\
"    return v;\n"\
"}\n"\
"\n"\
"uchar3 ETC_RGBExpandVecTo6Bit(uchar3 v)\n"\
"{\n"\
"    MEMBER(v, X) = ETC_ExpandTo6Bit(MEMBER(v, X));\n"\
"    MEMBER(v, Y) = ETC_ExpandTo6Bit(MEMBER(v, Y));\n"\
"    MEMBER(v, Z) = ETC_ExpandTo6Bit(MEMBER(v, Z));\n"\
"\n"\
"    return v;\n"\
"}\n"\
"uchar3 ETC_RGBExpandVecTo5Bit(uchar3 v)\n"\
"{\n"\
"    MEMBER(v, X) = ETC_ExpandTo5Bit(MEMBER(v, X));\n"\
"    MEMBER(v, Y) = ETC_ExpandTo5Bit(MEMBER(v, Y));\n"\
"    MEMBER(v, Z) = ETC_ExpandTo5Bit(MEMBER(v, Z));\n"\
"\n"\
"    return v;\n"\
"}\n"\
"uchar3 ETC_RGBExpandVecTo4Bit(uchar3 v)\n"\
"{\n"\
"    MEMBER(v, X) = ETC_ExpandTo4Bit(MEMBER(v, X));\n"\
"    MEMBER(v, Y) = ETC_ExpandTo4Bit(MEMBER(v, Y));\n"\
"    MEMBER(v, Z) = ETC_ExpandTo4Bit(MEMBER(v, Z));\n"\
"\n"\
"    return v;\n"\
"}\n"\
"\n"\
"\n"\
"void ETC_AddSampleToList(int sample_list_entries, etc_sample_t *list, etc_sample_t sample)\n"\
"{\n"\
"    int i, j;\n"\
"\n"\
"    for (i = 0; i < sample_list_entries; i++)\n"\
"    {\n"\
"        if (sample.error < list[i].error)\n"\
"        {\n"\
"            for (j = sample_list_entries - 1; j > i; j--)\n"\
"                list[j] = list[j - 1];\n"\
"            list[i] = sample;\n"\
"            break;\n"\
"        }\n"\
"    }\n"\
"}\n"\
"float ETC_EvaluateError(int is_ypbpr, float3 *trans_pixel, uchar3 rgb, __constant const int *partition_indexes)\n"\
"{\n"\
"    int i, table, j;\n"\
"    float best_table_dist = MAX_INIT_ERROR;\n"\
"    float3 rgb32f = VFLOAT3(MEMBER(rgb, X), MEMBER(rgb, Y), MEMBER(rgb, Z));\n"\
"    //DEBUG_PRINTF((\"trans_pixel / partition_indexes: 0x%p 0x%p\\n\", trans_pixel, partition_indexes));\n"\
"\n"\
"    for (table = 0; table < 8; table++)\n"\
"    {\n"\
"        float current_table_dist = 0.0f;\n"\
"        for (i = 0; i < 8; i++)\n"\
"        {\n"\
"            float best_dist = MAX_INIT_ERROR;\n"\
"            for (j = 0; j < 4; j++)\n"\
"            {\n"\
"                float3 temp_pixel = clamp(rgb32f + VFLOAT3(g_table[table][j], g_table[table][j], g_table[table][j]), 0.0f, 255.0f);\n"\
"                float3 delta;\n"\
"\n"\
"                ASSERT_RANGE(partition_indexes[i], 0, 15);\n"\
"\n"\
"                if (is_ypbpr)\n"\
"                {\n"\
"                    delta = ETC_ConvertToYPBPRf3(temp_pixel) - trans_pixel[partition_indexes[i]];\n"\
"                }\n"\
"                else\n"\
"                {\n"\
"                    delta = temp_pixel - trans_pixel[partition_indexes[i]];\n"\
"                }\n"\
"\n"\
"                float lensq = dot(delta, delta);\n"\
"\n"\
"                if (lensq < best_dist)\n"\
"                {\n"\
"                    best_dist = lensq;\n"\
"                }\n"\
"            }\n"\
"            current_table_dist += best_dist;\n"\
"        }\n"\
"        if (current_table_dist < best_table_dist)\n"\
"        {\n"\
"            best_table_dist = current_table_dist;\n"\
"        }\n"\
"    }\n"\
"    return best_table_dist;\n"\
"}\n"\
"\n"\
"float ETC_EvaluateErrorTSingle(int is_ypbpr, float3 *trans_pixel, uchar3 rgb, int *indexes, int num_indexes)\n"\
"{\n"\
"    int i;\n"\
"    float dist = 0.0f;\n"\
"    float3 rgb32f;\n"\
"\n"\
"    //DEBUG_PRINTF((\"trans_pixel / indexes / num_indexes: 0x%p 0x%p %i\\n\", trans_pixel, indexes, num_indexes));\n"\
"\n"\
"    if (!num_indexes)\n"\
"    {\n"\
"        return 0.0f;\n"\
"    }\n"\
"    rgb32f = VFLOAT3(MEMBER(rgb, X), MEMBER(rgb, Y), MEMBER(rgb, Z));\n"\
"\n"\
"    if (is_ypbpr)\n"\
"    {\n"\
"        rgb32f = ETC_ConvertToYPBPRf3(rgb32f);\n"\
"    }\n"\
"\n"\
"    for (i = 0; i < num_indexes; i++)\n"\
"    {\n"\
"        float3 delta;\n"\
"        ASSERT_RANGE(indexes[i], 0, 15);\n"\
"        delta = rgb32f - trans_pixel[indexes[i]];\n"\
"        dist += dot(delta, delta);\n"\
"    }\n"\
"    return dist;\n"\
"}\n"\
"float ETC_EvaluateErrorTTriple(int is_ypbpr, float3 *trans_pixel, uchar3 rgb, int *indexes, int num_indexes)\n"\
"{\n"\
"    int i, mode, j;\n"\
"    float dist = 0.0f;\n"\
"    float3 rgb32f;\n"\
"\n"\
"    //DEBUG_PRINTF((\"trans_pixel / indexes / num_indexes: 0x%p 0x%p %i\\n\", trans_pixel, indexes, num_indexes));\n"\
"\n"\
"    float best_mode_dist;\n"\
"\n"\
"    if (!num_indexes)\n"\
"    {\n"\
"        return 0.0f;\n"\
"    }\n"\
"    rgb32f = VFLOAT3(MEMBER(rgb, X), MEMBER(rgb, Y), MEMBER(rgb, Z));\n"\
"    best_mode_dist = MAX_INIT_ERROR;\n"\
"    for (mode = 0; mode < 8; mode++)\n"\
"    {\n"\
"        float current_mode_dist = 0.0f;\n"\
"        float3 points[3];\n"\
"        points[0] = clamp(rgb32f + VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);\n"\
"        points[1] = rgb32f;\n"\
"        points[2] = clamp(rgb32f - VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);\n"\
"        if (is_ypbpr)\n"\
"        {\n"\
"            points[0] = ETC_ConvertToYPBPRf3(points[0]);\n"\
"            points[1] = ETC_ConvertToYPBPRf3(points[1]);\n"\
"            points[2] = ETC_ConvertToYPBPRf3(points[2]);\n"\
"        }\n"\
"\n"\
"        for (i = 0; i < num_indexes; i++)\n"\
"        {\n"\
"            float best_dist = MAX_INIT_ERROR;\n"\
"            for (j = 0; j < 3; j++)\n"\
"            {\n"\
"                float3 delta;\n"\
"                float lensq;\n"\
"                ASSERT_RANGE(indexes[i], 0, 15);\n"\
"                delta = points[j] - trans_pixel[indexes[i]];\n"\
"                lensq = dot(delta, delta);\n"\
"                if (lensq < best_dist)\n"\
"                {\n"\
"                    best_dist = lensq;\n"\
"                }\n"\
"            }\n"\
"            current_mode_dist += best_dist;\n"\
"        }\n"\
"        if (current_mode_dist < best_mode_dist)\n"\
"        {\n"\
"            best_mode_dist = current_mode_dist;\n"\
"        }\n"\
"    }\n"\
"    return best_mode_dist;\n"\
"}\n"\
"\n"\
"float ETC_EvaluateErrorH(int is_ypbpr, float3 *trans_pixel, uchar3 rgb, int *indexes, int num_indexes, int mode)\n"\
"{\n"\
"    int i, j;\n"\
"    float dist = 0.0f;\n"\
"    float3 rgb32f;\n"\
"    float current_mode_dist = 0.0f;\n"\
"    float3 points[2];\n"\
"\n"\
"    //DEBUG_PRINTF((\"trans_pixel / indexes / num_indexes / mode: 0x%p 0x%p %i %i\\n\", trans_pixel, indexes, num_indexes, mode));\n"\
"\n"\
"    if (!num_indexes)\n"\
"    {\n"\
"        return 0.0f;\n"\
"    }\n"\
"\n"\
"    rgb32f = VFLOAT3(MEMBER(rgb, X), MEMBER(rgb, Y), MEMBER(rgb, Z));\n"\
"\n"\
"    ASSERT_RANGE(mode, 0, 7);\n"\
"\n"\
"    points[0] = clamp(rgb32f + VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);\n"\
"    points[1] = clamp(rgb32f - VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);\n"\
"\n"\
"    if (is_ypbpr)\n"\
"    {\n"\
"        points[0] = ETC_ConvertToYPBPRf3(points[0]);\n"\
"        points[1] = ETC_ConvertToYPBPRf3(points[1]);\n"\
"    }\n"\
"\n"\
"    for (i = 0; i < num_indexes; i++)\n"\
"    {\n"\
"        float best_dist = MAX_INIT_ERROR;\n"\
"        for (j = 0; j < 2; j++)\n"\
"        {\n"\
"            float3 delta;\n"\
"            float lensq;\n"\
"\n"\
"            ASSERT_RANGE(indexes[i], 0, 15);\n"\
"            delta = points[j] - trans_pixel[indexes[i]];\n"\
"            lensq = dot(delta, delta);\n"\
"\n"\
"            if (lensq < best_dist)\n"\
"            {\n"\
"                best_dist = lensq;\n"\
"            }\n"\
"        }\n"\
"        current_mode_dist += best_dist;\n"\
"    }\n"\
"\n"\
"    return current_mode_dist;\n"\
"}\n"\
"\n"\
"float EvaluateErrorGeneric(int mode, int is_ypbpr, float3 *trans_pixel, uchar3 rgb, etc_pathing_params_t *pathing_params)\n"\
"{\n"\
"    switch (mode)\n"\
"    {\n"\
"        case ETC_EVALUATEDELTAERRORGENERIC:\n"\
"            return ETC_EvaluateError(is_ypbpr, trans_pixel, rgb, pathing_params->partition_indexes);\n"\
"        case ETC_EVALUATETSINGLEERRORGENERIC:\n"\
"            return ETC_EvaluateErrorTSingle(is_ypbpr, trans_pixel, rgb, pathing_params->indexes, pathing_params->num_indexes);\n"\
"        case ETC_EVALUATETTRIPLEERRORGENERIC:\n"\
"            return ETC_EvaluateErrorTTriple(is_ypbpr, trans_pixel, rgb, pathing_params->indexes, pathing_params->num_indexes);\n"\
"        case ETC_EVALUATEHERRORGENERIC:\n"\
"            return ETC_EvaluateErrorH(is_ypbpr, trans_pixel, rgb, pathing_params->indexes, pathing_params->num_indexes, pathing_params->mode);\n"\
"        default:\n"\
"            return MAX_INIT_ERROR;\n"\
"    }\n"\
"}\n"\
"void ETC_GetOptimalIndexes(int is_ypbpr, float3 *trans_pixel, uchar3 rgb, __constant const int *partition_indexes, int *best_table, int *indexes)\n"\
"{\n"\
"    int i, table, j;\n"\
"    float best_table_dist = MAX_INIT_ERROR;\n"\
"    float3 rgb32f = VFLOAT3(MEMBER(rgb, X), MEMBER(rgb, Y), MEMBER(rgb, Z));\n"\
"\n"\
"    *best_table = 0;\n"\
"\n"\
"    for (table = 0; table < 8; table++)\n"\
"    {\n"\
"        float current_table_dist = 0.0f;\n"\
"        for (i = 0; i < 8; i++)\n"\
"        {\n"\
"            float best_dist = MAX_INIT_ERROR;\n"\
"            for (j = 0; j < 4; j++)\n"\
"            {\n"\
"                float3 temp_pixel = clamp(rgb32f + VFLOAT3(g_table[table][j], g_table[table][j], g_table[table][j]), 0.0f, 255.0f);\n"\
"                float3 delta;\n"\
"\n"\
"                ASSERT_RANGE(partition_indexes[i], 0, 15);\n"\
"\n"\
"                if (is_ypbpr)\n"\
"                {\n"\
"                    delta = ETC_ConvertToYPBPRf3(temp_pixel) - trans_pixel[partition_indexes[i]];\n"\
"                }\n"\
"                else\n"\
"                {\n"\
"                    delta = temp_pixel - trans_pixel[partition_indexes[i]];\n"\
"                }\n"\
"\n"\
"                float lensq = dot(delta, delta);\n"\
"\n"\
"                if (lensq < best_dist)\n"\
"                {\n"\
"                    best_dist = lensq;\n"\
"                }\n"\
"            }\n"\
"            current_table_dist += best_dist;\n"\
"        }\n"\
"        if (current_table_dist < best_table_dist)\n"\
"        {\n"\
"            *best_table = table;\n"\
"            best_table_dist = current_table_dist;\n"\
"        }\n"\
"    }\n"\
"\n"\
"    for (i = 0; i < 8; i++)\n"\
"    {\n"\
"        float best_dist = MAX_INIT_ERROR;\n"\
"        for (j = 0; j < 4; j++)\n"\
"        {\n"\
"            float3 temp_pixel = clamp(rgb32f + VFLOAT3(g_table[*best_table][j], g_table[*best_table][j], g_table[*best_table][j]), 0.0f, 255.0f);\n"\
"            float3 delta;\n"\
"\n"\
"            ASSERT_RANGE(partition_indexes[i], 0, 15);\n"\
"\n"\
"            if (is_ypbpr)\n"\
"            {\n"\
"                delta = ETC_ConvertToYPBPRf3(temp_pixel) - trans_pixel[partition_indexes[i]];\n"\
"            }\n"\
"            else\n"\
"            {\n"\
"                delta = temp_pixel - trans_pixel[partition_indexes[i]];\n"\
"            }\n"\
"\n"\
"            float lensq = dot(delta, delta);\n"\
"\n"\
"            if (lensq < best_dist)\n"\
"            {\n"\
"                indexes[partition_indexes[i]] = j;\n"\
"                best_dist = lensq;\n"\
"            }\n"\
"        }\n"\
"    }\n"\
"}\n"\
"\n"\
"float ETC_GetOptimalTIndexes(int is_ypbpr, float3 *trans_pixel, uchar3 rgb_single, uchar3 rgb_triple, int *indexes, int *best_mode)\n"\
"{\n"\
"    int i, mode, j;\n"\
"    float dist = 0.0f;\n"\
"    float3 rgb32f_single;\n"\
"    float3 rgb32f_triple;\n"\
"    float best_mode_dist;\n"\
"    float3 points[4];\n"\
"\n"\
"    rgb32f_single = VFLOAT3(MEMBER(rgb_single, X), MEMBER(rgb_single, Y), MEMBER(rgb_single, Z));\n"\
"    rgb32f_triple = VFLOAT3(MEMBER(rgb_triple, X), MEMBER(rgb_triple, Y), MEMBER(rgb_triple, Z));\n"\
"    best_mode_dist = MAX_INIT_ERROR;\n"\
"    *best_mode = 0;\n"\
"\n"\
"    points[0] = rgb32f_single;\n"\
"\n"\
"    if (is_ypbpr)\n"\
"    {\n"\
"        points[0] = ETC_ConvertToYPBPRf3(points[0]);\n"\
"    }\n"\
"\n"\
"    for (mode = 0; mode < 8; mode++)\n"\
"    {\n"\
"        float current_mode_dist = 0.0f;\n"\
"\n"\
"        points[1] = clamp(rgb32f_triple + VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);\n"\
"        points[2] = rgb32f_triple;\n"\
"        points[3] = clamp(rgb32f_triple - VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);\n"\
"\n"\
"        if (is_ypbpr)\n"\
"        {\n"\
"            points[1] = ETC_ConvertToYPBPRf3(points[1]);\n"\
"            points[2] = ETC_ConvertToYPBPRf3(points[2]);\n"\
"            points[3] = ETC_ConvertToYPBPRf3(points[3]);\n"\
"        }\n"\
"\n"\
"        for (i = 0; i < 16; i++)\n"\
"        {\n"\
"            float best_dist = MAX_INIT_ERROR;\n"\
"            for (j = 0; j < 4; j++)\n"\
"            {\n"\
"                float3 delta;\n"\
"                float lensq;\n"\
"                delta = points[j] - trans_pixel[i];\n"\
"                lensq = dot(delta, delta);\n"\
"                if (lensq < best_dist)\n"\
"                {\n"\
"                    best_dist = lensq;\n"\
"                }\n"\
"            }\n"\
"            current_mode_dist += best_dist;\n"\
"        }\n"\
"        if (current_mode_dist < best_mode_dist)\n"\
"        {\n"\
"            *best_mode = mode;\n"\
"            best_mode_dist = current_mode_dist;\n"\
"        }\n"\
"    }\n"\
"\n"\
"    ASSERT_RANGE(*best_mode, 0, 7);\n"\
"\n"\
"    points[1] = clamp(rgb32f_triple + VFLOAT3(g_etc2_tmode_distance[*best_mode], g_etc2_tmode_distance[*best_mode], g_etc2_tmode_distance[*best_mode]), 0.0f, 255.0f);\n"\
"    points[2] = rgb32f_triple;\n"\
"    points[3] = clamp(rgb32f_triple - VFLOAT3(g_etc2_tmode_distance[*best_mode], g_etc2_tmode_distance[*best_mode], g_etc2_tmode_distance[*best_mode]), 0.0f, 255.0f);\n"\
"\n"\
"    if (is_ypbpr)\n"\
"    {\n"\
"        points[1] = ETC_ConvertToYPBPRf3(points[1]);\n"\
"        points[2] = ETC_ConvertToYPBPRf3(points[2]);\n"\
"        points[3] = ETC_ConvertToYPBPRf3(points[3]);\n"\
"    }\n"\
"\n"\
"    dist = 0.0f;\n"\
"\n"\
"    for (i = 0; i < 16; i++)\n"\
"    {\n"\
"        float best_dist = MAX_INIT_ERROR;\n"\
"        for (j = 0; j < 4; j++)\n"\
"        {\n"\
"            float3 delta;\n"\
"            float lensq;\n"\
"            delta = points[j] - trans_pixel[i];\n"\
"            lensq = dot(delta, delta);\n"\
"            if (lensq < best_dist)\n"\
"            {\n"\
"                indexes[i] = j;\n"\
"                best_dist = lensq;\n"\
"            }\n"\
"        }\n"\
"        dist += best_dist;\n"\
"    }\n"\
"    return dist;\n"\
"}\n"\
"float ETC_GetOptimalHIndexes(int is_ypbpr, float3 *trans_pixel, uchar3 rgb_h0, uchar3 rgb_h1, int *indexes, int mode)\n"\
"{\n"\
"    int i, j;\n"\
"    float dist = 0.0f;\n"\
"    float3 rgb32f_h0;\n"\
"    float3 rgb32f_h1;\n"\
"    float3 points[4];\n"\
"\n"\
"    rgb32f_h0 = VFLOAT3(MEMBER(rgb_h0, X), MEMBER(rgb_h0, Y), MEMBER(rgb_h0, Z));\n"\
"    rgb32f_h1 = VFLOAT3(MEMBER(rgb_h1, X), MEMBER(rgb_h1, Y), MEMBER(rgb_h1, Z));\n"\
"\n"\
"    ASSERT_RANGE(mode, 0, 7);\n"\
"\n"\
"    points[0] = clamp(rgb32f_h0 + VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);\n"\
"    points[1] = clamp(rgb32f_h0 - VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);\n"\
"    points[2] = clamp(rgb32f_h1 + VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);\n"\
"    points[3] = clamp(rgb32f_h1 - VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);\n"\
"\n"\
"    if (is_ypbpr)\n"\
"    {\n"\
"        points[0] = ETC_ConvertToYPBPRf3(points[0]);\n"\
"        points[1] = ETC_ConvertToYPBPRf3(points[1]);\n"\
"        points[2] = ETC_ConvertToYPBPRf3(points[2]);\n"\
"        points[3] = ETC_ConvertToYPBPRf3(points[3]);\n"\
"    }\n"\
"\n"\
"    dist = 0.0f;\n"\
"\n"\
"    for (i = 0; i < 16; i++)\n"\
"    {\n"\
"        float best_dist = MAX_INIT_ERROR;\n"\
"        for (j = 0; j < 4; j++)\n"\
"        {\n"\
"            float3 delta;\n"\
"            float lensq;\n"\
"            delta = points[j] - trans_pixel[i];\n"\
"            lensq = dot(delta, delta);\n"\
"            if (lensq < best_dist)\n"\
"            {\n"\
"                indexes[i] = j;\n"\
"                best_dist = lensq;\n"\
"            }\n"\
"        }\n"\
"        dist += best_dist;\n"\
"    }\n"\
"    return dist;\n"\
"}\n"\
"\n"\
"void ETC_LeastCostDirectedPath(\n"\
"    int step,\n"\
"    int sample_list_entries,\n"\
"    float error_target,\n"\
"    int refine_search,\n"\
"    int is_ypbpr,\n"\
"    float3 *trans_pixel,\n"\
"    etc_sample_t sample,\n"\
"    etc_sample_t *sample_list,\n"\
"    int x_max,\n"\
"    int y_max,\n"\
"    int z_max,\n"\
"    etc_pathing_params_t *pathing_params,\n"\
"    int expand_cb_fp,\n"\
"    int evaluate_cb_fp)\n"\
"{\n"\
"    int         i;\n"\
"    int         j;\n"\
"    int         terminate;\n"\
"    float       dist[27];\n"\
"\n"\
"    DEBUG_PRINTF((\"trans_pixel: 0x%p partition_indexes: 0x%p indexes: 0x%p num_indexes: %i mode: %i\\n\", trans_pixel, pathing_params->partition_indexes, pathing_params->indexes, pathing_params->num_indexes, pathing_params->mode));\n"\
"\n"\
"    for (i = 0, terminate = 0; terminate == 0; i++)\n"\
"    {\n"\
"        uchar3 test_pos[7];\n"\
"        float best_dist;\n"\
"        int best_index;\n"\
"        int terminate_count = 0;\n"\
"\n"\
"        ETC_AddSampleToList(sample_list_entries, &sample_list[0], sample);\n"\
"\n"\
"        if (sample.error <= error_target)\n"\
"        {\n"\
"            break;\n"\
"        }\n"\
"\n"\
"        test_pos[0] = sample.pos_quantised + UCHAR3(step, 0, 0);\n"\
"        test_pos[1] = sample.pos_quantised + UCHAR3(0, step, 0);\n"\
"        test_pos[2] = sample.pos_quantised + UCHAR3(step, step, 0);\n"\
"        test_pos[3] = sample.pos_quantised + UCHAR3(0, 0, step);\n"\
"        test_pos[4] = sample.pos_quantised + UCHAR3(step, 0, step);\n"\
"        test_pos[5] = sample.pos_quantised + UCHAR3(0, step, step);\n"\
"        test_pos[6] = sample.pos_quantised + UCHAR3(step, step, step);\n"\
"\n"\
"        for (j = 0; j < 7; j++)\n"\
"        {\n"\
"            if ((MEMBER(test_pos[j], X) > x_max) || (MEMBER(test_pos[j], Y) > y_max) || (MEMBER(test_pos[j], Z) > z_max))\n"\
"            {\n"\
"                dist[j] = MAX_INIT_ERROR;\n"\
"            }\n"\
"            else\n"\
"            {\n"\
"                uchar3 v;\n"\
"\n"\
"                switch (expand_cb_fp)\n"\
"                {\n"\
"                    case ETC_RGBEXPANDVECTO4BIT:\n"\
"                        v = ETC_RGBExpandVecTo4Bit(test_pos[j]);\n"\
"                        break;\n"\
"                    case ETC_RGBEXPANDVECTO5BIT:\n"\
"                        v = ETC_RGBExpandVecTo5Bit(test_pos[j]);\n"\
"                        break;\n"\
"                }\n"\
"                dist[j] = EvaluateErrorGeneric(evaluate_cb_fp, is_ypbpr, trans_pixel, v, pathing_params);\n"\
"            }\n"\
"        }\n"\
"\n"\
"        best_dist = dist[0];\n"\
"        best_index = 0;\n"\
"        for (j = 1; j < 7; j++)\n"\
"        {\n"\
"            if (dist[j] < best_dist)\n"\
"            {\n"\
"                best_dist = dist[j];\n"\
"                best_index = j;\n"\
"            }\n"\
"        }\n"\
"\n"\
"        for (j = 0; j < 7; j++)\n"\
"            if (dist[j] == MAX_INIT_ERROR)\n"\
"            {\n"\
"                terminate_count++;\n"\
"            }\n"\
"\n"\
"        if (terminate_count == 7)\n"\
"        {\n"\
"            break;\n"\
"        }\n"\
"\n"\
"        if (dist[best_index] > MAX_ERROR_DIFF_MUL * sample_list[0].error)\n"\
"        {\n"\
"            break;\n"\
"        }\n"\
"\n"\
"        sample.pos_quantised = test_pos[best_index];\n"\
"        sample.error = dist[best_index];\n"\
"    }\n"\
"\n"\
"    if (refine_search)\n"\
"    {\n"\
"        sample.pos_quantised = sample_list[0].pos_quantised;\n"\
"        sample.error = sample_list[0].error;\n"\
"\n"\
"        for (i = 0, terminate = 0; terminate == 0; i++)\n"\
"        {\n"\
"            short3 test_pos[27];\n"\
"            float best_dist;\n"\
"            int best_index;\n"\
"            int terminate_count = 0;\n"\
"\n"\
"            if (i != 1)\n"\
"            {\n"\
"                ETC_AddSampleToList(sample_list_entries, &sample_list[0], sample);\n"\
"                DEBUG_PRINTF((\"trans_pixel: 0x%p partition_indexes: 0x%p indexes: 0x%p num_indexes: %i mode: %i\\n\", trans_pixel, pathing_params->partition_indexes, pathing_params->indexes, pathing_params->num_indexes, pathing_params->mode));\n"\
"            }\n"\
"\n"\
"            if (sample.error <= error_target)\n"\
"            {\n"\
"                break;\n"\
"            }\n"\
"\n"\
"            for (j = 0; j < 27; j++)\n"\
"                test_pos[j] = SHORT3(MEMBER(sample.pos_quantised, X), MEMBER(sample.pos_quantised, Y), MEMBER(sample.pos_quantised, Z)) + SHORT3((j % 3) - 1, ((j / 3) % 3) - 1, j/9 - 1);\n"\
"\n"\
"            for (j = 0; j < 27; j++)\n"\
"            {\n"\
"                if (j == 13)\n"\
"                    dist[j] = sample.error;\n"\
"                else if ((MEMBER(test_pos[j], X) > x_max) || (MEMBER(test_pos[j], Y) > y_max) || (MEMBER(test_pos[j], Z) > z_max) || (MEMBER(test_pos[j], X) < 0) || (MEMBER(test_pos[j], Y) < 0) || (MEMBER(test_pos[j], Z) < 0))\n"\
"                    dist[j] = MAX_INIT_ERROR;\n"\
"                else\n"\
"                {\n"\
"                    uchar3 v;\n"\
"\n"\
"                    switch (expand_cb_fp)\n"\
"                    {\n"\
"                    case ETC_RGBEXPANDVECTO4BIT:\n"\
"                        v = ETC_RGBExpandVecTo4Bit(UCHAR3(MEMBER(test_pos[j], X), MEMBER(test_pos[j], Y), MEMBER(test_pos[j], Z)));\n"\
"                        break;\n"\
"                    case ETC_RGBEXPANDVECTO5BIT:\n"\
"                        v = ETC_RGBExpandVecTo5Bit(UCHAR3(MEMBER(test_pos[j], X), MEMBER(test_pos[j], Y), MEMBER(test_pos[j], Z)));\n"\
"                        break;\n"\
"                    }\n"\
"\n"\
"                    dist[j] = EvaluateErrorGeneric(evaluate_cb_fp, is_ypbpr, trans_pixel, v, pathing_params);\n"\
"                }\n"\
"            }\n"\
"\n"\
"            best_dist = dist[0];\n"\
"            best_index = 0;\n"\
"            for (j = 1; j < 27; j++)\n"\
"            {\n"\
"                if (dist[j] < best_dist)\n"\
"                {\n"\
"                    best_dist = dist[j];\n"\
"                    best_index = j;\n"\
"                }\n"\
"            }\n"\
"\n"\
"            if (dist[13] == best_dist)\n"\
"                break;\n"\
"\n"\
"            for (j = 0; j < 27; j++)\n"\
"                if (dist[j] == MAX_INIT_ERROR)\n"\
"                    terminate_count++;\n"\
"\n"\
"            if (terminate_count >= 26)\n"\
"                break;\n"\
"\n"\
"            if (dist[best_index] > MAX_ERROR_DIFF_MUL * sample_list[0].error)\n"\
"                break;\n"\
"\n"\
"            sample.pos_quantised = UCHAR3(MEMBER(test_pos[best_index], X), MEMBER(test_pos[best_index], Y), MEMBER(test_pos[best_index], Z));\n"\
"            sample.error = dist[best_index];\n"\
"        }\n"\
"    }\n"\
"}\n"\
"void ETC_PrepareSampleList(int sample_list_entries, etc_sample_t sample_list[SAMPLE_LIST_SIZE0][SAMPLE_LIST_SIZE1][SAMPLE_LIST_SIZE2])\n"\
"{\n"\
"    int i;\n"\
"    int j;\n"\
"    int k;\n"\
"    for (i = 0; i < SAMPLE_LIST_SIZE0; i++)\n"\
"        for (j = 0; j < SAMPLE_LIST_SIZE1; j++)\n"\
"            for (k = 0; k < sample_list_entries; k++)\n"\
"            {\n"\
"                DEBUG_PRINTF((\"sample_list[%i][%i][%i]: 0x%p\\n\", i, j, k, &sample_list[i][j][k]));\n"\
"                sample_list[i][j][k].error = MAX_INIT_ERROR;\n"\
"            }\n"\
"}\n"\
"\n"\
"void ETC_KMeansTHMode(float3 *trans_pixel, int *indexes0, int *indexes1, int *set_count)\n"\
"{\n"\
"    float3 means[2];\n"\
"    int swap_indexes[2][2][16];\n"\
"    int point_count[2][2];\n"\
"    int ri[2];\n"\
"    int i;\n"\
"    int iteration;\n"\
"    int source;\n"\
"    int target;\n"\
"    int set;\n"\
"\n"\
"    ri[0] = 0;\n"\
"    ri[1] = 0;\n"\
"    \n"\
"    for (i = 0; i < 16; i++)\n"\
"        DEBUG_PRINTF((\"pixel[%i]: %f %f %f\\n\", i, MEMBER(trans_pixel[i], X), MEMBER(trans_pixel[i], Y), MEMBER(trans_pixel[i], Z)));\n"\
"\n"\
"    for (i = 1; i < 16; i++)\n"\
"        if(!(MEMBER(trans_pixel[ri[0]], X) == MEMBER(trans_pixel[i], X) && MEMBER(trans_pixel[ri[0]], Y) == MEMBER(trans_pixel[i], Y) && MEMBER(trans_pixel[ri[0]], Z) == MEMBER(trans_pixel[i], Z)))\n"\
"        {\n"\
"            ri[1] = i;\n"\
"            break;\n"\
"        }\n"\
"\n"\
"    means[0] = trans_pixel[ri[0]];\n"\
"    means[1] = trans_pixel[ri[1]];\n"\
"\n"\
"    for (i = 0; i < 16; i++)\n"\
"        swap_indexes[0][0][i] = i;\n"\
"\n"\
"    point_count[0][0] = 16;\n"\
"    point_count[0][1] = 0;\n"\
"    point_count[1][0] = 0;\n"\
"    point_count[1][1] = 0;\n"\
"\n"\
"    source = 0;\n"\
"    target = 1;\n"\
"\n"\
"    for (iteration = 0; iteration < MAX_KMEANS_ITERATIONS; iteration++)\n"\
"    {\n"\
"        float3 temp_means[2];\n"\
"\n"\
"        temp_means[0] = VFLOAT3(0.0f, 0.0f, 0.0f);\n"\
"        temp_means[1] = VFLOAT3(0.0f, 0.0f, 0.0f);\n"\
"\n"\
"        for (set = 0; set < 2; set++)\n"\
"        {\n"\
"            for (i = 0; i < point_count[source][set]; i++)\n"\
"            {\n"\
"                float3 diff[2];\n"\
"                float lensq[2];\n"\
"\n"\
"                ASSERT_RANGE(source, 0, 1);\n"\
"                ASSERT_RANGE(target, 0, 1);\n"\
"                ASSERT_RANGE(set, 0, 1);\n"\
"                ASSERT_RANGE(swap_indexes[source][set][i], 0, 15);\n"\
"                ASSERT_RANGE(point_count[target][0], 0, 15);\n"\
"                ASSERT_RANGE(point_count[target][1], 0, 15);\n"\
"\n"\
"                diff[0] = means[0] - trans_pixel[swap_indexes[source][set][i]];\n"\
"                diff[1] = means[1] - trans_pixel[swap_indexes[source][set][i]];\n"\
"\n"\
"                lensq[0] = dot(diff[0], diff[0]);\n"\
"                lensq[1] = dot(diff[1], diff[1]);\n"\
"\n"\
"                if (lensq[0] < lensq[1])\n"\
"                {\n"\
"                    swap_indexes[target][0][point_count[target][0]] = swap_indexes[source][set][i];\n"\
"                    temp_means[0] = temp_means[0] + trans_pixel[swap_indexes[source][set][i]];\n"\
"                    //printf(\"swap_indexes[%i][0][%i]: %i\\n\", target, point_count[target][0], swap_indexes[target][0][point_count[target][0]]);\n"\
"                    point_count[target][0]++;\n"\
"                }\n"\
"                else\n"\
"                {\n"\
"                    swap_indexes[target][1][point_count[target][1]] = swap_indexes[source][set][i];\n"\
"                    temp_means[1] = temp_means[1] + trans_pixel[swap_indexes[source][set][i]];\n"\
"                    //printf(\"swap_indexes[%i][1][%i]: %i\\n\", target, point_count[target][1], swap_indexes[target][1][point_count[target][1]]);\n"\
"                    point_count[target][1]++;\n"\
"                }\n"\
"            }\n"\
"        }\n"\
"\n"\
"        temp_means[0] = temp_means[0] / (float)(point_count[target][0] == 0 ? 1 : point_count[target][0]);\n"\
"        temp_means[1] = temp_means[1] / (float)(point_count[target][1] == 0 ? 1 : point_count[target][1]);\n"\
"        DEBUG_PRINTF((\"means[0] means[1]: %f %f %f, %f %f %f\\n\", MEMBER(temp_means[0], X), MEMBER(temp_means[0], Y), MEMBER(temp_means[0], Z), MEMBER(temp_means[1], X), MEMBER(temp_means[1], Y), MEMBER(temp_means[1], Z)));\n"\
"\n"\
"        means[0] = temp_means[0];\n"\
"        means[1] = temp_means[1];\n"\
"\n"\
"        source = (source + 1) % 2;\n"\
"        target = (target + 1) % 2;\n"\
"\n"\
"        point_count[target][0] = 0;\n"\
"        point_count[target][1] = 0;\n"\
"    }\n"\
"    for (i = 0; i < point_count[source][0]; i++)\n"\
"    {\n"\
"        ASSERT_RANGE(swap_indexes[source][0][i], 0, 15);\n"\
"        indexes0[i] = swap_indexes[source][0][i];\n"\
"    }\n"\
"    for (i = 0; i < point_count[source][1]; i++)\n"\
"    {\n"\
"        ASSERT_RANGE(swap_indexes[source][1][i], 0, 15);\n"\
"        indexes1[i] = swap_indexes[source][1][i];\n"\
"    }\n"\
"\n"\
"    set_count[0] = point_count[source][0];\n"\
"    set_count[1] = point_count[source][1];\n"\
"\n"\
"    ASSERT_RANGE(set_count[0], 0, 16);\n"\
"    ASSERT_RANGE(set_count[1], 0, 16);\n"\
"}\n"\
"\n"\
"void ETC_EncodeRGBFast(\n"\
"    int allowed_modes,\n"\
"    int is_etc2,\n"\
"    int is_ypbpr,\n"\
"    float4 *pixel,\n"\
"    __global uchar *block)\n"\
"{\n"\
"    int i, j, table, n;\n"\
"    float3 trans_pixel[16];\n"\
"    int is_delta;\n"\
"    int is_flipped;\n"\
"    etc_partition_mode_params_t params_partition;\n"\
"    etc_th_mode_params_t params_th;\n"\
"    etc_planar_mode_params_t params_planar;\n"\
"    etc_pathing_params_t pathing_params;\n"\
"    etc_partition_mode_params_t params_partition_nodelta;\n"\
"    uchar local_block[8];\n"\
"    float err[2] = {0.0f, 0.0f};\n"\
"    uchar3 partition_rgb[2][2];\n"\
"    float best_error[5] = {MAX_INIT_ERROR, MAX_INIT_ERROR, MAX_INIT_ERROR, MAX_INIT_ERROR, MAX_INIT_ERROR};\n"\
"    int best_mode = 0;\n"\
"    int found_mode = 0;\n"\
"\n"\
"    DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"    for (i = 0; i < 16; i++)\n"\
"    {\n"\
"        MEMBER(trans_pixel[i], X) = MEMBER(pixel[i], X);\n"\
"        MEMBER(trans_pixel[i], Y) = MEMBER(pixel[i], Y);\n"\
"        MEMBER(trans_pixel[i], Z) = MEMBER(pixel[i], Z);\n"\
"    }\n"\
"\n"\
"    if (allowed_modes & ETC_MODE_NODELTA)\n"\
"    {\n"\
"        for (is_flipped = 0; is_flipped < 2; is_flipped++)\n"\
"        {\n"\
"            float proj_mean[2] = {0.0f, 0.0f};\n"\
"            float x[2] = {0.0f, 0.0f};\n"\
"            float z[2] = {0.0f, 0.0f};\n"\
"\n"\
"            for (i = 0; i < 8; i++)\n"\
"            {\n"\
"                ASSERT_RANGE(g_partition_indexes[is_flipped][0][i], 0, 16);\n"\
"                ASSERT_RANGE(g_partition_indexes[is_flipped][1][i], 0, 16);\n"\
"\n"\
"                x[0] += MEMBER(trans_pixel[g_partition_indexes[is_flipped][0][i]], X);\n"\
"                x[0] -= MEMBER(trans_pixel[g_partition_indexes[is_flipped][0][i]], Y);\n"\
"                z[0] += MEMBER(trans_pixel[g_partition_indexes[is_flipped][0][i]], Z);\n"\
"                z[0] -= MEMBER(trans_pixel[g_partition_indexes[is_flipped][0][i]], Y);\n"\
"\n"\
"                x[1] += MEMBER(trans_pixel[g_partition_indexes[is_flipped][1][i]], X);\n"\
"                x[1] -= MEMBER(trans_pixel[g_partition_indexes[is_flipped][1][i]], Y);\n"\
"                z[1] += MEMBER(trans_pixel[g_partition_indexes[is_flipped][1][i]], Z);\n"\
"                z[1] -= MEMBER(trans_pixel[g_partition_indexes[is_flipped][1][i]], Y);\n"\
"            }\n"\
"\n"\
"            x[0] /= 8.0f;\n"\
"            x[1] /= 8.0f;\n"\
"            z[0] /= 8.0f;\n"\
"            z[1] /= 8.0f;\n"\
"\n"\
"            for (i = 0; i < 8; i++)\n"\
"            {\n"\
"                proj_mean[0] += dot(trans_pixel[g_partition_indexes[is_flipped][0][i]] - VFLOAT3(x[0], 0.0f, z[0]), VFLOAT3(0.57735f, 0.57735f, 0.57735f));\n"\
"                proj_mean[1] += dot(trans_pixel[g_partition_indexes[is_flipped][1][i]] - VFLOAT3(x[1], 0.0f, z[1]), VFLOAT3(0.57735f, 0.57735f, 0.57735f));\n"\
"            }\n"\
"\n"\
"            proj_mean[0] /= 8.0f;\n"\
"            proj_mean[1] /= 8.0f;\n"\
"            proj_mean[0] *= 0.57735f;\n"\
"            proj_mean[1] *= 0.57735f;\n"\
"\n"\
"            partition_rgb[is_flipped][0] = UCHAR3(clamp(x[0] + proj_mean[0], 0.0f, 255.0f), clamp(proj_mean[0], 0.0f, 255.0f), clamp(z[0] + proj_mean[0], 0.0f, 255.0f));\n"\
"            partition_rgb[is_flipped][1] = UCHAR3(clamp(x[1] + proj_mean[1], 0.0f, 255.0f), clamp(proj_mean[1], 0.0f, 255.0f), clamp(z[1] + proj_mean[1], 0.0f, 255.0f));\n"\
"\n"\
"            partition_rgb[is_flipped][0] = ETC_RGBRoundVecTo4Bit(partition_rgb[is_flipped][0]);\n"\
"            partition_rgb[is_flipped][1] = ETC_RGBRoundVecTo4Bit(partition_rgb[is_flipped][1]);\n"\
"\n"\
"            pathing_params.partition_indexes = &g_partition_indexes[is_flipped][0][0];\n"\
"            err[is_flipped] += EvaluateErrorGeneric(ETC_EVALUATEDELTAERRORGENERIC, is_ypbpr, trans_pixel, partition_rgb[is_flipped][0], &pathing_params);\n"\
"            pathing_params.partition_indexes = &g_partition_indexes[is_flipped][1][0];\n"\
"            err[is_flipped] += EvaluateErrorGeneric(ETC_EVALUATEDELTAERRORGENERIC, is_ypbpr, trans_pixel, partition_rgb[is_flipped][1], &pathing_params);\n"\
"        }\n"\
"        params_partition_nodelta.is_flipped = err[0] < err[1] ? 0 : 1;\n"\
"\n"\
"        best_error[ETC_ENC_MODE_NODELTA] = err[0] < err[1] ? err[0] : err[1];\n"\
"\n"\
"        params_partition_nodelta.rgb[0] = partition_rgb[params_partition_nodelta.is_flipped][0];\n"\
"        params_partition_nodelta.rgb[1] = partition_rgb[params_partition_nodelta.is_flipped][1];\n"\
"\n"\
"        if (!found_mode || (best_error[ETC_ENC_MODE_NODELTA] < best_error[best_mode]))\n"\
"        {\n"\
"            ETC_GetOptimalIndexes(is_ypbpr, trans_pixel, params_partition_nodelta.rgb[0], &g_partition_indexes[params_partition_nodelta.is_flipped][0][0], &params_partition_nodelta.table[0], params_partition_nodelta.indexes);\n"\
"            ETC_GetOptimalIndexes(is_ypbpr, trans_pixel, params_partition_nodelta.rgb[1], &g_partition_indexes[params_partition_nodelta.is_flipped][1][0], &params_partition_nodelta.table[1], params_partition_nodelta.indexes);\n"\
"\n"\
"            found_mode = 1;\n"\
"            best_mode = ETC_ENC_MODE_NODELTA;\n"\
"        }\n"\
"        err[0] = 0.0f;\n"\
"        err[1] = 0.0f;\n"\
"    }\n"\
"\n"\
"    if (allowed_modes & ETC_MODE_DELTA)\n"\
"    {\n"\
"        for (is_flipped = 0; is_flipped < 2; is_flipped++)\n"\
"        {\n"\
"            float proj_mean[2] = {0.0f, 0.0f};\n"\
"            float x[2] = {0.0f, 0.0f};\n"\
"            float z[2] = {0.0f, 0.0f};\n"\
"\n"\
"            for (i = 0; i < 8; i++)\n"\
"            {\n"\
"                ASSERT_RANGE(g_partition_indexes[is_flipped][0][i], 0, 16);\n"\
"                ASSERT_RANGE(g_partition_indexes[is_flipped][1][i], 0, 16);\n"\
"\n"\
"                x[0] += MEMBER(trans_pixel[g_partition_indexes[is_flipped][0][i]], X);\n"\
"                x[0] -= MEMBER(trans_pixel[g_partition_indexes[is_flipped][0][i]], Y);\n"\
"                z[0] += MEMBER(trans_pixel[g_partition_indexes[is_flipped][0][i]], Z);\n"\
"                z[0] -= MEMBER(trans_pixel[g_partition_indexes[is_flipped][0][i]], Y);\n"\
"\n"\
"                x[1] += MEMBER(trans_pixel[g_partition_indexes[is_flipped][1][i]], X);\n"\
"                x[1] -= MEMBER(trans_pixel[g_partition_indexes[is_flipped][1][i]], Y);\n"\
"                z[1] += MEMBER(trans_pixel[g_partition_indexes[is_flipped][1][i]], Z);\n"\
"                z[1] -= MEMBER(trans_pixel[g_partition_indexes[is_flipped][1][i]], Y);\n"\
"            }\n"\
"\n"\
"            x[0] /= 8.0f;\n"\
"            x[1] /= 8.0f;\n"\
"            z[0] /= 8.0f;\n"\
"            z[1] /= 8.0f;\n"\
"\n"\
"            for (i = 0; i < 8; i++)\n"\
"            {\n"\
"                proj_mean[0] += dot(trans_pixel[g_partition_indexes[is_flipped][0][i]] - VFLOAT3(x[0], 0.0f, z[0]), VFLOAT3(0.57735f, 0.57735f, 0.57735f));\n"\
"                proj_mean[1] += dot(trans_pixel[g_partition_indexes[is_flipped][1][i]] - VFLOAT3(x[1], 0.0f, z[1]), VFLOAT3(0.57735f, 0.57735f, 0.57735f));\n"\
"            }\n"\
"\n"\
"            proj_mean[0] /= 8.0f;\n"\
"            proj_mean[1] /= 8.0f;\n"\
"            proj_mean[0] *= 0.57735f;\n"\
"            proj_mean[1] *= 0.57735f;\n"\
"\n"\
"            partition_rgb[is_flipped][0] = UCHAR3(clamp(x[0] + proj_mean[0], 0.0f, 255.0f), clamp(proj_mean[0], 0.0f, 255.0f), clamp(z[0] + proj_mean[0], 0.0f, 255.0f));\n"\
"            partition_rgb[is_flipped][1] = UCHAR3(clamp(x[1] + proj_mean[1], 0.0f, 255.0f), clamp(proj_mean[1], 0.0f, 255.0f), clamp(z[1] + proj_mean[1], 0.0f, 255.0f));\n"\
"\n"\
"            partition_rgb[is_flipped][0] = ETC_RGBRoundVecTo5Bit(partition_rgb[is_flipped][0]);\n"\
"            partition_rgb[is_flipped][1] = ETC_RGBRoundVecTo5Bit(partition_rgb[is_flipped][1]);\n"\
"\n"\
"            pathing_params.partition_indexes = &g_partition_indexes[is_flipped][0][0];\n"\
"            err[is_flipped] += EvaluateErrorGeneric(ETC_EVALUATEDELTAERRORGENERIC, is_ypbpr, trans_pixel, partition_rgb[is_flipped][0], &pathing_params);\n"\
"            pathing_params.partition_indexes = &g_partition_indexes[is_flipped][1][0];\n"\
"            err[is_flipped] += EvaluateErrorGeneric(ETC_EVALUATEDELTAERRORGENERIC, is_ypbpr, trans_pixel, partition_rgb[is_flipped][1], &pathing_params);\n"\
"        }\n"\
"        params_partition.is_flipped = err[0] < err[1] ? 0 : 1;\n"\
"\n"\
"        params_partition.rgb[0] = partition_rgb[params_partition.is_flipped][0];\n"\
"        params_partition.rgb[1] = partition_rgb[params_partition.is_flipped][1];\n"\
"\n"\
"        is_delta = 0;\n"\
"        int diff = (int)((MEMBER(params_partition.rgb[1], X)) >> 3) - (int)((MEMBER(params_partition.rgb[0], X) >> 3));\n"\
"        if (diff < 4 && diff >= -4)\n"\
"            is_delta++;\n"\
"        diff = (int)((MEMBER(params_partition.rgb[1], Y)) >> 3) - (int)((MEMBER(params_partition.rgb[0], Y) >> 3));\n"\
"        if (diff < 4 && diff >= -4)\n"\
"            is_delta++;\n"\
"        diff = (int)((MEMBER(params_partition.rgb[1], Z)) >> 3) - (int)((MEMBER(params_partition.rgb[0], Z) >> 3));\n"\
"        if (diff < 4 && diff >= -4)\n"\
"            is_delta++;\n"\
"\n"\
"        if (is_delta == 3)\n"\
"        {\n"\
"            best_error[ETC_ENC_MODE_DELTA] = err[0] < err[1] ? err[0] : err[1];\n"\
"            if (!found_mode || (best_error[ETC_ENC_MODE_DELTA] < best_error[best_mode]))\n"\
"            {\n"\
"                ETC_GetOptimalIndexes(is_ypbpr, trans_pixel, params_partition.rgb[0], &g_partition_indexes[params_partition.is_flipped][0][0], &params_partition.table[0], params_partition.indexes);\n"\
"                ETC_GetOptimalIndexes(is_ypbpr, trans_pixel, params_partition.rgb[1], &g_partition_indexes[params_partition.is_flipped][1][0], &params_partition.table[1], params_partition.indexes);\n"\
"\n"\
"                found_mode = 1;\n"\
"                best_mode = ETC_ENC_MODE_DELTA;\n"\
"            }\n"\
"        }\n"\
"    }\n"\
"    if (is_etc2)\n"\
"    {\n"\
"        if (((best_error[best_mode] != 0.0f) || !found_mode) && (allowed_modes & (ETC_MODE_T | ETC_MODE_H)))\n"\
"        {\n"\
"            int set_indexes[2][16];\n"\
"            int set_count[2];\n"\
"            int best_error_flip;\n"\
"\n"\
"            ETC_KMeansTHMode(trans_pixel, &set_indexes[0][0], &set_indexes[1][0], &set_count[0]);\n"\
"\n"\
"            if (allowed_modes & ETC_MODE_T)\n"\
"            {\n"\
"                for (is_flipped = 0; is_flipped < 2; is_flipped++)\n"\
"                {\n"\
"                    float proj_mean[2] = {0.0f, 0.0f};\n"\
"                    float x[2] = {0.0f, 0.0f};\n"\
"                    float z[2] = {0.0f, 0.0f};\n"\
"\n"\
"                    for (i = 0; i < set_count[is_flipped]; i++)\n"\
"                    {\n"\
"                        ASSERT_RANGE(set_indexes[is_flipped][i], 0, 16);\n"\
"                        x[0] += MEMBER(trans_pixel[set_indexes[is_flipped][i]], X);\n"\
"                        x[0] -= MEMBER(trans_pixel[set_indexes[is_flipped][i]], Y);\n"\
"                        z[0] += MEMBER(trans_pixel[set_indexes[is_flipped][i]], Z);\n"\
"                        z[0] -= MEMBER(trans_pixel[set_indexes[is_flipped][i]], Y);\n"\
"                    }\n"\
"                    for (i = 0; i < set_count[(is_flipped + 1) % 2]; i++)\n"\
"                    {\n"\
"                        ASSERT_RANGE(set_indexes[(is_flipped + 1) % 2][i], 0, 16);\n"\
"                        x[1] += MEMBER(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]], X);\n"\
"                        x[1] -= MEMBER(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]], Y);\n"\
"                        z[1] += MEMBER(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]], Z);\n"\
"                        z[1] -= MEMBER(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]], Y);\n"\
"                    }\n"\
"\n"\
"                    x[0] /= (float)(set_count[is_flipped] == 0 ? 1 : set_count[is_flipped]);\n"\
"                    x[1] /= (float)(set_count[(is_flipped + 1) % 2] == 0 ? 1 : set_count[(is_flipped + 1) % 2]);\n"\
"                    z[0] /= (float)(set_count[is_flipped] == 0 ? 1 : set_count[is_flipped]);\n"\
"                    z[1] /= (float)(set_count[(is_flipped + 1) % 2] == 0 ? 1 : set_count[(is_flipped + 1) % 2]);\n"\
"\n"\
"                    for (i = 0; i < set_count[is_flipped]; i++)\n"\
"                        proj_mean[0] += dot(trans_pixel[set_indexes[is_flipped][i]] - VFLOAT3(x[0], 0.0f, z[0]), VFLOAT3(0.57735f, 0.57735f, 0.57735f));\n"\
"                    for (i = 0; i < set_count[(is_flipped + 1) % 2]; i++)\n"\
"                        proj_mean[1] += dot(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]] - VFLOAT3(x[1], 0.0f, z[1]), VFLOAT3(0.57735f, 0.57735f, 0.57735f));\n"\
"\n"\
"                    proj_mean[0] /= (float)(set_count[is_flipped] == 0 ? 1 : set_count[is_flipped]);\n"\
"                    proj_mean[1] /= (float)(set_count[(is_flipped + 1) % 2] == 0 ? 1 : set_count[(is_flipped + 1) % 2]);\n"\
"\n"\
"                    proj_mean[0] *= 0.57735f;\n"\
"                    proj_mean[1] *= 0.57735f;\n"\
"\n"\
"                    partition_rgb[is_flipped][0] = UCHAR3(clamp(x[0] + proj_mean[0], 0.0f, 255.0f), clamp(proj_mean[0], 0.0f, 255.0f), clamp(z[0] + proj_mean[0], 0.0f, 255.0f));\n"\
"                    partition_rgb[is_flipped][1] = UCHAR3(clamp(x[1] + proj_mean[1], 0.0f, 255.0f), clamp(proj_mean[1], 0.0f, 255.0f), clamp(z[1] + proj_mean[1], 0.0f, 255.0f));\n"\
"\n"\
"                    partition_rgb[is_flipped][0] = ETC_RGBRoundVecTo4Bit(partition_rgb[is_flipped][0]);\n"\
"                    partition_rgb[is_flipped][1] = ETC_RGBRoundVecTo4Bit(partition_rgb[is_flipped][1]);\n"\
"\n"\
"                    params_th.rgb[0] = partition_rgb[is_flipped][0];\n"\
"                    params_th.rgb[1] = partition_rgb[is_flipped][1];\n"\
"\n"\
"                    err[is_flipped] = ETC_GetOptimalTIndexes(is_ypbpr, trans_pixel, params_th.rgb[0], params_th.rgb[1], &params_th.indexes[0], &params_th.table);\n"\
"                }\n"\
"\n"\
"                best_error[ETC_ENC_MODE_T] = err[0] < err[1] ? err[0] : err[1];\n"\
"                best_error_flip = err[0] < err[1] ? 0 : 1;\n"\
"\n"\
"                params_th.rgb[0] = partition_rgb[best_error_flip][0];\n"\
"                params_th.rgb[1] = partition_rgb[best_error_flip][1];\n"\
"                ETC_GetOptimalTIndexes(is_ypbpr, trans_pixel, params_th.rgb[0], params_th.rgb[1], &params_th.indexes[0], &params_th.table);\n"\
"\n"\
"                if (!found_mode || (best_error[ETC_ENC_MODE_T] < best_error[best_mode]))\n"\
"                {\n"\
"                    found_mode = 1;\n"\
"                    best_mode = ETC_ENC_MODE_T;\n"\
"                }\n"\
"            }\n"\
"            if (allowed_modes & ETC_MODE_H)\n"\
"            {\n"\
"                int best_table[2];\n"\
"                etc_th_mode_params_t params_th_local;\n"\
"\n"\
"                for (is_flipped = 0; is_flipped < 2; is_flipped++)\n"\
"                {\n"\
"                    float proj_mean[2] = {0.0f, 0.0f};\n"\
"                    float x[2] = {0.0f, 0.0f};\n"\
"                    float z[2] = {0.0f, 0.0f};\n"\
"                    float local_best_error = MAX_INIT_ERROR;\n"\
"\n"\
"                    for (i = 0; i < set_count[is_flipped]; i++)\n"\
"                    {\n"\
"                        ASSERT_RANGE(set_indexes[is_flipped][i], 0, 16);\n"\
"                        x[0] += MEMBER(trans_pixel[set_indexes[is_flipped][i]], X);\n"\
"                        x[0] -= MEMBER(trans_pixel[set_indexes[is_flipped][i]], Y);\n"\
"                        z[0] += MEMBER(trans_pixel[set_indexes[is_flipped][i]], Z);\n"\
"                        z[0] -= MEMBER(trans_pixel[set_indexes[is_flipped][i]], Y);\n"\
"                    }\n"\
"                    for (i = 0; i < set_count[(is_flipped + 1) % 2]; i++)\n"\
"                    {\n"\
"                        ASSERT_RANGE(set_indexes[(is_flipped + 1) % 2][i], 0, 16);\n"\
"                        x[1] += MEMBER(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]], X);\n"\
"                        x[1] -= MEMBER(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]], Y);\n"\
"                        z[1] += MEMBER(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]], Z);\n"\
"                        z[1] -= MEMBER(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]], Y);\n"\
"                    }\n"\
"\n"\
"                    x[0] /= (float)(set_count[is_flipped] == 0 ? 1 : set_count[is_flipped]);\n"\
"                    x[1] /= (float)(set_count[(is_flipped + 1) % 2] == 0 ? 1 : set_count[(is_flipped + 1) % 2]);\n"\
"                    z[0] /= (float)(set_count[is_flipped] == 0 ? 1 : set_count[is_flipped]);\n"\
"                    z[1] /= (float)(set_count[(is_flipped + 1) % 2] == 0 ? 1 : set_count[(is_flipped + 1) % 2]);\n"\
"\n"\
"                    for (i = 0; i < set_count[is_flipped]; i++)\n"\
"                        proj_mean[0] += dot(trans_pixel[set_indexes[is_flipped][i]] - VFLOAT3(x[0], 0.0f, z[0]), VFLOAT3(0.57735f, 0.57735f, 0.57735f));\n"\
"                    for (i = 0; i < set_count[(is_flipped + 1) % 2]; i++)\n"\
"                        proj_mean[1] += dot(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]] - VFLOAT3(x[1], 0.0f, z[1]), VFLOAT3(0.57735f, 0.57735f, 0.57735f));\n"\
"\n"\
"                    proj_mean[0] /= (float)(set_count[is_flipped] == 0 ? 1 : set_count[is_flipped]);\n"\
"                    proj_mean[1] /= (float)(set_count[(is_flipped + 1) % 2] == 0 ? 1 : set_count[(is_flipped + 1) % 2]);\n"\
"\n"\
"                    proj_mean[0] *= 0.57735f;\n"\
"                    proj_mean[1] *= 0.57735f;\n"\
"\n"\
"                    partition_rgb[is_flipped][0] = UCHAR3(clamp(x[0] + proj_mean[0], 0.0f, 255.0f), clamp(proj_mean[0], 0.0f, 255.0f), clamp(z[0] + proj_mean[0], 0.0f, 255.0f));\n"\
"                    partition_rgb[is_flipped][1] = UCHAR3(clamp(x[1] + proj_mean[1], 0.0f, 255.0f), clamp(proj_mean[1], 0.0f, 255.0f), clamp(z[1] + proj_mean[1], 0.0f, 255.0f));\n"\
"\n"\
"                    partition_rgb[is_flipped][0] = ETC_RGBRoundVecTo4Bit(partition_rgb[is_flipped][0]);\n"\
"                    partition_rgb[is_flipped][1] = ETC_RGBRoundVecTo4Bit(partition_rgb[is_flipped][1]);\n"\
"\n"\
"                    params_th_local.rgb[0] = partition_rgb[is_flipped][0];\n"\
"                    params_th_local.rgb[1] = partition_rgb[is_flipped][1];\n"\
"\n"\
"                    for (table = 0; table < 8; table++)\n"\
"                    {\n"\
"                        float local_err = ETC_GetOptimalHIndexes(is_ypbpr, trans_pixel, params_th_local.rgb[0], params_th_local.rgb[1], &params_th_local.indexes[0], table);\n"\
"                        if (local_err < local_best_error)\n"\
"                        {\n"\
"                            best_table[is_flipped] = table;\n"\
"                            err[is_flipped] = local_err;\n"\
"                            local_best_error = local_err;\n"\
"                        }\n"\
"                    }\n"\
"                }\n"\
"\n"\
"                best_error[ETC_ENC_MODE_H] = err[0] < err[1] ? err[0] : err[1];\n"\
"                best_error_flip = err[0] < err[1] ? 0 : 1;\n"\
"\n"\
"                params_th_local.table = best_table[best_error_flip];\n"\
"                params_th_local.rgb[0] = partition_rgb[best_error_flip][0];\n"\
"                params_th_local.rgb[1] = partition_rgb[best_error_flip][1];\n"\
"                ETC_GetOptimalHIndexes(is_ypbpr, trans_pixel, params_th_local.rgb[0], params_th_local.rgb[1], &params_th_local.indexes[0], params_th_local.table);\n"\
"\n"\
"                if (!found_mode || (best_error[ETC_ENC_MODE_H] < best_error[best_mode]))\n"\
"                {\n"\
"                    found_mode = 1;\n"\
"                    best_mode = ETC_ENC_MODE_H;\n"\
"                    params_th = params_th_local;\n"\
"                }\n"\
"            }\n"\
"        }\n"\
"        if (((best_error[best_mode] != 0.0f) || !found_mode) && (allowed_modes & ETC_MODE_PLANAR))\n"\
"        {\n"\
"            // Planar mode: always check this because it's so cheap to compute\n"\
"\n"\
"            float3 points[3];\n"\
"            int3 points_i32[3];\n"\
"            float index_best_dist[3];\n"\
"            float best_dist = 0.0f;\n"\
"            int best_twiddle[3][3];\n"\
"            int index;\n"\
"            int twiddle0;\n"\
"            int twiddle1;\n"\
"            int twiddle2;\n"\
"            const float coeff[3][16] =\n"\
"            {\n"\
"                {23.0f, 17.0f, 11.0f, 5.0f, 17.0f, 11.0f, 5.0f, -1.0f, 11.0f, 5.0f, -1.0f, -7.0f, 5.0f, -1.0f, -7.0f, -13.0f},\n"\
"                {-1.0f, 9.0f, 19.0f, 29.0f, -7.0f, 3.0f, 13.0f, 23.0f, -13.0f, -3.0f, 7.0f, 17.0f, -19.0f, -9.0f, 1.0f, 11.0f},\n"\
"                {-1.0f, -7.0f, -13.0f, -19.0f, 9.0f, 3.0f, -3.0f, -9.0f, 19.0f, 13.0f, 7.0f, 1.0f, 29.0f, 23.0f, 17.0f, 11.0f}\n"\
"            };\n"\
"            DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"            points[0] = VFLOAT3(0.0f, 0.0f, 0.0f);\n"\
"            points[1] = VFLOAT3(0.0f, 0.0f, 0.0f);\n"\
"            points[2] = VFLOAT3(0.0f, 0.0f, 0.0f);\n"\
"            // TODO: this isn't trivial for the YCBCR case, just minimise in RGB space for now\n"\
"            if (is_ypbpr)\n"\
"                for (i = 0; i < 16; i++)\n"\
"                    trans_pixel[i] = clamp(ETC_ConvertToRGBf3(trans_pixel[i]), 0.0f, 255.0f);\n"\
"            for (j = 0; j < 16; j++)\n"\
"            {\n"\
"                MEMBER(points[0], X) += coeff[0][j] * MEMBER(trans_pixel[j], X);\n"\
"                MEMBER(points[1], X) += coeff[1][j] * MEMBER(trans_pixel[j], X);\n"\
"                MEMBER(points[2], X) += coeff[2][j] * MEMBER(trans_pixel[j], X);\n"\
"\n"\
"                MEMBER(points[0], Y) += coeff[0][j] * MEMBER(trans_pixel[j], Y);\n"\
"                MEMBER(points[1], Y) += coeff[1][j] * MEMBER(trans_pixel[j], Y);\n"\
"                MEMBER(points[2], Y) += coeff[2][j] * MEMBER(trans_pixel[j], Y);\n"\
"\n"\
"                MEMBER(points[0], Z) += coeff[0][j] * MEMBER(trans_pixel[j], Z);\n"\
"                MEMBER(points[1], Z) += coeff[1][j] * MEMBER(trans_pixel[j], Z);\n"\
"                MEMBER(points[2], Z) += coeff[2][j] * MEMBER(trans_pixel[j], Z);\n"\
"            }\n"\
"            points[0] = points[0] * (1.0f / 80.0f);\n"\
"            points[1] = points[1] * (1.0f / 80.0f);\n"\
"            points[2] = points[2] * (1.0f / 80.0f);\n"\
"\n"\
"            points[0] = clamp(points[0], 0.0f, 255.0f);\n"\
"            points[1] = clamp(points[1], 0.0f, 255.0f);\n"\
"            points[2] = clamp(points[2], 0.0f, 255.0f);\n"\
"\n"\
"            points_i32[0] = INT3(ETC_RGBRoundTo6Bit((uchar)MEMBER(points[0], X)), ETC_RGBRoundTo7Bit((uchar)MEMBER(points[0], Y)), ETC_RGBRoundTo6Bit((uchar)MEMBER(points[0], Z)));\n"\
"            points_i32[1] = INT3(ETC_RGBRoundTo6Bit((uchar)MEMBER(points[1], X)), ETC_RGBRoundTo7Bit((uchar)MEMBER(points[1], Y)), ETC_RGBRoundTo6Bit((uchar)MEMBER(points[1], Z)));\n"\
"            points_i32[2] = INT3(ETC_RGBRoundTo6Bit((uchar)MEMBER(points[2], X)), ETC_RGBRoundTo7Bit((uchar)MEMBER(points[2], Y)), ETC_RGBRoundTo6Bit((uchar)MEMBER(points[2], Z)));\n"\
"            for (index = 0; index < 3; index++)\n"\
"                index_best_dist[index] = MAX_INIT_ERROR;\n"\
"\n"\
"            for (twiddle0 = -1; twiddle0 <= 1; twiddle0++)\n"\
"            {\n"\
"                for (twiddle1 = -1; twiddle1 <= 1; twiddle1++)\n"\
"                {\n"\
"                    for (twiddle2 = -1; twiddle2 <= 1; twiddle2++)\n"\
"                    {\n"\
"                        int ppoints[3][3];\n"\
"                        float comp_err[3];\n"\
"                        int comb;\n"\
"\n"\
"                        comb =  (MEMBER(points_i32[0], X) + twiddle0 * 4) | (MEMBER(points_i32[1], X) + twiddle1 * 4) | (MEMBER(points_i32[2], X) + twiddle2 * 4) |\n"\
"                            (MEMBER(points_i32[0], Y) + twiddle0 * 2) | (MEMBER(points_i32[1], Y) + twiddle1 * 2) | (MEMBER(points_i32[2], Y) + twiddle2 * 2) |\n"\
"                            (MEMBER(points_i32[0], Z) + twiddle0 * 4) | (MEMBER(points_i32[1], Z) + twiddle1 * 4) | (MEMBER(points_i32[2], Z) + twiddle2 * 4);\n"\
"\n"\
"                        // trick: this tests if any of the values has negative sign or is >255, halving the number of comparisons needed\n"\
"                        if (comb & 0xFFFFFF00)\n"\
"                            continue;\n"\
"\n"\
"                        ppoints[0][0] = ETC_RGBRoundTo6Bit((MEMBER(points_i32[0], X) + twiddle0 * 4));\n"\
"                        ppoints[0][1] = ETC_RGBRoundTo6Bit((MEMBER(points_i32[1], X) + twiddle1 * 4));\n"\
"                        ppoints[0][2] = ETC_RGBRoundTo6Bit((MEMBER(points_i32[2], X) + twiddle2 * 4));\n"\
"\n"\
"                        ppoints[1][0] = ETC_RGBRoundTo7Bit((MEMBER(points_i32[0], Y) + twiddle0 * 2));\n"\
"                        ppoints[1][1] = ETC_RGBRoundTo7Bit((MEMBER(points_i32[1], Y) + twiddle1 * 2));\n"\
"                        ppoints[1][2] = ETC_RGBRoundTo7Bit((MEMBER(points_i32[2], Y) + twiddle2 * 2));\n"\
"\n"\
"                        ppoints[2][0] = ETC_RGBRoundTo6Bit((MEMBER(points_i32[0], Z) + twiddle0 * 4));\n"\
"                        ppoints[2][1] = ETC_RGBRoundTo6Bit((MEMBER(points_i32[1], Z) + twiddle1 * 4));\n"\
"                        ppoints[2][2] = ETC_RGBRoundTo6Bit((MEMBER(points_i32[2], Z) + twiddle2 * 4));\n"\
"\n"\
"                        comp_err[0] = 0.0f;\n"\
"                        comp_err[1] = 0.0f;\n"\
"                        comp_err[2] = 0.0f;\n"\
"\n"\
"                        for (j = 0; j < 4; j++) // v\n"\
"                        {\n"\
"                            for (i = 0; i < 4; i++) // u\n"\
"                            {\n"\
"                                float3 v;\n"\
"\n"\
"                                MEMBER(v, X) = (float)((i * (ppoints[0][1] - ppoints[0][0]) + j * (ppoints[0][2] - ppoints[0][0]) + 4 * (ppoints[0][0]) + 2) >> 2);\n"\
"                                MEMBER(v, Y) = (float)((i * (ppoints[1][1] - ppoints[1][0]) + j * (ppoints[1][2] - ppoints[1][0]) + 4 * (ppoints[1][0]) + 2) >> 2);\n"\
"                                MEMBER(v, Z) = (float)((i * (ppoints[2][1] - ppoints[2][0]) + j * (ppoints[2][2] - ppoints[2][0]) + 4 * (ppoints[2][0]) + 2) >> 2);\n"\
"\n"\
"                                v = clamp(v, VFLOAT3(0.0f, 0.0f, 0.0f), VFLOAT3(255.0f, 255.0f, 255.0f));\n"\
"                                v = v - trans_pixel[j*4 + i];\n"\
"\n"\
"                                comp_err[0] += MEMBER(v, X) * MEMBER(v, X);\n"\
"                                comp_err[1] += MEMBER(v, Y) * MEMBER(v, Y);\n"\
"                                comp_err[2] += MEMBER(v, Z) * MEMBER(v, Z);\n"\
"                            }\n"\
"                        }\n"\
"                        for (index = 0; index < 3; index++)\n"\
"                        {\n"\
"                            if (comp_err[index] < index_best_dist[index])\n"\
"                            {\n"\
"                                int scale = (index == 1 ? 2 : 4);\n"\
"                                best_twiddle[index][0] = twiddle0 * scale;\n"\
"                                best_twiddle[index][1] = twiddle1 * scale;\n"\
"                                best_twiddle[index][2] = twiddle2 * scale;\n"\
"                                index_best_dist[index] = comp_err[index];\n"\
"                            }\n"\
"                        }\n"\
"                    }\n"\
"                }\n"\
"            }\n"\
"\n"\
"            best_error[ETC_ENC_MODE_PLANAR] = index_best_dist[0] + index_best_dist[1] + index_best_dist[2];\n"\
"\n"\
"            if (!found_mode || (best_error[ETC_ENC_MODE_PLANAR] < best_error[best_mode]))\n"\
"            {\n"\
"                found_mode = 1;\n"\
"                best_mode = ETC_ENC_MODE_PLANAR;\n"\
"\n"\
"                params_planar.rgb[0] = UCHAR3(ETC_RGBRoundTo6Bit(MEMBER(points_i32[0], X) + best_twiddle[0][0]), ETC_RGBRoundTo7Bit(MEMBER(points_i32[0], Y) + best_twiddle[1][0]), ETC_RGBRoundTo6Bit(MEMBER(points_i32[0], Z) + best_twiddle[2][0]));\n"\
"                params_planar.rgb[1] = UCHAR3(ETC_RGBRoundTo6Bit(MEMBER(points_i32[1], X) + best_twiddle[0][1]), ETC_RGBRoundTo7Bit(MEMBER(points_i32[1], Y) + best_twiddle[1][1]), ETC_RGBRoundTo6Bit(MEMBER(points_i32[1], Z) + best_twiddle[2][1]));\n"\
"                params_planar.rgb[2] = UCHAR3(ETC_RGBRoundTo6Bit(MEMBER(points_i32[2], X) + best_twiddle[0][2]), ETC_RGBRoundTo7Bit(MEMBER(points_i32[2], Y) + best_twiddle[1][2]), ETC_RGBRoundTo6Bit(MEMBER(points_i32[2], Z) + best_twiddle[2][2]));\n"\
"            }\n"\
"        }\n"\
"    }\n"\
"    //printf(\"err: %i: %f %f %f %f %f\\n\", best_mode, best_error[0], best_error[1], best_error[2], best_error[3], best_error[4]);\n"\
"\n"\
"    if (best_mode == ETC_ENC_MODE_DELTA)\n"\
"    {\n"\
"        int3 diff;\n"\
"\n"\
"        MEMBER(diff, X) = (MEMBER(params_partition.rgb[1], X) >> 3) - (MEMBER(params_partition.rgb[0], X) >> 3);\n"\
"        MEMBER(diff, Y) = (MEMBER(params_partition.rgb[1], Y) >> 3) - (MEMBER(params_partition.rgb[0], Y) >> 3);\n"\
"        MEMBER(diff, Z) = (MEMBER(params_partition.rgb[1], Z) >> 3) - (MEMBER(params_partition.rgb[0], Z) >> 3);\n"\
"\n"\
"        ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], X) >> 3, 27, 5);\n"\
"        ETC_WriteBits(local_block, MEMBER(diff, X) >> 0, 24, 3);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], Y) >> 3, 19, 5);\n"\
"        ETC_WriteBits(local_block, MEMBER(diff, Y) >> 0, 16, 3);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], Z) >> 3, 11, 5);\n"\
"        ETC_WriteBits(local_block, MEMBER(diff, Z) >> 0,  8, 3);\n"\
"        ETC_WriteBits(local_block, 1, 1, 1); // diff bit\n"\
"\n"\
"        ETC_WriteBits(local_block, params_partition.table[0], 5, 3); // table codeword 1\n"\
"        ETC_WriteBits(local_block, params_partition.table[1], 2, 3); // table codeword 2\n"\
"        ETC_WriteBits(local_block, params_partition.is_flipped, 0, 1); // flip bit\n"\
"\n"\
"        for (i = 0; i < 16; i++)\n"\
"        {\n"\
"            int index = (i%4)*4 + i/4;\n"\
"\n"\
"            int idx = params_partition.indexes[i];\n"\
"\n"\
"            ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);\n"\
"            ETC_WriteBits(local_block, idx & 1, 32 + index, 1);\n"\
"\n"\
"        }\n"\
"        ETC_PackBlockSwapOrder(block, local_block);\n"\
"    }\n"\
"    else if (best_mode == ETC_ENC_MODE_NODELTA)\n"\
"    {\n"\
"        ETC_WriteBits(local_block, MEMBER(params_partition_nodelta.rgb[0], X) >> 4, 28, 4);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_partition_nodelta.rgb[1], X) >> 4, 24, 4);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_partition_nodelta.rgb[0], Y) >> 4, 20, 4);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_partition_nodelta.rgb[1], Y) >> 4, 16, 4);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_partition_nodelta.rgb[0], Z) >> 4, 12, 4);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_partition_nodelta.rgb[1], Z) >> 4,  8, 4);\n"\
"        ETC_WriteBits(local_block, 0, 1, 1); // diff bit\n"\
"\n"\
"        ETC_WriteBits(local_block, params_partition_nodelta.table[0], 5, 3); // table codeword 1\n"\
"        ETC_WriteBits(local_block, params_partition_nodelta.table[1], 2, 3); // table codeword 2\n"\
"        ETC_WriteBits(local_block, params_partition_nodelta.is_flipped, 0, 1); // flip bit\n"\
"\n"\
"        for (i = 0; i < 16; i++)\n"\
"        {\n"\
"            int index = (i%4)*4 + i/4;\n"\
"\n"\
"            int idx = params_partition_nodelta.indexes[i];\n"\
"\n"\
"            ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);\n"\
"            ETC_WriteBits(local_block, idx & 1, 32 + index, 1);\n"\
"\n"\
"        }\n"\
"        ETC_PackBlockSwapOrder(block, local_block);\n"\
"    }\n"\
"    else if (best_mode == ETC_ENC_MODE_T)\n"\
"    {\n"\
"        int min_rd = -4 + ((MEMBER(params_th.rgb[0], X) >> 4) & 3);\n"\
"        int max_rd = ((MEMBER(params_th.rgb[0], X) >> 4) & 3);\n"\
"        int min_r = (MEMBER(params_th.rgb[0], X) >> 6) & 3;\n"\
"        int max_r = 28 + min_r;\n"\
"        uchar r;\n"\
"        uchar rd;\n"\
"\n"\
"        if (min_rd + min_r < 0)\n"\
"        {\n"\
"            r = min_r;\n"\
"            rd = min_rd;\n"\
"        }\n"\
"        else\n"\
"        {\n"\
"            r = max_r;\n"\
"            rd = max_rd;\n"\
"        }\n"\
"        //printf(\"err: %i: params_th.rgb[0|2] %3u %3u %3u, %3u %3u %3u, table: %i\\n\", best_mode, MEMBER(params_th.rgb[0], X), MEMBER(params_th.rgb[0], Y), MEMBER(params_th.rgb[0], Z), MEMBER(params_th.rgb[1], X), MEMBER(params_th.rgb[1], Y), MEMBER(params_th.rgb[1], Z), params_th.table);\n"\
"\n"\
"        //printf(\"min_rd, min_r, r, rd: %i %i %i %i\\n\", min_rd, min_r, r, rd);\n"\
"        ETC_WriteBits(local_block, r, 27, 5);\n"\
"        ETC_WriteBits(local_block, rd, 24, 3);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Y) >> 4, 20, 4);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Z) >> 4, 16, 4);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], X) >> 4, 12, 4);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Y) >> 4,  8, 4);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Z) >> 4,  4, 4);\n"\
"\n"\
"        ETC_WriteBits(local_block, (params_th.table >> 1) & 3, 2, 2);\n"\
"        ETC_WriteBits(local_block, 1, 1, 1); // diff bit\n"\
"        ETC_WriteBits(local_block, params_th.table & 1, 0, 1); // flip bit\n"\
"\n"\
"        for (i = 0; i < 16; i++)\n"\
"        {\n"\
"            int index = (i % 4) * 4 + i / 4;\n"\
"\n"\
"            int idx = params_th.indexes[i];\n"\
"\n"\
"            //printf(\"%i: (%i)\\n\", i, params_th.indexes[i]);\n"\
"\n"\
"            ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);\n"\
"            ETC_WriteBits(local_block, idx & 1, 32 + index, 1);\n"\
"\n"\
"        }\n"\
"        ETC_PackBlockSwapOrder(block, local_block);\n"\
"        //printf(\"0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X\\n\", block[0], block[1], block[2], block[3], block[4], block[5], block[6], block[7]);\n"\
"    }\n"\
"    else if (best_mode == ETC_ENC_MODE_H)\n"\
"    {\n"\
"        int min_gd = -4 + ((MEMBER(params_th.rgb[0], Z) >> 5) & 3);\n"\
"        int max_gd = ((MEMBER(params_th.rgb[0], Z) >> 5) & 3);\n"\
"        int min_g = ((MEMBER(params_th.rgb[0], Z) >> 7) & 1) | (((MEMBER(params_th.rgb[0], Y) >> 4) & 1) << 1);\n"\
"        int max_g = 28 + min_g;\n"\
"        uchar g;\n"\
"        uchar gd;\n"\
"        int rd;\n"\
"        if (min_gd + min_g < 0)\n"\
"        {\n"\
"            g = min_g;\n"\
"            gd = min_gd;\n"\
"        }\n"\
"        else\n"\
"        {\n"\
"            g = max_g;\n"\
"            gd = max_gd;\n"\
"        }\n"\
"\n"\
"        rd = MEMBER(params_th.rgb[0], Y) >> 5;\n"\
"        if (rd >= 4)\n"\
"            rd = -4 + (rd & 3);\n"\
"\n"\
"        if ((int)(MEMBER(params_th.rgb[0], X) >> 4) + rd < 0)\n"\
"            ETC_WriteBits(local_block, 1, 31, 1);\n"\
"        else\n"\
"            ETC_WriteBits(local_block, 0, 31, 1);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], X) >> 4, 27, 4);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Y) >> 5, 24, 3);\n"\
"        ETC_WriteBits(local_block, g, 19, 5);\n"\
"        ETC_WriteBits(local_block, gd, 16, 3);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Z) >> 4, 15, 1);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], X) >> 4, 11, 4);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Y) >> 4,  7, 4);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Z) >> 4,  3, 4);\n"\
"\n"\
"        ETC_WriteBits(local_block, (params_th.table >> 2) & 1, 2, 1);\n"\
"        ETC_WriteBits(local_block, 1, 1, 1); // diff bit\n"\
"        ETC_WriteBits(local_block, (params_th.table >> 1) & 1 & 1, 0, 1); // flip bit\n"\
"\n"\
"        for (i = 0; i < 16; i++)\n"\
"        {\n"\
"            int index = (i % 4) * 4 + i / 4;\n"\
"\n"\
"            int idx = params_th.indexes[i];\n"\
"\n"\
"            ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);\n"\
"            ETC_WriteBits(local_block, idx & 1, 32 + index, 1);\n"\
"\n"\
"        }\n"\
"        ETC_PackBlockSwapOrder(block, local_block);\n"\
"    }\n"\
"    else if (best_mode == ETC_ENC_MODE_PLANAR)\n"\
"    {\n"\
"        int r, g, b;\n"\
"        int rd, gd, bd;\n"\
"        int min_bd;\n"\
"        int max_bd;\n"\
"        int min_b;\n"\
"        int max_b;\n"\
"        MEMBER(params_planar.rgb[0], X) >>= 2;\n"\
"        MEMBER(params_planar.rgb[0], Y) >>= 1;\n"\
"        MEMBER(params_planar.rgb[0], Z) >>= 2;\n"\
"\n"\
"        MEMBER(params_planar.rgb[1], X) >>= 2;\n"\
"        MEMBER(params_planar.rgb[1], Y) >>= 1;\n"\
"        MEMBER(params_planar.rgb[1], Z) >>= 2;\n"\
"\n"\
"        MEMBER(params_planar.rgb[2], X) >>= 2;\n"\
"        MEMBER(params_planar.rgb[2], Y) >>= 1;\n"\
"        MEMBER(params_planar.rgb[2], Z) >>= 2;\n"\
"\n"\
"        ETC_WriteBits(local_block, MEMBER(params_planar.rgb[2], Z), 32, 6);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_planar.rgb[2], Y), 38, 7);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_planar.rgb[2], X), 45, 6);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_planar.rgb[1], Z), 51, 6);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_planar.rgb[1], Y), 57, 7);\n"\
"\n"\
"        ETC_WriteBits(local_block, (MEMBER(params_planar.rgb[1], X)) & 1, 0, 1);\n"\
"        ETC_WriteBits(local_block, 1, 1, 1);\n"\
"        ETC_WriteBits(local_block, (MEMBER(params_planar.rgb[1], X) >> 1) & 31, 2, 5);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_planar.rgb[0], Z) & 7, 7, 3);\n"\
"        ETC_WriteBits(local_block, (MEMBER(params_planar.rgb[0], Z) >> 3) & 7, 11, 2);\n"\
"        ETC_WriteBits(local_block, (MEMBER(params_planar.rgb[0], Z) >> 5) & 1, 16, 1);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_planar.rgb[0], Y) & 63, 17, 6);\n"\
"        ETC_WriteBits(local_block, (MEMBER(params_planar.rgb[0], Y) >> 6) & 1, 24, 1);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_planar.rgb[0], X), 25, 6);\n"\
"\n"\
"        r = (MEMBER(params_planar.rgb[0], X) >> 2) & 63;\n"\
"        rd = (MEMBER(params_planar.rgb[0], Y) >> 6) | ((MEMBER(params_planar.rgb[0], X) & 3) << 1);\n"\
"        g = (MEMBER(params_planar.rgb[0], Y) >> 2) & 15;\n"\
"        gd = (MEMBER(params_planar.rgb[0], Z) >> 5) | ((MEMBER(params_planar.rgb[0], Y) & 3) << 1);\n"\
"        b = (MEMBER(params_planar.rgb[0], Z) >> 3) & 3;\n"\
"        bd = (MEMBER(params_planar.rgb[0], Z) >> 1) & 3;\n"\
"\n"\
"        if (rd >= 4)\n"\
"            rd = -4 + (rd & 3);\n"\
"        if (gd >= 4)\n"\
"            gd = -4 + (gd & 3);\n"\
"        if (bd >= 4)\n"\
"            bd = -4 + (bd & 3);\n"\
"\n"\
"        if (r + rd < 0)\n"\
"            ETC_WriteBits(local_block, 1, 31, 1);\n"\
"        else\n"\
"            ETC_WriteBits(local_block, 0, 31, 1);\n"\
"\n"\
"        if (g + gd < 0)\n"\
"            ETC_WriteBits(local_block, 1, 23, 1);\n"\
"        else\n"\
"            ETC_WriteBits(local_block, 0, 23, 1);\n"\
"\n"\
"        min_bd = -4 + bd;\n"\
"        max_bd = bd;\n"\
"        min_b = b;\n"\
"        max_b = 28 + min_b;\n"\
"\n"\
"        if (min_b + min_bd < 0)\n"\
"        {\n"\
"            ETC_WriteBits(local_block, min_bd, 8, 3);\n"\
"            ETC_WriteBits(local_block, min_b, 11, 5);\n"\
"        }\n"\
"        else\n"\
"        {\n"\
"            ETC_WriteBits(local_block, max_bd, 8, 3);\n"\
"            ETC_WriteBits(local_block, max_b, 11, 5);\n"\
"        }\n"\
"        ETC_PackBlockSwapOrder(block, local_block);\n"\
"    }\n"\
"}\n"\
"\n"\
"void ETC_EncodeRGBQuality(\n"\
"    int quality,\n"\
"    int allowed_modes,\n"\
"    float error_target,\n"\
"    int refine_search,\n"\
"    int is_etc2,\n"\
"    int is_ypbpr,\n"\
"    float4 *pixel,\n"\
"    __global uchar *block)\n"\
"{\n"\
"    int i, j, table, n;\n"\
"    float3 trans_pixel[16];\n"\
"    int is_delta;\n"\
"    int is_flipped;\n"\
"    float best_dist[2];\n"\
"    etc_sample_t sample_list[SAMPLE_LIST_SIZE0][SAMPLE_LIST_SIZE1][SAMPLE_LIST_SIZE2];\n"\
"    int flipped;\n"\
"    int partition;\n"\
"    int is_best_delta = 0;\n"\
"    float best_total_error = MAX_INIT_ERROR;\n"\
"    int enc_mode;\n"\
"    etc_partition_mode_params_t params_partition;\n"\
"    etc_th_mode_params_t params_th;\n"\
"    etc_planar_mode_params_t params_planar;\n"\
"    etc_pathing_params_t pathing_params;\n"\
"    uchar local_block[8];\n"\
"    int step = 1;\n"\
"    float3 projected_mins[2][2]; // delta/non-delta, flipped, partition\n"\
"    float3 projected_maxs[2][2];\n"\
"\n"\
"    //if (quality == CODEC_QUALITY_NORMAL)\n"\
"        //step = 1;\n"\
"\n"\
"    DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"    for (i = 0; i < 16; i++)\n"\
"    {\n"\
"        MEMBER(trans_pixel[i], X) = MEMBER(pixel[i], X);\n"\
"        MEMBER(trans_pixel[i], Y) = MEMBER(pixel[i], Y);\n"\
"        MEMBER(trans_pixel[i], Z) = MEMBER(pixel[i], Z);\n"\
"    }\n"\
"    DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"    for (flipped = 0; flipped < 2; flipped++)\n"\
"    {\n"\
"        for (partition = 0; partition < 2; partition++)\n"\
"        {\n"\
"            float3 mean = VFLOAT3(0.0f, 0.0f, 0.0f);\n"\
"            float mins_maxs_dist[2];\n"\
"            float3 temp;\n"\
"            \n"\
"            for (i = 0; i < 8; i++)\n"\
"                mean = mean + trans_pixel[g_partition_indexes[flipped][partition][i]];\n"\
"\n"\
"            mean = mean / 8.0f;\n"\
"            \n"\
"            mins_maxs_dist[0] = dot(trans_pixel[g_partition_indexes[flipped][partition][0]] - mean, VFLOAT3(0.57735f, 0.57735f, 0.57735f));\n"\
"            mins_maxs_dist[1] = mins_maxs_dist[0];\n"\
"            \n"\
"            for (i = 1; i < 8; i++)\n"\
"            {\n"\
"                float dist = dot(trans_pixel[g_partition_indexes[flipped][partition][i]] - mean, VFLOAT3(0.57735f, 0.57735f, 0.57735f));\n"\
"\n"\
"                if (dist < mins_maxs_dist[0])\n"\
"                    mins_maxs_dist[0] = dist;\n"\
"                if (dist > mins_maxs_dist[1])\n"\
"                    mins_maxs_dist[1] = dist;\n"\
"            }\n"\
"            projected_mins[flipped][partition] = mean + VFLOAT3(0.57735f, 0.57735f, 0.57735f) * mins_maxs_dist[0];\n"\
"            projected_maxs[flipped][partition] = mean + VFLOAT3(0.57735f, 0.57735f, 0.57735f) * mins_maxs_dist[1];\n"\
"        }\n"\
"    }\n"\
"    if (is_ypbpr)\n"\
"        for (i = 0; i < 16; i++)\n"\
"            trans_pixel[i] = ETC_ConvertToYPBPRf3(trans_pixel[i]);\n"\
"    DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"    if (allowed_modes & ETC_MODE_DELTA)\n"\
"    {\n"\
"        float3 mean[2][2];\n"\
"        uchar3 mean_quant[2][2];\n"\
"        int min_index[2][2];\n"\
"        int max_index[2][2];\n"\
"        float fixed_err = MAX_INIT_ERROR;\n"\
"        uchar3 best_positions[2];\n"\
"        int best_flipped = 0;\n"\
"        int found_fixed = 0;\n"\
"        uchar3 proj_mins;\n"\
"        uchar3 proj_maxs;\n"\
"        int fixed_flip = 0;\n"\
"#if 1\n"\
"        if (quality >= CODEC_QUALITY_NORMAL) // redundant, quality is always normal or better in this function\n"\
"        {\n"\
"            int max_distance;\n"\
"\n"\
"            if (quality == CODEC_QUALITY_BEST)\n"\
"                max_distance = 255;\n"\
"            else if (quality == CODEC_QUALITY_HIGH)\n"\
"                max_distance = 8;\n"\
"            else \n"\
"                max_distance = 1;\n"\
"\n"\
"            for (flipped = 0; flipped < 2; flipped++)\n"\
"            {\n"\
"                for (partition = 0; partition < 2; partition++)\n"\
"                {\n"\
"                    int distance = 0;\n"\
"                    mean[flipped][partition] = VFLOAT3(0.0f, 0.0f, 0.0f);\n"\
"                    for (i = 0; i < 8; i++)\n"\
"                    {\n"\
"                        mean[flipped][partition] = mean[flipped][partition] + trans_pixel[g_partition_indexes[flipped][partition][i]];\n"\
"                    }\n"\
"                    mean[flipped][partition] = mean[flipped][partition] / 8.0f;\n"\
"\n"\
"                    MEMBER(mean_quant[flipped][partition], X) = UCHAR(MEMBER(mean[flipped][partition], X)) >> 3;\n"\
"                    MEMBER(mean_quant[flipped][partition], Y) = UCHAR(MEMBER(mean[flipped][partition], Y)) >> 3;\n"\
"                    MEMBER(mean_quant[flipped][partition], Z) = UCHAR(MEMBER(mean[flipped][partition], Z)) >> 3;\n"\
"\n"\
"                    min_index[flipped][partition] = 0;\n"\
"                    max_index[flipped][partition] = 0;\n"\
"\n"\
"                    while ( ((int)MEMBER(mean_quant[flipped][partition], X) + min_index[flipped][partition] > 0) &&\n"\
"                            ((int)MEMBER(mean_quant[flipped][partition], Y) + min_index[flipped][partition] > 0) &&\n"\
"                            ((int)MEMBER(mean_quant[flipped][partition], Z) + min_index[flipped][partition] > 0))\n"\
"                    {\n"\
"                        min_index[flipped][partition]--;\n"\
"                        distance++;\n"\
"                        if (distance > max_distance)\n"\
"                            break;\n"\
"                    }\n"\
"                    distance = 0;\n"\
"                    while ( ((int)MEMBER(mean_quant[flipped][partition], X) + max_index[flipped][partition] < 31) &&\n"\
"                            ((int)MEMBER(mean_quant[flipped][partition], Y) + max_index[flipped][partition] < 31) &&\n"\
"                            ((int)MEMBER(mean_quant[flipped][partition], Z) + max_index[flipped][partition] < 31))\n"\
"                    {\n"\
"                        max_index[flipped][partition]++;\n"\
"                        distance++;\n"\
"                        if (distance > max_distance)\n"\
"                            break;\n"\
"                    }\n"\
"                }\n"\
"            }\n"\
"            for (flipped = 0; flipped < 2; flipped++)\n"\
"            {\n"\
"                int ip0;\n"\
"                int ip1;\n"\
"                for (ip0 = min_index[flipped][0]; ip0 <= max_index[flipped][0]; ip0++)\n"\
"                {\n"\
"                    uchar3 l0_quant;\n"\
"\n"\
"                    MEMBER(l0_quant, X) = MEMBER(mean_quant[flipped][0], X) + ip0;\n"\
"                    MEMBER(l0_quant, Y) = MEMBER(mean_quant[flipped][0], Y) + ip0;\n"\
"                    MEMBER(l0_quant, Z) = MEMBER(mean_quant[flipped][0], Z) + ip0;\n"\
"\n"\
"                    for (ip1 = min_index[flipped][1]; ip1 <= max_index[flipped][1]; ip1++)\n"\
"                    {\n"\
"                        uchar3 l1_quant;\n"\
"                        int dist[3];\n"\
"                        float local_error;\n"\
"\n"\
"                        MEMBER(l1_quant, X) = MEMBER(mean_quant[flipped][1], X) + ip1;\n"\
"                        MEMBER(l1_quant, Y) = MEMBER(mean_quant[flipped][1], Y) + ip1;\n"\
"                        MEMBER(l1_quant, Z) = MEMBER(mean_quant[flipped][1], Z) + ip1;\n"\
"\n"\
"                        dist[0] = (int)MEMBER(l1_quant, X) - (int)MEMBER(l0_quant, X);\n"\
"                        dist[1] = (int)MEMBER(l1_quant, Y) - (int)MEMBER(l0_quant, Y);\n"\
"                        dist[2] = (int)MEMBER(l1_quant, Z) - (int)MEMBER(l0_quant, Z);\n"\
"\n"\
"                        if ((dist[0] < -4 || dist[0] > 3) || \n"\
"                            (dist[1] < -4 || dist[1] > 3) || \n"\
"                            (dist[2] < -4 || dist[2] > 3))\n"\
"                            continue;\n"\
"\n"\
"                        local_error = ETC_EvaluateError(is_ypbpr, trans_pixel, ETC_RGBExpandVecTo5Bit(l0_quant), &g_partition_indexes[flipped][0][0]);\n"\
"                        local_error += ETC_EvaluateError(is_ypbpr, trans_pixel, ETC_RGBExpandVecTo5Bit(l1_quant), &g_partition_indexes[flipped][1][0]);\n"\
"\n"\
"                        if (local_error < fixed_err)\n"\
"                        {\n"\
"                            fixed_err = local_error;\n"\
"                            best_positions[0] = l0_quant;\n"\
"                            best_positions[1] = l1_quant;\n"\
"                            best_flipped = flipped;\n"\
"                            found_fixed = 1;\n"\
"                        }\n"\
"                    }\n"\
"                }\n"\
"            }\n"\
"            if (found_fixed)\n"\
"            {\n"\
"                uchar3 best_pos[2];\n"\
"                float combined_err = 0.0f;\n"\
"\n"\
"                best_pos[0] = best_positions[0];\n"\
"                best_pos[1] = best_positions[1];\n"\
"\n"\
"                for (partition = 0; partition < 2; partition++)\n"\
"                {\n"\
"                    int neighbourhood_width = (quality == CODEC_QUALITY_BEST ? 3 : 1);\n"\
"                    float best_err = MAX_INIT_ERROR;\n"\
"                    int x;\n"\
"                    int y;\n"\
"                    int z;\n"\
"                    int min_x = MEMBER(best_positions[partition], X) > (neighbourhood_width - 1) ? MEMBER(best_positions[partition], X) - neighbourhood_width : 0;\n"\
"                    int min_y = MEMBER(best_positions[partition], Y) > (neighbourhood_width - 1) ? MEMBER(best_positions[partition], Y) - neighbourhood_width : 0;\n"\
"                    int min_z = MEMBER(best_positions[partition], Z) > (neighbourhood_width - 1) ? MEMBER(best_positions[partition], Z) - neighbourhood_width : 0;\n"\
"                    int max_x = MEMBER(best_positions[partition], X) < (31 - neighbourhood_width) ? MEMBER(best_positions[partition], X) + neighbourhood_width : 31;\n"\
"                    int max_y = MEMBER(best_positions[partition], Y) < (31 - neighbourhood_width) ? MEMBER(best_positions[partition], Y) + neighbourhood_width : 31;\n"\
"                    int max_z = MEMBER(best_positions[partition], Z) < (31 - neighbourhood_width) ? MEMBER(best_positions[partition], Z) + neighbourhood_width : 31;\n"\
"\n"\
"                    for (z = min_z; z <= max_z; z++)\n"\
"                        for (y = min_y; y <= max_y; y++)\n"\
"                            for (x = min_x; x <= max_x; x++)\n"\
"                            {\n"\
"                                uchar3 pos = UCHAR3(x, y, z);\n"\
"                                float err;\n"\
"                                int dist[3];\n"\
"\n"\
"                                dist[0] = (int)MEMBER(pos, X) - (int)MEMBER(best_pos[partition ? 0 : 1], X);\n"\
"                                dist[1] = (int)MEMBER(pos, Y) - (int)MEMBER(best_pos[partition ? 0 : 1], Y);\n"\
"                                dist[2] = (int)MEMBER(pos, Z) - (int)MEMBER(best_pos[partition ? 0 : 1], Z);\n"\
"\n"\
"                                if ((dist[0] < -4 || dist[0] > 3) || \n"\
"                                    (dist[1] < -4 || dist[1] > 3) || \n"\
"                                    (dist[2] < -4 || dist[2] > 3))\n"\
"                                    continue;\n"\
"\n"\
"                                pos = ETC_RGBExpandVecTo5Bit(pos);\n"\
"                                err = ETC_EvaluateError(is_ypbpr, trans_pixel, pos, &g_partition_indexes[best_flipped][partition][0]);\n"\
"\n"\
"                                if (err < best_err)\n"\
"                                {\n"\
"                                    best_pos[partition] = UCHAR3(x, y, z);\n"\
"                                    best_err = err;\n"\
"                                }\n"\
"                            }\n"\
"                    combined_err += best_err;\n"\
"                }\n"\
"\n"\
"                if (combined_err < fixed_err)\n"\
"                {\n"\
"                    best_positions[0] = best_pos[0];\n"\
"                    best_positions[1] = best_pos[1];\n"\
"                    fixed_err = combined_err;\n"\
"                }\n"\
"            }\n"\
"        }\n"\
"#endif\n"\
"\n"\
"        DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"        ETC_PrepareSampleList(SAMPLE_LIST_SIZE2, sample_list);\n"\
"        DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"        for (flipped = 0; flipped < 2; flipped++)\n"\
"        {\n"\
"            for (partition = 0; partition < 2; partition++)\n"\
"            {\n"\
"                etc_sample_t sample;\n"\
"\n"\
"                float offset = 0.0f;\n"\
"\n"\
"                if (quality == CODEC_QUALITY_NORMAL)\n"\
"                    offset = 0.0f;\n"\
"                else if (quality > CODEC_QUALITY_NORMAL) // searching entire space on BEST tends to give values that can't be represented by delta encodings\n"\
"                    offset = 24.0f;\n"\
"\n"\
"                MEMBER(proj_mins, X) = ((uint)clamp(MEMBER(projected_mins[flipped][partition], X) - offset, 0.0f, 255.0f)) >> 3;\n"\
"                MEMBER(proj_mins, Y) = ((uint)clamp(MEMBER(projected_mins[flipped][partition], Y) - offset, 0.0f, 255.0f)) >> 3;\n"\
"                MEMBER(proj_mins, Z) = ((uint)clamp(MEMBER(projected_mins[flipped][partition], Z) - offset, 0.0f, 255.0f)) >> 3;\n"\
"                MEMBER(proj_maxs, X) = ((uint)clamp(MEMBER(projected_maxs[flipped][partition], X) + offset + 3, 0.0f, 255.0f)) >> 3;\n"\
"                MEMBER(proj_maxs, Y) = ((uint)clamp(MEMBER(projected_maxs[flipped][partition], Y) + offset + 3, 0.0f, 255.0f)) >> 3;\n"\
"                MEMBER(proj_maxs, Z) = ((uint)clamp(MEMBER(projected_maxs[flipped][partition], Z) + offset + 3, 0.0f, 255.0f)) >> 3;\n"\
"\n"\
"                sample.pos_quantised = proj_mins;\n"\
"                DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"                pathing_params.partition_indexes = &g_partition_indexes[flipped][partition][0];\n"\
"                sample.error = ETC_EvaluateError(is_ypbpr, trans_pixel, ETC_RGBExpandVecTo5Bit(sample.pos_quantised), &g_partition_indexes[flipped][partition][0]);\n"\
"                DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"                ETC_LeastCostDirectedPath(step, SAMPLE_LIST_SIZE2, error_target, refine_search, is_ypbpr, trans_pixel, sample, &sample_list[flipped][partition][0], MEMBER(proj_maxs, X), MEMBER(proj_maxs, Y), MEMBER(proj_maxs, Z), &pathing_params, ETC_RGBEXPANDVECTO5BIT, ETC_EVALUATEDELTAERRORGENERIC);\n"\
"                DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"            }\n"\
"        }\n"\
"        for (i = 0; i < 2; i++)\n"\
"            best_dist[i] = sample_list[i][0][0].error + sample_list[i][1][0].error;\n"\
"        if (best_dist[1] < best_dist[0])\n"\
"            is_flipped = 1;\n"\
"        else\n"\
"            is_flipped = 0;\n"\
"        is_delta = 0;\n"\
"        int diff = (int)(MEMBER(sample_list[is_flipped][1][0].pos_quantised, X)) - (int)(MEMBER(sample_list[is_flipped][0][0].pos_quantised, X));\n"\
"        if (diff < 4 && diff >= -4)\n"\
"            is_delta++;\n"\
"        diff = (int)(MEMBER(sample_list[is_flipped][1][0].pos_quantised, Y)) - (int)(MEMBER(sample_list[is_flipped][0][0].pos_quantised, Y));\n"\
"        if (diff < 4 && diff >= -4)\n"\
"            is_delta++;\n"\
"        diff = (int)(MEMBER(sample_list[is_flipped][1][0].pos_quantised, Z)) - (int)(MEMBER(sample_list[is_flipped][0][0].pos_quantised, Z));\n"\
"        if (diff < 4 && diff >= -4)\n"\
"            is_delta++;\n"\
"        is_best_delta = is_delta == 3 ? 1 : 0;\n"\
"        best_total_error = min(best_dist[0], best_dist[1]);\n"\
"\n"\
"        if (is_best_delta)\n"\
"            enc_mode = ETC_ENC_MODE_DELTA;\n"\
"\n"\
"        params_partition.rgb[0] = ETC_RGBExpandVecTo5Bit(sample_list[is_flipped][0][0].pos_quantised);\n"\
"        params_partition.rgb[1] = ETC_RGBExpandVecTo5Bit(sample_list[is_flipped][1][0].pos_quantised);\n"\
"        params_partition.is_flipped = is_flipped;\n"\
"\n"\
"        DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"        if (!is_best_delta)\n"\
"        {\n"\
"            int delta[2][SAMPLE_LIST_SIZE2][SAMPLE_LIST_SIZE2]; // TODO: can get rid of this if just do it inside the loop\n"\
"            float err[2][SAMPLE_LIST_SIZE2][SAMPLE_LIST_SIZE2]; // TODO: can get rid of this if just do it inside the loop\n"\
"            int best_delta[2] = {0, 0};\n"\
"            float best_delta_err = MAX_INIT_ERROR;\n"\
"            int delta_found = 0;\n"\
"            int best_flipped = 0;\n"\
"\n"\
"            for (n = 0; n < 2; n++)\n"\
"                for (i = 0; i < SAMPLE_LIST_SIZE2; i++)\n"\
"                {\n"\
"                    for (j = 0; j < SAMPLE_LIST_SIZE2; j++)\n"\
"                    {\n"\
"                        is_delta = 0;\n"\
"                        int diff = (int)(MEMBER(sample_list[n][1][j].pos_quantised, X)) - (int)(MEMBER(sample_list[n][0][i].pos_quantised, X));\n"\
"                        if (diff < 4 && diff >= -4)\n"\
"                            is_delta++;\n"\
"                        diff = (int)(MEMBER(sample_list[n][1][j].pos_quantised, Y)) - (int)(MEMBER(sample_list[n][0][i].pos_quantised, Y));\n"\
"                        if (diff < 4 && diff >= -4)\n"\
"                            is_delta++;\n"\
"                        diff = (int)(MEMBER(sample_list[n][1][j].pos_quantised, Z)) - (int)(MEMBER(sample_list[n][0][i].pos_quantised, Z));\n"\
"                        if (diff < 4 && diff >= -4)\n"\
"                            is_delta++;\n"\
"\n"\
"                        delta[n][i][j] = is_delta == 3 ? 1 : 0;\n"\
"                        err[n][i][j] = sample_list[n][1][j].error + sample_list[n][0][i].error;\n"\
"                    }\n"\
"                }\n"\
"            for (n = 0; n < 2; n++)\n"\
"                for (i = 0; i < SAMPLE_LIST_SIZE2; i++)\n"\
"                    for (j = 0; j < SAMPLE_LIST_SIZE2; j++)\n"\
"                    {\n"\
"                        if (delta[n][i][j])\n"\
"                        {\n"\
"                            if (err[n][i][j] < best_delta_err)\n"\
"                            {\n"\
"                                best_delta_err = err[n][i][j];\n"\
"                                best_delta[0] = i;\n"\
"                                best_delta[1] = j;\n"\
"                                delta_found = 1;\n"\
"                                best_flipped = n;\n"\
"                            }\n"\
"                        }\n"\
"                    }\n"\
"            best_total_error = best_delta_err;\n"\
"\n"\
"            if (delta_found)\n"\
"            {\n"\
"                enc_mode = ETC_ENC_MODE_DELTA;\n"\
"                params_partition.rgb[0] = ETC_RGBExpandVecTo5Bit(sample_list[best_flipped][0][best_delta[0]].pos_quantised);\n"\
"                params_partition.rgb[1] = ETC_RGBExpandVecTo5Bit(sample_list[best_flipped][1][best_delta[1]].pos_quantised);\n"\
"                params_partition.is_flipped = best_flipped;\n"\
"            }\n"\
"        }\n"\
"\n"\
"        if (found_fixed && fixed_err < best_total_error)\n"\
"        {\n"\
"            enc_mode = ETC_ENC_MODE_DELTA;\n"\
"            best_total_error = fixed_err;\n"\
"            params_partition.rgb[0] = ETC_RGBExpandVecTo5Bit(best_positions[0]);\n"\
"            params_partition.rgb[1] = ETC_RGBExpandVecTo5Bit(best_positions[1]);\n"\
"            params_partition.is_flipped = best_flipped;\n"\
"        }\n"\
"\n"\
"        DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"        ETC_GetOptimalIndexes(is_ypbpr, trans_pixel, params_partition.rgb[0], &g_partition_indexes[params_partition.is_flipped][0][0], &params_partition.table[0], params_partition.indexes);\n"\
"        DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"        ETC_GetOptimalIndexes(is_ypbpr, trans_pixel, params_partition.rgb[1], &g_partition_indexes[params_partition.is_flipped][1][0], &params_partition.table[1], params_partition.indexes);\n"\
"        DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"    }\n"\
"    if ((allowed_modes & ETC_MODE_NODELTA))\n"\
"    {\n"\
"        int is_non_delta_flipped;\n"\
"        float3 mean[2][2];\n"\
"        uchar3 mean_quant[2][2];\n"\
"        int min_index[2][2];\n"\
"        int max_index[2][2];\n"\
"        float fixed_err = MAX_INIT_ERROR;\n"\
"        uchar3 best_positions[2];\n"\
"        int best_flipped = 0;\n"\
"        int found_fixed = 0;\n"\
"        uchar3 proj_mins;\n"\
"        uchar3 proj_maxs;\n"\
"\n"\
"        if (quality >= CODEC_QUALITY_NORMAL) // redundant\n"\
"        {\n"\
"            float fixed_err_group[2][2];\n"\
"            uchar3 fixed_positions_group[2][2];\n"\
"            int max_distance;\n"\
"\n"\
"            if (quality == CODEC_QUALITY_BEST)\n"\
"                max_distance = 255;\n"\
"            else if (quality == CODEC_QUALITY_HIGH)\n"\
"                max_distance = 4;\n"\
"            else \n"\
"                max_distance = 1;\n"\
"\n"\
"            for (i = 0; i < 2; i++)\n"\
"                for (j = 0; j < 2; j++)\n"\
"                    fixed_err_group[i][j] = MAX_INIT_ERROR;\n"\
"\n"\
"            for (flipped = 0; flipped < 2; flipped++)\n"\
"            {\n"\
"                for (partition = 0; partition < 2; partition++)\n"\
"                {\n"\
"                    int distance = 0;\n"\
"                    mean[flipped][partition] = VFLOAT3(0.0f, 0.0f, 0.0f);\n"\
"                    for (i = 0; i < 8; i++)\n"\
"                    {\n"\
"                        mean[flipped][partition] = mean[flipped][partition] + trans_pixel[g_partition_indexes[flipped][partition][i]];\n"\
"                    }\n"\
"                    mean[flipped][partition] = mean[flipped][partition] / 8.0f;\n"\
"\n"\
"                    MEMBER(mean_quant[flipped][partition], X) = UCHAR(MEMBER(mean[flipped][partition], X)) >> 4;\n"\
"                    MEMBER(mean_quant[flipped][partition], Y) = UCHAR(MEMBER(mean[flipped][partition], Y)) >> 4;\n"\
"                    MEMBER(mean_quant[flipped][partition], Z) = UCHAR(MEMBER(mean[flipped][partition], Z)) >> 4;\n"\
"\n"\
"                    min_index[flipped][partition] = 0;\n"\
"                    max_index[flipped][partition] = 0;\n"\
"\n"\
"                    while ( ((int)MEMBER(mean_quant[flipped][partition], X) + min_index[flipped][partition] > 0) &&\n"\
"                            ((int)MEMBER(mean_quant[flipped][partition], Y) + min_index[flipped][partition] > 0) &&\n"\
"                            ((int)MEMBER(mean_quant[flipped][partition], Z) + min_index[flipped][partition] > 0))\n"\
"                    {\n"\
"                        min_index[flipped][partition]--;\n"\
"                        distance++;\n"\
"                        if (distance > max_distance)\n"\
"                            break;\n"\
"                    }\n"\
"                    distance = 0;\n"\
"                    while ( ((int)MEMBER(mean_quant[flipped][partition], X) + max_index[flipped][partition] < 16) &&\n"\
"                            ((int)MEMBER(mean_quant[flipped][partition], Y) + max_index[flipped][partition] < 16) &&\n"\
"                            ((int)MEMBER(mean_quant[flipped][partition], Z) + max_index[flipped][partition] < 16))\n"\
"                    {\n"\
"                        max_index[flipped][partition]++;\n"\
"                        distance++;\n"\
"                        if (distance > max_distance)\n"\
"                            break;\n"\
"                    }\n"\
"                }\n"\
"            }\n"\
"#if 1\n"\
"            for (flipped = 0; flipped < 2; flipped++)\n"\
"            {\n"\
"                for (partition = 0; partition < 2; partition++)\n"\
"                {\n"\
"                    int ip0;\n"\
"                    for (ip0 = min_index[flipped][partition]; ip0 <= max_index[flipped][partition]; ip0++)\n"\
"                    {\n"\
"                        uchar3 l0_quant;\n"\
"                        float err;\n"\
"\n"\
"                        MEMBER(l0_quant, X) = MEMBER(mean_quant[flipped][partition], X) + ip0;\n"\
"                        MEMBER(l0_quant, Y) = MEMBER(mean_quant[flipped][partition], Y) + ip0;\n"\
"                        MEMBER(l0_quant, Z) = MEMBER(mean_quant[flipped][partition], Z) + ip0;\n"\
"\n"\
"                        err = ETC_EvaluateError(is_ypbpr, trans_pixel, ETC_RGBExpandVecTo4Bit(l0_quant), &g_partition_indexes[flipped][partition][0]);\n"\
"\n"\
"                        if (err < fixed_err_group[flipped][partition])\n"\
"                        {\n"\
"                            fixed_err_group[flipped][partition] = err;\n"\
"                            fixed_positions_group[flipped][partition] = l0_quant;\n"\
"                        }\n"\
"                    }\n"\
"                }\n"\
"            }\n"\
"\n"\
"            if (fixed_err_group[0][0] + fixed_err_group[0][1] < fixed_err_group[1][0] + fixed_err_group[1][1])\n"\
"            {\n"\
"                fixed_err = fixed_err_group[0][0] + fixed_err_group[0][1];\n"\
"                best_positions[0] = fixed_positions_group[0][0];\n"\
"                best_positions[1] = fixed_positions_group[0][1];\n"\
"                best_flipped = 0;\n"\
"            }\n"\
"            else\n"\
"            {\n"\
"                fixed_err = fixed_err_group[1][0] + fixed_err_group[1][1];\n"\
"                best_positions[0] = fixed_positions_group[1][0];\n"\
"                best_positions[1] = fixed_positions_group[1][1];\n"\
"                best_flipped = 1;\n"\
"            }\n"\
"\n"\
"            found_fixed = 1;\n"\
"            if (found_fixed)\n"\
"            {\n"\
"                uchar3 best_pos[2];\n"\
"                float combined_err = 0.0f;\n"\
"            \n"\
"                best_pos[0] = best_positions[0];\n"\
"                best_pos[1] = best_positions[1];\n"\
"\n"\
"                for (partition = 0; partition < 2; partition++)\n"\
"                {\n"\
"                    int neighbourhood_width = (quality == CODEC_QUALITY_BEST ? 3 : 1);\n"\
"                    float best_err = MAX_INIT_ERROR;\n"\
"                    int x;\n"\
"                    int y;\n"\
"                    int z;\n"\
"                    int min_x = MEMBER(best_positions[partition], X) > (neighbourhood_width - 1) ? MEMBER(best_positions[partition], X) - neighbourhood_width : 0;\n"\
"                    int min_y = MEMBER(best_positions[partition], Y) > (neighbourhood_width - 1) ? MEMBER(best_positions[partition], Y) - neighbourhood_width : 0;\n"\
"                    int min_z = MEMBER(best_positions[partition], Z) > (neighbourhood_width - 1) ? MEMBER(best_positions[partition], Z) - neighbourhood_width : 0;\n"\
"                    int max_x = MEMBER(best_positions[partition], X) < (15 - neighbourhood_width) ? MEMBER(best_positions[partition], X) + neighbourhood_width : 15;\n"\
"                    int max_y = MEMBER(best_positions[partition], Y) < (15 - neighbourhood_width) ? MEMBER(best_positions[partition], Y) + neighbourhood_width : 15;\n"\
"                    int max_z = MEMBER(best_positions[partition], Z) < (15 - neighbourhood_width) ? MEMBER(best_positions[partition], Z) + neighbourhood_width : 15;\n"\
"\n"\
"                    for (z = min_z; z <= max_z; z++)\n"\
"                        for (y = min_y; y <= max_y; y++)\n"\
"                            for (x = min_x; x <= max_x; x++)\n"\
"                            {\n"\
"                                uchar3 pos = UCHAR3(x, y, z);\n"\
"                                float err;\n"\
"                                pos = ETC_RGBExpandVecTo4Bit(pos);\n"\
"                                err = ETC_EvaluateError(is_ypbpr, trans_pixel, pos, &g_partition_indexes[best_flipped][partition][0]);\n"\
"                                if (err < best_err)\n"\
"                                {\n"\
"                                    best_err = err;\n"\
"                                    best_pos[partition] = UCHAR3(x, y, z);\n"\
"                                }\n"\
"                            }\n"\
"                    combined_err += best_err;\n"\
"                }\n"\
"                best_positions[0] = best_pos[0];\n"\
"                best_positions[1] = best_pos[1];\n"\
"\n"\
"                fixed_err = combined_err;\n"\
"\n"\
"                for (partition = 0; partition < 2; partition++)\n"\
"                {\n"\
"                    int terminate = 0;\n"\
"                    uchar3 pos = best_positions[partition];\n"\
"\n"\
"                    if (quality != CODEC_QUALITY_BEST)\n"\
"                        terminate = 1;\n"\
"\n"\
"                    while(!terminate)\n"\
"                    {\n"\
"                        short3 test_pos[27];\n"\
"                        float dist[27];\n"\
"                        int best_index;\n"\
"                        float best_dist;\n"\
"                        int terminate_count = 0;\n"\
"\n"\
"                        for (j = 0; j < 27; j++)\n"\
"                            test_pos[j] = SHORT3(MEMBER(pos, X), MEMBER(pos, Y), MEMBER(pos, Z)) + SHORT3((j % 3) - 1, ((j / 3) % 3) - 1, j/9 - 1);\n"\
"\n"\
"                        for (j = 0; j < 27; j++)\n"\
"                        {\n"\
"                            if ((MEMBER(test_pos[j], X) > 15) || (MEMBER(test_pos[j], Y) > 15) || (MEMBER(test_pos[j], Z) > 15) || (MEMBER(test_pos[j], X) < 0) || (MEMBER(test_pos[j], Y) < 0) || (MEMBER(test_pos[j], Z) < 0))\n"\
"                                dist[j] = MAX_INIT_ERROR;\n"\
"                            else\n"\
"                            {\n"\
"                                uchar3 v;\n"\
"\n"\
"                                v = ETC_RGBExpandVecTo4Bit(UCHAR3(MEMBER(test_pos[j], X), MEMBER(test_pos[j], Y), MEMBER(test_pos[j], Z)));\n"\
"\n"\
"                                dist[j] = ETC_EvaluateError(is_ypbpr, trans_pixel, ETC_RGBExpandVecTo4Bit(v), &g_partition_indexes[best_flipped][partition][0]);\n"\
"                            }\n"\
"                        }\n"\
"\n"\
"                        best_dist = dist[0];\n"\
"                        best_index = 0;\n"\
"                        for (j = 1; j < 27; j++)\n"\
"                        {\n"\
"                            if (dist[j] < best_dist)\n"\
"                            {\n"\
"                                best_dist = dist[j];\n"\
"                                best_index = j;\n"\
"                            }\n"\
"                        }\n"\
"\n"\
"                        best_positions[partition] = pos;\n"\
"\n"\
"                        if (dist[13] == best_dist)\n"\
"                            break;\n"\
"\n"\
"                        for (j = 0; j < 27; j++)\n"\
"                            if (dist[j] == MAX_INIT_ERROR)\n"\
"                                terminate_count++;\n"\
"\n"\
"                        if (terminate_count >= 26)\n"\
"                            break;\n"\
"\n"\
"                        pos = UCHAR3(MEMBER(test_pos[best_index], X), MEMBER(test_pos[best_index], Y), MEMBER(test_pos[best_index], Z));\n"\
"                    }\n"\
"                }\n"\
"            }\n"\
"\n"\
"            if (found_fixed && fixed_err < best_total_error)\n"\
"            {\n"\
"                enc_mode = ETC_ENC_MODE_NODELTA;\n"\
"                best_total_error = fixed_err;\n"\
"                params_partition.rgb[0] = ETC_RGBExpandVecTo4Bit(best_positions[0]);\n"\
"                params_partition.rgb[1] = ETC_RGBExpandVecTo4Bit(best_positions[1]);\n"\
"                params_partition.is_flipped = best_flipped;\n"\
"            }\n"\
"        }\n"\
"#endif\n"\
"        // Non-delta mode\n"\
"        DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"        ETC_PrepareSampleList(1, sample_list);\n"\
"        DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"        for (flipped = 0; flipped < 2; flipped++)\n"\
"        {\n"\
"            for (partition = 0; partition < 2; partition++)\n"\
"            {\n"\
"                etc_sample_t sample;\n"\
"                float offset = 0.0f;\n"\
"\n"\
"                if (quality == CODEC_QUALITY_NORMAL)\n"\
"                    offset = 0.0f;\n"\
"                else if (quality == CODEC_QUALITY_HIGH)\n"\
"                    offset = 48.0f;\n"\
"                else \n"\
"                    offset = 96.0f;\n"\
"\n"\
"                if ((quality == CODEC_QUALITY_NORMAL) || (quality == CODEC_QUALITY_HIGH))\n"\
"                {\n"\
"                    MEMBER(proj_mins, X) = ((uint)clamp(MEMBER(projected_mins[flipped][partition], X) - offset, 0.0f, 255.0f)) >> 4;\n"\
"                    MEMBER(proj_mins, Y) = ((uint)clamp(MEMBER(projected_mins[flipped][partition], Y) - offset, 0.0f, 255.0f)) >> 4;\n"\
"                    MEMBER(proj_mins, Z) = ((uint)clamp(MEMBER(projected_mins[flipped][partition], Z) - offset, 0.0f, 255.0f)) >> 4;\n"\
"                    MEMBER(proj_maxs, X) = ((uint)clamp(MEMBER(projected_maxs[flipped][partition], X) + offset + 7, 0.0f, 255.0f)) >> 4;\n"\
"                    MEMBER(proj_maxs, Y) = ((uint)clamp(MEMBER(projected_maxs[flipped][partition], Y) + offset + 7, 0.0f, 255.0f)) >> 4;\n"\
"                    MEMBER(proj_maxs, Z) = ((uint)clamp(MEMBER(projected_maxs[flipped][partition], Z) + offset + 7, 0.0f, 255.0f)) >> 4;\n"\
"                }\n"\
"                else\n"\
"                {\n"\
"                    proj_mins = UCHAR3(0, 0, 0);\n"\
"                    proj_maxs = UCHAR3(15, 15, 15);\n"\
"                }\n"\
"\n"\
"                sample.pos_quantised = proj_mins;\n"\
"                DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"                pathing_params.partition_indexes = &g_partition_indexes[flipped][partition][0];\n"\
"                sample.error = ETC_EvaluateError(is_ypbpr, trans_pixel, ETC_RGBExpandVecTo4Bit(sample.pos_quantised), &g_partition_indexes[flipped][partition][0]);\n"\
"                DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"                ETC_LeastCostDirectedPath(step, 1, error_target, refine_search, is_ypbpr, trans_pixel, sample, &sample_list[flipped][partition][0], MEMBER(proj_maxs, X), MEMBER(proj_maxs, Y), MEMBER(proj_maxs, Z), &pathing_params, ETC_RGBEXPANDVECTO4BIT, ETC_EVALUATEDELTAERRORGENERIC);\n"\
"                DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"            }\n"\
"        }\n"\
"        for (i = 0; i < 2; i++)\n"\
"            best_dist[i] = sample_list[i][0][0].error + sample_list[i][1][0].error;\n"\
"        if (best_dist[1] < best_dist[0])\n"\
"            is_non_delta_flipped = 1;\n"\
"        else\n"\
"            is_non_delta_flipped = 0;\n"\
"        if (best_dist[is_non_delta_flipped] < best_total_error)\n"\
"        {\n"\
"            best_total_error = best_dist[is_non_delta_flipped];\n"\
"\n"\
"            enc_mode = ETC_ENC_MODE_NODELTA;\n"\
"            params_partition.rgb[0] = ETC_RGBExpandVecTo4Bit(sample_list[is_non_delta_flipped][0][0].pos_quantised);\n"\
"            params_partition.rgb[1] = ETC_RGBExpandVecTo4Bit(sample_list[is_non_delta_flipped][1][0].pos_quantised);\n"\
"            params_partition.is_flipped = is_non_delta_flipped;\n"\
"        }\n"\
"        DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"        ETC_GetOptimalIndexes(is_ypbpr, trans_pixel, params_partition.rgb[0], &g_partition_indexes[params_partition.is_flipped][0][0], &params_partition.table[0], params_partition.indexes);\n"\
"        DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"        ETC_GetOptimalIndexes(is_ypbpr, trans_pixel, params_partition.rgb[1], &g_partition_indexes[params_partition.is_flipped][1][0], &params_partition.table[1], params_partition.indexes);\n"\
"        DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"    }\n"\
"\n"\
"    if (is_etc2)\n"\
"    {\n"\
"        if ((best_total_error > error_target) && (allowed_modes & (ETC_MODE_T | ETC_MODE_H)))\n"\
"        {\n"\
"            int set_indexes[2][16];\n"\
"            int set_count[2];\n"\
"            etc_sample_t sample;\n"\
"            DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"            ETC_KMeansTHMode(trans_pixel, &set_indexes[0][0], &set_indexes[1][0], &set_count[0]);\n"\
"            DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"\n"\
"            for (partition = 0; partition < 2; partition++)\n"\
"            {\n"\
"                float3 mean = VFLOAT3(0.0f, 0.0f, 0.0f);\n"\
"                float mins_maxs_dist[2];\n"\
"                float3 temp;\n"\
"\n"\
"                for (i = 0; i < set_count[partition]; i++)\n"\
"                    mean = mean + trans_pixel[set_indexes[partition][i]];\n"\
"\n"\
"                mean = mean / (set_count[partition] ? (float)(set_count[partition]) : 1.0f);\n"\
"\n"\
"                if (set_count[partition])\n"\
"                {\n"\
"                    mins_maxs_dist[0] = dot(trans_pixel[set_indexes[partition][0]] - mean, VFLOAT3(0.57735f, 0.57735f, 0.57735f));\n"\
"                    mins_maxs_dist[1] = mins_maxs_dist[0];\n"\
"\n"\
"                    for (i = 0; i < set_count[partition]; i++)\n"\
"                    {\n"\
"                        float dist = dot(trans_pixel[set_indexes[partition][i]] - mean, VFLOAT3(0.57735f, 0.57735f, 0.57735f));\n"\
"\n"\
"                        if (dist < mins_maxs_dist[0])\n"\
"                            mins_maxs_dist[0] = dist;\n"\
"                        if (dist > mins_maxs_dist[1])\n"\
"                            mins_maxs_dist[1] = dist;\n"\
"                    }\n"\
"                    projected_mins[0][partition] = mean + VFLOAT3(0.57735f, 0.57735f, 0.57735f) * mins_maxs_dist[0];\n"\
"                    projected_maxs[0][partition] = mean + VFLOAT3(0.57735f, 0.57735f, 0.57735f) * mins_maxs_dist[1];\n"\
"                }\n"\
"                else\n"\
"                {\n"\
"                    projected_mins[0][partition] = mean;\n"\
"                    projected_maxs[0][partition] = mean;\n"\
"                }\n"\
"            }\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"            if (allowed_modes & ETC_MODE_T)\n"\
"            {\n"\
"                // T mode\n"\
"                DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"                ETC_PrepareSampleList(1, sample_list);\n"\
"                DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"                for (flipped = 0; flipped < 2; flipped++)\n"\
"                {\n"\
"                    etc_sample_t sample;\n"\
"                    uchar3 proj_mins;\n"\
"                    uchar3 proj_maxs;\n"\
"                    float offset = 0.0f;\n"\
"\n"\
"                    if (quality == CODEC_QUALITY_NORMAL)\n"\
"                        offset = 0.0f;\n"\
"                    else if (quality == CODEC_QUALITY_HIGH)\n"\
"                        offset = 48.0f;\n"\
"                    else \n"\
"                        offset = 96.0f;\n"\
"\n"\
"                    if ((quality == CODEC_QUALITY_NORMAL) || (quality == CODEC_QUALITY_HIGH))\n"\
"                    {\n"\
"                        MEMBER(proj_mins, X) = ((uint)clamp(MEMBER(projected_mins[0][flipped], X) - offset, 0.0f, 255.0f)) >> 4;\n"\
"                        MEMBER(proj_mins, Y) = ((uint)clamp(MEMBER(projected_mins[0][flipped], Y) - offset, 0.0f, 255.0f)) >> 4;\n"\
"                        MEMBER(proj_mins, Z) = ((uint)clamp(MEMBER(projected_mins[0][flipped], Z) - offset, 0.0f, 255.0f)) >> 4;\n"\
"                        MEMBER(proj_maxs, X) = ((uint)clamp(MEMBER(projected_maxs[0][flipped], X) + offset + 7, 0.0f, 255.0f)) >> 4;\n"\
"                        MEMBER(proj_maxs, Y) = ((uint)clamp(MEMBER(projected_maxs[0][flipped], Y) + offset + 7, 0.0f, 255.0f)) >> 4;\n"\
"                        MEMBER(proj_maxs, Z) = ((uint)clamp(MEMBER(projected_maxs[0][flipped], Z) + offset + 7, 0.0f, 255.0f)) >> 4;\n"\
"                    }\n"\
"                    else\n"\
"                    {\n"\
"                        proj_mins = UCHAR3(0, 0, 0);\n"\
"                        proj_maxs = UCHAR3(15, 15, 15);\n"\
"                    }\n"\
"\n"\
"                    sample.pos_quantised = proj_mins;\n"\
"                    DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"                    pathing_params.indexes = set_indexes[flipped];\n"\
"                    pathing_params.num_indexes = set_count[flipped];\n"\
"                    sample.error = ETC_EvaluateErrorTSingle(is_ypbpr, trans_pixel, ETC_RGBExpandVecTo4Bit(sample.pos_quantised), set_indexes[flipped], set_count[flipped]);\n"\
"                    DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"                    ETC_LeastCostDirectedPath(step, 1, error_target, refine_search, is_ypbpr, trans_pixel, sample, &sample_list[flipped][0][0], MEMBER(proj_maxs, X), MEMBER(proj_maxs, Y), MEMBER(proj_maxs, Z), &pathing_params, ETC_RGBEXPANDVECTO4BIT, ETC_EVALUATETSINGLEERRORGENERIC);\n"\
"                    DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"\n"\
"                    if ((quality == CODEC_QUALITY_NORMAL) || (quality == CODEC_QUALITY_HIGH))\n"\
"                    {\n"\
"                        MEMBER(proj_mins, X) = ((uint)clamp(MEMBER(projected_mins[0][(flipped + 1) % 2], X) - offset, 0.0f, 255.0f)) >> 4;\n"\
"                        MEMBER(proj_mins, Y) = ((uint)clamp(MEMBER(projected_mins[0][(flipped + 1) % 2], Y) - offset, 0.0f, 255.0f)) >> 4;\n"\
"                        MEMBER(proj_mins, Z) = ((uint)clamp(MEMBER(projected_mins[0][(flipped + 1) % 2], Z) - offset, 0.0f, 255.0f)) >> 4;\n"\
"                        MEMBER(proj_maxs, X) = ((uint)clamp(MEMBER(projected_maxs[0][(flipped + 1) % 2], X) + offset + 7, 0.0f, 255.0f)) >> 4;\n"\
"                        MEMBER(proj_maxs, Y) = ((uint)clamp(MEMBER(projected_maxs[0][(flipped + 1) % 2], Y) + offset + 7, 0.0f, 255.0f)) >> 4;\n"\
"                        MEMBER(proj_maxs, Z) = ((uint)clamp(MEMBER(projected_maxs[0][(flipped + 1) % 2], Z) + offset + 7, 0.0f, 255.0f)) >> 4;\n"\
"                    }\n"\
"                    else\n"\
"                    {\n"\
"                        proj_mins = UCHAR3(0, 0, 0);\n"\
"                        proj_maxs = UCHAR3(15, 15, 15);\n"\
"                    }\n"\
"\n"\
"                    sample.pos_quantised = proj_mins;\n"\
"                    DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"                    pathing_params.indexes = set_indexes[(flipped + 1) % 2];\n"\
"                    pathing_params.num_indexes = set_count[(flipped + 1) % 2];\n"\
"                    sample.error = ETC_EvaluateErrorTTriple(is_ypbpr, trans_pixel, ETC_RGBExpandVecTo4Bit(sample.pos_quantised), set_indexes[(flipped + 1) % 2], set_count[(flipped + 1) % 2]);\n"\
"                    DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"                    ETC_LeastCostDirectedPath(step, 1, error_target, refine_search, is_ypbpr, trans_pixel, sample, &sample_list[flipped][1][0], MEMBER(proj_maxs, X), MEMBER(proj_maxs, Y), MEMBER(proj_maxs, Z), &pathing_params, ETC_RGBEXPANDVECTO4BIT, ETC_EVALUATETTRIPLEERRORGENERIC);\n"\
"                    DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"                }\n"\
"                for (i = 0; i < 2; i++)\n"\
"                    best_dist[i] = sample_list[i][0][0].error + sample_list[i][1][0].error;\n"\
"\n"\
"                if ((best_dist[0] < best_total_error) || (best_dist[1] < best_total_error))\n"\
"                {\n"\
"                    enc_mode = ETC_ENC_MODE_T;\n"\
"\n"\
"                    if (best_dist[1] < best_dist[0])\n"\
"                        is_flipped = 1;\n"\
"                    else\n"\
"                        is_flipped = 0;\n"\
"\n"\
"                    params_th.rgb[0] = ETC_RGBExpandVecTo4Bit(sample_list[is_flipped][0][0].pos_quantised);\n"\
"                    params_th.rgb[1] = ETC_RGBExpandVecTo4Bit(sample_list[is_flipped][1][0].pos_quantised);\n"\
"                    DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"                    float d = ETC_GetOptimalTIndexes(is_ypbpr, trans_pixel, params_th.rgb[0], params_th.rgb[1], &params_th.indexes[0], &params_th.table);\n"\
"                    DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"                    best_total_error = d;\n"\
"                }\n"\
"            }\n"\
"\n"\
"            if ((best_total_error > error_target) && (allowed_modes & ETC_MODE_H))\n"\
"            {\n"\
"                int best_mode;\n"\
"\n"\
"                // H-Mode\n"\
"                ETC_PrepareSampleList(1, sample_list);\n"\
"                for (flipped = 0; flipped < 2; flipped++)\n"\
"                {\n"\
"                    uchar3 proj_mins;\n"\
"                    uchar3 proj_maxs;\n"\
"                    float offset = 0.0f;\n"\
"\n"\
"                    if (quality == CODEC_QUALITY_NORMAL)\n"\
"                        offset = 0.0f;\n"\
"                    else if (quality == CODEC_QUALITY_HIGH)\n"\
"                        offset = 48.0f;\n"\
"                    else \n"\
"                        offset = 96.0f;\n"\
"\n"\
"                    if (quality == CODEC_QUALITY_NORMAL)\n"\
"                    {\n"\
"                        MEMBER(proj_mins, X) = ((uint)clamp(MEMBER(projected_mins[0][flipped], X) - offset, 0.0f, 255.0f)) >> 4;\n"\
"                        MEMBER(proj_mins, Y) = ((uint)clamp(MEMBER(projected_mins[0][flipped], Y) - offset, 0.0f, 255.0f)) >> 4;\n"\
"                        MEMBER(proj_mins, Z) = ((uint)clamp(MEMBER(projected_mins[0][flipped], Z) - offset, 0.0f, 255.0f)) >> 4;\n"\
"                        MEMBER(proj_maxs, X) = ((uint)clamp(MEMBER(projected_maxs[0][flipped], X) + offset + 7, 0.0f, 255.0f)) >> 4;\n"\
"                        MEMBER(proj_maxs, Y) = ((uint)clamp(MEMBER(projected_maxs[0][flipped], Y) + offset + 7, 0.0f, 255.0f)) >> 4;\n"\
"                        MEMBER(proj_maxs, Z) = ((uint)clamp(MEMBER(projected_maxs[0][flipped], Z) + offset + 7, 0.0f, 255.0f)) >> 4;\n"\
"                    }\n"\
"                    else\n"\
"                    {\n"\
"                        proj_mins = UCHAR3(0, 0, 0);\n"\
"                        proj_maxs = UCHAR3(15, 15, 15);\n"\
"                    }\n"\
"\n"\
"                    for (table = 0; table < 8; table++)\n"\
"                    {\n"\
"                        sample.pos_quantised = proj_mins;\n"\
"                        DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"                        pathing_params.indexes = set_indexes[flipped];\n"\
"                        pathing_params.num_indexes = set_count[flipped];\n"\
"                        pathing_params.mode = table;\n"\
"                        sample.error = ETC_EvaluateErrorH(is_ypbpr, trans_pixel, ETC_RGBExpandVecTo4Bit(sample.pos_quantised), set_indexes[flipped], set_count[flipped], table);\n"\
"                        DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"                        ETC_LeastCostDirectedPath(step, 1, error_target, refine_search, is_ypbpr, trans_pixel, sample, &sample_list[flipped][table][0], MEMBER(proj_maxs, X), MEMBER(proj_maxs, Y), MEMBER(proj_maxs, Z), &pathing_params, ETC_RGBEXPANDVECTO4BIT, ETC_EVALUATEHERRORGENERIC);\n"\
"                        DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"                    }\n"\
"                }\n"\
"\n"\
"                best_dist[0] = sample_list[0][0][0].error + sample_list[1][0][0].error;\n"\
"                best_mode = 0;\n"\
"                for (flipped = 0; flipped < 2; flipped++)\n"\
"                    for (table = 0; table < 8; table++)\n"\
"                        if (sample_list[0][table][0].error + sample_list[1][table][0].error < best_dist[0])\n"\
"                        {\n"\
"                            best_dist[0] = sample_list[0][table][0].error + sample_list[1][table][0].error;\n"\
"                            best_mode = table;\n"\
"                        }\n"\
"                if (best_dist[0] < best_total_error)\n"\
"                {\n"\
"                    ushort rgbpacked[2];\n"\
"\n"\
"                    enc_mode = ETC_ENC_MODE_H;\n"\
"\n"\
"                    params_th.table = best_mode;\n"\
"\n"\
"                    if ((MEMBER(sample_list[0][params_th.table][0].pos_quantised, X) == MEMBER(sample_list[1][params_th.table][0].pos_quantised, X)) &&\n"\
"                        (MEMBER(sample_list[0][params_th.table][0].pos_quantised, Y) == MEMBER(sample_list[1][params_th.table][0].pos_quantised, Y)) &&\n"\
"                        (MEMBER(sample_list[0][params_th.table][0].pos_quantised, Z) == MEMBER(sample_list[1][params_th.table][0].pos_quantised, Z)))\n"\
"                        MEMBER(sample_list[0][params_th.table][0].pos_quantised, X) = (MEMBER(sample_list[0][params_th.table][0].pos_quantised, X) + 1) % 16;\n"\
"\n"\
"                    params_th.rgb[0] = ETC_RGBExpandVecTo4Bit(sample_list[0][params_th.table][0].pos_quantised);\n"\
"                    params_th.rgb[1] = ETC_RGBExpandVecTo4Bit(sample_list[1][params_th.table][0].pos_quantised);\n"\
"\n"\
"                    rgbpacked[0] =  (((ushort)MEMBER(sample_list[0][params_th.table][0].pos_quantised, X)) << 8) |\n"\
"                        (((ushort)MEMBER(sample_list[0][params_th.table][0].pos_quantised, Y)) << 4) |\n"\
"                        (((ushort)MEMBER(sample_list[0][params_th.table][0].pos_quantised, Z)) << 0);\n"\
"\n"\
"                    rgbpacked[1] =  (((ushort)MEMBER(sample_list[1][params_th.table][0].pos_quantised, X)) << 8) |\n"\
"                        (((ushort)MEMBER(sample_list[1][params_th.table][0].pos_quantised, Y)) << 4) |\n"\
"                        (((ushort)MEMBER(sample_list[1][params_th.table][0].pos_quantised, Z)) << 0);\n"\
"                    if (!(params_th.table & 1))\n"\
"                    {\n"\
"                        if (rgbpacked[0] > rgbpacked[1])\n"\
"                        {\n"\
"                            params_th.rgb[0] = ETC_RGBExpandVecTo4Bit(sample_list[1][params_th.table][0].pos_quantised);\n"\
"                            params_th.rgb[1] = ETC_RGBExpandVecTo4Bit(sample_list[0][params_th.table][0].pos_quantised);\n"\
"                        }\n"\
"                    }\n"\
"                    else\n"\
"                    {\n"\
"                        if (rgbpacked[0] < rgbpacked[1])\n"\
"                        {\n"\
"                            params_th.rgb[0] = ETC_RGBExpandVecTo4Bit(sample_list[1][params_th.table][0].pos_quantised);\n"\
"                            params_th.rgb[1] = ETC_RGBExpandVecTo4Bit(sample_list[0][params_th.table][0].pos_quantised);\n"\
"                        }\n"\
"                    }\n"\
"                    DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"                    best_total_error = ETC_GetOptimalHIndexes(is_ypbpr, trans_pixel, params_th.rgb[0], params_th.rgb[1], params_th.indexes, params_th.table);\n"\
"                    DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"                }\n"\
"            }\n"\
"        }\n"\
"\n"\
"        if ((best_total_error != 0.0f) && (allowed_modes & ETC_MODE_PLANAR))\n"\
"        {\n"\
"            // Planar mode: always check this because it's so cheap to compute\n"\
"\n"\
"            float3 points[3];\n"\
"            int3 points_i32[3];\n"\
"            float index_best_dist[3];\n"\
"            float best_dist = 0.0f;\n"\
"            int best_twiddle[3][3];\n"\
"            int index;\n"\
"            int twiddle0;\n"\
"            int twiddle1;\n"\
"            int twiddle2;\n"\
"            const float coeff[3][16] =\n"\
"            {\n"\
"                {23.0f, 17.0f, 11.0f, 5.0f, 17.0f, 11.0f, 5.0f, -1.0f, 11.0f, 5.0f, -1.0f, -7.0f, 5.0f, -1.0f, -7.0f, -13.0f},\n"\
"                {-1.0f, 9.0f, 19.0f, 29.0f, -7.0f, 3.0f, 13.0f, 23.0f, -13.0f, -3.0f, 7.0f, 17.0f, -19.0f, -9.0f, 1.0f, 11.0f},\n"\
"                {-1.0f, -7.0f, -13.0f, -19.0f, 9.0f, 3.0f, -3.0f, -9.0f, 19.0f, 13.0f, 7.0f, 1.0f, 29.0f, 23.0f, 17.0f, 11.0f}\n"\
"            };\n"\
"            DEBUG_PRINTF((\"trans_pixel: 0x%p\\n\", trans_pixel));\n"\
"            points[0] = VFLOAT3(0.0f, 0.0f, 0.0f);\n"\
"            points[1] = VFLOAT3(0.0f, 0.0f, 0.0f);\n"\
"            points[2] = VFLOAT3(0.0f, 0.0f, 0.0f);\n"\
"            // TODO: this isn't trivial for the YCBCR case, just minimise in RGB space for now\n"\
"            if (is_ypbpr)\n"\
"                for (i = 0; i < 16; i++)\n"\
"                    trans_pixel[i] = clamp(ETC_ConvertToRGBf3(trans_pixel[i]), 0.0f, 255.0f);\n"\
"            for (j = 0; j < 16; j++)\n"\
"            {\n"\
"                MEMBER(points[0], X) += coeff[0][j] * MEMBER(trans_pixel[j], X);\n"\
"                MEMBER(points[1], X) += coeff[1][j] * MEMBER(trans_pixel[j], X);\n"\
"                MEMBER(points[2], X) += coeff[2][j] * MEMBER(trans_pixel[j], X);\n"\
"\n"\
"                MEMBER(points[0], Y) += coeff[0][j] * MEMBER(trans_pixel[j], Y);\n"\
"                MEMBER(points[1], Y) += coeff[1][j] * MEMBER(trans_pixel[j], Y);\n"\
"                MEMBER(points[2], Y) += coeff[2][j] * MEMBER(trans_pixel[j], Y);\n"\
"\n"\
"                MEMBER(points[0], Z) += coeff[0][j] * MEMBER(trans_pixel[j], Z);\n"\
"                MEMBER(points[1], Z) += coeff[1][j] * MEMBER(trans_pixel[j], Z);\n"\
"                MEMBER(points[2], Z) += coeff[2][j] * MEMBER(trans_pixel[j], Z);\n"\
"            }\n"\
"            points[0] = points[0] * (1.0f / 80.0f);\n"\
"            points[1] = points[1] * (1.0f / 80.0f);\n"\
"            points[2] = points[2] * (1.0f / 80.0f);\n"\
"\n"\
"            points[0] = clamp(points[0], 0.0f, 255.0f);\n"\
"            points[1] = clamp(points[1], 0.0f, 255.0f);\n"\
"            points[2] = clamp(points[2], 0.0f, 255.0f);\n"\
"\n"\
"            points_i32[0] = INT3(ETC_RGBRoundTo6Bit((uchar)MEMBER(points[0], X)), ETC_RGBRoundTo7Bit((uchar)MEMBER(points[0], Y)), ETC_RGBRoundTo6Bit((uchar)MEMBER(points[0], Z)));\n"\
"            points_i32[1] = INT3(ETC_RGBRoundTo6Bit((uchar)MEMBER(points[1], X)), ETC_RGBRoundTo7Bit((uchar)MEMBER(points[1], Y)), ETC_RGBRoundTo6Bit((uchar)MEMBER(points[1], Z)));\n"\
"            points_i32[2] = INT3(ETC_RGBRoundTo6Bit((uchar)MEMBER(points[2], X)), ETC_RGBRoundTo7Bit((uchar)MEMBER(points[2], Y)), ETC_RGBRoundTo6Bit((uchar)MEMBER(points[2], Z)));\n"\
"            for (index = 0; index < 3; index++)\n"\
"                index_best_dist[index] = MAX_INIT_ERROR;\n"\
"\n"\
"            for (twiddle0 = -2; twiddle0 <= 2; twiddle0++)\n"\
"            {\n"\
"                for (twiddle1 = -2; twiddle1 <= 2; twiddle1++)\n"\
"                {\n"\
"                    for (twiddle2 = -2; twiddle2 <= 2; twiddle2++)\n"\
"                    {\n"\
"                        int ppoints[3][3];\n"\
"                        float comp_err[3];\n"\
"                        int comb;\n"\
"\n"\
"                        comb =  (MEMBER(points_i32[0], X) + twiddle0 * 4) | (MEMBER(points_i32[1], X) + twiddle1 * 4) | (MEMBER(points_i32[2], X) + twiddle2 * 4) |\n"\
"                            (MEMBER(points_i32[0], Y) + twiddle0 * 2) | (MEMBER(points_i32[1], Y) + twiddle1 * 2) | (MEMBER(points_i32[2], Y) + twiddle2 * 2) |\n"\
"                            (MEMBER(points_i32[0], Z) + twiddle0 * 4) | (MEMBER(points_i32[1], Z) + twiddle1 * 4) | (MEMBER(points_i32[2], Z) + twiddle2 * 4);\n"\
"\n"\
"                        // trick: this tests if any of the values has negative sign or is >255, halving the number of comparisons needed\n"\
"                        if (comb & 0xFFFFFF00)\n"\
"                            continue;\n"\
"\n"\
"                        ppoints[0][0] = ETC_RGBRoundTo6Bit((MEMBER(points_i32[0], X) + twiddle0 * 4));\n"\
"                        ppoints[0][1] = ETC_RGBRoundTo6Bit((MEMBER(points_i32[1], X) + twiddle1 * 4));\n"\
"                        ppoints[0][2] = ETC_RGBRoundTo6Bit((MEMBER(points_i32[2], X) + twiddle2 * 4));\n"\
"\n"\
"                        ppoints[1][0] = ETC_RGBRoundTo7Bit((MEMBER(points_i32[0], Y) + twiddle0 * 2));\n"\
"                        ppoints[1][1] = ETC_RGBRoundTo7Bit((MEMBER(points_i32[1], Y) + twiddle1 * 2));\n"\
"                        ppoints[1][2] = ETC_RGBRoundTo7Bit((MEMBER(points_i32[2], Y) + twiddle2 * 2));\n"\
"\n"\
"                        ppoints[2][0] = ETC_RGBRoundTo6Bit((MEMBER(points_i32[0], Z) + twiddle0 * 4));\n"\
"                        ppoints[2][1] = ETC_RGBRoundTo6Bit((MEMBER(points_i32[1], Z) + twiddle1 * 4));\n"\
"                        ppoints[2][2] = ETC_RGBRoundTo6Bit((MEMBER(points_i32[2], Z) + twiddle2 * 4));\n"\
"\n"\
"                        comp_err[0] = 0.0f;\n"\
"                        comp_err[1] = 0.0f;\n"\
"                        comp_err[2] = 0.0f;\n"\
"\n"\
"                        for (j = 0; j < 4; j++) // v\n"\
"                        {\n"\
"                            for (i = 0; i < 4; i++) // u\n"\
"                            {\n"\
"                                float3 v;\n"\
"\n"\
"                                MEMBER(v, X) = (float)((i * (ppoints[0][1] - ppoints[0][0]) + j * (ppoints[0][2] - ppoints[0][0]) + 4 * (ppoints[0][0]) + 2) >> 2);\n"\
"                                MEMBER(v, Y) = (float)((i * (ppoints[1][1] - ppoints[1][0]) + j * (ppoints[1][2] - ppoints[1][0]) + 4 * (ppoints[1][0]) + 2) >> 2);\n"\
"                                MEMBER(v, Z) = (float)((i * (ppoints[2][1] - ppoints[2][0]) + j * (ppoints[2][2] - ppoints[2][0]) + 4 * (ppoints[2][0]) + 2) >> 2);\n"\
"\n"\
"                                v = clamp(v, VFLOAT3(0.0f, 0.0f, 0.0f), VFLOAT3(255.0f, 255.0f, 255.0f));\n"\
"                                v = v - trans_pixel[j*4 + i];\n"\
"\n"\
"                                comp_err[0] += MEMBER(v, X) * MEMBER(v, X);\n"\
"                                comp_err[1] += MEMBER(v, Y) * MEMBER(v, Y);\n"\
"                                comp_err[2] += MEMBER(v, Z) * MEMBER(v, Z);\n"\
"                            }\n"\
"                        }\n"\
"                        for (index = 0; index < 3; index++)\n"\
"                        {\n"\
"                            if (comp_err[index] < index_best_dist[index])\n"\
"                            {\n"\
"                                int scale = (index == 1 ? 2 : 4);\n"\
"                                best_twiddle[index][0] = twiddle0 * scale;\n"\
"                                best_twiddle[index][1] = twiddle1 * scale;\n"\
"                                best_twiddle[index][2] = twiddle2 * scale;\n"\
"                                index_best_dist[index] = comp_err[index];\n"\
"                            }\n"\
"                        }\n"\
"                    }\n"\
"                }\n"\
"            }\n"\
"            best_dist = index_best_dist[0] + index_best_dist[1] + index_best_dist[2];\n"\
"            if (best_dist < best_total_error)\n"\
"            {\n"\
"                params_planar.rgb[0] = UCHAR3(ETC_RGBRoundTo6Bit(MEMBER(points_i32[0], X) + best_twiddle[0][0]), ETC_RGBRoundTo7Bit(MEMBER(points_i32[0], Y) + best_twiddle[1][0]), ETC_RGBRoundTo6Bit(MEMBER(points_i32[0], Z) + best_twiddle[2][0]));\n"\
"                params_planar.rgb[1] = UCHAR3(ETC_RGBRoundTo6Bit(MEMBER(points_i32[1], X) + best_twiddle[0][1]), ETC_RGBRoundTo7Bit(MEMBER(points_i32[1], Y) + best_twiddle[1][1]), ETC_RGBRoundTo6Bit(MEMBER(points_i32[1], Z) + best_twiddle[2][1]));\n"\
"                params_planar.rgb[2] = UCHAR3(ETC_RGBRoundTo6Bit(MEMBER(points_i32[2], X) + best_twiddle[0][2]), ETC_RGBRoundTo7Bit(MEMBER(points_i32[2], Y) + best_twiddle[1][2]), ETC_RGBRoundTo6Bit(MEMBER(points_i32[2], Z) + best_twiddle[2][2]));\n"\
"\n"\
"                enc_mode = ETC_ENC_MODE_PLANAR;\n"\
"\n"\
"                best_total_error = best_dist;\n"\
"            }\n"\
"        }\n"\
"    }\n"\
"\n"\
"    if ((enc_mode == ETC_ENC_MODE_DELTA) || (enc_mode == ETC_ENC_MODE_NODELTA))\n"\
"    {\n"\
"        if (enc_mode == ETC_ENC_MODE_NODELTA)\n"\
"        {\n"\
"            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], X) >> 4, 28, 4);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[1], X) >> 4, 24, 4);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], Y) >> 4, 20, 4);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[1], Y) >> 4, 16, 4);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], Z) >> 4, 12, 4);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[1], Z) >> 4,  8, 4);\n"\
"            ETC_WriteBits(local_block, 0, 1, 1); // diff bit\n"\
"        }\n"\
"        else\n"\
"        {\n"\
"            int3 diff;\n"\
"\n"\
"            MEMBER(diff, X) = (MEMBER(params_partition.rgb[1], X) >> 3) - (MEMBER(params_partition.rgb[0], X) >> 3);\n"\
"            MEMBER(diff, Y) = (MEMBER(params_partition.rgb[1], Y) >> 3) - (MEMBER(params_partition.rgb[0], Y) >> 3);\n"\
"            MEMBER(diff, Z) = (MEMBER(params_partition.rgb[1], Z) >> 3) - (MEMBER(params_partition.rgb[0], Z) >> 3);\n"\
"\n"\
"            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], X) >> 3, 27, 5);\n"\
"            ETC_WriteBits(local_block, MEMBER(diff, X) >> 0, 24, 3);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], Y) >> 3, 19, 5);\n"\
"            ETC_WriteBits(local_block, MEMBER(diff, Y) >> 0, 16, 3);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], Z) >> 3, 11, 5);\n"\
"            ETC_WriteBits(local_block, MEMBER(diff, Z) >> 0,  8, 3);\n"\
"            ETC_WriteBits(local_block, 1, 1, 1); // diff bit\n"\
"        }\n"\
"        ETC_WriteBits(local_block, params_partition.table[0], 5, 3); // table codeword 1\n"\
"        ETC_WriteBits(local_block, params_partition.table[1], 2, 3); // table codeword 2\n"\
"        ETC_WriteBits(local_block, params_partition.is_flipped, 0, 1); // flip bit\n"\
"\n"\
"        for (i = 0; i < 16; i++)\n"\
"        {\n"\
"            int index = (i%4)*4 + i/4;\n"\
"\n"\
"            int idx = params_partition.indexes[i];\n"\
"\n"\
"            ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);\n"\
"            ETC_WriteBits(local_block, idx & 1, 32 + index, 1);\n"\
"\n"\
"        }\n"\
"        ETC_PackBlockSwapOrder(block, local_block);\n"\
"    }\n"\
"    if (is_etc2)\n"\
"    {\n"\
"        if (enc_mode == ETC_ENC_MODE_T)\n"\
"        {\n"\
"            int min_rd = -4 + ((MEMBER(params_th.rgb[0], X) >> 4) & 3);\n"\
"            int max_rd = ((MEMBER(params_th.rgb[0], X) >> 4) & 3);\n"\
"            int min_r = (MEMBER(params_th.rgb[0], X) >> 6) & 3;\n"\
"            int max_r = 28 + min_r;\n"\
"            uchar r;\n"\
"            uchar rd;\n"\
"\n"\
"            if (min_rd + min_r < 0)\n"\
"            {\n"\
"                r = min_r;\n"\
"                rd = min_rd;\n"\
"            }\n"\
"            else\n"\
"            {\n"\
"                r = max_r;\n"\
"                rd = max_rd;\n"\
"            }\n"\
"\n"\
"            ETC_WriteBits(local_block, r, 27, 5);\n"\
"            ETC_WriteBits(local_block, rd, 24, 3);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Y) >> 4, 20, 4);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Z) >> 4, 16, 4);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], X) >> 4, 12, 4);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Y) >> 4,  8, 4);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Z) >> 4,  4, 4);\n"\
"\n"\
"            ETC_WriteBits(local_block, (params_th.table >> 1) & 3, 2, 2);\n"\
"            ETC_WriteBits(local_block, 1, 1, 1); // diff bit\n"\
"            ETC_WriteBits(local_block, params_th.table & 1, 0, 1); // flip bit\n"\
"\n"\
"            for (i = 0; i < 16; i++)\n"\
"            {\n"\
"                int index = (i % 4) * 4 + i / 4;\n"\
"\n"\
"                int idx = params_th.indexes[i];\n"\
"\n"\
"                ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);\n"\
"                ETC_WriteBits(local_block, idx & 1, 32 + index, 1);\n"\
"\n"\
"            }\n"\
"            ETC_PackBlockSwapOrder(block, local_block);\n"\
"        }\n"\
"        else if (enc_mode == ETC_ENC_MODE_H)\n"\
"        {\n"\
"            int min_gd = -4 + ((MEMBER(params_th.rgb[0], Z) >> 5) & 3);\n"\
"            int max_gd = ((MEMBER(params_th.rgb[0], Z) >> 5) & 3);\n"\
"            int min_g = ((MEMBER(params_th.rgb[0], Z) >> 7) & 1) | (((MEMBER(params_th.rgb[0], Y) >> 4) & 1) << 1);\n"\
"            int max_g = 28 + min_g;\n"\
"            uchar g;\n"\
"            uchar gd;\n"\
"            int rd;\n"\
"            if (min_gd + min_g < 0)\n"\
"            {\n"\
"                g = min_g;\n"\
"                gd = min_gd;\n"\
"            }\n"\
"            else\n"\
"            {\n"\
"                g = max_g;\n"\
"                gd = max_gd;\n"\
"            }\n"\
"\n"\
"            rd = MEMBER(params_th.rgb[0], Y) >> 5;\n"\
"            if (rd >= 4)\n"\
"                rd = -4 + (rd & 3);\n"\
"\n"\
"            if ((int)(MEMBER(params_th.rgb[0], X) >> 4) + rd < 0)\n"\
"                ETC_WriteBits(local_block, 1, 31, 1);\n"\
"            else\n"\
"                ETC_WriteBits(local_block, 0, 31, 1);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], X) >> 4, 27, 4);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Y) >> 5, 24, 3);\n"\
"            ETC_WriteBits(local_block, g, 19, 5);\n"\
"            ETC_WriteBits(local_block, gd, 16, 3);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Z) >> 4, 15, 1);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], X) >> 4, 11, 4);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Y) >> 4,  7, 4);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Z) >> 4,  3, 4);\n"\
"\n"\
"            ETC_WriteBits(local_block, (params_th.table >> 2) & 1, 2, 1);\n"\
"            ETC_WriteBits(local_block, 1, 1, 1); // diff bit\n"\
"            ETC_WriteBits(local_block, (params_th.table >> 1) & 1 & 1, 0, 1); // flip bit\n"\
"\n"\
"            for (i = 0; i < 16; i++)\n"\
"            {\n"\
"                int index = (i % 4) * 4 + i / 4;\n"\
"\n"\
"                int idx = params_th.indexes[i];\n"\
"\n"\
"                ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);\n"\
"                ETC_WriteBits(local_block, idx & 1, 32 + index, 1);\n"\
"\n"\
"            }\n"\
"            ETC_PackBlockSwapOrder(block, local_block);\n"\
"        }\n"\
"        else if (enc_mode == ETC_ENC_MODE_PLANAR)\n"\
"        {\n"\
"            int r, g, b;\n"\
"            int rd, gd, bd;\n"\
"            int min_bd;\n"\
"            int max_bd;\n"\
"            int min_b;\n"\
"            int max_b;\n"\
"            MEMBER(params_planar.rgb[0], X) >>= 2;\n"\
"            MEMBER(params_planar.rgb[0], Y) >>= 1;\n"\
"            MEMBER(params_planar.rgb[0], Z) >>= 2;\n"\
"\n"\
"            MEMBER(params_planar.rgb[1], X) >>= 2;\n"\
"            MEMBER(params_planar.rgb[1], Y) >>= 1;\n"\
"            MEMBER(params_planar.rgb[1], Z) >>= 2;\n"\
"\n"\
"            MEMBER(params_planar.rgb[2], X) >>= 2;\n"\
"            MEMBER(params_planar.rgb[2], Y) >>= 1;\n"\
"            MEMBER(params_planar.rgb[2], Z) >>= 2;\n"\
"\n"\
"            ETC_WriteBits(local_block, MEMBER(params_planar.rgb[2], Z), 32, 6);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_planar.rgb[2], Y), 38, 7);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_planar.rgb[2], X), 45, 6);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_planar.rgb[1], Z), 51, 6);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_planar.rgb[1], Y), 57, 7);\n"\
"\n"\
"            ETC_WriteBits(local_block, (MEMBER(params_planar.rgb[1], X)) & 1, 0, 1);\n"\
"            ETC_WriteBits(local_block, 1, 1, 1);\n"\
"            ETC_WriteBits(local_block, (MEMBER(params_planar.rgb[1], X) >> 1) & 31, 2, 5);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_planar.rgb[0], Z) & 7, 7, 3);\n"\
"            ETC_WriteBits(local_block, (MEMBER(params_planar.rgb[0], Z) >> 3) & 7, 11, 2);\n"\
"            ETC_WriteBits(local_block, (MEMBER(params_planar.rgb[0], Z) >> 5) & 1, 16, 1);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_planar.rgb[0], Y) & 63, 17, 6);\n"\
"            ETC_WriteBits(local_block, (MEMBER(params_planar.rgb[0], Y) >> 6) & 1, 24, 1);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_planar.rgb[0], X), 25, 6);\n"\
"\n"\
"            r = (MEMBER(params_planar.rgb[0], X) >> 2) & 63;\n"\
"            rd = (MEMBER(params_planar.rgb[0], Y) >> 6) | ((MEMBER(params_planar.rgb[0], X) & 3) << 1);\n"\
"            g = (MEMBER(params_planar.rgb[0], Y) >> 2) & 15;\n"\
"            gd = (MEMBER(params_planar.rgb[0], Z) >> 5) | ((MEMBER(params_planar.rgb[0], Y) & 3) << 1);\n"\
"            b = (MEMBER(params_planar.rgb[0], Z) >> 3) & 3;\n"\
"            bd = (MEMBER(params_planar.rgb[0], Z) >> 1) & 3;\n"\
"\n"\
"            if (rd >= 4)\n"\
"                rd = -4 + (rd & 3);\n"\
"            if (gd >= 4)\n"\
"                gd = -4 + (gd & 3);\n"\
"            if (bd >= 4)\n"\
"                bd = -4 + (bd & 3);\n"\
"\n"\
"            if (r + rd < 0)\n"\
"                ETC_WriteBits(local_block, 1, 31, 1);\n"\
"            else\n"\
"                ETC_WriteBits(local_block, 0, 31, 1);\n"\
"\n"\
"            if (g + gd < 0)\n"\
"                ETC_WriteBits(local_block, 1, 23, 1);\n"\
"            else\n"\
"                ETC_WriteBits(local_block, 0, 23, 1);\n"\
"\n"\
"            min_bd = -4 + bd;\n"\
"            max_bd = bd;\n"\
"            min_b = b;\n"\
"            max_b = 28 + min_b;\n"\
"\n"\
"            if (min_b + min_bd < 0)\n"\
"            {\n"\
"                ETC_WriteBits(local_block, min_bd, 8, 3);\n"\
"                ETC_WriteBits(local_block, min_b, 11, 5);\n"\
"            }\n"\
"            else\n"\
"            {\n"\
"                ETC_WriteBits(local_block, max_bd, 8, 3);\n"\
"                ETC_WriteBits(local_block, max_b, 11, 5);\n"\
"            }\n"\
"            ETC_PackBlockSwapOrder(block, local_block);\n"\
"        }\n"\
"    }\n"\
"}\n"\
"\n"\
"void ETC_EncodeRGB(\n"\
"    int quality,\n"\
"    int allowed_modes,\n"\
"    float error_target,\n"\
"    int refine_search,\n"\
"    int is_etc2,\n"\
"    int is_ypbpr,\n"\
"    float4 *pixel,\n"\
"    __global uchar *block)\n"\
"{\n"\
"    if (quality == CODEC_QUALITY_FAST)\n"\
"        ETC_EncodeRGBFast(allowed_modes, is_etc2, is_ypbpr, pixel, block);\n"\
"    else\n"\
"        ETC_EncodeRGBQuality(quality, allowed_modes, error_target, refine_search, is_etc2, is_ypbpr, pixel, block);\n"\
"}\n"\
"\n"\
"float ETC_EvaluateErrorAlpha(float *alpha, float base_alpha, float mul, int table)\n"\
"{\n"\
"    int i;\n"\
"    int j;\n"\
"    float total_err = 0.0f;\n"\
"    float point[8];\n"\
"\n"\
"    for (i = 0; i < 8; i++)\n"\
"        point[i] = clamp(base_alpha + mul * g_alpha[table][i], 0.0f, 255.0f);\n"\
"\n"\
"    for (i = 0; i < 16; i++)\n"\
"    {\n"\
"        float best_err = MAX_INIT_ERROR;\n"\
"        for (j = 0; j < 8; j++)\n"\
"        {\n"\
"            float err = (alpha[i] - point[j]) * (alpha[i] - point[j]);\n"\
"            if (err < best_err)\n"\
"                best_err = err;\n"\
"        }\n"\
"        total_err += best_err;\n"\
"    }\n"\
"    return total_err;\n"\
"}\n"\
"\n"\
"float ETC_FindBestBaseAlpha(float *alpha, float alpha_mins, float alpha_maxs, float mul, int table, int *best_base_alpha)\n"\
"{\n"\
"    int k;\n"\
"    float a = alpha_mins;\n"\
"    float b = alpha_maxs;\n"\
"    float c = b - (b - a) * M_INV_GOLDEN_F;\n"\
"    float d = a + (b - a) * M_INV_GOLDEN_F;\n"\
"    float best_error = MAX_INIT_ERROR;\n"\
"    float fc = 0.0f;\n"\
"    float fd = 0.0f;\n"\
"\n"\
"    fc = ETC_EvaluateErrorAlpha(alpha, floor(c + 0.5f), mul, table);\n"\
"    fd = ETC_EvaluateErrorAlpha(alpha, floor(d + 0.5f), mul, table);\n"\
"\n"\
"    for (k = 0; (k < 16) && (b - a) > 0.5f; k++)\n"\
"    {\n"\
"        if (fc < fd)\n"\
"        {\n"\
"            b = d;\n"\
"            c = b - (b - a) * M_INV_GOLDEN_F;\n"\
"            d = a + (b - a) * M_INV_GOLDEN_F;\n"\
"            fd = fc;\n"\
"            fc = ETC_EvaluateErrorAlpha(alpha, floor(c + 0.5f), mul, table);\n"\
"        }\n"\
"        else\n"\
"        {\n"\
"            a = c;\n"\
"            c = b - (b - a) * M_INV_GOLDEN_F;\n"\
"            d = a + (b - a) * M_INV_GOLDEN_F;\n"\
"            fc = fd;\n"\
"            fd = ETC_EvaluateErrorAlpha(alpha, floor(d + 0.5f), mul, table);\n"\
"        }\n"\
"    }\n"\
"    if (fc < fd)\n"\
"    {\n"\
"        *best_base_alpha = (int)c;\n"\
"        return fc;\n"\
"    }\n"\
"    else\n"\
"    {\n"\
"        *best_base_alpha = (int)d;\n"\
"        return fd;\n"\
"    }\n"\
"}\n"\
"\n"\
"void ETC_GetOptimalIndexesAlpha(float *alpha, float base_alpha, float mul, int table, int *indexes)\n"\
"{\n"\
"    int i;\n"\
"    int j;\n"\
"    float point[8];\n"\
"\n"\
"    for (i = 0; i < 8; i++)\n"\
"        point[i] = clamp(base_alpha + mul * g_alpha[table][i], 0.0f, 255.0f);\n"\
"\n"\
"    for (i = 0; i < 16; i++)\n"\
"    {\n"\
"        float best_err = MAX_INIT_ERROR;\n"\
"        for (j = 0; j < 8; j++)\n"\
"        {\n"\
"            float err = (alpha[i] - point[j]) * (alpha[i] - point[j]);\n"\
"            if (err < best_err)\n"\
"            {\n"\
"                best_err = err;\n"\
"                indexes[i] = j;\n"\
"            }\n"\
"        }\n"\
"    }\n"\
"}\n"\
"\n"\
"void ETC_EncodeAlpha(\n"\
"    float error_target,\n"\
"    int refine_search,\n"\
"    int search_radius,\n"\
"    float4 *pixel,\n"\
"    __global uchar *block)\n"\
"{\n"\
"    float alpha[16];\n"\
"    float alpha_mins;\n"\
"    float alpha_maxs;\n"\
"    float alpha_mid;\n"\
"    float alpha_half_range;\n"\
"    float best_error = MAX_INIT_ERROR;\n"\
"    float best_mul;\n"\
"    int best_table;\n"\
"    int i, j;\n"\
"    int alpha_index[16];\n"\
"    int best_base_alpha;\n"\
"    uchar local_block[8];\n"\
"\n"\
"    for (i = 0; i < 16; i++)\n"\
"        alpha[i] = MEMBER(pixel[i], W);\n"\
"\n"\
"    alpha_mins = alpha[0];\n"\
"    alpha_maxs = alpha[0];\n"\
"        for (i = 1; i < 16; i++)\n"\
"        {\n"\
"            alpha_mins = min(alpha_mins, alpha[i]);\n"\
"            alpha_maxs = max(alpha_maxs, alpha[i]);\n"\
"        }\n"\
"    alpha_mid = floor((alpha_mins + alpha_maxs) * 0.5f + 0.5f);\n"\
"    alpha_half_range = (alpha_maxs - alpha_mins) * 0.5f;\n"\
"        for (i = 0; i < 16; i++)\n"\
"        {\n"\
"            int lower_mul = (int)clamp((int)max(floor(2.0f * alpha_half_range / g_alpha_range[i]), 1.0f) - search_radius, 1, 16 - (search_radius * 2 + 1));\n"\
"            for (j = 0; j < search_radius * 2 + 1; j++)\n"\
"            {\n"\
"                float mul = (float)lower_mul + (float)j;\n"\
"                float err = ETC_EvaluateErrorAlpha(alpha, alpha_mid, mul, i);\n"\
"                    if (err < best_error)\n"\
"                    {\n"\
"                        best_table = i;\n"\
"                        best_error = err;\n"\
"                        best_mul = mul;\n"\
"                        best_base_alpha = (int)alpha_mid;\n"\
"                    }\n"\
"                if (refine_search)\n"\
"                {\n"\
"                    int base_alpha[2];\n"\
"                    float err_left = ETC_FindBestBaseAlpha(alpha, alpha_mins, alpha_mid, mul, i, &base_alpha[0]);\n"\
"                    float err_right = ETC_FindBestBaseAlpha(alpha, alpha_mid, alpha_maxs, mul, i, &base_alpha[1]);\n"\
"\n"\
"                    if (err_left < best_error)\n"\
"                    {\n"\
"                        best_table = i;\n"\
"                        best_error = err_left;\n"\
"                        best_mul = mul;\n"\
"                        best_base_alpha = base_alpha[0];\n"\
"                    }\n"\
"                    if (err_right < best_error)\n"\
"                    {\n"\
"                        best_table = i;\n"\
"                        best_error = err_right;\n"\
"                        best_mul = mul;\n"\
"                        best_base_alpha = base_alpha[1];\n"\
"                    }\n"\
"                }\n"\
"            }\n"\
"\n"\
"        }\n"\
"    ETC_GetOptimalIndexesAlpha(alpha, (float)best_base_alpha, best_mul, best_table, alpha_index);\n"\
"\n"\
"    //printf(\"alpha_mins %3f, alpha_maxs: %3f, best_base_alpha: %3i, best_mul: %3i, best_table: %3i\\n\", alpha_mins, alpha_maxs, best_base_alpha, best_mul, best_table);\n"\
"    ETC_WriteBits(local_block, (uint)best_base_alpha, 56, 8);\n"\
"    ETC_WriteBits(local_block, (uint)best_mul, 52, 4);\n"\
"    ETC_WriteBits(local_block, best_table, 48, 4);\n"\
"\n"\
"    for (i = 0; i < 16; i++)\n"\
"    {\n"\
"        int index = (i % 4) * 4 + i / 4;\n"\
"        ETC_WriteBits(local_block, alpha_index[i], 45 - index * 3, 3);\n"\
"    }\n"\
"    ETC_PackBlockReverseOrder(block, local_block);\n"\
"}\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"float ETC_EvaluateErrorA1(int *transparency, int is_ypbpr, float3 *trans_pixel, uchar3 rgb, __constant const int *partition_indexes)\n"\
"{\n"\
"    int i, table, j;\n"\
"    float best_table_dist = MAX_INIT_ERROR;\n"\
"    float3 rgb32f = VFLOAT3(MEMBER(rgb, X), MEMBER(rgb, Y), MEMBER(rgb, Z));\n"\
"\n"\
"    for (table = 0; table < 8; table++)\n"\
"    {\n"\
"        float current_table_dist = 0.0f;\n"\
"        for (i = 0; i < 8; i++)\n"\
"        {\n"\
"            float best_dist = MAX_INIT_ERROR;\n"\
"\n"\
"            if (transparency[partition_indexes[i]])\n"\
"                continue;\n"\
"\n"\
"            for (j = 0; j < 4; j++)\n"\
"            {\n"\
"                float3 temp_pixel;\n"\
"                float3 delta;\n"\
"\n"\
"                if (j == 0)     // RGBA = 0\n"\
"                    temp_pixel = rgb32f;\n"\
"                else if (j == 2)\n"\
"                    continue;\n"\
"                else\n"\
"                    temp_pixel = clamp(rgb32f + VFLOAT3(g_table[table][j], g_table[table][j], g_table[table][j]), 0.0f, 255.0f);\n"\
"\n"\
"                if (is_ypbpr)\n"\
"                    delta = ETC_ConvertToYPBPRf3(temp_pixel) - trans_pixel[partition_indexes[i]];\n"\
"                else\n"\
"                    delta = temp_pixel - trans_pixel[partition_indexes[i]];\n"\
"\n"\
"                float lensq = dot(delta, delta);\n"\
"\n"\
"                if (lensq < best_dist)\n"\
"                    best_dist = lensq;\n"\
"            }\n"\
"            current_table_dist += best_dist;\n"\
"        }\n"\
"        if (current_table_dist < best_table_dist)\n"\
"        {\n"\
"            best_table_dist = current_table_dist;\n"\
"        }\n"\
"    }\n"\
"    return best_table_dist;\n"\
"}\n"\
"\n"\
"float ETC_EvaluateErrorTSingleA1(int *transparency, int is_ypbpr, float3 *trans_pixel, uchar3 rgb, int *indexes, int num_indexes)\n"\
"{\n"\
"    int i;\n"\
"    float dist = 0.0f;\n"\
"    float3 rgb32f;\n"\
"\n"\
"    if (!num_indexes)\n"\
"        return 0.0f;\n"\
"\n"\
"    rgb32f = VFLOAT3(MEMBER(rgb, X), MEMBER(rgb, Y), MEMBER(rgb, Z));\n"\
"\n"\
"    if (is_ypbpr)\n"\
"        rgb32f = ETC_ConvertToYPBPRf3(rgb32f);\n"\
"\n"\
"    for (i = 0; i < num_indexes; i++)\n"\
"    {\n"\
"        float3 delta;\n"\
"\n"\
"        if (transparency[indexes[i]])\n"\
"            continue;\n"\
"\n"\
"        delta = rgb32f - trans_pixel[indexes[i]];\n"\
"        dist += dot(delta, delta);\n"\
"    }\n"\
"\n"\
"    return dist;\n"\
"}\n"\
"float ETC_EvaluateErrorTTripleA1(int *transparency, int is_ypbpr, float3 *trans_pixel, uchar3 rgb, int *indexes, int num_indexes)\n"\
"{\n"\
"    int i, mode, j;\n"\
"    float dist = 0.0f;\n"\
"    float3 rgb32f;\n"\
"    float best_mode_dist;\n"\
"\n"\
"    if (!num_indexes)\n"\
"        return 0.0f;\n"\
"\n"\
"    rgb32f = VFLOAT3(MEMBER(rgb, X), MEMBER(rgb, Y), MEMBER(rgb, Z));\n"\
"    best_mode_dist = MAX_INIT_ERROR;\n"\
"\n"\
"    for (mode = 0; mode < 8; mode++)\n"\
"    {\n"\
"        float current_mode_dist = 0.0f;\n"\
"        float3 points[2];\n"\
"        points[0] = clamp(rgb32f + VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);\n"\
"        points[1] = clamp(rgb32f - VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);\n"\
"\n"\
"        if (is_ypbpr)\n"\
"        {\n"\
"            points[0] = ETC_ConvertToYPBPRf3(points[0]);\n"\
"            points[1] = ETC_ConvertToYPBPRf3(points[1]);\n"\
"        }\n"\
"\n"\
"        for (i = 0; i < num_indexes; i++)\n"\
"        {\n"\
"            float best_dist = MAX_INIT_ERROR;\n"\
"\n"\
"            if (transparency[indexes[i]])\n"\
"                continue;\n"\
"\n"\
"            for (j = 0; j < 2; j++)\n"\
"            {\n"\
"                float3 delta;\n"\
"                float lensq;\n"\
"                delta = points[j] - trans_pixel[indexes[i]];\n"\
"                lensq = dot(delta, delta);\n"\
"                if (lensq < best_dist)\n"\
"                    best_dist = lensq;\n"\
"            }\n"\
"            current_mode_dist += best_dist;\n"\
"        }\n"\
"        if (current_mode_dist < best_mode_dist)\n"\
"        {\n"\
"            best_mode_dist = current_mode_dist;\n"\
"        }\n"\
"    }\n"\
"\n"\
"    return best_mode_dist;\n"\
"}\n"\
"\n"\
"float ETC_EvaluateErrorHA1(int *transparency, int is_ypbpr, float3 *trans_pixel, uchar3 rgb, int *indexes, int num_indexes, int mode, int h_index)\n"\
"{\n"\
"    int i, j;\n"\
"    float dist = 0.0f;\n"\
"    float3 rgb32f;\n"\
"    float current_mode_dist = 0.0f;\n"\
"    float3 points[2];\n"\
"    int num_points;\n"\
"\n"\
"    if (!num_indexes)\n"\
"        return 0.0f;\n"\
"\n"\
"    rgb32f = VFLOAT3(MEMBER(rgb, X), MEMBER(rgb, Y), MEMBER(rgb, Z));\n"\
"\n"\
"    if (h_index == 1)\n"\
"    {\n"\
"        num_points = 1;\n"\
"        points[0] = clamp(rgb32f - VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);\n"\
"    }\n"\
"    else\n"\
"    {\n"\
"        num_points = 2;\n"\
"        points[0] = clamp(rgb32f + VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);\n"\
"        points[1] = clamp(rgb32f - VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);\n"\
"    }\n"\
"\n"\
"    if (is_ypbpr)\n"\
"    {\n"\
"        for (j = 0; j < num_points; j++)\n"\
"            points[j] = ETC_ConvertToYPBPRf3(points[j]);\n"\
"    }\n"\
"\n"\
"    for (i = 0; i < num_indexes; i++)\n"\
"    {\n"\
"        float best_dist = MAX_INIT_ERROR;\n"\
"\n"\
"        if (transparency[indexes[i]])\n"\
"            continue;\n"\
"\n"\
"        for (j = 0; j < num_points; j++)\n"\
"        {\n"\
"            float3 delta;\n"\
"            float lensq;\n"\
"\n"\
"            delta = points[j] - trans_pixel[indexes[i]];\n"\
"            lensq = dot(delta, delta);\n"\
"\n"\
"            if (lensq < best_dist)\n"\
"                best_dist = lensq;\n"\
"        }\n"\
"        current_mode_dist += best_dist;\n"\
"    }\n"\
"\n"\
"    return current_mode_dist;\n"\
"}\n"\
"\n"\
"\n"\
"float EvaluateErrorGenericA1(int mode, int *transparency, int is_ypbpr, float3 *trans_pixel, uchar3 rgb, etc_pathing_params_t *pathing_params)\n"\
"{\n"\
"    switch (mode)\n"\
"    {\n"\
"    case ETC_EVALUATEDELTAERRORGENERICA1:\n"\
"        return ETC_EvaluateErrorA1(transparency, is_ypbpr, trans_pixel, rgb, pathing_params->partition_indexes);\n"\
"    case ETC_EVALUATETSINGLEERRORGENERICA1:\n"\
"        return ETC_EvaluateErrorTSingleA1(transparency, is_ypbpr, trans_pixel, rgb, pathing_params->indexes, pathing_params->num_indexes);\n"\
"    case ETC_EVALUATETTRIPLEERRORGENERICA1:\n"\
"        return ETC_EvaluateErrorTTripleA1(transparency, is_ypbpr, trans_pixel, rgb, pathing_params->indexes, pathing_params->num_indexes);\n"\
"    case ETC_EVALUATEHERRORGENERICA1:\n"\
"        return ETC_EvaluateErrorHA1(transparency, is_ypbpr, trans_pixel, rgb, pathing_params->indexes, pathing_params->num_indexes, pathing_params->mode, pathing_params->h_index);\n"\
"    default:\n"\
"        return MAX_INIT_ERROR;\n"\
"    }\n"\
"}\n"\
"\n"\
"void ETC_LeastCostDirectedPathA1(\n"\
"    int step,\n"\
"    int sample_list_entries,\n"\
"    int *transparency,\n"\
"    float error_target,\n"\
"    int refine_search,\n"\
"    int is_ypbpr,\n"\
"    float3 *trans_pixel,\n"\
"    etc_sample_t sample,\n"\
"    etc_sample_t *sample_list,\n"\
"    int x_max,\n"\
"    int y_max,\n"\
"    int z_max,\n"\
"    etc_pathing_params_t *pathing_params,\n"\
"    int expand_cb_fp,\n"\
"    int evaluate_cb_fp)\n"\
"{\n"\
"    int         i;\n"\
"    int         j;\n"\
"    int         terminate;\n"\
"    float   dist[27];\n"\
"\n"\
"    for (i = 0, terminate = 0; terminate == 0; i++)\n"\
"    {\n"\
"        uchar3 test_pos[7];\n"\
"        float best_dist;\n"\
"        int best_index;\n"\
"        int terminate_count = 0;\n"\
"\n"\
"        ETC_AddSampleToList(sample_list_entries, &sample_list[0], sample);\n"\
"\n"\
"        if (sample.error <= error_target)\n"\
"            break;\n"\
"\n"\
"        int scale = step;\n"\
"\n"\
"        test_pos[0] = sample.pos_quantised + UCHAR3(scale, 0, 0);\n"\
"        test_pos[1] = sample.pos_quantised + UCHAR3(0, scale, 0);\n"\
"        test_pos[2] = sample.pos_quantised + UCHAR3(scale, scale, 0);\n"\
"        test_pos[3] = sample.pos_quantised + UCHAR3(0, 0, scale);\n"\
"        test_pos[4] = sample.pos_quantised + UCHAR3(scale, 0, scale);\n"\
"        test_pos[5] = sample.pos_quantised + UCHAR3(0, scale, scale);\n"\
"        test_pos[6] = sample.pos_quantised + UCHAR3(scale, scale, scale);\n"\
"\n"\
"        for (j = 0; j < 7; j++)\n"\
"        {\n"\
"            if ((MEMBER(test_pos[j], X) > x_max) || (MEMBER(test_pos[j], Y) > y_max) || (MEMBER(test_pos[j], Z) > z_max))\n"\
"                dist[j] = MAX_INIT_ERROR;\n"\
"            else\n"\
"            {\n"\
"                uchar3 v;\n"\
"\n"\
"                switch (expand_cb_fp)\n"\
"                {\n"\
"                case ETC_RGBEXPANDVECTO4BIT:\n"\
"                    v = ETC_RGBExpandVecTo4Bit(test_pos[j]);\n"\
"                    break;\n"\
"                case ETC_RGBEXPANDVECTO5BIT:\n"\
"                    v = ETC_RGBExpandVecTo5Bit(test_pos[j]);\n"\
"                    break;\n"\
"                }\n"\
"\n"\
"                dist[j] = EvaluateErrorGenericA1(evaluate_cb_fp, transparency, is_ypbpr, trans_pixel, v, pathing_params);\n"\
"            }\n"\
"        }\n"\
"\n"\
"        best_dist = dist[0];\n"\
"        best_index = 0;\n"\
"        for (j = 1; j < 7; j++)\n"\
"        {\n"\
"            if (dist[j] < best_dist)\n"\
"            {\n"\
"                best_dist = dist[j];\n"\
"                best_index = j;\n"\
"            }\n"\
"        }\n"\
"\n"\
"        for (j = 0; j < 7; j++)\n"\
"            if (dist[j] == MAX_INIT_ERROR)\n"\
"                terminate_count++;\n"\
"\n"\
"        if (terminate_count == 7)\n"\
"            break;\n"\
"\n"\
"        if (dist[best_index] > MAX_ERROR_DIFF_MUL * sample_list[0].error)\n"\
"            break;\n"\
"\n"\
"        sample.pos_quantised = test_pos[best_index];\n"\
"        sample.error = dist[best_index];\n"\
"    }\n"\
"\n"\
"    if (refine_search)\n"\
"    {\n"\
"        sample.pos_quantised = sample_list[0].pos_quantised;\n"\
"        sample.error = sample_list[0].error;\n"\
"\n"\
"        for (i = 0, terminate = 0; terminate == 0; i++)\n"\
"        {\n"\
"            short3 test_pos[27];\n"\
"            float best_dist;\n"\
"            int best_index;\n"\
"            int terminate_count = 0;\n"\
"\n"\
"            if (i != 1)\n"\
"                ETC_AddSampleToList(sample_list_entries, &sample_list[0], sample);\n"\
"\n"\
"            if (sample.error <= error_target)\n"\
"                break;\n"\
"\n"\
"            int scale = 1;\n"\
"\n"\
"            for (j = 0; j < 27; j++)\n"\
"                test_pos[j] = SHORT3(MEMBER(sample.pos_quantised, X), MEMBER(sample.pos_quantised, Y), MEMBER(sample.pos_quantised, Z)) + SHORT3((j % 3) - 1, ((j / 3) % 3) - 1, j/9 - 1);\n"\
"\n"\
"            for (j = 0; j < 27; j++)\n"\
"            {\n"\
"                if (j == 13)\n"\
"                    dist[j] = sample.error;\n"\
"                else if ((MEMBER(test_pos[j], X) > x_max) || (MEMBER(test_pos[j], Y) > y_max) || (MEMBER(test_pos[j], Z) > z_max) || (MEMBER(test_pos[j], X) < 0) || (MEMBER(test_pos[j], Y) < 0) || (MEMBER(test_pos[j], Z) < 0))\n"\
"                    dist[j] = MAX_INIT_ERROR;\n"\
"                else\n"\
"                {\n"\
"                    uchar3 v;\n"\
"\n"\
"                    switch (expand_cb_fp)\n"\
"                    {\n"\
"                    case ETC_RGBEXPANDVECTO4BIT:\n"\
"                        v = ETC_RGBExpandVecTo4Bit(UCHAR3(MEMBER(test_pos[j], X), MEMBER(test_pos[j], Y), MEMBER(test_pos[j], Z)));\n"\
"                        break;\n"\
"                    case ETC_RGBEXPANDVECTO5BIT:\n"\
"                        v = ETC_RGBExpandVecTo5Bit(UCHAR3(MEMBER(test_pos[j], X), MEMBER(test_pos[j], Y), MEMBER(test_pos[j], Z)));\n"\
"                        break;\n"\
"                    }\n"\
"\n"\
"                    dist[j] = EvaluateErrorGenericA1(evaluate_cb_fp, transparency, is_ypbpr, trans_pixel, v, pathing_params);\n"\
"                }\n"\
"            }\n"\
"\n"\
"            best_dist = dist[0];\n"\
"            best_index = 0;\n"\
"            for (j = 1; j < 27; j++)\n"\
"            {\n"\
"                if (dist[j] < best_dist)\n"\
"                {\n"\
"                    best_dist = dist[j];\n"\
"                    best_index = j;\n"\
"                }\n"\
"            }\n"\
"            if (dist[13] == best_dist)\n"\
"                break;\n"\
"\n"\
"            for (j = 0; j < 27; j++)\n"\
"                if (dist[j] == MAX_INIT_ERROR)\n"\
"                    terminate_count++;\n"\
"\n"\
"            if (terminate_count >= 26)\n"\
"                break;\n"\
"\n"\
"            if (dist[best_index] > MAX_ERROR_DIFF_MUL * sample_list[0].error)\n"\
"                break;\n"\
"\n"\
"            sample.pos_quantised = UCHAR3(MEMBER(test_pos[best_index], X), MEMBER(test_pos[best_index], Y), MEMBER(test_pos[best_index], Z));\n"\
"            sample.error = dist[best_index];\n"\
"        }\n"\
"    }\n"\
"}\n"\
"\n"\
"void ETC_KMeansTHModeA1(int *transparency, float3 *trans_pixel, int *indexes0, int *indexes1, int *set_count)\n"\
"{\n"\
"    int *index[2] = {indexes0, indexes1};\n"\
"    float3 means[2];\n"\
"    int swap_indexes[2][2][16];\n"\
"    int point_count[2][2];\n"\
"    int ri[2];\n"\
"    int i;\n"\
"    int iteration;\n"\
"    int source;\n"\
"    int target;\n"\
"    int set;\n"\
"\n"\
"    for (i = 0; i < 16; i++)\n"\
"        if (!transparency[i])\n"\
"        {\n"\
"            ri[0] = i;\n"\
"            break;\n"\
"        }\n"\
"\n"\
"    ri[1] = i;\n"\
"\n"\
"    for (i = ri[0] + 1; i < 16; i++)\n"\
"        if (!transparency[i] && !(MEMBER(trans_pixel[ri[0]], X) == MEMBER(trans_pixel[i], X) && MEMBER(trans_pixel[ri[0]], Y) == MEMBER(trans_pixel[i], Y) && MEMBER(trans_pixel[ri[0]], Z) == MEMBER(trans_pixel[i], Z)))\n"\
"        {\n"\
"            ri[1] = i;\n"\
"            break;\n"\
"        }\n"\
"\n"\
"    means[0] = trans_pixel[ri[0]];\n"\
"    means[1] = trans_pixel[ri[1]];\n"\
"\n"\
"    for (iteration = 0, i = 0; iteration < 16; iteration++)\n"\
"    {\n"\
"        if (!transparency[iteration])\n"\
"        {\n"\
"            swap_indexes[0][0][i] = iteration;\n"\
"            i++;\n"\
"        }\n"\
"    }\n"\
"\n"\
"    point_count[0][0] = i;\n"\
"    point_count[0][1] = 0;\n"\
"    point_count[1][0] = 0;\n"\
"    point_count[1][1] = 0;\n"\
"\n"\
"    source = 0;\n"\
"    target = 1;\n"\
"\n"\
"    for (iteration = 0; iteration < MAX_KMEANS_ITERATIONS; iteration++)\n"\
"    {\n"\
"        float3 temp_means[2];\n"\
"\n"\
"        temp_means[0] = VFLOAT3(0.0f, 0.0f, 0.0f);\n"\
"        temp_means[1] = VFLOAT3(0.0f, 0.0f, 0.0f);\n"\
"\n"\
"        for (set = 0; set < 2; set++)\n"\
"        {\n"\
"            for (i = 0; i < point_count[source][set]; i++)\n"\
"            {\n"\
"                float3 diff[2];\n"\
"                float lensq[2];\n"\
"\n"\
"                diff[0] = means[0] - trans_pixel[swap_indexes[source][set][i]];\n"\
"                diff[1] = means[1] - trans_pixel[swap_indexes[source][set][i]];\n"\
"\n"\
"                lensq[0] = dot(diff[0], diff[0]);\n"\
"                lensq[1] = dot(diff[1], diff[1]);\n"\
"\n"\
"                if (lensq[0] < lensq[1])\n"\
"                {\n"\
"                    swap_indexes[target][0][point_count[target][0]] = swap_indexes[source][set][i];\n"\
"                    temp_means[0] = temp_means[0] + trans_pixel[swap_indexes[source][set][i]];\n"\
"                    point_count[target][0]++;\n"\
"                }\n"\
"                else\n"\
"                {\n"\
"                    swap_indexes[target][1][point_count[target][1]] = swap_indexes[source][set][i];\n"\
"                    temp_means[1] = temp_means[1] + trans_pixel[swap_indexes[source][set][i]];\n"\
"                    point_count[target][1]++;\n"\
"                }\n"\
"            }\n"\
"        }\n"\
"\n"\
"        if (point_count[target][0])\n"\
"            temp_means[0] = temp_means[0] / (float)point_count[target][0];\n"\
"        if (point_count[target][1])\n"\
"            temp_means[1] = temp_means[1] / (float)point_count[target][1];\n"\
"\n"\
"        if ((point_count[target][0] == point_count[source][0]) && (point_count[target][1] == point_count[source][1]))\n"\
"        {\n"\
"            if (!MemCmp(swap_indexes[target][0], swap_indexes[source][0], sizeof(int) * point_count[target][0]) &&\n"\
"                !MemCmp(swap_indexes[target][1], swap_indexes[source][1], sizeof(int) * point_count[target][1]))\n"\
"            {\n"\
"                if (!Vec3f32Cmp(temp_means[0], means[0]) && !Vec3f32Cmp(temp_means[1], means[1]))\n"\
"                {\n"\
"                    source = (source + 1) % 2;\n"\
"                    target = (target + 1) % 2;\n"\
"                    break;\n"\
"                }\n"\
"            }\n"\
"        }\n"\
"\n"\
"        means[0] = temp_means[0];\n"\
"        means[1] = temp_means[1];\n"\
"\n"\
"        source = (source + 1) % 2;\n"\
"        target = (target + 1) % 2;\n"\
"\n"\
"        point_count[target][0] = 0;\n"\
"        point_count[target][1] = 0;\n"\
"    }\n"\
"    for (i = 0; i < point_count[source][0]; i++)\n"\
"        indexes0[i] = swap_indexes[source][0][i];\n"\
"    for (i = 0; i < point_count[source][1]; i++)\n"\
"        indexes1[i] = swap_indexes[source][1][i];\n"\
"\n"\
"    set_count[0] = point_count[source][0];\n"\
"    set_count[1] = point_count[source][1];\n"\
"}\n"\
"\n"\
"void ETC_GetOptimalIndexesA1(int *transparency, int is_ypbpr, float3 *trans_pixel, uchar3 rgb, __constant const int *partition_indexes, int *best_table, int *indexes)\n"\
"{\n"\
"    int i, table, j;\n"\
"    float best_table_dist = MAX_INIT_ERROR;\n"\
"    float3 rgb32f = VFLOAT3(MEMBER(rgb, X), MEMBER(rgb, Y), MEMBER(rgb, Z));\n"\
"\n"\
"    *best_table = 0;\n"\
"\n"\
"    for (table = 0; table < 8; table++)\n"\
"    {\n"\
"        float current_table_dist = 0.0f;\n"\
"        for (i = 0; i < 8; i++)\n"\
"        {\n"\
"            float best_dist = MAX_INIT_ERROR;\n"\
"\n"\
"            if (transparency[partition_indexes[i]])\n"\
"                continue;\n"\
"\n"\
"            for (j = 0; j < 4; j++)\n"\
"            {\n"\
"                float3 temp_pixel;\n"\
"                float3 delta;\n"\
"\n"\
"                if (j == 0)     // RGBA = 0\n"\
"                    temp_pixel = rgb32f;\n"\
"                else if (j == 2)\n"\
"                    continue;\n"\
"                else\n"\
"                    temp_pixel = clamp(rgb32f + VFLOAT3(g_table[table][j], g_table[table][j], g_table[table][j]), 0.0f, 255.0f);\n"\
"\n"\
"                if (is_ypbpr)\n"\
"                    delta = ETC_ConvertToYPBPRf3(temp_pixel) - trans_pixel[partition_indexes[i]];\n"\
"                else\n"\
"                    delta = temp_pixel - trans_pixel[partition_indexes[i]];\n"\
"\n"\
"                float lensq = dot(delta, delta);\n"\
"\n"\
"                if (lensq < best_dist)\n"\
"                    best_dist = lensq;\n"\
"            }\n"\
"            current_table_dist += best_dist;\n"\
"        }\n"\
"        if (current_table_dist < best_table_dist)\n"\
"        {\n"\
"            *best_table = table;\n"\
"            best_table_dist = current_table_dist;\n"\
"        }\n"\
"    }\n"\
"\n"\
"    for (i = 0; i < 8; i++)\n"\
"    {\n"\
"        float best_dist = MAX_INIT_ERROR;\n"\
"\n"\
"        if (transparency[partition_indexes[i]])\n"\
"        {\n"\
"            indexes[partition_indexes[i]] = 2;\n"\
"            continue;\n"\
"        }\n"\
"\n"\
"        for (j = 0; j < 4; j++)\n"\
"        {\n"\
"            float3 temp_pixel;\n"\
"            float3 delta;\n"\
"\n"\
"            if (j == 0)     // RGBA = 0\n"\
"                temp_pixel = rgb32f;\n"\
"            else if (j == 2)\n"\
"                continue;\n"\
"            else\n"\
"                temp_pixel = clamp(rgb32f + VFLOAT3(g_table[*best_table][j], g_table[*best_table][j], g_table[*best_table][j]), 0.0f, 255.0f);\n"\
"\n"\
"            if (is_ypbpr)\n"\
"                delta = ETC_ConvertToYPBPRf3(temp_pixel) - trans_pixel[partition_indexes[i]];\n"\
"            else\n"\
"                delta = temp_pixel - trans_pixel[partition_indexes[i]];\n"\
"\n"\
"            float lensq = dot(delta, delta);\n"\
"\n"\
"            if (lensq < best_dist)\n"\
"            {\n"\
"                indexes[partition_indexes[i]] = j;\n"\
"                best_dist = lensq;\n"\
"            }\n"\
"        }\n"\
"    }\n"\
"}\n"\
"\n"\
"float ETC_GetOptimalTIndexesA1(int *transparency, int is_ypbpr, float3 *trans_pixel, uchar3 rgb_single, uchar3 rgb_triple, int *indexes, int *best_mode)\n"\
"{\n"\
"    int i, mode, j;\n"\
"    float dist = 0.0f;\n"\
"    float3 rgb32f_single;\n"\
"    float3 rgb32f_triple;\n"\
"    float best_mode_dist;\n"\
"    float3 points[4];\n"\
"\n"\
"    rgb32f_single = VFLOAT3(MEMBER(rgb_single, X), MEMBER(rgb_single, Y), MEMBER(rgb_single, Z));\n"\
"    rgb32f_triple = VFLOAT3(MEMBER(rgb_triple, X), MEMBER(rgb_triple, Y), MEMBER(rgb_triple, Z));\n"\
"    best_mode_dist = MAX_INIT_ERROR;\n"\
"    *best_mode = 0;\n"\
"\n"\
"    points[0] = rgb32f_single;\n"\
"\n"\
"    if (is_ypbpr)\n"\
"        points[0] = ETC_ConvertToYPBPRf3(points[0]);\n"\
"\n"\
"    for (mode = 0; mode < 8; mode++)\n"\
"    {\n"\
"        float current_mode_dist = 0.0f;\n"\
"\n"\
"        points[1] = clamp(rgb32f_triple + VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);\n"\
"        points[2] = rgb32f_triple;\n"\
"        points[3] = clamp(rgb32f_triple - VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);\n"\
"\n"\
"        if (is_ypbpr)\n"\
"        {\n"\
"            points[1] = ETC_ConvertToYPBPRf3(points[1]);\n"\
"            points[2] = ETC_ConvertToYPBPRf3(points[2]);\n"\
"            points[3] = ETC_ConvertToYPBPRf3(points[3]);\n"\
"        }\n"\
"\n"\
"        for (i = 0; i < 16; i++)\n"\
"        {\n"\
"            float best_dist = MAX_INIT_ERROR;\n"\
"\n"\
"            if (transparency[i])\n"\
"                continue;\n"\
"\n"\
"            for (j = 0; j < 4; j++)\n"\
"            {\n"\
"                float3 delta;\n"\
"                float lensq;\n"\
"                delta = points[j] - trans_pixel[i];\n"\
"                lensq = dot(delta, delta);\n"\
"                if (lensq < best_dist)\n"\
"                    best_dist = lensq;\n"\
"            }\n"\
"            current_mode_dist += best_dist;\n"\
"        }\n"\
"        if (current_mode_dist < best_mode_dist)\n"\
"        {\n"\
"            *best_mode = mode;\n"\
"            best_mode_dist = current_mode_dist;\n"\
"        }\n"\
"    }\n"\
"\n"\
"    points[1] = clamp(rgb32f_triple + VFLOAT3(g_etc2_tmode_distance[*best_mode], g_etc2_tmode_distance[*best_mode], g_etc2_tmode_distance[*best_mode]), 0.0f, 255.0f);\n"\
"    points[3] = clamp(rgb32f_triple - VFLOAT3(g_etc2_tmode_distance[*best_mode], g_etc2_tmode_distance[*best_mode], g_etc2_tmode_distance[*best_mode]), 0.0f, 255.0f);\n"\
"\n"\
"    if (is_ypbpr)\n"\
"    {\n"\
"        points[1] = ETC_ConvertToYPBPRf3(points[1]);\n"\
"        points[3] = ETC_ConvertToYPBPRf3(points[3]);\n"\
"    }\n"\
"\n"\
"    dist = 0.0f;\n"\
"\n"\
"    for (i = 0; i < 16; i++)\n"\
"    {\n"\
"        float best_dist = MAX_INIT_ERROR;\n"\
"\n"\
"        if (transparency[i])\n"\
"        {\n"\
"            indexes[i] = 2;\n"\
"            continue;\n"\
"        }\n"\
"\n"\
"        for (j = 0; j < 4; j++)\n"\
"        {\n"\
"            float3 delta;\n"\
"            float lensq;\n"\
"\n"\
"            if (j == 2)\n"\
"                continue;\n"\
"\n"\
"            delta = points[j] - trans_pixel[i];\n"\
"            lensq = dot(delta, delta);\n"\
"            if (lensq < best_dist)\n"\
"            {\n"\
"                indexes[i] = j;\n"\
"                best_dist = lensq;\n"\
"            }\n"\
"        }\n"\
"        dist += best_dist;\n"\
"    }\n"\
"    return dist;\n"\
"}\n"\
"float ETC_GetOptimalHIndexesA1(int *transparency, int is_ypbpr, float3 *trans_pixel, uchar3 rgb_h0, uchar3 rgb_h1, int *indexes, int mode)\n"\
"{\n"\
"    int i, j;\n"\
"    float dist = 0.0f;\n"\
"    float3 rgb32f_h0;\n"\
"    float3 rgb32f_h1;\n"\
"    float3 points[4];\n"\
"\n"\
"    rgb32f_h0 = VFLOAT3(MEMBER(rgb_h0, X), MEMBER(rgb_h0, Y), MEMBER(rgb_h0, Z));\n"\
"    rgb32f_h1 = VFLOAT3(MEMBER(rgb_h1, X), MEMBER(rgb_h1, Y), MEMBER(rgb_h1, Z));\n"\
"\n"\
"    points[0] = clamp(rgb32f_h0 + VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);\n"\
"    points[1] = clamp(rgb32f_h0 - VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);\n"\
"    points[3] = clamp(rgb32f_h1 - VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);\n"\
"\n"\
"    if (is_ypbpr)\n"\
"    {\n"\
"        points[0] = ETC_ConvertToYPBPRf3(points[0]);\n"\
"        points[1] = ETC_ConvertToYPBPRf3(points[1]);\n"\
"        points[3] = ETC_ConvertToYPBPRf3(points[3]);\n"\
"    }\n"\
"\n"\
"    dist = 0.0f;\n"\
"\n"\
"    for (i = 0; i < 16; i++)\n"\
"    {\n"\
"        float best_dist = MAX_INIT_ERROR;\n"\
"\n"\
"        if (transparency[i])\n"\
"        {\n"\
"            indexes[i] = 2;\n"\
"            continue;\n"\
"        }\n"\
"\n"\
"        for (j = 0; j < 4; j++)\n"\
"        {\n"\
"            float3 delta;\n"\
"            float lensq;\n"\
"\n"\
"            if (j == 2)\n"\
"                continue;\n"\
"\n"\
"            delta = points[j] - trans_pixel[i];\n"\
"            lensq = dot(delta, delta);\n"\
"            if (lensq < best_dist)\n"\
"            {\n"\
"                indexes[i] = j;\n"\
"                best_dist = lensq;\n"\
"            }\n"\
"        }\n"\
"        dist += best_dist;\n"\
"    }\n"\
"    return dist;\n"\
"}\n"\
"\n"\
"float ETC_EvaluateErrorWeighted(int is_ypbpr, float3 *trans_pixel, float *weight, uchar3 rgb, __constant const int *partition_indexes)\n"\
"{\n"\
"    int i, table, j;\n"\
"    float best_table_dist = MAX_INIT_ERROR;\n"\
"    float3 rgb32f = VFLOAT3(MEMBER(rgb, X), MEMBER(rgb, Y), MEMBER(rgb, Z));\n"\
"\n"\
"    for (table = 0; table < 8; table++)\n"\
"    {\n"\
"        float current_table_dist = 0.0f;\n"\
"        for (i = 0; i < 8; i++)\n"\
"        {\n"\
"            float best_dist = MAX_INIT_ERROR;\n"\
"            for (j = 0; j < 4; j++)\n"\
"            {\n"\
"                float3 temp_pixel = clamp(rgb32f + VFLOAT3(g_table[table][j], g_table[table][j], g_table[table][j]), 0.0f, 255.0f);\n"\
"                float3 delta;\n"\
"\n"\
"                if (is_ypbpr)\n"\
"                    delta = ETC_ConvertToYPBPRf3(temp_pixel) - trans_pixel[partition_indexes[i]];\n"\
"                else\n"\
"                    delta = temp_pixel - trans_pixel[partition_indexes[i]];\n"\
"\n"\
"                float lensq = dot(delta, delta) * weight[partition_indexes[i]];\n"\
"\n"\
"                if (lensq < best_dist)\n"\
"                    best_dist = lensq;\n"\
"            }\n"\
"            current_table_dist += best_dist;\n"\
"        }\n"\
"        if (current_table_dist < best_table_dist)\n"\
"        {\n"\
"            best_table_dist = current_table_dist;\n"\
"        }\n"\
"    }\n"\
"    return best_table_dist;\n"\
"}\n"\
"\n"\
"float ETC_EvaluateErrorTSingleWeighted(int is_ypbpr, float3 *trans_pixel, float *weight, uchar3 rgb, int *indexes, int num_indexes)\n"\
"{\n"\
"    int i;\n"\
"    float dist = 0.0f;\n"\
"    float3 rgb32f;\n"\
"\n"\
"    if (!num_indexes)\n"\
"        return 0.0f;\n"\
"\n"\
"    rgb32f = VFLOAT3(MEMBER(rgb, X), MEMBER(rgb, Y), MEMBER(rgb, Z));\n"\
"\n"\
"    if (is_ypbpr)\n"\
"        rgb32f = ETC_ConvertToYPBPRf3(rgb32f);\n"\
"\n"\
"    for (i = 0; i < num_indexes; i++)\n"\
"    {\n"\
"        float3 delta;\n"\
"        delta = rgb32f - trans_pixel[indexes[i]];\n"\
"        dist += dot(delta, delta) * weight[indexes[i]];\n"\
"    }\n"\
"\n"\
"    return dist;\n"\
"}\n"\
"float ETC_EvaluateErrorTTripleWeighted(int is_ypbpr, float3 *trans_pixel, float *weight, uchar3 rgb, int *indexes, int num_indexes)\n"\
"{\n"\
"    int i, mode, j;\n"\
"    float dist = 0.0f;\n"\
"    float3 rgb32f;\n"\
"    float best_mode_dist;\n"\
"\n"\
"    if (!num_indexes)\n"\
"        return 0.0f;\n"\
"\n"\
"    rgb32f = VFLOAT3(MEMBER(rgb, X), MEMBER(rgb, Y), MEMBER(rgb, Z));\n"\
"    best_mode_dist = MAX_INIT_ERROR;\n"\
"\n"\
"    for (mode = 0; mode < 8; mode++)\n"\
"    {\n"\
"        float current_mode_dist = 0.0f;\n"\
"        float3 points[3];\n"\
"        points[0] = clamp(rgb32f + VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);\n"\
"        points[1] = rgb32f;\n"\
"        points[2] = clamp(rgb32f - VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);\n"\
"\n"\
"        if (is_ypbpr)\n"\
"        {\n"\
"            points[0] = ETC_ConvertToYPBPRf3(points[0]);\n"\
"            points[1] = ETC_ConvertToYPBPRf3(points[1]);\n"\
"            points[2] = ETC_ConvertToYPBPRf3(points[2]);\n"\
"        }\n"\
"\n"\
"        for (i = 0; i < num_indexes; i++)\n"\
"        {\n"\
"            float best_dist = MAX_INIT_ERROR;\n"\
"            for (j = 0; j < 3; j++)\n"\
"            {\n"\
"                float3 delta;\n"\
"                float lensq;\n"\
"                delta = points[j] - trans_pixel[indexes[i]];\n"\
"                lensq = dot(delta, delta) * weight[indexes[i]];\n"\
"                if (lensq < best_dist)\n"\
"                    best_dist = lensq;\n"\
"            }\n"\
"            current_mode_dist += best_dist;\n"\
"        }\n"\
"        if (current_mode_dist < best_mode_dist)\n"\
"        {\n"\
"            best_mode_dist = current_mode_dist;\n"\
"        }\n"\
"    }\n"\
"\n"\
"    return best_mode_dist;\n"\
"}\n"\
"\n"\
"float ETC_EvaluateErrorHWeighted(int is_ypbpr, float3 *trans_pixel, float *weight, uchar3 rgb, int *indexes, int num_indexes, int mode)\n"\
"{\n"\
"    int i, j;\n"\
"    float dist = 0.0f;\n"\
"    float3 rgb32f;\n"\
"    float current_mode_dist = 0.0f;\n"\
"    float3 points[2];\n"\
"\n"\
"    if (!num_indexes)\n"\
"        return 0.0f;\n"\
"\n"\
"    rgb32f = VFLOAT3(MEMBER(rgb, X), MEMBER(rgb, Y), MEMBER(rgb, Z));\n"\
"\n"\
"    points[0] = clamp(rgb32f + VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);\n"\
"    points[1] = clamp(rgb32f - VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);\n"\
"\n"\
"    if (is_ypbpr)\n"\
"    {\n"\
"        points[0] = ETC_ConvertToYPBPRf3(points[0]);\n"\
"        points[1] = ETC_ConvertToYPBPRf3(points[1]);\n"\
"    }\n"\
"\n"\
"    for (i = 0; i < num_indexes; i++)\n"\
"    {\n"\
"        float best_dist = MAX_INIT_ERROR;\n"\
"        for (j = 0; j < 2; j++)\n"\
"        {\n"\
"            float3 delta;\n"\
"            float lensq;\n"\
"\n"\
"            delta = points[j] - trans_pixel[indexes[i]];\n"\
"            lensq = dot(delta, delta) * weight[indexes[i]];\n"\
"\n"\
"            if (lensq < best_dist)\n"\
"                best_dist = lensq;\n"\
"        }\n"\
"        current_mode_dist += best_dist;\n"\
"    }\n"\
"\n"\
"    return current_mode_dist;\n"\
"}\n"\
"\n"\
"float EvaluateErrorGenericWeighted(int mode, int is_ypbpr, float3 *trans_pixel, float *weight, uchar3 rgb, etc_pathing_params_t *pathing_params)\n"\
"{\n"\
"    switch (mode)\n"\
"    {\n"\
"    case ETC_EVALUATEDELTAERRORGENERICA1:\n"\
"        return ETC_EvaluateErrorWeighted(is_ypbpr, trans_pixel, weight, rgb, pathing_params->partition_indexes);\n"\
"    case ETC_EVALUATETSINGLEERRORGENERICA1:\n"\
"        return ETC_EvaluateErrorTSingleWeighted(is_ypbpr, trans_pixel, weight, rgb, pathing_params->indexes, pathing_params->num_indexes);\n"\
"    case ETC_EVALUATETTRIPLEERRORGENERICA1:\n"\
"        return ETC_EvaluateErrorTTripleWeighted(is_ypbpr, trans_pixel, weight, rgb, pathing_params->indexes, pathing_params->num_indexes);\n"\
"    case ETC_EVALUATEHERRORGENERICA1:\n"\
"        return ETC_EvaluateErrorHWeighted(is_ypbpr, trans_pixel, weight, rgb, pathing_params->indexes, pathing_params->num_indexes, pathing_params->mode);\n"\
"    default:\n"\
"        return MAX_INIT_ERROR;\n"\
"    }\n"\
"}\n"\
"void ETC_GetOptimalIndexesWeighted(int is_ypbpr, float3 *trans_pixel, float *weight, uchar3 rgb, __constant const int *partition_indexes, int *best_table, int *indexes)\n"\
"{\n"\
"    int i, table, j;\n"\
"    float best_table_dist = MAX_INIT_ERROR;\n"\
"    float3 rgb32f = VFLOAT3(MEMBER(rgb, X), MEMBER(rgb, Y), MEMBER(rgb, Z));\n"\
"\n"\
"    *best_table = 0;\n"\
"\n"\
"    for (table = 0; table < 8; table++)\n"\
"    {\n"\
"        float current_table_dist = 0.0f;\n"\
"        for (i = 0; i < 8; i++)\n"\
"        {\n"\
"            float best_dist = MAX_INIT_ERROR;\n"\
"            for (j = 0; j < 4; j++)\n"\
"            {\n"\
"                float3 temp_pixel = clamp(rgb32f + VFLOAT3(g_table[table][j], g_table[table][j], g_table[table][j]), 0.0f, 255.0f);\n"\
"                float3 delta;\n"\
"\n"\
"                if (is_ypbpr)\n"\
"                    delta = ETC_ConvertToYPBPRf3(temp_pixel) - trans_pixel[partition_indexes[i]];\n"\
"                else\n"\
"                    delta = temp_pixel - trans_pixel[partition_indexes[i]];\n"\
"\n"\
"                float lensq = dot(delta, delta) * weight[partition_indexes[i]];\n"\
"\n"\
"                if (lensq < best_dist)\n"\
"                    best_dist = lensq;\n"\
"            }\n"\
"            current_table_dist += best_dist;\n"\
"        }\n"\
"        if (current_table_dist < best_table_dist)\n"\
"        {\n"\
"            *best_table = table;\n"\
"            best_table_dist = current_table_dist;\n"\
"        }\n"\
"    }\n"\
"\n"\
"    for (i = 0; i < 8; i++)\n"\
"    {\n"\
"        float best_dist = MAX_INIT_ERROR;\n"\
"        for (j = 0; j < 4; j++)\n"\
"        {\n"\
"            float3 temp_pixel = clamp(rgb32f + VFLOAT3(g_table[*best_table][j], g_table[*best_table][j], g_table[*best_table][j]), 0.0f, 255.0f);\n"\
"            float3 delta;\n"\
"\n"\
"            if (is_ypbpr)\n"\
"                delta = ETC_ConvertToYPBPRf3(temp_pixel) - trans_pixel[partition_indexes[i]];\n"\
"            else\n"\
"                delta = temp_pixel - trans_pixel[partition_indexes[i]];\n"\
"\n"\
"            float lensq = dot(delta, delta) * weight[partition_indexes[i]];\n"\
"\n"\
"            if (lensq < best_dist)\n"\
"            {\n"\
"                indexes[partition_indexes[i]] = j;\n"\
"                best_dist = lensq;\n"\
"            }\n"\
"        }\n"\
"    }\n"\
"}\n"\
"\n"\
"float ETC_GetOptimalTIndexesWeighted(int is_ypbpr, float3 *trans_pixel, float *weight, uchar3 rgb_single, uchar3 rgb_triple, int *indexes, int *best_mode)\n"\
"{\n"\
"    int i, mode, j;\n"\
"    float dist = 0.0f;\n"\
"    float3 rgb32f_single;\n"\
"    float3 rgb32f_triple;\n"\
"    float best_mode_dist;\n"\
"    float3 points[4];\n"\
"\n"\
"    rgb32f_single = VFLOAT3(MEMBER(rgb_single, X), MEMBER(rgb_single, Y), MEMBER(rgb_single, Z));\n"\
"    rgb32f_triple = VFLOAT3(MEMBER(rgb_triple, X), MEMBER(rgb_triple, Y), MEMBER(rgb_triple, Z));\n"\
"    best_mode_dist = MAX_INIT_ERROR;\n"\
"    *best_mode = 0;\n"\
"\n"\
"    points[0] = rgb32f_single;\n"\
"\n"\
"    if (is_ypbpr)\n"\
"        points[0] = ETC_ConvertToYPBPRf3(points[0]);\n"\
"\n"\
"    for (mode = 0; mode < 8; mode++)\n"\
"    {\n"\
"        float current_mode_dist = 0.0f;\n"\
"\n"\
"        points[1] = clamp(rgb32f_triple + VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);\n"\
"        points[2] = rgb32f_triple;\n"\
"        points[3] = clamp(rgb32f_triple - VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);\n"\
"\n"\
"        if (is_ypbpr)\n"\
"        {\n"\
"            points[1] = ETC_ConvertToYPBPRf3(points[1]);\n"\
"            points[2] = ETC_ConvertToYPBPRf3(points[2]);\n"\
"            points[3] = ETC_ConvertToYPBPRf3(points[3]);\n"\
"        }\n"\
"\n"\
"        for (i = 0; i < 16; i++)\n"\
"        {\n"\
"            float best_dist = MAX_INIT_ERROR;\n"\
"            for (j = 0; j < 4; j++)\n"\
"            {\n"\
"                float3 delta;\n"\
"                float lensq;\n"\
"                delta = points[j] - trans_pixel[i];\n"\
"                lensq = dot(delta, delta) * weight[i];\n"\
"                if (lensq < best_dist)\n"\
"                    best_dist = lensq;\n"\
"            }\n"\
"            current_mode_dist += best_dist;\n"\
"        }\n"\
"        if (current_mode_dist < best_mode_dist)\n"\
"        {\n"\
"            *best_mode = mode;\n"\
"            best_mode_dist = current_mode_dist;\n"\
"        }\n"\
"    }\n"\
"\n"\
"    points[1] = clamp(rgb32f_triple + VFLOAT3(g_etc2_tmode_distance[*best_mode], g_etc2_tmode_distance[*best_mode], g_etc2_tmode_distance[*best_mode]), 0.0f, 255.0f);\n"\
"    points[2] = rgb32f_triple;\n"\
"    points[3] = clamp(rgb32f_triple - VFLOAT3(g_etc2_tmode_distance[*best_mode], g_etc2_tmode_distance[*best_mode], g_etc2_tmode_distance[*best_mode]), 0.0f, 255.0f);\n"\
"\n"\
"    if (is_ypbpr)\n"\
"    {\n"\
"        points[1] = ETC_ConvertToYPBPRf3(points[1]);\n"\
"        points[2] = ETC_ConvertToYPBPRf3(points[2]);\n"\
"        points[3] = ETC_ConvertToYPBPRf3(points[3]);\n"\
"    }\n"\
"\n"\
"    dist = 0.0f;\n"\
"\n"\
"    for (i = 0; i < 16; i++)\n"\
"    {\n"\
"        float best_dist = MAX_INIT_ERROR;\n"\
"        if (weight[i] == 0.0f)\n"\
"        {\n"\
"            indexes[i] = 0;\n"\
"            continue;\n"\
"        }\n"\
"        for (j = 0; j < 4; j++)\n"\
"        {\n"\
"            float3 delta;\n"\
"            float lensq;\n"\
"            delta = points[j] - trans_pixel[i];\n"\
"            lensq = dot(delta, delta) * weight[i];\n"\
"            if (lensq < best_dist)\n"\
"            {\n"\
"                indexes[i] = j;\n"\
"                best_dist = lensq;\n"\
"            }\n"\
"        }\n"\
"        dist += best_dist;\n"\
"    }\n"\
"    return dist;\n"\
"}\n"\
"float ETC_GetOptimalHIndexesWeighted(int is_ypbpr, float3 *trans_pixel, float *weight, uchar3 rgb_h0, uchar3 rgb_h1, int *indexes, int mode)\n"\
"{\n"\
"    int i, j;\n"\
"    float dist = 0.0f;\n"\
"    float3 rgb32f_h0;\n"\
"    float3 rgb32f_h1;\n"\
"    float3 points[4];\n"\
"\n"\
"    rgb32f_h0 = VFLOAT3(MEMBER(rgb_h0, X), MEMBER(rgb_h0, Y), MEMBER(rgb_h0, Z));\n"\
"    rgb32f_h1 = VFLOAT3(MEMBER(rgb_h1, X), MEMBER(rgb_h1, Y), MEMBER(rgb_h1, Z));\n"\
"\n"\
"    points[0] = clamp(rgb32f_h0 + VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);\n"\
"    points[1] = clamp(rgb32f_h0 - VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);\n"\
"    points[2] = clamp(rgb32f_h1 + VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);\n"\
"    points[3] = clamp(rgb32f_h1 - VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);\n"\
"\n"\
"    if (is_ypbpr)\n"\
"    {\n"\
"        points[0] = ETC_ConvertToYPBPRf3(points[0]);\n"\
"        points[1] = ETC_ConvertToYPBPRf3(points[1]);\n"\
"        points[2] = ETC_ConvertToYPBPRf3(points[2]);\n"\
"        points[3] = ETC_ConvertToYPBPRf3(points[3]);\n"\
"    }\n"\
"\n"\
"    dist = 0.0f;\n"\
"\n"\
"    for (i = 0; i < 16; i++)\n"\
"    {\n"\
"        float best_dist = MAX_INIT_ERROR;\n"\
"        for (j = 0; j < 4; j++)\n"\
"        {\n"\
"            float3 delta;\n"\
"            float lensq;\n"\
"            delta = points[j] - trans_pixel[i];\n"\
"            lensq = dot(delta, delta) * weight[i];\n"\
"            if (lensq < best_dist)\n"\
"            {\n"\
"                indexes[i] = j;\n"\
"                best_dist = lensq;\n"\
"            }\n"\
"        }\n"\
"        dist += best_dist;\n"\
"    }\n"\
"    return dist;\n"\
"}\n"\
"\n"\
"void ETC_LeastCostDirectedPathWeighted(\n"\
"    int step,\n"\
"    int sample_list_entries,\n"\
"    float error_target,\n"\
"    int refine_search,\n"\
"    int is_ypbpr,\n"\
"    float3 *trans_pixel,\n"\
"    float *weight,\n"\
"    etc_sample_t sample,\n"\
"    etc_sample_t *sample_list,\n"\
"    int x_max,\n"\
"    int y_max,\n"\
"    int z_max,\n"\
"    etc_pathing_params_t *pathing_params,\n"\
"    int expand_cb_fp,\n"\
"    int evaluate_cb_fp)\n"\
"{\n"\
"    int         i;\n"\
"    int         j;\n"\
"    int         terminate;\n"\
"    float   dist[27];\n"\
"\n"\
"    for (i = 0, terminate = 0; terminate == 0; i++)\n"\
"    {\n"\
"        uchar3 test_pos[7];\n"\
"        float best_dist;\n"\
"        int best_index;\n"\
"        int terminate_count = 0;\n"\
"\n"\
"        ETC_AddSampleToList(sample_list_entries, &sample_list[0], sample);\n"\
"\n"\
"        if (sample.error <= error_target)\n"\
"            break;\n"\
"\n"\
"        test_pos[0] = sample.pos_quantised + UCHAR3(step, 0, 0);\n"\
"        test_pos[1] = sample.pos_quantised + UCHAR3(0, step, 0);\n"\
"        test_pos[2] = sample.pos_quantised + UCHAR3(step, step, 0);\n"\
"        test_pos[3] = sample.pos_quantised + UCHAR3(0, 0, step);\n"\
"        test_pos[4] = sample.pos_quantised + UCHAR3(step, 0, step);\n"\
"        test_pos[5] = sample.pos_quantised + UCHAR3(0, step, step);\n"\
"        test_pos[6] = sample.pos_quantised + UCHAR3(step, step, step);\n"\
"\n"\
"        for (j = 0; j < 7; j++)\n"\
"        {\n"\
"            if ((MEMBER(test_pos[j], X) > x_max) || (MEMBER(test_pos[j], Y) > y_max) || (MEMBER(test_pos[j], Z) > z_max))\n"\
"                dist[j] = MAX_INIT_ERROR;\n"\
"            else\n"\
"            {\n"\
"                uchar3 v;\n"\
"\n"\
"                switch (expand_cb_fp)\n"\
"                {\n"\
"                case ETC_RGBEXPANDVECTO4BIT:\n"\
"                    v = ETC_RGBExpandVecTo4Bit(test_pos[j]);\n"\
"                    break;\n"\
"                case ETC_RGBEXPANDVECTO5BIT:\n"\
"                    v = ETC_RGBExpandVecTo5Bit(test_pos[j]);\n"\
"                    break;\n"\
"                }\n"\
"\n"\
"                dist[j] = EvaluateErrorGenericWeighted(evaluate_cb_fp, is_ypbpr, trans_pixel, weight, v, pathing_params);\n"\
"            }\n"\
"        }\n"\
"\n"\
"        best_dist = dist[0];\n"\
"        best_index = 0;\n"\
"        for (j = 1; j < 7; j++)\n"\
"        {\n"\
"            if (dist[j] < best_dist)\n"\
"            {\n"\
"                best_dist = dist[j];\n"\
"                best_index = j;\n"\
"            }\n"\
"        }\n"\
"\n"\
"        for (j = 0; j < 7; j++)\n"\
"            if (dist[j] == MAX_INIT_ERROR)\n"\
"                terminate_count++;\n"\
"\n"\
"        if (terminate_count == 7)\n"\
"            break;\n"\
"\n"\
"        if (dist[best_index] > MAX_ERROR_DIFF_MUL * sample_list[0].error)\n"\
"            break;\n"\
"\n"\
"        sample.pos_quantised = test_pos[best_index];\n"\
"        sample.error = dist[best_index];\n"\
"    }\n"\
"\n"\
"    if (refine_search)\n"\
"    {\n"\
"        sample.pos_quantised = sample_list[0].pos_quantised;\n"\
"        sample.error = sample_list[0].error;\n"\
"\n"\
"        for (i = 0, terminate = 0; terminate == 0; i++)\n"\
"        {\n"\
"            short3 test_pos[27];\n"\
"            float best_dist;\n"\
"            int best_index;\n"\
"            int terminate_count = 0;\n"\
"\n"\
"            if (i != 1)\n"\
"                ETC_AddSampleToList(sample_list_entries, &sample_list[0], sample);\n"\
"\n"\
"            if (sample.error <= error_target)\n"\
"                break;\n"\
"\n"\
"            for (j = 0; j < 27; j++)\n"\
"                test_pos[j] = SHORT3(MEMBER(sample.pos_quantised, X), MEMBER(sample.pos_quantised, Y), MEMBER(sample.pos_quantised, Z)) + SHORT3((j % 3) - 1, ((j / 3) % 3) - 1, j/9 - 1);\n"\
"\n"\
"            for (j = 0; j < 27; j++)\n"\
"            {\n"\
"                if (j == 13)\n"\
"                    dist[j] = sample.error;\n"\
"                else if ((MEMBER(test_pos[j], X) > x_max) || (MEMBER(test_pos[j], Y) > y_max) || (MEMBER(test_pos[j], Z) > z_max) || (MEMBER(test_pos[j], X) < 0) || (MEMBER(test_pos[j], Y) < 0) || (MEMBER(test_pos[j], Z) < 0))\n"\
"                    dist[j] = MAX_INIT_ERROR;\n"\
"                else\n"\
"                {\n"\
"                    uchar3 v;\n"\
"\n"\
"                    switch (expand_cb_fp)\n"\
"                    {\n"\
"                    case ETC_RGBEXPANDVECTO4BIT:\n"\
"                        v = ETC_RGBExpandVecTo4Bit(UCHAR3(MEMBER(test_pos[j], X), MEMBER(test_pos[j], Y), MEMBER(test_pos[j], Z)));\n"\
"                        break;\n"\
"                    case ETC_RGBEXPANDVECTO5BIT:\n"\
"                        v = ETC_RGBExpandVecTo5Bit(UCHAR3(MEMBER(test_pos[j], X), MEMBER(test_pos[j], Y), MEMBER(test_pos[j], Z)));\n"\
"                        break;\n"\
"                    }\n"\
"\n"\
"                    dist[j] = EvaluateErrorGenericWeighted(evaluate_cb_fp, is_ypbpr, trans_pixel, weight, v, pathing_params);\n"\
"                }\n"\
"            }\n"\
"\n"\
"            best_dist = dist[0];\n"\
"            best_index = 0;\n"\
"            for (j = 1; j < 27; j++)\n"\
"            {\n"\
"                if (dist[j] < best_dist)\n"\
"                {\n"\
"                    best_dist = dist[j];\n"\
"                    best_index = j;\n"\
"                }\n"\
"            }\n"\
"            if (dist[13] == best_dist)\n"\
"                break;\n"\
"\n"\
"            for (j = 0; j < 27; j++)\n"\
"                if (dist[j] == MAX_INIT_ERROR)\n"\
"                    terminate_count++;\n"\
"\n"\
"            if (terminate_count >= 26)\n"\
"                break;\n"\
"\n"\
"            if (dist[best_index] > MAX_ERROR_DIFF_MUL * sample_list[0].error)\n"\
"                break;\n"\
"\n"\
"            sample.pos_quantised = UCHAR3(MEMBER(test_pos[best_index], X), MEMBER(test_pos[best_index], Y), MEMBER(test_pos[best_index], Z));\n"\
"            sample.error = dist[best_index];\n"\
"        }\n"\
"    }\n"\
"}\n"\
"\n"\
"void ETC_EncodeRGBWeighted(\n"\
"    int quality,\n"\
"    int allowed_modes,\n"\
"    float error_target,\n"\
"    int refine_search,\n"\
"    int is_etc2,\n"\
"    int is_ypbpr,\n"\
"    float4 *pixel,\n"\
"    float *weight,\n"\
"    __global uchar *block)\n"\
"{\n"\
"    int i, j, table, n;\n"\
"    float3 trans_pixel[16];\n"\
"    int is_delta;\n"\
"    int is_flipped;\n"\
"    float best_dist[2];\n"\
"    etc_sample_t sample_list[SAMPLE_LIST_SIZE0][SAMPLE_LIST_SIZE1][SAMPLE_LIST_SIZE2];\n"\
"    int flipped;\n"\
"    int partition;\n"\
"    int is_best_delta = 0;\n"\
"    float best_total_error = MAX_INIT_ERROR;\n"\
"    int enc_mode;\n"\
"    etc_partition_mode_params_t params_partition;\n"\
"    etc_th_mode_params_t params_th;\n"\
"    etc_planar_mode_params_t params_planar;\n"\
"    etc_pathing_params_t pathing_params;\n"\
"    uchar local_block[8];\n"\
"    int step = 1;\n"\
"    float3 projected_mins[2][2]; // delta/non-delta, flipped, partition\n"\
"    float3 projected_maxs[2][2];\n"\
"\n"\
"    for (i = 0; i < 16; i++)\n"\
"    {\n"\
"        MEMBER(trans_pixel[i], X) = MEMBER(pixel[i], X);\n"\
"        MEMBER(trans_pixel[i], Y) = MEMBER(pixel[i], Y);\n"\
"        MEMBER(trans_pixel[i], Z) = MEMBER(pixel[i], Z);\n"\
"    }\n"\
"\n"\
"    for (flipped = 0; flipped < 2; flipped++)\n"\
"    {\n"\
"        for (partition = 0; partition < 2; partition++)\n"\
"        {\n"\
"            float3 mean = VFLOAT3(0.0f, 0.0f, 0.0f);\n"\
"            float mins_maxs_dist[2];\n"\
"            float3 temp;\n"\
"            int pixel_count = 0;\n"\
"\n"\
"            mins_maxs_dist[0] = MAX_INIT_ERROR;\n"\
"            mins_maxs_dist[1] = -MAX_INIT_ERROR;\n"\
"\n"\
"            for (i = 0; i < 8; i++)\n"\
"            {\n"\
"                if (weight[g_partition_indexes[flipped][partition][i]] == 0.0f)\n"\
"                    continue;\n"\
"                mean = mean + trans_pixel[g_partition_indexes[flipped][partition][i]];\n"\
"                pixel_count++;\n"\
"            }\n"\
"\n"\
"            pixel_count = pixel_count ? pixel_count : 1;\n"\
"\n"\
"            mean = mean / (float)(pixel_count);\n"\
"\n"\
"            for (i = 0; i < 8; i++)\n"\
"            {\n"\
"                float dist;\n"\
"\n"\
"                if (weight[g_partition_indexes[flipped][partition][i]] == 0.0f)\n"\
"                    continue;\n"\
"\n"\
"                dist = dot(trans_pixel[g_partition_indexes[flipped][partition][i]] - mean, VFLOAT3(0.57735f, 0.57735f, 0.57735f));\n"\
"\n"\
"                if (dist < mins_maxs_dist[0])\n"\
"                    mins_maxs_dist[0] = dist;\n"\
"                if (dist > mins_maxs_dist[1])\n"\
"                    mins_maxs_dist[1] = dist;\n"\
"            }\n"\
"            projected_mins[flipped][partition] = mean + VFLOAT3(0.57735f, 0.57735f, 0.57735f) * mins_maxs_dist[0];\n"\
"            projected_maxs[flipped][partition] = mean + VFLOAT3(0.57735f, 0.57735f, 0.57735f) * mins_maxs_dist[1];\n"\
"        }\n"\
"    }\n"\
"\n"\
"    if (is_ypbpr)\n"\
"        for (i = 0; i < 16; i++)\n"\
"        {\n"\
"            trans_pixel[i] = ETC_ConvertToYPBPRf3(trans_pixel[i]);\n"\
"        }\n"\
"\n"\
"    if (allowed_modes & ETC_MODE_DELTA)\n"\
"    {\n"\
"        float3 mean[2][2];\n"\
"        uchar3 mean_quant[2][2];\n"\
"        int min_index[2][2];\n"\
"        int max_index[2][2];\n"\
"        float fixed_err = MAX_INIT_ERROR;\n"\
"        uchar3 best_positions[2];\n"\
"        int best_flipped = 0;\n"\
"        int found_fixed = 0;\n"\
"        uchar3 proj_mins;\n"\
"        uchar3 proj_maxs;\n"\
"        int fixed_flip = 0;\n"\
"#if 1\n"\
"        if (quality >= CODEC_QUALITY_NORMAL) // redundant, quality is always normal or better in this function\n"\
"        {\n"\
"            int max_distance;\n"\
"\n"\
"            if (quality == CODEC_QUALITY_BEST)\n"\
"                max_distance = 255;\n"\
"            else if (quality == CODEC_QUALITY_HIGH)\n"\
"                max_distance = 8;\n"\
"            else \n"\
"                max_distance = 1;\n"\
"\n"\
"            for (flipped = 0; flipped < 2; flipped++)\n"\
"            {\n"\
"                for (partition = 0; partition < 2; partition++)\n"\
"                {\n"\
"                    int distance = 0;\n"\
"                    int num_pixels = 0;\n"\
"                    mean[flipped][partition] = VFLOAT3(0.0f, 0.0f, 0.0f);\n"\
"                    for (i = 0; i < 8; i++)\n"\
"                    {\n"\
"                        if (g_partition_indexes[flipped][partition][i] == 0.0f)\n"\
"                            continue;\n"\
"                        num_pixels++;\n"\
"                        mean[flipped][partition] = mean[flipped][partition] + trans_pixel[g_partition_indexes[flipped][partition][i]];\n"\
"                    }\n"\
"                    num_pixels = num_pixels ? num_pixels : 1;\n"\
"                    mean[flipped][partition] = mean[flipped][partition] / (float)(num_pixels);\n"\
"\n"\
"                    MEMBER(mean_quant[flipped][partition], X) = UCHAR(MEMBER(mean[flipped][partition], X)) >> 3;\n"\
"                    MEMBER(mean_quant[flipped][partition], Y) = UCHAR(MEMBER(mean[flipped][partition], Y)) >> 3;\n"\
"                    MEMBER(mean_quant[flipped][partition], Z) = UCHAR(MEMBER(mean[flipped][partition], Z)) >> 3;\n"\
"\n"\
"                    min_index[flipped][partition] = 0;\n"\
"                    max_index[flipped][partition] = 0;\n"\
"\n"\
"                    while ( ((int)MEMBER(mean_quant[flipped][partition], X) + min_index[flipped][partition] > 0) &&\n"\
"                        ((int)MEMBER(mean_quant[flipped][partition], Y) + min_index[flipped][partition] > 0) &&\n"\
"                        ((int)MEMBER(mean_quant[flipped][partition], Z) + min_index[flipped][partition] > 0))\n"\
"                    {\n"\
"                        min_index[flipped][partition]--;\n"\
"                        distance++;\n"\
"                        if (distance > max_distance)\n"\
"                            break;\n"\
"                    }\n"\
"                    distance = 0;\n"\
"                    while ( ((int)MEMBER(mean_quant[flipped][partition], X) + max_index[flipped][partition] < 31) &&\n"\
"                        ((int)MEMBER(mean_quant[flipped][partition], Y) + max_index[flipped][partition] < 31) &&\n"\
"                        ((int)MEMBER(mean_quant[flipped][partition], Z) + max_index[flipped][partition] < 31))\n"\
"                    {\n"\
"                        max_index[flipped][partition]++;\n"\
"                        distance++;\n"\
"                        if (distance > max_distance)\n"\
"                            break;\n"\
"                    }\n"\
"                }\n"\
"            }\n"\
"            for (flipped = 0; flipped < 2; flipped++)\n"\
"            {\n"\
"                int ip0;\n"\
"                int ip1;\n"\
"                for (ip0 = min_index[flipped][0]; ip0 <= max_index[flipped][0]; ip0++)\n"\
"                {\n"\
"                    uchar3 l0_quant;\n"\
"\n"\
"                    MEMBER(l0_quant, X) = MEMBER(mean_quant[flipped][0], X) + ip0;\n"\
"                    MEMBER(l0_quant, Y) = MEMBER(mean_quant[flipped][0], Y) + ip0;\n"\
"                    MEMBER(l0_quant, Z) = MEMBER(mean_quant[flipped][0], Z) + ip0;\n"\
"\n"\
"                    for (ip1 = min_index[flipped][1]; ip1 <= max_index[flipped][1]; ip1++)\n"\
"                    {\n"\
"                        uchar3 l1_quant;\n"\
"                        int dist[3];\n"\
"                        float local_error;\n"\
"\n"\
"                        MEMBER(l1_quant, X) = MEMBER(mean_quant[flipped][1], X) + ip1;\n"\
"                        MEMBER(l1_quant, Y) = MEMBER(mean_quant[flipped][1], Y) + ip1;\n"\
"                        MEMBER(l1_quant, Z) = MEMBER(mean_quant[flipped][1], Z) + ip1;\n"\
"\n"\
"                        dist[0] = (int)MEMBER(l1_quant, X) - (int)MEMBER(l0_quant, X);\n"\
"                        dist[1] = (int)MEMBER(l1_quant, Y) - (int)MEMBER(l0_quant, Y);\n"\
"                        dist[2] = (int)MEMBER(l1_quant, Z) - (int)MEMBER(l0_quant, Z);\n"\
"\n"\
"                        if ((dist[0] < -4 || dist[0] > 3) || \n"\
"                            (dist[1] < -4 || dist[1] > 3) || \n"\
"                            (dist[2] < -4 || dist[2] > 3))\n"\
"                            continue;\n"\
"\n"\
"                        local_error = ETC_EvaluateErrorWeighted(is_ypbpr, trans_pixel, weight, ETC_RGBExpandVecTo5Bit(l0_quant), &g_partition_indexes[flipped][0][0]);\n"\
"                        local_error += ETC_EvaluateErrorWeighted(is_ypbpr, trans_pixel, weight, ETC_RGBExpandVecTo5Bit(l1_quant), &g_partition_indexes[flipped][1][0]);\n"\
"\n"\
"                        if (local_error < fixed_err)\n"\
"                        {\n"\
"                            fixed_err = local_error;\n"\
"                            best_positions[0] = l0_quant;\n"\
"                            best_positions[1] = l1_quant;\n"\
"                            best_flipped = flipped;\n"\
"                            found_fixed = 1;\n"\
"                        }\n"\
"                    }\n"\
"                }\n"\
"            }\n"\
"            if (found_fixed)\n"\
"            {\n"\
"                uchar3 best_pos[2];\n"\
"                float combined_err = 0.0f;\n"\
"\n"\
"                best_pos[0] = best_positions[0];\n"\
"                best_pos[1] = best_positions[1];\n"\
"\n"\
"                for (partition = 0; partition < 2; partition++)\n"\
"                {\n"\
"                    int neighbourhood_width = (quality == CODEC_QUALITY_BEST ? 3 : 1);\n"\
"                    float best_err = MAX_INIT_ERROR;\n"\
"                    int x;\n"\
"                    int y;\n"\
"                    int z;\n"\
"                    int min_x = MEMBER(best_positions[partition], X) > (neighbourhood_width - 1) ? MEMBER(best_positions[partition], X) - neighbourhood_width : 0;\n"\
"                    int min_y = MEMBER(best_positions[partition], Y) > (neighbourhood_width - 1) ? MEMBER(best_positions[partition], Y) - neighbourhood_width : 0;\n"\
"                    int min_z = MEMBER(best_positions[partition], Z) > (neighbourhood_width - 1) ? MEMBER(best_positions[partition], Z) - neighbourhood_width : 0;\n"\
"                    int max_x = MEMBER(best_positions[partition], X) < (31 - neighbourhood_width) ? MEMBER(best_positions[partition], X) + neighbourhood_width : 31;\n"\
"                    int max_y = MEMBER(best_positions[partition], Y) < (31 - neighbourhood_width) ? MEMBER(best_positions[partition], Y) + neighbourhood_width : 31;\n"\
"                    int max_z = MEMBER(best_positions[partition], Z) < (31 - neighbourhood_width) ? MEMBER(best_positions[partition], Z) + neighbourhood_width : 31;\n"\
"\n"\
"                    for (z = min_z; z <= max_z; z++)\n"\
"                        for (y = min_y; y <= max_y; y++)\n"\
"                            for (x = min_x; x <= max_x; x++)\n"\
"                            {\n"\
"                                uchar3 pos = UCHAR3(x, y, z);\n"\
"                                float err;\n"\
"                                int dist[3];\n"\
"\n"\
"                                dist[0] = (int)MEMBER(pos, X) - (int)MEMBER(best_pos[partition ? 0 : 1], X);\n"\
"                                dist[1] = (int)MEMBER(pos, Y) - (int)MEMBER(best_pos[partition ? 0 : 1], Y);\n"\
"                                dist[2] = (int)MEMBER(pos, Z) - (int)MEMBER(best_pos[partition ? 0 : 1], Z);\n"\
"\n"\
"                                if ((dist[0] < -4 || dist[0] > 3) || \n"\
"                                    (dist[1] < -4 || dist[1] > 3) || \n"\
"                                    (dist[2] < -4 || dist[2] > 3))\n"\
"                                    continue;\n"\
"\n"\
"                                pos = ETC_RGBExpandVecTo5Bit(pos);\n"\
"                                err = ETC_EvaluateErrorWeighted(is_ypbpr, trans_pixel, weight, pos, &g_partition_indexes[best_flipped][partition][0]);\n"\
"\n"\
"                                if (err < best_err)\n"\
"                                {\n"\
"                                    best_pos[partition] = UCHAR3(x, y, z);\n"\
"                                    best_err = err;\n"\
"                                }\n"\
"                            }\n"\
"                    combined_err += best_err;\n"\
"                }\n"\
"\n"\
"                if (combined_err < fixed_err)\n"\
"                {\n"\
"                    best_positions[0] = best_pos[0];\n"\
"                    best_positions[1] = best_pos[1];\n"\
"                    fixed_err = combined_err;\n"\
"                }\n"\
"            }\n"\
"        }\n"\
"#endif\n"\
"        // Delta mode\n"\
"        ETC_PrepareSampleList(SAMPLE_LIST_SIZE2, sample_list);\n"\
"\n"\
"        for (flipped = 0; flipped < 2; flipped++)\n"\
"        {\n"\
"            for (partition = 0; partition < 2; partition++)\n"\
"            {\n"\
"                etc_sample_t sample;\n"\
"\n"\
"                float offset = 0.0f;\n"\
"\n"\
"                if (quality == CODEC_QUALITY_NORMAL)\n"\
"                    offset = 0.0f;\n"\
"                else if (quality > CODEC_QUALITY_NORMAL) // searching entire space on BEST tends to give values that can't be represented by delta encodings\n"\
"                    offset = 24.0f;\n"\
"\n"\
"                MEMBER(proj_mins, X) = ((uint)clamp(MEMBER(projected_mins[flipped][partition], X) - offset, 0.0f, 255.0f)) >> 3;\n"\
"                MEMBER(proj_mins, Y) = ((uint)clamp(MEMBER(projected_mins[flipped][partition], Y) - offset, 0.0f, 255.0f)) >> 3;\n"\
"                MEMBER(proj_mins, Z) = ((uint)clamp(MEMBER(projected_mins[flipped][partition], Z) - offset, 0.0f, 255.0f)) >> 3;\n"\
"                MEMBER(proj_maxs, X) = ((uint)clamp(MEMBER(projected_maxs[flipped][partition], X) + offset + 3, 0.0f, 255.0f)) >> 3;\n"\
"                MEMBER(proj_maxs, Y) = ((uint)clamp(MEMBER(projected_maxs[flipped][partition], Y) + offset + 3, 0.0f, 255.0f)) >> 3;\n"\
"                MEMBER(proj_maxs, Z) = ((uint)clamp(MEMBER(projected_maxs[flipped][partition], Z) + offset + 3, 0.0f, 255.0f)) >> 3;\n"\
"\n"\
"                sample.pos_quantised = proj_mins;\n"\
"                pathing_params.partition_indexes = &g_partition_indexes[flipped][partition][0];\n"\
"                sample.error = ETC_EvaluateErrorWeighted(is_ypbpr, trans_pixel, weight, ETC_RGBExpandVecTo5Bit(sample.pos_quantised), &g_partition_indexes[flipped][partition][0]);\n"\
"                ETC_LeastCostDirectedPathWeighted(1, SAMPLE_LIST_SIZE2, error_target, refine_search, is_ypbpr, trans_pixel, weight, sample, &sample_list[flipped][partition][0], MEMBER(proj_maxs, X), MEMBER(proj_maxs, Y), MEMBER(proj_maxs, Z), &pathing_params, ETC_RGBEXPANDVECTO5BIT, ETC_EVALUATEDELTAERRORGENERICWEIGHTED);\n"\
"            }\n"\
"        }\n"\
"\n"\
"        for (i = 0; i < 2; i++)\n"\
"            best_dist[i] = sample_list[i][0][0].error + sample_list[i][1][0].error;\n"\
"\n"\
"        if (best_dist[1] < best_dist[0])\n"\
"            is_flipped = 1;\n"\
"        else\n"\
"            is_flipped = 0;\n"\
"\n"\
"        is_delta = 0;\n"\
"\n"\
"        int diff = (int)(MEMBER(sample_list[is_flipped][1][0].pos_quantised, X)) - (int)(MEMBER(sample_list[is_flipped][0][0].pos_quantised, X));\n"\
"        if (diff < 4 && diff >= -4)\n"\
"            is_delta++;\n"\
"        diff = (int)(MEMBER(sample_list[is_flipped][1][0].pos_quantised, Y)) - (int)(MEMBER(sample_list[is_flipped][0][0].pos_quantised, Y));\n"\
"        if (diff < 4 && diff >= -4)\n"\
"            is_delta++;\n"\
"        diff = (int)(MEMBER(sample_list[is_flipped][1][0].pos_quantised, Z)) - (int)(MEMBER(sample_list[is_flipped][0][0].pos_quantised, Z));\n"\
"        if (diff < 4 && diff >= -4)\n"\
"            is_delta++;\n"\
"\n"\
"        is_best_delta = is_delta == 3 ? 1 : 0;\n"\
"\n"\
"        best_total_error = min(best_dist[0], best_dist[1]);\n"\
"\n"\
"        enc_mode = ETC_ENC_MODE_DELTA;\n"\
"        params_partition.rgb[0] = ETC_RGBExpandVecTo5Bit(sample_list[is_flipped][0][0].pos_quantised);\n"\
"        params_partition.rgb[1] = ETC_RGBExpandVecTo5Bit(sample_list[is_flipped][1][0].pos_quantised);\n"\
"        params_partition.is_flipped = is_flipped;\n"\
"\n"\
"        if (!is_best_delta)\n"\
"        {\n"\
"            int delta[2][SAMPLE_LIST_SIZE2][SAMPLE_LIST_SIZE2]; // TODO: can get rid of this if just do it inside the loop\n"\
"            float err[2][SAMPLE_LIST_SIZE2][SAMPLE_LIST_SIZE2]; // TODO: can get rid of this if just do it inside the loop\n"\
"            int best_delta[2] = {0, 0};\n"\
"            float best_delta_err = MAX_INIT_ERROR;\n"\
"            int delta_found = 0;\n"\
"            int best_flipped = 0;\n"\
"\n"\
"            for (n = 0; n < 2; n++)\n"\
"                for (i = 0; i < SAMPLE_LIST_SIZE2; i++)\n"\
"                {\n"\
"                    for (j = 0; j < SAMPLE_LIST_SIZE2; j++)\n"\
"                    {\n"\
"                        is_delta = 0;\n"\
"                        int diff = (int)(MEMBER(sample_list[n][1][j].pos_quantised, X)) - (int)(MEMBER(sample_list[n][0][i].pos_quantised, X));\n"\
"                        if (diff < 4 && diff >= -4)\n"\
"                            is_delta++;\n"\
"                        diff = (int)(MEMBER(sample_list[n][1][j].pos_quantised, Y)) - (int)(MEMBER(sample_list[n][0][i].pos_quantised, Y));\n"\
"                        if (diff < 4 && diff >= -4)\n"\
"                            is_delta++;\n"\
"                        diff = (int)(MEMBER(sample_list[n][1][j].pos_quantised, Z)) - (int)(MEMBER(sample_list[n][0][i].pos_quantised, Z));\n"\
"                        if (diff < 4 && diff >= -4)\n"\
"                            is_delta++;\n"\
"\n"\
"                        delta[n][i][j] = is_delta == 3 ? 1 : 0;\n"\
"                        err[n][i][j] = sample_list[n][1][j].error + sample_list[n][0][i].error;\n"\
"                    }\n"\
"                }\n"\
"            for (n = 0; n < 2; n++)\n"\
"                for (i = 0; i < SAMPLE_LIST_SIZE2; i++)\n"\
"                    for (j = 0; j < SAMPLE_LIST_SIZE2; j++)\n"\
"                        if (delta[n][i][j])\n"\
"                            if (err[n][i][j] < best_delta_err)\n"\
"                            {\n"\
"                                best_delta_err = err[n][i][j];\n"\
"                                best_delta[0] = i;\n"\
"                                best_delta[1] = j;\n"\
"                                delta_found = 1;\n"\
"                                best_flipped = n;\n"\
"                            }\n"\
"\n"\
"            best_total_error = best_delta_err;\n"\
"\n"\
"            if (delta_found)\n"\
"            {\n"\
"                params_partition.rgb[0] = ETC_RGBExpandVecTo5Bit(sample_list[best_flipped][0][best_delta[0]].pos_quantised);\n"\
"                params_partition.rgb[1] = ETC_RGBExpandVecTo5Bit(sample_list[best_flipped][1][best_delta[1]].pos_quantised);\n"\
"                params_partition.is_flipped = best_flipped;\n"\
"            }\n"\
"        }\n"\
"\n"\
"        if (found_fixed && fixed_err < best_total_error)\n"\
"        {\n"\
"            enc_mode = ETC_ENC_MODE_DELTA;\n"\
"            best_total_error = fixed_err;\n"\
"            params_partition.rgb[0] = ETC_RGBExpandVecTo5Bit(best_positions[0]);\n"\
"            params_partition.rgb[1] = ETC_RGBExpandVecTo5Bit(best_positions[1]);\n"\
"            params_partition.is_flipped = best_flipped;\n"\
"        }\n"\
"\n"\
"        ETC_GetOptimalIndexesWeighted(is_ypbpr, trans_pixel, weight, params_partition.rgb[0], &g_partition_indexes[params_partition.is_flipped][0][0], &params_partition.table[0], params_partition.indexes);\n"\
"        ETC_GetOptimalIndexesWeighted(is_ypbpr, trans_pixel, weight, params_partition.rgb[1], &g_partition_indexes[params_partition.is_flipped][1][0], &params_partition.table[1], params_partition.indexes);\n"\
"    }\n"\
"\n"\
"    if ((!is_best_delta) && (allowed_modes & ETC_MODE_NODELTA))\n"\
"    {\n"\
"        int is_non_delta_flipped;\n"\
"        float3 mean[2][2];\n"\
"        uchar3 mean_quant[2][2];\n"\
"        int min_index[2][2];\n"\
"        int max_index[2][2];\n"\
"        float fixed_err = MAX_INIT_ERROR;\n"\
"        uchar3 best_positions[2];\n"\
"        int best_flipped = 0;\n"\
"        int found_fixed = 0;\n"\
"        uchar3 proj_mins;\n"\
"        uchar3 proj_maxs;\n"\
"\n"\
"        if (quality >= CODEC_QUALITY_NORMAL) // redundant\n"\
"        {\n"\
"            float fixed_err_group[2][2];\n"\
"            uchar3 fixed_positions_group[2][2];\n"\
"            int max_distance;\n"\
"\n"\
"            if (quality == CODEC_QUALITY_BEST)\n"\
"                max_distance = 255;\n"\
"            else if (quality == CODEC_QUALITY_HIGH)\n"\
"                max_distance = 4;\n"\
"            else \n"\
"                max_distance = 1;\n"\
"\n"\
"            for (i = 0; i < 2; i++)\n"\
"                for (j = 0; j < 2; j++)\n"\
"                    fixed_err_group[i][j] = MAX_INIT_ERROR;\n"\
"\n"\
"            for (flipped = 0; flipped < 2; flipped++)\n"\
"            {\n"\
"                for (partition = 0; partition < 2; partition++)\n"\
"                {\n"\
"                    int distance = 0;\n"\
"                    int num_pixels = 0;\n"\
"                    mean[flipped][partition] = VFLOAT3(0.0f, 0.0f, 0.0f);\n"\
"                    for (i = 0; i < 8; i++)\n"\
"                    {\n"\
"                        if (g_partition_indexes[flipped][partition][i] == 0.0f)\n"\
"                            continue;\n"\
"                        num_pixels++;\n"\
"                        mean[flipped][partition] = mean[flipped][partition] + trans_pixel[g_partition_indexes[flipped][partition][i]];\n"\
"                    }\n"\
"                    num_pixels = num_pixels ? num_pixels : 1;\n"\
"                    mean[flipped][partition] = mean[flipped][partition] / (float)(num_pixels);\n"\
"\n"\
"                    MEMBER(mean_quant[flipped][partition], X) = UCHAR(MEMBER(mean[flipped][partition], X)) >> 4;\n"\
"                    MEMBER(mean_quant[flipped][partition], Y) = UCHAR(MEMBER(mean[flipped][partition], Y)) >> 4;\n"\
"                    MEMBER(mean_quant[flipped][partition], Z) = UCHAR(MEMBER(mean[flipped][partition], Z)) >> 4;\n"\
"\n"\
"                    min_index[flipped][partition] = 0;\n"\
"                    max_index[flipped][partition] = 0;\n"\
"\n"\
"                    while ( ((int)MEMBER(mean_quant[flipped][partition], X) + min_index[flipped][partition] > 0) &&\n"\
"                        ((int)MEMBER(mean_quant[flipped][partition], Y) + min_index[flipped][partition] > 0) &&\n"\
"                        ((int)MEMBER(mean_quant[flipped][partition], Z) + min_index[flipped][partition] > 0))\n"\
"                    {\n"\
"                        min_index[flipped][partition]--;\n"\
"                        distance++;\n"\
"                        if (distance > max_distance)\n"\
"                            break;\n"\
"                    }\n"\
"                    distance = 0;\n"\
"                    while ( ((int)MEMBER(mean_quant[flipped][partition], X) + max_index[flipped][partition] < 16) &&\n"\
"                        ((int)MEMBER(mean_quant[flipped][partition], Y) + max_index[flipped][partition] < 16) &&\n"\
"                        ((int)MEMBER(mean_quant[flipped][partition], Z) + max_index[flipped][partition] < 16))\n"\
"                    {\n"\
"                        max_index[flipped][partition]++;\n"\
"                        distance++;\n"\
"                        if (distance > max_distance)\n"\
"                            break;\n"\
"                    }\n"\
"                }\n"\
"            }\n"\
"#if 1\n"\
"            for (flipped = 0; flipped < 2; flipped++)\n"\
"            {\n"\
"                for (partition = 0; partition < 2; partition++)\n"\
"                {\n"\
"                    int ip0;\n"\
"                    for (ip0 = min_index[flipped][partition]; ip0 <= max_index[flipped][partition]; ip0++)\n"\
"                    {\n"\
"                        uchar3 l0_quant;\n"\
"                        float err;\n"\
"\n"\
"                        MEMBER(l0_quant, X) = MEMBER(mean_quant[flipped][partition], X) + ip0;\n"\
"                        MEMBER(l0_quant, Y) = MEMBER(mean_quant[flipped][partition], Y) + ip0;\n"\
"                        MEMBER(l0_quant, Z) = MEMBER(mean_quant[flipped][partition], Z) + ip0;\n"\
"\n"\
"                        err = ETC_EvaluateErrorWeighted(is_ypbpr, trans_pixel, weight, ETC_RGBExpandVecTo4Bit(l0_quant), &g_partition_indexes[flipped][partition][0]);\n"\
"\n"\
"                        if (err < fixed_err_group[flipped][partition])\n"\
"                        {\n"\
"                            fixed_err_group[flipped][partition] = err;\n"\
"                            fixed_positions_group[flipped][partition] = l0_quant;\n"\
"                        }\n"\
"                    }\n"\
"                }\n"\
"            }\n"\
"\n"\
"            if (fixed_err_group[0][0] + fixed_err_group[0][1] < fixed_err_group[1][0] + fixed_err_group[1][1])\n"\
"            {\n"\
"                fixed_err = fixed_err_group[0][0] + fixed_err_group[0][1];\n"\
"                best_positions[0] = fixed_positions_group[0][0];\n"\
"                best_positions[1] = fixed_positions_group[0][1];\n"\
"                best_flipped = 0;\n"\
"            }\n"\
"            else\n"\
"            {\n"\
"                fixed_err = fixed_err_group[1][0] + fixed_err_group[1][1];\n"\
"                best_positions[0] = fixed_positions_group[1][0];\n"\
"                best_positions[1] = fixed_positions_group[1][1];\n"\
"                best_flipped = 1;\n"\
"            }\n"\
"\n"\
"            found_fixed = 1;\n"\
"            if (found_fixed)\n"\
"            {\n"\
"                uchar3 best_pos[2];\n"\
"                float combined_err = 0.0f;\n"\
"\n"\
"                best_pos[0] = best_positions[0];\n"\
"                best_pos[1] = best_positions[1];\n"\
"\n"\
"                for (partition = 0; partition < 2; partition++)\n"\
"                {\n"\
"                    int neighbourhood_width = (quality == CODEC_QUALITY_BEST ? 3 : 1);\n"\
"                    float best_err = MAX_INIT_ERROR;\n"\
"                    int x;\n"\
"                    int y;\n"\
"                    int z;\n"\
"                    int min_x = MEMBER(best_positions[partition], X) > (neighbourhood_width - 1) ? MEMBER(best_positions[partition], X) - neighbourhood_width : 0;\n"\
"                    int min_y = MEMBER(best_positions[partition], Y) > (neighbourhood_width - 1) ? MEMBER(best_positions[partition], Y) - neighbourhood_width : 0;\n"\
"                    int min_z = MEMBER(best_positions[partition], Z) > (neighbourhood_width - 1) ? MEMBER(best_positions[partition], Z) - neighbourhood_width : 0;\n"\
"                    int max_x = MEMBER(best_positions[partition], X) < (15 - neighbourhood_width) ? MEMBER(best_positions[partition], X) + neighbourhood_width : 15;\n"\
"                    int max_y = MEMBER(best_positions[partition], Y) < (15 - neighbourhood_width) ? MEMBER(best_positions[partition], Y) + neighbourhood_width : 15;\n"\
"                    int max_z = MEMBER(best_positions[partition], Z) < (15 - neighbourhood_width) ? MEMBER(best_positions[partition], Z) + neighbourhood_width : 15;\n"\
"\n"\
"                    for (z = min_z; z <= max_z; z++)\n"\
"                        for (y = min_y; y <= max_y; y++)\n"\
"                            for (x = min_x; x <= max_x; x++)\n"\
"                            {\n"\
"                                uchar3 pos = UCHAR3(x, y, z);\n"\
"                                float err;\n"\
"                                pos = ETC_RGBExpandVecTo4Bit(pos);\n"\
"                                err = ETC_EvaluateErrorWeighted(is_ypbpr, trans_pixel, weight, pos, &g_partition_indexes[best_flipped][partition][0]);\n"\
"                                if (err < best_err)\n"\
"                                {\n"\
"                                    best_err = err;\n"\
"                                    best_pos[partition] = UCHAR3(x, y, z);\n"\
"                                }\n"\
"                            }\n"\
"                    combined_err += best_err;\n"\
"                }\n"\
"                best_positions[0] = best_pos[0];\n"\
"                best_positions[1] = best_pos[1];\n"\
"\n"\
"                fixed_err = combined_err;\n"\
"\n"\
"                for (partition = 0; partition < 2; partition++)\n"\
"                {\n"\
"                    int terminate = 0;\n"\
"                    uchar3 pos = best_positions[partition];\n"\
"\n"\
"                    if (quality != CODEC_QUALITY_BEST)\n"\
"                        terminate = 1;\n"\
"\n"\
"                    while(!terminate)\n"\
"                    {\n"\
"                        short3 test_pos[27];\n"\
"                        float dist[27];\n"\
"                        int best_index;\n"\
"                        float best_dist;\n"\
"                        int terminate_count = 0;\n"\
"\n"\
"                        for (j = 0; j < 27; j++)\n"\
"                            test_pos[j] = SHORT3(MEMBER(pos, X), MEMBER(pos, Y), MEMBER(pos, Z)) + SHORT3((j % 3) - 1, ((j / 3) % 3) - 1, j/9 - 1);\n"\
"\n"\
"                        for (j = 0; j < 27; j++)\n"\
"                        {\n"\
"                            if ((MEMBER(test_pos[j], X) > 15) || (MEMBER(test_pos[j], Y) > 15) || (MEMBER(test_pos[j], Z) > 15) || (MEMBER(test_pos[j], X) < 0) || (MEMBER(test_pos[j], Y) < 0) || (MEMBER(test_pos[j], Z) < 0))\n"\
"                                dist[j] = MAX_INIT_ERROR;\n"\
"                            else\n"\
"                            {\n"\
"                                uchar3 v;\n"\
"\n"\
"                                v = ETC_RGBExpandVecTo4Bit(UCHAR3(MEMBER(test_pos[j], X), MEMBER(test_pos[j], Y), MEMBER(test_pos[j], Z)));\n"\
"\n"\
"                                dist[j] = ETC_EvaluateErrorWeighted(is_ypbpr, trans_pixel, weight, ETC_RGBExpandVecTo4Bit(v), &g_partition_indexes[best_flipped][partition][0]);\n"\
"                            }\n"\
"                        }\n"\
"\n"\
"                        best_dist = dist[0];\n"\
"                        best_index = 0;\n"\
"                        for (j = 1; j < 27; j++)\n"\
"                        {\n"\
"                            if (dist[j] < best_dist)\n"\
"                            {\n"\
"                                best_dist = dist[j];\n"\
"                                best_index = j;\n"\
"                            }\n"\
"                        }\n"\
"\n"\
"                        best_positions[partition] = pos;\n"\
"\n"\
"                        if (dist[13] == best_dist)\n"\
"                            break;\n"\
"\n"\
"                        for (j = 0; j < 27; j++)\n"\
"                            if (dist[j] == MAX_INIT_ERROR)\n"\
"                                terminate_count++;\n"\
"\n"\
"                        if (terminate_count >= 26)\n"\
"                            break;\n"\
"\n"\
"                        pos = UCHAR3(MEMBER(test_pos[best_index], X), MEMBER(test_pos[best_index], Y), MEMBER(test_pos[best_index], Z));\n"\
"                    }\n"\
"                }\n"\
"            }\n"\
"\n"\
"            if (found_fixed && fixed_err < best_total_error)\n"\
"            {\n"\
"                enc_mode = ETC_ENC_MODE_NODELTA;\n"\
"                best_total_error = fixed_err;\n"\
"                params_partition.rgb[0] = ETC_RGBExpandVecTo4Bit(best_positions[0]);\n"\
"                params_partition.rgb[1] = ETC_RGBExpandVecTo4Bit(best_positions[1]);\n"\
"                params_partition.is_flipped = best_flipped;\n"\
"            }\n"\
"        }\n"\
"#endif\n"\
"\n"\
"        // Non-delta mode\n"\
"        ETC_PrepareSampleList(1, sample_list);\n"\
"\n"\
"        for (flipped = 0; flipped < 2; flipped++)\n"\
"        {\n"\
"            for (partition = 0; partition < 2; partition++)\n"\
"            {\n"\
"                etc_sample_t sample;\n"\
"                float offset = 0.0f;\n"\
"\n"\
"                if (quality == CODEC_QUALITY_NORMAL)\n"\
"                    offset = 0.0f;\n"\
"                else if (quality == CODEC_QUALITY_HIGH)\n"\
"                    offset = 48.0f;\n"\
"                else \n"\
"                    offset = 96.0f;\n"\
"\n"\
"                if ((quality == CODEC_QUALITY_NORMAL) || (quality == CODEC_QUALITY_HIGH))\n"\
"                {\n"\
"                    MEMBER(proj_mins, X) = ((uint)clamp(MEMBER(projected_mins[flipped][partition], X) - offset, 0.0f, 255.0f)) >> 4;\n"\
"                    MEMBER(proj_mins, Y) = ((uint)clamp(MEMBER(projected_mins[flipped][partition], Y) - offset, 0.0f, 255.0f)) >> 4;\n"\
"                    MEMBER(proj_mins, Z) = ((uint)clamp(MEMBER(projected_mins[flipped][partition], Z) - offset, 0.0f, 255.0f)) >> 4;\n"\
"                    MEMBER(proj_maxs, X) = ((uint)clamp(MEMBER(projected_maxs[flipped][partition], X) + offset + 7, 0.0f, 255.0f)) >> 4;\n"\
"                    MEMBER(proj_maxs, Y) = ((uint)clamp(MEMBER(projected_maxs[flipped][partition], Y) + offset + 7, 0.0f, 255.0f)) >> 4;\n"\
"                    MEMBER(proj_maxs, Z) = ((uint)clamp(MEMBER(projected_maxs[flipped][partition], Z) + offset + 7, 0.0f, 255.0f)) >> 4;\n"\
"                }\n"\
"                else\n"\
"                {\n"\
"                    proj_mins = UCHAR3(0, 0, 0);\n"\
"                    proj_maxs = UCHAR3(15, 15, 15);\n"\
"                }\n"\
"\n"\
"                sample.pos_quantised = proj_mins;\n"\
"                pathing_params.partition_indexes = &g_partition_indexes[flipped][partition][0];\n"\
"                sample.error = ETC_EvaluateErrorWeighted(is_ypbpr, trans_pixel, weight, ETC_RGBExpandVecTo4Bit(sample.pos_quantised), &g_partition_indexes[flipped][partition][0]);\n"\
"                ETC_LeastCostDirectedPathWeighted(1, 1, error_target, refine_search, is_ypbpr, trans_pixel, weight, sample, &sample_list[flipped][partition][0], MEMBER(proj_maxs, X), MEMBER(proj_maxs, Y), MEMBER(proj_maxs, Z), &pathing_params, ETC_RGBEXPANDVECTO4BIT, ETC_EVALUATEDELTAERRORGENERICWEIGHTED);\n"\
"            }\n"\
"        }\n"\
"\n"\
"        for (i = 0; i < 2; i++)\n"\
"            best_dist[i] = sample_list[i][0][0].error + sample_list[i][1][0].error;\n"\
"\n"\
"        if (best_dist[1] < best_dist[0])\n"\
"            is_non_delta_flipped = 1;\n"\
"        else\n"\
"            is_non_delta_flipped = 0;\n"\
"\n"\
"        if (best_dist[is_non_delta_flipped] < best_total_error)\n"\
"        {\n"\
"            best_total_error = best_dist[is_non_delta_flipped];\n"\
"\n"\
"            enc_mode = ETC_ENC_MODE_NODELTA;\n"\
"            params_partition.rgb[0] = ETC_RGBExpandVecTo4Bit(sample_list[is_non_delta_flipped][0][0].pos_quantised);\n"\
"            params_partition.rgb[1] = ETC_RGBExpandVecTo4Bit(sample_list[is_non_delta_flipped][1][0].pos_quantised);\n"\
"            params_partition.is_flipped = is_non_delta_flipped;\n"\
"        }\n"\
"\n"\
"        ETC_GetOptimalIndexesWeighted(is_ypbpr, trans_pixel, weight, params_partition.rgb[0], &g_partition_indexes[params_partition.is_flipped][0][0], &params_partition.table[0], params_partition.indexes);\n"\
"        ETC_GetOptimalIndexesWeighted(is_ypbpr, trans_pixel, weight, params_partition.rgb[1], &g_partition_indexes[params_partition.is_flipped][1][0], &params_partition.table[1], params_partition.indexes);\n"\
"    }\n"\
"\n"\
"    if (is_etc2)\n"\
"    {\n"\
"        if ((best_total_error > error_target) && (allowed_modes & (ETC_MODE_T | ETC_MODE_H)))\n"\
"        {\n"\
"            int set_indexes[2][16];\n"\
"            int set_count[2];\n"\
"            etc_sample_t sample;\n"\
"\n"\
"            ETC_KMeansTHMode(trans_pixel, &set_indexes[0][0], &set_indexes[1][0], &set_count[0]); // TODO: this should be weighted\n"\
"\n"\
"            for (partition = 0; partition < 2; partition++) // TODO: this should be weighted\n"\
"            {\n"\
"                float3 mean = VFLOAT3(0.0f, 0.0f, 0.0f);\n"\
"                float mins_maxs_dist[2];\n"\
"                float3 temp;\n"\
"\n"\
"                for (i = 0; i < set_count[partition]; i++)\n"\
"                    mean = mean + trans_pixel[set_indexes[partition][i]];\n"\
"\n"\
"                mean = mean / (set_count[partition] ? (float)(set_count[partition]) : 1.0f);\n"\
"\n"\
"                if (set_count[partition])\n"\
"                {\n"\
"                    mins_maxs_dist[0] = dot(trans_pixel[set_indexes[partition][0]] - mean, VFLOAT3(0.57735f, 0.57735f, 0.57735f));\n"\
"                    mins_maxs_dist[1] = mins_maxs_dist[0];\n"\
"\n"\
"                    for (i = 0; i < set_count[partition]; i++)\n"\
"                    {\n"\
"                        float dist = dot(trans_pixel[set_indexes[partition][i]] - mean, VFLOAT3(0.57735f, 0.57735f, 0.57735f));\n"\
"\n"\
"                        if (dist < mins_maxs_dist[0])\n"\
"                            mins_maxs_dist[0] = dist;\n"\
"                        if (dist > mins_maxs_dist[1])\n"\
"                            mins_maxs_dist[1] = dist;\n"\
"                    }\n"\
"                    projected_mins[0][partition] = mean + VFLOAT3(0.57735f, 0.57735f, 0.57735f) * mins_maxs_dist[0];\n"\
"                    projected_maxs[0][partition] = mean + VFLOAT3(0.57735f, 0.57735f, 0.57735f) * mins_maxs_dist[1];\n"\
"                }\n"\
"                else\n"\
"                {\n"\
"                    projected_mins[0][partition] = mean;\n"\
"                    projected_maxs[0][partition] = mean;\n"\
"                }\n"\
"            }\n"\
"\n"\
"            if (allowed_modes & ETC_MODE_T)\n"\
"            {\n"\
"                // T mode\n"\
"                ETC_PrepareSampleList(1, sample_list);\n"\
"                for (flipped = 0; flipped < 2; flipped++)\n"\
"                {\n"\
"                    etc_sample_t sample;\n"\
"                    uchar3 proj_mins;\n"\
"                    uchar3 proj_maxs;\n"\
"                    float offset = 0.0f;\n"\
"\n"\
"                    if (quality == CODEC_QUALITY_NORMAL)\n"\
"                        offset = 0.0f;\n"\
"                    else if (quality == CODEC_QUALITY_HIGH)\n"\
"                        offset = 48.0f;\n"\
"                    else \n"\
"                        offset = 96.0f;\n"\
"\n"\
"                    if ((quality == CODEC_QUALITY_NORMAL) || (quality == CODEC_QUALITY_HIGH))\n"\
"                    {\n"\
"                        MEMBER(proj_mins, X) = ((uint)clamp(MEMBER(projected_mins[0][flipped], X) - offset, 0.0f, 255.0f)) >> 4;\n"\
"                        MEMBER(proj_mins, Y) = ((uint)clamp(MEMBER(projected_mins[0][flipped], Y) - offset, 0.0f, 255.0f)) >> 4;\n"\
"                        MEMBER(proj_mins, Z) = ((uint)clamp(MEMBER(projected_mins[0][flipped], Z) - offset, 0.0f, 255.0f)) >> 4;\n"\
"                        MEMBER(proj_maxs, X) = ((uint)clamp(MEMBER(projected_maxs[0][flipped], X) + offset + 7, 0.0f, 255.0f)) >> 4;\n"\
"                        MEMBER(proj_maxs, Y) = ((uint)clamp(MEMBER(projected_maxs[0][flipped], Y) + offset + 7, 0.0f, 255.0f)) >> 4;\n"\
"                        MEMBER(proj_maxs, Z) = ((uint)clamp(MEMBER(projected_maxs[0][flipped], Z) + offset + 7, 0.0f, 255.0f)) >> 4;\n"\
"                    }\n"\
"                    else\n"\
"                    {\n"\
"                        proj_mins = UCHAR3(0, 0, 0);\n"\
"                        proj_maxs = UCHAR3(15, 15, 15);\n"\
"                    }\n"\
"\n"\
"                    sample.pos_quantised = proj_mins;\n"\
"                    pathing_params.indexes = set_indexes[flipped];\n"\
"                    pathing_params.num_indexes = set_count[flipped];\n"\
"                    sample.error = ETC_EvaluateErrorTSingleWeighted(is_ypbpr, trans_pixel, weight, ETC_RGBExpandVecTo4Bit(sample.pos_quantised), set_indexes[flipped], set_count[flipped]);\n"\
"                    ETC_LeastCostDirectedPathWeighted(1, 1, error_target, refine_search, is_ypbpr, trans_pixel, weight, sample, &sample_list[flipped][0][0], MEMBER(proj_maxs, X), MEMBER(proj_maxs, Y), MEMBER(proj_maxs, Z), &pathing_params, ETC_RGBEXPANDVECTO4BIT, ETC_EVALUATETSINGLEERRORGENERICWEIGHTED);\n"\
"\n"\
"                    if ((quality == CODEC_QUALITY_NORMAL) || (quality == CODEC_QUALITY_HIGH))\n"\
"                    {\n"\
"                        MEMBER(proj_mins, X) = ((uint)clamp(MEMBER(projected_mins[0][(flipped + 1) % 2], X) - offset, 0.0f, 255.0f)) >> 4;\n"\
"                        MEMBER(proj_mins, Y) = ((uint)clamp(MEMBER(projected_mins[0][(flipped + 1) % 2], Y) - offset, 0.0f, 255.0f)) >> 4;\n"\
"                        MEMBER(proj_mins, Z) = ((uint)clamp(MEMBER(projected_mins[0][(flipped + 1) % 2], Z) - offset, 0.0f, 255.0f)) >> 4;\n"\
"                        MEMBER(proj_maxs, X) = ((uint)clamp(MEMBER(projected_maxs[0][(flipped + 1) % 2], X) + offset + 7, 0.0f, 255.0f)) >> 4;\n"\
"                        MEMBER(proj_maxs, Y) = ((uint)clamp(MEMBER(projected_maxs[0][(flipped + 1) % 2], Y) + offset + 7, 0.0f, 255.0f)) >> 4;\n"\
"                        MEMBER(proj_maxs, Z) = ((uint)clamp(MEMBER(projected_maxs[0][(flipped + 1) % 2], Z) + offset + 7, 0.0f, 255.0f)) >> 4;\n"\
"                    }\n"\
"                    else\n"\
"                    {\n"\
"                        proj_mins = UCHAR3(0, 0, 0);\n"\
"                        proj_maxs = UCHAR3(15, 15, 15);\n"\
"                    }\n"\
"\n"\
"                    sample.pos_quantised = proj_mins;\n"\
"                    pathing_params.indexes = set_indexes[(flipped + 1) % 2];\n"\
"                    pathing_params.num_indexes = set_count[(flipped + 1) % 2];\n"\
"                    sample.error = ETC_EvaluateErrorTTripleWeighted(is_ypbpr, trans_pixel, weight, ETC_RGBExpandVecTo4Bit(sample.pos_quantised), set_indexes[(flipped + 1) % 2], set_count[(flipped + 1) % 2]);\n"\
"                    ETC_LeastCostDirectedPathWeighted(1, 1, error_target, refine_search, is_ypbpr, trans_pixel, weight, sample, &sample_list[flipped][1][0], MEMBER(proj_maxs, X), MEMBER(proj_maxs, Y), MEMBER(proj_maxs, Z), &pathing_params, ETC_RGBEXPANDVECTO4BIT, ETC_EVALUATETTRIPLEERRORGENERICWEIGHTED);\n"\
"\n"\
"                }\n"\
"                for (i = 0; i < 2; i++)\n"\
"                    best_dist[i] = sample_list[i][0][0].error + sample_list[i][1][0].error;\n"\
"\n"\
"                if ((best_dist[0] < best_total_error) || (best_dist[1] < best_total_error))\n"\
"                {\n"\
"                    enc_mode = ETC_ENC_MODE_T;\n"\
"\n"\
"                    if (best_dist[1] < best_dist[0])\n"\
"                        is_flipped = 1;\n"\
"                    else\n"\
"                        is_flipped = 0;\n"\
"\n"\
"                    params_th.rgb[0] = ETC_RGBExpandVecTo4Bit(sample_list[is_flipped][0][0].pos_quantised);\n"\
"                    params_th.rgb[1] = ETC_RGBExpandVecTo4Bit(sample_list[is_flipped][1][0].pos_quantised);\n"\
"\n"\
"                    float d = ETC_GetOptimalTIndexesWeighted(is_ypbpr, trans_pixel, weight, params_th.rgb[0], params_th.rgb[1], &params_th.indexes[0], &params_th.table);\n"\
"\n"\
"                    best_total_error = d;\n"\
"                }\n"\
"            }\n"\
"\n"\
"            if ((best_total_error > error_target) && (allowed_modes & ETC_MODE_H))\n"\
"            {\n"\
"                int best_mode;\n"\
"\n"\
"                // H-Mode\n"\
"                ETC_PrepareSampleList(1, sample_list);\n"\
"                for (flipped = 0; flipped < 2; flipped++)\n"\
"                {\n"\
"                    uchar3 proj_mins;\n"\
"                    uchar3 proj_maxs;\n"\
"                    float offset = 0.0f;\n"\
"\n"\
"                    if (quality == CODEC_QUALITY_NORMAL)\n"\
"                        offset = 0.0f;\n"\
"                    else if (quality == CODEC_QUALITY_HIGH)\n"\
"                        offset = 48.0f;\n"\
"                    else \n"\
"                        offset = 96.0f;\n"\
"\n"\
"                    if ((quality == CODEC_QUALITY_NORMAL) || (quality == CODEC_QUALITY_HIGH))\n"\
"                    {\n"\
"                        MEMBER(proj_mins, X) = ((uint)clamp(MEMBER(projected_mins[0][flipped], X) - offset, 0.0f, 255.0f)) >> 4;\n"\
"                        MEMBER(proj_mins, Y) = ((uint)clamp(MEMBER(projected_mins[0][flipped], Y) - offset, 0.0f, 255.0f)) >> 4;\n"\
"                        MEMBER(proj_mins, Z) = ((uint)clamp(MEMBER(projected_mins[0][flipped], Z) - offset, 0.0f, 255.0f)) >> 4;\n"\
"                        MEMBER(proj_maxs, X) = ((uint)clamp(MEMBER(projected_maxs[0][flipped], X) + offset + 7, 0.0f, 255.0f)) >> 4;\n"\
"                        MEMBER(proj_maxs, Y) = ((uint)clamp(MEMBER(projected_maxs[0][flipped], Y) + offset + 7, 0.0f, 255.0f)) >> 4;\n"\
"                        MEMBER(proj_maxs, Z) = ((uint)clamp(MEMBER(projected_maxs[0][flipped], Z) + offset + 7, 0.0f, 255.0f)) >> 4;\n"\
"                    }\n"\
"                    else\n"\
"                    {\n"\
"                        proj_mins = UCHAR3(0, 0, 0);\n"\
"                        proj_maxs = UCHAR3(15, 15, 15);\n"\
"                    }\n"\
"                    for (table = 0; table < 8; table++)\n"\
"                    {\n"\
"                        sample.pos_quantised = proj_mins;\n"\
"                        pathing_params.indexes = set_indexes[flipped];\n"\
"                        pathing_params.num_indexes = set_count[flipped];\n"\
"                        pathing_params.mode = table;\n"\
"                        sample.error = ETC_EvaluateErrorHWeighted(is_ypbpr, trans_pixel, weight, ETC_RGBExpandVecTo4Bit(sample.pos_quantised), set_indexes[flipped], set_count[flipped], table);\n"\
"                        ETC_LeastCostDirectedPathWeighted(1, 1, error_target, refine_search, is_ypbpr, trans_pixel, weight, sample, &sample_list[flipped][table][0], MEMBER(proj_maxs, X), MEMBER(proj_maxs, Y), MEMBER(proj_maxs, Z), &pathing_params, ETC_RGBEXPANDVECTO4BIT, ETC_EVALUATEHERRORGENERICWEIGHTED);\n"\
"                    }\n"\
"                }\n"\
"\n"\
"                best_dist[0] = sample_list[0][0][0].error + sample_list[1][0][0].error;\n"\
"                best_mode = 0;\n"\
"\n"\
"                for (flipped = 0; flipped < 2; flipped++)\n"\
"                    for (table = 0; table < 8; table++)\n"\
"                        if (sample_list[0][table][0].error + sample_list[1][table][0].error < best_dist[0])\n"\
"                        {\n"\
"                            best_dist[0] = sample_list[0][table][0].error + sample_list[1][table][0].error;\n"\
"                            best_mode = table;\n"\
"                        }\n"\
"\n"\
"                if (best_dist[0] < best_total_error)\n"\
"                {\n"\
"                    ushort rgbpacked[2];\n"\
"\n"\
"                    enc_mode = ETC_ENC_MODE_H;\n"\
"\n"\
"                    params_th.table = best_mode;\n"\
"\n"\
"                    if ((MEMBER(sample_list[0][params_th.table][0].pos_quantised, X) == MEMBER(sample_list[1][params_th.table][0].pos_quantised, X)) &&\n"\
"                        (MEMBER(sample_list[0][params_th.table][0].pos_quantised, Y) == MEMBER(sample_list[1][params_th.table][0].pos_quantised, Y)) &&\n"\
"                        (MEMBER(sample_list[0][params_th.table][0].pos_quantised, Z) == MEMBER(sample_list[1][params_th.table][0].pos_quantised, Z)))\n"\
"                        MEMBER(sample_list[0][params_th.table][0].pos_quantised, X) = (MEMBER(sample_list[0][params_th.table][0].pos_quantised, X) + 1) % 16;\n"\
"\n"\
"                    params_th.rgb[0] = ETC_RGBExpandVecTo4Bit(sample_list[0][params_th.table][0].pos_quantised);\n"\
"                    params_th.rgb[1] = ETC_RGBExpandVecTo4Bit(sample_list[1][params_th.table][0].pos_quantised);\n"\
"\n"\
"                    rgbpacked[0] =  (((ushort)MEMBER(sample_list[0][params_th.table][0].pos_quantised, X)) << 8) |\n"\
"                        (((ushort)MEMBER(sample_list[0][params_th.table][0].pos_quantised, Y)) << 4) |\n"\
"                        (((ushort)MEMBER(sample_list[0][params_th.table][0].pos_quantised, Z)) << 0);\n"\
"\n"\
"                    rgbpacked[1] =  (((ushort)MEMBER(sample_list[1][params_th.table][0].pos_quantised, X)) << 8) |\n"\
"                        (((ushort)MEMBER(sample_list[1][params_th.table][0].pos_quantised, Y)) << 4) |\n"\
"                        (((ushort)MEMBER(sample_list[1][params_th.table][0].pos_quantised, Z)) << 0);\n"\
"\n"\
"                    if (!(params_th.table & 1))\n"\
"                    {\n"\
"                        if (rgbpacked[0] > rgbpacked[1])\n"\
"                        {\n"\
"                            params_th.rgb[0] = ETC_RGBExpandVecTo4Bit(sample_list[1][params_th.table][0].pos_quantised);\n"\
"                            params_th.rgb[1] = ETC_RGBExpandVecTo4Bit(sample_list[0][params_th.table][0].pos_quantised);\n"\
"                        }\n"\
"                    }\n"\
"                    else\n"\
"                    {\n"\
"                        if (rgbpacked[0] < rgbpacked[1])\n"\
"                        {\n"\
"                            params_th.rgb[0] = ETC_RGBExpandVecTo4Bit(sample_list[1][params_th.table][0].pos_quantised);\n"\
"                            params_th.rgb[1] = ETC_RGBExpandVecTo4Bit(sample_list[0][params_th.table][0].pos_quantised);\n"\
"                        }\n"\
"                    }\n"\
"\n"\
"                    best_total_error = ETC_GetOptimalHIndexesWeighted(is_ypbpr, trans_pixel, weight, params_th.rgb[0], params_th.rgb[1], params_th.indexes, params_th.table);\n"\
"                }\n"\
"            }\n"\
"        }\n"\
"\n"\
"        if ((best_total_error != 0.0f) && (allowed_modes & ETC_MODE_PLANAR))\n"\
"        {\n"\
"            // Planar mode: always check this because it's so cheap to compute\n"\
"\n"\
"            float3 points[3];\n"\
"            int3 points_i32[3];\n"\
"            float index_best_dist[3];\n"\
"            float best_dist = 0.0f;\n"\
"            int best_twiddle[3][3];\n"\
"            int index;\n"\
"            int twiddle0;\n"\
"            int twiddle1;\n"\
"            int twiddle2;\n"\
"            const float coeff[3][16] =\n"\
"            {\n"\
"                {23.0f, 17.0f, 11.0f, 5.0f, 17.0f, 11.0f, 5.0f, -1.0f, 11.0f, 5.0f, -1.0f, -7.0f, 5.0f, -1.0f, -7.0f, -13.0f},\n"\
"                {-1.0f, 9.0f, 19.0f, 29.0f, -7.0f, 3.0f, 13.0f, 23.0f, -13.0f, -3.0f, 7.0f, 17.0f, -19.0f, -9.0f, 1.0f, 11.0f},\n"\
"                {-1.0f, -7.0f, -13.0f, -19.0f, 9.0f, 3.0f, -3.0f, -9.0f, 19.0f, 13.0f, 7.0f, 1.0f, 29.0f, 23.0f, 17.0f, 11.0f}\n"\
"            };\n"\
"\n"\
"            points[0] = VFLOAT3(0.0f, 0.0f, 0.0f);\n"\
"            points[1] = VFLOAT3(0.0f, 0.0f, 0.0f);\n"\
"            points[2] = VFLOAT3(0.0f, 0.0f, 0.0f);\n"\
"\n"\
"            // TODO: this isn't trivial for the YCBCR case, just minimise in RGB space for now\n"\
"            if (is_ypbpr)\n"\
"                for (i = 0; i < 16; i++)\n"\
"                    trans_pixel[i] = clamp(ETC_ConvertToRGBf3(trans_pixel[i]), 0.0f, 255.0f);\n"\
"\n"\
"            for (j = 0; j < 16; j++)\n"\
"            {\n"\
"                MEMBER(points[0], X) += coeff[0][j] * MEMBER(trans_pixel[j], X) * weight[j];\n"\
"                MEMBER(points[1], X) += coeff[1][j] * MEMBER(trans_pixel[j], X) * weight[j];\n"\
"                MEMBER(points[2], X) += coeff[2][j] * MEMBER(trans_pixel[j], X) * weight[j];\n"\
"\n"\
"                MEMBER(points[0], Y) += coeff[0][j] * MEMBER(trans_pixel[j], Y) * weight[j];\n"\
"                MEMBER(points[1], Y) += coeff[1][j] * MEMBER(trans_pixel[j], Y) * weight[j];\n"\
"                MEMBER(points[2], Y) += coeff[2][j] * MEMBER(trans_pixel[j], Y) * weight[j];\n"\
"\n"\
"                MEMBER(points[0], Z) += coeff[0][j] * MEMBER(trans_pixel[j], Z) * weight[j];\n"\
"                MEMBER(points[1], Z) += coeff[1][j] * MEMBER(trans_pixel[j], Z) * weight[j];\n"\
"                MEMBER(points[2], Z) += coeff[2][j] * MEMBER(trans_pixel[j], Z) * weight[j];\n"\
"            }\n"\
"\n"\
"            points[0] = points[0] * (1.0f / 80.0f);\n"\
"            points[1] = points[1] * (1.0f / 80.0f);\n"\
"            points[2] = points[2] * (1.0f / 80.0f);\n"\
"\n"\
"            points[0] = clamp(points[0], 0.0f, 255.0f);\n"\
"            points[1] = clamp(points[1], 0.0f, 255.0f);\n"\
"            points[2] = clamp(points[2], 0.0f, 255.0f);\n"\
"\n"\
"            points_i32[0] = INT3(ETC_RGBRoundTo6Bit((uchar)MEMBER(points[0], X)), ETC_RGBRoundTo7Bit((uchar)MEMBER(points[0], Y)), ETC_RGBRoundTo6Bit((uchar)MEMBER(points[0], Z)));\n"\
"            points_i32[1] = INT3(ETC_RGBRoundTo6Bit((uchar)MEMBER(points[1], X)), ETC_RGBRoundTo7Bit((uchar)MEMBER(points[1], Y)), ETC_RGBRoundTo6Bit((uchar)MEMBER(points[1], Z)));\n"\
"            points_i32[2] = INT3(ETC_RGBRoundTo6Bit((uchar)MEMBER(points[2], X)), ETC_RGBRoundTo7Bit((uchar)MEMBER(points[2], Y)), ETC_RGBRoundTo6Bit((uchar)MEMBER(points[2], Z)));\n"\
"\n"\
"            for (index = 0; index < 3; index++)\n"\
"                index_best_dist[index] = MAX_INIT_ERROR;\n"\
"\n"\
"            for (twiddle0 = -2; twiddle0 <= 2; twiddle0++)\n"\
"            {\n"\
"                for (twiddle1 = -2; twiddle1 <= 2; twiddle1++)\n"\
"                {\n"\
"                    for (twiddle2 = -2; twiddle2 <= 2; twiddle2++)\n"\
"                    {\n"\
"                        int ppoints[3][3];\n"\
"                        float comp_err[3];\n"\
"                        int comb;\n"\
"\n"\
"                        comb =  (MEMBER(points_i32[0], X) + twiddle0 * 4) | (MEMBER(points_i32[1], X) + twiddle1 * 4) | (MEMBER(points_i32[2], X) + twiddle2 * 4) |\n"\
"                            (MEMBER(points_i32[0], Y) + twiddle0 * 2) | (MEMBER(points_i32[1], Y) + twiddle1 * 2) | (MEMBER(points_i32[2], Y) + twiddle2 * 2) |\n"\
"                            (MEMBER(points_i32[0], Z) + twiddle0 * 4) | (MEMBER(points_i32[1], Z) + twiddle1 * 4) | (MEMBER(points_i32[2], Z) + twiddle2 * 4);\n"\
"\n"\
"                        // trick: this tests if any of the values has negative sign or is >255, halving the number of comparisons needed\n"\
"                        if (comb & 0xFFFFFF00)\n"\
"                            continue;\n"\
"\n"\
"                        ppoints[0][0] = ETC_RGBRoundTo6Bit((MEMBER(points_i32[0], X) + twiddle0 * 4));\n"\
"                        ppoints[0][1] = ETC_RGBRoundTo6Bit((MEMBER(points_i32[1], X) + twiddle1 * 4));\n"\
"                        ppoints[0][2] = ETC_RGBRoundTo6Bit((MEMBER(points_i32[2], X) + twiddle2 * 4));\n"\
"\n"\
"                        ppoints[1][0] = ETC_RGBRoundTo7Bit((MEMBER(points_i32[0], Y) + twiddle0 * 2));\n"\
"                        ppoints[1][1] = ETC_RGBRoundTo7Bit((MEMBER(points_i32[1], Y) + twiddle1 * 2));\n"\
"                        ppoints[1][2] = ETC_RGBRoundTo7Bit((MEMBER(points_i32[2], Y) + twiddle2 * 2));\n"\
"\n"\
"                        ppoints[2][0] = ETC_RGBRoundTo6Bit((MEMBER(points_i32[0], Z) + twiddle0 * 4));\n"\
"                        ppoints[2][1] = ETC_RGBRoundTo6Bit((MEMBER(points_i32[1], Z) + twiddle1 * 4));\n"\
"                        ppoints[2][2] = ETC_RGBRoundTo6Bit((MEMBER(points_i32[2], Z) + twiddle2 * 4));\n"\
"\n"\
"                        comp_err[0] = 0.0f;\n"\
"                        comp_err[1] = 0.0f;\n"\
"                        comp_err[2] = 0.0f;\n"\
"\n"\
"                        for (j = 0; j < 4; j++) // v\n"\
"                        {\n"\
"                            for (i = 0; i < 4; i++) // u\n"\
"                            {\n"\
"                                float3 v;\n"\
"\n"\
"                                MEMBER(v, X) = (float)((i * (ppoints[0][1] - ppoints[0][0]) + j * (ppoints[0][2] - ppoints[0][0]) + 4 * (ppoints[0][0]) + 2) >> 2);\n"\
"                                MEMBER(v, Y) = (float)((i * (ppoints[1][1] - ppoints[1][0]) + j * (ppoints[1][2] - ppoints[1][0]) + 4 * (ppoints[1][0]) + 2) >> 2);\n"\
"                                MEMBER(v, Z) = (float)((i * (ppoints[2][1] - ppoints[2][0]) + j * (ppoints[2][2] - ppoints[2][0]) + 4 * (ppoints[2][0]) + 2) >> 2);\n"\
"\n"\
"                                v = clamp(v, VFLOAT3(0.0f, 0.0f, 0.0f), VFLOAT3(255.0f, 255.0f, 255.0f));\n"\
"                                v = v - trans_pixel[j*4 + i];\n"\
"\n"\
"                                comp_err[0] += MEMBER(v, X) * MEMBER(v, X) * weight[j*4 + i];\n"\
"                                comp_err[1] += MEMBER(v, Y) * MEMBER(v, Y) * weight[j*4 + i];\n"\
"                                comp_err[2] += MEMBER(v, Z) * MEMBER(v, Z) * weight[j*4 + i];\n"\
"                            }\n"\
"                        }\n"\
"                        for (index = 0; index < 3; index++)\n"\
"                        {\n"\
"                            if (comp_err[index] < index_best_dist[index])\n"\
"                            {\n"\
"                                int scale = (index == 1 ? 2 : 4);\n"\
"                                best_twiddle[index][0] = twiddle0 * scale;\n"\
"                                best_twiddle[index][1] = twiddle1 * scale;\n"\
"                                best_twiddle[index][2] = twiddle2 * scale;\n"\
"                                index_best_dist[index] = comp_err[index];\n"\
"                            }\n"\
"                        }\n"\
"                    }\n"\
"                }\n"\
"            }\n"\
"            best_dist = index_best_dist[0] + index_best_dist[1] + index_best_dist[2];\n"\
"\n"\
"            if (best_dist < best_total_error)\n"\
"            {\n"\
"                params_planar.rgb[0] = UCHAR3(ETC_RGBRoundTo6Bit(MEMBER(points_i32[0], X) + best_twiddle[0][0]), ETC_RGBRoundTo7Bit(MEMBER(points_i32[0], Y) + best_twiddle[1][0]), ETC_RGBRoundTo6Bit(MEMBER(points_i32[0], Z) + best_twiddle[2][0]));\n"\
"                params_planar.rgb[1] = UCHAR3(ETC_RGBRoundTo6Bit(MEMBER(points_i32[1], X) + best_twiddle[0][1]), ETC_RGBRoundTo7Bit(MEMBER(points_i32[1], Y) + best_twiddle[1][1]), ETC_RGBRoundTo6Bit(MEMBER(points_i32[1], Z) + best_twiddle[2][1]));\n"\
"                params_planar.rgb[2] = UCHAR3(ETC_RGBRoundTo6Bit(MEMBER(points_i32[2], X) + best_twiddle[0][2]), ETC_RGBRoundTo7Bit(MEMBER(points_i32[2], Y) + best_twiddle[1][2]), ETC_RGBRoundTo6Bit(MEMBER(points_i32[2], Z) + best_twiddle[2][2]));\n"\
"\n"\
"                enc_mode = ETC_ENC_MODE_PLANAR;\n"\
"\n"\
"                best_total_error = best_dist;\n"\
"            }\n"\
"        }\n"\
"    }\n"\
"\n"\
"    if ((enc_mode == ETC_ENC_MODE_DELTA) || (enc_mode == ETC_ENC_MODE_NODELTA))\n"\
"    {\n"\
"        if (enc_mode == ETC_ENC_MODE_NODELTA)\n"\
"        {\n"\
"            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], X) >> 4, 28, 4);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[1], X) >> 4, 24, 4);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], Y) >> 4, 20, 4);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[1], Y) >> 4, 16, 4);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], Z) >> 4, 12, 4);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[1], Z) >> 4,  8, 4);\n"\
"            ETC_WriteBits(local_block, 0, 1, 1); // diff bit\n"\
"        }\n"\
"        else\n"\
"        {\n"\
"            int3 diff;\n"\
"\n"\
"            MEMBER(diff, X) = (MEMBER(params_partition.rgb[1], X) >> 3) - (MEMBER(params_partition.rgb[0], X) >> 3);\n"\
"            MEMBER(diff, Y) = (MEMBER(params_partition.rgb[1], Y) >> 3) - (MEMBER(params_partition.rgb[0], Y) >> 3);\n"\
"            MEMBER(diff, Z) = (MEMBER(params_partition.rgb[1], Z) >> 3) - (MEMBER(params_partition.rgb[0], Z) >> 3);\n"\
"\n"\
"            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], X) >> 3, 27, 5);\n"\
"            ETC_WriteBits(local_block, MEMBER(diff, X) >> 0, 24, 3);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], Y) >> 3, 19, 5);\n"\
"            ETC_WriteBits(local_block, MEMBER(diff, Y) >> 0, 16, 3);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], Z) >> 3, 11, 5);\n"\
"            ETC_WriteBits(local_block, MEMBER(diff, Z) >> 0,  8, 3);\n"\
"            ETC_WriteBits(local_block, 1, 1, 1); // diff bit\n"\
"        }\n"\
"        ETC_WriteBits(local_block, params_partition.table[0], 5, 3); // table codeword 1\n"\
"        ETC_WriteBits(local_block, params_partition.table[1], 2, 3); // table codeword 2\n"\
"        ETC_WriteBits(local_block, params_partition.is_flipped, 0, 1); // flip bit\n"\
"\n"\
"        for (i = 0; i < 16; i++)\n"\
"        {\n"\
"            int index = (i%4)*4 + i/4;\n"\
"\n"\
"            int idx = params_partition.indexes[i];\n"\
"\n"\
"            ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);\n"\
"            ETC_WriteBits(local_block, idx & 1, 32 + index, 1);\n"\
"\n"\
"        }\n"\
"        ETC_PackBlockSwapOrder(block, local_block);\n"\
"    }\n"\
"    if (is_etc2)\n"\
"    {\n"\
"        if (enc_mode == ETC_ENC_MODE_T)\n"\
"        {\n"\
"            int min_rd = -4 + ((MEMBER(params_th.rgb[0], X) >> 4) & 3);\n"\
"            int max_rd = ((MEMBER(params_th.rgb[0], X) >> 4) & 3);\n"\
"            int min_r = (MEMBER(params_th.rgb[0], X) >> 6) & 3;\n"\
"            int max_r = 28 + min_r;\n"\
"            uchar r;\n"\
"            uchar rd;\n"\
"\n"\
"            if (min_rd + min_r < 0)\n"\
"            {\n"\
"                r = min_r;\n"\
"                rd = min_rd;\n"\
"            }\n"\
"            else\n"\
"            {\n"\
"                r = max_r;\n"\
"                rd = max_rd;\n"\
"            }\n"\
"\n"\
"            ETC_WriteBits(local_block, r, 27, 5);\n"\
"            ETC_WriteBits(local_block, rd, 24, 3);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Y) >> 4, 20, 4);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Z) >> 4, 16, 4);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], X) >> 4, 12, 4);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Y) >> 4,  8, 4);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Z) >> 4,  4, 4);\n"\
"\n"\
"            ETC_WriteBits(local_block, (params_th.table >> 1) & 3, 2, 2);\n"\
"            ETC_WriteBits(local_block, 1, 1, 1); // diff bit\n"\
"            ETC_WriteBits(local_block, params_th.table & 1, 0, 1); // flip bit\n"\
"\n"\
"            for (i = 0; i < 16; i++)\n"\
"            {\n"\
"                int index = (i % 4) * 4 + i / 4;\n"\
"\n"\
"                int idx = params_th.indexes[i];\n"\
"\n"\
"                ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);\n"\
"                ETC_WriteBits(local_block, idx & 1, 32 + index, 1);\n"\
"\n"\
"            }\n"\
"            ETC_PackBlockSwapOrder(block, local_block);\n"\
"        }\n"\
"        else if (enc_mode == ETC_ENC_MODE_H)\n"\
"        {\n"\
"            int min_gd = -4 + ((MEMBER(params_th.rgb[0], Z) >> 5) & 3);\n"\
"            int max_gd = ((MEMBER(params_th.rgb[0], Z) >> 5) & 3);\n"\
"            int min_g = ((MEMBER(params_th.rgb[0], Z) >> 7) & 1) | (((MEMBER(params_th.rgb[0], Y) >> 4) & 1) << 1);\n"\
"            int max_g = 28 + min_g;\n"\
"            uchar g;\n"\
"            uchar gd;\n"\
"            int rd;\n"\
"\n"\
"            if (min_gd + min_g < 0)\n"\
"            {\n"\
"                g = min_g;\n"\
"                gd = min_gd;\n"\
"            }\n"\
"            else\n"\
"            {\n"\
"                g = max_g;\n"\
"                gd = max_gd;\n"\
"            }\n"\
"\n"\
"            rd = MEMBER(params_th.rgb[0], Y) >> 5;\n"\
"            if (rd >= 4)\n"\
"                rd = -4 + (rd & 3);\n"\
"\n"\
"            if ((int)(MEMBER(params_th.rgb[0], X) >> 4) + rd < 0)\n"\
"                ETC_WriteBits(local_block, 1, 31, 1);\n"\
"            else\n"\
"                ETC_WriteBits(local_block, 0, 31, 1);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], X) >> 4, 27, 4);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Y) >> 5, 24, 3);\n"\
"            ETC_WriteBits(local_block, g, 19, 5);\n"\
"            ETC_WriteBits(local_block, gd, 16, 3);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Z) >> 4, 15, 1);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], X) >> 4, 11, 4);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Y) >> 4,  7, 4);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Z) >> 4,  3, 4);\n"\
"\n"\
"            ETC_WriteBits(local_block, (params_th.table >> 2) & 1, 2, 1);\n"\
"            ETC_WriteBits(local_block, 1, 1, 1); // diff bit\n"\
"            ETC_WriteBits(local_block, (params_th.table >> 1) & 1 & 1, 0, 1); // flip bit\n"\
"\n"\
"            for (i = 0; i < 16; i++)\n"\
"            {\n"\
"                int index = (i % 4) * 4 + i / 4;\n"\
"\n"\
"                int idx = params_th.indexes[i];\n"\
"\n"\
"                ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);\n"\
"                ETC_WriteBits(local_block, idx & 1, 32 + index, 1);\n"\
"\n"\
"            }\n"\
"            ETC_PackBlockSwapOrder(block, local_block);\n"\
"        }\n"\
"        else if (enc_mode == ETC_ENC_MODE_PLANAR)\n"\
"        {\n"\
"            int r, g, b;\n"\
"            int rd, gd, bd;\n"\
"            int min_bd;\n"\
"            int max_bd;\n"\
"            int min_b;\n"\
"            int max_b;\n"\
"\n"\
"            MEMBER(params_planar.rgb[0], X) >>= 2;\n"\
"            MEMBER(params_planar.rgb[0], Y) >>= 1;\n"\
"            MEMBER(params_planar.rgb[0], Z) >>= 2;\n"\
"\n"\
"            MEMBER(params_planar.rgb[1], X) >>= 2;\n"\
"            MEMBER(params_planar.rgb[1], Y) >>= 1;\n"\
"            MEMBER(params_planar.rgb[1], Z) >>= 2;\n"\
"\n"\
"            MEMBER(params_planar.rgb[2], X) >>= 2;\n"\
"            MEMBER(params_planar.rgb[2], Y) >>= 1;\n"\
"            MEMBER(params_planar.rgb[2], Z) >>= 2;\n"\
"\n"\
"            ETC_WriteBits(local_block, MEMBER(params_planar.rgb[2], Z), 32, 6);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_planar.rgb[2], Y), 38, 7);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_planar.rgb[2], X), 45, 6);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_planar.rgb[1], Z), 51, 6);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_planar.rgb[1], Y), 57, 7);\n"\
"\n"\
"            ETC_WriteBits(local_block, (MEMBER(params_planar.rgb[1], X)) & 1, 0, 1);\n"\
"            ETC_WriteBits(local_block, 1, 1, 1);\n"\
"            ETC_WriteBits(local_block, (MEMBER(params_planar.rgb[1], X) >> 1) & 31, 2, 5);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_planar.rgb[0], Z) & 7, 7, 3);\n"\
"            ETC_WriteBits(local_block, (MEMBER(params_planar.rgb[0], Z) >> 3) & 7, 11, 2);\n"\
"            ETC_WriteBits(local_block, (MEMBER(params_planar.rgb[0], Z) >> 5) & 1, 16, 1);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_planar.rgb[0], Y) & 63, 17, 6);\n"\
"            ETC_WriteBits(local_block, (MEMBER(params_planar.rgb[0], Y) >> 6) & 1, 24, 1);\n"\
"            ETC_WriteBits(local_block, MEMBER(params_planar.rgb[0], X), 25, 6);\n"\
"\n"\
"            r = (MEMBER(params_planar.rgb[0], X) >> 2) & 63;\n"\
"            rd = (MEMBER(params_planar.rgb[0], Y) >> 6) | ((MEMBER(params_planar.rgb[0], X) & 3) << 1);\n"\
"            g = (MEMBER(params_planar.rgb[0], Y) >> 2) & 15;\n"\
"            gd = (MEMBER(params_planar.rgb[0], Z) >> 5) | ((MEMBER(params_planar.rgb[0], Y) & 3) << 1);\n"\
"            b = (MEMBER(params_planar.rgb[0], Z) >> 3) & 3;\n"\
"            bd = (MEMBER(params_planar.rgb[0], Z) >> 1) & 3;\n"\
"\n"\
"            if (rd >= 4)\n"\
"                rd = -4 + (rd & 3);\n"\
"            if (gd >= 4)\n"\
"                gd = -4 + (gd & 3);\n"\
"            if (bd >= 4)\n"\
"                bd = -4 + (bd & 3);\n"\
"\n"\
"            if (r + rd < 0)\n"\
"                ETC_WriteBits(local_block, 1, 31, 1);\n"\
"            else\n"\
"                ETC_WriteBits(local_block, 0, 31, 1);\n"\
"\n"\
"            if (g + gd < 0)\n"\
"                ETC_WriteBits(local_block, 1, 23, 1);\n"\
"            else\n"\
"                ETC_WriteBits(local_block, 0, 23, 1);\n"\
"\n"\
"            min_bd = -4 + bd;\n"\
"            max_bd = bd;\n"\
"            min_b = b;\n"\
"            max_b = 28 + min_b;\n"\
"\n"\
"            if (min_b + min_bd < 0)\n"\
"            {\n"\
"                ETC_WriteBits(local_block, min_bd, 8, 3);\n"\
"                ETC_WriteBits(local_block, min_b, 11, 5);\n"\
"            }\n"\
"            else\n"\
"            {\n"\
"                ETC_WriteBits(local_block, max_bd, 8, 3);\n"\
"                ETC_WriteBits(local_block, max_b, 11, 5);\n"\
"            }\n"\
"            ETC_PackBlockSwapOrder(block, local_block);\n"\
"        }\n"\
"    }\n"\
"}\n"\
"\n"\
"float ETC_EvaluateErrorAlphaWeighted(float *alpha, float *weight, float base_alpha, float mul, int table)\n"\
"{\n"\
"    int i;\n"\
"    int j;\n"\
"    float total_err = 0.0f;\n"\
"    float point[8];\n"\
"\n"\
"    for (i = 0; i < 8; i++)\n"\
"        point[i] = clamp(base_alpha + mul * g_alpha[table][i], 0.0f, 255.0f);\n"\
"\n"\
"    for (i = 0; i < 16; i++)\n"\
"    {\n"\
"        float best_err = MAX_INIT_ERROR;\n"\
"        for (j = 0; j < 8; j++)\n"\
"        {\n"\
"            float err = (alpha[i] - point[j]) * (alpha[i] - point[j]) * weight[i];\n"\
"            if (err < best_err)\n"\
"                best_err = err;\n"\
"        }\n"\
"        total_err += best_err;\n"\
"    }\n"\
"    return total_err;\n"\
"}\n"\
"\n"\
"float ETC_FindBestBaseAlphaWeighted(float *alpha, float *weight, float alpha_mins, float alpha_maxs, float mul, int table, int *best_base_alpha)\n"\
"{\n"\
"    int k;\n"\
"    float a = alpha_mins;\n"\
"    float b = alpha_maxs;\n"\
"    float c = b - (b - a) * M_INV_GOLDEN_F;\n"\
"    float d = a + (b - a) * M_INV_GOLDEN_F;\n"\
"    float best_error = MAX_INIT_ERROR;\n"\
"    float fc = 0.0f;\n"\
"    float fd = 0.0f;\n"\
"\n"\
"    fc = ETC_EvaluateErrorAlphaWeighted(alpha, weight, floor(c + 0.5f), mul, table);\n"\
"    fd = ETC_EvaluateErrorAlphaWeighted(alpha, weight, floor(d + 0.5f), mul, table);\n"\
"\n"\
"    for (k = 0; (k < 16) && (b - a) > 0.5f; k++)\n"\
"    {\n"\
"        if (fc < fd)\n"\
"        {\n"\
"            b = d;\n"\
"            c = b - (b - a) * M_INV_GOLDEN_F;\n"\
"            d = a + (b - a) * M_INV_GOLDEN_F;\n"\
"            fd = fc;\n"\
"            fc = ETC_EvaluateErrorAlphaWeighted(alpha, weight, floor(c + 0.5f), mul, table);\n"\
"        }\n"\
"        else\n"\
"        {\n"\
"            a = c;\n"\
"            c = b - (b - a) * M_INV_GOLDEN_F;\n"\
"            d = a + (b - a) * M_INV_GOLDEN_F;\n"\
"            fc = fd;\n"\
"            fd = ETC_EvaluateErrorAlphaWeighted(alpha, weight, floor(d + 0.5f), mul, table);\n"\
"        }\n"\
"    }\n"\
"    if (fc < fd)\n"\
"    {\n"\
"        *best_base_alpha = (int)c;\n"\
"        return fc;\n"\
"    }\n"\
"    else\n"\
"    {\n"\
"        *best_base_alpha = (int)d;\n"\
"        return fd;\n"\
"    }\n"\
"}\n"\
"\n"\
"void ETC_GetOptimalIndexesAlphaWeighted(float *alpha, float *weight, float base_alpha, float mul, int table, int *indexes)\n"\
"{\n"\
"    int i;\n"\
"    int j;\n"\
"    float point[8];\n"\
"\n"\
"    for (i = 0; i < 8; i++)\n"\
"        point[i] = clamp(base_alpha + mul * g_alpha[table][i], 0.0f, 255.0f);\n"\
"\n"\
"    for (i = 0; i < 16; i++)\n"\
"    {\n"\
"        float best_err = MAX_INIT_ERROR;\n"\
"        for (j = 0; j < 8; j++)\n"\
"        {\n"\
"            float err = (alpha[i] - point[j]) * (alpha[i] - point[j]) * weight[i];\n"\
"            if (err < best_err)\n"\
"            {\n"\
"                best_err = err;\n"\
"                indexes[i] = j;\n"\
"            }\n"\
"        }\n"\
"    }\n"\
"}\n"\
"\n"\
"void ETC_EncodeAlphaWeighted(\n"\
"    float error_target,\n"\
"    int refine_search,\n"\
"    int search_radius,\n"\
"    float4 *pixel,\n"\
"    float *weight,\n"\
"    __global uchar *block)\n"\
"{\n"\
"    float alpha[16];\n"\
"    float alpha_mins;\n"\
"    float alpha_maxs;\n"\
"    float alpha_mid;\n"\
"    float alpha_half_range;\n"\
"    float best_error = MAX_INIT_ERROR;\n"\
"    float best_mul;\n"\
"    int best_table;\n"\
"    int i, j;\n"\
"    int alpha_index[16];\n"\
"    int best_base_alpha;\n"\
"    uchar local_block[8];\n"\
"\n"\
"    for (i = 0; i < 16; i++)\n"\
"        alpha[i] = MEMBER(pixel[i], W);\n"\
"\n"\
"    alpha_mins = alpha[0];\n"\
"    alpha_maxs = alpha[0];\n"\
"\n"\
"    for (i = 1; i < 16; i++)\n"\
"    {\n"\
"        alpha_mins = min(alpha_mins, alpha[i]);\n"\
"        alpha_maxs = max(alpha_maxs, alpha[i]);\n"\
"    }\n"\
"    alpha_mid = floor((alpha_mins + alpha_maxs) * 0.5f + 0.5f);\n"\
"    alpha_half_range = (alpha_maxs - alpha_mins) * 0.5f;\n"\
"\n"\
"    for (i = 0; i < 16; i++)\n"\
"    {\n"\
"        int lower_mul = (int)clamp((int)max(floor(2.0f * alpha_half_range / g_alpha_range[i]), 1.0f) - search_radius, 1, 16 - (search_radius * 2 + 1));\n"\
"        for (j = 0; j < search_radius * 2 + 1; j++)\n"\
"        {\n"\
"            float mul = (float)lower_mul + (float)j;\n"\
"            float err = ETC_EvaluateErrorAlphaWeighted(alpha, weight, alpha_mid, mul, i);\n"\
"\n"\
"            if (err < best_error)\n"\
"            {\n"\
"                best_table = i;\n"\
"                best_error = err;\n"\
"                best_mul = mul;\n"\
"                best_base_alpha = (int)alpha_mid;\n"\
"            }\n"\
"            if (refine_search)\n"\
"            {\n"\
"                int base_alpha[2];\n"\
"                float err_left = ETC_FindBestBaseAlphaWeighted(alpha, weight, alpha_mins, alpha_mid, mul, i, &base_alpha[0]);\n"\
"                float err_right = ETC_FindBestBaseAlphaWeighted(alpha, weight, alpha_mid, alpha_maxs, mul, i, &base_alpha[1]);\n"\
"\n"\
"                if (err_left < best_error)\n"\
"                {\n"\
"                    best_table = i;\n"\
"                    best_error = err_left;\n"\
"                    best_mul = mul;\n"\
"                    best_base_alpha = base_alpha[0];\n"\
"                }\n"\
"                if (err_right < best_error)\n"\
"                {\n"\
"                    best_table = i;\n"\
"                    best_error = err_right;\n"\
"                    best_mul = mul;\n"\
"                    best_base_alpha = base_alpha[1];\n"\
"                }\n"\
"            }\n"\
"        }\n"\
"\n"\
"    }\n"\
"    ETC_GetOptimalIndexesAlphaWeighted(alpha, weight, (float)best_base_alpha, best_mul, best_table, alpha_index);\n"\
"\n"\
"    ETC_WriteBits(local_block, (uint)best_base_alpha, 56, 8);\n"\
"    ETC_WriteBits(local_block, (uint)best_mul, 52, 4);\n"\
"    ETC_WriteBits(local_block, best_table, 48, 4);\n"\
"\n"\
"    for (i = 0; i < 16; i++)\n"\
"    {\n"\
"        int index = (i % 4) * 4 + i / 4;\n"\
"        ETC_WriteBits(local_block, alpha_index[i], 45 - index * 3, 3);\n"\
"    }\n"\
"\n"\
"    ETC_PackBlockReverseOrder(block, local_block);\n"\
"}\n"\
"\n"\
"void ETC_EncodeRGBA1WeightedFast(\n"\
"    int allowed_modes,\n"\
"    int is_ypbpr,\n"\
"    float alpha_cutoff,\n"\
"    float4 *pixel,\n"\
"    float *weight,\n"\
"    __global uchar *block)\n"\
"{\n"\
"    int i, j, table, n;\n"\
"    float3 trans_pixel[16];\n"\
"    int is_delta;\n"\
"    int is_flipped;\n"\
"    int is_best_delta = 0;\n"\
"    float best_total_error = MAX_INIT_ERROR;\n"\
"    int enc_mode;\n"\
"    etc_partition_mode_params_t params_partition;\n"\
"    etc_th_mode_params_t params_th;\n"\
"    uchar local_block[8];\n"\
"    int transparency[16];\n"\
"    int transparent_count = 0;\n"\
"    etc_pathing_params_t pathing_params;\n"\
"    int real_transparent_count = 0;\n"\
"    float err[2] = {0.0f, 0.0f};\n"\
"    uchar3 partition_rgb[2][2];\n"\
"    etc_partition_mode_params_t params_partition_nodelta;\n"\
"    float best_error[5] = {MAX_INIT_ERROR, MAX_INIT_ERROR, MAX_INIT_ERROR, MAX_INIT_ERROR, MAX_INIT_ERROR};\n"\
"    int best_mode = 0;\n"\
"    int found_mode = 0;\n"\
"\n"\
"    for (i = 0; i < 16; i++)\n"\
"    {\n"\
"        MEMBER(trans_pixel[i], X) = MEMBER(pixel[i], X);\n"\
"        MEMBER(trans_pixel[i], Y) = MEMBER(pixel[i], Y);\n"\
"        MEMBER(trans_pixel[i], Z) = MEMBER(pixel[i], Z);\n"\
"    }\n"\
"    for (i = 0; i < 16; i++)\n"\
"    {\n"\
"        transparency[i] = (MEMBER(pixel[i], W) <= alpha_cutoff) ? (int)weight[i] : 0;\n"\
"        transparent_count += transparency[i];\n"\
"        real_transparent_count += ((MEMBER(pixel[i], W) <= alpha_cutoff) && (weight[i] != 0.0f)) ? 1 : 0;\n"\
"    }\n"\
"\n"\
"    if (transparent_count == 16)\n"\
"    {\n"\
"        ETC_WriteBits(local_block, 0, 27, 5);\n"\
"        ETC_WriteBits(local_block, 0, 24, 3);\n"\
"        ETC_WriteBits(local_block, 0, 19, 5);\n"\
"        ETC_WriteBits(local_block, 0, 16, 3);\n"\
"        ETC_WriteBits(local_block, 0, 11, 5);\n"\
"        ETC_WriteBits(local_block, 0,  8, 3);\n"\
"        ETC_WriteBits(local_block, 0, 1, 1); // diff bit\n"\
"\n"\
"        ETC_WriteBits(local_block, 0, 5, 3); // table codeword 1\n"\
"        ETC_WriteBits(local_block, 0, 2, 3); // table codeword 2\n"\
"        ETC_WriteBits(local_block, 0, 0, 1); // flip bit\n"\
"\n"\
"        for (i = 0; i < 16; i++)\n"\
"        {\n"\
"            int index = (i%4)*4 + i/4;\n"\
"            int idx = 2;\n"\
"\n"\
"            ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);\n"\
"            ETC_WriteBits(local_block, idx & 1, 32 + index, 1);\n"\
"        }\n"\
"        ETC_PackBlockSwapOrder(block, local_block);\n"\
"        return;\n"\
"    }\n"\
"\n"\
"    if (allowed_modes & ETC_MODE_NODELTA)\n"\
"    {\n"\
"        for (is_flipped = 0; is_flipped < 2; is_flipped++)\n"\
"        {\n"\
"            float proj_mean[2] = {0.0f, 0.0f};\n"\
"            float x[2] = {0.0f, 0.0f};\n"\
"            float z[2] = {0.0f, 0.0f};\n"\
"            float count[2] = {0.0f, 0.0f};\n"\
"\n"\
"            for (i = 0; i < 8; i++)\n"\
"            {\n"\
"                if (!transparency[g_partition_indexes[is_flipped][0][i]])\n"\
"                {\n"\
"                    x[0] += MEMBER(trans_pixel[g_partition_indexes[is_flipped][0][i]], X);\n"\
"                    x[0] -= MEMBER(trans_pixel[g_partition_indexes[is_flipped][0][i]], Y);\n"\
"                    z[0] += MEMBER(trans_pixel[g_partition_indexes[is_flipped][0][i]], Z);\n"\
"                    z[0] -= MEMBER(trans_pixel[g_partition_indexes[is_flipped][0][i]], Y);\n"\
"                    count[0] += 1.0f;\n"\
"                }\n"\
"\n"\
"                if (!transparency[g_partition_indexes[is_flipped][1][i]])\n"\
"                {\n"\
"                    x[1] += MEMBER(trans_pixel[g_partition_indexes[is_flipped][1][i]], X);\n"\
"                    x[1] -= MEMBER(trans_pixel[g_partition_indexes[is_flipped][1][i]], Y);\n"\
"                    z[1] += MEMBER(trans_pixel[g_partition_indexes[is_flipped][1][i]], Z);\n"\
"                    z[1] -= MEMBER(trans_pixel[g_partition_indexes[is_flipped][1][i]], Y);\n"\
"                    count[1] += 1.0f;\n"\
"                }\n"\
"            }\n"\
"\n"\
"            x[0] /= count[0] == 0.0f ? 1.0f : count[0];\n"\
"            x[1] /= count[1] == 0.0f ? 1.0f : count[1];\n"\
"            z[0] /= count[0] == 0.0f ? 1.0f : count[0];\n"\
"            z[1] /= count[1] == 0.0f ? 1.0f : count[1];\n"\
"\n"\
"            for (i = 0; i < 8; i++)\n"\
"            {\n"\
"                if (!transparency[g_partition_indexes[is_flipped][0][i]])\n"\
"                    proj_mean[0] += dot(trans_pixel[g_partition_indexes[is_flipped][0][i]] - VFLOAT3(x[0], 0.0f, z[0]), VFLOAT3(0.57735f, 0.57735f, 0.57735f));\n"\
"                if (!transparency[g_partition_indexes[is_flipped][1][i]])\n"\
"                    proj_mean[1] += dot(trans_pixel[g_partition_indexes[is_flipped][1][i]] - VFLOAT3(x[1], 0.0f, z[1]), VFLOAT3(0.57735f, 0.57735f, 0.57735f));\n"\
"            }\n"\
"\n"\
"            proj_mean[0] /= count[0] == 0.0f ? 1.0f : count[0];\n"\
"            proj_mean[1] /= count[1] == 0.0f ? 1.0f : count[1];\n"\
"            proj_mean[0] *= 0.57735f;\n"\
"            proj_mean[1] *= 0.57735f;\n"\
"\n"\
"            partition_rgb[is_flipped][0] = UCHAR3(clamp(x[0] + proj_mean[0], 0.0f, 255.0f), clamp(proj_mean[0], 0.0f, 255.0f), clamp(z[0] + proj_mean[0], 0.0f, 255.0f));\n"\
"            partition_rgb[is_flipped][1] = UCHAR3(clamp(x[1] + proj_mean[1], 0.0f, 255.0f), clamp(proj_mean[1], 0.0f, 255.0f), clamp(z[1] + proj_mean[1], 0.0f, 255.0f));\n"\
"\n"\
"            partition_rgb[is_flipped][0] = ETC_RGBRoundVecTo4Bit(partition_rgb[is_flipped][0]);\n"\
"            partition_rgb[is_flipped][1] = ETC_RGBRoundVecTo4Bit(partition_rgb[is_flipped][1]);\n"\
"\n"\
"            pathing_params.partition_indexes = &g_partition_indexes[is_flipped][0][0];\n"\
"            err[is_flipped] += EvaluateErrorGenericA1(ETC_EVALUATEDELTAERRORGENERIC, transparency, is_ypbpr, trans_pixel, partition_rgb[is_flipped][0], &pathing_params);\n"\
"            pathing_params.partition_indexes = &g_partition_indexes[is_flipped][1][0];\n"\
"            err[is_flipped] += EvaluateErrorGenericA1(ETC_EVALUATEDELTAERRORGENERIC, transparency, is_ypbpr, trans_pixel, partition_rgb[is_flipped][1], &pathing_params);\n"\
"        }\n"\
"        params_partition_nodelta.is_flipped = err[0] < err[1] ? 0 : 1;\n"\
"\n"\
"        best_error[ETC_ENC_MODE_NODELTA] = err[0] < err[1] ? err[0] : err[1];\n"\
"\n"\
"        params_partition_nodelta.rgb[0] = partition_rgb[params_partition_nodelta.is_flipped][0];\n"\
"        params_partition_nodelta.rgb[1] = partition_rgb[params_partition_nodelta.is_flipped][1];\n"\
"\n"\
"        if (!found_mode || (best_error[ETC_ENC_MODE_NODELTA] < best_error[best_mode]))\n"\
"        {\n"\
"            ETC_GetOptimalIndexesA1(transparency, is_ypbpr, trans_pixel, params_partition_nodelta.rgb[0], &g_partition_indexes[params_partition_nodelta.is_flipped][0][0], &params_partition_nodelta.table[0], params_partition_nodelta.indexes);\n"\
"            ETC_GetOptimalIndexesA1(transparency, is_ypbpr, trans_pixel, params_partition_nodelta.rgb[1], &g_partition_indexes[params_partition_nodelta.is_flipped][1][0], &params_partition_nodelta.table[1], params_partition_nodelta.indexes);\n"\
"\n"\
"            found_mode = 1;\n"\
"            best_mode = ETC_ENC_MODE_NODELTA;\n"\
"        }\n"\
"        err[0] = 0.0f;\n"\
"        err[1] = 0.0f;\n"\
"    }\n"\
"\n"\
"    if (allowed_modes & ETC_MODE_DELTA)\n"\
"    {\n"\
"        for (is_flipped = 0; is_flipped < 2; is_flipped++)\n"\
"        {\n"\
"            float proj_mean[2] = {0.0f, 0.0f};\n"\
"            float x[2] = {0.0f, 0.0f};\n"\
"            float z[2] = {0.0f, 0.0f};\n"\
"            float count[2] = {0.0f, 0.0f};\n"\
"\n"\
"            for (i = 0; i < 8; i++)\n"\
"            {\n"\
"                if (!transparency[g_partition_indexes[is_flipped][0][i]])\n"\
"                {\n"\
"                    x[0] += MEMBER(trans_pixel[g_partition_indexes[is_flipped][0][i]], X);\n"\
"                    x[0] -= MEMBER(trans_pixel[g_partition_indexes[is_flipped][0][i]], Y);\n"\
"                    z[0] += MEMBER(trans_pixel[g_partition_indexes[is_flipped][0][i]], Z);\n"\
"                    z[0] -= MEMBER(trans_pixel[g_partition_indexes[is_flipped][0][i]], Y);\n"\
"                    count[0] += 1.0f;\n"\
"                }\n"\
"\n"\
"                if (!transparency[g_partition_indexes[is_flipped][1][i]])\n"\
"                {\n"\
"                    x[1] += MEMBER(trans_pixel[g_partition_indexes[is_flipped][1][i]], X);\n"\
"                    x[1] -= MEMBER(trans_pixel[g_partition_indexes[is_flipped][1][i]], Y);\n"\
"                    z[1] += MEMBER(trans_pixel[g_partition_indexes[is_flipped][1][i]], Z);\n"\
"                    z[1] -= MEMBER(trans_pixel[g_partition_indexes[is_flipped][1][i]], Y);\n"\
"                    count[1] += 1.0f;\n"\
"                }\n"\
"            }\n"\
"\n"\
"            x[0] /= count[0] == 0.0f ? 1.0f : count[0];\n"\
"            x[1] /= count[1] == 0.0f ? 1.0f : count[1];\n"\
"            z[0] /= count[0] == 0.0f ? 1.0f : count[0];\n"\
"            z[1] /= count[1] == 0.0f ? 1.0f : count[1];\n"\
"\n"\
"            for (i = 0; i < 8; i++)\n"\
"            {\n"\
"                if (!transparency[g_partition_indexes[is_flipped][0][i]])\n"\
"                    proj_mean[0] += dot(trans_pixel[g_partition_indexes[is_flipped][0][i]] - VFLOAT3(x[0], 0.0f, z[0]), VFLOAT3(0.57735f, 0.57735f, 0.57735f));\n"\
"                if (!transparency[g_partition_indexes[is_flipped][1][i]])\n"\
"                    proj_mean[1] += dot(trans_pixel[g_partition_indexes[is_flipped][1][i]] - VFLOAT3(x[1], 0.0f, z[1]), VFLOAT3(0.57735f, 0.57735f, 0.57735f));\n"\
"            }\n"\
"\n"\
"            proj_mean[0] /= count[0] == 0.0f ? 1.0f : count[0];\n"\
"            proj_mean[1] /= count[1] == 0.0f ? 1.0f : count[1];\n"\
"            proj_mean[0] *= 0.57735f;\n"\
"            proj_mean[1] *= 0.57735f;\n"\
"\n"\
"            partition_rgb[is_flipped][0] = UCHAR3(clamp(x[0] + proj_mean[0], 0.0f, 255.0f), clamp(proj_mean[0], 0.0f, 255.0f), clamp(z[0] + proj_mean[0], 0.0f, 255.0f));\n"\
"            partition_rgb[is_flipped][1] = UCHAR3(clamp(x[1] + proj_mean[1], 0.0f, 255.0f), clamp(proj_mean[1], 0.0f, 255.0f), clamp(z[1] + proj_mean[1], 0.0f, 255.0f));\n"\
"\n"\
"            partition_rgb[is_flipped][0] = ETC_RGBRoundVecTo5Bit(partition_rgb[is_flipped][0]);\n"\
"            partition_rgb[is_flipped][1] = ETC_RGBRoundVecTo5Bit(partition_rgb[is_flipped][1]);\n"\
"\n"\
"            pathing_params.partition_indexes = &g_partition_indexes[is_flipped][0][0];\n"\
"            err[is_flipped] += EvaluateErrorGenericA1(ETC_EVALUATEDELTAERRORGENERIC, transparency, is_ypbpr, trans_pixel, partition_rgb[is_flipped][0], &pathing_params);\n"\
"            pathing_params.partition_indexes = &g_partition_indexes[is_flipped][1][0];\n"\
"            err[is_flipped] += EvaluateErrorGenericA1(ETC_EVALUATEDELTAERRORGENERIC, transparency, is_ypbpr, trans_pixel, partition_rgb[is_flipped][1], &pathing_params);\n"\
"        }\n"\
"        params_partition.is_flipped = err[0] < err[1] ? 0 : 1;\n"\
"\n"\
"        params_partition.rgb[0] = partition_rgb[params_partition.is_flipped][0];\n"\
"        params_partition.rgb[1] = partition_rgb[params_partition.is_flipped][1];\n"\
"\n"\
"        is_delta = 0;\n"\
"        int diff = (int)((MEMBER(params_partition.rgb[1], X)) >> 3) - (int)((MEMBER(params_partition.rgb[0], X) >> 3));\n"\
"        if (diff < 4 && diff >= -4)\n"\
"            is_delta++;\n"\
"        diff = (int)((MEMBER(params_partition.rgb[1], Y)) >> 3) - (int)((MEMBER(params_partition.rgb[0], Y) >> 3));\n"\
"        if (diff < 4 && diff >= -4)\n"\
"            is_delta++;\n"\
"        diff = (int)((MEMBER(params_partition.rgb[1], Z)) >> 3) - (int)((MEMBER(params_partition.rgb[0], Z) >> 3));\n"\
"        if (diff < 4 && diff >= -4)\n"\
"            is_delta++;\n"\
"\n"\
"        if (is_delta == 3)\n"\
"        {\n"\
"            best_error[ETC_ENC_MODE_DELTA] = err[0] < err[1] ? err[0] : err[1];\n"\
"            if (!found_mode || (best_error[ETC_ENC_MODE_DELTA] < best_error[best_mode]))\n"\
"            {\n"\
"                ETC_GetOptimalIndexesA1(transparency, is_ypbpr, trans_pixel, params_partition.rgb[0], &g_partition_indexes[params_partition.is_flipped][0][0], &params_partition.table[0], params_partition.indexes);\n"\
"                ETC_GetOptimalIndexesA1(transparency, is_ypbpr, trans_pixel, params_partition.rgb[1], &g_partition_indexes[params_partition.is_flipped][1][0], &params_partition.table[1], params_partition.indexes);\n"\
"\n"\
"                found_mode = 1;\n"\
"                best_mode = ETC_ENC_MODE_DELTA;\n"\
"            }\n"\
"        }\n"\
"    }\n"\
"    if (((best_error[best_mode] != 0.0f) || !found_mode) && (allowed_modes & (ETC_MODE_T | ETC_MODE_H)))\n"\
"    {\n"\
"        int set_indexes[2][16];\n"\
"        int set_count[2];\n"\
"        int best_error_flip;\n"\
"\n"\
"        ETC_KMeansTHMode(trans_pixel, &set_indexes[0][0], &set_indexes[1][0], &set_count[0]);\n"\
"\n"\
"        if (allowed_modes & ETC_MODE_T)\n"\
"        {\n"\
"            for (is_flipped = 0; is_flipped < 2; is_flipped++)\n"\
"            {\n"\
"                float proj_mean[2] = {0.0f, 0.0f};\n"\
"                float x[2] = {0.0f, 0.0f};\n"\
"                float z[2] = {0.0f, 0.0f};\n"\
"                float count[2] = {0.0f, 0.0f};\n"\
"\n"\
"                for (i = 0; i < set_count[is_flipped]; i++)\n"\
"                {\n"\
"                    if (!transparency[set_indexes[is_flipped][i]])\n"\
"                    {\n"\
"                        x[0] += MEMBER(trans_pixel[set_indexes[is_flipped][i]], X);\n"\
"                        x[0] -= MEMBER(trans_pixel[set_indexes[is_flipped][i]], Y);\n"\
"                        z[0] += MEMBER(trans_pixel[set_indexes[is_flipped][i]], Z);\n"\
"                        z[0] -= MEMBER(trans_pixel[set_indexes[is_flipped][i]], Y);\n"\
"                        count[0] += 1.0f;\n"\
"                    }\n"\
"                }\n"\
"                for (i = 0; i < set_count[(is_flipped + 1) % 2]; i++)\n"\
"                {\n"\
"                    if (!transparency[set_indexes[(is_flipped + 1) % 2][i]])\n"\
"                    {\n"\
"                        x[1] += MEMBER(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]], X);\n"\
"                        x[1] -= MEMBER(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]], Y);\n"\
"                        z[1] += MEMBER(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]], Z);\n"\
"                        z[1] -= MEMBER(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]], Y);\n"\
"                        count[1] += 1.0f;\n"\
"                    }\n"\
"                }\n"\
"\n"\
"                x[0] /= count[0] == 0.0f ? 1.0f : count[0];\n"\
"                x[1] /= count[1] == 0.0f ? 1.0f : count[1];\n"\
"                z[0] /= count[0] == 0.0f ? 1.0f : count[0];\n"\
"                z[1] /= count[1] == 0.0f ? 1.0f : count[1];\n"\
"\n"\
"                for (i = 0; i < set_count[is_flipped]; i++)\n"\
"                    if (!transparency[set_indexes[is_flipped][i]])\n"\
"                        proj_mean[0] += dot(trans_pixel[set_indexes[is_flipped][i]] - VFLOAT3(x[0], 0.0f, z[0]), VFLOAT3(0.57735f, 0.57735f, 0.57735f));\n"\
"                for (i = 0; i < set_count[(is_flipped + 1) % 2]; i++)\n"\
"                    if (!transparency[set_indexes[(is_flipped + 1) % 2][i]])\n"\
"                        proj_mean[1] += dot(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]] - VFLOAT3(x[1], 0.0f, z[1]), VFLOAT3(0.57735f, 0.57735f, 0.57735f));\n"\
"\n"\
"                proj_mean[0] /= count[0] == 0.0f ? 1.0f : count[0];\n"\
"                proj_mean[1] /= count[1] == 0.0f ? 1.0f : count[1];\n"\
"\n"\
"                proj_mean[0] *= 0.57735f;\n"\
"                proj_mean[1] *= 0.57735f;\n"\
"\n"\
"                partition_rgb[is_flipped][0] = UCHAR3(clamp(x[0] + proj_mean[0], 0.0f, 255.0f), clamp(proj_mean[0], 0.0f, 255.0f), clamp(z[0] + proj_mean[0], 0.0f, 255.0f));\n"\
"                partition_rgb[is_flipped][1] = UCHAR3(clamp(x[1] + proj_mean[1], 0.0f, 255.0f), clamp(proj_mean[1], 0.0f, 255.0f), clamp(z[1] + proj_mean[1], 0.0f, 255.0f));\n"\
"\n"\
"                partition_rgb[is_flipped][0] = ETC_RGBRoundVecTo4Bit(partition_rgb[is_flipped][0]);\n"\
"                partition_rgb[is_flipped][1] = ETC_RGBRoundVecTo4Bit(partition_rgb[is_flipped][1]);\n"\
"\n"\
"                params_th.rgb[0] = partition_rgb[is_flipped][0];\n"\
"                params_th.rgb[1] = partition_rgb[is_flipped][1];\n"\
"\n"\
"                err[is_flipped] = ETC_GetOptimalTIndexesA1(transparency, is_ypbpr, trans_pixel, params_th.rgb[0], params_th.rgb[1], &params_th.indexes[0], &params_th.table);\n"\
"            }\n"\
"\n"\
"            best_error[ETC_ENC_MODE_T] = err[0] < err[1] ? err[0] : err[1];\n"\
"            best_error_flip = err[0] < err[1] ? 0 : 1;\n"\
"\n"\
"            params_th.rgb[0] = partition_rgb[best_error_flip][0];\n"\
"            params_th.rgb[1] = partition_rgb[best_error_flip][1];\n"\
"            ETC_GetOptimalTIndexesA1(transparency, is_ypbpr, trans_pixel, params_th.rgb[0], params_th.rgb[1], &params_th.indexes[0], &params_th.table);\n"\
"\n"\
"            if (!found_mode || (best_error[ETC_ENC_MODE_T] < best_error[best_mode]))\n"\
"            {\n"\
"                found_mode = 1;\n"\
"                best_mode = ETC_ENC_MODE_T;\n"\
"            }\n"\
"        }\n"\
"        if (allowed_modes & ETC_MODE_H)\n"\
"        {\n"\
"            int best_table[2];\n"\
"            etc_th_mode_params_t params_th_local;\n"\
"\n"\
"            for (is_flipped = 0; is_flipped < 2; is_flipped++)\n"\
"            {\n"\
"                float proj_mean[2] = {0.0f, 0.0f};\n"\
"                float x[2] = {0.0f, 0.0f};\n"\
"                float z[2] = {0.0f, 0.0f};\n"\
"                float local_best_error = MAX_INIT_ERROR;\n"\
"\n"\
"                float count[2] = {0.0f, 0.0f};\n"\
"\n"\
"                for (i = 0; i < set_count[is_flipped]; i++)\n"\
"                {\n"\
"                    if (!transparency[set_indexes[is_flipped][i]])\n"\
"                    {\n"\
"                        x[0] += MEMBER(trans_pixel[set_indexes[is_flipped][i]], X);\n"\
"                        x[0] -= MEMBER(trans_pixel[set_indexes[is_flipped][i]], Y);\n"\
"                        z[0] += MEMBER(trans_pixel[set_indexes[is_flipped][i]], Z);\n"\
"                        z[0] -= MEMBER(trans_pixel[set_indexes[is_flipped][i]], Y);\n"\
"                        count[0] += 1.0f;\n"\
"                    }\n"\
"                }\n"\
"                for (i = 0; i < set_count[(is_flipped + 1) % 2]; i++)\n"\
"                {\n"\
"                    if (!transparency[set_indexes[(is_flipped + 1) % 2][i]])\n"\
"                    {\n"\
"                        x[1] += MEMBER(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]], X);\n"\
"                        x[1] -= MEMBER(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]], Y);\n"\
"                        z[1] += MEMBER(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]], Z);\n"\
"                        z[1] -= MEMBER(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]], Y);\n"\
"                        count[1] += 1.0f;\n"\
"                    }\n"\
"                }\n"\
"\n"\
"                x[0] /= count[0] == 0.0f ? 1.0f : count[0];\n"\
"                x[1] /= count[1] == 0.0f ? 1.0f : count[1];\n"\
"                z[0] /= count[0] == 0.0f ? 1.0f : count[0];\n"\
"                z[1] /= count[1] == 0.0f ? 1.0f : count[1];\n"\
"\n"\
"                for (i = 0; i < set_count[is_flipped]; i++)\n"\
"                    if (!transparency[set_indexes[is_flipped][i]])\n"\
"                        proj_mean[0] += dot(trans_pixel[set_indexes[is_flipped][i]] - VFLOAT3(x[0], 0.0f, z[0]), VFLOAT3(0.57735f, 0.57735f, 0.57735f));\n"\
"                for (i = 0; i < set_count[(is_flipped + 1) % 2]; i++)\n"\
"                    if (!transparency[set_indexes[(is_flipped + 1) % 2][i]])\n"\
"                        proj_mean[1] += dot(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]] - VFLOAT3(x[1], 0.0f, z[1]), VFLOAT3(0.57735f, 0.57735f, 0.57735f));\n"\
"\n"\
"                proj_mean[0] /= count[0] == 0.0f ? 1.0f : count[0];\n"\
"                proj_mean[1] /= count[1] == 0.0f ? 1.0f : count[1];\n"\
"\n"\
"                proj_mean[0] *= 0.57735f;\n"\
"                proj_mean[1] *= 0.57735f;\n"\
"\n"\
"                partition_rgb[is_flipped][0] = UCHAR3(clamp(x[0] + proj_mean[0], 0.0f, 255.0f), clamp(proj_mean[0], 0.0f, 255.0f), clamp(z[0] + proj_mean[0], 0.0f, 255.0f));\n"\
"                partition_rgb[is_flipped][1] = UCHAR3(clamp(x[1] + proj_mean[1], 0.0f, 255.0f), clamp(proj_mean[1], 0.0f, 255.0f), clamp(z[1] + proj_mean[1], 0.0f, 255.0f));\n"\
"\n"\
"                partition_rgb[is_flipped][0] = ETC_RGBRoundVecTo4Bit(partition_rgb[is_flipped][0]);\n"\
"                partition_rgb[is_flipped][1] = ETC_RGBRoundVecTo4Bit(partition_rgb[is_flipped][1]);\n"\
"\n"\
"                params_th_local.rgb[0] = partition_rgb[is_flipped][0];\n"\
"                params_th_local.rgb[1] = partition_rgb[is_flipped][1];\n"\
"\n"\
"                for (table = 0; table < 8; table++)\n"\
"                {\n"\
"                    float local_err = ETC_GetOptimalHIndexesA1(transparency, is_ypbpr, trans_pixel, params_th_local.rgb[0], params_th_local.rgb[1], &params_th_local.indexes[0], table);\n"\
"                    if (local_err < local_best_error)\n"\
"                    {\n"\
"                        best_table[is_flipped] = table;\n"\
"                        err[is_flipped] = local_err;\n"\
"                        local_best_error = local_err;\n"\
"                    }\n"\
"                }\n"\
"            }\n"\
"\n"\
"            best_error[ETC_ENC_MODE_H] = err[0] < err[1] ? err[0] : err[1];\n"\
"            best_error_flip = err[0] < err[1] ? 0 : 1;\n"\
"\n"\
"            params_th_local.table = best_table[best_error_flip];\n"\
"            params_th_local.rgb[0] = partition_rgb[best_error_flip][0];\n"\
"            params_th_local.rgb[1] = partition_rgb[best_error_flip][1];\n"\
"            ETC_GetOptimalHIndexesA1(transparency, is_ypbpr, trans_pixel, params_th_local.rgb[0], params_th_local.rgb[1], &params_th_local.indexes[0], params_th_local.table);\n"\
"\n"\
"            if (!found_mode || (best_error[ETC_ENC_MODE_H] < best_error[best_mode]))\n"\
"            {\n"\
"                found_mode = 1;\n"\
"                best_mode = ETC_ENC_MODE_H;\n"\
"                params_th = params_th_local;\n"\
"            }\n"\
"        }\n"\
"    }\n"\
"\n"\
"    if (best_mode == ETC_ENC_MODE_NODELTA)\n"\
"        params_partition = params_partition_nodelta;\n"\
"    enc_mode = best_mode;\n"\
"\n"\
"    if (enc_mode == ETC_ENC_MODE_DELTA)\n"\
"    {\n"\
"        int3 diff;\n"\
"\n"\
"        MEMBER(diff, X) = (MEMBER(params_partition.rgb[1], X) >> 3) - (MEMBER(params_partition.rgb[0], X) >> 3);\n"\
"        MEMBER(diff, Y) = (MEMBER(params_partition.rgb[1], Y) >> 3) - (MEMBER(params_partition.rgb[0], Y) >> 3);\n"\
"        MEMBER(diff, Z) = (MEMBER(params_partition.rgb[1], Z) >> 3) - (MEMBER(params_partition.rgb[0], Z) >> 3);\n"\
"\n"\
"        ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], X) >> 3, 27, 5);\n"\
"        ETC_WriteBits(local_block, MEMBER(diff, X) >> 0, 24, 3);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], Y) >> 3, 19, 5);\n"\
"        ETC_WriteBits(local_block, MEMBER(diff, Y) >> 0, 16, 3);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], Z) >> 3, 11, 5);\n"\
"        ETC_WriteBits(local_block, MEMBER(diff, Z) >> 0,  8, 3);\n"\
"        ETC_WriteBits(local_block, 0, 1, 1); // diff bit\n"\
"\n"\
"        ETC_WriteBits(local_block, params_partition.table[0], 5, 3); // table codeword 1\n"\
"        ETC_WriteBits(local_block, params_partition.table[1], 2, 3); // table codeword 2\n"\
"        ETC_WriteBits(local_block, params_partition.is_flipped, 0, 1); // flip bit\n"\
"\n"\
"        for (i = 0; i < 16; i++)\n"\
"        {\n"\
"            int index = (i%4)*4 + i/4;\n"\
"\n"\
"            int idx = params_partition.indexes[i];\n"\
"\n"\
"            if (transparency[i])\n"\
"                idx = 2;\n"\
"\n"\
"            ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);\n"\
"            ETC_WriteBits(local_block, idx & 1, 32 + index, 1);\n"\
"        }\n"\
"        ETC_PackBlockSwapOrder(block, local_block);\n"\
"    }\n"\
"    else if (enc_mode == ETC_ENC_MODE_T)\n"\
"    {\n"\
"        int min_rd = -4 + ((MEMBER(params_th.rgb[0], X) >> 4) & 3);\n"\
"        int max_rd = ((MEMBER(params_th.rgb[0], X) >> 4) & 3);\n"\
"        int min_r = (MEMBER(params_th.rgb[0], X) >> 6) & 3;\n"\
"        int max_r = 28 + min_r;\n"\
"        uchar r;\n"\
"        uchar rd;\n"\
"\n"\
"        if (min_rd + min_r < 0)\n"\
"        {\n"\
"            r = min_r;\n"\
"            rd = min_rd;\n"\
"        }\n"\
"        else\n"\
"        {\n"\
"            r = max_r;\n"\
"            rd = max_rd;\n"\
"        }\n"\
"\n"\
"        ETC_WriteBits(local_block, r, 27, 5);\n"\
"        ETC_WriteBits(local_block, rd, 24, 3);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Y) >> 4, 20, 4);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Z) >> 4, 16, 4);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], X) >> 4, 12, 4);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Y) >> 4,  8, 4);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Z) >> 4,  4, 4);\n"\
"\n"\
"        ETC_WriteBits(local_block, (params_th.table >> 1) & 3, 2, 2);\n"\
"        ETC_WriteBits(local_block, 0, 1, 1); // diff bit\n"\
"        ETC_WriteBits(local_block, params_th.table & 1, 0, 1); // flip bit\n"\
"\n"\
"        for (i = 0; i < 16; i++)\n"\
"        {\n"\
"            int index = (i % 4) * 4 + i / 4;\n"\
"\n"\
"            int idx = params_th.indexes[i];\n"\
"\n"\
"            if (transparency[i])\n"\
"                idx = 2;\n"\
"\n"\
"            ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);\n"\
"            ETC_WriteBits(local_block, idx & 1, 32 + index, 1);\n"\
"\n"\
"        }\n"\
"        ETC_PackBlockSwapOrder(block, local_block);\n"\
"    }\n"\
"    else if (enc_mode == ETC_ENC_MODE_H)\n"\
"    {\n"\
"        int min_gd = -4 + ((MEMBER(params_th.rgb[0], Z) >> 5) & 3);\n"\
"        int max_gd = ((MEMBER(params_th.rgb[0], Z) >> 5) & 3);\n"\
"        int min_g = ((MEMBER(params_th.rgb[0], Z) >> 7) & 1) | (((MEMBER(params_th.rgb[0], Y) >> 4) & 1) << 1);\n"\
"        int max_g = 28 + min_g;\n"\
"        uchar g;\n"\
"        uchar gd;\n"\
"        int rd;\n"\
"\n"\
"        if (min_gd + min_g < 0)\n"\
"        {\n"\
"            g = min_g;\n"\
"            gd = min_gd;\n"\
"        }\n"\
"        else\n"\
"        {\n"\
"            g = max_g;\n"\
"            gd = max_gd;\n"\
"        }\n"\
"\n"\
"        rd = MEMBER(params_th.rgb[0], Y) >> 5;\n"\
"        if (rd >= 4)\n"\
"            rd = -4 + (rd & 3);\n"\
"\n"\
"        if ((int)(MEMBER(params_th.rgb[0], X) >> 4) + rd < 0)\n"\
"            ETC_WriteBits(local_block, 1, 31, 1);\n"\
"        else\n"\
"            ETC_WriteBits(local_block, 0, 31, 1);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], X) >> 4, 27, 4);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Y) >> 5, 24, 3);\n"\
"        ETC_WriteBits(local_block, g, 19, 5);\n"\
"        ETC_WriteBits(local_block, gd, 16, 3);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Z) >> 4, 15, 1);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], X) >> 4, 11, 4);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Y) >> 4,  7, 4);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Z) >> 4,  3, 4);\n"\
"\n"\
"        ETC_WriteBits(local_block, (params_th.table >> 2) & 1, 2, 1);\n"\
"        ETC_WriteBits(local_block, 0, 1, 1); // diff bit\n"\
"        ETC_WriteBits(local_block, (params_th.table >> 1) & 1 & 1, 0, 1); // flip bit\n"\
"\n"\
"        for (i = 0; i < 16; i++)\n"\
"        {\n"\
"            int index = (i % 4) * 4 + i / 4;\n"\
"\n"\
"            int idx = params_th.indexes[i];\n"\
"\n"\
"            if (transparency[i])\n"\
"                idx = 2;\n"\
"\n"\
"            ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);\n"\
"            ETC_WriteBits(local_block, idx & 1, 32 + index, 1);\n"\
"\n"\
"        }\n"\
"        ETC_PackBlockSwapOrder(block, local_block);\n"\
"    }\n"\
"}\n"\
"void ETC_EncodeRGBA1WeightedQuality(\n"\
"    int quality,\n"\
"    int allowed_modes,\n"\
"    float error_target,\n"\
"    int refine_search,\n"\
"    int is_ypbpr,\n"\
"    float alpha_cutoff,\n"\
"    float4 *pixel,\n"\
"    float *weight,\n"\
"    __global uchar *block)\n"\
"{\n"\
"    int i, j, table, n;\n"\
"    float3 trans_pixel[16];\n"\
"    int is_delta;\n"\
"    int is_flipped;\n"\
"    float best_dist[2];\n"\
"    etc_sample_t sample_list[SAMPLE_LIST_SIZE0][SAMPLE_LIST_SIZE1][SAMPLE_LIST_SIZE2];\n"\
"    int flipped;\n"\
"    int partition;\n"\
"    int is_best_delta = 0;\n"\
"    float best_total_error = MAX_INIT_ERROR;\n"\
"    int enc_mode;\n"\
"    etc_partition_mode_params_t params_partition;\n"\
"    etc_th_mode_params_t params_th;\n"\
"    uchar local_block[8];\n"\
"    int transparency[16];\n"\
"    int transparent_count = 0;\n"\
"    etc_pathing_params_t pathing_params;\n"\
"    int real_transparent_count = 0;\n"\
"    float3 projected_mins[2][2]; // delta/non-delta, flipped, partition\n"\
"    float3 projected_maxs[2][2];\n"\
"\n"\
"    for (i = 0; i < 16; i++)\n"\
"    {\n"\
"        MEMBER(trans_pixel[i], X) = MEMBER(pixel[i], X);\n"\
"        MEMBER(trans_pixel[i], Y) = MEMBER(pixel[i], Y);\n"\
"        MEMBER(trans_pixel[i], Z) = MEMBER(pixel[i], Z);\n"\
"    }\n"\
"    for (i = 0; i < 16; i++)\n"\
"    {\n"\
"        transparency[i] = (MEMBER(pixel[i], W) <= alpha_cutoff) ? (int)weight[i] : 0;\n"\
"        transparent_count += transparency[i];\n"\
"        real_transparent_count += ((MEMBER(pixel[i], W) <= alpha_cutoff) && (weight[i] != 0.0f)) ? 1 : 0;\n"\
"    }\n"\
"\n"\
"    if (transparent_count == 16)\n"\
"    {\n"\
"        ETC_WriteBits(local_block, 0, 27, 5);\n"\
"        ETC_WriteBits(local_block, 0, 24, 3);\n"\
"        ETC_WriteBits(local_block, 0, 19, 5);\n"\
"        ETC_WriteBits(local_block, 0, 16, 3);\n"\
"        ETC_WriteBits(local_block, 0, 11, 5);\n"\
"        ETC_WriteBits(local_block, 0,  8, 3);\n"\
"        ETC_WriteBits(local_block, 0, 1, 1); // diff bit\n"\
"\n"\
"        ETC_WriteBits(local_block, 0, 5, 3); // table codeword 1\n"\
"        ETC_WriteBits(local_block, 0, 2, 3); // table codeword 2\n"\
"        ETC_WriteBits(local_block, 0, 0, 1); // flip bit\n"\
"\n"\
"        for (i = 0; i < 16; i++)\n"\
"        {\n"\
"            int index = (i%4)*4 + i/4;\n"\
"            int idx = 2;\n"\
"\n"\
"            ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);\n"\
"            ETC_WriteBits(local_block, idx & 1, 32 + index, 1);\n"\
"        }\n"\
"        ETC_PackBlockSwapOrder(block, local_block);\n"\
"        return;\n"\
"    }\n"\
"\n"\
"    for (flipped = 0; flipped < 2; flipped++)\n"\
"    {\n"\
"        for (partition = 0; partition < 2; partition++)\n"\
"        {\n"\
"            float3 mean = VFLOAT3(0.0f, 0.0f, 0.0f);\n"\
"            float mins_maxs_dist[2];\n"\
"            float3 temp;\n"\
"            int pixel_count = 0;\n"\
"\n"\
"            mins_maxs_dist[0] = MAX_INIT_ERROR;\n"\
"            mins_maxs_dist[1] = -MAX_INIT_ERROR;\n"\
"\n"\
"            for (i = 0; i < 8; i++)\n"\
"            {\n"\
"                if (transparency[g_partition_indexes[flipped][partition][i]])\n"\
"                    continue;\n"\
"                mean = mean + trans_pixel[g_partition_indexes[flipped][partition][i]];\n"\
"                pixel_count++;\n"\
"            }\n"\
"\n"\
"            pixel_count = pixel_count ? pixel_count : 1;\n"\
"\n"\
"            mean = mean / (float)(pixel_count);\n"\
"\n"\
"            for (i = 0; i < 8; i++)\n"\
"            {\n"\
"                float dist;\n"\
"\n"\
"                if (transparency[g_partition_indexes[flipped][partition][i]])\n"\
"                    continue;\n"\
"\n"\
"                dist = dot(trans_pixel[g_partition_indexes[flipped][partition][i]] - mean, VFLOAT3(0.57735f, 0.57735f, 0.57735f));\n"\
"\n"\
"                if (dist < mins_maxs_dist[0])\n"\
"                    mins_maxs_dist[0] = dist;\n"\
"                if (dist > mins_maxs_dist[1])\n"\
"                    mins_maxs_dist[1] = dist;\n"\
"            }\n"\
"            projected_mins[flipped][partition] = mean + VFLOAT3(0.57735f, 0.57735f, 0.57735f) * mins_maxs_dist[0];\n"\
"            projected_maxs[flipped][partition] = mean + VFLOAT3(0.57735f, 0.57735f, 0.57735f) * mins_maxs_dist[1];\n"\
"        }\n"\
"    }\n"\
"\n"\
"    if (is_ypbpr)\n"\
"        for (i = 0; i < 16; i++)\n"\
"            trans_pixel[i] = ETC_ConvertToYPBPRf3(trans_pixel[i]);\n"\
"\n"\
"    if (allowed_modes & ETC_MODE_DELTA)\n"\
"    {\n"\
"        float3 mean[2][2];\n"\
"        uchar3 mean_quant[2][2];\n"\
"        int min_index[2][2];\n"\
"        int max_index[2][2];\n"\
"        float fixed_err = MAX_INIT_ERROR;\n"\
"        uchar3 best_positions[2];\n"\
"        int best_flipped = 0;\n"\
"        int found_fixed = 0;\n"\
"        uchar3 proj_mins;\n"\
"        uchar3 proj_maxs;\n"\
"#if 1\n"\
"        if (quality >= CODEC_QUALITY_NORMAL) // redundant, quality is always normal or better in this function\n"\
"        {\n"\
"            int max_distance;\n"\
"\n"\
"            if (quality == CODEC_QUALITY_BEST)\n"\
"                max_distance = 255;\n"\
"            else if (quality == CODEC_QUALITY_HIGH)\n"\
"                max_distance = 8;\n"\
"            else \n"\
"                max_distance = 1;\n"\
"\n"\
"            for (flipped = 0; flipped < 2; flipped++)\n"\
"            {\n"\
"                for (partition = 0; partition < 2; partition++)\n"\
"                {\n"\
"                    int distance = 0;\n"\
"                    mean[flipped][partition] = VFLOAT3(0.0f, 0.0f, 0.0f);\n"\
"                    for (i = 0; i < 8; i++) // TODO: this should be weighted\n"\
"                    {\n"\
"                        mean[flipped][partition] = mean[flipped][partition] + trans_pixel[g_partition_indexes[flipped][partition][i]];\n"\
"                    }\n"\
"                    mean[flipped][partition] = mean[flipped][partition] / 8.0f;\n"\
"\n"\
"                    MEMBER(mean_quant[flipped][partition], X) = UCHAR(MEMBER(mean[flipped][partition], X)) >> 3;\n"\
"                    MEMBER(mean_quant[flipped][partition], Y) = UCHAR(MEMBER(mean[flipped][partition], Y)) >> 3;\n"\
"                    MEMBER(mean_quant[flipped][partition], Z) = UCHAR(MEMBER(mean[flipped][partition], Z)) >> 3;\n"\
"\n"\
"                    min_index[flipped][partition] = 0;\n"\
"                    max_index[flipped][partition] = 0;\n"\
"\n"\
"                    while ( ((int)MEMBER(mean_quant[flipped][partition], X) + min_index[flipped][partition] > 0) &&\n"\
"                        ((int)MEMBER(mean_quant[flipped][partition], Y) + min_index[flipped][partition] > 0) &&\n"\
"                        ((int)MEMBER(mean_quant[flipped][partition], Z) + min_index[flipped][partition] > 0))\n"\
"                    {\n"\
"                        min_index[flipped][partition]--;\n"\
"                        distance++;\n"\
"                        if (distance > max_distance)\n"\
"                            break;\n"\
"                    }\n"\
"                    distance = 0;\n"\
"                    while ( ((int)MEMBER(mean_quant[flipped][partition], X) + max_index[flipped][partition] < 31) &&\n"\
"                        ((int)MEMBER(mean_quant[flipped][partition], Y) + max_index[flipped][partition] < 31) &&\n"\
"                        ((int)MEMBER(mean_quant[flipped][partition], Z) + max_index[flipped][partition] < 31))\n"\
"                    {\n"\
"                        max_index[flipped][partition]++;\n"\
"                        distance++;\n"\
"                        if (distance > max_distance)\n"\
"                            break;\n"\
"                    }\n"\
"                }\n"\
"            }\n"\
"            for (flipped = 0; flipped < 2; flipped++)\n"\
"            {\n"\
"                int ip0;\n"\
"                int ip1;\n"\
"                for (ip0 = min_index[flipped][0]; ip0 <= max_index[flipped][0]; ip0++)\n"\
"                {\n"\
"                    uchar3 l0_quant;\n"\
"\n"\
"                    MEMBER(l0_quant, X) = MEMBER(mean_quant[flipped][0], X) + ip0;\n"\
"                    MEMBER(l0_quant, Y) = MEMBER(mean_quant[flipped][0], Y) + ip0;\n"\
"                    MEMBER(l0_quant, Z) = MEMBER(mean_quant[flipped][0], Z) + ip0;\n"\
"\n"\
"                    for (ip1 = min_index[flipped][1]; ip1 <= max_index[flipped][1]; ip1++)\n"\
"                    {\n"\
"                        uchar3 l1_quant;\n"\
"                        int dist[3];\n"\
"                        float local_error;\n"\
"\n"\
"                        MEMBER(l1_quant, X) = MEMBER(mean_quant[flipped][1], X) + ip1;\n"\
"                        MEMBER(l1_quant, Y) = MEMBER(mean_quant[flipped][1], Y) + ip1;\n"\
"                        MEMBER(l1_quant, Z) = MEMBER(mean_quant[flipped][1], Z) + ip1;\n"\
"\n"\
"                        dist[0] = (int)MEMBER(l1_quant, X) - (int)MEMBER(l0_quant, X);\n"\
"                        dist[1] = (int)MEMBER(l1_quant, Y) - (int)MEMBER(l0_quant, Y);\n"\
"                        dist[2] = (int)MEMBER(l1_quant, Z) - (int)MEMBER(l0_quant, Z);\n"\
"\n"\
"                        if ((dist[0] < -4 || dist[0] > 3) || \n"\
"                            (dist[1] < -4 || dist[1] > 3) || \n"\
"                            (dist[2] < -4 || dist[2] > 3))\n"\
"                            continue;\n"\
"\n"\
"                        local_error = ETC_EvaluateErrorA1(transparency, is_ypbpr, trans_pixel, ETC_RGBExpandVecTo5Bit(l0_quant), &g_partition_indexes[flipped][0][0]);\n"\
"                        local_error += ETC_EvaluateErrorA1(transparency, is_ypbpr, trans_pixel, ETC_RGBExpandVecTo5Bit(l1_quant), &g_partition_indexes[flipped][1][0]);\n"\
"\n"\
"                        if (local_error < fixed_err)\n"\
"                        {\n"\
"                            fixed_err = local_error;\n"\
"                            best_positions[0] = l0_quant;\n"\
"                            best_positions[1] = l1_quant;\n"\
"                            best_flipped = flipped;\n"\
"\n"\
"                            found_fixed = 1;\n"\
"                        }\n"\
"                    }\n"\
"                }\n"\
"            }\n"\
"            if (found_fixed)\n"\
"            {\n"\
"                uchar3 best_pos[2];\n"\
"                float combined_err = 0.0f;\n"\
"\n"\
"                best_pos[0] = best_positions[0];\n"\
"                best_pos[1] = best_positions[1];\n"\
"\n"\
"                for (partition = 0; partition < 2; partition++)\n"\
"                {\n"\
"                    int neighbourhood_width = (quality == CODEC_QUALITY_BEST ? 3 : 1);\n"\
"                    float best_err = MAX_INIT_ERROR;\n"\
"                    int x;\n"\
"                    int y;\n"\
"                    int z;\n"\
"                    int min_x = MEMBER(best_positions[partition], X) > (neighbourhood_width - 1) ? MEMBER(best_positions[partition], X) - neighbourhood_width : 0;\n"\
"                    int min_y = MEMBER(best_positions[partition], Y) > (neighbourhood_width - 1) ? MEMBER(best_positions[partition], Y) - neighbourhood_width : 0;\n"\
"                    int min_z = MEMBER(best_positions[partition], Z) > (neighbourhood_width - 1) ? MEMBER(best_positions[partition], Z) - neighbourhood_width : 0;\n"\
"                    int max_x = MEMBER(best_positions[partition], X) < (31 - neighbourhood_width) ? MEMBER(best_positions[partition], X) + neighbourhood_width : 31;\n"\
"                    int max_y = MEMBER(best_positions[partition], Y) < (31 - neighbourhood_width) ? MEMBER(best_positions[partition], Y) + neighbourhood_width : 31;\n"\
"                    int max_z = MEMBER(best_positions[partition], Z) < (31 - neighbourhood_width) ? MEMBER(best_positions[partition], Z) + neighbourhood_width : 31;\n"\
"\n"\
"                    for (z = min_z; z <= max_z; z++)\n"\
"                        for (y = min_y; y <= max_y; y++)\n"\
"                            for (x = min_x; x <= max_x; x++)\n"\
"                            {\n"\
"                                uchar3 pos = UCHAR3(x, y, z);\n"\
"                                float err;\n"\
"                                int dist[3];\n"\
"\n"\
"                                dist[0] = (int)MEMBER(pos, X) - (int)MEMBER(best_pos[partition ? 0 : 1], X);\n"\
"                                dist[1] = (int)MEMBER(pos, Y) - (int)MEMBER(best_pos[partition ? 0 : 1], Y);\n"\
"                                dist[2] = (int)MEMBER(pos, Z) - (int)MEMBER(best_pos[partition ? 0 : 1], Z);\n"\
"\n"\
"                                if ((dist[0] < -4 || dist[0] > 3) || \n"\
"                                    (dist[1] < -4 || dist[1] > 3) || \n"\
"                                    (dist[2] < -4 || dist[2] > 3))\n"\
"                                    continue;\n"\
"\n"\
"                                pos = ETC_RGBExpandVecTo5Bit(pos);\n"\
"                                err = ETC_EvaluateErrorA1(transparency, is_ypbpr, trans_pixel, pos, &g_partition_indexes[best_flipped][partition][0]);\n"\
"\n"\
"                                if (err < best_err)\n"\
"                                {\n"\
"                                    best_pos[partition] = UCHAR3(x, y, z);\n"\
"                                    best_err = err;\n"\
"                                }\n"\
"                            }\n"\
"                    combined_err += best_err;\n"\
"                }\n"\
"\n"\
"                if (combined_err < fixed_err)\n"\
"                {\n"\
"                    best_positions[0] = best_pos[0];\n"\
"                    best_positions[1] = best_pos[1];\n"\
"                    fixed_err = combined_err;\n"\
"                }\n"\
"            }\n"\
"        }\n"\
"#endif\n"\
"\n"\
"        // Delta mode\n"\
"        ETC_PrepareSampleList(SAMPLE_LIST_SIZE2, sample_list);\n"\
"\n"\
"        for (flipped = 0; flipped < 2; flipped++)\n"\
"        {\n"\
"            for (partition = 0; partition < 2; partition++)\n"\
"            {\n"\
"                etc_sample_t sample;\n"\
"                float offset = 0.0f;\n"\
"\n"\
"                if (quality == CODEC_QUALITY_NORMAL)\n"\
"                    offset = 0.0f;\n"\
"                else if (quality > CODEC_QUALITY_NORMAL) // searching entire space on BEST tends to give values that can't be represented by delta encodings\n"\
"                    offset = 24.0f;\n"\
"\n"\
"                MEMBER(proj_mins, X) = ((uint)clamp(MEMBER(projected_mins[flipped][partition], X) - offset, 0.0f, 255.0f)) >> 3;\n"\
"                MEMBER(proj_mins, Y) = ((uint)clamp(MEMBER(projected_mins[flipped][partition], Y) - offset, 0.0f, 255.0f)) >> 3;\n"\
"                MEMBER(proj_mins, Z) = ((uint)clamp(MEMBER(projected_mins[flipped][partition], Z) - offset, 0.0f, 255.0f)) >> 3;\n"\
"                MEMBER(proj_maxs, X) = ((uint)clamp(MEMBER(projected_maxs[flipped][partition], X) + offset + 3, 0.0f, 255.0f)) >> 3;\n"\
"                MEMBER(proj_maxs, Y) = ((uint)clamp(MEMBER(projected_maxs[flipped][partition], Y) + offset + 3, 0.0f, 255.0f)) >> 3;\n"\
"                MEMBER(proj_maxs, Z) = ((uint)clamp(MEMBER(projected_maxs[flipped][partition], Z) + offset + 3, 0.0f, 255.0f)) >> 3;\n"\
"\n"\
"                sample.pos_quantised = proj_mins;\n"\
"                pathing_params.partition_indexes = &g_partition_indexes[flipped][partition][0];\n"\
"                sample.error = ETC_EvaluateErrorA1(transparency, is_ypbpr, trans_pixel, ETC_RGBExpandVecTo5Bit(sample.pos_quantised), &g_partition_indexes[flipped][partition][0]);\n"\
"                ETC_LeastCostDirectedPathA1(1, SAMPLE_LIST_SIZE2, transparency, error_target, refine_search, is_ypbpr, trans_pixel, sample, &sample_list[flipped][partition][0], MEMBER(proj_maxs, X), MEMBER(proj_maxs, Y), MEMBER(proj_maxs, Z), &pathing_params, ETC_RGBEXPANDVECTO5BIT, ETC_EVALUATEDELTAERRORGENERICA1);\n"\
"            }\n"\
"        }\n"\
"\n"\
"        for (i = 0; i < 2; i++)\n"\
"            best_dist[i] = sample_list[i][0][0].error + sample_list[i][1][0].error;\n"\
"\n"\
"        if (best_dist[1] < best_dist[0])\n"\
"            is_flipped = 1;\n"\
"        else\n"\
"            is_flipped = 0;\n"\
"\n"\
"        is_delta = 0;\n"\
"\n"\
"        int diff = (int)(MEMBER(sample_list[is_flipped][1][0].pos_quantised, X)) - (int)(MEMBER(sample_list[is_flipped][0][0].pos_quantised, X));\n"\
"        if (diff < 4 && diff >= -4)\n"\
"            is_delta++;\n"\
"        diff = (int)(MEMBER(sample_list[is_flipped][1][0].pos_quantised, Y)) - (int)(MEMBER(sample_list[is_flipped][0][0].pos_quantised, Y));\n"\
"        if (diff < 4 && diff >= -4)\n"\
"            is_delta++;\n"\
"        diff = (int)(MEMBER(sample_list[is_flipped][1][0].pos_quantised, Z)) - (int)(MEMBER(sample_list[is_flipped][0][0].pos_quantised, Z));\n"\
"        if (diff < 4 && diff >= -4)\n"\
"            is_delta++;\n"\
"\n"\
"        is_best_delta = is_delta == 3 ? 1 : 0;\n"\
"\n"\
"        best_total_error = min(best_dist[0], best_dist[1]);\n"\
"\n"\
"        enc_mode = ETC_ENC_MODE_DELTA;\n"\
"        params_partition.rgb[0] = ETC_RGBExpandVecTo5Bit(sample_list[is_flipped][0][0].pos_quantised);\n"\
"        params_partition.rgb[1] = ETC_RGBExpandVecTo5Bit(sample_list[is_flipped][1][0].pos_quantised);\n"\
"        params_partition.is_flipped = is_flipped;\n"\
"\n"\
"        if (!is_best_delta)\n"\
"        {\n"\
"            int delta[2][SAMPLE_LIST_SIZE2][SAMPLE_LIST_SIZE2]; // TODO: can get rid of this if just do it inside the loop\n"\
"            float err[2][SAMPLE_LIST_SIZE2][SAMPLE_LIST_SIZE2]; // TODO: can get rid of this if just do it inside the loop\n"\
"            int best_delta[2] = {0, 0};\n"\
"            float best_delta_err = MAX_INIT_ERROR;\n"\
"            int delta_found = 0;\n"\
"            int best_flipped = 0;\n"\
"\n"\
"            for (n = 0; n < 2; n++)\n"\
"                for (i = 0; i < SAMPLE_LIST_SIZE2; i++)\n"\
"                {\n"\
"                    for (j = 0; j < SAMPLE_LIST_SIZE2; j++)\n"\
"                    {\n"\
"                        is_delta = 0;\n"\
"                        int diff = (int)(MEMBER(sample_list[n][1][j].pos_quantised, X)) - (int)(MEMBER(sample_list[n][0][i].pos_quantised, X));\n"\
"                        if (diff < 4 && diff >= -4)\n"\
"                            is_delta++;\n"\
"                        diff = (int)(MEMBER(sample_list[n][1][j].pos_quantised, Y)) - (int)(MEMBER(sample_list[n][0][i].pos_quantised, Y));\n"\
"                        if (diff < 4 && diff >= -4)\n"\
"                            is_delta++;\n"\
"                        diff = (int)(MEMBER(sample_list[n][1][j].pos_quantised, Z)) - (int)(MEMBER(sample_list[n][0][i].pos_quantised, Z));\n"\
"                        if (diff < 4 && diff >= -4)\n"\
"                            is_delta++;\n"\
"\n"\
"                        delta[n][i][j] = is_delta == 3 ? 1 : 0;\n"\
"                        err[n][i][j] = sample_list[n][1][j].error + sample_list[n][0][i].error;\n"\
"                    }\n"\
"                }\n"\
"            for (n = 0; n < 2; n++)\n"\
"                for (i = 0; i < SAMPLE_LIST_SIZE2; i++)\n"\
"                    for (j = 0; j < SAMPLE_LIST_SIZE2; j++)\n"\
"                        if (delta[n][i][j])\n"\
"                            if (err[n][i][j] < best_delta_err)\n"\
"                            {\n"\
"                                best_delta_err = err[n][i][j];\n"\
"                                best_delta[0] = i;\n"\
"                                best_delta[1] = j;\n"\
"                                delta_found = 1;\n"\
"                                best_flipped = n;\n"\
"                            }\n"\
"\n"\
"            best_total_error = best_delta_err;\n"\
"\n"\
"            if (delta_found)\n"\
"            {\n"\
"                params_partition.rgb[0] = ETC_RGBExpandVecTo5Bit(sample_list[best_flipped][0][best_delta[0]].pos_quantised);\n"\
"                params_partition.rgb[1] = ETC_RGBExpandVecTo5Bit(sample_list[best_flipped][1][best_delta[1]].pos_quantised);\n"\
"                params_partition.is_flipped = best_flipped;\n"\
"            }\n"\
"        }\n"\
"\n"\
"        if (found_fixed && fixed_err < best_total_error)\n"\
"        {\n"\
"            enc_mode = ETC_ENC_MODE_DELTA;\n"\
"            best_total_error = fixed_err;\n"\
"            params_partition.rgb[0] = ETC_RGBExpandVecTo5Bit(best_positions[0]);\n"\
"            params_partition.rgb[1] = ETC_RGBExpandVecTo5Bit(best_positions[1]);\n"\
"            params_partition.is_flipped = best_flipped;\n"\
"        }\n"\
"\n"\
"        ETC_GetOptimalIndexesA1(transparency, is_ypbpr, trans_pixel, params_partition.rgb[0], &g_partition_indexes[params_partition.is_flipped][0][0], &params_partition.table[0], params_partition.indexes);\n"\
"        ETC_GetOptimalIndexesA1(transparency, is_ypbpr, trans_pixel, params_partition.rgb[1], &g_partition_indexes[params_partition.is_flipped][1][0], &params_partition.table[1], params_partition.indexes);\n"\
"    }\n"\
"\n"\
"    if ((best_total_error > error_target) && (allowed_modes & (ETC_MODE_T | ETC_MODE_H)))\n"\
"    {\n"\
"        int set_indexes[2][16];\n"\
"        int set_count[2];\n"\
"        etc_sample_t sample;\n"\
"\n"\
"        ETC_KMeansTHModeA1(transparency, trans_pixel, &set_indexes[0][0], &set_indexes[1][0], &set_count[0]);\n"\
"\n"\
"        for (partition = 0; partition < 2; partition++) // TODO: this should be weighted\n"\
"        {\n"\
"            float3 mean = VFLOAT3(0.0f, 0.0f, 0.0f);\n"\
"            float mins_maxs_dist[2];\n"\
"            float3 temp;\n"\
"            int pixel_count = 0;\n"\
"\n"\
"            for (i = 0; i < set_count[partition]; i++)\n"\
"            {\n"\
"                if (transparency[set_indexes[partition][i]])\n"\
"                    continue;\n"\
"                mean = mean + trans_pixel[set_indexes[partition][i]];\n"\
"                pixel_count++;\n"\
"            }\n"\
"\n"\
"            pixel_count = pixel_count ? pixel_count : 1;\n"\
"\n"\
"            mean = mean / (float)(pixel_count);\n"\
"\n"\
"            if (set_count[partition] && pixel_count)\n"\
"            {\n"\
"                mins_maxs_dist[0] = MAX_INIT_ERROR;\n"\
"                mins_maxs_dist[1] = -MAX_INIT_ERROR;\n"\
"\n"\
"                for (i = 0; i < set_count[partition]; i++)\n"\
"                {\n"\
"                    float dist;\n"\
"\n"\
"                    if (transparency[set_indexes[partition][i]])\n"\
"                        continue;\n"\
"\n"\
"                    dist = dot(trans_pixel[set_indexes[partition][i]] - mean, VFLOAT3(0.57735f, 0.57735f, 0.57735f));\n"\
"\n"\
"                    if (dist < mins_maxs_dist[0])\n"\
"                        mins_maxs_dist[0] = dist;\n"\
"                    if (dist > mins_maxs_dist[1])\n"\
"                        mins_maxs_dist[1] = dist;\n"\
"                }\n"\
"                projected_mins[0][partition] = mean + VFLOAT3(0.57735f, 0.57735f, 0.57735f) * mins_maxs_dist[0];\n"\
"                projected_maxs[0][partition] = mean + VFLOAT3(0.57735f, 0.57735f, 0.57735f) * mins_maxs_dist[1];\n"\
"            }\n"\
"            else\n"\
"            {\n"\
"                projected_mins[0][partition] = mean;\n"\
"                projected_maxs[0][partition] = mean;\n"\
"            }\n"\
"        }\n"\
"\n"\
"        if (allowed_modes & ETC_MODE_T)\n"\
"        {\n"\
"            // T mode\n"\
"            ETC_PrepareSampleList(1, sample_list);\n"\
"            for (flipped = 0; flipped < 2; flipped++)\n"\
"            {\n"\
"                etc_sample_t sample;\n"\
"                uchar3 proj_mins;\n"\
"                uchar3 proj_maxs;\n"\
"                float offset = 0.0f;\n"\
"\n"\
"                if (quality == CODEC_QUALITY_NORMAL)\n"\
"                    offset = 0.0f;\n"\
"                else if (quality == CODEC_QUALITY_HIGH)\n"\
"                    offset = 48.0f;\n"\
"                else \n"\
"                    offset = 96.0f;\n"\
"\n"\
"                if ((quality == CODEC_QUALITY_NORMAL) || (quality == CODEC_QUALITY_HIGH))\n"\
"                {\n"\
"                    MEMBER(proj_mins, X) = ((uint)clamp(MEMBER(projected_mins[0][flipped], X) - offset, 0.0f, 255.0f)) >> 4;\n"\
"                    MEMBER(proj_mins, Y) = ((uint)clamp(MEMBER(projected_mins[0][flipped], Y) - offset, 0.0f, 255.0f)) >> 4;\n"\
"                    MEMBER(proj_mins, Z) = ((uint)clamp(MEMBER(projected_mins[0][flipped], Z) - offset, 0.0f, 255.0f)) >> 4;\n"\
"                    MEMBER(proj_maxs, X) = ((uint)clamp(MEMBER(projected_maxs[0][flipped], X) + offset + 7, 0.0f, 255.0f)) >> 4;\n"\
"                    MEMBER(proj_maxs, Y) = ((uint)clamp(MEMBER(projected_maxs[0][flipped], Y) + offset + 7, 0.0f, 255.0f)) >> 4;\n"\
"                    MEMBER(proj_maxs, Z) = ((uint)clamp(MEMBER(projected_maxs[0][flipped], Z) + offset + 7, 0.0f, 255.0f)) >> 4;\n"\
"                }\n"\
"                else\n"\
"                {\n"\
"                    proj_mins = UCHAR3(0, 0, 0);\n"\
"                    proj_maxs = UCHAR3(15, 15, 15);\n"\
"                }\n"\
"\n"\
"                sample.pos_quantised = proj_mins;\n"\
"                pathing_params.indexes = set_indexes[flipped];\n"\
"                pathing_params.num_indexes = set_count[flipped];\n"\
"                sample.error = ETC_EvaluateErrorTSingleA1(transparency, is_ypbpr, trans_pixel, ETC_RGBExpandVecTo4Bit(sample.pos_quantised), set_indexes[flipped], set_count[flipped]);\n"\
"                ETC_LeastCostDirectedPathA1(1, 1, transparency, error_target, refine_search, is_ypbpr, trans_pixel, sample, &sample_list[flipped][0][0], MEMBER(proj_maxs, X), MEMBER(proj_maxs, Y), MEMBER(proj_maxs, Z), &pathing_params, ETC_RGBEXPANDVECTO4BIT, ETC_EVALUATETSINGLEERRORGENERICA1);\n"\
"\n"\
"                if ((quality == CODEC_QUALITY_NORMAL) || (quality == CODEC_QUALITY_HIGH))\n"\
"                {\n"\
"                    MEMBER(proj_mins, X) = ((uint)clamp(MEMBER(projected_mins[0][(flipped + 1) % 2], X) - offset, 0.0f, 255.0f)) >> 4;\n"\
"                    MEMBER(proj_mins, Y) = ((uint)clamp(MEMBER(projected_mins[0][(flipped + 1) % 2], Y) - offset, 0.0f, 255.0f)) >> 4;\n"\
"                    MEMBER(proj_mins, Z) = ((uint)clamp(MEMBER(projected_mins[0][(flipped + 1) % 2], Z) - offset, 0.0f, 255.0f)) >> 4;\n"\
"                    MEMBER(proj_maxs, X) = ((uint)clamp(MEMBER(projected_maxs[0][(flipped + 1) % 2], X) + offset + 7, 0.0f, 255.0f)) >> 4;\n"\
"                    MEMBER(proj_maxs, Y) = ((uint)clamp(MEMBER(projected_maxs[0][(flipped + 1) % 2], Y) + offset + 7, 0.0f, 255.0f)) >> 4;\n"\
"                    MEMBER(proj_maxs, Z) = ((uint)clamp(MEMBER(projected_maxs[0][(flipped + 1) % 2], Z) + offset + 7, 0.0f, 255.0f)) >> 4;\n"\
"                }\n"\
"                else\n"\
"                {\n"\
"                    proj_mins = UCHAR3(0, 0, 0);\n"\
"                    proj_maxs = UCHAR3(15, 15, 15);\n"\
"                }\n"\
"                sample.pos_quantised = proj_mins;\n"\
"                pathing_params.indexes = set_indexes[(flipped + 1) % 2];\n"\
"                pathing_params.num_indexes = set_count[(flipped + 1) % 2];\n"\
"                sample.error = ETC_EvaluateErrorTTripleA1(transparency, is_ypbpr, trans_pixel, ETC_RGBExpandVecTo4Bit(sample.pos_quantised), set_indexes[(flipped + 1) % 2], set_count[(flipped + 1) % 2]);\n"\
"                ETC_LeastCostDirectedPathA1(1, 1, transparency, error_target, refine_search, is_ypbpr, trans_pixel, sample, &sample_list[flipped][1][0], MEMBER(proj_maxs, X), MEMBER(proj_maxs, Y), MEMBER(proj_maxs, Z), &pathing_params, ETC_RGBEXPANDVECTO4BIT, ETC_EVALUATETTRIPLEERRORGENERICA1);\n"\
"            }\n"\
"            for (i = 0; i < 2; i++)\n"\
"                best_dist[i] = sample_list[i][0][0].error + sample_list[i][1][0].error;\n"\
"\n"\
"            if ((best_dist[0] < best_total_error) || (best_dist[1] < best_total_error))\n"\
"            {\n"\
"                enc_mode = ETC_ENC_MODE_T;\n"\
"\n"\
"                if (best_dist[1] < best_dist[0])\n"\
"                    is_flipped = 1;\n"\
"                else\n"\
"                    is_flipped = 0;\n"\
"\n"\
"                params_th.rgb[0] = ETC_RGBExpandVecTo4Bit(sample_list[is_flipped][0][0].pos_quantised);\n"\
"                params_th.rgb[1] = ETC_RGBExpandVecTo4Bit(sample_list[is_flipped][1][0].pos_quantised);\n"\
"\n"\
"                float d = ETC_GetOptimalTIndexesA1(transparency, is_ypbpr, trans_pixel, params_th.rgb[0], params_th.rgb[1], &params_th.indexes[0], &params_th.table);\n"\
"\n"\
"                best_total_error = d;\n"\
"            }\n"\
"        }\n"\
"\n"\
"        if ((best_total_error > error_target) && (allowed_modes & ETC_MODE_H))\n"\
"        {\n"\
"            int best_mode;\n"\
"\n"\
"            // H-Mode\n"\
"            ETC_PrepareSampleList(1, sample_list);\n"\
"            for (flipped = 0; flipped < 2; flipped++)\n"\
"            {\n"\
"                uchar3 proj_mins;\n"\
"                uchar3 proj_maxs;\n"\
"                float offset = 0.0f;\n"\
"\n"\
"                if (quality == CODEC_QUALITY_NORMAL)\n"\
"                    offset = 0.0f;\n"\
"                else if (quality == CODEC_QUALITY_HIGH)\n"\
"                    offset = 48.0f;\n"\
"                else \n"\
"                    offset = 96.0f;\n"\
"\n"\
"                if ((quality == CODEC_QUALITY_NORMAL) || (quality == CODEC_QUALITY_HIGH))\n"\
"                {\n"\
"                    MEMBER(proj_mins, X) = ((uint)clamp(MEMBER(projected_mins[0][flipped], X) - offset, 0.0f, 255.0f)) >> 4;\n"\
"                    MEMBER(proj_mins, Y) = ((uint)clamp(MEMBER(projected_mins[0][flipped], Y) - offset, 0.0f, 255.0f)) >> 4;\n"\
"                    MEMBER(proj_mins, Z) = ((uint)clamp(MEMBER(projected_mins[0][flipped], Z) - offset, 0.0f, 255.0f)) >> 4;\n"\
"                    MEMBER(proj_maxs, X) = ((uint)clamp(MEMBER(projected_maxs[0][flipped], X) + offset + 7, 0.0f, 255.0f)) >> 4;\n"\
"                    MEMBER(proj_maxs, Y) = ((uint)clamp(MEMBER(projected_maxs[0][flipped], Y) + offset + 7, 0.0f, 255.0f)) >> 4;\n"\
"                    MEMBER(proj_maxs, Z) = ((uint)clamp(MEMBER(projected_maxs[0][flipped], Z) + offset + 7, 0.0f, 255.0f)) >> 4;\n"\
"                }\n"\
"                else\n"\
"                {\n"\
"                    proj_mins = UCHAR3(0, 0, 0);\n"\
"                    proj_maxs = UCHAR3(15, 15, 15);\n"\
"                }\n"\
"                for (table = 0; table < 8; table++)\n"\
"                {\n"\
"                    sample.pos_quantised = proj_mins;\n"\
"                    pathing_params.indexes = set_indexes[flipped];\n"\
"                    pathing_params.num_indexes = set_count[flipped];\n"\
"                    pathing_params.mode = table;\n"\
"                    pathing_params.h_index = flipped;\n"\
"                    sample.error = ETC_EvaluateErrorHA1(transparency, is_ypbpr, trans_pixel, ETC_RGBExpandVecTo4Bit(sample.pos_quantised), set_indexes[flipped], set_count[flipped], table, flipped);\n"\
"                    ETC_LeastCostDirectedPathA1(1, 1, transparency, error_target, refine_search, is_ypbpr, trans_pixel, sample, &sample_list[flipped][table][0], MEMBER(proj_maxs, X), MEMBER(proj_maxs, Y), MEMBER(proj_maxs, Z), &pathing_params, ETC_RGBEXPANDVECTO4BIT, ETC_EVALUATEHERRORGENERICA1);\n"\
"                }\n"\
"            }\n"\
"\n"\
"            best_dist[0] = sample_list[0][0][0].error + sample_list[1][0][0].error;\n"\
"            best_mode = 0;\n"\
"\n"\
"            for (flipped = 0; flipped < 2; flipped++)\n"\
"                for (table = 0; table < 8; table++)\n"\
"                    if (sample_list[0][table][0].error + sample_list[1][table][0].error < best_dist[0])\n"\
"                    {\n"\
"                        best_dist[0] = sample_list[0][table][0].error + sample_list[1][table][0].error;\n"\
"                        best_mode = table;\n"\
"                    }\n"\
"\n"\
"            if (best_dist[0] < best_total_error)\n"\
"            {\n"\
"                ushort rgbpacked[2];\n"\
"\n"\
"                enc_mode = ETC_ENC_MODE_H;\n"\
"\n"\
"                params_th.table = best_mode;\n"\
"\n"\
"                if ((MEMBER(sample_list[0][params_th.table][0].pos_quantised, X) == MEMBER(sample_list[1][params_th.table][0].pos_quantised, X)) &&\n"\
"                    (MEMBER(sample_list[0][params_th.table][0].pos_quantised, Y) == MEMBER(sample_list[1][params_th.table][0].pos_quantised, Y)) &&\n"\
"                    (MEMBER(sample_list[0][params_th.table][0].pos_quantised, Z) == MEMBER(sample_list[1][params_th.table][0].pos_quantised, Z)))\n"\
"                    MEMBER(sample_list[0][params_th.table][0].pos_quantised, X) = (MEMBER(sample_list[0][params_th.table][0].pos_quantised, X) + 1) % 16;\n"\
"\n"\
"                params_th.rgb[0] = ETC_RGBExpandVecTo4Bit(sample_list[0][params_th.table][0].pos_quantised);\n"\
"                params_th.rgb[1] = ETC_RGBExpandVecTo4Bit(sample_list[1][params_th.table][0].pos_quantised);\n"\
"\n"\
"                rgbpacked[0] =  (((ushort)MEMBER(sample_list[0][params_th.table][0].pos_quantised, X)) << 8) |\n"\
"                    (((ushort)MEMBER(sample_list[0][params_th.table][0].pos_quantised, Y)) << 4) |\n"\
"                    (((ushort)MEMBER(sample_list[0][params_th.table][0].pos_quantised, Z)) << 0);\n"\
"\n"\
"                rgbpacked[1] =  (((ushort)MEMBER(sample_list[1][params_th.table][0].pos_quantised, X)) << 8) |\n"\
"                    (((ushort)MEMBER(sample_list[1][params_th.table][0].pos_quantised, Y)) << 4) |\n"\
"                    (((ushort)MEMBER(sample_list[1][params_th.table][0].pos_quantised, Z)) << 0);\n"\
"\n"\
"                if (!(params_th.table & 1))\n"\
"                {\n"\
"                    if (rgbpacked[0] > rgbpacked[1])\n"\
"                    {\n"\
"                        params_th.rgb[0] = ETC_RGBExpandVecTo4Bit(sample_list[1][params_th.table][0].pos_quantised);\n"\
"                        params_th.rgb[1] = ETC_RGBExpandVecTo4Bit(sample_list[0][params_th.table][0].pos_quantised);\n"\
"                    }\n"\
"                }\n"\
"                else\n"\
"                {\n"\
"                    if (rgbpacked[0] < rgbpacked[1])\n"\
"                    {\n"\
"                        params_th.rgb[0] = ETC_RGBExpandVecTo4Bit(sample_list[1][params_th.table][0].pos_quantised);\n"\
"                        params_th.rgb[1] = ETC_RGBExpandVecTo4Bit(sample_list[0][params_th.table][0].pos_quantised);\n"\
"                    }\n"\
"                }\n"\
"\n"\
"                best_total_error = ETC_GetOptimalHIndexesA1(transparency, is_ypbpr, trans_pixel, params_th.rgb[0], params_th.rgb[1], params_th.indexes, params_th.table);\n"\
"            }\n"\
"        }\n"\
"    }\n"\
"\n"\
"    if (enc_mode == ETC_ENC_MODE_DELTA)\n"\
"    {\n"\
"        int3 diff;\n"\
"\n"\
"        MEMBER(diff, X) = (MEMBER(params_partition.rgb[1], X) >> 3) - (MEMBER(params_partition.rgb[0], X) >> 3);\n"\
"        MEMBER(diff, Y) = (MEMBER(params_partition.rgb[1], Y) >> 3) - (MEMBER(params_partition.rgb[0], Y) >> 3);\n"\
"        MEMBER(diff, Z) = (MEMBER(params_partition.rgb[1], Z) >> 3) - (MEMBER(params_partition.rgb[0], Z) >> 3);\n"\
"\n"\
"        ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], X) >> 3, 27, 5);\n"\
"        ETC_WriteBits(local_block, MEMBER(diff, X) >> 0, 24, 3);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], Y) >> 3, 19, 5);\n"\
"        ETC_WriteBits(local_block, MEMBER(diff, Y) >> 0, 16, 3);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], Z) >> 3, 11, 5);\n"\
"        ETC_WriteBits(local_block, MEMBER(diff, Z) >> 0,  8, 3);\n"\
"        ETC_WriteBits(local_block, 0, 1, 1); // diff bit\n"\
"\n"\
"        ETC_WriteBits(local_block, params_partition.table[0], 5, 3); // table codeword 1\n"\
"        ETC_WriteBits(local_block, params_partition.table[1], 2, 3); // table codeword 2\n"\
"        ETC_WriteBits(local_block, params_partition.is_flipped, 0, 1); // flip bit\n"\
"\n"\
"        for (i = 0; i < 16; i++)\n"\
"        {\n"\
"            int index = (i%4)*4 + i/4;\n"\
"\n"\
"            int idx = params_partition.indexes[i];\n"\
"\n"\
"            if (transparency[i])\n"\
"                idx = 2;\n"\
"\n"\
"            ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);\n"\
"            ETC_WriteBits(local_block, idx & 1, 32 + index, 1);\n"\
"        }\n"\
"        ETC_PackBlockSwapOrder(block, local_block);\n"\
"    }\n"\
"    else if (enc_mode == ETC_ENC_MODE_T)\n"\
"    {\n"\
"        int min_rd = -4 + ((MEMBER(params_th.rgb[0], X) >> 4) & 3);\n"\
"        int max_rd = ((MEMBER(params_th.rgb[0], X) >> 4) & 3);\n"\
"        int min_r = (MEMBER(params_th.rgb[0], X) >> 6) & 3;\n"\
"        int max_r = 28 + min_r;\n"\
"        uchar r;\n"\
"        uchar rd;\n"\
"\n"\
"        if (min_rd + min_r < 0)\n"\
"        {\n"\
"            r = min_r;\n"\
"            rd = min_rd;\n"\
"        }\n"\
"        else\n"\
"        {\n"\
"            r = max_r;\n"\
"            rd = max_rd;\n"\
"        }\n"\
"\n"\
"        ETC_WriteBits(local_block, r, 27, 5);\n"\
"        ETC_WriteBits(local_block, rd, 24, 3);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Y) >> 4, 20, 4);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Z) >> 4, 16, 4);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], X) >> 4, 12, 4);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Y) >> 4,  8, 4);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Z) >> 4,  4, 4);\n"\
"\n"\
"        ETC_WriteBits(local_block, (params_th.table >> 1) & 3, 2, 2);\n"\
"        ETC_WriteBits(local_block, 0, 1, 1); // diff bit\n"\
"        ETC_WriteBits(local_block, params_th.table & 1, 0, 1); // flip bit\n"\
"\n"\
"        for (i = 0; i < 16; i++)\n"\
"        {\n"\
"            int index = (i % 4) * 4 + i / 4;\n"\
"\n"\
"            int idx = params_th.indexes[i];\n"\
"\n"\
"            if (transparency[i])\n"\
"                idx = 2;\n"\
"\n"\
"            ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);\n"\
"            ETC_WriteBits(local_block, idx & 1, 32 + index, 1);\n"\
"\n"\
"        }\n"\
"        ETC_PackBlockSwapOrder(block, local_block);\n"\
"    }\n"\
"    else if (enc_mode == ETC_ENC_MODE_H)\n"\
"    {\n"\
"        int min_gd = -4 + ((MEMBER(params_th.rgb[0], Z) >> 5) & 3);\n"\
"        int max_gd = ((MEMBER(params_th.rgb[0], Z) >> 5) & 3);\n"\
"        int min_g = ((MEMBER(params_th.rgb[0], Z) >> 7) & 1) | (((MEMBER(params_th.rgb[0], Y) >> 4) & 1) << 1);\n"\
"        int max_g = 28 + min_g;\n"\
"        uchar g;\n"\
"        uchar gd;\n"\
"        int rd;\n"\
"\n"\
"        if (min_gd + min_g < 0)\n"\
"        {\n"\
"            g = min_g;\n"\
"            gd = min_gd;\n"\
"        }\n"\
"        else\n"\
"        {\n"\
"            g = max_g;\n"\
"            gd = max_gd;\n"\
"        }\n"\
"\n"\
"        rd = MEMBER(params_th.rgb[0], Y) >> 5;\n"\
"        if (rd >= 4)\n"\
"            rd = -4 + (rd & 3);\n"\
"\n"\
"        if ((int)(MEMBER(params_th.rgb[0], X) >> 4) + rd < 0)\n"\
"            ETC_WriteBits(local_block, 1, 31, 1);\n"\
"        else\n"\
"            ETC_WriteBits(local_block, 0, 31, 1);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], X) >> 4, 27, 4);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Y) >> 5, 24, 3);\n"\
"        ETC_WriteBits(local_block, g, 19, 5);\n"\
"        ETC_WriteBits(local_block, gd, 16, 3);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Z) >> 4, 15, 1);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], X) >> 4, 11, 4);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Y) >> 4,  7, 4);\n"\
"        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Z) >> 4,  3, 4);\n"\
"\n"\
"        ETC_WriteBits(local_block, (params_th.table >> 2) & 1, 2, 1);\n"\
"        ETC_WriteBits(local_block, 0, 1, 1); // diff bit\n"\
"        ETC_WriteBits(local_block, (params_th.table >> 1) & 1 & 1, 0, 1); // flip bit\n"\
"\n"\
"        for (i = 0; i < 16; i++)\n"\
"        {\n"\
"            int index = (i % 4) * 4 + i / 4;\n"\
"\n"\
"            int idx = params_th.indexes[i];\n"\
"\n"\
"            if (transparency[i])\n"\
"                idx = 2;\n"\
"\n"\
"            ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);\n"\
"            ETC_WriteBits(local_block, idx & 1, 32 + index, 1);\n"\
"\n"\
"        }\n"\
"        ETC_PackBlockSwapOrder(block, local_block);\n"\
"    }\n"\
"}\n"\
"\n"\
"\n"\
"void ETC_EncodeRGBA1Weighted(\n"\
"    int quality,\n"\
"    int allowed_modes,\n"\
"    float error_target,\n"\
"    int refine_search,\n"\
"    int is_ypbpr,\n"\
"    float alpha_cutoff,\n"\
"    float4 *pixel,\n"\
"    float *weight,\n"\
"    __global uchar *block)\n"\
"{\n"\
"\n"\
"    if (quality == CODEC_QUALITY_FAST)\n"\
"        ETC_EncodeRGBA1WeightedFast(allowed_modes, is_ypbpr, alpha_cutoff, pixel, weight, block);\n"\
"    else\n"\
"        ETC_EncodeRGBA1WeightedQuality(quality, allowed_modes, error_target, refine_search, is_ypbpr, alpha_cutoff, pixel, weight, block);\n"\
"}\n"\
"\n"\
"void ETC_EncodeETC4x4(\n"\
"    int allowed_modes,                              // bitfield of allowed modes for encoder, mostly for debugging. see MODE preprocessor definitions. suggested default: ETC_MODE_ANY. should never be set to \"ETC_MODE_DELTA\" only.\n"\
"    float alpha_cutoff,                             // valid range 0 - 255, used in RGBA1 mode. (x <= cutoff) = transparent pixel.\n"\
"    float rgb_error_target,                 // MSE error target for colour channels. 0 for max quality, 256 for approximately PVRTexTool \"slow\" quality. high performance impact for lower values. suggested default: 0\n"\
"    float alpha_error_target,               // MSE error target for alpha in RGBA8 mode. 0 for max quality. moderate performance impact. suggested default: 0\n"\
"    int is_ypbpr,                                   // measure MSE in YPbPr space instead of RGB space? moderate performance impact if enabled\n"\
"    int is_etc2,                                    // is ETC1 or ETC2?\n"\
"    int is_alpha,                                   // has an alpha channel?\n"\
"    int is_punchthrough,                    // is alpha channel 1-bit?\n"\
"    int refine_rgb_search,                  // search for best minimum in local neighbourhood to improve quality for RGB. high performance impact. suggested default: 0\n"\
"    int refine_alpha_search,                // search for better \"base alpha\" instead of using simple estimate. moderate performance impact. suggested default: 1\n"\
"    int alpha_search_radius,                // valid range 0 - 7. search radius for better alpha multiplier. moderate performance impact. suggested default: 1\n"\
"    int width,                                              // image width in pixels\n"\
"    int height,                                             // image height in pixels\n"\
"    __global float *pixel_rgba,             // pixel RGBA in R, G, B, A order, (width x height) entries\n"\
"    __global uchar *block,                  // output data\n"\
"    int quality)                          // low-quality, high-speed\n"\
"{\n"\
"    float4 pixel[16];\n"\
"    float weight[16];\n"\
"    int block_x = get_global_id(0);\n"\
"    int block_y = get_global_id(1);\n"\
"    int i;\n"\
"    int j;\n"\
"    int line_out_blocks = (width + 3) >> 2;\n"\
"\n"\
"        for (i = 0; i < 16; i++)\n"\
"            weight[i] = 1.0f;\n"\
"    for (i = 0; i < 4; i++)\n"\
"        for (j = 0; j < 4; j++)\n"\
"        {\n"\
"            MEMBER(pixel[(i*4 + j)], X) = pixel_rgba[((i + block_y*4)*width + (j + block_x*4))*4 + 0];\n"\
"            MEMBER(pixel[(i*4 + j)], Y) = pixel_rgba[((i + block_y*4)*width + (j + block_x*4))*4 + 1];\n"\
"            MEMBER(pixel[(i*4 + j)], Z) = pixel_rgba[((i + block_y*4)*width + (j + block_x*4))*4 + 2];\n"\
"            MEMBER(pixel[(i*4 + j)], W) = pixel_rgba[((i + block_y*4)*width + (j + block_x*4))*4 + 3];\n"\
"\n"\
"        }\n"\
"\n"\
"        if (is_alpha && is_etc2)\n"\
"        {\n"\
"            if (!is_punchthrough)\n"\
"            {\n"\
"                    ETC_EncodeRGB(quality, allowed_modes, rgb_error_target, refine_rgb_search, is_etc2, is_ypbpr, pixel, &block[(block_x * 8 * 2) + (block_y) * line_out_blocks * 8 * 2 + 8]);\n"\
"                    ETC_EncodeAlpha(alpha_error_target, refine_alpha_search, alpha_search_radius, pixel, &block[(block_x * 8 * 2) + (block_y) * line_out_blocks * 8 * 2 + 0]);\n"\
"            }\n"\
"            else\n"\
"            {\n"\
"                int transparent_count = 0;\n"\
"\n"\
"                for (i = 0; i < 16; i++)\n"\
"                    if (MEMBER(pixel[i], W) <= alpha_cutoff)\n"\
"                    {\n"\
"                        transparent_count++;\n"\
"                        break;\n"\
"                    }\n"\
"                if (transparent_count == 0)\n"\
"                    ETC_EncodeRGB(quality, allowed_modes, rgb_error_target, refine_rgb_search, is_etc2, is_ypbpr, pixel, &block[(block_x * 8) + (block_y) * line_out_blocks * 8 + 0]);\n"\
"                else\n"\
"                    ETC_EncodeRGBA1Weighted(quality, allowed_modes, rgb_error_target, refine_rgb_search, is_ypbpr, alpha_cutoff, pixel, weight, &block[(block_x * 8) + (block_y) * line_out_blocks * 8 + 0]);\n"\
"            }\n"\
"        }\n"\
"        else\n"\
"        {\n"\
"            ETC_EncodeRGB(quality, allowed_modes, rgb_error_target, refine_rgb_search, is_etc2, is_ypbpr, pixel, &block[(block_x * 8) + (block_y) * line_out_blocks * 8 + 0]);\n"\
"        }\n"\
"}\n"\
"\n"\
"void ETC_EncodeETCN4x4(\n"\
"    int allowed_modes,                              // bitfield of allowed modes for encoder, mostly for debugging. see MODE preprocessor definitions. suggested default: ETC_MODE_ANY. should never be set to \"ETC_MODE_DELTA\" only.\n"\
"    float alpha_cutoff,                             // valid range 0 - 255, used in RGBA1 mode. (x <= cutoff) = transparent pixel.\n"\
"    float rgb_error_target,                 // MSE error target for colour channels. 0 for max quality, 256 for approximately PVRTexTool \"slow\" quality. high performance impact for lower values. suggested default: 0\n"\
"    float alpha_error_target,               // MSE error target for alpha in RGBA8 mode. 0 for max quality. moderate performance impact. suggested default: 0\n"\
"    int is_ypbpr,                                   // measure MSE in YPbPr space instead of RGB space? moderate performance impact if enabled\n"\
"    int is_etc2,                                    // is ETC1 or ETC2?\n"\
"    int is_alpha,                                   // has an alpha channel?\n"\
"    int is_punchthrough,                    // is alpha channel 1-bit?\n"\
"    int refine_rgb_search,                  // search for best minimum in local neighbourhood to improve quality for RGB. high performance impact. suggested default: 0\n"\
"    int refine_alpha_search,                // search for better \"base alpha\" instead of using simple estimate. moderate performance impact. suggested default: 1\n"\
"    int alpha_search_radius,                // valid range 0 - 7. search radius for better alpha multiplier. moderate performance impact. suggested default: 1\n"\
"    int width,                                              // image width in pixels\n"\
"    int height,                                             // image height in pixels\n"\
"    __global float *pixel_rgba,             // pixel RGBA in R, G, B, A order, (width x height) entries\n"\
"    __global uchar *block,                      // output data\n"\
"    int quality)\n"\
"{\n"\
"    float4 pixel[16];\n"\
"    float weight[16];\n"\
"    int block_x = get_global_id(0);\n"\
"    int block_y = get_global_id(1);\n"\
"    int i;\n"\
"    int j;\n"\
"    int max_x;\n"\
"    int max_y;\n"\
"    int line_out_blocks = (width + 3) >> 2;\n"\
"\n"\
"    max_x = clamp(width - block_x*4, 1, 4);\n"\
"    max_y = clamp(height - block_y*4, 1, 4);\n"\
"\n"\
"    for (i = 0; i < 16; i++)\n"\
"    {\n"\
"        pixel[i] = VFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);\n"\
"        weight[i] = 0.0f;\n"\
"    }\n"\
"\n"\
"    for (i = 0; i < max_y; i++)\n"\
"        for (j = 0; j < max_x; j++)\n"\
"        {\n"\
"            MEMBER(pixel[(i*4 + j)], X) = pixel_rgba[((i + block_y*4)*width + (j + block_x*4))*4 + 0];\n"\
"            MEMBER(pixel[(i*4 + j)], Y) = pixel_rgba[((i + block_y*4)*width + (j + block_x*4))*4 + 1];\n"\
"            MEMBER(pixel[(i*4 + j)], Z) = pixel_rgba[((i + block_y*4)*width + (j + block_x*4))*4 + 2];\n"\
"            MEMBER(pixel[(i*4 + j)], W) = pixel_rgba[((i + block_y*4)*width + (j + block_x*4))*4 + 3];\n"\
"\n"\
"            weight[(i*4 + j)] = 1.0f;\n"\
"\n"\
"        }\n"\
"\n"\
"    if (is_alpha && is_etc2)\n"\
"    {\n"\
"        if (!is_punchthrough)\n"\
"        {\n"\
"            ETC_EncodeRGBWeighted(quality, allowed_modes, rgb_error_target, refine_rgb_search, is_etc2, is_ypbpr, pixel, weight, &block[(block_x * 8 * 2) + (block_y) * line_out_blocks * 8 * 2 + 8]);\n"\
"            ETC_EncodeAlphaWeighted(alpha_error_target, refine_alpha_search, alpha_search_radius, pixel, weight, &block[(block_x * 8 * 2) + (block_y) * line_out_blocks * 8 * 2 + 0]);\n"\
"        }\n"\
"        else\n"\
"        {\n"\
"            int transparent_count = 0;\n"\
"\n"\
"            for (i = 0; i < 16; i++)\n"\
"                if (MEMBER(pixel[i], W) <= alpha_cutoff)\n"\
"                {\n"\
"                    transparent_count++;\n"\
"                    break;\n"\
"                }\n"\
"\n"\
"            if (transparent_count == 0)\n"\
"                ETC_EncodeRGBWeighted(quality, allowed_modes, rgb_error_target, refine_rgb_search, is_etc2, is_ypbpr, pixel, weight, &block[(block_x * 8) + (block_y) * line_out_blocks * 8 + 0]);\n"\
"            else\n"\
"                ETC_EncodeRGBA1Weighted(quality, allowed_modes, rgb_error_target, refine_rgb_search, is_ypbpr, alpha_cutoff, pixel, weight, &block[(block_x * 8) + (block_y) * line_out_blocks * 8 + 0]);\n"\
"        }\n"\
"    }\n"\
"    else\n"\
"    {\n"\
"        ETC_EncodeRGBWeighted(quality, allowed_modes, rgb_error_target, refine_rgb_search, is_etc2, is_ypbpr, pixel, weight, &block[(block_x * 8) + (block_y) * line_out_blocks * 8 + 0]);\n"\
"    }\n"\
"}\n"\
"\n"\
"\n"\
"__kernel void ETC_EncodeETC(\n"\
"    int allowed_modes,                              // bitfield of allowed modes for encoder, mostly for debugging. see MODE preprocessor definitions. suggested default: ETC_MODE_ANY. should never be set to \"ETC_MODE_DELTA\" only.\n"\
"    float alpha_cutoff,                             // valid range 0 - 255, used in RGBA1 mode. (x <= cutoff) = transparent pixel.\n"\
"    float rgb_error_target,                 // MSE error target for colour channels. 0 for max quality, 256 for approximately PVRTexTool \"slow\" quality. high performance impact for lower values. suggested default: 0\n"\
"    float alpha_error_target,               // MSE error target for alpha in RGBA8 mode. 0 for max quality. moderate performance impact. suggested default: 0\n"\
"    int is_ypbpr,                                   // measure MSE in YPbPr space instead of RGB space? moderate performance impact if enabled\n"\
"    int is_etc2,                                    // is ETC1 or ETC2?\n"\
"    int is_alpha,                                   // has an alpha channel?\n"\
"    int is_punchthrough,                    // is alpha channel 1-bit?\n"\
"    int refine_rgb_search,                  // search for best minimum in local neighbourhood to improve quality for RGB. high performance impact. suggested default: 0\n"\
"    int refine_alpha_search,                // search for better \"base alpha\" instead of using simple estimate. moderate performance impact. suggested default: 1\n"\
"    int alpha_search_radius,                // valid range 0 - 7. search radius for better alpha multiplier. moderate performance impact. suggested default: 1\n"\
"    int width,                                              // image width in pixels\n"\
"    int height,                                             // image height in pixels\n"\
"    __global float *pixel_rgba,             // pixel RGBA in R, G, B, A order, (width x height) entries\n"\
"    __global uchar *block,                       // output data\n"\
"    int quality)\n"\
"{\n"\
"    int block_x = get_global_id(0);\n"\
"    int block_y = get_global_id(1);\n"\
"    int max_x;\n"\
"    int max_y;\n"\
"    int is_4x4;\n"\
"\n"\
"    //DEBUG_NCOND return;\n"\
"\n"\
"        if ((block_x * 4 >= width) || (block_y * 4 >= height))\n"\
"            return;\n"\
"        if (!is_etc2)\n"\
"            allowed_modes &= ETC_MODE_ETC1;\n"\
"        else if (is_etc2 && is_alpha && is_punchthrough)\n"\
"            allowed_modes &= ETC_MODE_ETC2RGBA1;\n"\
"        else\n"\
"            allowed_modes &= ETC_MODE_ANY;\n"\
"        max_x = clamp(width - block_x*4, 1, 4);\n"\
"    max_y = clamp(height - block_y*4, 1, 4);\n"\
"        is_4x4 = (max_x + max_y == 8) ? 1 : 0;\n"\
"        if (is_4x4)\n"\
"            ETC_EncodeETC4x4(\n"\
"                allowed_modes,\n"\
"                alpha_cutoff,\n"\
"                rgb_error_target,\n"\
"                alpha_error_target,\n"\
"                is_ypbpr,\n"\
"                is_etc2,\n"\
"                is_alpha,\n"\
"                is_punchthrough,\n"\
"                refine_rgb_search,\n"\
"                refine_alpha_search,\n"\
"                alpha_search_radius,\n"\
"                width,\n"\
"                height,\n"\
"                pixel_rgba,\n"\
"                block,\n"\
"                quality);\n"\
"        else\n"\
"            ETC_EncodeETCN4x4(\n"\
"                allowed_modes,\n"\
"                alpha_cutoff,\n"\
"                rgb_error_target,\n"\
"                alpha_error_target,\n"\
"                is_ypbpr,\n"\
"                is_etc2,\n"\
"                is_alpha,\n"\
"                is_punchthrough,\n"\
"                refine_rgb_search,\n"\
"                refine_alpha_search,\n"\
"                alpha_search_radius,\n"\
"                width,\n"\
"                height,\n"\
"                pixel_rgba,\n"\
"                block,\n"\
"                quality);\n"\
"}\n";