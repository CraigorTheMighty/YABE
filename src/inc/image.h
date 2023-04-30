typedef struct image_s
{
	int		dst_format;
	int		dst_block_size;
	int		num_mipmaps;
	int		*src_width;
	int		*src_height;
	float	**src_rgba_0_255; // num_mipmaps * src_width[i] * src_height[i]
	uint8_t	**dst_encoded;
}image_t;

void Image_GenMipMaps();

image_t Image_FromSysImage(sys_image_t *sys_image, int num_mipmap_levels, int encoded_format);
void Image_Destroy(image_t *image);
void Image_ExtractSubImageRGBAf32(float *dst, image_t *image, int mip_level, int width, int height, int x, int y);
void Image_CopyEncodedToImage(image_t *image, uint8_t *src, int mip_level, int width, int height, int x, int y);
int Image_GetRequiredBytes(int width, int height, int format);
image_t Image_Create(int width, int height, int mipmaps, int encoded_format);