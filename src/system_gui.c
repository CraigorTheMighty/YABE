#define OUTPUT_TYPE_DDS 0
#define OUTPUT_TYPE_KTX	1

#define MACROS_X		(512 - 64 - 16 - 16 + 80)
#define OPTION_WIDTH	(384 + 80)
#define WIDTH_FULL		(464 + 80)
#define WIDTH_SRGB		(64)
#define WIDTH_MIPMAPS	(80)
#define POS_MIPMAPS_X	(112)
#define POS_SRGB_X		(112 + 96)
#define POS_SAVEKTX_X	(112 + 96 + 80)
#define POS_SAVEDDS_X	(216 + 96 + 80)

#define WINDOW_CLASSNAME	L"YABE"
#define WINDOW_TITLE		L"YABE"

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <conio.h>
#include <commctrl.h>
#include <math.h>
#include <psapi.h>
#include <Dbghelp.h>
#include <process.h>
#include <uxtheme.h>
#include <shlobj.h>

#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glext.h>
#include <gl\wglext.h>

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

#define WM_USER_LOADING_COMPLETE	(WM_USER+1)
#define WM_USER_ENCODING_COMPLETE	(WM_USER+2)

WNDPROC button_orig_wndproc; 

static const char *g_window_id_string[] =
{
	"APP_MAIN_WINDOW",
	"APP_INPUT_FILE",
	"APP_OUTPUT_FOLDER",
	"APP_DEVICE_TEXT",
	"APP_DEVICE",
	"APP_QUALITY_TEXT",
	"APP_QUALITY",
	"APP_OUTPUT_BC1RGB_TEXT",
	"APP_OUTPUT_BC1RGB_SRGB",
	"APP_OUTPUT_BC1RGB_SAVEKTX",
	"APP_OUTPUT_BC1RGB_MACROS",
	"APP_OUTPUT_BC1RGB",
	"APP_OUTPUT_BC1RGBA_TEXT",
	"APP_OUTPUT_BC1RGBA_SRGB",
	"APP_OUTPUT_BC1RGBA_SAVEKTX",
	"APP_OUTPUT_BC1RGBA_SAVEDDS",
	"APP_OUTPUT_BC1RGBA_MACROS",
	"APP_OUTPUT_BC1RGBA",
	"APP_OUTPUT_BC2RGBA_TEXT",
	"APP_OUTPUT_BC2RGBA_SRGB",
	"APP_OUTPUT_BC2RGBA_SAVEKTX",
	"APP_OUTPUT_BC2RGBA_SAVEDDS",
	"APP_OUTPUT_BC2RGBA_MACROS",
	"APP_OUTPUT_BC2RGBA",
	"APP_OUTPUT_BC3RGBA_TEXT",
	"APP_OUTPUT_BC3RGBA_SRGB",
	"APP_OUTPUT_BC3RGBA_SAVEKTX",
	"APP_OUTPUT_BC3RGBA_SAVEDDS",
	"APP_OUTPUT_BC3RGBA_MACROS",
	"APP_OUTPUT_BC3RGBA",
	"APP_OUTPUT_BC4RED_TEXT",
	"APP_OUTPUT_BC4RED_SAVEKTX",
	"APP_OUTPUT_BC4RED_SAVEDDS",
	"APP_OUTPUT_BC4RED_MACROS",
	"APP_OUTPUT_BC4RED",
	"APP_OUTPUT_BC5RG_TEXT",
	"APP_OUTPUT_BC5RG_SAVEKTX",
	"APP_OUTPUT_BC5RG_SAVEDDS",
	"APP_OUTPUT_BC5RG_MACROS",
	"APP_OUTPUT_BC5RG",
	"APP_OUTPUT_ETC1RGB_TEXT",
 	"APP_OUTPUT_ETC1RGB_SAVEKTX",
	"APP_OUTPUT_ETC1RGB_MACROS",
	"APP_OUTPUT_ETC1RGB",
	"APP_OUTPUT_ETC2RGB_TEXT",
	"APP_OUTPUT_ETC2RGB_SRGB",
	"APP_OUTPUT_ETC2RGB_SAVEKTX",
	"APP_OUTPUT_ETC2RGB_MACROS",
	"APP_OUTPUT_ETC2RGB",
	"APP_OUTPUT_ETC2RGBA1_TEXT",
	"APP_OUTPUT_ETC2RGBA1_SRGB",
	"APP_OUTPUT_ETC2RGBA1_SAVEKTX",
	"APP_OUTPUT_ETC2RGBA1_MACROS",
	"APP_OUTPUT_ETC2RGBA1",
	"APP_OUTPUT_ETC2RGBA8_TEXT",
	"APP_OUTPUT_ETC2RGBA8_SRGB",
	"APP_OUTPUT_ETC2RGBA8_SAVEKTX",
	"APP_OUTPUT_ETC2RGBA8_MACROS",
	"APP_OUTPUT_ETC2RGBA8",
	"APP_ENCODE",
	"APP_CANCEL",
	"APP_PROGRESS_TEXT",
	"APP_PROGRESS_BAR",
	"APP_OUTPUT_BC1RGB_TOOLTIP",
	"APP_OUTPUT_BC1RGBA_TOOLTIP",
	"APP_OUTPUT_BC2RGBA_TOOLTIP",
	"APP_OUTPUT_BC3RGBA_TOOLTIP",
	"APP_OUTPUT_BC4RED_TOOLTIP",
	"APP_OUTPUT_BC5RG_TOOLTIP",
	"APP_OUTPUT_ETC1RGB_TOOLTIP",
	"APP_OUTPUT_ETC2RGB_TOOLTIP",
	"APP_OUTPUT_ETC2RGBA1_TOOLTIP",
	"APP_OUTPUT_ETC2RGBA8_TOOLTIP",
	"APP_OUTPUT_BC1RGB_MIPMAPS",
	"APP_OUTPUT_BC1RGBA_MIPMAPS",
	"APP_OUTPUT_BC2RGBA_MIPMAPS",
	"APP_OUTPUT_BC3RGBA_MIPMAPS",
	"APP_OUTPUT_BC4RED_MIPMAPS",
	"APP_OUTPUT_BC5RG_MIPMAPS",
	"APP_OUTPUT_ETC1RGB_MIPMAPS",
	"APP_OUTPUT_ETC2RGB_MIPMAPS",
	"APP_OUTPUT_ETC2RGBA1_MIPMAPS",
	"APP_OUTPUT_ETC2RGBA8_MIPMAPS",
	"APP_NUM"
};

