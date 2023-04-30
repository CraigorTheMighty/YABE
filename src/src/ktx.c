#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <conio.h>
#include <commctrl.h>
#include <math.h>
#include <psapi.h>
#include <Dbghelp.h>

#include "..\inc\ktx\ktx.h"
#include "..\inc\timer.h"
#include "..\inc\system.h"
#include "..\inc\memory.h"

static char *KTXErrToString(KTX_error_code err)
{
	switch(err)
	{
		case KTX_SUCCESS:					return "KTX_SUCCESS";
		case KTX_FILE_DATA_ERROR:			return "KTX_FILE_DATA_ERROR";
		case KTX_FILE_ISPIPE:				return "KTX_FILE_ISPIPE";
		case KTX_FILE_OPEN_FAILED:			return "KTX_FILE_OPEN_FAILED";
		case KTX_FILE_OVERFLOW:				return "KTX_FILE_OVERFLOW";
		case KTX_FILE_READ_ERROR:			return "KTX_FILE_READ_ERROR";
		case KTX_FILE_SEEK_ERROR:			return "KTX_FILE_SEEK_ERROR";
		case KTX_FILE_UNEXPECTED_EOF:		return "KTX_FILE_UNEXPECTED_EOF";
		case KTX_FILE_WRITE_ERROR:			return "KTX_FILE_WRITE_ERROR";
		case KTX_GL_ERROR:					return "KTX_GL_ERROR";
		case KTX_INVALID_OPERATION:			return "KTX_INVALID_OPERATION";
		case KTX_INVALID_VALUE:				return "KTX_INVALID_VALUE";
		case KTX_NOT_FOUND:					return "KTX_NOT_FOUND";
		case KTX_OUT_OF_MEMORY:				return "KTX_OUT_OF_MEMORY";
		case KTX_TRANSCODE_FAILED:			return "KTX_TRANSCODE_FAILED";
		case KTX_UNKNOWN_FILE_FORMAT:		return "KTX_UNKNOWN_FILE_FORMAT";
		case KTX_UNSUPPORTED_TEXTURE_TYPE:	return "KTX_UNSUPPORTED_TEXTURE_TYPE";
		case KTX_UNSUPPORTED_FEATURE:		return "KTX_UNSUPPORTED_FEATURE";
		case KTX_LIBRARY_NOT_LINKED:		return "KTX_LIBRARY_NOT_LINKED";
		default:							return "<UNKNOWN>";
	}
}

int KTX_SaveETC(char *output_name, int format, int width, int height, int block_mul)
{
	ktxTexture1* texture;
	ktxTextureCreateInfo createInfo = {0};
	KTX_error_code result;
	ktx_uint32_t level, layer, faceSlice;
	ktx_size_t srcSize;
	int i;

	createInfo.glInternalformat = format;
	createInfo.baseWidth = width;
	createInfo.baseHeight = height;
	createInfo.baseDepth = 1;
	createInfo.numDimensions = 2;
	createInfo.numLevels = g_system.opts.enable_mipmap ? g_system.num_mipmap_levels : 1;
	createInfo.numLayers = 1;
	createInfo.numFaces = 1;
	createInfo.isArray = KTX_FALSE;
	createInfo.generateMipmaps = KTX_FALSE;
	result = ktxTexture1_Create(&createInfo, KTX_TEXTURE_CREATE_ALLOC_STORAGE, &texture);
	COND_PRINT(result != KTX_SUCCESS, "ktxTexture1_Create() result: %i (%s)\n", (int)result, KTXErrToString(result));
	level = 0;
	layer = 0;
	faceSlice = 0;
	if (result != KTX_SUCCESS)
		return -1;
	for (i = 0; i < g_system.num_mipmap_levels; i++)
	{
		srcSize = ((g_system.image[i].width + 3) >> 2) * ((g_system.image[i].height + 3) >> 2) * 8 * block_mul;
		LOG_PRINT("Mip level %i, %i x %i (%i x %i blocks), size: %i\n", i, g_system.image[i].width, g_system.image[i].height, ((g_system.image[i].width + 3) >> 2), ((g_system.image[i].height + 3) >> 2), (int)srcSize);
		result = ktxTexture_SetImageFromMemory((ktxTexture*)texture, i, layer, faceSlice, g_system.image[i].encoded, srcSize);
		COND_PRINT(result != KTX_SUCCESS, "ktxTexture_SetImageFromMemory() result: %i (%s)\n", (int)result, KTXErrToString(result));
		if (result != KTX_SUCCESS)
		{
			ktxTexture_Destroy((ktxTexture*)texture);
			return -1;
		}
	}
	result = ktxTexture_WriteToNamedFile((ktxTexture*)texture, output_name);
	COND_PRINT(result != KTX_SUCCESS, "ktxTexture_WriteToNamedFile() result: %i (%s)\n", (int)result, KTXErrToString(result));
	if (result != KTX_SUCCESS)
	{
		ktxTexture_Destroy((ktxTexture*)texture);
		return -1;
	}
	ktxTexture_Destroy((ktxTexture*)texture);
	return 0;
}
