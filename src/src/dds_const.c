#include <stdint.h>

#include "../inc/dds_const.h"

uint32_t g_bc6h_fixup[32] = 
{
	15, 15, 15, 15, 
	15, 15, 15, 15, 
	15, 15, 15, 15, 
	15, 15, 15, 15, 
	15,  2,  8,  2,
	2,  8,  8, 15,
	2,  8,  2,  2,
	8,  8,  2,  2,
};

bc6h_superblock_desc_t g_bc6h_superblock_desc[BC6H_NUM_SUPERBLOCKS] =
{
	{0, 2, {1, 2}},
	{3, 2, {5, 6}},
	{7, 2, {4, 8}},
	{10, 3, {9, 11, 12}},
	{13, 2, {14, 15}},
	{16, 3, {21, 23, 24}},
	{17, 2, {19, 20}},
	{18, 2, {22, 25}},
	{26, 2, {27, 31}},
	{29, 2, {28, 30}}
};

bc6h_desc_t g_bc6h_desc[14] = 
{
	{
		.mode = 0,
		.mode_bits = 2,
		.mode_group_count = 1,
		.mode_group_base = 0,
		.endpoint_bits = 
	{
		{
			{10, 10, 10},
	{ 5,  5,  5},
		},
			{
				{ 5,  5,  5},
	{ 5,  5,  5},
			},
},
.entry = 
	{
		{ BC6H_M, 0}, { BC6H_M, 1}, {BC6H_GY, 4}, {BC6H_BY, 4}, {BC6H_BZ, 4}, {BC6H_RW, 0}, {BC6H_RW, 1}, {BC6H_RW, 2}, {BC6H_RW, 3},
	{BC6H_RW, 4}, {BC6H_RW, 5}, {BC6H_RW, 6}, {BC6H_RW, 7}, {BC6H_RW, 8}, {BC6H_RW, 9}, {BC6H_GW, 0}, {BC6H_GW, 1}, {BC6H_GW, 2},
	{BC6H_GW, 3}, {BC6H_GW, 4}, {BC6H_GW, 5}, {BC6H_GW, 6}, {BC6H_GW, 7}, {BC6H_GW, 8}, {BC6H_GW, 9}, {BC6H_BW, 0}, {BC6H_BW, 1},
	{BC6H_BW, 2}, {BC6H_BW, 3}, {BC6H_BW, 4}, {BC6H_BW, 5}, {BC6H_BW, 6}, {BC6H_BW, 7}, {BC6H_BW, 8}, {BC6H_BW, 9}, {BC6H_RX, 0},
	{BC6H_RX, 1}, {BC6H_RX, 2}, {BC6H_RX, 3}, {BC6H_RX, 4}, {BC6H_GZ, 4}, {BC6H_GY, 0}, {BC6H_GY, 1}, {BC6H_GY, 2}, {BC6H_GY, 3},
	{BC6H_GX, 0}, {BC6H_GX, 1}, {BC6H_GX, 2}, {BC6H_GX, 3}, {BC6H_GX, 4}, {BC6H_BZ, 0}, {BC6H_GZ, 0}, {BC6H_GZ, 1}, {BC6H_GZ, 2},
	{BC6H_GZ, 3}, {BC6H_BX, 0}, {BC6H_BX, 1}, {BC6H_BX, 2}, {BC6H_BX, 3}, {BC6H_BX, 4}, {BC6H_BZ, 1}, {BC6H_BY, 0}, {BC6H_BY, 1},
	{BC6H_BY, 2}, {BC6H_BY, 3}, {BC6H_RY, 0}, {BC6H_RY, 1}, {BC6H_RY, 2}, {BC6H_RY, 3}, {BC6H_RY, 4}, {BC6H_BZ, 2}, {BC6H_RZ, 0},
	{BC6H_RZ, 1}, {BC6H_RZ, 2}, {BC6H_RZ, 3}, {BC6H_RZ, 4}, {BC6H_BZ, 3}, { BC6H_D, 0}, { BC6H_D, 1}, { BC6H_D, 2}, { BC6H_D, 3},
	{ BC6H_D, 4},
}
	},
	{
		.mode = 1,
		.mode_bits = 2,
		.mode_group_count = 1,
		.mode_group_base = 1,
		.endpoint_bits = 
	{
		{
			{ 7,  7,  7},
	{ 6,  6,  6},
		},
			{
				{ 6,  6,  6},
	{ 6,  6,  6},
			},
},
.entry = 
	{
		{ BC6H_M, 0}, { BC6H_M, 1}, {BC6H_GY, 5}, {BC6H_GZ, 4}, {BC6H_GZ, 5}, {BC6H_RW, 0}, {BC6H_RW, 1}, {BC6H_RW, 2}, {BC6H_RW, 3},
	{BC6H_RW, 4}, {BC6H_RW, 5}, {BC6H_RW, 6}, {BC6H_BZ, 0}, {BC6H_BZ, 1}, {BC6H_BY, 4}, {BC6H_GW, 0}, {BC6H_GW, 1}, {BC6H_GW, 2},
	{BC6H_GW, 3}, {BC6H_GW, 4}, {BC6H_GW, 5}, {BC6H_GW, 6}, {BC6H_BY, 5}, {BC6H_BZ, 2}, {BC6H_GY, 4}, {BC6H_BW, 0}, {BC6H_BW, 1},
	{BC6H_BW, 2}, {BC6H_BW, 3}, {BC6H_BW, 4}, {BC6H_BW, 5}, {BC6H_BW, 6}, {BC6H_BZ, 3}, {BC6H_BZ, 5}, {BC6H_BZ, 4}, {BC6H_RX, 0},
	{BC6H_RX, 1}, {BC6H_RX, 2}, {BC6H_RX, 3}, {BC6H_RX, 4}, {BC6H_RX, 5}, {BC6H_GY, 0}, {BC6H_GY, 1}, {BC6H_GY, 2}, {BC6H_GY, 3},
	{BC6H_GX, 0}, {BC6H_GX, 1}, {BC6H_GX, 2}, {BC6H_GX, 3}, {BC6H_GX, 4}, {BC6H_GX, 5}, {BC6H_GZ, 0}, {BC6H_GZ, 1}, {BC6H_GZ, 2},
	{BC6H_GZ, 3}, {BC6H_BX, 0}, {BC6H_BX, 1}, {BC6H_BX, 2}, {BC6H_BX, 3}, {BC6H_BX, 4}, {BC6H_BX, 5}, {BC6H_BY, 0}, {BC6H_BY, 1},
	{BC6H_BY, 2}, {BC6H_BY, 3}, {BC6H_RY, 0}, {BC6H_RY, 1}, {BC6H_RY, 2}, {BC6H_RY, 3}, {BC6H_RY, 4}, {BC6H_RY, 5}, {BC6H_RZ, 0},
	{BC6H_RZ, 1}, {BC6H_RZ, 2}, {BC6H_RZ, 3}, {BC6H_RZ, 4}, {BC6H_RZ, 5}, { BC6H_D, 0}, { BC6H_D, 1}, { BC6H_D, 2}, { BC6H_D, 3},
	{ BC6H_D, 4},
}
	},
	{
		.mode = 2,
		.mode_bits = 5,
		.mode_group_count = 3,
		.mode_group_base = 2,
		.endpoint_bits = 
	{
		{
			{11, 11, 11},
	{ 5,  4,  4},
		},
			{
				{ 5,  4,  4},
	{ 5,  4,  4},
			},
},
.entry = 
	{
		{ BC6H_M, 0}, { BC6H_M, 1}, { BC6H_M, 2}, { BC6H_M, 3}, { BC6H_M, 4}, {BC6H_RW, 0}, {BC6H_RW, 1}, {BC6H_RW, 2}, {BC6H_RW, 3},
	{BC6H_RW, 4}, {BC6H_RW, 5}, {BC6H_RW, 6}, {BC6H_RW, 7}, {BC6H_RW, 8}, {BC6H_RW, 9}, {BC6H_GW, 0}, {BC6H_GW, 1}, {BC6H_GW, 2},
	{BC6H_GW, 3}, {BC6H_GW, 4}, {BC6H_GW, 5}, {BC6H_GW, 6}, {BC6H_GW, 7}, {BC6H_GW, 8}, {BC6H_GW, 9}, {BC6H_BW, 0}, {BC6H_BW, 1},
	{BC6H_BW, 2}, {BC6H_BW, 3}, {BC6H_BW, 4}, {BC6H_BW, 5}, {BC6H_BW, 6}, {BC6H_BW, 7}, {BC6H_BW, 8}, {BC6H_BW, 9}, {BC6H_RX, 0},
	{BC6H_RX, 1}, {BC6H_RX, 2}, {BC6H_RX, 3}, {BC6H_RX, 4}, {BC6H_RW,10}, {BC6H_GY, 0}, {BC6H_GY, 1}, {BC6H_GY, 2}, {BC6H_GY, 3},
	{BC6H_GX, 0}, {BC6H_GX, 1}, {BC6H_GX, 2}, {BC6H_GX, 3}, {BC6H_GW,10}, {BC6H_BZ, 0}, {BC6H_GZ, 0}, {BC6H_GZ, 1}, {BC6H_GZ, 2},
	{BC6H_GZ, 3}, {BC6H_BX, 0}, {BC6H_BX, 1}, {BC6H_BX, 2}, {BC6H_BX, 3}, {BC6H_BW,10}, {BC6H_BZ, 1}, {BC6H_BY, 0}, {BC6H_BY, 1},
	{BC6H_BY, 2}, {BC6H_BY, 3}, {BC6H_RY, 0}, {BC6H_RY, 1}, {BC6H_RY, 2}, {BC6H_RY, 3}, {BC6H_RY, 4}, {BC6H_BZ, 2}, {BC6H_RZ, 0},
	{BC6H_RZ, 1}, {BC6H_RZ, 2}, {BC6H_RZ, 3}, {BC6H_RZ, 4}, {BC6H_BZ, 3}, { BC6H_D, 0}, { BC6H_D, 1}, { BC6H_D, 2}, { BC6H_D, 3},
	{ BC6H_D, 4},
}
	},
	{
		.mode = 6,
		.mode_bits = 5,
		.mode_group_count = 3,
		.mode_group_base = 2,
		.endpoint_bits = 
	{
		{
			{11, 11, 11},
	{ 4,  5,  4},
		},
			{
				{ 4,  5,  4},
	{ 4,  5,  4},
			},
},
.entry = 
	{
		{ BC6H_M, 0}, { BC6H_M, 1}, { BC6H_M, 2}, { BC6H_M, 3}, { BC6H_M, 4}, {BC6H_RW, 0}, {BC6H_RW, 1}, {BC6H_RW, 2}, {BC6H_RW, 3},
	{BC6H_RW, 4}, {BC6H_RW, 5}, {BC6H_RW, 6}, {BC6H_RW, 7}, {BC6H_RW, 8}, {BC6H_RW, 9}, {BC6H_GW, 0}, {BC6H_GW, 1}, {BC6H_GW, 2},
	{BC6H_GW, 3}, {BC6H_GW, 4}, {BC6H_GW, 5}, {BC6H_GW, 6}, {BC6H_GW, 7}, {BC6H_GW, 8}, {BC6H_GW, 9}, {BC6H_BW, 0}, {BC6H_BW, 1},
	{BC6H_BW, 2}, {BC6H_BW, 3}, {BC6H_BW, 4}, {BC6H_BW, 5}, {BC6H_BW, 6}, {BC6H_BW, 7}, {BC6H_BW, 8}, {BC6H_BW, 9}, {BC6H_RX, 0},
	{BC6H_RX, 1}, {BC6H_RX, 2}, {BC6H_RX, 3}, {BC6H_RW,10}, {BC6H_GZ, 4}, {BC6H_GY, 0}, {BC6H_GY, 1}, {BC6H_GY, 2}, {BC6H_GY, 3},
	{BC6H_GX, 0}, {BC6H_GX, 1}, {BC6H_GX, 2}, {BC6H_GX, 3}, {BC6H_GX, 4}, {BC6H_GW,10}, {BC6H_GZ, 0}, {BC6H_GZ, 1}, {BC6H_GZ, 2},
	{BC6H_GZ, 3}, {BC6H_BX, 0}, {BC6H_BX, 1}, {BC6H_BX, 2}, {BC6H_BX, 3}, {BC6H_BW,10}, {BC6H_BZ, 1}, {BC6H_BY, 0}, {BC6H_BY, 1},
	{BC6H_BY, 2}, {BC6H_BY, 3}, {BC6H_RY, 0}, {BC6H_RY, 1}, {BC6H_RY, 2}, {BC6H_RY, 3}, {BC6H_BZ, 0}, {BC6H_BZ, 2}, {BC6H_RZ, 0},
	{BC6H_RZ, 1}, {BC6H_RZ, 2}, {BC6H_RZ, 3}, {BC6H_GY, 4}, {BC6H_BZ, 3}, { BC6H_D, 0}, { BC6H_D, 1}, { BC6H_D, 2}, { BC6H_D, 3},
	{ BC6H_D, 4},
}
	},
	{
		.mode = 10,
		.mode_bits = 5,
		.mode_group_count = 3,
		.mode_group_base = 2,
		.endpoint_bits = 
	{
		{
			{11, 11, 11},
	{ 4,  4,  5},
		},
			{
				{ 4,  4,  5},
	{ 4,  4,  5},
			},
},
.entry = 
	{
		{ BC6H_M, 0}, { BC6H_M, 1}, { BC6H_M, 2}, { BC6H_M, 3}, { BC6H_M, 4}, {BC6H_RW, 0}, {BC6H_RW, 1}, {BC6H_RW, 2}, {BC6H_RW, 3},
	{BC6H_RW, 4}, {BC6H_RW, 5}, {BC6H_RW, 6}, {BC6H_RW, 7}, {BC6H_RW, 8}, {BC6H_RW, 9}, {BC6H_GW, 0}, {BC6H_GW, 1}, {BC6H_GW, 2},
	{BC6H_GW, 3}, {BC6H_GW, 4}, {BC6H_GW, 5}, {BC6H_GW, 6}, {BC6H_GW, 7}, {BC6H_GW, 8}, {BC6H_GW, 9}, {BC6H_BW, 0}, {BC6H_BW, 1},
	{BC6H_BW, 2}, {BC6H_BW, 3}, {BC6H_BW, 4}, {BC6H_BW, 5}, {BC6H_BW, 6}, {BC6H_BW, 7}, {BC6H_BW, 8}, {BC6H_BW, 9}, {BC6H_RX, 0},
	{BC6H_RX, 1}, {BC6H_RX, 2}, {BC6H_RX, 3}, {BC6H_RW,10}, {BC6H_BY, 4}, {BC6H_GY, 0}, {BC6H_GY, 1}, {BC6H_GY, 2}, {BC6H_GY, 3},
	{BC6H_GX, 0}, {BC6H_GX, 1}, {BC6H_GX, 2}, {BC6H_GX, 3}, {BC6H_GW,10}, {BC6H_BZ, 0}, {BC6H_GZ, 0}, {BC6H_GZ, 1}, {BC6H_GZ, 2},
	{BC6H_GZ, 3}, {BC6H_BX, 0}, {BC6H_BX, 1}, {BC6H_BX, 2}, {BC6H_BX, 3}, {BC6H_BX, 4}, {BC6H_BW,10}, {BC6H_BY, 0}, {BC6H_BY, 1},
	{BC6H_BY, 2}, {BC6H_BY, 3}, {BC6H_RY, 0}, {BC6H_RY, 1}, {BC6H_RY, 2}, {BC6H_RY, 3}, {BC6H_BZ, 1}, {BC6H_BZ, 2}, {BC6H_RZ, 0},
	{BC6H_RZ, 1}, {BC6H_RZ, 2}, {BC6H_RZ, 3}, {BC6H_BZ, 4}, {BC6H_BZ, 3}, { BC6H_D, 0}, { BC6H_D, 1}, { BC6H_D, 2}, { BC6H_D, 3},
	{ BC6H_D, 4},
}
	},
	{
		.mode = 14,
		.mode_bits = 5,
		.mode_group_count = 1,
		.mode_group_base = 5,
		.endpoint_bits = 
	{
		{
			{ 9,  9,  9},
	{ 5,  5,  5},
		},
			{
				{ 5,  5,  5},
	{ 5,  5,  5},
			},
},
.entry = 
	{
		{ BC6H_M, 0}, { BC6H_M, 1}, { BC6H_M, 2}, { BC6H_M, 3}, { BC6H_M, 4}, {BC6H_RW, 0}, {BC6H_RW, 1}, {BC6H_RW, 2}, {BC6H_RW, 3},
	{BC6H_RW, 4}, {BC6H_RW, 5}, {BC6H_RW, 6}, {BC6H_RW, 7}, {BC6H_RW, 8}, {BC6H_BY, 4}, {BC6H_GW, 0}, {BC6H_GW, 1}, {BC6H_GW, 2},
	{BC6H_GW, 3}, {BC6H_GW, 4}, {BC6H_GW, 5}, {BC6H_GW, 6}, {BC6H_GW, 7}, {BC6H_GW, 8}, {BC6H_GY, 4}, {BC6H_BW, 0}, {BC6H_BW, 1},
	{BC6H_BW, 2}, {BC6H_BW, 3}, {BC6H_BW, 4}, {BC6H_BW, 5}, {BC6H_BW, 6}, {BC6H_BW, 7}, {BC6H_BW, 8}, {BC6H_BZ, 4}, {BC6H_RX, 0},
	{BC6H_RX, 1}, {BC6H_RX, 2}, {BC6H_RX, 3}, {BC6H_RX, 4}, {BC6H_GZ, 4}, {BC6H_GY, 0}, {BC6H_GY, 1}, {BC6H_GY, 2}, {BC6H_GY, 3},
	{BC6H_GX, 0}, {BC6H_GX, 1}, {BC6H_GX, 2}, {BC6H_GX, 3}, {BC6H_GX, 4}, {BC6H_BZ, 0}, {BC6H_GZ, 0}, {BC6H_GZ, 1}, {BC6H_GZ, 2},
	{BC6H_GZ, 3}, {BC6H_BX, 0}, {BC6H_BX, 1}, {BC6H_BX, 2}, {BC6H_BX, 3}, {BC6H_BX, 4}, {BC6H_BZ, 1}, {BC6H_BY, 0}, {BC6H_BY, 1},
	{BC6H_BY, 2}, {BC6H_BY, 3}, {BC6H_RY, 0}, {BC6H_RY, 1}, {BC6H_RY, 2}, {BC6H_RY, 3}, {BC6H_RY, 4}, {BC6H_BZ, 2}, {BC6H_RZ, 0},
	{BC6H_RZ, 1}, {BC6H_RZ, 2}, {BC6H_RZ, 3}, {BC6H_RZ, 4}, {BC6H_BZ, 3}, { BC6H_D, 0}, { BC6H_D, 1}, { BC6H_D, 2}, { BC6H_D, 3},
	{ BC6H_D, 4},
}
	},
	{
		.mode = 18,
		.mode_bits = 5,
		.mode_group_count = 3,
		.mode_group_base = 6,
		.endpoint_bits = 
	{
		{
			{ 8,  8,  8},
	{ 6,  5,  5},
		},
			{
				{ 6,  5,  5},
	{ 6,  5,  5},
			},
},
.entry = 
	{
		{ BC6H_M, 0}, { BC6H_M, 1}, { BC6H_M, 2}, { BC6H_M, 3}, { BC6H_M, 4}, {BC6H_RW, 0}, {BC6H_RW, 1}, {BC6H_RW, 2}, {BC6H_RW, 3},
	{BC6H_RW, 4}, {BC6H_RW, 5}, {BC6H_RW, 6}, {BC6H_RW, 7}, {BC6H_GZ, 4}, {BC6H_BY, 4}, {BC6H_GW, 0}, {BC6H_GW, 1}, {BC6H_GW, 2},
	{BC6H_GW, 3}, {BC6H_GW, 4}, {BC6H_GW, 5}, {BC6H_GW, 6}, {BC6H_GW, 7}, {BC6H_BZ, 2}, {BC6H_GY, 4}, {BC6H_BW, 0}, {BC6H_BW, 1},
	{BC6H_BW, 2}, {BC6H_BW, 3}, {BC6H_BW, 4}, {BC6H_BW, 5}, {BC6H_BW, 6}, {BC6H_BW, 7}, {BC6H_BZ, 3}, {BC6H_BZ, 4}, {BC6H_RX, 0},
	{BC6H_RX, 1}, {BC6H_RX, 2}, {BC6H_RX, 3}, {BC6H_RX, 4}, {BC6H_RX, 5}, {BC6H_GY, 0}, {BC6H_GY, 1}, {BC6H_GY, 2}, {BC6H_GY, 3},
	{BC6H_GX, 0}, {BC6H_GX, 1}, {BC6H_GX, 2}, {BC6H_GX, 3}, {BC6H_GX, 4}, {BC6H_BZ, 0}, {BC6H_GZ, 0}, {BC6H_GZ, 1}, {BC6H_GZ, 2},
	{BC6H_GZ, 3}, {BC6H_BX, 0}, {BC6H_BX, 1}, {BC6H_BX, 2}, {BC6H_BX, 3}, {BC6H_BX, 4}, {BC6H_BZ, 1}, {BC6H_BY, 0}, {BC6H_BY, 1},
	{BC6H_BY, 2}, {BC6H_BY, 3}, {BC6H_RY, 0}, {BC6H_RY, 1}, {BC6H_RY, 2}, {BC6H_RY, 3}, {BC6H_RY, 4}, {BC6H_RY, 5}, {BC6H_RZ, 0},
	{BC6H_RZ, 1}, {BC6H_RZ, 2}, {BC6H_RZ, 3}, {BC6H_RZ, 4}, {BC6H_RZ, 5}, { BC6H_D, 0}, { BC6H_D, 1}, { BC6H_D, 2}, { BC6H_D, 3},
	{ BC6H_D, 4},
}
	},
	{
		.mode = 22,
		.mode_bits = 5,
		.mode_group_count = 3,
		.mode_group_base = 6,
		.endpoint_bits = 
	{
		{
			{ 8,  8,  8},
	{ 5,  6,  5},
		},
			{
				{ 5,  6,  5},
	{ 5,  6,  5},
			},
},
.entry = 
	{
		{ BC6H_M, 0}, { BC6H_M, 1}, { BC6H_M, 2}, { BC6H_M, 3}, { BC6H_M, 4}, {BC6H_RW, 0}, {BC6H_RW, 1}, {BC6H_RW, 2}, {BC6H_RW, 3},
	{BC6H_RW, 4}, {BC6H_RW, 5}, {BC6H_RW, 6}, {BC6H_RW, 7}, {BC6H_BZ, 0}, {BC6H_BY, 4}, {BC6H_GW, 0}, {BC6H_GW, 1}, {BC6H_GW, 2},
	{BC6H_GW, 3}, {BC6H_GW, 4}, {BC6H_GW, 5}, {BC6H_GW, 6}, {BC6H_GW, 7}, {BC6H_GY, 5}, {BC6H_GY, 4}, {BC6H_BW, 0}, {BC6H_BW, 1},
	{BC6H_BW, 2}, {BC6H_BW, 3}, {BC6H_BW, 4}, {BC6H_BW, 5}, {BC6H_BW, 6}, {BC6H_BW, 7}, {BC6H_GZ, 5}, {BC6H_BZ, 4}, {BC6H_RX, 0},
	{BC6H_RX, 1}, {BC6H_RX, 2}, {BC6H_RX, 3}, {BC6H_RX, 4}, {BC6H_GZ, 4}, {BC6H_GY, 0}, {BC6H_GY, 1}, {BC6H_GY, 2}, {BC6H_GY, 3},
	{BC6H_GX, 0}, {BC6H_GX, 1}, {BC6H_GX, 2}, {BC6H_GX, 3}, {BC6H_GX, 4}, {BC6H_GX, 5}, {BC6H_GZ, 0}, {BC6H_GZ, 1}, {BC6H_GZ, 2},
	{BC6H_GZ, 3}, {BC6H_BX, 0}, {BC6H_BX, 1}, {BC6H_BX, 2}, {BC6H_BX, 3}, {BC6H_BX, 4}, {BC6H_BZ, 1}, {BC6H_BY, 0}, {BC6H_BY, 1},
	{BC6H_BY, 2}, {BC6H_BY, 3}, {BC6H_RY, 0}, {BC6H_RY, 1}, {BC6H_RY, 2}, {BC6H_RY, 3}, {BC6H_RY, 4}, {BC6H_BZ, 2}, {BC6H_RZ, 0},
	{BC6H_RZ, 1}, {BC6H_RZ, 2}, {BC6H_RZ, 3}, {BC6H_RZ, 4}, {BC6H_BZ, 3}, { BC6H_D, 0}, { BC6H_D, 1}, { BC6H_D, 2}, { BC6H_D, 3},
	{ BC6H_D, 4},
}
	},
	{
		.mode = 26,
		.mode_bits = 5,
		.mode_group_count = 3,
		.mode_group_base = 6,
		.endpoint_bits = 
	{
		{
			{ 8,  8,  8},
	{ 5,  5,  6},
		},
			{
				{ 5,  5,  6},
	{ 5,  5,  6},
			},
},
.entry = 
	{
		{ BC6H_M, 0}, { BC6H_M, 1}, { BC6H_M, 2}, { BC6H_M, 3}, { BC6H_M, 4}, {BC6H_RW, 0}, {BC6H_RW, 1}, {BC6H_RW, 2}, {BC6H_RW, 3},
	{BC6H_RW, 4}, {BC6H_RW, 5}, {BC6H_RW, 6}, {BC6H_RW, 7}, {BC6H_BZ, 1}, {BC6H_BY, 4}, {BC6H_GW, 0}, {BC6H_GW, 1}, {BC6H_GW, 2},
	{BC6H_GW, 3}, {BC6H_GW, 4}, {BC6H_GW, 5}, {BC6H_GW, 6}, {BC6H_GW, 7}, {BC6H_BY, 5}, {BC6H_GY, 4}, {BC6H_BW, 0}, {BC6H_BW, 1},
	{BC6H_BW, 2}, {BC6H_BW, 3}, {BC6H_BW, 4}, {BC6H_BW, 5}, {BC6H_BW, 6}, {BC6H_BW, 7}, {BC6H_BZ, 5}, {BC6H_BZ, 4}, {BC6H_RX, 0},
	{BC6H_RX, 1}, {BC6H_RX, 2}, {BC6H_RX, 3}, {BC6H_RX, 4}, {BC6H_GZ, 4}, {BC6H_GY, 0}, {BC6H_GY, 1}, {BC6H_GY, 2}, {BC6H_GY, 3},
	{BC6H_GX, 0}, {BC6H_GX, 1}, {BC6H_GX, 2}, {BC6H_GX, 3}, {BC6H_GX, 4}, {BC6H_BZ, 0}, {BC6H_GZ, 0}, {BC6H_GZ, 1}, {BC6H_GZ, 2},
	{BC6H_GZ, 3}, {BC6H_BX, 0}, {BC6H_BX, 1}, {BC6H_BX, 2}, {BC6H_BX, 3}, {BC6H_BX, 4}, {BC6H_BX, 5}, {BC6H_BY, 0}, {BC6H_BY, 1},
	{BC6H_BY, 2}, {BC6H_BY, 3}, {BC6H_RY, 0}, {BC6H_RY, 1}, {BC6H_RY, 2}, {BC6H_RY, 3}, {BC6H_RY, 4}, {BC6H_BZ, 2}, {BC6H_RZ, 0},
	{BC6H_RZ, 1}, {BC6H_RZ, 2}, {BC6H_RZ, 3}, {BC6H_RZ, 4}, {BC6H_BZ, 3}, { BC6H_D, 0}, { BC6H_D, 1}, { BC6H_D, 2}, { BC6H_D, 3},
	{ BC6H_D, 4},
}
	},
	{
		.mode = 30,
		.mode_bits = 5,
		.mode_group_count = 1,
		.mode_group_base = 9,
		.endpoint_bits = 
	{
		{
			{ 6,  6,  6},
	{ 6,  6,  6},
		},
			{
				{ 6,  6,  6},
	{ 6,  6,  6},
			},
},
.entry = 
	{
		{ BC6H_M, 0}, { BC6H_M, 1}, { BC6H_M, 2}, { BC6H_M, 3}, { BC6H_M, 4}, {BC6H_RW, 0}, {BC6H_RW, 1}, {BC6H_RW, 2}, {BC6H_RW, 3},
	{BC6H_RW, 4}, {BC6H_RW, 5}, {BC6H_GZ, 4}, {BC6H_BZ, 0}, {BC6H_BZ, 1}, {BC6H_BY, 4}, {BC6H_GW, 0}, {BC6H_GW, 1}, {BC6H_GW, 2},
	{BC6H_GW, 3}, {BC6H_GW, 4}, {BC6H_GW, 5}, {BC6H_GY, 5}, {BC6H_BY, 5}, {BC6H_BZ, 2}, {BC6H_GY, 4}, {BC6H_BW, 0}, {BC6H_BW, 1},
	{BC6H_BW, 2}, {BC6H_BW, 3}, {BC6H_BW, 4}, {BC6H_BW, 5}, {BC6H_GZ, 5}, {BC6H_BZ, 3}, {BC6H_BZ, 5}, {BC6H_BZ, 4}, {BC6H_RX, 0},
	{BC6H_RX, 1}, {BC6H_RX, 2}, {BC6H_RX, 3}, {BC6H_RX, 4}, {BC6H_RX, 5}, {BC6H_GY, 0}, {BC6H_GY, 1}, {BC6H_GY, 2}, {BC6H_GY, 3},
	{BC6H_GX, 0}, {BC6H_GX, 1}, {BC6H_GX, 2}, {BC6H_GX, 3}, {BC6H_GX, 4}, {BC6H_GX, 5}, {BC6H_GZ, 0}, {BC6H_GZ, 1}, {BC6H_GZ, 2},
	{BC6H_GZ, 3}, {BC6H_BX, 0}, {BC6H_BX, 1}, {BC6H_BX, 2}, {BC6H_BX, 3}, {BC6H_BX, 4}, {BC6H_BX, 5}, {BC6H_BY, 0}, {BC6H_BY, 1},
	{BC6H_BY, 2}, {BC6H_BY, 3}, {BC6H_RY, 0}, {BC6H_RY, 1}, {BC6H_RY, 2}, {BC6H_RY, 3}, {BC6H_RY, 4}, {BC6H_RY, 5}, {BC6H_RZ, 0},
	{BC6H_RZ, 1}, {BC6H_RZ, 2}, {BC6H_RZ, 3}, {BC6H_RZ, 4}, {BC6H_RZ, 5}, { BC6H_D, 0}, { BC6H_D, 1}, { BC6H_D, 2}, { BC6H_D, 3},
	{ BC6H_D, 4},
}
	},
	{
		.mode = 3,
		.mode_bits = 5,
		.mode_group_count = 1,
		.mode_group_base = 10,
		.endpoint_bits = 
	{
		{
			{10, 10, 10},
	{10, 10, 10},
		},
},
.entry = 
	{
		{ BC6H_M, 0}, { BC6H_M, 1}, { BC6H_M, 2}, { BC6H_M, 3}, { BC6H_M, 4}, {BC6H_RW, 0}, {BC6H_RW, 1}, {BC6H_RW, 2}, {BC6H_RW, 3},
	{BC6H_RW, 4}, {BC6H_RW, 5}, {BC6H_RW, 6}, {BC6H_RW, 7}, {BC6H_RW, 8}, {BC6H_RW, 9}, {BC6H_GW, 0}, {BC6H_GW, 1}, {BC6H_GW, 2},
	{BC6H_GW, 3}, {BC6H_GW, 4}, {BC6H_GW, 5}, {BC6H_GW, 6}, {BC6H_GW, 7}, {BC6H_GW, 8}, {BC6H_GW, 9}, {BC6H_BW, 0}, {BC6H_BW, 1},
	{BC6H_BW, 2}, {BC6H_BW, 3}, {BC6H_BW, 4}, {BC6H_BW, 5}, {BC6H_BW, 6}, {BC6H_BW, 7}, {BC6H_BW, 8}, {BC6H_BW, 9}, {BC6H_RX, 0},
	{BC6H_RX, 1}, {BC6H_RX, 2}, {BC6H_RX, 3}, {BC6H_RX, 4}, {BC6H_RX, 5}, {BC6H_RX, 6}, {BC6H_RX, 7}, {BC6H_RX, 8}, {BC6H_RX, 9},
	{BC6H_GX, 0}, {BC6H_GX, 1}, {BC6H_GX, 2}, {BC6H_GX, 3}, {BC6H_GX, 4}, {BC6H_GX, 5}, {BC6H_GX, 6}, {BC6H_GX, 7}, {BC6H_GX, 8},
	{BC6H_GX, 9}, {BC6H_BX, 0}, {BC6H_BX, 1}, {BC6H_BX, 2}, {BC6H_BX, 3}, {BC6H_BX, 4}, {BC6H_BX, 5}, {BC6H_BX, 6}, {BC6H_BX, 7},
	{BC6H_BX, 8}, {BC6H_BX, 9}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0},
	{BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0},
	{BC6H_XX, 0},
}
	},
	{
		.mode = 7,
		.mode_bits = 5,
		.mode_group_count = 3,
		.mode_group_base = 11,
		.endpoint_bits = 
	{
		{
			{11, 11, 11},
	{ 9,  9,  9},
		},
},
.entry = 
	{
		{ BC6H_M, 0}, { BC6H_M, 1}, { BC6H_M, 2}, { BC6H_M, 3}, { BC6H_M, 4}, {BC6H_RW, 0}, {BC6H_RW, 1}, {BC6H_RW, 2}, {BC6H_RW, 3},
	{BC6H_RW, 4}, {BC6H_RW, 5}, {BC6H_RW, 6}, {BC6H_RW, 7}, {BC6H_RW, 8}, {BC6H_RW, 9}, {BC6H_GW, 0}, {BC6H_GW, 1}, {BC6H_GW, 2},
	{BC6H_GW, 3}, {BC6H_GW, 4}, {BC6H_GW, 5}, {BC6H_GW, 6}, {BC6H_GW, 7}, {BC6H_GW, 8}, {BC6H_GW, 9}, {BC6H_BW, 0}, {BC6H_BW, 1},
	{BC6H_BW, 2}, {BC6H_BW, 3}, {BC6H_BW, 4}, {BC6H_BW, 5}, {BC6H_BW, 6}, {BC6H_BW, 7}, {BC6H_BW, 8}, {BC6H_BW, 9}, {BC6H_RX, 0},
	{BC6H_RX, 1}, {BC6H_RX, 2}, {BC6H_RX, 3}, {BC6H_RX, 4}, {BC6H_RX, 5}, {BC6H_RX, 6}, {BC6H_RX, 7}, {BC6H_RX, 8}, {BC6H_RW,10},
	{BC6H_GX, 0}, {BC6H_GX, 1}, {BC6H_GX, 2}, {BC6H_GX, 3}, {BC6H_GX, 4}, {BC6H_GX, 5}, {BC6H_GX, 6}, {BC6H_GX, 7}, {BC6H_GX, 8},
	{BC6H_GW,10}, {BC6H_BX, 0}, {BC6H_BX, 1}, {BC6H_BX, 2}, {BC6H_BX, 3}, {BC6H_BX, 4}, {BC6H_BX, 5}, {BC6H_BX, 6}, {BC6H_BX, 7},
	{BC6H_BX, 8}, {BC6H_BW,10}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0},
	{BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0},
	{BC6H_XX, 0},
}
	},
	{
		.mode = 11,
		.mode_bits = 5,
		.mode_group_count = 3,
		.mode_group_base = 11,
		.endpoint_bits = 
	{
		{
			{12, 12, 12},
	{ 8,  8,  8},
		},
},
.entry = 
	{
		{ BC6H_M, 0}, { BC6H_M, 1}, { BC6H_M, 2}, { BC6H_M, 3}, { BC6H_M, 4}, {BC6H_RW, 0}, {BC6H_RW, 1}, {BC6H_RW, 2}, {BC6H_RW, 3},
	{BC6H_RW, 4}, {BC6H_RW, 5}, {BC6H_RW, 6}, {BC6H_RW, 7}, {BC6H_RW, 8}, {BC6H_RW, 9}, {BC6H_GW, 0}, {BC6H_GW, 1}, {BC6H_GW, 2},
	{BC6H_GW, 3}, {BC6H_GW, 4}, {BC6H_GW, 5}, {BC6H_GW, 6}, {BC6H_GW, 7}, {BC6H_GW, 8}, {BC6H_GW, 9}, {BC6H_BW, 0}, {BC6H_BW, 1},
	{BC6H_BW, 2}, {BC6H_BW, 3}, {BC6H_BW, 4}, {BC6H_BW, 5}, {BC6H_BW, 6}, {BC6H_BW, 7}, {BC6H_BW, 8}, {BC6H_BW, 9}, {BC6H_RX, 0},
	{BC6H_RX, 1}, {BC6H_RX, 2}, {BC6H_RX, 3}, {BC6H_RX, 4}, {BC6H_RX, 5}, {BC6H_RX, 6}, {BC6H_RX, 7}, {BC6H_RW,11}, {BC6H_RW,10},
	{BC6H_GX, 0}, {BC6H_GX, 1}, {BC6H_GX, 2}, {BC6H_GX, 3}, {BC6H_GX, 4}, {BC6H_GX, 5}, {BC6H_GX, 6}, {BC6H_GX, 7}, {BC6H_GW,11},
	{BC6H_GW,10}, {BC6H_BX, 0}, {BC6H_BX, 1}, {BC6H_BX, 2}, {BC6H_BX, 3}, {BC6H_BX, 4}, {BC6H_BX, 5}, {BC6H_BX, 6}, {BC6H_BX, 7},
	{BC6H_BW,11}, {BC6H_BW,10}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0},
	{BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0},
	{BC6H_XX, 0},
}
	},
	{
		.mode = 15,
		.mode_bits = 5,
		.mode_group_count = 3,
		.mode_group_base = 11,
		.endpoint_bits = 
	{
		{
			{16, 16, 16},
	{ 4,  4,  4},
		},
},
.entry = 
	{
		{ BC6H_M, 0}, { BC6H_M, 1}, { BC6H_M, 2}, { BC6H_M, 3}, { BC6H_M, 4}, {BC6H_RW, 0}, {BC6H_RW, 1}, {BC6H_RW, 2}, {BC6H_RW, 3},
	{BC6H_RW, 4}, {BC6H_RW, 5}, {BC6H_RW, 6}, {BC6H_RW, 7}, {BC6H_RW, 8}, {BC6H_RW, 9}, {BC6H_GW, 0}, {BC6H_GW, 1}, {BC6H_GW, 2},
	{BC6H_GW, 3}, {BC6H_GW, 4}, {BC6H_GW, 5}, {BC6H_GW, 6}, {BC6H_GW, 7}, {BC6H_GW, 8}, {BC6H_GW, 9}, {BC6H_BW, 0}, {BC6H_BW, 1},
	{BC6H_BW, 2}, {BC6H_BW, 3}, {BC6H_BW, 4}, {BC6H_BW, 5}, {BC6H_BW, 6}, {BC6H_BW, 7}, {BC6H_BW, 8}, {BC6H_BW, 9}, {BC6H_RX, 0},
	{BC6H_RX, 1}, {BC6H_RX, 2}, {BC6H_RX, 3}, {BC6H_RW,15}, {BC6H_RW,14}, {BC6H_RW,13}, {BC6H_RW,12}, {BC6H_RW,11}, {BC6H_RW,10},
	{BC6H_GX, 0}, {BC6H_GX, 1}, {BC6H_GX, 2}, {BC6H_GX, 3}, {BC6H_GW,15}, {BC6H_GW,14}, {BC6H_GW,13}, {BC6H_GW,12}, {BC6H_GW,11},
	{BC6H_GW,10}, {BC6H_BX, 0}, {BC6H_BX, 1}, {BC6H_BX, 2}, {BC6H_BX, 3}, {BC6H_BW,15}, {BC6H_BW,14}, {BC6H_BW,13}, {BC6H_BW,12},
	{BC6H_BW,11}, {BC6H_BW,10}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0},
	{BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0}, {BC6H_XX, 0},
	{BC6H_XX, 0},
}
	},
};

