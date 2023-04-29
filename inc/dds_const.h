#define BC6H_NUM_SUPERBLOCKS	10

#define BC3_4_ALPHA_ENCODE_FULL		0
#define BC3_4_ALPHA_ENCODE_0_255	1

/* TEMP REMOVE */
#define BC7ENC_MAX_PARTITIONS1 (64)
#define BC7ENC_MAX_UBER_LEVEL (4)

#define BC6H_MIN_ERROR		0.0
#define BC6H_EARLY_EXIT
#define BC6H_EARLY_COLOUR_EXIT
#define BC6H_ERROR_ESTIMATOR

enum
{
	BC6H_M,
	BC6H_D,
	BC6H_RW,
	BC6H_RX,
	BC6H_RY,
	BC6H_RZ,
	BC6H_GW,
	BC6H_GX,
	BC6H_GY,
	BC6H_GZ,
	BC6H_BW,
	BC6H_BX,
	BC6H_BY,
	BC6H_BZ,
	BC6H_XX,
};

typedef struct bc6h_desc_entry_s
{
	int member;
	int bit;
}bc6h_desc_entry_t;

typedef struct bc6h_desc_s
{
	uint32_t			mode;
	uint32_t			mode_bits;
	uint32_t			mode_group_base;
	uint32_t			mode_group_count;
	uint32_t			endpoint_bits[2][2][3];
	bc6h_desc_entry_t	entry[82];
}bc6h_desc_t;

typedef struct bc6h_header_s
{
	uint32_t	mode;
	uint32_t	real_mode;
	uint32_t	shape_index;
	int32_t		endpoint[2][2][3];
	uint32_t	is_transformed;
}bc6h_header_t;

typedef struct bc6h7_shape_index_s
{
	int index[16];
}bc6h7_shape_index_t;

typedef struct bc7_header_s
{
	uint32_t			mode;
	uint32_t			rotation;
	uint32_t			idx;
	uint32_t			shape_index;
	int32_t				endpoint[6][4];
	int32_t				p[6];
}bc7_header_t;

typedef struct bc7_desc_s
{
	uint32_t			index_bits[2];
	bc6h7_shape_index_t	*shape_subset;
	uint32_t			partition_bits;
	uint32_t			num_endpoints;
	uint32_t			num_p;
	uint32_t			has_rotation;
	uint32_t			has_idx;
	uint32_t			endpoint_bits[6][4];
	uint32_t			*fixup[2];
}bc7_desc_t;

typedef struct bc6h_superblock_desc_s
{
	uint32_t parent;
	uint32_t num_children;
	uint32_t children[3];
}bc6h_superblock_desc_t;

typedef struct bc6h7_partition_order_s
{
	int from_to[2];
}bc6h7_partition_order_t;

typedef struct bc6h7_partition_delta_s
{
	float set_a0_count;
	float set_a1_count;
	float set_b0_count;
	float set_b1_count;
	int num_diff;
	int diff[4];
}bc6h7_partition_delta_t;


extern uint32_t g_bc6h_fixup[32];
extern bc6h_superblock_desc_t g_bc6h_superblock_desc[BC6H_NUM_SUPERBLOCKS];
extern bc6h_desc_t g_bc6h_desc[14];
extern bc6h7_shape_index_t g_bc6h_shape_index[32];
extern int g_bc6h_weights3[8];
extern int g_bc6h_weights4[16];
extern uint32_t g_bc7_fixup2_1[64];
extern uint32_t g_bc7_fixup3_1[64];
extern uint32_t g_bc7_fixup3_2[64];
extern bc6h7_shape_index_t g_bc6h7_shape_index1[1];
extern bc6h7_shape_index_t g_bc7_shape_index2[64];
extern bc6h7_shape_index_t g_bc7_shape_index3[64];
extern bc6h7_partition_delta_t g_bc6h7_partition_delta[31];
extern bc6h7_partition_order_t g_bc6h_partition_order[31];
extern int g_bc7_weights2[4];
extern int g_bc7_weights3[8];
extern int g_bc7_weights4[16];
extern bc7_desc_t g_bc7_desc[8];