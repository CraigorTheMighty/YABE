/*

For paper: 

#define DDS_DEBUG_BLOCK		((block_x == 160/4) && (block_y == 100/4))

result = ilLoadImage(L"E:\\Craig\\Programming\\New Stuff\\ImageCompressor\\x64\\Release\\256x144halfblurredgradient_constantgreen.bmp");

*/

//#define DDS_DEBUG_BLOCK		((block_x == 256/4) && (block_y == 44/4))
//#define DDS_DEBUG_BLOCK		((block_x == 308/4) && (block_y == 120/4))
//#define DDS_DEBUG_BLOCK		((block_x == 256/4) && (block_y == 44/4))
//#define DDS_DEBUG_BLOCK		((block_x == 260/4) && (block_y == 152/4))
//#define DDS_DEBUG_BLOCK		((block_x == 448/4) && (block_y == 140/4))
//#define DDS_DEBUG_BLOCK		((block_x == 268/4) && (block_y == 12/4))
/*
#define DDS_DEBUG_BLOCK		((block_x == 772/4) && (block_y == 428/4))
#define DDS_DEBUG_BLOCK		((block_x == 428/4) && (block_y == 640/4))
#define DDS_DEBUG_BLOCK		((block_x == 936/4) && (block_y == 488/4))
#define DDS_DEBUG_BLOCK		((block_x == 364/4) && (block_y == 236/4))
#define DDS_DEBUG_BLOCK		((block_x == 248/4) && (block_y == 640/4))
#define DDS_DEBUG_BLOCK		((block_x == 444/4) && (block_y == 476/4))
#define DDS_DEBUG_BLOCK		((block_x == 89) && (block_y == 37))
#define DDS_DEBUG_BLOCK		((block_x == 112/4) && (block_y == 80/4))
#define DDS_DEBUG_BLOCK		((block_x == 108/4) && (block_y == 64/4))
#define DDS_DEBUG_BLOCK		((block_x == 196/4) && (block_y == 28/4))
#define DDS_DEBUG_BLOCK		((block_x == 204/4) && (block_y == 40/4))
#define DDS_DEBUG_BLOCK		((block_x == 164/4) && (block_y == 40/4))
#define DDS_DEBUG_BLOCK		((block_x == 200/4) && (block_y == 32/4))
#define DDS_DEBUG_BLOCK		((block_x == 160/4) && (block_y == 100/4))


#define DDS_DEBUG_BLOCK		((block_x == 160/4) && (block_y == 84/4))
#define DDS_DEBUG_BLOCK		((block_x == 84/4) && (block_y == 32/4))
#define DDS_DEBUG_BLOCK		((block_x == 100/4) && (block_y == 8/4))
#define DDS_DEBUG_BLOCK		((block_x == 164/4) && (block_y == 32/4))
#define DDS_DEBUG_BLOCK		((block_x == 184/4) && (block_y == 32/4))
#define DDS_DEBUG_BLOCK		((block_x == 148/4) && (block_y == 12/4))

#define DDS_DEBUG_BLOCK		((block_x == 19) && (block_y == 15))
#define DDS_DEBUG_BLOCK		((block_x == 21) && (block_y == 8))
#define DDS_DEBUG_BLOCK		((block_x == 40/4) && (block_y == 112/4))*/
#define DDS_DEBUG_BLOCK		(0)

void DDS_EncodeBC1Block(uint8_t *block, double *pixel4x4_rgba, int is_premultiplied, int is_srgb, int is_signed, int block_x, int block_y, uint8_t alpha_cutoff, int is_bc23);
void DDS_EncodeBC2Block(uint8_t *block, double *pixel4x4_rgba, int is_premultiplied, int is_srgb, int is_signed, int block_x, int block_y);
void DDS_EncodeBC3Block(uint8_t *block, double *pixel4x4_rgba, int is_premultiplied, int is_srgb, int is_signed, int block_x, int block_y);
void DDS_EncodeBC4Block(uint8_t *block, double *pixel4x4_rgba, int is_premultiplied, int is_srgb, int is_signed, int block_x, int block_y);
void DDS_EncodeBC5Block(uint8_t *block, double *pixel4x4_rgba, int is_premultiplied, int is_srgb, int is_signed, int block_x, int block_y);
void DDS_EncodeBC6HBlockf32(uint8_t *block, double *pixel4x4_rgba, int is_premultiplied, int is_srgb, int is_signed, int block_x, int block_y);
void DDS_EncodeBC7Blockf32(uint8_t *block, double *pixel4x4_rgba, int is_premultiplied, int is_srgb, int is_signed, int block_x, int block_y);
int DDS_BlockSize(int format);

int EncodeDDSCPU(
    uint8_t **block, 
    float *pixel4x4_rgba, 
    int format,
    int width, 
    int height, 
    float alpha_cutoff);
int DDS_SaveDDS(char *output_name, int format);

void DDS_DecodeBC1Block(uint8_t *block, float *pixel4x4_rgba, int is_premultiplied, int is_srgb, int is_signed, int block_x, int block_y);
void DDS_DecodeBC2Block(uint8_t *block, float *pixel4x4_rgba, int is_premultiplied, int is_srgb, int is_signed, int block_x, int block_y);
void DDS_DecodeBC3Block(uint8_t *block, float *pixel4x4_rgba, int is_premultiplied, int is_srgb, int is_signed, int block_x, int block_y);
void DDS_DecodeBC4Block(uint8_t *block, float *pixel4x4_rgba, int is_premultiplied, int is_srgb, int is_signed, int block_x, int block_y);
void DDS_DecodeBC5Block(uint8_t *block, float *pixel4x4_rgba, int is_premultiplied, int is_srgb, int is_signed, int block_x, int block_y);

#define DDS_MAX_INIT_ERROR                  9999999999999999999999999999999999.0f

#define DDS_ENCODE_WALK_PATH            (1 << 0)    // expensive
#define DDS_ENCODE_EXTEND_ENDPOINTS     (1 << 1)    // only valid with DDS_ENCODE_WALK_PATH, potentially very expensive
#define DDS_ENCODE_REFINE_ENDPOINTS     (1 << 2)
#define DDS_ENCODE_TEST 			    (1 << 15)

#define DDS_QUALITY_FAST                (0) // this will always be faster than "normal"
#define DDS_QUALITY_NORMAL              (DDS_ENCODE_WALK_PATH) // this will always be faster than "high"
#define DDS_QUALITY_HIGH                (DDS_ENCODE_WALK_PATH | DDS_ENCODE_REFINE_ENDPOINTS)    // for images that are random noise, this mode tends to degenerate into "best"
#define DDS_QUALITY_BEST                (DDS_ENCODE_WALK_PATH | DDS_ENCODE_EXTEND_ENDPOINTS | DDS_ENCODE_REFINE_ENDPOINTS)
#define DDS_QUALITY_TEST                (DDS_ENCODE_WALK_PATH | DDS_ENCODE_EXTEND_ENDPOINTS | DDS_ENCODE_REFINE_ENDPOINTS | DDS_ENCODE_TEST)

void DDS_EncodeBC4Blockf32(int channel, uint8_t *block, float *pixel4x4_rgba, int is_premultiplied, int is_srgb, int is_signed, int block_x, int block_y);