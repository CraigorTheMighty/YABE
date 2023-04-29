float errsum = 0.0f;

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <conio.h>
#include <commctrl.h>
#include <math.h>
#include <psapi.h>
#include <Dbghelp.h>
#include <process.h>

#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glext.h>
#include <gl\wglext.h>

uint64_t g_ticks = 0;
/*
#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT   0x83F0		// BC1
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT  0x83F1		// BC1
#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT  0x83F2		// BC2
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT  0x83F3		// BC3
#define GL_COMPRESSED_RED_RGTC1           0x8DBB		// BC4
#define GL_COMPRESSED_SIGNED_RED_RGTC1    0x8DBC		// BC4
#define GL_COMPRESSED_RG_RGTC2            0x8DBD		// BC5
#define GL_COMPRESSED_SIGNED_RG_RGTC2     0x8DBE		// BC5

#define GL_COMPRESSED_SRGB_S3TC_DXT1_EXT  0x8C4C		// BC1
#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT 0x8C4D	// BC1
#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT 0x8C4E	// BC2
#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT 0x8C4F	// BC3

#define GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT 0x8E8E		// BC6
#define GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT 0x8E8F	// BC6
#define GL_COMPRESSED_RGBA_BPTC_UNORM     0x8E8C		// BC7
#define GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM 0x8E8D		// BC7

*/

#ifndef GL_ETC1_RGB8_OES
#define GL_ETC1_RGB8_OES	0x8D64
#endif
#ifndef GL_ETC1_SRGB8_NV
#define GL_ETC1_SRGB8_NV	0x88EE
#endif

#define CL_TARGET_OPENCL_VERSION	300

#include <cl\cl.h>

#include "..\inc\system.h"
#include "..\inc\image.h"
#include "..\inc\device_codec.h"
#include "..\inc\opencl.h"
#include "..\inc\timer.h"
#include "..\inc\ktx.h"
#include "..\inc\math.h"
#include "..\inc\memory.h"
#include "..\inc\opencl_bcn.h"

#include "..\inc\IL\il.h"
#include "..\inc\IL\ilu.h"
#include "..\inc\IL\ilut.h"

#include "..\inc\etc.h"
#include "..\inc\dds.h"

device_group_t *g_device_group;
system_t g_system = {0};

typedef struct
{
	BYTE type;
	BYTE length;
	WORD handle;
	BYTE data[1];
}dmi_header;

/*
Structure needed to get the SMBIOS table using GetSystemFirmwareTable API.
see https://docs.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-getsystemfirmwaretable
*/
typedef struct
{
	BYTE  Used20CallingMethod;
	BYTE  SMBIOSMajorVersion;
	BYTE  SMBIOSMinorVersion;
	BYTE  DmiRevision;
	DWORD  Length;
	BYTE  SMBIOSTableData[1];
}RawSMBIOSData ;