gui_element_t g_gui_element_list[APP_NUM] = 
{
	{	// APP_MAIN_WINDOW
		WINDOW_CLASSNAME,
		WINDOW_TITLE,
		0,
		WS_OVERLAPPEDWINDOW,
		WS_EX_APPWINDOW,
		CW_USEDEFAULT, 
		0,
		512 + 80,
		816 + 128,
		0,
	},
	{	// APP_INPUT_FILE
		L"BUTTON", 
		L"Click to select input files, or drag files here.",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		WS_EX_ACCEPTFILES,
		16,
		16,
		WIDTH_FULL,
		32,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_FOLDER
		L"BUTTON",
		L"Click to select output folder, or drag folder here.",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		WS_EX_ACCEPTFILES,
		16,
		56,
		WIDTH_FULL,
		32,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_QUALITY_TEXT
		WC_STATIC,
		L"Device",
		1,
		WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | SS_LEFT,
		0,
		16,
		56 + 40*1,
		280,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_QUALITY
		WC_COMBOBOX,
		L"",
		0,
		CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
		0,
		16,
		56 + 40*1 + 24,
		WIDTH_FULL,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_DEVICE_TEXT
		WC_STATIC,
		L"Quality",
		1,
		WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | SS_LEFT,
		0,
		16,
		56 + 40*1 + 32 + 24*1,
		280,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_DEVICE
		WC_COMBOBOX,
		L"",
		0,
		CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
		0,
		16,
		56 + 40*1 + 32 + 24*2,
		WIDTH_FULL,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC1RGB_TEXT
		WC_STATIC,
		L"BC1 RGB",
		1,
		WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | SS_LEFT,
		0,
		16,
		56 + 40*1 + 32 + 24*2 + 32,
		280,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC1RGB_SRGB
		L"BUTTON", 
		L"sRGB",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		0,
		POS_SRGB_X,
		56 + 40*1 + 32 + 24*2 + 32 - 2,
		WIDTH_SRGB,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC1RGB_SAVEKTX
		L"BUTTON", 
		L"Save KTX",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		0,
		POS_SAVEKTX_X,
		56 + 40*1 + 32 + 24*2 + 32 - 2,
		88,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC1RGB_MACROS
		L"BUTTON", 
		L"Macros",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		0,
		MACROS_X,
		56 + 40*1 + 32 + 24*2 + 32 + 24,
		64,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC1RGB
		WC_EDIT,
		L"",
		0,
		WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
		0,
		16,
		56 + 40*1 + 32 + 24*2 + 32 + 24,
		OPTION_WIDTH,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC1RGBA_TEXT
		WC_STATIC,
		L"BC1 RGBA",
		1,
		WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | SS_LEFT,
		0,
		16,
		56 + 40*1 + 32 + 24*2 + (32)*2 + 24,
		280,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC1RGBA_SRGB
		L"BUTTON", 
		L"sRGB",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		0,
		POS_SRGB_X,
		56 + 40*1 + 32 + 24*2 + (32)*2 + 24 - 2,
		WIDTH_SRGB,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC1RGBA_SAVEKTX
		L"BUTTON", 
		L"Save KTX",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		0,
		POS_SAVEKTX_X,
		56 + 40*1 + 32 + 24*2 + (32)*2 + 24 - 2,
		88,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC1RGBA_SAVEDDS
		L"BUTTON", 
		L"Save DDS",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		0,
		POS_SAVEDDS_X,
		56 + 40*1 + 32 + 24*2 + (32)*2 + 24 - 2,
		88,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC1RGBA_MACROS
		L"BUTTON", 
		L"Macros",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		0,
		MACROS_X,
		56 + 40*1 + 32 + 24*2 + (32 + 24)*2,
		64,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC1RGBA
		WC_EDIT,
		L"",
		0,
		WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
		0,
		16,
		56 + 40*1 + 32 + 24*2 + (32 + 24)*2,
		OPTION_WIDTH,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC2RGBA_TEXT
		WC_STATIC,
		L"BC2 RGBA",
		1,
		WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | SS_LEFT,
		0,
		16,
		56 + 40*1 + 32 + (32 + 24)*3 + 24,
		280,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC2RGB_SRGB
		L"BUTTON", 
		L"sRGB",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		0,
		POS_SRGB_X,
		56 + 40*1 + 32 + (32 + 24)*3 + 24 - 2,
		WIDTH_SRGB,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC2RGBA_SAVEKTX
		L"BUTTON", 
		L"Save KTX",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		0,
		POS_SAVEKTX_X,
		56 + 40*1 + 32 + (32 + 24)*3 + 24 - 2,
		88,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC2RGBA_SAVEDDS
		L"BUTTON", 
		L"Save DDS",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		0,
		POS_SAVEDDS_X,
		56 + 40*1 + 32 + (32 + 24)*3 + 24 - 2,
		88,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC2RGBA_MACROS
		L"BUTTON", 
		L"Macros",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		0,
		MACROS_X,
		56 + 40*1 + 32 + 24*2 + (32 + 24)*3,
		64,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC2RGBA
		WC_EDIT,
		L"",
		0,
		WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
		0,
		16,
		56 + 40*1 + 32 + 24*2 + (32 + 24)*3,
		OPTION_WIDTH,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC3RGBA_TEXT
		WC_STATIC,
		L"BC3 RGBA",
		1,
		WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | SS_LEFT,
		0,
		16,
		56 + 40*1 + 32 + (32 + 24)*4 + 24,
		280,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC3RGBA_SRGB
		L"BUTTON", 
		L"sRGB",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		0,
		POS_SRGB_X,
		56 + 40*1 + 32 + (32 + 24)*4 + 24 - 2,
		WIDTH_SRGB,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC3RGBA_SAVEKTX
		L"BUTTON", 
		L"Save KTX",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		0,
		POS_SAVEKTX_X,
		56 + 40*1 + 32 + (32 + 24)*4 + 24 - 2,
		88,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC3RGBA_SAVEDDS
		L"BUTTON", 
		L"Save DDS",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		0,
		POS_SAVEDDS_X,
		56 + 40*1 + 32 + (32 + 24)*4 + 24 - 2,
		88,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC3RGBA_MACROS
		L"BUTTON", 
		L"Macros",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		0,
		MACROS_X,
		56 + 40*1 + 32 + 24*2 + (32 + 24)*4,
		64,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC3RGBA
		WC_EDIT,
		L"",
		0,
		WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
		0,
		16,
		56 + 40*1 + 32 + 24*2 + (32 + 24)*4,
		OPTION_WIDTH,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC4RED_TEXT
		WC_STATIC,
		L"BC4 RED",
		1,
		WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | SS_LEFT,
		0,
		16,
		56 + 40*1 + 32 + (32 + 24)*5 + 24,
		280,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC4RED_SAVEKTX
		L"BUTTON", 
		L"Save KTX",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		0,
		POS_SAVEKTX_X,
		56 + 40*1 + 32 + (32 + 24)*5 + 24 - 2,
		88,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC4RED_SAVEDDS
		L"BUTTON", 
		L"Save DDS",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		0,
		POS_SAVEDDS_X,
		56 + 40*1 + 32 + (32 + 24)*5 + 24 - 2,
		88,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC4RED_MACROS
		L"BUTTON", 
		L"Macros",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		0,
		MACROS_X,
		56 + 40*1 + 32 + 24*2 + (32 + 24)*5,
		64,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC4RED
		WC_EDIT,
		L"",
		0,
		WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
		0,
		16,
		56 + 40*1 + 32 + 24*2 + (32 + 24)*5,
		OPTION_WIDTH,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC5RG_TEXT
		WC_STATIC,
		L"BC5 RG",
		1,
		WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | SS_LEFT,
		0,
		16,
		56 + 40*1 + 32 + (32 + 24)*6 + 24,
		280,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC5RG_SAVEKTX
		L"BUTTON", 
		L"Save KTX",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		0,
		POS_SAVEKTX_X,
		56 + 40*1 + 32 + (32 + 24)*6 + 24 - 2,
		88,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC5RG_SAVEDDS
		L"BUTTON", 
		L"Save DDS",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		0,
		POS_SAVEDDS_X,
		56 + 40*1 + 32 + (32 + 24)*6 + 24 - 2,
		88,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC5RG_MACROS
		L"BUTTON", 
		L"Macros",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		0,
		MACROS_X,
		56 + 40*1 + 32 + 24*2 + (32 + 24)*6,
		64,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC5RG
		WC_EDIT,
		L"",
		0,
		WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
		0,
		16,
		56 + 40*1 + 32 + 24*2 + (32 + 24)*6,
		OPTION_WIDTH,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_ETC1RGB_TEXT
		WC_STATIC,
		L"ETC1 RGB",
		1,
		WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | SS_LEFT,
		0,
		16,
		56 + 40*1 + 32 + (32 + 24)*7 + 24,
		280,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_ETC1RGB_SAVEKTX
		L"BUTTON", 
		L"Save KTX",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		0,
		POS_SAVEKTX_X,
		56 + 40*1 + 32 + (32 + 24)*7 + 24 - 2,
		88,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_ETC1RGB_MACROS
		L"BUTTON", 
		L"Macros",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		0,
		MACROS_X,
		56 + 40*1 + 32 + 24*2 + (32 + 24)*7,
		64,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_ETC1RGB
		WC_EDIT,
		L"",
		0,
		WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
		0,
		16,
		56 + 40*1 + 32 + 24*2 + (32 + 24)*7,
		OPTION_WIDTH,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_ETC2RGB_TEXT
		WC_STATIC,
		L"ETC2 RGB",
		1,
		WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | SS_LEFT,
		0,
		16,
		56 + 40*1 + 32 + (32 + 24)*8 + 24,
		280,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_ETC2RGB_SRGB
		L"BUTTON", 
		L"sRGB",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		0,
		POS_SRGB_X,
		56 + 40*1 + 32 + (32 + 24)*8 + 24 - 2,
		WIDTH_SRGB,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_ETC2RGB_SAVEKTX
		L"BUTTON", 
		L"Save KTX",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		0,
		POS_SAVEKTX_X,
		56 + 40*1 + 32 + (32 + 24)*8 + 24 - 2,
		88,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_ETC2RGB_MACROS
		L"BUTTON", 
		L"Macros",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		0,
		MACROS_X,
		56 + 40*1 + 32 + 24*2 + (32 + 24)*8,
		64,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_ETC2RGB
		WC_EDIT,
		L"",
		0,
		WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
		0,
		16,
		56 + 40*1 + 32 + 24*2 + (32 + 24)*8,
		OPTION_WIDTH,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_ETC2RGBA1_TEXT
		WC_STATIC,
		L"ETC2 RGBA1",
		1,
		WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | SS_LEFT,
		0,
		16,
		56 + 40*1 + 32 + (32 + 24)*9 + 24,
		280,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_ETC2RGBA1_SRGB
		L"BUTTON", 
		L"sRGB",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		0,
		POS_SRGB_X,
		56 + 40*1 + 32 + (32 + 24)*9 + 24 - 2,
		WIDTH_SRGB,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_ETC2RGBA1_SAVEKTX
		L"BUTTON", 
		L"Save KTX",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		0,
		POS_SAVEKTX_X,
		56 + 40*1 + 32 + (32 + 24)*9 + 24 - 2,
		88,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_ETC2RGBA1_MACROS
		L"BUTTON", 
		L"Macros",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		0,
		MACROS_X,
		56 + 40*1 + 32 + 24*2 + (32 + 24)*9,
		64,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_ETC2RGBA1
		WC_EDIT,
		L"",
		0,
		WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
		0,
		16,
		56 + 40*1 + 32 + 24*2 + (32 + 24)*9,
		OPTION_WIDTH,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_ETC2RGBA8_TEXT
		WC_STATIC,
		L"ETC2 RGBA8",
		1,
		WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | SS_LEFT,
		0,
		16,
		56 + 40*1 + 32 + (32 + 24)*10 + 24,
		280,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_ETC2RGBA8_SRGB
		L"BUTTON", 
		L"sRGB",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		0,
		POS_SRGB_X,
		56 + 40*1 + 32 + (32 + 24)*10 + 24 - 2,
		WIDTH_SRGB,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_ETC2RGBA8_SAVEKTX
		L"BUTTON", 
		L"Save KTX",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		0,
		POS_SAVEKTX_X,
		56 + 40*1 + 32 + (32 + 24)*10 + 24 - 2,
		88,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_ETC2RGBA8_MACROS
		L"BUTTON", 
		L"Macros",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		0,
		MACROS_X,
		56 + 40*1 + 32 + 24*2 + (32 + 24)*10,
		64,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_ETC2RGBA8
		WC_EDIT,
		L"",
		0,
		WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
		0,
		16,
		56 + 40*1 + 32 + 24*2 + (32 + 24)*10,
		OPTION_WIDTH,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_ENCODE
		L"BUTTON", 
		L"Encode",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		0,
		16,
		56 + 40*1 + 32 + (32 + 24)*11 + 24 + 16,
		224+40,
		32,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_CANCEL
		L"BUTTON", 
		L"Cancel",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		0,
		16 + 224 + 16+40,
		56 + 40*1 + 32 + (32 + 24)*11 + 24 + 16,
		224+40,
		32,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_PROGRESS_TEXT
		WC_STATIC,
		L"Progress",
		1,
		WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | SS_LEFT | SS_LEFTNOWORDWRAP,
		0,
		16,
		56 + 40*1 + 32 + (32 + 24)*11 + 32 + 32 + 32,
		WIDTH_FULL,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_PROGRESS_BAR
		PROGRESS_CLASS,
		L"",
		0,
		WS_CHILD | WS_VISIBLE,
		0,
		16,
		56 + 40*1 + 32 + (32 + 24)*11 + 32 + 32 + 24 + 32,
		WIDTH_FULL,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC1RGB_TOOLTIP
		TOOLTIPS_CLASS,
		NULL,
		0,
		WS_POPUP | TTS_ALWAYSTIP | TTS_BALLOON,
		0,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		&g_gui_element_list[APP_OUTPUT_BC1RGB],
	},
	{	// APP_OUTPUT_BC1RGBA_TOOLTIP
		TOOLTIPS_CLASS,
		NULL,
		0,
		WS_POPUP | TTS_ALWAYSTIP | TTS_BALLOON,
		0,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		&g_gui_element_list[APP_OUTPUT_BC1RGBA],
	},
	{	// APP_OUTPUT_BC2RGBA_TOOLTIP
		TOOLTIPS_CLASS,
		NULL,
		0,
		WS_POPUP | TTS_ALWAYSTIP | TTS_BALLOON,
		0,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		&g_gui_element_list[APP_OUTPUT_BC2RGBA],
	},
	{	// APP_OUTPUT_BC3RGBA_TOOLTIP
		TOOLTIPS_CLASS,
		NULL,
		0,
		WS_POPUP | TTS_ALWAYSTIP | TTS_BALLOON,
		0,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		&g_gui_element_list[APP_OUTPUT_BC3RGBA],
	},
	{	// APP_OUTPUT_BC4RED_TOOLTIP
		TOOLTIPS_CLASS,
		NULL,
		0,
		WS_POPUP | TTS_ALWAYSTIP | TTS_BALLOON,
		0,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		&g_gui_element_list[APP_OUTPUT_BC4RED],
	},
	{	// APP_OUTPUT_BC5RG_TOOLTIP
		TOOLTIPS_CLASS,
		NULL,
		0,
		WS_POPUP | TTS_ALWAYSTIP | TTS_BALLOON,
		0,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		&g_gui_element_list[APP_OUTPUT_BC5RG],
	},
	{	// APP_OUTPUT_ETC1RGB_TOOLTIP
		TOOLTIPS_CLASS,
		NULL,
		0,
		WS_POPUP | TTS_ALWAYSTIP | TTS_BALLOON,
		0,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		&g_gui_element_list[APP_OUTPUT_ETC1RGB],
	},
	{	// APP_OUTPUT_ETC2RGB_TOOLTIP
		TOOLTIPS_CLASS,
		NULL,
		0,
		WS_POPUP | TTS_ALWAYSTIP | TTS_BALLOON,
		0,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		&g_gui_element_list[APP_OUTPUT_ETC2RGB],
	},
	{	// APP_OUTPUT_ETC2RGBA1_TOOLTIP
		TOOLTIPS_CLASS,
		NULL,
		0,
		WS_POPUP | TTS_ALWAYSTIP | TTS_BALLOON,
		0,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		&g_gui_element_list[APP_OUTPUT_ETC2RGBA1],
	},
	{	// APP_OUTPUT_ETC2RGBA8_TOOLTIP
		TOOLTIPS_CLASS,
		NULL,
		0,
		WS_POPUP | TTS_ALWAYSTIP | TTS_BALLOON,
		0,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		&g_gui_element_list[APP_OUTPUT_ETC2RGBA8],
	},
	{	// APP_OUTPUT_BC1RGB_MIPMAPS
		L"BUTTON", 
		L"Mipmaps",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		0,
		POS_MIPMAPS_X,
		56 + 40*1 + 32 + (32 + 24)*1 + 24 - 2,
		WIDTH_MIPMAPS,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC1RGBA_MIPMAPS
		L"BUTTON", 
		L"Mipmaps",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		0,
		POS_MIPMAPS_X,
		56 + 40*1 + 32 + (32 + 24)*2 + 24 - 2,
		WIDTH_MIPMAPS,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC2RGBA_MIPMAPS
		L"BUTTON", 
		L"Mipmaps",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		0,
		POS_MIPMAPS_X,
		56 + 40*1 + 32 + (32 + 24)*3 + 24 - 2,
		WIDTH_MIPMAPS,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC3RGBA_MIPMAPS
		L"BUTTON", 
		L"Mipmaps",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		0,
		POS_MIPMAPS_X,
		56 + 40*1 + 32 + (32 + 24)*4 + 24 - 2,
		WIDTH_MIPMAPS,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC4RED_MIPMAPS
		L"BUTTON", 
		L"Mipmaps",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		0,
		POS_MIPMAPS_X,
		56 + 40*1 + 32 + (32 + 24)*5 + 24 - 2,
		WIDTH_MIPMAPS,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_BC5RG_MIPMAPS
		L"BUTTON", 
		L"Mipmaps",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		0,
		POS_MIPMAPS_X,
		56 + 40*1 + 32 + (32 + 24)*6 + 24 - 2,
		WIDTH_MIPMAPS,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_ETC1RGB_MIPMAPS
		L"BUTTON", 
		L"Mipmaps",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		0,
		POS_MIPMAPS_X,
		56 + 40*1 + 32 + (32 + 24)*7 + 24 - 2,
		WIDTH_MIPMAPS,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_ETC2RGB_MIPMAPS
		L"BUTTON", 
		L"Mipmaps",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		0,
		POS_MIPMAPS_X,
		56 + 40*1 + 32 + (32 + 24)*8 + 24 - 2,
		WIDTH_MIPMAPS,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_ETC2RGBA1_MIPMAPS
		L"BUTTON", 
		L"Mipmaps",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		0,
		POS_MIPMAPS_X,
		56 + 40*1 + 32 + (32 + 24)*9 + 24 - 2,
		WIDTH_MIPMAPS,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
	{	// APP_OUTPUT_ETC2RGBA8_MIPMAPS
		L"BUTTON", 
		L"Mipmaps",
		1,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		0,
		POS_MIPMAPS_X,
		56 + 40*1 + 32 + (32 + 24)*10 + 24 - 2,
		WIDTH_MIPMAPS,
		24,
		&g_gui_element_list[APP_MAIN_WINDOW],
	},
};

window_interface_t g_win_system = {0};

int ShouldEncodeBeEnabled()
{
	int i;
	int list[] = 
	{
		APP_OUTPUT_BC1RGB_SAVEKTX,
		APP_OUTPUT_BC1RGBA_SAVEKTX,
		APP_OUTPUT_BC1RGBA_SAVEDDS,
		APP_OUTPUT_BC2RGBA_SAVEKTX,
		APP_OUTPUT_BC2RGBA_SAVEDDS,
		APP_OUTPUT_BC3RGBA_SAVEKTX,
		APP_OUTPUT_BC3RGBA_SAVEDDS,
		APP_OUTPUT_BC4RED_SAVEKTX,
		APP_OUTPUT_BC4RED_SAVEDDS,
		APP_OUTPUT_BC5RG_SAVEKTX,
		APP_OUTPUT_BC5RG_SAVEDDS,
		APP_OUTPUT_ETC1RGB_SAVEKTX,
		APP_OUTPUT_ETC2RGB_SAVEKTX,
		APP_OUTPUT_ETC2RGBA1_SAVEKTX,
		APP_OUTPUT_ETC2RGBA8_SAVEKTX
	};

	if (g_win_system.num_input_files == 0 || g_win_system.output_folder == 0 || g_win_system.encoding)
		return 0;

	for (i = 0; i < sizeof(list) / sizeof(int); i++)
		if (SendMessage(g_win_system.gui_element[list[i]].hwnd, BM_GETCHECK, 0, 0))
			return 1;

	return 0;
}
int IDFromHWND(HWND hwnd)
{
	int i;

	for (i = 0; i < APP_NUM; i++)
		if (hwnd == g_win_system.gui_element[i].hwnd)
			return i;

	return -1;
}
const char *IDNameString(int id)
{
	if (id >= 0 && id < APP_NUM)
		return g_window_id_string[id];
	else
		return "<UNKNOWN>";
}
int IsMacroButton(HWND hwnd)
{
	switch(IDFromHWND(hwnd))
	{
		case APP_OUTPUT_BC1RGB_MACROS:
		case APP_OUTPUT_BC1RGBA_MACROS:
		case APP_OUTPUT_BC2RGBA_MACROS:
		case APP_OUTPUT_BC3RGBA_MACROS:
		case APP_OUTPUT_BC4RED_MACROS:
		case APP_OUTPUT_BC5RG_MACROS:
		case APP_OUTPUT_ETC1RGB_MACROS:
		case APP_OUTPUT_ETC2RGB_MACROS:
		case APP_OUTPUT_ETC2RGBA1_MACROS:
		case APP_OUTPUT_ETC2RGBA8_MACROS:
			return 1;
		default:
			return 0;
	}
}
int IsTextField(HWND hwnd)
{
	switch(IDFromHWND(hwnd))
	{
		case APP_OUTPUT_BC1RGB:
		case APP_OUTPUT_BC1RGBA:
		case APP_OUTPUT_BC2RGBA:
		case APP_OUTPUT_BC3RGBA:
		case APP_OUTPUT_BC4RED:
		case APP_OUTPUT_BC5RG:
		case APP_OUTPUT_ETC1RGB:
		case APP_OUTPUT_ETC2RGB:
		case APP_OUTPUT_ETC2RGBA1:
		case APP_OUTPUT_ETC2RGBA8:
			return 1;
		default:
			return 0;
	}
}
int IsSRGBButton(HWND hwnd)
{
	switch(IDFromHWND(hwnd))
	{
		case APP_OUTPUT_BC1RGB_SRGB:
		case APP_OUTPUT_BC1RGBA_SRGB:
		case APP_OUTPUT_BC2RGBA_SRGB:
		case APP_OUTPUT_BC3RGBA_SRGB:
		case APP_OUTPUT_ETC2RGB_SRGB:
		case APP_OUTPUT_ETC2RGBA1_SRGB:
		case APP_OUTPUT_ETC2RGBA8_SRGB:
			return 1;
		default:
			return 0;
	}
}
int SRGBIDFromGroupID(int group_id)
{
	switch(group_id)
	{
		case APP_GROUP_BC1RGB:
			return APP_OUTPUT_BC1RGB_SRGB;
		case APP_GROUP_BC1RGBA:
			return APP_OUTPUT_BC1RGBA_SRGB;
		case APP_GROUP_BC2RGBA:
			return APP_OUTPUT_BC2RGBA_SRGB;
		case APP_GROUP_BC3RGBA:
			return APP_OUTPUT_BC3RGBA_SRGB;
		case APP_GROUP_ETC2RGB:
			return APP_OUTPUT_ETC2RGB_SRGB;
		case APP_GROUP_ETC2RGBA1:
			return APP_OUTPUT_ETC2RGBA1_SRGB;
		case APP_GROUP_ETC2RGBA8:
			return APP_OUTPUT_ETC2RGBA8_SRGB;
		default:
			return 0;
	}
}
int MipmapsIDFromGroupID(int group_id)
{
	switch(group_id)
	{
		case APP_GROUP_BC1RGB:
			return APP_OUTPUT_BC1RGB_MIPMAPS;
		case APP_GROUP_BC1RGBA:
			return APP_OUTPUT_BC1RGBA_MIPMAPS;
		case APP_GROUP_BC2RGBA:
			return APP_OUTPUT_BC2RGBA_MIPMAPS;
		case APP_GROUP_BC3RGBA:
			return APP_OUTPUT_BC3RGBA_MIPMAPS;
		case APP_GROUP_ETC2RGB:
			return APP_OUTPUT_ETC2RGB_MIPMAPS;
		case APP_GROUP_ETC2RGBA1:
			return APP_OUTPUT_ETC2RGBA1_MIPMAPS;
		case APP_GROUP_ETC2RGBA8:
			return APP_OUTPUT_ETC2RGBA8_MIPMAPS;
		default:
			return 0;
	}
}
int MacroButtonIDOffset(HWND hwnd)
{
	switch(IDFromHWND(hwnd))
	{
		case APP_OUTPUT_BC1RGB_MACROS:
			return 5*0;
		case APP_OUTPUT_BC1RGBA_MACROS:
			return 5*1;
		case APP_OUTPUT_BC2RGBA_MACROS:
			return 5*2;
		case APP_OUTPUT_BC3RGBA_MACROS:
			return 5*3;
		case APP_OUTPUT_BC4RED_MACROS:
			return 5*4;
		case APP_OUTPUT_BC5RG_MACROS:
			return 5*5;
		case APP_OUTPUT_ETC1RGB_MACROS:
			return 5*6;
		case APP_OUTPUT_ETC2RGB_MACROS:
			return 5*7;
		case APP_OUTPUT_ETC2RGBA1_MACROS:
			return 5*8;
		case APP_OUTPUT_ETC2RGBA8_MACROS:
			return 5*9;
		default:
			return 0;
	}
}
int GroupIDFromID(int id)
{
	switch(id)
	{
		case APP_OUTPUT_BC1RGB_TEXT:
		case APP_OUTPUT_BC1RGB_SRGB:
		case APP_OUTPUT_BC1RGB_SAVEKTX:
		case APP_OUTPUT_BC1RGB_MACROS:
		case APP_OUTPUT_BC1RGB:
			return APP_GROUP_BC1RGB;
		case APP_OUTPUT_BC1RGBA_TEXT:
		case APP_OUTPUT_BC1RGBA_SRGB:
		case APP_OUTPUT_BC1RGBA_SAVEKTX:
		case APP_OUTPUT_BC1RGBA_SAVEDDS:
		case APP_OUTPUT_BC1RGBA_MACROS:
		case APP_OUTPUT_BC1RGBA:
			return APP_GROUP_BC1RGBA;
		case APP_OUTPUT_BC2RGBA_TEXT:
		case APP_OUTPUT_BC2RGBA_SRGB:
		case APP_OUTPUT_BC2RGBA_SAVEKTX:
		case APP_OUTPUT_BC2RGBA_SAVEDDS:
		case APP_OUTPUT_BC2RGBA_MACROS:
		case APP_OUTPUT_BC2RGBA:
			return APP_GROUP_BC2RGBA;
		case APP_OUTPUT_BC3RGBA_TEXT:
		case APP_OUTPUT_BC3RGBA_SRGB:
		case APP_OUTPUT_BC3RGBA_SAVEKTX:
		case APP_OUTPUT_BC3RGBA_SAVEDDS:
		case APP_OUTPUT_BC3RGBA_MACROS:
		case APP_OUTPUT_BC3RGBA:
			return APP_GROUP_BC3RGBA;
		case APP_OUTPUT_BC4RED_TEXT:
		case APP_OUTPUT_BC4RED_SAVEKTX:
		case APP_OUTPUT_BC4RED_SAVEDDS:
		case APP_OUTPUT_BC4RED_MACROS:
		case APP_OUTPUT_BC4RED:
			return APP_GROUP_BC4RED;
		case APP_OUTPUT_BC5RG_TEXT:
		case APP_OUTPUT_BC5RG_SAVEKTX:
		case APP_OUTPUT_BC5RG_SAVEDDS:
		case APP_OUTPUT_BC5RG_MACROS:
		case APP_OUTPUT_BC5RG:
			return APP_GROUP_BC5RG;
		case APP_OUTPUT_ETC1RGB_TEXT:
		case APP_OUTPUT_ETC1RGB_SAVEKTX:
		case APP_OUTPUT_ETC1RGB_MACROS:
		case APP_OUTPUT_ETC1RGB:
			return APP_GROUP_ETC1RGB;
		case APP_OUTPUT_ETC2RGB_TEXT:
		case APP_OUTPUT_ETC2RGB_SRGB:
		case APP_OUTPUT_ETC2RGB_SAVEKTX:
		case APP_OUTPUT_ETC2RGB_MACROS:
		case APP_OUTPUT_ETC2RGB:
			return APP_GROUP_ETC2RGB;
		case APP_OUTPUT_ETC2RGBA1_TEXT:
		case APP_OUTPUT_ETC2RGBA1_SRGB:
		case APP_OUTPUT_ETC2RGBA1_SAVEKTX:
		case APP_OUTPUT_ETC2RGBA1_MACROS:
		case APP_OUTPUT_ETC2RGBA1:
			return APP_GROUP_ETC2RGBA1;
		case APP_OUTPUT_ETC2RGBA8_TEXT:
		case APP_OUTPUT_ETC2RGBA8_SRGB:
		case APP_OUTPUT_ETC2RGBA8_SAVEKTX:
		case APP_OUTPUT_ETC2RGBA8_MACROS:
		case APP_OUTPUT_ETC2RGBA8:
			return APP_GROUP_ETC2RGBA8;
		default:
			return -1;
	}
}

int GroupIDFromHWND(HWND hwnd)
{
	return GroupIDFromID(IDFromHWND(hwnd));
}
gui_element_t *GetMacroTextElement(int menu_id)
{
	switch(menu_id / 5)
	{
		case 0:
			return &g_win_system.gui_element[APP_OUTPUT_BC1RGB_TEXT];
		case 1:
			return &g_win_system.gui_element[APP_OUTPUT_BC1RGBA_TEXT];
		case 2:
			return &g_win_system.gui_element[APP_OUTPUT_BC2RGBA_TEXT];
		case 3:
			return &g_win_system.gui_element[APP_OUTPUT_BC3RGBA_TEXT];
		case 4:
			return &g_win_system.gui_element[APP_OUTPUT_BC4RED_TEXT];
		case 5:
			return &g_win_system.gui_element[APP_OUTPUT_BC5RG_TEXT];
		case 6:
			return &g_win_system.gui_element[APP_OUTPUT_ETC1RGB_TEXT];
		case 7:
			return &g_win_system.gui_element[APP_OUTPUT_ETC2RGB_TEXT];
		case 8:
			return &g_win_system.gui_element[APP_OUTPUT_ETC2RGBA1_TEXT];
		case 9:
			return &g_win_system.gui_element[APP_OUTPUT_ETC2RGBA8_TEXT];
		default:
			return 0;
	}
}
int GroupIDFromMenuID(int menu_id)
{
	switch(menu_id / 5)
	{
		case 0:
			return APP_GROUP_BC1RGB;
		case 1:
			return APP_GROUP_BC1RGBA;
		case 2:
			return APP_GROUP_BC2RGBA;
		case 3:
			return APP_GROUP_BC3RGBA;
		case 4:
			return APP_GROUP_BC4RED;
		case 5:
			return APP_GROUP_BC5RG;
		case 6:
			return APP_GROUP_ETC1RGB;
		case 7:
			return APP_GROUP_ETC2RGB;
		case 8:
			return APP_GROUP_ETC2RGBA1;
		case 9:
			return APP_GROUP_ETC2RGBA8;
		default:
			return -1;
	}
}
int PathIDFromGroupID(int group_id)
{
	switch(group_id)
	{
		case APP_GROUP_BC1RGB:
			return APP_OUTPUT_BC1RGB;
		case APP_GROUP_BC1RGBA:
			return APP_OUTPUT_BC1RGBA;
		case APP_GROUP_BC2RGBA:
			return APP_OUTPUT_BC2RGBA;
		case APP_GROUP_BC3RGBA:
			return APP_OUTPUT_BC3RGBA;
		case APP_GROUP_BC4RED:
			return APP_OUTPUT_BC4RED;
		case APP_GROUP_BC5RG:
			return APP_OUTPUT_BC5RG;
		case APP_GROUP_ETC1RGB:
			return APP_OUTPUT_ETC1RGB;
		case APP_GROUP_ETC2RGB:
			return APP_OUTPUT_ETC2RGB;
		case APP_GROUP_ETC2RGBA1:
			return APP_OUTPUT_ETC2RGBA1;
		case APP_GROUP_ETC2RGBA8:
			return APP_OUTPUT_ETC2RGBA8;
		default:
			return -1;
	}
}
int SaveKTXIDFromGroupID(int group_id)
{
	switch(group_id)
	{
		case APP_GROUP_BC1RGB:
			return APP_OUTPUT_BC1RGB_SAVEKTX;
		case APP_GROUP_BC1RGBA:
			return APP_OUTPUT_BC1RGBA_SAVEKTX;
		case APP_GROUP_BC2RGBA:
			return APP_OUTPUT_BC2RGBA_SAVEKTX;
		case APP_GROUP_BC3RGBA:
			return APP_OUTPUT_BC3RGBA_SAVEKTX;
		case APP_GROUP_BC4RED:
			return APP_OUTPUT_BC4RED_SAVEKTX;
		case APP_GROUP_BC5RG:
			return APP_OUTPUT_BC5RG_SAVEKTX;
		case APP_GROUP_ETC1RGB:
			return APP_OUTPUT_ETC1RGB_SAVEKTX;
		case APP_GROUP_ETC2RGB:
			return APP_OUTPUT_ETC2RGB_SAVEKTX;
		case APP_GROUP_ETC2RGBA1:
			return APP_OUTPUT_ETC2RGBA1_SAVEKTX;
		case APP_GROUP_ETC2RGBA8:
			return APP_OUTPUT_ETC2RGBA8_SAVEKTX;
		default:
			return -1;
	}
}
int SaveDDSIDFromGroupID(int group_id)
{
	switch(group_id)
	{
		case APP_GROUP_BC1RGBA:
			return APP_OUTPUT_BC1RGBA_SAVEDDS;
		case APP_GROUP_BC2RGBA:
			return APP_OUTPUT_BC2RGBA_SAVEDDS;
		case APP_GROUP_BC3RGBA:
			return APP_OUTPUT_BC3RGBA_SAVEDDS;
		case APP_GROUP_BC4RED:
			return APP_OUTPUT_BC4RED_SAVEDDS;
		case APP_GROUP_BC5RG:
			return APP_OUTPUT_BC5RG_SAVEDDS;
		default:
			return -1;
	}
}
int TooltipIDFromGroupID(int group_id)
{
	switch(group_id)
	{
		case APP_GROUP_BC1RGB:
			return APP_OUTPUT_BC1RGB_TOOLTIP;
		case APP_GROUP_BC1RGBA:
			return APP_OUTPUT_BC1RGBA_TOOLTIP;
		case APP_GROUP_BC2RGBA:
			return APP_OUTPUT_BC2RGBA_TOOLTIP;
		case APP_GROUP_BC3RGBA:
			return APP_OUTPUT_BC3RGBA_TOOLTIP;
		case APP_GROUP_BC4RED:
			return APP_OUTPUT_BC4RED_TOOLTIP;
		case APP_GROUP_BC5RG:
			return APP_OUTPUT_BC5RG_TOOLTIP;
		case APP_GROUP_ETC1RGB:
			return APP_OUTPUT_ETC1RGB_TOOLTIP;
		case APP_GROUP_ETC2RGB:
			return APP_OUTPUT_ETC2RGB_TOOLTIP;
		case APP_GROUP_ETC2RGBA1:
			return APP_OUTPUT_ETC2RGBA1_TOOLTIP;
		case APP_GROUP_ETC2RGBA8:
			return APP_OUTPUT_ETC2RGBA8_TOOLTIP;
		default:
			return -1;
	}
}

LRESULT System_WndProcButton(HWND hwnd, 
	UINT uMsg, 
	WPARAM wParam, 
	LPARAM lParam 
)
{
	switch (uMsg)
	{
		case WM_DROPFILES:
		{
			HDROP hdrop = (HDROP)wParam;
			int num;
			wchar_t *string;
			int i;
			int len;

			num = DragQueryFile(hdrop, 0xFFFFFFFF, 0, 0);

			if (IDFromHWND(hwnd) == APP_OUTPUT_FOLDER)
			{
				if (num != 1)
					return 0;
				len = DragQueryFile(hdrop, 0, 0, 0);
				string = Mem_Malloc((len + 2) * sizeof(wchar_t));
				DragQueryFile(hdrop, 0, string, len + 1);
				if (GetFileAttributes(string) & FILE_ATTRIBUTE_DIRECTORY)
				{
					string[len] = L'\\';
					string[len + 1] = 0;

					Mem_Free(g_win_system.output_folder);
					g_win_system.output_folder = Mem_Malloc(wcslen(string) + 1);
					sprintf_s(g_win_system.output_folder, wcslen(string) + 1, "%ls", string);
					SendMessage(g_win_system.gui_element[APP_OUTPUT_FOLDER].hwnd, WM_SETTEXT, 0, (LPARAM)string);
				}
				Mem_Free(string);
				return 0;
			}
			else if (IDFromHWND(hwnd) == APP_INPUT_FILE)
			{
				wchar_t *ptr;

				for (i = 0; i < g_win_system.num_input_files; i++)
					Mem_Free(g_win_system.input_file[i]);
				Mem_Free(g_win_system.input_file);
				Mem_Free(g_win_system.input_path);

				if (num > 1)
					SendMessage(g_win_system.gui_element[APP_INPUT_FILE].hwnd, WM_SETTEXT, 0, (LPARAM)L"Multiple input files selected");

				g_win_system.input_file = Mem_Malloc(sizeof(char*) * num);

				len = DragQueryFile(hdrop, 0, 0, 0);
				string = Mem_Malloc((len + 2) * sizeof(wchar_t));
				DragQueryFile(hdrop, 0, string, len + 1);

				ptr = wcsrchr(string, '\\');
				if (ptr)
					ptr[1] = 0;

				g_win_system.input_path = Mem_Malloc(wcslen(string) + 1);
				sprintf_s(g_win_system.input_path, wcslen(string) + 1, "%ls", string);

				Mem_Free(string);

				g_win_system.num_input_files = num;

				for (i = 0; i < num; i++)
				{
					char *temp;
					len = DragQueryFile(hdrop, i, 0, 0);
					string = Mem_Malloc((len + 1) * sizeof(wchar_t));
					DragQueryFile(hdrop, i, string, len + 1);

					ptr = wcsrchr(string, '\\');
					if (!ptr)
						ptr = string;
					else
						ptr++;

					temp = Mem_Malloc(wcslen(ptr) + 1);
					sprintf_s(temp, wcslen(ptr) + 1, "%ls", ptr);

					if (i == 0 && num <= 1)
						SendMessage(g_win_system.gui_element[APP_INPUT_FILE].hwnd, WM_SETTEXT, 0, (LPARAM)ptr);

					g_win_system.input_file[i] = temp;

					Mem_Free(string);
				}
			}

			DragFinish(hdrop);
			return 0;
		}
	}
	return CallWindowProc(button_orig_wndproc, hwnd, uMsg, wParam, lParam);
}

char *ExpandWText(wchar_t *input, int file_index, int output_index)
{
	wchar_t *string[5] = {L"$(InDir)", L"$(OutDir)", L"$(InName)", L"$(InExt)", L"$(OutExt)"};
	char *output = 0;
	int counts[5] = {0};
	wchar_t *ptr;
	char	*out_ptr;
	int i;
	int newlen = 0;
	char *fname;
	char *fext;

	if (!g_win_system.num_input_files || !g_win_system.output_folder)
	{
		output = Mem_Malloc(512);
		sprintf_s(output, 512, "Please add input file(s) and output folder");
		return output;
	}

	fname = Mem_Malloc(strlen(g_win_system.input_file[file_index]) + 1);
	fext = Mem_Malloc(strlen(g_win_system.input_file[file_index]) + 1);
	memcpy(fname, g_win_system.input_file[file_index], strlen(g_win_system.input_file[file_index]) + 1);
	memcpy(fext, g_win_system.input_file[file_index], strlen(g_win_system.input_file[file_index]) + 1);

	out_ptr = strrchr(fname, '.');
	if (out_ptr)
		*out_ptr = 0;

	out_ptr = strrchr(fext, '.');
	if (out_ptr)
		memmove(fext, out_ptr + 1, strlen(out_ptr + 1) + 1);
	else
		*fext = 0;

	for (i = 0; i < 5; i++)
	{
		ptr = input;
		while((ptr = wcsstr(ptr, string[i])))
		{
			counts[i]++;
			ptr += wcslen(string[i]);
		}
	}
	for (i = 0; i < 5; i++)
	{
		switch(i)
		{
			case 0:
				newlen += (int)strlen(g_win_system.input_path) * counts[i];
				break;
			case 1:
				newlen += (int)strlen(g_win_system.output_folder) * counts[i];
				break;
			case 2:
				newlen += (int)strlen(fname) * counts[i];
				break;
			case 3:
				newlen += (int)strlen(fext) * counts[i];
				break;
			case 4:
				if (output_index == OUTPUT_TYPE_DDS)
					newlen += (int)strlen("dds") * counts[i];
				else if (output_index == OUTPUT_TYPE_KTX)
					newlen += (int)strlen("ktx") * counts[i];
				break;
		}
	}
	newlen += (int)wcslen(input);
	
	output = Mem_Malloc(newlen + 1);
	memset(output, 0, newlen + 1);

	ptr = input;
	out_ptr = output;

	do
	{
		int found = -1;
		for (i = 0; i < 5; i++)
		{
			if (!_wcsnicmp(ptr, string[i], wcslen(string[i])))
			{
				found = i;
				break;
			}
		}
		if (found != -1)
		{
			int local_size = (int)(newlen + 1 - (out_ptr - output));
			switch(found)
			{
				case 0:
					strcat_s(out_ptr, local_size, g_win_system.input_path);
					break;
				case 1:
					strcat_s(out_ptr, local_size, g_win_system.output_folder);
					break;
				case 2:
					strcat_s(out_ptr, local_size, fname);
					break;
				case 3:
					strcat_s(out_ptr, local_size, fext);
					break;
				case 4:
					if (output_index == OUTPUT_TYPE_DDS)
						strcat_s(out_ptr, local_size, "dds");
					else if (output_index == OUTPUT_TYPE_KTX)
						strcat_s(out_ptr, local_size, "ktx");
					break;
			}
			out_ptr += strlen(out_ptr);
			ptr += wcslen(string[found]);
		}
		else
		{
			out_ptr[0] = (char)ptr[0];
			out_ptr[1] = 0;
			out_ptr++;
			ptr++;
		}
	}while(*ptr != 0);

	Mem_Free(fname);
	Mem_Free(fext);

	return output;
}

unsigned __stdcall System_EncodingThread(void *context)
{
	int i;
	int file_id;
	int codec_id;
	ILuint devil_image;
	ILboolean result;
	ILuint uint_result;
	ILuint width;
	ILuint height;
	uint8_t *rgba_u8;
	image_t image;

	for (file_id = 0; file_id < g_win_system.num_input_files; file_id++)
	{
		char *path = Mem_Malloc(strlen(g_win_system.input_path) + strlen(g_win_system.input_file[file_id]) + 1);
		wchar_t *wpath = Mem_Malloc((strlen(g_win_system.input_path) + strlen(g_win_system.input_file[file_id]) + 1) * sizeof(wchar_t));
		sprintf_s(path, strlen(g_win_system.input_path) + strlen(g_win_system.input_file[file_id]) + 1, "%s%s", g_win_system.input_path, g_win_system.input_file[file_id]);
		swprintf_s(wpath, strlen(g_win_system.input_path) + strlen(g_win_system.input_file[file_id]) + 1, L"%S", path);

		ilGenImages(1, &devil_image);
		ilBindImage(devil_image);

		result = ilLoadImage(wpath);

		if (!result)
		{
			ALWAYS_PRINT("failed to load image \"%ls\"\n", wpath);
			ilDeleteImages(1, &devil_image);
			Mem_Free(path);
			Mem_Free(wpath);
			continue;
		}

		width = ilGetInteger(IL_IMAGE_WIDTH);
		height = ilGetInteger(IL_IMAGE_HEIGHT);

		if (width * height > 67108864)
		{
			ALWAYS_PRINT("image \"%ls\" too large (%i x %i)\n", wpath, width, height);
			ilDeleteImages(1, &devil_image);
			Mem_Free(path);
			Mem_Free(wpath);
			continue;
		}

		g_system.num_mipmap_levels = 1;

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

		//codec = System_ModeToCodecID(g_system.opts.encode_mode);
		//gl_mode = System_CodecToGLFormat(codec, g_system.opts.srgb);

		//image = Image_FromSysImage(g_system.image, g_system.num_mipmap_levels, codec);

		Image_GenMipMaps();

		ilDeleteImages(1, &devil_image);

		for (codec_id = 0; codec_id < APP_GROUP_NUM; codec_id++)
		{
			int encode_mode = codec_id + MODE_BC1_RGB;
			int savektx_id = SaveKTXIDFromGroupID(codec_id);
			int savedds_id = SaveDDSIDFromGroupID(codec_id);
			int do_save_ktx = 0;
			int do_save_dds = 0;
			codec_options_etc_t		etc_opts;
			codec_options_bcn_t		bcn_opts;

			if (savektx_id >= 0)
				do_save_ktx = (int)SendMessage(g_win_system.gui_element[savektx_id].hwnd, BM_GETCHECK, 0, 0);
			
			if (savedds_id >= 0)
				do_save_dds = (int)SendMessage(g_win_system.gui_element[savedds_id].hwnd, BM_GETCHECK, 0, 0);

			if (do_save_ktx || do_save_dds)
			{
				int codec;
				int gl_mode;
				int is_srgb = 0;
				int srgb_id = SRGBIDFromGroupID(codec_id);
				int is_mipmaps = (int)SendMessage(g_win_system.gui_element[MipmapsIDFromGroupID(codec_id)].hwnd, BM_GETCHECK, 0, 0);
				int count;
				int ret = 0;
				void *options = 0;
				int block_size;
				wchar_t *progress_text = Mem_Malloc(1048576);
				int path_id = PathIDFromGroupID(codec_id);
				char *out_filename;
				int len = (int)SendMessage(g_win_system.gui_element[path_id].hwnd, WM_GETTEXTLENGTH, 0, 0);
				wchar_t *text = Mem_Malloc(sizeof(wchar_t) * (len + 1));

				if (srgb_id >= 0)
					is_srgb = (int)SendMessage(g_win_system.gui_element[srgb_id].hwnd, BM_GETCHECK, 0, 0);

				SendMessage(g_win_system.gui_element[path_id].hwnd, WM_GETTEXT, len + 1, (LPARAM)text);

				memset(progress_text, 0, 1048576);

				swprintf_s(progress_text, 1048576 / 2, L"Encoding file %i/%i, mode %S\n", file_id + 1, g_win_system.num_input_files, System_ModeToString(encode_mode));
				SendMessage(g_win_system.gui_element[APP_PROGRESS_TEXT].hwnd, WM_SETTEXT, (WPARAM)0, (LPARAM)progress_text);
				Mem_Free(progress_text);

				codec = System_ModeToCodecID(encode_mode);
				gl_mode = System_CodecToGLFormat(codec, is_srgb);

				switch(encode_mode)
				{
					case MODE_BC1_RGB:
					case MODE_BC1_RGBA:
					case MODE_BC2_RGBA:
					case MODE_BC3_RGBA:
					case MODE_BC4_RED:
					case MODE_BC5_RG:
						options = &bcn_opts;
						bcn_opts.is_test = 0;
						bcn_opts.output_dds = do_save_dds;
						bcn_opts.output_ktx = do_save_ktx;
						bcn_opts.common.alpha_cutoff = 127;
						bcn_opts.common.is_srgb = is_srgb;
						bcn_opts.common.is_ypbpr = 0;
						bcn_opts.common.quality = g_win_system.quality;
						block_size = DDS_BlockSize(gl_mode) >> 3;
						break;
					case MODE_ETC1:
					case MODE_ETC2_RGB:
					case MODE_ETC2_RGBA1:
					case MODE_ETC2_RGBA8:
						options = &etc_opts;
						etc_opts.alpha_error = 0.0f;
						etc_opts.colour_error = 0.0f;
						etc_opts.common.alpha_cutoff = 127;
						etc_opts.common.is_srgb = is_srgb;
						etc_opts.common.is_ypbpr = 0;
						etc_opts.common.quality = g_win_system.quality;
						block_size = codec == CODEC_ETC2_RGBA8 ? 2 : 1;
						break;
				}

				image = Image_FromSysImage(g_system.image, g_system.num_mipmap_levels, codec);

				count = 0;
				for (i = 0; i < (is_mipmaps ? g_system.num_mipmap_levels : 1); i++)
					count += Codec_GetEncodeChunks(g_win_system.device_group, g_win_system.device, &image, codec, (int)i, 0, options);
				System_StartProgressThread(1, count);

				ALWAYS_PRINT("Encoding \"%s\" as %s, quality %i, chunks %i, device %i\n", path, System_ModeToString(encode_mode), g_win_system.quality, count, g_win_system.device);

				for (i = 0; i < (is_mipmaps ? g_system.num_mipmap_levels : 1); i++)
				{
					if (Codec_Encode(g_win_system.device_group, g_win_system.device, &image, codec, (int)i, 0, 0, 0, options))
					{
						if (g_win_system.device != 0)
						{
							ret = 1;
							break;
						}
					}
				}
				System_EndProgressThread();
				SendMessage(g_win_system.gui_element[APP_PROGRESS_BAR].hwnd, PBM_SETPOS, (WPARAM)0, 0);

				if (ret)
				{
					count = 0;
					for (i = 0; i < (is_mipmaps ? g_system.num_mipmap_levels : 1); i++)
						count += Codec_GetEncodeChunks(g_win_system.device_group, 0, &image, codec, (int)i, 0, options);
					System_StartProgressThread(1, count);

					ALWAYS_PRINT("OpenCL error, encoding \"%s\" as %s, quality %i, chunks %i, CPU\n", path, System_ModeToString(encode_mode), g_win_system.quality, count);

					for (i = 0; i < (is_mipmaps ? g_system.num_mipmap_levels : 1); i++)
						Codec_Encode(g_win_system.device_group, 0, &image, codec, (int)i, 0, 0, 0, options);
					System_EndProgressThread();
					SendMessage(g_win_system.gui_element[APP_PROGRESS_BAR].hwnd, PBM_SETPOS, (WPARAM)0, 0);
				}

				for (i = 0; i < (is_mipmaps ? g_system.num_mipmap_levels : 1); i++)
					g_system.image[i].encoded = image.dst_encoded[i];

				if (do_save_ktx)
				{
					out_filename = ExpandWText(text, file_id, OUTPUT_TYPE_KTX);
					LOG_PRINT("out filename (KTX): \"%s\"\n", out_filename);
					g_system.opts.enable_mipmap = is_mipmaps;
					KTX_SaveETC(out_filename, gl_mode, width, height, block_size);
					Mem_Free(out_filename);
				}
				if (do_save_dds)
				{
					out_filename = ExpandWText(text, file_id, OUTPUT_TYPE_DDS);
					LOG_PRINT("out filename (DDS): \"%s\"\n", out_filename);
					g_system.opts.enable_mipmap = is_mipmaps;
					DDS_SaveDDS(out_filename, gl_mode);
					Mem_Free(out_filename);
				}
				Mem_Free(text);

				Image_Destroy(&image);

				if (g_win_system.pending_cancel)
					break;
			}
		}

		for (i = 0; i < g_system.num_mipmap_levels; i++)
			Mem_Free(g_system.image[i].rgba);
		Mem_Free(g_system.image);

		Mem_Free(path);
		Mem_Free(wpath);

		if (g_win_system.pending_cancel)
			break;
	}
	SendMessage(g_win_system.gui_element[APP_PROGRESS_TEXT].hwnd, WM_SETTEXT, (WPARAM)0, (LPARAM)L"");
	g_win_system.pending_cancel = 0;
	g_win_system.encoding = 0;
	PostMessage(g_win_system.gui_element[APP_MAIN_WINDOW].hwnd, WM_USER_ENCODING_COMPLETE, 0, 0);

	_endthreadex(0);
	return 0;
}

void UpdateToolTip(int group_id)
{
	int path_id = PathIDFromGroupID(group_id);
	int tooltip_id = TooltipIDFromGroupID(group_id);
	int len = (int)SendMessage(g_win_system.gui_element[path_id].hwnd, WM_GETTEXTLENGTH, 0, 0);
	wchar_t *text = Mem_Malloc(sizeof(wchar_t) * (len + 1));
	wchar_t *tooltip_text;
	int i;
	int total_len = 0;
	TOOLINFO toolInfo = {0};

	SendMessage(g_win_system.gui_element[path_id].hwnd, WM_GETTEXT, len + 1, (LPARAM)text);

	for (i = 0; i < (g_win_system.num_input_files < 5 ? g_win_system.num_input_files : 5); i++)
	{
		int ktx_id = SaveKTXIDFromGroupID(group_id);
		int dds_id = SaveDDSIDFromGroupID(group_id);
		char *local_text;

		if (ktx_id >= 0)
		{
			if (SendMessage(g_win_system.gui_element[ktx_id].hwnd, BM_GETCHECK, 0, 0))
			{
				local_text = ExpandWText(text, i, OUTPUT_TYPE_KTX);
				total_len += (int)strlen(local_text) + (int)strlen("\n");
				Mem_Free(local_text);
			}
		}
		if (dds_id >= 0)
		{
			if (SendMessage(g_win_system.gui_element[dds_id].hwnd, BM_GETCHECK, 0, 0))
			{
				local_text = ExpandWText(text, i, OUTPUT_TYPE_DDS);
				total_len += (int)strlen(local_text) + (int)strlen("\n");
				Mem_Free(local_text);
			}
		}
	}
	total_len += (int)strlen("\n...");
	total_len++;

	tooltip_text = Mem_Malloc((total_len) * sizeof(wchar_t));
	memset(tooltip_text, 0, (total_len) * sizeof(wchar_t));

	for (i = 0; i < (g_win_system.num_input_files < 5 ? g_win_system.num_input_files : 5); i++)
	{
		int ktx_id = SaveKTXIDFromGroupID(group_id);
		int dds_id = SaveDDSIDFromGroupID(group_id);
		char *local_text;

		if (ktx_id >= 0)
		{
			if (SendMessage(g_win_system.gui_element[ktx_id].hwnd, BM_GETCHECK, 0, 0))
			{
				local_text = ExpandWText(text, i, OUTPUT_TYPE_KTX);
				if (wcslen(tooltip_text))
					swprintf_s(tooltip_text, total_len, L"%s\n%S", tooltip_text, local_text);
				else
					swprintf_s(tooltip_text, total_len, L"%S", local_text);
				Mem_Free(local_text);
			}
		}
		if (dds_id >= 0)
		{
			if (SendMessage(g_win_system.gui_element[dds_id].hwnd, BM_GETCHECK, 0, 0))
			{
				local_text = ExpandWText(text, i, OUTPUT_TYPE_DDS);
				if (wcslen(tooltip_text))
					swprintf_s(tooltip_text, total_len, L"%s\n%S", tooltip_text, local_text);
				else
					swprintf_s(tooltip_text, total_len, L"%S", local_text);
				Mem_Free(local_text);
			}
		}
	}
	if (g_win_system.num_input_files > 5)
		swprintf_s(tooltip_text, total_len, L"%s\n...", tooltip_text);

	toolInfo.cbSize = sizeof(toolInfo);
	toolInfo.hwnd = g_win_system.gui_element[path_id].hwnd;
	toolInfo.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	toolInfo.uId = (UINT_PTR)g_win_system.gui_element[path_id].hwnd;
	toolInfo.lpszText = tooltip_text;
	SendMessage(g_win_system.gui_element[tooltip_id].hwnd, TTM_SETTOOLINFO, 0, (LPARAM)&toolInfo);

	Mem_Free(text);
	Mem_Free(tooltip_text);
}

BOOL SH_EnumChildProc(HWND hwnd, LPARAM lParam)
{
	wchar_t classname[2048];
	GetClassName(hwnd, classname, 2048);

	if (!wcscmp(classname, L"SysTreeView32"))
		*(HWND*)lParam = hwnd;
	return TRUE;
}

int CALLBACK SH_BrowseNotify(HWND hWnd, UINT iMessage, long wParam, LPARAM lParam)
{   
	if (iMessage == BFFM_SELCHANGED)
	{
		HWND tvhwnd = 0;
		HTREEITEM item;

		EnumChildWindows(hWnd, SH_EnumChildProc, (LPARAM)&tvhwnd);

		if (tvhwnd)
		{
			item = (HTREEITEM)SendMessage(tvhwnd, TVM_GETNEXTITEM, (WPARAM)TVGN_CARET, 0);
			if (item)
				SendMessage(tvhwnd, TVM_ENSUREVISIBLE, 0, (LPARAM)item);
		}
		return 0;
	}
	if (iMessage == BFFM_INITIALIZED)
	{   
		wchar_t *pathw;
		if (g_win_system.output_folder)
		{
			pathw = Mem_Malloc(sizeof(wchar_t) * (strlen(g_win_system.output_folder) + 1));
			swprintf_s(pathw, strlen(g_win_system.output_folder) + 1, L"%S", g_win_system.output_folder);
			SendMessage(hWnd, BFFM_SETSELECTION, 1, (LPARAM)pathw);
			Mem_Free(pathw);
		}
		else if (!g_win_system.output_folder && g_win_system.input_path)
		{
			pathw = Mem_Malloc(sizeof(wchar_t) * (strlen(g_win_system.input_path) + 1));
			swprintf_s(pathw, strlen(g_win_system.input_path) + 1, L"%S", g_win_system.input_path);
			SendMessage(hWnd, BFFM_SETSELECTION, 1, (LPARAM)pathw);
			Mem_Free(pathw);
		}
		return 1;
	}
	return 0;
}

LRESULT System_WndProc(HWND hwnd, 
	UINT uMsg, 
	WPARAM wParam, 
	LPARAM lParam 
)
{
	switch (uMsg)
	{
		case WM_GETMINMAXINFO:
		{
			MINMAXINFO *minmax = (MINMAXINFO*)lParam;

			minmax->ptMinTrackSize.x = 512 + 80;
			minmax->ptMinTrackSize.y = 816 + 128;
			minmax->ptMaxTrackSize.x = 512 + 80;
			minmax->ptMaxTrackSize.y = 816 + 128;

			break;
		}
		case WM_USER_LOADING_COMPLETE:
		{
			int i;
			for (i = 0; i < g_win_system.num_gui_element; i++)
				if (i != APP_CANCEL && i != APP_ENCODE && i != APP_MAIN_WINDOW && i != APP_PROGRESS_BAR && i != APP_PROGRESS_TEXT)
					EnableWindow(g_win_system.gui_element[i].hwnd, TRUE);

			WaitForSingleObject(g_win_system.worker_thread_h, INFINITE);
			CloseHandle(g_win_system.worker_thread_h);

			return 0;
		}
		case WM_USER_ENCODING_COMPLETE:
		{
			int i;
			for (i = 0; i < g_win_system.num_gui_element; i++)
				if (i != APP_CANCEL && i != APP_MAIN_WINDOW && i != APP_PROGRESS_BAR && i != APP_PROGRESS_TEXT)
					EnableWindow(g_win_system.gui_element[i].hwnd, TRUE);

			EnableWindow(g_win_system.gui_element[APP_CANCEL].hwnd, FALSE);

			WaitForSingleObject(g_win_system.worker_thread_h, INFINITE);
			CloseHandle(g_win_system.worker_thread_h);

			return 0;
		}
		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}
		case WM_COMMAND:
		{
			if (IsTextField((HWND)lParam))
			{
				int group_id = GroupIDFromHWND((HWND)lParam);

				switch (HIWORD(wParam))
				{
					case EN_CHANGE:
					{
						UpdateToolTip(group_id);
						break;
					}
				}
				break;
			}
			if (IsMacroButton((HWND)lParam))
			{
				int maxlen = 512;
				wchar_t *string[5];
				POINT pt;
				HMENU hSplitMenu;

				GetCursorPos(&pt);

				if (g_win_system.num_input_files)
					maxlen = 512 + (int)strlen(g_win_system.input_file[0]);
				if (g_win_system.output_folder)
					if (512 + strlen(g_win_system.output_folder) > maxlen)
						maxlen = 512 + (int)strlen(g_win_system.output_folder);
				if (g_win_system.input_path)
					if (512 + strlen(g_win_system.input_path) > maxlen)
						maxlen = 512 + (int)strlen(g_win_system.input_path);

				// Create a menu and add items.
				hSplitMenu = CreatePopupMenu();

				AppendMenu(hSplitMenu, MF_BYPOSITION, MACRO_INPUT_FOLDER + MacroButtonIDOffset((HWND)lParam), L"$(InDir)");
				AppendMenu(hSplitMenu, MF_BYPOSITION, MACRO_OUTPUT_FOLDER + MacroButtonIDOffset((HWND)lParam), L"$(OutDir)");
				AppendMenu(hSplitMenu, MF_BYPOSITION, MACRO_INPUT_NAME + MacroButtonIDOffset((HWND)lParam), L"$(InName)");
				AppendMenu(hSplitMenu, MF_BYPOSITION, MACRO_INPUT_EXT + MacroButtonIDOffset((HWND)lParam), L"$(InExt)");
				AppendMenu(hSplitMenu, MF_BYPOSITION, MACRO_OUTPUT_EXT + MacroButtonIDOffset((HWND)lParam), L"$(OutExt)");

				string[0] = Mem_Malloc(maxlen);
				string[1] = Mem_Malloc(maxlen);
				string[2] = Mem_Malloc(maxlen);
				string[3] = Mem_Malloc(maxlen);
				string[4] = Mem_Malloc(maxlen);
				
				if (g_win_system.input_path)
					swprintf_s(string[0], maxlen/2, L"Expands to \"%S\"", g_win_system.input_path);
				else
					swprintf_s(string[0], maxlen/2, L"(Please select one or more input files first)");
				if (g_win_system.output_folder)
					swprintf_s(string[1], maxlen/2, L"Expands to \"%S\"", g_win_system.output_folder);
				else
					swprintf_s(string[1], maxlen/2, L"(Please select and output directory first)");
				if (g_win_system.num_input_files)
				{
					char *temp = Mem_Malloc(maxlen);
					char *ptr;
					memcpy(temp, g_win_system.input_file[0], strlen(g_win_system.input_file[0]) + 1);
					ptr = strrchr(temp, '.');
					if (ptr)
						*ptr = 0;
					swprintf_s(string[2], maxlen/2, L"Expands to \"[input filename excluding extension, e.g. \"%S\"]\"", temp);
					Mem_Free(temp);
				}
				else
					swprintf_s(string[2], maxlen/2, L"Expands to \"[input filename excluding extension, e.g. \"image\"]\"");
				if (g_win_system.num_input_files)
				{
					char *temp = Mem_Malloc(maxlen);
					char *ptr;
					memcpy(temp, g_win_system.input_file[0], strlen(g_win_system.input_file[0]) + 1);
					ptr = strrchr(temp, '.');
					if (ptr)
					{
						ptr++;
						swprintf_s(string[3], maxlen/2, L"Expands to \"[input filename extension, e.g. \"%S\"]\"", ptr);
					}
					else
						swprintf_s(string[3], maxlen/2, L"Expands to \"[input filename extension, e.g. \"png\"]\"");
					Mem_Free(temp);
				}
				else
					swprintf_s(string[3], maxlen/2, L"Expands to \"[input filename extension, e.g. \"png\"]\"");
				
				swprintf_s(string[4], maxlen/2, L"Expands to \"[output filename extension, e.g. \"dds\"]\"");
				
				AppendMenu(hSplitMenu, MF_MENUBREAK|MF_DISABLED, 0, string[0]);
				AppendMenu(hSplitMenu, MF_DISABLED, 0, string[1]);
				AppendMenu(hSplitMenu, MF_DISABLED, 0, string[2]);
				AppendMenu(hSplitMenu, MF_DISABLED, 0, string[3]);
				AppendMenu(hSplitMenu, MF_DISABLED, 0, string[4]);
				
				Mem_Free(string[0]);
				Mem_Free(string[1]);
				Mem_Free(string[2]);
				Mem_Free(string[3]);
				Mem_Free(string[4]);

				// Display the menu.
				TrackPopupMenu(hSplitMenu, TPM_LEFTALIGN | TPM_TOPALIGN, pt.x, pt.y, 0, hwnd, NULL);
				return 0;
			}
			else
			{
				if ((HIWORD(wParam) == 0) && (lParam == 0)) // menu
				{
					int group_id = GroupIDFromMenuID(LOWORD(wParam));
					int path_id = PathIDFromGroupID(group_id);
					int sub_id = LOWORD(wParam) - 5 * (LOWORD(wParam) / 5);
					wchar_t *text;
					int len;
					int start_sel = 0;
					int end_sel = 0;
					wchar_t *string[5] = {L"$(InDir)", L"$(OutDir)", L"$(InName)", L"$(InExt)", L"$(OutExt)"};
					int len_sub = (int)wcslen(string[sub_id]);

					if (path_id < 0)
						return 0;

					len = (int)SendMessage(g_win_system.gui_element[path_id].hwnd, WM_GETTEXTLENGTH, 0, 0);
					text = Mem_Malloc(sizeof(wchar_t) * (len + 1 + len_sub));

					SendMessage(g_win_system.gui_element[path_id].hwnd, WM_GETTEXT, len + 1, (LPARAM)text);
					SendMessage(g_win_system.gui_element[path_id].hwnd, EM_GETSEL, (WPARAM)&start_sel, (LPARAM)&end_sel);

					memmove(&text[start_sel + len_sub], &text[start_sel], (wcslen(&text[start_sel]) + 1) * sizeof(wchar_t));
					memcpy(&text[start_sel], string[sub_id], sizeof(wchar_t) * (len_sub));

					SendMessage(g_win_system.gui_element[path_id].hwnd, WM_SETTEXT, 0, (LPARAM)text);

					Mem_Free(text);

					UpdateToolTip(group_id);

					return 0;
				}
				else
				{
					int i;
					switch (HIWORD(wParam))
					{
						case BN_CLICKED:
						{
							HWND button_hwnd = (HWND)lParam;
							if (button_hwnd == g_win_system.gui_element[APP_INPUT_FILE].hwnd)
							{
								OPENFILENAME ofn;       // common dialog box structure
								TCHAR *szFile = Mem_Malloc(1048576);       // if using TCHAR macros
								memset(szFile, 0, 1048576);

								// Initialize OPENFILENAME
								ZeroMemory(&ofn, sizeof(ofn));
								ofn.lStructSize = sizeof(ofn);
								ofn.hwndOwner = g_win_system.gui_element[APP_INPUT_FILE].hwnd;
								ofn.lpstrFile = szFile;
								ofn.nMaxFile = 1048576;
								ofn.lpstrFilter = L"Image files\0*.jpg;*.tga;*.png;*.bmp;*.gif;*.jpeg;*.pcx;*.tif;*.dds\0All\0*.*\0";
								ofn.nFilterIndex = 1;
								ofn.lpstrFileTitle = NULL;
								ofn.nMaxFileTitle = 0;
								ofn.lpstrInitialDir = NULL;
								ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT | OFN_EXPLORER;

								if (GetOpenFileName(&ofn) == TRUE)
								{
									wchar_t *ptr = ofn.lpstrFile;
									int len;
									for (i = 0; i < g_win_system.num_input_files; i++)
										Mem_Free(g_win_system.input_file[i]);
									Mem_Free(g_win_system.input_file);
									Mem_Free(g_win_system.input_path);

									g_win_system.input_file = 0;
									g_win_system.num_input_files = 0;

									g_win_system.input_path = Mem_Malloc(ofn.nFileOffset + 2);
									_snprintf_s(g_win_system.input_path, ofn.nFileOffset + 1, ofn.nFileOffset, "%ls", ptr);
									g_win_system.input_path[ofn.nFileOffset] = 0;

									len = (int)strlen(g_win_system.input_path);

									if (g_win_system.input_path[len - 1] != '\\')
									{
										g_win_system.input_path[len] = '\\';
										g_win_system.input_path[len + 1] = 0;
									}
									ptr += ofn.nFileOffset;

									do
									{
										g_win_system.num_input_files++;
										g_win_system.input_file = Mem_Realloc(g_win_system.input_file, sizeof(char*) * g_win_system.num_input_files);
										g_win_system.input_file[g_win_system.num_input_files - 1] = Mem_Malloc(wcslen(ptr) + 1);
										sprintf_s(g_win_system.input_file[g_win_system.num_input_files - 1], wcslen(ptr) + 1, "%ls", ptr);
										ptr += wcslen(ptr) + 1;
									}while((ptr[-1] == 0) && (ptr[0] != 0));

									if (g_win_system.num_input_files > 1)
									{
										SendMessage(g_win_system.gui_element[APP_INPUT_FILE].hwnd, WM_SETTEXT, 0, (LPARAM)L"Multiple input files selected");
									}
									else
									{
										wchar_t *button_text = Mem_Malloc(sizeof(wchar_t) * (strlen(g_win_system.input_file[0]) + 1));
										swprintf_s(button_text, strlen(g_win_system.input_file[0]) + 1, L"%S", g_win_system.input_file[0]);
										SendMessage(g_win_system.gui_element[APP_INPUT_FILE].hwnd, WM_SETTEXT, 0, (LPARAM)button_text);
										Mem_Free(button_text);
									}
								}
								Mem_Free(szFile);
							}
							else if (button_hwnd == g_win_system.gui_element[APP_OUTPUT_FOLDER].hwnd)
							{
								BROWSEINFO binf = {0};
								PIDLIST_ABSOLUTE pidl;
								wchar_t path[MAX_PATH < 4096 ? 4096 : MAX_PATH];

								binf.hwndOwner = g_win_system.gui_element[APP_OUTPUT_FOLDER].hwnd;
								binf.pszDisplayName = path;
								binf.lpszTitle = L"Select output folder";
								binf.ulFlags = BIF_NEWDIALOGSTYLE;
								binf.lpfn = (BFFCALLBACK)SH_BrowseNotify;

								pidl = SHBrowseForFolder(&binf);

								if (pidl)
								{
									SHGetPathFromIDList(pidl, path);

									Mem_Free(g_win_system.output_folder);
									g_win_system.output_folder = Mem_Malloc(wcslen(path) + 2);
									sprintf_s(g_win_system.output_folder, wcslen(path) + 1, "%ls", path);
									g_win_system.output_folder[wcslen(path)] = '\\';
									g_win_system.output_folder[wcslen(path) + 1] = 0;
									SendMessage(g_win_system.gui_element[APP_OUTPUT_FOLDER].hwnd, WM_SETTEXT, 0, (LPARAM)path);

									CoTaskMemFree(pidl);
								}
							}
							else if (button_hwnd == g_win_system.gui_element[APP_ENCODE].hwnd)
							{
								g_win_system.encoding = 1;
								g_win_system.pending_cancel = 0;
								g_win_system.device = (int)SendMessage(g_win_system.gui_element[APP_DEVICE].hwnd, CB_GETCURSEL, 0, 0);
								g_win_system.device = g_win_system.device_index_map_from_cb[g_win_system.device];
								g_win_system.quality = (int)SendMessage(g_win_system.gui_element[APP_QUALITY].hwnd, CB_GETCURSEL, 0, 0);
								EnableWindow(g_win_system.gui_element[APP_CANCEL].hwnd, TRUE); 
								for (i = 0; i < g_win_system.num_gui_element; i++)
								{
									if (i != APP_MAIN_WINDOW && i != APP_PROGRESS_BAR && i != APP_PROGRESS_TEXT && i != APP_CANCEL)
										EnableWindow(g_win_system.gui_element[i].hwnd, FALSE); 
								}
								g_win_system.worker_thread_h = (HANDLE)_beginthreadex(NULL, 0, System_EncodingThread, NULL, 0, &g_win_system.worker_thread_id);
							}
							else if (button_hwnd == g_win_system.gui_element[APP_CANCEL].hwnd)
							{
								EnableWindow(g_win_system.gui_element[APP_CANCEL].hwnd, FALSE); 
								g_win_system.pending_cancel = 1;
							}

							for (i = 0; i < APP_GROUP_NUM; i++)
								UpdateToolTip(i);

							if (ShouldEncodeBeEnabled())
								EnableWindow(g_win_system.gui_element[APP_ENCODE].hwnd, TRUE);
							else
								EnableWindow(g_win_system.gui_element[APP_ENCODE].hwnd, FALSE);
							break;
						}
					}
				}
			}
		}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void System_UpdateGUIProgressBar(double x)
{
	SendMessage(g_win_system.gui_element[APP_PROGRESS_BAR].hwnd, PBM_SETPOS, (WPARAM)(1000 * x), 0);
}

unsigned __stdcall System_LoadingThread(void *context)
{
	int i;
	double best_performance;
	double cpu_perf;
	int best_device;
	int valid_count;
	wchar_t *string;

	for (i = 0; i < g_win_system.device_group->num_devices; i++)
	{
		if (i == 0)
		{
			string = Mem_Malloc((1 + 512) * sizeof(wchar_t));
			swprintf_s(string, (1 + 512), L"Loading ETC codec for device %S", "CPU");
			SendMessage(g_win_system.gui_element[APP_PROGRESS_TEXT].hwnd, WM_SETTEXT, (WPARAM)0, (LPARAM)string);
			Mem_Free(string);
			Codec_LoadGroup(g_win_system.device_group, i, CODEC_GROUP_ETC);
			//Codec_InspectGroup(g_win_system.device_group, i, CODEC_GROUP_ETC);
			//Codec_DeInspectGroup(&g_win_system.device_group->device[i], CODEC_GROUP_ETC);

			string = Mem_Malloc((1 + 512) * sizeof(wchar_t));
			swprintf_s(string, (1 + 512), L"Loading BCN codec for device %S", "CPU");
			SendMessage(g_win_system.gui_element[APP_PROGRESS_TEXT].hwnd, WM_SETTEXT, (WPARAM)0, (LPARAM)string);
			Mem_Free(string);
			Codec_LoadGroup(g_win_system.device_group, i, CODEC_GROUP_BCN);
			//Codec_InspectGroup(g_win_system.device_group, i, CODEC_GROUP_BCN);
			//Codec_DeInspectGroup(&g_win_system.device_group->device[i], CODEC_GROUP_BCN);
		}
		else
		{
			string = Mem_Malloc((strlen(g_win_system.device_group->device[i].cl_device_info.name) + 1 + 512) * sizeof(wchar_t));
			swprintf_s(string, strlen(g_win_system.device_group->device[i].cl_device_info.name) + 1 + 512, L"Loading ETC codec for device %S", g_win_system.device_group->device[i].cl_device_info.name);
			SendMessage(g_win_system.gui_element[APP_PROGRESS_TEXT].hwnd, WM_SETTEXT, (WPARAM)0, (LPARAM)string);
			Mem_Free(string);
			Codec_LoadGroup(g_win_system.device_group, i, CODEC_GROUP_ETC);
			//Codec_InspectGroup(g_win_system.device_group, i, CODEC_GROUP_ETC);
			//Codec_DeInspectGroup(&g_win_system.device_group->device[i], CODEC_GROUP_ETC);

			string = Mem_Malloc((strlen(g_win_system.device_group->device[i].cl_device_info.name) + 1 + 512) * sizeof(wchar_t));
			swprintf_s(string, strlen(g_win_system.device_group->device[i].cl_device_info.name) + 1 + 512, L"Loading BCN codec for device %S", g_win_system.device_group->device[i].cl_device_info.name);
			SendMessage(g_win_system.gui_element[APP_PROGRESS_TEXT].hwnd, WM_SETTEXT, (WPARAM)0, (LPARAM)string);
			Mem_Free(string);
			Codec_LoadGroup(g_win_system.device_group, i, CODEC_GROUP_BCN);
			//Codec_InspectGroup(g_win_system.device_group, i, CODEC_GROUP_BCN);
			//Codec_DeInspectGroup(&g_win_system.device_group->device[i], CODEC_GROUP_BCN);
		}
	}

	SendMessage(g_win_system.gui_element[APP_PROGRESS_TEXT].hwnd, WM_SETTEXT, (WPARAM)0, (LPARAM)L"");

	Codec_InspectGroup(g_win_system.device_group, 0, Codec_GroupFromCodec(0));

	best_performance = g_win_system.device_group->device[0].codec[0].pixels_per_second[CODEC_QUALITY_BEST];
	cpu_perf = best_performance;
	best_device = 0;

	//Codec_DeInspectGroup(&g_win_system.device_group->device[0], Codec_GroupFromCodec(0));

	ALWAYS_PRINT_NODEC("Device CPU performance: %.2f MP/s\n", best_performance / 1000000.0);

	g_win_system.device_index_map_from_cb[0] = 0;

	for (i = 1; i < g_win_system.device_group->num_devices; i++)
	{
		int ret = Codec_InspectGroup(g_win_system.device_group, (int)i, Codec_GroupFromCodec(0));
		if (!ret)
		{
			ALWAYS_PRINT_NODEC("Device %i performance: %.2f MP/s\n", (int)i - 1, g_win_system.device_group->device[i].codec[0].pixels_per_second[CODEC_QUALITY_BEST] / 1000000.0);
			if (g_win_system.device_group->device[i].codec[0].pixels_per_second[CODEC_QUALITY_BEST] > best_performance)
			{
				best_performance = g_win_system.device_group->device[i].codec[0].pixels_per_second[CODEC_QUALITY_BEST];
				best_device = (int)i;
			}
		}
		else
			ALWAYS_PRINT_NODEC("Device %i unavailable due to build errors\n", (int)i - 1);
		//Codec_DeInspectGroup(&g_win_system.device_group->device[i], Codec_GroupFromCodec(0));
	}

	string = Mem_Malloc((strlen("CPU") + 1 + 64) * sizeof(wchar_t));
	swprintf_s(string, strlen("CPU") + 1 + 64, L"Speed %.0f%%: CPU", 100.0 * cpu_perf / best_performance);
	SendMessage(g_win_system.gui_element[APP_DEVICE].hwnd, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)string);
	Mem_Free(string);

	for (valid_count = 1, i = 1; i < g_win_system.device_group->num_devices; i++)
	{
		int ret = Codec_InspectGroup(g_win_system.device_group, (int)i, Codec_GroupFromCodec(0));
		if (!ret)
		{
			string = Mem_Malloc((strlen(g_win_system.device_group->device[i].cl_device_info.name) + 1 + 64) * sizeof(wchar_t));
			swprintf_s(string, strlen(g_win_system.device_group->device[i].cl_device_info.name) + 1 + 64, L"Speed %.0f%%: %S", 100.0 * g_win_system.device_group->device[i].codec[0].pixels_per_second[CODEC_QUALITY_BEST] / best_performance, g_win_system.device_group->device[i].cl_device_info.name);
			SendMessage(g_win_system.gui_element[APP_DEVICE].hwnd, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)string);
			Mem_Free(string);
			g_win_system.device_index_map_from_cb[valid_count] = i;
			valid_count++;
		}
		//Codec_DeInspectGroup(&g_win_system.device_group->device[i], Codec_GroupFromCodec(0));
	}

	SendMessage(g_win_system.gui_element[APP_DEVICE].hwnd, (UINT)CB_SETCURSEL, (WPARAM)best_device, (LPARAM)0);

	SendMessage(g_win_system.gui_element[APP_PROGRESS_BAR].hwnd, PBM_SETPOS, (WPARAM)0, 0);

	PostMessage(g_win_system.gui_element[APP_MAIN_WINDOW].hwnd, WM_USER_LOADING_COMPLETE, 0, 0);

	_endthreadex(0);
	return 0;
}

