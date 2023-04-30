#define NOMINMAX

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
#include <dxgiformat.h>
#include <ddraw.h>

#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glext.h>
#include <gl\wglext.h>

#define CL_TARGET_OPENCL_VERSION	200
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS

#define BINARY_FILE_TARGET_ELEMENTS_NO_UUID (28 + 3 * 16)

#define BINARY_FILE_TARGET_BYTES  (16 + BINARY_FILE_TARGET_ELEMENTS_NO_UUID*4)
#define BINARY_FILE_TARGET_ELEMENTS (16 + BINARY_FILE_TARGET_ELEMENTS_NO_UUID)

#include <cl\cl.h>

#include "..\inc\IL\il.h"
#include "..\inc\IL\ilu.h"
#include "..\inc\IL\ilut.h"

#include "../inc/math.h"
#include "../inc/memory.h"
#include "../inc/dds.h"
#include "../inc/system.h"
#include "../inc/timer.h"
#include "../inc/math.h"
#include "../inc/vecmat.h"
#include "../inc/dds_const.h"
#include "../inc/dds_util.h"
#include "../inc/dds.h"
#include "..\inc\image.h"
#include "..\inc\device_codec.h"
#include "../inc/opencl.h"

#define RGBCX_IMPLEMENTATION

#include "../inc/rgbcx.h"

extern "C"
{
	void RGBCX_Init()
	{
		rgbcx::init(rgbcx::bc1_approx_mode::cBC1IdealRound4);
	}
	void RGBCX_EncodeBC1(uint8_t *block_out, double *block_in, int block_x, int block_y)
	{
		uint8_t block_in_rgba8[4*4*4];
		int i;

		for (i = 0; i < 64; i++)
		{
			if (block_in[i] > 255.0)
				block_in_rgba8[i] = 255;
			else if (block_in[i] < 0.0)
				block_in_rgba8[i] = 0;
			else
				block_in_rgba8[i] = (uint8_t)block_in[i];
		}

		rgbcx::encode_bc1(RGBCX_QUALITY_VALUE, block_out, block_in_rgba8, false, false);
	}
	void RGBCX_EncodeBC4(uint8_t *block_out, double *block_in, int block_x, int block_y)
	{
		uint8_t block_in_rgba8[4*4*4];
		int i;

		for (i = 0; i < 64; i++)
		{
			if (block_in[i] > 255.0)
				block_in_rgba8[i] = 255;
			else if (block_in[i] < 0.0)
				block_in_rgba8[i] = 0;
			else
				block_in_rgba8[i] = (uint8_t)block_in[i];
		}

		rgbcx::encode_bc4(block_out, block_in_rgba8);
	}
}