BOOL System_GetBIOSUUID(unsigned char *uuid)
{
	BOOL result = FALSE;

	RawSMBIOSData *smb = NULL;
	BYTE *data;

	DWORD size = 0;

	// Get size of BIOS table
	size = GetSystemFirmwareTable ('RSMB', 0, smb, size);
	smb = (RawSMBIOSData*)Mem_Malloc(size);

	// Get BIOS table
	GetSystemFirmwareTable ('RSMB', 0, smb, size);

	//Go through BIOS structures
	data = smb->SMBIOSTableData;
	while (data < smb->SMBIOSTableData + smb->Length)
	{
		BYTE *next;
		dmi_header *h = (dmi_header*)data;

		if (h->length < 4)
			break;

		//Search for System Information structure with type 0x01 (see para 7.2)
		if (h->type == 0x01 && h->length >= 0x19)
		{
			data += 0x08; //UUID is at offset 0x08

			// check if there is a valid UUID (not all 0x00 or all 0xff)
			BOOL all_zero = TRUE, all_one = TRUE;
			for (int i = 0; i < 16 && (all_zero || all_one); i++)
			{
				if (data[i] != 0x00) all_zero = FALSE;
				if (data[i] != 0xFF) all_one = FALSE;
			}
			if (!all_zero && !all_one)
			{
				/* As off version 2.6 of the SMBIOS specification, the first 3 fields
				of the UUID are supposed to be encoded on little-endian. (para 7.2.1) */
				*uuid++ = data[3];
				*uuid++ = data[2];
				*uuid++ = data[1];
				*uuid++ = data[0];
				*uuid++ = data[5];
				*uuid++ = data[4];
				*uuid++ = data[7];
				*uuid++ = data[6];
				for (int i = 8; i < 16; i++)
					*uuid++ = data[i];

				result = TRUE;
			}
			break;
		}

		//skip over formatted area
		next = data + h->length;

		//skip over unformatted area of the structure (marker is 0000h)
		while (next < smb->SMBIOSTableData + smb->Length && (next[0] != 0 || next[1] != 0))
			next++;
		next += 2;

		data = next;
	}
	Mem_Free(smb);
	return result;
}
unsigned int System_ProgressThread(void *p)
{
	uint64_t timer;
	int i = 0;
	timer = Timer_GetTicks();

	while(g_system.is_running)
	{
		i++;
		if ((!g_system.opts.enable_log) && (i == 10))
		{
			ALWAYS_PRINT_NODEC("\r%.1f sec... (%.2f%%)", Timer_TicksToSecondsf64(Timer_GetTicks() - timer), (100.0f * g_system.current_block) / g_system.total_blocks);
			fflush(stdout);
		}
		if (g_system.is_running)	// TODO: this will actually add up to 10ms to the encoding time, as the main thread blocks until this thread completes
			Sleep(10);
		if (i == 10)
			i = 0;
	}
	if (!g_system.opts.enable_log)
		ALWAYS_PRINT_NODEC("\r%.1f sec... (%.2f%%)\n", Timer_TicksToSecondsf64(Timer_GetTicks() - timer), 100.0f);
	g_system.progress_complete = 1;
	_endthread();
	return 0;
}
void System_StartProgressThread(int is_encode_progress, int total_iterations)
{
	if (!g_system.opts.enable_log)
	{
		g_system.is_encode_progress = is_encode_progress;
		g_system.is_running = 1;
		g_system.total_blocks = total_iterations;
		g_system.current_block = 0;
		g_system.progress_thread_id = 0;
		g_system.progress_thread_h = _beginthreadex(NULL, 0, System_ProgressThread, 0, 0, &g_system.progress_thread_id);
	}
}
void System_EndProgressThread()
{
	if (!g_system.opts.enable_log)
	{
		g_system.is_running = 0;
		WaitForSingleObject((HANDLE)g_system.progress_thread_h, INFINITE);
		CloseHandle((HANDLE)g_system.progress_thread_h);
		g_system.progress_thread_h = 0;
		g_system.progress_thread_id = 0;
	}
}
void System_AddProgress(int is_encode_progress, int iterations)
{
	if (!g_system.opts.enable_log && is_encode_progress == g_system.is_encode_progress)
	{
		g_system.current_block += iterations;
	}
}
void System_PrintUsage()
{
	g_system.opts.enable_log = 0;

	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("=====\n");
	ALWAYS_PRINT_NODEC("Usage\n");
	ALWAYS_PRINT_NODEC("=====\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("ImageCompressor [options]\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("Example: ImageCompressor -input \"test_image.jpg\" -output \"encoded\" -mode ETC2RGBA8 -mipmap\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("=======\n");
	ALWAYS_PRINT_NODEC("Options\n");
	ALWAYS_PRINT_NODEC("=======\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("-?\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("\tPrint this documentation and exit (overrides all other options).\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("-input \"[filename]\"\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("\tAttempt to load the image file [filename].\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("-output \"[filename]\"\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("\tSave the results to [filename] as KTX format, using the filename extension \".ktx\".\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("-quality [mode]\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("\tCompress the input image using quality [mode], where [mode] must be one of the following constants:\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("\t\tfast         Extremely fast, low quality.\n");
	ALWAYS_PRINT_NODEC("\t\tnormal       Moderate performance. Typically large quality improvement over \"fast\".\n");
	ALWAYS_PRINT_NODEC("\t\thigh         Slow. Typically small quality improvement over \"normal\".\n");
	ALWAYS_PRINT_NODEC("\t\tbest         Very slow. Typically tiny quality improvement over \"high\".\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("-mode [mode]\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("\tCompress the input image using [mode], where [mode] must be one of the following constants:\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("\t\tETC1             ETC1 RGB\n");
	ALWAYS_PRINT_NODEC("\t\tETC2             ETC2 RGB\n");
	ALWAYS_PRINT_NODEC("\t\tETC2RGBA8        ETC2 RGB with 8-bit alpha\n");
	ALWAYS_PRINT_NODEC("\t\tETC2RGBA1        ETC2 RGB with 1-bit alpha\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("\t\tBC1RGB           BC1 RGB (DXT1)\n");
	ALWAYS_PRINT_NODEC("\t\tBC1RGBA          BC1 RGB with 1-bit alpha (DXT1)\n");
	ALWAYS_PRINT_NODEC("\t\tBC2RGBA          BC2 RGBA (DXT3)\n");
	ALWAYS_PRINT_NODEC("\t\tBC3RGBA          BC3 RGBA (DXT5)\n");
	ALWAYS_PRINT_NODEC("\t\tBC4RED           BC4 single-channel (red)\n");
	ALWAYS_PRINT_NODEC("\t\tBC5RG            BC5 dual-channel (red, green)\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("-mipmap\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("\tGenerate mipmaps for output file.\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("-alpha_cutoff [value]\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("\tAlpha value below which pixels will be fully transparent in 1-bit alpha modes. Default value is 127.0.\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("-srgb\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("\tUse sRGB colourspace instead of RGB colourspace.\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("-log\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("\tPrint debug information while running.\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("-device [index/\"CPU\"]\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("\tOverride which device to use, or force usage of CPU-based codec. If the index specified is not a valid index,\n");
	ALWAYS_PRINT_NODEC("\tthe CPU-based codec will be used. If this option is not specified, the estimated fastest device will be used.\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("-cl_macroblock [value]\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("\tOverride the size of macroblocks to run the codec on. Larger values may increase performance but may not work\n");
	ALWAYS_PRINT_NODEC("\ton all hardware. If this option is not specified, the estimated best and safest macroblock size will be used.\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("====================\n");
	ALWAYS_PRINT_NODEC("ETC-specific options\n");
	ALWAYS_PRINT_NODEC("====================\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("-colour_error [value]\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("\tTarget colour error. Default value is 0.0. Higher values increase performance at the cost of quality.\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("-alpha_error [value]\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("\tTarget alpha error. Default value is 0.0. Higher values increase performance at the cost of quality.\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("-ypbpr\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("\tEncode by minimising error in YPbPr colourspace instead of RGB.\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("====================\n");
	ALWAYS_PRINT_NODEC("DDS-specific options\n");
	ALWAYS_PRINT_NODEC("====================\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("-ktx\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("\tSave encoded image as KTX file. If \"-dds\" is not specified, this option will be enabled by default.\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("-dds\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("\tSave encoded image as DDS file.\n");
	ALWAYS_PRINT_NODEC("\n");
	ALWAYS_PRINT_NODEC("=========================\n");
	ALWAYS_PRINT_NODEC("OpenCL compatible devices\n");
	ALWAYS_PRINT_NODEC("=========================\n");
	ALWAYS_PRINT_NODEC("\n");
	CL_ListCLDevices(TRUE);
}

// TODO: add error messages for options with missing arguments
int System_ParseOptions(int argc, char **argv)
{
	int i;
	int error = 0;

	for (i = 1; i < argc; i++)
	{
		if (!strcmp(argv[i], "-log"))
		{
			g_system.opts.enable_log = 1;
		}
		else if (!strcmp(argv[i], "-mode"))
		{
			i++;
			if (i == argc)
				return 1;
			if (!strcmp(argv[i], "ETC1"))
				g_system.opts.encode_mode = MODE_ETC1;
			else if (!strcmp(argv[i], "ETC2"))
				g_system.opts.encode_mode = MODE_ETC2_RGB;
			else if (!strcmp(argv[i], "ETC2RGBA1"))
				g_system.opts.encode_mode = MODE_ETC2_RGBA1;
			else if (!strcmp(argv[i], "ETC2RGBA8"))
				g_system.opts.encode_mode = MODE_ETC2_RGBA8;
			else if (!strcmp(argv[i], "BC1RGB"))
				g_system.opts.encode_mode = MODE_BC1_RGB;
			else if (!strcmp(argv[i], "BC1RGBA"))
				g_system.opts.encode_mode = MODE_BC1_RGBA;
			else if (!strcmp(argv[i], "BC2RGBA"))
				g_system.opts.encode_mode = MODE_BC2_RGBA;
			else if (!strcmp(argv[i], "BC3RGBA"))
				g_system.opts.encode_mode = MODE_BC3_RGBA;
			else if (!strcmp(argv[i], "BC4RED"))
				g_system.opts.encode_mode = MODE_BC4_RED;
			else if (!strcmp(argv[i], "BC5RG"))
				g_system.opts.encode_mode = MODE_BC5_RG;
			else
			{
				System_PrintUsage();
				return 1;
			}
		}
		else if (!strcmp(argv[i], "-mipmap"))
		{
			g_system.opts.enable_mipmap = 1;
		}
		else if (!strcmp(argv[i], "-ypbpr"))
		{
			g_system.opts.is_ypbpr = 1;
		}
		else if (!strcmp(argv[i], "-input"))
		{
			i++;
			if (i == argc)
			{
				System_PrintUsage();
				return 1;
			}
			Mem_Free(g_system.opts.in_filename);
			g_system.opts.in_filename = Mem_Malloc(strlen(argv[i]) + 1);
			strcpy_s(g_system.opts.in_filename, strlen(argv[i]) + 1, argv[i]);
		}
		else if (!strcmp(argv[i], "-output"))
		{
			char *name;
			char *ptr;
			i++;
			if (i == argc)
			{
				System_PrintUsage();
				return 1;
			}
			Mem_Free(g_system.opts.out_filename);
			g_system.opts.out_filename = Mem_Malloc(strlen(argv[i]) + 1);
			strcpy_s(g_system.opts.out_filename, strlen(argv[i]) + 1, argv[i]);
			name = Mem_Malloc(strlen(g_system.opts.out_filename) + 1 + 4);
			strcpy_s(name, strlen(g_system.opts.out_filename) + 1 + 4, g_system.opts.out_filename);
			ptr = strrchr(name, '.');

			if (ptr)
			{
				if (strlen(ptr) == 4)
				{
					if (!(((ptr[1] == 'k') || (ptr[1] == 'K')) && ((ptr[2] == 't') || (ptr[2] == 'T')) && ((ptr[3] == 'x') || (ptr[3] == 'X'))))
						sprintf_s(ptr, 5, ".ktx");
				}
				else
					sprintf_s(ptr, 5, ".ktx");
			}
			else
				strcat_s(name, strlen(g_system.opts.out_filename) + 1 + 4, ".ktx");
			Mem_Free(g_system.opts.out_filename);
			g_system.opts.out_filename = name;
			g_system.opts.out_filename_dds = Mem_Malloc(strlen(g_system.opts.out_filename) + 1);
			memcpy(g_system.opts.out_filename_dds, g_system.opts.out_filename, strlen(g_system.opts.out_filename) + 1);
			ptr = strrchr(g_system.opts.out_filename_dds, '.');
			memcpy(ptr, ".dds", 5);
		}
		else if (!strcmp(argv[i], "-colour_error"))
		{
			i++;
			if (i == argc)
			{
				System_PrintUsage();
				return 1;
			}
			g_system.opts.colour_error_target = (float)atof(argv[i]);
			g_system.opts.colour_error_target = g_system.opts.colour_error_target < 0.0f ? 0.0f : g_system.opts.colour_error_target;
		}
		else if (!strcmp(argv[i], "-alpha_error"))
		{
			i++;
			if (i == argc)
			{
				System_PrintUsage();
				return 1;
			}
			g_system.opts.alpha_error_target = (float)atof(argv[i]);
			g_system.opts.alpha_error_target = g_system.opts.alpha_error_target < 0.0f ? 0.0f : g_system.opts.alpha_error_target;
		}
		else if (!strcmp(argv[i], "-alpha_cutoff"))
		{
			i++;
			if (i == argc)
			{
				System_PrintUsage();
				return 1;
			}
			g_system.opts.alpha_cutoff = (float)atof(argv[i]);
		}
		else if (!strcmp(argv[i], "-device"))
		{
			i++;
			if (i == argc)
			{
				System_PrintUsage();
				return 1;
			}
			if (!_stricmp(argv[i], "CPU"))
				g_system.opts.force_cpu = 1;
			else
			{
				g_system.opts.force_cpu = 0;
				g_system.opts.cl_device = atoi(argv[i]);
				if (g_system.opts.cl_device < 0)
					g_system.opts.cl_device = (1 << 30);
			}
		}
		else if (!strcmp(argv[i], "-srgb"))
		{
			g_system.opts.srgb = 1;
		}
		else if (!strcmp(argv[i], "-quality"))
		{
			i++;
			if (i == argc)
			{
				System_PrintUsage();
				return 1;
			}
			if (!_stricmp(argv[i], "fast"))
				g_system.opts.dds_quality = CODEC_QUALITY_FAST;
			else if (!_stricmp(argv[i], "normal"))
				g_system.opts.dds_quality = CODEC_QUALITY_NORMAL;
			else if (!_stricmp(argv[i], "high"))
				g_system.opts.dds_quality = CODEC_QUALITY_HIGH;
			else if (!_stricmp(argv[i], "best"))
				g_system.opts.dds_quality = CODEC_QUALITY_BEST;
			else
			{
				ALWAYS_PRINT_NODEC("ERROR: Unknown quality mode \"%s\"\n", argv[i]);
				System_PrintUsage();
				return 1;
			}
		}
		else if (!strcmp(argv[i], "-ktx"))
		{
			g_system.opts.save_ktx = 1;
		}
		else if (!strcmp(argv[i], "-dds"))
		{
			g_system.opts.save_dds = 1;
		}
		else if (!strcmp(argv[i], "-?"))
		{
			System_PrintUsage();
			return -1;
		}
		else if (!strcmp(argv[i], "-cl_macroblock"))
		{
			i++;
			if (i == argc)
			{
				System_PrintUsage();
				return 1;
			}
			g_system.opts.cl_macroblock_size = (int)Math_FloorPow2u64(atoi(argv[i]));
			g_system.opts.override_macroblock = g_system.opts.cl_macroblock_size;
			if (g_system.opts.cl_macroblock_size < 1)
			{
				g_system.opts.cl_macroblock_size = 1;
				g_system.opts.override_macroblock = 1;
			}
		}
		else
		{
			ALWAYS_PRINT_NODEC("ERROR: Unknown option \"%s\"\n", argv[i]);
			System_PrintUsage();
			return 1;
		}
	}

	if (!g_system.opts.in_filename)
	{
		ALWAYS_PRINT_NODEC("ERROR: No input filename specified.\n");
		error = 1;
	}
	if (!g_system.opts.out_filename)
	{
		ALWAYS_PRINT_NODEC("ERROR: No output filename specified.\n");
		error = 1;
	}
	if (g_system.opts.encode_mode == MODE_INVALID)
	{
		ALWAYS_PRINT_NODEC("ERROR: No encoding mode specified.\n");
		error = 1;
	}
	if (error)
	{
		System_PrintUsage();
		return 1;
	}

	return 0;
}

char *System_ModeToString()
{
	switch(g_system.opts.encode_mode)
	{
		case MODE_ETC1:
			return "ETC1";
		case MODE_ETC2_RGB:
			return "ETC2_RGB";
		case MODE_ETC2_RGBA1:
			return "ETC2_RGBA1";
		case MODE_ETC2_RGBA8:
			return "ETC2_RGBA8";
		case MODE_BC1_RGB:
			return "BC1_RGB";
		case MODE_BC1_RGBA:
			return "BC1_RGBA";
		case MODE_BC2_RGBA:
			return "BC2_RGBA";
		case MODE_BC3_RGBA:
			return "BC3_RGBA";
		case MODE_BC4_RED:
			return "BC4_RED";
		case MODE_BC5_RG:
			return "BC5_RG";
		default:
			return "INVALID";
	}
}

int System_ModeToCodecID(int mode)
{
	switch (mode)
	{
		case MODE_BC1_RGB:		return CODEC_BC1_RGB;
		case MODE_BC1_RGBA:		return CODEC_BC1_RGBA;
		case MODE_BC2_RGBA:		return CODEC_BC2_RGBA;
		case MODE_BC3_RGBA:		return CODEC_BC3_RGBA;
		case MODE_BC4_RED:		return CODEC_BC4_RED;
		case MODE_BC5_RG:		return CODEC_BC5_RG;
		case MODE_ETC1:			return CODEC_ETC1;
		case MODE_ETC2_RGB:		return CODEC_ETC2_RGB;
		case MODE_ETC2_RGBA1:	return CODEC_ETC2_RGBA1;
		case MODE_ETC2_RGBA8:	return CODEC_ETC2_RGBA8;
		default: return -1;
	}
}

int System_CodecToGLFormat(int codec, int is_srgb)
{
	switch (codec)
	{
		case CODEC_BC1_RGB:		return is_srgb ? GL_COMPRESSED_SRGB_S3TC_DXT1_EXT : GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
		case CODEC_BC1_RGBA:	return is_srgb ? GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT : GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		case CODEC_BC2_RGBA:	return is_srgb ? GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT : GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		case CODEC_BC3_RGBA:	return is_srgb ? GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT : GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		case CODEC_BC4_RED:		return GL_COMPRESSED_RED_RGTC1;
		case CODEC_BC5_RG:		return GL_COMPRESSED_RG_RGTC2;
		case CODEC_ETC1:		return GL_ETC1_RGB8_OES;
		case CODEC_ETC2_RGB:	return is_srgb ? GL_COMPRESSED_SRGB8_ETC2 : GL_COMPRESSED_RGB8_ETC2;
		case CODEC_ETC2_RGBA1:	return is_srgb ? GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2 : GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2;
		case CODEC_ETC2_RGBA8:	return is_srgb ? GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC : GL_COMPRESSED_RGBA8_ETC2_EAC;
		default: return -1;
	}
}

int main(int argc, char **argvv)
{
	int error = 0;
	wchar_t *in_wpath = 0;
	wchar_t *out_wpath = 0;
	ILuint devil_image;
	ILboolean result;
	ILuint uint_result;
	ILuint width;
	ILuint height;
	int gl_mode;
	uint64_t i;
	HWND consolehwnd = GetConsoleWindow();
	DWORD dwprocessid;
	unsigned char *rgba_u8;
	int ret;
	char *argv[256];
	image_t image;
	uint64_t kernel_ticks = 0;
	uint64_t total_ticks = 0;
	int codec;
	uint64_t local_kernel_ticks;
	uint64_t local_total_ticks;
	void *options;
	codec_options_etc_t etc_opts;
	codec_options_bcn_t bcn_opts;
	int quality;
	int count;
	int block_size;
	int num_cl_devices;

	for (i = 0; i < argc; i++)
		argv[i] = argvv[i];

#if 0
#ifdef _DEBUG
	printf("DEBUG MODE\n");
	argv[ 0] = "ImageCompressor.exe";
	argv[ 1] = "-input";
	argv[ 2] = "E:\\Craig\\Programming\\New Stuff\\ImageCompressor\\x64\\Debug\\1024x1024.png";
	argv[ 3] = "-output";
	argv[ 4] = "E:\\Craig\\Programming\\New Stuff\\ImageCompressor\\x64\\Debug\\TEST";
	argv[ 5] = "-mode";
	argv[ 6] = "ETC1";
	argv[ 7] = "-quality";
	argv[ 8] = "fast";
	argv[ 9] = "-device";
	argv[10] = "CPU";
	argv[11] = "-dds";
	argv[12] = "-log";
	argc = 13;
#endif
#endif
	g_system.info.time_start = Timer_GetTicks();
	g_system.opts.dds_quality = DDS_QUALITY_NORMAL;

	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_WIN32);

	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_UPPER_LEFT);

	ilGenImages(1, &devil_image);
	ilBindImage(devil_image);

	ALWAYS_PRINT_NODEC("\n");

	g_device_group = DeviceGroup_New();

	num_cl_devices = g_device_group->num_devices - 1;

	CL_ETC_Init(g_device_group);
	CL_BCN_Init(g_device_group);

	g_system.opts.alpha_cutoff = 127.0f;
	g_system.opts.colour_error_target = 0.0f;
	g_system.opts.alpha_error_target = 0.0f;
	g_system.opts.cl_macroblock_size = 0;
	g_system.opts.cl_device = -1;

	ret = System_ParseOptions(argc, argv);

	if (ret == 1)
	{
		ALWAYS_PRINT_NODEC("\n****************************\n");
		ALWAYS_PRINT_NODEC("Error parsing command-line.\n");
		ALWAYS_PRINT_NODEC("****************************\n");
		for (i = 0; i < argc; i++)
			printf("Argument %i: %s\n", i, argv[i]);
		error = 1;
		goto MAIN_EXIT;
	}
	else if (ret == -1)
	{
		error = 0;
		goto MAIN_EXIT;
	}

	in_wpath = Mem_Malloc(sizeof(wchar_t) * (strlen(g_system.opts.in_filename) + 1));
	out_wpath = Mem_Malloc(sizeof(wchar_t) * (strlen(g_system.opts.out_filename) + 1));
	swprintf(in_wpath, (strlen(g_system.opts.in_filename) + 1), L"%S", g_system.opts.in_filename);
	swprintf(out_wpath, (strlen(g_system.opts.out_filename) + 1), L"%S", g_system.opts.out_filename);
	result = ilLoadImage(in_wpath);

	if (!result)
	{
		ilDeleteImages(1, &devil_image);
		ALWAYS_PRINT("Error loading file \"%ls\".\n", in_wpath);
		error = 1;
		goto MAIN_EXIT;
	}
	ilBindImage(devil_image);
	width = ilGetInteger(IL_IMAGE_WIDTH);
	height = ilGetInteger(IL_IMAGE_HEIGHT);

	if (width * height > 67108864)
	{
		ilDeleteImages(1, &devil_image);
		ALWAYS_PRINT("Image too large: max size of image must be less than 67.1 MP (image is %.2f MP)\n", (width * height) / 1000000.0);
		error = 1;
		goto MAIN_EXIT;
	}

	ALWAYS_PRINT_NODEC("Input: \"%s\" (%i x %i)\n", g_system.opts.in_filename, width, height);
	if (Codec_GroupFromCodec(System_ModeToCodecID(g_system.opts.encode_mode)) == CODEC_GROUP_BCN)
	{
		ALWAYS_PRINT_NODEC("Output: ");
		if (g_system.opts.save_ktx)
			ALWAYS_PRINT_NODEC("\"%s\"", g_system.opts.out_filename);
		if (g_system.opts.save_ktx && g_system.opts.save_dds)
			ALWAYS_PRINT_NODEC(", ");
		if (g_system.opts.save_dds)
			ALWAYS_PRINT_NODEC("\"%s\"", g_system.opts.out_filename_dds);
		ALWAYS_PRINT_NODEC("\n");
	}
	else
	{
		ALWAYS_PRINT_NODEC("Output: \"%s\"\n", g_system.opts.out_filename);
	}
	ALWAYS_PRINT_NODEC("Colour mode: %s\n", g_system.opts.is_ypbpr ? "YPbPr" : "RGB");
	ALWAYS_PRINT_NODEC("Colourspace: %s\n", g_system.opts.srgb? "sRGB" : "RGB");
	ALWAYS_PRINT_NODEC("Encoding mode: %s\n", System_ModeToString());
	ALWAYS_PRINT_NODEC("Mipmaps: %s (%i)\n", g_system.opts.enable_mipmap ? "Enabled" : "Disabled", g_system.num_mipmap_levels);
	ALWAYS_PRINT_NODEC("Alpha cutoff: %f\n", g_system.opts.alpha_cutoff);
	ALWAYS_PRINT_NODEC("Colour error target: %f\n", g_system.opts.colour_error_target);
	ALWAYS_PRINT_NODEC("Alpha error target: %f\n", g_system.opts.alpha_error_target);
	ALWAYS_PRINT_NODEC("Logging: %s\n", g_system.opts.enable_log ? "Enabled" : "Disabled");

	g_system.num_mipmap_levels = 1;

	if (g_system.opts.enable_mipmap)
	{
		int w = width;
		int h = height;
		while ((w > 1) || (h > 1))
		{
			w >>= w > 1 ? 1 : 0;
			h >>= h > 1 ? 1 : 0;
			g_system.num_mipmap_levels++;
		}
	}

	g_system.image = Mem_Malloc(sizeof(sys_image_t) * g_system.num_mipmap_levels);
	memset(g_system.image, 0, sizeof(sys_image_t) * g_system.num_mipmap_levels);

	g_system.image[0].rgba = Mem_Malloc((uint64_t)width * (uint64_t)height * 4 * sizeof(float));
	g_system.image[0].width = width;
	g_system.image[0].height = height;

	rgba_u8 = Mem_Malloc((uint64_t)width * (uint64_t)height * 4);

	uint_result = ilCopyPixels(0, 0, 0, width, height, 1, IL_RGBA, IL_FLOAT, g_system.image[0].rgba);

	for (i = 0; i < ((uint64_t)width * (uint64_t)height * 4); i++)
	{
		g_system.image[0].rgba[i] *= 255.0f;
	}
	Mem_Free(rgba_u8);

	Image_GenMipMaps();

	ilDeleteImages(1, &devil_image);

	codec = System_ModeToCodecID(g_system.opts.encode_mode);
	gl_mode = System_CodecToGLFormat(codec, g_system.opts.srgb);

	image = Image_FromSysImage(g_system.image, g_system.num_mipmap_levels, codec);

	if (Codec_GroupFromCodec(codec) == CODEC_GROUP_ETC)
	{
		options = &etc_opts;

		etc_opts.common.alpha_cutoff = (int)g_system.opts.alpha_cutoff;
		etc_opts.common.is_srgb = g_system.opts.srgb;
		etc_opts.common.is_ypbpr = g_system.opts.is_ypbpr;
		etc_opts.alpha_error = g_system.opts.alpha_error_target;
		etc_opts.colour_error = g_system.opts.colour_error_target;
		etc_opts.common.quality = g_system.opts.dds_quality;

		g_system.opts.save_ktx = 1;
		g_system.opts.save_dds = 0;

		quality = etc_opts.common.quality;
		block_size = codec == CODEC_ETC2_RGBA8 ? 2 : 1;
	}
	else //if (Codec_GroupFromCodec(codec) == CODEC_GROUP_BCN)
	{
		options = &bcn_opts;

		bcn_opts.common.alpha_cutoff = (int)g_system.opts.alpha_cutoff;
		bcn_opts.common.is_srgb = g_system.opts.srgb;
		bcn_opts.common.is_ypbpr = g_system.opts.is_ypbpr;
		bcn_opts.output_dds = g_system.opts.save_dds;
		bcn_opts.output_ktx = g_system.opts.save_ktx;
		bcn_opts.is_test = 0;
		bcn_opts.common.quality = g_system.opts.dds_quality;

		quality = bcn_opts.common.quality;
		block_size = DDS_BlockSize(gl_mode) >> 3;
	}

	if (g_system.opts.cl_device == -1 && !g_system.opts.force_cpu)
	{
		int best_device = 0;
		double best_performance;

		ALWAYS_PRINT_NODEC("Finding best device...\n");

		Codec_InspectGroup(g_device_group, 0, Codec_GroupFromCodec(codec));

		best_performance = g_device_group->device[0].codec[codec].pixels_per_second[quality];

		Codec_DeInspectGroup(&g_device_group->device[0], Codec_GroupFromCodec(codec));

		ALWAYS_PRINT_NODEC("Device CPU performance: %.2f MP/s\n", best_performance / 1000000.0);

		for (i = 1; i < g_device_group->num_devices; i++)
		{
			int ret = Codec_InspectGroup(g_device_group, (int)i, Codec_GroupFromCodec(codec));
			if (!ret)
			{
				ALWAYS_PRINT_NODEC("Device %i performance: %.2f MP/s\n", (int)i - 1, g_device_group->device[i].codec[codec].pixels_per_second[quality] / 1000000.0);
				if (g_device_group->device[i].codec[codec].pixels_per_second[quality] > best_performance)
				{
					best_performance = g_device_group->device[i].codec[codec].pixels_per_second[quality];
					best_device = (int)i;
				}
			}
			else
				ALWAYS_PRINT_NODEC("Device %i unavailable due to build errors\n", (int)i - 1);
			Codec_DeInspectGroup(&g_device_group->device[i], Codec_GroupFromCodec(codec));
		}

		g_system.opts.cl_device = best_device;

		if (g_system.opts.cl_device == 0)
			ALWAYS_PRINT_NODEC("Using device CPU\n");
		else
			ALWAYS_PRINT_NODEC("Using device %i\n", g_system.opts.cl_device - DEVICE_CL_START);
	}
	else
	{
		g_system.opts.cl_device = g_system.opts.cl_device + DEVICE_CL_START;

		if (g_system.opts.cl_device >= g_device_group->num_devices)
		{
			ALWAYS_PRINT_NODEC("Invalid device index, reverting to CPU\n");
			g_system.opts.force_cpu = 1;
			g_system.opts.cl_device = 0;
		}
	}

	ret = Codec_LoadGroup(g_device_group, g_system.opts.cl_device, Codec_GroupFromCodec(codec));

	if (!ret)
	{
		if ((width * height) / Codec_GetPerformance(g_device_group, g_system.opts.cl_device, codec, options) < 1.0)
			ALWAYS_PRINT_NODEC("Estimated time to encode: %.2f - %.2f ms\n", 0.5 * 1000.0 * (width * height) / Codec_GetPerformance(g_device_group, g_system.opts.cl_device, codec, options), 1000.0 * (width * height) / Codec_GetPerformance(g_device_group, g_system.opts.cl_device, codec, options));
		else
			ALWAYS_PRINT_NODEC("Estimated time to encode: %.2f - %.2f sec\n", 0.5 * (width * height) / Codec_GetPerformance(g_device_group, g_system.opts.cl_device, codec, options), (width * height) / Codec_GetPerformance(g_device_group, g_system.opts.cl_device, codec, options));
		ALWAYS_PRINT_NODEC("Encoding.\n");

		count = 0;
		for (i = 0; i < g_system.num_mipmap_levels; i++)
			count += Codec_GetEncodeChunks(g_device_group, g_system.opts.cl_device, &image, codec, (int)i, g_system.opts.cl_macroblock_size, options);
		System_StartProgressThread(1, count);

		for (i = 0; i < g_system.num_mipmap_levels; i++)
		{
			if (Codec_Encode(g_device_group, g_system.opts.cl_device, &image, codec, (int)i, g_system.opts.cl_macroblock_size, &local_kernel_ticks, &local_total_ticks, options))
			{
				if (g_system.opts.force_cpu == 0)
				{
					ret = 1;
					break;
				}
			}
			kernel_ticks += local_kernel_ticks;
			total_ticks += local_total_ticks;
		}
		System_EndProgressThread();
		if (Timer_TicksToSecondsf64(total_ticks) < 1.0)
			ALWAYS_PRINT_NODEC("Encoding took %.2f ms (%.2f MP/s)\n", 1000.0 * Timer_TicksToSecondsf64(total_ticks), (width * height) / (1000000.0 * Timer_TicksToSecondsf64(total_ticks)));
		else
			ALWAYS_PRINT_NODEC("Encoding took %.2f sec (%.2f MP/s)\n", Timer_TicksToSecondsf64(total_ticks), (width * height) / (1000000.0 * Timer_TicksToSecondsf64(total_ticks)));
	}
	if (ret) // NOT else, ret is conditionally set in previous conditional
	{
		ALWAYS_PRINT("Error with device %i, reverting to CPU\n", g_system.opts.cl_device - DEVICE_CL_START);
		g_system.opts.force_cpu = 1;
		g_system.opts.cl_device = 0;

		Codec_LoadGroup(g_device_group, g_system.opts.cl_device, Codec_GroupFromCodec(codec));

		if ((width * height) / Codec_GetPerformance(g_device_group, g_system.opts.cl_device, codec, options) < 1.0)
			ALWAYS_PRINT_NODEC("Estimated time to encode: %.2f - %.2f ms\n", 0.5 * 1000.0 * (width * height) / Codec_GetPerformance(g_device_group, g_system.opts.cl_device, codec, options), 1000.0 * (width * height) / Codec_GetPerformance(g_device_group, g_system.opts.cl_device, codec, options));
		else
			ALWAYS_PRINT_NODEC("Estimated time to encode: %.2f - %.2f sec\n", 0.5 * (width * height) / Codec_GetPerformance(g_device_group, g_system.opts.cl_device, codec, options), (width * height) / Codec_GetPerformance(g_device_group, g_system.opts.cl_device, codec, options));
		ALWAYS_PRINT_NODEC("Encoding.\n");

		kernel_ticks = 0;
		total_ticks = 0;
		ret = 0;

		count = 0;
		for (i = 0; i < g_system.num_mipmap_levels; i++)
			count += Codec_GetEncodeChunks(g_device_group, g_system.opts.cl_device, &image, codec, (int)i, g_system.opts.cl_macroblock_size, options);
		System_StartProgressThread(1, count);

		for (i = 0; i < g_system.num_mipmap_levels; i++)
		{
			Codec_Encode(g_device_group, g_system.opts.cl_device, &image, codec, (int)i, g_system.opts.cl_macroblock_size, &local_kernel_ticks, &local_total_ticks, options);

			kernel_ticks += local_kernel_ticks;
			total_ticks += local_total_ticks;
		}
		System_EndProgressThread();
		if (Timer_TicksToSecondsf64(total_ticks) < 1.0)
			ALWAYS_PRINT_NODEC("Encoding took %.2f ms (%.2f MP/s)\n", 1000.0 * Timer_TicksToSecondsf64(total_ticks), (width * height) / (1000000.0 * Timer_TicksToSecondsf64(total_ticks)));
		else
			ALWAYS_PRINT_NODEC("Encoding took %.2f sec (%.2f MP/s)\n", Timer_TicksToSecondsf64(total_ticks), (width * height) / (1000000.0 * Timer_TicksToSecondsf64(total_ticks)));
	}

	for (i = 0; i < g_system.num_mipmap_levels; i++)
		g_system.image[i].encoded = image.dst_encoded[i];

	if (g_system.opts.save_ktx)
		if (KTX_SaveETC(g_system.opts.out_filename, gl_mode, width, height, block_size))
		{
			error = 1;
			ALWAYS_PRINT("Error during saving KTX file \"%s\".\n", g_system.opts.out_filename);
			goto MAIN_EXIT;
		}
	if (g_system.opts.save_dds)
		if (DDS_SaveDDS(g_system.opts.out_filename_dds, gl_mode))
		{
			error = 1;
			ALWAYS_PRINT("Error during saving DDS file \"%s\".\n", g_system.opts.out_filename_dds);
			goto MAIN_EXIT;
		}

	Image_Destroy(&image);

MAIN_EXIT:

	DeviceGroup_Destroy(g_device_group);
	Mem_Free(g_device_group);

	for (i = 0; i < g_system.num_mipmap_levels; i++)
		Mem_Free(g_system.image[i].rgba);
	Mem_Free(g_system.image);

	if (error)
	{
		ALWAYS_PRINT_NODEC("\n****************************\n");
		ALWAYS_PRINT_NODEC("One or more errors occurred.\n");
		ALWAYS_PRINT_NODEC("****************************\n");
	}
	Mem_Free(in_wpath);
	Mem_Free(out_wpath);
	Mem_Free(g_system.opts.in_filename);
	Mem_Free(g_system.opts.out_filename);
	Mem_Free(g_system.opts.out_filename_dds);

	if (g_system.opts.enable_log)
		Mem_ReportAllocatedBlocks();

	if (!error)
		ALWAYS_PRINT_NODEC("Task completed.\n");

	GetWindowThreadProcessId(consolehwnd, &dwprocessid);
	if (GetCurrentProcessId() == dwprocessid)
	{
		ALWAYS_PRINT_NODEC("\n\nPress any key to exit.\n");
		_getch();
	}

	fflush(stdout);
	fflush(stderr);

	return error ? -1 : num_cl_devices;
}
