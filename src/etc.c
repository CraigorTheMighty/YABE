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

extern "C" {
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
#include "..\inc\opencl_bcn.h"
#include "..\inc\etc.h"
#include "..\inc\dds.h"

}

#define REFINE_RGB_SEARCH   0
//#define DEBUG_BLOCK (block_x == 516/4 && block_y == 40/4)
//#define DEBUG_BLOCK (block_x == 187 && block_y == 230)
#define DEBUG_BLOCK (block_x == 64 && block_y == 64)

#define DPIX_X    372
#define DPIX_Y        200
#define DEBUG_COND if(get_global_id(0) == DPIX_X/4 && get_global_id(1) == DPIX_Y/4)
#define DEBUG_NCOND if(!(get_global_id(0) == DPIX_X/4 && get_global_id(1) == DPIX_Y/4))

#ifdef TRACK_OPENCL_RANGE
#define ASSERT_RANGE(x, min, max)   do{if ((x < min) || (x > max)) printf("%s():%i range error: (%s < %s) || (%s > %s), actual value: %i (min: %i, max %i)\n", __FUNCTION__, __LINE__, #x, #min, #x, #max, x, min, max);}while(0)
#else
#define ASSERT_RANGE(x, min, max)   
#endif

#if TRACK_OPENCL_TEST_PRINTS
#define DEBUG_PRINT_LINE		printf("%s():%i\n", __FUNCTION__, __LINE__);
#define DEBUG_PRINTF(arg)		{printf("%s():%i: ", __FUNCTION__, __LINE__);printf arg;};
#else
#define DEBUG_PRINT_LINE		
#define DEBUG_PRINTF(arg)		
#endif

#define __kernel
#define __global
#define __constant

#define uchar uint8_t
#define ushort uint16_t
#define uint uint32_t
#define ulong uint64_t

#define long int64_t

#define g_local_group_size 16

#define get_global_id(x)    g_block[x]

#define X   0
#define Y   1
#define Z   2
#define W   3

#define MEMBER(a, b)    a.v[b]

typedef struct float3_s
{
    float   v[3];
}float3;

typedef struct float4_s
{
    float   v[4];
}float4;

typedef struct uchar3_s
{
    uchar   v[3];
}uchar3;

typedef struct short3_s
{
    short   v[3];
}short3;
typedef struct int3_s
{
    int   v[3];
}int3;

static int GetGlobalID(int d)
{
    return 0;
}

static int clamp(int x, int a, int b)
{
    if (x < a)
        return a;
    else if (x > b)
        return b;
    else
        return x;
}
static float clamp(float x, float a, float b)
{
    if (x < a)
        return a;
    else if (x > b)
        return b;
    else
        return x;
}
static float dot(float3 a, float3 b)
{
    return a.v[0]*b.v[0] + a.v[1]*b.v[1] + a.v[2]*b.v[2];
}
static float3 clamp(float3 x, float3 a, float3 b)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        x.v[i] = clamp(x.v[i], a.v[i], b.v[i]);
    }
    return x;
}
static float3 clamp(float3 x, float a, float b)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        x.v[i] = clamp(x.v[i], a, b);
    }
    return x;
}
static float floorf32(float a)
{
    return (float)floor(a);
}
static float4 _VFLOAT4(float a, float b, float c, float d)
{
    float4 x;
    x.v[0] = a;
    x.v[1] = b;
    x.v[2] = c;
    x.v[3] = d;
    return x;
}
static float3 _VFLOAT3(float a, float b, float c)
{
    float3 x;
    x.v[0] = a;
    x.v[1] = b;
    x.v[2] = c;
    return x;
}
static uchar3 _UCHAR3(uchar a, uchar b, uchar c)
{
    uchar3 x;
    x.v[0] = a;
    x.v[1] = b;
    x.v[2] = c;
    return x;
}
static short3 _SHORT3(short a, short b, short c)
{
    short3 x;
    x.v[0] = a;
    x.v[1] = b;
    x.v[2] = c;
    return x;
}
static int3 _INT3(int a, int b, int c)
{
    int3 x;
    x.v[0] = a;
    x.v[1] = b;
    x.v[2] = c;
    return x;
}

float3 operator+(float3 a, float3 b)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        a.v[i] += b.v[i];
    }
    return a;
}
float3 operator-(float3 a, float3 b)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        a.v[i] -= b.v[i];
    }
    return a;
}
float3 operator*(float3 a, float b)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        a.v[i] *= b;
    }
    return a;
}
float3 operator/(float3 a, float b)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        a.v[i] /= b;
    }
    return a;
}

uchar3 operator+(uchar3 a, uchar3 b)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        a.v[i] += b.v[i];
    }
    return a;
}
uchar3 operator-(uchar3 a, uchar3 b)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        a.v[i] -= b.v[i];
    }
    return a;
}
uchar3 operator*(uchar3 a, uchar b)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        a.v[i] *= b;
    }
    return a;
}

short3 operator+(short3 a, short3 b)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        a.v[i] += b.v[i];
    }
    return a;
}
short3 operator-(short3 a, short3 b)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        a.v[i] -= b.v[i];
    }
    return a;
}
short3 operator*(short3 a, short b)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        a.v[i] *= b;
    }
    return a;
}

#define floor                   floorf32

#define VFLOAT4(a, b, c, d)		_VFLOAT4((float)(a), (float)(b), (float)(c), (float)(d))
#define VFLOAT3(a, b, c)		_VFLOAT3((float)(a), (float)(b), (float)(c))
#define UCHAR3(a, b, c)			_UCHAR3((uchar)(a), (uchar)(b), (uchar)(c))
#define SHORT3(a, b, c)			_SHORT3((short)(a), (short)(b), (short)(c))
#define INT3(a, b, c)			_INT3((int)(a), (int)(b), (int)(c))

#pragma OPENCL EXTENSION cl_khr_byte_addressable_store : enable

#define MAX_ERROR_DIFF_MUL              16.0f   // highest multiple that current value of the cost function can be to the current best value during pathing before aborting search
#define MAX_INIT_ERROR                  9999999999999999999999999999999999.0f
#define SAMPLE_LIST_SIZE0       2               // must be 2+
#define SAMPLE_LIST_SIZE1       8               // must be 8+
#define SAMPLE_LIST_SIZE2       8               // used in delta mode pathing, performance vs quality trade-off
#define MAX_KMEANS_ITERATIONS   16
#define M_INV_GOLDEN_F                  0.618033988749894848204586834365638f

#define ETC_MODE_DELTA      1
#define ETC_MODE_NODELTA    2
#define ETC_MODE_T          4
#define ETC_MODE_H          8
#define ETC_MODE_PLANAR     16

#define ETC_MODE_ANY            (ETC_MODE_DELTA | ETC_MODE_NODELTA | ETC_MODE_T | ETC_MODE_H | ETC_MODE_PLANAR)
#define ETC_MODE_ETC1           (ETC_MODE_DELTA | ETC_MODE_NODELTA)
#define ETC_MODE_ETC2RGBA1      (ETC_MODE_DELTA | ETC_MODE_T | ETC_MODE_H | ETC_MODE_PLANAR)

#define ETC_RGBEXPANDVECTO4BIT  0
#define ETC_RGBEXPANDVECTO5BIT  1

#define ETC_EVALUATEDELTAERRORGENERIC   0
#define ETC_EVALUATETSINGLEERRORGENERIC 1
#define ETC_EVALUATETTRIPLEERRORGENERIC 2
#define ETC_EVALUATEHERRORGENERIC               3

#define ETC_EVALUATEDELTAERRORGENERICWEIGHTED   4
#define ETC_EVALUATETSINGLEERRORGENERICWEIGHTED 5
#define ETC_EVALUATETTRIPLEERRORGENERICWEIGHTED 6
#define ETC_EVALUATEHERRORGENERICWEIGHTED               7

#define ETC_EVALUATEDELTAERRORGENERICA1         8
#define ETC_EVALUATETSINGLEERRORGENERICA1       9
#define ETC_EVALUATETTRIPLEERRORGENERICA1       10
#define ETC_EVALUATEHERRORGENERICA1                     11

enum
{
    ETC_ENC_MODE_DELTA = 0,
    ETC_ENC_MODE_NODELTA = 1,
    ETC_ENC_MODE_T = 2,
    ETC_ENC_MODE_H = 3,
    ETC_ENC_MODE_PLANAR = 4,
};

typedef struct etc_sample_s
{
    uchar3      pos_quantised;
    float       error;
}etc_sample_t;

typedef struct etc_partition_mode_params_s
{
    uchar3     rgb[2];
    int     is_flipped;
    int     indexes[16];
    int     table[2];
}etc_partition_mode_params_t;

typedef struct etc_th_mode_params_s
{
    uchar3  rgb[2];
    int     indexes[16];
    int     table;
}etc_th_mode_params_t;

typedef struct etc_pathing_params_s
{
    __constant const int    *partition_indexes;
    int                     *indexes;
    int                     num_indexes;
    int                     mode;
    int                     h_index;
}etc_pathing_params_t;

typedef struct etc_planar_mode_params_s
{
    uchar3      rgb[3];
}etc_planar_mode_params_t;

__constant const int g_partition_indexes[2][2][8] =
{
    {
        {0, 1, 4, 5, 8, 9, 12, 13},
        {2, 3, 6, 7, 10, 11, 14, 15}
    },
    {
        {0, 1, 2, 3, 4, 5, 6, 7},
        {8, 9, 10, 11, 12, 13, 14, 15}
    }
};

__constant const int g_table[8][4] =
{
    {  2,  8,   -2,   -8 },
    {  5, 17,   -5,  -17 },
    {  9, 29,   -9,  -29 },
    { 13, 42,  -13,  -42 },
    { 18, 60,  -18,  -60 },
    { 24, 80,  -24,  -80 },
    { 33, 106, -33, -106 },
    { 47, 183, -47, -183 }
};

__constant const int g_etc2_tmode_distance[8] =
{
    3, 6, 11, 16, 23, 32, 41, 64
};

__constant const int g_alpha[16][8] =
{
    { -3, -6,  -9, -15, 2, 5, 8, 14 },
    { -3, -7, -10, -13, 2, 6, 9, 12 },
    { -2, -5,  -8, -13, 1, 4, 7, 12 },
    { -2, -4,  -6, -13, 1, 3, 5, 12 },
    { -3, -6,  -8, -12, 2, 5, 7, 11 },
    { -3, -7,  -9, -11, 2, 6, 8, 10 },
    { -4, -7,  -8, -11, 3, 6, 7, 10 },
    { -3, -5,  -8, -11, 2, 4, 7, 10 },
    { -2, -6,  -8, -10, 1, 5, 7,  9 },
    { -2, -5,  -8, -10, 1, 4, 7,  9 },
    { -2, -4,  -8, -10, 1, 3, 7,  9 },
    { -2, -5,  -7, -10, 1, 4, 6,  9 },
    { -3, -4,  -7, -10, 2, 3, 6,  9 },
    { -1, -2,  -3, -10, 0, 1, 2,  9 },
    { -4, -6,  -8,  -9, 3, 5, 7,  8 },
    { -3, -5,  -7,  -9, 2, 4, 6,  8 }
};
__constant const int g_alpha_range[16] =
{
    14 + 15,
    12 + 13,
    12 + 13,
    12 + 13,
    11 + 12,
    10 + 11,
    10 + 11,
    10 + 11,
    9 + 10,
    9 + 10,
    9 + 10,
    9 + 10,
    9 + 10,
    9 + 10,
    8 + 9,
    8 + 9
};

float3 ETC_ConvertToRGBf3(float3 v)
{
    float3 rgb;
    MEMBER(rgb, X) = MEMBER(v, X) + 1.402f * MEMBER(v, Z);
    MEMBER(rgb, Y) = MEMBER(v, X) - 0.344136f * MEMBER(v, Y) - 0.714136f * MEMBER(v, Z);
    MEMBER(rgb, Z) = MEMBER(v, X) + 1.772f * MEMBER(v, Y);
    return rgb;
}

float3 ETC_ConvertToYPBPRf3(float3 v)
{
    float3 ypbpr;
    MEMBER(ypbpr, X) = 0.299f * MEMBER(v, X) + 0.587f * MEMBER(v, Y) + 0.114f * MEMBER(v, Z);
    MEMBER(ypbpr, Y) = 0.5f * (MEMBER(v, Z) - MEMBER(ypbpr, X)) / (1.0f - 0.114f);
    MEMBER(ypbpr, Z) = 0.5f * (MEMBER(v, X) - MEMBER(ypbpr, X)) / (1.0f - 0.299f);
    return ypbpr;
}
float3 ETC_ConvertToYPBPRu3(uchar3 v)
{
    float3 ypbpr;
    MEMBER(ypbpr, X) = 0.299f * (float)MEMBER(v, X) + 0.587f * (float)MEMBER(v, Y) + 0.114f * (float)MEMBER(v, Z);
    MEMBER(ypbpr, Y) = 0.5f * ((float)MEMBER(v, Z) - MEMBER(ypbpr, X)) / (1.0f - 0.114f);
    MEMBER(ypbpr, Z) = 0.5f * ((float)MEMBER(v, X) - MEMBER(ypbpr, X)) / (1.0f - 0.299f);
    return ypbpr;
}
float3 ETC_ConvertToYPBPRs3(short3 v)
{
    float3 ypbpr;
    MEMBER(ypbpr, X) = 0.299f * (float)MEMBER(v, X) + 0.587f * (float)MEMBER(v, Y) + 0.114f * (float)MEMBER(v, Z);
    MEMBER(ypbpr, Y) = 0.5f * ((float)MEMBER(v, Z) - MEMBER(ypbpr, X)) / (1.0f - 0.114f);
    MEMBER(ypbpr, Z) = 0.5f * ((float)MEMBER(v, X) - MEMBER(ypbpr, X)) / (1.0f - 0.299f);
    return ypbpr;
}
static int MemCmp(void *a, void *b, int size)
{
    int i;
    uchar *ac = (uchar*)a;
    uchar *bc = (uchar*)b;
    for (i = 0; i < size; i++)
    {
        if (ac[i] != bc[i])
        {
            return 1;
        }
    }
    return 0;
}
static int Vec3f32Cmp(float3 a, float3 b)
{
    if ((MEMBER(a, X) != MEMBER(b, X)) || (MEMBER(a, Y) != MEMBER(b, Y)) || (MEMBER(a, Z) != MEMBER(b, Z)))
        return 1;
    else
        return 0;
}

static void ETC_PackBlockSwapOrder(__global uchar *out_block, uchar *in_block)
{
    out_block[0] = in_block[3];
    out_block[1] = in_block[2];
    out_block[2] = in_block[1];
    out_block[3] = in_block[0];
    out_block[4] = in_block[7];
    out_block[5] = in_block[6];
    out_block[6] = in_block[5];
    out_block[7] = in_block[4];
}
static void ETC_PackBlockReverseOrder(__global uchar *out_block, uchar *in_block)
{
    out_block[0] = in_block[7];
    out_block[1] = in_block[6];
    out_block[2] = in_block[5];
    out_block[3] = in_block[4];
    out_block[4] = in_block[3];
    out_block[5] = in_block[2];
    out_block[6] = in_block[1];
    out_block[7] = in_block[0];
}
static void ETC_WriteBits(uchar *block, uint x, int start_bit, int num_bits)
{
    int i = 0;

    DEBUG_PRINTF(("writing %u of len %i to %i\n", x, num_bits, start_bit));

    if (num_bits == 0)
    {
        return;
    }
        for (i = 0; i < num_bits; i++)
        {
            block[(start_bit + i) >> 3] &= ~(1 << ((start_bit + i) & 0x07));
            block[(start_bit + i) >> 3] |= ((x >> i) & 1) << ((start_bit + i) & 0x07);
        }
}

uchar ETC_RGBRoundTo7Bit(uchar v)
{
    uint temp = v;
    temp = ((temp + 1) * 127) >> 7;
    temp >>= 1;
    temp <<= 1;
    temp |= temp >> 7;
    v = UCHAR(temp);

    return v;
}
uchar ETC_RGBRoundTo6Bit(uchar v)
{
    uint temp = v;
    temp = ((temp + 3) * 63) >> 6;
    temp >>= 2;
    temp <<= 2;
    temp |= temp >> 6;
    v = UCHAR(temp);

    return v;
}
uchar ETC_RGBRoundTo5Bit(uchar v)
{
    uint temp = v;
    temp = ((temp + 5) * 31) >> 5;
    temp >>= 3;
    temp <<= 3;
    temp |= temp >> 5;
    v = UCHAR(temp);

    return v;
}
uchar ETC_RGBRoundTo4Bit(uchar v)
{
    uint temp = v;
    temp = ((temp + 9) * 15) >> 4;
    temp >>= 4;
    temp <<= 4;
    temp |= temp >> 4;
    v = UCHAR(temp);

    return v;
}
uchar3 ETC_RGBRoundVecTo7Bit(uchar3 v)
{
    MEMBER(v, X) = ETC_RGBRoundTo7Bit(MEMBER(v, X));
    MEMBER(v, Y) = ETC_RGBRoundTo7Bit(MEMBER(v, Y));
    MEMBER(v, Z) = ETC_RGBRoundTo7Bit(MEMBER(v, Z));

    return v;
}
uchar3 ETC_RGBRoundVecTo6Bit(uchar3 v)
{
    MEMBER(v, X) = ETC_RGBRoundTo6Bit(MEMBER(v, X));
    MEMBER(v, Y) = ETC_RGBRoundTo6Bit(MEMBER(v, Y));
    MEMBER(v, Z) = ETC_RGBRoundTo6Bit(MEMBER(v, Z));

    return v;
}
uchar3 ETC_RGBRoundVecTo5Bit(uchar3 v)
{
    MEMBER(v, X) = ETC_RGBRoundTo5Bit(MEMBER(v, X));
    MEMBER(v, Y) = ETC_RGBRoundTo5Bit(MEMBER(v, Y));
    MEMBER(v, Z) = ETC_RGBRoundTo5Bit(MEMBER(v, Z));

    return v;
}
uchar3 ETC_RGBRoundVecTo4Bit(uchar3 v)
{
    MEMBER(v, X) = ETC_RGBRoundTo4Bit(MEMBER(v, X));
    MEMBER(v, Y) = ETC_RGBRoundTo4Bit(MEMBER(v, Y));
    MEMBER(v, Z) = ETC_RGBRoundTo4Bit(MEMBER(v, Z));

    return v;
}

uchar ETC_ExpandTo7Bit(uchar v)
{
    uint temp = v;
    temp <<= 1;
    temp |= temp >> 7;
    v = UCHAR(temp);
    return v;
}
uchar ETC_ExpandTo6Bit(uchar v)
{
    uint temp = v;
    temp <<= 2;
    temp |= temp >> 6;
    v = UCHAR(temp);
    return v;
}
uchar ETC_ExpandTo5Bit(uchar v)
{
    uint temp = v;
    temp <<= 3;
    temp |= temp >> 5;
    v = UCHAR(temp);
    return v;
}
uchar ETC_ExpandTo4Bit(uchar v)
{
    uint temp = v;
    temp <<= 4;
    temp |= temp >> 4;
    v = UCHAR(temp);
    return v;
}

uchar3 ETC_RGBExpandVecTo7Bit(uchar3 v)
{
    MEMBER(v, X) = ETC_ExpandTo7Bit(MEMBER(v, X));
    MEMBER(v, Y) = ETC_ExpandTo7Bit(MEMBER(v, Y));
    MEMBER(v, Z) = ETC_ExpandTo7Bit(MEMBER(v, Z));

    return v;
}

uchar3 ETC_RGBExpandVecTo6Bit(uchar3 v)
{
    MEMBER(v, X) = ETC_ExpandTo6Bit(MEMBER(v, X));
    MEMBER(v, Y) = ETC_ExpandTo6Bit(MEMBER(v, Y));
    MEMBER(v, Z) = ETC_ExpandTo6Bit(MEMBER(v, Z));

    return v;
}
uchar3 ETC_RGBExpandVecTo5Bit(uchar3 v)
{
    MEMBER(v, X) = ETC_ExpandTo5Bit(MEMBER(v, X));
    MEMBER(v, Y) = ETC_ExpandTo5Bit(MEMBER(v, Y));
    MEMBER(v, Z) = ETC_ExpandTo5Bit(MEMBER(v, Z));

    return v;
}
uchar3 ETC_RGBExpandVecTo4Bit(uchar3 v)
{
    MEMBER(v, X) = ETC_ExpandTo4Bit(MEMBER(v, X));
    MEMBER(v, Y) = ETC_ExpandTo4Bit(MEMBER(v, Y));
    MEMBER(v, Z) = ETC_ExpandTo4Bit(MEMBER(v, Z));

    return v;
}


void ETC_AddSampleToList(int sample_list_entries, etc_sample_t *list, etc_sample_t sample)
{
    int i, j;

    for (i = 0; i < sample_list_entries; i++)
    {
        if (sample.error < list[i].error)
        {
            for (j = sample_list_entries - 1; j > i; j--)
                list[j] = list[j - 1];
            list[i] = sample;
            break;
        }
    }
}
float ETC_EvaluateError(int is_ypbpr, float3 *trans_pixel, uchar3 rgb, __constant const int *partition_indexes)
{
    int i, table, j;
    float best_table_dist = MAX_INIT_ERROR;
    float3 rgb32f = VFLOAT3(MEMBER(rgb, X), MEMBER(rgb, Y), MEMBER(rgb, Z));
    //DEBUG_PRINTF(("trans_pixel / partition_indexes: 0x%p 0x%p\n", trans_pixel, partition_indexes));

    for (table = 0; table < 8; table++)
    {
        float current_table_dist = 0.0f;
        for (i = 0; i < 8; i++)
        {
            float best_dist = MAX_INIT_ERROR;
            for (j = 0; j < 4; j++)
            {
                float3 temp_pixel = clamp(rgb32f + VFLOAT3(g_table[table][j], g_table[table][j], g_table[table][j]), 0.0f, 255.0f);
                float3 delta;

                ASSERT_RANGE(partition_indexes[i], 0, 15);

                if (is_ypbpr)
                {
                    delta = ETC_ConvertToYPBPRf3(temp_pixel) - trans_pixel[partition_indexes[i]];
                }
                else
                {
                    delta = temp_pixel - trans_pixel[partition_indexes[i]];
                }

                float lensq = dot(delta, delta);

                if (lensq < best_dist)
                {
                    best_dist = lensq;
                }
            }
            current_table_dist += best_dist;
        }
        if (current_table_dist < best_table_dist)
        {
            best_table_dist = current_table_dist;
        }
    }
    return best_table_dist;
}

float ETC_EvaluateErrorTSingle(int is_ypbpr, float3 *trans_pixel, uchar3 rgb, int *indexes, int num_indexes)
{
    int i;
    float dist = 0.0f;
    float3 rgb32f;

    //DEBUG_PRINTF(("trans_pixel / indexes / num_indexes: 0x%p 0x%p %i\n", trans_pixel, indexes, num_indexes));

    if (!num_indexes)
    {
        return 0.0f;
    }
    rgb32f = VFLOAT3(MEMBER(rgb, X), MEMBER(rgb, Y), MEMBER(rgb, Z));

    if (is_ypbpr)
    {
        rgb32f = ETC_ConvertToYPBPRf3(rgb32f);
    }

    for (i = 0; i < num_indexes; i++)
    {
        float3 delta;
        ASSERT_RANGE(indexes[i], 0, 15);
        delta = rgb32f - trans_pixel[indexes[i]];
        dist += dot(delta, delta);
    }
    return dist;
}
float ETC_EvaluateErrorTTriple(int is_ypbpr, float3 *trans_pixel, uchar3 rgb, int *indexes, int num_indexes)
{
    int i, mode, j;
    float3 rgb32f;

    //DEBUG_PRINTF(("trans_pixel / indexes / num_indexes: 0x%p 0x%p %i\n", trans_pixel, indexes, num_indexes));

    float best_mode_dist;

    if (!num_indexes)
    {
        return 0.0f;
    }
    rgb32f = VFLOAT3(MEMBER(rgb, X), MEMBER(rgb, Y), MEMBER(rgb, Z));
    best_mode_dist = MAX_INIT_ERROR;
    for (mode = 0; mode < 8; mode++)
    {
        float current_mode_dist = 0.0f;
        float3 points[3];
        points[0] = clamp(rgb32f + VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);
        points[1] = rgb32f;
        points[2] = clamp(rgb32f - VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);
        if (is_ypbpr)
        {
            points[0] = ETC_ConvertToYPBPRf3(points[0]);
            points[1] = ETC_ConvertToYPBPRf3(points[1]);
            points[2] = ETC_ConvertToYPBPRf3(points[2]);
        }

        for (i = 0; i < num_indexes; i++)
        {
            float best_dist = MAX_INIT_ERROR;
            for (j = 0; j < 3; j++)
            {
                float3 delta;
                float lensq;
                ASSERT_RANGE(indexes[i], 0, 15);
                delta = points[j] - trans_pixel[indexes[i]];
                lensq = dot(delta, delta);
                if (lensq < best_dist)
                {
                    best_dist = lensq;
                }
            }
            current_mode_dist += best_dist;
        }
        if (current_mode_dist < best_mode_dist)
        {
            best_mode_dist = current_mode_dist;
        }
    }
    return best_mode_dist;
}

float ETC_EvaluateErrorH(int is_ypbpr, float3 *trans_pixel, uchar3 rgb, int *indexes, int num_indexes, int mode)
{
    int i, j;
    float3 rgb32f;
    float current_mode_dist = 0.0f;
    float3 points[2];

    //DEBUG_PRINTF(("trans_pixel / indexes / num_indexes / mode: 0x%p 0x%p %i %i\n", trans_pixel, indexes, num_indexes, mode));

    if (!num_indexes)
    {
        return 0.0f;
    }

    rgb32f = VFLOAT3(MEMBER(rgb, X), MEMBER(rgb, Y), MEMBER(rgb, Z));

    ASSERT_RANGE(mode, 0, 7);

    points[0] = clamp(rgb32f + VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);
    points[1] = clamp(rgb32f - VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);

    if (is_ypbpr)
    {
        points[0] = ETC_ConvertToYPBPRf3(points[0]);
        points[1] = ETC_ConvertToYPBPRf3(points[1]);
    }

    for (i = 0; i < num_indexes; i++)
    {
        float best_dist = MAX_INIT_ERROR;
        for (j = 0; j < 2; j++)
        {
            float3 delta;
            float lensq;

            ASSERT_RANGE(indexes[i], 0, 15);
            delta = points[j] - trans_pixel[indexes[i]];
            lensq = dot(delta, delta);

            if (lensq < best_dist)
            {
                best_dist = lensq;
            }
        }
        current_mode_dist += best_dist;
    }

    return current_mode_dist;
}

float EvaluateErrorGeneric(int mode, int is_ypbpr, float3 *trans_pixel, uchar3 rgb, etc_pathing_params_t *pathing_params)
{
    switch (mode)
    {
        case ETC_EVALUATEDELTAERRORGENERIC:
            return ETC_EvaluateError(is_ypbpr, trans_pixel, rgb, pathing_params->partition_indexes);
        case ETC_EVALUATETSINGLEERRORGENERIC:
            return ETC_EvaluateErrorTSingle(is_ypbpr, trans_pixel, rgb, pathing_params->indexes, pathing_params->num_indexes);
        case ETC_EVALUATETTRIPLEERRORGENERIC:
            return ETC_EvaluateErrorTTriple(is_ypbpr, trans_pixel, rgb, pathing_params->indexes, pathing_params->num_indexes);
        case ETC_EVALUATEHERRORGENERIC:
            return ETC_EvaluateErrorH(is_ypbpr, trans_pixel, rgb, pathing_params->indexes, pathing_params->num_indexes, pathing_params->mode);
        default:
            return MAX_INIT_ERROR;
    }
}
void ETC_GetOptimalIndexes(int is_ypbpr, float3 *trans_pixel, uchar3 rgb, __constant const int *partition_indexes, int *best_table, int *indexes)
{
    int i, table, j;
    float best_table_dist = MAX_INIT_ERROR;
    float3 rgb32f = VFLOAT3(MEMBER(rgb, X), MEMBER(rgb, Y), MEMBER(rgb, Z));

    *best_table = 0;

    for (table = 0; table < 8; table++)
    {
        float current_table_dist = 0.0f;
        for (i = 0; i < 8; i++)
        {
            float best_dist = MAX_INIT_ERROR;
            for (j = 0; j < 4; j++)
            {
                float3 temp_pixel = clamp(rgb32f + VFLOAT3(g_table[table][j], g_table[table][j], g_table[table][j]), 0.0f, 255.0f);
                float3 delta;

                ASSERT_RANGE(partition_indexes[i], 0, 15);

                if (is_ypbpr)
                {
                    delta = ETC_ConvertToYPBPRf3(temp_pixel) - trans_pixel[partition_indexes[i]];
                }
                else
                {
                    delta = temp_pixel - trans_pixel[partition_indexes[i]];
                }

                float lensq = dot(delta, delta);

                if (lensq < best_dist)
                {
                    best_dist = lensq;
                }
            }
            current_table_dist += best_dist;
        }
        if (current_table_dist < best_table_dist)
        {
            *best_table = table;
            best_table_dist = current_table_dist;
        }
    }

    for (i = 0; i < 8; i++)
    {
        float best_dist = MAX_INIT_ERROR;
        for (j = 0; j < 4; j++)
        {
            float3 temp_pixel = clamp(rgb32f + VFLOAT3(g_table[*best_table][j], g_table[*best_table][j], g_table[*best_table][j]), 0.0f, 255.0f);
            float3 delta;

            ASSERT_RANGE(partition_indexes[i], 0, 15);

            if (is_ypbpr)
            {
                delta = ETC_ConvertToYPBPRf3(temp_pixel) - trans_pixel[partition_indexes[i]];
            }
            else
            {
                delta = temp_pixel - trans_pixel[partition_indexes[i]];
            }

            float lensq = dot(delta, delta);

            if (lensq < best_dist)
            {
                indexes[partition_indexes[i]] = j;
                best_dist = lensq;
            }
        }
    }
}

float ETC_GetOptimalTIndexes(int is_ypbpr, float3 *trans_pixel, uchar3 rgb_single, uchar3 rgb_triple, int *indexes, int *best_mode)
{
    int i, mode, j;
    float dist = 0.0f;
    float3 rgb32f_single;
    float3 rgb32f_triple;
    float best_mode_dist;
    float3 points[4];

    rgb32f_single = VFLOAT3(MEMBER(rgb_single, X), MEMBER(rgb_single, Y), MEMBER(rgb_single, Z));
    rgb32f_triple = VFLOAT3(MEMBER(rgb_triple, X), MEMBER(rgb_triple, Y), MEMBER(rgb_triple, Z));
    best_mode_dist = MAX_INIT_ERROR;
    *best_mode = 0;

    points[0] = rgb32f_single;

    if (is_ypbpr)
    {
        points[0] = ETC_ConvertToYPBPRf3(points[0]);
    }

    for (mode = 0; mode < 8; mode++)
    {
        float current_mode_dist = 0.0f;

        points[1] = clamp(rgb32f_triple + VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);
        points[2] = rgb32f_triple;
        points[3] = clamp(rgb32f_triple - VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);

        if (is_ypbpr)
        {
            points[1] = ETC_ConvertToYPBPRf3(points[1]);
            points[2] = ETC_ConvertToYPBPRf3(points[2]);
            points[3] = ETC_ConvertToYPBPRf3(points[3]);
        }

        for (i = 0; i < 16; i++)
        {
            float best_dist = MAX_INIT_ERROR;
            for (j = 0; j < 4; j++)
            {
                float3 delta;
                float lensq;
                delta = points[j] - trans_pixel[i];
                lensq = dot(delta, delta);
                if (lensq < best_dist)
                {
                    best_dist = lensq;
                }
            }
            current_mode_dist += best_dist;
        }
        if (current_mode_dist < best_mode_dist)
        {
            *best_mode = mode;
            best_mode_dist = current_mode_dist;
        }
    }

    ASSERT_RANGE(*best_mode, 0, 7);

    points[1] = clamp(rgb32f_triple + VFLOAT3(g_etc2_tmode_distance[*best_mode], g_etc2_tmode_distance[*best_mode], g_etc2_tmode_distance[*best_mode]), 0.0f, 255.0f);
    points[2] = rgb32f_triple;
    points[3] = clamp(rgb32f_triple - VFLOAT3(g_etc2_tmode_distance[*best_mode], g_etc2_tmode_distance[*best_mode], g_etc2_tmode_distance[*best_mode]), 0.0f, 255.0f);

    if (is_ypbpr)
    {
        points[1] = ETC_ConvertToYPBPRf3(points[1]);
        points[2] = ETC_ConvertToYPBPRf3(points[2]);
        points[3] = ETC_ConvertToYPBPRf3(points[3]);
    }

    dist = 0.0f;

    for (i = 0; i < 16; i++)
    {
        float best_dist = MAX_INIT_ERROR;
        for (j = 0; j < 4; j++)
        {
            float3 delta;
            float lensq;
            delta = points[j] - trans_pixel[i];
            lensq = dot(delta, delta);
            if (lensq < best_dist)
            {
                indexes[i] = j;
                best_dist = lensq;
            }
        }
        dist += best_dist;
    }
    return dist;
}
float ETC_GetOptimalHIndexes(int is_ypbpr, float3 *trans_pixel, uchar3 rgb_h0, uchar3 rgb_h1, int *indexes, int mode)
{
    int i, j;
    float dist = 0.0f;
    float3 rgb32f_h0;
    float3 rgb32f_h1;
    float3 points[4];

    rgb32f_h0 = VFLOAT3(MEMBER(rgb_h0, X), MEMBER(rgb_h0, Y), MEMBER(rgb_h0, Z));
    rgb32f_h1 = VFLOAT3(MEMBER(rgb_h1, X), MEMBER(rgb_h1, Y), MEMBER(rgb_h1, Z));

    ASSERT_RANGE(mode, 0, 7);

    points[0] = clamp(rgb32f_h0 + VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);
    points[1] = clamp(rgb32f_h0 - VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);
    points[2] = clamp(rgb32f_h1 + VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);
    points[3] = clamp(rgb32f_h1 - VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);

    if (is_ypbpr)
    {
        points[0] = ETC_ConvertToYPBPRf3(points[0]);
        points[1] = ETC_ConvertToYPBPRf3(points[1]);
        points[2] = ETC_ConvertToYPBPRf3(points[2]);
        points[3] = ETC_ConvertToYPBPRf3(points[3]);
    }

    dist = 0.0f;

    for (i = 0; i < 16; i++)
    {
        float best_dist = MAX_INIT_ERROR;
        for (j = 0; j < 4; j++)
        {
            float3 delta;
            float lensq;
            delta = points[j] - trans_pixel[i];
            lensq = dot(delta, delta);
            if (lensq < best_dist)
            {
                indexes[i] = j;
                best_dist = lensq;
            }
        }
        dist += best_dist;
    }
    return dist;
}

void ETC_LeastCostDirectedPath(
    int step,
    int sample_list_entries,
    float error_target,
    int refine_search,
    int is_ypbpr,
    float3 *trans_pixel,
    etc_sample_t sample,
    etc_sample_t *sample_list,
    int x_max,
    int y_max,
    int z_max,
    etc_pathing_params_t *pathing_params,
    int expand_cb_fp,
    int evaluate_cb_fp,
    int block_x,
    int block_y)
{
    int         i;
    int         j;
    int         terminate;
    float       dist[27];

    DEBUG_PRINTF(("trans_pixel: 0x%p partition_indexes: 0x%p indexes: 0x%p num_indexes: %i mode: %i\n", trans_pixel, pathing_params->partition_indexes, pathing_params->indexes, pathing_params->num_indexes, pathing_params->mode));

    for (i = 0, terminate = 0; terminate == 0; i++)
    {
        uchar3 test_pos[7];
        float best_dist;
        int best_index;
        int terminate_count = 0;

        ETC_AddSampleToList(sample_list_entries, &sample_list[0], sample);
        DEBUG_PRINTF(("function: %i sample pos: %i %i %i sample error: %f trans_pixel: 0x%p partition_indexes: 0x%p indexes: 0x%p num_indexes: %i mode: %i\n", evaluate_cb_fp, MEMBER(sample.pos_quantised, X), MEMBER(sample.pos_quantised, Y), MEMBER(sample.pos_quantised, Z), sample.error, trans_pixel, pathing_params->partition_indexes, pathing_params->indexes, pathing_params->num_indexes, pathing_params->mode));

        if (sample.error <= error_target)
        {
            break;
        }

        test_pos[0] = sample.pos_quantised + UCHAR3(step, 0, 0);
        test_pos[1] = sample.pos_quantised + UCHAR3(0, step, 0);
        test_pos[2] = sample.pos_quantised + UCHAR3(step, step, 0);
        test_pos[3] = sample.pos_quantised + UCHAR3(0, 0, step);
        test_pos[4] = sample.pos_quantised + UCHAR3(step, 0, step);
        test_pos[5] = sample.pos_quantised + UCHAR3(0, step, step);
        test_pos[6] = sample.pos_quantised + UCHAR3(step, step, step);

        for (j = 0; j < 7; j++)
        {
            if ((MEMBER(test_pos[j], X) > x_max) || (MEMBER(test_pos[j], Y) > y_max) || (MEMBER(test_pos[j], Z) > z_max))
            {
                dist[j] = MAX_INIT_ERROR;
            }
            else
            {
                uchar3 v;

                switch (expand_cb_fp)
                {
                    case ETC_RGBEXPANDVECTO4BIT:
                        v = ETC_RGBExpandVecTo4Bit(test_pos[j]);
                        break;
                    case ETC_RGBEXPANDVECTO5BIT:
                        v = ETC_RGBExpandVecTo5Bit(test_pos[j]);
                        break;
                }
                dist[j] = EvaluateErrorGeneric(evaluate_cb_fp, is_ypbpr, trans_pixel, v, pathing_params);
            }
        }

        best_dist = dist[0];
        best_index = 0;
        for (j = 1; j < 7; j++)
        {
            if (dist[j] < best_dist)
            {
                best_dist = dist[j];
                best_index = j;
            }
        }

        for (j = 0; j < 7; j++)
            if (dist[j] == MAX_INIT_ERROR)
            {
                terminate_count++;
            }

        if (terminate_count == 7)
        {
            break;
        }

        if (dist[best_index] > MAX_ERROR_DIFF_MUL * sample_list[0].error)
        {
            break;
        }

        sample.pos_quantised = test_pos[best_index];
        sample.error = dist[best_index];
    }

    if (refine_search)
    {
        sample.pos_quantised = sample_list[0].pos_quantised;
        sample.error = sample_list[0].error;

        for (i = 0, terminate = 0; terminate == 0; i++)
        {
            short3 test_pos[27];
            float best_dist;
            int best_index;
            int terminate_count = 0;

            if (i != 1)
            {
                ETC_AddSampleToList(sample_list_entries, &sample_list[0], sample);
                DEBUG_PRINTF(("trans_pixel: 0x%p partition_indexes: 0x%p indexes: 0x%p num_indexes: %i mode: %i\n", trans_pixel, pathing_params->partition_indexes, pathing_params->indexes, pathing_params->num_indexes, pathing_params->mode));
            }

            if (sample.error <= error_target)
            {
                break;
            }

            for (j = 0; j < 27; j++)
                test_pos[j] = SHORT3(MEMBER(sample.pos_quantised, X), MEMBER(sample.pos_quantised, Y), MEMBER(sample.pos_quantised, Z)) + SHORT3((j % 3) - 1, ((j / 3) % 3) - 1, j/9 - 1);

            for (j = 0; j < 27; j++)
            {
                if (j == 13)
                    dist[j] = sample.error;
                else if ((MEMBER(test_pos[j], X) > x_max) || (MEMBER(test_pos[j], Y) > y_max) || (MEMBER(test_pos[j], Z) > z_max) || (MEMBER(test_pos[j], X) < 0) || (MEMBER(test_pos[j], Y) < 0) || (MEMBER(test_pos[j], Z) < 0))
                    dist[j] = MAX_INIT_ERROR;
                else
                {
                    uchar3 v;

                    switch (expand_cb_fp)
                    {
                    case ETC_RGBEXPANDVECTO4BIT:
                        v = ETC_RGBExpandVecTo4Bit(UCHAR3(MEMBER(test_pos[j], X), MEMBER(test_pos[j], Y), MEMBER(test_pos[j], Z)));
                        break;
                    case ETC_RGBEXPANDVECTO5BIT:
                        v = ETC_RGBExpandVecTo5Bit(UCHAR3(MEMBER(test_pos[j], X), MEMBER(test_pos[j], Y), MEMBER(test_pos[j], Z)));
                        break;
                    }

                    dist[j] = EvaluateErrorGeneric(evaluate_cb_fp, is_ypbpr, trans_pixel, v, pathing_params);
                }
            }

            best_dist = dist[0];
            best_index = 0;
            for (j = 1; j < 27; j++)
            {
                if (dist[j] < best_dist)
                {
                    best_dist = dist[j];
                    best_index = j;
                }
            }

            if (dist[13] == best_dist)
                break;

            for (j = 0; j < 27; j++)
                if (dist[j] == MAX_INIT_ERROR)
                    terminate_count++;

            if (terminate_count >= 26)
                break;

            if (dist[best_index] > MAX_ERROR_DIFF_MUL * sample_list[0].error)
                break;

            sample.pos_quantised = UCHAR3(MEMBER(test_pos[best_index], X), MEMBER(test_pos[best_index], Y), MEMBER(test_pos[best_index], Z));
            sample.error = dist[best_index];
        }
    }
}
void ETC_PrepareSampleList(int sample_list_entries, etc_sample_t sample_list[SAMPLE_LIST_SIZE0][SAMPLE_LIST_SIZE1][SAMPLE_LIST_SIZE2])
{
    int i;
    int j;
    int k;
    for (i = 0; i < SAMPLE_LIST_SIZE0; i++)
        for (j = 0; j < SAMPLE_LIST_SIZE1; j++)
            for (k = 0; k < sample_list_entries; k++)
            {
                DEBUG_PRINTF(("sample_list[%i][%i][%i]: 0x%p\n", i, j, k, &sample_list[i][j][k]));
                sample_list[i][j][k].error = MAX_INIT_ERROR;
            }
}

void ETC_KMeansTHMode(float3 *trans_pixel, int *indexes0, int *indexes1, int *set_count)
{
    float3 means[2];
    int swap_indexes[2][2][16];
    int point_count[2][2];
    int ri[2];
    int i;
    int iteration;
    int source;
    int target;
    int set;

    ri[0] = 0;
    ri[1] = 0;
    
    for (i = 0; i < 16; i++)
        DEBUG_PRINTF(("pixel[%i]: %f %f %f\n", i, MEMBER(trans_pixel[i], X), MEMBER(trans_pixel[i], Y), MEMBER(trans_pixel[i], Z)));

    for (i = 1; i < 16; i++)
        if(!(MEMBER(trans_pixel[ri[0]], X) == MEMBER(trans_pixel[i], X) && MEMBER(trans_pixel[ri[0]], Y) == MEMBER(trans_pixel[i], Y) && MEMBER(trans_pixel[ri[0]], Z) == MEMBER(trans_pixel[i], Z)))
        {
            ri[1] = i;
            break;
        }

    means[0] = trans_pixel[ri[0]];
    means[1] = trans_pixel[ri[1]];

    for (i = 0; i < 16; i++)
        swap_indexes[0][0][i] = i;

    point_count[0][0] = 16;
    point_count[0][1] = 0;
    point_count[1][0] = 0;
    point_count[1][1] = 0;

    source = 0;
    target = 1;

    for (iteration = 0; iteration < MAX_KMEANS_ITERATIONS; iteration++)
    {
        float3 temp_means[2];

        temp_means[0] = VFLOAT3(0.0f, 0.0f, 0.0f);
        temp_means[1] = VFLOAT3(0.0f, 0.0f, 0.0f);

        for (set = 0; set < 2; set++)
        {
            for (i = 0; i < point_count[source][set]; i++)
            {
                float3 diff[2];
                float lensq[2];

                ASSERT_RANGE(source, 0, 1);
                ASSERT_RANGE(target, 0, 1);
                ASSERT_RANGE(set, 0, 1);
                ASSERT_RANGE(swap_indexes[source][set][i], 0, 15);
                ASSERT_RANGE(point_count[target][0], 0, 15);
                ASSERT_RANGE(point_count[target][1], 0, 15);

                diff[0] = means[0] - trans_pixel[swap_indexes[source][set][i]];
                diff[1] = means[1] - trans_pixel[swap_indexes[source][set][i]];

                lensq[0] = dot(diff[0], diff[0]);
                lensq[1] = dot(diff[1], diff[1]);

                if (lensq[0] < lensq[1])
                {
                    swap_indexes[target][0][point_count[target][0]] = swap_indexes[source][set][i];
                    temp_means[0] = temp_means[0] + trans_pixel[swap_indexes[source][set][i]];
                    //printf("swap_indexes[%i][0][%i]: %i\n", target, point_count[target][0], swap_indexes[target][0][point_count[target][0]]);
                    point_count[target][0]++;
                }
                else
                {
                    swap_indexes[target][1][point_count[target][1]] = swap_indexes[source][set][i];
                    temp_means[1] = temp_means[1] + trans_pixel[swap_indexes[source][set][i]];
                    //printf("swap_indexes[%i][1][%i]: %i\n", target, point_count[target][1], swap_indexes[target][1][point_count[target][1]]);
                    point_count[target][1]++;
                }
            }
        }

        temp_means[0] = temp_means[0] / (float)(point_count[target][0] == 0 ? 1 : point_count[target][0]);
        temp_means[1] = temp_means[1] / (float)(point_count[target][1] == 0 ? 1 : point_count[target][1]);
        DEBUG_PRINTF(("means[0] means[1]: %f %f %f, %f %f %f\n", MEMBER(temp_means[0], X), MEMBER(temp_means[0], Y), MEMBER(temp_means[0], Z), MEMBER(temp_means[1], X), MEMBER(temp_means[1], Y), MEMBER(temp_means[1], Z)));

        means[0] = temp_means[0];
        means[1] = temp_means[1];

        source = (source + 1) % 2;
        target = (target + 1) % 2;

        point_count[target][0] = 0;
        point_count[target][1] = 0;
    }
    for (i = 0; i < point_count[source][0]; i++)
    {
        ASSERT_RANGE(swap_indexes[source][0][i], 0, 15);
        indexes0[i] = swap_indexes[source][0][i];
    }
    for (i = 0; i < point_count[source][1]; i++)
    {
        ASSERT_RANGE(swap_indexes[source][1][i], 0, 15);
        indexes1[i] = swap_indexes[source][1][i];
    }

    set_count[0] = point_count[source][0];
    set_count[1] = point_count[source][1];

    ASSERT_RANGE(set_count[0], 0, 16);
    ASSERT_RANGE(set_count[1], 0, 16);
}

void ETC_EncodeRGBFast(
    int allowed_modes,
    int is_etc2,
    int is_ypbpr,
    float4 *pixel,
    __global uchar *block)
{
    int i, j, table;
    float3 trans_pixel[16];
    int is_delta;
    int is_flipped;
    etc_partition_mode_params_t params_partition;
    etc_th_mode_params_t params_th;
    etc_planar_mode_params_t params_planar;
    etc_pathing_params_t pathing_params;
    etc_partition_mode_params_t params_partition_nodelta;
    uchar local_block[8];
    float err[2] = {0.0f, 0.0f};
    uchar3 partition_rgb[2][2];
    float best_error[5] = {MAX_INIT_ERROR, MAX_INIT_ERROR, MAX_INIT_ERROR, MAX_INIT_ERROR, MAX_INIT_ERROR};
    int best_mode = 0;
    int found_mode = 0;

    DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
    for (i = 0; i < 16; i++)
    {
        MEMBER(trans_pixel[i], X) = MEMBER(pixel[i], X);
        MEMBER(trans_pixel[i], Y) = MEMBER(pixel[i], Y);
        MEMBER(trans_pixel[i], Z) = MEMBER(pixel[i], Z);
    }

    if (allowed_modes & ETC_MODE_NODELTA)
    {
        for (is_flipped = 0; is_flipped < 2; is_flipped++)
        {
            float proj_mean[2] = {0.0f, 0.0f};
            float x[2] = {0.0f, 0.0f};
            float z[2] = {0.0f, 0.0f};

            for (i = 0; i < 8; i++)
            {
                ASSERT_RANGE(g_partition_indexes[is_flipped][0][i], 0, 16);
                ASSERT_RANGE(g_partition_indexes[is_flipped][1][i], 0, 16);

                x[0] += MEMBER(trans_pixel[g_partition_indexes[is_flipped][0][i]], X);
                x[0] -= MEMBER(trans_pixel[g_partition_indexes[is_flipped][0][i]], Y);
                z[0] += MEMBER(trans_pixel[g_partition_indexes[is_flipped][0][i]], Z);
                z[0] -= MEMBER(trans_pixel[g_partition_indexes[is_flipped][0][i]], Y);

                x[1] += MEMBER(trans_pixel[g_partition_indexes[is_flipped][1][i]], X);
                x[1] -= MEMBER(trans_pixel[g_partition_indexes[is_flipped][1][i]], Y);
                z[1] += MEMBER(trans_pixel[g_partition_indexes[is_flipped][1][i]], Z);
                z[1] -= MEMBER(trans_pixel[g_partition_indexes[is_flipped][1][i]], Y);
            }

            x[0] /= 8.0f;
            x[1] /= 8.0f;
            z[0] /= 8.0f;
            z[1] /= 8.0f;

            for (i = 0; i < 8; i++)
            {
                proj_mean[0] += dot(trans_pixel[g_partition_indexes[is_flipped][0][i]] - VFLOAT3(x[0], 0.0f, z[0]), VFLOAT3(0.57735f, 0.57735f, 0.57735f));
                proj_mean[1] += dot(trans_pixel[g_partition_indexes[is_flipped][1][i]] - VFLOAT3(x[1], 0.0f, z[1]), VFLOAT3(0.57735f, 0.57735f, 0.57735f));
            }

            proj_mean[0] /= 8.0f;
            proj_mean[1] /= 8.0f;
            proj_mean[0] *= 0.57735f;
            proj_mean[1] *= 0.57735f;

            partition_rgb[is_flipped][0] = UCHAR3(clamp(x[0] + proj_mean[0], 0.0f, 255.0f), clamp(proj_mean[0], 0.0f, 255.0f), clamp(z[0] + proj_mean[0], 0.0f, 255.0f));
            partition_rgb[is_flipped][1] = UCHAR3(clamp(x[1] + proj_mean[1], 0.0f, 255.0f), clamp(proj_mean[1], 0.0f, 255.0f), clamp(z[1] + proj_mean[1], 0.0f, 255.0f));

            partition_rgb[is_flipped][0] = ETC_RGBRoundVecTo4Bit(partition_rgb[is_flipped][0]);
            partition_rgb[is_flipped][1] = ETC_RGBRoundVecTo4Bit(partition_rgb[is_flipped][1]);

            pathing_params.partition_indexes = &g_partition_indexes[is_flipped][0][0];
            err[is_flipped] += EvaluateErrorGeneric(ETC_EVALUATEDELTAERRORGENERIC, is_ypbpr, trans_pixel, partition_rgb[is_flipped][0], &pathing_params);
            pathing_params.partition_indexes = &g_partition_indexes[is_flipped][1][0];
            err[is_flipped] += EvaluateErrorGeneric(ETC_EVALUATEDELTAERRORGENERIC, is_ypbpr, trans_pixel, partition_rgb[is_flipped][1], &pathing_params);
        }
        params_partition_nodelta.is_flipped = err[0] < err[1] ? 0 : 1;

        best_error[ETC_ENC_MODE_NODELTA] = err[0] < err[1] ? err[0] : err[1];

        params_partition_nodelta.rgb[0] = partition_rgb[params_partition_nodelta.is_flipped][0];
        params_partition_nodelta.rgb[1] = partition_rgb[params_partition_nodelta.is_flipped][1];

        if (!found_mode || (best_error[ETC_ENC_MODE_NODELTA] < best_error[best_mode]))
        {
            ETC_GetOptimalIndexes(is_ypbpr, trans_pixel, params_partition_nodelta.rgb[0], &g_partition_indexes[params_partition_nodelta.is_flipped][0][0], &params_partition_nodelta.table[0], params_partition_nodelta.indexes);
            ETC_GetOptimalIndexes(is_ypbpr, trans_pixel, params_partition_nodelta.rgb[1], &g_partition_indexes[params_partition_nodelta.is_flipped][1][0], &params_partition_nodelta.table[1], params_partition_nodelta.indexes);

            found_mode = 1;
            best_mode = ETC_ENC_MODE_NODELTA;
        }
        err[0] = 0.0f;
        err[1] = 0.0f;
    }

    if (allowed_modes & ETC_MODE_DELTA)
    {
        for (is_flipped = 0; is_flipped < 2; is_flipped++)
        {
            float proj_mean[2] = {0.0f, 0.0f};
            float x[2] = {0.0f, 0.0f};
            float z[2] = {0.0f, 0.0f};

            for (i = 0; i < 8; i++)
            {
                ASSERT_RANGE(g_partition_indexes[is_flipped][0][i], 0, 16);
                ASSERT_RANGE(g_partition_indexes[is_flipped][1][i], 0, 16);

                x[0] += MEMBER(trans_pixel[g_partition_indexes[is_flipped][0][i]], X);
                x[0] -= MEMBER(trans_pixel[g_partition_indexes[is_flipped][0][i]], Y);
                z[0] += MEMBER(trans_pixel[g_partition_indexes[is_flipped][0][i]], Z);
                z[0] -= MEMBER(trans_pixel[g_partition_indexes[is_flipped][0][i]], Y);

                x[1] += MEMBER(trans_pixel[g_partition_indexes[is_flipped][1][i]], X);
                x[1] -= MEMBER(trans_pixel[g_partition_indexes[is_flipped][1][i]], Y);
                z[1] += MEMBER(trans_pixel[g_partition_indexes[is_flipped][1][i]], Z);
                z[1] -= MEMBER(trans_pixel[g_partition_indexes[is_flipped][1][i]], Y);
            }

            x[0] /= 8.0f;
            x[1] /= 8.0f;
            z[0] /= 8.0f;
            z[1] /= 8.0f;

            for (i = 0; i < 8; i++)
            {
                proj_mean[0] += dot(trans_pixel[g_partition_indexes[is_flipped][0][i]] - VFLOAT3(x[0], 0.0f, z[0]), VFLOAT3(0.57735f, 0.57735f, 0.57735f));
                proj_mean[1] += dot(trans_pixel[g_partition_indexes[is_flipped][1][i]] - VFLOAT3(x[1], 0.0f, z[1]), VFLOAT3(0.57735f, 0.57735f, 0.57735f));
            }

            proj_mean[0] /= 8.0f;
            proj_mean[1] /= 8.0f;
            proj_mean[0] *= 0.57735f;
            proj_mean[1] *= 0.57735f;

            partition_rgb[is_flipped][0] = UCHAR3(clamp(x[0] + proj_mean[0], 0.0f, 255.0f), clamp(proj_mean[0], 0.0f, 255.0f), clamp(z[0] + proj_mean[0], 0.0f, 255.0f));
            partition_rgb[is_flipped][1] = UCHAR3(clamp(x[1] + proj_mean[1], 0.0f, 255.0f), clamp(proj_mean[1], 0.0f, 255.0f), clamp(z[1] + proj_mean[1], 0.0f, 255.0f));

            partition_rgb[is_flipped][0] = ETC_RGBRoundVecTo5Bit(partition_rgb[is_flipped][0]);
            partition_rgb[is_flipped][1] = ETC_RGBRoundVecTo5Bit(partition_rgb[is_flipped][1]);

            pathing_params.partition_indexes = &g_partition_indexes[is_flipped][0][0];
            err[is_flipped] += EvaluateErrorGeneric(ETC_EVALUATEDELTAERRORGENERIC, is_ypbpr, trans_pixel, partition_rgb[is_flipped][0], &pathing_params);
            pathing_params.partition_indexes = &g_partition_indexes[is_flipped][1][0];
            err[is_flipped] += EvaluateErrorGeneric(ETC_EVALUATEDELTAERRORGENERIC, is_ypbpr, trans_pixel, partition_rgb[is_flipped][1], &pathing_params);
        }
        params_partition.is_flipped = err[0] < err[1] ? 0 : 1;

        params_partition.rgb[0] = partition_rgb[params_partition.is_flipped][0];
        params_partition.rgb[1] = partition_rgb[params_partition.is_flipped][1];

        is_delta = 0;
        int diff = (int)((MEMBER(params_partition.rgb[1], X)) >> 3) - (int)((MEMBER(params_partition.rgb[0], X) >> 3));
        if (diff < 4 && diff >= -4)
            is_delta++;
        diff = (int)((MEMBER(params_partition.rgb[1], Y)) >> 3) - (int)((MEMBER(params_partition.rgb[0], Y) >> 3));
        if (diff < 4 && diff >= -4)
            is_delta++;
        diff = (int)((MEMBER(params_partition.rgb[1], Z)) >> 3) - (int)((MEMBER(params_partition.rgb[0], Z) >> 3));
        if (diff < 4 && diff >= -4)
            is_delta++;

        if (is_delta == 3)
        {
            best_error[ETC_ENC_MODE_DELTA] = err[0] < err[1] ? err[0] : err[1];
            if (!found_mode || (best_error[ETC_ENC_MODE_DELTA] < best_error[best_mode]))
            {
                ETC_GetOptimalIndexes(is_ypbpr, trans_pixel, params_partition.rgb[0], &g_partition_indexes[params_partition.is_flipped][0][0], &params_partition.table[0], params_partition.indexes);
                ETC_GetOptimalIndexes(is_ypbpr, trans_pixel, params_partition.rgb[1], &g_partition_indexes[params_partition.is_flipped][1][0], &params_partition.table[1], params_partition.indexes);

                found_mode = 1;
                best_mode = ETC_ENC_MODE_DELTA;
            }
        }
    }
    if (is_etc2)
    {
        if (((best_error[best_mode] != 0.0f) || !found_mode) && (allowed_modes & (ETC_MODE_T | ETC_MODE_H)))
        {
            int set_indexes[2][16];
            int set_count[2];
            int best_error_flip;

            ETC_KMeansTHMode(trans_pixel, &set_indexes[0][0], &set_indexes[1][0], &set_count[0]);

            if (allowed_modes & ETC_MODE_T)
            {
                for (is_flipped = 0; is_flipped < 2; is_flipped++)
                {
                    float proj_mean[2] = {0.0f, 0.0f};
                    float x[2] = {0.0f, 0.0f};
                    float z[2] = {0.0f, 0.0f};

                    for (i = 0; i < set_count[is_flipped]; i++)
                    {
                        ASSERT_RANGE(set_indexes[is_flipped][i], 0, 16);
                        x[0] += MEMBER(trans_pixel[set_indexes[is_flipped][i]], X);
                        x[0] -= MEMBER(trans_pixel[set_indexes[is_flipped][i]], Y);
                        z[0] += MEMBER(trans_pixel[set_indexes[is_flipped][i]], Z);
                        z[0] -= MEMBER(trans_pixel[set_indexes[is_flipped][i]], Y);
                    }
                    for (i = 0; i < set_count[(is_flipped + 1) % 2]; i++)
                    {
                        ASSERT_RANGE(set_indexes[(is_flipped + 1) % 2][i], 0, 16);
                        x[1] += MEMBER(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]], X);
                        x[1] -= MEMBER(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]], Y);
                        z[1] += MEMBER(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]], Z);
                        z[1] -= MEMBER(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]], Y);
                    }

                    x[0] /= (float)(set_count[is_flipped] == 0 ? 1 : set_count[is_flipped]);
                    x[1] /= (float)(set_count[(is_flipped + 1) % 2] == 0 ? 1 : set_count[(is_flipped + 1) % 2]);
                    z[0] /= (float)(set_count[is_flipped] == 0 ? 1 : set_count[is_flipped]);
                    z[1] /= (float)(set_count[(is_flipped + 1) % 2] == 0 ? 1 : set_count[(is_flipped + 1) % 2]);

                    for (i = 0; i < set_count[is_flipped]; i++)
                        proj_mean[0] += dot(trans_pixel[set_indexes[is_flipped][i]] - VFLOAT3(x[0], 0.0f, z[0]), VFLOAT3(0.57735f, 0.57735f, 0.57735f));
                    for (i = 0; i < set_count[(is_flipped + 1) % 2]; i++)
                        proj_mean[1] += dot(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]] - VFLOAT3(x[1], 0.0f, z[1]), VFLOAT3(0.57735f, 0.57735f, 0.57735f));

                    proj_mean[0] /= (float)(set_count[is_flipped] == 0 ? 1 : set_count[is_flipped]);
                    proj_mean[1] /= (float)(set_count[(is_flipped + 1) % 2] == 0 ? 1 : set_count[(is_flipped + 1) % 2]);

                    proj_mean[0] *= 0.57735f;
                    proj_mean[1] *= 0.57735f;

                    partition_rgb[is_flipped][0] = UCHAR3(clamp(x[0] + proj_mean[0], 0.0f, 255.0f), clamp(proj_mean[0], 0.0f, 255.0f), clamp(z[0] + proj_mean[0], 0.0f, 255.0f));
                    partition_rgb[is_flipped][1] = UCHAR3(clamp(x[1] + proj_mean[1], 0.0f, 255.0f), clamp(proj_mean[1], 0.0f, 255.0f), clamp(z[1] + proj_mean[1], 0.0f, 255.0f));

                    partition_rgb[is_flipped][0] = ETC_RGBRoundVecTo4Bit(partition_rgb[is_flipped][0]);
                    partition_rgb[is_flipped][1] = ETC_RGBRoundVecTo4Bit(partition_rgb[is_flipped][1]);

                    params_th.rgb[0] = partition_rgb[is_flipped][0];
                    params_th.rgb[1] = partition_rgb[is_flipped][1];

                    err[is_flipped] = ETC_GetOptimalTIndexes(is_ypbpr, trans_pixel, params_th.rgb[0], params_th.rgb[1], &params_th.indexes[0], &params_th.table);
                }

                best_error[ETC_ENC_MODE_T] = err[0] < err[1] ? err[0] : err[1];
                best_error_flip = err[0] < err[1] ? 0 : 1;

                params_th.rgb[0] = partition_rgb[best_error_flip][0];
                params_th.rgb[1] = partition_rgb[best_error_flip][1];
                ETC_GetOptimalTIndexes(is_ypbpr, trans_pixel, params_th.rgb[0], params_th.rgb[1], &params_th.indexes[0], &params_th.table);

                if (!found_mode || (best_error[ETC_ENC_MODE_T] < best_error[best_mode]))
                {
                    found_mode = 1;
                    best_mode = ETC_ENC_MODE_T;
                }
            }
            if (allowed_modes & ETC_MODE_H)
            {
                int best_table[2];
                etc_th_mode_params_t params_th_local;

                for (is_flipped = 0; is_flipped < 2; is_flipped++)
                {
                    float proj_mean[2] = {0.0f, 0.0f};
                    float x[2] = {0.0f, 0.0f};
                    float z[2] = {0.0f, 0.0f};
                    float local_best_error = MAX_INIT_ERROR;

                    for (i = 0; i < set_count[is_flipped]; i++)
                    {
                        ASSERT_RANGE(set_indexes[is_flipped][i], 0, 16);
                        x[0] += MEMBER(trans_pixel[set_indexes[is_flipped][i]], X);
                        x[0] -= MEMBER(trans_pixel[set_indexes[is_flipped][i]], Y);
                        z[0] += MEMBER(trans_pixel[set_indexes[is_flipped][i]], Z);
                        z[0] -= MEMBER(trans_pixel[set_indexes[is_flipped][i]], Y);
                    }
                    for (i = 0; i < set_count[(is_flipped + 1) % 2]; i++)
                    {
                        ASSERT_RANGE(set_indexes[(is_flipped + 1) % 2][i], 0, 16);
                        x[1] += MEMBER(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]], X);
                        x[1] -= MEMBER(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]], Y);
                        z[1] += MEMBER(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]], Z);
                        z[1] -= MEMBER(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]], Y);
                    }

                    x[0] /= (float)(set_count[is_flipped] == 0 ? 1 : set_count[is_flipped]);
                    x[1] /= (float)(set_count[(is_flipped + 1) % 2] == 0 ? 1 : set_count[(is_flipped + 1) % 2]);
                    z[0] /= (float)(set_count[is_flipped] == 0 ? 1 : set_count[is_flipped]);
                    z[1] /= (float)(set_count[(is_flipped + 1) % 2] == 0 ? 1 : set_count[(is_flipped + 1) % 2]);

                    for (i = 0; i < set_count[is_flipped]; i++)
                        proj_mean[0] += dot(trans_pixel[set_indexes[is_flipped][i]] - VFLOAT3(x[0], 0.0f, z[0]), VFLOAT3(0.57735f, 0.57735f, 0.57735f));
                    for (i = 0; i < set_count[(is_flipped + 1) % 2]; i++)
                        proj_mean[1] += dot(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]] - VFLOAT3(x[1], 0.0f, z[1]), VFLOAT3(0.57735f, 0.57735f, 0.57735f));

                    proj_mean[0] /= (float)(set_count[is_flipped] == 0 ? 1 : set_count[is_flipped]);
                    proj_mean[1] /= (float)(set_count[(is_flipped + 1) % 2] == 0 ? 1 : set_count[(is_flipped + 1) % 2]);

                    proj_mean[0] *= 0.57735f;
                    proj_mean[1] *= 0.57735f;

                    partition_rgb[is_flipped][0] = UCHAR3(clamp(x[0] + proj_mean[0], 0.0f, 255.0f), clamp(proj_mean[0], 0.0f, 255.0f), clamp(z[0] + proj_mean[0], 0.0f, 255.0f));
                    partition_rgb[is_flipped][1] = UCHAR3(clamp(x[1] + proj_mean[1], 0.0f, 255.0f), clamp(proj_mean[1], 0.0f, 255.0f), clamp(z[1] + proj_mean[1], 0.0f, 255.0f));

                    partition_rgb[is_flipped][0] = ETC_RGBRoundVecTo4Bit(partition_rgb[is_flipped][0]);
                    partition_rgb[is_flipped][1] = ETC_RGBRoundVecTo4Bit(partition_rgb[is_flipped][1]);

                    params_th_local.rgb[0] = partition_rgb[is_flipped][0];
                    params_th_local.rgb[1] = partition_rgb[is_flipped][1];

                    for (table = 0; table < 8; table++)
                    {
                        float local_err = ETC_GetOptimalHIndexes(is_ypbpr, trans_pixel, params_th_local.rgb[0], params_th_local.rgb[1], &params_th_local.indexes[0], table);
                        if (local_err < local_best_error)
                        {
                            best_table[is_flipped] = table;
                            err[is_flipped] = local_err;
                            local_best_error = local_err;
                        }
                    }
                }

                best_error[ETC_ENC_MODE_H] = err[0] < err[1] ? err[0] : err[1];
                best_error_flip = err[0] < err[1] ? 0 : 1;

                params_th_local.table = best_table[best_error_flip];
                params_th_local.rgb[0] = partition_rgb[best_error_flip][0];
                params_th_local.rgb[1] = partition_rgb[best_error_flip][1];
                ETC_GetOptimalHIndexes(is_ypbpr, trans_pixel, params_th_local.rgb[0], params_th_local.rgb[1], &params_th_local.indexes[0], params_th_local.table);

                if (!found_mode || (best_error[ETC_ENC_MODE_H] < best_error[best_mode]))
                {
                    found_mode = 1;
                    best_mode = ETC_ENC_MODE_H;
                    params_th = params_th_local;
                }
            }
        }
        if (((best_error[best_mode] != 0.0f) || !found_mode) && (allowed_modes & ETC_MODE_PLANAR))
        {
            // Planar mode: always check this because it's so cheap to compute

            float3 points[3];
            int3 points_i32[3];
            float index_best_dist[3];
            int best_twiddle[3][3];
            int index;
            int twiddle0;
            int twiddle1;
            int twiddle2;
            const float coeff[3][16] =
            {
                {23.0f, 17.0f, 11.0f, 5.0f, 17.0f, 11.0f, 5.0f, -1.0f, 11.0f, 5.0f, -1.0f, -7.0f, 5.0f, -1.0f, -7.0f, -13.0f},
                {-1.0f, 9.0f, 19.0f, 29.0f, -7.0f, 3.0f, 13.0f, 23.0f, -13.0f, -3.0f, 7.0f, 17.0f, -19.0f, -9.0f, 1.0f, 11.0f},
                {-1.0f, -7.0f, -13.0f, -19.0f, 9.0f, 3.0f, -3.0f, -9.0f, 19.0f, 13.0f, 7.0f, 1.0f, 29.0f, 23.0f, 17.0f, 11.0f}
            };
            DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
            points[0] = VFLOAT3(0.0f, 0.0f, 0.0f);
            points[1] = VFLOAT3(0.0f, 0.0f, 0.0f);
            points[2] = VFLOAT3(0.0f, 0.0f, 0.0f);
            // TODO: this isn't trivial for the YCBCR case, just minimise in RGB space for now
            if (is_ypbpr)
                for (i = 0; i < 16; i++)
                    trans_pixel[i] = clamp(ETC_ConvertToRGBf3(trans_pixel[i]), 0.0f, 255.0f);
            for (j = 0; j < 16; j++)
            {
                MEMBER(points[0], X) += coeff[0][j] * MEMBER(trans_pixel[j], X);
                MEMBER(points[1], X) += coeff[1][j] * MEMBER(trans_pixel[j], X);
                MEMBER(points[2], X) += coeff[2][j] * MEMBER(trans_pixel[j], X);

                MEMBER(points[0], Y) += coeff[0][j] * MEMBER(trans_pixel[j], Y);
                MEMBER(points[1], Y) += coeff[1][j] * MEMBER(trans_pixel[j], Y);
                MEMBER(points[2], Y) += coeff[2][j] * MEMBER(trans_pixel[j], Y);

                MEMBER(points[0], Z) += coeff[0][j] * MEMBER(trans_pixel[j], Z);
                MEMBER(points[1], Z) += coeff[1][j] * MEMBER(trans_pixel[j], Z);
                MEMBER(points[2], Z) += coeff[2][j] * MEMBER(trans_pixel[j], Z);
            }
            points[0] = points[0] * (1.0f / 80.0f);
            points[1] = points[1] * (1.0f / 80.0f);
            points[2] = points[2] * (1.0f / 80.0f);

            points[0] = clamp(points[0], 0.0f, 255.0f);
            points[1] = clamp(points[1], 0.0f, 255.0f);
            points[2] = clamp(points[2], 0.0f, 255.0f);

            points_i32[0] = INT3(ETC_RGBRoundTo6Bit((uchar)MEMBER(points[0], X)), ETC_RGBRoundTo7Bit((uchar)MEMBER(points[0], Y)), ETC_RGBRoundTo6Bit((uchar)MEMBER(points[0], Z)));
            points_i32[1] = INT3(ETC_RGBRoundTo6Bit((uchar)MEMBER(points[1], X)), ETC_RGBRoundTo7Bit((uchar)MEMBER(points[1], Y)), ETC_RGBRoundTo6Bit((uchar)MEMBER(points[1], Z)));
            points_i32[2] = INT3(ETC_RGBRoundTo6Bit((uchar)MEMBER(points[2], X)), ETC_RGBRoundTo7Bit((uchar)MEMBER(points[2], Y)), ETC_RGBRoundTo6Bit((uchar)MEMBER(points[2], Z)));
            for (index = 0; index < 3; index++)
                index_best_dist[index] = MAX_INIT_ERROR;

            for (twiddle0 = -1; twiddle0 <= 1; twiddle0++)
            {
                for (twiddle1 = -1; twiddle1 <= 1; twiddle1++)
                {
                    for (twiddle2 = -1; twiddle2 <= 1; twiddle2++)
                    {
                        int ppoints[3][3];
                        float comp_err[3];
                        int comb;

                        comb =  (MEMBER(points_i32[0], X) + twiddle0 * 4) | (MEMBER(points_i32[1], X) + twiddle1 * 4) | (MEMBER(points_i32[2], X) + twiddle2 * 4) |
                            (MEMBER(points_i32[0], Y) + twiddle0 * 2) | (MEMBER(points_i32[1], Y) + twiddle1 * 2) | (MEMBER(points_i32[2], Y) + twiddle2 * 2) |
                            (MEMBER(points_i32[0], Z) + twiddle0 * 4) | (MEMBER(points_i32[1], Z) + twiddle1 * 4) | (MEMBER(points_i32[2], Z) + twiddle2 * 4);

                        // trick: this tests if any of the values has negative sign or is >255, halving the number of comparisons needed
                        if (comb & 0xFFFFFF00)
                            continue;

                        ppoints[0][0] = ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[0], X) + twiddle0 * 4));
                        ppoints[0][1] = ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[1], X) + twiddle1 * 4));
                        ppoints[0][2] = ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[2], X) + twiddle2 * 4));

                        ppoints[1][0] = ETC_RGBRoundTo7Bit(UCHAR(MEMBER(points_i32[0], Y) + twiddle0 * 2));
                        ppoints[1][1] = ETC_RGBRoundTo7Bit(UCHAR(MEMBER(points_i32[1], Y) + twiddle1 * 2));
                        ppoints[1][2] = ETC_RGBRoundTo7Bit(UCHAR(MEMBER(points_i32[2], Y) + twiddle2 * 2));

                        ppoints[2][0] = ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[0], Z) + twiddle0 * 4));
                        ppoints[2][1] = ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[1], Z) + twiddle1 * 4));
                        ppoints[2][2] = ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[2], Z) + twiddle2 * 4));

                        comp_err[0] = 0.0f;
                        comp_err[1] = 0.0f;
                        comp_err[2] = 0.0f;

                        for (j = 0; j < 4; j++) // v
                        {
                            for (i = 0; i < 4; i++) // u
                            {
                                float3 v;

                                MEMBER(v, X) = (float)((i * (ppoints[0][1] - ppoints[0][0]) + j * (ppoints[0][2] - ppoints[0][0]) + 4 * (ppoints[0][0]) + 2) >> 2);
                                MEMBER(v, Y) = (float)((i * (ppoints[1][1] - ppoints[1][0]) + j * (ppoints[1][2] - ppoints[1][0]) + 4 * (ppoints[1][0]) + 2) >> 2);
                                MEMBER(v, Z) = (float)((i * (ppoints[2][1] - ppoints[2][0]) + j * (ppoints[2][2] - ppoints[2][0]) + 4 * (ppoints[2][0]) + 2) >> 2);

                                v = clamp(v, VFLOAT3(0.0f, 0.0f, 0.0f), VFLOAT3(255.0f, 255.0f, 255.0f));
                                v = v - trans_pixel[j*4 + i];

                                comp_err[0] += MEMBER(v, X) * MEMBER(v, X);
                                comp_err[1] += MEMBER(v, Y) * MEMBER(v, Y);
                                comp_err[2] += MEMBER(v, Z) * MEMBER(v, Z);
                            }
                        }
                        for (index = 0; index < 3; index++)
                        {
                            if (comp_err[index] < index_best_dist[index])
                            {
                                int scale = (index == 1 ? 2 : 4);
                                best_twiddle[index][0] = twiddle0 * scale;
                                best_twiddle[index][1] = twiddle1 * scale;
                                best_twiddle[index][2] = twiddle2 * scale;
                                index_best_dist[index] = comp_err[index];
                            }
                        }
                    }
                }
            }

            best_error[ETC_ENC_MODE_PLANAR] = index_best_dist[0] + index_best_dist[1] + index_best_dist[2];

            if (!found_mode || (best_error[ETC_ENC_MODE_PLANAR] < best_error[best_mode]))
            {
                found_mode = 1;
                best_mode = ETC_ENC_MODE_PLANAR;

                params_planar.rgb[0] = UCHAR3(ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[0], X) + best_twiddle[0][0])), ETC_RGBRoundTo7Bit(UCHAR(MEMBER(points_i32[0], Y) + best_twiddle[1][0])), ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[0], Z) + best_twiddle[2][0])));
                params_planar.rgb[1] = UCHAR3(ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[1], X) + best_twiddle[0][1])), ETC_RGBRoundTo7Bit(UCHAR(MEMBER(points_i32[1], Y) + best_twiddle[1][1])), ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[1], Z) + best_twiddle[2][1])));
                params_planar.rgb[2] = UCHAR3(ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[2], X) + best_twiddle[0][2])), ETC_RGBRoundTo7Bit(UCHAR(MEMBER(points_i32[2], Y) + best_twiddle[1][2])), ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[2], Z) + best_twiddle[2][2])));
            }
        }
    }
    //printf("err: %i: %f %f %f %f %f\n", best_mode, best_error[0], best_error[1], best_error[2], best_error[3], best_error[4]);

    if (best_mode == ETC_ENC_MODE_DELTA)
    {
        int3 diff;

        MEMBER(diff, X) = (MEMBER(params_partition.rgb[1], X) >> 3) - (MEMBER(params_partition.rgb[0], X) >> 3);
        MEMBER(diff, Y) = (MEMBER(params_partition.rgb[1], Y) >> 3) - (MEMBER(params_partition.rgb[0], Y) >> 3);
        MEMBER(diff, Z) = (MEMBER(params_partition.rgb[1], Z) >> 3) - (MEMBER(params_partition.rgb[0], Z) >> 3);

        ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], X) >> 3, 27, 5);
        ETC_WriteBits(local_block, MEMBER(diff, X) >> 0, 24, 3);
        ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], Y) >> 3, 19, 5);
        ETC_WriteBits(local_block, MEMBER(diff, Y) >> 0, 16, 3);
        ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], Z) >> 3, 11, 5);
        ETC_WriteBits(local_block, MEMBER(diff, Z) >> 0,  8, 3);
        ETC_WriteBits(local_block, 1, 1, 1); // diff bit

        ETC_WriteBits(local_block, params_partition.table[0], 5, 3); // table codeword 1
        ETC_WriteBits(local_block, params_partition.table[1], 2, 3); // table codeword 2
        ETC_WriteBits(local_block, params_partition.is_flipped, 0, 1); // flip bit

        for (i = 0; i < 16; i++)
        {
            int index = (i%4)*4 + i/4;

            int idx = params_partition.indexes[i];

            ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);
            ETC_WriteBits(local_block, idx & 1, 32 + index, 1);

        }
        ETC_PackBlockSwapOrder(block, local_block);
    }
    else if (best_mode == ETC_ENC_MODE_NODELTA)
    {
        ETC_WriteBits(local_block, MEMBER(params_partition_nodelta.rgb[0], X) >> 4, 28, 4);
        ETC_WriteBits(local_block, MEMBER(params_partition_nodelta.rgb[1], X) >> 4, 24, 4);
        ETC_WriteBits(local_block, MEMBER(params_partition_nodelta.rgb[0], Y) >> 4, 20, 4);
        ETC_WriteBits(local_block, MEMBER(params_partition_nodelta.rgb[1], Y) >> 4, 16, 4);
        ETC_WriteBits(local_block, MEMBER(params_partition_nodelta.rgb[0], Z) >> 4, 12, 4);
        ETC_WriteBits(local_block, MEMBER(params_partition_nodelta.rgb[1], Z) >> 4,  8, 4);
        ETC_WriteBits(local_block, 0, 1, 1); // diff bit

        ETC_WriteBits(local_block, params_partition_nodelta.table[0], 5, 3); // table codeword 1
        ETC_WriteBits(local_block, params_partition_nodelta.table[1], 2, 3); // table codeword 2
        ETC_WriteBits(local_block, params_partition_nodelta.is_flipped, 0, 1); // flip bit

        for (i = 0; i < 16; i++)
        {
            int index = (i%4)*4 + i/4;

            int idx = params_partition_nodelta.indexes[i];

            ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);
            ETC_WriteBits(local_block, idx & 1, 32 + index, 1);

        }
        ETC_PackBlockSwapOrder(block, local_block);
    }
    else if (best_mode == ETC_ENC_MODE_T)
    {
        int min_rd = -4 + ((MEMBER(params_th.rgb[0], X) >> 4) & 3);
        int max_rd = ((MEMBER(params_th.rgb[0], X) >> 4) & 3);
        int min_r = (MEMBER(params_th.rgb[0], X) >> 6) & 3;
        int max_r = 28 + min_r;
        uchar r;
        uchar rd;

        if (min_rd + min_r < 0)
        {
            r = UCHAR(min_r);
            rd = UCHAR(min_rd);
        }
        else
        {
            r = UCHAR(max_r);
            rd = UCHAR(max_rd);
        }
        //printf("err: %i: params_th.rgb[0|2] %3u %3u %3u, %3u %3u %3u, table: %i\n", best_mode, MEMBER(params_th.rgb[0], X), MEMBER(params_th.rgb[0], Y), MEMBER(params_th.rgb[0], Z), MEMBER(params_th.rgb[1], X), MEMBER(params_th.rgb[1], Y), MEMBER(params_th.rgb[1], Z), params_th.table);

        //printf("min_rd, min_r, r, rd: %i %i %i %i\n", min_rd, min_r, r, rd);
        ETC_WriteBits(local_block, r, 27, 5);
        ETC_WriteBits(local_block, rd, 24, 3);
        ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Y) >> 4, 20, 4);
        ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Z) >> 4, 16, 4);
        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], X) >> 4, 12, 4);
        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Y) >> 4,  8, 4);
        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Z) >> 4,  4, 4);

        ETC_WriteBits(local_block, (params_th.table >> 1) & 3, 2, 2);
        ETC_WriteBits(local_block, 1, 1, 1); // diff bit
        ETC_WriteBits(local_block, params_th.table & 1, 0, 1); // flip bit

        for (i = 0; i < 16; i++)
        {
            int index = (i % 4) * 4 + i / 4;

            int idx = params_th.indexes[i];

            //printf("%i: (%i)\n", i, params_th.indexes[i]);

            ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);
            ETC_WriteBits(local_block, idx & 1, 32 + index, 1);

        }
        ETC_PackBlockSwapOrder(block, local_block);
        //printf("0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X\n", block[0], block[1], block[2], block[3], block[4], block[5], block[6], block[7]);
    }
    else if (best_mode == ETC_ENC_MODE_H)
    {
        int min_gd = -4 + ((MEMBER(params_th.rgb[0], Z) >> 5) & 3);
        int max_gd = ((MEMBER(params_th.rgb[0], Z) >> 5) & 3);
        int min_g = ((MEMBER(params_th.rgb[0], Z) >> 7) & 1) | (((MEMBER(params_th.rgb[0], Y) >> 4) & 1) << 1);
        int max_g = 28 + min_g;
        uchar g;
        uchar gd;
        int rd;
        if (min_gd + min_g < 0)
        {
            g = UCHAR(min_g);
            gd = UCHAR(min_gd);
        }
        else
        {
            g = UCHAR(max_g);
            gd = UCHAR(max_gd);
        }

        rd = MEMBER(params_th.rgb[0], Y) >> 5;
        if (rd >= 4)
            rd = -4 + (rd & 3);

        if ((int)(MEMBER(params_th.rgb[0], X) >> 4) + rd < 0)
            ETC_WriteBits(local_block, 1, 31, 1);
        else
            ETC_WriteBits(local_block, 0, 31, 1);
        ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], X) >> 4, 27, 4);
        ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Y) >> 5, 24, 3);
        ETC_WriteBits(local_block, g, 19, 5);
        ETC_WriteBits(local_block, gd, 16, 3);
        ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Z) >> 4, 15, 1);
        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], X) >> 4, 11, 4);
        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Y) >> 4,  7, 4);
        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Z) >> 4,  3, 4);

        ETC_WriteBits(local_block, (params_th.table >> 2) & 1, 2, 1);
        ETC_WriteBits(local_block, 1, 1, 1); // diff bit
        ETC_WriteBits(local_block, (params_th.table >> 1) & 1 & 1, 0, 1); // flip bit

        for (i = 0; i < 16; i++)
        {
            int index = (i % 4) * 4 + i / 4;

            int idx = params_th.indexes[i];

            ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);
            ETC_WriteBits(local_block, idx & 1, 32 + index, 1);

        }
        ETC_PackBlockSwapOrder(block, local_block);
    }
    else if (best_mode == ETC_ENC_MODE_PLANAR)
    {
        int r, g, b;
        int rd, gd, bd;
        int min_bd;
        int max_bd;
        int min_b;
        int max_b;
        MEMBER(params_planar.rgb[0], X) >>= 2;
        MEMBER(params_planar.rgb[0], Y) >>= 1;
        MEMBER(params_planar.rgb[0], Z) >>= 2;

        MEMBER(params_planar.rgb[1], X) >>= 2;
        MEMBER(params_planar.rgb[1], Y) >>= 1;
        MEMBER(params_planar.rgb[1], Z) >>= 2;

        MEMBER(params_planar.rgb[2], X) >>= 2;
        MEMBER(params_planar.rgb[2], Y) >>= 1;
        MEMBER(params_planar.rgb[2], Z) >>= 2;

        ETC_WriteBits(local_block, MEMBER(params_planar.rgb[2], Z), 32, 6);
        ETC_WriteBits(local_block, MEMBER(params_planar.rgb[2], Y), 38, 7);
        ETC_WriteBits(local_block, MEMBER(params_planar.rgb[2], X), 45, 6);
        ETC_WriteBits(local_block, MEMBER(params_planar.rgb[1], Z), 51, 6);
        ETC_WriteBits(local_block, MEMBER(params_planar.rgb[1], Y), 57, 7);

        ETC_WriteBits(local_block, (MEMBER(params_planar.rgb[1], X)) & 1, 0, 1);
        ETC_WriteBits(local_block, 1, 1, 1);
        ETC_WriteBits(local_block, (MEMBER(params_planar.rgb[1], X) >> 1) & 31, 2, 5);
        ETC_WriteBits(local_block, MEMBER(params_planar.rgb[0], Z) & 7, 7, 3);
        ETC_WriteBits(local_block, (MEMBER(params_planar.rgb[0], Z) >> 3) & 7, 11, 2);
        ETC_WriteBits(local_block, (MEMBER(params_planar.rgb[0], Z) >> 5) & 1, 16, 1);
        ETC_WriteBits(local_block, MEMBER(params_planar.rgb[0], Y) & 63, 17, 6);
        ETC_WriteBits(local_block, (MEMBER(params_planar.rgb[0], Y) >> 6) & 1, 24, 1);
        ETC_WriteBits(local_block, MEMBER(params_planar.rgb[0], X), 25, 6);

        r = (MEMBER(params_planar.rgb[0], X) >> 2) & 63;
        rd = (MEMBER(params_planar.rgb[0], Y) >> 6) | ((MEMBER(params_planar.rgb[0], X) & 3) << 1);
        g = (MEMBER(params_planar.rgb[0], Y) >> 2) & 15;
        gd = (MEMBER(params_planar.rgb[0], Z) >> 5) | ((MEMBER(params_planar.rgb[0], Y) & 3) << 1);
        b = (MEMBER(params_planar.rgb[0], Z) >> 3) & 3;
        bd = (MEMBER(params_planar.rgb[0], Z) >> 1) & 3;

        if (rd >= 4)
            rd = -4 + (rd & 3);
        if (gd >= 4)
            gd = -4 + (gd & 3);
        if (bd >= 4)
            bd = -4 + (bd & 3);

        if (r + rd < 0)
            ETC_WriteBits(local_block, 1, 31, 1);
        else
            ETC_WriteBits(local_block, 0, 31, 1);

        if (g + gd < 0)
            ETC_WriteBits(local_block, 1, 23, 1);
        else
            ETC_WriteBits(local_block, 0, 23, 1);

        min_bd = -4 + bd;
        max_bd = bd;
        min_b = b;
        max_b = 28 + min_b;

        if (min_b + min_bd < 0)
        {
            ETC_WriteBits(local_block, min_bd, 8, 3);
            ETC_WriteBits(local_block, min_b, 11, 5);
        }
        else
        {
            ETC_WriteBits(local_block, max_bd, 8, 3);
            ETC_WriteBits(local_block, max_b, 11, 5);
        }
        ETC_PackBlockSwapOrder(block, local_block);
    }
}

void ETC_EncodeRGBQuality(
    int quality,
    int allowed_modes,
    float error_target,
    int refine_search,
    int is_etc2,
    int is_ypbpr,
    float4 *pixel,
    __global uchar *block,
    int block_x,
    int block_y)
{
    int i, j, table, n;
    float3 trans_pixel[16];
    int is_delta;
    int is_flipped;
    float best_dist[2];
    etc_sample_t sample_list[SAMPLE_LIST_SIZE0][SAMPLE_LIST_SIZE1][SAMPLE_LIST_SIZE2];
    int flipped;
    int partition;
    int is_best_delta = 0;
    float best_total_error = MAX_INIT_ERROR;
    int enc_mode;
    etc_partition_mode_params_t params_partition;
    etc_th_mode_params_t params_th;
    etc_planar_mode_params_t params_planar;
    etc_pathing_params_t pathing_params;
    uchar local_block[8];
    int step = 1;
    float3 projected_mins[2][2]; // delta/non-delta, flipped, partition
    float3 projected_maxs[2][2];

    //if (quality == CODEC_QUALITY_NORMAL)
        //step = 1;

    DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
    for (i = 0; i < 16; i++)
    {
        MEMBER(trans_pixel[i], X) = MEMBER(pixel[i], X);
        MEMBER(trans_pixel[i], Y) = MEMBER(pixel[i], Y);
        MEMBER(trans_pixel[i], Z) = MEMBER(pixel[i], Z);
    }
    DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));

    for (flipped = 0; flipped < 2; flipped++)
    {
        for (partition = 0; partition < 2; partition++)
        {
            float3 mean = VFLOAT3(0.0f, 0.0f, 0.0f);
            float mins_maxs_dist[2];
            
            for (i = 0; i < 8; i++)
                mean = mean + trans_pixel[g_partition_indexes[flipped][partition][i]];

            mean = mean / 8.0f;
            
            mins_maxs_dist[0] = dot(trans_pixel[g_partition_indexes[flipped][partition][0]] - mean, VFLOAT3(0.57735f, 0.57735f, 0.57735f));
            mins_maxs_dist[1] = mins_maxs_dist[0];
            
            for (i = 1; i < 8; i++)
            {
                float dist = dot(trans_pixel[g_partition_indexes[flipped][partition][i]] - mean, VFLOAT3(0.57735f, 0.57735f, 0.57735f));

                if (dist < mins_maxs_dist[0])
                    mins_maxs_dist[0] = dist;
                if (dist > mins_maxs_dist[1])
                    mins_maxs_dist[1] = dist;
            }
            projected_mins[flipped][partition] = mean + VFLOAT3(0.57735f, 0.57735f, 0.57735f) * mins_maxs_dist[0];
            projected_maxs[flipped][partition] = mean + VFLOAT3(0.57735f, 0.57735f, 0.57735f) * mins_maxs_dist[1];
        }
    }
    if (is_ypbpr)
        for (i = 0; i < 16; i++)
            trans_pixel[i] = ETC_ConvertToYPBPRf3(trans_pixel[i]);
    DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
    if (allowed_modes & ETC_MODE_DELTA)
    {
        float3 mean[2][2];
        uchar3 mean_quant[2][2];
        int min_index[2][2];
        int max_index[2][2];
        float fixed_err = MAX_INIT_ERROR;
        uchar3 best_positions[2];
        int best_flipped = 0;
        int found_fixed = 0;
        uchar3 proj_mins;
        uchar3 proj_maxs;
#if 1
        if (quality >= CODEC_QUALITY_NORMAL) // redundant, quality is always normal or better in this function
        {
            int max_distance;

            if (quality == CODEC_QUALITY_BEST)
                max_distance = 255;
            else if (quality == CODEC_QUALITY_HIGH)
                max_distance = 8;
            else 
                max_distance = 1;

            for (flipped = 0; flipped < 2; flipped++)
            {
                for (partition = 0; partition < 2; partition++)
                {
                    int distance = 0;
                    mean[flipped][partition] = VFLOAT3(0.0f, 0.0f, 0.0f);
                    for (i = 0; i < 8; i++)
                    {
                        mean[flipped][partition] = mean[flipped][partition] + trans_pixel[g_partition_indexes[flipped][partition][i]];
                    }
                    mean[flipped][partition] = mean[flipped][partition] / 8.0f;

                    MEMBER(mean_quant[flipped][partition], X) = UCHAR(MEMBER(mean[flipped][partition], X)) >> 3;
                    MEMBER(mean_quant[flipped][partition], Y) = UCHAR(MEMBER(mean[flipped][partition], Y)) >> 3;
                    MEMBER(mean_quant[flipped][partition], Z) = UCHAR(MEMBER(mean[flipped][partition], Z)) >> 3;

                    min_index[flipped][partition] = 0;
                    max_index[flipped][partition] = 0;

                    while ( ((int)MEMBER(mean_quant[flipped][partition], X) + min_index[flipped][partition] > 0) &&
                            ((int)MEMBER(mean_quant[flipped][partition], Y) + min_index[flipped][partition] > 0) &&
                            ((int)MEMBER(mean_quant[flipped][partition], Z) + min_index[flipped][partition] > 0))
                    {
                        min_index[flipped][partition]--;
                        distance++;
                        if (distance > max_distance)
                            break;
                    }
                    distance = 0;
                    while ( ((int)MEMBER(mean_quant[flipped][partition], X) + max_index[flipped][partition] < 31) &&
                            ((int)MEMBER(mean_quant[flipped][partition], Y) + max_index[flipped][partition] < 31) &&
                            ((int)MEMBER(mean_quant[flipped][partition], Z) + max_index[flipped][partition] < 31))
                    {
                        max_index[flipped][partition]++;
                        distance++;
                        if (distance > max_distance)
                            break;
                    }
                }
            }
            if (DEBUG_BLOCK)
            {
                for (i = 0; i < 2; i++)
                    for (j = 0; j < 2; j++)
                printf("indexes: [%i:%i] %3u %3u %3u\n", min_index[i][j], max_index[i][j], mean_quant[i][j].v[0], mean_quant[i][j].v[1], mean_quant[i][j].v[2]);
            }
            for (flipped = 0; flipped < 2; flipped++)
            {
                int ip0;
                int ip1;
                for (ip0 = min_index[flipped][0]; ip0 <= max_index[flipped][0]; ip0++)
                {
                    uchar3 l0_quant;

                    MEMBER(l0_quant, X) = UCHAR(MEMBER(mean_quant[flipped][0], X) + ip0);
                    MEMBER(l0_quant, Y) = UCHAR(MEMBER(mean_quant[flipped][0], Y) + ip0);
                    MEMBER(l0_quant, Z) = UCHAR(MEMBER(mean_quant[flipped][0], Z) + ip0);

                    for (ip1 = min_index[flipped][1]; ip1 <= max_index[flipped][1]; ip1++)
                    {
                        uchar3 l1_quant;
                        int dist[3];
                        float local_error;

                        MEMBER(l1_quant, X) = UCHAR(MEMBER(mean_quant[flipped][1], X) + ip1);
                        MEMBER(l1_quant, Y) = UCHAR(MEMBER(mean_quant[flipped][1], Y) + ip1);
                        MEMBER(l1_quant, Z) = UCHAR(MEMBER(mean_quant[flipped][1], Z) + ip1);

                        dist[0] = (int)MEMBER(l1_quant, X) - (int)MEMBER(l0_quant, X);
                        dist[1] = (int)MEMBER(l1_quant, Y) - (int)MEMBER(l0_quant, Y);
                        dist[2] = (int)MEMBER(l1_quant, Z) - (int)MEMBER(l0_quant, Z);

                        if ((dist[0] < -4 || dist[0] > 3) || 
                            (dist[1] < -4 || dist[1] > 3) || 
                            (dist[2] < -4 || dist[2] > 3))
                            continue;

                        local_error = ETC_EvaluateError(is_ypbpr, trans_pixel, ETC_RGBExpandVecTo5Bit(l0_quant), &g_partition_indexes[flipped][0][0]);
                        local_error += ETC_EvaluateError(is_ypbpr, trans_pixel, ETC_RGBExpandVecTo5Bit(l1_quant), &g_partition_indexes[flipped][1][0]);

                        if (local_error < fixed_err)
                        {
                            fixed_err = local_error;
                            best_positions[0] = l0_quant;
                            best_positions[1] = l1_quant;
                            best_flipped = flipped;
                            found_fixed = 1;
                        }
                    }
                }
            }
            if (found_fixed)
            {
                uchar3 best_pos[2];
                float combined_err = 0.0f;

                best_pos[0] = best_positions[0];
                best_pos[1] = best_positions[1];

                for (partition = 0; partition < 2; partition++)
                {
                    int neighbourhood_width = (quality == CODEC_QUALITY_BEST ? 3 : 1);
                    float best_err = MAX_INIT_ERROR;
                    int x;
                    int y;
                    int z;
                    int min_x = MEMBER(best_positions[partition], X) > (neighbourhood_width - 1) ? MEMBER(best_positions[partition], X) - neighbourhood_width : 0;
                    int min_y = MEMBER(best_positions[partition], Y) > (neighbourhood_width - 1) ? MEMBER(best_positions[partition], Y) - neighbourhood_width : 0;
                    int min_z = MEMBER(best_positions[partition], Z) > (neighbourhood_width - 1) ? MEMBER(best_positions[partition], Z) - neighbourhood_width : 0;
                    int max_x = MEMBER(best_positions[partition], X) < (31 - neighbourhood_width) ? MEMBER(best_positions[partition], X) + neighbourhood_width : 31;
                    int max_y = MEMBER(best_positions[partition], Y) < (31 - neighbourhood_width) ? MEMBER(best_positions[partition], Y) + neighbourhood_width : 31;
                    int max_z = MEMBER(best_positions[partition], Z) < (31 - neighbourhood_width) ? MEMBER(best_positions[partition], Z) + neighbourhood_width : 31;

                    for (z = min_z; z <= max_z; z++)
                        for (y = min_y; y <= max_y; y++)
                            for (x = min_x; x <= max_x; x++)
                            {
                                uchar3 pos = UCHAR3(x, y, z);
                                float err;
                                int dist[3];

                                dist[0] = (int)MEMBER(pos, X) - (int)MEMBER(best_pos[partition ? 0 : 1], X);
                                dist[1] = (int)MEMBER(pos, Y) - (int)MEMBER(best_pos[partition ? 0 : 1], Y);
                                dist[2] = (int)MEMBER(pos, Z) - (int)MEMBER(best_pos[partition ? 0 : 1], Z);

                                if ((dist[0] < -4 || dist[0] > 3) || 
                                    (dist[1] < -4 || dist[1] > 3) || 
                                    (dist[2] < -4 || dist[2] > 3))
                                    continue;

                                pos = ETC_RGBExpandVecTo5Bit(pos);
                                err = ETC_EvaluateError(is_ypbpr, trans_pixel, pos, &g_partition_indexes[best_flipped][partition][0]);

                                if (err < best_err)
                                {
                                    best_pos[partition] = UCHAR3(x, y, z);
                                    best_err = err;
                                }
                            }
                    combined_err += best_err;
                }

                if (combined_err < fixed_err)
                {
                    best_positions[0] = best_pos[0];
                    best_positions[1] = best_pos[1];
                    fixed_err = combined_err;
                }
            }
        }
#endif

        DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
        ETC_PrepareSampleList(SAMPLE_LIST_SIZE2, sample_list);
        DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
        for (flipped = 0; flipped < 2; flipped++)
        {
            for (partition = 0; partition < 2; partition++)
            {
                etc_sample_t sample;

                float offset = 0.0f;

                if (quality == CODEC_QUALITY_NORMAL)
                    offset = 0.0f;
                else if (quality > CODEC_QUALITY_NORMAL) // searching entire space on BEST tends to give values that can't be represented by delta encodings
                    offset = 24.0f;

                MEMBER(proj_mins, X) = UCHAR(((uint)clamp(MEMBER(projected_mins[flipped][partition], X) - offset, 0.0f, 255.0f)) >> 3);
                MEMBER(proj_mins, Y) = UCHAR(((uint)clamp(MEMBER(projected_mins[flipped][partition], Y) - offset, 0.0f, 255.0f)) >> 3);
                MEMBER(proj_mins, Z) = UCHAR(((uint)clamp(MEMBER(projected_mins[flipped][partition], Z) - offset, 0.0f, 255.0f)) >> 3);
                MEMBER(proj_maxs, X) = UCHAR(((uint)clamp(MEMBER(projected_maxs[flipped][partition], X) + offset + 3, 0.0f, 255.0f)) >> 3);
                MEMBER(proj_maxs, Y) = UCHAR(((uint)clamp(MEMBER(projected_maxs[flipped][partition], Y) + offset + 3, 0.0f, 255.0f)) >> 3);
                MEMBER(proj_maxs, Z) = UCHAR(((uint)clamp(MEMBER(projected_maxs[flipped][partition], Z) + offset + 3, 0.0f, 255.0f)) >> 3);

                sample.pos_quantised = proj_mins;
                DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
                pathing_params.partition_indexes = &g_partition_indexes[flipped][partition][0];
                sample.error = ETC_EvaluateError(is_ypbpr, trans_pixel, ETC_RGBExpandVecTo5Bit(sample.pos_quantised), &g_partition_indexes[flipped][partition][0]);
                DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
                ETC_LeastCostDirectedPath(step, SAMPLE_LIST_SIZE2, error_target, refine_search, is_ypbpr, trans_pixel, sample, &sample_list[flipped][partition][0], MEMBER(proj_maxs, X), MEMBER(proj_maxs, Y), MEMBER(proj_maxs, Z), &pathing_params, ETC_RGBEXPANDVECTO5BIT, ETC_EVALUATEDELTAERRORGENERIC, block_x, block_y);
                DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
            }
        }
        for (i = 0; i < 2; i++)
            best_dist[i] = sample_list[i][0][0].error + sample_list[i][1][0].error;
        if (best_dist[1] < best_dist[0])
            is_flipped = 1;
        else
            is_flipped = 0;
        is_delta = 0;
        int diff = (int)(MEMBER(sample_list[is_flipped][1][0].pos_quantised, X)) - (int)(MEMBER(sample_list[is_flipped][0][0].pos_quantised, X));
        if (diff < 4 && diff >= -4)
            is_delta++;
        diff = (int)(MEMBER(sample_list[is_flipped][1][0].pos_quantised, Y)) - (int)(MEMBER(sample_list[is_flipped][0][0].pos_quantised, Y));
        if (diff < 4 && diff >= -4)
            is_delta++;
        diff = (int)(MEMBER(sample_list[is_flipped][1][0].pos_quantised, Z)) - (int)(MEMBER(sample_list[is_flipped][0][0].pos_quantised, Z));
        if (diff < 4 && diff >= -4)
            is_delta++;
        is_best_delta = is_delta == 3 ? 1 : 0;
        best_total_error = min(best_dist[0], best_dist[1]);

        if (is_best_delta)
            enc_mode = ETC_ENC_MODE_DELTA;

        params_partition.rgb[0] = ETC_RGBExpandVecTo5Bit(sample_list[is_flipped][0][0].pos_quantised);
        params_partition.rgb[1] = ETC_RGBExpandVecTo5Bit(sample_list[is_flipped][1][0].pos_quantised);
        params_partition.is_flipped = is_flipped;

        DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
        if (!is_best_delta)
        {
            int delta[2][SAMPLE_LIST_SIZE2][SAMPLE_LIST_SIZE2]; // TODO: can get rid of this if just do it inside the loop
            float err[2][SAMPLE_LIST_SIZE2][SAMPLE_LIST_SIZE2]; // TODO: can get rid of this if just do it inside the loop
            int best_delta[2] = {0, 0};
            float best_delta_err = MAX_INIT_ERROR;
            int delta_found = 0;
            int best_flipped = 0;

            for (n = 0; n < 2; n++)
                for (i = 0; i < SAMPLE_LIST_SIZE2; i++)
                {
                    for (j = 0; j < SAMPLE_LIST_SIZE2; j++)
                    {
                        is_delta = 0;
                        int diff = (int)(MEMBER(sample_list[n][1][j].pos_quantised, X)) - (int)(MEMBER(sample_list[n][0][i].pos_quantised, X));
                        if (diff < 4 && diff >= -4)
                            is_delta++;
                        diff = (int)(MEMBER(sample_list[n][1][j].pos_quantised, Y)) - (int)(MEMBER(sample_list[n][0][i].pos_quantised, Y));
                        if (diff < 4 && diff >= -4)
                            is_delta++;
                        diff = (int)(MEMBER(sample_list[n][1][j].pos_quantised, Z)) - (int)(MEMBER(sample_list[n][0][i].pos_quantised, Z));
                        if (diff < 4 && diff >= -4)
                            is_delta++;

                        delta[n][i][j] = is_delta == 3 ? 1 : 0;
                        err[n][i][j] = sample_list[n][1][j].error + sample_list[n][0][i].error;
                    }
                }
            for (n = 0; n < 2; n++)
                for (i = 0; i < SAMPLE_LIST_SIZE2; i++)
                    for (j = 0; j < SAMPLE_LIST_SIZE2; j++)
                    {
                        if (delta[n][i][j])
                        {
                            if (err[n][i][j] < best_delta_err)
                            {
                                best_delta_err = err[n][i][j];
                                best_delta[0] = i;
                                best_delta[1] = j;
                                delta_found = 1;
                                best_flipped = n;
                            }
                        }
                    }
            best_total_error = best_delta_err;

            if (delta_found)
            {
                enc_mode = ETC_ENC_MODE_DELTA;
                params_partition.rgb[0] = ETC_RGBExpandVecTo5Bit(sample_list[best_flipped][0][best_delta[0]].pos_quantised);
                params_partition.rgb[1] = ETC_RGBExpandVecTo5Bit(sample_list[best_flipped][1][best_delta[1]].pos_quantised);
                params_partition.is_flipped = best_flipped;
            }
        }

        if (found_fixed && fixed_err < best_total_error)
        {
            enc_mode = ETC_ENC_MODE_DELTA;
            best_total_error = fixed_err;
            params_partition.rgb[0] = ETC_RGBExpandVecTo5Bit(best_positions[0]);
            params_partition.rgb[1] = ETC_RGBExpandVecTo5Bit(best_positions[1]);
            params_partition.is_flipped = best_flipped;
        }

        DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
        ETC_GetOptimalIndexes(is_ypbpr, trans_pixel, params_partition.rgb[0], &g_partition_indexes[params_partition.is_flipped][0][0], &params_partition.table[0], params_partition.indexes);
        DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
        ETC_GetOptimalIndexes(is_ypbpr, trans_pixel, params_partition.rgb[1], &g_partition_indexes[params_partition.is_flipped][1][0], &params_partition.table[1], params_partition.indexes);
        DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
    }
    if ((allowed_modes & ETC_MODE_NODELTA))
    {
        int is_non_delta_flipped;
        float3 mean[2][2];
        uchar3 mean_quant[2][2];
        int min_index[2][2];
        int max_index[2][2];
        float fixed_err = MAX_INIT_ERROR;
        uchar3 best_positions[2];
        int best_flipped = 0;
        int found_fixed = 0;
        uchar3 proj_mins;
        uchar3 proj_maxs;

        if (quality >= CODEC_QUALITY_NORMAL) // redundant
        {
            float fixed_err_group[2][2];
            uchar3 fixed_positions_group[2][2];
            int max_distance;

            if (quality == CODEC_QUALITY_BEST)
                max_distance = 255;
            else if (quality == CODEC_QUALITY_HIGH)
                max_distance = 4;
            else 
                max_distance = 1;

            for (i = 0; i < 2; i++)
                for (j = 0; j < 2; j++)
                    fixed_err_group[i][j] = MAX_INIT_ERROR;

            for (flipped = 0; flipped < 2; flipped++)
            {
                for (partition = 0; partition < 2; partition++)
                {
                    int distance = 0;
                    mean[flipped][partition] = VFLOAT3(0.0f, 0.0f, 0.0f);
                    for (i = 0; i < 8; i++)
                    {
                        mean[flipped][partition] = mean[flipped][partition] + trans_pixel[g_partition_indexes[flipped][partition][i]];
                    }
                    mean[flipped][partition] = mean[flipped][partition] / 8.0f;

                    MEMBER(mean_quant[flipped][partition], X) = UCHAR(MEMBER(mean[flipped][partition], X)) >> 4;
                    MEMBER(mean_quant[flipped][partition], Y) = UCHAR(MEMBER(mean[flipped][partition], Y)) >> 4;
                    MEMBER(mean_quant[flipped][partition], Z) = UCHAR(MEMBER(mean[flipped][partition], Z)) >> 4;

                    min_index[flipped][partition] = 0;
                    max_index[flipped][partition] = 0;

                    while ( ((int)MEMBER(mean_quant[flipped][partition], X) + min_index[flipped][partition] > 0) &&
                            ((int)MEMBER(mean_quant[flipped][partition], Y) + min_index[flipped][partition] > 0) &&
                            ((int)MEMBER(mean_quant[flipped][partition], Z) + min_index[flipped][partition] > 0))
                    {
                        min_index[flipped][partition]--;
                        distance++;
                        if (distance > max_distance)
                            break;
                    }
                    distance = 0;
                    while ( ((int)MEMBER(mean_quant[flipped][partition], X) + max_index[flipped][partition] < 16) &&
                            ((int)MEMBER(mean_quant[flipped][partition], Y) + max_index[flipped][partition] < 16) &&
                            ((int)MEMBER(mean_quant[flipped][partition], Z) + max_index[flipped][partition] < 16))
                    {
                        max_index[flipped][partition]++;
                        distance++;
                        if (distance > max_distance)
                            break;
                    }
                }
            }
#if 1
            for (flipped = 0; flipped < 2; flipped++)
            {
                for (partition = 0; partition < 2; partition++)
                {
                    int ip0;
                    for (ip0 = min_index[flipped][partition]; ip0 <= max_index[flipped][partition]; ip0++)
                    {
                        uchar3 l0_quant;
                        float err;

                        MEMBER(l0_quant, X) = UCHAR(MEMBER(mean_quant[flipped][partition], X) + ip0);
                        MEMBER(l0_quant, Y) = UCHAR(MEMBER(mean_quant[flipped][partition], Y) + ip0);
                        MEMBER(l0_quant, Z) = UCHAR(MEMBER(mean_quant[flipped][partition], Z) + ip0);

                        err = ETC_EvaluateError(is_ypbpr, trans_pixel, ETC_RGBExpandVecTo4Bit(l0_quant), &g_partition_indexes[flipped][partition][0]);

                        if (err < fixed_err_group[flipped][partition])
                        {
                            fixed_err_group[flipped][partition] = err;
                            fixed_positions_group[flipped][partition] = l0_quant;
                        }
                    }
                }
            }

            if (fixed_err_group[0][0] + fixed_err_group[0][1] < fixed_err_group[1][0] + fixed_err_group[1][1])
            {
                fixed_err = fixed_err_group[0][0] + fixed_err_group[0][1];
                best_positions[0] = fixed_positions_group[0][0];
                best_positions[1] = fixed_positions_group[0][1];
                best_flipped = 0;
            }
            else
            {
                fixed_err = fixed_err_group[1][0] + fixed_err_group[1][1];
                best_positions[0] = fixed_positions_group[1][0];
                best_positions[1] = fixed_positions_group[1][1];
                best_flipped = 1;
            }

            found_fixed = 1;
            if (found_fixed)
            {
                uchar3 best_pos[2];
                float combined_err = 0.0f;
            
                best_pos[0] = best_positions[0];
                best_pos[1] = best_positions[1];

                for (partition = 0; partition < 2; partition++)
                {
                    int neighbourhood_width = (quality == CODEC_QUALITY_BEST ? 3 : 1);
                    float best_err = MAX_INIT_ERROR;
                    int x;
                    int y;
                    int z;
                    int min_x = MEMBER(best_positions[partition], X) > (neighbourhood_width - 1) ? MEMBER(best_positions[partition], X) - neighbourhood_width : 0;
                    int min_y = MEMBER(best_positions[partition], Y) > (neighbourhood_width - 1) ? MEMBER(best_positions[partition], Y) - neighbourhood_width : 0;
                    int min_z = MEMBER(best_positions[partition], Z) > (neighbourhood_width - 1) ? MEMBER(best_positions[partition], Z) - neighbourhood_width : 0;
                    int max_x = MEMBER(best_positions[partition], X) < (15 - neighbourhood_width) ? MEMBER(best_positions[partition], X) + neighbourhood_width : 15;
                    int max_y = MEMBER(best_positions[partition], Y) < (15 - neighbourhood_width) ? MEMBER(best_positions[partition], Y) + neighbourhood_width : 15;
                    int max_z = MEMBER(best_positions[partition], Z) < (15 - neighbourhood_width) ? MEMBER(best_positions[partition], Z) + neighbourhood_width : 15;

                    for (z = min_z; z <= max_z; z++)
                        for (y = min_y; y <= max_y; y++)
                            for (x = min_x; x <= max_x; x++)
                            {
                                uchar3 pos = UCHAR3(x, y, z);
                                float err;
                                pos = ETC_RGBExpandVecTo4Bit(pos);
                                err = ETC_EvaluateError(is_ypbpr, trans_pixel, pos, &g_partition_indexes[best_flipped][partition][0]);
                                if (err < best_err)
                                {
                                    best_err = err;
                                    best_pos[partition] = UCHAR3(x, y, z);
                                }
                            }
                    combined_err += best_err;
                }
                best_positions[0] = best_pos[0];
                best_positions[1] = best_pos[1];

                fixed_err = combined_err;

                for (partition = 0; partition < 2; partition++)
                {
                    int terminate = 0;
                    uchar3 pos = best_positions[partition];

                    if (quality != CODEC_QUALITY_BEST)
                        terminate = 1;

                    while(!terminate)
                    {
                        short3 test_pos[27];
                        float dist[27];
                        int best_index;
                        float best_dist;
                        int terminate_count = 0;

                        for (j = 0; j < 27; j++)
                            test_pos[j] = SHORT3(MEMBER(pos, X), MEMBER(pos, Y), MEMBER(pos, Z)) + SHORT3((j % 3) - 1, ((j / 3) % 3) - 1, j/9 - 1);

                        for (j = 0; j < 27; j++)
                        {
                            if ((MEMBER(test_pos[j], X) > 15) || (MEMBER(test_pos[j], Y) > 15) || (MEMBER(test_pos[j], Z) > 15) || (MEMBER(test_pos[j], X) < 0) || (MEMBER(test_pos[j], Y) < 0) || (MEMBER(test_pos[j], Z) < 0))
                                dist[j] = MAX_INIT_ERROR;
                            else
                            {
                                uchar3 v;

                                v = ETC_RGBExpandVecTo4Bit(UCHAR3(MEMBER(test_pos[j], X), MEMBER(test_pos[j], Y), MEMBER(test_pos[j], Z)));

                                dist[j] = ETC_EvaluateError(is_ypbpr, trans_pixel, ETC_RGBExpandVecTo4Bit(v), &g_partition_indexes[best_flipped][partition][0]);
                            }
                        }

                        best_dist = dist[0];
                        best_index = 0;
                        for (j = 1; j < 27; j++)
                        {
                            if (dist[j] < best_dist)
                            {
                                best_dist = dist[j];
                                best_index = j;
                            }
                        }

                        if (DEBUG_BLOCK)
                        {
                            uchar3 v;

                            v = ETC_RGBExpandVecTo4Bit(UCHAR3(MEMBER(test_pos[best_index], X), MEMBER(test_pos[best_index], Y), MEMBER(test_pos[best_index], Z)));

                            printf("best err[%i]: %f vs %f at %3u %3u %3u\n", partition, best_dist, dist[13], v.v[0], v.v[1], v.v[2]);
                        }

                        best_positions[partition] = pos;

                        if (dist[13] == best_dist)
                            break;

                        for (j = 0; j < 27; j++)
                            if (dist[j] == MAX_INIT_ERROR)
                                terminate_count++;

                        if (terminate_count >= 26)
                            break;

                        pos = UCHAR3(MEMBER(test_pos[best_index], X), MEMBER(test_pos[best_index], Y), MEMBER(test_pos[best_index], Z));
                    }
                }
            }

            if (found_fixed && fixed_err < best_total_error)
            {
                enc_mode = ETC_ENC_MODE_NODELTA;
                best_total_error = fixed_err;
                params_partition.rgb[0] = ETC_RGBExpandVecTo4Bit(best_positions[0]);
                params_partition.rgb[1] = ETC_RGBExpandVecTo4Bit(best_positions[1]);
                params_partition.is_flipped = best_flipped;
            }
        }
#endif
        // Non-delta mode
        DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
        ETC_PrepareSampleList(1, sample_list);
        DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
        for (flipped = 0; flipped < 2; flipped++)
        {
            for (partition = 0; partition < 2; partition++)
            {
                etc_sample_t sample;
                float offset = 0.0f;

                if (quality == CODEC_QUALITY_NORMAL)
                    offset = 0.0f;
                else if (quality == CODEC_QUALITY_HIGH)
                    offset = 48.0f;
                else 
                    offset = 96.0f;

                if ((quality == CODEC_QUALITY_NORMAL) || (quality == CODEC_QUALITY_HIGH))
                {
                    MEMBER(proj_mins, X) = UCHAR(((uint)clamp(MEMBER(projected_mins[flipped][partition], X) - offset, 0.0f, 255.0f)) >> 4);
                    MEMBER(proj_mins, Y) = UCHAR(((uint)clamp(MEMBER(projected_mins[flipped][partition], Y) - offset, 0.0f, 255.0f)) >> 4);
                    MEMBER(proj_mins, Z) = UCHAR(((uint)clamp(MEMBER(projected_mins[flipped][partition], Z) - offset, 0.0f, 255.0f)) >> 4);
                    MEMBER(proj_maxs, X) = UCHAR(((uint)clamp(MEMBER(projected_maxs[flipped][partition], X) + offset + 7, 0.0f, 255.0f)) >> 4);
                    MEMBER(proj_maxs, Y) = UCHAR(((uint)clamp(MEMBER(projected_maxs[flipped][partition], Y) + offset + 7, 0.0f, 255.0f)) >> 4);
                    MEMBER(proj_maxs, Z) = UCHAR(((uint)clamp(MEMBER(projected_maxs[flipped][partition], Z) + offset + 7, 0.0f, 255.0f)) >> 4);
                }
                else
                {
                    proj_mins = UCHAR3(0, 0, 0);
                    proj_maxs = UCHAR3(15, 15, 15);
                }

                sample.pos_quantised = proj_mins;
                DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
                pathing_params.partition_indexes = &g_partition_indexes[flipped][partition][0];
                sample.error = ETC_EvaluateError(is_ypbpr, trans_pixel, ETC_RGBExpandVecTo4Bit(sample.pos_quantised), &g_partition_indexes[flipped][partition][0]);
                DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
                ETC_LeastCostDirectedPath(step, 1, error_target, refine_search, is_ypbpr, trans_pixel, sample, &sample_list[flipped][partition][0], MEMBER(proj_maxs, X), MEMBER(proj_maxs, Y), MEMBER(proj_maxs, Z), &pathing_params, ETC_RGBEXPANDVECTO4BIT, ETC_EVALUATEDELTAERRORGENERIC, block_x, block_y);
                DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
            }
        }
        for (i = 0; i < 2; i++)
            best_dist[i] = sample_list[i][0][0].error + sample_list[i][1][0].error;
        if (best_dist[1] < best_dist[0])
            is_non_delta_flipped = 1;
        else
            is_non_delta_flipped = 0;
        if (best_dist[is_non_delta_flipped] < best_total_error)
        {
            best_total_error = best_dist[is_non_delta_flipped];

            enc_mode = ETC_ENC_MODE_NODELTA;
            params_partition.rgb[0] = ETC_RGBExpandVecTo4Bit(sample_list[is_non_delta_flipped][0][0].pos_quantised);
            params_partition.rgb[1] = ETC_RGBExpandVecTo4Bit(sample_list[is_non_delta_flipped][1][0].pos_quantised);
            params_partition.is_flipped = is_non_delta_flipped;
        }
        DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
        ETC_GetOptimalIndexes(is_ypbpr, trans_pixel, params_partition.rgb[0], &g_partition_indexes[params_partition.is_flipped][0][0], &params_partition.table[0], params_partition.indexes);
        DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
        ETC_GetOptimalIndexes(is_ypbpr, trans_pixel, params_partition.rgb[1], &g_partition_indexes[params_partition.is_flipped][1][0], &params_partition.table[1], params_partition.indexes);
        DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
    }

    if (is_etc2)
    {
        if ((best_total_error > error_target) && (allowed_modes & (ETC_MODE_T | ETC_MODE_H)))
        {
            int set_indexes[2][16];
            int set_count[2];
            etc_sample_t sample;
            DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
            ETC_KMeansTHMode(trans_pixel, &set_indexes[0][0], &set_indexes[1][0], &set_count[0]);
            DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));

            for (partition = 0; partition < 2; partition++)
            {
                float3 mean = VFLOAT3(0.0f, 0.0f, 0.0f);
                float mins_maxs_dist[2];

                for (i = 0; i < set_count[partition]; i++)
                    mean = mean + trans_pixel[set_indexes[partition][i]];

                mean = mean / (set_count[partition] ? (float)(set_count[partition]) : 1.0f);

                if (set_count[partition])
                {
                    mins_maxs_dist[0] = dot(trans_pixel[set_indexes[partition][0]] - mean, VFLOAT3(0.57735f, 0.57735f, 0.57735f));
                    mins_maxs_dist[1] = mins_maxs_dist[0];

                    for (i = 0; i < set_count[partition]; i++)
                    {
                        float dist = dot(trans_pixel[set_indexes[partition][i]] - mean, VFLOAT3(0.57735f, 0.57735f, 0.57735f));

                        if (dist < mins_maxs_dist[0])
                            mins_maxs_dist[0] = dist;
                        if (dist > mins_maxs_dist[1])
                            mins_maxs_dist[1] = dist;
                    }
                    projected_mins[0][partition] = mean + VFLOAT3(0.57735f, 0.57735f, 0.57735f) * mins_maxs_dist[0];
                    projected_maxs[0][partition] = mean + VFLOAT3(0.57735f, 0.57735f, 0.57735f) * mins_maxs_dist[1];
                }
                else
                {
                    projected_mins[0][partition] = mean;
                    projected_maxs[0][partition] = mean;
                }
            }





            if (allowed_modes & ETC_MODE_T)
            {
                // T mode
                DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
                ETC_PrepareSampleList(1, sample_list);
                DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
                for (flipped = 0; flipped < 2; flipped++)
                {
                    etc_sample_t sample;
                    uchar3 proj_mins;
                    uchar3 proj_maxs;
                    float offset = 0.0f;

                    if (quality == CODEC_QUALITY_NORMAL)
                        offset = 0.0f;
                    else if (quality == CODEC_QUALITY_HIGH)
                        offset = 48.0f;
                    else 
                        offset = 96.0f;

                    if ((quality == CODEC_QUALITY_NORMAL) || (quality == CODEC_QUALITY_HIGH))
                    {
                        MEMBER(proj_mins, X) = UCHAR(((uint)clamp(MEMBER(projected_mins[0][flipped], X) - offset, 0.0f, 255.0f)) >> 4);
                        MEMBER(proj_mins, Y) = UCHAR(((uint)clamp(MEMBER(projected_mins[0][flipped], Y) - offset, 0.0f, 255.0f)) >> 4);
                        MEMBER(proj_mins, Z) = UCHAR(((uint)clamp(MEMBER(projected_mins[0][flipped], Z) - offset, 0.0f, 255.0f)) >> 4);
                        MEMBER(proj_maxs, X) = UCHAR(((uint)clamp(MEMBER(projected_maxs[0][flipped], X) + offset + 7, 0.0f, 255.0f)) >> 4);
                        MEMBER(proj_maxs, Y) = UCHAR(((uint)clamp(MEMBER(projected_maxs[0][flipped], Y) + offset + 7, 0.0f, 255.0f)) >> 4);
                        MEMBER(proj_maxs, Z) = UCHAR(((uint)clamp(MEMBER(projected_maxs[0][flipped], Z) + offset + 7, 0.0f, 255.0f)) >> 4);
                    }
                    else
                    {
                        proj_mins = UCHAR3(0, 0, 0);
                        proj_maxs = UCHAR3(15, 15, 15);
                    }

                    sample.pos_quantised = proj_mins;
                    DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
                    pathing_params.indexes = set_indexes[flipped];
                    pathing_params.num_indexes = set_count[flipped];
                    sample.error = ETC_EvaluateErrorTSingle(is_ypbpr, trans_pixel, ETC_RGBExpandVecTo4Bit(sample.pos_quantised), set_indexes[flipped], set_count[flipped]);
                    DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
                    ETC_LeastCostDirectedPath(step, 1, error_target, refine_search, is_ypbpr, trans_pixel, sample, &sample_list[flipped][0][0], MEMBER(proj_maxs, X), MEMBER(proj_maxs, Y), MEMBER(proj_maxs, Z), &pathing_params, ETC_RGBEXPANDVECTO4BIT, ETC_EVALUATETSINGLEERRORGENERIC, block_x, block_y);
                    DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));

                    if ((quality == CODEC_QUALITY_NORMAL) || (quality == CODEC_QUALITY_HIGH))
                    {
                        MEMBER(proj_mins, X) = UCHAR(((uint)clamp(MEMBER(projected_mins[0][(flipped + 1) % 2], X) - offset, 0.0f, 255.0f)) >> 4);
                        MEMBER(proj_mins, Y) = UCHAR(((uint)clamp(MEMBER(projected_mins[0][(flipped + 1) % 2], Y) - offset, 0.0f, 255.0f)) >> 4);
                        MEMBER(proj_mins, Z) = UCHAR(((uint)clamp(MEMBER(projected_mins[0][(flipped + 1) % 2], Z) - offset, 0.0f, 255.0f)) >> 4);
                        MEMBER(proj_maxs, X) = UCHAR(((uint)clamp(MEMBER(projected_maxs[0][(flipped + 1) % 2], X) + offset + 7, 0.0f, 255.0f)) >> 4);
                        MEMBER(proj_maxs, Y) = UCHAR(((uint)clamp(MEMBER(projected_maxs[0][(flipped + 1) % 2], Y) + offset + 7, 0.0f, 255.0f)) >> 4);
                        MEMBER(proj_maxs, Z) = UCHAR(((uint)clamp(MEMBER(projected_maxs[0][(flipped + 1) % 2], Z) + offset + 7, 0.0f, 255.0f)) >> 4);
                    }
                    else
                    {
                        proj_mins = UCHAR3(0, 0, 0);
                        proj_maxs = UCHAR3(15, 15, 15);
                    }

                    sample.pos_quantised = proj_mins;
                    DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
                    pathing_params.indexes = set_indexes[(flipped + 1) % 2];
                    pathing_params.num_indexes = set_count[(flipped + 1) % 2];
                    sample.error = ETC_EvaluateErrorTTriple(is_ypbpr, trans_pixel, ETC_RGBExpandVecTo4Bit(sample.pos_quantised), set_indexes[(flipped + 1) % 2], set_count[(flipped + 1) % 2]);
                    DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
                    ETC_LeastCostDirectedPath(step, 1, error_target, refine_search, is_ypbpr, trans_pixel, sample, &sample_list[flipped][1][0], MEMBER(proj_maxs, X), MEMBER(proj_maxs, Y), MEMBER(proj_maxs, Z), &pathing_params, ETC_RGBEXPANDVECTO4BIT, ETC_EVALUATETTRIPLEERRORGENERIC, block_x, block_y);
                    DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
                }
                for (i = 0; i < 2; i++)
                    best_dist[i] = sample_list[i][0][0].error + sample_list[i][1][0].error;

                if ((best_dist[0] < best_total_error) || (best_dist[1] < best_total_error))
                {
                    enc_mode = ETC_ENC_MODE_T;

                    if (best_dist[1] < best_dist[0])
                        is_flipped = 1;
                    else
                        is_flipped = 0;

                    params_th.rgb[0] = ETC_RGBExpandVecTo4Bit(sample_list[is_flipped][0][0].pos_quantised);
                    params_th.rgb[1] = ETC_RGBExpandVecTo4Bit(sample_list[is_flipped][1][0].pos_quantised);
                    DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
                    float d = ETC_GetOptimalTIndexes(is_ypbpr, trans_pixel, params_th.rgb[0], params_th.rgb[1], &params_th.indexes[0], &params_th.table);
                    DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
                    best_total_error = d;
                }
            }

            if ((best_total_error > error_target) && (allowed_modes & ETC_MODE_H))
            {
                int best_mode;

                // H-Mode
                ETC_PrepareSampleList(1, sample_list);
                for (flipped = 0; flipped < 2; flipped++)
                {
                    uchar3 proj_mins;
                    uchar3 proj_maxs;
                    float offset = 0.0f;

                    if (quality == CODEC_QUALITY_NORMAL)
                        offset = 0.0f;
                    else if (quality == CODEC_QUALITY_HIGH)
                        offset = 48.0f;
                    else 
                        offset = 96.0f;

                    if ((quality == CODEC_QUALITY_NORMAL) || (quality == CODEC_QUALITY_HIGH))
                    {
                        MEMBER(proj_mins, X) = UCHAR(((uint)clamp(MEMBER(projected_mins[0][flipped], X) - offset, 0.0f, 255.0f)) >> 4);
                        MEMBER(proj_mins, Y) = UCHAR(((uint)clamp(MEMBER(projected_mins[0][flipped], Y) - offset, 0.0f, 255.0f)) >> 4);
                        MEMBER(proj_mins, Z) = UCHAR(((uint)clamp(MEMBER(projected_mins[0][flipped], Z) - offset, 0.0f, 255.0f)) >> 4);
                        MEMBER(proj_maxs, X) = UCHAR(((uint)clamp(MEMBER(projected_maxs[0][flipped], X) + offset + 7, 0.0f, 255.0f)) >> 4);
                        MEMBER(proj_maxs, Y) = UCHAR(((uint)clamp(MEMBER(projected_maxs[0][flipped], Y) + offset + 7, 0.0f, 255.0f)) >> 4);
                        MEMBER(proj_maxs, Z) = UCHAR(((uint)clamp(MEMBER(projected_maxs[0][flipped], Z) + offset + 7, 0.0f, 255.0f)) >> 4);
                    }
                    else
                    {
                        proj_mins = UCHAR3(0, 0, 0);
                        proj_maxs = UCHAR3(15, 15, 15);
                    }

                    for (table = 0; table < 8; table++)
                    {
                        sample.pos_quantised = proj_mins;
                        DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
                        pathing_params.indexes = set_indexes[flipped];
                        pathing_params.num_indexes = set_count[flipped];
                        pathing_params.mode = table;
                        sample.error = ETC_EvaluateErrorH(is_ypbpr, trans_pixel, ETC_RGBExpandVecTo4Bit(sample.pos_quantised), set_indexes[flipped], set_count[flipped], table);
                        DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
                        ETC_LeastCostDirectedPath(step, 1, error_target, refine_search, is_ypbpr, trans_pixel, sample, &sample_list[flipped][table][0], MEMBER(proj_maxs, X), MEMBER(proj_maxs, Y), MEMBER(proj_maxs, Z), &pathing_params, ETC_RGBEXPANDVECTO4BIT, ETC_EVALUATEHERRORGENERIC, block_x, block_y);
                        DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
                    }
                }

                best_dist[0] = sample_list[0][0][0].error + sample_list[1][0][0].error;
                best_mode = 0;
                for (flipped = 0; flipped < 2; flipped++)
                    for (table = 0; table < 8; table++)
                        if (sample_list[0][table][0].error + sample_list[1][table][0].error < best_dist[0])
                        {
                            best_dist[0] = sample_list[0][table][0].error + sample_list[1][table][0].error;
                            best_mode = table;
                        }
                if (best_dist[0] < best_total_error)
                {
                    ushort rgbpacked[2];

                    enc_mode = ETC_ENC_MODE_H;

                    params_th.table = best_mode;

                    if ((MEMBER(sample_list[0][params_th.table][0].pos_quantised, X) == MEMBER(sample_list[1][params_th.table][0].pos_quantised, X)) &&
                        (MEMBER(sample_list[0][params_th.table][0].pos_quantised, Y) == MEMBER(sample_list[1][params_th.table][0].pos_quantised, Y)) &&
                        (MEMBER(sample_list[0][params_th.table][0].pos_quantised, Z) == MEMBER(sample_list[1][params_th.table][0].pos_quantised, Z)))
                        MEMBER(sample_list[0][params_th.table][0].pos_quantised, X) = (MEMBER(sample_list[0][params_th.table][0].pos_quantised, X) + 1) % 16;

                    params_th.rgb[0] = ETC_RGBExpandVecTo4Bit(sample_list[0][params_th.table][0].pos_quantised);
                    params_th.rgb[1] = ETC_RGBExpandVecTo4Bit(sample_list[1][params_th.table][0].pos_quantised);

                    rgbpacked[0] =  (((ushort)MEMBER(sample_list[0][params_th.table][0].pos_quantised, X)) << 8) |
                        (((ushort)MEMBER(sample_list[0][params_th.table][0].pos_quantised, Y)) << 4) |
                        (((ushort)MEMBER(sample_list[0][params_th.table][0].pos_quantised, Z)) << 0);

                    rgbpacked[1] =  (((ushort)MEMBER(sample_list[1][params_th.table][0].pos_quantised, X)) << 8) |
                        (((ushort)MEMBER(sample_list[1][params_th.table][0].pos_quantised, Y)) << 4) |
                        (((ushort)MEMBER(sample_list[1][params_th.table][0].pos_quantised, Z)) << 0);
                    if (!(params_th.table & 1))
                    {
                        if (rgbpacked[0] > rgbpacked[1])
                        {
                            params_th.rgb[0] = ETC_RGBExpandVecTo4Bit(sample_list[1][params_th.table][0].pos_quantised);
                            params_th.rgb[1] = ETC_RGBExpandVecTo4Bit(sample_list[0][params_th.table][0].pos_quantised);
                        }
                    }
                    else
                    {
                        if (rgbpacked[0] < rgbpacked[1])
                        {
                            params_th.rgb[0] = ETC_RGBExpandVecTo4Bit(sample_list[1][params_th.table][0].pos_quantised);
                            params_th.rgb[1] = ETC_RGBExpandVecTo4Bit(sample_list[0][params_th.table][0].pos_quantised);
                        }
                    }
                    DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
                    best_total_error = ETC_GetOptimalHIndexes(is_ypbpr, trans_pixel, params_th.rgb[0], params_th.rgb[1], params_th.indexes, params_th.table);
                    DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
                }
            }
        }

        if ((best_total_error != 0.0f) && (allowed_modes & ETC_MODE_PLANAR))
        {
            // Planar mode: always check this because it's so cheap to compute

            float3 points[3];
            int3 points_i32[3];
            float index_best_dist[3];
            float best_dist = 0.0f;
            int best_twiddle[3][3];
            int index;
            int twiddle0;
            int twiddle1;
            int twiddle2;
            const float coeff[3][16] =
            {
                {23.0f, 17.0f, 11.0f, 5.0f, 17.0f, 11.0f, 5.0f, -1.0f, 11.0f, 5.0f, -1.0f, -7.0f, 5.0f, -1.0f, -7.0f, -13.0f},
                {-1.0f, 9.0f, 19.0f, 29.0f, -7.0f, 3.0f, 13.0f, 23.0f, -13.0f, -3.0f, 7.0f, 17.0f, -19.0f, -9.0f, 1.0f, 11.0f},
                {-1.0f, -7.0f, -13.0f, -19.0f, 9.0f, 3.0f, -3.0f, -9.0f, 19.0f, 13.0f, 7.0f, 1.0f, 29.0f, 23.0f, 17.0f, 11.0f}
            };
            DEBUG_PRINTF(("trans_pixel: 0x%p\n", trans_pixel));
            points[0] = VFLOAT3(0.0f, 0.0f, 0.0f);
            points[1] = VFLOAT3(0.0f, 0.0f, 0.0f);
            points[2] = VFLOAT3(0.0f, 0.0f, 0.0f);
            // TODO: this isn't trivial for the YCBCR case, just minimise in RGB space for now
            if (is_ypbpr)
                for (i = 0; i < 16; i++)
                    trans_pixel[i] = clamp(ETC_ConvertToRGBf3(trans_pixel[i]), 0.0f, 255.0f);
            for (j = 0; j < 16; j++)
            {
                MEMBER(points[0], X) += coeff[0][j] * MEMBER(trans_pixel[j], X);
                MEMBER(points[1], X) += coeff[1][j] * MEMBER(trans_pixel[j], X);
                MEMBER(points[2], X) += coeff[2][j] * MEMBER(trans_pixel[j], X);

                MEMBER(points[0], Y) += coeff[0][j] * MEMBER(trans_pixel[j], Y);
                MEMBER(points[1], Y) += coeff[1][j] * MEMBER(trans_pixel[j], Y);
                MEMBER(points[2], Y) += coeff[2][j] * MEMBER(trans_pixel[j], Y);

                MEMBER(points[0], Z) += coeff[0][j] * MEMBER(trans_pixel[j], Z);
                MEMBER(points[1], Z) += coeff[1][j] * MEMBER(trans_pixel[j], Z);
                MEMBER(points[2], Z) += coeff[2][j] * MEMBER(trans_pixel[j], Z);
            }
            points[0] = points[0] * (1.0f / 80.0f);
            points[1] = points[1] * (1.0f / 80.0f);
            points[2] = points[2] * (1.0f / 80.0f);

            points[0] = clamp(points[0], 0.0f, 255.0f);
            points[1] = clamp(points[1], 0.0f, 255.0f);
            points[2] = clamp(points[2], 0.0f, 255.0f);

            points_i32[0] = INT3(ETC_RGBRoundTo6Bit((uchar)MEMBER(points[0], X)), ETC_RGBRoundTo7Bit((uchar)MEMBER(points[0], Y)), ETC_RGBRoundTo6Bit((uchar)MEMBER(points[0], Z)));
            points_i32[1] = INT3(ETC_RGBRoundTo6Bit((uchar)MEMBER(points[1], X)), ETC_RGBRoundTo7Bit((uchar)MEMBER(points[1], Y)), ETC_RGBRoundTo6Bit((uchar)MEMBER(points[1], Z)));
            points_i32[2] = INT3(ETC_RGBRoundTo6Bit((uchar)MEMBER(points[2], X)), ETC_RGBRoundTo7Bit((uchar)MEMBER(points[2], Y)), ETC_RGBRoundTo6Bit((uchar)MEMBER(points[2], Z)));
            for (index = 0; index < 3; index++)
                index_best_dist[index] = MAX_INIT_ERROR;

            for (twiddle0 = -2; twiddle0 <= 2; twiddle0++)
            {
                for (twiddle1 = -2; twiddle1 <= 2; twiddle1++)
                {
                    for (twiddle2 = -2; twiddle2 <= 2; twiddle2++)
                    {
                        int ppoints[3][3];
                        float comp_err[3];
                        int comb;

                        comb =  (MEMBER(points_i32[0], X) + twiddle0 * 4) | (MEMBER(points_i32[1], X) + twiddle1 * 4) | (MEMBER(points_i32[2], X) + twiddle2 * 4) |
                            (MEMBER(points_i32[0], Y) + twiddle0 * 2) | (MEMBER(points_i32[1], Y) + twiddle1 * 2) | (MEMBER(points_i32[2], Y) + twiddle2 * 2) |
                            (MEMBER(points_i32[0], Z) + twiddle0 * 4) | (MEMBER(points_i32[1], Z) + twiddle1 * 4) | (MEMBER(points_i32[2], Z) + twiddle2 * 4);

                        // trick: this tests if any of the values has negative sign or is >255, halving the number of comparisons needed
                        if (comb & 0xFFFFFF00)
                            continue;

                        ppoints[0][0] = ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[0], X) + twiddle0 * 4));
                        ppoints[0][1] = ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[1], X) + twiddle1 * 4));
                        ppoints[0][2] = ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[2], X) + twiddle2 * 4));

                        ppoints[1][0] = ETC_RGBRoundTo7Bit(UCHAR(MEMBER(points_i32[0], Y) + twiddle0 * 2));
                        ppoints[1][1] = ETC_RGBRoundTo7Bit(UCHAR(MEMBER(points_i32[1], Y) + twiddle1 * 2));
                        ppoints[1][2] = ETC_RGBRoundTo7Bit(UCHAR(MEMBER(points_i32[2], Y) + twiddle2 * 2));

                        ppoints[2][0] = ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[0], Z) + twiddle0 * 4));
                        ppoints[2][1] = ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[1], Z) + twiddle1 * 4));
                        ppoints[2][2] = ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[2], Z) + twiddle2 * 4));

                        comp_err[0] = 0.0f;
                        comp_err[1] = 0.0f;
                        comp_err[2] = 0.0f;

                        for (j = 0; j < 4; j++) // v
                        {
                            for (i = 0; i < 4; i++) // u
                            {
                                float3 v;

                                MEMBER(v, X) = (float)((i * (ppoints[0][1] - ppoints[0][0]) + j * (ppoints[0][2] - ppoints[0][0]) + 4 * (ppoints[0][0]) + 2) >> 2);
                                MEMBER(v, Y) = (float)((i * (ppoints[1][1] - ppoints[1][0]) + j * (ppoints[1][2] - ppoints[1][0]) + 4 * (ppoints[1][0]) + 2) >> 2);
                                MEMBER(v, Z) = (float)((i * (ppoints[2][1] - ppoints[2][0]) + j * (ppoints[2][2] - ppoints[2][0]) + 4 * (ppoints[2][0]) + 2) >> 2);

                                v = clamp(v, VFLOAT3(0.0f, 0.0f, 0.0f), VFLOAT3(255.0f, 255.0f, 255.0f));
                                v = v - trans_pixel[j*4 + i];

                                comp_err[0] += MEMBER(v, X) * MEMBER(v, X);
                                comp_err[1] += MEMBER(v, Y) * MEMBER(v, Y);
                                comp_err[2] += MEMBER(v, Z) * MEMBER(v, Z);
                            }
                        }
                        for (index = 0; index < 3; index++)
                        {
                            if (comp_err[index] < index_best_dist[index])
                            {
                                int scale = (index == 1 ? 2 : 4);
                                best_twiddle[index][0] = twiddle0 * scale;
                                best_twiddle[index][1] = twiddle1 * scale;
                                best_twiddle[index][2] = twiddle2 * scale;
                                index_best_dist[index] = comp_err[index];
                            }
                        }
                    }
                }
            }
            best_dist = index_best_dist[0] + index_best_dist[1] + index_best_dist[2];
            if (best_dist < best_total_error)
            {
                params_planar.rgb[0] = UCHAR3(ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[0], X) + best_twiddle[0][0])), ETC_RGBRoundTo7Bit(UCHAR(MEMBER(points_i32[0], Y) + best_twiddle[1][0])), ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[0], Z) + best_twiddle[2][0])));
                params_planar.rgb[1] = UCHAR3(ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[1], X) + best_twiddle[0][1])), ETC_RGBRoundTo7Bit(UCHAR(MEMBER(points_i32[1], Y) + best_twiddle[1][1])), ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[1], Z) + best_twiddle[2][1])));
                params_planar.rgb[2] = UCHAR3(ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[2], X) + best_twiddle[0][2])), ETC_RGBRoundTo7Bit(UCHAR(MEMBER(points_i32[2], Y) + best_twiddle[1][2])), ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[2], Z) + best_twiddle[2][2])));

                enc_mode = ETC_ENC_MODE_PLANAR;

                best_total_error = best_dist;
            }
        }
    }

    if (DEBUG_BLOCK)
        printf("best_total_error = %f, encode mode: %i\n", best_total_error, enc_mode);

    if ((enc_mode == ETC_ENC_MODE_DELTA) || (enc_mode == ETC_ENC_MODE_NODELTA))
    {
        if (enc_mode == ETC_ENC_MODE_NODELTA)
        {
            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], X) >> 4, 28, 4);
            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[1], X) >> 4, 24, 4);
            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], Y) >> 4, 20, 4);
            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[1], Y) >> 4, 16, 4);
            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], Z) >> 4, 12, 4);
            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[1], Z) >> 4,  8, 4);
            ETC_WriteBits(local_block, 0, 1, 1); // diff bit
        }
        else
        {
            int3 diff;

            MEMBER(diff, X) = (MEMBER(params_partition.rgb[1], X) >> 3) - (MEMBER(params_partition.rgb[0], X) >> 3);
            MEMBER(diff, Y) = (MEMBER(params_partition.rgb[1], Y) >> 3) - (MEMBER(params_partition.rgb[0], Y) >> 3);
            MEMBER(diff, Z) = (MEMBER(params_partition.rgb[1], Z) >> 3) - (MEMBER(params_partition.rgb[0], Z) >> 3);

            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], X) >> 3, 27, 5);
            ETC_WriteBits(local_block, MEMBER(diff, X) >> 0, 24, 3);
            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], Y) >> 3, 19, 5);
            ETC_WriteBits(local_block, MEMBER(diff, Y) >> 0, 16, 3);
            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], Z) >> 3, 11, 5);
            ETC_WriteBits(local_block, MEMBER(diff, Z) >> 0,  8, 3);
            ETC_WriteBits(local_block, 1, 1, 1); // diff bit
        }
        ETC_WriteBits(local_block, params_partition.table[0], 5, 3); // table codeword 1
        ETC_WriteBits(local_block, params_partition.table[1], 2, 3); // table codeword 2
        ETC_WriteBits(local_block, params_partition.is_flipped, 0, 1); // flip bit

        for (i = 0; i < 16; i++)
        {
            int index = (i%4)*4 + i/4;

            int idx = params_partition.indexes[i];

            ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);
            ETC_WriteBits(local_block, idx & 1, 32 + index, 1);

        }
        ETC_PackBlockSwapOrder(block, local_block);
    }
    if (is_etc2)
    {
        if (enc_mode == ETC_ENC_MODE_T)
        {
            int min_rd = -4 + ((MEMBER(params_th.rgb[0], X) >> 4) & 3);
            int max_rd = ((MEMBER(params_th.rgb[0], X) >> 4) & 3);
            int min_r = (MEMBER(params_th.rgb[0], X) >> 6) & 3;
            int max_r = 28 + min_r;
            uchar r;
            uchar rd;

            if (min_rd + min_r < 0)
            {
                r = UCHAR(min_r);
                rd = UCHAR(min_rd);
            }
            else
            {
                r = UCHAR(max_r);
                rd = UCHAR(max_rd);
            }

            ETC_WriteBits(local_block, r, 27, 5);
            ETC_WriteBits(local_block, rd, 24, 3);
            ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Y) >> 4, 20, 4);
            ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Z) >> 4, 16, 4);
            ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], X) >> 4, 12, 4);
            ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Y) >> 4,  8, 4);
            ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Z) >> 4,  4, 4);

            ETC_WriteBits(local_block, (params_th.table >> 1) & 3, 2, 2);
            ETC_WriteBits(local_block, 1, 1, 1); // diff bit
            ETC_WriteBits(local_block, params_th.table & 1, 0, 1); // flip bit

            for (i = 0; i < 16; i++)
            {
                int index = (i % 4) * 4 + i / 4;

                int idx = params_th.indexes[i];

                ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);
                ETC_WriteBits(local_block, idx & 1, 32 + index, 1);

            }
            ETC_PackBlockSwapOrder(block, local_block);
        }
        else if (enc_mode == ETC_ENC_MODE_H)
        {
            int min_gd = -4 + ((MEMBER(params_th.rgb[0], Z) >> 5) & 3);
            int max_gd = ((MEMBER(params_th.rgb[0], Z) >> 5) & 3);
            int min_g = ((MEMBER(params_th.rgb[0], Z) >> 7) & 1) | (((MEMBER(params_th.rgb[0], Y) >> 4) & 1) << 1);
            int max_g = 28 + min_g;
            uchar g;
            uchar gd;
            int rd;
            if (min_gd + min_g < 0)
            {
                g = UCHAR(min_g);
                gd = UCHAR(min_gd);
            }
            else
            {
                g = UCHAR(max_g);
                gd = UCHAR(max_gd);
            }

            rd = MEMBER(params_th.rgb[0], Y) >> 5;
            if (rd >= 4)
                rd = -4 + (rd & 3);

            if ((int)(MEMBER(params_th.rgb[0], X) >> 4) + rd < 0)
                ETC_WriteBits(local_block, 1, 31, 1);
            else
                ETC_WriteBits(local_block, 0, 31, 1);
            ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], X) >> 4, 27, 4);
            ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Y) >> 5, 24, 3);
            ETC_WriteBits(local_block, g, 19, 5);
            ETC_WriteBits(local_block, gd, 16, 3);
            ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Z) >> 4, 15, 1);
            ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], X) >> 4, 11, 4);
            ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Y) >> 4,  7, 4);
            ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Z) >> 4,  3, 4);

            ETC_WriteBits(local_block, (params_th.table >> 2) & 1, 2, 1);
            ETC_WriteBits(local_block, 1, 1, 1); // diff bit
            ETC_WriteBits(local_block, (params_th.table >> 1) & 1 & 1, 0, 1); // flip bit

            for (i = 0; i < 16; i++)
            {
                int index = (i % 4) * 4 + i / 4;

                int idx = params_th.indexes[i];

                ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);
                ETC_WriteBits(local_block, idx & 1, 32 + index, 1);

            }
            ETC_PackBlockSwapOrder(block, local_block);
        }
        else if (enc_mode == ETC_ENC_MODE_PLANAR)
        {
            int r, g, b;
            int rd, gd, bd;
            int min_bd;
            int max_bd;
            int min_b;
            int max_b;
            MEMBER(params_planar.rgb[0], X) >>= 2;
            MEMBER(params_planar.rgb[0], Y) >>= 1;
            MEMBER(params_planar.rgb[0], Z) >>= 2;

            MEMBER(params_planar.rgb[1], X) >>= 2;
            MEMBER(params_planar.rgb[1], Y) >>= 1;
            MEMBER(params_planar.rgb[1], Z) >>= 2;

            MEMBER(params_planar.rgb[2], X) >>= 2;
            MEMBER(params_planar.rgb[2], Y) >>= 1;
            MEMBER(params_planar.rgb[2], Z) >>= 2;

            ETC_WriteBits(local_block, MEMBER(params_planar.rgb[2], Z), 32, 6);
            ETC_WriteBits(local_block, MEMBER(params_planar.rgb[2], Y), 38, 7);
            ETC_WriteBits(local_block, MEMBER(params_planar.rgb[2], X), 45, 6);
            ETC_WriteBits(local_block, MEMBER(params_planar.rgb[1], Z), 51, 6);
            ETC_WriteBits(local_block, MEMBER(params_planar.rgb[1], Y), 57, 7);

            ETC_WriteBits(local_block, (MEMBER(params_planar.rgb[1], X)) & 1, 0, 1);
            ETC_WriteBits(local_block, 1, 1, 1);
            ETC_WriteBits(local_block, (MEMBER(params_planar.rgb[1], X) >> 1) & 31, 2, 5);
            ETC_WriteBits(local_block, MEMBER(params_planar.rgb[0], Z) & 7, 7, 3);
            ETC_WriteBits(local_block, (MEMBER(params_planar.rgb[0], Z) >> 3) & 7, 11, 2);
            ETC_WriteBits(local_block, (MEMBER(params_planar.rgb[0], Z) >> 5) & 1, 16, 1);
            ETC_WriteBits(local_block, MEMBER(params_planar.rgb[0], Y) & 63, 17, 6);
            ETC_WriteBits(local_block, (MEMBER(params_planar.rgb[0], Y) >> 6) & 1, 24, 1);
            ETC_WriteBits(local_block, MEMBER(params_planar.rgb[0], X), 25, 6);

            r = (MEMBER(params_planar.rgb[0], X) >> 2) & 63;
            rd = (MEMBER(params_planar.rgb[0], Y) >> 6) | ((MEMBER(params_planar.rgb[0], X) & 3) << 1);
            g = (MEMBER(params_planar.rgb[0], Y) >> 2) & 15;
            gd = (MEMBER(params_planar.rgb[0], Z) >> 5) | ((MEMBER(params_planar.rgb[0], Y) & 3) << 1);
            b = (MEMBER(params_planar.rgb[0], Z) >> 3) & 3;
            bd = (MEMBER(params_planar.rgb[0], Z) >> 1) & 3;

            if (rd >= 4)
                rd = -4 + (rd & 3);
            if (gd >= 4)
                gd = -4 + (gd & 3);
            if (bd >= 4)
                bd = -4 + (bd & 3);

            if (r + rd < 0)
                ETC_WriteBits(local_block, 1, 31, 1);
            else
                ETC_WriteBits(local_block, 0, 31, 1);

            if (g + gd < 0)
                ETC_WriteBits(local_block, 1, 23, 1);
            else
                ETC_WriteBits(local_block, 0, 23, 1);

            min_bd = -4 + bd;
            max_bd = bd;
            min_b = b;
            max_b = 28 + min_b;

            if (min_b + min_bd < 0)
            {
                ETC_WriteBits(local_block, min_bd, 8, 3);
                ETC_WriteBits(local_block, min_b, 11, 5);
            }
            else
            {
                ETC_WriteBits(local_block, max_bd, 8, 3);
                ETC_WriteBits(local_block, max_b, 11, 5);
            }
            ETC_PackBlockSwapOrder(block, local_block);
        }
    }
}

void ETC_EncodeRGB(
    int quality,
    int allowed_modes,
    float error_target,
    int refine_search,
    int is_etc2,
    int is_ypbpr,
    float4 *pixel,
    __global uchar *block,
    int block_x,
    int block_y)
{
    if (quality == CODEC_QUALITY_FAST)
        ETC_EncodeRGBFast(allowed_modes, is_etc2, is_ypbpr, pixel, block);
    else
        ETC_EncodeRGBQuality(quality, allowed_modes, error_target, refine_search, is_etc2, is_ypbpr, pixel, block, block_x, block_y);
}

float ETC_EvaluateErrorAlpha(float *alpha, float base_alpha, float mul, int table)
{
    int i;
    int j;
    float total_err = 0.0f;
    float point[8];

    for (i = 0; i < 8; i++)
        point[i] = clamp(base_alpha + mul * g_alpha[table][i], 0.0f, 255.0f);

    for (i = 0; i < 16; i++)
    {
        float best_err = MAX_INIT_ERROR;
        for (j = 0; j < 8; j++)
        {
            float err = (alpha[i] - point[j]) * (alpha[i] - point[j]);
            if (err < best_err)
                best_err = err;
        }
        total_err += best_err;
    }
    return total_err;
}

float ETC_FindBestBaseAlpha(float *alpha, float alpha_mins, float alpha_maxs, float mul, int table, int *best_base_alpha)
{
    int k;
    float a = alpha_mins;
    float b = alpha_maxs;
    float c = b - (b - a) * M_INV_GOLDEN_F;
    float d = a + (b - a) * M_INV_GOLDEN_F;
    float fc = 0.0f;
    float fd = 0.0f;

    fc = ETC_EvaluateErrorAlpha(alpha, floor(c + 0.5f), mul, table);
    fd = ETC_EvaluateErrorAlpha(alpha, floor(d + 0.5f), mul, table);

    for (k = 0; (k < 16) && (b - a) > 0.5f; k++)
    {
        if (fc < fd)
        {
            b = d;
            c = b - (b - a) * M_INV_GOLDEN_F;
            d = a + (b - a) * M_INV_GOLDEN_F;
            fd = fc;
            fc = ETC_EvaluateErrorAlpha(alpha, floor(c + 0.5f), mul, table);
        }
        else
        {
            a = c;
            c = b - (b - a) * M_INV_GOLDEN_F;
            d = a + (b - a) * M_INV_GOLDEN_F;
            fc = fd;
            fd = ETC_EvaluateErrorAlpha(alpha, floor(d + 0.5f), mul, table);
        }
    }
    if (fc < fd)
    {
        *best_base_alpha = (int)c;
        return fc;
    }
    else
    {
        *best_base_alpha = (int)d;
        return fd;
    }
}

void ETC_GetOptimalIndexesAlpha(float *alpha, float base_alpha, float mul, int table, int *indexes)
{
    int i;
    int j;
    float point[8];

    for (i = 0; i < 8; i++)
        point[i] = clamp(base_alpha + mul * g_alpha[table][i], 0.0f, 255.0f);

    for (i = 0; i < 16; i++)
    {
        float best_err = MAX_INIT_ERROR;
        for (j = 0; j < 8; j++)
        {
            float err = (alpha[i] - point[j]) * (alpha[i] - point[j]);
            if (err < best_err)
            {
                best_err = err;
                indexes[i] = j;
            }
        }
    }
}

void ETC_EncodeAlpha(
    float error_target,
    int refine_search,
    int search_radius,
    float4 *pixel,
    __global uchar *block)
{
    float alpha[16];
    float alpha_mins;
    float alpha_maxs;
    float alpha_mid;
    float alpha_half_range;
    float best_error = MAX_INIT_ERROR;
    float best_mul;
    int best_table;
    int i, j;
    int alpha_index[16];
    int best_base_alpha;
    uchar local_block[8];

    for (i = 0; i < 16; i++)
        alpha[i] = MEMBER(pixel[i], W);

    alpha_mins = alpha[0];
    alpha_maxs = alpha[0];
        for (i = 1; i < 16; i++)
        {
            alpha_mins = min(alpha_mins, alpha[i]);
            alpha_maxs = max(alpha_maxs, alpha[i]);
        }
    alpha_mid = floor((alpha_mins + alpha_maxs) * 0.5f + 0.5f);
    alpha_half_range = (alpha_maxs - alpha_mins) * 0.5f;
        for (i = 0; i < 16; i++)
        {
            int lower_mul = (int)clamp((int)max(floor(2.0f * alpha_half_range / g_alpha_range[i]), 1.0f) - search_radius, 1, 16 - (search_radius * 2 + 1));
            for (j = 0; j < search_radius * 2 + 1; j++)
            {
                float mul = (float)lower_mul + (float)j;
                float err = ETC_EvaluateErrorAlpha(alpha, alpha_mid, mul, i);
                    if (err < best_error)
                    {
                        best_table = i;
                        best_error = err;
                        best_mul = mul;
                        best_base_alpha = (int)alpha_mid;
                    }
                if (refine_search)
                {
                    int base_alpha[2];
                    float err_left = ETC_FindBestBaseAlpha(alpha, alpha_mins, alpha_mid, mul, i, &base_alpha[0]);
                    float err_right = ETC_FindBestBaseAlpha(alpha, alpha_mid, alpha_maxs, mul, i, &base_alpha[1]);

                    if (err_left < best_error)
                    {
                        best_table = i;
                        best_error = err_left;
                        best_mul = mul;
                        best_base_alpha = base_alpha[0];
                    }
                    if (err_right < best_error)
                    {
                        best_table = i;
                        best_error = err_right;
                        best_mul = mul;
                        best_base_alpha = base_alpha[1];
                    }
                }
            }

        }
    ETC_GetOptimalIndexesAlpha(alpha, (float)best_base_alpha, best_mul, best_table, alpha_index);

    //printf("alpha_mins %3f, alpha_maxs: %3f, best_base_alpha: %3i, best_mul: %3i, best_table: %3i\n", alpha_mins, alpha_maxs, best_base_alpha, best_mul, best_table);
    ETC_WriteBits(local_block, (uint)best_base_alpha, 56, 8);
    ETC_WriteBits(local_block, (uint)best_mul, 52, 4);
    ETC_WriteBits(local_block, best_table, 48, 4);

    for (i = 0; i < 16; i++)
    {
        int index = (i % 4) * 4 + i / 4;
        ETC_WriteBits(local_block, alpha_index[i], 45 - index * 3, 3);
    }
    ETC_PackBlockReverseOrder(block, local_block);
}






























float ETC_EvaluateErrorA1(int *transparency, int is_ypbpr, float3 *trans_pixel, uchar3 rgb, __constant const int *partition_indexes)
{
    int i, table, j;
    float best_table_dist = MAX_INIT_ERROR;
    float3 rgb32f = VFLOAT3(MEMBER(rgb, X), MEMBER(rgb, Y), MEMBER(rgb, Z));

    for (table = 0; table < 8; table++)
    {
        float current_table_dist = 0.0f;
        for (i = 0; i < 8; i++)
        {
            float best_dist = MAX_INIT_ERROR;

            if (transparency[partition_indexes[i]])
                continue;

            for (j = 0; j < 4; j++)
            {
                float3 temp_pixel;
                float3 delta;

                if (j == 0)     // RGBA = 0
                    temp_pixel = rgb32f;
                else if (j == 2)
                    continue;
                else
                    temp_pixel = clamp(rgb32f + VFLOAT3(g_table[table][j], g_table[table][j], g_table[table][j]), 0.0f, 255.0f);

                if (is_ypbpr)
                    delta = ETC_ConvertToYPBPRf3(temp_pixel) - trans_pixel[partition_indexes[i]];
                else
                    delta = temp_pixel - trans_pixel[partition_indexes[i]];

                float lensq = dot(delta, delta);

                if (lensq < best_dist)
                    best_dist = lensq;
            }
            current_table_dist += best_dist;
        }
        if (current_table_dist < best_table_dist)
        {
            best_table_dist = current_table_dist;
        }
    }
    return best_table_dist;
}

float ETC_EvaluateErrorTSingleA1(int *transparency, int is_ypbpr, float3 *trans_pixel, uchar3 rgb, int *indexes, int num_indexes)
{
    int i;
    float dist = 0.0f;
    float3 rgb32f;

    if (!num_indexes)
        return 0.0f;

    rgb32f = VFLOAT3(MEMBER(rgb, X), MEMBER(rgb, Y), MEMBER(rgb, Z));

    if (is_ypbpr)
        rgb32f = ETC_ConvertToYPBPRf3(rgb32f);

    for (i = 0; i < num_indexes; i++)
    {
        float3 delta;

        if (transparency[indexes[i]])
            continue;

        delta = rgb32f - trans_pixel[indexes[i]];
        dist += dot(delta, delta);
    }

    return dist;
}
float ETC_EvaluateErrorTTripleA1(int *transparency, int is_ypbpr, float3 *trans_pixel, uchar3 rgb, int *indexes, int num_indexes)
{
    int i, mode, j;
    float3 rgb32f;
    float best_mode_dist;

    if (!num_indexes)
        return 0.0f;

    rgb32f = VFLOAT3(MEMBER(rgb, X), MEMBER(rgb, Y), MEMBER(rgb, Z));
    best_mode_dist = MAX_INIT_ERROR;

    for (mode = 0; mode < 8; mode++)
    {
        float current_mode_dist = 0.0f;
        float3 points[2];
        points[0] = clamp(rgb32f + VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);
        points[1] = clamp(rgb32f - VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);

        if (is_ypbpr)
        {
            points[0] = ETC_ConvertToYPBPRf3(points[0]);
            points[1] = ETC_ConvertToYPBPRf3(points[1]);
        }

        for (i = 0; i < num_indexes; i++)
        {
            float best_dist = MAX_INIT_ERROR;

            if (transparency[indexes[i]])
                continue;

            for (j = 0; j < 2; j++)
            {
                float3 delta;
                float lensq;
                delta = points[j] - trans_pixel[indexes[i]];
                lensq = dot(delta, delta);
                if (lensq < best_dist)
                    best_dist = lensq;
            }
            current_mode_dist += best_dist;
        }
        if (current_mode_dist < best_mode_dist)
        {
            best_mode_dist = current_mode_dist;
        }
    }

    return best_mode_dist;
}

float ETC_EvaluateErrorHA1(int *transparency, int is_ypbpr, float3 *trans_pixel, uchar3 rgb, int *indexes, int num_indexes, int mode, int h_index)
{
    int i, j;
    float3 rgb32f;
    float current_mode_dist = 0.0f;
    float3 points[2];
    int num_points;

    if (!num_indexes)
        return 0.0f;

    rgb32f = VFLOAT3(MEMBER(rgb, X), MEMBER(rgb, Y), MEMBER(rgb, Z));

    if (h_index == 1)
    {
        num_points = 1;
        points[0] = clamp(rgb32f - VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);
    }
    else
    {
        num_points = 2;
        points[0] = clamp(rgb32f + VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);
        points[1] = clamp(rgb32f - VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);
    }

    if (is_ypbpr)
    {
        for (j = 0; j < num_points; j++)
            points[j] = ETC_ConvertToYPBPRf3(points[j]);
    }

    for (i = 0; i < num_indexes; i++)
    {
        float best_dist = MAX_INIT_ERROR;

        if (transparency[indexes[i]])
            continue;

        for (j = 0; j < num_points; j++)
        {
            float3 delta;
            float lensq;

            delta = points[j] - trans_pixel[indexes[i]];
            lensq = dot(delta, delta);

            if (lensq < best_dist)
                best_dist = lensq;
        }
        current_mode_dist += best_dist;
    }

    return current_mode_dist;
}


float EvaluateErrorGenericA1(int mode, int *transparency, int is_ypbpr, float3 *trans_pixel, uchar3 rgb, etc_pathing_params_t *pathing_params)
{
    switch (mode)
    {
    case ETC_EVALUATEDELTAERRORGENERICA1:
        return ETC_EvaluateErrorA1(transparency, is_ypbpr, trans_pixel, rgb, pathing_params->partition_indexes);
    case ETC_EVALUATETSINGLEERRORGENERICA1:
        return ETC_EvaluateErrorTSingleA1(transparency, is_ypbpr, trans_pixel, rgb, pathing_params->indexes, pathing_params->num_indexes);
    case ETC_EVALUATETTRIPLEERRORGENERICA1:
        return ETC_EvaluateErrorTTripleA1(transparency, is_ypbpr, trans_pixel, rgb, pathing_params->indexes, pathing_params->num_indexes);
    case ETC_EVALUATEHERRORGENERICA1:
        return ETC_EvaluateErrorHA1(transparency, is_ypbpr, trans_pixel, rgb, pathing_params->indexes, pathing_params->num_indexes, pathing_params->mode, pathing_params->h_index);
    default:
        return MAX_INIT_ERROR;
    }
}

void ETC_LeastCostDirectedPathA1(
    int step,
    int sample_list_entries,
    int *transparency,
    float error_target,
    int refine_search,
    int is_ypbpr,
    float3 *trans_pixel,
    etc_sample_t sample,
    etc_sample_t *sample_list,
    int x_max,
    int y_max,
    int z_max,
    etc_pathing_params_t *pathing_params,
    int expand_cb_fp,
    int evaluate_cb_fp)
{
    int         i;
    int         j;
    int         terminate;
    float   dist[27];

    for (i = 0, terminate = 0; terminate == 0; i++)
    {
        uchar3 test_pos[7];
        float best_dist;
        int best_index;
        int terminate_count = 0;

        ETC_AddSampleToList(sample_list_entries, &sample_list[0], sample);

        if (sample.error <= error_target)
            break;

        int scale = step;

        test_pos[0] = sample.pos_quantised + UCHAR3(scale, 0, 0);
        test_pos[1] = sample.pos_quantised + UCHAR3(0, scale, 0);
        test_pos[2] = sample.pos_quantised + UCHAR3(scale, scale, 0);
        test_pos[3] = sample.pos_quantised + UCHAR3(0, 0, scale);
        test_pos[4] = sample.pos_quantised + UCHAR3(scale, 0, scale);
        test_pos[5] = sample.pos_quantised + UCHAR3(0, scale, scale);
        test_pos[6] = sample.pos_quantised + UCHAR3(scale, scale, scale);

        for (j = 0; j < 7; j++)
        {
            if ((MEMBER(test_pos[j], X) > x_max) || (MEMBER(test_pos[j], Y) > y_max) || (MEMBER(test_pos[j], Z) > z_max))
                dist[j] = MAX_INIT_ERROR;
            else
            {
                uchar3 v;

                switch (expand_cb_fp)
                {
                case ETC_RGBEXPANDVECTO4BIT:
                    v = ETC_RGBExpandVecTo4Bit(test_pos[j]);
                    break;
                case ETC_RGBEXPANDVECTO5BIT:
                    v = ETC_RGBExpandVecTo5Bit(test_pos[j]);
                    break;
                }

                dist[j] = EvaluateErrorGenericA1(evaluate_cb_fp, transparency, is_ypbpr, trans_pixel, v, pathing_params);
            }
        }

        best_dist = dist[0];
        best_index = 0;
        for (j = 1; j < 7; j++)
        {
            if (dist[j] < best_dist)
            {
                best_dist = dist[j];
                best_index = j;
            }
        }

        for (j = 0; j < 7; j++)
            if (dist[j] == MAX_INIT_ERROR)
                terminate_count++;

        if (terminate_count == 7)
            break;

        if (dist[best_index] > MAX_ERROR_DIFF_MUL * sample_list[0].error)
            break;

        sample.pos_quantised = test_pos[best_index];
        sample.error = dist[best_index];
    }

    if (refine_search)
    {
        sample.pos_quantised = sample_list[0].pos_quantised;
        sample.error = sample_list[0].error;

        for (i = 0, terminate = 0; terminate == 0; i++)
        {
            short3 test_pos[27];
            float best_dist;
            int best_index;
            int terminate_count = 0;

            if (i != 1)
                ETC_AddSampleToList(sample_list_entries, &sample_list[0], sample);

            if (sample.error <= error_target)
                break;

            for (j = 0; j < 27; j++)
                test_pos[j] = SHORT3(MEMBER(sample.pos_quantised, X), MEMBER(sample.pos_quantised, Y), MEMBER(sample.pos_quantised, Z)) + SHORT3((j % 3) - 1, ((j / 3) % 3) - 1, j/9 - 1);

            for (j = 0; j < 27; j++)
            {
                if (j == 13)
                    dist[j] = sample.error;
                else if ((MEMBER(test_pos[j], X) > x_max) || (MEMBER(test_pos[j], Y) > y_max) || (MEMBER(test_pos[j], Z) > z_max) || (MEMBER(test_pos[j], X) < 0) || (MEMBER(test_pos[j], Y) < 0) || (MEMBER(test_pos[j], Z) < 0))
                    dist[j] = MAX_INIT_ERROR;
                else
                {
                    uchar3 v;

                    switch (expand_cb_fp)
                    {
                    case ETC_RGBEXPANDVECTO4BIT:
                        v = ETC_RGBExpandVecTo4Bit(UCHAR3(MEMBER(test_pos[j], X), MEMBER(test_pos[j], Y), MEMBER(test_pos[j], Z)));
                        break;
                    case ETC_RGBEXPANDVECTO5BIT:
                        v = ETC_RGBExpandVecTo5Bit(UCHAR3(MEMBER(test_pos[j], X), MEMBER(test_pos[j], Y), MEMBER(test_pos[j], Z)));
                        break;
                    }

                    dist[j] = EvaluateErrorGenericA1(evaluate_cb_fp, transparency, is_ypbpr, trans_pixel, v, pathing_params);
                }
            }

            best_dist = dist[0];
            best_index = 0;
            for (j = 1; j < 27; j++)
            {
                if (dist[j] < best_dist)
                {
                    best_dist = dist[j];
                    best_index = j;
                }
            }
            if (dist[13] == best_dist)
                break;

            for (j = 0; j < 27; j++)
                if (dist[j] == MAX_INIT_ERROR)
                    terminate_count++;

            if (terminate_count >= 26)
                break;

            if (dist[best_index] > MAX_ERROR_DIFF_MUL * sample_list[0].error)
                break;

            sample.pos_quantised = UCHAR3(MEMBER(test_pos[best_index], X), MEMBER(test_pos[best_index], Y), MEMBER(test_pos[best_index], Z));
            sample.error = dist[best_index];
        }
    }
}

void ETC_KMeansTHModeA1(int *transparency, float3 *trans_pixel, int *indexes0, int *indexes1, int *set_count)
{
    int *index[2] = {indexes0, indexes1};
    float3 means[2];
    int swap_indexes[2][2][16];
    int point_count[2][2];
    int ri[2];
    int i;
    int iteration;
    int source;
    int target;
    int set;

    for (i = 0; i < 16; i++)
        if (!transparency[i])
        {
            ri[0] = i;
            break;
        }

    ri[1] = i;

    for (i = ri[0] + 1; i < 16; i++)
        if (!transparency[i] && !(MEMBER(trans_pixel[ri[0]], X) == MEMBER(trans_pixel[i], X) && MEMBER(trans_pixel[ri[0]], Y) == MEMBER(trans_pixel[i], Y) && MEMBER(trans_pixel[ri[0]], Z) == MEMBER(trans_pixel[i], Z)))
        {
            ri[1] = i;
            break;
        }

    means[0] = trans_pixel[ri[0]];
    means[1] = trans_pixel[ri[1]];

    for (iteration = 0, i = 0; iteration < 16; iteration++)
    {
        if (!transparency[iteration])
        {
            swap_indexes[0][0][i] = iteration;
            i++;
        }
    }

    point_count[0][0] = i;
    point_count[0][1] = 0;
    point_count[1][0] = 0;
    point_count[1][1] = 0;

    source = 0;
    target = 1;

    for (iteration = 0; iteration < MAX_KMEANS_ITERATIONS; iteration++)
    {
        float3 temp_means[2];

        temp_means[0] = VFLOAT3(0.0f, 0.0f, 0.0f);
        temp_means[1] = VFLOAT3(0.0f, 0.0f, 0.0f);

        for (set = 0; set < 2; set++)
        {
            for (i = 0; i < point_count[source][set]; i++)
            {
                float3 diff[2];
                float lensq[2];

                diff[0] = means[0] - trans_pixel[swap_indexes[source][set][i]];
                diff[1] = means[1] - trans_pixel[swap_indexes[source][set][i]];

                lensq[0] = dot(diff[0], diff[0]);
                lensq[1] = dot(diff[1], diff[1]);

                if (lensq[0] < lensq[1])
                {
                    swap_indexes[target][0][point_count[target][0]] = swap_indexes[source][set][i];
                    temp_means[0] = temp_means[0] + trans_pixel[swap_indexes[source][set][i]];
                    point_count[target][0]++;
                }
                else
                {
                    swap_indexes[target][1][point_count[target][1]] = swap_indexes[source][set][i];
                    temp_means[1] = temp_means[1] + trans_pixel[swap_indexes[source][set][i]];
                    point_count[target][1]++;
                }
            }
        }

        if (point_count[target][0])
            temp_means[0] = temp_means[0] / (float)point_count[target][0];
        if (point_count[target][1])
            temp_means[1] = temp_means[1] / (float)point_count[target][1];

        if ((point_count[target][0] == point_count[source][0]) && (point_count[target][1] == point_count[source][1]))
        {
            if (!MemCmp(swap_indexes[target][0], swap_indexes[source][0], sizeof(int) * point_count[target][0]) &&
                !MemCmp(swap_indexes[target][1], swap_indexes[source][1], sizeof(int) * point_count[target][1]))
            {
                if (!Vec3f32Cmp(temp_means[0], means[0]) && !Vec3f32Cmp(temp_means[1], means[1]))
                {
                    source = (source + 1) % 2;
                    target = (target + 1) % 2;
                    break;
                }
            }
        }

        means[0] = temp_means[0];
        means[1] = temp_means[1];

        source = (source + 1) % 2;
        target = (target + 1) % 2;

        point_count[target][0] = 0;
        point_count[target][1] = 0;
    }
    for (i = 0; i < point_count[source][0]; i++)
        indexes0[i] = swap_indexes[source][0][i];
    for (i = 0; i < point_count[source][1]; i++)
        indexes1[i] = swap_indexes[source][1][i];

    set_count[0] = point_count[source][0];
    set_count[1] = point_count[source][1];
}

void ETC_GetOptimalIndexesA1(int *transparency, int is_ypbpr, float3 *trans_pixel, uchar3 rgb, __constant const int *partition_indexes, int *best_table, int *indexes)
{
    int i, table, j;
    float best_table_dist = MAX_INIT_ERROR;
    float3 rgb32f = VFLOAT3(MEMBER(rgb, X), MEMBER(rgb, Y), MEMBER(rgb, Z));

    *best_table = 0;

    for (table = 0; table < 8; table++)
    {
        float current_table_dist = 0.0f;
        for (i = 0; i < 8; i++)
        {
            float best_dist = MAX_INIT_ERROR;

            if (transparency[partition_indexes[i]])
                continue;

            for (j = 0; j < 4; j++)
            {
                float3 temp_pixel;
                float3 delta;

                if (j == 0)     // RGBA = 0
                    temp_pixel = rgb32f;
                else if (j == 2)
                    continue;
                else
                    temp_pixel = clamp(rgb32f + VFLOAT3(g_table[table][j], g_table[table][j], g_table[table][j]), 0.0f, 255.0f);

                if (is_ypbpr)
                    delta = ETC_ConvertToYPBPRf3(temp_pixel) - trans_pixel[partition_indexes[i]];
                else
                    delta = temp_pixel - trans_pixel[partition_indexes[i]];

                float lensq = dot(delta, delta);

                if (lensq < best_dist)
                    best_dist = lensq;
            }
            current_table_dist += best_dist;
        }
        if (current_table_dist < best_table_dist)
        {
            *best_table = table;
            best_table_dist = current_table_dist;
        }
    }

    for (i = 0; i < 8; i++)
    {
        float best_dist = MAX_INIT_ERROR;

        if (transparency[partition_indexes[i]])
        {
            indexes[partition_indexes[i]] = 2;
            continue;
        }

        for (j = 0; j < 4; j++)
        {
            float3 temp_pixel;
            float3 delta;

            if (j == 0)     // RGBA = 0
                temp_pixel = rgb32f;
            else if (j == 2)
                continue;
            else
                temp_pixel = clamp(rgb32f + VFLOAT3(g_table[*best_table][j], g_table[*best_table][j], g_table[*best_table][j]), 0.0f, 255.0f);

            if (is_ypbpr)
                delta = ETC_ConvertToYPBPRf3(temp_pixel) - trans_pixel[partition_indexes[i]];
            else
                delta = temp_pixel - trans_pixel[partition_indexes[i]];

            float lensq = dot(delta, delta);

            if (lensq < best_dist)
            {
                indexes[partition_indexes[i]] = j;
                best_dist = lensq;
            }
        }
    }
}

float ETC_GetOptimalTIndexesA1(int *transparency, int is_ypbpr, float3 *trans_pixel, uchar3 rgb_single, uchar3 rgb_triple, int *indexes, int *best_mode)
{
    int i, mode, j;
    float dist = 0.0f;
    float3 rgb32f_single;
    float3 rgb32f_triple;
    float best_mode_dist;
    float3 points[4];

    rgb32f_single = VFLOAT3(MEMBER(rgb_single, X), MEMBER(rgb_single, Y), MEMBER(rgb_single, Z));
    rgb32f_triple = VFLOAT3(MEMBER(rgb_triple, X), MEMBER(rgb_triple, Y), MEMBER(rgb_triple, Z));
    best_mode_dist = MAX_INIT_ERROR;
    *best_mode = 0;

    points[0] = rgb32f_single;

    if (is_ypbpr)
        points[0] = ETC_ConvertToYPBPRf3(points[0]);

    for (mode = 0; mode < 8; mode++)
    {
        float current_mode_dist = 0.0f;

        points[1] = clamp(rgb32f_triple + VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);
        points[2] = rgb32f_triple;
        points[3] = clamp(rgb32f_triple - VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);

        if (is_ypbpr)
        {
            points[1] = ETC_ConvertToYPBPRf3(points[1]);
            points[2] = ETC_ConvertToYPBPRf3(points[2]);
            points[3] = ETC_ConvertToYPBPRf3(points[3]);
        }

        for (i = 0; i < 16; i++)
        {
            float best_dist = MAX_INIT_ERROR;

            if (transparency[i])
                continue;

            for (j = 0; j < 4; j++)
            {
                float3 delta;
                float lensq;
                delta = points[j] - trans_pixel[i];
                lensq = dot(delta, delta);
                if (lensq < best_dist)
                    best_dist = lensq;
            }
            current_mode_dist += best_dist;
        }
        if (current_mode_dist < best_mode_dist)
        {
            *best_mode = mode;
            best_mode_dist = current_mode_dist;
        }
    }

    points[1] = clamp(rgb32f_triple + VFLOAT3(g_etc2_tmode_distance[*best_mode], g_etc2_tmode_distance[*best_mode], g_etc2_tmode_distance[*best_mode]), 0.0f, 255.0f);
    points[3] = clamp(rgb32f_triple - VFLOAT3(g_etc2_tmode_distance[*best_mode], g_etc2_tmode_distance[*best_mode], g_etc2_tmode_distance[*best_mode]), 0.0f, 255.0f);

    if (is_ypbpr)
    {
        points[1] = ETC_ConvertToYPBPRf3(points[1]);
        points[3] = ETC_ConvertToYPBPRf3(points[3]);
    }

    dist = 0.0f;

    for (i = 0; i < 16; i++)
    {
        float best_dist = MAX_INIT_ERROR;

        if (transparency[i])
        {
            indexes[i] = 2;
            continue;
        }

        for (j = 0; j < 4; j++)
        {
            float3 delta;
            float lensq;

            if (j == 2)
                continue;

            delta = points[j] - trans_pixel[i];
            lensq = dot(delta, delta);
            if (lensq < best_dist)
            {
                indexes[i] = j;
                best_dist = lensq;
            }
        }
        dist += best_dist;
    }
    return dist;
}
float ETC_GetOptimalHIndexesA1(int *transparency, int is_ypbpr, float3 *trans_pixel, uchar3 rgb_h0, uchar3 rgb_h1, int *indexes, int mode)
{
    int i, j;
    float dist = 0.0f;
    float3 rgb32f_h0;
    float3 rgb32f_h1;
    float3 points[4];

    rgb32f_h0 = VFLOAT3(MEMBER(rgb_h0, X), MEMBER(rgb_h0, Y), MEMBER(rgb_h0, Z));
    rgb32f_h1 = VFLOAT3(MEMBER(rgb_h1, X), MEMBER(rgb_h1, Y), MEMBER(rgb_h1, Z));

    points[0] = clamp(rgb32f_h0 + VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);
    points[1] = clamp(rgb32f_h0 - VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);
    points[3] = clamp(rgb32f_h1 - VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);

    if (is_ypbpr)
    {
        points[0] = ETC_ConvertToYPBPRf3(points[0]);
        points[1] = ETC_ConvertToYPBPRf3(points[1]);
        points[3] = ETC_ConvertToYPBPRf3(points[3]);
    }

    dist = 0.0f;

    for (i = 0; i < 16; i++)
    {
        float best_dist = MAX_INIT_ERROR;

        if (transparency[i])
        {
            indexes[i] = 2;
            continue;
        }

        for (j = 0; j < 4; j++)
        {
            float3 delta;
            float lensq;

            if (j == 2)
                continue;

            delta = points[j] - trans_pixel[i];
            lensq = dot(delta, delta);
            if (lensq < best_dist)
            {
                indexes[i] = j;
                best_dist = lensq;
            }
        }
        dist += best_dist;
    }
    return dist;
}

float ETC_EvaluateErrorWeighted(int is_ypbpr, float3 *trans_pixel, float *weight, uchar3 rgb, __constant const int *partition_indexes)
{
    int i, table, j;
    float best_table_dist = MAX_INIT_ERROR;
    float3 rgb32f = VFLOAT3(MEMBER(rgb, X), MEMBER(rgb, Y), MEMBER(rgb, Z));

    for (table = 0; table < 8; table++)
    {
        float current_table_dist = 0.0f;
        for (i = 0; i < 8; i++)
        {
            float best_dist = MAX_INIT_ERROR;
            for (j = 0; j < 4; j++)
            {
                float3 temp_pixel = clamp(rgb32f + VFLOAT3(g_table[table][j], g_table[table][j], g_table[table][j]), 0.0f, 255.0f);
                float3 delta;

                if (is_ypbpr)
                    delta = ETC_ConvertToYPBPRf3(temp_pixel) - trans_pixel[partition_indexes[i]];
                else
                    delta = temp_pixel - trans_pixel[partition_indexes[i]];

                float lensq = dot(delta, delta) * weight[partition_indexes[i]];

                if (lensq < best_dist)
                    best_dist = lensq;
            }
            current_table_dist += best_dist;
        }
        if (current_table_dist < best_table_dist)
        {
            best_table_dist = current_table_dist;
        }
    }
    return best_table_dist;
}

float ETC_EvaluateErrorTSingleWeighted(int is_ypbpr, float3 *trans_pixel, float *weight, uchar3 rgb, int *indexes, int num_indexes)
{
    int i;
    float dist = 0.0f;
    float3 rgb32f;

    if (!num_indexes)
        return 0.0f;

    rgb32f = VFLOAT3(MEMBER(rgb, X), MEMBER(rgb, Y), MEMBER(rgb, Z));

    if (is_ypbpr)
        rgb32f = ETC_ConvertToYPBPRf3(rgb32f);

    for (i = 0; i < num_indexes; i++)
    {
        float3 delta;
        delta = rgb32f - trans_pixel[indexes[i]];
        dist += dot(delta, delta) * weight[indexes[i]];
    }

    return dist;
}
float ETC_EvaluateErrorTTripleWeighted(int is_ypbpr, float3 *trans_pixel, float *weight, uchar3 rgb, int *indexes, int num_indexes)
{
    int i, mode, j;
    float3 rgb32f;
    float best_mode_dist;

    if (!num_indexes)
        return 0.0f;

    rgb32f = VFLOAT3(MEMBER(rgb, X), MEMBER(rgb, Y), MEMBER(rgb, Z));
    best_mode_dist = MAX_INIT_ERROR;

    for (mode = 0; mode < 8; mode++)
    {
        float current_mode_dist = 0.0f;
        float3 points[3];
        points[0] = clamp(rgb32f + VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);
        points[1] = rgb32f;
        points[2] = clamp(rgb32f - VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);

        if (is_ypbpr)
        {
            points[0] = ETC_ConvertToYPBPRf3(points[0]);
            points[1] = ETC_ConvertToYPBPRf3(points[1]);
            points[2] = ETC_ConvertToYPBPRf3(points[2]);
        }

        for (i = 0; i < num_indexes; i++)
        {
            float best_dist = MAX_INIT_ERROR;
            for (j = 0; j < 3; j++)
            {
                float3 delta;
                float lensq;
                delta = points[j] - trans_pixel[indexes[i]];
                lensq = dot(delta, delta) * weight[indexes[i]];
                if (lensq < best_dist)
                    best_dist = lensq;
            }
            current_mode_dist += best_dist;
        }
        if (current_mode_dist < best_mode_dist)
        {
            best_mode_dist = current_mode_dist;
        }
    }

    return best_mode_dist;
}

float ETC_EvaluateErrorHWeighted(int is_ypbpr, float3 *trans_pixel, float *weight, uchar3 rgb, int *indexes, int num_indexes, int mode)
{
    int i, j;
    float3 rgb32f;
    float current_mode_dist = 0.0f;
    float3 points[2];

    if (!num_indexes)
        return 0.0f;

    rgb32f = VFLOAT3(MEMBER(rgb, X), MEMBER(rgb, Y), MEMBER(rgb, Z));

    points[0] = clamp(rgb32f + VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);
    points[1] = clamp(rgb32f - VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);

    if (is_ypbpr)
    {
        points[0] = ETC_ConvertToYPBPRf3(points[0]);
        points[1] = ETC_ConvertToYPBPRf3(points[1]);
    }

    for (i = 0; i < num_indexes; i++)
    {
        float best_dist = MAX_INIT_ERROR;
        for (j = 0; j < 2; j++)
        {
            float3 delta;
            float lensq;

            delta = points[j] - trans_pixel[indexes[i]];
            lensq = dot(delta, delta) * weight[indexes[i]];

            if (lensq < best_dist)
                best_dist = lensq;
        }
        current_mode_dist += best_dist;
    }

    return current_mode_dist;
}

float EvaluateErrorGenericWeighted(int mode, int is_ypbpr, float3 *trans_pixel, float *weight, uchar3 rgb, etc_pathing_params_t *pathing_params)
{
    switch (mode)
    {
    case ETC_EVALUATEDELTAERRORGENERICA1:
        return ETC_EvaluateErrorWeighted(is_ypbpr, trans_pixel, weight, rgb, pathing_params->partition_indexes);
    case ETC_EVALUATETSINGLEERRORGENERICA1:
        return ETC_EvaluateErrorTSingleWeighted(is_ypbpr, trans_pixel, weight, rgb, pathing_params->indexes, pathing_params->num_indexes);
    case ETC_EVALUATETTRIPLEERRORGENERICA1:
        return ETC_EvaluateErrorTTripleWeighted(is_ypbpr, trans_pixel, weight, rgb, pathing_params->indexes, pathing_params->num_indexes);
    case ETC_EVALUATEHERRORGENERICA1:
        return ETC_EvaluateErrorHWeighted(is_ypbpr, trans_pixel, weight, rgb, pathing_params->indexes, pathing_params->num_indexes, pathing_params->mode);
    default:
        return MAX_INIT_ERROR;
    }
}
void ETC_GetOptimalIndexesWeighted(int is_ypbpr, float3 *trans_pixel, float *weight, uchar3 rgb, __constant const int *partition_indexes, int *best_table, int *indexes)
{
    int i, table, j;
    float best_table_dist = MAX_INIT_ERROR;
    float3 rgb32f = VFLOAT3(MEMBER(rgb, X), MEMBER(rgb, Y), MEMBER(rgb, Z));

    *best_table = 0;

    for (table = 0; table < 8; table++)
    {
        float current_table_dist = 0.0f;
        for (i = 0; i < 8; i++)
        {
            float best_dist = MAX_INIT_ERROR;
            for (j = 0; j < 4; j++)
            {
                float3 temp_pixel = clamp(rgb32f + VFLOAT3(g_table[table][j], g_table[table][j], g_table[table][j]), 0.0f, 255.0f);
                float3 delta;

                if (is_ypbpr)
                    delta = ETC_ConvertToYPBPRf3(temp_pixel) - trans_pixel[partition_indexes[i]];
                else
                    delta = temp_pixel - trans_pixel[partition_indexes[i]];

                float lensq = dot(delta, delta) * weight[partition_indexes[i]];

                if (lensq < best_dist)
                    best_dist = lensq;
            }
            current_table_dist += best_dist;
        }
        if (current_table_dist < best_table_dist)
        {
            *best_table = table;
            best_table_dist = current_table_dist;
        }
    }

    for (i = 0; i < 8; i++)
    {
        float best_dist = MAX_INIT_ERROR;
        for (j = 0; j < 4; j++)
        {
            float3 temp_pixel = clamp(rgb32f + VFLOAT3(g_table[*best_table][j], g_table[*best_table][j], g_table[*best_table][j]), 0.0f, 255.0f);
            float3 delta;

            if (is_ypbpr)
                delta = ETC_ConvertToYPBPRf3(temp_pixel) - trans_pixel[partition_indexes[i]];
            else
                delta = temp_pixel - trans_pixel[partition_indexes[i]];

            float lensq = dot(delta, delta) * weight[partition_indexes[i]];

            if (lensq < best_dist)
            {
                indexes[partition_indexes[i]] = j;
                best_dist = lensq;
            }
        }
    }
}

float ETC_GetOptimalTIndexesWeighted(int is_ypbpr, float3 *trans_pixel, float *weight, uchar3 rgb_single, uchar3 rgb_triple, int *indexes, int *best_mode)
{
    int i, mode, j;
    float dist = 0.0f;
    float3 rgb32f_single;
    float3 rgb32f_triple;
    float best_mode_dist;
    float3 points[4];

    rgb32f_single = VFLOAT3(MEMBER(rgb_single, X), MEMBER(rgb_single, Y), MEMBER(rgb_single, Z));
    rgb32f_triple = VFLOAT3(MEMBER(rgb_triple, X), MEMBER(rgb_triple, Y), MEMBER(rgb_triple, Z));
    best_mode_dist = MAX_INIT_ERROR;
    *best_mode = 0;

    points[0] = rgb32f_single;

    if (is_ypbpr)
        points[0] = ETC_ConvertToYPBPRf3(points[0]);

    for (mode = 0; mode < 8; mode++)
    {
        float current_mode_dist = 0.0f;

        points[1] = clamp(rgb32f_triple + VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);
        points[2] = rgb32f_triple;
        points[3] = clamp(rgb32f_triple - VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);

        if (is_ypbpr)
        {
            points[1] = ETC_ConvertToYPBPRf3(points[1]);
            points[2] = ETC_ConvertToYPBPRf3(points[2]);
            points[3] = ETC_ConvertToYPBPRf3(points[3]);
        }

        for (i = 0; i < 16; i++)
        {
            float best_dist = MAX_INIT_ERROR;
            for (j = 0; j < 4; j++)
            {
                float3 delta;
                float lensq;
                delta = points[j] - trans_pixel[i];
                lensq = dot(delta, delta) * weight[i];
                if (lensq < best_dist)
                    best_dist = lensq;
            }
            current_mode_dist += best_dist;
        }
        if (current_mode_dist < best_mode_dist)
        {
            *best_mode = mode;
            best_mode_dist = current_mode_dist;
        }
    }

    points[1] = clamp(rgb32f_triple + VFLOAT3(g_etc2_tmode_distance[*best_mode], g_etc2_tmode_distance[*best_mode], g_etc2_tmode_distance[*best_mode]), 0.0f, 255.0f);
    points[2] = rgb32f_triple;
    points[3] = clamp(rgb32f_triple - VFLOAT3(g_etc2_tmode_distance[*best_mode], g_etc2_tmode_distance[*best_mode], g_etc2_tmode_distance[*best_mode]), 0.0f, 255.0f);

    if (is_ypbpr)
    {
        points[1] = ETC_ConvertToYPBPRf3(points[1]);
        points[2] = ETC_ConvertToYPBPRf3(points[2]);
        points[3] = ETC_ConvertToYPBPRf3(points[3]);
    }

    dist = 0.0f;

    for (i = 0; i < 16; i++)
    {
        float best_dist = MAX_INIT_ERROR;
        if (weight[i] == 0.0f)
        {
            indexes[i] = 0;
            continue;
        }
        for (j = 0; j < 4; j++)
        {
            float3 delta;
            float lensq;
            delta = points[j] - trans_pixel[i];
            lensq = dot(delta, delta) * weight[i];
            if (lensq < best_dist)
            {
                indexes[i] = j;
                best_dist = lensq;
            }
        }
        dist += best_dist;
    }
    return dist;
}
float ETC_GetOptimalHIndexesWeighted(int is_ypbpr, float3 *trans_pixel, float *weight, uchar3 rgb_h0, uchar3 rgb_h1, int *indexes, int mode)
{
    int i, j;
    float dist = 0.0f;
    float3 rgb32f_h0;
    float3 rgb32f_h1;
    float3 points[4];

    rgb32f_h0 = VFLOAT3(MEMBER(rgb_h0, X), MEMBER(rgb_h0, Y), MEMBER(rgb_h0, Z));
    rgb32f_h1 = VFLOAT3(MEMBER(rgb_h1, X), MEMBER(rgb_h1, Y), MEMBER(rgb_h1, Z));

    points[0] = clamp(rgb32f_h0 + VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);
    points[1] = clamp(rgb32f_h0 - VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);
    points[2] = clamp(rgb32f_h1 + VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);
    points[3] = clamp(rgb32f_h1 - VFLOAT3(g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode], g_etc2_tmode_distance[mode]), 0.0f, 255.0f);

    if (is_ypbpr)
    {
        points[0] = ETC_ConvertToYPBPRf3(points[0]);
        points[1] = ETC_ConvertToYPBPRf3(points[1]);
        points[2] = ETC_ConvertToYPBPRf3(points[2]);
        points[3] = ETC_ConvertToYPBPRf3(points[3]);
    }

    dist = 0.0f;

    for (i = 0; i < 16; i++)
    {
        float best_dist = MAX_INIT_ERROR;
        for (j = 0; j < 4; j++)
        {
            float3 delta;
            float lensq;
            delta = points[j] - trans_pixel[i];
            lensq = dot(delta, delta) * weight[i];
            if (lensq < best_dist)
            {
                indexes[i] = j;
                best_dist = lensq;
            }
        }
        dist += best_dist;
    }
    return dist;
}

void ETC_LeastCostDirectedPathWeighted(
    int step,
    int sample_list_entries,
    float error_target,
    int refine_search,
    int is_ypbpr,
    float3 *trans_pixel,
    float *weight,
    etc_sample_t sample,
    etc_sample_t *sample_list,
    int x_max,
    int y_max,
    int z_max,
    etc_pathing_params_t *pathing_params,
    int expand_cb_fp,
    int evaluate_cb_fp)
{
    int         i;
    int         j;
    int         terminate;
    float   dist[27];

    for (i = 0, terminate = 0; terminate == 0; i++)
    {
        uchar3 test_pos[7];
        float best_dist;
        int best_index;
        int terminate_count = 0;

        ETC_AddSampleToList(sample_list_entries, &sample_list[0], sample);

        if (sample.error <= error_target)
            break;

        test_pos[0] = sample.pos_quantised + UCHAR3(step, 0, 0);
        test_pos[1] = sample.pos_quantised + UCHAR3(0, step, 0);
        test_pos[2] = sample.pos_quantised + UCHAR3(step, step, 0);
        test_pos[3] = sample.pos_quantised + UCHAR3(0, 0, step);
        test_pos[4] = sample.pos_quantised + UCHAR3(step, 0, step);
        test_pos[5] = sample.pos_quantised + UCHAR3(0, step, step);
        test_pos[6] = sample.pos_quantised + UCHAR3(step, step, step);

        for (j = 0; j < 7; j++)
        {
            if ((MEMBER(test_pos[j], X) > x_max) || (MEMBER(test_pos[j], Y) > y_max) || (MEMBER(test_pos[j], Z) > z_max))
                dist[j] = MAX_INIT_ERROR;
            else
            {
                uchar3 v;

                switch (expand_cb_fp)
                {
                case ETC_RGBEXPANDVECTO4BIT:
                    v = ETC_RGBExpandVecTo4Bit(test_pos[j]);
                    break;
                case ETC_RGBEXPANDVECTO5BIT:
                    v = ETC_RGBExpandVecTo5Bit(test_pos[j]);
                    break;
                }

                dist[j] = EvaluateErrorGenericWeighted(evaluate_cb_fp, is_ypbpr, trans_pixel, weight, v, pathing_params);
            }
        }

        best_dist = dist[0];
        best_index = 0;
        for (j = 1; j < 7; j++)
        {
            if (dist[j] < best_dist)
            {
                best_dist = dist[j];
                best_index = j;
            }
        }

        for (j = 0; j < 7; j++)
            if (dist[j] == MAX_INIT_ERROR)
                terminate_count++;

        if (terminate_count == 7)
            break;

        if (dist[best_index] > MAX_ERROR_DIFF_MUL * sample_list[0].error)
            break;

        sample.pos_quantised = test_pos[best_index];
        sample.error = dist[best_index];
    }

    if (refine_search)
    {
        sample.pos_quantised = sample_list[0].pos_quantised;
        sample.error = sample_list[0].error;

        for (i = 0, terminate = 0; terminate == 0; i++)
        {
            short3 test_pos[27];
            float best_dist;
            int best_index;
            int terminate_count = 0;

            if (i != 1)
                ETC_AddSampleToList(sample_list_entries, &sample_list[0], sample);

            if (sample.error <= error_target)
                break;

            for (j = 0; j < 27; j++)
                test_pos[j] = SHORT3(MEMBER(sample.pos_quantised, X), MEMBER(sample.pos_quantised, Y), MEMBER(sample.pos_quantised, Z)) + SHORT3((j % 3) - 1, ((j / 3) % 3) - 1, j/9 - 1);

            for (j = 0; j < 27; j++)
            {
                if (j == 13)
                    dist[j] = sample.error;
                else if ((MEMBER(test_pos[j], X) > x_max) || (MEMBER(test_pos[j], Y) > y_max) || (MEMBER(test_pos[j], Z) > z_max) || (MEMBER(test_pos[j], X) < 0) || (MEMBER(test_pos[j], Y) < 0) || (MEMBER(test_pos[j], Z) < 0))
                    dist[j] = MAX_INIT_ERROR;
                else
                {
                    uchar3 v;

                    switch (expand_cb_fp)
                    {
                    case ETC_RGBEXPANDVECTO4BIT:
                        v = ETC_RGBExpandVecTo4Bit(UCHAR3(MEMBER(test_pos[j], X), MEMBER(test_pos[j], Y), MEMBER(test_pos[j], Z)));
                        break;
                    case ETC_RGBEXPANDVECTO5BIT:
                        v = ETC_RGBExpandVecTo5Bit(UCHAR3(MEMBER(test_pos[j], X), MEMBER(test_pos[j], Y), MEMBER(test_pos[j], Z)));
                        break;
                    }

                    dist[j] = EvaluateErrorGenericWeighted(evaluate_cb_fp, is_ypbpr, trans_pixel, weight, v, pathing_params);
                }
            }

            best_dist = dist[0];
            best_index = 0;
            for (j = 1; j < 27; j++)
            {
                if (dist[j] < best_dist)
                {
                    best_dist = dist[j];
                    best_index = j;
                }
            }
            if (dist[13] == best_dist)
                break;

            for (j = 0; j < 27; j++)
                if (dist[j] == MAX_INIT_ERROR)
                    terminate_count++;

            if (terminate_count >= 26)
                break;

            if (dist[best_index] > MAX_ERROR_DIFF_MUL * sample_list[0].error)
                break;

            sample.pos_quantised = UCHAR3(MEMBER(test_pos[best_index], X), MEMBER(test_pos[best_index], Y), MEMBER(test_pos[best_index], Z));
            sample.error = dist[best_index];
        }
    }
}

void ETC_EncodeRGBWeighted(
    int quality,
    int allowed_modes,
    float error_target,
    int refine_search,
    int is_etc2,
    int is_ypbpr,
    float4 *pixel,
    float *weight,
    __global uchar *block)
{
    int i, j, table, n;
    float3 trans_pixel[16];
    int is_delta;
    int is_flipped;
    float best_dist[2];
    etc_sample_t sample_list[SAMPLE_LIST_SIZE0][SAMPLE_LIST_SIZE1][SAMPLE_LIST_SIZE2];
    int flipped;
    int partition;
    int is_best_delta = 0;
    float best_total_error = MAX_INIT_ERROR;
    int enc_mode;
    etc_partition_mode_params_t params_partition;
    etc_th_mode_params_t params_th;
    etc_planar_mode_params_t params_planar;
    etc_pathing_params_t pathing_params;
    uchar local_block[8];
    float3 projected_mins[2][2]; // delta/non-delta, flipped, partition
    float3 projected_maxs[2][2];

    for (i = 0; i < 16; i++)
    {
        MEMBER(trans_pixel[i], X) = MEMBER(pixel[i], X);
        MEMBER(trans_pixel[i], Y) = MEMBER(pixel[i], Y);
        MEMBER(trans_pixel[i], Z) = MEMBER(pixel[i], Z);
    }

    for (flipped = 0; flipped < 2; flipped++)
    {
        for (partition = 0; partition < 2; partition++)
        {
            float3 mean = VFLOAT3(0.0f, 0.0f, 0.0f);
            float mins_maxs_dist[2];
            int pixel_count = 0;

            mins_maxs_dist[0] = MAX_INIT_ERROR;
            mins_maxs_dist[1] = -MAX_INIT_ERROR;

            for (i = 0; i < 8; i++)
            {
                if (weight[g_partition_indexes[flipped][partition][i]] == 0.0f)
                    continue;
                mean = mean + trans_pixel[g_partition_indexes[flipped][partition][i]];
                pixel_count++;
            }

            pixel_count = pixel_count ? pixel_count : 1;

            mean = mean / (float)(pixel_count);

            for (i = 0; i < 8; i++)
            {
                float dist;

                if (weight[g_partition_indexes[flipped][partition][i]] == 0.0f)
                    continue;

                dist = dot(trans_pixel[g_partition_indexes[flipped][partition][i]] - mean, VFLOAT3(0.57735f, 0.57735f, 0.57735f));

                if (dist < mins_maxs_dist[0])
                    mins_maxs_dist[0] = dist;
                if (dist > mins_maxs_dist[1])
                    mins_maxs_dist[1] = dist;
            }
            projected_mins[flipped][partition] = mean + VFLOAT3(0.57735f, 0.57735f, 0.57735f) * mins_maxs_dist[0];
            projected_maxs[flipped][partition] = mean + VFLOAT3(0.57735f, 0.57735f, 0.57735f) * mins_maxs_dist[1];
        }
    }

    if (is_ypbpr)
        for (i = 0; i < 16; i++)
        {
            trans_pixel[i] = ETC_ConvertToYPBPRf3(trans_pixel[i]);
        }

    if (allowed_modes & ETC_MODE_DELTA)
    {
        float3 mean[2][2];
        uchar3 mean_quant[2][2];
        int min_index[2][2];
        int max_index[2][2];
        float fixed_err = MAX_INIT_ERROR;
        uchar3 best_positions[2];
        int best_flipped = 0;
        int found_fixed = 0;
        uchar3 proj_mins;
        uchar3 proj_maxs;
#if 1
        if (quality >= CODEC_QUALITY_NORMAL) // redundant, quality is always normal or better in this function
        {
            int max_distance;

            if (quality == CODEC_QUALITY_BEST)
                max_distance = 255;
            else if (quality == CODEC_QUALITY_HIGH)
                max_distance = 8;
            else 
                max_distance = 1;

            for (flipped = 0; flipped < 2; flipped++)
            {
                for (partition = 0; partition < 2; partition++)
                {
                    int distance = 0;
                    int num_pixels = 0;
                    mean[flipped][partition] = VFLOAT3(0.0f, 0.0f, 0.0f);
                    for (i = 0; i < 8; i++)
                    {
                        if (g_partition_indexes[flipped][partition][i] == 0.0f)
                            continue;
                        num_pixels++;
                        mean[flipped][partition] = mean[flipped][partition] + trans_pixel[g_partition_indexes[flipped][partition][i]];
                    }
                    num_pixels = num_pixels ? num_pixels : 1;
                    mean[flipped][partition] = mean[flipped][partition] / (float)(num_pixels);

                    MEMBER(mean_quant[flipped][partition], X) = UCHAR(MEMBER(mean[flipped][partition], X)) >> 3;
                    MEMBER(mean_quant[flipped][partition], Y) = UCHAR(MEMBER(mean[flipped][partition], Y)) >> 3;
                    MEMBER(mean_quant[flipped][partition], Z) = UCHAR(MEMBER(mean[flipped][partition], Z)) >> 3;

                    min_index[flipped][partition] = 0;
                    max_index[flipped][partition] = 0;

                    while ( ((int)MEMBER(mean_quant[flipped][partition], X) + min_index[flipped][partition] > 0) &&
                        ((int)MEMBER(mean_quant[flipped][partition], Y) + min_index[flipped][partition] > 0) &&
                        ((int)MEMBER(mean_quant[flipped][partition], Z) + min_index[flipped][partition] > 0))
                    {
                        min_index[flipped][partition]--;
                        distance++;
                        if (distance > max_distance)
                            break;
                    }
                    distance = 0;
                    while ( ((int)MEMBER(mean_quant[flipped][partition], X) + max_index[flipped][partition] < 31) &&
                        ((int)MEMBER(mean_quant[flipped][partition], Y) + max_index[flipped][partition] < 31) &&
                        ((int)MEMBER(mean_quant[flipped][partition], Z) + max_index[flipped][partition] < 31))
                    {
                        max_index[flipped][partition]++;
                        distance++;
                        if (distance > max_distance)
                            break;
                    }
                }
            }
            for (flipped = 0; flipped < 2; flipped++)
            {
                int ip0;
                int ip1;
                for (ip0 = min_index[flipped][0]; ip0 <= max_index[flipped][0]; ip0++)
                {
                    uchar3 l0_quant;

                    MEMBER(l0_quant, X) = UCHAR(MEMBER(mean_quant[flipped][0], X) + ip0);
                    MEMBER(l0_quant, Y) = UCHAR(MEMBER(mean_quant[flipped][0], Y) + ip0);
                    MEMBER(l0_quant, Z) = UCHAR(MEMBER(mean_quant[flipped][0], Z) + ip0);

                    for (ip1 = min_index[flipped][1]; ip1 <= max_index[flipped][1]; ip1++)
                    {
                        uchar3 l1_quant;
                        int dist[3];
                        float local_error;

                        MEMBER(l1_quant, X) = UCHAR(MEMBER(mean_quant[flipped][1], X) + ip1);
                        MEMBER(l1_quant, Y) = UCHAR(MEMBER(mean_quant[flipped][1], Y) + ip1);
                        MEMBER(l1_quant, Z) = UCHAR(MEMBER(mean_quant[flipped][1], Z) + ip1);

                        dist[0] = (int)MEMBER(l1_quant, X) - (int)MEMBER(l0_quant, X);
                        dist[1] = (int)MEMBER(l1_quant, Y) - (int)MEMBER(l0_quant, Y);
                        dist[2] = (int)MEMBER(l1_quant, Z) - (int)MEMBER(l0_quant, Z);

                        if ((dist[0] < -4 || dist[0] > 3) || 
                            (dist[1] < -4 || dist[1] > 3) || 
                            (dist[2] < -4 || dist[2] > 3))
                            continue;

                        local_error = ETC_EvaluateErrorWeighted(is_ypbpr, trans_pixel, weight, ETC_RGBExpandVecTo5Bit(l0_quant), &g_partition_indexes[flipped][0][0]);
                        local_error += ETC_EvaluateErrorWeighted(is_ypbpr, trans_pixel, weight, ETC_RGBExpandVecTo5Bit(l1_quant), &g_partition_indexes[flipped][1][0]);

                        if (local_error < fixed_err)
                        {
                            fixed_err = local_error;
                            best_positions[0] = l0_quant;
                            best_positions[1] = l1_quant;
                            best_flipped = flipped;
                            found_fixed = 1;
                        }
                    }
                }
            }
            if (found_fixed)
            {
                uchar3 best_pos[2];
                float combined_err = 0.0f;

                best_pos[0] = best_positions[0];
                best_pos[1] = best_positions[1];

                for (partition = 0; partition < 2; partition++)
                {
                    int neighbourhood_width = (quality == CODEC_QUALITY_BEST ? 3 : 1);
                    float best_err = MAX_INIT_ERROR;
                    int x;
                    int y;
                    int z;
                    int min_x = MEMBER(best_positions[partition], X) > (neighbourhood_width - 1) ? MEMBER(best_positions[partition], X) - neighbourhood_width : 0;
                    int min_y = MEMBER(best_positions[partition], Y) > (neighbourhood_width - 1) ? MEMBER(best_positions[partition], Y) - neighbourhood_width : 0;
                    int min_z = MEMBER(best_positions[partition], Z) > (neighbourhood_width - 1) ? MEMBER(best_positions[partition], Z) - neighbourhood_width : 0;
                    int max_x = MEMBER(best_positions[partition], X) < (31 - neighbourhood_width) ? MEMBER(best_positions[partition], X) + neighbourhood_width : 31;
                    int max_y = MEMBER(best_positions[partition], Y) < (31 - neighbourhood_width) ? MEMBER(best_positions[partition], Y) + neighbourhood_width : 31;
                    int max_z = MEMBER(best_positions[partition], Z) < (31 - neighbourhood_width) ? MEMBER(best_positions[partition], Z) + neighbourhood_width : 31;

                    for (z = min_z; z <= max_z; z++)
                        for (y = min_y; y <= max_y; y++)
                            for (x = min_x; x <= max_x; x++)
                            {
                                uchar3 pos = UCHAR3(x, y, z);
                                float err;
                                int dist[3];

                                dist[0] = (int)MEMBER(pos, X) - (int)MEMBER(best_pos[partition ? 0 : 1], X);
                                dist[1] = (int)MEMBER(pos, Y) - (int)MEMBER(best_pos[partition ? 0 : 1], Y);
                                dist[2] = (int)MEMBER(pos, Z) - (int)MEMBER(best_pos[partition ? 0 : 1], Z);

                                if ((dist[0] < -4 || dist[0] > 3) || 
                                    (dist[1] < -4 || dist[1] > 3) || 
                                    (dist[2] < -4 || dist[2] > 3))
                                    continue;

                                pos = ETC_RGBExpandVecTo5Bit(pos);
                                err = ETC_EvaluateErrorWeighted(is_ypbpr, trans_pixel, weight, pos, &g_partition_indexes[best_flipped][partition][0]);

                                if (err < best_err)
                                {
                                    best_pos[partition] = UCHAR3(x, y, z);
                                    best_err = err;
                                }
                            }
                    combined_err += best_err;
                }

                if (combined_err < fixed_err)
                {
                    best_positions[0] = best_pos[0];
                    best_positions[1] = best_pos[1];
                    fixed_err = combined_err;
                }
            }
        }
#endif
        // Delta mode
        ETC_PrepareSampleList(SAMPLE_LIST_SIZE2, sample_list);

        for (flipped = 0; flipped < 2; flipped++)
        {
            for (partition = 0; partition < 2; partition++)
            {
                etc_sample_t sample;

                float offset = 0.0f;

                if (quality == CODEC_QUALITY_NORMAL)
                    offset = 0.0f;
                else if (quality > CODEC_QUALITY_NORMAL) // searching entire space on BEST tends to give values that can't be represented by delta encodings
                    offset = 24.0f;

                MEMBER(proj_mins, X) = UCHAR(((uint)clamp(MEMBER(projected_mins[flipped][partition], X) - offset, 0.0f, 255.0f)) >> 3);
                MEMBER(proj_mins, Y) = UCHAR(((uint)clamp(MEMBER(projected_mins[flipped][partition], Y) - offset, 0.0f, 255.0f)) >> 3);
                MEMBER(proj_mins, Z) = UCHAR(((uint)clamp(MEMBER(projected_mins[flipped][partition], Z) - offset, 0.0f, 255.0f)) >> 3);
                MEMBER(proj_maxs, X) = UCHAR(((uint)clamp(MEMBER(projected_maxs[flipped][partition], X) + offset + 3, 0.0f, 255.0f)) >> 3);
                MEMBER(proj_maxs, Y) = UCHAR(((uint)clamp(MEMBER(projected_maxs[flipped][partition], Y) + offset + 3, 0.0f, 255.0f)) >> 3);
                MEMBER(proj_maxs, Z) = UCHAR(((uint)clamp(MEMBER(projected_maxs[flipped][partition], Z) + offset + 3, 0.0f, 255.0f)) >> 3);

                sample.pos_quantised = proj_mins;
                pathing_params.partition_indexes = &g_partition_indexes[flipped][partition][0];
                sample.error = ETC_EvaluateErrorWeighted(is_ypbpr, trans_pixel, weight, ETC_RGBExpandVecTo5Bit(sample.pos_quantised), &g_partition_indexes[flipped][partition][0]);
                ETC_LeastCostDirectedPathWeighted(1, SAMPLE_LIST_SIZE2, error_target, refine_search, is_ypbpr, trans_pixel, weight, sample, &sample_list[flipped][partition][0], MEMBER(proj_maxs, X), MEMBER(proj_maxs, Y), MEMBER(proj_maxs, Z), &pathing_params, ETC_RGBEXPANDVECTO5BIT, ETC_EVALUATEDELTAERRORGENERICWEIGHTED);
            }
        }

        for (i = 0; i < 2; i++)
            best_dist[i] = sample_list[i][0][0].error + sample_list[i][1][0].error;

        if (best_dist[1] < best_dist[0])
            is_flipped = 1;
        else
            is_flipped = 0;

        is_delta = 0;

        int diff = (int)(MEMBER(sample_list[is_flipped][1][0].pos_quantised, X)) - (int)(MEMBER(sample_list[is_flipped][0][0].pos_quantised, X));
        if (diff < 4 && diff >= -4)
            is_delta++;
        diff = (int)(MEMBER(sample_list[is_flipped][1][0].pos_quantised, Y)) - (int)(MEMBER(sample_list[is_flipped][0][0].pos_quantised, Y));
        if (diff < 4 && diff >= -4)
            is_delta++;
        diff = (int)(MEMBER(sample_list[is_flipped][1][0].pos_quantised, Z)) - (int)(MEMBER(sample_list[is_flipped][0][0].pos_quantised, Z));
        if (diff < 4 && diff >= -4)
            is_delta++;

        is_best_delta = is_delta == 3 ? 1 : 0;

        best_total_error = min(best_dist[0], best_dist[1]);

        enc_mode = ETC_ENC_MODE_DELTA;
        params_partition.rgb[0] = ETC_RGBExpandVecTo5Bit(sample_list[is_flipped][0][0].pos_quantised);
        params_partition.rgb[1] = ETC_RGBExpandVecTo5Bit(sample_list[is_flipped][1][0].pos_quantised);
        params_partition.is_flipped = is_flipped;

        if (!is_best_delta)
        {
            int delta[2][SAMPLE_LIST_SIZE2][SAMPLE_LIST_SIZE2]; // TODO: can get rid of this if just do it inside the loop
            float err[2][SAMPLE_LIST_SIZE2][SAMPLE_LIST_SIZE2]; // TODO: can get rid of this if just do it inside the loop
            int best_delta[2] = {0, 0};
            float best_delta_err = MAX_INIT_ERROR;
            int delta_found = 0;
            int best_flipped = 0;

            for (n = 0; n < 2; n++)
                for (i = 0; i < SAMPLE_LIST_SIZE2; i++)
                {
                    for (j = 0; j < SAMPLE_LIST_SIZE2; j++)
                    {
                        is_delta = 0;
                        int diff = (int)(MEMBER(sample_list[n][1][j].pos_quantised, X)) - (int)(MEMBER(sample_list[n][0][i].pos_quantised, X));
                        if (diff < 4 && diff >= -4)
                            is_delta++;
                        diff = (int)(MEMBER(sample_list[n][1][j].pos_quantised, Y)) - (int)(MEMBER(sample_list[n][0][i].pos_quantised, Y));
                        if (diff < 4 && diff >= -4)
                            is_delta++;
                        diff = (int)(MEMBER(sample_list[n][1][j].pos_quantised, Z)) - (int)(MEMBER(sample_list[n][0][i].pos_quantised, Z));
                        if (diff < 4 && diff >= -4)
                            is_delta++;

                        delta[n][i][j] = is_delta == 3 ? 1 : 0;
                        err[n][i][j] = sample_list[n][1][j].error + sample_list[n][0][i].error;
                    }
                }
            for (n = 0; n < 2; n++)
                for (i = 0; i < SAMPLE_LIST_SIZE2; i++)
                    for (j = 0; j < SAMPLE_LIST_SIZE2; j++)
                        if (delta[n][i][j])
                            if (err[n][i][j] < best_delta_err)
                            {
                                best_delta_err = err[n][i][j];
                                best_delta[0] = i;
                                best_delta[1] = j;
                                delta_found = 1;
                                best_flipped = n;
                            }

            best_total_error = best_delta_err;

            if (delta_found)
            {
                params_partition.rgb[0] = ETC_RGBExpandVecTo5Bit(sample_list[best_flipped][0][best_delta[0]].pos_quantised);
                params_partition.rgb[1] = ETC_RGBExpandVecTo5Bit(sample_list[best_flipped][1][best_delta[1]].pos_quantised);
                params_partition.is_flipped = best_flipped;
            }
        }

        if (found_fixed && fixed_err < best_total_error)
        {
            enc_mode = ETC_ENC_MODE_DELTA;
            best_total_error = fixed_err;
            params_partition.rgb[0] = ETC_RGBExpandVecTo5Bit(best_positions[0]);
            params_partition.rgb[1] = ETC_RGBExpandVecTo5Bit(best_positions[1]);
            params_partition.is_flipped = best_flipped;
        }

        ETC_GetOptimalIndexesWeighted(is_ypbpr, trans_pixel, weight, params_partition.rgb[0], &g_partition_indexes[params_partition.is_flipped][0][0], &params_partition.table[0], params_partition.indexes);
        ETC_GetOptimalIndexesWeighted(is_ypbpr, trans_pixel, weight, params_partition.rgb[1], &g_partition_indexes[params_partition.is_flipped][1][0], &params_partition.table[1], params_partition.indexes);
    }

    if ((!is_best_delta) && (allowed_modes & ETC_MODE_NODELTA))
    {
        int is_non_delta_flipped;
        float3 mean[2][2];
        uchar3 mean_quant[2][2];
        int min_index[2][2];
        int max_index[2][2];
        float fixed_err = MAX_INIT_ERROR;
        uchar3 best_positions[2];
        int best_flipped = 0;
        int found_fixed = 0;
        uchar3 proj_mins;
        uchar3 proj_maxs;

        if (quality >= CODEC_QUALITY_NORMAL) // redundant
        {
            float fixed_err_group[2][2];
            uchar3 fixed_positions_group[2][2];
            int max_distance;

            if (quality == CODEC_QUALITY_BEST)
                max_distance = 255;
            else if (quality == CODEC_QUALITY_HIGH)
                max_distance = 4;
            else 
                max_distance = 1;

            for (i = 0; i < 2; i++)
                for (j = 0; j < 2; j++)
                    fixed_err_group[i][j] = MAX_INIT_ERROR;

            for (flipped = 0; flipped < 2; flipped++)
            {
                for (partition = 0; partition < 2; partition++)
                {
                    int distance = 0;
                    int num_pixels = 0;
                    mean[flipped][partition] = VFLOAT3(0.0f, 0.0f, 0.0f);
                    for (i = 0; i < 8; i++)
                    {
                        if (g_partition_indexes[flipped][partition][i] == 0.0f)
                            continue;
                        num_pixels++;
                        mean[flipped][partition] = mean[flipped][partition] + trans_pixel[g_partition_indexes[flipped][partition][i]];
                    }
                    num_pixels = num_pixels ? num_pixels : 1;
                    mean[flipped][partition] = mean[flipped][partition] / (float)(num_pixels);

                    MEMBER(mean_quant[flipped][partition], X) = UCHAR(MEMBER(mean[flipped][partition], X)) >> 4;
                    MEMBER(mean_quant[flipped][partition], Y) = UCHAR(MEMBER(mean[flipped][partition], Y)) >> 4;
                    MEMBER(mean_quant[flipped][partition], Z) = UCHAR(MEMBER(mean[flipped][partition], Z)) >> 4;

                    min_index[flipped][partition] = 0;
                    max_index[flipped][partition] = 0;

                    while ( ((int)MEMBER(mean_quant[flipped][partition], X) + min_index[flipped][partition] > 0) &&
                        ((int)MEMBER(mean_quant[flipped][partition], Y) + min_index[flipped][partition] > 0) &&
                        ((int)MEMBER(mean_quant[flipped][partition], Z) + min_index[flipped][partition] > 0))
                    {
                        min_index[flipped][partition]--;
                        distance++;
                        if (distance > max_distance)
                            break;
                    }
                    distance = 0;
                    while ( ((int)MEMBER(mean_quant[flipped][partition], X) + max_index[flipped][partition] < 16) &&
                        ((int)MEMBER(mean_quant[flipped][partition], Y) + max_index[flipped][partition] < 16) &&
                        ((int)MEMBER(mean_quant[flipped][partition], Z) + max_index[flipped][partition] < 16))
                    {
                        max_index[flipped][partition]++;
                        distance++;
                        if (distance > max_distance)
                            break;
                    }
                }
            }
#if 1
            for (flipped = 0; flipped < 2; flipped++)
            {
                for (partition = 0; partition < 2; partition++)
                {
                    int ip0;
                    for (ip0 = min_index[flipped][partition]; ip0 <= max_index[flipped][partition]; ip0++)
                    {
                        uchar3 l0_quant;
                        float err;

                        MEMBER(l0_quant, X) = UCHAR(MEMBER(mean_quant[flipped][partition], X) + ip0);
                        MEMBER(l0_quant, Y) = UCHAR(MEMBER(mean_quant[flipped][partition], Y) + ip0);
                        MEMBER(l0_quant, Z) = UCHAR(MEMBER(mean_quant[flipped][partition], Z) + ip0);

                        err = ETC_EvaluateErrorWeighted(is_ypbpr, trans_pixel, weight, ETC_RGBExpandVecTo4Bit(l0_quant), &g_partition_indexes[flipped][partition][0]);

                        if (err < fixed_err_group[flipped][partition])
                        {
                            fixed_err_group[flipped][partition] = err;
                            fixed_positions_group[flipped][partition] = l0_quant;
                        }
                    }
                }
            }

            if (fixed_err_group[0][0] + fixed_err_group[0][1] < fixed_err_group[1][0] + fixed_err_group[1][1])
            {
                fixed_err = fixed_err_group[0][0] + fixed_err_group[0][1];
                best_positions[0] = fixed_positions_group[0][0];
                best_positions[1] = fixed_positions_group[0][1];
                best_flipped = 0;
            }
            else
            {
                fixed_err = fixed_err_group[1][0] + fixed_err_group[1][1];
                best_positions[0] = fixed_positions_group[1][0];
                best_positions[1] = fixed_positions_group[1][1];
                best_flipped = 1;
            }

            found_fixed = 1;
            if (found_fixed)
            {
                uchar3 best_pos[2];
                float combined_err = 0.0f;

                best_pos[0] = best_positions[0];
                best_pos[1] = best_positions[1];

                for (partition = 0; partition < 2; partition++)
                {
                    int neighbourhood_width = (quality == CODEC_QUALITY_BEST ? 3 : 1);
                    float best_err = MAX_INIT_ERROR;
                    int x;
                    int y;
                    int z;
                    int min_x = MEMBER(best_positions[partition], X) > (neighbourhood_width - 1) ? MEMBER(best_positions[partition], X) - neighbourhood_width : 0;
                    int min_y = MEMBER(best_positions[partition], Y) > (neighbourhood_width - 1) ? MEMBER(best_positions[partition], Y) - neighbourhood_width : 0;
                    int min_z = MEMBER(best_positions[partition], Z) > (neighbourhood_width - 1) ? MEMBER(best_positions[partition], Z) - neighbourhood_width : 0;
                    int max_x = MEMBER(best_positions[partition], X) < (15 - neighbourhood_width) ? MEMBER(best_positions[partition], X) + neighbourhood_width : 15;
                    int max_y = MEMBER(best_positions[partition], Y) < (15 - neighbourhood_width) ? MEMBER(best_positions[partition], Y) + neighbourhood_width : 15;
                    int max_z = MEMBER(best_positions[partition], Z) < (15 - neighbourhood_width) ? MEMBER(best_positions[partition], Z) + neighbourhood_width : 15;

                    for (z = min_z; z <= max_z; z++)
                        for (y = min_y; y <= max_y; y++)
                            for (x = min_x; x <= max_x; x++)
                            {
                                uchar3 pos = UCHAR3(x, y, z);
                                float err;
                                pos = ETC_RGBExpandVecTo4Bit(pos);
                                err = ETC_EvaluateErrorWeighted(is_ypbpr, trans_pixel, weight, pos, &g_partition_indexes[best_flipped][partition][0]);
                                if (err < best_err)
                                {
                                    best_err = err;
                                    best_pos[partition] = UCHAR3(x, y, z);
                                }
                            }
                    combined_err += best_err;
                }
                best_positions[0] = best_pos[0];
                best_positions[1] = best_pos[1];

                fixed_err = combined_err;

                for (partition = 0; partition < 2; partition++)
                {
                    int terminate = 0;
                    uchar3 pos = best_positions[partition];

                    if (quality != CODEC_QUALITY_BEST)
                        terminate = 1;

                    while(!terminate)
                    {
                        short3 test_pos[27];
                        float dist[27];
                        int best_index;
                        float best_dist;
                        int terminate_count = 0;

                        for (j = 0; j < 27; j++)
                            test_pos[j] = SHORT3(MEMBER(pos, X), MEMBER(pos, Y), MEMBER(pos, Z)) + SHORT3((j % 3) - 1, ((j / 3) % 3) - 1, j/9 - 1);

                        for (j = 0; j < 27; j++)
                        {
                            if ((MEMBER(test_pos[j], X) > 15) || (MEMBER(test_pos[j], Y) > 15) || (MEMBER(test_pos[j], Z) > 15) || (MEMBER(test_pos[j], X) < 0) || (MEMBER(test_pos[j], Y) < 0) || (MEMBER(test_pos[j], Z) < 0))
                                dist[j] = MAX_INIT_ERROR;
                            else
                            {
                                uchar3 v;

                                v = ETC_RGBExpandVecTo4Bit(UCHAR3(MEMBER(test_pos[j], X), MEMBER(test_pos[j], Y), MEMBER(test_pos[j], Z)));

                                dist[j] = ETC_EvaluateErrorWeighted(is_ypbpr, trans_pixel, weight, ETC_RGBExpandVecTo4Bit(v), &g_partition_indexes[best_flipped][partition][0]);
                            }
                        }

                        best_dist = dist[0];
                        best_index = 0;
                        for (j = 1; j < 27; j++)
                        {
                            if (dist[j] < best_dist)
                            {
                                best_dist = dist[j];
                                best_index = j;
                            }
                        }

                        best_positions[partition] = pos;

                        if (dist[13] == best_dist)
                            break;

                        for (j = 0; j < 27; j++)
                            if (dist[j] == MAX_INIT_ERROR)
                                terminate_count++;

                        if (terminate_count >= 26)
                            break;

                        pos = UCHAR3(MEMBER(test_pos[best_index], X), MEMBER(test_pos[best_index], Y), MEMBER(test_pos[best_index], Z));
                    }
                }
            }

            if (found_fixed && fixed_err < best_total_error)
            {
                enc_mode = ETC_ENC_MODE_NODELTA;
                best_total_error = fixed_err;
                params_partition.rgb[0] = ETC_RGBExpandVecTo4Bit(best_positions[0]);
                params_partition.rgb[1] = ETC_RGBExpandVecTo4Bit(best_positions[1]);
                params_partition.is_flipped = best_flipped;
            }
        }
#endif

        // Non-delta mode
        ETC_PrepareSampleList(1, sample_list);

        for (flipped = 0; flipped < 2; flipped++)
        {
            for (partition = 0; partition < 2; partition++)
            {
                etc_sample_t sample;
                float offset = 0.0f;

                if (quality == CODEC_QUALITY_NORMAL)
                    offset = 0.0f;
                else if (quality == CODEC_QUALITY_HIGH)
                    offset = 48.0f;
                else 
                    offset = 96.0f;

                if ((quality == CODEC_QUALITY_NORMAL) || (quality == CODEC_QUALITY_HIGH))
                {
                    MEMBER(proj_mins, X) = UCHAR(((uint)clamp(MEMBER(projected_mins[flipped][partition], X) - offset, 0.0f, 255.0f)) >> 4);
                    MEMBER(proj_mins, Y) = UCHAR(((uint)clamp(MEMBER(projected_mins[flipped][partition], Y) - offset, 0.0f, 255.0f)) >> 4);
                    MEMBER(proj_mins, Z) = UCHAR(((uint)clamp(MEMBER(projected_mins[flipped][partition], Z) - offset, 0.0f, 255.0f)) >> 4);
                    MEMBER(proj_maxs, X) = UCHAR(((uint)clamp(MEMBER(projected_maxs[flipped][partition], X) + offset + 7, 0.0f, 255.0f)) >> 4);
                    MEMBER(proj_maxs, Y) = UCHAR(((uint)clamp(MEMBER(projected_maxs[flipped][partition], Y) + offset + 7, 0.0f, 255.0f)) >> 4);
                    MEMBER(proj_maxs, Z) = UCHAR(((uint)clamp(MEMBER(projected_maxs[flipped][partition], Z) + offset + 7, 0.0f, 255.0f)) >> 4);
                }
                else
                {
                    proj_mins = UCHAR3(0, 0, 0);
                    proj_maxs = UCHAR3(15, 15, 15);
                }

                sample.pos_quantised = proj_mins;
                pathing_params.partition_indexes = &g_partition_indexes[flipped][partition][0];
                sample.error = ETC_EvaluateErrorWeighted(is_ypbpr, trans_pixel, weight, ETC_RGBExpandVecTo4Bit(sample.pos_quantised), &g_partition_indexes[flipped][partition][0]);
                ETC_LeastCostDirectedPathWeighted(1, 1, error_target, refine_search, is_ypbpr, trans_pixel, weight, sample, &sample_list[flipped][partition][0], MEMBER(proj_maxs, X), MEMBER(proj_maxs, Y), MEMBER(proj_maxs, Z), &pathing_params, ETC_RGBEXPANDVECTO4BIT, ETC_EVALUATEDELTAERRORGENERICWEIGHTED);
            }
        }

        for (i = 0; i < 2; i++)
            best_dist[i] = sample_list[i][0][0].error + sample_list[i][1][0].error;

        if (best_dist[1] < best_dist[0])
            is_non_delta_flipped = 1;
        else
            is_non_delta_flipped = 0;

        if (best_dist[is_non_delta_flipped] < best_total_error)
        {
            best_total_error = best_dist[is_non_delta_flipped];

            enc_mode = ETC_ENC_MODE_NODELTA;
            params_partition.rgb[0] = ETC_RGBExpandVecTo4Bit(sample_list[is_non_delta_flipped][0][0].pos_quantised);
            params_partition.rgb[1] = ETC_RGBExpandVecTo4Bit(sample_list[is_non_delta_flipped][1][0].pos_quantised);
            params_partition.is_flipped = is_non_delta_flipped;
        }

        ETC_GetOptimalIndexesWeighted(is_ypbpr, trans_pixel, weight, params_partition.rgb[0], &g_partition_indexes[params_partition.is_flipped][0][0], &params_partition.table[0], params_partition.indexes);
        ETC_GetOptimalIndexesWeighted(is_ypbpr, trans_pixel, weight, params_partition.rgb[1], &g_partition_indexes[params_partition.is_flipped][1][0], &params_partition.table[1], params_partition.indexes);
    }

    if (is_etc2)
    {
        if ((best_total_error > error_target) && (allowed_modes & (ETC_MODE_T | ETC_MODE_H)))
        {
            int set_indexes[2][16];
            int set_count[2];
            etc_sample_t sample;

            ETC_KMeansTHMode(trans_pixel, &set_indexes[0][0], &set_indexes[1][0], &set_count[0]); // TODO: this should be weighted

            for (partition = 0; partition < 2; partition++) // TODO: this should be weighted
            {
                float3 mean = VFLOAT3(0.0f, 0.0f, 0.0f);
                float mins_maxs_dist[2];

                for (i = 0; i < set_count[partition]; i++)
                    mean = mean + trans_pixel[set_indexes[partition][i]];

                mean = mean / (set_count[partition] ? (float)(set_count[partition]) : 1.0f);

                if (set_count[partition])
                {
                    mins_maxs_dist[0] = dot(trans_pixel[set_indexes[partition][0]] - mean, VFLOAT3(0.57735f, 0.57735f, 0.57735f));
                    mins_maxs_dist[1] = mins_maxs_dist[0];

                    for (i = 0; i < set_count[partition]; i++)
                    {
                        float dist = dot(trans_pixel[set_indexes[partition][i]] - mean, VFLOAT3(0.57735f, 0.57735f, 0.57735f));

                        if (dist < mins_maxs_dist[0])
                            mins_maxs_dist[0] = dist;
                        if (dist > mins_maxs_dist[1])
                            mins_maxs_dist[1] = dist;
                    }
                    projected_mins[0][partition] = mean + VFLOAT3(0.57735f, 0.57735f, 0.57735f) * mins_maxs_dist[0];
                    projected_maxs[0][partition] = mean + VFLOAT3(0.57735f, 0.57735f, 0.57735f) * mins_maxs_dist[1];
                }
                else
                {
                    projected_mins[0][partition] = mean;
                    projected_maxs[0][partition] = mean;
                }
            }

            if (allowed_modes & ETC_MODE_T)
            {
                // T mode
                ETC_PrepareSampleList(1, sample_list);
                for (flipped = 0; flipped < 2; flipped++)
                {
                    etc_sample_t sample;
                    uchar3 proj_mins;
                    uchar3 proj_maxs;
                    float offset = 0.0f;

                    if (quality == CODEC_QUALITY_NORMAL)
                        offset = 0.0f;
                    else if (quality == CODEC_QUALITY_HIGH)
                        offset = 48.0f;
                    else 
                        offset = 96.0f;

                    if ((quality == CODEC_QUALITY_NORMAL) || (quality == CODEC_QUALITY_HIGH))
                    {
                        MEMBER(proj_mins, X) = UCHAR(((uint)clamp(MEMBER(projected_mins[0][flipped], X) - offset, 0.0f, 255.0f)) >> 4);
                        MEMBER(proj_mins, Y) = UCHAR(((uint)clamp(MEMBER(projected_mins[0][flipped], Y) - offset, 0.0f, 255.0f)) >> 4);
                        MEMBER(proj_mins, Z) = UCHAR(((uint)clamp(MEMBER(projected_mins[0][flipped], Z) - offset, 0.0f, 255.0f)) >> 4);
                        MEMBER(proj_maxs, X) = UCHAR(((uint)clamp(MEMBER(projected_maxs[0][flipped], X) + offset + 7, 0.0f, 255.0f)) >> 4);
                        MEMBER(proj_maxs, Y) = UCHAR(((uint)clamp(MEMBER(projected_maxs[0][flipped], Y) + offset + 7, 0.0f, 255.0f)) >> 4);
                        MEMBER(proj_maxs, Z) = UCHAR(((uint)clamp(MEMBER(projected_maxs[0][flipped], Z) + offset + 7, 0.0f, 255.0f)) >> 4);
                    }
                    else
                    {
                        proj_mins = UCHAR3(0, 0, 0);
                        proj_maxs = UCHAR3(15, 15, 15);
                    }

                    sample.pos_quantised = proj_mins;
                    pathing_params.indexes = set_indexes[flipped];
                    pathing_params.num_indexes = set_count[flipped];
                    sample.error = ETC_EvaluateErrorTSingleWeighted(is_ypbpr, trans_pixel, weight, ETC_RGBExpandVecTo4Bit(sample.pos_quantised), set_indexes[flipped], set_count[flipped]);
                    ETC_LeastCostDirectedPathWeighted(1, 1, error_target, refine_search, is_ypbpr, trans_pixel, weight, sample, &sample_list[flipped][0][0], MEMBER(proj_maxs, X), MEMBER(proj_maxs, Y), MEMBER(proj_maxs, Z), &pathing_params, ETC_RGBEXPANDVECTO4BIT, ETC_EVALUATETSINGLEERRORGENERICWEIGHTED);

                    if ((quality == CODEC_QUALITY_NORMAL) || (quality == CODEC_QUALITY_HIGH))
                    {
                        MEMBER(proj_mins, X) = UCHAR(((uint)clamp(MEMBER(projected_mins[0][(flipped + 1) % 2], X) - offset, 0.0f, 255.0f)) >> 4);
                        MEMBER(proj_mins, Y) = UCHAR(((uint)clamp(MEMBER(projected_mins[0][(flipped + 1) % 2], Y) - offset, 0.0f, 255.0f)) >> 4);
                        MEMBER(proj_mins, Z) = UCHAR(((uint)clamp(MEMBER(projected_mins[0][(flipped + 1) % 2], Z) - offset, 0.0f, 255.0f)) >> 4);
                        MEMBER(proj_maxs, X) = UCHAR(((uint)clamp(MEMBER(projected_maxs[0][(flipped + 1) % 2], X) + offset + 7, 0.0f, 255.0f)) >> 4);
                        MEMBER(proj_maxs, Y) = UCHAR(((uint)clamp(MEMBER(projected_maxs[0][(flipped + 1) % 2], Y) + offset + 7, 0.0f, 255.0f)) >> 4);
                        MEMBER(proj_maxs, Z) = UCHAR(((uint)clamp(MEMBER(projected_maxs[0][(flipped + 1) % 2], Z) + offset + 7, 0.0f, 255.0f)) >> 4);
                    }
                    else
                    {
                        proj_mins = UCHAR3(0, 0, 0);
                        proj_maxs = UCHAR3(15, 15, 15);
                    }

                    sample.pos_quantised = proj_mins;
                    pathing_params.indexes = set_indexes[(flipped + 1) % 2];
                    pathing_params.num_indexes = set_count[(flipped + 1) % 2];
                    sample.error = ETC_EvaluateErrorTTripleWeighted(is_ypbpr, trans_pixel, weight, ETC_RGBExpandVecTo4Bit(sample.pos_quantised), set_indexes[(flipped + 1) % 2], set_count[(flipped + 1) % 2]);
                    ETC_LeastCostDirectedPathWeighted(1, 1, error_target, refine_search, is_ypbpr, trans_pixel, weight, sample, &sample_list[flipped][1][0], MEMBER(proj_maxs, X), MEMBER(proj_maxs, Y), MEMBER(proj_maxs, Z), &pathing_params, ETC_RGBEXPANDVECTO4BIT, ETC_EVALUATETTRIPLEERRORGENERICWEIGHTED);

                }
                for (i = 0; i < 2; i++)
                    best_dist[i] = sample_list[i][0][0].error + sample_list[i][1][0].error;

                if ((best_dist[0] < best_total_error) || (best_dist[1] < best_total_error))
                {
                    enc_mode = ETC_ENC_MODE_T;

                    if (best_dist[1] < best_dist[0])
                        is_flipped = 1;
                    else
                        is_flipped = 0;

                    params_th.rgb[0] = ETC_RGBExpandVecTo4Bit(sample_list[is_flipped][0][0].pos_quantised);
                    params_th.rgb[1] = ETC_RGBExpandVecTo4Bit(sample_list[is_flipped][1][0].pos_quantised);

                    float d = ETC_GetOptimalTIndexesWeighted(is_ypbpr, trans_pixel, weight, params_th.rgb[0], params_th.rgb[1], &params_th.indexes[0], &params_th.table);

                    best_total_error = d;
                }
            }

            if ((best_total_error > error_target) && (allowed_modes & ETC_MODE_H))
            {
                int best_mode;

                // H-Mode
                ETC_PrepareSampleList(1, sample_list);
                for (flipped = 0; flipped < 2; flipped++)
                {
                    uchar3 proj_mins;
                    uchar3 proj_maxs;
                    float offset = 0.0f;

                    if (quality == CODEC_QUALITY_NORMAL)
                        offset = 0.0f;
                    else if (quality == CODEC_QUALITY_HIGH)
                        offset = 48.0f;
                    else 
                        offset = 96.0f;

                    if ((quality == CODEC_QUALITY_NORMAL) || (quality == CODEC_QUALITY_HIGH))
                    {
                        MEMBER(proj_mins, X) = UCHAR(((uint)clamp(MEMBER(projected_mins[0][flipped], X) - offset, 0.0f, 255.0f)) >> 4);
                        MEMBER(proj_mins, Y) = UCHAR(((uint)clamp(MEMBER(projected_mins[0][flipped], Y) - offset, 0.0f, 255.0f)) >> 4);
                        MEMBER(proj_mins, Z) = UCHAR(((uint)clamp(MEMBER(projected_mins[0][flipped], Z) - offset, 0.0f, 255.0f)) >> 4);
                        MEMBER(proj_maxs, X) = UCHAR(((uint)clamp(MEMBER(projected_maxs[0][flipped], X) + offset + 7, 0.0f, 255.0f)) >> 4);
                        MEMBER(proj_maxs, Y) = UCHAR(((uint)clamp(MEMBER(projected_maxs[0][flipped], Y) + offset + 7, 0.0f, 255.0f)) >> 4);
                        MEMBER(proj_maxs, Z) = UCHAR(((uint)clamp(MEMBER(projected_maxs[0][flipped], Z) + offset + 7, 0.0f, 255.0f)) >> 4);
                    }
                    else
                    {
                        proj_mins = UCHAR3(0, 0, 0);
                        proj_maxs = UCHAR3(15, 15, 15);
                    }
                    for (table = 0; table < 8; table++)
                    {
                        sample.pos_quantised = proj_mins;
                        pathing_params.indexes = set_indexes[flipped];
                        pathing_params.num_indexes = set_count[flipped];
                        pathing_params.mode = table;
                        sample.error = ETC_EvaluateErrorHWeighted(is_ypbpr, trans_pixel, weight, ETC_RGBExpandVecTo4Bit(sample.pos_quantised), set_indexes[flipped], set_count[flipped], table);
                        ETC_LeastCostDirectedPathWeighted(1, 1, error_target, refine_search, is_ypbpr, trans_pixel, weight, sample, &sample_list[flipped][table][0], MEMBER(proj_maxs, X), MEMBER(proj_maxs, Y), MEMBER(proj_maxs, Z), &pathing_params, ETC_RGBEXPANDVECTO4BIT, ETC_EVALUATEHERRORGENERICWEIGHTED);
                    }
                }

                best_dist[0] = sample_list[0][0][0].error + sample_list[1][0][0].error;
                best_mode = 0;

                for (flipped = 0; flipped < 2; flipped++)
                    for (table = 0; table < 8; table++)
                        if (sample_list[0][table][0].error + sample_list[1][table][0].error < best_dist[0])
                        {
                            best_dist[0] = sample_list[0][table][0].error + sample_list[1][table][0].error;
                            best_mode = table;
                        }

                if (best_dist[0] < best_total_error)
                {
                    ushort rgbpacked[2];

                    enc_mode = ETC_ENC_MODE_H;

                    params_th.table = best_mode;

                    if ((MEMBER(sample_list[0][params_th.table][0].pos_quantised, X) == MEMBER(sample_list[1][params_th.table][0].pos_quantised, X)) &&
                        (MEMBER(sample_list[0][params_th.table][0].pos_quantised, Y) == MEMBER(sample_list[1][params_th.table][0].pos_quantised, Y)) &&
                        (MEMBER(sample_list[0][params_th.table][0].pos_quantised, Z) == MEMBER(sample_list[1][params_th.table][0].pos_quantised, Z)))
                        MEMBER(sample_list[0][params_th.table][0].pos_quantised, X) = (MEMBER(sample_list[0][params_th.table][0].pos_quantised, X) + 1) % 16;

                    params_th.rgb[0] = ETC_RGBExpandVecTo4Bit(sample_list[0][params_th.table][0].pos_quantised);
                    params_th.rgb[1] = ETC_RGBExpandVecTo4Bit(sample_list[1][params_th.table][0].pos_quantised);

                    rgbpacked[0] =  (((ushort)MEMBER(sample_list[0][params_th.table][0].pos_quantised, X)) << 8) |
                        (((ushort)MEMBER(sample_list[0][params_th.table][0].pos_quantised, Y)) << 4) |
                        (((ushort)MEMBER(sample_list[0][params_th.table][0].pos_quantised, Z)) << 0);

                    rgbpacked[1] =  (((ushort)MEMBER(sample_list[1][params_th.table][0].pos_quantised, X)) << 8) |
                        (((ushort)MEMBER(sample_list[1][params_th.table][0].pos_quantised, Y)) << 4) |
                        (((ushort)MEMBER(sample_list[1][params_th.table][0].pos_quantised, Z)) << 0);

                    if (!(params_th.table & 1))
                    {
                        if (rgbpacked[0] > rgbpacked[1])
                        {
                            params_th.rgb[0] = ETC_RGBExpandVecTo4Bit(sample_list[1][params_th.table][0].pos_quantised);
                            params_th.rgb[1] = ETC_RGBExpandVecTo4Bit(sample_list[0][params_th.table][0].pos_quantised);
                        }
                    }
                    else
                    {
                        if (rgbpacked[0] < rgbpacked[1])
                        {
                            params_th.rgb[0] = ETC_RGBExpandVecTo4Bit(sample_list[1][params_th.table][0].pos_quantised);
                            params_th.rgb[1] = ETC_RGBExpandVecTo4Bit(sample_list[0][params_th.table][0].pos_quantised);
                        }
                    }

                    best_total_error = ETC_GetOptimalHIndexesWeighted(is_ypbpr, trans_pixel, weight, params_th.rgb[0], params_th.rgb[1], params_th.indexes, params_th.table);
                }
            }
        }

        if ((best_total_error != 0.0f) && (allowed_modes & ETC_MODE_PLANAR))
        {
            // Planar mode: always check this because it's so cheap to compute

            float3 points[3];
            int3 points_i32[3];
            float index_best_dist[3];
            float best_dist = 0.0f;
            int best_twiddle[3][3];
            int index;
            int twiddle0;
            int twiddle1;
            int twiddle2;
            const float coeff[3][16] =
            {
                {23.0f, 17.0f, 11.0f, 5.0f, 17.0f, 11.0f, 5.0f, -1.0f, 11.0f, 5.0f, -1.0f, -7.0f, 5.0f, -1.0f, -7.0f, -13.0f},
                {-1.0f, 9.0f, 19.0f, 29.0f, -7.0f, 3.0f, 13.0f, 23.0f, -13.0f, -3.0f, 7.0f, 17.0f, -19.0f, -9.0f, 1.0f, 11.0f},
                {-1.0f, -7.0f, -13.0f, -19.0f, 9.0f, 3.0f, -3.0f, -9.0f, 19.0f, 13.0f, 7.0f, 1.0f, 29.0f, 23.0f, 17.0f, 11.0f}
            };

            points[0] = VFLOAT3(0.0f, 0.0f, 0.0f);
            points[1] = VFLOAT3(0.0f, 0.0f, 0.0f);
            points[2] = VFLOAT3(0.0f, 0.0f, 0.0f);

            // TODO: this isn't trivial for the YCBCR case, just minimise in RGB space for now
            if (is_ypbpr)
                for (i = 0; i < 16; i++)
                    trans_pixel[i] = clamp(ETC_ConvertToRGBf3(trans_pixel[i]), 0.0f, 255.0f);

            for (j = 0; j < 16; j++)
            {
                MEMBER(points[0], X) += coeff[0][j] * MEMBER(trans_pixel[j], X) * weight[j];
                MEMBER(points[1], X) += coeff[1][j] * MEMBER(trans_pixel[j], X) * weight[j];
                MEMBER(points[2], X) += coeff[2][j] * MEMBER(trans_pixel[j], X) * weight[j];

                MEMBER(points[0], Y) += coeff[0][j] * MEMBER(trans_pixel[j], Y) * weight[j];
                MEMBER(points[1], Y) += coeff[1][j] * MEMBER(trans_pixel[j], Y) * weight[j];
                MEMBER(points[2], Y) += coeff[2][j] * MEMBER(trans_pixel[j], Y) * weight[j];

                MEMBER(points[0], Z) += coeff[0][j] * MEMBER(trans_pixel[j], Z) * weight[j];
                MEMBER(points[1], Z) += coeff[1][j] * MEMBER(trans_pixel[j], Z) * weight[j];
                MEMBER(points[2], Z) += coeff[2][j] * MEMBER(trans_pixel[j], Z) * weight[j];
            }

            points[0] = points[0] * (1.0f / 80.0f);
            points[1] = points[1] * (1.0f / 80.0f);
            points[2] = points[2] * (1.0f / 80.0f);

            points[0] = clamp(points[0], 0.0f, 255.0f);
            points[1] = clamp(points[1], 0.0f, 255.0f);
            points[2] = clamp(points[2], 0.0f, 255.0f);

            points_i32[0] = INT3(ETC_RGBRoundTo6Bit((uchar)MEMBER(points[0], X)), ETC_RGBRoundTo7Bit((uchar)MEMBER(points[0], Y)), ETC_RGBRoundTo6Bit((uchar)MEMBER(points[0], Z)));
            points_i32[1] = INT3(ETC_RGBRoundTo6Bit((uchar)MEMBER(points[1], X)), ETC_RGBRoundTo7Bit((uchar)MEMBER(points[1], Y)), ETC_RGBRoundTo6Bit((uchar)MEMBER(points[1], Z)));
            points_i32[2] = INT3(ETC_RGBRoundTo6Bit((uchar)MEMBER(points[2], X)), ETC_RGBRoundTo7Bit((uchar)MEMBER(points[2], Y)), ETC_RGBRoundTo6Bit((uchar)MEMBER(points[2], Z)));

            for (index = 0; index < 3; index++)
                index_best_dist[index] = MAX_INIT_ERROR;

            for (twiddle0 = -2; twiddle0 <= 2; twiddle0++)
            {
                for (twiddle1 = -2; twiddle1 <= 2; twiddle1++)
                {
                    for (twiddle2 = -2; twiddle2 <= 2; twiddle2++)
                    {
                        int ppoints[3][3];
                        float comp_err[3];
                        int comb;

                        comb =  (MEMBER(points_i32[0], X) + twiddle0 * 4) | (MEMBER(points_i32[1], X) + twiddle1 * 4) | (MEMBER(points_i32[2], X) + twiddle2 * 4) |
                            (MEMBER(points_i32[0], Y) + twiddle0 * 2) | (MEMBER(points_i32[1], Y) + twiddle1 * 2) | (MEMBER(points_i32[2], Y) + twiddle2 * 2) |
                            (MEMBER(points_i32[0], Z) + twiddle0 * 4) | (MEMBER(points_i32[1], Z) + twiddle1 * 4) | (MEMBER(points_i32[2], Z) + twiddle2 * 4);

                        // trick: this tests if any of the values has negative sign or is >255, halving the number of comparisons needed
                        if (comb & 0xFFFFFF00)
                            continue;

                        ppoints[0][0] = ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[0], X) + twiddle0 * 4));
                        ppoints[0][1] = ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[1], X) + twiddle1 * 4));
                        ppoints[0][2] = ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[2], X) + twiddle2 * 4));

                        ppoints[1][0] = ETC_RGBRoundTo7Bit(UCHAR(MEMBER(points_i32[0], Y) + twiddle0 * 2));
                        ppoints[1][1] = ETC_RGBRoundTo7Bit(UCHAR(MEMBER(points_i32[1], Y) + twiddle1 * 2));
                        ppoints[1][2] = ETC_RGBRoundTo7Bit(UCHAR(MEMBER(points_i32[2], Y) + twiddle2 * 2));

                        ppoints[2][0] = ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[0], Z) + twiddle0 * 4));
                        ppoints[2][1] = ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[1], Z) + twiddle1 * 4));
                        ppoints[2][2] = ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[2], Z) + twiddle2 * 4));

                        comp_err[0] = 0.0f;
                        comp_err[1] = 0.0f;
                        comp_err[2] = 0.0f;

                        for (j = 0; j < 4; j++) // v
                        {
                            for (i = 0; i < 4; i++) // u
                            {
                                float3 v;

                                MEMBER(v, X) = (float)((i * (ppoints[0][1] - ppoints[0][0]) + j * (ppoints[0][2] - ppoints[0][0]) + 4 * (ppoints[0][0]) + 2) >> 2);
                                MEMBER(v, Y) = (float)((i * (ppoints[1][1] - ppoints[1][0]) + j * (ppoints[1][2] - ppoints[1][0]) + 4 * (ppoints[1][0]) + 2) >> 2);
                                MEMBER(v, Z) = (float)((i * (ppoints[2][1] - ppoints[2][0]) + j * (ppoints[2][2] - ppoints[2][0]) + 4 * (ppoints[2][0]) + 2) >> 2);

                                v = clamp(v, VFLOAT3(0.0f, 0.0f, 0.0f), VFLOAT3(255.0f, 255.0f, 255.0f));
                                v = v - trans_pixel[j*4 + i];

                                comp_err[0] += MEMBER(v, X) * MEMBER(v, X) * weight[j*4 + i];
                                comp_err[1] += MEMBER(v, Y) * MEMBER(v, Y) * weight[j*4 + i];
                                comp_err[2] += MEMBER(v, Z) * MEMBER(v, Z) * weight[j*4 + i];
                            }
                        }
                        for (index = 0; index < 3; index++)
                        {
                            if (comp_err[index] < index_best_dist[index])
                            {
                                int scale = (index == 1 ? 2 : 4);
                                best_twiddle[index][0] = twiddle0 * scale;
                                best_twiddle[index][1] = twiddle1 * scale;
                                best_twiddle[index][2] = twiddle2 * scale;
                                index_best_dist[index] = comp_err[index];
                            }
                        }
                    }
                }
            }
            best_dist = index_best_dist[0] + index_best_dist[1] + index_best_dist[2];

            if (best_dist < best_total_error)
            {
                params_planar.rgb[0] = UCHAR3(ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[0], X) + best_twiddle[0][0])), ETC_RGBRoundTo7Bit(UCHAR(MEMBER(points_i32[0], Y) + best_twiddle[1][0])), ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[0], Z) + best_twiddle[2][0])));
                params_planar.rgb[1] = UCHAR3(ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[1], X) + best_twiddle[0][1])), ETC_RGBRoundTo7Bit(UCHAR(MEMBER(points_i32[1], Y) + best_twiddle[1][1])), ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[1], Z) + best_twiddle[2][1])));
                params_planar.rgb[2] = UCHAR3(ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[2], X) + best_twiddle[0][2])), ETC_RGBRoundTo7Bit(UCHAR(MEMBER(points_i32[2], Y) + best_twiddle[1][2])), ETC_RGBRoundTo6Bit(UCHAR(MEMBER(points_i32[2], Z) + best_twiddle[2][2])));

                enc_mode = ETC_ENC_MODE_PLANAR;

                best_total_error = best_dist;
            }
        }
    }

    if ((enc_mode == ETC_ENC_MODE_DELTA) || (enc_mode == ETC_ENC_MODE_NODELTA))
    {
        if (enc_mode == ETC_ENC_MODE_NODELTA)
        {
            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], X) >> 4, 28, 4);
            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[1], X) >> 4, 24, 4);
            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], Y) >> 4, 20, 4);
            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[1], Y) >> 4, 16, 4);
            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], Z) >> 4, 12, 4);
            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[1], Z) >> 4,  8, 4);
            ETC_WriteBits(local_block, 0, 1, 1); // diff bit
        }
        else
        {
            int3 diff;

            MEMBER(diff, X) = (MEMBER(params_partition.rgb[1], X) >> 3) - (MEMBER(params_partition.rgb[0], X) >> 3);
            MEMBER(diff, Y) = (MEMBER(params_partition.rgb[1], Y) >> 3) - (MEMBER(params_partition.rgb[0], Y) >> 3);
            MEMBER(diff, Z) = (MEMBER(params_partition.rgb[1], Z) >> 3) - (MEMBER(params_partition.rgb[0], Z) >> 3);

            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], X) >> 3, 27, 5);
            ETC_WriteBits(local_block, MEMBER(diff, X) >> 0, 24, 3);
            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], Y) >> 3, 19, 5);
            ETC_WriteBits(local_block, MEMBER(diff, Y) >> 0, 16, 3);
            ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], Z) >> 3, 11, 5);
            ETC_WriteBits(local_block, MEMBER(diff, Z) >> 0,  8, 3);
            ETC_WriteBits(local_block, 1, 1, 1); // diff bit
        }
        ETC_WriteBits(local_block, params_partition.table[0], 5, 3); // table codeword 1
        ETC_WriteBits(local_block, params_partition.table[1], 2, 3); // table codeword 2
        ETC_WriteBits(local_block, params_partition.is_flipped, 0, 1); // flip bit

        for (i = 0; i < 16; i++)
        {
            int index = (i%4)*4 + i/4;

            int idx = params_partition.indexes[i];

            ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);
            ETC_WriteBits(local_block, idx & 1, 32 + index, 1);

        }
        ETC_PackBlockSwapOrder(block, local_block);
    }
    if (is_etc2)
    {
        if (enc_mode == ETC_ENC_MODE_T)
        {
            int min_rd = -4 + ((MEMBER(params_th.rgb[0], X) >> 4) & 3);
            int max_rd = ((MEMBER(params_th.rgb[0], X) >> 4) & 3);
            int min_r = (MEMBER(params_th.rgb[0], X) >> 6) & 3;
            int max_r = 28 + min_r;
            uchar r;
            uchar rd;

            if (min_rd + min_r < 0)
            {
                r = UCHAR(min_r);
                rd = UCHAR(min_rd);
            }
            else
            {
                r = UCHAR(max_r);
                rd = UCHAR(max_rd);
            }

            ETC_WriteBits(local_block, r, 27, 5);
            ETC_WriteBits(local_block, rd, 24, 3);
            ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Y) >> 4, 20, 4);
            ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Z) >> 4, 16, 4);
            ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], X) >> 4, 12, 4);
            ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Y) >> 4,  8, 4);
            ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Z) >> 4,  4, 4);

            ETC_WriteBits(local_block, (params_th.table >> 1) & 3, 2, 2);
            ETC_WriteBits(local_block, 1, 1, 1); // diff bit
            ETC_WriteBits(local_block, params_th.table & 1, 0, 1); // flip bit

            for (i = 0; i < 16; i++)
            {
                int index = (i % 4) * 4 + i / 4;

                int idx = params_th.indexes[i];

                ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);
                ETC_WriteBits(local_block, idx & 1, 32 + index, 1);

            }
            ETC_PackBlockSwapOrder(block, local_block);
        }
        else if (enc_mode == ETC_ENC_MODE_H)
        {
            int min_gd = -4 + ((MEMBER(params_th.rgb[0], Z) >> 5) & 3);
            int max_gd = ((MEMBER(params_th.rgb[0], Z) >> 5) & 3);
            int min_g = ((MEMBER(params_th.rgb[0], Z) >> 7) & 1) | (((MEMBER(params_th.rgb[0], Y) >> 4) & 1) << 1);
            int max_g = 28 + min_g;
            uchar g;
            uchar gd;
            int rd;

            if (min_gd + min_g < 0)
            {
                g = UCHAR(min_g);
                gd = UCHAR(min_gd);
            }
            else
            {
                g = UCHAR(max_g);
                gd = UCHAR(max_gd);
            }

            rd = MEMBER(params_th.rgb[0], Y) >> 5;
            if (rd >= 4)
                rd = -4 + (rd & 3);

            if ((int)(MEMBER(params_th.rgb[0], X) >> 4) + rd < 0)
                ETC_WriteBits(local_block, 1, 31, 1);
            else
                ETC_WriteBits(local_block, 0, 31, 1);
            ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], X) >> 4, 27, 4);
            ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Y) >> 5, 24, 3);
            ETC_WriteBits(local_block, g, 19, 5);
            ETC_WriteBits(local_block, gd, 16, 3);
            ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Z) >> 4, 15, 1);
            ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], X) >> 4, 11, 4);
            ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Y) >> 4,  7, 4);
            ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Z) >> 4,  3, 4);

            ETC_WriteBits(local_block, (params_th.table >> 2) & 1, 2, 1);
            ETC_WriteBits(local_block, 1, 1, 1); // diff bit
            ETC_WriteBits(local_block, (params_th.table >> 1) & 1 & 1, 0, 1); // flip bit

            for (i = 0; i < 16; i++)
            {
                int index = (i % 4) * 4 + i / 4;

                int idx = params_th.indexes[i];

                ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);
                ETC_WriteBits(local_block, idx & 1, 32 + index, 1);

            }
            ETC_PackBlockSwapOrder(block, local_block);
        }
        else if (enc_mode == ETC_ENC_MODE_PLANAR)
        {
            int r, g, b;
            int rd, gd, bd;
            int min_bd;
            int max_bd;
            int min_b;
            int max_b;

            MEMBER(params_planar.rgb[0], X) >>= 2;
            MEMBER(params_planar.rgb[0], Y) >>= 1;
            MEMBER(params_planar.rgb[0], Z) >>= 2;

            MEMBER(params_planar.rgb[1], X) >>= 2;
            MEMBER(params_planar.rgb[1], Y) >>= 1;
            MEMBER(params_planar.rgb[1], Z) >>= 2;

            MEMBER(params_planar.rgb[2], X) >>= 2;
            MEMBER(params_planar.rgb[2], Y) >>= 1;
            MEMBER(params_planar.rgb[2], Z) >>= 2;

            ETC_WriteBits(local_block, MEMBER(params_planar.rgb[2], Z), 32, 6);
            ETC_WriteBits(local_block, MEMBER(params_planar.rgb[2], Y), 38, 7);
            ETC_WriteBits(local_block, MEMBER(params_planar.rgb[2], X), 45, 6);
            ETC_WriteBits(local_block, MEMBER(params_planar.rgb[1], Z), 51, 6);
            ETC_WriteBits(local_block, MEMBER(params_planar.rgb[1], Y), 57, 7);

            ETC_WriteBits(local_block, (MEMBER(params_planar.rgb[1], X)) & 1, 0, 1);
            ETC_WriteBits(local_block, 1, 1, 1);
            ETC_WriteBits(local_block, (MEMBER(params_planar.rgb[1], X) >> 1) & 31, 2, 5);
            ETC_WriteBits(local_block, MEMBER(params_planar.rgb[0], Z) & 7, 7, 3);
            ETC_WriteBits(local_block, (MEMBER(params_planar.rgb[0], Z) >> 3) & 7, 11, 2);
            ETC_WriteBits(local_block, (MEMBER(params_planar.rgb[0], Z) >> 5) & 1, 16, 1);
            ETC_WriteBits(local_block, MEMBER(params_planar.rgb[0], Y) & 63, 17, 6);
            ETC_WriteBits(local_block, (MEMBER(params_planar.rgb[0], Y) >> 6) & 1, 24, 1);
            ETC_WriteBits(local_block, MEMBER(params_planar.rgb[0], X), 25, 6);

            r = (MEMBER(params_planar.rgb[0], X) >> 2) & 63;
            rd = (MEMBER(params_planar.rgb[0], Y) >> 6) | ((MEMBER(params_planar.rgb[0], X) & 3) << 1);
            g = (MEMBER(params_planar.rgb[0], Y) >> 2) & 15;
            gd = (MEMBER(params_planar.rgb[0], Z) >> 5) | ((MEMBER(params_planar.rgb[0], Y) & 3) << 1);
            b = (MEMBER(params_planar.rgb[0], Z) >> 3) & 3;
            bd = (MEMBER(params_planar.rgb[0], Z) >> 1) & 3;

            if (rd >= 4)
                rd = -4 + (rd & 3);
            if (gd >= 4)
                gd = -4 + (gd & 3);
            if (bd >= 4)
                bd = -4 + (bd & 3);

            if (r + rd < 0)
                ETC_WriteBits(local_block, 1, 31, 1);
            else
                ETC_WriteBits(local_block, 0, 31, 1);

            if (g + gd < 0)
                ETC_WriteBits(local_block, 1, 23, 1);
            else
                ETC_WriteBits(local_block, 0, 23, 1);

            min_bd = -4 + bd;
            max_bd = bd;
            min_b = b;
            max_b = 28 + min_b;

            if (min_b + min_bd < 0)
            {
                ETC_WriteBits(local_block, min_bd, 8, 3);
                ETC_WriteBits(local_block, min_b, 11, 5);
            }
            else
            {
                ETC_WriteBits(local_block, max_bd, 8, 3);
                ETC_WriteBits(local_block, max_b, 11, 5);
            }
            ETC_PackBlockSwapOrder(block, local_block);
        }
    }
}

float ETC_EvaluateErrorAlphaWeighted(float *alpha, float *weight, float base_alpha, float mul, int table)
{
    int i;
    int j;
    float total_err = 0.0f;
    float point[8];

    for (i = 0; i < 8; i++)
        point[i] = clamp(base_alpha + mul * g_alpha[table][i], 0.0f, 255.0f);

    for (i = 0; i < 16; i++)
    {
        float best_err = MAX_INIT_ERROR;
        for (j = 0; j < 8; j++)
        {
            float err = (alpha[i] - point[j]) * (alpha[i] - point[j]) * weight[i];
            if (err < best_err)
                best_err = err;
        }
        total_err += best_err;
    }
    return total_err;
}

float ETC_FindBestBaseAlphaWeighted(float *alpha, float *weight, float alpha_mins, float alpha_maxs, float mul, int table, int *best_base_alpha)
{
    int k;
    float a = alpha_mins;
    float b = alpha_maxs;
    float c = b - (b - a) * M_INV_GOLDEN_F;
    float d = a + (b - a) * M_INV_GOLDEN_F;
    float fc = 0.0f;
    float fd = 0.0f;

    fc = ETC_EvaluateErrorAlphaWeighted(alpha, weight, floor(c + 0.5f), mul, table);
    fd = ETC_EvaluateErrorAlphaWeighted(alpha, weight, floor(d + 0.5f), mul, table);

    for (k = 0; (k < 16) && (b - a) > 0.5f; k++)
    {
        if (fc < fd)
        {
            b = d;
            c = b - (b - a) * M_INV_GOLDEN_F;
            d = a + (b - a) * M_INV_GOLDEN_F;
            fd = fc;
            fc = ETC_EvaluateErrorAlphaWeighted(alpha, weight, floor(c + 0.5f), mul, table);
        }
        else
        {
            a = c;
            c = b - (b - a) * M_INV_GOLDEN_F;
            d = a + (b - a) * M_INV_GOLDEN_F;
            fc = fd;
            fd = ETC_EvaluateErrorAlphaWeighted(alpha, weight, floor(d + 0.5f), mul, table);
        }
    }
    if (fc < fd)
    {
        *best_base_alpha = (int)c;
        return fc;
    }
    else
    {
        *best_base_alpha = (int)d;
        return fd;
    }
}

void ETC_GetOptimalIndexesAlphaWeighted(float *alpha, float *weight, float base_alpha, float mul, int table, int *indexes)
{
    int i;
    int j;
    float point[8];

    for (i = 0; i < 8; i++)
        point[i] = clamp(base_alpha + mul * g_alpha[table][i], 0.0f, 255.0f);

    for (i = 0; i < 16; i++)
    {
        float best_err = MAX_INIT_ERROR;
        for (j = 0; j < 8; j++)
        {
            float err = (alpha[i] - point[j]) * (alpha[i] - point[j]) * weight[i];
            if (err < best_err)
            {
                best_err = err;
                indexes[i] = j;
            }
        }
    }
}

void ETC_EncodeAlphaWeighted(
    float error_target,
    int refine_search,
    int search_radius,
    float4 *pixel,
    float *weight,
    __global uchar *block)
{
    float alpha[16];
    float alpha_mins;
    float alpha_maxs;
    float alpha_mid;
    float alpha_half_range;
    float best_error = MAX_INIT_ERROR;
    float best_mul;
    int best_table;
    int i, j;
    int alpha_index[16];
    int best_base_alpha;
    uchar local_block[8];

    for (i = 0; i < 16; i++)
        alpha[i] = MEMBER(pixel[i], W);

    alpha_mins = alpha[0];
    alpha_maxs = alpha[0];

    for (i = 1; i < 16; i++)
    {
        alpha_mins = min(alpha_mins, alpha[i]);
        alpha_maxs = max(alpha_maxs, alpha[i]);
    }
    alpha_mid = floor((alpha_mins + alpha_maxs) * 0.5f + 0.5f);
    alpha_half_range = (alpha_maxs - alpha_mins) * 0.5f;

    for (i = 0; i < 16; i++)
    {
        int lower_mul = (int)clamp((int)max(floor(2.0f * alpha_half_range / g_alpha_range[i]), 1.0f) - search_radius, 1, 16 - (search_radius * 2 + 1));
        for (j = 0; j < search_radius * 2 + 1; j++)
        {
            float mul = (float)lower_mul + (float)j;
            float err = ETC_EvaluateErrorAlphaWeighted(alpha, weight, alpha_mid, mul, i);

            if (err < best_error)
            {
                best_table = i;
                best_error = err;
                best_mul = mul;
                best_base_alpha = (int)alpha_mid;
            }
            if (refine_search)
            {
                int base_alpha[2];
                float err_left = ETC_FindBestBaseAlphaWeighted(alpha, weight, alpha_mins, alpha_mid, mul, i, &base_alpha[0]);
                float err_right = ETC_FindBestBaseAlphaWeighted(alpha, weight, alpha_mid, alpha_maxs, mul, i, &base_alpha[1]);

                if (err_left < best_error)
                {
                    best_table = i;
                    best_error = err_left;
                    best_mul = mul;
                    best_base_alpha = base_alpha[0];
                }
                if (err_right < best_error)
                {
                    best_table = i;
                    best_error = err_right;
                    best_mul = mul;
                    best_base_alpha = base_alpha[1];
                }
            }
        }

    }
    ETC_GetOptimalIndexesAlphaWeighted(alpha, weight, (float)best_base_alpha, best_mul, best_table, alpha_index);

    ETC_WriteBits(local_block, (uint)best_base_alpha, 56, 8);
    ETC_WriteBits(local_block, (uint)best_mul, 52, 4);
    ETC_WriteBits(local_block, best_table, 48, 4);

    for (i = 0; i < 16; i++)
    {
        int index = (i % 4) * 4 + i / 4;
        ETC_WriteBits(local_block, alpha_index[i], 45 - index * 3, 3);
    }

    ETC_PackBlockReverseOrder(block, local_block);
}

void ETC_EncodeRGBA1WeightedFast(
    int allowed_modes,
    int is_ypbpr,
    float alpha_cutoff,
    float4 *pixel,
    float *weight,
    __global uchar *block)
{
    int i, table;
    float3 trans_pixel[16];
    int is_delta;
    int is_flipped;
    int enc_mode;
    etc_partition_mode_params_t params_partition;
    etc_th_mode_params_t params_th;
    uchar local_block[8];
    int transparency[16];
    int transparent_count = 0;
    etc_pathing_params_t pathing_params;
    int real_transparent_count = 0;
    float err[2] = {0.0f, 0.0f};
    uchar3 partition_rgb[2][2];
    etc_partition_mode_params_t params_partition_nodelta;
    float best_error[5] = {MAX_INIT_ERROR, MAX_INIT_ERROR, MAX_INIT_ERROR, MAX_INIT_ERROR, MAX_INIT_ERROR};
    int best_mode = 0;
    int found_mode = 0;

    for (i = 0; i < 16; i++)
    {
        MEMBER(trans_pixel[i], X) = MEMBER(pixel[i], X);
        MEMBER(trans_pixel[i], Y) = MEMBER(pixel[i], Y);
        MEMBER(trans_pixel[i], Z) = MEMBER(pixel[i], Z);
    }
    for (i = 0; i < 16; i++)
    {
        transparency[i] = (MEMBER(pixel[i], W) <= alpha_cutoff) ? (int)weight[i] : 0;
        transparent_count += transparency[i];
        real_transparent_count += ((MEMBER(pixel[i], W) <= alpha_cutoff) && (weight[i] != 0.0f)) ? 1 : 0;
    }

    if (transparent_count == 16)
    {
        ETC_WriteBits(local_block, 0, 27, 5);
        ETC_WriteBits(local_block, 0, 24, 3);
        ETC_WriteBits(local_block, 0, 19, 5);
        ETC_WriteBits(local_block, 0, 16, 3);
        ETC_WriteBits(local_block, 0, 11, 5);
        ETC_WriteBits(local_block, 0,  8, 3);
        ETC_WriteBits(local_block, 0, 1, 1); // diff bit

        ETC_WriteBits(local_block, 0, 5, 3); // table codeword 1
        ETC_WriteBits(local_block, 0, 2, 3); // table codeword 2
        ETC_WriteBits(local_block, 0, 0, 1); // flip bit

        for (i = 0; i < 16; i++)
        {
            int index = (i%4)*4 + i/4;
            int idx = 2;

            ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);
            ETC_WriteBits(local_block, idx & 1, 32 + index, 1);
        }
        ETC_PackBlockSwapOrder(block, local_block);
        return;
    }

    if (allowed_modes & ETC_MODE_NODELTA)
    {
        for (is_flipped = 0; is_flipped < 2; is_flipped++)
        {
            float proj_mean[2] = {0.0f, 0.0f};
            float x[2] = {0.0f, 0.0f};
            float z[2] = {0.0f, 0.0f};
            float count[2] = {0.0f, 0.0f};

            for (i = 0; i < 8; i++)
            {
                if (!transparency[g_partition_indexes[is_flipped][0][i]])
                {
                    x[0] += MEMBER(trans_pixel[g_partition_indexes[is_flipped][0][i]], X);
                    x[0] -= MEMBER(trans_pixel[g_partition_indexes[is_flipped][0][i]], Y);
                    z[0] += MEMBER(trans_pixel[g_partition_indexes[is_flipped][0][i]], Z);
                    z[0] -= MEMBER(trans_pixel[g_partition_indexes[is_flipped][0][i]], Y);
                    count[0] += 1.0f;
                }

                if (!transparency[g_partition_indexes[is_flipped][1][i]])
                {
                    x[1] += MEMBER(trans_pixel[g_partition_indexes[is_flipped][1][i]], X);
                    x[1] -= MEMBER(trans_pixel[g_partition_indexes[is_flipped][1][i]], Y);
                    z[1] += MEMBER(trans_pixel[g_partition_indexes[is_flipped][1][i]], Z);
                    z[1] -= MEMBER(trans_pixel[g_partition_indexes[is_flipped][1][i]], Y);
                    count[1] += 1.0f;
                }
            }

            x[0] /= count[0] == 0.0f ? 1.0f : count[0];
            x[1] /= count[1] == 0.0f ? 1.0f : count[1];
            z[0] /= count[0] == 0.0f ? 1.0f : count[0];
            z[1] /= count[1] == 0.0f ? 1.0f : count[1];

            for (i = 0; i < 8; i++)
            {
                if (!transparency[g_partition_indexes[is_flipped][0][i]])
                    proj_mean[0] += dot(trans_pixel[g_partition_indexes[is_flipped][0][i]] - VFLOAT3(x[0], 0.0f, z[0]), VFLOAT3(0.57735f, 0.57735f, 0.57735f));
                if (!transparency[g_partition_indexes[is_flipped][1][i]])
                    proj_mean[1] += dot(trans_pixel[g_partition_indexes[is_flipped][1][i]] - VFLOAT3(x[1], 0.0f, z[1]), VFLOAT3(0.57735f, 0.57735f, 0.57735f));
            }

            proj_mean[0] /= count[0] == 0.0f ? 1.0f : count[0];
            proj_mean[1] /= count[1] == 0.0f ? 1.0f : count[1];
            proj_mean[0] *= 0.57735f;
            proj_mean[1] *= 0.57735f;

            partition_rgb[is_flipped][0] = UCHAR3(clamp(x[0] + proj_mean[0], 0.0f, 255.0f), clamp(proj_mean[0], 0.0f, 255.0f), clamp(z[0] + proj_mean[0], 0.0f, 255.0f));
            partition_rgb[is_flipped][1] = UCHAR3(clamp(x[1] + proj_mean[1], 0.0f, 255.0f), clamp(proj_mean[1], 0.0f, 255.0f), clamp(z[1] + proj_mean[1], 0.0f, 255.0f));

            partition_rgb[is_flipped][0] = ETC_RGBRoundVecTo4Bit(partition_rgb[is_flipped][0]);
            partition_rgb[is_flipped][1] = ETC_RGBRoundVecTo4Bit(partition_rgb[is_flipped][1]);

            pathing_params.partition_indexes = &g_partition_indexes[is_flipped][0][0];
            err[is_flipped] += EvaluateErrorGenericA1(ETC_EVALUATEDELTAERRORGENERIC, transparency, is_ypbpr, trans_pixel, partition_rgb[is_flipped][0], &pathing_params);
            pathing_params.partition_indexes = &g_partition_indexes[is_flipped][1][0];
            err[is_flipped] += EvaluateErrorGenericA1(ETC_EVALUATEDELTAERRORGENERIC, transparency, is_ypbpr, trans_pixel, partition_rgb[is_flipped][1], &pathing_params);
        }
        params_partition_nodelta.is_flipped = err[0] < err[1] ? 0 : 1;

        best_error[ETC_ENC_MODE_NODELTA] = err[0] < err[1] ? err[0] : err[1];

        params_partition_nodelta.rgb[0] = partition_rgb[params_partition_nodelta.is_flipped][0];
        params_partition_nodelta.rgb[1] = partition_rgb[params_partition_nodelta.is_flipped][1];

        if (!found_mode || (best_error[ETC_ENC_MODE_NODELTA] < best_error[best_mode]))
        {
            ETC_GetOptimalIndexesA1(transparency, is_ypbpr, trans_pixel, params_partition_nodelta.rgb[0], &g_partition_indexes[params_partition_nodelta.is_flipped][0][0], &params_partition_nodelta.table[0], params_partition_nodelta.indexes);
            ETC_GetOptimalIndexesA1(transparency, is_ypbpr, trans_pixel, params_partition_nodelta.rgb[1], &g_partition_indexes[params_partition_nodelta.is_flipped][1][0], &params_partition_nodelta.table[1], params_partition_nodelta.indexes);

            found_mode = 1;
            best_mode = ETC_ENC_MODE_NODELTA;
        }
        err[0] = 0.0f;
        err[1] = 0.0f;
    }

    if (allowed_modes & ETC_MODE_DELTA)
    {
        for (is_flipped = 0; is_flipped < 2; is_flipped++)
        {
            float proj_mean[2] = {0.0f, 0.0f};
            float x[2] = {0.0f, 0.0f};
            float z[2] = {0.0f, 0.0f};
            float count[2] = {0.0f, 0.0f};

            for (i = 0; i < 8; i++)
            {
                if (!transparency[g_partition_indexes[is_flipped][0][i]])
                {
                    x[0] += MEMBER(trans_pixel[g_partition_indexes[is_flipped][0][i]], X);
                    x[0] -= MEMBER(trans_pixel[g_partition_indexes[is_flipped][0][i]], Y);
                    z[0] += MEMBER(trans_pixel[g_partition_indexes[is_flipped][0][i]], Z);
                    z[0] -= MEMBER(trans_pixel[g_partition_indexes[is_flipped][0][i]], Y);
                    count[0] += 1.0f;
                }

                if (!transparency[g_partition_indexes[is_flipped][1][i]])
                {
                    x[1] += MEMBER(trans_pixel[g_partition_indexes[is_flipped][1][i]], X);
                    x[1] -= MEMBER(trans_pixel[g_partition_indexes[is_flipped][1][i]], Y);
                    z[1] += MEMBER(trans_pixel[g_partition_indexes[is_flipped][1][i]], Z);
                    z[1] -= MEMBER(trans_pixel[g_partition_indexes[is_flipped][1][i]], Y);
                    count[1] += 1.0f;
                }
            }

            x[0] /= count[0] == 0.0f ? 1.0f : count[0];
            x[1] /= count[1] == 0.0f ? 1.0f : count[1];
            z[0] /= count[0] == 0.0f ? 1.0f : count[0];
            z[1] /= count[1] == 0.0f ? 1.0f : count[1];

            for (i = 0; i < 8; i++)
            {
                if (!transparency[g_partition_indexes[is_flipped][0][i]])
                    proj_mean[0] += dot(trans_pixel[g_partition_indexes[is_flipped][0][i]] - VFLOAT3(x[0], 0.0f, z[0]), VFLOAT3(0.57735f, 0.57735f, 0.57735f));
                if (!transparency[g_partition_indexes[is_flipped][1][i]])
                    proj_mean[1] += dot(trans_pixel[g_partition_indexes[is_flipped][1][i]] - VFLOAT3(x[1], 0.0f, z[1]), VFLOAT3(0.57735f, 0.57735f, 0.57735f));
            }

            proj_mean[0] /= count[0] == 0.0f ? 1.0f : count[0];
            proj_mean[1] /= count[1] == 0.0f ? 1.0f : count[1];
            proj_mean[0] *= 0.57735f;
            proj_mean[1] *= 0.57735f;

            partition_rgb[is_flipped][0] = UCHAR3(clamp(x[0] + proj_mean[0], 0.0f, 255.0f), clamp(proj_mean[0], 0.0f, 255.0f), clamp(z[0] + proj_mean[0], 0.0f, 255.0f));
            partition_rgb[is_flipped][1] = UCHAR3(clamp(x[1] + proj_mean[1], 0.0f, 255.0f), clamp(proj_mean[1], 0.0f, 255.0f), clamp(z[1] + proj_mean[1], 0.0f, 255.0f));

            partition_rgb[is_flipped][0] = ETC_RGBRoundVecTo5Bit(partition_rgb[is_flipped][0]);
            partition_rgb[is_flipped][1] = ETC_RGBRoundVecTo5Bit(partition_rgb[is_flipped][1]);

            pathing_params.partition_indexes = &g_partition_indexes[is_flipped][0][0];
            err[is_flipped] += EvaluateErrorGenericA1(ETC_EVALUATEDELTAERRORGENERIC, transparency, is_ypbpr, trans_pixel, partition_rgb[is_flipped][0], &pathing_params);
            pathing_params.partition_indexes = &g_partition_indexes[is_flipped][1][0];
            err[is_flipped] += EvaluateErrorGenericA1(ETC_EVALUATEDELTAERRORGENERIC, transparency, is_ypbpr, trans_pixel, partition_rgb[is_flipped][1], &pathing_params);
        }
        params_partition.is_flipped = err[0] < err[1] ? 0 : 1;

        params_partition.rgb[0] = partition_rgb[params_partition.is_flipped][0];
        params_partition.rgb[1] = partition_rgb[params_partition.is_flipped][1];

        is_delta = 0;
        int diff = (int)((MEMBER(params_partition.rgb[1], X)) >> 3) - (int)((MEMBER(params_partition.rgb[0], X) >> 3));
        if (diff < 4 && diff >= -4)
            is_delta++;
        diff = (int)((MEMBER(params_partition.rgb[1], Y)) >> 3) - (int)((MEMBER(params_partition.rgb[0], Y) >> 3));
        if (diff < 4 && diff >= -4)
            is_delta++;
        diff = (int)((MEMBER(params_partition.rgb[1], Z)) >> 3) - (int)((MEMBER(params_partition.rgb[0], Z) >> 3));
        if (diff < 4 && diff >= -4)
            is_delta++;

        if (is_delta == 3)
        {
            best_error[ETC_ENC_MODE_DELTA] = err[0] < err[1] ? err[0] : err[1];
            if (!found_mode || (best_error[ETC_ENC_MODE_DELTA] < best_error[best_mode]))
            {
                ETC_GetOptimalIndexesA1(transparency, is_ypbpr, trans_pixel, params_partition.rgb[0], &g_partition_indexes[params_partition.is_flipped][0][0], &params_partition.table[0], params_partition.indexes);
                ETC_GetOptimalIndexesA1(transparency, is_ypbpr, trans_pixel, params_partition.rgb[1], &g_partition_indexes[params_partition.is_flipped][1][0], &params_partition.table[1], params_partition.indexes);

                found_mode = 1;
                best_mode = ETC_ENC_MODE_DELTA;
            }
        }
    }
    if (((best_error[best_mode] != 0.0f) || !found_mode) && (allowed_modes & (ETC_MODE_T | ETC_MODE_H)))
    {
        int set_indexes[2][16];
        int set_count[2];
        int best_error_flip;

        ETC_KMeansTHMode(trans_pixel, &set_indexes[0][0], &set_indexes[1][0], &set_count[0]);

        if (allowed_modes & ETC_MODE_T)
        {
            for (is_flipped = 0; is_flipped < 2; is_flipped++)
            {
                float proj_mean[2] = {0.0f, 0.0f};
                float x[2] = {0.0f, 0.0f};
                float z[2] = {0.0f, 0.0f};
                float count[2] = {0.0f, 0.0f};

                for (i = 0; i < set_count[is_flipped]; i++)
                {
                    if (!transparency[set_indexes[is_flipped][i]])
                    {
                        x[0] += MEMBER(trans_pixel[set_indexes[is_flipped][i]], X);
                        x[0] -= MEMBER(trans_pixel[set_indexes[is_flipped][i]], Y);
                        z[0] += MEMBER(trans_pixel[set_indexes[is_flipped][i]], Z);
                        z[0] -= MEMBER(trans_pixel[set_indexes[is_flipped][i]], Y);
                        count[0] += 1.0f;
                    }
                }
                for (i = 0; i < set_count[(is_flipped + 1) % 2]; i++)
                {
                    if (!transparency[set_indexes[(is_flipped + 1) % 2][i]])
                    {
                        x[1] += MEMBER(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]], X);
                        x[1] -= MEMBER(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]], Y);
                        z[1] += MEMBER(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]], Z);
                        z[1] -= MEMBER(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]], Y);
                        count[1] += 1.0f;
                    }
                }

                x[0] /= count[0] == 0.0f ? 1.0f : count[0];
                x[1] /= count[1] == 0.0f ? 1.0f : count[1];
                z[0] /= count[0] == 0.0f ? 1.0f : count[0];
                z[1] /= count[1] == 0.0f ? 1.0f : count[1];

                for (i = 0; i < set_count[is_flipped]; i++)
                    if (!transparency[set_indexes[is_flipped][i]])
                        proj_mean[0] += dot(trans_pixel[set_indexes[is_flipped][i]] - VFLOAT3(x[0], 0.0f, z[0]), VFLOAT3(0.57735f, 0.57735f, 0.57735f));
                for (i = 0; i < set_count[(is_flipped + 1) % 2]; i++)
                    if (!transparency[set_indexes[(is_flipped + 1) % 2][i]])
                        proj_mean[1] += dot(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]] - VFLOAT3(x[1], 0.0f, z[1]), VFLOAT3(0.57735f, 0.57735f, 0.57735f));

                proj_mean[0] /= count[0] == 0.0f ? 1.0f : count[0];
                proj_mean[1] /= count[1] == 0.0f ? 1.0f : count[1];

                proj_mean[0] *= 0.57735f;
                proj_mean[1] *= 0.57735f;

                partition_rgb[is_flipped][0] = UCHAR3(clamp(x[0] + proj_mean[0], 0.0f, 255.0f), clamp(proj_mean[0], 0.0f, 255.0f), clamp(z[0] + proj_mean[0], 0.0f, 255.0f));
                partition_rgb[is_flipped][1] = UCHAR3(clamp(x[1] + proj_mean[1], 0.0f, 255.0f), clamp(proj_mean[1], 0.0f, 255.0f), clamp(z[1] + proj_mean[1], 0.0f, 255.0f));

                partition_rgb[is_flipped][0] = ETC_RGBRoundVecTo4Bit(partition_rgb[is_flipped][0]);
                partition_rgb[is_flipped][1] = ETC_RGBRoundVecTo4Bit(partition_rgb[is_flipped][1]);

                params_th.rgb[0] = partition_rgb[is_flipped][0];
                params_th.rgb[1] = partition_rgb[is_flipped][1];

                err[is_flipped] = ETC_GetOptimalTIndexesA1(transparency, is_ypbpr, trans_pixel, params_th.rgb[0], params_th.rgb[1], &params_th.indexes[0], &params_th.table);
            }

            best_error[ETC_ENC_MODE_T] = err[0] < err[1] ? err[0] : err[1];
            best_error_flip = err[0] < err[1] ? 0 : 1;

            params_th.rgb[0] = partition_rgb[best_error_flip][0];
            params_th.rgb[1] = partition_rgb[best_error_flip][1];
            ETC_GetOptimalTIndexesA1(transparency, is_ypbpr, trans_pixel, params_th.rgb[0], params_th.rgb[1], &params_th.indexes[0], &params_th.table);

            if (!found_mode || (best_error[ETC_ENC_MODE_T] < best_error[best_mode]))
            {
                found_mode = 1;
                best_mode = ETC_ENC_MODE_T;
            }
        }
        if (allowed_modes & ETC_MODE_H)
        {
            int best_table[2];
            etc_th_mode_params_t params_th_local;

            for (is_flipped = 0; is_flipped < 2; is_flipped++)
            {
                float proj_mean[2] = {0.0f, 0.0f};
                float x[2] = {0.0f, 0.0f};
                float z[2] = {0.0f, 0.0f};
                float local_best_error = MAX_INIT_ERROR;

                float count[2] = {0.0f, 0.0f};

                for (i = 0; i < set_count[is_flipped]; i++)
                {
                    if (!transparency[set_indexes[is_flipped][i]])
                    {
                        x[0] += MEMBER(trans_pixel[set_indexes[is_flipped][i]], X);
                        x[0] -= MEMBER(trans_pixel[set_indexes[is_flipped][i]], Y);
                        z[0] += MEMBER(trans_pixel[set_indexes[is_flipped][i]], Z);
                        z[0] -= MEMBER(trans_pixel[set_indexes[is_flipped][i]], Y);
                        count[0] += 1.0f;
                    }
                }
                for (i = 0; i < set_count[(is_flipped + 1) % 2]; i++)
                {
                    if (!transparency[set_indexes[(is_flipped + 1) % 2][i]])
                    {
                        x[1] += MEMBER(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]], X);
                        x[1] -= MEMBER(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]], Y);
                        z[1] += MEMBER(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]], Z);
                        z[1] -= MEMBER(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]], Y);
                        count[1] += 1.0f;
                    }
                }

                x[0] /= count[0] == 0.0f ? 1.0f : count[0];
                x[1] /= count[1] == 0.0f ? 1.0f : count[1];
                z[0] /= count[0] == 0.0f ? 1.0f : count[0];
                z[1] /= count[1] == 0.0f ? 1.0f : count[1];

                for (i = 0; i < set_count[is_flipped]; i++)
                    if (!transparency[set_indexes[is_flipped][i]])
                        proj_mean[0] += dot(trans_pixel[set_indexes[is_flipped][i]] - VFLOAT3(x[0], 0.0f, z[0]), VFLOAT3(0.57735f, 0.57735f, 0.57735f));
                for (i = 0; i < set_count[(is_flipped + 1) % 2]; i++)
                    if (!transparency[set_indexes[(is_flipped + 1) % 2][i]])
                        proj_mean[1] += dot(trans_pixel[set_indexes[(is_flipped + 1) % 2][i]] - VFLOAT3(x[1], 0.0f, z[1]), VFLOAT3(0.57735f, 0.57735f, 0.57735f));

                proj_mean[0] /= count[0] == 0.0f ? 1.0f : count[0];
                proj_mean[1] /= count[1] == 0.0f ? 1.0f : count[1];

                proj_mean[0] *= 0.57735f;
                proj_mean[1] *= 0.57735f;

                partition_rgb[is_flipped][0] = UCHAR3(clamp(x[0] + proj_mean[0], 0.0f, 255.0f), clamp(proj_mean[0], 0.0f, 255.0f), clamp(z[0] + proj_mean[0], 0.0f, 255.0f));
                partition_rgb[is_flipped][1] = UCHAR3(clamp(x[1] + proj_mean[1], 0.0f, 255.0f), clamp(proj_mean[1], 0.0f, 255.0f), clamp(z[1] + proj_mean[1], 0.0f, 255.0f));

                partition_rgb[is_flipped][0] = ETC_RGBRoundVecTo4Bit(partition_rgb[is_flipped][0]);
                partition_rgb[is_flipped][1] = ETC_RGBRoundVecTo4Bit(partition_rgb[is_flipped][1]);

                params_th_local.rgb[0] = partition_rgb[is_flipped][0];
                params_th_local.rgb[1] = partition_rgb[is_flipped][1];

                for (table = 0; table < 8; table++)
                {
                    float local_err = ETC_GetOptimalHIndexesA1(transparency, is_ypbpr, trans_pixel, params_th_local.rgb[0], params_th_local.rgb[1], &params_th_local.indexes[0], table);
                    if (local_err < local_best_error)
                    {
                        best_table[is_flipped] = table;
                        err[is_flipped] = local_err;
                        local_best_error = local_err;
                    }
                }
            }

            best_error[ETC_ENC_MODE_H] = err[0] < err[1] ? err[0] : err[1];
            best_error_flip = err[0] < err[1] ? 0 : 1;

            params_th_local.table = best_table[best_error_flip];
            params_th_local.rgb[0] = partition_rgb[best_error_flip][0];
            params_th_local.rgb[1] = partition_rgb[best_error_flip][1];
            ETC_GetOptimalHIndexesA1(transparency, is_ypbpr, trans_pixel, params_th_local.rgb[0], params_th_local.rgb[1], &params_th_local.indexes[0], params_th_local.table);

            if (!found_mode || (best_error[ETC_ENC_MODE_H] < best_error[best_mode]))
            {
                found_mode = 1;
                best_mode = ETC_ENC_MODE_H;
                params_th = params_th_local;
            }
        }
    }

    if (best_mode == ETC_ENC_MODE_NODELTA)
        params_partition = params_partition_nodelta;
    enc_mode = best_mode;

    if (enc_mode == ETC_ENC_MODE_DELTA)
    {
        int3 diff;

        MEMBER(diff, X) = (MEMBER(params_partition.rgb[1], X) >> 3) - (MEMBER(params_partition.rgb[0], X) >> 3);
        MEMBER(diff, Y) = (MEMBER(params_partition.rgb[1], Y) >> 3) - (MEMBER(params_partition.rgb[0], Y) >> 3);
        MEMBER(diff, Z) = (MEMBER(params_partition.rgb[1], Z) >> 3) - (MEMBER(params_partition.rgb[0], Z) >> 3);

        ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], X) >> 3, 27, 5);
        ETC_WriteBits(local_block, MEMBER(diff, X) >> 0, 24, 3);
        ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], Y) >> 3, 19, 5);
        ETC_WriteBits(local_block, MEMBER(diff, Y) >> 0, 16, 3);
        ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], Z) >> 3, 11, 5);
        ETC_WriteBits(local_block, MEMBER(diff, Z) >> 0,  8, 3);
        ETC_WriteBits(local_block, 0, 1, 1); // diff bit

        ETC_WriteBits(local_block, params_partition.table[0], 5, 3); // table codeword 1
        ETC_WriteBits(local_block, params_partition.table[1], 2, 3); // table codeword 2
        ETC_WriteBits(local_block, params_partition.is_flipped, 0, 1); // flip bit

        for (i = 0; i < 16; i++)
        {
            int index = (i%4)*4 + i/4;

            int idx = params_partition.indexes[i];

            if (transparency[i])
                idx = 2;

            ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);
            ETC_WriteBits(local_block, idx & 1, 32 + index, 1);
        }
        ETC_PackBlockSwapOrder(block, local_block);
    }
    else if (enc_mode == ETC_ENC_MODE_T)
    {
        int min_rd = -4 + ((MEMBER(params_th.rgb[0], X) >> 4) & 3);
        int max_rd = ((MEMBER(params_th.rgb[0], X) >> 4) & 3);
        int min_r = (MEMBER(params_th.rgb[0], X) >> 6) & 3;
        int max_r = 28 + min_r;
        uchar r;
        uchar rd;

        if (min_rd + min_r < 0)
        {
            r = UCHAR(min_r);
            rd = UCHAR(min_rd);
        }
        else
        {
            r = UCHAR(max_r);
            rd = UCHAR(max_rd);
        }

        ETC_WriteBits(local_block, r, 27, 5);
        ETC_WriteBits(local_block, rd, 24, 3);
        ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Y) >> 4, 20, 4);
        ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Z) >> 4, 16, 4);
        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], X) >> 4, 12, 4);
        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Y) >> 4,  8, 4);
        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Z) >> 4,  4, 4);

        ETC_WriteBits(local_block, (params_th.table >> 1) & 3, 2, 2);
        ETC_WriteBits(local_block, 0, 1, 1); // diff bit
        ETC_WriteBits(local_block, params_th.table & 1, 0, 1); // flip bit

        for (i = 0; i < 16; i++)
        {
            int index = (i % 4) * 4 + i / 4;

            int idx = params_th.indexes[i];

            if (transparency[i])
                idx = 2;

            ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);
            ETC_WriteBits(local_block, idx & 1, 32 + index, 1);

        }
        ETC_PackBlockSwapOrder(block, local_block);
    }
    else if (enc_mode == ETC_ENC_MODE_H)
    {
        int min_gd = -4 + ((MEMBER(params_th.rgb[0], Z) >> 5) & 3);
        int max_gd = ((MEMBER(params_th.rgb[0], Z) >> 5) & 3);
        int min_g = ((MEMBER(params_th.rgb[0], Z) >> 7) & 1) | (((MEMBER(params_th.rgb[0], Y) >> 4) & 1) << 1);
        int max_g = 28 + min_g;
        uchar g;
        uchar gd;
        int rd;

        if (min_gd + min_g < 0)
        {
            g = UCHAR(min_g);
            gd = UCHAR(min_gd);
        }
        else
        {
            g = UCHAR(max_g);
            gd = UCHAR(max_gd);
        }

        rd = MEMBER(params_th.rgb[0], Y) >> 5;
        if (rd >= 4)
            rd = -4 + (rd & 3);

        if ((int)(MEMBER(params_th.rgb[0], X) >> 4) + rd < 0)
            ETC_WriteBits(local_block, 1, 31, 1);
        else
            ETC_WriteBits(local_block, 0, 31, 1);
        ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], X) >> 4, 27, 4);
        ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Y) >> 5, 24, 3);
        ETC_WriteBits(local_block, g, 19, 5);
        ETC_WriteBits(local_block, gd, 16, 3);
        ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Z) >> 4, 15, 1);
        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], X) >> 4, 11, 4);
        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Y) >> 4,  7, 4);
        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Z) >> 4,  3, 4);

        ETC_WriteBits(local_block, (params_th.table >> 2) & 1, 2, 1);
        ETC_WriteBits(local_block, 0, 1, 1); // diff bit
        ETC_WriteBits(local_block, (params_th.table >> 1) & 1 & 1, 0, 1); // flip bit

        for (i = 0; i < 16; i++)
        {
            int index = (i % 4) * 4 + i / 4;

            int idx = params_th.indexes[i];

            if (transparency[i])
                idx = 2;

            ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);
            ETC_WriteBits(local_block, idx & 1, 32 + index, 1);

        }
        ETC_PackBlockSwapOrder(block, local_block);
    }
}
void ETC_EncodeRGBA1WeightedQuality(
    int quality,
    int allowed_modes,
    float error_target,
    int refine_search,
    int is_ypbpr,
    float alpha_cutoff,
    float4 *pixel,
    float *weight,
    __global uchar *block)
{
    int i, j, table, n;
    float3 trans_pixel[16];
    int is_delta;
    int is_flipped;
    float best_dist[2];
    etc_sample_t sample_list[SAMPLE_LIST_SIZE0][SAMPLE_LIST_SIZE1][SAMPLE_LIST_SIZE2];
    int flipped;
    int partition;
    int is_best_delta = 0;
    float best_total_error = MAX_INIT_ERROR;
    int enc_mode;
    etc_partition_mode_params_t params_partition;
    etc_th_mode_params_t params_th;
    uchar local_block[8];
    int transparency[16];
    int transparent_count = 0;
    etc_pathing_params_t pathing_params;
    int real_transparent_count = 0;
    float3 projected_mins[2][2]; // delta/non-delta, flipped, partition
    float3 projected_maxs[2][2];

    for (i = 0; i < 16; i++)
    {
        MEMBER(trans_pixel[i], X) = MEMBER(pixel[i], X);
        MEMBER(trans_pixel[i], Y) = MEMBER(pixel[i], Y);
        MEMBER(trans_pixel[i], Z) = MEMBER(pixel[i], Z);
    }
    for (i = 0; i < 16; i++)
    {
        transparency[i] = (MEMBER(pixel[i], W) <= alpha_cutoff) ? (int)weight[i] : 0;
        transparent_count += transparency[i];
        real_transparent_count += ((MEMBER(pixel[i], W) <= alpha_cutoff) && (weight[i] != 0.0f)) ? 1 : 0;
    }

    if (transparent_count == 16)
    {
        ETC_WriteBits(local_block, 0, 27, 5);
        ETC_WriteBits(local_block, 0, 24, 3);
        ETC_WriteBits(local_block, 0, 19, 5);
        ETC_WriteBits(local_block, 0, 16, 3);
        ETC_WriteBits(local_block, 0, 11, 5);
        ETC_WriteBits(local_block, 0,  8, 3);
        ETC_WriteBits(local_block, 0, 1, 1); // diff bit

        ETC_WriteBits(local_block, 0, 5, 3); // table codeword 1
        ETC_WriteBits(local_block, 0, 2, 3); // table codeword 2
        ETC_WriteBits(local_block, 0, 0, 1); // flip bit

        for (i = 0; i < 16; i++)
        {
            int index = (i%4)*4 + i/4;
            int idx = 2;

            ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);
            ETC_WriteBits(local_block, idx & 1, 32 + index, 1);
        }
        ETC_PackBlockSwapOrder(block, local_block);
        return;
    }

    for (flipped = 0; flipped < 2; flipped++)
    {
        for (partition = 0; partition < 2; partition++)
        {
            float3 mean = VFLOAT3(0.0f, 0.0f, 0.0f);
            float mins_maxs_dist[2];
            int pixel_count = 0;

            mins_maxs_dist[0] = MAX_INIT_ERROR;
            mins_maxs_dist[1] = -MAX_INIT_ERROR;

            for (i = 0; i < 8; i++)
            {
                if (transparency[g_partition_indexes[flipped][partition][i]])
                    continue;
                mean = mean + trans_pixel[g_partition_indexes[flipped][partition][i]];
                pixel_count++;
            }

            pixel_count = pixel_count ? pixel_count : 1;

            mean = mean / (float)(pixel_count);

            for (i = 0; i < 8; i++)
            {
                float dist;

                if (transparency[g_partition_indexes[flipped][partition][i]])
                    continue;

                dist = dot(trans_pixel[g_partition_indexes[flipped][partition][i]] - mean, VFLOAT3(0.57735f, 0.57735f, 0.57735f));

                if (dist < mins_maxs_dist[0])
                    mins_maxs_dist[0] = dist;
                if (dist > mins_maxs_dist[1])
                    mins_maxs_dist[1] = dist;
            }
            projected_mins[flipped][partition] = mean + VFLOAT3(0.57735f, 0.57735f, 0.57735f) * mins_maxs_dist[0];
            projected_maxs[flipped][partition] = mean + VFLOAT3(0.57735f, 0.57735f, 0.57735f) * mins_maxs_dist[1];
        }
    }

    if (is_ypbpr)
        for (i = 0; i < 16; i++)
            trans_pixel[i] = ETC_ConvertToYPBPRf3(trans_pixel[i]);

    if (allowed_modes & ETC_MODE_DELTA)
    {
        float3 mean[2][2];
        uchar3 mean_quant[2][2];
        int min_index[2][2];
        int max_index[2][2];
        float fixed_err = MAX_INIT_ERROR;
        uchar3 best_positions[2];
        int best_flipped = 0;
        int found_fixed = 0;
        uchar3 proj_mins;
        uchar3 proj_maxs;
#if 1
        if (quality >= CODEC_QUALITY_NORMAL) // redundant, quality is always normal or better in this function
        {
            int max_distance;

            if (quality == CODEC_QUALITY_BEST)
                max_distance = 255;
            else if (quality == CODEC_QUALITY_HIGH)
                max_distance = 8;
            else 
                max_distance = 1;

            for (flipped = 0; flipped < 2; flipped++)
            {
                for (partition = 0; partition < 2; partition++)
                {
                    int distance = 0;
                    mean[flipped][partition] = VFLOAT3(0.0f, 0.0f, 0.0f);
                    for (i = 0; i < 8; i++) // TODO: this should be weighted
                    {
                        mean[flipped][partition] = mean[flipped][partition] + trans_pixel[g_partition_indexes[flipped][partition][i]];
                    }
                    mean[flipped][partition] = mean[flipped][partition] / 8.0f;

                    MEMBER(mean_quant[flipped][partition], X) = UCHAR(MEMBER(mean[flipped][partition], X)) >> 3;
                    MEMBER(mean_quant[flipped][partition], Y) = UCHAR(MEMBER(mean[flipped][partition], Y)) >> 3;
                    MEMBER(mean_quant[flipped][partition], Z) = UCHAR(MEMBER(mean[flipped][partition], Z)) >> 3;

                    min_index[flipped][partition] = 0;
                    max_index[flipped][partition] = 0;

                    while ( ((int)MEMBER(mean_quant[flipped][partition], X) + min_index[flipped][partition] > 0) &&
                        ((int)MEMBER(mean_quant[flipped][partition], Y) + min_index[flipped][partition] > 0) &&
                        ((int)MEMBER(mean_quant[flipped][partition], Z) + min_index[flipped][partition] > 0))
                    {
                        min_index[flipped][partition]--;
                        distance++;
                        if (distance > max_distance)
                            break;
                    }
                    distance = 0;
                    while ( ((int)MEMBER(mean_quant[flipped][partition], X) + max_index[flipped][partition] < 31) &&
                        ((int)MEMBER(mean_quant[flipped][partition], Y) + max_index[flipped][partition] < 31) &&
                        ((int)MEMBER(mean_quant[flipped][partition], Z) + max_index[flipped][partition] < 31))
                    {
                        max_index[flipped][partition]++;
                        distance++;
                        if (distance > max_distance)
                            break;
                    }
                }
            }
            for (flipped = 0; flipped < 2; flipped++)
            {
                int ip0;
                int ip1;
                for (ip0 = min_index[flipped][0]; ip0 <= max_index[flipped][0]; ip0++)
                {
                    uchar3 l0_quant;

                    MEMBER(l0_quant, X) = UCHAR(MEMBER(mean_quant[flipped][0], X) + ip0);
                    MEMBER(l0_quant, Y) = UCHAR(MEMBER(mean_quant[flipped][0], Y) + ip0);
                    MEMBER(l0_quant, Z) = UCHAR(MEMBER(mean_quant[flipped][0], Z) + ip0);

                    for (ip1 = min_index[flipped][1]; ip1 <= max_index[flipped][1]; ip1++)
                    {
                        uchar3 l1_quant;
                        int dist[3];
                        float local_error;

                        MEMBER(l1_quant, X) = UCHAR(MEMBER(mean_quant[flipped][1], X) + ip1);
                        MEMBER(l1_quant, Y) = UCHAR(MEMBER(mean_quant[flipped][1], Y) + ip1);
                        MEMBER(l1_quant, Z) = UCHAR(MEMBER(mean_quant[flipped][1], Z) + ip1);

                        dist[0] = (int)MEMBER(l1_quant, X) - (int)MEMBER(l0_quant, X);
                        dist[1] = (int)MEMBER(l1_quant, Y) - (int)MEMBER(l0_quant, Y);
                        dist[2] = (int)MEMBER(l1_quant, Z) - (int)MEMBER(l0_quant, Z);

                        if ((dist[0] < -4 || dist[0] > 3) || 
                            (dist[1] < -4 || dist[1] > 3) || 
                            (dist[2] < -4 || dist[2] > 3))
                            continue;

                        local_error = ETC_EvaluateErrorA1(transparency, is_ypbpr, trans_pixel, ETC_RGBExpandVecTo5Bit(l0_quant), &g_partition_indexes[flipped][0][0]);
                        local_error += ETC_EvaluateErrorA1(transparency, is_ypbpr, trans_pixel, ETC_RGBExpandVecTo5Bit(l1_quant), &g_partition_indexes[flipped][1][0]);

                        if (local_error < fixed_err)
                        {
                            fixed_err = local_error;
                            best_positions[0] = l0_quant;
                            best_positions[1] = l1_quant;
                            best_flipped = flipped;

                            found_fixed = 1;
                        }
                    }
                }
            }
            if (found_fixed)
            {
                uchar3 best_pos[2];
                float combined_err = 0.0f;

                best_pos[0] = best_positions[0];
                best_pos[1] = best_positions[1];

                for (partition = 0; partition < 2; partition++)
                {
                    int neighbourhood_width = (quality == CODEC_QUALITY_BEST ? 3 : 1);
                    float best_err = MAX_INIT_ERROR;
                    int x;
                    int y;
                    int z;
                    int min_x = MEMBER(best_positions[partition], X) > (neighbourhood_width - 1) ? MEMBER(best_positions[partition], X) - neighbourhood_width : 0;
                    int min_y = MEMBER(best_positions[partition], Y) > (neighbourhood_width - 1) ? MEMBER(best_positions[partition], Y) - neighbourhood_width : 0;
                    int min_z = MEMBER(best_positions[partition], Z) > (neighbourhood_width - 1) ? MEMBER(best_positions[partition], Z) - neighbourhood_width : 0;
                    int max_x = MEMBER(best_positions[partition], X) < (31 - neighbourhood_width) ? MEMBER(best_positions[partition], X) + neighbourhood_width : 31;
                    int max_y = MEMBER(best_positions[partition], Y) < (31 - neighbourhood_width) ? MEMBER(best_positions[partition], Y) + neighbourhood_width : 31;
                    int max_z = MEMBER(best_positions[partition], Z) < (31 - neighbourhood_width) ? MEMBER(best_positions[partition], Z) + neighbourhood_width : 31;

                    for (z = min_z; z <= max_z; z++)
                        for (y = min_y; y <= max_y; y++)
                            for (x = min_x; x <= max_x; x++)
                            {
                                uchar3 pos = UCHAR3(x, y, z);
                                float err;
                                int dist[3];

                                dist[0] = (int)MEMBER(pos, X) - (int)MEMBER(best_pos[partition ? 0 : 1], X);
                                dist[1] = (int)MEMBER(pos, Y) - (int)MEMBER(best_pos[partition ? 0 : 1], Y);
                                dist[2] = (int)MEMBER(pos, Z) - (int)MEMBER(best_pos[partition ? 0 : 1], Z);

                                if ((dist[0] < -4 || dist[0] > 3) || 
                                    (dist[1] < -4 || dist[1] > 3) || 
                                    (dist[2] < -4 || dist[2] > 3))
                                    continue;

                                pos = ETC_RGBExpandVecTo5Bit(pos);
                                err = ETC_EvaluateErrorA1(transparency, is_ypbpr, trans_pixel, pos, &g_partition_indexes[best_flipped][partition][0]);

                                if (err < best_err)
                                {
                                    best_pos[partition] = UCHAR3(x, y, z);
                                    best_err = err;
                                }
                            }
                    combined_err += best_err;
                }

                if (combined_err < fixed_err)
                {
                    best_positions[0] = best_pos[0];
                    best_positions[1] = best_pos[1];
                    fixed_err = combined_err;
                }
            }
        }
#endif

        // Delta mode
        ETC_PrepareSampleList(SAMPLE_LIST_SIZE2, sample_list);

        for (flipped = 0; flipped < 2; flipped++)
        {
            for (partition = 0; partition < 2; partition++)
            {
                etc_sample_t sample;
                float offset = 0.0f;

                if (quality == CODEC_QUALITY_NORMAL)
                    offset = 0.0f;
                else if (quality > CODEC_QUALITY_NORMAL) // searching entire space on BEST tends to give values that can't be represented by delta encodings
                    offset = 24.0f;

                MEMBER(proj_mins, X) = UCHAR(((uint)clamp(MEMBER(projected_mins[flipped][partition], X) - offset, 0.0f, 255.0f)) >> 3);
                MEMBER(proj_mins, Y) = UCHAR(((uint)clamp(MEMBER(projected_mins[flipped][partition], Y) - offset, 0.0f, 255.0f)) >> 3);
                MEMBER(proj_mins, Z) = UCHAR(((uint)clamp(MEMBER(projected_mins[flipped][partition], Z) - offset, 0.0f, 255.0f)) >> 3);
                MEMBER(proj_maxs, X) = UCHAR(((uint)clamp(MEMBER(projected_maxs[flipped][partition], X) + offset + 3, 0.0f, 255.0f)) >> 3);
                MEMBER(proj_maxs, Y) = UCHAR(((uint)clamp(MEMBER(projected_maxs[flipped][partition], Y) + offset + 3, 0.0f, 255.0f)) >> 3);
                MEMBER(proj_maxs, Z) = UCHAR(((uint)clamp(MEMBER(projected_maxs[flipped][partition], Z) + offset + 3, 0.0f, 255.0f)) >> 3);

                sample.pos_quantised = proj_mins;
                pathing_params.partition_indexes = &g_partition_indexes[flipped][partition][0];
                sample.error = ETC_EvaluateErrorA1(transparency, is_ypbpr, trans_pixel, ETC_RGBExpandVecTo5Bit(sample.pos_quantised), &g_partition_indexes[flipped][partition][0]);
                ETC_LeastCostDirectedPathA1(1, SAMPLE_LIST_SIZE2, transparency, error_target, refine_search, is_ypbpr, trans_pixel, sample, &sample_list[flipped][partition][0], MEMBER(proj_maxs, X), MEMBER(proj_maxs, Y), MEMBER(proj_maxs, Z), &pathing_params, ETC_RGBEXPANDVECTO5BIT, ETC_EVALUATEDELTAERRORGENERICA1);
            }
        }

        for (i = 0; i < 2; i++)
            best_dist[i] = sample_list[i][0][0].error + sample_list[i][1][0].error;

        if (best_dist[1] < best_dist[0])
            is_flipped = 1;
        else
            is_flipped = 0;

        is_delta = 0;

        int diff = (int)(MEMBER(sample_list[is_flipped][1][0].pos_quantised, X)) - (int)(MEMBER(sample_list[is_flipped][0][0].pos_quantised, X));
        if (diff < 4 && diff >= -4)
            is_delta++;
        diff = (int)(MEMBER(sample_list[is_flipped][1][0].pos_quantised, Y)) - (int)(MEMBER(sample_list[is_flipped][0][0].pos_quantised, Y));
        if (diff < 4 && diff >= -4)
            is_delta++;
        diff = (int)(MEMBER(sample_list[is_flipped][1][0].pos_quantised, Z)) - (int)(MEMBER(sample_list[is_flipped][0][0].pos_quantised, Z));
        if (diff < 4 && diff >= -4)
            is_delta++;

        is_best_delta = is_delta == 3 ? 1 : 0;

        best_total_error = min(best_dist[0], best_dist[1]);

        enc_mode = ETC_ENC_MODE_DELTA;
        params_partition.rgb[0] = ETC_RGBExpandVecTo5Bit(sample_list[is_flipped][0][0].pos_quantised);
        params_partition.rgb[1] = ETC_RGBExpandVecTo5Bit(sample_list[is_flipped][1][0].pos_quantised);
        params_partition.is_flipped = is_flipped;

        if (!is_best_delta)
        {
            int delta[2][SAMPLE_LIST_SIZE2][SAMPLE_LIST_SIZE2]; // TODO: can get rid of this if just do it inside the loop
            float err[2][SAMPLE_LIST_SIZE2][SAMPLE_LIST_SIZE2]; // TODO: can get rid of this if just do it inside the loop
            int best_delta[2] = {0, 0};
            float best_delta_err = MAX_INIT_ERROR;
            int delta_found = 0;
            int best_flipped = 0;

            for (n = 0; n < 2; n++)
                for (i = 0; i < SAMPLE_LIST_SIZE2; i++)
                {
                    for (j = 0; j < SAMPLE_LIST_SIZE2; j++)
                    {
                        is_delta = 0;
                        int diff = (int)(MEMBER(sample_list[n][1][j].pos_quantised, X)) - (int)(MEMBER(sample_list[n][0][i].pos_quantised, X));
                        if (diff < 4 && diff >= -4)
                            is_delta++;
                        diff = (int)(MEMBER(sample_list[n][1][j].pos_quantised, Y)) - (int)(MEMBER(sample_list[n][0][i].pos_quantised, Y));
                        if (diff < 4 && diff >= -4)
                            is_delta++;
                        diff = (int)(MEMBER(sample_list[n][1][j].pos_quantised, Z)) - (int)(MEMBER(sample_list[n][0][i].pos_quantised, Z));
                        if (diff < 4 && diff >= -4)
                            is_delta++;

                        delta[n][i][j] = is_delta == 3 ? 1 : 0;
                        err[n][i][j] = sample_list[n][1][j].error + sample_list[n][0][i].error;
                    }
                }
            for (n = 0; n < 2; n++)
                for (i = 0; i < SAMPLE_LIST_SIZE2; i++)
                    for (j = 0; j < SAMPLE_LIST_SIZE2; j++)
                        if (delta[n][i][j])
                            if (err[n][i][j] < best_delta_err)
                            {
                                best_delta_err = err[n][i][j];
                                best_delta[0] = i;
                                best_delta[1] = j;
                                delta_found = 1;
                                best_flipped = n;
                            }

            best_total_error = best_delta_err;

            if (delta_found)
            {
                params_partition.rgb[0] = ETC_RGBExpandVecTo5Bit(sample_list[best_flipped][0][best_delta[0]].pos_quantised);
                params_partition.rgb[1] = ETC_RGBExpandVecTo5Bit(sample_list[best_flipped][1][best_delta[1]].pos_quantised);
                params_partition.is_flipped = best_flipped;
            }
        }

        if (found_fixed && fixed_err < best_total_error)
        {
            enc_mode = ETC_ENC_MODE_DELTA;
            best_total_error = fixed_err;
            params_partition.rgb[0] = ETC_RGBExpandVecTo5Bit(best_positions[0]);
            params_partition.rgb[1] = ETC_RGBExpandVecTo5Bit(best_positions[1]);
            params_partition.is_flipped = best_flipped;
        }

        ETC_GetOptimalIndexesA1(transparency, is_ypbpr, trans_pixel, params_partition.rgb[0], &g_partition_indexes[params_partition.is_flipped][0][0], &params_partition.table[0], params_partition.indexes);
        ETC_GetOptimalIndexesA1(transparency, is_ypbpr, trans_pixel, params_partition.rgb[1], &g_partition_indexes[params_partition.is_flipped][1][0], &params_partition.table[1], params_partition.indexes);
    }

    if ((best_total_error > error_target) && (allowed_modes & (ETC_MODE_T | ETC_MODE_H)))
    {
        int set_indexes[2][16];
        int set_count[2];
        etc_sample_t sample;

        ETC_KMeansTHModeA1(transparency, trans_pixel, &set_indexes[0][0], &set_indexes[1][0], &set_count[0]);

        for (partition = 0; partition < 2; partition++) // TODO: this should be weighted
        {
            float3 mean = VFLOAT3(0.0f, 0.0f, 0.0f);
            float mins_maxs_dist[2];
            int pixel_count = 0;

            for (i = 0; i < set_count[partition]; i++)
            {
                if (transparency[set_indexes[partition][i]])
                    continue;
                mean = mean + trans_pixel[set_indexes[partition][i]];
                pixel_count++;
            }

            pixel_count = pixel_count ? pixel_count : 1;

            mean = mean / (float)(pixel_count);

            if (set_count[partition] && pixel_count)
            {
                mins_maxs_dist[0] = MAX_INIT_ERROR;
                mins_maxs_dist[1] = -MAX_INIT_ERROR;

                for (i = 0; i < set_count[partition]; i++)
                {
                    float dist;

                    if (transparency[set_indexes[partition][i]])
                        continue;

                    dist = dot(trans_pixel[set_indexes[partition][i]] - mean, VFLOAT3(0.57735f, 0.57735f, 0.57735f));

                    if (dist < mins_maxs_dist[0])
                        mins_maxs_dist[0] = dist;
                    if (dist > mins_maxs_dist[1])
                        mins_maxs_dist[1] = dist;
                }
                projected_mins[0][partition] = mean + VFLOAT3(0.57735f, 0.57735f, 0.57735f) * mins_maxs_dist[0];
                projected_maxs[0][partition] = mean + VFLOAT3(0.57735f, 0.57735f, 0.57735f) * mins_maxs_dist[1];
            }
            else
            {
                projected_mins[0][partition] = mean;
                projected_maxs[0][partition] = mean;
            }
        }

        if (allowed_modes & ETC_MODE_T)
        {
            // T mode
            ETC_PrepareSampleList(1, sample_list);
            for (flipped = 0; flipped < 2; flipped++)
            {
                etc_sample_t sample;
                uchar3 proj_mins;
                uchar3 proj_maxs;
                float offset = 0.0f;

                if (quality == CODEC_QUALITY_NORMAL)
                    offset = 0.0f;
                else if (quality == CODEC_QUALITY_HIGH)
                    offset = 48.0f;
                else 
                    offset = 96.0f;

                if ((quality == CODEC_QUALITY_NORMAL) || (quality == CODEC_QUALITY_HIGH))
                {
                    MEMBER(proj_mins, X) = UCHAR(((uint)clamp(MEMBER(projected_mins[0][flipped], X) - offset, 0.0f, 255.0f)) >> 4);
                    MEMBER(proj_mins, Y) = UCHAR(((uint)clamp(MEMBER(projected_mins[0][flipped], Y) - offset, 0.0f, 255.0f)) >> 4);
                    MEMBER(proj_mins, Z) = UCHAR(((uint)clamp(MEMBER(projected_mins[0][flipped], Z) - offset, 0.0f, 255.0f)) >> 4);
                    MEMBER(proj_maxs, X) = UCHAR(((uint)clamp(MEMBER(projected_maxs[0][flipped], X) + offset + 7, 0.0f, 255.0f)) >> 4);
                    MEMBER(proj_maxs, Y) = UCHAR(((uint)clamp(MEMBER(projected_maxs[0][flipped], Y) + offset + 7, 0.0f, 255.0f)) >> 4);
                    MEMBER(proj_maxs, Z) = UCHAR(((uint)clamp(MEMBER(projected_maxs[0][flipped], Z) + offset + 7, 0.0f, 255.0f)) >> 4);
                }
                else
                {
                    proj_mins = UCHAR3(0, 0, 0);
                    proj_maxs = UCHAR3(15, 15, 15);
                }

                sample.pos_quantised = proj_mins;
                pathing_params.indexes = set_indexes[flipped];
                pathing_params.num_indexes = set_count[flipped];
                sample.error = ETC_EvaluateErrorTSingleA1(transparency, is_ypbpr, trans_pixel, ETC_RGBExpandVecTo4Bit(sample.pos_quantised), set_indexes[flipped], set_count[flipped]);
                ETC_LeastCostDirectedPathA1(1, 1, transparency, error_target, refine_search, is_ypbpr, trans_pixel, sample, &sample_list[flipped][0][0], MEMBER(proj_maxs, X), MEMBER(proj_maxs, Y), MEMBER(proj_maxs, Z), &pathing_params, ETC_RGBEXPANDVECTO4BIT, ETC_EVALUATETSINGLEERRORGENERICA1);

                if ((quality == CODEC_QUALITY_NORMAL) || (quality == CODEC_QUALITY_HIGH))
                {
                    MEMBER(proj_mins, X) = UCHAR(((uint)clamp(MEMBER(projected_mins[0][(flipped + 1) % 2], X) - offset, 0.0f, 255.0f)) >> 4);
                    MEMBER(proj_mins, Y) = UCHAR(((uint)clamp(MEMBER(projected_mins[0][(flipped + 1) % 2], Y) - offset, 0.0f, 255.0f)) >> 4);
                    MEMBER(proj_mins, Z) = UCHAR(((uint)clamp(MEMBER(projected_mins[0][(flipped + 1) % 2], Z) - offset, 0.0f, 255.0f)) >> 4);
                    MEMBER(proj_maxs, X) = UCHAR(((uint)clamp(MEMBER(projected_maxs[0][(flipped + 1) % 2], X) + offset + 7, 0.0f, 255.0f)) >> 4);
                    MEMBER(proj_maxs, Y) = UCHAR(((uint)clamp(MEMBER(projected_maxs[0][(flipped + 1) % 2], Y) + offset + 7, 0.0f, 255.0f)) >> 4);
                    MEMBER(proj_maxs, Z) = UCHAR(((uint)clamp(MEMBER(projected_maxs[0][(flipped + 1) % 2], Z) + offset + 7, 0.0f, 255.0f)) >> 4);
                }
                else
                {
                    proj_mins = UCHAR3(0, 0, 0);
                    proj_maxs = UCHAR3(15, 15, 15);
                }
                sample.pos_quantised = proj_mins;
                pathing_params.indexes = set_indexes[(flipped + 1) % 2];
                pathing_params.num_indexes = set_count[(flipped + 1) % 2];
                sample.error = ETC_EvaluateErrorTTripleA1(transparency, is_ypbpr, trans_pixel, ETC_RGBExpandVecTo4Bit(sample.pos_quantised), set_indexes[(flipped + 1) % 2], set_count[(flipped + 1) % 2]);
                ETC_LeastCostDirectedPathA1(1, 1, transparency, error_target, refine_search, is_ypbpr, trans_pixel, sample, &sample_list[flipped][1][0], MEMBER(proj_maxs, X), MEMBER(proj_maxs, Y), MEMBER(proj_maxs, Z), &pathing_params, ETC_RGBEXPANDVECTO4BIT, ETC_EVALUATETTRIPLEERRORGENERICA1);
            }
            for (i = 0; i < 2; i++)
                best_dist[i] = sample_list[i][0][0].error + sample_list[i][1][0].error;

            if ((best_dist[0] < best_total_error) || (best_dist[1] < best_total_error))
            {
                enc_mode = ETC_ENC_MODE_T;

                if (best_dist[1] < best_dist[0])
                    is_flipped = 1;
                else
                    is_flipped = 0;

                params_th.rgb[0] = ETC_RGBExpandVecTo4Bit(sample_list[is_flipped][0][0].pos_quantised);
                params_th.rgb[1] = ETC_RGBExpandVecTo4Bit(sample_list[is_flipped][1][0].pos_quantised);

                float d = ETC_GetOptimalTIndexesA1(transparency, is_ypbpr, trans_pixel, params_th.rgb[0], params_th.rgb[1], &params_th.indexes[0], &params_th.table);

                best_total_error = d;
            }
        }

        if ((best_total_error > error_target) && (allowed_modes & ETC_MODE_H))
        {
            int best_mode;

            // H-Mode
            ETC_PrepareSampleList(1, sample_list);
            for (flipped = 0; flipped < 2; flipped++)
            {
                uchar3 proj_mins;
                uchar3 proj_maxs;
                float offset = 0.0f;

                if (quality == CODEC_QUALITY_NORMAL)
                    offset = 0.0f;
                else if (quality == CODEC_QUALITY_HIGH)
                    offset = 48.0f;
                else 
                    offset = 96.0f;

                if ((quality == CODEC_QUALITY_NORMAL) || (quality == CODEC_QUALITY_HIGH))
                {
                    MEMBER(proj_mins, X) = UCHAR(((uint)clamp(MEMBER(projected_mins[0][flipped], X) - offset, 0.0f, 255.0f)) >> 4);
                    MEMBER(proj_mins, Y) = UCHAR(((uint)clamp(MEMBER(projected_mins[0][flipped], Y) - offset, 0.0f, 255.0f)) >> 4);
                    MEMBER(proj_mins, Z) = UCHAR(((uint)clamp(MEMBER(projected_mins[0][flipped], Z) - offset, 0.0f, 255.0f)) >> 4);
                    MEMBER(proj_maxs, X) = UCHAR(((uint)clamp(MEMBER(projected_maxs[0][flipped], X) + offset + 7, 0.0f, 255.0f)) >> 4);
                    MEMBER(proj_maxs, Y) = UCHAR(((uint)clamp(MEMBER(projected_maxs[0][flipped], Y) + offset + 7, 0.0f, 255.0f)) >> 4);
                    MEMBER(proj_maxs, Z) = UCHAR(((uint)clamp(MEMBER(projected_maxs[0][flipped], Z) + offset + 7, 0.0f, 255.0f)) >> 4);
                }
                else
                {
                    proj_mins = UCHAR3(0, 0, 0);
                    proj_maxs = UCHAR3(15, 15, 15);
                }
                for (table = 0; table < 8; table++)
                {
                    sample.pos_quantised = proj_mins;
                    pathing_params.indexes = set_indexes[flipped];
                    pathing_params.num_indexes = set_count[flipped];
                    pathing_params.mode = table;
                    pathing_params.h_index = flipped;
                    sample.error = ETC_EvaluateErrorHA1(transparency, is_ypbpr, trans_pixel, ETC_RGBExpandVecTo4Bit(sample.pos_quantised), set_indexes[flipped], set_count[flipped], table, flipped);
                    ETC_LeastCostDirectedPathA1(1, 1, transparency, error_target, refine_search, is_ypbpr, trans_pixel, sample, &sample_list[flipped][table][0], MEMBER(proj_maxs, X), MEMBER(proj_maxs, Y), MEMBER(proj_maxs, Z), &pathing_params, ETC_RGBEXPANDVECTO4BIT, ETC_EVALUATEHERRORGENERICA1);
                }
            }

            best_dist[0] = sample_list[0][0][0].error + sample_list[1][0][0].error;
            best_mode = 0;

            for (flipped = 0; flipped < 2; flipped++)
                for (table = 0; table < 8; table++)
                    if (sample_list[0][table][0].error + sample_list[1][table][0].error < best_dist[0])
                    {
                        best_dist[0] = sample_list[0][table][0].error + sample_list[1][table][0].error;
                        best_mode = table;
                    }

            if (best_dist[0] < best_total_error)
            {
                ushort rgbpacked[2];

                enc_mode = ETC_ENC_MODE_H;

                params_th.table = best_mode;

                if ((MEMBER(sample_list[0][params_th.table][0].pos_quantised, X) == MEMBER(sample_list[1][params_th.table][0].pos_quantised, X)) &&
                    (MEMBER(sample_list[0][params_th.table][0].pos_quantised, Y) == MEMBER(sample_list[1][params_th.table][0].pos_quantised, Y)) &&
                    (MEMBER(sample_list[0][params_th.table][0].pos_quantised, Z) == MEMBER(sample_list[1][params_th.table][0].pos_quantised, Z)))
                    MEMBER(sample_list[0][params_th.table][0].pos_quantised, X) = (MEMBER(sample_list[0][params_th.table][0].pos_quantised, X) + 1) % 16;

                params_th.rgb[0] = ETC_RGBExpandVecTo4Bit(sample_list[0][params_th.table][0].pos_quantised);
                params_th.rgb[1] = ETC_RGBExpandVecTo4Bit(sample_list[1][params_th.table][0].pos_quantised);

                rgbpacked[0] =  (((ushort)MEMBER(sample_list[0][params_th.table][0].pos_quantised, X)) << 8) |
                    (((ushort)MEMBER(sample_list[0][params_th.table][0].pos_quantised, Y)) << 4) |
                    (((ushort)MEMBER(sample_list[0][params_th.table][0].pos_quantised, Z)) << 0);

                rgbpacked[1] =  (((ushort)MEMBER(sample_list[1][params_th.table][0].pos_quantised, X)) << 8) |
                    (((ushort)MEMBER(sample_list[1][params_th.table][0].pos_quantised, Y)) << 4) |
                    (((ushort)MEMBER(sample_list[1][params_th.table][0].pos_quantised, Z)) << 0);

                if (!(params_th.table & 1))
                {
                    if (rgbpacked[0] > rgbpacked[1])
                    {
                        params_th.rgb[0] = ETC_RGBExpandVecTo4Bit(sample_list[1][params_th.table][0].pos_quantised);
                        params_th.rgb[1] = ETC_RGBExpandVecTo4Bit(sample_list[0][params_th.table][0].pos_quantised);
                    }
                }
                else
                {
                    if (rgbpacked[0] < rgbpacked[1])
                    {
                        params_th.rgb[0] = ETC_RGBExpandVecTo4Bit(sample_list[1][params_th.table][0].pos_quantised);
                        params_th.rgb[1] = ETC_RGBExpandVecTo4Bit(sample_list[0][params_th.table][0].pos_quantised);
                    }
                }

                best_total_error = ETC_GetOptimalHIndexesA1(transparency, is_ypbpr, trans_pixel, params_th.rgb[0], params_th.rgb[1], params_th.indexes, params_th.table);
            }
        }
    }

    if (enc_mode == ETC_ENC_MODE_DELTA)
    {
        int3 diff;

        MEMBER(diff, X) = (MEMBER(params_partition.rgb[1], X) >> 3) - (MEMBER(params_partition.rgb[0], X) >> 3);
        MEMBER(diff, Y) = (MEMBER(params_partition.rgb[1], Y) >> 3) - (MEMBER(params_partition.rgb[0], Y) >> 3);
        MEMBER(diff, Z) = (MEMBER(params_partition.rgb[1], Z) >> 3) - (MEMBER(params_partition.rgb[0], Z) >> 3);

        ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], X) >> 3, 27, 5);
        ETC_WriteBits(local_block, MEMBER(diff, X) >> 0, 24, 3);
        ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], Y) >> 3, 19, 5);
        ETC_WriteBits(local_block, MEMBER(diff, Y) >> 0, 16, 3);
        ETC_WriteBits(local_block, MEMBER(params_partition.rgb[0], Z) >> 3, 11, 5);
        ETC_WriteBits(local_block, MEMBER(diff, Z) >> 0,  8, 3);
        ETC_WriteBits(local_block, 0, 1, 1); // diff bit

        ETC_WriteBits(local_block, params_partition.table[0], 5, 3); // table codeword 1
        ETC_WriteBits(local_block, params_partition.table[1], 2, 3); // table codeword 2
        ETC_WriteBits(local_block, params_partition.is_flipped, 0, 1); // flip bit

        for (i = 0; i < 16; i++)
        {
            int index = (i%4)*4 + i/4;

            int idx = params_partition.indexes[i];

            if (transparency[i])
                idx = 2;

            ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);
            ETC_WriteBits(local_block, idx & 1, 32 + index, 1);
        }
        ETC_PackBlockSwapOrder(block, local_block);
    }
    else if (enc_mode == ETC_ENC_MODE_T)
    {
        int min_rd = -4 + ((MEMBER(params_th.rgb[0], X) >> 4) & 3);
        int max_rd = ((MEMBER(params_th.rgb[0], X) >> 4) & 3);
        int min_r = (MEMBER(params_th.rgb[0], X) >> 6) & 3;
        int max_r = 28 + min_r;
        uchar r;
        uchar rd;

        if (min_rd + min_r < 0)
        {
            r = UCHAR(min_r);
            rd = UCHAR(min_rd);
        }
        else
        {
            r = UCHAR(max_r);
            rd = UCHAR(max_rd);
        }

        ETC_WriteBits(local_block, r, 27, 5);
        ETC_WriteBits(local_block, rd, 24, 3);
        ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Y) >> 4, 20, 4);
        ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Z) >> 4, 16, 4);
        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], X) >> 4, 12, 4);
        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Y) >> 4,  8, 4);
        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Z) >> 4,  4, 4);

        ETC_WriteBits(local_block, (params_th.table >> 1) & 3, 2, 2);
        ETC_WriteBits(local_block, 0, 1, 1); // diff bit
        ETC_WriteBits(local_block, params_th.table & 1, 0, 1); // flip bit

        for (i = 0; i < 16; i++)
        {
            int index = (i % 4) * 4 + i / 4;

            int idx = params_th.indexes[i];

            if (transparency[i])
                idx = 2;

            ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);
            ETC_WriteBits(local_block, idx & 1, 32 + index, 1);

        }
        ETC_PackBlockSwapOrder(block, local_block);
    }
    else if (enc_mode == ETC_ENC_MODE_H)
    {
        int min_gd = -4 + ((MEMBER(params_th.rgb[0], Z) >> 5) & 3);
        int max_gd = ((MEMBER(params_th.rgb[0], Z) >> 5) & 3);
        int min_g = ((MEMBER(params_th.rgb[0], Z) >> 7) & 1) | (((MEMBER(params_th.rgb[0], Y) >> 4) & 1) << 1);
        int max_g = 28 + min_g;
        uchar g;
        uchar gd;
        int rd;

        if (min_gd + min_g < 0)
        {
            g = UCHAR(min_g);
            gd = UCHAR(min_gd);
        }
        else
        {
            g = UCHAR(max_g);
            gd = UCHAR(max_gd);
        }

        rd = MEMBER(params_th.rgb[0], Y) >> 5;
        if (rd >= 4)
            rd = -4 + (rd & 3);

        if ((int)(MEMBER(params_th.rgb[0], X) >> 4) + rd < 0)
            ETC_WriteBits(local_block, 1, 31, 1);
        else
            ETC_WriteBits(local_block, 0, 31, 1);
        ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], X) >> 4, 27, 4);
        ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Y) >> 5, 24, 3);
        ETC_WriteBits(local_block, g, 19, 5);
        ETC_WriteBits(local_block, gd, 16, 3);
        ETC_WriteBits(local_block, MEMBER(params_th.rgb[0], Z) >> 4, 15, 1);
        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], X) >> 4, 11, 4);
        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Y) >> 4,  7, 4);
        ETC_WriteBits(local_block, MEMBER(params_th.rgb[1], Z) >> 4,  3, 4);

        ETC_WriteBits(local_block, (params_th.table >> 2) & 1, 2, 1);
        ETC_WriteBits(local_block, 0, 1, 1); // diff bit
        ETC_WriteBits(local_block, (params_th.table >> 1) & 1 & 1, 0, 1); // flip bit

        for (i = 0; i < 16; i++)
        {
            int index = (i % 4) * 4 + i / 4;

            int idx = params_th.indexes[i];

            if (transparency[i])
                idx = 2;

            ETC_WriteBits(local_block, idx >> 1, 48 + index, 1);
            ETC_WriteBits(local_block, idx & 1, 32 + index, 1);

        }
        ETC_PackBlockSwapOrder(block, local_block);
    }
}


void ETC_EncodeRGBA1Weighted(
    int quality,
    int allowed_modes,
    float error_target,
    int refine_search,
    int is_ypbpr,
    float alpha_cutoff,
    float4 *pixel,
    float *weight,
    __global uchar *block)
{

    if (quality == CODEC_QUALITY_FAST)
        ETC_EncodeRGBA1WeightedFast(allowed_modes, is_ypbpr, alpha_cutoff, pixel, weight, block);
    else
        ETC_EncodeRGBA1WeightedQuality(quality, allowed_modes, error_target, refine_search, is_ypbpr, alpha_cutoff, pixel, weight, block);
}

void ETC_EncodeETC4x4(
    int *g_block, // CPU ARG ONLY
    int allowed_modes,                              // bitfield of allowed modes for encoder, mostly for debugging. see MODE preprocessor definitions. suggested default: ETC_MODE_ANY. should never be set to "ETC_MODE_DELTA" only.
    float alpha_cutoff,                             // valid range 0 - 255, used in RGBA1 mode. (x <= cutoff) = transparent pixel.
    float rgb_error_target,                 // MSE error target for colour channels. 0 for max quality, 256 for approximately PVRTexTool "slow" quality. high performance impact for lower values. suggested default: 0
    float alpha_error_target,               // MSE error target for alpha in RGBA8 mode. 0 for max quality. moderate performance impact. suggested default: 0
    int is_ypbpr,                                   // measure MSE in YPbPr space instead of RGB space? moderate performance impact if enabled
    int is_etc2,                                    // is ETC1 or ETC2?
    int is_alpha,                                   // has an alpha channel?
    int is_punchthrough,                    // is alpha channel 1-bit?
    int refine_rgb_search,                  // search for best minimum in local neighbourhood to improve quality for RGB. high performance impact. suggested default: 0
    int refine_alpha_search,                // search for better "base alpha" instead of using simple estimate. moderate performance impact. suggested default: 1
    int alpha_search_radius,                // valid range 0 - 7. search radius for better alpha multiplier. moderate performance impact. suggested default: 1
    int width,                                              // image width in pixels
    int height,                                             // image height in pixels
    __global float *pixel_rgba,             // pixel RGBA in R, G, B, A order, (width x height) entries
    __global uchar *block,                  // output data
    int quality)                          // low-quality, high-speed
{
    float4 pixel[16];
    float weight[16];
    int block_x = get_global_id(0);
    int block_y = get_global_id(1);
    int i;
    int j;
    int line_out_blocks = (width + 3) >> 2;

        for (i = 0; i < 16; i++)
            weight[i] = 1.0f;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
        {
            MEMBER(pixel[(i*4 + j)], X) = pixel_rgba[((i + block_y*4)*width + (j + block_x*4))*4 + 0];
            MEMBER(pixel[(i*4 + j)], Y) = pixel_rgba[((i + block_y*4)*width + (j + block_x*4))*4 + 1];
            MEMBER(pixel[(i*4 + j)], Z) = pixel_rgba[((i + block_y*4)*width + (j + block_x*4))*4 + 2];
            MEMBER(pixel[(i*4 + j)], W) = pixel_rgba[((i + block_y*4)*width + (j + block_x*4))*4 + 3];

        }

        if (is_alpha && is_etc2)
        {
            if (!is_punchthrough)
            {
                    ETC_EncodeRGB(quality, allowed_modes, rgb_error_target, refine_rgb_search, is_etc2, is_ypbpr, pixel, &block[(block_x * 8 * 2) + (block_y) * line_out_blocks * 8 * 2 + 8], block_x, block_y);
                    ETC_EncodeAlpha(alpha_error_target, refine_alpha_search, alpha_search_radius, pixel, &block[(block_x * 8 * 2) + (block_y) * line_out_blocks * 8 * 2 + 0]);
            }
            else
            {
                int transparent_count = 0;

                for (i = 0; i < 16; i++)
                    if (MEMBER(pixel[i], W) <= alpha_cutoff)
                    {
                        transparent_count++;
                        break;
                    }
                if (transparent_count == 0)
                    ETC_EncodeRGB(quality, allowed_modes, rgb_error_target, refine_rgb_search, is_etc2, is_ypbpr, pixel, &block[(block_x * 8) + (block_y) * line_out_blocks * 8 + 0], block_x, block_y);
                else
                    ETC_EncodeRGBA1Weighted(quality, allowed_modes, rgb_error_target, refine_rgb_search, is_ypbpr, alpha_cutoff, pixel, weight, &block[(block_x * 8) + (block_y) * line_out_blocks * 8 + 0]);
            }
        }
        else
        {
            ETC_EncodeRGB(quality, allowed_modes, rgb_error_target, refine_rgb_search, is_etc2, is_ypbpr, pixel, &block[(block_x * 8) + (block_y) * line_out_blocks * 8 + 0], block_x, block_y);
        }
}

void ETC_EncodeETCN4x4(
    int *g_block, // CPU ARG ONLY
    int allowed_modes,                              // bitfield of allowed modes for encoder, mostly for debugging. see MODE preprocessor definitions. suggested default: ETC_MODE_ANY. should never be set to "ETC_MODE_DELTA" only.
    float alpha_cutoff,                             // valid range 0 - 255, used in RGBA1 mode. (x <= cutoff) = transparent pixel.
    float rgb_error_target,                 // MSE error target for colour channels. 0 for max quality, 256 for approximately PVRTexTool "slow" quality. high performance impact for lower values. suggested default: 0
    float alpha_error_target,               // MSE error target for alpha in RGBA8 mode. 0 for max quality. moderate performance impact. suggested default: 0
    int is_ypbpr,                                   // measure MSE in YPbPr space instead of RGB space? moderate performance impact if enabled
    int is_etc2,                                    // is ETC1 or ETC2?
    int is_alpha,                                   // has an alpha channel?
    int is_punchthrough,                    // is alpha channel 1-bit?
    int refine_rgb_search,                  // search for best minimum in local neighbourhood to improve quality for RGB. high performance impact. suggested default: 0
    int refine_alpha_search,                // search for better "base alpha" instead of using simple estimate. moderate performance impact. suggested default: 1
    int alpha_search_radius,                // valid range 0 - 7. search radius for better alpha multiplier. moderate performance impact. suggested default: 1
    int width,                                              // image width in pixels
    int height,                                             // image height in pixels
    __global float *pixel_rgba,             // pixel RGBA in R, G, B, A order, (width x height) entries
    __global uchar *block,                      // output data
    int quality)
{
    float4 pixel[16];
    float weight[16];
    int block_x = get_global_id(0);
    int block_y = get_global_id(1);
    int i;
    int j;
    int max_x;
    int max_y;
    int line_out_blocks = (width + 3) >> 2;

    max_x = clamp(width - block_x*4, 1, 4);
    max_y = clamp(height - block_y*4, 1, 4);

    for (i = 0; i < 16; i++)
    {
        pixel[i] = VFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
        weight[i] = 0.0f;
    }

    for (i = 0; i < max_y; i++)
        for (j = 0; j < max_x; j++)
        {
            MEMBER(pixel[(i*4 + j)], X) = pixel_rgba[((i + block_y*4)*width + (j + block_x*4))*4 + 0];
            MEMBER(pixel[(i*4 + j)], Y) = pixel_rgba[((i + block_y*4)*width + (j + block_x*4))*4 + 1];
            MEMBER(pixel[(i*4 + j)], Z) = pixel_rgba[((i + block_y*4)*width + (j + block_x*4))*4 + 2];
            MEMBER(pixel[(i*4 + j)], W) = pixel_rgba[((i + block_y*4)*width + (j + block_x*4))*4 + 3];

            weight[(i*4 + j)] = 1.0f;

        }

    if (is_alpha && is_etc2)
    {
        if (!is_punchthrough)
        {
            ETC_EncodeRGBWeighted(quality, allowed_modes, rgb_error_target, refine_rgb_search, is_etc2, is_ypbpr, pixel, weight, &block[(block_x * 8 * 2) + (block_y) * line_out_blocks * 8 * 2 + 8]);
            ETC_EncodeAlphaWeighted(alpha_error_target, refine_alpha_search, alpha_search_radius, pixel, weight, &block[(block_x * 8 * 2) + (block_y) * line_out_blocks * 8 * 2 + 0]);
        }
        else
        {
            int transparent_count = 0;

            for (i = 0; i < 16; i++)
                if (MEMBER(pixel[i], W) <= alpha_cutoff)
                {
                    transparent_count++;
                    break;
                }

            if (transparent_count == 0)
                ETC_EncodeRGBWeighted(quality, allowed_modes, rgb_error_target, refine_rgb_search, is_etc2, is_ypbpr, pixel, weight, &block[(block_x * 8) + (block_y) * line_out_blocks * 8 + 0]);
            else
                ETC_EncodeRGBA1Weighted(quality, allowed_modes, rgb_error_target, refine_rgb_search, is_ypbpr, alpha_cutoff, pixel, weight, &block[(block_x * 8) + (block_y) * line_out_blocks * 8 + 0]);
        }
    }
    else
    {
        ETC_EncodeRGBWeighted(quality, allowed_modes, rgb_error_target, refine_rgb_search, is_etc2, is_ypbpr, pixel, weight, &block[(block_x * 8) + (block_y) * line_out_blocks * 8 + 0]);
    }
}


__kernel void ETC_EncodeETC(
    int *g_block, // CPU ARG ONLY
    int allowed_modes,                              // bitfield of allowed modes for encoder, mostly for debugging. see MODE preprocessor definitions. suggested default: ETC_MODE_ANY. should never be set to "ETC_MODE_DELTA" only.
    float alpha_cutoff,                             // valid range 0 - 255, used in RGBA1 mode. (x <= cutoff) = transparent pixel.
    float rgb_error_target,                 // MSE error target for colour channels. 0 for max quality, 256 for approximately PVRTexTool "slow" quality. high performance impact for lower values. suggested default: 0
    float alpha_error_target,               // MSE error target for alpha in RGBA8 mode. 0 for max quality. moderate performance impact. suggested default: 0
    int is_ypbpr,                                   // measure MSE in YPbPr space instead of RGB space? moderate performance impact if enabled
    int is_etc2,                                    // is ETC1 or ETC2?
    int is_alpha,                                   // has an alpha channel?
    int is_punchthrough,                    // is alpha channel 1-bit?
    int refine_rgb_search,                  // search for best minimum in local neighbourhood to improve quality for RGB. high performance impact. suggested default: 0
    int refine_alpha_search,                // search for better "base alpha" instead of using simple estimate. moderate performance impact. suggested default: 1
    int alpha_search_radius,                // valid range 0 - 7. search radius for better alpha multiplier. moderate performance impact. suggested default: 1
    int width,                                              // image width in pixels
    int height,                                             // image height in pixels
    __global float *pixel_rgba,             // pixel RGBA in R, G, B, A order, (width x height) entries
    __global uchar *block,                       // output data
    int quality)
{
    int block_x = get_global_id(0);
    int block_y = get_global_id(1);
    int max_x;
    int max_y;
    int is_4x4;

    //DEBUG_NCOND return;

        if ((block_x * 4 >= width) || (block_y * 4 >= height))
            return;
        if (!is_etc2)
            allowed_modes &= ETC_MODE_ETC1;
        else if (is_etc2 && is_alpha && is_punchthrough)
            allowed_modes &= ETC_MODE_ETC2RGBA1;
        else
            allowed_modes &= ETC_MODE_ANY;
        max_x = clamp(width - block_x*4, 1, 4);
    max_y = clamp(height - block_y*4, 1, 4);
        is_4x4 = (max_x + max_y == 8) ? 1 : 0;
        if (is_4x4)
            ETC_EncodeETC4x4(
                g_block,
                allowed_modes,
                alpha_cutoff,
                rgb_error_target,
                alpha_error_target,
                is_ypbpr,
                is_etc2,
                is_alpha,
                is_punchthrough,
                refine_rgb_search,
                refine_alpha_search,
                alpha_search_radius,
                width,
                height,
                pixel_rgba,
                block,
                quality);
        else
            ETC_EncodeETCN4x4(
                g_block,
                allowed_modes,
                alpha_cutoff,
                rgb_error_target,
                alpha_error_target,
                is_ypbpr,
                is_etc2,
                is_alpha,
                is_punchthrough,
                refine_rgb_search,
                refine_alpha_search,
                alpha_search_radius,
                width,
                height,
                pixel_rgba,
                block,
                quality);
}


void ETC_EncodeETC_CPU(
    int quality,
    int workdim_x,
    int workdim_y,
    int allowed_modes,                              // bitfield of allowed modes for encoder, mostly for debugging. see MODE preprocessor definitions. suggested default: ETC_MODE_ANY. should never be set to "ETC_MODE_DELTA" only.
    float alpha_cutoff,                             // valid range 0 - 255, used in RGBA1 mode. (x <= cutoff) = transparent pixel.
    float rgb_error_target,                 // MSE error target for colour channels. 0 for max quality, 256 for approximately PVRTexTool "slow" quality. high performance impact for lower values. suggested default: 0
    float alpha_error_target,               // MSE error target for alpha in RGBA8 mode. 0 for max quality. moderate performance impact. suggested default: 0
    int is_ypbpr,                                   // measure MSE in YPbPr space instead of RGB space? moderate performance impact if enabled
    int is_etc2,                                    // is ETC1 or ETC2?
    int is_alpha,                                   // has an alpha channel?
    int is_punchthrough,                    // is alpha channel 1-bit?
    int refine_rgb_search,                  // search for best minimum in local neighbourhood to improve quality for RGB. high performance impact. suggested default: 0
    int refine_alpha_search,                // search for better "base alpha" instead of using simple estimate. moderate performance impact. suggested default: 1
    int alpha_search_radius,                // valid range 0 - 7. search radius for better alpha multiplier. moderate performance impact. suggested default: 1
    int width,                                              // image width in pixels
    int height,                                             // image height in pixels
    __global float *pixel_rgba,             // pixel RGBA in R, G, B, A order, (width x height) entries
    __global uchar *block)                       // output data
{
    int x, y;

#if USE_OPENMP
#pragma omp parallel for private(y) private(x)
#endif
    for (y = 0; y < workdim_y; y++)
        for (x = 0; x < workdim_x; x++)
        {
            int block_id[2] = {x, y};

            ETC_EncodeETC(
                block_id,
                allowed_modes,
                alpha_cutoff,
                rgb_error_target,
                alpha_error_target,
                is_ypbpr,
                is_etc2,
                is_alpha,
                is_punchthrough,
                refine_rgb_search,
                refine_alpha_search,
                alpha_search_radius,
                width,
                height,
                pixel_rgba,
                block,
                quality);
        }
}

extern "C" {

int EncodeETCCPU(
    int quality,
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
    float alpha_error_target)
{
    size_t blocks_x = (width + 3) >> 2;
    size_t blocks_y = (height + 3) >> 2;
    size_t bytes_in = (size_t)width * (size_t)height * sizeof(float) * (size_t)4;
    size_t bytes_out = ((size_t)blocks_x * (size_t)blocks_y * (size_t)16) >> 1;
    uint8_t *local_block;
    float *local_rgba = 0;
    size_t global_sub_block = 0;
    int x;
    int y;
    size_t local_bytes_in;
    size_t local_bytes_out;
    size_t local_macro_blocks_x;
    size_t local_macro_blocks_y;
    int total_blocks;
    int scale = (is_alpha && !is_punchthrough) ? 2 : 1;
    int max_dim;
    int is_error = 1;

    if (is_alpha && !is_punchthrough)
        bytes_out <<= 1;

    global_sub_block = g_local_group_size < g_system.opts.cl_macroblock_size ? g_system.opts.cl_macroblock_size : g_local_group_size;
    max_dim = (int)Math_CeilPow2u64((width + 3) / 4) > (int)Math_CeilPow2u64((height + 3) / 4) ? (int)Math_CeilPow2u64((width + 3) / 4) : (int)Math_CeilPow2u64((height + 3) / 4);
    if (global_sub_block > max_dim)
        global_sub_block = max_dim;

    local_macro_blocks_x = ((width + global_sub_block * 4 - 1) & ~(global_sub_block * 4 - 1)) / (global_sub_block * 4);
    local_macro_blocks_y = ((height + global_sub_block * 4 - 1) & ~(global_sub_block * 4 - 1)) / (global_sub_block * 4);

    local_bytes_in = (size_t)global_sub_block * (size_t)global_sub_block * sizeof(float) * (size_t)4 * 16;
    local_bytes_out = ((size_t)((global_sub_block * 4 + 3) >> 2) * (size_t)((global_sub_block * 4 + 3) >> 2) * (size_t)16) >> 1;
    if (is_alpha && !is_punchthrough)
        local_bytes_out <<= 1;

    LOG_PRINT("%i x %i sub blocks of size %i x %i\n", (int)local_macro_blocks_x, (int)local_macro_blocks_y, (int)global_sub_block, (int)global_sub_block);
    LOG_PRINT("total size: %i x %i, blocks: %I64i x %I64i (%I64i bytes in, %I64i bytes out)\n", width, height, (int64_t)blocks_x, (int64_t)blocks_y, (int64_t)bytes_in, (int64_t)bytes_out);
    LOG_PRINT("local size: %i x %i, macro blocks: %I64i x %I64i (%I64i bytes in, %I64i bytes out)\n", (int)global_sub_block * 4, (int)global_sub_block * 4, local_macro_blocks_x, local_macro_blocks_y, local_bytes_in, local_bytes_out);

    if (is_alpha && !is_punchthrough)
        bytes_out <<= 1;

    *block = (uint8_t*)Mem_Malloc(bytes_out);
    local_rgba = (float*)Mem_Malloc(local_bytes_in);
    local_block = (uint8_t*)Mem_Malloc(local_bytes_out);

    memset(*block, 0xCC, bytes_out);

    total_blocks = (int)(local_macro_blocks_x * local_macro_blocks_y);

#if TEST_OPENCL_ONLY
    is_ypbpr = 1;
    is_etc2 = 1; 
    is_alpha = 1;
    is_punchthrough = 0;
    total_blocks = 1;
    local_macro_blocks_y = 1;
    local_macro_blocks_x = 1;
#undef    g_local_group_size
#define    g_local_group_size  1
    global_sub_block = 1;
    width = 4;
    height = 4;
#endif

    for (y = 0; y < local_macro_blocks_y; y++)
    {
        for (x = 0; x < local_macro_blocks_x; x++)
        {
            uint64_t t[2];
            int yl;
            const size_t local[2] = {g_local_group_size < global_sub_block ? g_local_group_size : global_sub_block, g_local_group_size < global_sub_block ? g_local_group_size : global_sub_block};
            const size_t global[2] = {global_sub_block, global_sub_block};
            const int local_width = (int)(width - x * global_sub_block * 4 < global_sub_block * 4 ? width - x * global_sub_block * 4 : global_sub_block * 4);
            const int local_height = (int)(height - y * global_sub_block * 4 < global_sub_block * 4 ? height - y * global_sub_block * 4 : global_sub_block * 4);
            unsigned int n[16] = 
            {
                ETC_ALLOWED_MODES, // allowed modes
                (unsigned int)is_ypbpr, // is_ypbpr
                (unsigned int)is_etc2, 
                (unsigned int)is_alpha, // is_alpha
                (unsigned int)is_punchthrough, // is_punchthrough
                REFINE_RGB_SEARCH, // refine_rgb_search
                1, // refine_alpha_search
                1, // alpha_search_radius (valid range 0 -> 7)
                (unsigned int)local_width, 
                (unsigned int)local_height
            };
            float err_targ[3] = 
            {
                alpha_cutoff, // alpha_cutoff
                rgb_error_target, // rgb error
                alpha_error_target	// alpha error
            };
            //printf("%i/%i\n", (int)(y*local_macro_blocks_x + x), (int)total_blocks);
#if TEST_OPENCL_ONLY == 0
            for (yl = 0; yl < local_height; yl++)
            {
                int src_offset = (int)(((y * global_sub_block * 4 + yl) * width + x * global_sub_block * 4) * 4);
                int dst_offset = (int)(yl * local_width * 4);
                int bytes = 16 * local_width;
                memcpy(&local_rgba[dst_offset], &pixel4x4_rgba[src_offset], bytes);
            }
#endif
#if TEST_OPENCL_ONLY
            srand(0);
            for (yl = 0; yl < local_width * local_height * 4; yl++)
                local_rgba[yl] = (float)(rand()%256);
#endif

            t[0] = Timer_GetTicks();

            ETC_EncodeETC_CPU(
                quality,
                (int)global[0],
                (int)global[1],
                ETC_ALLOWED_MODES,
                alpha_cutoff,
                rgb_error_target,
                alpha_error_target,
                is_ypbpr,
                is_etc2,
                is_alpha,
                is_punchthrough,
                REFINE_RGB_SEARCH,
                1,
                1,
                local_width,
                local_height,
                local_rgba,
                local_block);

            local_bytes_in = (size_t)local_width * (size_t)local_height * sizeof(float) * (size_t)4;
            local_bytes_out = ((size_t)((local_width + 3) >> 2) * (size_t)((local_height + 3) >> 2) * (size_t)16) >> 1;
            if (is_alpha && !is_punchthrough)
                local_bytes_out <<= 1;

            //LOG_PRINT("Local width/height, global group, local group: %i x %i, %i x %i, %i x %i\n", local_width, local_height, (int)global[0], (int)global[1], (int)local[0], (int)local[0]);

            //printf("x, y, local_width, local_height: %i, %i, %i, %i, global: %i (in: %i bytes, out %i bytes)\n", x, y, local_width, local_height, global_sub_block, local_bytes_in, local_bytes_out);
            t[1] = Timer_GetTicks();
            //LOG_PRINT("Block encoding time: %.2fms\n", 1000.0 * Timer_TicksToSecondsf32(t[1] - t[0]));

            for (yl = 0; yl < ((local_height + 3) >> 2); yl++)
            {
                int src_offset = ((yl * ((local_width + 3) >> 2) * 16) >> 1) * scale;
                int bytes = ((((local_width + 3) >> 2) * 16) >> 1) * scale;
                int dst_offset = (int)(((((y*((global_sub_block * 4) >> 2) + yl) * ((width + 3) >> 2) + (x*((global_sub_block * 4) >> 2))) * 16) >> 1) * scale);
                memcpy(&(*block)[dst_offset], &local_block[src_offset], bytes);
            }
            System_AddProgress(1, 1);
        }
    }
    is_error = 0;

#if TEST_OPENCL_ONLY
    Sleep(1000);
    exit(0);
#endif
    Mem_Free(local_rgba);
    Mem_Free(local_block);
    if (is_error)
        return -1;

    return 0;
}


}
