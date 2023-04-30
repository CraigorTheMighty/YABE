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
#include "..\inc\opencl_bcn.h"
#include "..\inc\etc.h"
#include "..\inc\dds.h"

int CPU_Encode(device_t *device, image_t *image, codec_e codec, int mip_level, int override_macro_size, uint64_t *kernel_ticks, uint64_t *total_ticks, void *context)
{
	uint8_t *block = 0;
	uint64_t t[2];
	
	t[0] = Timer_GetTicks();

	switch (Codec_GroupFromCodec(codec))
	{
		case CODEC_GROUP_BCN:
		{
			codec_options_bcn_t *options = (codec_options_bcn_t*)context;
			int old_options = g_system.opts.dds_quality;

			g_system.opts.dds_quality = BCN_QualityToQualityBitfield(options->common.quality);

			if (options->is_test)
				g_system.opts.dds_quality |= DDS_ENCODE_TEST;

			EncodeDDSCPU(&block, image->src_rgba_0_255[mip_level], System_CodecToGLFormat(codec, options->common.is_srgb), image->src_width[mip_level], image->src_height[mip_level], (float)options->common.alpha_cutoff);

			g_system.opts.dds_quality = old_options;

			break;
		}
		case CODEC_GROUP_ETC:
		{
			codec_options_etc_t *options = (codec_options_etc_t*)context;

			if (override_macro_size)
				g_system.opts.cl_macroblock_size = override_macro_size;
			else
				g_system.opts.cl_macroblock_size = device->codec[codec].macroblock_size[options->common.quality];

			LOG_PRINT("quality %i\n", options->common.quality);

			EncodeETCCPU(
				options->common.quality,
				&block, 
				image->src_rgba_0_255[mip_level], 
				image->src_width[mip_level], 
				image->src_height[mip_level], 
				options->common.is_ypbpr,
				codec == CODEC_ETC1 ? 0 : 1,	// is_etc2
				((codec == CODEC_ETC2_RGBA1) || (codec == CODEC_ETC2_RGBA8)) ? 1 : 0,	// is_alpha
				codec == CODEC_ETC2_RGBA1 ? 1 : 0, // is_punchthrough
				(float)options->common.alpha_cutoff,
				options->colour_error,
				options->alpha_error);

			break;
		}
		default: 
			return -1;
	}

	t[1] = Timer_GetTicks();
	if (kernel_ticks)
		*kernel_ticks = t[1] - t[0];
	if (total_ticks)
		*total_ticks = t[1] - t[0];

	memcpy(image->dst_encoded[mip_level], block, Image_GetRequiredBytes(image->src_width[mip_level], image->src_height[mip_level], codec));
	Mem_Free(block);
	return 0;
}