int System_LoadGUIElements()
{
	int i;
	COMBOBOXINFO cbi = {0};

	for (i = 0; i < g_win_system.num_gui_element; i++)
	{
		HWND parent = 0;

		if (!g_win_system.gui_element[i].classname)
			continue;
		
		if (g_win_system.gui_element[i].parent_p)
			parent = g_win_system.gui_element[i].parent_p->hwnd;

		g_win_system.gui_element[i].hwnd
			= CreateWindowEx(
				g_win_system.gui_element[i].win_ex_style,
				g_win_system.gui_element[i].classname,
				g_win_system.gui_element[i].text,
				g_win_system.gui_element[i].win_style,
				g_win_system.gui_element[i].x,
				g_win_system.gui_element[i].y,
				g_win_system.gui_element[i].width,
				g_win_system.gui_element[i].height,
				parent,
				NULL,
				GetModuleHandle(NULL),
				NULL);
		if (g_win_system.gui_element[i].hwnd == 0)
			return -1;
		if (g_win_system.gui_element[i].classname == TOOLTIPS_CLASS)
		{
			TOOLINFO toolInfo = {0};
			toolInfo.cbSize = sizeof(toolInfo);
			toolInfo.hwnd = parent;
			toolInfo.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
			toolInfo.uId = (UINT_PTR)parent;
			toolInfo.lpszText = L"";
			SendMessage(g_win_system.gui_element[i].hwnd, TTM_ADDTOOL, 0, (LPARAM)&toolInfo);
			SendMessage(g_win_system.gui_element[i].hwnd, TTM_SETMAXTIPWIDTH, 0, 65535);
		}
	}

	SendMessage(g_win_system.gui_element[APP_PROGRESS_BAR].hwnd, PBM_SETRANGE, 0, MAKELPARAM(0, 1000));
	SendMessage(g_win_system.gui_element[APP_PROGRESS_BAR].hwnd, PBM_SETSTEP, (WPARAM) 1, 0); 

	SendMessage(g_win_system.gui_element[APP_QUALITY].hwnd, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)L"Fast");
	SendMessage(g_win_system.gui_element[APP_QUALITY].hwnd, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)L"Normal");
	SendMessage(g_win_system.gui_element[APP_QUALITY].hwnd, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)L"High");
	SendMessage(g_win_system.gui_element[APP_QUALITY].hwnd, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)L"Best");
	
	SendMessage(g_win_system.gui_element[APP_QUALITY].hwnd, (UINT)CB_SETCURSEL, (WPARAM)1, (LPARAM)0);

	g_win_system.worker_thread_h = (HANDLE)_beginthreadex(NULL, 0, System_LoadingThread, NULL, 0, &g_win_system.worker_thread_id);

	cbi.cbSize = sizeof(COMBOBOXINFO);

	GetComboBoxInfo(g_win_system.gui_element[APP_QUALITY].hwnd, &cbi);
	SendMessage(cbi.hwndItem, EM_SETREADONLY, (WPARAM)TRUE, 0);

	GetComboBoxInfo(g_win_system.gui_element[APP_DEVICE].hwnd, &cbi);
	SendMessage(cbi.hwndItem, EM_SETREADONLY, (WPARAM)TRUE, 0);

	SendMessage(g_win_system.gui_element[APP_OUTPUT_BC1RGB].hwnd, WM_SETTEXT, 0, (LPARAM)L"$(OutDir)$(InName)_out_BC1RGB.$(OutExt)");
	SendMessage(g_win_system.gui_element[APP_OUTPUT_BC1RGBA].hwnd, WM_SETTEXT, 0, (LPARAM)L"$(OutDir)$(InName)_out_BC1RGBA.$(OutExt)");
	SendMessage(g_win_system.gui_element[APP_OUTPUT_BC2RGBA].hwnd, WM_SETTEXT, 0, (LPARAM)L"$(OutDir)$(InName)_out_BC2RGBA.$(OutExt)");
	SendMessage(g_win_system.gui_element[APP_OUTPUT_BC3RGBA].hwnd, WM_SETTEXT, 0, (LPARAM)L"$(OutDir)$(InName)_out_BC3RGBA.$(OutExt)");
	SendMessage(g_win_system.gui_element[APP_OUTPUT_BC4RED].hwnd, WM_SETTEXT, 0, (LPARAM)L"$(OutDir)$(InName)_out_BC4RED.$(OutExt)");
	SendMessage(g_win_system.gui_element[APP_OUTPUT_BC5RG].hwnd, WM_SETTEXT, 0, (LPARAM)L"$(OutDir)$(InName)_out_BC5RG.$(OutExt)");
	SendMessage(g_win_system.gui_element[APP_OUTPUT_ETC1RGB].hwnd, WM_SETTEXT, 0, (LPARAM)L"$(OutDir)$(InName)_out_ETC1RGB.$(OutExt)");
	SendMessage(g_win_system.gui_element[APP_OUTPUT_ETC2RGB].hwnd, WM_SETTEXT, 0, (LPARAM)L"$(OutDir)$(InName)_out_ETC2RGB.$(OutExt)");
	SendMessage(g_win_system.gui_element[APP_OUTPUT_ETC2RGBA1].hwnd, WM_SETTEXT, 0, (LPARAM)L"$(OutDir)$(InName)_out_ETC2RGBA1.$(OutExt)");
	SendMessage(g_win_system.gui_element[APP_OUTPUT_ETC2RGBA8].hwnd, WM_SETTEXT, 0, (LPARAM)L"$(OutDir)$(InName)_out_ETC2RGBA8.$(OutExt)");

	for (i = 0; i < APP_GROUP_NUM; i++)
		UpdateToolTip(i);

	for (i = 0; i < g_win_system.num_gui_element; i++)
	{
		if (i != APP_MAIN_WINDOW && i != APP_PROGRESS_BAR && i != APP_PROGRESS_TEXT)
			EnableWindow(g_win_system.gui_element[i].hwnd, FALSE); 
	}

	for (i = 0; i < APP_GROUP_NUM; i++)
		g_win_system.encode_options[i].output_path_control_id = PathIDFromGroupID(i);

	button_orig_wndproc = (WNDPROC)SetWindowLongPtr(g_win_system.gui_element[APP_INPUT_FILE].hwnd, GWLP_WNDPROC, (LONG_PTR)System_WndProcButton);
	SetWindowLongPtr(g_win_system.gui_element[APP_OUTPUT_FOLDER].hwnd, GWLP_WNDPROC, (LONG_PTR)System_WndProcButton);

	return 0;
}

