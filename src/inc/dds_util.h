mat3x3f64_t DDS_BlockCovariance3D(double *pixel4x4_rgba, double *mean, double alpha_cutoff);
vec3f64_t DDS_BlockPrincipalEigenVector3D(mat3x3f64_t cvmat);
void DDS_UnpackTof64(uint32_t x, uint8_t r_bits, uint8_t g_bits, uint8_t b_bits, uint8_t a_bits, double *rgba);
uint32_t *DDS_BC6HMemberToP(bc6h_header_t *header, int member);
void DDS_GenBC3_4Alphau8(int mode, float *alpha, uint8_t alpha0, uint8_t alpha1);
void DDS_BlockCovariancePartition3DPreCalcMeanf32(int max_partitions, mat3x3f32_t *mat, float *pixel4x4_rgba, vec3f32_t *mean, bc6h7_shape_index_t *shape_index);
vec3f32_t DDS_BlockPrincipalEigenVector3Df32(mat3x3f32_t cvmat);
void DDS_BC6HQuantiseIntEndpoints(int num_partitions, int source_bits, int *target_bits, int *src_endpoint00, int *src_endpoint01, int *src_endpoint10, int *src_endpoint11, int *q_endpoint00, int *q_endpoint01, int *q_endpoint10, int *q_endpoint11);
void DDS_BC6HInvTransformNoWrap(int num_partitions, int endpoint00, int *endpoint01, int *endpoint10, int *endpoint11);
int DDS_BC6HGetAllowedSubMode(int mode, int *q_endpoint00, int *q_endpoint01, int *q_endpoint10, int *q_endpoint11, int is_transformed, int is_signed);
int F16_FinishQuantise(int x, int bits, int is_signed);
int F16_StartQuantise(int comp, int bits, int is_signed);
uint32_t MiniFloat_From32F(float x, uint8_t is_signed, uint8_t exponent_bits, uint8_t mantissa_bits, int clamp_to_range);
void DDS_WriteBits(uint8_t *block, uint32_t x, int start_bit, int num_bits);
void DDS_BC6H_FitPartition(
	int max_partitions, 
	int partition_id,
	bc6h7_shape_index_t *partition,
	int *tmodes,
	int num_tmodes,
	float *pixel4x4_rgba_half, 
	vec3f32_t *trans_pixel, 
	vec3f32_t *mean,
	int is_signed,
	int *partition_indexes,
	int *mode_endpoint_quant00,
	int *mode_endpoint_quant01,
	int *mode_endpoint_quant10,
	int *mode_endpoint_quant11,
	int *best_header_mode,
	float *err,
	int *is_flipped);

mat3x3f32_t DDS_BlockCovariance3Df32(float *pixel4x4_rgba, float *mean, float alpha_cutoff);
void DDS_UnpackTof32(uint32_t x, uint8_t r_bits, uint8_t g_bits, uint8_t b_bits, uint8_t a_bits, float *rgba);

int DDS_BresenhamPath16Bit(vec3u8_t path_quantised[64], vec3u8_t start_quantised, vec3u8_t end_quantised);
int DDS_BresenhamPath16BitVisitAll(vec3u8_t path_quantised[128], vec3u8_t start_quantised, vec3u8_t end_quantised);
vec3u8_t DDS_BresenhamPath16BitVisitLastSphere(vec3u8_t start_quantised, vec3u8_t end_quantised, int half_sphere_reverse_map[11*11*11][2]);
void DDS_RoundEndpointsToRGB565(vec3f32_t *colour);
int DDS_BresenhamPath16BitVisitAllClamp(vec3u8_t path_quantised[128], vec3f32_t start_quantisedf32, vec3f32_t end_quantisedf32);