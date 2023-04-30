#define ETC_QUALITY_FAST                (0) // this will always be faster than "normal"
#define ETC_QUALITY_NORMAL              (1) // this will always be faster than "high"
#define ETC_QUALITY_HIGH                (2) // for images that are random noise, this mode tends to degenerate into "best"
#define ETC_QUALITY_BEST                (3)

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
    float alpha_error_target);