bc6h7_shape_index_t g_bc6h_shape_index[32] =
{
	{0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1},
	{0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
	{0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
	{0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1},
	{0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1},
	{0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1},
	{0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
	{0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1},
	{0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0},
	{0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0},
	{0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1},
	{0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0},
	{0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0},
	{0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0},
	{0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0},
	{0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
	{0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0},
	{0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
};

int g_bc6h_weights3[8] = {0, 9, 18, 27, 37, 46, 55, 64};
int g_bc6h_weights4[16] = {0, 4, 9, 13, 17, 21, 26, 30, 34, 38, 43, 47, 51, 55, 60, 64};

uint32_t g_bc7_fixup2_1[64] = 
{
	15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15,
	15,  2,  8,  2,  2,  8,  8, 15,
	2,  8,  2,  2,  8,  8,  2,  2,
	15, 15,  6,  8,  2,  8, 15, 15,
	2,  8,  2,  2,  2, 15, 15,  6,
	6,  2,  6,  8, 15, 15,  2,  2,
	15, 15, 15, 15, 15,  2,  2, 15,
};
uint32_t g_bc7_fixup3_1[64] = 
{
	3,  3, 15, 15,  8,  3, 15, 15,
	8,  8,  6,  6,  6,  5,  3,  3,
	3,  3,  8, 15,  3,  3,  6, 10,
	5,  8,  8,  6,  8,  5, 15, 15,
	8, 15,  3,  5,  6, 10,  8, 15,
	15,  3, 15,  5, 15, 15, 15, 15,
	3, 15,  5,  5,  5,  8,  5, 10,
	5, 10,  8, 13, 15, 12,  3,  3,
};
uint32_t g_bc7_fixup3_2[64] = 
{
	15,  8,  8,  3, 15, 15,  3,  8,
	15, 15, 15, 15, 15, 15, 15,  8,
	15,  8, 15,  3, 15,  8, 15,  8,
	3, 15,  6, 10, 15, 15, 10,  8,
	15,  3, 15, 10, 10,  8,  9, 10,
	6, 15,  8, 15,  3,  6,  6,  8,
	15,  3, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15,  3, 15, 15,  8,
};

bc6h7_shape_index_t g_bc6h7_shape_index1[1] =
{
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};
bc6h7_shape_index_t g_bc7_shape_index2[64] =
{
	{0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1},
	{0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
	{0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
	{0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1},
	{0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1},
	{0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1},
	{0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
	{0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1},
	{0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0},
	{0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0},
	{0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1},
	{0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0},
	{0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0},
	{0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0},
	{0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0},
	{0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
	{0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0},
	{0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
	{0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
	{0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1},
	{0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0},
	{0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0},
	{0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0},
	{0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0},
	{0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1},
	{0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1},
	{0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0},
	{0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0},
	{0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0},
	{0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0},
	{0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0},
	{0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1},
	{0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1},
	{0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0},
	{0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0},
	{0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1},
	{0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1},
	{0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0},
	{0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0},
	{0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1},
	{0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1},
	{0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
	{0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1},
	{0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1},
	{0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
	{0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0},
	{0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1},
};

bc6h7_shape_index_t g_bc7_shape_index3[64] =
{
	{0, 0, 1, 1, 0, 0, 1, 1, 0, 2, 2, 1, 2, 2, 2, 2},
	{0, 0, 0, 1, 0, 0, 1, 1, 2, 2, 1, 1, 2, 2, 2, 1},
	{0, 0, 0, 0, 2, 0, 0, 1, 2, 2, 1, 1, 2, 2, 1, 1},
	{0, 2, 2, 2, 0, 0, 2, 2, 0, 0, 1, 1, 0, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 2, 1, 1, 2, 2},
	{0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 2, 2, 0, 0, 2, 2},
	{0, 0, 2, 2, 0, 0, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1},
	{0, 0, 1, 1, 0, 0, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2},
	{0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2},
	{0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2},
	{0, 0, 1, 2, 0, 0, 1, 2, 0, 0, 1, 2, 0, 0, 1, 2},
	{0, 1, 1, 2, 0, 1, 1, 2, 0, 1, 1, 2, 0, 1, 1, 2},
	{0, 1, 2, 2, 0, 1, 2, 2, 0, 1, 2, 2, 0, 1, 2, 2},
	{0, 0, 1, 1, 0, 1, 1, 2, 1, 1, 2, 2, 1, 2, 2, 2},
	{0, 0, 1, 1, 2, 0, 0, 1, 2, 2, 0, 0, 2, 2, 2, 0},
	{0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 2, 1, 1, 2, 2},
	{0, 1, 1, 1, 0, 0, 1, 1, 2, 0, 0, 1, 2, 2, 0, 0},
	{0, 0, 0, 0, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 2, 2},
	{0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 2, 2, 1, 1, 1, 1},
	{0, 1, 1, 1, 0, 1, 1, 1, 0, 2, 2, 2, 0, 2, 2, 2},
	{0, 0, 0, 1, 0, 0, 0, 1, 2, 2, 2, 1, 2, 2, 2, 1},
	{0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 2, 2, 0, 1, 2, 2},
	{0, 0, 0, 0, 1, 1, 0, 0, 2, 2, 1, 0, 2, 2, 1, 0},
	{0, 1, 2, 2, 0, 1, 2, 2, 0, 0, 1, 1, 0, 0, 0, 0},
	{0, 0, 1, 2, 0, 0, 1, 2, 1, 1, 2, 2, 2, 2, 2, 2},
	{0, 1, 1, 0, 1, 2, 2, 1, 1, 2, 2, 1, 0, 1, 1, 0},
	{0, 0, 0, 0, 0, 1, 1, 0, 1, 2, 2, 1, 1, 2, 2, 1},
	{0, 0, 2, 2, 1, 1, 0, 2, 1, 1, 0, 2, 0, 0, 2, 2},
	{0, 1, 1, 0, 0, 1, 1, 0, 2, 0, 0, 2, 2, 2, 2, 2},
	{0, 0, 1, 1, 0, 1, 2, 2, 0, 1, 2, 2, 0, 0, 1, 1},
	{0, 0, 0, 0, 2, 0, 0, 0, 2, 2, 1, 1, 2, 2, 2, 1},
	{0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 2, 2, 1, 2, 2, 2},
	{0, 2, 2, 2, 0, 0, 2, 2, 0, 0, 1, 2, 0, 0, 1, 1},
	{0, 0, 1, 1, 0, 0, 1, 2, 0, 0, 2, 2, 0, 2, 2, 2},
	{0, 1, 2, 0, 0, 1, 2, 0, 0, 1, 2, 0, 0, 1, 2, 0},
	{0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 0, 0, 0, 0},
	{0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0},
	{0, 1, 2, 0, 2, 0, 1, 2, 1, 2, 0, 1, 0, 1, 2, 0},
	{0, 0, 1, 1, 2, 2, 0, 0, 1, 1, 2, 2, 0, 0, 1, 1},
	{0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 0, 0, 0, 0, 1, 1},
	{0, 1, 0, 1, 0, 1, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2},
	{0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 2, 1, 2, 1, 2, 1},
	{0, 0, 2, 2, 1, 1, 2, 2, 0, 0, 2, 2, 1, 1, 2, 2},
	{0, 0, 2, 2, 0, 0, 1, 1, 0, 0, 2, 2, 0, 0, 1, 1},
	{0, 2, 2, 0, 1, 2, 2, 1, 0, 2, 2, 0, 1, 2, 2, 1},
	{0, 1, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 0, 1, 0, 1},
	{0, 0, 0, 0, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},
	{0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 2, 2, 2, 2},
	{0, 2, 2, 2, 0, 1, 1, 1, 0, 2, 2, 2, 0, 1, 1, 1},
	{0, 0, 0, 2, 1, 1, 1, 2, 0, 0, 0, 2, 1, 1, 1, 2},
	{0, 0, 0, 0, 2, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 2},
	{0, 2, 2, 2, 0, 1, 1, 1, 0, 1, 1, 1, 0, 2, 2, 2},
	{0, 0, 0, 2, 1, 1, 1, 2, 1, 1, 1, 2, 0, 0, 0, 2},
	{0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 2, 2, 2, 2},
	{0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 2, 2, 1, 1, 2},
	{0, 1, 1, 0, 0, 1, 1, 0, 2, 2, 2, 2, 2, 2, 2, 2},
	{0, 0, 2, 2, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 2, 2},
	{0, 0, 2, 2, 1, 1, 2, 2, 1, 1, 2, 2, 0, 0, 2, 2},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 2},
	{0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1},
	{0, 2, 2, 2, 1, 2, 2, 2, 0, 2, 2, 2, 1, 2, 2, 2},
	{0, 1, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
	{0, 1, 1, 1, 2, 0, 1, 1, 2, 2, 0, 1, 2, 2, 2, 0},
};

bc6h7_partition_delta_t g_bc6h7_partition_delta[31] =
{
	{8.0f, 8.0f, 0.125f, 0.125f, 2, {2, 13, 0, 0}},
	{8.0f, 8.0f, 0.125f, 0.125f, 2, {1, 14, 0, 0}},
	{8.0f, 8.0f, 0.166667f, 0.1f, 2, {9, 12, 0, 0}},
	{8.0f, 8.0f, 0.1f, 0.166667f, 2, {3, 6, 0, 0}},
	{10.0f, 6.0f, 0.0833333f, 0.25f, 2, {10, 13, 0, 0}},
	{12.0f, 4.0f, 0.0769231f, 0.333333f, 1, {7, 0, 0, 0}},
	{6.0f, 10.0f, 0.25f, 0.0833333f, 2, {2, 5, 0, 0}},
	{4.0f, 12.0f, 0.333333f, 0.0769231f, 1, {8, 0, 0, 0}},
	{4.0f, 12.0f, 0.125f, 0.125f, 4, {7, 11, 14, 15}},
	{6.0f, 10.0f, 0.125f, 0.125f, 2, {3, 6, 0, 0}},
	{13.0f, 3.0f, 0.0833333f, 0.25f, 1, {13, 0, 0, 0}},
	{3.0f, 13.0f, 0.25f, 0.0833333f, 1, {2, 0, 0, 0}},
	{8.0f, 8.0f, 0.125f, 0.125f, 2, {7, 8, 0, 0}},
	{12.0f, 4.0f, 0.0833333f, 0.25f, 2, {11, 12, 0, 0}},
	{4.0f, 12.0f, 0.25f, 0.0833333f, 2, {3, 4, 0, 0}},
	{4.0f, 12.0f, 0.125f, 0.125f, 4, {11, 13, 14, 15}},
	{8.0f, 8.0f, 0.125f, 0.125f, 2, {4, 11, 0, 0}},
	{4.0f, 12.0f, 0.125f, 0.125f, 4, {12, 13, 14, 15}},
	{12.0f, 4.0f, 0.0833333f, 0.25f, 2, {8, 15, 0, 0}},
	{8.0f, 8.0f, 0.1f, 0.166667f, 2, {10, 15, 0, 0}},
	{12.0f, 4.0f, 0.0769231f, 0.333333f, 1, {14, 0, 0, 0}},
	{12.0f, 4.0f, 0.125f, 0.125f, 4, {1, 2, 3, 7}},
	{8.0f, 8.0f, 0.1f, 0.166667f, 2, {10, 15, 0, 0}},
	{13.0f, 3.0f, 0.0833333f, 0.25f, 1, {4, 0, 0, 0}},
	{12.0f, 4.0f, 0.125f, 0.125f, 4, {2, 3, 7, 11}},
	{12.0f, 4.0f, 0.0833333f, 0.25f, 2, {3, 14, 0, 0}},
	{4.0f, 12.0f, 0.25f, 0.0833333f, 2, {1, 12, 0, 0}},
	{4.0f, 12.0f, 0.125f, 0.125f, 4, {3, 7, 11, 15}},
	{10.0f, 6.0f, 0.0833333f, 0.25f, 2, {6, 11, 0, 0}},
	{12.0f, 4.0f, 0.0769231f, 0.333333f, 1, {1, 0, 0, 0}},
	{13.0f, 3.0f, 0.0833333f, 0.25f, 1, {11, 0, 0, 0}}
};
bc6h7_partition_order_t g_bc6h_partition_order[31] =
{
	{0, 3},
	{0, 23},
	{3, 6},
	{3, 7},
	{7, 4},
	{4, 8},
	{6, 5},
	{5, 9},
	{5, 27},
	{6, 10},
	{8, 11},
	{9, 12},
	{10, 13},
	{11, 15},
	{12, 14},
	{12, 28},
	{13, 16},
	{14, 29},
	{15, 18},
	{16, 21},
	{18, 22},
	{18, 30},
	{23, 19},
	{22, 25},
	{25, 31},
	{4, 1},
	{5, 2},
	{2, 26},
	{19, 17},
	{17, 20},
	{20, 24},
};

int g_bc7_weights2[4] = {0, 21, 43, 64};
int g_bc7_weights3[8] = {0, 9, 18, 27, 37, 46, 55, 64};
int g_bc7_weights4[16] = {0, 4, 9, 13, 17, 21, 26, 30, 34, 38, 43, 47, 51, 55, 60, 64};

bc7_desc_t g_bc7_desc[8] = 
{
	{
		.index_bits = {3, 0},
		.shape_subset = g_bc7_shape_index3,
		.fixup = {g_bc7_fixup3_1, g_bc7_fixup3_2},
		.partition_bits = 4,
		.num_endpoints = 6,
		.num_p = 6,
		.has_rotation = 0,
		.has_idx = 0,
		.endpoint_bits = 
	{
		{4, 4, 4, 0},
	{4, 4, 4, 0},
	{4, 4, 4, 0},
	{4, 4, 4, 0},
	{4, 4, 4, 0},
	{4, 4, 4, 0},
},
	},
	{
		.index_bits = {3, 0},
		.shape_subset = g_bc7_shape_index2,
		.fixup = {g_bc7_fixup2_1, 0},
		.partition_bits = 6,
		.num_endpoints = 4,
		.num_p = 2,
		.has_rotation = 0,
		.has_idx = 0,
		.endpoint_bits = 
	{
		{6, 6, 6, 0},
	{6, 6, 6, 0},
	{6, 6, 6, 0},
	{6, 6, 6, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
},
	},
	{
		.index_bits = {2, 0},
		.shape_subset = g_bc7_shape_index3,
		.fixup = {g_bc7_fixup3_1, g_bc7_fixup3_2},
		.partition_bits = 6,
		.num_endpoints = 6,
		.num_p = 0,
		.has_rotation = 0,
		.has_idx = 0,
		.endpoint_bits = 
	{
		{5, 5, 5, 0},
	{5, 5, 5, 0},
	{5, 5, 5, 0},
	{5, 5, 5, 0},
	{5, 5, 5, 0},
	{5, 5, 5, 0},
},
	},
	{
		.index_bits = {2, 0},
		.shape_subset = g_bc7_shape_index2,
		.fixup = {g_bc7_fixup2_1, 0},
		.partition_bits = 6,
		.num_endpoints = 4,
		.num_p = 4,
		.has_rotation = 0,
		.has_idx = 0,
		.endpoint_bits = 
	{
		{7, 7, 7, 0},
	{7, 7, 7, 0},
	{7, 7, 7, 0},
	{7, 7, 7, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
},
	},
	{
		.index_bits = {2, 3},
		.shape_subset = g_bc6h7_shape_index1,
		.fixup = {0, 0},
		.partition_bits = 0,
		.num_endpoints = 2,
		.num_p = 0,
		.has_rotation = 1,
		.has_idx = 1,
		.endpoint_bits = 
	{
		{5, 5, 5, 6},
	{5, 5, 5, 6},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
},
	},
	{
		.index_bits = {2, 2},
		.shape_subset = g_bc6h7_shape_index1,
		.fixup = {0, 0},
		.partition_bits = 0,
		.num_endpoints = 2,
		.num_p = 0,
		.has_rotation = 1,
		.has_idx = 0,
		.endpoint_bits = 
	{
		{7, 7, 7, 8},
	{7, 7, 7, 8},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
},
	},
	{
		.index_bits = {4, 0},
		.shape_subset = g_bc6h7_shape_index1,
		.fixup = {0, 0},
		.partition_bits = 0,
		.num_endpoints = 2,
		.num_p = 2,
		.has_rotation = 0,
		.has_idx = 0,
		.endpoint_bits = 
	{
		{7, 7, 7, 7},
	{7, 7, 7, 7},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
},
	},
	{
		.index_bits = {2, 0},
		.shape_subset = g_bc7_shape_index2,
		.fixup = {g_bc7_fixup2_1, 0},
		.partition_bits = 6,
		.num_endpoints = 4,
		.num_p = 4,
		.has_rotation = 0,
		.has_idx = 0,
		.endpoint_bits = 
	{
		{5, 5, 5, 5},
	{5, 5, 5, 5},
	{5, 5, 5, 5},
	{5, 5, 5, 5},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
},
	},
};