// windows subsystem
int CALLBACK WinMain(
	HINSTANCE   hInstance,
	HINSTANCE   hPrevInstance,
	LPSTR       lpCmdLine,
	int         nCmdShow)
{
	int is_debug = 0;
	WNDCLASS				wc;
	int						is_quit = 0;
	MSG						msg;
	INITCOMMONCONTROLSEX	InitCtrls;

	g_win_system.is_gui = 1;
	g_win_system.gui_element = g_gui_element_list;
	g_win_system.num_gui_element = APP_NUM;

	System_ParseOptions(__argc, __argv);
#ifdef _DEBUG
	g_system.opts.enable_log = 1;
	is_debug = 1;
#endif
	is_debug |= g_system.opts.enable_log;

	if (is_debug)
	{
		FILE *f;
		AllocConsole();
		freopen_s(&f, "CONOUT$", "w", stdout);
		freopen_s(&f, "CONOUT$", "w", stderr);
		freopen_s(&f, "CONIN$", "r", stdin);
	}

	g_system.info.time_start = Timer_GetTicks();

	g_win_system.device_group = DeviceGroup_New();

	g_win_system.num_cl_devices = g_win_system.device_group->num_devices - 1;
	g_win_system.device_index_map_from_cb = Mem_Malloc(sizeof(int) * g_win_system.num_cl_devices);
	memset(g_win_system.device_index_map_from_cb, 0, sizeof(int) * g_win_system.num_cl_devices);

	CL_ETC_Init(g_win_system.device_group);
	CL_BCN_Init(g_win_system.device_group);

	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_STANDARD_CLASSES;
	
	InitCommonControlsEx(&InitCtrls);

	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_WIN32);

	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_UPPER_LEFT);

	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;	
	wc.lpfnWndProc		= System_WndProc;						// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= GetModuleHandle(NULL);				// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= WINDOW_CLASSNAME;					// Set The Class Name
	wc.hbrBackground	= (HBRUSH)(COLOR_WINDOW);

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL, L"Failed to register the window class.\n", L"Error", MB_OK);
		return 0;
	}

	if (System_LoadGUIElements())
	{
		MessageBox(NULL, L"Failed to load interface.\n", L"Error", MB_OK);
		return 0;
	}

	SendMessage(g_win_system.gui_element[APP_QUALITY].hwnd, EM_SETREADONLY, FALSE, 0);

	ShowWindow(g_win_system.gui_element[APP_MAIN_WINDOW].hwnd, SW_SHOW);
	SetForegroundWindow(g_win_system.gui_element[APP_MAIN_WINDOW].hwnd);
	SetFocus(g_win_system.gui_element[APP_MAIN_WINDOW].hwnd);

	while ((is_quit = GetMessage(&msg, NULL, 0, 0)))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	DestroyWindow(g_win_system.gui_element[APP_MAIN_WINDOW].hwnd);
	UnregisterClass(WINDOW_CLASSNAME, GetModuleHandle(NULL));
	if (is_debug)
	{
		printf("\n\nDone.");
		_getch();
	}

	return 0;
}