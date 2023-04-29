#include <stdint.h>
#include <math.h>

#include "../inc/vecmat.h"

#define G_F64_ZERO 0.0
#define G_F64_ONE 1.0
#define G_F64_NEG_ONE -1.0
#define G_F32_ZERO 0.0f
#define G_F32_ONE 1.0f
#define G_F32_NEG_ONE -1.0f
#define G_U64_ZERO 0
#define G_U64_ONE 1
#define G_U64_NEG_ONE (-1)
#define G_I64_ZERO 0
#define G_I64_ONE 1
#define G_I64_NEG_ONE (-1)
#define G_U32_ZERO 0
#define G_U32_ONE 1
#define G_U32_NEG_ONE (-1)
#define G_I32_ZERO 0
#define G_I32_ONE 1
#define G_I32_NEG_ONE (-1)
#define G_U16_ZERO 0
#define G_U16_ONE 1
#define G_U16_NEG_ONE (-1)
#define G_I16_ZERO 0
#define G_I16_ONE 1
#define G_I16_NEG_ONE (-1)
#define G_U8_ZERO 0
#define G_U8_ONE 1
#define G_U8_NEG_ONE (-1)
#define G_I8_ZERO 0
#define G_I8_ONE 1
#define G_I8_NEG_ONE (-1)

static const vec2f64_t G_VEC2F64_T_ZERO = {0.0, 0.0};
static const vec2f64_t G_VEC2F64_T_ONE = {1.0, 1.0};
static const vec2f32_t G_VEC2F32_T_ZERO = {0.0f, 0.0f};
static const vec2f32_t G_VEC2F32_T_ONE = {1.0f, 1.0f};
static const vec2u64_t G_VEC2U64_T_ZERO = {0, 0};
static const vec2u64_t G_VEC2U64_T_ONE = {1, 1};
static const vec2i64_t G_VEC2I64_T_ZERO = {0, 0};
static const vec2i64_t G_VEC2I64_T_ONE = {1, 1};
static const vec2u32_t G_VEC2U32_T_ZERO = {0, 0};
static const vec2u32_t G_VEC2U32_T_ONE = {1, 1};
static const vec2i32_t G_VEC2I32_T_ZERO = {0, 0};
static const vec2i32_t G_VEC2I32_T_ONE = {1, 1};
static const vec2u16_t G_VEC2U16_T_ZERO = {0, 0};
static const vec2u16_t G_VEC2U16_T_ONE = {1, 1};
static const vec2i16_t G_VEC2I16_T_ZERO = {0, 0};
static const vec2i16_t G_VEC2I16_T_ONE = {1, 1};
static const vec2u8_t G_VEC2U8_T_ZERO = {0, 0};
static const vec2u8_t G_VEC2U8_T_ONE = {1, 1};
static const vec2i8_t G_VEC2I8_T_ZERO = {0, 0};
static const vec2i8_t G_VEC2I8_T_ONE = {1, 1};
static const vec3f64_t G_VEC3F64_T_ZERO = {0.0, 0.0, 0.0};
static const vec3f64_t G_VEC3F64_T_ONE = {1.0, 1.0, 1.0};
static const vec3f32_t G_VEC3F32_T_ZERO = {0.0f, 0.0f, 0.0f};
static const vec3f32_t G_VEC3F32_T_ONE = {1.0f, 1.0f, 1.0f};
static const vec3u64_t G_VEC3U64_T_ZERO = {0, 0, 0};
static const vec3u64_t G_VEC3U64_T_ONE = {1, 1, 1};
static const vec3i64_t G_VEC3I64_T_ZERO = {0, 0, 0};
static const vec3i64_t G_VEC3I64_T_ONE = {1, 1, 1};
static const vec3u32_t G_VEC3U32_T_ZERO = {0, 0, 0};
static const vec3u32_t G_VEC3U32_T_ONE = {1, 1, 1};
static const vec3i32_t G_VEC3I32_T_ZERO = {0, 0, 0};
static const vec3i32_t G_VEC3I32_T_ONE = {1, 1, 1};
static const vec3u16_t G_VEC3U16_T_ZERO = {0, 0, 0};
static const vec3u16_t G_VEC3U16_T_ONE = {1, 1, 1};
static const vec3i16_t G_VEC3I16_T_ZERO = {0, 0, 0};
static const vec3i16_t G_VEC3I16_T_ONE = {1, 1, 1};
static const vec3u8_t G_VEC3U8_T_ZERO = {0, 0, 0};
static const vec3u8_t G_VEC3U8_T_ONE = {1, 1, 1};
static const vec3i8_t G_VEC3I8_T_ZERO = {0, 0, 0};
static const vec3i8_t G_VEC3I8_T_ONE = {1, 1, 1};
static const vec4f64_t G_VEC4F64_T_ZERO = {0.0, 0.0, 0.0, 0.0};
static const vec4f64_t G_VEC4F64_T_ONE = {1.0, 1.0, 1.0, 1.0};
static const vec4f32_t G_VEC4F32_T_ZERO = {0.0f, 0.0f, 0.0f, 0.0f};
static const vec4f32_t G_VEC4F32_T_ONE = {1.0f, 1.0f, 1.0f, 1.0f};
static const vec4u64_t G_VEC4U64_T_ZERO = {0, 0, 0, 0};
static const vec4u64_t G_VEC4U64_T_ONE = {1, 1, 1, 1};
static const vec4i64_t G_VEC4I64_T_ZERO = {0, 0, 0, 0};
static const vec4i64_t G_VEC4I64_T_ONE = {1, 1, 1, 1};
static const vec4u32_t G_VEC4U32_T_ZERO = {0, 0, 0, 0};
static const vec4u32_t G_VEC4U32_T_ONE = {1, 1, 1, 1};
static const vec4i32_t G_VEC4I32_T_ZERO = {0, 0, 0, 0};
static const vec4i32_t G_VEC4I32_T_ONE = {1, 1, 1, 1};
static const vec4u16_t G_VEC4U16_T_ZERO = {0, 0, 0, 0};
static const vec4u16_t G_VEC4U16_T_ONE = {1, 1, 1, 1};
static const vec4i16_t G_VEC4I16_T_ZERO = {0, 0, 0, 0};
static const vec4i16_t G_VEC4I16_T_ONE = {1, 1, 1, 1};
static const vec4u8_t G_VEC4U8_T_ZERO = {0, 0, 0, 0};
static const vec4u8_t G_VEC4U8_T_ONE = {1, 1, 1, 1};
static const vec4i8_t G_VEC4I8_T_ZERO = {0, 0, 0, 0};
static const vec4i8_t G_VEC4I8_T_ONE = {1, 1, 1, 1};
static const vec5f64_t G_VEC5F64_T_ZERO = {0.0, 0.0, 0.0, 0.0, 0.0};
static const vec5f64_t G_VEC5F64_T_ONE = {1.0, 1.0, 1.0, 1.0, 1.0};
static const vec5f32_t G_VEC5F32_T_ZERO = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
static const vec5f32_t G_VEC5F32_T_ONE = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
static const vec5u64_t G_VEC5U64_T_ZERO = {0, 0, 0, 0, 0};
static const vec5u64_t G_VEC5U64_T_ONE = {1, 1, 1, 1, 1};
static const vec5i64_t G_VEC5I64_T_ZERO = {0, 0, 0, 0, 0};
static const vec5i64_t G_VEC5I64_T_ONE = {1, 1, 1, 1, 1};
static const vec5u32_t G_VEC5U32_T_ZERO = {0, 0, 0, 0, 0};
static const vec5u32_t G_VEC5U32_T_ONE = {1, 1, 1, 1, 1};
static const vec5i32_t G_VEC5I32_T_ZERO = {0, 0, 0, 0, 0};
static const vec5i32_t G_VEC5I32_T_ONE = {1, 1, 1, 1, 1};
static const vec5u16_t G_VEC5U16_T_ZERO = {0, 0, 0, 0, 0};
static const vec5u16_t G_VEC5U16_T_ONE = {1, 1, 1, 1, 1};
static const vec5i16_t G_VEC5I16_T_ZERO = {0, 0, 0, 0, 0};
static const vec5i16_t G_VEC5I16_T_ONE = {1, 1, 1, 1, 1};
static const vec5u8_t G_VEC5U8_T_ZERO = {0, 0, 0, 0, 0};
static const vec5u8_t G_VEC5U8_T_ONE = {1, 1, 1, 1, 1};
static const vec5i8_t G_VEC5I8_T_ZERO = {0, 0, 0, 0, 0};
static const vec5i8_t G_VEC5I8_T_ONE = {1, 1, 1, 1, 1};
static const vec6f64_t G_VEC6F64_T_ZERO = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
static const vec6f64_t G_VEC6F64_T_ONE = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
static const vec6f32_t G_VEC6F32_T_ZERO = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
static const vec6f32_t G_VEC6F32_T_ONE = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
static const vec6u64_t G_VEC6U64_T_ZERO = {0, 0, 0, 0, 0, 0};
static const vec6u64_t G_VEC6U64_T_ONE = {1, 1, 1, 1, 1, 1};
static const vec6i64_t G_VEC6I64_T_ZERO = {0, 0, 0, 0, 0, 0};
static const vec6i64_t G_VEC6I64_T_ONE = {1, 1, 1, 1, 1, 1};
static const vec6u32_t G_VEC6U32_T_ZERO = {0, 0, 0, 0, 0, 0};
static const vec6u32_t G_VEC6U32_T_ONE = {1, 1, 1, 1, 1, 1};
static const vec6i32_t G_VEC6I32_T_ZERO = {0, 0, 0, 0, 0, 0};
static const vec6i32_t G_VEC6I32_T_ONE = {1, 1, 1, 1, 1, 1};
static const vec6u16_t G_VEC6U16_T_ZERO = {0, 0, 0, 0, 0, 0};
static const vec6u16_t G_VEC6U16_T_ONE = {1, 1, 1, 1, 1, 1};
static const vec6i16_t G_VEC6I16_T_ZERO = {0, 0, 0, 0, 0, 0};
static const vec6i16_t G_VEC6I16_T_ONE = {1, 1, 1, 1, 1, 1};
static const vec6u8_t G_VEC6U8_T_ZERO = {0, 0, 0, 0, 0, 0};
static const vec6u8_t G_VEC6U8_T_ONE = {1, 1, 1, 1, 1, 1};
static const vec6i8_t G_VEC6I8_T_ZERO = {0, 0, 0, 0, 0, 0};
static const vec6i8_t G_VEC6I8_T_ONE = {1, 1, 1, 1, 1, 1};
static const vec7f64_t G_VEC7F64_T_ZERO = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
static const vec7f64_t G_VEC7F64_T_ONE = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
static const vec7f32_t G_VEC7F32_T_ZERO = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
static const vec7f32_t G_VEC7F32_T_ONE = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
static const vec7u64_t G_VEC7U64_T_ZERO = {0, 0, 0, 0, 0, 0, 0};
static const vec7u64_t G_VEC7U64_T_ONE = {1, 1, 1, 1, 1, 1, 1};
static const vec7i64_t G_VEC7I64_T_ZERO = {0, 0, 0, 0, 0, 0, 0};
static const vec7i64_t G_VEC7I64_T_ONE = {1, 1, 1, 1, 1, 1, 1};
static const vec7u32_t G_VEC7U32_T_ZERO = {0, 0, 0, 0, 0, 0, 0};
static const vec7u32_t G_VEC7U32_T_ONE = {1, 1, 1, 1, 1, 1, 1};
static const vec7i32_t G_VEC7I32_T_ZERO = {0, 0, 0, 0, 0, 0, 0};
static const vec7i32_t G_VEC7I32_T_ONE = {1, 1, 1, 1, 1, 1, 1};
static const vec7u16_t G_VEC7U16_T_ZERO = {0, 0, 0, 0, 0, 0, 0};
static const vec7u16_t G_VEC7U16_T_ONE = {1, 1, 1, 1, 1, 1, 1};
static const vec7i16_t G_VEC7I16_T_ZERO = {0, 0, 0, 0, 0, 0, 0};
static const vec7i16_t G_VEC7I16_T_ONE = {1, 1, 1, 1, 1, 1, 1};
static const vec7u8_t G_VEC7U8_T_ZERO = {0, 0, 0, 0, 0, 0, 0};
static const vec7u8_t G_VEC7U8_T_ONE = {1, 1, 1, 1, 1, 1, 1};
static const vec7i8_t G_VEC7I8_T_ZERO = {0, 0, 0, 0, 0, 0, 0};
static const vec7i8_t G_VEC7I8_T_ONE = {1, 1, 1, 1, 1, 1, 1};
static const vec8f64_t G_VEC8F64_T_ZERO = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
static const vec8f64_t G_VEC8F64_T_ONE = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
static const vec8f32_t G_VEC8F32_T_ZERO = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
static const vec8f32_t G_VEC8F32_T_ONE = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
static const vec8u64_t G_VEC8U64_T_ZERO = {0, 0, 0, 0, 0, 0, 0, 0};
static const vec8u64_t G_VEC8U64_T_ONE = {1, 1, 1, 1, 1, 1, 1, 1};
static const vec8i64_t G_VEC8I64_T_ZERO = {0, 0, 0, 0, 0, 0, 0, 0};
static const vec8i64_t G_VEC8I64_T_ONE = {1, 1, 1, 1, 1, 1, 1, 1};
static const vec8u32_t G_VEC8U32_T_ZERO = {0, 0, 0, 0, 0, 0, 0, 0};
static const vec8u32_t G_VEC8U32_T_ONE = {1, 1, 1, 1, 1, 1, 1, 1};
static const vec8i32_t G_VEC8I32_T_ZERO = {0, 0, 0, 0, 0, 0, 0, 0};
static const vec8i32_t G_VEC8I32_T_ONE = {1, 1, 1, 1, 1, 1, 1, 1};
static const vec8u16_t G_VEC8U16_T_ZERO = {0, 0, 0, 0, 0, 0, 0, 0};
static const vec8u16_t G_VEC8U16_T_ONE = {1, 1, 1, 1, 1, 1, 1, 1};
static const vec8i16_t G_VEC8I16_T_ZERO = {0, 0, 0, 0, 0, 0, 0, 0};
static const vec8i16_t G_VEC8I16_T_ONE = {1, 1, 1, 1, 1, 1, 1, 1};
static const vec8u8_t G_VEC8U8_T_ZERO = {0, 0, 0, 0, 0, 0, 0, 0};
static const vec8u8_t G_VEC8U8_T_ONE = {1, 1, 1, 1, 1, 1, 1, 1};
static const vec8i8_t G_VEC8I8_T_ZERO = {0, 0, 0, 0, 0, 0, 0, 0};
static const vec8i8_t G_VEC8I8_T_ONE = {1, 1, 1, 1, 1, 1, 1, 1};

vec2f64_t Vec2f64_SetComponent(vec2f64_t v, int index, double value)
{
	v.v[index] = value;

	return v;
}
vec2f64_t Vec2f64_Vec(double x0, double x1)
{
	vec2f64_t v;

	v.v[0] = x0;
	v.v[1] = x1;

	return v;
}
vec2f64_t Vec2f64_Add(vec2f64_t v0, vec2f64_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];

	return v0;
}
vec2f64_t Vec2f64_Sub(vec2f64_t v0, vec2f64_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];

	return v0;
}
double Vec2f64_GetComponent(vec2f64_t v, int index)
{
	return v.v[index];
}
vec2f64_t Vec2f64_Mul(vec2f64_t v0, vec2f64_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];

	return v0;
}
vec2f64_t Vec2f64_Div(vec2f64_t v0, vec2f64_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];

	return v0;
}
vec2f64_t Vec2f64_Scale(vec2f64_t v, double scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;

	return v;
}
vec2f64_t Vec2f64_DivScale(vec2f64_t v, double divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;

	return v;
}
vec2f64_t Vec2f64_MA(vec2f64_t v, vec2f64_t dir, double scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;

	return v;
}
vec2f64_t Vec2f64_DA(vec2f64_t v, vec2f64_t dir, double divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;

	return v;
}
double Vec2f64_Dot(vec2f64_t v0, vec2f64_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1];
}
double Vec2f64_LenSq(vec2f64_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1];
}
double Vec2f64_Len(vec2f64_t v)
{
	return sqrt(Vec2f64_LenSq(v));
}
vec2f64_t Vec2f64_Normalise(vec2f64_t v)
{
	double lensq = Vec2f64_LenSq(v);

	if (lensq == G_F64_ZERO)
		return v;
	else
		return Vec2f64_Scale(v, G_F64_ONE / sqrt(lensq));
}
vec2f64_t Vec2f64_Abs(vec2f64_t v)
{
	v.v[0] = fabs(v.v[0]);
	v.v[1] = fabs(v.v[1]);

	return v;
}
vec2f64_t Vec2f64_Floor(vec2f64_t v)
{
	v.v[0] = floor(v.v[0]);
	v.v[1] = floor(v.v[1]);

	return v;
}
vec2f64_t Vec2f64_Ceil(vec2f64_t v)
{
	v.v[0] = ceil(v.v[0]);
	v.v[1] = ceil(v.v[1]);

	return v;
}
vec2f64_t Vec2f64_Fract(vec2f64_t v)
{
	return Vec2f64_Sub(v, Vec2f64_Floor(v));
}
vec2f64_t Vec2f64_Mod(vec2f64_t v0, vec2f64_t v1)
{
	v0.v[0] = fmod(v0.v[0], v1.v[0]);
	v0.v[1] = fmod(v0.v[1], v1.v[1]);

	return v0;
}
vec2f64_t Vec2f64_ModS(vec2f64_t v0, double x)
{
	v0.v[0] = fmod(v0.v[0], x);
	v0.v[1] = fmod(v0.v[1], x);

	return v0;
}
vec2f64_t Vec2f64_Min(vec2f64_t v0, vec2f64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];

	return v0;
}
vec2f64_t Vec2f64_Max(vec2f64_t v0, vec2f64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];

	return v0;
}
vec2f64_t Vec2f64_MinS(vec2f64_t v0, double x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;

	return v0;
}
vec2f64_t Vec2f64_MaxS(vec2f64_t v0, double x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;

	return v0;
}
vec2f64_t Vec2f64_Clamp(vec2f64_t v, vec2f64_t min, vec2f64_t max)
{
	return Vec2f64_Max(Vec2f64_Min(v, max), min);
}
vec2f64_t Vec2f64_ClampS(vec2f64_t v, double min, double max)
{
	return Vec2f64_MaxS(Vec2f64_MinS(v, max), min);
}
vec2f64_t Vec2f64_Neg(vec2f64_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];

	return v;
}
vec2f64_t Vec2f64_Reciprocal(vec2f64_t v)
{
	v.v[0] = G_F64_ONE / v.v[0];
	v.v[1] = G_F64_ONE / v.v[1];

	return v;
}
vec2f64_t Vec2f64_Truncate(vec2f64_t v)
{
	v.v[0] = v.v[0] < G_F64_ZERO ? ceil(v.v[0]) : floor(v.v[0]);
	v.v[1] = v.v[1] < G_F64_ZERO ? ceil(v.v[1]) : floor(v.v[1]);

	return v;
}
vec2f64_t Vec2f64_TruncateAway(vec2f64_t v)
{
	v.v[0] = v.v[0] < G_F64_ZERO ? floor(v.v[0]) : ceil(v.v[0]);
	v.v[1] = v.v[1] < G_F64_ZERO ? floor(v.v[1]) : ceil(v.v[1]);

	return v;
}
vec2f64_t Vec2f64_CmpLT(vec2f64_t v0, vec2f64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec2f64_t Vec2f64_CmpLE(vec2f64_t v0, vec2f64_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec2f64_t Vec2f64_CmpEQ(vec2f64_t v0, vec2f64_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec2f64_t Vec2f64_CmpGT(vec2f64_t v0, vec2f64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec2f64_t Vec2f64_CmpGE(vec2f64_t v0, vec2f64_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec2f64_t Vec2f64_CmpNE(vec2f64_t v0, vec2f64_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec2f64_t Vec2f64_CmpLTS(vec2f64_t v0, double x)
{
	v0.v[0] = v0.v[0] < x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] < x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec2f64_t Vec2f64_CmpLES(vec2f64_t v0, double x)
{
	v0.v[0] = v0.v[0] <= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec2f64_t Vec2f64_CmpEQS(vec2f64_t v0, double x)
{
	v0.v[0] = v0.v[0] == x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] == x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec2f64_t Vec2f64_CmpGTS(vec2f64_t v0, double x)
{
	v0.v[0] = v0.v[0] > x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] > x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec2f64_t Vec2f64_CmpGES(vec2f64_t v0, double x)
{
	v0.v[0] = v0.v[0] >= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec2f64_t Vec2f64_CmpNES(vec2f64_t v0, double x)
{
	v0.v[0] = v0.v[0] != x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] != x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec2f64_t Vec2f64_Sign(vec2f64_t v)
{
	v.v[0] = v.v[0] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;
	v.v[1] = v.v[1] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;

	return v;
}
vec2f64_t Vec2f64_SignPosNeg(vec2f64_t v)
{
	v.v[0] = v.v[0] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;
	v.v[1] = v.v[1] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;

	return v;
}
vec2f64_t Vec2f64_Zero()
{
	return G_VEC2F64_T_ZERO;
}
vec2f64_t Vec2f64_One()
{
	return G_VEC2F64_T_ONE;
}
vec2f64_t Vec2f64_NegOne()
{
	return Vec2f64_Neg(G_VEC2F64_T_ONE);
}
vec2f64_t Vec2f64_Cross(vec2f64_t v0)
{
	vec2f64_t v;

	v.v[0] = v0.v[1];
	v.v[1] = -v0.v[0];

	return v;
}
vec2f64_t Vec2f64_Lerp(vec2f64_t v0, vec2f64_t v1, vec2f64_t vt)
{
	vec2f64_t v;

	v.v[0] = (G_F64_ONE - vt.v[0]) * v0.v[0] + v1.v[0] * vt.v[0];
	v.v[1] = (G_F64_ONE - vt.v[1]) * v0.v[1] + v1.v[1] * vt.v[1];

	return v;
}
vec2f64_t Vec2f64_LerpS(vec2f64_t v0, vec2f64_t v1, double t)
{
	vec2f64_t v;

	v.v[0] = (G_F64_ONE - t) * v0.v[0] + v1.v[0] * t;
	v.v[1] = (G_F64_ONE - t) * v0.v[1] + v1.v[1] * t;

	return v;
}
vec3f64_t Vec2f64_ToVec3f64(vec2f64_t v, double x0)
{
	vec3f64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;

	return outv;
}
vec4f64_t Vec2f64_ToVec4f64(vec2f64_t v, double x0, double x1)
{
	vec4f64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;

	return outv;
}
vec5f64_t Vec2f64_ToVec5f64(vec2f64_t v, double x0, double x1, double x2)
{
	vec5f64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;

	return outv;
}
vec6f64_t Vec2f64_ToVec6f64(vec2f64_t v, double x0, double x1, double x2, double x3)
{
	vec6f64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;
	outv.v[5] = x3;

	return outv;
}
vec7f64_t Vec2f64_ToVec7f64(vec2f64_t v, double x0, double x1, double x2, double x3, double x4)
{
	vec7f64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;
	outv.v[5] = x3;
	outv.v[6] = x4;

	return outv;
}
vec8f64_t Vec2f64_ToVec8f64(vec2f64_t v, double x0, double x1, double x2, double x3, double x4, double x5)
{
	vec8f64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;
	outv.v[5] = x3;
	outv.v[6] = x4;
	outv.v[7] = x5;

	return outv;
}
vec2f32_t Vec2f32_SetComponent(vec2f32_t v, int index, float value)
{
	v.v[index] = value;

	return v;
}
vec2f32_t Vec2f32_Vec(float x0, float x1)
{
	vec2f32_t v;

	v.v[0] = x0;
	v.v[1] = x1;

	return v;
}
vec2f32_t Vec2f32_Add(vec2f32_t v0, vec2f32_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];

	return v0;
}
vec2f32_t Vec2f32_Sub(vec2f32_t v0, vec2f32_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];

	return v0;
}
float Vec2f32_GetComponent(vec2f32_t v, int index)
{
	return v.v[index];
}
vec2f32_t Vec2f32_Mul(vec2f32_t v0, vec2f32_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];

	return v0;
}
vec2f32_t Vec2f32_Div(vec2f32_t v0, vec2f32_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];

	return v0;
}
vec2f32_t Vec2f32_Scale(vec2f32_t v, float scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;

	return v;
}
vec2f32_t Vec2f32_DivScale(vec2f32_t v, float divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;

	return v;
}
vec2f32_t Vec2f32_MA(vec2f32_t v, vec2f32_t dir, float scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;

	return v;
}
vec2f32_t Vec2f32_DA(vec2f32_t v, vec2f32_t dir, float divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;

	return v;
}
float Vec2f32_Dot(vec2f32_t v0, vec2f32_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1];
}
float Vec2f32_LenSq(vec2f32_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1];
}
float Vec2f32_Len(vec2f32_t v)
{
	return sqrtf(Vec2f32_LenSq(v));
}
vec2f32_t Vec2f32_Normalise(vec2f32_t v)
{
	float lensq = Vec2f32_LenSq(v);

	if (lensq == G_F32_ZERO)
		return v;
	else
		return Vec2f32_Scale(v, G_F32_ONE / sqrtf(lensq));
}
vec2f32_t Vec2f32_Abs(vec2f32_t v)
{
	v.v[0] = fabsf(v.v[0]);
	v.v[1] = fabsf(v.v[1]);

	return v;
}
vec2f32_t Vec2f32_Floor(vec2f32_t v)
{
	v.v[0] = floorf(v.v[0]);
	v.v[1] = floorf(v.v[1]);

	return v;
}
vec2f32_t Vec2f32_Ceil(vec2f32_t v)
{
	v.v[0] = ceilf(v.v[0]);
	v.v[1] = ceilf(v.v[1]);

	return v;
}
vec2f32_t Vec2f32_Fract(vec2f32_t v)
{
	return Vec2f32_Sub(v, Vec2f32_Floor(v));
}
vec2f32_t Vec2f32_Mod(vec2f32_t v0, vec2f32_t v1)
{
	v0.v[0] = fmodf(v0.v[0], v1.v[0]);
	v0.v[1] = fmodf(v0.v[1], v1.v[1]);

	return v0;
}
vec2f32_t Vec2f32_ModS(vec2f32_t v0, float x)
{
	v0.v[0] = fmodf(v0.v[0], x);
	v0.v[1] = fmodf(v0.v[1], x);

	return v0;
}
vec2f32_t Vec2f32_Min(vec2f32_t v0, vec2f32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];

	return v0;
}
vec2f32_t Vec2f32_Max(vec2f32_t v0, vec2f32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];

	return v0;
}
vec2f32_t Vec2f32_MinS(vec2f32_t v0, float x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;

	return v0;
}
vec2f32_t Vec2f32_MaxS(vec2f32_t v0, float x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;

	return v0;
}
vec2f32_t Vec2f32_Clamp(vec2f32_t v, vec2f32_t min, vec2f32_t max)
{
	return Vec2f32_Max(Vec2f32_Min(v, max), min);
}
vec2f32_t Vec2f32_ClampS(vec2f32_t v, float min, float max)
{
	return Vec2f32_MaxS(Vec2f32_MinS(v, max), min);
}
vec2f32_t Vec2f32_Neg(vec2f32_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];

	return v;
}
vec2f32_t Vec2f32_Reciprocal(vec2f32_t v)
{
	v.v[0] = G_F32_ONE / v.v[0];
	v.v[1] = G_F32_ONE / v.v[1];

	return v;
}
vec2f32_t Vec2f32_Truncate(vec2f32_t v)
{
	v.v[0] = v.v[0] < G_F32_ZERO ? ceilf(v.v[0]) : floorf(v.v[0]);
	v.v[1] = v.v[1] < G_F32_ZERO ? ceilf(v.v[1]) : floorf(v.v[1]);

	return v;
}
vec2f32_t Vec2f32_TruncateAway(vec2f32_t v)
{
	v.v[0] = v.v[0] < G_F32_ZERO ? floorf(v.v[0]) : ceilf(v.v[0]);
	v.v[1] = v.v[1] < G_F32_ZERO ? floorf(v.v[1]) : ceilf(v.v[1]);

	return v;
}
vec2f32_t Vec2f32_CmpLT(vec2f32_t v0, vec2f32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec2f32_t Vec2f32_CmpLE(vec2f32_t v0, vec2f32_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec2f32_t Vec2f32_CmpEQ(vec2f32_t v0, vec2f32_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec2f32_t Vec2f32_CmpGT(vec2f32_t v0, vec2f32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec2f32_t Vec2f32_CmpGE(vec2f32_t v0, vec2f32_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec2f32_t Vec2f32_CmpNE(vec2f32_t v0, vec2f32_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec2f32_t Vec2f32_CmpLTS(vec2f32_t v0, float x)
{
	v0.v[0] = v0.v[0] < x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] < x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec2f32_t Vec2f32_CmpLES(vec2f32_t v0, float x)
{
	v0.v[0] = v0.v[0] <= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec2f32_t Vec2f32_CmpEQS(vec2f32_t v0, float x)
{
	v0.v[0] = v0.v[0] == x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] == x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec2f32_t Vec2f32_CmpGTS(vec2f32_t v0, float x)
{
	v0.v[0] = v0.v[0] > x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] > x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec2f32_t Vec2f32_CmpGES(vec2f32_t v0, float x)
{
	v0.v[0] = v0.v[0] >= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec2f32_t Vec2f32_CmpNES(vec2f32_t v0, float x)
{
	v0.v[0] = v0.v[0] != x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] != x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec2f32_t Vec2f32_Sign(vec2f32_t v)
{
	v.v[0] = v.v[0] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;
	v.v[1] = v.v[1] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;

	return v;
}
vec2f32_t Vec2f32_SignPosNeg(vec2f32_t v)
{
	v.v[0] = v.v[0] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;
	v.v[1] = v.v[1] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;

	return v;
}
vec2f32_t Vec2f32_Zero()
{
	return G_VEC2F32_T_ZERO;
}
vec2f32_t Vec2f32_One()
{
	return G_VEC2F32_T_ONE;
}
vec2f32_t Vec2f32_NegOne()
{
	return Vec2f32_Neg(G_VEC2F32_T_ONE);
}
vec2f32_t Vec2f32_Cross(vec2f32_t v0)
{
	vec2f32_t v;

	v.v[0] = v0.v[1];
	v.v[1] = -v0.v[0];

	return v;
}
vec2f32_t Vec2f32_Lerp(vec2f32_t v0, vec2f32_t v1, vec2f32_t vt)
{
	vec2f32_t v;

	v.v[0] = (G_F32_ONE - vt.v[0]) * v0.v[0] + v1.v[0] * vt.v[0];
	v.v[1] = (G_F32_ONE - vt.v[1]) * v0.v[1] + v1.v[1] * vt.v[1];

	return v;
}
vec2f32_t Vec2f32_LerpS(vec2f32_t v0, vec2f32_t v1, float t)
{
	vec2f32_t v;

	v.v[0] = (G_F32_ONE - t) * v0.v[0] + v1.v[0] * t;
	v.v[1] = (G_F32_ONE - t) * v0.v[1] + v1.v[1] * t;

	return v;
}
vec3f32_t Vec2f32_ToVec3f32(vec2f32_t v, float x0)
{
	vec3f32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;

	return outv;
}
vec4f32_t Vec2f32_ToVec4f32(vec2f32_t v, float x0, float x1)
{
	vec4f32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;

	return outv;
}
vec5f32_t Vec2f32_ToVec5f32(vec2f32_t v, float x0, float x1, float x2)
{
	vec5f32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;

	return outv;
}
vec6f32_t Vec2f32_ToVec6f32(vec2f32_t v, float x0, float x1, float x2, float x3)
{
	vec6f32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;
	outv.v[5] = x3;

	return outv;
}
vec7f32_t Vec2f32_ToVec7f32(vec2f32_t v, float x0, float x1, float x2, float x3, float x4)
{
	vec7f32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;
	outv.v[5] = x3;
	outv.v[6] = x4;

	return outv;
}
vec8f32_t Vec2f32_ToVec8f32(vec2f32_t v, float x0, float x1, float x2, float x3, float x4, float x5)
{
	vec8f32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;
	outv.v[5] = x3;
	outv.v[6] = x4;
	outv.v[7] = x5;

	return outv;
}
vec2u64_t Vec2u64_SetComponent(vec2u64_t v, int index, uint64_t value)
{
	v.v[index] = value;

	return v;
}
vec2u64_t Vec2u64_Vec(uint64_t x0, uint64_t x1)
{
	vec2u64_t v;

	v.v[0] = x0;
	v.v[1] = x1;

	return v;
}
vec2u64_t Vec2u64_Add(vec2u64_t v0, vec2u64_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];

	return v0;
}
vec2u64_t Vec2u64_Sub(vec2u64_t v0, vec2u64_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];

	return v0;
}
uint64_t Vec2u64_GetComponent(vec2u64_t v, int index)
{
	return v.v[index];
}
vec2u64_t Vec2u64_Mul(vec2u64_t v0, vec2u64_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];

	return v0;
}
vec2u64_t Vec2u64_Div(vec2u64_t v0, vec2u64_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];

	return v0;
}
vec2u64_t Vec2u64_Scale(vec2u64_t v, uint64_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;

	return v;
}
vec2u64_t Vec2u64_DivScale(vec2u64_t v, uint64_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;

	return v;
}
vec2u64_t Vec2u64_MA(vec2u64_t v, vec2u64_t dir, uint64_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;

	return v;
}
vec2u64_t Vec2u64_DA(vec2u64_t v, vec2u64_t dir, uint64_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;

	return v;
}
uint64_t Vec2u64_Dot(vec2u64_t v0, vec2u64_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1];
}
uint64_t Vec2u64_LenSq(vec2u64_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1];
}
uint64_t Vec2u64_Len(vec2u64_t v)
{
	return sqrt(Vec2u64_LenSq(v));
}
vec2u64_t Vec2u64_Mod(vec2u64_t v0, vec2u64_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);

	return v0;
}
vec2u64_t Vec2u64_ModS(vec2u64_t v0, uint64_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);

	return v0;
}
vec2u64_t Vec2u64_Min(vec2u64_t v0, vec2u64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];

	return v0;
}
vec2u64_t Vec2u64_Max(vec2u64_t v0, vec2u64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];

	return v0;
}
vec2u64_t Vec2u64_MinS(vec2u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;

	return v0;
}
vec2u64_t Vec2u64_MaxS(vec2u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;

	return v0;
}
vec2u64_t Vec2u64_Clamp(vec2u64_t v, vec2u64_t min, vec2u64_t max)
{
	return Vec2u64_Max(Vec2u64_Min(v, max), min);
}
vec2u64_t Vec2u64_ClampS(vec2u64_t v, uint64_t min, uint64_t max)
{
	return Vec2u64_MaxS(Vec2u64_MinS(v, max), min);
}
vec2u64_t Vec2u64_CmpLT(vec2u64_t v0, vec2u64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec2u64_t Vec2u64_CmpLE(vec2u64_t v0, vec2u64_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec2u64_t Vec2u64_CmpEQ(vec2u64_t v0, vec2u64_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec2u64_t Vec2u64_CmpGT(vec2u64_t v0, vec2u64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec2u64_t Vec2u64_CmpGE(vec2u64_t v0, vec2u64_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec2u64_t Vec2u64_CmpNE(vec2u64_t v0, vec2u64_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec2u64_t Vec2u64_CmpLTS(vec2u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] < x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] < x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec2u64_t Vec2u64_CmpLES(vec2u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec2u64_t Vec2u64_CmpEQS(vec2u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] == x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] == x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec2u64_t Vec2u64_CmpGTS(vec2u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] > x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] > x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec2u64_t Vec2u64_CmpGES(vec2u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec2u64_t Vec2u64_CmpNES(vec2u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] != x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] != x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec2u64_t Vec2u64_Sign(vec2u64_t v)
{
	v.v[0] = v.v[0] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;
	v.v[1] = v.v[1] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;

	return v;
}
vec2u64_t Vec2u64_SignPosNeg(vec2u64_t v)
{
	v.v[0] = v.v[0] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;
	v.v[1] = v.v[1] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;

	return v;
}
vec2u64_t Vec2u64_Zero()
{
	return G_VEC2U64_T_ZERO;
}
vec2u64_t Vec2u64_One()
{
	return G_VEC2U64_T_ONE;
}
vec2u64_t Vec2u64_Cross(vec2u64_t v0)
{
	vec2u64_t v;

	v.v[0] = v0.v[1];
	v.v[1] = (uint64_t)-(int64_t)v0.v[0];

	return v;
}
vec3u64_t Vec2u64_ToVec3u64(vec2u64_t v, uint64_t x0)
{
	vec3u64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;

	return outv;
}
vec4u64_t Vec2u64_ToVec4u64(vec2u64_t v, uint64_t x0, uint64_t x1)
{
	vec4u64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;

	return outv;
}
vec5u64_t Vec2u64_ToVec5u64(vec2u64_t v, uint64_t x0, uint64_t x1, uint64_t x2)
{
	vec5u64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;

	return outv;
}
vec6u64_t Vec2u64_ToVec6u64(vec2u64_t v, uint64_t x0, uint64_t x1, uint64_t x2, uint64_t x3)
{
	vec6u64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;
	outv.v[5] = x3;

	return outv;
}
vec7u64_t Vec2u64_ToVec7u64(vec2u64_t v, uint64_t x0, uint64_t x1, uint64_t x2, uint64_t x3, uint64_t x4)
{
	vec7u64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;
	outv.v[5] = x3;
	outv.v[6] = x4;

	return outv;
}
vec8u64_t Vec2u64_ToVec8u64(vec2u64_t v, uint64_t x0, uint64_t x1, uint64_t x2, uint64_t x3, uint64_t x4, uint64_t x5)
{
	vec8u64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;
	outv.v[5] = x3;
	outv.v[6] = x4;
	outv.v[7] = x5;

	return outv;
}
vec2i64_t Vec2i64_SetComponent(vec2i64_t v, int index, int64_t value)
{
	v.v[index] = value;

	return v;
}
vec2i64_t Vec2i64_Vec(int64_t x0, int64_t x1)
{
	vec2i64_t v;

	v.v[0] = x0;
	v.v[1] = x1;

	return v;
}
vec2i64_t Vec2i64_Add(vec2i64_t v0, vec2i64_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];

	return v0;
}
vec2i64_t Vec2i64_Sub(vec2i64_t v0, vec2i64_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];

	return v0;
}
int64_t Vec2i64_GetComponent(vec2i64_t v, int index)
{
	return v.v[index];
}
vec2i64_t Vec2i64_Mul(vec2i64_t v0, vec2i64_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];

	return v0;
}
vec2i64_t Vec2i64_Div(vec2i64_t v0, vec2i64_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];

	return v0;
}
vec2i64_t Vec2i64_Scale(vec2i64_t v, int64_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;

	return v;
}
vec2i64_t Vec2i64_DivScale(vec2i64_t v, int64_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;

	return v;
}
vec2i64_t Vec2i64_MA(vec2i64_t v, vec2i64_t dir, int64_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;

	return v;
}
vec2i64_t Vec2i64_DA(vec2i64_t v, vec2i64_t dir, int64_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;

	return v;
}
int64_t Vec2i64_Dot(vec2i64_t v0, vec2i64_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1];
}
int64_t Vec2i64_LenSq(vec2i64_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1];
}
int64_t Vec2i64_Len(vec2i64_t v)
{
	return sqrt(Vec2i64_LenSq(v));
}
vec2i64_t Vec2i64_Abs(vec2i64_t v)
{
	v.v[0] = (v.v[0] < 0 ? -v.v[0] : v.v[0]);
	v.v[1] = (v.v[1] < 0 ? -v.v[1] : v.v[1]);

	return v;
}
vec2i64_t Vec2i64_Mod(vec2i64_t v0, vec2i64_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);

	return v0;
}
vec2i64_t Vec2i64_ModS(vec2i64_t v0, int64_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);

	return v0;
}
vec2i64_t Vec2i64_Min(vec2i64_t v0, vec2i64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];

	return v0;
}
vec2i64_t Vec2i64_Max(vec2i64_t v0, vec2i64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];

	return v0;
}
vec2i64_t Vec2i64_MinS(vec2i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;

	return v0;
}
vec2i64_t Vec2i64_MaxS(vec2i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;

	return v0;
}
vec2i64_t Vec2i64_Clamp(vec2i64_t v, vec2i64_t min, vec2i64_t max)
{
	return Vec2i64_Max(Vec2i64_Min(v, max), min);
}
vec2i64_t Vec2i64_ClampS(vec2i64_t v, int64_t min, int64_t max)
{
	return Vec2i64_MaxS(Vec2i64_MinS(v, max), min);
}
vec2i64_t Vec2i64_Neg(vec2i64_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];

	return v;
}
vec2i64_t Vec2i64_CmpLT(vec2i64_t v0, vec2i64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec2i64_t Vec2i64_CmpLE(vec2i64_t v0, vec2i64_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec2i64_t Vec2i64_CmpEQ(vec2i64_t v0, vec2i64_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec2i64_t Vec2i64_CmpGT(vec2i64_t v0, vec2i64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec2i64_t Vec2i64_CmpGE(vec2i64_t v0, vec2i64_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec2i64_t Vec2i64_CmpNE(vec2i64_t v0, vec2i64_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec2i64_t Vec2i64_CmpLTS(vec2i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] < x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] < x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec2i64_t Vec2i64_CmpLES(vec2i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec2i64_t Vec2i64_CmpEQS(vec2i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] == x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] == x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec2i64_t Vec2i64_CmpGTS(vec2i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] > x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] > x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec2i64_t Vec2i64_CmpGES(vec2i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec2i64_t Vec2i64_CmpNES(vec2i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] != x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] != x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec2i64_t Vec2i64_Sign(vec2i64_t v)
{
	v.v[0] = v.v[0] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;
	v.v[1] = v.v[1] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;

	return v;
}
vec2i64_t Vec2i64_SignPosNeg(vec2i64_t v)
{
	v.v[0] = v.v[0] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;
	v.v[1] = v.v[1] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;

	return v;
}
vec2i64_t Vec2i64_Zero()
{
	return G_VEC2I64_T_ZERO;
}
vec2i64_t Vec2i64_One()
{
	return G_VEC2I64_T_ONE;
}
vec2i64_t Vec2i64_NegOne()
{
	return Vec2i64_Neg(G_VEC2I64_T_ONE);
}
vec2i64_t Vec2i64_Cross(vec2i64_t v0)
{
	vec2i64_t v;

	v.v[0] = v0.v[1];
	v.v[1] = -v0.v[0];

	return v;
}
vec3i64_t Vec2i64_ToVec3i64(vec2i64_t v, int64_t x0)
{
	vec3i64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;

	return outv;
}
vec4i64_t Vec2i64_ToVec4i64(vec2i64_t v, int64_t x0, int64_t x1)
{
	vec4i64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;

	return outv;
}
vec5i64_t Vec2i64_ToVec5i64(vec2i64_t v, int64_t x0, int64_t x1, int64_t x2)
{
	vec5i64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;

	return outv;
}
vec6i64_t Vec2i64_ToVec6i64(vec2i64_t v, int64_t x0, int64_t x1, int64_t x2, int64_t x3)
{
	vec6i64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;
	outv.v[5] = x3;

	return outv;
}
vec7i64_t Vec2i64_ToVec7i64(vec2i64_t v, int64_t x0, int64_t x1, int64_t x2, int64_t x3, int64_t x4)
{
	vec7i64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;
	outv.v[5] = x3;
	outv.v[6] = x4;

	return outv;
}
vec8i64_t Vec2i64_ToVec8i64(vec2i64_t v, int64_t x0, int64_t x1, int64_t x2, int64_t x3, int64_t x4, int64_t x5)
{
	vec8i64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;
	outv.v[5] = x3;
	outv.v[6] = x4;
	outv.v[7] = x5;

	return outv;
}
vec2u32_t Vec2u32_SetComponent(vec2u32_t v, int index, uint32_t value)
{
	v.v[index] = value;

	return v;
}
vec2u32_t Vec2u32_Vec(uint32_t x0, uint32_t x1)
{
	vec2u32_t v;

	v.v[0] = x0;
	v.v[1] = x1;

	return v;
}
vec2u32_t Vec2u32_Add(vec2u32_t v0, vec2u32_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];

	return v0;
}
vec2u32_t Vec2u32_Sub(vec2u32_t v0, vec2u32_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];

	return v0;
}
uint32_t Vec2u32_GetComponent(vec2u32_t v, int index)
{
	return v.v[index];
}
vec2u32_t Vec2u32_Mul(vec2u32_t v0, vec2u32_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];

	return v0;
}
vec2u32_t Vec2u32_Div(vec2u32_t v0, vec2u32_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];

	return v0;
}
vec2u32_t Vec2u32_Scale(vec2u32_t v, uint32_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;

	return v;
}
vec2u32_t Vec2u32_DivScale(vec2u32_t v, uint32_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;

	return v;
}
vec2u32_t Vec2u32_MA(vec2u32_t v, vec2u32_t dir, uint32_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;

	return v;
}
vec2u32_t Vec2u32_DA(vec2u32_t v, vec2u32_t dir, uint32_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;

	return v;
}
uint32_t Vec2u32_Dot(vec2u32_t v0, vec2u32_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1];
}
uint32_t Vec2u32_LenSq(vec2u32_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1];
}
uint32_t Vec2u32_Len(vec2u32_t v)
{
	return sqrtf(Vec2u32_LenSq(v));
}
vec2u32_t Vec2u32_Mod(vec2u32_t v0, vec2u32_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);

	return v0;
}
vec2u32_t Vec2u32_ModS(vec2u32_t v0, uint32_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);

	return v0;
}
vec2u32_t Vec2u32_Min(vec2u32_t v0, vec2u32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];

	return v0;
}
vec2u32_t Vec2u32_Max(vec2u32_t v0, vec2u32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];

	return v0;
}
vec2u32_t Vec2u32_MinS(vec2u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;

	return v0;
}
vec2u32_t Vec2u32_MaxS(vec2u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;

	return v0;
}
vec2u32_t Vec2u32_Clamp(vec2u32_t v, vec2u32_t min, vec2u32_t max)
{
	return Vec2u32_Max(Vec2u32_Min(v, max), min);
}
vec2u32_t Vec2u32_ClampS(vec2u32_t v, uint32_t min, uint32_t max)
{
	return Vec2u32_MaxS(Vec2u32_MinS(v, max), min);
}
vec2u32_t Vec2u32_CmpLT(vec2u32_t v0, vec2u32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec2u32_t Vec2u32_CmpLE(vec2u32_t v0, vec2u32_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec2u32_t Vec2u32_CmpEQ(vec2u32_t v0, vec2u32_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec2u32_t Vec2u32_CmpGT(vec2u32_t v0, vec2u32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec2u32_t Vec2u32_CmpGE(vec2u32_t v0, vec2u32_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec2u32_t Vec2u32_CmpNE(vec2u32_t v0, vec2u32_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec2u32_t Vec2u32_CmpLTS(vec2u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] < x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] < x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec2u32_t Vec2u32_CmpLES(vec2u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec2u32_t Vec2u32_CmpEQS(vec2u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] == x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] == x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec2u32_t Vec2u32_CmpGTS(vec2u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] > x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] > x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec2u32_t Vec2u32_CmpGES(vec2u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec2u32_t Vec2u32_CmpNES(vec2u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] != x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] != x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec2u32_t Vec2u32_Sign(vec2u32_t v)
{
	v.v[0] = v.v[0] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;
	v.v[1] = v.v[1] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;

	return v;
}
vec2u32_t Vec2u32_SignPosNeg(vec2u32_t v)
{
	v.v[0] = v.v[0] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;
	v.v[1] = v.v[1] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;

	return v;
}
vec2u32_t Vec2u32_Zero()
{
	return G_VEC2U32_T_ZERO;
}
vec2u32_t Vec2u32_One()
{
	return G_VEC2U32_T_ONE;
}
vec2u32_t Vec2u32_Cross(vec2u32_t v0)
{
	vec2u32_t v;

	v.v[0] = v0.v[1];
	v.v[1] = (uint32_t)-(int32_t)v0.v[0];

	return v;
}
vec3u32_t Vec2u32_ToVec3u32(vec2u32_t v, uint32_t x0)
{
	vec3u32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;

	return outv;
}
vec4u32_t Vec2u32_ToVec4u32(vec2u32_t v, uint32_t x0, uint32_t x1)
{
	vec4u32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;

	return outv;
}
vec5u32_t Vec2u32_ToVec5u32(vec2u32_t v, uint32_t x0, uint32_t x1, uint32_t x2)
{
	vec5u32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;

	return outv;
}
vec6u32_t Vec2u32_ToVec6u32(vec2u32_t v, uint32_t x0, uint32_t x1, uint32_t x2, uint32_t x3)
{
	vec6u32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;
	outv.v[5] = x3;

	return outv;
}
vec7u32_t Vec2u32_ToVec7u32(vec2u32_t v, uint32_t x0, uint32_t x1, uint32_t x2, uint32_t x3, uint32_t x4)
{
	vec7u32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;
	outv.v[5] = x3;
	outv.v[6] = x4;

	return outv;
}
vec8u32_t Vec2u32_ToVec8u32(vec2u32_t v, uint32_t x0, uint32_t x1, uint32_t x2, uint32_t x3, uint32_t x4, uint32_t x5)
{
	vec8u32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;
	outv.v[5] = x3;
	outv.v[6] = x4;
	outv.v[7] = x5;

	return outv;
}
vec2i32_t Vec2i32_SetComponent(vec2i32_t v, int index, int32_t value)
{
	v.v[index] = value;

	return v;
}
vec2i32_t Vec2i32_Vec(int32_t x0, int32_t x1)
{
	vec2i32_t v;

	v.v[0] = x0;
	v.v[1] = x1;

	return v;
}
vec2i32_t Vec2i32_Add(vec2i32_t v0, vec2i32_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];

	return v0;
}
vec2i32_t Vec2i32_Sub(vec2i32_t v0, vec2i32_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];

	return v0;
}
int32_t Vec2i32_GetComponent(vec2i32_t v, int index)
{
	return v.v[index];
}
vec2i32_t Vec2i32_Mul(vec2i32_t v0, vec2i32_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];

	return v0;
}
vec2i32_t Vec2i32_Div(vec2i32_t v0, vec2i32_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];

	return v0;
}
vec2i32_t Vec2i32_Scale(vec2i32_t v, int32_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;

	return v;
}
vec2i32_t Vec2i32_DivScale(vec2i32_t v, int32_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;

	return v;
}
vec2i32_t Vec2i32_MA(vec2i32_t v, vec2i32_t dir, int32_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;

	return v;
}
vec2i32_t Vec2i32_DA(vec2i32_t v, vec2i32_t dir, int32_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;

	return v;
}
int32_t Vec2i32_Dot(vec2i32_t v0, vec2i32_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1];
}
int32_t Vec2i32_LenSq(vec2i32_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1];
}
int32_t Vec2i32_Len(vec2i32_t v)
{
	return sqrtf(Vec2i32_LenSq(v));
}
vec2i32_t Vec2i32_Abs(vec2i32_t v)
{
	v.v[0] = (v.v[0] < 0 ? -v.v[0] : v.v[0]);
	v.v[1] = (v.v[1] < 0 ? -v.v[1] : v.v[1]);

	return v;
}
vec2i32_t Vec2i32_Mod(vec2i32_t v0, vec2i32_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);

	return v0;
}
vec2i32_t Vec2i32_ModS(vec2i32_t v0, int32_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);

	return v0;
}
vec2i32_t Vec2i32_Min(vec2i32_t v0, vec2i32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];

	return v0;
}
vec2i32_t Vec2i32_Max(vec2i32_t v0, vec2i32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];

	return v0;
}
vec2i32_t Vec2i32_MinS(vec2i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;

	return v0;
}
vec2i32_t Vec2i32_MaxS(vec2i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;

	return v0;
}
vec2i32_t Vec2i32_Clamp(vec2i32_t v, vec2i32_t min, vec2i32_t max)
{
	return Vec2i32_Max(Vec2i32_Min(v, max), min);
}
vec2i32_t Vec2i32_ClampS(vec2i32_t v, int32_t min, int32_t max)
{
	return Vec2i32_MaxS(Vec2i32_MinS(v, max), min);
}
vec2i32_t Vec2i32_Neg(vec2i32_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];

	return v;
}
vec2i32_t Vec2i32_CmpLT(vec2i32_t v0, vec2i32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec2i32_t Vec2i32_CmpLE(vec2i32_t v0, vec2i32_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec2i32_t Vec2i32_CmpEQ(vec2i32_t v0, vec2i32_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec2i32_t Vec2i32_CmpGT(vec2i32_t v0, vec2i32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec2i32_t Vec2i32_CmpGE(vec2i32_t v0, vec2i32_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec2i32_t Vec2i32_CmpNE(vec2i32_t v0, vec2i32_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec2i32_t Vec2i32_CmpLTS(vec2i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] < x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] < x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec2i32_t Vec2i32_CmpLES(vec2i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec2i32_t Vec2i32_CmpEQS(vec2i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] == x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] == x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec2i32_t Vec2i32_CmpGTS(vec2i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] > x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] > x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec2i32_t Vec2i32_CmpGES(vec2i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec2i32_t Vec2i32_CmpNES(vec2i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] != x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] != x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec2i32_t Vec2i32_Sign(vec2i32_t v)
{
	v.v[0] = v.v[0] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;
	v.v[1] = v.v[1] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;

	return v;
}
vec2i32_t Vec2i32_SignPosNeg(vec2i32_t v)
{
	v.v[0] = v.v[0] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;
	v.v[1] = v.v[1] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;

	return v;
}
vec2i32_t Vec2i32_Zero()
{
	return G_VEC2I32_T_ZERO;
}
vec2i32_t Vec2i32_One()
{
	return G_VEC2I32_T_ONE;
}
vec2i32_t Vec2i32_NegOne()
{
	return Vec2i32_Neg(G_VEC2I32_T_ONE);
}
vec2i32_t Vec2i32_Cross(vec2i32_t v0)
{
	vec2i32_t v;

	v.v[0] = v0.v[1];
	v.v[1] = -v0.v[0];

	return v;
}
vec3i32_t Vec2i32_ToVec3i32(vec2i32_t v, int32_t x0)
{
	vec3i32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;

	return outv;
}
vec4i32_t Vec2i32_ToVec4i32(vec2i32_t v, int32_t x0, int32_t x1)
{
	vec4i32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;

	return outv;
}
vec5i32_t Vec2i32_ToVec5i32(vec2i32_t v, int32_t x0, int32_t x1, int32_t x2)
{
	vec5i32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;

	return outv;
}
vec6i32_t Vec2i32_ToVec6i32(vec2i32_t v, int32_t x0, int32_t x1, int32_t x2, int32_t x3)
{
	vec6i32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;
	outv.v[5] = x3;

	return outv;
}
vec7i32_t Vec2i32_ToVec7i32(vec2i32_t v, int32_t x0, int32_t x1, int32_t x2, int32_t x3, int32_t x4)
{
	vec7i32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;
	outv.v[5] = x3;
	outv.v[6] = x4;

	return outv;
}
vec8i32_t Vec2i32_ToVec8i32(vec2i32_t v, int32_t x0, int32_t x1, int32_t x2, int32_t x3, int32_t x4, int32_t x5)
{
	vec8i32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;
	outv.v[5] = x3;
	outv.v[6] = x4;
	outv.v[7] = x5;

	return outv;
}
vec2u16_t Vec2u16_SetComponent(vec2u16_t v, int index, uint16_t value)
{
	v.v[index] = value;

	return v;
}
vec2u16_t Vec2u16_Vec(uint16_t x0, uint16_t x1)
{
	vec2u16_t v;

	v.v[0] = x0;
	v.v[1] = x1;

	return v;
}
vec2u16_t Vec2u16_Add(vec2u16_t v0, vec2u16_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];

	return v0;
}
vec2u16_t Vec2u16_Sub(vec2u16_t v0, vec2u16_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];

	return v0;
}
uint16_t Vec2u16_GetComponent(vec2u16_t v, int index)
{
	return v.v[index];
}
vec2u16_t Vec2u16_Mul(vec2u16_t v0, vec2u16_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];

	return v0;
}
vec2u16_t Vec2u16_Div(vec2u16_t v0, vec2u16_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];

	return v0;
}
vec2u16_t Vec2u16_Scale(vec2u16_t v, uint16_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;

	return v;
}
vec2u16_t Vec2u16_DivScale(vec2u16_t v, uint16_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;

	return v;
}
vec2u16_t Vec2u16_MA(vec2u16_t v, vec2u16_t dir, uint16_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;

	return v;
}
vec2u16_t Vec2u16_DA(vec2u16_t v, vec2u16_t dir, uint16_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;

	return v;
}
uint16_t Vec2u16_Dot(vec2u16_t v0, vec2u16_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1];
}
uint16_t Vec2u16_LenSq(vec2u16_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1];
}
uint16_t Vec2u16_Len(vec2u16_t v)
{
	return sqrtf(Vec2u16_LenSq(v));
}
vec2u16_t Vec2u16_Mod(vec2u16_t v0, vec2u16_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);

	return v0;
}
vec2u16_t Vec2u16_ModS(vec2u16_t v0, uint16_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);

	return v0;
}
vec2u16_t Vec2u16_Min(vec2u16_t v0, vec2u16_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];

	return v0;
}
vec2u16_t Vec2u16_Max(vec2u16_t v0, vec2u16_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];

	return v0;
}
vec2u16_t Vec2u16_MinS(vec2u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;

	return v0;
}
vec2u16_t Vec2u16_MaxS(vec2u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;

	return v0;
}
vec2u16_t Vec2u16_Clamp(vec2u16_t v, vec2u16_t min, vec2u16_t max)
{
	return Vec2u16_Max(Vec2u16_Min(v, max), min);
}
vec2u16_t Vec2u16_ClampS(vec2u16_t v, uint16_t min, uint16_t max)
{
	return Vec2u16_MaxS(Vec2u16_MinS(v, max), min);
}
vec2u16_t Vec2u16_CmpLT(vec2u16_t v0, vec2u16_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec2u16_t Vec2u16_CmpLE(vec2u16_t v0, vec2u16_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec2u16_t Vec2u16_CmpEQ(vec2u16_t v0, vec2u16_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec2u16_t Vec2u16_CmpGT(vec2u16_t v0, vec2u16_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec2u16_t Vec2u16_CmpGE(vec2u16_t v0, vec2u16_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec2u16_t Vec2u16_CmpNE(vec2u16_t v0, vec2u16_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec2u16_t Vec2u16_CmpLTS(vec2u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] < x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] < x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec2u16_t Vec2u16_CmpLES(vec2u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec2u16_t Vec2u16_CmpEQS(vec2u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] == x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] == x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec2u16_t Vec2u16_CmpGTS(vec2u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] > x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] > x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec2u16_t Vec2u16_CmpGES(vec2u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec2u16_t Vec2u16_CmpNES(vec2u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] != x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] != x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec2u16_t Vec2u16_Sign(vec2u16_t v)
{
	v.v[0] = v.v[0] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;
	v.v[1] = v.v[1] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;

	return v;
}
vec2u16_t Vec2u16_SignPosNeg(vec2u16_t v)
{
	v.v[0] = v.v[0] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;
	v.v[1] = v.v[1] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;

	return v;
}
vec2u16_t Vec2u16_Zero()
{
	return G_VEC2U16_T_ZERO;
}
vec2u16_t Vec2u16_One()
{
	return G_VEC2U16_T_ONE;
}
vec2u16_t Vec2u16_Cross(vec2u16_t v0)
{
	vec2u16_t v;

	v.v[0] = v0.v[1];
	v.v[1] = -v0.v[0];

	return v;
}
vec3u16_t Vec2u16_ToVec3u16(vec2u16_t v, uint16_t x0)
{
	vec3u16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;

	return outv;
}
vec4u16_t Vec2u16_ToVec4u16(vec2u16_t v, uint16_t x0, uint16_t x1)
{
	vec4u16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;

	return outv;
}
vec5u16_t Vec2u16_ToVec5u16(vec2u16_t v, uint16_t x0, uint16_t x1, uint16_t x2)
{
	vec5u16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;

	return outv;
}
vec6u16_t Vec2u16_ToVec6u16(vec2u16_t v, uint16_t x0, uint16_t x1, uint16_t x2, uint16_t x3)
{
	vec6u16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;
	outv.v[5] = x3;

	return outv;
}
vec7u16_t Vec2u16_ToVec7u16(vec2u16_t v, uint16_t x0, uint16_t x1, uint16_t x2, uint16_t x3, uint16_t x4)
{
	vec7u16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;
	outv.v[5] = x3;
	outv.v[6] = x4;

	return outv;
}
vec8u16_t Vec2u16_ToVec8u16(vec2u16_t v, uint16_t x0, uint16_t x1, uint16_t x2, uint16_t x3, uint16_t x4, uint16_t x5)
{
	vec8u16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;
	outv.v[5] = x3;
	outv.v[6] = x4;
	outv.v[7] = x5;

	return outv;
}
vec2i16_t Vec2i16_SetComponent(vec2i16_t v, int index, int16_t value)
{
	v.v[index] = value;

	return v;
}
vec2i16_t Vec2i16_Vec(int16_t x0, int16_t x1)
{
	vec2i16_t v;

	v.v[0] = x0;
	v.v[1] = x1;

	return v;
}
vec2i16_t Vec2i16_Add(vec2i16_t v0, vec2i16_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];

	return v0;
}
vec2i16_t Vec2i16_Sub(vec2i16_t v0, vec2i16_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];

	return v0;
}
int16_t Vec2i16_GetComponent(vec2i16_t v, int index)
{
	return v.v[index];
}
vec2i16_t Vec2i16_Mul(vec2i16_t v0, vec2i16_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];

	return v0;
}
vec2i16_t Vec2i16_Div(vec2i16_t v0, vec2i16_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];

	return v0;
}
vec2i16_t Vec2i16_Scale(vec2i16_t v, int16_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;

	return v;
}
vec2i16_t Vec2i16_DivScale(vec2i16_t v, int16_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;

	return v;
}
vec2i16_t Vec2i16_MA(vec2i16_t v, vec2i16_t dir, int16_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;

	return v;
}
vec2i16_t Vec2i16_DA(vec2i16_t v, vec2i16_t dir, int16_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;

	return v;
}
int16_t Vec2i16_Dot(vec2i16_t v0, vec2i16_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1];
}
int16_t Vec2i16_LenSq(vec2i16_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1];
}
int16_t Vec2i16_Len(vec2i16_t v)
{
	return sqrtf(Vec2i16_LenSq(v));
}
vec2i16_t Vec2i16_Abs(vec2i16_t v)
{
	v.v[0] = (v.v[0] < 0 ? -v.v[0] : v.v[0]);
	v.v[1] = (v.v[1] < 0 ? -v.v[1] : v.v[1]);

	return v;
}
vec2i16_t Vec2i16_Mod(vec2i16_t v0, vec2i16_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);

	return v0;
}
vec2i16_t Vec2i16_ModS(vec2i16_t v0, int16_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);

	return v0;
}
vec2i16_t Vec2i16_Min(vec2i16_t v0, vec2i16_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];

	return v0;
}
vec2i16_t Vec2i16_Max(vec2i16_t v0, vec2i16_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];

	return v0;
}
vec2i16_t Vec2i16_MinS(vec2i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;

	return v0;
}
vec2i16_t Vec2i16_MaxS(vec2i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;

	return v0;
}
vec2i16_t Vec2i16_Clamp(vec2i16_t v, vec2i16_t min, vec2i16_t max)
{
	return Vec2i16_Max(Vec2i16_Min(v, max), min);
}
vec2i16_t Vec2i16_ClampS(vec2i16_t v, int16_t min, int16_t max)
{
	return Vec2i16_MaxS(Vec2i16_MinS(v, max), min);
}
vec2i16_t Vec2i16_Neg(vec2i16_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];

	return v;
}
vec2i16_t Vec2i16_CmpLT(vec2i16_t v0, vec2i16_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec2i16_t Vec2i16_CmpLE(vec2i16_t v0, vec2i16_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec2i16_t Vec2i16_CmpEQ(vec2i16_t v0, vec2i16_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec2i16_t Vec2i16_CmpGT(vec2i16_t v0, vec2i16_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec2i16_t Vec2i16_CmpGE(vec2i16_t v0, vec2i16_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec2i16_t Vec2i16_CmpNE(vec2i16_t v0, vec2i16_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec2i16_t Vec2i16_CmpLTS(vec2i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] < x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] < x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec2i16_t Vec2i16_CmpLES(vec2i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec2i16_t Vec2i16_CmpEQS(vec2i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] == x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] == x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec2i16_t Vec2i16_CmpGTS(vec2i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] > x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] > x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec2i16_t Vec2i16_CmpGES(vec2i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec2i16_t Vec2i16_CmpNES(vec2i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] != x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] != x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec2i16_t Vec2i16_Sign(vec2i16_t v)
{
	v.v[0] = v.v[0] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;
	v.v[1] = v.v[1] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;

	return v;
}
vec2i16_t Vec2i16_SignPosNeg(vec2i16_t v)
{
	v.v[0] = v.v[0] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;
	v.v[1] = v.v[1] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;

	return v;
}
vec2i16_t Vec2i16_Zero()
{
	return G_VEC2I16_T_ZERO;
}
vec2i16_t Vec2i16_One()
{
	return G_VEC2I16_T_ONE;
}
vec2i16_t Vec2i16_NegOne()
{
	return Vec2i16_Neg(G_VEC2I16_T_ONE);
}
vec2i16_t Vec2i16_Cross(vec2i16_t v0)
{
	vec2i16_t v;

	v.v[0] = v0.v[1];
	v.v[1] = -v0.v[0];

	return v;
}
vec3i16_t Vec2i16_ToVec3i16(vec2i16_t v, int16_t x0)
{
	vec3i16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;

	return outv;
}
vec4i16_t Vec2i16_ToVec4i16(vec2i16_t v, int16_t x0, int16_t x1)
{
	vec4i16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;

	return outv;
}
vec5i16_t Vec2i16_ToVec5i16(vec2i16_t v, int16_t x0, int16_t x1, int16_t x2)
{
	vec5i16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;

	return outv;
}
vec6i16_t Vec2i16_ToVec6i16(vec2i16_t v, int16_t x0, int16_t x1, int16_t x2, int16_t x3)
{
	vec6i16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;
	outv.v[5] = x3;

	return outv;
}
vec7i16_t Vec2i16_ToVec7i16(vec2i16_t v, int16_t x0, int16_t x1, int16_t x2, int16_t x3, int16_t x4)
{
	vec7i16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;
	outv.v[5] = x3;
	outv.v[6] = x4;

	return outv;
}
vec8i16_t Vec2i16_ToVec8i16(vec2i16_t v, int16_t x0, int16_t x1, int16_t x2, int16_t x3, int16_t x4, int16_t x5)
{
	vec8i16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;
	outv.v[5] = x3;
	outv.v[6] = x4;
	outv.v[7] = x5;

	return outv;
}
vec2u8_t Vec2u8_SetComponent(vec2u8_t v, int index, uint8_t value)
{
	v.v[index] = value;

	return v;
}
vec2u8_t Vec2u8_Vec(uint8_t x0, uint8_t x1)
{
	vec2u8_t v;

	v.v[0] = x0;
	v.v[1] = x1;

	return v;
}
vec2u8_t Vec2u8_Add(vec2u8_t v0, vec2u8_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];

	return v0;
}
vec2u8_t Vec2u8_Sub(vec2u8_t v0, vec2u8_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];

	return v0;
}
uint8_t Vec2u8_GetComponent(vec2u8_t v, int index)
{
	return v.v[index];
}
vec2u8_t Vec2u8_Mul(vec2u8_t v0, vec2u8_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];

	return v0;
}
vec2u8_t Vec2u8_Div(vec2u8_t v0, vec2u8_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];

	return v0;
}
vec2u8_t Vec2u8_Scale(vec2u8_t v, uint8_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;

	return v;
}
vec2u8_t Vec2u8_DivScale(vec2u8_t v, uint8_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;

	return v;
}
vec2u8_t Vec2u8_MA(vec2u8_t v, vec2u8_t dir, uint8_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;

	return v;
}
vec2u8_t Vec2u8_DA(vec2u8_t v, vec2u8_t dir, uint8_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;

	return v;
}
uint8_t Vec2u8_Dot(vec2u8_t v0, vec2u8_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1];
}
uint8_t Vec2u8_LenSq(vec2u8_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1];
}
uint8_t Vec2u8_Len(vec2u8_t v)
{
	return sqrtf(Vec2u8_LenSq(v));
}
vec2u8_t Vec2u8_Mod(vec2u8_t v0, vec2u8_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);

	return v0;
}
vec2u8_t Vec2u8_ModS(vec2u8_t v0, uint8_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);

	return v0;
}
vec2u8_t Vec2u8_Min(vec2u8_t v0, vec2u8_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];

	return v0;
}
vec2u8_t Vec2u8_Max(vec2u8_t v0, vec2u8_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];

	return v0;
}
vec2u8_t Vec2u8_MinS(vec2u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;

	return v0;
}
vec2u8_t Vec2u8_MaxS(vec2u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;

	return v0;
}
vec2u8_t Vec2u8_Clamp(vec2u8_t v, vec2u8_t min, vec2u8_t max)
{
	return Vec2u8_Max(Vec2u8_Min(v, max), min);
}
vec2u8_t Vec2u8_ClampS(vec2u8_t v, uint8_t min, uint8_t max)
{
	return Vec2u8_MaxS(Vec2u8_MinS(v, max), min);
}
vec2u8_t Vec2u8_CmpLT(vec2u8_t v0, vec2u8_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec2u8_t Vec2u8_CmpLE(vec2u8_t v0, vec2u8_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec2u8_t Vec2u8_CmpEQ(vec2u8_t v0, vec2u8_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec2u8_t Vec2u8_CmpGT(vec2u8_t v0, vec2u8_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec2u8_t Vec2u8_CmpGE(vec2u8_t v0, vec2u8_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec2u8_t Vec2u8_CmpNE(vec2u8_t v0, vec2u8_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec2u8_t Vec2u8_CmpLTS(vec2u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] < x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] < x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec2u8_t Vec2u8_CmpLES(vec2u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec2u8_t Vec2u8_CmpEQS(vec2u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] == x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] == x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec2u8_t Vec2u8_CmpGTS(vec2u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] > x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] > x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec2u8_t Vec2u8_CmpGES(vec2u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec2u8_t Vec2u8_CmpNES(vec2u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] != x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] != x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec2u8_t Vec2u8_Sign(vec2u8_t v)
{
	v.v[0] = v.v[0] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;
	v.v[1] = v.v[1] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;

	return v;
}
vec2u8_t Vec2u8_SignPosNeg(vec2u8_t v)
{
	v.v[0] = v.v[0] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;
	v.v[1] = v.v[1] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;

	return v;
}
vec2u8_t Vec2u8_Zero()
{
	return G_VEC2U8_T_ZERO;
}
vec2u8_t Vec2u8_One()
{
	return G_VEC2U8_T_ONE;
}
vec2u8_t Vec2u8_Cross(vec2u8_t v0)
{
	vec2u8_t v;

	v.v[0] = v0.v[1];
	v.v[1] = -v0.v[0];

	return v;
}
vec3u8_t Vec2u8_ToVec3u8(vec2u8_t v, uint8_t x0)
{
	vec3u8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;

	return outv;
}
vec4u8_t Vec2u8_ToVec4u8(vec2u8_t v, uint8_t x0, uint8_t x1)
{
	vec4u8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;

	return outv;
}
vec5u8_t Vec2u8_ToVec5u8(vec2u8_t v, uint8_t x0, uint8_t x1, uint8_t x2)
{
	vec5u8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;

	return outv;
}
vec6u8_t Vec2u8_ToVec6u8(vec2u8_t v, uint8_t x0, uint8_t x1, uint8_t x2, uint8_t x3)
{
	vec6u8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;
	outv.v[5] = x3;

	return outv;
}
vec7u8_t Vec2u8_ToVec7u8(vec2u8_t v, uint8_t x0, uint8_t x1, uint8_t x2, uint8_t x3, uint8_t x4)
{
	vec7u8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;
	outv.v[5] = x3;
	outv.v[6] = x4;

	return outv;
}
vec8u8_t Vec2u8_ToVec8u8(vec2u8_t v, uint8_t x0, uint8_t x1, uint8_t x2, uint8_t x3, uint8_t x4, uint8_t x5)
{
	vec8u8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;
	outv.v[5] = x3;
	outv.v[6] = x4;
	outv.v[7] = x5;

	return outv;
}
vec2i8_t Vec2i8_SetComponent(vec2i8_t v, int index, int8_t value)
{
	v.v[index] = value;

	return v;
}
vec2i8_t Vec2i8_Vec(int8_t x0, int8_t x1)
{
	vec2i8_t v;

	v.v[0] = x0;
	v.v[1] = x1;

	return v;
}
vec2i8_t Vec2i8_Add(vec2i8_t v0, vec2i8_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];

	return v0;
}
vec2i8_t Vec2i8_Sub(vec2i8_t v0, vec2i8_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];

	return v0;
}
int8_t Vec2i8_GetComponent(vec2i8_t v, int index)
{
	return v.v[index];
}
vec2i8_t Vec2i8_Mul(vec2i8_t v0, vec2i8_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];

	return v0;
}
vec2i8_t Vec2i8_Div(vec2i8_t v0, vec2i8_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];

	return v0;
}
vec2i8_t Vec2i8_Scale(vec2i8_t v, int8_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;

	return v;
}
vec2i8_t Vec2i8_DivScale(vec2i8_t v, int8_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;

	return v;
}
vec2i8_t Vec2i8_MA(vec2i8_t v, vec2i8_t dir, int8_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;

	return v;
}
vec2i8_t Vec2i8_DA(vec2i8_t v, vec2i8_t dir, int8_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;

	return v;
}
int8_t Vec2i8_Dot(vec2i8_t v0, vec2i8_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1];
}
int8_t Vec2i8_LenSq(vec2i8_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1];
}
int8_t Vec2i8_Len(vec2i8_t v)
{
	return sqrtf(Vec2i8_LenSq(v));
}
vec2i8_t Vec2i8_Abs(vec2i8_t v)
{
	v.v[0] = (v.v[0] < 0 ? -v.v[0] : v.v[0]);
	v.v[1] = (v.v[1] < 0 ? -v.v[1] : v.v[1]);

	return v;
}
vec2i8_t Vec2i8_Mod(vec2i8_t v0, vec2i8_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);

	return v0;
}
vec2i8_t Vec2i8_ModS(vec2i8_t v0, int8_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);

	return v0;
}
vec2i8_t Vec2i8_Min(vec2i8_t v0, vec2i8_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];

	return v0;
}
vec2i8_t Vec2i8_Max(vec2i8_t v0, vec2i8_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];

	return v0;
}
vec2i8_t Vec2i8_MinS(vec2i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;

	return v0;
}
vec2i8_t Vec2i8_MaxS(vec2i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;

	return v0;
}
vec2i8_t Vec2i8_Clamp(vec2i8_t v, vec2i8_t min, vec2i8_t max)
{
	return Vec2i8_Max(Vec2i8_Min(v, max), min);
}
vec2i8_t Vec2i8_ClampS(vec2i8_t v, int8_t min, int8_t max)
{
	return Vec2i8_MaxS(Vec2i8_MinS(v, max), min);
}
vec2i8_t Vec2i8_Neg(vec2i8_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];

	return v;
}
vec2i8_t Vec2i8_CmpLT(vec2i8_t v0, vec2i8_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec2i8_t Vec2i8_CmpLE(vec2i8_t v0, vec2i8_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec2i8_t Vec2i8_CmpEQ(vec2i8_t v0, vec2i8_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec2i8_t Vec2i8_CmpGT(vec2i8_t v0, vec2i8_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec2i8_t Vec2i8_CmpGE(vec2i8_t v0, vec2i8_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec2i8_t Vec2i8_CmpNE(vec2i8_t v0, vec2i8_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec2i8_t Vec2i8_CmpLTS(vec2i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] < x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] < x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec2i8_t Vec2i8_CmpLES(vec2i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec2i8_t Vec2i8_CmpEQS(vec2i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] == x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] == x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec2i8_t Vec2i8_CmpGTS(vec2i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] > x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] > x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec2i8_t Vec2i8_CmpGES(vec2i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec2i8_t Vec2i8_CmpNES(vec2i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] != x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] != x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec2i8_t Vec2i8_Sign(vec2i8_t v)
{
	v.v[0] = v.v[0] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;
	v.v[1] = v.v[1] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;

	return v;
}
vec2i8_t Vec2i8_SignPosNeg(vec2i8_t v)
{
	v.v[0] = v.v[0] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;
	v.v[1] = v.v[1] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;

	return v;
}
vec2i8_t Vec2i8_Zero()
{
	return G_VEC2I8_T_ZERO;
}
vec2i8_t Vec2i8_One()
{
	return G_VEC2I8_T_ONE;
}
vec2i8_t Vec2i8_NegOne()
{
	return Vec2i8_Neg(G_VEC2I8_T_ONE);
}
vec2i8_t Vec2i8_Cross(vec2i8_t v0)
{
	vec2i8_t v;

	v.v[0] = v0.v[1];
	v.v[1] = -v0.v[0];

	return v;
}
vec3i8_t Vec2i8_ToVec3i8(vec2i8_t v, int8_t x0)
{
	vec3i8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;

	return outv;
}
vec4i8_t Vec2i8_ToVec4i8(vec2i8_t v, int8_t x0, int8_t x1)
{
	vec4i8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;

	return outv;
}
vec5i8_t Vec2i8_ToVec5i8(vec2i8_t v, int8_t x0, int8_t x1, int8_t x2)
{
	vec5i8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;

	return outv;
}
vec6i8_t Vec2i8_ToVec6i8(vec2i8_t v, int8_t x0, int8_t x1, int8_t x2, int8_t x3)
{
	vec6i8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;
	outv.v[5] = x3;

	return outv;
}
vec7i8_t Vec2i8_ToVec7i8(vec2i8_t v, int8_t x0, int8_t x1, int8_t x2, int8_t x3, int8_t x4)
{
	vec7i8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;
	outv.v[5] = x3;
	outv.v[6] = x4;

	return outv;
}
vec8i8_t Vec2i8_ToVec8i8(vec2i8_t v, int8_t x0, int8_t x1, int8_t x2, int8_t x3, int8_t x4, int8_t x5)
{
	vec8i8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = x0;
	outv.v[3] = x1;
	outv.v[4] = x2;
	outv.v[5] = x3;
	outv.v[6] = x4;
	outv.v[7] = x5;

	return outv;
}
vec3f64_t Vec3f64_SetComponent(vec3f64_t v, int index, double value)
{
	v.v[index] = value;

	return v;
}
vec3f64_t Vec3f64_Vec(double x0, double x1, double x2)
{
	vec3f64_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;

	return v;
}
vec3f64_t Vec3f64_Add(vec3f64_t v0, vec3f64_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];

	return v0;
}
vec3f64_t Vec3f64_Sub(vec3f64_t v0, vec3f64_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];

	return v0;
}
double Vec3f64_GetComponent(vec3f64_t v, int index)
{
	return v.v[index];
}
vec3f64_t Vec3f64_Mul(vec3f64_t v0, vec3f64_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];

	return v0;
}
vec3f64_t Vec3f64_Div(vec3f64_t v0, vec3f64_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];

	return v0;
}
vec3f64_t Vec3f64_Scale(vec3f64_t v, double scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;

	return v;
}
vec3f64_t Vec3f64_DivScale(vec3f64_t v, double divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;

	return v;
}
vec3f64_t Vec3f64_MA(vec3f64_t v, vec3f64_t dir, double scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;

	return v;
}
vec3f64_t Vec3f64_DA(vec3f64_t v, vec3f64_t dir, double divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;

	return v;
}
double Vec3f64_Dot(vec3f64_t v0, vec3f64_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2];
}
double Vec3f64_LenSq(vec3f64_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2];
}
double Vec3f64_Len(vec3f64_t v)
{
	return sqrt(Vec3f64_LenSq(v));
}
vec3f64_t Vec3f64_Normalise(vec3f64_t v)
{
	double lensq = Vec3f64_LenSq(v);

	if (lensq == G_F64_ZERO)
		return v;
	else
		return Vec3f64_Scale(v, G_F64_ONE / sqrt(lensq));
}
vec3f64_t Vec3f64_Abs(vec3f64_t v)
{
	v.v[0] = fabs(v.v[0]);
	v.v[1] = fabs(v.v[1]);
	v.v[2] = fabs(v.v[2]);

	return v;
}
vec3f64_t Vec3f64_Floor(vec3f64_t v)
{
	v.v[0] = floor(v.v[0]);
	v.v[1] = floor(v.v[1]);
	v.v[2] = floor(v.v[2]);

	return v;
}
vec3f64_t Vec3f64_Ceil(vec3f64_t v)
{
	v.v[0] = ceil(v.v[0]);
	v.v[1] = ceil(v.v[1]);
	v.v[2] = ceil(v.v[2]);

	return v;
}
vec3f64_t Vec3f64_Fract(vec3f64_t v)
{
	return Vec3f64_Sub(v, Vec3f64_Floor(v));
}
vec3f64_t Vec3f64_Mod(vec3f64_t v0, vec3f64_t v1)
{
	v0.v[0] = fmod(v0.v[0], v1.v[0]);
	v0.v[1] = fmod(v0.v[1], v1.v[1]);
	v0.v[2] = fmod(v0.v[2], v1.v[2]);

	return v0;
}
vec3f64_t Vec3f64_ModS(vec3f64_t v0, double x)
{
	v0.v[0] = fmod(v0.v[0], x);
	v0.v[1] = fmod(v0.v[1], x);
	v0.v[2] = fmod(v0.v[2], x);

	return v0;
}
vec3f64_t Vec3f64_Min(vec3f64_t v0, vec3f64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];

	return v0;
}
vec3f64_t Vec3f64_Max(vec3f64_t v0, vec3f64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];

	return v0;
}
vec3f64_t Vec3f64_MinS(vec3f64_t v0, double x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;

	return v0;
}
vec3f64_t Vec3f64_MaxS(vec3f64_t v0, double x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;

	return v0;
}
vec3f64_t Vec3f64_Clamp(vec3f64_t v, vec3f64_t min, vec3f64_t max)
{
	return Vec3f64_Max(Vec3f64_Min(v, max), min);
}
vec3f64_t Vec3f64_ClampS(vec3f64_t v, double min, double max)
{
	return Vec3f64_MaxS(Vec3f64_MinS(v, max), min);
}
vec3f64_t Vec3f64_Neg(vec3f64_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];

	return v;
}
vec3f64_t Vec3f64_Reciprocal(vec3f64_t v)
{
	v.v[0] = G_F64_ONE / v.v[0];
	v.v[1] = G_F64_ONE / v.v[1];
	v.v[2] = G_F64_ONE / v.v[2];

	return v;
}
vec3f64_t Vec3f64_Truncate(vec3f64_t v)
{
	v.v[0] = v.v[0] < G_F64_ZERO ? ceil(v.v[0]) : floor(v.v[0]);
	v.v[1] = v.v[1] < G_F64_ZERO ? ceil(v.v[1]) : floor(v.v[1]);
	v.v[2] = v.v[2] < G_F64_ZERO ? ceil(v.v[2]) : floor(v.v[2]);

	return v;
}
vec3f64_t Vec3f64_TruncateAway(vec3f64_t v)
{
	v.v[0] = v.v[0] < G_F64_ZERO ? floor(v.v[0]) : ceil(v.v[0]);
	v.v[1] = v.v[1] < G_F64_ZERO ? floor(v.v[1]) : ceil(v.v[1]);
	v.v[2] = v.v[2] < G_F64_ZERO ? floor(v.v[2]) : ceil(v.v[2]);

	return v;
}
vec3f64_t Vec3f64_CmpLT(vec3f64_t v0, vec3f64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec3f64_t Vec3f64_CmpLE(vec3f64_t v0, vec3f64_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec3f64_t Vec3f64_CmpEQ(vec3f64_t v0, vec3f64_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec3f64_t Vec3f64_CmpGT(vec3f64_t v0, vec3f64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec3f64_t Vec3f64_CmpGE(vec3f64_t v0, vec3f64_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec3f64_t Vec3f64_CmpNE(vec3f64_t v0, vec3f64_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec3f64_t Vec3f64_CmpLTS(vec3f64_t v0, double x)
{
	v0.v[0] = v0.v[0] < x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] < x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] < x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec3f64_t Vec3f64_CmpLES(vec3f64_t v0, double x)
{
	v0.v[0] = v0.v[0] <= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec3f64_t Vec3f64_CmpEQS(vec3f64_t v0, double x)
{
	v0.v[0] = v0.v[0] == x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] == x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] == x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec3f64_t Vec3f64_CmpGTS(vec3f64_t v0, double x)
{
	v0.v[0] = v0.v[0] > x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] > x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] > x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec3f64_t Vec3f64_CmpGES(vec3f64_t v0, double x)
{
	v0.v[0] = v0.v[0] >= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec3f64_t Vec3f64_CmpNES(vec3f64_t v0, double x)
{
	v0.v[0] = v0.v[0] != x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] != x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] != x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec3f64_t Vec3f64_Sign(vec3f64_t v)
{
	v.v[0] = v.v[0] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;
	v.v[1] = v.v[1] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;
	v.v[2] = v.v[2] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;

	return v;
}
vec3f64_t Vec3f64_SignPosNeg(vec3f64_t v)
{
	v.v[0] = v.v[0] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;
	v.v[1] = v.v[1] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;
	v.v[2] = v.v[2] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;

	return v;
}
vec3f64_t Vec3f64_Zero()
{
	return G_VEC3F64_T_ZERO;
}
vec3f64_t Vec3f64_One()
{
	return G_VEC3F64_T_ONE;
}
vec3f64_t Vec3f64_NegOne()
{
	return Vec3f64_Neg(G_VEC3F64_T_ONE);
}
vec3f64_t Vec3f64_Cross(vec3f64_t v0, vec3f64_t v1)
{
	vec3f64_t v;

	v.v[0] = v0.v[1] * v1.v[2] - v0.v[2] * v1.v[1];
	v.v[1] = v0.v[2] * v1.v[0] - v0.v[0] * v1.v[2];
	v.v[2] = v0.v[0] * v1.v[1] - v0.v[1] * v1.v[0];

	return v;
}
vec3f64_t Vec3f64_Lerp(vec3f64_t v0, vec3f64_t v1, vec3f64_t vt)
{
	vec3f64_t v;

	v.v[0] = (G_F64_ONE - vt.v[0]) * v0.v[0] + v1.v[0] * vt.v[0];
	v.v[1] = (G_F64_ONE - vt.v[1]) * v0.v[1] + v1.v[1] * vt.v[1];
	v.v[2] = (G_F64_ONE - vt.v[2]) * v0.v[2] + v1.v[2] * vt.v[2];

	return v;
}
vec3f64_t Vec3f64_LerpS(vec3f64_t v0, vec3f64_t v1, double t)
{
	vec3f64_t v;

	v.v[0] = (G_F64_ONE - t) * v0.v[0] + v1.v[0] * t;
	v.v[1] = (G_F64_ONE - t) * v0.v[1] + v1.v[1] * t;
	v.v[2] = (G_F64_ONE - t) * v0.v[2] + v1.v[2] * t;

	return v;
}
vec4f64_t Vec3f64_ToVec4f64(vec3f64_t v, double x0)
{
	vec4f64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;

	return outv;
}
vec5f64_t Vec3f64_ToVec5f64(vec3f64_t v, double x0, double x1)
{
	vec5f64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;

	return outv;
}
vec6f64_t Vec3f64_ToVec6f64(vec3f64_t v, double x0, double x1, double x2)
{
	vec6f64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;
	outv.v[5] = x2;

	return outv;
}
vec7f64_t Vec3f64_ToVec7f64(vec3f64_t v, double x0, double x1, double x2, double x3)
{
	vec7f64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;
	outv.v[5] = x2;
	outv.v[6] = x3;

	return outv;
}
vec8f64_t Vec3f64_ToVec8f64(vec3f64_t v, double x0, double x1, double x2, double x3, double x4)
{
	vec8f64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;
	outv.v[5] = x2;
	outv.v[6] = x3;
	outv.v[7] = x4;

	return outv;
}
vec3f32_t Vec3f32_SetComponent(vec3f32_t v, int index, float value)
{
	v.v[index] = value;

	return v;
}
vec3f32_t Vec3f32_Vec(float x0, float x1, float x2)
{
	vec3f32_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;

	return v;
}
vec3f32_t Vec3f32_Add(vec3f32_t v0, vec3f32_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];

	return v0;
}
vec3f32_t Vec3f32_Sub(vec3f32_t v0, vec3f32_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];

	return v0;
}
float Vec3f32_GetComponent(vec3f32_t v, int index)
{
	return v.v[index];
}
vec3f32_t Vec3f32_Mul(vec3f32_t v0, vec3f32_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];

	return v0;
}
vec3f32_t Vec3f32_Div(vec3f32_t v0, vec3f32_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];

	return v0;
}
vec3f32_t Vec3f32_Scale(vec3f32_t v, float scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;

	return v;
}
vec3f32_t Vec3f32_DivScale(vec3f32_t v, float divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;

	return v;
}
vec3f32_t Vec3f32_MA(vec3f32_t v, vec3f32_t dir, float scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;

	return v;
}
vec3f32_t Vec3f32_DA(vec3f32_t v, vec3f32_t dir, float divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;

	return v;
}
float Vec3f32_Dot(vec3f32_t v0, vec3f32_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2];
}
float Vec3f32_LenSq(vec3f32_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2];
}
float Vec3f32_Len(vec3f32_t v)
{
	return sqrtf(Vec3f32_LenSq(v));
}
vec3f32_t Vec3f32_Normalise(vec3f32_t v)
{
	float lensq = Vec3f32_LenSq(v);

	if (lensq == G_F32_ZERO)
		return v;
	else
		return Vec3f32_Scale(v, G_F32_ONE / sqrtf(lensq));
}
vec3f32_t Vec3f32_Abs(vec3f32_t v)
{
	v.v[0] = fabsf(v.v[0]);
	v.v[1] = fabsf(v.v[1]);
	v.v[2] = fabsf(v.v[2]);

	return v;
}
vec3f32_t Vec3f32_Floor(vec3f32_t v)
{
	v.v[0] = floorf(v.v[0]);
	v.v[1] = floorf(v.v[1]);
	v.v[2] = floorf(v.v[2]);

	return v;
}
vec3f32_t Vec3f32_Ceil(vec3f32_t v)
{
	v.v[0] = ceilf(v.v[0]);
	v.v[1] = ceilf(v.v[1]);
	v.v[2] = ceilf(v.v[2]);

	return v;
}
vec3f32_t Vec3f32_Fract(vec3f32_t v)
{
	return Vec3f32_Sub(v, Vec3f32_Floor(v));
}
vec3f32_t Vec3f32_Mod(vec3f32_t v0, vec3f32_t v1)
{
	v0.v[0] = fmodf(v0.v[0], v1.v[0]);
	v0.v[1] = fmodf(v0.v[1], v1.v[1]);
	v0.v[2] = fmodf(v0.v[2], v1.v[2]);

	return v0;
}
vec3f32_t Vec3f32_ModS(vec3f32_t v0, float x)
{
	v0.v[0] = fmodf(v0.v[0], x);
	v0.v[1] = fmodf(v0.v[1], x);
	v0.v[2] = fmodf(v0.v[2], x);

	return v0;
}
vec3f32_t Vec3f32_Min(vec3f32_t v0, vec3f32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];

	return v0;
}
vec3f32_t Vec3f32_Max(vec3f32_t v0, vec3f32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];

	return v0;
}
vec3f32_t Vec3f32_MinS(vec3f32_t v0, float x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;

	return v0;
}
vec3f32_t Vec3f32_MaxS(vec3f32_t v0, float x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;

	return v0;
}
vec3f32_t Vec3f32_Clamp(vec3f32_t v, vec3f32_t min, vec3f32_t max)
{
	return Vec3f32_Max(Vec3f32_Min(v, max), min);
}
vec3f32_t Vec3f32_ClampS(vec3f32_t v, float min, float max)
{
	return Vec3f32_MaxS(Vec3f32_MinS(v, max), min);
}
vec3f32_t Vec3f32_Neg(vec3f32_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];

	return v;
}
vec3f32_t Vec3f32_Reciprocal(vec3f32_t v)
{
	v.v[0] = G_F32_ONE / v.v[0];
	v.v[1] = G_F32_ONE / v.v[1];
	v.v[2] = G_F32_ONE / v.v[2];

	return v;
}
vec3f32_t Vec3f32_Truncate(vec3f32_t v)
{
	v.v[0] = v.v[0] < G_F32_ZERO ? ceilf(v.v[0]) : floorf(v.v[0]);
	v.v[1] = v.v[1] < G_F32_ZERO ? ceilf(v.v[1]) : floorf(v.v[1]);
	v.v[2] = v.v[2] < G_F32_ZERO ? ceilf(v.v[2]) : floorf(v.v[2]);

	return v;
}
vec3f32_t Vec3f32_TruncateAway(vec3f32_t v)
{
	v.v[0] = v.v[0] < G_F32_ZERO ? floorf(v.v[0]) : ceilf(v.v[0]);
	v.v[1] = v.v[1] < G_F32_ZERO ? floorf(v.v[1]) : ceilf(v.v[1]);
	v.v[2] = v.v[2] < G_F32_ZERO ? floorf(v.v[2]) : ceilf(v.v[2]);

	return v;
}
vec3f32_t Vec3f32_CmpLT(vec3f32_t v0, vec3f32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec3f32_t Vec3f32_CmpLE(vec3f32_t v0, vec3f32_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec3f32_t Vec3f32_CmpEQ(vec3f32_t v0, vec3f32_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec3f32_t Vec3f32_CmpGT(vec3f32_t v0, vec3f32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec3f32_t Vec3f32_CmpGE(vec3f32_t v0, vec3f32_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec3f32_t Vec3f32_CmpNE(vec3f32_t v0, vec3f32_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec3f32_t Vec3f32_CmpLTS(vec3f32_t v0, float x)
{
	v0.v[0] = v0.v[0] < x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] < x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] < x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec3f32_t Vec3f32_CmpLES(vec3f32_t v0, float x)
{
	v0.v[0] = v0.v[0] <= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec3f32_t Vec3f32_CmpEQS(vec3f32_t v0, float x)
{
	v0.v[0] = v0.v[0] == x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] == x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] == x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec3f32_t Vec3f32_CmpGTS(vec3f32_t v0, float x)
{
	v0.v[0] = v0.v[0] > x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] > x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] > x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec3f32_t Vec3f32_CmpGES(vec3f32_t v0, float x)
{
	v0.v[0] = v0.v[0] >= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec3f32_t Vec3f32_CmpNES(vec3f32_t v0, float x)
{
	v0.v[0] = v0.v[0] != x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] != x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] != x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec3f32_t Vec3f32_Sign(vec3f32_t v)
{
	v.v[0] = v.v[0] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;
	v.v[1] = v.v[1] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;
	v.v[2] = v.v[2] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;

	return v;
}
vec3f32_t Vec3f32_SignPosNeg(vec3f32_t v)
{
	v.v[0] = v.v[0] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;
	v.v[1] = v.v[1] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;
	v.v[2] = v.v[2] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;

	return v;
}
vec3f32_t Vec3f32_Zero()
{
	return G_VEC3F32_T_ZERO;
}
vec3f32_t Vec3f32_One()
{
	return G_VEC3F32_T_ONE;
}
vec3f32_t Vec3f32_NegOne()
{
	return Vec3f32_Neg(G_VEC3F32_T_ONE);
}
vec3f32_t Vec3f32_Cross(vec3f32_t v0, vec3f32_t v1)
{
	vec3f32_t v;

	v.v[0] = v0.v[1] * v1.v[2] - v0.v[2] * v1.v[1];
	v.v[1] = v0.v[2] * v1.v[0] - v0.v[0] * v1.v[2];
	v.v[2] = v0.v[0] * v1.v[1] - v0.v[1] * v1.v[0];

	return v;
}
vec3f32_t Vec3f32_Lerp(vec3f32_t v0, vec3f32_t v1, vec3f32_t vt)
{
	vec3f32_t v;

	v.v[0] = (G_F32_ONE - vt.v[0]) * v0.v[0] + v1.v[0] * vt.v[0];
	v.v[1] = (G_F32_ONE - vt.v[1]) * v0.v[1] + v1.v[1] * vt.v[1];
	v.v[2] = (G_F32_ONE - vt.v[2]) * v0.v[2] + v1.v[2] * vt.v[2];

	return v;
}
vec3f32_t Vec3f32_LerpS(vec3f32_t v0, vec3f32_t v1, float t)
{
	vec3f32_t v;

	v.v[0] = (G_F32_ONE - t) * v0.v[0] + v1.v[0] * t;
	v.v[1] = (G_F32_ONE - t) * v0.v[1] + v1.v[1] * t;
	v.v[2] = (G_F32_ONE - t) * v0.v[2] + v1.v[2] * t;

	return v;
}
vec4f32_t Vec3f32_ToVec4f32(vec3f32_t v, float x0)
{
	vec4f32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;

	return outv;
}
vec5f32_t Vec3f32_ToVec5f32(vec3f32_t v, float x0, float x1)
{
	vec5f32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;

	return outv;
}
vec6f32_t Vec3f32_ToVec6f32(vec3f32_t v, float x0, float x1, float x2)
{
	vec6f32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;
	outv.v[5] = x2;

	return outv;
}
vec7f32_t Vec3f32_ToVec7f32(vec3f32_t v, float x0, float x1, float x2, float x3)
{
	vec7f32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;
	outv.v[5] = x2;
	outv.v[6] = x3;

	return outv;
}
vec8f32_t Vec3f32_ToVec8f32(vec3f32_t v, float x0, float x1, float x2, float x3, float x4)
{
	vec8f32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;
	outv.v[5] = x2;
	outv.v[6] = x3;
	outv.v[7] = x4;

	return outv;
}
vec3u64_t Vec3u64_SetComponent(vec3u64_t v, int index, uint64_t value)
{
	v.v[index] = value;

	return v;
}
vec3u64_t Vec3u64_Vec(uint64_t x0, uint64_t x1, uint64_t x2)
{
	vec3u64_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;

	return v;
}
vec3u64_t Vec3u64_Add(vec3u64_t v0, vec3u64_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];

	return v0;
}
vec3u64_t Vec3u64_Sub(vec3u64_t v0, vec3u64_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];

	return v0;
}
uint64_t Vec3u64_GetComponent(vec3u64_t v, int index)
{
	return v.v[index];
}
vec3u64_t Vec3u64_Mul(vec3u64_t v0, vec3u64_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];

	return v0;
}
vec3u64_t Vec3u64_Div(vec3u64_t v0, vec3u64_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];

	return v0;
}
vec3u64_t Vec3u64_Scale(vec3u64_t v, uint64_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;

	return v;
}
vec3u64_t Vec3u64_DivScale(vec3u64_t v, uint64_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;

	return v;
}
vec3u64_t Vec3u64_MA(vec3u64_t v, vec3u64_t dir, uint64_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;

	return v;
}
vec3u64_t Vec3u64_DA(vec3u64_t v, vec3u64_t dir, uint64_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;

	return v;
}
uint64_t Vec3u64_Dot(vec3u64_t v0, vec3u64_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2];
}
uint64_t Vec3u64_LenSq(vec3u64_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2];
}
uint64_t Vec3u64_Len(vec3u64_t v)
{
	return sqrt(Vec3u64_LenSq(v));
}
vec3u64_t Vec3u64_Mod(vec3u64_t v0, vec3u64_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);

	return v0;
}
vec3u64_t Vec3u64_ModS(vec3u64_t v0, uint64_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);

	return v0;
}
vec3u64_t Vec3u64_Min(vec3u64_t v0, vec3u64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];

	return v0;
}
vec3u64_t Vec3u64_Max(vec3u64_t v0, vec3u64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];

	return v0;
}
vec3u64_t Vec3u64_MinS(vec3u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;

	return v0;
}
vec3u64_t Vec3u64_MaxS(vec3u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;

	return v0;
}
vec3u64_t Vec3u64_Clamp(vec3u64_t v, vec3u64_t min, vec3u64_t max)
{
	return Vec3u64_Max(Vec3u64_Min(v, max), min);
}
vec3u64_t Vec3u64_ClampS(vec3u64_t v, uint64_t min, uint64_t max)
{
	return Vec3u64_MaxS(Vec3u64_MinS(v, max), min);
}
vec3u64_t Vec3u64_CmpLT(vec3u64_t v0, vec3u64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec3u64_t Vec3u64_CmpLE(vec3u64_t v0, vec3u64_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec3u64_t Vec3u64_CmpEQ(vec3u64_t v0, vec3u64_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec3u64_t Vec3u64_CmpGT(vec3u64_t v0, vec3u64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec3u64_t Vec3u64_CmpGE(vec3u64_t v0, vec3u64_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec3u64_t Vec3u64_CmpNE(vec3u64_t v0, vec3u64_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec3u64_t Vec3u64_CmpLTS(vec3u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] < x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] < x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] < x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec3u64_t Vec3u64_CmpLES(vec3u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec3u64_t Vec3u64_CmpEQS(vec3u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] == x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] == x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] == x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec3u64_t Vec3u64_CmpGTS(vec3u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] > x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] > x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] > x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec3u64_t Vec3u64_CmpGES(vec3u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec3u64_t Vec3u64_CmpNES(vec3u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] != x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] != x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] != x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec3u64_t Vec3u64_Sign(vec3u64_t v)
{
	v.v[0] = v.v[0] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;
	v.v[1] = v.v[1] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;
	v.v[2] = v.v[2] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;

	return v;
}
vec3u64_t Vec3u64_SignPosNeg(vec3u64_t v)
{
	v.v[0] = v.v[0] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;
	v.v[1] = v.v[1] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;
	v.v[2] = v.v[2] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;

	return v;
}
vec3u64_t Vec3u64_Zero()
{
	return G_VEC3U64_T_ZERO;
}
vec3u64_t Vec3u64_One()
{
	return G_VEC3U64_T_ONE;
}
vec3u64_t Vec3u64_Cross(vec3u64_t v0, vec3u64_t v1)
{
	vec3u64_t v;

	v.v[0] = v0.v[1] * v1.v[2] - v0.v[2] * v1.v[1];
	v.v[1] = v0.v[2] * v1.v[0] - v0.v[0] * v1.v[2];
	v.v[2] = v0.v[0] * v1.v[1] - v0.v[1] * v1.v[0];

	return v;
}
vec4u64_t Vec3u64_ToVec4u64(vec3u64_t v, uint64_t x0)
{
	vec4u64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;

	return outv;
}
vec5u64_t Vec3u64_ToVec5u64(vec3u64_t v, uint64_t x0, uint64_t x1)
{
	vec5u64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;

	return outv;
}
vec6u64_t Vec3u64_ToVec6u64(vec3u64_t v, uint64_t x0, uint64_t x1, uint64_t x2)
{
	vec6u64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;
	outv.v[5] = x2;

	return outv;
}
vec7u64_t Vec3u64_ToVec7u64(vec3u64_t v, uint64_t x0, uint64_t x1, uint64_t x2, uint64_t x3)
{
	vec7u64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;
	outv.v[5] = x2;
	outv.v[6] = x3;

	return outv;
}
vec8u64_t Vec3u64_ToVec8u64(vec3u64_t v, uint64_t x0, uint64_t x1, uint64_t x2, uint64_t x3, uint64_t x4)
{
	vec8u64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;
	outv.v[5] = x2;
	outv.v[6] = x3;
	outv.v[7] = x4;

	return outv;
}
vec3i64_t Vec3i64_SetComponent(vec3i64_t v, int index, int64_t value)
{
	v.v[index] = value;

	return v;
}
vec3i64_t Vec3i64_Vec(int64_t x0, int64_t x1, int64_t x2)
{
	vec3i64_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;

	return v;
}
vec3i64_t Vec3i64_Add(vec3i64_t v0, vec3i64_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];

	return v0;
}
vec3i64_t Vec3i64_Sub(vec3i64_t v0, vec3i64_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];

	return v0;
}
int64_t Vec3i64_GetComponent(vec3i64_t v, int index)
{
	return v.v[index];
}
vec3i64_t Vec3i64_Mul(vec3i64_t v0, vec3i64_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];

	return v0;
}
vec3i64_t Vec3i64_Div(vec3i64_t v0, vec3i64_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];

	return v0;
}
vec3i64_t Vec3i64_Scale(vec3i64_t v, int64_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;

	return v;
}
vec3i64_t Vec3i64_DivScale(vec3i64_t v, int64_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;

	return v;
}
vec3i64_t Vec3i64_MA(vec3i64_t v, vec3i64_t dir, int64_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;

	return v;
}
vec3i64_t Vec3i64_DA(vec3i64_t v, vec3i64_t dir, int64_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;

	return v;
}
int64_t Vec3i64_Dot(vec3i64_t v0, vec3i64_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2];
}
int64_t Vec3i64_LenSq(vec3i64_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2];
}
int64_t Vec3i64_Len(vec3i64_t v)
{
	return sqrt(Vec3i64_LenSq(v));
}
vec3i64_t Vec3i64_Abs(vec3i64_t v)
{
	v.v[0] = (v.v[0] < 0 ? -v.v[0] : v.v[0]);
	v.v[1] = (v.v[1] < 0 ? -v.v[1] : v.v[1]);
	v.v[2] = (v.v[2] < 0 ? -v.v[2] : v.v[2]);

	return v;
}
vec3i64_t Vec3i64_Mod(vec3i64_t v0, vec3i64_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);

	return v0;
}
vec3i64_t Vec3i64_ModS(vec3i64_t v0, int64_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);

	return v0;
}
vec3i64_t Vec3i64_Min(vec3i64_t v0, vec3i64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];

	return v0;
}
vec3i64_t Vec3i64_Max(vec3i64_t v0, vec3i64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];

	return v0;
}
vec3i64_t Vec3i64_MinS(vec3i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;

	return v0;
}
vec3i64_t Vec3i64_MaxS(vec3i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;

	return v0;
}
vec3i64_t Vec3i64_Clamp(vec3i64_t v, vec3i64_t min, vec3i64_t max)
{
	return Vec3i64_Max(Vec3i64_Min(v, max), min);
}
vec3i64_t Vec3i64_ClampS(vec3i64_t v, int64_t min, int64_t max)
{
	return Vec3i64_MaxS(Vec3i64_MinS(v, max), min);
}
vec3i64_t Vec3i64_Neg(vec3i64_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];

	return v;
}
vec3i64_t Vec3i64_CmpLT(vec3i64_t v0, vec3i64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec3i64_t Vec3i64_CmpLE(vec3i64_t v0, vec3i64_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec3i64_t Vec3i64_CmpEQ(vec3i64_t v0, vec3i64_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec3i64_t Vec3i64_CmpGT(vec3i64_t v0, vec3i64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec3i64_t Vec3i64_CmpGE(vec3i64_t v0, vec3i64_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec3i64_t Vec3i64_CmpNE(vec3i64_t v0, vec3i64_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec3i64_t Vec3i64_CmpLTS(vec3i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] < x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] < x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] < x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec3i64_t Vec3i64_CmpLES(vec3i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec3i64_t Vec3i64_CmpEQS(vec3i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] == x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] == x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] == x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec3i64_t Vec3i64_CmpGTS(vec3i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] > x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] > x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] > x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec3i64_t Vec3i64_CmpGES(vec3i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec3i64_t Vec3i64_CmpNES(vec3i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] != x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] != x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] != x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec3i64_t Vec3i64_Sign(vec3i64_t v)
{
	v.v[0] = v.v[0] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;
	v.v[1] = v.v[1] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;
	v.v[2] = v.v[2] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;

	return v;
}
vec3i64_t Vec3i64_SignPosNeg(vec3i64_t v)
{
	v.v[0] = v.v[0] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;
	v.v[1] = v.v[1] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;
	v.v[2] = v.v[2] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;

	return v;
}
vec3i64_t Vec3i64_Zero()
{
	return G_VEC3I64_T_ZERO;
}
vec3i64_t Vec3i64_One()
{
	return G_VEC3I64_T_ONE;
}
vec3i64_t Vec3i64_NegOne()
{
	return Vec3i64_Neg(G_VEC3I64_T_ONE);
}
vec3i64_t Vec3i64_Cross(vec3i64_t v0, vec3i64_t v1)
{
	vec3i64_t v;

	v.v[0] = v0.v[1] * v1.v[2] - v0.v[2] * v1.v[1];
	v.v[1] = v0.v[2] * v1.v[0] - v0.v[0] * v1.v[2];
	v.v[2] = v0.v[0] * v1.v[1] - v0.v[1] * v1.v[0];

	return v;
}
vec4i64_t Vec3i64_ToVec4i64(vec3i64_t v, int64_t x0)
{
	vec4i64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;

	return outv;
}
vec5i64_t Vec3i64_ToVec5i64(vec3i64_t v, int64_t x0, int64_t x1)
{
	vec5i64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;

	return outv;
}
vec6i64_t Vec3i64_ToVec6i64(vec3i64_t v, int64_t x0, int64_t x1, int64_t x2)
{
	vec6i64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;
	outv.v[5] = x2;

	return outv;
}
vec7i64_t Vec3i64_ToVec7i64(vec3i64_t v, int64_t x0, int64_t x1, int64_t x2, int64_t x3)
{
	vec7i64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;
	outv.v[5] = x2;
	outv.v[6] = x3;

	return outv;
}
vec8i64_t Vec3i64_ToVec8i64(vec3i64_t v, int64_t x0, int64_t x1, int64_t x2, int64_t x3, int64_t x4)
{
	vec8i64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;
	outv.v[5] = x2;
	outv.v[6] = x3;
	outv.v[7] = x4;

	return outv;
}
vec3u32_t Vec3u32_SetComponent(vec3u32_t v, int index, uint32_t value)
{
	v.v[index] = value;

	return v;
}
vec3u32_t Vec3u32_Vec(uint32_t x0, uint32_t x1, uint32_t x2)
{
	vec3u32_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;

	return v;
}
vec3u32_t Vec3u32_Add(vec3u32_t v0, vec3u32_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];

	return v0;
}
vec3u32_t Vec3u32_Sub(vec3u32_t v0, vec3u32_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];

	return v0;
}
uint32_t Vec3u32_GetComponent(vec3u32_t v, int index)
{
	return v.v[index];
}
vec3u32_t Vec3u32_Mul(vec3u32_t v0, vec3u32_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];

	return v0;
}
vec3u32_t Vec3u32_Div(vec3u32_t v0, vec3u32_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];

	return v0;
}
vec3u32_t Vec3u32_Scale(vec3u32_t v, uint32_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;

	return v;
}
vec3u32_t Vec3u32_DivScale(vec3u32_t v, uint32_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;

	return v;
}
vec3u32_t Vec3u32_MA(vec3u32_t v, vec3u32_t dir, uint32_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;

	return v;
}
vec3u32_t Vec3u32_DA(vec3u32_t v, vec3u32_t dir, uint32_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;

	return v;
}
uint32_t Vec3u32_Dot(vec3u32_t v0, vec3u32_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2];
}
uint32_t Vec3u32_LenSq(vec3u32_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2];
}
uint32_t Vec3u32_Len(vec3u32_t v)
{
	return sqrtf(Vec3u32_LenSq(v));
}
vec3u32_t Vec3u32_Mod(vec3u32_t v0, vec3u32_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);

	return v0;
}
vec3u32_t Vec3u32_ModS(vec3u32_t v0, uint32_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);

	return v0;
}
vec3u32_t Vec3u32_Min(vec3u32_t v0, vec3u32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];

	return v0;
}
vec3u32_t Vec3u32_Max(vec3u32_t v0, vec3u32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];

	return v0;
}
vec3u32_t Vec3u32_MinS(vec3u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;

	return v0;
}
vec3u32_t Vec3u32_MaxS(vec3u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;

	return v0;
}
vec3u32_t Vec3u32_Clamp(vec3u32_t v, vec3u32_t min, vec3u32_t max)
{
	return Vec3u32_Max(Vec3u32_Min(v, max), min);
}
vec3u32_t Vec3u32_ClampS(vec3u32_t v, uint32_t min, uint32_t max)
{
	return Vec3u32_MaxS(Vec3u32_MinS(v, max), min);
}
vec3u32_t Vec3u32_CmpLT(vec3u32_t v0, vec3u32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec3u32_t Vec3u32_CmpLE(vec3u32_t v0, vec3u32_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec3u32_t Vec3u32_CmpEQ(vec3u32_t v0, vec3u32_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec3u32_t Vec3u32_CmpGT(vec3u32_t v0, vec3u32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec3u32_t Vec3u32_CmpGE(vec3u32_t v0, vec3u32_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec3u32_t Vec3u32_CmpNE(vec3u32_t v0, vec3u32_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec3u32_t Vec3u32_CmpLTS(vec3u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] < x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] < x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] < x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec3u32_t Vec3u32_CmpLES(vec3u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec3u32_t Vec3u32_CmpEQS(vec3u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] == x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] == x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] == x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec3u32_t Vec3u32_CmpGTS(vec3u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] > x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] > x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] > x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec3u32_t Vec3u32_CmpGES(vec3u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec3u32_t Vec3u32_CmpNES(vec3u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] != x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] != x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] != x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec3u32_t Vec3u32_Sign(vec3u32_t v)
{
	v.v[0] = v.v[0] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;
	v.v[1] = v.v[1] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;
	v.v[2] = v.v[2] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;

	return v;
}
vec3u32_t Vec3u32_SignPosNeg(vec3u32_t v)
{
	v.v[0] = v.v[0] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;
	v.v[1] = v.v[1] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;
	v.v[2] = v.v[2] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;

	return v;
}
vec3u32_t Vec3u32_Zero()
{
	return G_VEC3U32_T_ZERO;
}
vec3u32_t Vec3u32_One()
{
	return G_VEC3U32_T_ONE;
}
vec3u32_t Vec3u32_Cross(vec3u32_t v0, vec3u32_t v1)
{
	vec3u32_t v;

	v.v[0] = v0.v[1] * v1.v[2] - v0.v[2] * v1.v[1];
	v.v[1] = v0.v[2] * v1.v[0] - v0.v[0] * v1.v[2];
	v.v[2] = v0.v[0] * v1.v[1] - v0.v[1] * v1.v[0];

	return v;
}
vec4u32_t Vec3u32_ToVec4u32(vec3u32_t v, uint32_t x0)
{
	vec4u32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;

	return outv;
}
vec5u32_t Vec3u32_ToVec5u32(vec3u32_t v, uint32_t x0, uint32_t x1)
{
	vec5u32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;

	return outv;
}
vec6u32_t Vec3u32_ToVec6u32(vec3u32_t v, uint32_t x0, uint32_t x1, uint32_t x2)
{
	vec6u32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;
	outv.v[5] = x2;

	return outv;
}
vec7u32_t Vec3u32_ToVec7u32(vec3u32_t v, uint32_t x0, uint32_t x1, uint32_t x2, uint32_t x3)
{
	vec7u32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;
	outv.v[5] = x2;
	outv.v[6] = x3;

	return outv;
}
vec8u32_t Vec3u32_ToVec8u32(vec3u32_t v, uint32_t x0, uint32_t x1, uint32_t x2, uint32_t x3, uint32_t x4)
{
	vec8u32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;
	outv.v[5] = x2;
	outv.v[6] = x3;
	outv.v[7] = x4;

	return outv;
}
vec3i32_t Vec3i32_SetComponent(vec3i32_t v, int index, int32_t value)
{
	v.v[index] = value;

	return v;
}
vec3i32_t Vec3i32_Vec(int32_t x0, int32_t x1, int32_t x2)
{
	vec3i32_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;

	return v;
}
vec3i32_t Vec3i32_Add(vec3i32_t v0, vec3i32_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];

	return v0;
}
vec3i32_t Vec3i32_Sub(vec3i32_t v0, vec3i32_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];

	return v0;
}
int32_t Vec3i32_GetComponent(vec3i32_t v, int index)
{
	return v.v[index];
}
vec3i32_t Vec3i32_Mul(vec3i32_t v0, vec3i32_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];

	return v0;
}
vec3i32_t Vec3i32_Div(vec3i32_t v0, vec3i32_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];

	return v0;
}
vec3i32_t Vec3i32_Scale(vec3i32_t v, int32_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;

	return v;
}
vec3i32_t Vec3i32_DivScale(vec3i32_t v, int32_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;

	return v;
}
vec3i32_t Vec3i32_MA(vec3i32_t v, vec3i32_t dir, int32_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;

	return v;
}
vec3i32_t Vec3i32_DA(vec3i32_t v, vec3i32_t dir, int32_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;

	return v;
}
int32_t Vec3i32_Dot(vec3i32_t v0, vec3i32_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2];
}
int32_t Vec3i32_LenSq(vec3i32_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2];
}
int32_t Vec3i32_Len(vec3i32_t v)
{
	return sqrtf(Vec3i32_LenSq(v));
}
vec3i32_t Vec3i32_Abs(vec3i32_t v)
{
	v.v[0] = (v.v[0] < 0 ? -v.v[0] : v.v[0]);
	v.v[1] = (v.v[1] < 0 ? -v.v[1] : v.v[1]);
	v.v[2] = (v.v[2] < 0 ? -v.v[2] : v.v[2]);

	return v;
}
vec3i32_t Vec3i32_Mod(vec3i32_t v0, vec3i32_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);

	return v0;
}
vec3i32_t Vec3i32_ModS(vec3i32_t v0, int32_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);

	return v0;
}
vec3i32_t Vec3i32_Min(vec3i32_t v0, vec3i32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];

	return v0;
}
vec3i32_t Vec3i32_Max(vec3i32_t v0, vec3i32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];

	return v0;
}
vec3i32_t Vec3i32_MinS(vec3i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;

	return v0;
}
vec3i32_t Vec3i32_MaxS(vec3i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;

	return v0;
}
vec3i32_t Vec3i32_Clamp(vec3i32_t v, vec3i32_t min, vec3i32_t max)
{
	return Vec3i32_Max(Vec3i32_Min(v, max), min);
}
vec3i32_t Vec3i32_ClampS(vec3i32_t v, int32_t min, int32_t max)
{
	return Vec3i32_MaxS(Vec3i32_MinS(v, max), min);
}
vec3i32_t Vec3i32_Neg(vec3i32_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];

	return v;
}
vec3i32_t Vec3i32_CmpLT(vec3i32_t v0, vec3i32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec3i32_t Vec3i32_CmpLE(vec3i32_t v0, vec3i32_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec3i32_t Vec3i32_CmpEQ(vec3i32_t v0, vec3i32_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec3i32_t Vec3i32_CmpGT(vec3i32_t v0, vec3i32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec3i32_t Vec3i32_CmpGE(vec3i32_t v0, vec3i32_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec3i32_t Vec3i32_CmpNE(vec3i32_t v0, vec3i32_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec3i32_t Vec3i32_CmpLTS(vec3i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] < x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] < x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] < x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec3i32_t Vec3i32_CmpLES(vec3i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec3i32_t Vec3i32_CmpEQS(vec3i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] == x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] == x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] == x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec3i32_t Vec3i32_CmpGTS(vec3i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] > x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] > x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] > x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec3i32_t Vec3i32_CmpGES(vec3i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec3i32_t Vec3i32_CmpNES(vec3i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] != x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] != x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] != x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec3i32_t Vec3i32_Sign(vec3i32_t v)
{
	v.v[0] = v.v[0] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;
	v.v[1] = v.v[1] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;
	v.v[2] = v.v[2] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;

	return v;
}
vec3i32_t Vec3i32_SignPosNeg(vec3i32_t v)
{
	v.v[0] = v.v[0] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;
	v.v[1] = v.v[1] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;
	v.v[2] = v.v[2] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;

	return v;
}
vec3i32_t Vec3i32_Zero()
{
	return G_VEC3I32_T_ZERO;
}
vec3i32_t Vec3i32_One()
{
	return G_VEC3I32_T_ONE;
}
vec3i32_t Vec3i32_NegOne()
{
	return Vec3i32_Neg(G_VEC3I32_T_ONE);
}
vec3i32_t Vec3i32_Cross(vec3i32_t v0, vec3i32_t v1)
{
	vec3i32_t v;

	v.v[0] = v0.v[1] * v1.v[2] - v0.v[2] * v1.v[1];
	v.v[1] = v0.v[2] * v1.v[0] - v0.v[0] * v1.v[2];
	v.v[2] = v0.v[0] * v1.v[1] - v0.v[1] * v1.v[0];

	return v;
}
vec4i32_t Vec3i32_ToVec4i32(vec3i32_t v, int32_t x0)
{
	vec4i32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;

	return outv;
}
vec5i32_t Vec3i32_ToVec5i32(vec3i32_t v, int32_t x0, int32_t x1)
{
	vec5i32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;

	return outv;
}
vec6i32_t Vec3i32_ToVec6i32(vec3i32_t v, int32_t x0, int32_t x1, int32_t x2)
{
	vec6i32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;
	outv.v[5] = x2;

	return outv;
}
vec7i32_t Vec3i32_ToVec7i32(vec3i32_t v, int32_t x0, int32_t x1, int32_t x2, int32_t x3)
{
	vec7i32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;
	outv.v[5] = x2;
	outv.v[6] = x3;

	return outv;
}
vec8i32_t Vec3i32_ToVec8i32(vec3i32_t v, int32_t x0, int32_t x1, int32_t x2, int32_t x3, int32_t x4)
{
	vec8i32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;
	outv.v[5] = x2;
	outv.v[6] = x3;
	outv.v[7] = x4;

	return outv;
}
vec3u16_t Vec3u16_SetComponent(vec3u16_t v, int index, uint16_t value)
{
	v.v[index] = value;

	return v;
}
vec3u16_t Vec3u16_Vec(uint16_t x0, uint16_t x1, uint16_t x2)
{
	vec3u16_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;

	return v;
}
vec3u16_t Vec3u16_Add(vec3u16_t v0, vec3u16_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];

	return v0;
}
vec3u16_t Vec3u16_Sub(vec3u16_t v0, vec3u16_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];

	return v0;
}
uint16_t Vec3u16_GetComponent(vec3u16_t v, int index)
{
	return v.v[index];
}
vec3u16_t Vec3u16_Mul(vec3u16_t v0, vec3u16_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];

	return v0;
}
vec3u16_t Vec3u16_Div(vec3u16_t v0, vec3u16_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];

	return v0;
}
vec3u16_t Vec3u16_Scale(vec3u16_t v, uint16_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;

	return v;
}
vec3u16_t Vec3u16_DivScale(vec3u16_t v, uint16_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;

	return v;
}
vec3u16_t Vec3u16_MA(vec3u16_t v, vec3u16_t dir, uint16_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;

	return v;
}
vec3u16_t Vec3u16_DA(vec3u16_t v, vec3u16_t dir, uint16_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;

	return v;
}
uint16_t Vec3u16_Dot(vec3u16_t v0, vec3u16_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2];
}
uint16_t Vec3u16_LenSq(vec3u16_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2];
}
uint16_t Vec3u16_Len(vec3u16_t v)
{
	return sqrtf(Vec3u16_LenSq(v));
}
vec3u16_t Vec3u16_Mod(vec3u16_t v0, vec3u16_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);

	return v0;
}
vec3u16_t Vec3u16_ModS(vec3u16_t v0, uint16_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);

	return v0;
}
vec3u16_t Vec3u16_Min(vec3u16_t v0, vec3u16_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];

	return v0;
}
vec3u16_t Vec3u16_Max(vec3u16_t v0, vec3u16_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];

	return v0;
}
vec3u16_t Vec3u16_MinS(vec3u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;

	return v0;
}
vec3u16_t Vec3u16_MaxS(vec3u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;

	return v0;
}
vec3u16_t Vec3u16_Clamp(vec3u16_t v, vec3u16_t min, vec3u16_t max)
{
	return Vec3u16_Max(Vec3u16_Min(v, max), min);
}
vec3u16_t Vec3u16_ClampS(vec3u16_t v, uint16_t min, uint16_t max)
{
	return Vec3u16_MaxS(Vec3u16_MinS(v, max), min);
}
vec3u16_t Vec3u16_CmpLT(vec3u16_t v0, vec3u16_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec3u16_t Vec3u16_CmpLE(vec3u16_t v0, vec3u16_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec3u16_t Vec3u16_CmpEQ(vec3u16_t v0, vec3u16_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec3u16_t Vec3u16_CmpGT(vec3u16_t v0, vec3u16_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec3u16_t Vec3u16_CmpGE(vec3u16_t v0, vec3u16_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec3u16_t Vec3u16_CmpNE(vec3u16_t v0, vec3u16_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec3u16_t Vec3u16_CmpLTS(vec3u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] < x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] < x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] < x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec3u16_t Vec3u16_CmpLES(vec3u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec3u16_t Vec3u16_CmpEQS(vec3u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] == x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] == x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] == x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec3u16_t Vec3u16_CmpGTS(vec3u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] > x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] > x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] > x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec3u16_t Vec3u16_CmpGES(vec3u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec3u16_t Vec3u16_CmpNES(vec3u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] != x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] != x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] != x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec3u16_t Vec3u16_Sign(vec3u16_t v)
{
	v.v[0] = v.v[0] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;
	v.v[1] = v.v[1] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;
	v.v[2] = v.v[2] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;

	return v;
}
vec3u16_t Vec3u16_SignPosNeg(vec3u16_t v)
{
	v.v[0] = v.v[0] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;
	v.v[1] = v.v[1] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;
	v.v[2] = v.v[2] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;

	return v;
}
vec3u16_t Vec3u16_Zero()
{
	return G_VEC3U16_T_ZERO;
}
vec3u16_t Vec3u16_One()
{
	return G_VEC3U16_T_ONE;
}
vec3u16_t Vec3u16_Cross(vec3u16_t v0, vec3u16_t v1)
{
	vec3u16_t v;

	v.v[0] = v0.v[1] * v1.v[2] - v0.v[2] * v1.v[1];
	v.v[1] = v0.v[2] * v1.v[0] - v0.v[0] * v1.v[2];
	v.v[2] = v0.v[0] * v1.v[1] - v0.v[1] * v1.v[0];

	return v;
}
vec4u16_t Vec3u16_ToVec4u16(vec3u16_t v, uint16_t x0)
{
	vec4u16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;

	return outv;
}
vec5u16_t Vec3u16_ToVec5u16(vec3u16_t v, uint16_t x0, uint16_t x1)
{
	vec5u16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;

	return outv;
}
vec6u16_t Vec3u16_ToVec6u16(vec3u16_t v, uint16_t x0, uint16_t x1, uint16_t x2)
{
	vec6u16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;
	outv.v[5] = x2;

	return outv;
}
vec7u16_t Vec3u16_ToVec7u16(vec3u16_t v, uint16_t x0, uint16_t x1, uint16_t x2, uint16_t x3)
{
	vec7u16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;
	outv.v[5] = x2;
	outv.v[6] = x3;

	return outv;
}
vec8u16_t Vec3u16_ToVec8u16(vec3u16_t v, uint16_t x0, uint16_t x1, uint16_t x2, uint16_t x3, uint16_t x4)
{
	vec8u16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;
	outv.v[5] = x2;
	outv.v[6] = x3;
	outv.v[7] = x4;

	return outv;
}
vec3i16_t Vec3i16_SetComponent(vec3i16_t v, int index, int16_t value)
{
	v.v[index] = value;

	return v;
}
vec3i16_t Vec3i16_Vec(int16_t x0, int16_t x1, int16_t x2)
{
	vec3i16_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;

	return v;
}
vec3i16_t Vec3i16_Add(vec3i16_t v0, vec3i16_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];

	return v0;
}
vec3i16_t Vec3i16_Sub(vec3i16_t v0, vec3i16_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];

	return v0;
}
int16_t Vec3i16_GetComponent(vec3i16_t v, int index)
{
	return v.v[index];
}
vec3i16_t Vec3i16_Mul(vec3i16_t v0, vec3i16_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];

	return v0;
}
vec3i16_t Vec3i16_Div(vec3i16_t v0, vec3i16_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];

	return v0;
}
vec3i16_t Vec3i16_Scale(vec3i16_t v, int16_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;

	return v;
}
vec3i16_t Vec3i16_DivScale(vec3i16_t v, int16_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;

	return v;
}
vec3i16_t Vec3i16_MA(vec3i16_t v, vec3i16_t dir, int16_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;

	return v;
}
vec3i16_t Vec3i16_DA(vec3i16_t v, vec3i16_t dir, int16_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;

	return v;
}
int16_t Vec3i16_Dot(vec3i16_t v0, vec3i16_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2];
}
int16_t Vec3i16_LenSq(vec3i16_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2];
}
int16_t Vec3i16_Len(vec3i16_t v)
{
	return sqrtf(Vec3i16_LenSq(v));
}
vec3i16_t Vec3i16_Abs(vec3i16_t v)
{
	v.v[0] = (v.v[0] < 0 ? -v.v[0] : v.v[0]);
	v.v[1] = (v.v[1] < 0 ? -v.v[1] : v.v[1]);
	v.v[2] = (v.v[2] < 0 ? -v.v[2] : v.v[2]);

	return v;
}
vec3i16_t Vec3i16_Mod(vec3i16_t v0, vec3i16_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);

	return v0;
}
vec3i16_t Vec3i16_ModS(vec3i16_t v0, int16_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);

	return v0;
}
vec3i16_t Vec3i16_Min(vec3i16_t v0, vec3i16_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];

	return v0;
}
vec3i16_t Vec3i16_Max(vec3i16_t v0, vec3i16_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];

	return v0;
}
vec3i16_t Vec3i16_MinS(vec3i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;

	return v0;
}
vec3i16_t Vec3i16_MaxS(vec3i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;

	return v0;
}
vec3i16_t Vec3i16_Clamp(vec3i16_t v, vec3i16_t min, vec3i16_t max)
{
	return Vec3i16_Max(Vec3i16_Min(v, max), min);
}
vec3i16_t Vec3i16_ClampS(vec3i16_t v, int16_t min, int16_t max)
{
	return Vec3i16_MaxS(Vec3i16_MinS(v, max), min);
}
vec3i16_t Vec3i16_Neg(vec3i16_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];

	return v;
}
vec3i16_t Vec3i16_CmpLT(vec3i16_t v0, vec3i16_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec3i16_t Vec3i16_CmpLE(vec3i16_t v0, vec3i16_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec3i16_t Vec3i16_CmpEQ(vec3i16_t v0, vec3i16_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec3i16_t Vec3i16_CmpGT(vec3i16_t v0, vec3i16_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec3i16_t Vec3i16_CmpGE(vec3i16_t v0, vec3i16_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec3i16_t Vec3i16_CmpNE(vec3i16_t v0, vec3i16_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec3i16_t Vec3i16_CmpLTS(vec3i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] < x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] < x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] < x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec3i16_t Vec3i16_CmpLES(vec3i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec3i16_t Vec3i16_CmpEQS(vec3i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] == x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] == x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] == x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec3i16_t Vec3i16_CmpGTS(vec3i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] > x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] > x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] > x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec3i16_t Vec3i16_CmpGES(vec3i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec3i16_t Vec3i16_CmpNES(vec3i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] != x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] != x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] != x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec3i16_t Vec3i16_Sign(vec3i16_t v)
{
	v.v[0] = v.v[0] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;
	v.v[1] = v.v[1] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;
	v.v[2] = v.v[2] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;

	return v;
}
vec3i16_t Vec3i16_SignPosNeg(vec3i16_t v)
{
	v.v[0] = v.v[0] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;
	v.v[1] = v.v[1] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;
	v.v[2] = v.v[2] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;

	return v;
}
vec3i16_t Vec3i16_Zero()
{
	return G_VEC3I16_T_ZERO;
}
vec3i16_t Vec3i16_One()
{
	return G_VEC3I16_T_ONE;
}
vec3i16_t Vec3i16_NegOne()
{
	return Vec3i16_Neg(G_VEC3I16_T_ONE);
}
vec3i16_t Vec3i16_Cross(vec3i16_t v0, vec3i16_t v1)
{
	vec3i16_t v;

	v.v[0] = v0.v[1] * v1.v[2] - v0.v[2] * v1.v[1];
	v.v[1] = v0.v[2] * v1.v[0] - v0.v[0] * v1.v[2];
	v.v[2] = v0.v[0] * v1.v[1] - v0.v[1] * v1.v[0];

	return v;
}
vec4i16_t Vec3i16_ToVec4i16(vec3i16_t v, int16_t x0)
{
	vec4i16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;

	return outv;
}
vec5i16_t Vec3i16_ToVec5i16(vec3i16_t v, int16_t x0, int16_t x1)
{
	vec5i16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;

	return outv;
}
vec6i16_t Vec3i16_ToVec6i16(vec3i16_t v, int16_t x0, int16_t x1, int16_t x2)
{
	vec6i16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;
	outv.v[5] = x2;

	return outv;
}
vec7i16_t Vec3i16_ToVec7i16(vec3i16_t v, int16_t x0, int16_t x1, int16_t x2, int16_t x3)
{
	vec7i16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;
	outv.v[5] = x2;
	outv.v[6] = x3;

	return outv;
}
vec8i16_t Vec3i16_ToVec8i16(vec3i16_t v, int16_t x0, int16_t x1, int16_t x2, int16_t x3, int16_t x4)
{
	vec8i16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;
	outv.v[5] = x2;
	outv.v[6] = x3;
	outv.v[7] = x4;

	return outv;
}
vec3u8_t Vec3u8_SetComponent(vec3u8_t v, int index, uint8_t value)
{
	v.v[index] = value;

	return v;
}
vec3u8_t Vec3u8_Vec(uint8_t x0, uint8_t x1, uint8_t x2)
{
	vec3u8_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;

	return v;
}
vec3u8_t Vec3u8_Add(vec3u8_t v0, vec3u8_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];

	return v0;
}
vec3u8_t Vec3u8_Sub(vec3u8_t v0, vec3u8_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];

	return v0;
}
uint8_t Vec3u8_GetComponent(vec3u8_t v, int index)
{
	return v.v[index];
}
vec3u8_t Vec3u8_Mul(vec3u8_t v0, vec3u8_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];

	return v0;
}
vec3u8_t Vec3u8_Div(vec3u8_t v0, vec3u8_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];

	return v0;
}
vec3u8_t Vec3u8_Scale(vec3u8_t v, uint8_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;

	return v;
}
vec3u8_t Vec3u8_DivScale(vec3u8_t v, uint8_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;

	return v;
}
vec3u8_t Vec3u8_MA(vec3u8_t v, vec3u8_t dir, uint8_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;

	return v;
}
vec3u8_t Vec3u8_DA(vec3u8_t v, vec3u8_t dir, uint8_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;

	return v;
}
uint8_t Vec3u8_Dot(vec3u8_t v0, vec3u8_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2];
}
uint8_t Vec3u8_LenSq(vec3u8_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2];
}
uint8_t Vec3u8_Len(vec3u8_t v)
{
	return sqrtf(Vec3u8_LenSq(v));
}
vec3u8_t Vec3u8_Mod(vec3u8_t v0, vec3u8_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);

	return v0;
}
vec3u8_t Vec3u8_ModS(vec3u8_t v0, uint8_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);

	return v0;
}
vec3u8_t Vec3u8_Min(vec3u8_t v0, vec3u8_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];

	return v0;
}
vec3u8_t Vec3u8_Max(vec3u8_t v0, vec3u8_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];

	return v0;
}
vec3u8_t Vec3u8_MinS(vec3u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;

	return v0;
}
vec3u8_t Vec3u8_MaxS(vec3u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;

	return v0;
}
vec3u8_t Vec3u8_Clamp(vec3u8_t v, vec3u8_t min, vec3u8_t max)
{
	return Vec3u8_Max(Vec3u8_Min(v, max), min);
}
vec3u8_t Vec3u8_ClampS(vec3u8_t v, uint8_t min, uint8_t max)
{
	return Vec3u8_MaxS(Vec3u8_MinS(v, max), min);
}
vec3u8_t Vec3u8_CmpLT(vec3u8_t v0, vec3u8_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec3u8_t Vec3u8_CmpLE(vec3u8_t v0, vec3u8_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec3u8_t Vec3u8_CmpEQ(vec3u8_t v0, vec3u8_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec3u8_t Vec3u8_CmpGT(vec3u8_t v0, vec3u8_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec3u8_t Vec3u8_CmpGE(vec3u8_t v0, vec3u8_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec3u8_t Vec3u8_CmpNE(vec3u8_t v0, vec3u8_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec3u8_t Vec3u8_CmpLTS(vec3u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] < x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] < x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] < x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec3u8_t Vec3u8_CmpLES(vec3u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec3u8_t Vec3u8_CmpEQS(vec3u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] == x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] == x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] == x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec3u8_t Vec3u8_CmpGTS(vec3u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] > x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] > x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] > x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec3u8_t Vec3u8_CmpGES(vec3u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec3u8_t Vec3u8_CmpNES(vec3u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] != x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] != x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] != x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec3u8_t Vec3u8_Sign(vec3u8_t v)
{
	v.v[0] = v.v[0] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;
	v.v[1] = v.v[1] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;
	v.v[2] = v.v[2] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;

	return v;
}
vec3u8_t Vec3u8_SignPosNeg(vec3u8_t v)
{
	v.v[0] = v.v[0] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;
	v.v[1] = v.v[1] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;
	v.v[2] = v.v[2] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;

	return v;
}
vec3u8_t Vec3u8_Zero()
{
	return G_VEC3U8_T_ZERO;
}
vec3u8_t Vec3u8_One()
{
	return G_VEC3U8_T_ONE;
}
vec3u8_t Vec3u8_Cross(vec3u8_t v0, vec3u8_t v1)
{
	vec3u8_t v;

	v.v[0] = v0.v[1] * v1.v[2] - v0.v[2] * v1.v[1];
	v.v[1] = v0.v[2] * v1.v[0] - v0.v[0] * v1.v[2];
	v.v[2] = v0.v[0] * v1.v[1] - v0.v[1] * v1.v[0];

	return v;
}
vec4u8_t Vec3u8_ToVec4u8(vec3u8_t v, uint8_t x0)
{
	vec4u8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;

	return outv;
}
vec5u8_t Vec3u8_ToVec5u8(vec3u8_t v, uint8_t x0, uint8_t x1)
{
	vec5u8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;

	return outv;
}
vec6u8_t Vec3u8_ToVec6u8(vec3u8_t v, uint8_t x0, uint8_t x1, uint8_t x2)
{
	vec6u8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;
	outv.v[5] = x2;

	return outv;
}
vec7u8_t Vec3u8_ToVec7u8(vec3u8_t v, uint8_t x0, uint8_t x1, uint8_t x2, uint8_t x3)
{
	vec7u8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;
	outv.v[5] = x2;
	outv.v[6] = x3;

	return outv;
}
vec8u8_t Vec3u8_ToVec8u8(vec3u8_t v, uint8_t x0, uint8_t x1, uint8_t x2, uint8_t x3, uint8_t x4)
{
	vec8u8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;
	outv.v[5] = x2;
	outv.v[6] = x3;
	outv.v[7] = x4;

	return outv;
}
vec3i8_t Vec3i8_SetComponent(vec3i8_t v, int index, int8_t value)
{
	v.v[index] = value;

	return v;
}
vec3i8_t Vec3i8_Vec(int8_t x0, int8_t x1, int8_t x2)
{
	vec3i8_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;

	return v;
}
vec3i8_t Vec3i8_Add(vec3i8_t v0, vec3i8_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];

	return v0;
}
vec3i8_t Vec3i8_Sub(vec3i8_t v0, vec3i8_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];

	return v0;
}
int8_t Vec3i8_GetComponent(vec3i8_t v, int index)
{
	return v.v[index];
}
vec3i8_t Vec3i8_Mul(vec3i8_t v0, vec3i8_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];

	return v0;
}
vec3i8_t Vec3i8_Div(vec3i8_t v0, vec3i8_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];

	return v0;
}
vec3i8_t Vec3i8_Scale(vec3i8_t v, int8_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;

	return v;
}
vec3i8_t Vec3i8_DivScale(vec3i8_t v, int8_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;

	return v;
}
vec3i8_t Vec3i8_MA(vec3i8_t v, vec3i8_t dir, int8_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;

	return v;
}
vec3i8_t Vec3i8_DA(vec3i8_t v, vec3i8_t dir, int8_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;

	return v;
}
int8_t Vec3i8_Dot(vec3i8_t v0, vec3i8_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2];
}
int8_t Vec3i8_LenSq(vec3i8_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2];
}
int8_t Vec3i8_Len(vec3i8_t v)
{
	return sqrtf(Vec3i8_LenSq(v));
}
vec3i8_t Vec3i8_Abs(vec3i8_t v)
{
	v.v[0] = (v.v[0] < 0 ? -v.v[0] : v.v[0]);
	v.v[1] = (v.v[1] < 0 ? -v.v[1] : v.v[1]);
	v.v[2] = (v.v[2] < 0 ? -v.v[2] : v.v[2]);

	return v;
}
vec3i8_t Vec3i8_Mod(vec3i8_t v0, vec3i8_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);

	return v0;
}
vec3i8_t Vec3i8_ModS(vec3i8_t v0, int8_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);

	return v0;
}
vec3i8_t Vec3i8_Min(vec3i8_t v0, vec3i8_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];

	return v0;
}
vec3i8_t Vec3i8_Max(vec3i8_t v0, vec3i8_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];

	return v0;
}
vec3i8_t Vec3i8_MinS(vec3i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;

	return v0;
}
vec3i8_t Vec3i8_MaxS(vec3i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;

	return v0;
}
vec3i8_t Vec3i8_Clamp(vec3i8_t v, vec3i8_t min, vec3i8_t max)
{
	return Vec3i8_Max(Vec3i8_Min(v, max), min);
}
vec3i8_t Vec3i8_ClampS(vec3i8_t v, int8_t min, int8_t max)
{
	return Vec3i8_MaxS(Vec3i8_MinS(v, max), min);
}
vec3i8_t Vec3i8_Neg(vec3i8_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];

	return v;
}
vec3i8_t Vec3i8_CmpLT(vec3i8_t v0, vec3i8_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec3i8_t Vec3i8_CmpLE(vec3i8_t v0, vec3i8_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec3i8_t Vec3i8_CmpEQ(vec3i8_t v0, vec3i8_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec3i8_t Vec3i8_CmpGT(vec3i8_t v0, vec3i8_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec3i8_t Vec3i8_CmpGE(vec3i8_t v0, vec3i8_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec3i8_t Vec3i8_CmpNE(vec3i8_t v0, vec3i8_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec3i8_t Vec3i8_CmpLTS(vec3i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] < x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] < x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] < x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec3i8_t Vec3i8_CmpLES(vec3i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec3i8_t Vec3i8_CmpEQS(vec3i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] == x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] == x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] == x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec3i8_t Vec3i8_CmpGTS(vec3i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] > x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] > x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] > x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec3i8_t Vec3i8_CmpGES(vec3i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec3i8_t Vec3i8_CmpNES(vec3i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] != x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] != x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] != x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec3i8_t Vec3i8_Sign(vec3i8_t v)
{
	v.v[0] = v.v[0] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;
	v.v[1] = v.v[1] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;
	v.v[2] = v.v[2] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;

	return v;
}
vec3i8_t Vec3i8_SignPosNeg(vec3i8_t v)
{
	v.v[0] = v.v[0] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;
	v.v[1] = v.v[1] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;
	v.v[2] = v.v[2] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;

	return v;
}
vec3i8_t Vec3i8_Zero()
{
	return G_VEC3I8_T_ZERO;
}
vec3i8_t Vec3i8_One()
{
	return G_VEC3I8_T_ONE;
}
vec3i8_t Vec3i8_NegOne()
{
	return Vec3i8_Neg(G_VEC3I8_T_ONE);
}
vec3i8_t Vec3i8_Cross(vec3i8_t v0, vec3i8_t v1)
{
	vec3i8_t v;

	v.v[0] = v0.v[1] * v1.v[2] - v0.v[2] * v1.v[1];
	v.v[1] = v0.v[2] * v1.v[0] - v0.v[0] * v1.v[2];
	v.v[2] = v0.v[0] * v1.v[1] - v0.v[1] * v1.v[0];

	return v;
}
vec4i8_t Vec3i8_ToVec4i8(vec3i8_t v, int8_t x0)
{
	vec4i8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;

	return outv;
}
vec5i8_t Vec3i8_ToVec5i8(vec3i8_t v, int8_t x0, int8_t x1)
{
	vec5i8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;

	return outv;
}
vec6i8_t Vec3i8_ToVec6i8(vec3i8_t v, int8_t x0, int8_t x1, int8_t x2)
{
	vec6i8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;
	outv.v[5] = x2;

	return outv;
}
vec7i8_t Vec3i8_ToVec7i8(vec3i8_t v, int8_t x0, int8_t x1, int8_t x2, int8_t x3)
{
	vec7i8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;
	outv.v[5] = x2;
	outv.v[6] = x3;

	return outv;
}
vec8i8_t Vec3i8_ToVec8i8(vec3i8_t v, int8_t x0, int8_t x1, int8_t x2, int8_t x3, int8_t x4)
{
	vec8i8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = x0;
	outv.v[4] = x1;
	outv.v[5] = x2;
	outv.v[6] = x3;
	outv.v[7] = x4;

	return outv;
}
vec4f64_t Vec4f64_SetComponent(vec4f64_t v, int index, double value)
{
	v.v[index] = value;

	return v;
}
vec4f64_t Vec4f64_Vec(double x0, double x1, double x2, double x3)
{
	vec4f64_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;

	return v;
}
vec4f64_t Vec4f64_Add(vec4f64_t v0, vec4f64_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];

	return v0;
}
vec4f64_t Vec4f64_Sub(vec4f64_t v0, vec4f64_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];

	return v0;
}
double Vec4f64_GetComponent(vec4f64_t v, int index)
{
	return v.v[index];
}
vec4f64_t Vec4f64_Mul(vec4f64_t v0, vec4f64_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];

	return v0;
}
vec4f64_t Vec4f64_Div(vec4f64_t v0, vec4f64_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];

	return v0;
}
vec4f64_t Vec4f64_Scale(vec4f64_t v, double scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;

	return v;
}
vec4f64_t Vec4f64_DivScale(vec4f64_t v, double divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;

	return v;
}
vec4f64_t Vec4f64_MA(vec4f64_t v, vec4f64_t dir, double scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;

	return v;
}
vec4f64_t Vec4f64_DA(vec4f64_t v, vec4f64_t dir, double divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;

	return v;
}
double Vec4f64_Dot(vec4f64_t v0, vec4f64_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3];
}
double Vec4f64_LenSq(vec4f64_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3];
}
double Vec4f64_Len(vec4f64_t v)
{
	return sqrt(Vec4f64_LenSq(v));
}
vec4f64_t Vec4f64_Normalise(vec4f64_t v)
{
	double lensq = Vec4f64_LenSq(v);

	if (lensq == G_F64_ZERO)
		return v;
	else
		return Vec4f64_Scale(v, G_F64_ONE / sqrt(lensq));
}
vec4f64_t Vec4f64_Abs(vec4f64_t v)
{
	v.v[0] = fabs(v.v[0]);
	v.v[1] = fabs(v.v[1]);
	v.v[2] = fabs(v.v[2]);
	v.v[3] = fabs(v.v[3]);

	return v;
}
vec4f64_t Vec4f64_Floor(vec4f64_t v)
{
	v.v[0] = floor(v.v[0]);
	v.v[1] = floor(v.v[1]);
	v.v[2] = floor(v.v[2]);
	v.v[3] = floor(v.v[3]);

	return v;
}
vec4f64_t Vec4f64_Ceil(vec4f64_t v)
{
	v.v[0] = ceil(v.v[0]);
	v.v[1] = ceil(v.v[1]);
	v.v[2] = ceil(v.v[2]);
	v.v[3] = ceil(v.v[3]);

	return v;
}
vec4f64_t Vec4f64_Fract(vec4f64_t v)
{
	return Vec4f64_Sub(v, Vec4f64_Floor(v));
}
vec4f64_t Vec4f64_Mod(vec4f64_t v0, vec4f64_t v1)
{
	v0.v[0] = fmod(v0.v[0], v1.v[0]);
	v0.v[1] = fmod(v0.v[1], v1.v[1]);
	v0.v[2] = fmod(v0.v[2], v1.v[2]);
	v0.v[3] = fmod(v0.v[3], v1.v[3]);

	return v0;
}
vec4f64_t Vec4f64_ModS(vec4f64_t v0, double x)
{
	v0.v[0] = fmod(v0.v[0], x);
	v0.v[1] = fmod(v0.v[1], x);
	v0.v[2] = fmod(v0.v[2], x);
	v0.v[3] = fmod(v0.v[3], x);

	return v0;
}
vec4f64_t Vec4f64_Min(vec4f64_t v0, vec4f64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];

	return v0;
}
vec4f64_t Vec4f64_Max(vec4f64_t v0, vec4f64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];

	return v0;
}
vec4f64_t Vec4f64_MinS(vec4f64_t v0, double x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;

	return v0;
}
vec4f64_t Vec4f64_MaxS(vec4f64_t v0, double x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;

	return v0;
}
vec4f64_t Vec4f64_Clamp(vec4f64_t v, vec4f64_t min, vec4f64_t max)
{
	return Vec4f64_Max(Vec4f64_Min(v, max), min);
}
vec4f64_t Vec4f64_ClampS(vec4f64_t v, double min, double max)
{
	return Vec4f64_MaxS(Vec4f64_MinS(v, max), min);
}
vec4f64_t Vec4f64_Neg(vec4f64_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];
	v.v[3] = -v.v[3];

	return v;
}
vec4f64_t Vec4f64_Reciprocal(vec4f64_t v)
{
	v.v[0] = G_F64_ONE / v.v[0];
	v.v[1] = G_F64_ONE / v.v[1];
	v.v[2] = G_F64_ONE / v.v[2];
	v.v[3] = G_F64_ONE / v.v[3];

	return v;
}
vec4f64_t Vec4f64_Truncate(vec4f64_t v)
{
	v.v[0] = v.v[0] < G_F64_ZERO ? ceil(v.v[0]) : floor(v.v[0]);
	v.v[1] = v.v[1] < G_F64_ZERO ? ceil(v.v[1]) : floor(v.v[1]);
	v.v[2] = v.v[2] < G_F64_ZERO ? ceil(v.v[2]) : floor(v.v[2]);
	v.v[3] = v.v[3] < G_F64_ZERO ? ceil(v.v[3]) : floor(v.v[3]);

	return v;
}
vec4f64_t Vec4f64_TruncateAway(vec4f64_t v)
{
	v.v[0] = v.v[0] < G_F64_ZERO ? floor(v.v[0]) : ceil(v.v[0]);
	v.v[1] = v.v[1] < G_F64_ZERO ? floor(v.v[1]) : ceil(v.v[1]);
	v.v[2] = v.v[2] < G_F64_ZERO ? floor(v.v[2]) : ceil(v.v[2]);
	v.v[3] = v.v[3] < G_F64_ZERO ? floor(v.v[3]) : ceil(v.v[3]);

	return v;
}
vec4f64_t Vec4f64_CmpLT(vec4f64_t v0, vec4f64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec4f64_t Vec4f64_CmpLE(vec4f64_t v0, vec4f64_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec4f64_t Vec4f64_CmpEQ(vec4f64_t v0, vec4f64_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec4f64_t Vec4f64_CmpGT(vec4f64_t v0, vec4f64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec4f64_t Vec4f64_CmpGE(vec4f64_t v0, vec4f64_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec4f64_t Vec4f64_CmpNE(vec4f64_t v0, vec4f64_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec4f64_t Vec4f64_CmpLTS(vec4f64_t v0, double x)
{
	v0.v[0] = v0.v[0] < x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] < x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] < x ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] < x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec4f64_t Vec4f64_CmpLES(vec4f64_t v0, double x)
{
	v0.v[0] = v0.v[0] <= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec4f64_t Vec4f64_CmpEQS(vec4f64_t v0, double x)
{
	v0.v[0] = v0.v[0] == x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] == x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] == x ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] == x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec4f64_t Vec4f64_CmpGTS(vec4f64_t v0, double x)
{
	v0.v[0] = v0.v[0] > x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] > x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] > x ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] > x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec4f64_t Vec4f64_CmpGES(vec4f64_t v0, double x)
{
	v0.v[0] = v0.v[0] >= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec4f64_t Vec4f64_CmpNES(vec4f64_t v0, double x)
{
	v0.v[0] = v0.v[0] != x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] != x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] != x ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] != x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec4f64_t Vec4f64_Sign(vec4f64_t v)
{
	v.v[0] = v.v[0] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;
	v.v[1] = v.v[1] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;
	v.v[2] = v.v[2] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;
	v.v[3] = v.v[3] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;

	return v;
}
vec4f64_t Vec4f64_SignPosNeg(vec4f64_t v)
{
	v.v[0] = v.v[0] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;
	v.v[1] = v.v[1] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;
	v.v[2] = v.v[2] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;
	v.v[3] = v.v[3] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;

	return v;
}
vec4f64_t Vec4f64_Zero()
{
	return G_VEC4F64_T_ZERO;
}
vec4f64_t Vec4f64_One()
{
	return G_VEC4F64_T_ONE;
}
vec4f64_t Vec4f64_NegOne()
{
	return Vec4f64_Neg(G_VEC4F64_T_ONE);
}
vec4f64_t Vec4f64_Cross(vec4f64_t v0, vec4f64_t v1, vec4f64_t v2)
{
	vec4f64_t v;
	mat4x4f64_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;

	for (i = 0; i < 4; i++)
		v.v[i] = Mat3x3f64_Det(Mat4x4f64_DeleteRowColumn(mat, 0, i));

	return v;
}
vec4f64_t Vec4f64_Lerp(vec4f64_t v0, vec4f64_t v1, vec4f64_t vt)
{
	vec4f64_t v;

	v.v[0] = (G_F64_ONE - vt.v[0]) * v0.v[0] + v1.v[0] * vt.v[0];
	v.v[1] = (G_F64_ONE - vt.v[1]) * v0.v[1] + v1.v[1] * vt.v[1];
	v.v[2] = (G_F64_ONE - vt.v[2]) * v0.v[2] + v1.v[2] * vt.v[2];
	v.v[3] = (G_F64_ONE - vt.v[3]) * v0.v[3] + v1.v[3] * vt.v[3];

	return v;
}
vec4f64_t Vec4f64_LerpS(vec4f64_t v0, vec4f64_t v1, double t)
{
	vec4f64_t v;

	v.v[0] = (G_F64_ONE - t) * v0.v[0] + v1.v[0] * t;
	v.v[1] = (G_F64_ONE - t) * v0.v[1] + v1.v[1] * t;
	v.v[2] = (G_F64_ONE - t) * v0.v[2] + v1.v[2] * t;
	v.v[3] = (G_F64_ONE - t) * v0.v[3] + v1.v[3] * t;

	return v;
}
vec5f64_t Vec4f64_ToVec5f64(vec4f64_t v, double x0)
{
	vec5f64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;

	return outv;
}
vec6f64_t Vec4f64_ToVec6f64(vec4f64_t v, double x0, double x1)
{
	vec6f64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;
	outv.v[5] = x1;

	return outv;
}
vec7f64_t Vec4f64_ToVec7f64(vec4f64_t v, double x0, double x1, double x2)
{
	vec7f64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;
	outv.v[5] = x1;
	outv.v[6] = x2;

	return outv;
}
vec8f64_t Vec4f64_ToVec8f64(vec4f64_t v, double x0, double x1, double x2, double x3)
{
	vec8f64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;
	outv.v[5] = x1;
	outv.v[6] = x2;
	outv.v[7] = x3;

	return outv;
}
vec4f32_t Vec4f32_SetComponent(vec4f32_t v, int index, float value)
{
	v.v[index] = value;

	return v;
}
vec4f32_t Vec4f32_Vec(float x0, float x1, float x2, float x3)
{
	vec4f32_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;

	return v;
}
vec4f32_t Vec4f32_Add(vec4f32_t v0, vec4f32_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];

	return v0;
}
vec4f32_t Vec4f32_Sub(vec4f32_t v0, vec4f32_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];

	return v0;
}
float Vec4f32_GetComponent(vec4f32_t v, int index)
{
	return v.v[index];
}
vec4f32_t Vec4f32_Mul(vec4f32_t v0, vec4f32_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];

	return v0;
}
vec4f32_t Vec4f32_Div(vec4f32_t v0, vec4f32_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];

	return v0;
}
vec4f32_t Vec4f32_Scale(vec4f32_t v, float scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;

	return v;
}
vec4f32_t Vec4f32_DivScale(vec4f32_t v, float divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;

	return v;
}
vec4f32_t Vec4f32_MA(vec4f32_t v, vec4f32_t dir, float scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;

	return v;
}
vec4f32_t Vec4f32_DA(vec4f32_t v, vec4f32_t dir, float divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;

	return v;
}
float Vec4f32_Dot(vec4f32_t v0, vec4f32_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3];
}
float Vec4f32_LenSq(vec4f32_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3];
}
float Vec4f32_Len(vec4f32_t v)
{
	return sqrtf(Vec4f32_LenSq(v));
}
vec4f32_t Vec4f32_Normalise(vec4f32_t v)
{
	float lensq = Vec4f32_LenSq(v);

	if (lensq == G_F32_ZERO)
		return v;
	else
		return Vec4f32_Scale(v, G_F32_ONE / sqrtf(lensq));
}
vec4f32_t Vec4f32_Abs(vec4f32_t v)
{
	v.v[0] = fabsf(v.v[0]);
	v.v[1] = fabsf(v.v[1]);
	v.v[2] = fabsf(v.v[2]);
	v.v[3] = fabsf(v.v[3]);

	return v;
}
vec4f32_t Vec4f32_Floor(vec4f32_t v)
{
	v.v[0] = floorf(v.v[0]);
	v.v[1] = floorf(v.v[1]);
	v.v[2] = floorf(v.v[2]);
	v.v[3] = floorf(v.v[3]);

	return v;
}
vec4f32_t Vec4f32_Ceil(vec4f32_t v)
{
	v.v[0] = ceilf(v.v[0]);
	v.v[1] = ceilf(v.v[1]);
	v.v[2] = ceilf(v.v[2]);
	v.v[3] = ceilf(v.v[3]);

	return v;
}
vec4f32_t Vec4f32_Fract(vec4f32_t v)
{
	return Vec4f32_Sub(v, Vec4f32_Floor(v));
}
vec4f32_t Vec4f32_Mod(vec4f32_t v0, vec4f32_t v1)
{
	v0.v[0] = fmodf(v0.v[0], v1.v[0]);
	v0.v[1] = fmodf(v0.v[1], v1.v[1]);
	v0.v[2] = fmodf(v0.v[2], v1.v[2]);
	v0.v[3] = fmodf(v0.v[3], v1.v[3]);

	return v0;
}
vec4f32_t Vec4f32_ModS(vec4f32_t v0, float x)
{
	v0.v[0] = fmodf(v0.v[0], x);
	v0.v[1] = fmodf(v0.v[1], x);
	v0.v[2] = fmodf(v0.v[2], x);
	v0.v[3] = fmodf(v0.v[3], x);

	return v0;
}
vec4f32_t Vec4f32_Min(vec4f32_t v0, vec4f32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];

	return v0;
}
vec4f32_t Vec4f32_Max(vec4f32_t v0, vec4f32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];

	return v0;
}
vec4f32_t Vec4f32_MinS(vec4f32_t v0, float x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;

	return v0;
}
vec4f32_t Vec4f32_MaxS(vec4f32_t v0, float x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;

	return v0;
}
vec4f32_t Vec4f32_Clamp(vec4f32_t v, vec4f32_t min, vec4f32_t max)
{
	return Vec4f32_Max(Vec4f32_Min(v, max), min);
}
vec4f32_t Vec4f32_ClampS(vec4f32_t v, float min, float max)
{
	return Vec4f32_MaxS(Vec4f32_MinS(v, max), min);
}
vec4f32_t Vec4f32_Neg(vec4f32_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];
	v.v[3] = -v.v[3];

	return v;
}
vec4f32_t Vec4f32_Reciprocal(vec4f32_t v)
{
	v.v[0] = G_F32_ONE / v.v[0];
	v.v[1] = G_F32_ONE / v.v[1];
	v.v[2] = G_F32_ONE / v.v[2];
	v.v[3] = G_F32_ONE / v.v[3];

	return v;
}
vec4f32_t Vec4f32_Truncate(vec4f32_t v)
{
	v.v[0] = v.v[0] < G_F32_ZERO ? ceilf(v.v[0]) : floorf(v.v[0]);
	v.v[1] = v.v[1] < G_F32_ZERO ? ceilf(v.v[1]) : floorf(v.v[1]);
	v.v[2] = v.v[2] < G_F32_ZERO ? ceilf(v.v[2]) : floorf(v.v[2]);
	v.v[3] = v.v[3] < G_F32_ZERO ? ceilf(v.v[3]) : floorf(v.v[3]);

	return v;
}
vec4f32_t Vec4f32_TruncateAway(vec4f32_t v)
{
	v.v[0] = v.v[0] < G_F32_ZERO ? floorf(v.v[0]) : ceilf(v.v[0]);
	v.v[1] = v.v[1] < G_F32_ZERO ? floorf(v.v[1]) : ceilf(v.v[1]);
	v.v[2] = v.v[2] < G_F32_ZERO ? floorf(v.v[2]) : ceilf(v.v[2]);
	v.v[3] = v.v[3] < G_F32_ZERO ? floorf(v.v[3]) : ceilf(v.v[3]);

	return v;
}
vec4f32_t Vec4f32_CmpLT(vec4f32_t v0, vec4f32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec4f32_t Vec4f32_CmpLE(vec4f32_t v0, vec4f32_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec4f32_t Vec4f32_CmpEQ(vec4f32_t v0, vec4f32_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec4f32_t Vec4f32_CmpGT(vec4f32_t v0, vec4f32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec4f32_t Vec4f32_CmpGE(vec4f32_t v0, vec4f32_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec4f32_t Vec4f32_CmpNE(vec4f32_t v0, vec4f32_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec4f32_t Vec4f32_CmpLTS(vec4f32_t v0, float x)
{
	v0.v[0] = v0.v[0] < x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] < x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] < x ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] < x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec4f32_t Vec4f32_CmpLES(vec4f32_t v0, float x)
{
	v0.v[0] = v0.v[0] <= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec4f32_t Vec4f32_CmpEQS(vec4f32_t v0, float x)
{
	v0.v[0] = v0.v[0] == x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] == x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] == x ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] == x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec4f32_t Vec4f32_CmpGTS(vec4f32_t v0, float x)
{
	v0.v[0] = v0.v[0] > x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] > x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] > x ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] > x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec4f32_t Vec4f32_CmpGES(vec4f32_t v0, float x)
{
	v0.v[0] = v0.v[0] >= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec4f32_t Vec4f32_CmpNES(vec4f32_t v0, float x)
{
	v0.v[0] = v0.v[0] != x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] != x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] != x ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] != x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec4f32_t Vec4f32_Sign(vec4f32_t v)
{
	v.v[0] = v.v[0] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;
	v.v[1] = v.v[1] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;
	v.v[2] = v.v[2] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;
	v.v[3] = v.v[3] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;

	return v;
}
vec4f32_t Vec4f32_SignPosNeg(vec4f32_t v)
{
	v.v[0] = v.v[0] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;
	v.v[1] = v.v[1] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;
	v.v[2] = v.v[2] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;
	v.v[3] = v.v[3] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;

	return v;
}
vec4f32_t Vec4f32_Zero()
{
	return G_VEC4F32_T_ZERO;
}
vec4f32_t Vec4f32_One()
{
	return G_VEC4F32_T_ONE;
}
vec4f32_t Vec4f32_NegOne()
{
	return Vec4f32_Neg(G_VEC4F32_T_ONE);
}
vec4f32_t Vec4f32_Cross(vec4f32_t v0, vec4f32_t v1, vec4f32_t v2)
{
	vec4f32_t v;
	mat4x4f32_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;

	for (i = 0; i < 4; i++)
		v.v[i] = Mat3x3f32_Det(Mat4x4f32_DeleteRowColumn(mat, 0, i));

	return v;
}
vec4f32_t Vec4f32_Lerp(vec4f32_t v0, vec4f32_t v1, vec4f32_t vt)
{
	vec4f32_t v;

	v.v[0] = (G_F32_ONE - vt.v[0]) * v0.v[0] + v1.v[0] * vt.v[0];
	v.v[1] = (G_F32_ONE - vt.v[1]) * v0.v[1] + v1.v[1] * vt.v[1];
	v.v[2] = (G_F32_ONE - vt.v[2]) * v0.v[2] + v1.v[2] * vt.v[2];
	v.v[3] = (G_F32_ONE - vt.v[3]) * v0.v[3] + v1.v[3] * vt.v[3];

	return v;
}
vec4f32_t Vec4f32_LerpS(vec4f32_t v0, vec4f32_t v1, float t)
{
	vec4f32_t v;

	v.v[0] = (G_F32_ONE - t) * v0.v[0] + v1.v[0] * t;
	v.v[1] = (G_F32_ONE - t) * v0.v[1] + v1.v[1] * t;
	v.v[2] = (G_F32_ONE - t) * v0.v[2] + v1.v[2] * t;
	v.v[3] = (G_F32_ONE - t) * v0.v[3] + v1.v[3] * t;

	return v;
}
vec5f32_t Vec4f32_ToVec5f32(vec4f32_t v, float x0)
{
	vec5f32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;

	return outv;
}
vec6f32_t Vec4f32_ToVec6f32(vec4f32_t v, float x0, float x1)
{
	vec6f32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;
	outv.v[5] = x1;

	return outv;
}
vec7f32_t Vec4f32_ToVec7f32(vec4f32_t v, float x0, float x1, float x2)
{
	vec7f32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;
	outv.v[5] = x1;
	outv.v[6] = x2;

	return outv;
}
vec8f32_t Vec4f32_ToVec8f32(vec4f32_t v, float x0, float x1, float x2, float x3)
{
	vec8f32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;
	outv.v[5] = x1;
	outv.v[6] = x2;
	outv.v[7] = x3;

	return outv;
}
vec4u64_t Vec4u64_SetComponent(vec4u64_t v, int index, uint64_t value)
{
	v.v[index] = value;

	return v;
}
vec4u64_t Vec4u64_Vec(uint64_t x0, uint64_t x1, uint64_t x2, uint64_t x3)
{
	vec4u64_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;

	return v;
}
vec4u64_t Vec4u64_Add(vec4u64_t v0, vec4u64_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];

	return v0;
}
vec4u64_t Vec4u64_Sub(vec4u64_t v0, vec4u64_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];

	return v0;
}
uint64_t Vec4u64_GetComponent(vec4u64_t v, int index)
{
	return v.v[index];
}
vec4u64_t Vec4u64_Mul(vec4u64_t v0, vec4u64_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];

	return v0;
}
vec4u64_t Vec4u64_Div(vec4u64_t v0, vec4u64_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];

	return v0;
}
vec4u64_t Vec4u64_Scale(vec4u64_t v, uint64_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;

	return v;
}
vec4u64_t Vec4u64_DivScale(vec4u64_t v, uint64_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;

	return v;
}
vec4u64_t Vec4u64_MA(vec4u64_t v, vec4u64_t dir, uint64_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;

	return v;
}
vec4u64_t Vec4u64_DA(vec4u64_t v, vec4u64_t dir, uint64_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;

	return v;
}
uint64_t Vec4u64_Dot(vec4u64_t v0, vec4u64_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3];
}
uint64_t Vec4u64_LenSq(vec4u64_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3];
}
uint64_t Vec4u64_Len(vec4u64_t v)
{
	return sqrt(Vec4u64_LenSq(v));
}
vec4u64_t Vec4u64_Mod(vec4u64_t v0, vec4u64_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);

	return v0;
}
vec4u64_t Vec4u64_ModS(vec4u64_t v0, uint64_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);

	return v0;
}
vec4u64_t Vec4u64_Min(vec4u64_t v0, vec4u64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];

	return v0;
}
vec4u64_t Vec4u64_Max(vec4u64_t v0, vec4u64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];

	return v0;
}
vec4u64_t Vec4u64_MinS(vec4u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;

	return v0;
}
vec4u64_t Vec4u64_MaxS(vec4u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;

	return v0;
}
vec4u64_t Vec4u64_Clamp(vec4u64_t v, vec4u64_t min, vec4u64_t max)
{
	return Vec4u64_Max(Vec4u64_Min(v, max), min);
}
vec4u64_t Vec4u64_ClampS(vec4u64_t v, uint64_t min, uint64_t max)
{
	return Vec4u64_MaxS(Vec4u64_MinS(v, max), min);
}
vec4u64_t Vec4u64_CmpLT(vec4u64_t v0, vec4u64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec4u64_t Vec4u64_CmpLE(vec4u64_t v0, vec4u64_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec4u64_t Vec4u64_CmpEQ(vec4u64_t v0, vec4u64_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec4u64_t Vec4u64_CmpGT(vec4u64_t v0, vec4u64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec4u64_t Vec4u64_CmpGE(vec4u64_t v0, vec4u64_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec4u64_t Vec4u64_CmpNE(vec4u64_t v0, vec4u64_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec4u64_t Vec4u64_CmpLTS(vec4u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] < x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] < x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] < x ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] < x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec4u64_t Vec4u64_CmpLES(vec4u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec4u64_t Vec4u64_CmpEQS(vec4u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] == x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] == x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] == x ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] == x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec4u64_t Vec4u64_CmpGTS(vec4u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] > x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] > x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] > x ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] > x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec4u64_t Vec4u64_CmpGES(vec4u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec4u64_t Vec4u64_CmpNES(vec4u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] != x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] != x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] != x ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] != x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec4u64_t Vec4u64_Sign(vec4u64_t v)
{
	v.v[0] = v.v[0] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;
	v.v[1] = v.v[1] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;
	v.v[2] = v.v[2] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;
	v.v[3] = v.v[3] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;

	return v;
}
vec4u64_t Vec4u64_SignPosNeg(vec4u64_t v)
{
	v.v[0] = v.v[0] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;
	v.v[1] = v.v[1] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;
	v.v[2] = v.v[2] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;
	v.v[3] = v.v[3] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;

	return v;
}
vec4u64_t Vec4u64_Zero()
{
	return G_VEC4U64_T_ZERO;
}
vec4u64_t Vec4u64_One()
{
	return G_VEC4U64_T_ONE;
}
vec4u64_t Vec4u64_Cross(vec4u64_t v0, vec4u64_t v1, vec4u64_t v2)
{
	vec4u64_t v;
	mat4x4u64_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;

	for (i = 0; i < 4; i++)
		v.v[i] = Mat3x3u64_Det(Mat4x4u64_DeleteRowColumn(mat, 0, i));

	return v;
}
vec5u64_t Vec4u64_ToVec5u64(vec4u64_t v, uint64_t x0)
{
	vec5u64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;

	return outv;
}
vec6u64_t Vec4u64_ToVec6u64(vec4u64_t v, uint64_t x0, uint64_t x1)
{
	vec6u64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;
	outv.v[5] = x1;

	return outv;
}
vec7u64_t Vec4u64_ToVec7u64(vec4u64_t v, uint64_t x0, uint64_t x1, uint64_t x2)
{
	vec7u64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;
	outv.v[5] = x1;
	outv.v[6] = x2;

	return outv;
}
vec8u64_t Vec4u64_ToVec8u64(vec4u64_t v, uint64_t x0, uint64_t x1, uint64_t x2, uint64_t x3)
{
	vec8u64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;
	outv.v[5] = x1;
	outv.v[6] = x2;
	outv.v[7] = x3;

	return outv;
}
vec4i64_t Vec4i64_SetComponent(vec4i64_t v, int index, int64_t value)
{
	v.v[index] = value;

	return v;
}
vec4i64_t Vec4i64_Vec(int64_t x0, int64_t x1, int64_t x2, int64_t x3)
{
	vec4i64_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;

	return v;
}
vec4i64_t Vec4i64_Add(vec4i64_t v0, vec4i64_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];

	return v0;
}
vec4i64_t Vec4i64_Sub(vec4i64_t v0, vec4i64_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];

	return v0;
}
int64_t Vec4i64_GetComponent(vec4i64_t v, int index)
{
	return v.v[index];
}
vec4i64_t Vec4i64_Mul(vec4i64_t v0, vec4i64_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];

	return v0;
}
vec4i64_t Vec4i64_Div(vec4i64_t v0, vec4i64_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];

	return v0;
}
vec4i64_t Vec4i64_Scale(vec4i64_t v, int64_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;

	return v;
}
vec4i64_t Vec4i64_DivScale(vec4i64_t v, int64_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;

	return v;
}
vec4i64_t Vec4i64_MA(vec4i64_t v, vec4i64_t dir, int64_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;

	return v;
}
vec4i64_t Vec4i64_DA(vec4i64_t v, vec4i64_t dir, int64_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;

	return v;
}
int64_t Vec4i64_Dot(vec4i64_t v0, vec4i64_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3];
}
int64_t Vec4i64_LenSq(vec4i64_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3];
}
int64_t Vec4i64_Len(vec4i64_t v)
{
	return sqrt(Vec4i64_LenSq(v));
}
vec4i64_t Vec4i64_Abs(vec4i64_t v)
{
	v.v[0] = (v.v[0] < 0 ? -v.v[0] : v.v[0]);
	v.v[1] = (v.v[1] < 0 ? -v.v[1] : v.v[1]);
	v.v[2] = (v.v[2] < 0 ? -v.v[2] : v.v[2]);
	v.v[3] = (v.v[3] < 0 ? -v.v[3] : v.v[3]);

	return v;
}
vec4i64_t Vec4i64_Mod(vec4i64_t v0, vec4i64_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);

	return v0;
}
vec4i64_t Vec4i64_ModS(vec4i64_t v0, int64_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);

	return v0;
}
vec4i64_t Vec4i64_Min(vec4i64_t v0, vec4i64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];

	return v0;
}
vec4i64_t Vec4i64_Max(vec4i64_t v0, vec4i64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];

	return v0;
}
vec4i64_t Vec4i64_MinS(vec4i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;

	return v0;
}
vec4i64_t Vec4i64_MaxS(vec4i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;

	return v0;
}
vec4i64_t Vec4i64_Clamp(vec4i64_t v, vec4i64_t min, vec4i64_t max)
{
	return Vec4i64_Max(Vec4i64_Min(v, max), min);
}
vec4i64_t Vec4i64_ClampS(vec4i64_t v, int64_t min, int64_t max)
{
	return Vec4i64_MaxS(Vec4i64_MinS(v, max), min);
}
vec4i64_t Vec4i64_Neg(vec4i64_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];
	v.v[3] = -v.v[3];

	return v;
}
vec4i64_t Vec4i64_CmpLT(vec4i64_t v0, vec4i64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec4i64_t Vec4i64_CmpLE(vec4i64_t v0, vec4i64_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec4i64_t Vec4i64_CmpEQ(vec4i64_t v0, vec4i64_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec4i64_t Vec4i64_CmpGT(vec4i64_t v0, vec4i64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec4i64_t Vec4i64_CmpGE(vec4i64_t v0, vec4i64_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec4i64_t Vec4i64_CmpNE(vec4i64_t v0, vec4i64_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec4i64_t Vec4i64_CmpLTS(vec4i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] < x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] < x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] < x ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] < x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec4i64_t Vec4i64_CmpLES(vec4i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec4i64_t Vec4i64_CmpEQS(vec4i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] == x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] == x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] == x ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] == x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec4i64_t Vec4i64_CmpGTS(vec4i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] > x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] > x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] > x ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] > x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec4i64_t Vec4i64_CmpGES(vec4i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec4i64_t Vec4i64_CmpNES(vec4i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] != x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] != x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] != x ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] != x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec4i64_t Vec4i64_Sign(vec4i64_t v)
{
	v.v[0] = v.v[0] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;
	v.v[1] = v.v[1] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;
	v.v[2] = v.v[2] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;
	v.v[3] = v.v[3] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;

	return v;
}
vec4i64_t Vec4i64_SignPosNeg(vec4i64_t v)
{
	v.v[0] = v.v[0] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;
	v.v[1] = v.v[1] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;
	v.v[2] = v.v[2] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;
	v.v[3] = v.v[3] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;

	return v;
}
vec4i64_t Vec4i64_Zero()
{
	return G_VEC4I64_T_ZERO;
}
vec4i64_t Vec4i64_One()
{
	return G_VEC4I64_T_ONE;
}
vec4i64_t Vec4i64_NegOne()
{
	return Vec4i64_Neg(G_VEC4I64_T_ONE);
}
vec4i64_t Vec4i64_Cross(vec4i64_t v0, vec4i64_t v1, vec4i64_t v2)
{
	vec4i64_t v;
	mat4x4i64_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;

	for (i = 0; i < 4; i++)
		v.v[i] = Mat3x3i64_Det(Mat4x4i64_DeleteRowColumn(mat, 0, i));

	return v;
}
vec5i64_t Vec4i64_ToVec5i64(vec4i64_t v, int64_t x0)
{
	vec5i64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;

	return outv;
}
vec6i64_t Vec4i64_ToVec6i64(vec4i64_t v, int64_t x0, int64_t x1)
{
	vec6i64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;
	outv.v[5] = x1;

	return outv;
}
vec7i64_t Vec4i64_ToVec7i64(vec4i64_t v, int64_t x0, int64_t x1, int64_t x2)
{
	vec7i64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;
	outv.v[5] = x1;
	outv.v[6] = x2;

	return outv;
}
vec8i64_t Vec4i64_ToVec8i64(vec4i64_t v, int64_t x0, int64_t x1, int64_t x2, int64_t x3)
{
	vec8i64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;
	outv.v[5] = x1;
	outv.v[6] = x2;
	outv.v[7] = x3;

	return outv;
}
vec4u32_t Vec4u32_SetComponent(vec4u32_t v, int index, uint32_t value)
{
	v.v[index] = value;

	return v;
}
vec4u32_t Vec4u32_Vec(uint32_t x0, uint32_t x1, uint32_t x2, uint32_t x3)
{
	vec4u32_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;

	return v;
}
vec4u32_t Vec4u32_Add(vec4u32_t v0, vec4u32_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];

	return v0;
}
vec4u32_t Vec4u32_Sub(vec4u32_t v0, vec4u32_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];

	return v0;
}
uint32_t Vec4u32_GetComponent(vec4u32_t v, int index)
{
	return v.v[index];
}
vec4u32_t Vec4u32_Mul(vec4u32_t v0, vec4u32_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];

	return v0;
}
vec4u32_t Vec4u32_Div(vec4u32_t v0, vec4u32_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];

	return v0;
}
vec4u32_t Vec4u32_Scale(vec4u32_t v, uint32_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;

	return v;
}
vec4u32_t Vec4u32_DivScale(vec4u32_t v, uint32_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;

	return v;
}
vec4u32_t Vec4u32_MA(vec4u32_t v, vec4u32_t dir, uint32_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;

	return v;
}
vec4u32_t Vec4u32_DA(vec4u32_t v, vec4u32_t dir, uint32_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;

	return v;
}
uint32_t Vec4u32_Dot(vec4u32_t v0, vec4u32_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3];
}
uint32_t Vec4u32_LenSq(vec4u32_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3];
}
uint32_t Vec4u32_Len(vec4u32_t v)
{
	return sqrtf(Vec4u32_LenSq(v));
}
vec4u32_t Vec4u32_Mod(vec4u32_t v0, vec4u32_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);

	return v0;
}
vec4u32_t Vec4u32_ModS(vec4u32_t v0, uint32_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);

	return v0;
}
vec4u32_t Vec4u32_Min(vec4u32_t v0, vec4u32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];

	return v0;
}
vec4u32_t Vec4u32_Max(vec4u32_t v0, vec4u32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];

	return v0;
}
vec4u32_t Vec4u32_MinS(vec4u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;

	return v0;
}
vec4u32_t Vec4u32_MaxS(vec4u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;

	return v0;
}
vec4u32_t Vec4u32_Clamp(vec4u32_t v, vec4u32_t min, vec4u32_t max)
{
	return Vec4u32_Max(Vec4u32_Min(v, max), min);
}
vec4u32_t Vec4u32_ClampS(vec4u32_t v, uint32_t min, uint32_t max)
{
	return Vec4u32_MaxS(Vec4u32_MinS(v, max), min);
}
vec4u32_t Vec4u32_CmpLT(vec4u32_t v0, vec4u32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec4u32_t Vec4u32_CmpLE(vec4u32_t v0, vec4u32_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec4u32_t Vec4u32_CmpEQ(vec4u32_t v0, vec4u32_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec4u32_t Vec4u32_CmpGT(vec4u32_t v0, vec4u32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec4u32_t Vec4u32_CmpGE(vec4u32_t v0, vec4u32_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec4u32_t Vec4u32_CmpNE(vec4u32_t v0, vec4u32_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec4u32_t Vec4u32_CmpLTS(vec4u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] < x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] < x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] < x ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] < x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec4u32_t Vec4u32_CmpLES(vec4u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec4u32_t Vec4u32_CmpEQS(vec4u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] == x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] == x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] == x ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] == x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec4u32_t Vec4u32_CmpGTS(vec4u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] > x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] > x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] > x ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] > x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec4u32_t Vec4u32_CmpGES(vec4u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec4u32_t Vec4u32_CmpNES(vec4u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] != x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] != x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] != x ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] != x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec4u32_t Vec4u32_Sign(vec4u32_t v)
{
	v.v[0] = v.v[0] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;
	v.v[1] = v.v[1] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;
	v.v[2] = v.v[2] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;
	v.v[3] = v.v[3] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;

	return v;
}
vec4u32_t Vec4u32_SignPosNeg(vec4u32_t v)
{
	v.v[0] = v.v[0] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;
	v.v[1] = v.v[1] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;
	v.v[2] = v.v[2] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;
	v.v[3] = v.v[3] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;

	return v;
}
vec4u32_t Vec4u32_Zero()
{
	return G_VEC4U32_T_ZERO;
}
vec4u32_t Vec4u32_One()
{
	return G_VEC4U32_T_ONE;
}
vec4u32_t Vec4u32_Cross(vec4u32_t v0, vec4u32_t v1, vec4u32_t v2)
{
	vec4u32_t v;
	mat4x4u32_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;

	for (i = 0; i < 4; i++)
		v.v[i] = Mat3x3u32_Det(Mat4x4u32_DeleteRowColumn(mat, 0, i));

	return v;
}
vec5u32_t Vec4u32_ToVec5u32(vec4u32_t v, uint32_t x0)
{
	vec5u32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;

	return outv;
}
vec6u32_t Vec4u32_ToVec6u32(vec4u32_t v, uint32_t x0, uint32_t x1)
{
	vec6u32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;
	outv.v[5] = x1;

	return outv;
}
vec7u32_t Vec4u32_ToVec7u32(vec4u32_t v, uint32_t x0, uint32_t x1, uint32_t x2)
{
	vec7u32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;
	outv.v[5] = x1;
	outv.v[6] = x2;

	return outv;
}
vec8u32_t Vec4u32_ToVec8u32(vec4u32_t v, uint32_t x0, uint32_t x1, uint32_t x2, uint32_t x3)
{
	vec8u32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;
	outv.v[5] = x1;
	outv.v[6] = x2;
	outv.v[7] = x3;

	return outv;
}
vec4i32_t Vec4i32_SetComponent(vec4i32_t v, int index, int32_t value)
{
	v.v[index] = value;

	return v;
}
vec4i32_t Vec4i32_Vec(int32_t x0, int32_t x1, int32_t x2, int32_t x3)
{
	vec4i32_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;

	return v;
}
vec4i32_t Vec4i32_Add(vec4i32_t v0, vec4i32_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];

	return v0;
}
vec4i32_t Vec4i32_Sub(vec4i32_t v0, vec4i32_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];

	return v0;
}
int32_t Vec4i32_GetComponent(vec4i32_t v, int index)
{
	return v.v[index];
}
vec4i32_t Vec4i32_Mul(vec4i32_t v0, vec4i32_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];

	return v0;
}
vec4i32_t Vec4i32_Div(vec4i32_t v0, vec4i32_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];

	return v0;
}
vec4i32_t Vec4i32_Scale(vec4i32_t v, int32_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;

	return v;
}
vec4i32_t Vec4i32_DivScale(vec4i32_t v, int32_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;

	return v;
}
vec4i32_t Vec4i32_MA(vec4i32_t v, vec4i32_t dir, int32_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;

	return v;
}
vec4i32_t Vec4i32_DA(vec4i32_t v, vec4i32_t dir, int32_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;

	return v;
}
int32_t Vec4i32_Dot(vec4i32_t v0, vec4i32_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3];
}
int32_t Vec4i32_LenSq(vec4i32_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3];
}
int32_t Vec4i32_Len(vec4i32_t v)
{
	return sqrtf(Vec4i32_LenSq(v));
}
vec4i32_t Vec4i32_Abs(vec4i32_t v)
{
	v.v[0] = (v.v[0] < 0 ? -v.v[0] : v.v[0]);
	v.v[1] = (v.v[1] < 0 ? -v.v[1] : v.v[1]);
	v.v[2] = (v.v[2] < 0 ? -v.v[2] : v.v[2]);
	v.v[3] = (v.v[3] < 0 ? -v.v[3] : v.v[3]);

	return v;
}
vec4i32_t Vec4i32_Mod(vec4i32_t v0, vec4i32_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);

	return v0;
}
vec4i32_t Vec4i32_ModS(vec4i32_t v0, int32_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);

	return v0;
}
vec4i32_t Vec4i32_Min(vec4i32_t v0, vec4i32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];

	return v0;
}
vec4i32_t Vec4i32_Max(vec4i32_t v0, vec4i32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];

	return v0;
}
vec4i32_t Vec4i32_MinS(vec4i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;

	return v0;
}
vec4i32_t Vec4i32_MaxS(vec4i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;

	return v0;
}
vec4i32_t Vec4i32_Clamp(vec4i32_t v, vec4i32_t min, vec4i32_t max)
{
	return Vec4i32_Max(Vec4i32_Min(v, max), min);
}
vec4i32_t Vec4i32_ClampS(vec4i32_t v, int32_t min, int32_t max)
{
	return Vec4i32_MaxS(Vec4i32_MinS(v, max), min);
}
vec4i32_t Vec4i32_Neg(vec4i32_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];
	v.v[3] = -v.v[3];

	return v;
}
vec4i32_t Vec4i32_CmpLT(vec4i32_t v0, vec4i32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec4i32_t Vec4i32_CmpLE(vec4i32_t v0, vec4i32_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec4i32_t Vec4i32_CmpEQ(vec4i32_t v0, vec4i32_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec4i32_t Vec4i32_CmpGT(vec4i32_t v0, vec4i32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec4i32_t Vec4i32_CmpGE(vec4i32_t v0, vec4i32_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec4i32_t Vec4i32_CmpNE(vec4i32_t v0, vec4i32_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec4i32_t Vec4i32_CmpLTS(vec4i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] < x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] < x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] < x ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] < x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec4i32_t Vec4i32_CmpLES(vec4i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec4i32_t Vec4i32_CmpEQS(vec4i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] == x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] == x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] == x ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] == x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec4i32_t Vec4i32_CmpGTS(vec4i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] > x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] > x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] > x ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] > x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec4i32_t Vec4i32_CmpGES(vec4i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec4i32_t Vec4i32_CmpNES(vec4i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] != x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] != x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] != x ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] != x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec4i32_t Vec4i32_Sign(vec4i32_t v)
{
	v.v[0] = v.v[0] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;
	v.v[1] = v.v[1] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;
	v.v[2] = v.v[2] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;
	v.v[3] = v.v[3] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;

	return v;
}
vec4i32_t Vec4i32_SignPosNeg(vec4i32_t v)
{
	v.v[0] = v.v[0] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;
	v.v[1] = v.v[1] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;
	v.v[2] = v.v[2] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;
	v.v[3] = v.v[3] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;

	return v;
}
vec4i32_t Vec4i32_Zero()
{
	return G_VEC4I32_T_ZERO;
}
vec4i32_t Vec4i32_One()
{
	return G_VEC4I32_T_ONE;
}
vec4i32_t Vec4i32_NegOne()
{
	return Vec4i32_Neg(G_VEC4I32_T_ONE);
}
vec4i32_t Vec4i32_Cross(vec4i32_t v0, vec4i32_t v1, vec4i32_t v2)
{
	vec4i32_t v;
	mat4x4i32_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;

	for (i = 0; i < 4; i++)
		v.v[i] = Mat3x3i32_Det(Mat4x4i32_DeleteRowColumn(mat, 0, i));

	return v;
}
vec5i32_t Vec4i32_ToVec5i32(vec4i32_t v, int32_t x0)
{
	vec5i32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;

	return outv;
}
vec6i32_t Vec4i32_ToVec6i32(vec4i32_t v, int32_t x0, int32_t x1)
{
	vec6i32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;
	outv.v[5] = x1;

	return outv;
}
vec7i32_t Vec4i32_ToVec7i32(vec4i32_t v, int32_t x0, int32_t x1, int32_t x2)
{
	vec7i32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;
	outv.v[5] = x1;
	outv.v[6] = x2;

	return outv;
}
vec8i32_t Vec4i32_ToVec8i32(vec4i32_t v, int32_t x0, int32_t x1, int32_t x2, int32_t x3)
{
	vec8i32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;
	outv.v[5] = x1;
	outv.v[6] = x2;
	outv.v[7] = x3;

	return outv;
}
vec4u16_t Vec4u16_SetComponent(vec4u16_t v, int index, uint16_t value)
{
	v.v[index] = value;

	return v;
}
vec4u16_t Vec4u16_Vec(uint16_t x0, uint16_t x1, uint16_t x2, uint16_t x3)
{
	vec4u16_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;

	return v;
}
vec4u16_t Vec4u16_Add(vec4u16_t v0, vec4u16_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];

	return v0;
}
vec4u16_t Vec4u16_Sub(vec4u16_t v0, vec4u16_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];

	return v0;
}
uint16_t Vec4u16_GetComponent(vec4u16_t v, int index)
{
	return v.v[index];
}
vec4u16_t Vec4u16_Mul(vec4u16_t v0, vec4u16_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];

	return v0;
}
vec4u16_t Vec4u16_Div(vec4u16_t v0, vec4u16_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];

	return v0;
}
vec4u16_t Vec4u16_Scale(vec4u16_t v, uint16_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;

	return v;
}
vec4u16_t Vec4u16_DivScale(vec4u16_t v, uint16_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;

	return v;
}
vec4u16_t Vec4u16_MA(vec4u16_t v, vec4u16_t dir, uint16_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;

	return v;
}
vec4u16_t Vec4u16_DA(vec4u16_t v, vec4u16_t dir, uint16_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;

	return v;
}
uint16_t Vec4u16_Dot(vec4u16_t v0, vec4u16_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3];
}
uint16_t Vec4u16_LenSq(vec4u16_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3];
}
uint16_t Vec4u16_Len(vec4u16_t v)
{
	return sqrtf(Vec4u16_LenSq(v));
}
vec4u16_t Vec4u16_Mod(vec4u16_t v0, vec4u16_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);

	return v0;
}
vec4u16_t Vec4u16_ModS(vec4u16_t v0, uint16_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);

	return v0;
}
vec4u16_t Vec4u16_Min(vec4u16_t v0, vec4u16_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];

	return v0;
}
vec4u16_t Vec4u16_Max(vec4u16_t v0, vec4u16_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];

	return v0;
}
vec4u16_t Vec4u16_MinS(vec4u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;

	return v0;
}
vec4u16_t Vec4u16_MaxS(vec4u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;

	return v0;
}
vec4u16_t Vec4u16_Clamp(vec4u16_t v, vec4u16_t min, vec4u16_t max)
{
	return Vec4u16_Max(Vec4u16_Min(v, max), min);
}
vec4u16_t Vec4u16_ClampS(vec4u16_t v, uint16_t min, uint16_t max)
{
	return Vec4u16_MaxS(Vec4u16_MinS(v, max), min);
}
vec4u16_t Vec4u16_CmpLT(vec4u16_t v0, vec4u16_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec4u16_t Vec4u16_CmpLE(vec4u16_t v0, vec4u16_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec4u16_t Vec4u16_CmpEQ(vec4u16_t v0, vec4u16_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec4u16_t Vec4u16_CmpGT(vec4u16_t v0, vec4u16_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec4u16_t Vec4u16_CmpGE(vec4u16_t v0, vec4u16_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec4u16_t Vec4u16_CmpNE(vec4u16_t v0, vec4u16_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec4u16_t Vec4u16_CmpLTS(vec4u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] < x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] < x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] < x ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] < x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec4u16_t Vec4u16_CmpLES(vec4u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec4u16_t Vec4u16_CmpEQS(vec4u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] == x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] == x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] == x ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] == x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec4u16_t Vec4u16_CmpGTS(vec4u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] > x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] > x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] > x ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] > x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec4u16_t Vec4u16_CmpGES(vec4u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec4u16_t Vec4u16_CmpNES(vec4u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] != x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] != x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] != x ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] != x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec4u16_t Vec4u16_Sign(vec4u16_t v)
{
	v.v[0] = v.v[0] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;
	v.v[1] = v.v[1] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;
	v.v[2] = v.v[2] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;
	v.v[3] = v.v[3] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;

	return v;
}
vec4u16_t Vec4u16_SignPosNeg(vec4u16_t v)
{
	v.v[0] = v.v[0] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;
	v.v[1] = v.v[1] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;
	v.v[2] = v.v[2] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;
	v.v[3] = v.v[3] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;

	return v;
}
vec4u16_t Vec4u16_Zero()
{
	return G_VEC4U16_T_ZERO;
}
vec4u16_t Vec4u16_One()
{
	return G_VEC4U16_T_ONE;
}
vec4u16_t Vec4u16_Cross(vec4u16_t v0, vec4u16_t v1, vec4u16_t v2)
{
	vec4u16_t v;
	mat4x4u16_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;

	for (i = 0; i < 4; i++)
		v.v[i] = Mat3x3u16_Det(Mat4x4u16_DeleteRowColumn(mat, 0, i));

	return v;
}
vec5u16_t Vec4u16_ToVec5u16(vec4u16_t v, uint16_t x0)
{
	vec5u16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;

	return outv;
}
vec6u16_t Vec4u16_ToVec6u16(vec4u16_t v, uint16_t x0, uint16_t x1)
{
	vec6u16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;
	outv.v[5] = x1;

	return outv;
}
vec7u16_t Vec4u16_ToVec7u16(vec4u16_t v, uint16_t x0, uint16_t x1, uint16_t x2)
{
	vec7u16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;
	outv.v[5] = x1;
	outv.v[6] = x2;

	return outv;
}
vec8u16_t Vec4u16_ToVec8u16(vec4u16_t v, uint16_t x0, uint16_t x1, uint16_t x2, uint16_t x3)
{
	vec8u16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;
	outv.v[5] = x1;
	outv.v[6] = x2;
	outv.v[7] = x3;

	return outv;
}
vec4i16_t Vec4i16_SetComponent(vec4i16_t v, int index, int16_t value)
{
	v.v[index] = value;

	return v;
}
vec4i16_t Vec4i16_Vec(int16_t x0, int16_t x1, int16_t x2, int16_t x3)
{
	vec4i16_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;

	return v;
}
vec4i16_t Vec4i16_Add(vec4i16_t v0, vec4i16_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];

	return v0;
}
vec4i16_t Vec4i16_Sub(vec4i16_t v0, vec4i16_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];

	return v0;
}
int16_t Vec4i16_GetComponent(vec4i16_t v, int index)
{
	return v.v[index];
}
vec4i16_t Vec4i16_Mul(vec4i16_t v0, vec4i16_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];

	return v0;
}
vec4i16_t Vec4i16_Div(vec4i16_t v0, vec4i16_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];

	return v0;
}
vec4i16_t Vec4i16_Scale(vec4i16_t v, int16_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;

	return v;
}
vec4i16_t Vec4i16_DivScale(vec4i16_t v, int16_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;

	return v;
}
vec4i16_t Vec4i16_MA(vec4i16_t v, vec4i16_t dir, int16_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;

	return v;
}
vec4i16_t Vec4i16_DA(vec4i16_t v, vec4i16_t dir, int16_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;

	return v;
}
int16_t Vec4i16_Dot(vec4i16_t v0, vec4i16_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3];
}
int16_t Vec4i16_LenSq(vec4i16_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3];
}
int16_t Vec4i16_Len(vec4i16_t v)
{
	return sqrtf(Vec4i16_LenSq(v));
}
vec4i16_t Vec4i16_Abs(vec4i16_t v)
{
	v.v[0] = (v.v[0] < 0 ? -v.v[0] : v.v[0]);
	v.v[1] = (v.v[1] < 0 ? -v.v[1] : v.v[1]);
	v.v[2] = (v.v[2] < 0 ? -v.v[2] : v.v[2]);
	v.v[3] = (v.v[3] < 0 ? -v.v[3] : v.v[3]);

	return v;
}
vec4i16_t Vec4i16_Mod(vec4i16_t v0, vec4i16_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);

	return v0;
}
vec4i16_t Vec4i16_ModS(vec4i16_t v0, int16_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);

	return v0;
}
vec4i16_t Vec4i16_Min(vec4i16_t v0, vec4i16_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];

	return v0;
}
vec4i16_t Vec4i16_Max(vec4i16_t v0, vec4i16_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];

	return v0;
}
vec4i16_t Vec4i16_MinS(vec4i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;

	return v0;
}
vec4i16_t Vec4i16_MaxS(vec4i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;

	return v0;
}
vec4i16_t Vec4i16_Clamp(vec4i16_t v, vec4i16_t min, vec4i16_t max)
{
	return Vec4i16_Max(Vec4i16_Min(v, max), min);
}
vec4i16_t Vec4i16_ClampS(vec4i16_t v, int16_t min, int16_t max)
{
	return Vec4i16_MaxS(Vec4i16_MinS(v, max), min);
}
vec4i16_t Vec4i16_Neg(vec4i16_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];
	v.v[3] = -v.v[3];

	return v;
}
vec4i16_t Vec4i16_CmpLT(vec4i16_t v0, vec4i16_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec4i16_t Vec4i16_CmpLE(vec4i16_t v0, vec4i16_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec4i16_t Vec4i16_CmpEQ(vec4i16_t v0, vec4i16_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec4i16_t Vec4i16_CmpGT(vec4i16_t v0, vec4i16_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec4i16_t Vec4i16_CmpGE(vec4i16_t v0, vec4i16_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec4i16_t Vec4i16_CmpNE(vec4i16_t v0, vec4i16_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec4i16_t Vec4i16_CmpLTS(vec4i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] < x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] < x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] < x ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] < x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec4i16_t Vec4i16_CmpLES(vec4i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec4i16_t Vec4i16_CmpEQS(vec4i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] == x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] == x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] == x ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] == x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec4i16_t Vec4i16_CmpGTS(vec4i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] > x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] > x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] > x ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] > x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec4i16_t Vec4i16_CmpGES(vec4i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec4i16_t Vec4i16_CmpNES(vec4i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] != x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] != x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] != x ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] != x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec4i16_t Vec4i16_Sign(vec4i16_t v)
{
	v.v[0] = v.v[0] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;
	v.v[1] = v.v[1] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;
	v.v[2] = v.v[2] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;
	v.v[3] = v.v[3] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;

	return v;
}
vec4i16_t Vec4i16_SignPosNeg(vec4i16_t v)
{
	v.v[0] = v.v[0] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;
	v.v[1] = v.v[1] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;
	v.v[2] = v.v[2] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;
	v.v[3] = v.v[3] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;

	return v;
}
vec4i16_t Vec4i16_Zero()
{
	return G_VEC4I16_T_ZERO;
}
vec4i16_t Vec4i16_One()
{
	return G_VEC4I16_T_ONE;
}
vec4i16_t Vec4i16_NegOne()
{
	return Vec4i16_Neg(G_VEC4I16_T_ONE);
}
vec4i16_t Vec4i16_Cross(vec4i16_t v0, vec4i16_t v1, vec4i16_t v2)
{
	vec4i16_t v;
	mat4x4i16_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;

	for (i = 0; i < 4; i++)
		v.v[i] = Mat3x3i16_Det(Mat4x4i16_DeleteRowColumn(mat, 0, i));

	return v;
}
vec5i16_t Vec4i16_ToVec5i16(vec4i16_t v, int16_t x0)
{
	vec5i16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;

	return outv;
}
vec6i16_t Vec4i16_ToVec6i16(vec4i16_t v, int16_t x0, int16_t x1)
{
	vec6i16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;
	outv.v[5] = x1;

	return outv;
}
vec7i16_t Vec4i16_ToVec7i16(vec4i16_t v, int16_t x0, int16_t x1, int16_t x2)
{
	vec7i16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;
	outv.v[5] = x1;
	outv.v[6] = x2;

	return outv;
}
vec8i16_t Vec4i16_ToVec8i16(vec4i16_t v, int16_t x0, int16_t x1, int16_t x2, int16_t x3)
{
	vec8i16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;
	outv.v[5] = x1;
	outv.v[6] = x2;
	outv.v[7] = x3;

	return outv;
}
vec4u8_t Vec4u8_SetComponent(vec4u8_t v, int index, uint8_t value)
{
	v.v[index] = value;

	return v;
}
vec4u8_t Vec4u8_Vec(uint8_t x0, uint8_t x1, uint8_t x2, uint8_t x3)
{
	vec4u8_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;

	return v;
}
vec4u8_t Vec4u8_Add(vec4u8_t v0, vec4u8_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];

	return v0;
}
vec4u8_t Vec4u8_Sub(vec4u8_t v0, vec4u8_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];

	return v0;
}
uint8_t Vec4u8_GetComponent(vec4u8_t v, int index)
{
	return v.v[index];
}
vec4u8_t Vec4u8_Mul(vec4u8_t v0, vec4u8_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];

	return v0;
}
vec4u8_t Vec4u8_Div(vec4u8_t v0, vec4u8_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];

	return v0;
}
vec4u8_t Vec4u8_Scale(vec4u8_t v, uint8_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;

	return v;
}
vec4u8_t Vec4u8_DivScale(vec4u8_t v, uint8_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;

	return v;
}
vec4u8_t Vec4u8_MA(vec4u8_t v, vec4u8_t dir, uint8_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;

	return v;
}
vec4u8_t Vec4u8_DA(vec4u8_t v, vec4u8_t dir, uint8_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;

	return v;
}
uint8_t Vec4u8_Dot(vec4u8_t v0, vec4u8_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3];
}
uint8_t Vec4u8_LenSq(vec4u8_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3];
}
uint8_t Vec4u8_Len(vec4u8_t v)
{
	return sqrtf(Vec4u8_LenSq(v));
}
vec4u8_t Vec4u8_Mod(vec4u8_t v0, vec4u8_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);

	return v0;
}
vec4u8_t Vec4u8_ModS(vec4u8_t v0, uint8_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);

	return v0;
}
vec4u8_t Vec4u8_Min(vec4u8_t v0, vec4u8_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];

	return v0;
}
vec4u8_t Vec4u8_Max(vec4u8_t v0, vec4u8_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];

	return v0;
}
vec4u8_t Vec4u8_MinS(vec4u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;

	return v0;
}
vec4u8_t Vec4u8_MaxS(vec4u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;

	return v0;
}
vec4u8_t Vec4u8_Clamp(vec4u8_t v, vec4u8_t min, vec4u8_t max)
{
	return Vec4u8_Max(Vec4u8_Min(v, max), min);
}
vec4u8_t Vec4u8_ClampS(vec4u8_t v, uint8_t min, uint8_t max)
{
	return Vec4u8_MaxS(Vec4u8_MinS(v, max), min);
}
vec4u8_t Vec4u8_CmpLT(vec4u8_t v0, vec4u8_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec4u8_t Vec4u8_CmpLE(vec4u8_t v0, vec4u8_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec4u8_t Vec4u8_CmpEQ(vec4u8_t v0, vec4u8_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec4u8_t Vec4u8_CmpGT(vec4u8_t v0, vec4u8_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec4u8_t Vec4u8_CmpGE(vec4u8_t v0, vec4u8_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec4u8_t Vec4u8_CmpNE(vec4u8_t v0, vec4u8_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec4u8_t Vec4u8_CmpLTS(vec4u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] < x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] < x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] < x ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] < x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec4u8_t Vec4u8_CmpLES(vec4u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec4u8_t Vec4u8_CmpEQS(vec4u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] == x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] == x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] == x ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] == x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec4u8_t Vec4u8_CmpGTS(vec4u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] > x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] > x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] > x ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] > x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec4u8_t Vec4u8_CmpGES(vec4u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec4u8_t Vec4u8_CmpNES(vec4u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] != x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] != x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] != x ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] != x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec4u8_t Vec4u8_Sign(vec4u8_t v)
{
	v.v[0] = v.v[0] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;
	v.v[1] = v.v[1] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;
	v.v[2] = v.v[2] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;
	v.v[3] = v.v[3] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;

	return v;
}
vec4u8_t Vec4u8_SignPosNeg(vec4u8_t v)
{
	v.v[0] = v.v[0] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;
	v.v[1] = v.v[1] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;
	v.v[2] = v.v[2] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;
	v.v[3] = v.v[3] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;

	return v;
}
vec4u8_t Vec4u8_Zero()
{
	return G_VEC4U8_T_ZERO;
}
vec4u8_t Vec4u8_One()
{
	return G_VEC4U8_T_ONE;
}
vec4u8_t Vec4u8_Cross(vec4u8_t v0, vec4u8_t v1, vec4u8_t v2)
{
	vec4u8_t v;
	mat4x4u8_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;

	for (i = 0; i < 4; i++)
		v.v[i] = Mat3x3u8_Det(Mat4x4u8_DeleteRowColumn(mat, 0, i));

	return v;
}
vec5u8_t Vec4u8_ToVec5u8(vec4u8_t v, uint8_t x0)
{
	vec5u8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;

	return outv;
}
vec6u8_t Vec4u8_ToVec6u8(vec4u8_t v, uint8_t x0, uint8_t x1)
{
	vec6u8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;
	outv.v[5] = x1;

	return outv;
}
vec7u8_t Vec4u8_ToVec7u8(vec4u8_t v, uint8_t x0, uint8_t x1, uint8_t x2)
{
	vec7u8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;
	outv.v[5] = x1;
	outv.v[6] = x2;

	return outv;
}
vec8u8_t Vec4u8_ToVec8u8(vec4u8_t v, uint8_t x0, uint8_t x1, uint8_t x2, uint8_t x3)
{
	vec8u8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;
	outv.v[5] = x1;
	outv.v[6] = x2;
	outv.v[7] = x3;

	return outv;
}
vec4i8_t Vec4i8_SetComponent(vec4i8_t v, int index, int8_t value)
{
	v.v[index] = value;

	return v;
}
vec4i8_t Vec4i8_Vec(int8_t x0, int8_t x1, int8_t x2, int8_t x3)
{
	vec4i8_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;

	return v;
}
vec4i8_t Vec4i8_Add(vec4i8_t v0, vec4i8_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];

	return v0;
}
vec4i8_t Vec4i8_Sub(vec4i8_t v0, vec4i8_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];

	return v0;
}
int8_t Vec4i8_GetComponent(vec4i8_t v, int index)
{
	return v.v[index];
}
vec4i8_t Vec4i8_Mul(vec4i8_t v0, vec4i8_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];

	return v0;
}
vec4i8_t Vec4i8_Div(vec4i8_t v0, vec4i8_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];

	return v0;
}
vec4i8_t Vec4i8_Scale(vec4i8_t v, int8_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;

	return v;
}
vec4i8_t Vec4i8_DivScale(vec4i8_t v, int8_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;

	return v;
}
vec4i8_t Vec4i8_MA(vec4i8_t v, vec4i8_t dir, int8_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;

	return v;
}
vec4i8_t Vec4i8_DA(vec4i8_t v, vec4i8_t dir, int8_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;

	return v;
}
int8_t Vec4i8_Dot(vec4i8_t v0, vec4i8_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3];
}
int8_t Vec4i8_LenSq(vec4i8_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3];
}
int8_t Vec4i8_Len(vec4i8_t v)
{
	return sqrtf(Vec4i8_LenSq(v));
}
vec4i8_t Vec4i8_Abs(vec4i8_t v)
{
	v.v[0] = (v.v[0] < 0 ? -v.v[0] : v.v[0]);
	v.v[1] = (v.v[1] < 0 ? -v.v[1] : v.v[1]);
	v.v[2] = (v.v[2] < 0 ? -v.v[2] : v.v[2]);
	v.v[3] = (v.v[3] < 0 ? -v.v[3] : v.v[3]);

	return v;
}
vec4i8_t Vec4i8_Mod(vec4i8_t v0, vec4i8_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);

	return v0;
}
vec4i8_t Vec4i8_ModS(vec4i8_t v0, int8_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);

	return v0;
}
vec4i8_t Vec4i8_Min(vec4i8_t v0, vec4i8_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];

	return v0;
}
vec4i8_t Vec4i8_Max(vec4i8_t v0, vec4i8_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];

	return v0;
}
vec4i8_t Vec4i8_MinS(vec4i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;

	return v0;
}
vec4i8_t Vec4i8_MaxS(vec4i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;

	return v0;
}
vec4i8_t Vec4i8_Clamp(vec4i8_t v, vec4i8_t min, vec4i8_t max)
{
	return Vec4i8_Max(Vec4i8_Min(v, max), min);
}
vec4i8_t Vec4i8_ClampS(vec4i8_t v, int8_t min, int8_t max)
{
	return Vec4i8_MaxS(Vec4i8_MinS(v, max), min);
}
vec4i8_t Vec4i8_Neg(vec4i8_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];
	v.v[3] = -v.v[3];

	return v;
}
vec4i8_t Vec4i8_CmpLT(vec4i8_t v0, vec4i8_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec4i8_t Vec4i8_CmpLE(vec4i8_t v0, vec4i8_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec4i8_t Vec4i8_CmpEQ(vec4i8_t v0, vec4i8_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec4i8_t Vec4i8_CmpGT(vec4i8_t v0, vec4i8_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec4i8_t Vec4i8_CmpGE(vec4i8_t v0, vec4i8_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec4i8_t Vec4i8_CmpNE(vec4i8_t v0, vec4i8_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec4i8_t Vec4i8_CmpLTS(vec4i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] < x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] < x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] < x ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] < x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec4i8_t Vec4i8_CmpLES(vec4i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec4i8_t Vec4i8_CmpEQS(vec4i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] == x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] == x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] == x ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] == x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec4i8_t Vec4i8_CmpGTS(vec4i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] > x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] > x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] > x ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] > x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec4i8_t Vec4i8_CmpGES(vec4i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec4i8_t Vec4i8_CmpNES(vec4i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] != x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] != x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] != x ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] != x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec4i8_t Vec4i8_Sign(vec4i8_t v)
{
	v.v[0] = v.v[0] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;
	v.v[1] = v.v[1] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;
	v.v[2] = v.v[2] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;
	v.v[3] = v.v[3] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;

	return v;
}
vec4i8_t Vec4i8_SignPosNeg(vec4i8_t v)
{
	v.v[0] = v.v[0] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;
	v.v[1] = v.v[1] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;
	v.v[2] = v.v[2] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;
	v.v[3] = v.v[3] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;

	return v;
}
vec4i8_t Vec4i8_Zero()
{
	return G_VEC4I8_T_ZERO;
}
vec4i8_t Vec4i8_One()
{
	return G_VEC4I8_T_ONE;
}
vec4i8_t Vec4i8_NegOne()
{
	return Vec4i8_Neg(G_VEC4I8_T_ONE);
}
vec4i8_t Vec4i8_Cross(vec4i8_t v0, vec4i8_t v1, vec4i8_t v2)
{
	vec4i8_t v;
	mat4x4i8_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;

	for (i = 0; i < 4; i++)
		v.v[i] = Mat3x3i8_Det(Mat4x4i8_DeleteRowColumn(mat, 0, i));

	return v;
}
vec5i8_t Vec4i8_ToVec5i8(vec4i8_t v, int8_t x0)
{
	vec5i8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;

	return outv;
}
vec6i8_t Vec4i8_ToVec6i8(vec4i8_t v, int8_t x0, int8_t x1)
{
	vec6i8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;
	outv.v[5] = x1;

	return outv;
}
vec7i8_t Vec4i8_ToVec7i8(vec4i8_t v, int8_t x0, int8_t x1, int8_t x2)
{
	vec7i8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;
	outv.v[5] = x1;
	outv.v[6] = x2;

	return outv;
}
vec8i8_t Vec4i8_ToVec8i8(vec4i8_t v, int8_t x0, int8_t x1, int8_t x2, int8_t x3)
{
	vec8i8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = x0;
	outv.v[5] = x1;
	outv.v[6] = x2;
	outv.v[7] = x3;

	return outv;
}
vec5f64_t Vec5f64_SetComponent(vec5f64_t v, int index, double value)
{
	v.v[index] = value;

	return v;
}
vec5f64_t Vec5f64_Vec(double x0, double x1, double x2, double x3, double x4)
{
	vec5f64_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;

	return v;
}
vec5f64_t Vec5f64_Add(vec5f64_t v0, vec5f64_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];

	return v0;
}
vec5f64_t Vec5f64_Sub(vec5f64_t v0, vec5f64_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];

	return v0;
}
double Vec5f64_GetComponent(vec5f64_t v, int index)
{
	return v.v[index];
}
vec5f64_t Vec5f64_Mul(vec5f64_t v0, vec5f64_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];

	return v0;
}
vec5f64_t Vec5f64_Div(vec5f64_t v0, vec5f64_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];

	return v0;
}
vec5f64_t Vec5f64_Scale(vec5f64_t v, double scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;

	return v;
}
vec5f64_t Vec5f64_DivScale(vec5f64_t v, double divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;

	return v;
}
vec5f64_t Vec5f64_MA(vec5f64_t v, vec5f64_t dir, double scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;

	return v;
}
vec5f64_t Vec5f64_DA(vec5f64_t v, vec5f64_t dir, double divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;

	return v;
}
double Vec5f64_Dot(vec5f64_t v0, vec5f64_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4];
}
double Vec5f64_LenSq(vec5f64_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4];
}
double Vec5f64_Len(vec5f64_t v)
{
	return sqrt(Vec5f64_LenSq(v));
}
vec5f64_t Vec5f64_Normalise(vec5f64_t v)
{
	double lensq = Vec5f64_LenSq(v);

	if (lensq == G_F64_ZERO)
		return v;
	else
		return Vec5f64_Scale(v, G_F64_ONE / sqrt(lensq));
}
vec5f64_t Vec5f64_Abs(vec5f64_t v)
{
	v.v[0] = fabs(v.v[0]);
	v.v[1] = fabs(v.v[1]);
	v.v[2] = fabs(v.v[2]);
	v.v[3] = fabs(v.v[3]);
	v.v[4] = fabs(v.v[4]);

	return v;
}
vec5f64_t Vec5f64_Floor(vec5f64_t v)
{
	v.v[0] = floor(v.v[0]);
	v.v[1] = floor(v.v[1]);
	v.v[2] = floor(v.v[2]);
	v.v[3] = floor(v.v[3]);
	v.v[4] = floor(v.v[4]);

	return v;
}
vec5f64_t Vec5f64_Ceil(vec5f64_t v)
{
	v.v[0] = ceil(v.v[0]);
	v.v[1] = ceil(v.v[1]);
	v.v[2] = ceil(v.v[2]);
	v.v[3] = ceil(v.v[3]);
	v.v[4] = ceil(v.v[4]);

	return v;
}
vec5f64_t Vec5f64_Fract(vec5f64_t v)
{
	return Vec5f64_Sub(v, Vec5f64_Floor(v));
}
vec5f64_t Vec5f64_Mod(vec5f64_t v0, vec5f64_t v1)
{
	v0.v[0] = fmod(v0.v[0], v1.v[0]);
	v0.v[1] = fmod(v0.v[1], v1.v[1]);
	v0.v[2] = fmod(v0.v[2], v1.v[2]);
	v0.v[3] = fmod(v0.v[3], v1.v[3]);
	v0.v[4] = fmod(v0.v[4], v1.v[4]);

	return v0;
}
vec5f64_t Vec5f64_ModS(vec5f64_t v0, double x)
{
	v0.v[0] = fmod(v0.v[0], x);
	v0.v[1] = fmod(v0.v[1], x);
	v0.v[2] = fmod(v0.v[2], x);
	v0.v[3] = fmod(v0.v[3], x);
	v0.v[4] = fmod(v0.v[4], x);

	return v0;
}
vec5f64_t Vec5f64_Min(vec5f64_t v0, vec5f64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];

	return v0;
}
vec5f64_t Vec5f64_Max(vec5f64_t v0, vec5f64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];

	return v0;
}
vec5f64_t Vec5f64_MinS(vec5f64_t v0, double x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;

	return v0;
}
vec5f64_t Vec5f64_MaxS(vec5f64_t v0, double x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;

	return v0;
}
vec5f64_t Vec5f64_Clamp(vec5f64_t v, vec5f64_t min, vec5f64_t max)
{
	return Vec5f64_Max(Vec5f64_Min(v, max), min);
}
vec5f64_t Vec5f64_ClampS(vec5f64_t v, double min, double max)
{
	return Vec5f64_MaxS(Vec5f64_MinS(v, max), min);
}
vec5f64_t Vec5f64_Neg(vec5f64_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];
	v.v[3] = -v.v[3];
	v.v[4] = -v.v[4];

	return v;
}
vec5f64_t Vec5f64_Reciprocal(vec5f64_t v)
{
	v.v[0] = G_F64_ONE / v.v[0];
	v.v[1] = G_F64_ONE / v.v[1];
	v.v[2] = G_F64_ONE / v.v[2];
	v.v[3] = G_F64_ONE / v.v[3];
	v.v[4] = G_F64_ONE / v.v[4];

	return v;
}
vec5f64_t Vec5f64_Truncate(vec5f64_t v)
{
	v.v[0] = v.v[0] < G_F64_ZERO ? ceil(v.v[0]) : floor(v.v[0]);
	v.v[1] = v.v[1] < G_F64_ZERO ? ceil(v.v[1]) : floor(v.v[1]);
	v.v[2] = v.v[2] < G_F64_ZERO ? ceil(v.v[2]) : floor(v.v[2]);
	v.v[3] = v.v[3] < G_F64_ZERO ? ceil(v.v[3]) : floor(v.v[3]);
	v.v[4] = v.v[4] < G_F64_ZERO ? ceil(v.v[4]) : floor(v.v[4]);

	return v;
}
vec5f64_t Vec5f64_TruncateAway(vec5f64_t v)
{
	v.v[0] = v.v[0] < G_F64_ZERO ? floor(v.v[0]) : ceil(v.v[0]);
	v.v[1] = v.v[1] < G_F64_ZERO ? floor(v.v[1]) : ceil(v.v[1]);
	v.v[2] = v.v[2] < G_F64_ZERO ? floor(v.v[2]) : ceil(v.v[2]);
	v.v[3] = v.v[3] < G_F64_ZERO ? floor(v.v[3]) : ceil(v.v[3]);
	v.v[4] = v.v[4] < G_F64_ZERO ? floor(v.v[4]) : ceil(v.v[4]);

	return v;
}
vec5f64_t Vec5f64_CmpLT(vec5f64_t v0, vec5f64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec5f64_t Vec5f64_CmpLE(vec5f64_t v0, vec5f64_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec5f64_t Vec5f64_CmpEQ(vec5f64_t v0, vec5f64_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec5f64_t Vec5f64_CmpGT(vec5f64_t v0, vec5f64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec5f64_t Vec5f64_CmpGE(vec5f64_t v0, vec5f64_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec5f64_t Vec5f64_CmpNE(vec5f64_t v0, vec5f64_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec5f64_t Vec5f64_CmpLTS(vec5f64_t v0, double x)
{
	v0.v[0] = v0.v[0] < x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] < x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] < x ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] < x ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] < x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec5f64_t Vec5f64_CmpLES(vec5f64_t v0, double x)
{
	v0.v[0] = v0.v[0] <= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec5f64_t Vec5f64_CmpEQS(vec5f64_t v0, double x)
{
	v0.v[0] = v0.v[0] == x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] == x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] == x ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] == x ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] == x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec5f64_t Vec5f64_CmpGTS(vec5f64_t v0, double x)
{
	v0.v[0] = v0.v[0] > x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] > x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] > x ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] > x ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] > x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec5f64_t Vec5f64_CmpGES(vec5f64_t v0, double x)
{
	v0.v[0] = v0.v[0] >= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec5f64_t Vec5f64_CmpNES(vec5f64_t v0, double x)
{
	v0.v[0] = v0.v[0] != x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] != x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] != x ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] != x ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] != x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec5f64_t Vec5f64_Sign(vec5f64_t v)
{
	v.v[0] = v.v[0] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;
	v.v[1] = v.v[1] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;
	v.v[2] = v.v[2] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;
	v.v[3] = v.v[3] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;
	v.v[4] = v.v[4] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;

	return v;
}
vec5f64_t Vec5f64_SignPosNeg(vec5f64_t v)
{
	v.v[0] = v.v[0] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;
	v.v[1] = v.v[1] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;
	v.v[2] = v.v[2] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;
	v.v[3] = v.v[3] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;
	v.v[4] = v.v[4] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;

	return v;
}
vec5f64_t Vec5f64_Zero()
{
	return G_VEC5F64_T_ZERO;
}
vec5f64_t Vec5f64_One()
{
	return G_VEC5F64_T_ONE;
}
vec5f64_t Vec5f64_NegOne()
{
	return Vec5f64_Neg(G_VEC5F64_T_ONE);
}
vec5f64_t Vec5f64_Cross(vec5f64_t v0, vec5f64_t v1, vec5f64_t v2, vec5f64_t v3)
{
	vec5f64_t v;
	mat5x5f64_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;

	for (i = 0; i < 5; i++)
		v.v[i] = Mat4x4f64_Det(Mat5x5f64_DeleteRowColumn(mat, 0, i));

	return v;
}
vec5f64_t Vec5f64_Lerp(vec5f64_t v0, vec5f64_t v1, vec5f64_t vt)
{
	vec5f64_t v;

	v.v[0] = (G_F64_ONE - vt.v[0]) * v0.v[0] + v1.v[0] * vt.v[0];
	v.v[1] = (G_F64_ONE - vt.v[1]) * v0.v[1] + v1.v[1] * vt.v[1];
	v.v[2] = (G_F64_ONE - vt.v[2]) * v0.v[2] + v1.v[2] * vt.v[2];
	v.v[3] = (G_F64_ONE - vt.v[3]) * v0.v[3] + v1.v[3] * vt.v[3];
	v.v[4] = (G_F64_ONE - vt.v[4]) * v0.v[4] + v1.v[4] * vt.v[4];

	return v;
}
vec5f64_t Vec5f64_LerpS(vec5f64_t v0, vec5f64_t v1, double t)
{
	vec5f64_t v;

	v.v[0] = (G_F64_ONE - t) * v0.v[0] + v1.v[0] * t;
	v.v[1] = (G_F64_ONE - t) * v0.v[1] + v1.v[1] * t;
	v.v[2] = (G_F64_ONE - t) * v0.v[2] + v1.v[2] * t;
	v.v[3] = (G_F64_ONE - t) * v0.v[3] + v1.v[3] * t;
	v.v[4] = (G_F64_ONE - t) * v0.v[4] + v1.v[4] * t;

	return v;
}
vec6f64_t Vec5f64_ToVec6f64(vec5f64_t v, double x0)
{
	vec6f64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = x0;

	return outv;
}
vec7f64_t Vec5f64_ToVec7f64(vec5f64_t v, double x0, double x1)
{
	vec7f64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = x0;
	outv.v[6] = x1;

	return outv;
}
vec8f64_t Vec5f64_ToVec8f64(vec5f64_t v, double x0, double x1, double x2)
{
	vec8f64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = x0;
	outv.v[6] = x1;
	outv.v[7] = x2;

	return outv;
}
vec5f32_t Vec5f32_SetComponent(vec5f32_t v, int index, float value)
{
	v.v[index] = value;

	return v;
}
vec5f32_t Vec5f32_Vec(float x0, float x1, float x2, float x3, float x4)
{
	vec5f32_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;

	return v;
}
vec5f32_t Vec5f32_Add(vec5f32_t v0, vec5f32_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];

	return v0;
}
vec5f32_t Vec5f32_Sub(vec5f32_t v0, vec5f32_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];

	return v0;
}
float Vec5f32_GetComponent(vec5f32_t v, int index)
{
	return v.v[index];
}
vec5f32_t Vec5f32_Mul(vec5f32_t v0, vec5f32_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];

	return v0;
}
vec5f32_t Vec5f32_Div(vec5f32_t v0, vec5f32_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];

	return v0;
}
vec5f32_t Vec5f32_Scale(vec5f32_t v, float scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;

	return v;
}
vec5f32_t Vec5f32_DivScale(vec5f32_t v, float divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;

	return v;
}
vec5f32_t Vec5f32_MA(vec5f32_t v, vec5f32_t dir, float scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;

	return v;
}
vec5f32_t Vec5f32_DA(vec5f32_t v, vec5f32_t dir, float divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;

	return v;
}
float Vec5f32_Dot(vec5f32_t v0, vec5f32_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4];
}
float Vec5f32_LenSq(vec5f32_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4];
}
float Vec5f32_Len(vec5f32_t v)
{
	return sqrtf(Vec5f32_LenSq(v));
}
vec5f32_t Vec5f32_Normalise(vec5f32_t v)
{
	float lensq = Vec5f32_LenSq(v);

	if (lensq == G_F32_ZERO)
		return v;
	else
		return Vec5f32_Scale(v, G_F32_ONE / sqrtf(lensq));
}
vec5f32_t Vec5f32_Abs(vec5f32_t v)
{
	v.v[0] = fabsf(v.v[0]);
	v.v[1] = fabsf(v.v[1]);
	v.v[2] = fabsf(v.v[2]);
	v.v[3] = fabsf(v.v[3]);
	v.v[4] = fabsf(v.v[4]);

	return v;
}
vec5f32_t Vec5f32_Floor(vec5f32_t v)
{
	v.v[0] = floorf(v.v[0]);
	v.v[1] = floorf(v.v[1]);
	v.v[2] = floorf(v.v[2]);
	v.v[3] = floorf(v.v[3]);
	v.v[4] = floorf(v.v[4]);

	return v;
}
vec5f32_t Vec5f32_Ceil(vec5f32_t v)
{
	v.v[0] = ceilf(v.v[0]);
	v.v[1] = ceilf(v.v[1]);
	v.v[2] = ceilf(v.v[2]);
	v.v[3] = ceilf(v.v[3]);
	v.v[4] = ceilf(v.v[4]);

	return v;
}
vec5f32_t Vec5f32_Fract(vec5f32_t v)
{
	return Vec5f32_Sub(v, Vec5f32_Floor(v));
}
vec5f32_t Vec5f32_Mod(vec5f32_t v0, vec5f32_t v1)
{
	v0.v[0] = fmodf(v0.v[0], v1.v[0]);
	v0.v[1] = fmodf(v0.v[1], v1.v[1]);
	v0.v[2] = fmodf(v0.v[2], v1.v[2]);
	v0.v[3] = fmodf(v0.v[3], v1.v[3]);
	v0.v[4] = fmodf(v0.v[4], v1.v[4]);

	return v0;
}
vec5f32_t Vec5f32_ModS(vec5f32_t v0, float x)
{
	v0.v[0] = fmodf(v0.v[0], x);
	v0.v[1] = fmodf(v0.v[1], x);
	v0.v[2] = fmodf(v0.v[2], x);
	v0.v[3] = fmodf(v0.v[3], x);
	v0.v[4] = fmodf(v0.v[4], x);

	return v0;
}
vec5f32_t Vec5f32_Min(vec5f32_t v0, vec5f32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];

	return v0;
}
vec5f32_t Vec5f32_Max(vec5f32_t v0, vec5f32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];

	return v0;
}
vec5f32_t Vec5f32_MinS(vec5f32_t v0, float x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;

	return v0;
}
vec5f32_t Vec5f32_MaxS(vec5f32_t v0, float x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;

	return v0;
}
vec5f32_t Vec5f32_Clamp(vec5f32_t v, vec5f32_t min, vec5f32_t max)
{
	return Vec5f32_Max(Vec5f32_Min(v, max), min);
}
vec5f32_t Vec5f32_ClampS(vec5f32_t v, float min, float max)
{
	return Vec5f32_MaxS(Vec5f32_MinS(v, max), min);
}
vec5f32_t Vec5f32_Neg(vec5f32_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];
	v.v[3] = -v.v[3];
	v.v[4] = -v.v[4];

	return v;
}
vec5f32_t Vec5f32_Reciprocal(vec5f32_t v)
{
	v.v[0] = G_F32_ONE / v.v[0];
	v.v[1] = G_F32_ONE / v.v[1];
	v.v[2] = G_F32_ONE / v.v[2];
	v.v[3] = G_F32_ONE / v.v[3];
	v.v[4] = G_F32_ONE / v.v[4];

	return v;
}
vec5f32_t Vec5f32_Truncate(vec5f32_t v)
{
	v.v[0] = v.v[0] < G_F32_ZERO ? ceilf(v.v[0]) : floorf(v.v[0]);
	v.v[1] = v.v[1] < G_F32_ZERO ? ceilf(v.v[1]) : floorf(v.v[1]);
	v.v[2] = v.v[2] < G_F32_ZERO ? ceilf(v.v[2]) : floorf(v.v[2]);
	v.v[3] = v.v[3] < G_F32_ZERO ? ceilf(v.v[3]) : floorf(v.v[3]);
	v.v[4] = v.v[4] < G_F32_ZERO ? ceilf(v.v[4]) : floorf(v.v[4]);

	return v;
}
vec5f32_t Vec5f32_TruncateAway(vec5f32_t v)
{
	v.v[0] = v.v[0] < G_F32_ZERO ? floorf(v.v[0]) : ceilf(v.v[0]);
	v.v[1] = v.v[1] < G_F32_ZERO ? floorf(v.v[1]) : ceilf(v.v[1]);
	v.v[2] = v.v[2] < G_F32_ZERO ? floorf(v.v[2]) : ceilf(v.v[2]);
	v.v[3] = v.v[3] < G_F32_ZERO ? floorf(v.v[3]) : ceilf(v.v[3]);
	v.v[4] = v.v[4] < G_F32_ZERO ? floorf(v.v[4]) : ceilf(v.v[4]);

	return v;
}
vec5f32_t Vec5f32_CmpLT(vec5f32_t v0, vec5f32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec5f32_t Vec5f32_CmpLE(vec5f32_t v0, vec5f32_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec5f32_t Vec5f32_CmpEQ(vec5f32_t v0, vec5f32_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec5f32_t Vec5f32_CmpGT(vec5f32_t v0, vec5f32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec5f32_t Vec5f32_CmpGE(vec5f32_t v0, vec5f32_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec5f32_t Vec5f32_CmpNE(vec5f32_t v0, vec5f32_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec5f32_t Vec5f32_CmpLTS(vec5f32_t v0, float x)
{
	v0.v[0] = v0.v[0] < x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] < x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] < x ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] < x ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] < x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec5f32_t Vec5f32_CmpLES(vec5f32_t v0, float x)
{
	v0.v[0] = v0.v[0] <= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec5f32_t Vec5f32_CmpEQS(vec5f32_t v0, float x)
{
	v0.v[0] = v0.v[0] == x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] == x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] == x ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] == x ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] == x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec5f32_t Vec5f32_CmpGTS(vec5f32_t v0, float x)
{
	v0.v[0] = v0.v[0] > x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] > x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] > x ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] > x ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] > x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec5f32_t Vec5f32_CmpGES(vec5f32_t v0, float x)
{
	v0.v[0] = v0.v[0] >= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec5f32_t Vec5f32_CmpNES(vec5f32_t v0, float x)
{
	v0.v[0] = v0.v[0] != x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] != x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] != x ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] != x ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] != x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec5f32_t Vec5f32_Sign(vec5f32_t v)
{
	v.v[0] = v.v[0] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;
	v.v[1] = v.v[1] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;
	v.v[2] = v.v[2] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;
	v.v[3] = v.v[3] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;
	v.v[4] = v.v[4] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;

	return v;
}
vec5f32_t Vec5f32_SignPosNeg(vec5f32_t v)
{
	v.v[0] = v.v[0] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;
	v.v[1] = v.v[1] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;
	v.v[2] = v.v[2] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;
	v.v[3] = v.v[3] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;
	v.v[4] = v.v[4] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;

	return v;
}
vec5f32_t Vec5f32_Zero()
{
	return G_VEC5F32_T_ZERO;
}
vec5f32_t Vec5f32_One()
{
	return G_VEC5F32_T_ONE;
}
vec5f32_t Vec5f32_NegOne()
{
	return Vec5f32_Neg(G_VEC5F32_T_ONE);
}
vec5f32_t Vec5f32_Cross(vec5f32_t v0, vec5f32_t v1, vec5f32_t v2, vec5f32_t v3)
{
	vec5f32_t v;
	mat5x5f32_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;

	for (i = 0; i < 5; i++)
		v.v[i] = Mat4x4f32_Det(Mat5x5f32_DeleteRowColumn(mat, 0, i));

	return v;
}
vec5f32_t Vec5f32_Lerp(vec5f32_t v0, vec5f32_t v1, vec5f32_t vt)
{
	vec5f32_t v;

	v.v[0] = (G_F32_ONE - vt.v[0]) * v0.v[0] + v1.v[0] * vt.v[0];
	v.v[1] = (G_F32_ONE - vt.v[1]) * v0.v[1] + v1.v[1] * vt.v[1];
	v.v[2] = (G_F32_ONE - vt.v[2]) * v0.v[2] + v1.v[2] * vt.v[2];
	v.v[3] = (G_F32_ONE - vt.v[3]) * v0.v[3] + v1.v[3] * vt.v[3];
	v.v[4] = (G_F32_ONE - vt.v[4]) * v0.v[4] + v1.v[4] * vt.v[4];

	return v;
}
vec5f32_t Vec5f32_LerpS(vec5f32_t v0, vec5f32_t v1, float t)
{
	vec5f32_t v;

	v.v[0] = (G_F32_ONE - t) * v0.v[0] + v1.v[0] * t;
	v.v[1] = (G_F32_ONE - t) * v0.v[1] + v1.v[1] * t;
	v.v[2] = (G_F32_ONE - t) * v0.v[2] + v1.v[2] * t;
	v.v[3] = (G_F32_ONE - t) * v0.v[3] + v1.v[3] * t;
	v.v[4] = (G_F32_ONE - t) * v0.v[4] + v1.v[4] * t;

	return v;
}
vec6f32_t Vec5f32_ToVec6f32(vec5f32_t v, float x0)
{
	vec6f32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = x0;

	return outv;
}
vec7f32_t Vec5f32_ToVec7f32(vec5f32_t v, float x0, float x1)
{
	vec7f32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = x0;
	outv.v[6] = x1;

	return outv;
}
vec8f32_t Vec5f32_ToVec8f32(vec5f32_t v, float x0, float x1, float x2)
{
	vec8f32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = x0;
	outv.v[6] = x1;
	outv.v[7] = x2;

	return outv;
}
vec5u64_t Vec5u64_SetComponent(vec5u64_t v, int index, uint64_t value)
{
	v.v[index] = value;

	return v;
}
vec5u64_t Vec5u64_Vec(uint64_t x0, uint64_t x1, uint64_t x2, uint64_t x3, uint64_t x4)
{
	vec5u64_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;

	return v;
}
vec5u64_t Vec5u64_Add(vec5u64_t v0, vec5u64_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];

	return v0;
}
vec5u64_t Vec5u64_Sub(vec5u64_t v0, vec5u64_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];

	return v0;
}
uint64_t Vec5u64_GetComponent(vec5u64_t v, int index)
{
	return v.v[index];
}
vec5u64_t Vec5u64_Mul(vec5u64_t v0, vec5u64_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];

	return v0;
}
vec5u64_t Vec5u64_Div(vec5u64_t v0, vec5u64_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];

	return v0;
}
vec5u64_t Vec5u64_Scale(vec5u64_t v, uint64_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;

	return v;
}
vec5u64_t Vec5u64_DivScale(vec5u64_t v, uint64_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;

	return v;
}
vec5u64_t Vec5u64_MA(vec5u64_t v, vec5u64_t dir, uint64_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;

	return v;
}
vec5u64_t Vec5u64_DA(vec5u64_t v, vec5u64_t dir, uint64_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;

	return v;
}
uint64_t Vec5u64_Dot(vec5u64_t v0, vec5u64_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4];
}
uint64_t Vec5u64_LenSq(vec5u64_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4];
}
uint64_t Vec5u64_Len(vec5u64_t v)
{
	return sqrt(Vec5u64_LenSq(v));
}
vec5u64_t Vec5u64_Mod(vec5u64_t v0, vec5u64_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);
	v0.v[4] = (v0.v[4] % v1.v[4]);

	return v0;
}
vec5u64_t Vec5u64_ModS(vec5u64_t v0, uint64_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);
	v0.v[4] = (v0.v[4] % x);

	return v0;
}
vec5u64_t Vec5u64_Min(vec5u64_t v0, vec5u64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];

	return v0;
}
vec5u64_t Vec5u64_Max(vec5u64_t v0, vec5u64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];

	return v0;
}
vec5u64_t Vec5u64_MinS(vec5u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;

	return v0;
}
vec5u64_t Vec5u64_MaxS(vec5u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;

	return v0;
}
vec5u64_t Vec5u64_Clamp(vec5u64_t v, vec5u64_t min, vec5u64_t max)
{
	return Vec5u64_Max(Vec5u64_Min(v, max), min);
}
vec5u64_t Vec5u64_ClampS(vec5u64_t v, uint64_t min, uint64_t max)
{
	return Vec5u64_MaxS(Vec5u64_MinS(v, max), min);
}
vec5u64_t Vec5u64_CmpLT(vec5u64_t v0, vec5u64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec5u64_t Vec5u64_CmpLE(vec5u64_t v0, vec5u64_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec5u64_t Vec5u64_CmpEQ(vec5u64_t v0, vec5u64_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec5u64_t Vec5u64_CmpGT(vec5u64_t v0, vec5u64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec5u64_t Vec5u64_CmpGE(vec5u64_t v0, vec5u64_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec5u64_t Vec5u64_CmpNE(vec5u64_t v0, vec5u64_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec5u64_t Vec5u64_CmpLTS(vec5u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] < x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] < x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] < x ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] < x ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] < x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec5u64_t Vec5u64_CmpLES(vec5u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec5u64_t Vec5u64_CmpEQS(vec5u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] == x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] == x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] == x ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] == x ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] == x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec5u64_t Vec5u64_CmpGTS(vec5u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] > x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] > x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] > x ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] > x ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] > x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec5u64_t Vec5u64_CmpGES(vec5u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec5u64_t Vec5u64_CmpNES(vec5u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] != x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] != x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] != x ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] != x ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] != x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec5u64_t Vec5u64_Sign(vec5u64_t v)
{
	v.v[0] = v.v[0] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;
	v.v[1] = v.v[1] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;
	v.v[2] = v.v[2] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;
	v.v[3] = v.v[3] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;
	v.v[4] = v.v[4] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;

	return v;
}
vec5u64_t Vec5u64_SignPosNeg(vec5u64_t v)
{
	v.v[0] = v.v[0] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;
	v.v[1] = v.v[1] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;
	v.v[2] = v.v[2] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;
	v.v[3] = v.v[3] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;
	v.v[4] = v.v[4] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;

	return v;
}
vec5u64_t Vec5u64_Zero()
{
	return G_VEC5U64_T_ZERO;
}
vec5u64_t Vec5u64_One()
{
	return G_VEC5U64_T_ONE;
}
vec5u64_t Vec5u64_Cross(vec5u64_t v0, vec5u64_t v1, vec5u64_t v2, vec5u64_t v3)
{
	vec5u64_t v;
	mat5x5u64_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;

	for (i = 0; i < 5; i++)
		v.v[i] = Mat4x4u64_Det(Mat5x5u64_DeleteRowColumn(mat, 0, i));

	return v;
}
vec6u64_t Vec5u64_ToVec6u64(vec5u64_t v, uint64_t x0)
{
	vec6u64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = x0;

	return outv;
}
vec7u64_t Vec5u64_ToVec7u64(vec5u64_t v, uint64_t x0, uint64_t x1)
{
	vec7u64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = x0;
	outv.v[6] = x1;

	return outv;
}
vec8u64_t Vec5u64_ToVec8u64(vec5u64_t v, uint64_t x0, uint64_t x1, uint64_t x2)
{
	vec8u64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = x0;
	outv.v[6] = x1;
	outv.v[7] = x2;

	return outv;
}
vec5i64_t Vec5i64_SetComponent(vec5i64_t v, int index, int64_t value)
{
	v.v[index] = value;

	return v;
}
vec5i64_t Vec5i64_Vec(int64_t x0, int64_t x1, int64_t x2, int64_t x3, int64_t x4)
{
	vec5i64_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;

	return v;
}
vec5i64_t Vec5i64_Add(vec5i64_t v0, vec5i64_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];

	return v0;
}
vec5i64_t Vec5i64_Sub(vec5i64_t v0, vec5i64_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];

	return v0;
}
int64_t Vec5i64_GetComponent(vec5i64_t v, int index)
{
	return v.v[index];
}
vec5i64_t Vec5i64_Mul(vec5i64_t v0, vec5i64_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];

	return v0;
}
vec5i64_t Vec5i64_Div(vec5i64_t v0, vec5i64_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];

	return v0;
}
vec5i64_t Vec5i64_Scale(vec5i64_t v, int64_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;

	return v;
}
vec5i64_t Vec5i64_DivScale(vec5i64_t v, int64_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;

	return v;
}
vec5i64_t Vec5i64_MA(vec5i64_t v, vec5i64_t dir, int64_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;

	return v;
}
vec5i64_t Vec5i64_DA(vec5i64_t v, vec5i64_t dir, int64_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;

	return v;
}
int64_t Vec5i64_Dot(vec5i64_t v0, vec5i64_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4];
}
int64_t Vec5i64_LenSq(vec5i64_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4];
}
int64_t Vec5i64_Len(vec5i64_t v)
{
	return sqrt(Vec5i64_LenSq(v));
}
vec5i64_t Vec5i64_Abs(vec5i64_t v)
{
	v.v[0] = (v.v[0] < 0 ? -v.v[0] : v.v[0]);
	v.v[1] = (v.v[1] < 0 ? -v.v[1] : v.v[1]);
	v.v[2] = (v.v[2] < 0 ? -v.v[2] : v.v[2]);
	v.v[3] = (v.v[3] < 0 ? -v.v[3] : v.v[3]);
	v.v[4] = (v.v[4] < 0 ? -v.v[4] : v.v[4]);

	return v;
}
vec5i64_t Vec5i64_Mod(vec5i64_t v0, vec5i64_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);
	v0.v[4] = (v0.v[4] % v1.v[4]);

	return v0;
}
vec5i64_t Vec5i64_ModS(vec5i64_t v0, int64_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);
	v0.v[4] = (v0.v[4] % x);

	return v0;
}
vec5i64_t Vec5i64_Min(vec5i64_t v0, vec5i64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];

	return v0;
}
vec5i64_t Vec5i64_Max(vec5i64_t v0, vec5i64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];

	return v0;
}
vec5i64_t Vec5i64_MinS(vec5i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;

	return v0;
}
vec5i64_t Vec5i64_MaxS(vec5i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;

	return v0;
}
vec5i64_t Vec5i64_Clamp(vec5i64_t v, vec5i64_t min, vec5i64_t max)
{
	return Vec5i64_Max(Vec5i64_Min(v, max), min);
}
vec5i64_t Vec5i64_ClampS(vec5i64_t v, int64_t min, int64_t max)
{
	return Vec5i64_MaxS(Vec5i64_MinS(v, max), min);
}
vec5i64_t Vec5i64_Neg(vec5i64_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];
	v.v[3] = -v.v[3];
	v.v[4] = -v.v[4];

	return v;
}
vec5i64_t Vec5i64_CmpLT(vec5i64_t v0, vec5i64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec5i64_t Vec5i64_CmpLE(vec5i64_t v0, vec5i64_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec5i64_t Vec5i64_CmpEQ(vec5i64_t v0, vec5i64_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec5i64_t Vec5i64_CmpGT(vec5i64_t v0, vec5i64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec5i64_t Vec5i64_CmpGE(vec5i64_t v0, vec5i64_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec5i64_t Vec5i64_CmpNE(vec5i64_t v0, vec5i64_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec5i64_t Vec5i64_CmpLTS(vec5i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] < x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] < x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] < x ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] < x ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] < x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec5i64_t Vec5i64_CmpLES(vec5i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec5i64_t Vec5i64_CmpEQS(vec5i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] == x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] == x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] == x ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] == x ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] == x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec5i64_t Vec5i64_CmpGTS(vec5i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] > x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] > x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] > x ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] > x ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] > x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec5i64_t Vec5i64_CmpGES(vec5i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec5i64_t Vec5i64_CmpNES(vec5i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] != x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] != x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] != x ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] != x ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] != x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec5i64_t Vec5i64_Sign(vec5i64_t v)
{
	v.v[0] = v.v[0] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;
	v.v[1] = v.v[1] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;
	v.v[2] = v.v[2] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;
	v.v[3] = v.v[3] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;
	v.v[4] = v.v[4] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;

	return v;
}
vec5i64_t Vec5i64_SignPosNeg(vec5i64_t v)
{
	v.v[0] = v.v[0] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;
	v.v[1] = v.v[1] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;
	v.v[2] = v.v[2] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;
	v.v[3] = v.v[3] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;
	v.v[4] = v.v[4] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;

	return v;
}
vec5i64_t Vec5i64_Zero()
{
	return G_VEC5I64_T_ZERO;
}
vec5i64_t Vec5i64_One()
{
	return G_VEC5I64_T_ONE;
}
vec5i64_t Vec5i64_NegOne()
{
	return Vec5i64_Neg(G_VEC5I64_T_ONE);
}
vec5i64_t Vec5i64_Cross(vec5i64_t v0, vec5i64_t v1, vec5i64_t v2, vec5i64_t v3)
{
	vec5i64_t v;
	mat5x5i64_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;

	for (i = 0; i < 5; i++)
		v.v[i] = Mat4x4i64_Det(Mat5x5i64_DeleteRowColumn(mat, 0, i));

	return v;
}
vec6i64_t Vec5i64_ToVec6i64(vec5i64_t v, int64_t x0)
{
	vec6i64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = x0;

	return outv;
}
vec7i64_t Vec5i64_ToVec7i64(vec5i64_t v, int64_t x0, int64_t x1)
{
	vec7i64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = x0;
	outv.v[6] = x1;

	return outv;
}
vec8i64_t Vec5i64_ToVec8i64(vec5i64_t v, int64_t x0, int64_t x1, int64_t x2)
{
	vec8i64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = x0;
	outv.v[6] = x1;
	outv.v[7] = x2;

	return outv;
}
vec5u32_t Vec5u32_SetComponent(vec5u32_t v, int index, uint32_t value)
{
	v.v[index] = value;

	return v;
}
vec5u32_t Vec5u32_Vec(uint32_t x0, uint32_t x1, uint32_t x2, uint32_t x3, uint32_t x4)
{
	vec5u32_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;

	return v;
}
vec5u32_t Vec5u32_Add(vec5u32_t v0, vec5u32_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];

	return v0;
}
vec5u32_t Vec5u32_Sub(vec5u32_t v0, vec5u32_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];

	return v0;
}
uint32_t Vec5u32_GetComponent(vec5u32_t v, int index)
{
	return v.v[index];
}
vec5u32_t Vec5u32_Mul(vec5u32_t v0, vec5u32_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];

	return v0;
}
vec5u32_t Vec5u32_Div(vec5u32_t v0, vec5u32_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];

	return v0;
}
vec5u32_t Vec5u32_Scale(vec5u32_t v, uint32_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;

	return v;
}
vec5u32_t Vec5u32_DivScale(vec5u32_t v, uint32_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;

	return v;
}
vec5u32_t Vec5u32_MA(vec5u32_t v, vec5u32_t dir, uint32_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;

	return v;
}
vec5u32_t Vec5u32_DA(vec5u32_t v, vec5u32_t dir, uint32_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;

	return v;
}
uint32_t Vec5u32_Dot(vec5u32_t v0, vec5u32_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4];
}
uint32_t Vec5u32_LenSq(vec5u32_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4];
}
uint32_t Vec5u32_Len(vec5u32_t v)
{
	return sqrtf(Vec5u32_LenSq(v));
}
vec5u32_t Vec5u32_Mod(vec5u32_t v0, vec5u32_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);
	v0.v[4] = (v0.v[4] % v1.v[4]);

	return v0;
}
vec5u32_t Vec5u32_ModS(vec5u32_t v0, uint32_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);
	v0.v[4] = (v0.v[4] % x);

	return v0;
}
vec5u32_t Vec5u32_Min(vec5u32_t v0, vec5u32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];

	return v0;
}
vec5u32_t Vec5u32_Max(vec5u32_t v0, vec5u32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];

	return v0;
}
vec5u32_t Vec5u32_MinS(vec5u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;

	return v0;
}
vec5u32_t Vec5u32_MaxS(vec5u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;

	return v0;
}
vec5u32_t Vec5u32_Clamp(vec5u32_t v, vec5u32_t min, vec5u32_t max)
{
	return Vec5u32_Max(Vec5u32_Min(v, max), min);
}
vec5u32_t Vec5u32_ClampS(vec5u32_t v, uint32_t min, uint32_t max)
{
	return Vec5u32_MaxS(Vec5u32_MinS(v, max), min);
}
vec5u32_t Vec5u32_CmpLT(vec5u32_t v0, vec5u32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec5u32_t Vec5u32_CmpLE(vec5u32_t v0, vec5u32_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec5u32_t Vec5u32_CmpEQ(vec5u32_t v0, vec5u32_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec5u32_t Vec5u32_CmpGT(vec5u32_t v0, vec5u32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec5u32_t Vec5u32_CmpGE(vec5u32_t v0, vec5u32_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec5u32_t Vec5u32_CmpNE(vec5u32_t v0, vec5u32_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec5u32_t Vec5u32_CmpLTS(vec5u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] < x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] < x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] < x ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] < x ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] < x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec5u32_t Vec5u32_CmpLES(vec5u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec5u32_t Vec5u32_CmpEQS(vec5u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] == x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] == x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] == x ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] == x ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] == x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec5u32_t Vec5u32_CmpGTS(vec5u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] > x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] > x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] > x ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] > x ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] > x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec5u32_t Vec5u32_CmpGES(vec5u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec5u32_t Vec5u32_CmpNES(vec5u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] != x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] != x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] != x ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] != x ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] != x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec5u32_t Vec5u32_Sign(vec5u32_t v)
{
	v.v[0] = v.v[0] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;
	v.v[1] = v.v[1] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;
	v.v[2] = v.v[2] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;
	v.v[3] = v.v[3] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;
	v.v[4] = v.v[4] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;

	return v;
}
vec5u32_t Vec5u32_SignPosNeg(vec5u32_t v)
{
	v.v[0] = v.v[0] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;
	v.v[1] = v.v[1] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;
	v.v[2] = v.v[2] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;
	v.v[3] = v.v[3] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;
	v.v[4] = v.v[4] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;

	return v;
}
vec5u32_t Vec5u32_Zero()
{
	return G_VEC5U32_T_ZERO;
}
vec5u32_t Vec5u32_One()
{
	return G_VEC5U32_T_ONE;
}
vec5u32_t Vec5u32_Cross(vec5u32_t v0, vec5u32_t v1, vec5u32_t v2, vec5u32_t v3)
{
	vec5u32_t v;
	mat5x5u32_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;

	for (i = 0; i < 5; i++)
		v.v[i] = Mat4x4u32_Det(Mat5x5u32_DeleteRowColumn(mat, 0, i));

	return v;
}
vec6u32_t Vec5u32_ToVec6u32(vec5u32_t v, uint32_t x0)
{
	vec6u32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = x0;

	return outv;
}
vec7u32_t Vec5u32_ToVec7u32(vec5u32_t v, uint32_t x0, uint32_t x1)
{
	vec7u32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = x0;
	outv.v[6] = x1;

	return outv;
}
vec8u32_t Vec5u32_ToVec8u32(vec5u32_t v, uint32_t x0, uint32_t x1, uint32_t x2)
{
	vec8u32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = x0;
	outv.v[6] = x1;
	outv.v[7] = x2;

	return outv;
}
vec5i32_t Vec5i32_SetComponent(vec5i32_t v, int index, int32_t value)
{
	v.v[index] = value;

	return v;
}
vec5i32_t Vec5i32_Vec(int32_t x0, int32_t x1, int32_t x2, int32_t x3, int32_t x4)
{
	vec5i32_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;

	return v;
}
vec5i32_t Vec5i32_Add(vec5i32_t v0, vec5i32_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];

	return v0;
}
vec5i32_t Vec5i32_Sub(vec5i32_t v0, vec5i32_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];

	return v0;
}
int32_t Vec5i32_GetComponent(vec5i32_t v, int index)
{
	return v.v[index];
}
vec5i32_t Vec5i32_Mul(vec5i32_t v0, vec5i32_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];

	return v0;
}
vec5i32_t Vec5i32_Div(vec5i32_t v0, vec5i32_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];

	return v0;
}
vec5i32_t Vec5i32_Scale(vec5i32_t v, int32_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;

	return v;
}
vec5i32_t Vec5i32_DivScale(vec5i32_t v, int32_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;

	return v;
}
vec5i32_t Vec5i32_MA(vec5i32_t v, vec5i32_t dir, int32_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;

	return v;
}
vec5i32_t Vec5i32_DA(vec5i32_t v, vec5i32_t dir, int32_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;

	return v;
}
int32_t Vec5i32_Dot(vec5i32_t v0, vec5i32_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4];
}
int32_t Vec5i32_LenSq(vec5i32_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4];
}
int32_t Vec5i32_Len(vec5i32_t v)
{
	return sqrtf(Vec5i32_LenSq(v));
}
vec5i32_t Vec5i32_Abs(vec5i32_t v)
{
	v.v[0] = (v.v[0] < 0 ? -v.v[0] : v.v[0]);
	v.v[1] = (v.v[1] < 0 ? -v.v[1] : v.v[1]);
	v.v[2] = (v.v[2] < 0 ? -v.v[2] : v.v[2]);
	v.v[3] = (v.v[3] < 0 ? -v.v[3] : v.v[3]);
	v.v[4] = (v.v[4] < 0 ? -v.v[4] : v.v[4]);

	return v;
}
vec5i32_t Vec5i32_Mod(vec5i32_t v0, vec5i32_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);
	v0.v[4] = (v0.v[4] % v1.v[4]);

	return v0;
}
vec5i32_t Vec5i32_ModS(vec5i32_t v0, int32_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);
	v0.v[4] = (v0.v[4] % x);

	return v0;
}
vec5i32_t Vec5i32_Min(vec5i32_t v0, vec5i32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];

	return v0;
}
vec5i32_t Vec5i32_Max(vec5i32_t v0, vec5i32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];

	return v0;
}
vec5i32_t Vec5i32_MinS(vec5i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;

	return v0;
}
vec5i32_t Vec5i32_MaxS(vec5i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;

	return v0;
}
vec5i32_t Vec5i32_Clamp(vec5i32_t v, vec5i32_t min, vec5i32_t max)
{
	return Vec5i32_Max(Vec5i32_Min(v, max), min);
}
vec5i32_t Vec5i32_ClampS(vec5i32_t v, int32_t min, int32_t max)
{
	return Vec5i32_MaxS(Vec5i32_MinS(v, max), min);
}
vec5i32_t Vec5i32_Neg(vec5i32_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];
	v.v[3] = -v.v[3];
	v.v[4] = -v.v[4];

	return v;
}
vec5i32_t Vec5i32_CmpLT(vec5i32_t v0, vec5i32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec5i32_t Vec5i32_CmpLE(vec5i32_t v0, vec5i32_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec5i32_t Vec5i32_CmpEQ(vec5i32_t v0, vec5i32_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec5i32_t Vec5i32_CmpGT(vec5i32_t v0, vec5i32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec5i32_t Vec5i32_CmpGE(vec5i32_t v0, vec5i32_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec5i32_t Vec5i32_CmpNE(vec5i32_t v0, vec5i32_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec5i32_t Vec5i32_CmpLTS(vec5i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] < x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] < x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] < x ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] < x ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] < x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec5i32_t Vec5i32_CmpLES(vec5i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec5i32_t Vec5i32_CmpEQS(vec5i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] == x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] == x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] == x ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] == x ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] == x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec5i32_t Vec5i32_CmpGTS(vec5i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] > x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] > x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] > x ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] > x ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] > x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec5i32_t Vec5i32_CmpGES(vec5i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec5i32_t Vec5i32_CmpNES(vec5i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] != x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] != x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] != x ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] != x ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] != x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec5i32_t Vec5i32_Sign(vec5i32_t v)
{
	v.v[0] = v.v[0] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;
	v.v[1] = v.v[1] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;
	v.v[2] = v.v[2] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;
	v.v[3] = v.v[3] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;
	v.v[4] = v.v[4] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;

	return v;
}
vec5i32_t Vec5i32_SignPosNeg(vec5i32_t v)
{
	v.v[0] = v.v[0] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;
	v.v[1] = v.v[1] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;
	v.v[2] = v.v[2] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;
	v.v[3] = v.v[3] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;
	v.v[4] = v.v[4] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;

	return v;
}
vec5i32_t Vec5i32_Zero()
{
	return G_VEC5I32_T_ZERO;
}
vec5i32_t Vec5i32_One()
{
	return G_VEC5I32_T_ONE;
}
vec5i32_t Vec5i32_NegOne()
{
	return Vec5i32_Neg(G_VEC5I32_T_ONE);
}
vec5i32_t Vec5i32_Cross(vec5i32_t v0, vec5i32_t v1, vec5i32_t v2, vec5i32_t v3)
{
	vec5i32_t v;
	mat5x5i32_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;

	for (i = 0; i < 5; i++)
		v.v[i] = Mat4x4i32_Det(Mat5x5i32_DeleteRowColumn(mat, 0, i));

	return v;
}
vec6i32_t Vec5i32_ToVec6i32(vec5i32_t v, int32_t x0)
{
	vec6i32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = x0;

	return outv;
}
vec7i32_t Vec5i32_ToVec7i32(vec5i32_t v, int32_t x0, int32_t x1)
{
	vec7i32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = x0;
	outv.v[6] = x1;

	return outv;
}
vec8i32_t Vec5i32_ToVec8i32(vec5i32_t v, int32_t x0, int32_t x1, int32_t x2)
{
	vec8i32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = x0;
	outv.v[6] = x1;
	outv.v[7] = x2;

	return outv;
}
vec5u16_t Vec5u16_SetComponent(vec5u16_t v, int index, uint16_t value)
{
	v.v[index] = value;

	return v;
}
vec5u16_t Vec5u16_Vec(uint16_t x0, uint16_t x1, uint16_t x2, uint16_t x3, uint16_t x4)
{
	vec5u16_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;

	return v;
}
vec5u16_t Vec5u16_Add(vec5u16_t v0, vec5u16_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];

	return v0;
}
vec5u16_t Vec5u16_Sub(vec5u16_t v0, vec5u16_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];

	return v0;
}
uint16_t Vec5u16_GetComponent(vec5u16_t v, int index)
{
	return v.v[index];
}
vec5u16_t Vec5u16_Mul(vec5u16_t v0, vec5u16_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];

	return v0;
}
vec5u16_t Vec5u16_Div(vec5u16_t v0, vec5u16_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];

	return v0;
}
vec5u16_t Vec5u16_Scale(vec5u16_t v, uint16_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;

	return v;
}
vec5u16_t Vec5u16_DivScale(vec5u16_t v, uint16_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;

	return v;
}
vec5u16_t Vec5u16_MA(vec5u16_t v, vec5u16_t dir, uint16_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;

	return v;
}
vec5u16_t Vec5u16_DA(vec5u16_t v, vec5u16_t dir, uint16_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;

	return v;
}
uint16_t Vec5u16_Dot(vec5u16_t v0, vec5u16_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4];
}
uint16_t Vec5u16_LenSq(vec5u16_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4];
}
uint16_t Vec5u16_Len(vec5u16_t v)
{
	return sqrtf(Vec5u16_LenSq(v));
}
vec5u16_t Vec5u16_Mod(vec5u16_t v0, vec5u16_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);
	v0.v[4] = (v0.v[4] % v1.v[4]);

	return v0;
}
vec5u16_t Vec5u16_ModS(vec5u16_t v0, uint16_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);
	v0.v[4] = (v0.v[4] % x);

	return v0;
}
vec5u16_t Vec5u16_Min(vec5u16_t v0, vec5u16_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];

	return v0;
}
vec5u16_t Vec5u16_Max(vec5u16_t v0, vec5u16_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];

	return v0;
}
vec5u16_t Vec5u16_MinS(vec5u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;

	return v0;
}
vec5u16_t Vec5u16_MaxS(vec5u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;

	return v0;
}
vec5u16_t Vec5u16_Clamp(vec5u16_t v, vec5u16_t min, vec5u16_t max)
{
	return Vec5u16_Max(Vec5u16_Min(v, max), min);
}
vec5u16_t Vec5u16_ClampS(vec5u16_t v, uint16_t min, uint16_t max)
{
	return Vec5u16_MaxS(Vec5u16_MinS(v, max), min);
}
vec5u16_t Vec5u16_CmpLT(vec5u16_t v0, vec5u16_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec5u16_t Vec5u16_CmpLE(vec5u16_t v0, vec5u16_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec5u16_t Vec5u16_CmpEQ(vec5u16_t v0, vec5u16_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec5u16_t Vec5u16_CmpGT(vec5u16_t v0, vec5u16_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec5u16_t Vec5u16_CmpGE(vec5u16_t v0, vec5u16_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec5u16_t Vec5u16_CmpNE(vec5u16_t v0, vec5u16_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec5u16_t Vec5u16_CmpLTS(vec5u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] < x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] < x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] < x ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] < x ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] < x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec5u16_t Vec5u16_CmpLES(vec5u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec5u16_t Vec5u16_CmpEQS(vec5u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] == x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] == x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] == x ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] == x ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] == x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec5u16_t Vec5u16_CmpGTS(vec5u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] > x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] > x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] > x ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] > x ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] > x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec5u16_t Vec5u16_CmpGES(vec5u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec5u16_t Vec5u16_CmpNES(vec5u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] != x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] != x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] != x ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] != x ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] != x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec5u16_t Vec5u16_Sign(vec5u16_t v)
{
	v.v[0] = v.v[0] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;
	v.v[1] = v.v[1] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;
	v.v[2] = v.v[2] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;
	v.v[3] = v.v[3] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;
	v.v[4] = v.v[4] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;

	return v;
}
vec5u16_t Vec5u16_SignPosNeg(vec5u16_t v)
{
	v.v[0] = v.v[0] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;
	v.v[1] = v.v[1] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;
	v.v[2] = v.v[2] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;
	v.v[3] = v.v[3] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;
	v.v[4] = v.v[4] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;

	return v;
}
vec5u16_t Vec5u16_Zero()
{
	return G_VEC5U16_T_ZERO;
}
vec5u16_t Vec5u16_One()
{
	return G_VEC5U16_T_ONE;
}
vec5u16_t Vec5u16_Cross(vec5u16_t v0, vec5u16_t v1, vec5u16_t v2, vec5u16_t v3)
{
	vec5u16_t v;
	mat5x5u16_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;

	for (i = 0; i < 5; i++)
		v.v[i] = Mat4x4u16_Det(Mat5x5u16_DeleteRowColumn(mat, 0, i));

	return v;
}
vec6u16_t Vec5u16_ToVec6u16(vec5u16_t v, uint16_t x0)
{
	vec6u16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = x0;

	return outv;
}
vec7u16_t Vec5u16_ToVec7u16(vec5u16_t v, uint16_t x0, uint16_t x1)
{
	vec7u16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = x0;
	outv.v[6] = x1;

	return outv;
}
vec8u16_t Vec5u16_ToVec8u16(vec5u16_t v, uint16_t x0, uint16_t x1, uint16_t x2)
{
	vec8u16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = x0;
	outv.v[6] = x1;
	outv.v[7] = x2;

	return outv;
}
vec5i16_t Vec5i16_SetComponent(vec5i16_t v, int index, int16_t value)
{
	v.v[index] = value;

	return v;
}
vec5i16_t Vec5i16_Vec(int16_t x0, int16_t x1, int16_t x2, int16_t x3, int16_t x4)
{
	vec5i16_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;

	return v;
}
vec5i16_t Vec5i16_Add(vec5i16_t v0, vec5i16_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];

	return v0;
}
vec5i16_t Vec5i16_Sub(vec5i16_t v0, vec5i16_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];

	return v0;
}
int16_t Vec5i16_GetComponent(vec5i16_t v, int index)
{
	return v.v[index];
}
vec5i16_t Vec5i16_Mul(vec5i16_t v0, vec5i16_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];

	return v0;
}
vec5i16_t Vec5i16_Div(vec5i16_t v0, vec5i16_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];

	return v0;
}
vec5i16_t Vec5i16_Scale(vec5i16_t v, int16_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;

	return v;
}
vec5i16_t Vec5i16_DivScale(vec5i16_t v, int16_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;

	return v;
}
vec5i16_t Vec5i16_MA(vec5i16_t v, vec5i16_t dir, int16_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;

	return v;
}
vec5i16_t Vec5i16_DA(vec5i16_t v, vec5i16_t dir, int16_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;

	return v;
}
int16_t Vec5i16_Dot(vec5i16_t v0, vec5i16_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4];
}
int16_t Vec5i16_LenSq(vec5i16_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4];
}
int16_t Vec5i16_Len(vec5i16_t v)
{
	return sqrtf(Vec5i16_LenSq(v));
}
vec5i16_t Vec5i16_Abs(vec5i16_t v)
{
	v.v[0] = (v.v[0] < 0 ? -v.v[0] : v.v[0]);
	v.v[1] = (v.v[1] < 0 ? -v.v[1] : v.v[1]);
	v.v[2] = (v.v[2] < 0 ? -v.v[2] : v.v[2]);
	v.v[3] = (v.v[3] < 0 ? -v.v[3] : v.v[3]);
	v.v[4] = (v.v[4] < 0 ? -v.v[4] : v.v[4]);

	return v;
}
vec5i16_t Vec5i16_Mod(vec5i16_t v0, vec5i16_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);
	v0.v[4] = (v0.v[4] % v1.v[4]);

	return v0;
}
vec5i16_t Vec5i16_ModS(vec5i16_t v0, int16_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);
	v0.v[4] = (v0.v[4] % x);

	return v0;
}
vec5i16_t Vec5i16_Min(vec5i16_t v0, vec5i16_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];

	return v0;
}
vec5i16_t Vec5i16_Max(vec5i16_t v0, vec5i16_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];

	return v0;
}
vec5i16_t Vec5i16_MinS(vec5i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;

	return v0;
}
vec5i16_t Vec5i16_MaxS(vec5i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;

	return v0;
}
vec5i16_t Vec5i16_Clamp(vec5i16_t v, vec5i16_t min, vec5i16_t max)
{
	return Vec5i16_Max(Vec5i16_Min(v, max), min);
}
vec5i16_t Vec5i16_ClampS(vec5i16_t v, int16_t min, int16_t max)
{
	return Vec5i16_MaxS(Vec5i16_MinS(v, max), min);
}
vec5i16_t Vec5i16_Neg(vec5i16_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];
	v.v[3] = -v.v[3];
	v.v[4] = -v.v[4];

	return v;
}
vec5i16_t Vec5i16_CmpLT(vec5i16_t v0, vec5i16_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec5i16_t Vec5i16_CmpLE(vec5i16_t v0, vec5i16_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec5i16_t Vec5i16_CmpEQ(vec5i16_t v0, vec5i16_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec5i16_t Vec5i16_CmpGT(vec5i16_t v0, vec5i16_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec5i16_t Vec5i16_CmpGE(vec5i16_t v0, vec5i16_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec5i16_t Vec5i16_CmpNE(vec5i16_t v0, vec5i16_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec5i16_t Vec5i16_CmpLTS(vec5i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] < x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] < x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] < x ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] < x ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] < x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec5i16_t Vec5i16_CmpLES(vec5i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec5i16_t Vec5i16_CmpEQS(vec5i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] == x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] == x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] == x ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] == x ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] == x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec5i16_t Vec5i16_CmpGTS(vec5i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] > x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] > x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] > x ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] > x ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] > x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec5i16_t Vec5i16_CmpGES(vec5i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec5i16_t Vec5i16_CmpNES(vec5i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] != x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] != x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] != x ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] != x ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] != x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec5i16_t Vec5i16_Sign(vec5i16_t v)
{
	v.v[0] = v.v[0] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;
	v.v[1] = v.v[1] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;
	v.v[2] = v.v[2] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;
	v.v[3] = v.v[3] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;
	v.v[4] = v.v[4] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;

	return v;
}
vec5i16_t Vec5i16_SignPosNeg(vec5i16_t v)
{
	v.v[0] = v.v[0] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;
	v.v[1] = v.v[1] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;
	v.v[2] = v.v[2] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;
	v.v[3] = v.v[3] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;
	v.v[4] = v.v[4] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;

	return v;
}
vec5i16_t Vec5i16_Zero()
{
	return G_VEC5I16_T_ZERO;
}
vec5i16_t Vec5i16_One()
{
	return G_VEC5I16_T_ONE;
}
vec5i16_t Vec5i16_NegOne()
{
	return Vec5i16_Neg(G_VEC5I16_T_ONE);
}
vec5i16_t Vec5i16_Cross(vec5i16_t v0, vec5i16_t v1, vec5i16_t v2, vec5i16_t v3)
{
	vec5i16_t v;
	mat5x5i16_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;

	for (i = 0; i < 5; i++)
		v.v[i] = Mat4x4i16_Det(Mat5x5i16_DeleteRowColumn(mat, 0, i));

	return v;
}
vec6i16_t Vec5i16_ToVec6i16(vec5i16_t v, int16_t x0)
{
	vec6i16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = x0;

	return outv;
}
vec7i16_t Vec5i16_ToVec7i16(vec5i16_t v, int16_t x0, int16_t x1)
{
	vec7i16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = x0;
	outv.v[6] = x1;

	return outv;
}
vec8i16_t Vec5i16_ToVec8i16(vec5i16_t v, int16_t x0, int16_t x1, int16_t x2)
{
	vec8i16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = x0;
	outv.v[6] = x1;
	outv.v[7] = x2;

	return outv;
}
vec5u8_t Vec5u8_SetComponent(vec5u8_t v, int index, uint8_t value)
{
	v.v[index] = value;

	return v;
}
vec5u8_t Vec5u8_Vec(uint8_t x0, uint8_t x1, uint8_t x2, uint8_t x3, uint8_t x4)
{
	vec5u8_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;

	return v;
}
vec5u8_t Vec5u8_Add(vec5u8_t v0, vec5u8_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];

	return v0;
}
vec5u8_t Vec5u8_Sub(vec5u8_t v0, vec5u8_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];

	return v0;
}
uint8_t Vec5u8_GetComponent(vec5u8_t v, int index)
{
	return v.v[index];
}
vec5u8_t Vec5u8_Mul(vec5u8_t v0, vec5u8_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];

	return v0;
}
vec5u8_t Vec5u8_Div(vec5u8_t v0, vec5u8_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];

	return v0;
}
vec5u8_t Vec5u8_Scale(vec5u8_t v, uint8_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;

	return v;
}
vec5u8_t Vec5u8_DivScale(vec5u8_t v, uint8_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;

	return v;
}
vec5u8_t Vec5u8_MA(vec5u8_t v, vec5u8_t dir, uint8_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;

	return v;
}
vec5u8_t Vec5u8_DA(vec5u8_t v, vec5u8_t dir, uint8_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;

	return v;
}
uint8_t Vec5u8_Dot(vec5u8_t v0, vec5u8_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4];
}
uint8_t Vec5u8_LenSq(vec5u8_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4];
}
uint8_t Vec5u8_Len(vec5u8_t v)
{
	return sqrtf(Vec5u8_LenSq(v));
}
vec5u8_t Vec5u8_Mod(vec5u8_t v0, vec5u8_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);
	v0.v[4] = (v0.v[4] % v1.v[4]);

	return v0;
}
vec5u8_t Vec5u8_ModS(vec5u8_t v0, uint8_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);
	v0.v[4] = (v0.v[4] % x);

	return v0;
}
vec5u8_t Vec5u8_Min(vec5u8_t v0, vec5u8_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];

	return v0;
}
vec5u8_t Vec5u8_Max(vec5u8_t v0, vec5u8_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];

	return v0;
}
vec5u8_t Vec5u8_MinS(vec5u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;

	return v0;
}
vec5u8_t Vec5u8_MaxS(vec5u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;

	return v0;
}
vec5u8_t Vec5u8_Clamp(vec5u8_t v, vec5u8_t min, vec5u8_t max)
{
	return Vec5u8_Max(Vec5u8_Min(v, max), min);
}
vec5u8_t Vec5u8_ClampS(vec5u8_t v, uint8_t min, uint8_t max)
{
	return Vec5u8_MaxS(Vec5u8_MinS(v, max), min);
}
vec5u8_t Vec5u8_CmpLT(vec5u8_t v0, vec5u8_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec5u8_t Vec5u8_CmpLE(vec5u8_t v0, vec5u8_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec5u8_t Vec5u8_CmpEQ(vec5u8_t v0, vec5u8_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec5u8_t Vec5u8_CmpGT(vec5u8_t v0, vec5u8_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec5u8_t Vec5u8_CmpGE(vec5u8_t v0, vec5u8_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec5u8_t Vec5u8_CmpNE(vec5u8_t v0, vec5u8_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec5u8_t Vec5u8_CmpLTS(vec5u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] < x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] < x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] < x ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] < x ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] < x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec5u8_t Vec5u8_CmpLES(vec5u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec5u8_t Vec5u8_CmpEQS(vec5u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] == x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] == x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] == x ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] == x ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] == x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec5u8_t Vec5u8_CmpGTS(vec5u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] > x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] > x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] > x ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] > x ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] > x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec5u8_t Vec5u8_CmpGES(vec5u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec5u8_t Vec5u8_CmpNES(vec5u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] != x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] != x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] != x ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] != x ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] != x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec5u8_t Vec5u8_Sign(vec5u8_t v)
{
	v.v[0] = v.v[0] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;
	v.v[1] = v.v[1] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;
	v.v[2] = v.v[2] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;
	v.v[3] = v.v[3] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;
	v.v[4] = v.v[4] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;

	return v;
}
vec5u8_t Vec5u8_SignPosNeg(vec5u8_t v)
{
	v.v[0] = v.v[0] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;
	v.v[1] = v.v[1] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;
	v.v[2] = v.v[2] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;
	v.v[3] = v.v[3] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;
	v.v[4] = v.v[4] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;

	return v;
}
vec5u8_t Vec5u8_Zero()
{
	return G_VEC5U8_T_ZERO;
}
vec5u8_t Vec5u8_One()
{
	return G_VEC5U8_T_ONE;
}
vec5u8_t Vec5u8_Cross(vec5u8_t v0, vec5u8_t v1, vec5u8_t v2, vec5u8_t v3)
{
	vec5u8_t v;
	mat5x5u8_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;

	for (i = 0; i < 5; i++)
		v.v[i] = Mat4x4u8_Det(Mat5x5u8_DeleteRowColumn(mat, 0, i));

	return v;
}
vec6u8_t Vec5u8_ToVec6u8(vec5u8_t v, uint8_t x0)
{
	vec6u8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = x0;

	return outv;
}
vec7u8_t Vec5u8_ToVec7u8(vec5u8_t v, uint8_t x0, uint8_t x1)
{
	vec7u8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = x0;
	outv.v[6] = x1;

	return outv;
}
vec8u8_t Vec5u8_ToVec8u8(vec5u8_t v, uint8_t x0, uint8_t x1, uint8_t x2)
{
	vec8u8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = x0;
	outv.v[6] = x1;
	outv.v[7] = x2;

	return outv;
}
vec5i8_t Vec5i8_SetComponent(vec5i8_t v, int index, int8_t value)
{
	v.v[index] = value;

	return v;
}
vec5i8_t Vec5i8_Vec(int8_t x0, int8_t x1, int8_t x2, int8_t x3, int8_t x4)
{
	vec5i8_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;

	return v;
}
vec5i8_t Vec5i8_Add(vec5i8_t v0, vec5i8_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];

	return v0;
}
vec5i8_t Vec5i8_Sub(vec5i8_t v0, vec5i8_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];

	return v0;
}
int8_t Vec5i8_GetComponent(vec5i8_t v, int index)
{
	return v.v[index];
}
vec5i8_t Vec5i8_Mul(vec5i8_t v0, vec5i8_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];

	return v0;
}
vec5i8_t Vec5i8_Div(vec5i8_t v0, vec5i8_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];

	return v0;
}
vec5i8_t Vec5i8_Scale(vec5i8_t v, int8_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;

	return v;
}
vec5i8_t Vec5i8_DivScale(vec5i8_t v, int8_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;

	return v;
}
vec5i8_t Vec5i8_MA(vec5i8_t v, vec5i8_t dir, int8_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;

	return v;
}
vec5i8_t Vec5i8_DA(vec5i8_t v, vec5i8_t dir, int8_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;

	return v;
}
int8_t Vec5i8_Dot(vec5i8_t v0, vec5i8_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4];
}
int8_t Vec5i8_LenSq(vec5i8_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4];
}
int8_t Vec5i8_Len(vec5i8_t v)
{
	return sqrtf(Vec5i8_LenSq(v));
}
vec5i8_t Vec5i8_Abs(vec5i8_t v)
{
	v.v[0] = (v.v[0] < 0 ? -v.v[0] : v.v[0]);
	v.v[1] = (v.v[1] < 0 ? -v.v[1] : v.v[1]);
	v.v[2] = (v.v[2] < 0 ? -v.v[2] : v.v[2]);
	v.v[3] = (v.v[3] < 0 ? -v.v[3] : v.v[3]);
	v.v[4] = (v.v[4] < 0 ? -v.v[4] : v.v[4]);

	return v;
}
vec5i8_t Vec5i8_Mod(vec5i8_t v0, vec5i8_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);
	v0.v[4] = (v0.v[4] % v1.v[4]);

	return v0;
}
vec5i8_t Vec5i8_ModS(vec5i8_t v0, int8_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);
	v0.v[4] = (v0.v[4] % x);

	return v0;
}
vec5i8_t Vec5i8_Min(vec5i8_t v0, vec5i8_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];

	return v0;
}
vec5i8_t Vec5i8_Max(vec5i8_t v0, vec5i8_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];

	return v0;
}
vec5i8_t Vec5i8_MinS(vec5i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;

	return v0;
}
vec5i8_t Vec5i8_MaxS(vec5i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;

	return v0;
}
vec5i8_t Vec5i8_Clamp(vec5i8_t v, vec5i8_t min, vec5i8_t max)
{
	return Vec5i8_Max(Vec5i8_Min(v, max), min);
}
vec5i8_t Vec5i8_ClampS(vec5i8_t v, int8_t min, int8_t max)
{
	return Vec5i8_MaxS(Vec5i8_MinS(v, max), min);
}
vec5i8_t Vec5i8_Neg(vec5i8_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];
	v.v[3] = -v.v[3];
	v.v[4] = -v.v[4];

	return v;
}
vec5i8_t Vec5i8_CmpLT(vec5i8_t v0, vec5i8_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec5i8_t Vec5i8_CmpLE(vec5i8_t v0, vec5i8_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec5i8_t Vec5i8_CmpEQ(vec5i8_t v0, vec5i8_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec5i8_t Vec5i8_CmpGT(vec5i8_t v0, vec5i8_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec5i8_t Vec5i8_CmpGE(vec5i8_t v0, vec5i8_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec5i8_t Vec5i8_CmpNE(vec5i8_t v0, vec5i8_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec5i8_t Vec5i8_CmpLTS(vec5i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] < x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] < x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] < x ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] < x ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] < x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec5i8_t Vec5i8_CmpLES(vec5i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec5i8_t Vec5i8_CmpEQS(vec5i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] == x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] == x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] == x ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] == x ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] == x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec5i8_t Vec5i8_CmpGTS(vec5i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] > x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] > x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] > x ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] > x ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] > x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec5i8_t Vec5i8_CmpGES(vec5i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec5i8_t Vec5i8_CmpNES(vec5i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] != x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] != x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] != x ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] != x ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] != x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec5i8_t Vec5i8_Sign(vec5i8_t v)
{
	v.v[0] = v.v[0] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;
	v.v[1] = v.v[1] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;
	v.v[2] = v.v[2] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;
	v.v[3] = v.v[3] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;
	v.v[4] = v.v[4] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;

	return v;
}
vec5i8_t Vec5i8_SignPosNeg(vec5i8_t v)
{
	v.v[0] = v.v[0] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;
	v.v[1] = v.v[1] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;
	v.v[2] = v.v[2] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;
	v.v[3] = v.v[3] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;
	v.v[4] = v.v[4] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;

	return v;
}
vec5i8_t Vec5i8_Zero()
{
	return G_VEC5I8_T_ZERO;
}
vec5i8_t Vec5i8_One()
{
	return G_VEC5I8_T_ONE;
}
vec5i8_t Vec5i8_NegOne()
{
	return Vec5i8_Neg(G_VEC5I8_T_ONE);
}
vec5i8_t Vec5i8_Cross(vec5i8_t v0, vec5i8_t v1, vec5i8_t v2, vec5i8_t v3)
{
	vec5i8_t v;
	mat5x5i8_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;

	for (i = 0; i < 5; i++)
		v.v[i] = Mat4x4i8_Det(Mat5x5i8_DeleteRowColumn(mat, 0, i));

	return v;
}
vec6i8_t Vec5i8_ToVec6i8(vec5i8_t v, int8_t x0)
{
	vec6i8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = x0;

	return outv;
}
vec7i8_t Vec5i8_ToVec7i8(vec5i8_t v, int8_t x0, int8_t x1)
{
	vec7i8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = x0;
	outv.v[6] = x1;

	return outv;
}
vec8i8_t Vec5i8_ToVec8i8(vec5i8_t v, int8_t x0, int8_t x1, int8_t x2)
{
	vec8i8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = x0;
	outv.v[6] = x1;
	outv.v[7] = x2;

	return outv;
}
vec6f64_t Vec6f64_SetComponent(vec6f64_t v, int index, double value)
{
	v.v[index] = value;

	return v;
}
vec6f64_t Vec6f64_Vec(double x0, double x1, double x2, double x3, double x4, double x5)
{
	vec6f64_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;
	v.v[5] = x5;

	return v;
}
vec6f64_t Vec6f64_Add(vec6f64_t v0, vec6f64_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];
	v0.v[5] += v1.v[5];

	return v0;
}
vec6f64_t Vec6f64_Sub(vec6f64_t v0, vec6f64_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];
	v0.v[5] -= v1.v[5];

	return v0;
}
double Vec6f64_GetComponent(vec6f64_t v, int index)
{
	return v.v[index];
}
vec6f64_t Vec6f64_Mul(vec6f64_t v0, vec6f64_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];
	v0.v[5] *= v1.v[5];

	return v0;
}
vec6f64_t Vec6f64_Div(vec6f64_t v0, vec6f64_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];
	v0.v[5] /= v1.v[5];

	return v0;
}
vec6f64_t Vec6f64_Scale(vec6f64_t v, double scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;
	v.v[5] *= scale;

	return v;
}
vec6f64_t Vec6f64_DivScale(vec6f64_t v, double divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;
	v.v[5] /= divscale;

	return v;
}
vec6f64_t Vec6f64_MA(vec6f64_t v, vec6f64_t dir, double scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;
	v.v[5] += dir.v[5] * scale;

	return v;
}
vec6f64_t Vec6f64_DA(vec6f64_t v, vec6f64_t dir, double divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;
	v.v[5] += dir.v[5] / divscale;

	return v;
}
double Vec6f64_Dot(vec6f64_t v0, vec6f64_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4] + v0.v[5] * v1.v[5];
}
double Vec6f64_LenSq(vec6f64_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4] + v.v[5] * v.v[5];
}
double Vec6f64_Len(vec6f64_t v)
{
	return sqrt(Vec6f64_LenSq(v));
}
vec6f64_t Vec6f64_Normalise(vec6f64_t v)
{
	double lensq = Vec6f64_LenSq(v);

	if (lensq == G_F64_ZERO)
		return v;
	else
		return Vec6f64_Scale(v, G_F64_ONE / sqrt(lensq));
}
vec6f64_t Vec6f64_Abs(vec6f64_t v)
{
	v.v[0] = fabs(v.v[0]);
	v.v[1] = fabs(v.v[1]);
	v.v[2] = fabs(v.v[2]);
	v.v[3] = fabs(v.v[3]);
	v.v[4] = fabs(v.v[4]);
	v.v[5] = fabs(v.v[5]);

	return v;
}
vec6f64_t Vec6f64_Floor(vec6f64_t v)
{
	v.v[0] = floor(v.v[0]);
	v.v[1] = floor(v.v[1]);
	v.v[2] = floor(v.v[2]);
	v.v[3] = floor(v.v[3]);
	v.v[4] = floor(v.v[4]);
	v.v[5] = floor(v.v[5]);

	return v;
}
vec6f64_t Vec6f64_Ceil(vec6f64_t v)
{
	v.v[0] = ceil(v.v[0]);
	v.v[1] = ceil(v.v[1]);
	v.v[2] = ceil(v.v[2]);
	v.v[3] = ceil(v.v[3]);
	v.v[4] = ceil(v.v[4]);
	v.v[5] = ceil(v.v[5]);

	return v;
}
vec6f64_t Vec6f64_Fract(vec6f64_t v)
{
	return Vec6f64_Sub(v, Vec6f64_Floor(v));
}
vec6f64_t Vec6f64_Mod(vec6f64_t v0, vec6f64_t v1)
{
	v0.v[0] = fmod(v0.v[0], v1.v[0]);
	v0.v[1] = fmod(v0.v[1], v1.v[1]);
	v0.v[2] = fmod(v0.v[2], v1.v[2]);
	v0.v[3] = fmod(v0.v[3], v1.v[3]);
	v0.v[4] = fmod(v0.v[4], v1.v[4]);
	v0.v[5] = fmod(v0.v[5], v1.v[5]);

	return v0;
}
vec6f64_t Vec6f64_ModS(vec6f64_t v0, double x)
{
	v0.v[0] = fmod(v0.v[0], x);
	v0.v[1] = fmod(v0.v[1], x);
	v0.v[2] = fmod(v0.v[2], x);
	v0.v[3] = fmod(v0.v[3], x);
	v0.v[4] = fmod(v0.v[4], x);
	v0.v[5] = fmod(v0.v[5], x);

	return v0;
}
vec6f64_t Vec6f64_Min(vec6f64_t v0, vec6f64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] < v1.v[5] ? v0.v[5] : v1.v[5];

	return v0;
}
vec6f64_t Vec6f64_Max(vec6f64_t v0, vec6f64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] > v1.v[5] ? v0.v[5] : v1.v[5];

	return v0;
}
vec6f64_t Vec6f64_MinS(vec6f64_t v0, double x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] < x ? v0.v[5] : x;

	return v0;
}
vec6f64_t Vec6f64_MaxS(vec6f64_t v0, double x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] > x ? v0.v[5] : x;

	return v0;
}
vec6f64_t Vec6f64_Clamp(vec6f64_t v, vec6f64_t min, vec6f64_t max)
{
	return Vec6f64_Max(Vec6f64_Min(v, max), min);
}
vec6f64_t Vec6f64_ClampS(vec6f64_t v, double min, double max)
{
	return Vec6f64_MaxS(Vec6f64_MinS(v, max), min);
}
vec6f64_t Vec6f64_Neg(vec6f64_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];
	v.v[3] = -v.v[3];
	v.v[4] = -v.v[4];
	v.v[5] = -v.v[5];

	return v;
}
vec6f64_t Vec6f64_Reciprocal(vec6f64_t v)
{
	v.v[0] = G_F64_ONE / v.v[0];
	v.v[1] = G_F64_ONE / v.v[1];
	v.v[2] = G_F64_ONE / v.v[2];
	v.v[3] = G_F64_ONE / v.v[3];
	v.v[4] = G_F64_ONE / v.v[4];
	v.v[5] = G_F64_ONE / v.v[5];

	return v;
}
vec6f64_t Vec6f64_Truncate(vec6f64_t v)
{
	v.v[0] = v.v[0] < G_F64_ZERO ? ceil(v.v[0]) : floor(v.v[0]);
	v.v[1] = v.v[1] < G_F64_ZERO ? ceil(v.v[1]) : floor(v.v[1]);
	v.v[2] = v.v[2] < G_F64_ZERO ? ceil(v.v[2]) : floor(v.v[2]);
	v.v[3] = v.v[3] < G_F64_ZERO ? ceil(v.v[3]) : floor(v.v[3]);
	v.v[4] = v.v[4] < G_F64_ZERO ? ceil(v.v[4]) : floor(v.v[4]);
	v.v[5] = v.v[5] < G_F64_ZERO ? ceil(v.v[5]) : floor(v.v[5]);

	return v;
}
vec6f64_t Vec6f64_TruncateAway(vec6f64_t v)
{
	v.v[0] = v.v[0] < G_F64_ZERO ? floor(v.v[0]) : ceil(v.v[0]);
	v.v[1] = v.v[1] < G_F64_ZERO ? floor(v.v[1]) : ceil(v.v[1]);
	v.v[2] = v.v[2] < G_F64_ZERO ? floor(v.v[2]) : ceil(v.v[2]);
	v.v[3] = v.v[3] < G_F64_ZERO ? floor(v.v[3]) : ceil(v.v[3]);
	v.v[4] = v.v[4] < G_F64_ZERO ? floor(v.v[4]) : ceil(v.v[4]);
	v.v[5] = v.v[5] < G_F64_ZERO ? floor(v.v[5]) : ceil(v.v[5]);

	return v;
}
vec6f64_t Vec6f64_CmpLT(vec6f64_t v0, vec6f64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] < v1.v[5] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec6f64_t Vec6f64_CmpLE(vec6f64_t v0, vec6f64_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] <= v1.v[5] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec6f64_t Vec6f64_CmpEQ(vec6f64_t v0, vec6f64_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] == v1.v[5] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec6f64_t Vec6f64_CmpGT(vec6f64_t v0, vec6f64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] > v1.v[5] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec6f64_t Vec6f64_CmpGE(vec6f64_t v0, vec6f64_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] >= v1.v[5] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec6f64_t Vec6f64_CmpNE(vec6f64_t v0, vec6f64_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] != v1.v[5] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec6f64_t Vec6f64_CmpLTS(vec6f64_t v0, double x)
{
	v0.v[0] = v0.v[0] < x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] < x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] < x ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] < x ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] < x ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] < x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec6f64_t Vec6f64_CmpLES(vec6f64_t v0, double x)
{
	v0.v[0] = v0.v[0] <= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] <= x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec6f64_t Vec6f64_CmpEQS(vec6f64_t v0, double x)
{
	v0.v[0] = v0.v[0] == x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] == x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] == x ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] == x ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] == x ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] == x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec6f64_t Vec6f64_CmpGTS(vec6f64_t v0, double x)
{
	v0.v[0] = v0.v[0] > x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] > x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] > x ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] > x ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] > x ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] > x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec6f64_t Vec6f64_CmpGES(vec6f64_t v0, double x)
{
	v0.v[0] = v0.v[0] >= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] >= x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec6f64_t Vec6f64_CmpNES(vec6f64_t v0, double x)
{
	v0.v[0] = v0.v[0] != x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] != x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] != x ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] != x ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] != x ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] != x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec6f64_t Vec6f64_Sign(vec6f64_t v)
{
	v.v[0] = v.v[0] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;
	v.v[1] = v.v[1] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;
	v.v[2] = v.v[2] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;
	v.v[3] = v.v[3] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;
	v.v[4] = v.v[4] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;
	v.v[5] = v.v[5] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;

	return v;
}
vec6f64_t Vec6f64_SignPosNeg(vec6f64_t v)
{
	v.v[0] = v.v[0] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;
	v.v[1] = v.v[1] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;
	v.v[2] = v.v[2] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;
	v.v[3] = v.v[3] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;
	v.v[4] = v.v[4] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;
	v.v[5] = v.v[5] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;

	return v;
}
vec6f64_t Vec6f64_Zero()
{
	return G_VEC6F64_T_ZERO;
}
vec6f64_t Vec6f64_One()
{
	return G_VEC6F64_T_ONE;
}
vec6f64_t Vec6f64_NegOne()
{
	return Vec6f64_Neg(G_VEC6F64_T_ONE);
}
vec6f64_t Vec6f64_Cross(vec6f64_t v0, vec6f64_t v1, vec6f64_t v2, vec6f64_t v3, vec6f64_t v4)
{
	vec6f64_t v;
	mat6x6f64_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;
	mat.v[5] = v4;

	for (i = 0; i < 6; i++)
		v.v[i] = Mat5x5f64_Det(Mat6x6f64_DeleteRowColumn(mat, 0, i));

	return v;
}
vec6f64_t Vec6f64_Lerp(vec6f64_t v0, vec6f64_t v1, vec6f64_t vt)
{
	vec6f64_t v;

	v.v[0] = (G_F64_ONE - vt.v[0]) * v0.v[0] + v1.v[0] * vt.v[0];
	v.v[1] = (G_F64_ONE - vt.v[1]) * v0.v[1] + v1.v[1] * vt.v[1];
	v.v[2] = (G_F64_ONE - vt.v[2]) * v0.v[2] + v1.v[2] * vt.v[2];
	v.v[3] = (G_F64_ONE - vt.v[3]) * v0.v[3] + v1.v[3] * vt.v[3];
	v.v[4] = (G_F64_ONE - vt.v[4]) * v0.v[4] + v1.v[4] * vt.v[4];
	v.v[5] = (G_F64_ONE - vt.v[5]) * v0.v[5] + v1.v[5] * vt.v[5];

	return v;
}
vec6f64_t Vec6f64_LerpS(vec6f64_t v0, vec6f64_t v1, double t)
{
	vec6f64_t v;

	v.v[0] = (G_F64_ONE - t) * v0.v[0] + v1.v[0] * t;
	v.v[1] = (G_F64_ONE - t) * v0.v[1] + v1.v[1] * t;
	v.v[2] = (G_F64_ONE - t) * v0.v[2] + v1.v[2] * t;
	v.v[3] = (G_F64_ONE - t) * v0.v[3] + v1.v[3] * t;
	v.v[4] = (G_F64_ONE - t) * v0.v[4] + v1.v[4] * t;
	v.v[5] = (G_F64_ONE - t) * v0.v[5] + v1.v[5] * t;

	return v;
}
vec7f64_t Vec6f64_ToVec7f64(vec6f64_t v, double x0)
{
	vec7f64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = v.v[5];
	outv.v[6] = x0;

	return outv;
}
vec8f64_t Vec6f64_ToVec8f64(vec6f64_t v, double x0, double x1)
{
	vec8f64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = v.v[5];
	outv.v[6] = x0;
	outv.v[7] = x1;

	return outv;
}
vec6f32_t Vec6f32_SetComponent(vec6f32_t v, int index, float value)
{
	v.v[index] = value;

	return v;
}
vec6f32_t Vec6f32_Vec(float x0, float x1, float x2, float x3, float x4, float x5)
{
	vec6f32_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;
	v.v[5] = x5;

	return v;
}
vec6f32_t Vec6f32_Add(vec6f32_t v0, vec6f32_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];
	v0.v[5] += v1.v[5];

	return v0;
}
vec6f32_t Vec6f32_Sub(vec6f32_t v0, vec6f32_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];
	v0.v[5] -= v1.v[5];

	return v0;
}
float Vec6f32_GetComponent(vec6f32_t v, int index)
{
	return v.v[index];
}
vec6f32_t Vec6f32_Mul(vec6f32_t v0, vec6f32_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];
	v0.v[5] *= v1.v[5];

	return v0;
}
vec6f32_t Vec6f32_Div(vec6f32_t v0, vec6f32_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];
	v0.v[5] /= v1.v[5];

	return v0;
}
vec6f32_t Vec6f32_Scale(vec6f32_t v, float scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;
	v.v[5] *= scale;

	return v;
}
vec6f32_t Vec6f32_DivScale(vec6f32_t v, float divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;
	v.v[5] /= divscale;

	return v;
}
vec6f32_t Vec6f32_MA(vec6f32_t v, vec6f32_t dir, float scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;
	v.v[5] += dir.v[5] * scale;

	return v;
}
vec6f32_t Vec6f32_DA(vec6f32_t v, vec6f32_t dir, float divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;
	v.v[5] += dir.v[5] / divscale;

	return v;
}
float Vec6f32_Dot(vec6f32_t v0, vec6f32_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4] + v0.v[5] * v1.v[5];
}
float Vec6f32_LenSq(vec6f32_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4] + v.v[5] * v.v[5];
}
float Vec6f32_Len(vec6f32_t v)
{
	return sqrtf(Vec6f32_LenSq(v));
}
vec6f32_t Vec6f32_Normalise(vec6f32_t v)
{
	float lensq = Vec6f32_LenSq(v);

	if (lensq == G_F32_ZERO)
		return v;
	else
		return Vec6f32_Scale(v, G_F32_ONE / sqrtf(lensq));
}
vec6f32_t Vec6f32_Abs(vec6f32_t v)
{
	v.v[0] = fabsf(v.v[0]);
	v.v[1] = fabsf(v.v[1]);
	v.v[2] = fabsf(v.v[2]);
	v.v[3] = fabsf(v.v[3]);
	v.v[4] = fabsf(v.v[4]);
	v.v[5] = fabsf(v.v[5]);

	return v;
}
vec6f32_t Vec6f32_Floor(vec6f32_t v)
{
	v.v[0] = floorf(v.v[0]);
	v.v[1] = floorf(v.v[1]);
	v.v[2] = floorf(v.v[2]);
	v.v[3] = floorf(v.v[3]);
	v.v[4] = floorf(v.v[4]);
	v.v[5] = floorf(v.v[5]);

	return v;
}
vec6f32_t Vec6f32_Ceil(vec6f32_t v)
{
	v.v[0] = ceilf(v.v[0]);
	v.v[1] = ceilf(v.v[1]);
	v.v[2] = ceilf(v.v[2]);
	v.v[3] = ceilf(v.v[3]);
	v.v[4] = ceilf(v.v[4]);
	v.v[5] = ceilf(v.v[5]);

	return v;
}
vec6f32_t Vec6f32_Fract(vec6f32_t v)
{
	return Vec6f32_Sub(v, Vec6f32_Floor(v));
}
vec6f32_t Vec6f32_Mod(vec6f32_t v0, vec6f32_t v1)
{
	v0.v[0] = fmodf(v0.v[0], v1.v[0]);
	v0.v[1] = fmodf(v0.v[1], v1.v[1]);
	v0.v[2] = fmodf(v0.v[2], v1.v[2]);
	v0.v[3] = fmodf(v0.v[3], v1.v[3]);
	v0.v[4] = fmodf(v0.v[4], v1.v[4]);
	v0.v[5] = fmodf(v0.v[5], v1.v[5]);

	return v0;
}
vec6f32_t Vec6f32_ModS(vec6f32_t v0, float x)
{
	v0.v[0] = fmodf(v0.v[0], x);
	v0.v[1] = fmodf(v0.v[1], x);
	v0.v[2] = fmodf(v0.v[2], x);
	v0.v[3] = fmodf(v0.v[3], x);
	v0.v[4] = fmodf(v0.v[4], x);
	v0.v[5] = fmodf(v0.v[5], x);

	return v0;
}
vec6f32_t Vec6f32_Min(vec6f32_t v0, vec6f32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] < v1.v[5] ? v0.v[5] : v1.v[5];

	return v0;
}
vec6f32_t Vec6f32_Max(vec6f32_t v0, vec6f32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] > v1.v[5] ? v0.v[5] : v1.v[5];

	return v0;
}
vec6f32_t Vec6f32_MinS(vec6f32_t v0, float x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] < x ? v0.v[5] : x;

	return v0;
}
vec6f32_t Vec6f32_MaxS(vec6f32_t v0, float x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] > x ? v0.v[5] : x;

	return v0;
}
vec6f32_t Vec6f32_Clamp(vec6f32_t v, vec6f32_t min, vec6f32_t max)
{
	return Vec6f32_Max(Vec6f32_Min(v, max), min);
}
vec6f32_t Vec6f32_ClampS(vec6f32_t v, float min, float max)
{
	return Vec6f32_MaxS(Vec6f32_MinS(v, max), min);
}
vec6f32_t Vec6f32_Neg(vec6f32_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];
	v.v[3] = -v.v[3];
	v.v[4] = -v.v[4];
	v.v[5] = -v.v[5];

	return v;
}
vec6f32_t Vec6f32_Reciprocal(vec6f32_t v)
{
	v.v[0] = G_F32_ONE / v.v[0];
	v.v[1] = G_F32_ONE / v.v[1];
	v.v[2] = G_F32_ONE / v.v[2];
	v.v[3] = G_F32_ONE / v.v[3];
	v.v[4] = G_F32_ONE / v.v[4];
	v.v[5] = G_F32_ONE / v.v[5];

	return v;
}
vec6f32_t Vec6f32_Truncate(vec6f32_t v)
{
	v.v[0] = v.v[0] < G_F32_ZERO ? ceilf(v.v[0]) : floorf(v.v[0]);
	v.v[1] = v.v[1] < G_F32_ZERO ? ceilf(v.v[1]) : floorf(v.v[1]);
	v.v[2] = v.v[2] < G_F32_ZERO ? ceilf(v.v[2]) : floorf(v.v[2]);
	v.v[3] = v.v[3] < G_F32_ZERO ? ceilf(v.v[3]) : floorf(v.v[3]);
	v.v[4] = v.v[4] < G_F32_ZERO ? ceilf(v.v[4]) : floorf(v.v[4]);
	v.v[5] = v.v[5] < G_F32_ZERO ? ceilf(v.v[5]) : floorf(v.v[5]);

	return v;
}
vec6f32_t Vec6f32_TruncateAway(vec6f32_t v)
{
	v.v[0] = v.v[0] < G_F32_ZERO ? floorf(v.v[0]) : ceilf(v.v[0]);
	v.v[1] = v.v[1] < G_F32_ZERO ? floorf(v.v[1]) : ceilf(v.v[1]);
	v.v[2] = v.v[2] < G_F32_ZERO ? floorf(v.v[2]) : ceilf(v.v[2]);
	v.v[3] = v.v[3] < G_F32_ZERO ? floorf(v.v[3]) : ceilf(v.v[3]);
	v.v[4] = v.v[4] < G_F32_ZERO ? floorf(v.v[4]) : ceilf(v.v[4]);
	v.v[5] = v.v[5] < G_F32_ZERO ? floorf(v.v[5]) : ceilf(v.v[5]);

	return v;
}
vec6f32_t Vec6f32_CmpLT(vec6f32_t v0, vec6f32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] < v1.v[5] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec6f32_t Vec6f32_CmpLE(vec6f32_t v0, vec6f32_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] <= v1.v[5] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec6f32_t Vec6f32_CmpEQ(vec6f32_t v0, vec6f32_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] == v1.v[5] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec6f32_t Vec6f32_CmpGT(vec6f32_t v0, vec6f32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] > v1.v[5] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec6f32_t Vec6f32_CmpGE(vec6f32_t v0, vec6f32_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] >= v1.v[5] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec6f32_t Vec6f32_CmpNE(vec6f32_t v0, vec6f32_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] != v1.v[5] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec6f32_t Vec6f32_CmpLTS(vec6f32_t v0, float x)
{
	v0.v[0] = v0.v[0] < x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] < x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] < x ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] < x ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] < x ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] < x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec6f32_t Vec6f32_CmpLES(vec6f32_t v0, float x)
{
	v0.v[0] = v0.v[0] <= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] <= x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec6f32_t Vec6f32_CmpEQS(vec6f32_t v0, float x)
{
	v0.v[0] = v0.v[0] == x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] == x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] == x ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] == x ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] == x ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] == x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec6f32_t Vec6f32_CmpGTS(vec6f32_t v0, float x)
{
	v0.v[0] = v0.v[0] > x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] > x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] > x ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] > x ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] > x ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] > x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec6f32_t Vec6f32_CmpGES(vec6f32_t v0, float x)
{
	v0.v[0] = v0.v[0] >= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] >= x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec6f32_t Vec6f32_CmpNES(vec6f32_t v0, float x)
{
	v0.v[0] = v0.v[0] != x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] != x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] != x ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] != x ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] != x ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] != x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec6f32_t Vec6f32_Sign(vec6f32_t v)
{
	v.v[0] = v.v[0] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;
	v.v[1] = v.v[1] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;
	v.v[2] = v.v[2] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;
	v.v[3] = v.v[3] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;
	v.v[4] = v.v[4] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;
	v.v[5] = v.v[5] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;

	return v;
}
vec6f32_t Vec6f32_SignPosNeg(vec6f32_t v)
{
	v.v[0] = v.v[0] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;
	v.v[1] = v.v[1] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;
	v.v[2] = v.v[2] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;
	v.v[3] = v.v[3] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;
	v.v[4] = v.v[4] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;
	v.v[5] = v.v[5] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;

	return v;
}
vec6f32_t Vec6f32_Zero()
{
	return G_VEC6F32_T_ZERO;
}
vec6f32_t Vec6f32_One()
{
	return G_VEC6F32_T_ONE;
}
vec6f32_t Vec6f32_NegOne()
{
	return Vec6f32_Neg(G_VEC6F32_T_ONE);
}
vec6f32_t Vec6f32_Cross(vec6f32_t v0, vec6f32_t v1, vec6f32_t v2, vec6f32_t v3, vec6f32_t v4)
{
	vec6f32_t v;
	mat6x6f32_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;
	mat.v[5] = v4;

	for (i = 0; i < 6; i++)
		v.v[i] = Mat5x5f32_Det(Mat6x6f32_DeleteRowColumn(mat, 0, i));

	return v;
}
vec6f32_t Vec6f32_Lerp(vec6f32_t v0, vec6f32_t v1, vec6f32_t vt)
{
	vec6f32_t v;

	v.v[0] = (G_F32_ONE - vt.v[0]) * v0.v[0] + v1.v[0] * vt.v[0];
	v.v[1] = (G_F32_ONE - vt.v[1]) * v0.v[1] + v1.v[1] * vt.v[1];
	v.v[2] = (G_F32_ONE - vt.v[2]) * v0.v[2] + v1.v[2] * vt.v[2];
	v.v[3] = (G_F32_ONE - vt.v[3]) * v0.v[3] + v1.v[3] * vt.v[3];
	v.v[4] = (G_F32_ONE - vt.v[4]) * v0.v[4] + v1.v[4] * vt.v[4];
	v.v[5] = (G_F32_ONE - vt.v[5]) * v0.v[5] + v1.v[5] * vt.v[5];

	return v;
}
vec6f32_t Vec6f32_LerpS(vec6f32_t v0, vec6f32_t v1, float t)
{
	vec6f32_t v;

	v.v[0] = (G_F32_ONE - t) * v0.v[0] + v1.v[0] * t;
	v.v[1] = (G_F32_ONE - t) * v0.v[1] + v1.v[1] * t;
	v.v[2] = (G_F32_ONE - t) * v0.v[2] + v1.v[2] * t;
	v.v[3] = (G_F32_ONE - t) * v0.v[3] + v1.v[3] * t;
	v.v[4] = (G_F32_ONE - t) * v0.v[4] + v1.v[4] * t;
	v.v[5] = (G_F32_ONE - t) * v0.v[5] + v1.v[5] * t;

	return v;
}
vec7f32_t Vec6f32_ToVec7f32(vec6f32_t v, float x0)
{
	vec7f32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = v.v[5];
	outv.v[6] = x0;

	return outv;
}
vec8f32_t Vec6f32_ToVec8f32(vec6f32_t v, float x0, float x1)
{
	vec8f32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = v.v[5];
	outv.v[6] = x0;
	outv.v[7] = x1;

	return outv;
}
vec6u64_t Vec6u64_SetComponent(vec6u64_t v, int index, uint64_t value)
{
	v.v[index] = value;

	return v;
}
vec6u64_t Vec6u64_Vec(uint64_t x0, uint64_t x1, uint64_t x2, uint64_t x3, uint64_t x4, uint64_t x5)
{
	vec6u64_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;
	v.v[5] = x5;

	return v;
}
vec6u64_t Vec6u64_Add(vec6u64_t v0, vec6u64_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];
	v0.v[5] += v1.v[5];

	return v0;
}
vec6u64_t Vec6u64_Sub(vec6u64_t v0, vec6u64_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];
	v0.v[5] -= v1.v[5];

	return v0;
}
uint64_t Vec6u64_GetComponent(vec6u64_t v, int index)
{
	return v.v[index];
}
vec6u64_t Vec6u64_Mul(vec6u64_t v0, vec6u64_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];
	v0.v[5] *= v1.v[5];

	return v0;
}
vec6u64_t Vec6u64_Div(vec6u64_t v0, vec6u64_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];
	v0.v[5] /= v1.v[5];

	return v0;
}
vec6u64_t Vec6u64_Scale(vec6u64_t v, uint64_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;
	v.v[5] *= scale;

	return v;
}
vec6u64_t Vec6u64_DivScale(vec6u64_t v, uint64_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;
	v.v[5] /= divscale;

	return v;
}
vec6u64_t Vec6u64_MA(vec6u64_t v, vec6u64_t dir, uint64_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;
	v.v[5] += dir.v[5] * scale;

	return v;
}
vec6u64_t Vec6u64_DA(vec6u64_t v, vec6u64_t dir, uint64_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;
	v.v[5] += dir.v[5] / divscale;

	return v;
}
uint64_t Vec6u64_Dot(vec6u64_t v0, vec6u64_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4] + v0.v[5] * v1.v[5];
}
uint64_t Vec6u64_LenSq(vec6u64_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4] + v.v[5] * v.v[5];
}
uint64_t Vec6u64_Len(vec6u64_t v)
{
	return sqrt(Vec6u64_LenSq(v));
}
vec6u64_t Vec6u64_Mod(vec6u64_t v0, vec6u64_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);
	v0.v[4] = (v0.v[4] % v1.v[4]);
	v0.v[5] = (v0.v[5] % v1.v[5]);

	return v0;
}
vec6u64_t Vec6u64_ModS(vec6u64_t v0, uint64_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);
	v0.v[4] = (v0.v[4] % x);
	v0.v[5] = (v0.v[5] % x);

	return v0;
}
vec6u64_t Vec6u64_Min(vec6u64_t v0, vec6u64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] < v1.v[5] ? v0.v[5] : v1.v[5];

	return v0;
}
vec6u64_t Vec6u64_Max(vec6u64_t v0, vec6u64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] > v1.v[5] ? v0.v[5] : v1.v[5];

	return v0;
}
vec6u64_t Vec6u64_MinS(vec6u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] < x ? v0.v[5] : x;

	return v0;
}
vec6u64_t Vec6u64_MaxS(vec6u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] > x ? v0.v[5] : x;

	return v0;
}
vec6u64_t Vec6u64_Clamp(vec6u64_t v, vec6u64_t min, vec6u64_t max)
{
	return Vec6u64_Max(Vec6u64_Min(v, max), min);
}
vec6u64_t Vec6u64_ClampS(vec6u64_t v, uint64_t min, uint64_t max)
{
	return Vec6u64_MaxS(Vec6u64_MinS(v, max), min);
}
vec6u64_t Vec6u64_CmpLT(vec6u64_t v0, vec6u64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] < v1.v[5] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec6u64_t Vec6u64_CmpLE(vec6u64_t v0, vec6u64_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] <= v1.v[5] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec6u64_t Vec6u64_CmpEQ(vec6u64_t v0, vec6u64_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] == v1.v[5] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec6u64_t Vec6u64_CmpGT(vec6u64_t v0, vec6u64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] > v1.v[5] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec6u64_t Vec6u64_CmpGE(vec6u64_t v0, vec6u64_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] >= v1.v[5] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec6u64_t Vec6u64_CmpNE(vec6u64_t v0, vec6u64_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] != v1.v[5] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec6u64_t Vec6u64_CmpLTS(vec6u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] < x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] < x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] < x ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] < x ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] < x ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] < x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec6u64_t Vec6u64_CmpLES(vec6u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] <= x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec6u64_t Vec6u64_CmpEQS(vec6u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] == x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] == x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] == x ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] == x ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] == x ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] == x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec6u64_t Vec6u64_CmpGTS(vec6u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] > x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] > x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] > x ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] > x ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] > x ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] > x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec6u64_t Vec6u64_CmpGES(vec6u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] >= x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec6u64_t Vec6u64_CmpNES(vec6u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] != x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] != x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] != x ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] != x ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] != x ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] != x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec6u64_t Vec6u64_Sign(vec6u64_t v)
{
	v.v[0] = v.v[0] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;
	v.v[1] = v.v[1] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;
	v.v[2] = v.v[2] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;
	v.v[3] = v.v[3] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;
	v.v[4] = v.v[4] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;
	v.v[5] = v.v[5] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;

	return v;
}
vec6u64_t Vec6u64_SignPosNeg(vec6u64_t v)
{
	v.v[0] = v.v[0] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;
	v.v[1] = v.v[1] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;
	v.v[2] = v.v[2] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;
	v.v[3] = v.v[3] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;
	v.v[4] = v.v[4] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;
	v.v[5] = v.v[5] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;

	return v;
}
vec6u64_t Vec6u64_Zero()
{
	return G_VEC6U64_T_ZERO;
}
vec6u64_t Vec6u64_One()
{
	return G_VEC6U64_T_ONE;
}
vec6u64_t Vec6u64_Cross(vec6u64_t v0, vec6u64_t v1, vec6u64_t v2, vec6u64_t v3, vec6u64_t v4)
{
	vec6u64_t v;
	mat6x6u64_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;
	mat.v[5] = v4;

	for (i = 0; i < 6; i++)
		v.v[i] = Mat5x5u64_Det(Mat6x6u64_DeleteRowColumn(mat, 0, i));

	return v;
}
vec7u64_t Vec6u64_ToVec7u64(vec6u64_t v, uint64_t x0)
{
	vec7u64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = v.v[5];
	outv.v[6] = x0;

	return outv;
}
vec8u64_t Vec6u64_ToVec8u64(vec6u64_t v, uint64_t x0, uint64_t x1)
{
	vec8u64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = v.v[5];
	outv.v[6] = x0;
	outv.v[7] = x1;

	return outv;
}
vec6i64_t Vec6i64_SetComponent(vec6i64_t v, int index, int64_t value)
{
	v.v[index] = value;

	return v;
}
vec6i64_t Vec6i64_Vec(int64_t x0, int64_t x1, int64_t x2, int64_t x3, int64_t x4, int64_t x5)
{
	vec6i64_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;
	v.v[5] = x5;

	return v;
}
vec6i64_t Vec6i64_Add(vec6i64_t v0, vec6i64_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];
	v0.v[5] += v1.v[5];

	return v0;
}
vec6i64_t Vec6i64_Sub(vec6i64_t v0, vec6i64_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];
	v0.v[5] -= v1.v[5];

	return v0;
}
int64_t Vec6i64_GetComponent(vec6i64_t v, int index)
{
	return v.v[index];
}
vec6i64_t Vec6i64_Mul(vec6i64_t v0, vec6i64_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];
	v0.v[5] *= v1.v[5];

	return v0;
}
vec6i64_t Vec6i64_Div(vec6i64_t v0, vec6i64_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];
	v0.v[5] /= v1.v[5];

	return v0;
}
vec6i64_t Vec6i64_Scale(vec6i64_t v, int64_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;
	v.v[5] *= scale;

	return v;
}
vec6i64_t Vec6i64_DivScale(vec6i64_t v, int64_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;
	v.v[5] /= divscale;

	return v;
}
vec6i64_t Vec6i64_MA(vec6i64_t v, vec6i64_t dir, int64_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;
	v.v[5] += dir.v[5] * scale;

	return v;
}
vec6i64_t Vec6i64_DA(vec6i64_t v, vec6i64_t dir, int64_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;
	v.v[5] += dir.v[5] / divscale;

	return v;
}
int64_t Vec6i64_Dot(vec6i64_t v0, vec6i64_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4] + v0.v[5] * v1.v[5];
}
int64_t Vec6i64_LenSq(vec6i64_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4] + v.v[5] * v.v[5];
}
int64_t Vec6i64_Len(vec6i64_t v)
{
	return sqrt(Vec6i64_LenSq(v));
}
vec6i64_t Vec6i64_Abs(vec6i64_t v)
{
	v.v[0] = (v.v[0] < 0 ? -v.v[0] : v.v[0]);
	v.v[1] = (v.v[1] < 0 ? -v.v[1] : v.v[1]);
	v.v[2] = (v.v[2] < 0 ? -v.v[2] : v.v[2]);
	v.v[3] = (v.v[3] < 0 ? -v.v[3] : v.v[3]);
	v.v[4] = (v.v[4] < 0 ? -v.v[4] : v.v[4]);
	v.v[5] = (v.v[5] < 0 ? -v.v[5] : v.v[5]);

	return v;
}
vec6i64_t Vec6i64_Mod(vec6i64_t v0, vec6i64_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);
	v0.v[4] = (v0.v[4] % v1.v[4]);
	v0.v[5] = (v0.v[5] % v1.v[5]);

	return v0;
}
vec6i64_t Vec6i64_ModS(vec6i64_t v0, int64_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);
	v0.v[4] = (v0.v[4] % x);
	v0.v[5] = (v0.v[5] % x);

	return v0;
}
vec6i64_t Vec6i64_Min(vec6i64_t v0, vec6i64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] < v1.v[5] ? v0.v[5] : v1.v[5];

	return v0;
}
vec6i64_t Vec6i64_Max(vec6i64_t v0, vec6i64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] > v1.v[5] ? v0.v[5] : v1.v[5];

	return v0;
}
vec6i64_t Vec6i64_MinS(vec6i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] < x ? v0.v[5] : x;

	return v0;
}
vec6i64_t Vec6i64_MaxS(vec6i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] > x ? v0.v[5] : x;

	return v0;
}
vec6i64_t Vec6i64_Clamp(vec6i64_t v, vec6i64_t min, vec6i64_t max)
{
	return Vec6i64_Max(Vec6i64_Min(v, max), min);
}
vec6i64_t Vec6i64_ClampS(vec6i64_t v, int64_t min, int64_t max)
{
	return Vec6i64_MaxS(Vec6i64_MinS(v, max), min);
}
vec6i64_t Vec6i64_Neg(vec6i64_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];
	v.v[3] = -v.v[3];
	v.v[4] = -v.v[4];
	v.v[5] = -v.v[5];

	return v;
}
vec6i64_t Vec6i64_CmpLT(vec6i64_t v0, vec6i64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] < v1.v[5] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec6i64_t Vec6i64_CmpLE(vec6i64_t v0, vec6i64_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] <= v1.v[5] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec6i64_t Vec6i64_CmpEQ(vec6i64_t v0, vec6i64_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] == v1.v[5] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec6i64_t Vec6i64_CmpGT(vec6i64_t v0, vec6i64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] > v1.v[5] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec6i64_t Vec6i64_CmpGE(vec6i64_t v0, vec6i64_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] >= v1.v[5] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec6i64_t Vec6i64_CmpNE(vec6i64_t v0, vec6i64_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] != v1.v[5] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec6i64_t Vec6i64_CmpLTS(vec6i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] < x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] < x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] < x ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] < x ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] < x ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] < x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec6i64_t Vec6i64_CmpLES(vec6i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] <= x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec6i64_t Vec6i64_CmpEQS(vec6i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] == x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] == x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] == x ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] == x ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] == x ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] == x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec6i64_t Vec6i64_CmpGTS(vec6i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] > x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] > x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] > x ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] > x ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] > x ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] > x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec6i64_t Vec6i64_CmpGES(vec6i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] >= x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec6i64_t Vec6i64_CmpNES(vec6i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] != x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] != x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] != x ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] != x ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] != x ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] != x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec6i64_t Vec6i64_Sign(vec6i64_t v)
{
	v.v[0] = v.v[0] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;
	v.v[1] = v.v[1] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;
	v.v[2] = v.v[2] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;
	v.v[3] = v.v[3] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;
	v.v[4] = v.v[4] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;
	v.v[5] = v.v[5] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;

	return v;
}
vec6i64_t Vec6i64_SignPosNeg(vec6i64_t v)
{
	v.v[0] = v.v[0] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;
	v.v[1] = v.v[1] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;
	v.v[2] = v.v[2] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;
	v.v[3] = v.v[3] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;
	v.v[4] = v.v[4] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;
	v.v[5] = v.v[5] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;

	return v;
}
vec6i64_t Vec6i64_Zero()
{
	return G_VEC6I64_T_ZERO;
}
vec6i64_t Vec6i64_One()
{
	return G_VEC6I64_T_ONE;
}
vec6i64_t Vec6i64_NegOne()
{
	return Vec6i64_Neg(G_VEC6I64_T_ONE);
}
vec6i64_t Vec6i64_Cross(vec6i64_t v0, vec6i64_t v1, vec6i64_t v2, vec6i64_t v3, vec6i64_t v4)
{
	vec6i64_t v;
	mat6x6i64_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;
	mat.v[5] = v4;

	for (i = 0; i < 6; i++)
		v.v[i] = Mat5x5i64_Det(Mat6x6i64_DeleteRowColumn(mat, 0, i));

	return v;
}
vec7i64_t Vec6i64_ToVec7i64(vec6i64_t v, int64_t x0)
{
	vec7i64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = v.v[5];
	outv.v[6] = x0;

	return outv;
}
vec8i64_t Vec6i64_ToVec8i64(vec6i64_t v, int64_t x0, int64_t x1)
{
	vec8i64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = v.v[5];
	outv.v[6] = x0;
	outv.v[7] = x1;

	return outv;
}
vec6u32_t Vec6u32_SetComponent(vec6u32_t v, int index, uint32_t value)
{
	v.v[index] = value;

	return v;
}
vec6u32_t Vec6u32_Vec(uint32_t x0, uint32_t x1, uint32_t x2, uint32_t x3, uint32_t x4, uint32_t x5)
{
	vec6u32_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;
	v.v[5] = x5;

	return v;
}
vec6u32_t Vec6u32_Add(vec6u32_t v0, vec6u32_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];
	v0.v[5] += v1.v[5];

	return v0;
}
vec6u32_t Vec6u32_Sub(vec6u32_t v0, vec6u32_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];
	v0.v[5] -= v1.v[5];

	return v0;
}
uint32_t Vec6u32_GetComponent(vec6u32_t v, int index)
{
	return v.v[index];
}
vec6u32_t Vec6u32_Mul(vec6u32_t v0, vec6u32_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];
	v0.v[5] *= v1.v[5];

	return v0;
}
vec6u32_t Vec6u32_Div(vec6u32_t v0, vec6u32_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];
	v0.v[5] /= v1.v[5];

	return v0;
}
vec6u32_t Vec6u32_Scale(vec6u32_t v, uint32_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;
	v.v[5] *= scale;

	return v;
}
vec6u32_t Vec6u32_DivScale(vec6u32_t v, uint32_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;
	v.v[5] /= divscale;

	return v;
}
vec6u32_t Vec6u32_MA(vec6u32_t v, vec6u32_t dir, uint32_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;
	v.v[5] += dir.v[5] * scale;

	return v;
}
vec6u32_t Vec6u32_DA(vec6u32_t v, vec6u32_t dir, uint32_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;
	v.v[5] += dir.v[5] / divscale;

	return v;
}
uint32_t Vec6u32_Dot(vec6u32_t v0, vec6u32_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4] + v0.v[5] * v1.v[5];
}
uint32_t Vec6u32_LenSq(vec6u32_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4] + v.v[5] * v.v[5];
}
uint32_t Vec6u32_Len(vec6u32_t v)
{
	return sqrtf(Vec6u32_LenSq(v));
}
vec6u32_t Vec6u32_Mod(vec6u32_t v0, vec6u32_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);
	v0.v[4] = (v0.v[4] % v1.v[4]);
	v0.v[5] = (v0.v[5] % v1.v[5]);

	return v0;
}
vec6u32_t Vec6u32_ModS(vec6u32_t v0, uint32_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);
	v0.v[4] = (v0.v[4] % x);
	v0.v[5] = (v0.v[5] % x);

	return v0;
}
vec6u32_t Vec6u32_Min(vec6u32_t v0, vec6u32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] < v1.v[5] ? v0.v[5] : v1.v[5];

	return v0;
}
vec6u32_t Vec6u32_Max(vec6u32_t v0, vec6u32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] > v1.v[5] ? v0.v[5] : v1.v[5];

	return v0;
}
vec6u32_t Vec6u32_MinS(vec6u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] < x ? v0.v[5] : x;

	return v0;
}
vec6u32_t Vec6u32_MaxS(vec6u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] > x ? v0.v[5] : x;

	return v0;
}
vec6u32_t Vec6u32_Clamp(vec6u32_t v, vec6u32_t min, vec6u32_t max)
{
	return Vec6u32_Max(Vec6u32_Min(v, max), min);
}
vec6u32_t Vec6u32_ClampS(vec6u32_t v, uint32_t min, uint32_t max)
{
	return Vec6u32_MaxS(Vec6u32_MinS(v, max), min);
}
vec6u32_t Vec6u32_CmpLT(vec6u32_t v0, vec6u32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] < v1.v[5] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec6u32_t Vec6u32_CmpLE(vec6u32_t v0, vec6u32_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] <= v1.v[5] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec6u32_t Vec6u32_CmpEQ(vec6u32_t v0, vec6u32_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] == v1.v[5] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec6u32_t Vec6u32_CmpGT(vec6u32_t v0, vec6u32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] > v1.v[5] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec6u32_t Vec6u32_CmpGE(vec6u32_t v0, vec6u32_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] >= v1.v[5] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec6u32_t Vec6u32_CmpNE(vec6u32_t v0, vec6u32_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] != v1.v[5] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec6u32_t Vec6u32_CmpLTS(vec6u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] < x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] < x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] < x ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] < x ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] < x ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] < x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec6u32_t Vec6u32_CmpLES(vec6u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] <= x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec6u32_t Vec6u32_CmpEQS(vec6u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] == x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] == x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] == x ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] == x ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] == x ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] == x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec6u32_t Vec6u32_CmpGTS(vec6u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] > x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] > x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] > x ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] > x ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] > x ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] > x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec6u32_t Vec6u32_CmpGES(vec6u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] >= x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec6u32_t Vec6u32_CmpNES(vec6u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] != x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] != x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] != x ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] != x ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] != x ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] != x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec6u32_t Vec6u32_Sign(vec6u32_t v)
{
	v.v[0] = v.v[0] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;
	v.v[1] = v.v[1] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;
	v.v[2] = v.v[2] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;
	v.v[3] = v.v[3] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;
	v.v[4] = v.v[4] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;
	v.v[5] = v.v[5] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;

	return v;
}
vec6u32_t Vec6u32_SignPosNeg(vec6u32_t v)
{
	v.v[0] = v.v[0] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;
	v.v[1] = v.v[1] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;
	v.v[2] = v.v[2] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;
	v.v[3] = v.v[3] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;
	v.v[4] = v.v[4] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;
	v.v[5] = v.v[5] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;

	return v;
}
vec6u32_t Vec6u32_Zero()
{
	return G_VEC6U32_T_ZERO;
}
vec6u32_t Vec6u32_One()
{
	return G_VEC6U32_T_ONE;
}
vec6u32_t Vec6u32_Cross(vec6u32_t v0, vec6u32_t v1, vec6u32_t v2, vec6u32_t v3, vec6u32_t v4)
{
	vec6u32_t v;
	mat6x6u32_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;
	mat.v[5] = v4;

	for (i = 0; i < 6; i++)
		v.v[i] = Mat5x5u32_Det(Mat6x6u32_DeleteRowColumn(mat, 0, i));

	return v;
}
vec7u32_t Vec6u32_ToVec7u32(vec6u32_t v, uint32_t x0)
{
	vec7u32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = v.v[5];
	outv.v[6] = x0;

	return outv;
}
vec8u32_t Vec6u32_ToVec8u32(vec6u32_t v, uint32_t x0, uint32_t x1)
{
	vec8u32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = v.v[5];
	outv.v[6] = x0;
	outv.v[7] = x1;

	return outv;
}
vec6i32_t Vec6i32_SetComponent(vec6i32_t v, int index, int32_t value)
{
	v.v[index] = value;

	return v;
}
vec6i32_t Vec6i32_Vec(int32_t x0, int32_t x1, int32_t x2, int32_t x3, int32_t x4, int32_t x5)
{
	vec6i32_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;
	v.v[5] = x5;

	return v;
}
vec6i32_t Vec6i32_Add(vec6i32_t v0, vec6i32_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];
	v0.v[5] += v1.v[5];

	return v0;
}
vec6i32_t Vec6i32_Sub(vec6i32_t v0, vec6i32_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];
	v0.v[5] -= v1.v[5];

	return v0;
}
int32_t Vec6i32_GetComponent(vec6i32_t v, int index)
{
	return v.v[index];
}
vec6i32_t Vec6i32_Mul(vec6i32_t v0, vec6i32_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];
	v0.v[5] *= v1.v[5];

	return v0;
}
vec6i32_t Vec6i32_Div(vec6i32_t v0, vec6i32_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];
	v0.v[5] /= v1.v[5];

	return v0;
}
vec6i32_t Vec6i32_Scale(vec6i32_t v, int32_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;
	v.v[5] *= scale;

	return v;
}
vec6i32_t Vec6i32_DivScale(vec6i32_t v, int32_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;
	v.v[5] /= divscale;

	return v;
}
vec6i32_t Vec6i32_MA(vec6i32_t v, vec6i32_t dir, int32_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;
	v.v[5] += dir.v[5] * scale;

	return v;
}
vec6i32_t Vec6i32_DA(vec6i32_t v, vec6i32_t dir, int32_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;
	v.v[5] += dir.v[5] / divscale;

	return v;
}
int32_t Vec6i32_Dot(vec6i32_t v0, vec6i32_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4] + v0.v[5] * v1.v[5];
}
int32_t Vec6i32_LenSq(vec6i32_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4] + v.v[5] * v.v[5];
}
int32_t Vec6i32_Len(vec6i32_t v)
{
	return sqrtf(Vec6i32_LenSq(v));
}
vec6i32_t Vec6i32_Abs(vec6i32_t v)
{
	v.v[0] = (v.v[0] < 0 ? -v.v[0] : v.v[0]);
	v.v[1] = (v.v[1] < 0 ? -v.v[1] : v.v[1]);
	v.v[2] = (v.v[2] < 0 ? -v.v[2] : v.v[2]);
	v.v[3] = (v.v[3] < 0 ? -v.v[3] : v.v[3]);
	v.v[4] = (v.v[4] < 0 ? -v.v[4] : v.v[4]);
	v.v[5] = (v.v[5] < 0 ? -v.v[5] : v.v[5]);

	return v;
}
vec6i32_t Vec6i32_Mod(vec6i32_t v0, vec6i32_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);
	v0.v[4] = (v0.v[4] % v1.v[4]);
	v0.v[5] = (v0.v[5] % v1.v[5]);

	return v0;
}
vec6i32_t Vec6i32_ModS(vec6i32_t v0, int32_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);
	v0.v[4] = (v0.v[4] % x);
	v0.v[5] = (v0.v[5] % x);

	return v0;
}
vec6i32_t Vec6i32_Min(vec6i32_t v0, vec6i32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] < v1.v[5] ? v0.v[5] : v1.v[5];

	return v0;
}
vec6i32_t Vec6i32_Max(vec6i32_t v0, vec6i32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] > v1.v[5] ? v0.v[5] : v1.v[5];

	return v0;
}
vec6i32_t Vec6i32_MinS(vec6i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] < x ? v0.v[5] : x;

	return v0;
}
vec6i32_t Vec6i32_MaxS(vec6i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] > x ? v0.v[5] : x;

	return v0;
}
vec6i32_t Vec6i32_Clamp(vec6i32_t v, vec6i32_t min, vec6i32_t max)
{
	return Vec6i32_Max(Vec6i32_Min(v, max), min);
}
vec6i32_t Vec6i32_ClampS(vec6i32_t v, int32_t min, int32_t max)
{
	return Vec6i32_MaxS(Vec6i32_MinS(v, max), min);
}
vec6i32_t Vec6i32_Neg(vec6i32_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];
	v.v[3] = -v.v[3];
	v.v[4] = -v.v[4];
	v.v[5] = -v.v[5];

	return v;
}
vec6i32_t Vec6i32_CmpLT(vec6i32_t v0, vec6i32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] < v1.v[5] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec6i32_t Vec6i32_CmpLE(vec6i32_t v0, vec6i32_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] <= v1.v[5] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec6i32_t Vec6i32_CmpEQ(vec6i32_t v0, vec6i32_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] == v1.v[5] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec6i32_t Vec6i32_CmpGT(vec6i32_t v0, vec6i32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] > v1.v[5] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec6i32_t Vec6i32_CmpGE(vec6i32_t v0, vec6i32_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] >= v1.v[5] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec6i32_t Vec6i32_CmpNE(vec6i32_t v0, vec6i32_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] != v1.v[5] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec6i32_t Vec6i32_CmpLTS(vec6i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] < x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] < x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] < x ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] < x ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] < x ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] < x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec6i32_t Vec6i32_CmpLES(vec6i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] <= x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec6i32_t Vec6i32_CmpEQS(vec6i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] == x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] == x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] == x ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] == x ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] == x ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] == x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec6i32_t Vec6i32_CmpGTS(vec6i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] > x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] > x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] > x ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] > x ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] > x ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] > x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec6i32_t Vec6i32_CmpGES(vec6i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] >= x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec6i32_t Vec6i32_CmpNES(vec6i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] != x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] != x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] != x ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] != x ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] != x ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] != x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec6i32_t Vec6i32_Sign(vec6i32_t v)
{
	v.v[0] = v.v[0] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;
	v.v[1] = v.v[1] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;
	v.v[2] = v.v[2] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;
	v.v[3] = v.v[3] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;
	v.v[4] = v.v[4] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;
	v.v[5] = v.v[5] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;

	return v;
}
vec6i32_t Vec6i32_SignPosNeg(vec6i32_t v)
{
	v.v[0] = v.v[0] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;
	v.v[1] = v.v[1] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;
	v.v[2] = v.v[2] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;
	v.v[3] = v.v[3] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;
	v.v[4] = v.v[4] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;
	v.v[5] = v.v[5] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;

	return v;
}
vec6i32_t Vec6i32_Zero()
{
	return G_VEC6I32_T_ZERO;
}
vec6i32_t Vec6i32_One()
{
	return G_VEC6I32_T_ONE;
}
vec6i32_t Vec6i32_NegOne()
{
	return Vec6i32_Neg(G_VEC6I32_T_ONE);
}
vec6i32_t Vec6i32_Cross(vec6i32_t v0, vec6i32_t v1, vec6i32_t v2, vec6i32_t v3, vec6i32_t v4)
{
	vec6i32_t v;
	mat6x6i32_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;
	mat.v[5] = v4;

	for (i = 0; i < 6; i++)
		v.v[i] = Mat5x5i32_Det(Mat6x6i32_DeleteRowColumn(mat, 0, i));

	return v;
}
vec7i32_t Vec6i32_ToVec7i32(vec6i32_t v, int32_t x0)
{
	vec7i32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = v.v[5];
	outv.v[6] = x0;

	return outv;
}
vec8i32_t Vec6i32_ToVec8i32(vec6i32_t v, int32_t x0, int32_t x1)
{
	vec8i32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = v.v[5];
	outv.v[6] = x0;
	outv.v[7] = x1;

	return outv;
}
vec6u16_t Vec6u16_SetComponent(vec6u16_t v, int index, uint16_t value)
{
	v.v[index] = value;

	return v;
}
vec6u16_t Vec6u16_Vec(uint16_t x0, uint16_t x1, uint16_t x2, uint16_t x3, uint16_t x4, uint16_t x5)
{
	vec6u16_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;
	v.v[5] = x5;

	return v;
}
vec6u16_t Vec6u16_Add(vec6u16_t v0, vec6u16_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];
	v0.v[5] += v1.v[5];

	return v0;
}
vec6u16_t Vec6u16_Sub(vec6u16_t v0, vec6u16_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];
	v0.v[5] -= v1.v[5];

	return v0;
}
uint16_t Vec6u16_GetComponent(vec6u16_t v, int index)
{
	return v.v[index];
}
vec6u16_t Vec6u16_Mul(vec6u16_t v0, vec6u16_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];
	v0.v[5] *= v1.v[5];

	return v0;
}
vec6u16_t Vec6u16_Div(vec6u16_t v0, vec6u16_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];
	v0.v[5] /= v1.v[5];

	return v0;
}
vec6u16_t Vec6u16_Scale(vec6u16_t v, uint16_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;
	v.v[5] *= scale;

	return v;
}
vec6u16_t Vec6u16_DivScale(vec6u16_t v, uint16_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;
	v.v[5] /= divscale;

	return v;
}
vec6u16_t Vec6u16_MA(vec6u16_t v, vec6u16_t dir, uint16_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;
	v.v[5] += dir.v[5] * scale;

	return v;
}
vec6u16_t Vec6u16_DA(vec6u16_t v, vec6u16_t dir, uint16_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;
	v.v[5] += dir.v[5] / divscale;

	return v;
}
uint16_t Vec6u16_Dot(vec6u16_t v0, vec6u16_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4] + v0.v[5] * v1.v[5];
}
uint16_t Vec6u16_LenSq(vec6u16_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4] + v.v[5] * v.v[5];
}
uint16_t Vec6u16_Len(vec6u16_t v)
{
	return sqrtf(Vec6u16_LenSq(v));
}
vec6u16_t Vec6u16_Mod(vec6u16_t v0, vec6u16_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);
	v0.v[4] = (v0.v[4] % v1.v[4]);
	v0.v[5] = (v0.v[5] % v1.v[5]);

	return v0;
}
vec6u16_t Vec6u16_ModS(vec6u16_t v0, uint16_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);
	v0.v[4] = (v0.v[4] % x);
	v0.v[5] = (v0.v[5] % x);

	return v0;
}
vec6u16_t Vec6u16_Min(vec6u16_t v0, vec6u16_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] < v1.v[5] ? v0.v[5] : v1.v[5];

	return v0;
}
vec6u16_t Vec6u16_Max(vec6u16_t v0, vec6u16_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] > v1.v[5] ? v0.v[5] : v1.v[5];

	return v0;
}
vec6u16_t Vec6u16_MinS(vec6u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] < x ? v0.v[5] : x;

	return v0;
}
vec6u16_t Vec6u16_MaxS(vec6u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] > x ? v0.v[5] : x;

	return v0;
}
vec6u16_t Vec6u16_Clamp(vec6u16_t v, vec6u16_t min, vec6u16_t max)
{
	return Vec6u16_Max(Vec6u16_Min(v, max), min);
}
vec6u16_t Vec6u16_ClampS(vec6u16_t v, uint16_t min, uint16_t max)
{
	return Vec6u16_MaxS(Vec6u16_MinS(v, max), min);
}
vec6u16_t Vec6u16_CmpLT(vec6u16_t v0, vec6u16_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] < v1.v[5] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec6u16_t Vec6u16_CmpLE(vec6u16_t v0, vec6u16_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] <= v1.v[5] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec6u16_t Vec6u16_CmpEQ(vec6u16_t v0, vec6u16_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] == v1.v[5] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec6u16_t Vec6u16_CmpGT(vec6u16_t v0, vec6u16_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] > v1.v[5] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec6u16_t Vec6u16_CmpGE(vec6u16_t v0, vec6u16_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] >= v1.v[5] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec6u16_t Vec6u16_CmpNE(vec6u16_t v0, vec6u16_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] != v1.v[5] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec6u16_t Vec6u16_CmpLTS(vec6u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] < x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] < x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] < x ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] < x ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] < x ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] < x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec6u16_t Vec6u16_CmpLES(vec6u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] <= x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec6u16_t Vec6u16_CmpEQS(vec6u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] == x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] == x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] == x ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] == x ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] == x ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] == x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec6u16_t Vec6u16_CmpGTS(vec6u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] > x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] > x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] > x ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] > x ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] > x ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] > x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec6u16_t Vec6u16_CmpGES(vec6u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] >= x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec6u16_t Vec6u16_CmpNES(vec6u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] != x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] != x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] != x ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] != x ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] != x ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] != x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec6u16_t Vec6u16_Sign(vec6u16_t v)
{
	v.v[0] = v.v[0] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;
	v.v[1] = v.v[1] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;
	v.v[2] = v.v[2] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;
	v.v[3] = v.v[3] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;
	v.v[4] = v.v[4] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;
	v.v[5] = v.v[5] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;

	return v;
}
vec6u16_t Vec6u16_SignPosNeg(vec6u16_t v)
{
	v.v[0] = v.v[0] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;
	v.v[1] = v.v[1] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;
	v.v[2] = v.v[2] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;
	v.v[3] = v.v[3] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;
	v.v[4] = v.v[4] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;
	v.v[5] = v.v[5] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;

	return v;
}
vec6u16_t Vec6u16_Zero()
{
	return G_VEC6U16_T_ZERO;
}
vec6u16_t Vec6u16_One()
{
	return G_VEC6U16_T_ONE;
}
vec6u16_t Vec6u16_Cross(vec6u16_t v0, vec6u16_t v1, vec6u16_t v2, vec6u16_t v3, vec6u16_t v4)
{
	vec6u16_t v;
	mat6x6u16_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;
	mat.v[5] = v4;

	for (i = 0; i < 6; i++)
		v.v[i] = Mat5x5u16_Det(Mat6x6u16_DeleteRowColumn(mat, 0, i));

	return v;
}
vec7u16_t Vec6u16_ToVec7u16(vec6u16_t v, uint16_t x0)
{
	vec7u16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = v.v[5];
	outv.v[6] = x0;

	return outv;
}
vec8u16_t Vec6u16_ToVec8u16(vec6u16_t v, uint16_t x0, uint16_t x1)
{
	vec8u16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = v.v[5];
	outv.v[6] = x0;
	outv.v[7] = x1;

	return outv;
}
vec6i16_t Vec6i16_SetComponent(vec6i16_t v, int index, int16_t value)
{
	v.v[index] = value;

	return v;
}
vec6i16_t Vec6i16_Vec(int16_t x0, int16_t x1, int16_t x2, int16_t x3, int16_t x4, int16_t x5)
{
	vec6i16_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;
	v.v[5] = x5;

	return v;
}
vec6i16_t Vec6i16_Add(vec6i16_t v0, vec6i16_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];
	v0.v[5] += v1.v[5];

	return v0;
}
vec6i16_t Vec6i16_Sub(vec6i16_t v0, vec6i16_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];
	v0.v[5] -= v1.v[5];

	return v0;
}
int16_t Vec6i16_GetComponent(vec6i16_t v, int index)
{
	return v.v[index];
}
vec6i16_t Vec6i16_Mul(vec6i16_t v0, vec6i16_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];
	v0.v[5] *= v1.v[5];

	return v0;
}
vec6i16_t Vec6i16_Div(vec6i16_t v0, vec6i16_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];
	v0.v[5] /= v1.v[5];

	return v0;
}
vec6i16_t Vec6i16_Scale(vec6i16_t v, int16_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;
	v.v[5] *= scale;

	return v;
}
vec6i16_t Vec6i16_DivScale(vec6i16_t v, int16_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;
	v.v[5] /= divscale;

	return v;
}
vec6i16_t Vec6i16_MA(vec6i16_t v, vec6i16_t dir, int16_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;
	v.v[5] += dir.v[5] * scale;

	return v;
}
vec6i16_t Vec6i16_DA(vec6i16_t v, vec6i16_t dir, int16_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;
	v.v[5] += dir.v[5] / divscale;

	return v;
}
int16_t Vec6i16_Dot(vec6i16_t v0, vec6i16_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4] + v0.v[5] * v1.v[5];
}
int16_t Vec6i16_LenSq(vec6i16_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4] + v.v[5] * v.v[5];
}
int16_t Vec6i16_Len(vec6i16_t v)
{
	return sqrtf(Vec6i16_LenSq(v));
}
vec6i16_t Vec6i16_Abs(vec6i16_t v)
{
	v.v[0] = (v.v[0] < 0 ? -v.v[0] : v.v[0]);
	v.v[1] = (v.v[1] < 0 ? -v.v[1] : v.v[1]);
	v.v[2] = (v.v[2] < 0 ? -v.v[2] : v.v[2]);
	v.v[3] = (v.v[3] < 0 ? -v.v[3] : v.v[3]);
	v.v[4] = (v.v[4] < 0 ? -v.v[4] : v.v[4]);
	v.v[5] = (v.v[5] < 0 ? -v.v[5] : v.v[5]);

	return v;
}
vec6i16_t Vec6i16_Mod(vec6i16_t v0, vec6i16_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);
	v0.v[4] = (v0.v[4] % v1.v[4]);
	v0.v[5] = (v0.v[5] % v1.v[5]);

	return v0;
}
vec6i16_t Vec6i16_ModS(vec6i16_t v0, int16_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);
	v0.v[4] = (v0.v[4] % x);
	v0.v[5] = (v0.v[5] % x);

	return v0;
}
vec6i16_t Vec6i16_Min(vec6i16_t v0, vec6i16_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] < v1.v[5] ? v0.v[5] : v1.v[5];

	return v0;
}
vec6i16_t Vec6i16_Max(vec6i16_t v0, vec6i16_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] > v1.v[5] ? v0.v[5] : v1.v[5];

	return v0;
}
vec6i16_t Vec6i16_MinS(vec6i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] < x ? v0.v[5] : x;

	return v0;
}
vec6i16_t Vec6i16_MaxS(vec6i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] > x ? v0.v[5] : x;

	return v0;
}
vec6i16_t Vec6i16_Clamp(vec6i16_t v, vec6i16_t min, vec6i16_t max)
{
	return Vec6i16_Max(Vec6i16_Min(v, max), min);
}
vec6i16_t Vec6i16_ClampS(vec6i16_t v, int16_t min, int16_t max)
{
	return Vec6i16_MaxS(Vec6i16_MinS(v, max), min);
}
vec6i16_t Vec6i16_Neg(vec6i16_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];
	v.v[3] = -v.v[3];
	v.v[4] = -v.v[4];
	v.v[5] = -v.v[5];

	return v;
}
vec6i16_t Vec6i16_CmpLT(vec6i16_t v0, vec6i16_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] < v1.v[5] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec6i16_t Vec6i16_CmpLE(vec6i16_t v0, vec6i16_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] <= v1.v[5] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec6i16_t Vec6i16_CmpEQ(vec6i16_t v0, vec6i16_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] == v1.v[5] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec6i16_t Vec6i16_CmpGT(vec6i16_t v0, vec6i16_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] > v1.v[5] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec6i16_t Vec6i16_CmpGE(vec6i16_t v0, vec6i16_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] >= v1.v[5] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec6i16_t Vec6i16_CmpNE(vec6i16_t v0, vec6i16_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] != v1.v[5] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec6i16_t Vec6i16_CmpLTS(vec6i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] < x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] < x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] < x ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] < x ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] < x ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] < x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec6i16_t Vec6i16_CmpLES(vec6i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] <= x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec6i16_t Vec6i16_CmpEQS(vec6i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] == x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] == x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] == x ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] == x ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] == x ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] == x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec6i16_t Vec6i16_CmpGTS(vec6i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] > x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] > x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] > x ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] > x ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] > x ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] > x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec6i16_t Vec6i16_CmpGES(vec6i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] >= x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec6i16_t Vec6i16_CmpNES(vec6i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] != x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] != x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] != x ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] != x ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] != x ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] != x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec6i16_t Vec6i16_Sign(vec6i16_t v)
{
	v.v[0] = v.v[0] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;
	v.v[1] = v.v[1] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;
	v.v[2] = v.v[2] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;
	v.v[3] = v.v[3] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;
	v.v[4] = v.v[4] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;
	v.v[5] = v.v[5] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;

	return v;
}
vec6i16_t Vec6i16_SignPosNeg(vec6i16_t v)
{
	v.v[0] = v.v[0] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;
	v.v[1] = v.v[1] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;
	v.v[2] = v.v[2] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;
	v.v[3] = v.v[3] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;
	v.v[4] = v.v[4] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;
	v.v[5] = v.v[5] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;

	return v;
}
vec6i16_t Vec6i16_Zero()
{
	return G_VEC6I16_T_ZERO;
}
vec6i16_t Vec6i16_One()
{
	return G_VEC6I16_T_ONE;
}
vec6i16_t Vec6i16_NegOne()
{
	return Vec6i16_Neg(G_VEC6I16_T_ONE);
}
vec6i16_t Vec6i16_Cross(vec6i16_t v0, vec6i16_t v1, vec6i16_t v2, vec6i16_t v3, vec6i16_t v4)
{
	vec6i16_t v;
	mat6x6i16_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;
	mat.v[5] = v4;

	for (i = 0; i < 6; i++)
		v.v[i] = Mat5x5i16_Det(Mat6x6i16_DeleteRowColumn(mat, 0, i));

	return v;
}
vec7i16_t Vec6i16_ToVec7i16(vec6i16_t v, int16_t x0)
{
	vec7i16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = v.v[5];
	outv.v[6] = x0;

	return outv;
}
vec8i16_t Vec6i16_ToVec8i16(vec6i16_t v, int16_t x0, int16_t x1)
{
	vec8i16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = v.v[5];
	outv.v[6] = x0;
	outv.v[7] = x1;

	return outv;
}
vec6u8_t Vec6u8_SetComponent(vec6u8_t v, int index, uint8_t value)
{
	v.v[index] = value;

	return v;
}
vec6u8_t Vec6u8_Vec(uint8_t x0, uint8_t x1, uint8_t x2, uint8_t x3, uint8_t x4, uint8_t x5)
{
	vec6u8_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;
	v.v[5] = x5;

	return v;
}
vec6u8_t Vec6u8_Add(vec6u8_t v0, vec6u8_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];
	v0.v[5] += v1.v[5];

	return v0;
}
vec6u8_t Vec6u8_Sub(vec6u8_t v0, vec6u8_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];
	v0.v[5] -= v1.v[5];

	return v0;
}
uint8_t Vec6u8_GetComponent(vec6u8_t v, int index)
{
	return v.v[index];
}
vec6u8_t Vec6u8_Mul(vec6u8_t v0, vec6u8_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];
	v0.v[5] *= v1.v[5];

	return v0;
}
vec6u8_t Vec6u8_Div(vec6u8_t v0, vec6u8_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];
	v0.v[5] /= v1.v[5];

	return v0;
}
vec6u8_t Vec6u8_Scale(vec6u8_t v, uint8_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;
	v.v[5] *= scale;

	return v;
}
vec6u8_t Vec6u8_DivScale(vec6u8_t v, uint8_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;
	v.v[5] /= divscale;

	return v;
}
vec6u8_t Vec6u8_MA(vec6u8_t v, vec6u8_t dir, uint8_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;
	v.v[5] += dir.v[5] * scale;

	return v;
}
vec6u8_t Vec6u8_DA(vec6u8_t v, vec6u8_t dir, uint8_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;
	v.v[5] += dir.v[5] / divscale;

	return v;
}
uint8_t Vec6u8_Dot(vec6u8_t v0, vec6u8_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4] + v0.v[5] * v1.v[5];
}
uint8_t Vec6u8_LenSq(vec6u8_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4] + v.v[5] * v.v[5];
}
uint8_t Vec6u8_Len(vec6u8_t v)
{
	return sqrtf(Vec6u8_LenSq(v));
}
vec6u8_t Vec6u8_Mod(vec6u8_t v0, vec6u8_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);
	v0.v[4] = (v0.v[4] % v1.v[4]);
	v0.v[5] = (v0.v[5] % v1.v[5]);

	return v0;
}
vec6u8_t Vec6u8_ModS(vec6u8_t v0, uint8_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);
	v0.v[4] = (v0.v[4] % x);
	v0.v[5] = (v0.v[5] % x);

	return v0;
}
vec6u8_t Vec6u8_Min(vec6u8_t v0, vec6u8_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] < v1.v[5] ? v0.v[5] : v1.v[5];

	return v0;
}
vec6u8_t Vec6u8_Max(vec6u8_t v0, vec6u8_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] > v1.v[5] ? v0.v[5] : v1.v[5];

	return v0;
}
vec6u8_t Vec6u8_MinS(vec6u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] < x ? v0.v[5] : x;

	return v0;
}
vec6u8_t Vec6u8_MaxS(vec6u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] > x ? v0.v[5] : x;

	return v0;
}
vec6u8_t Vec6u8_Clamp(vec6u8_t v, vec6u8_t min, vec6u8_t max)
{
	return Vec6u8_Max(Vec6u8_Min(v, max), min);
}
vec6u8_t Vec6u8_ClampS(vec6u8_t v, uint8_t min, uint8_t max)
{
	return Vec6u8_MaxS(Vec6u8_MinS(v, max), min);
}
vec6u8_t Vec6u8_CmpLT(vec6u8_t v0, vec6u8_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] < v1.v[5] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec6u8_t Vec6u8_CmpLE(vec6u8_t v0, vec6u8_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] <= v1.v[5] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec6u8_t Vec6u8_CmpEQ(vec6u8_t v0, vec6u8_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] == v1.v[5] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec6u8_t Vec6u8_CmpGT(vec6u8_t v0, vec6u8_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] > v1.v[5] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec6u8_t Vec6u8_CmpGE(vec6u8_t v0, vec6u8_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] >= v1.v[5] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec6u8_t Vec6u8_CmpNE(vec6u8_t v0, vec6u8_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] != v1.v[5] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec6u8_t Vec6u8_CmpLTS(vec6u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] < x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] < x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] < x ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] < x ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] < x ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] < x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec6u8_t Vec6u8_CmpLES(vec6u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] <= x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec6u8_t Vec6u8_CmpEQS(vec6u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] == x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] == x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] == x ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] == x ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] == x ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] == x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec6u8_t Vec6u8_CmpGTS(vec6u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] > x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] > x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] > x ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] > x ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] > x ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] > x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec6u8_t Vec6u8_CmpGES(vec6u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] >= x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec6u8_t Vec6u8_CmpNES(vec6u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] != x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] != x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] != x ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] != x ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] != x ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] != x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec6u8_t Vec6u8_Sign(vec6u8_t v)
{
	v.v[0] = v.v[0] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;
	v.v[1] = v.v[1] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;
	v.v[2] = v.v[2] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;
	v.v[3] = v.v[3] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;
	v.v[4] = v.v[4] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;
	v.v[5] = v.v[5] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;

	return v;
}
vec6u8_t Vec6u8_SignPosNeg(vec6u8_t v)
{
	v.v[0] = v.v[0] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;
	v.v[1] = v.v[1] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;
	v.v[2] = v.v[2] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;
	v.v[3] = v.v[3] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;
	v.v[4] = v.v[4] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;
	v.v[5] = v.v[5] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;

	return v;
}
vec6u8_t Vec6u8_Zero()
{
	return G_VEC6U8_T_ZERO;
}
vec6u8_t Vec6u8_One()
{
	return G_VEC6U8_T_ONE;
}
vec6u8_t Vec6u8_Cross(vec6u8_t v0, vec6u8_t v1, vec6u8_t v2, vec6u8_t v3, vec6u8_t v4)
{
	vec6u8_t v;
	mat6x6u8_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;
	mat.v[5] = v4;

	for (i = 0; i < 6; i++)
		v.v[i] = Mat5x5u8_Det(Mat6x6u8_DeleteRowColumn(mat, 0, i));

	return v;
}
vec7u8_t Vec6u8_ToVec7u8(vec6u8_t v, uint8_t x0)
{
	vec7u8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = v.v[5];
	outv.v[6] = x0;

	return outv;
}
vec8u8_t Vec6u8_ToVec8u8(vec6u8_t v, uint8_t x0, uint8_t x1)
{
	vec8u8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = v.v[5];
	outv.v[6] = x0;
	outv.v[7] = x1;

	return outv;
}
vec6i8_t Vec6i8_SetComponent(vec6i8_t v, int index, int8_t value)
{
	v.v[index] = value;

	return v;
}
vec6i8_t Vec6i8_Vec(int8_t x0, int8_t x1, int8_t x2, int8_t x3, int8_t x4, int8_t x5)
{
	vec6i8_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;
	v.v[5] = x5;

	return v;
}
vec6i8_t Vec6i8_Add(vec6i8_t v0, vec6i8_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];
	v0.v[5] += v1.v[5];

	return v0;
}
vec6i8_t Vec6i8_Sub(vec6i8_t v0, vec6i8_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];
	v0.v[5] -= v1.v[5];

	return v0;
}
int8_t Vec6i8_GetComponent(vec6i8_t v, int index)
{
	return v.v[index];
}
vec6i8_t Vec6i8_Mul(vec6i8_t v0, vec6i8_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];
	v0.v[5] *= v1.v[5];

	return v0;
}
vec6i8_t Vec6i8_Div(vec6i8_t v0, vec6i8_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];
	v0.v[5] /= v1.v[5];

	return v0;
}
vec6i8_t Vec6i8_Scale(vec6i8_t v, int8_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;
	v.v[5] *= scale;

	return v;
}
vec6i8_t Vec6i8_DivScale(vec6i8_t v, int8_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;
	v.v[5] /= divscale;

	return v;
}
vec6i8_t Vec6i8_MA(vec6i8_t v, vec6i8_t dir, int8_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;
	v.v[5] += dir.v[5] * scale;

	return v;
}
vec6i8_t Vec6i8_DA(vec6i8_t v, vec6i8_t dir, int8_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;
	v.v[5] += dir.v[5] / divscale;

	return v;
}
int8_t Vec6i8_Dot(vec6i8_t v0, vec6i8_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4] + v0.v[5] * v1.v[5];
}
int8_t Vec6i8_LenSq(vec6i8_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4] + v.v[5] * v.v[5];
}
int8_t Vec6i8_Len(vec6i8_t v)
{
	return sqrtf(Vec6i8_LenSq(v));
}
vec6i8_t Vec6i8_Abs(vec6i8_t v)
{
	v.v[0] = (v.v[0] < 0 ? -v.v[0] : v.v[0]);
	v.v[1] = (v.v[1] < 0 ? -v.v[1] : v.v[1]);
	v.v[2] = (v.v[2] < 0 ? -v.v[2] : v.v[2]);
	v.v[3] = (v.v[3] < 0 ? -v.v[3] : v.v[3]);
	v.v[4] = (v.v[4] < 0 ? -v.v[4] : v.v[4]);
	v.v[5] = (v.v[5] < 0 ? -v.v[5] : v.v[5]);

	return v;
}
vec6i8_t Vec6i8_Mod(vec6i8_t v0, vec6i8_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);
	v0.v[4] = (v0.v[4] % v1.v[4]);
	v0.v[5] = (v0.v[5] % v1.v[5]);

	return v0;
}
vec6i8_t Vec6i8_ModS(vec6i8_t v0, int8_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);
	v0.v[4] = (v0.v[4] % x);
	v0.v[5] = (v0.v[5] % x);

	return v0;
}
vec6i8_t Vec6i8_Min(vec6i8_t v0, vec6i8_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] < v1.v[5] ? v0.v[5] : v1.v[5];

	return v0;
}
vec6i8_t Vec6i8_Max(vec6i8_t v0, vec6i8_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] > v1.v[5] ? v0.v[5] : v1.v[5];

	return v0;
}
vec6i8_t Vec6i8_MinS(vec6i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] < x ? v0.v[5] : x;

	return v0;
}
vec6i8_t Vec6i8_MaxS(vec6i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] > x ? v0.v[5] : x;

	return v0;
}
vec6i8_t Vec6i8_Clamp(vec6i8_t v, vec6i8_t min, vec6i8_t max)
{
	return Vec6i8_Max(Vec6i8_Min(v, max), min);
}
vec6i8_t Vec6i8_ClampS(vec6i8_t v, int8_t min, int8_t max)
{
	return Vec6i8_MaxS(Vec6i8_MinS(v, max), min);
}
vec6i8_t Vec6i8_Neg(vec6i8_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];
	v.v[3] = -v.v[3];
	v.v[4] = -v.v[4];
	v.v[5] = -v.v[5];

	return v;
}
vec6i8_t Vec6i8_CmpLT(vec6i8_t v0, vec6i8_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] < v1.v[5] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec6i8_t Vec6i8_CmpLE(vec6i8_t v0, vec6i8_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] <= v1.v[5] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec6i8_t Vec6i8_CmpEQ(vec6i8_t v0, vec6i8_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] == v1.v[5] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec6i8_t Vec6i8_CmpGT(vec6i8_t v0, vec6i8_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] > v1.v[5] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec6i8_t Vec6i8_CmpGE(vec6i8_t v0, vec6i8_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] >= v1.v[5] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec6i8_t Vec6i8_CmpNE(vec6i8_t v0, vec6i8_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] != v1.v[5] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec6i8_t Vec6i8_CmpLTS(vec6i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] < x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] < x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] < x ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] < x ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] < x ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] < x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec6i8_t Vec6i8_CmpLES(vec6i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] <= x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec6i8_t Vec6i8_CmpEQS(vec6i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] == x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] == x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] == x ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] == x ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] == x ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] == x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec6i8_t Vec6i8_CmpGTS(vec6i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] > x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] > x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] > x ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] > x ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] > x ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] > x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec6i8_t Vec6i8_CmpGES(vec6i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] >= x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec6i8_t Vec6i8_CmpNES(vec6i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] != x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] != x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] != x ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] != x ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] != x ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] != x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec6i8_t Vec6i8_Sign(vec6i8_t v)
{
	v.v[0] = v.v[0] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;
	v.v[1] = v.v[1] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;
	v.v[2] = v.v[2] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;
	v.v[3] = v.v[3] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;
	v.v[4] = v.v[4] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;
	v.v[5] = v.v[5] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;

	return v;
}
vec6i8_t Vec6i8_SignPosNeg(vec6i8_t v)
{
	v.v[0] = v.v[0] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;
	v.v[1] = v.v[1] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;
	v.v[2] = v.v[2] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;
	v.v[3] = v.v[3] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;
	v.v[4] = v.v[4] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;
	v.v[5] = v.v[5] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;

	return v;
}
vec6i8_t Vec6i8_Zero()
{
	return G_VEC6I8_T_ZERO;
}
vec6i8_t Vec6i8_One()
{
	return G_VEC6I8_T_ONE;
}
vec6i8_t Vec6i8_NegOne()
{
	return Vec6i8_Neg(G_VEC6I8_T_ONE);
}
vec6i8_t Vec6i8_Cross(vec6i8_t v0, vec6i8_t v1, vec6i8_t v2, vec6i8_t v3, vec6i8_t v4)
{
	vec6i8_t v;
	mat6x6i8_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;
	mat.v[5] = v4;

	for (i = 0; i < 6; i++)
		v.v[i] = Mat5x5i8_Det(Mat6x6i8_DeleteRowColumn(mat, 0, i));

	return v;
}
vec7i8_t Vec6i8_ToVec7i8(vec6i8_t v, int8_t x0)
{
	vec7i8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = v.v[5];
	outv.v[6] = x0;

	return outv;
}
vec8i8_t Vec6i8_ToVec8i8(vec6i8_t v, int8_t x0, int8_t x1)
{
	vec8i8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = v.v[5];
	outv.v[6] = x0;
	outv.v[7] = x1;

	return outv;
}
vec7f64_t Vec7f64_SetComponent(vec7f64_t v, int index, double value)
{
	v.v[index] = value;

	return v;
}
vec7f64_t Vec7f64_Vec(double x0, double x1, double x2, double x3, double x4, double x5, double x6)
{
	vec7f64_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;
	v.v[5] = x5;
	v.v[6] = x6;

	return v;
}
vec7f64_t Vec7f64_Add(vec7f64_t v0, vec7f64_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];
	v0.v[5] += v1.v[5];
	v0.v[6] += v1.v[6];

	return v0;
}
vec7f64_t Vec7f64_Sub(vec7f64_t v0, vec7f64_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];
	v0.v[5] -= v1.v[5];
	v0.v[6] -= v1.v[6];

	return v0;
}
double Vec7f64_GetComponent(vec7f64_t v, int index)
{
	return v.v[index];
}
vec7f64_t Vec7f64_Mul(vec7f64_t v0, vec7f64_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];
	v0.v[5] *= v1.v[5];
	v0.v[6] *= v1.v[6];

	return v0;
}
vec7f64_t Vec7f64_Div(vec7f64_t v0, vec7f64_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];
	v0.v[5] /= v1.v[5];
	v0.v[6] /= v1.v[6];

	return v0;
}
vec7f64_t Vec7f64_Scale(vec7f64_t v, double scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;
	v.v[5] *= scale;
	v.v[6] *= scale;

	return v;
}
vec7f64_t Vec7f64_DivScale(vec7f64_t v, double divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;
	v.v[5] /= divscale;
	v.v[6] /= divscale;

	return v;
}
vec7f64_t Vec7f64_MA(vec7f64_t v, vec7f64_t dir, double scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;
	v.v[5] += dir.v[5] * scale;
	v.v[6] += dir.v[6] * scale;

	return v;
}
vec7f64_t Vec7f64_DA(vec7f64_t v, vec7f64_t dir, double divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;
	v.v[5] += dir.v[5] / divscale;
	v.v[6] += dir.v[6] / divscale;

	return v;
}
double Vec7f64_Dot(vec7f64_t v0, vec7f64_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4] + v0.v[5] * v1.v[5] + v0.v[6] * v1.v[6];
}
double Vec7f64_LenSq(vec7f64_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4] + v.v[5] * v.v[5] + v.v[6] * v.v[6];
}
double Vec7f64_Len(vec7f64_t v)
{
	return sqrt(Vec7f64_LenSq(v));
}
vec7f64_t Vec7f64_Normalise(vec7f64_t v)
{
	double lensq = Vec7f64_LenSq(v);

	if (lensq == G_F64_ZERO)
		return v;
	else
		return Vec7f64_Scale(v, G_F64_ONE / sqrt(lensq));
}
vec7f64_t Vec7f64_Abs(vec7f64_t v)
{
	v.v[0] = fabs(v.v[0]);
	v.v[1] = fabs(v.v[1]);
	v.v[2] = fabs(v.v[2]);
	v.v[3] = fabs(v.v[3]);
	v.v[4] = fabs(v.v[4]);
	v.v[5] = fabs(v.v[5]);
	v.v[6] = fabs(v.v[6]);

	return v;
}
vec7f64_t Vec7f64_Floor(vec7f64_t v)
{
	v.v[0] = floor(v.v[0]);
	v.v[1] = floor(v.v[1]);
	v.v[2] = floor(v.v[2]);
	v.v[3] = floor(v.v[3]);
	v.v[4] = floor(v.v[4]);
	v.v[5] = floor(v.v[5]);
	v.v[6] = floor(v.v[6]);

	return v;
}
vec7f64_t Vec7f64_Ceil(vec7f64_t v)
{
	v.v[0] = ceil(v.v[0]);
	v.v[1] = ceil(v.v[1]);
	v.v[2] = ceil(v.v[2]);
	v.v[3] = ceil(v.v[3]);
	v.v[4] = ceil(v.v[4]);
	v.v[5] = ceil(v.v[5]);
	v.v[6] = ceil(v.v[6]);

	return v;
}
vec7f64_t Vec7f64_Fract(vec7f64_t v)
{
	return Vec7f64_Sub(v, Vec7f64_Floor(v));
}
vec7f64_t Vec7f64_Mod(vec7f64_t v0, vec7f64_t v1)
{
	v0.v[0] = fmod(v0.v[0], v1.v[0]);
	v0.v[1] = fmod(v0.v[1], v1.v[1]);
	v0.v[2] = fmod(v0.v[2], v1.v[2]);
	v0.v[3] = fmod(v0.v[3], v1.v[3]);
	v0.v[4] = fmod(v0.v[4], v1.v[4]);
	v0.v[5] = fmod(v0.v[5], v1.v[5]);
	v0.v[6] = fmod(v0.v[6], v1.v[6]);

	return v0;
}
vec7f64_t Vec7f64_ModS(vec7f64_t v0, double x)
{
	v0.v[0] = fmod(v0.v[0], x);
	v0.v[1] = fmod(v0.v[1], x);
	v0.v[2] = fmod(v0.v[2], x);
	v0.v[3] = fmod(v0.v[3], x);
	v0.v[4] = fmod(v0.v[4], x);
	v0.v[5] = fmod(v0.v[5], x);
	v0.v[6] = fmod(v0.v[6], x);

	return v0;
}
vec7f64_t Vec7f64_Min(vec7f64_t v0, vec7f64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] < v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] < v1.v[6] ? v0.v[6] : v1.v[6];

	return v0;
}
vec7f64_t Vec7f64_Max(vec7f64_t v0, vec7f64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] > v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] > v1.v[6] ? v0.v[6] : v1.v[6];

	return v0;
}
vec7f64_t Vec7f64_MinS(vec7f64_t v0, double x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] < x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] < x ? v0.v[6] : x;

	return v0;
}
vec7f64_t Vec7f64_MaxS(vec7f64_t v0, double x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] > x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] > x ? v0.v[6] : x;

	return v0;
}
vec7f64_t Vec7f64_Clamp(vec7f64_t v, vec7f64_t min, vec7f64_t max)
{
	return Vec7f64_Max(Vec7f64_Min(v, max), min);
}
vec7f64_t Vec7f64_ClampS(vec7f64_t v, double min, double max)
{
	return Vec7f64_MaxS(Vec7f64_MinS(v, max), min);
}
vec7f64_t Vec7f64_Neg(vec7f64_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];
	v.v[3] = -v.v[3];
	v.v[4] = -v.v[4];
	v.v[5] = -v.v[5];
	v.v[6] = -v.v[6];

	return v;
}
vec7f64_t Vec7f64_Reciprocal(vec7f64_t v)
{
	v.v[0] = G_F64_ONE / v.v[0];
	v.v[1] = G_F64_ONE / v.v[1];
	v.v[2] = G_F64_ONE / v.v[2];
	v.v[3] = G_F64_ONE / v.v[3];
	v.v[4] = G_F64_ONE / v.v[4];
	v.v[5] = G_F64_ONE / v.v[5];
	v.v[6] = G_F64_ONE / v.v[6];

	return v;
}
vec7f64_t Vec7f64_Truncate(vec7f64_t v)
{
	v.v[0] = v.v[0] < G_F64_ZERO ? ceil(v.v[0]) : floor(v.v[0]);
	v.v[1] = v.v[1] < G_F64_ZERO ? ceil(v.v[1]) : floor(v.v[1]);
	v.v[2] = v.v[2] < G_F64_ZERO ? ceil(v.v[2]) : floor(v.v[2]);
	v.v[3] = v.v[3] < G_F64_ZERO ? ceil(v.v[3]) : floor(v.v[3]);
	v.v[4] = v.v[4] < G_F64_ZERO ? ceil(v.v[4]) : floor(v.v[4]);
	v.v[5] = v.v[5] < G_F64_ZERO ? ceil(v.v[5]) : floor(v.v[5]);
	v.v[6] = v.v[6] < G_F64_ZERO ? ceil(v.v[6]) : floor(v.v[6]);

	return v;
}
vec7f64_t Vec7f64_TruncateAway(vec7f64_t v)
{
	v.v[0] = v.v[0] < G_F64_ZERO ? floor(v.v[0]) : ceil(v.v[0]);
	v.v[1] = v.v[1] < G_F64_ZERO ? floor(v.v[1]) : ceil(v.v[1]);
	v.v[2] = v.v[2] < G_F64_ZERO ? floor(v.v[2]) : ceil(v.v[2]);
	v.v[3] = v.v[3] < G_F64_ZERO ? floor(v.v[3]) : ceil(v.v[3]);
	v.v[4] = v.v[4] < G_F64_ZERO ? floor(v.v[4]) : ceil(v.v[4]);
	v.v[5] = v.v[5] < G_F64_ZERO ? floor(v.v[5]) : ceil(v.v[5]);
	v.v[6] = v.v[6] < G_F64_ZERO ? floor(v.v[6]) : ceil(v.v[6]);

	return v;
}
vec7f64_t Vec7f64_CmpLT(vec7f64_t v0, vec7f64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] < v1.v[5] ? G_F64_ONE : G_F64_ZERO;
	v0.v[6] = v0.v[6] < v1.v[6] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec7f64_t Vec7f64_CmpLE(vec7f64_t v0, vec7f64_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] <= v1.v[5] ? G_F64_ONE : G_F64_ZERO;
	v0.v[6] = v0.v[6] <= v1.v[6] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec7f64_t Vec7f64_CmpEQ(vec7f64_t v0, vec7f64_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] == v1.v[5] ? G_F64_ONE : G_F64_ZERO;
	v0.v[6] = v0.v[6] == v1.v[6] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec7f64_t Vec7f64_CmpGT(vec7f64_t v0, vec7f64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] > v1.v[5] ? G_F64_ONE : G_F64_ZERO;
	v0.v[6] = v0.v[6] > v1.v[6] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec7f64_t Vec7f64_CmpGE(vec7f64_t v0, vec7f64_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] >= v1.v[5] ? G_F64_ONE : G_F64_ZERO;
	v0.v[6] = v0.v[6] >= v1.v[6] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec7f64_t Vec7f64_CmpNE(vec7f64_t v0, vec7f64_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] != v1.v[5] ? G_F64_ONE : G_F64_ZERO;
	v0.v[6] = v0.v[6] != v1.v[6] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec7f64_t Vec7f64_CmpLTS(vec7f64_t v0, double x)
{
	v0.v[0] = v0.v[0] < x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] < x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] < x ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] < x ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] < x ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] < x ? G_F64_ONE : G_F64_ZERO;
	v0.v[6] = v0.v[6] < x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec7f64_t Vec7f64_CmpLES(vec7f64_t v0, double x)
{
	v0.v[0] = v0.v[0] <= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] <= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[6] = v0.v[6] <= x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec7f64_t Vec7f64_CmpEQS(vec7f64_t v0, double x)
{
	v0.v[0] = v0.v[0] == x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] == x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] == x ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] == x ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] == x ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] == x ? G_F64_ONE : G_F64_ZERO;
	v0.v[6] = v0.v[6] == x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec7f64_t Vec7f64_CmpGTS(vec7f64_t v0, double x)
{
	v0.v[0] = v0.v[0] > x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] > x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] > x ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] > x ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] > x ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] > x ? G_F64_ONE : G_F64_ZERO;
	v0.v[6] = v0.v[6] > x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec7f64_t Vec7f64_CmpGES(vec7f64_t v0, double x)
{
	v0.v[0] = v0.v[0] >= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] >= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[6] = v0.v[6] >= x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec7f64_t Vec7f64_CmpNES(vec7f64_t v0, double x)
{
	v0.v[0] = v0.v[0] != x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] != x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] != x ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] != x ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] != x ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] != x ? G_F64_ONE : G_F64_ZERO;
	v0.v[6] = v0.v[6] != x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec7f64_t Vec7f64_Sign(vec7f64_t v)
{
	v.v[0] = v.v[0] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;
	v.v[1] = v.v[1] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;
	v.v[2] = v.v[2] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;
	v.v[3] = v.v[3] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;
	v.v[4] = v.v[4] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;
	v.v[5] = v.v[5] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;
	v.v[6] = v.v[6] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;

	return v;
}
vec7f64_t Vec7f64_SignPosNeg(vec7f64_t v)
{
	v.v[0] = v.v[0] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;
	v.v[1] = v.v[1] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;
	v.v[2] = v.v[2] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;
	v.v[3] = v.v[3] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;
	v.v[4] = v.v[4] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;
	v.v[5] = v.v[5] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;
	v.v[6] = v.v[6] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;

	return v;
}
vec7f64_t Vec7f64_Zero()
{
	return G_VEC7F64_T_ZERO;
}
vec7f64_t Vec7f64_One()
{
	return G_VEC7F64_T_ONE;
}
vec7f64_t Vec7f64_NegOne()
{
	return Vec7f64_Neg(G_VEC7F64_T_ONE);
}
vec7f64_t Vec7f64_Cross(vec7f64_t v0, vec7f64_t v1, vec7f64_t v2, vec7f64_t v3, vec7f64_t v4, vec7f64_t v5)
{
	vec7f64_t v;
	mat7x7f64_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;
	mat.v[5] = v4;
	mat.v[6] = v5;

	for (i = 0; i < 7; i++)
		v.v[i] = Mat6x6f64_Det(Mat7x7f64_DeleteRowColumn(mat, 0, i));

	return v;
}
vec7f64_t Vec7f64_Lerp(vec7f64_t v0, vec7f64_t v1, vec7f64_t vt)
{
	vec7f64_t v;

	v.v[0] = (G_F64_ONE - vt.v[0]) * v0.v[0] + v1.v[0] * vt.v[0];
	v.v[1] = (G_F64_ONE - vt.v[1]) * v0.v[1] + v1.v[1] * vt.v[1];
	v.v[2] = (G_F64_ONE - vt.v[2]) * v0.v[2] + v1.v[2] * vt.v[2];
	v.v[3] = (G_F64_ONE - vt.v[3]) * v0.v[3] + v1.v[3] * vt.v[3];
	v.v[4] = (G_F64_ONE - vt.v[4]) * v0.v[4] + v1.v[4] * vt.v[4];
	v.v[5] = (G_F64_ONE - vt.v[5]) * v0.v[5] + v1.v[5] * vt.v[5];
	v.v[6] = (G_F64_ONE - vt.v[6]) * v0.v[6] + v1.v[6] * vt.v[6];

	return v;
}
vec7f64_t Vec7f64_LerpS(vec7f64_t v0, vec7f64_t v1, double t)
{
	vec7f64_t v;

	v.v[0] = (G_F64_ONE - t) * v0.v[0] + v1.v[0] * t;
	v.v[1] = (G_F64_ONE - t) * v0.v[1] + v1.v[1] * t;
	v.v[2] = (G_F64_ONE - t) * v0.v[2] + v1.v[2] * t;
	v.v[3] = (G_F64_ONE - t) * v0.v[3] + v1.v[3] * t;
	v.v[4] = (G_F64_ONE - t) * v0.v[4] + v1.v[4] * t;
	v.v[5] = (G_F64_ONE - t) * v0.v[5] + v1.v[5] * t;
	v.v[6] = (G_F64_ONE - t) * v0.v[6] + v1.v[6] * t;

	return v;
}
vec8f64_t Vec7f64_ToVec8f64(vec7f64_t v, double x0)
{
	vec8f64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = v.v[5];
	outv.v[6] = v.v[6];
	outv.v[7] = x0;

	return outv;
}
vec7f32_t Vec7f32_SetComponent(vec7f32_t v, int index, float value)
{
	v.v[index] = value;

	return v;
}
vec7f32_t Vec7f32_Vec(float x0, float x1, float x2, float x3, float x4, float x5, float x6)
{
	vec7f32_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;
	v.v[5] = x5;
	v.v[6] = x6;

	return v;
}
vec7f32_t Vec7f32_Add(vec7f32_t v0, vec7f32_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];
	v0.v[5] += v1.v[5];
	v0.v[6] += v1.v[6];

	return v0;
}
vec7f32_t Vec7f32_Sub(vec7f32_t v0, vec7f32_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];
	v0.v[5] -= v1.v[5];
	v0.v[6] -= v1.v[6];

	return v0;
}
float Vec7f32_GetComponent(vec7f32_t v, int index)
{
	return v.v[index];
}
vec7f32_t Vec7f32_Mul(vec7f32_t v0, vec7f32_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];
	v0.v[5] *= v1.v[5];
	v0.v[6] *= v1.v[6];

	return v0;
}
vec7f32_t Vec7f32_Div(vec7f32_t v0, vec7f32_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];
	v0.v[5] /= v1.v[5];
	v0.v[6] /= v1.v[6];

	return v0;
}
vec7f32_t Vec7f32_Scale(vec7f32_t v, float scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;
	v.v[5] *= scale;
	v.v[6] *= scale;

	return v;
}
vec7f32_t Vec7f32_DivScale(vec7f32_t v, float divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;
	v.v[5] /= divscale;
	v.v[6] /= divscale;

	return v;
}
vec7f32_t Vec7f32_MA(vec7f32_t v, vec7f32_t dir, float scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;
	v.v[5] += dir.v[5] * scale;
	v.v[6] += dir.v[6] * scale;

	return v;
}
vec7f32_t Vec7f32_DA(vec7f32_t v, vec7f32_t dir, float divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;
	v.v[5] += dir.v[5] / divscale;
	v.v[6] += dir.v[6] / divscale;

	return v;
}
float Vec7f32_Dot(vec7f32_t v0, vec7f32_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4] + v0.v[5] * v1.v[5] + v0.v[6] * v1.v[6];
}
float Vec7f32_LenSq(vec7f32_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4] + v.v[5] * v.v[5] + v.v[6] * v.v[6];
}
float Vec7f32_Len(vec7f32_t v)
{
	return sqrtf(Vec7f32_LenSq(v));
}
vec7f32_t Vec7f32_Normalise(vec7f32_t v)
{
	float lensq = Vec7f32_LenSq(v);

	if (lensq == G_F32_ZERO)
		return v;
	else
		return Vec7f32_Scale(v, G_F32_ONE / sqrtf(lensq));
}
vec7f32_t Vec7f32_Abs(vec7f32_t v)
{
	v.v[0] = fabsf(v.v[0]);
	v.v[1] = fabsf(v.v[1]);
	v.v[2] = fabsf(v.v[2]);
	v.v[3] = fabsf(v.v[3]);
	v.v[4] = fabsf(v.v[4]);
	v.v[5] = fabsf(v.v[5]);
	v.v[6] = fabsf(v.v[6]);

	return v;
}
vec7f32_t Vec7f32_Floor(vec7f32_t v)
{
	v.v[0] = floorf(v.v[0]);
	v.v[1] = floorf(v.v[1]);
	v.v[2] = floorf(v.v[2]);
	v.v[3] = floorf(v.v[3]);
	v.v[4] = floorf(v.v[4]);
	v.v[5] = floorf(v.v[5]);
	v.v[6] = floorf(v.v[6]);

	return v;
}
vec7f32_t Vec7f32_Ceil(vec7f32_t v)
{
	v.v[0] = ceilf(v.v[0]);
	v.v[1] = ceilf(v.v[1]);
	v.v[2] = ceilf(v.v[2]);
	v.v[3] = ceilf(v.v[3]);
	v.v[4] = ceilf(v.v[4]);
	v.v[5] = ceilf(v.v[5]);
	v.v[6] = ceilf(v.v[6]);

	return v;
}
vec7f32_t Vec7f32_Fract(vec7f32_t v)
{
	return Vec7f32_Sub(v, Vec7f32_Floor(v));
}
vec7f32_t Vec7f32_Mod(vec7f32_t v0, vec7f32_t v1)
{
	v0.v[0] = fmodf(v0.v[0], v1.v[0]);
	v0.v[1] = fmodf(v0.v[1], v1.v[1]);
	v0.v[2] = fmodf(v0.v[2], v1.v[2]);
	v0.v[3] = fmodf(v0.v[3], v1.v[3]);
	v0.v[4] = fmodf(v0.v[4], v1.v[4]);
	v0.v[5] = fmodf(v0.v[5], v1.v[5]);
	v0.v[6] = fmodf(v0.v[6], v1.v[6]);

	return v0;
}
vec7f32_t Vec7f32_ModS(vec7f32_t v0, float x)
{
	v0.v[0] = fmodf(v0.v[0], x);
	v0.v[1] = fmodf(v0.v[1], x);
	v0.v[2] = fmodf(v0.v[2], x);
	v0.v[3] = fmodf(v0.v[3], x);
	v0.v[4] = fmodf(v0.v[4], x);
	v0.v[5] = fmodf(v0.v[5], x);
	v0.v[6] = fmodf(v0.v[6], x);

	return v0;
}
vec7f32_t Vec7f32_Min(vec7f32_t v0, vec7f32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] < v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] < v1.v[6] ? v0.v[6] : v1.v[6];

	return v0;
}
vec7f32_t Vec7f32_Max(vec7f32_t v0, vec7f32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] > v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] > v1.v[6] ? v0.v[6] : v1.v[6];

	return v0;
}
vec7f32_t Vec7f32_MinS(vec7f32_t v0, float x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] < x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] < x ? v0.v[6] : x;

	return v0;
}
vec7f32_t Vec7f32_MaxS(vec7f32_t v0, float x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] > x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] > x ? v0.v[6] : x;

	return v0;
}
vec7f32_t Vec7f32_Clamp(vec7f32_t v, vec7f32_t min, vec7f32_t max)
{
	return Vec7f32_Max(Vec7f32_Min(v, max), min);
}
vec7f32_t Vec7f32_ClampS(vec7f32_t v, float min, float max)
{
	return Vec7f32_MaxS(Vec7f32_MinS(v, max), min);
}
vec7f32_t Vec7f32_Neg(vec7f32_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];
	v.v[3] = -v.v[3];
	v.v[4] = -v.v[4];
	v.v[5] = -v.v[5];
	v.v[6] = -v.v[6];

	return v;
}
vec7f32_t Vec7f32_Reciprocal(vec7f32_t v)
{
	v.v[0] = G_F32_ONE / v.v[0];
	v.v[1] = G_F32_ONE / v.v[1];
	v.v[2] = G_F32_ONE / v.v[2];
	v.v[3] = G_F32_ONE / v.v[3];
	v.v[4] = G_F32_ONE / v.v[4];
	v.v[5] = G_F32_ONE / v.v[5];
	v.v[6] = G_F32_ONE / v.v[6];

	return v;
}
vec7f32_t Vec7f32_Truncate(vec7f32_t v)
{
	v.v[0] = v.v[0] < G_F32_ZERO ? ceilf(v.v[0]) : floorf(v.v[0]);
	v.v[1] = v.v[1] < G_F32_ZERO ? ceilf(v.v[1]) : floorf(v.v[1]);
	v.v[2] = v.v[2] < G_F32_ZERO ? ceilf(v.v[2]) : floorf(v.v[2]);
	v.v[3] = v.v[3] < G_F32_ZERO ? ceilf(v.v[3]) : floorf(v.v[3]);
	v.v[4] = v.v[4] < G_F32_ZERO ? ceilf(v.v[4]) : floorf(v.v[4]);
	v.v[5] = v.v[5] < G_F32_ZERO ? ceilf(v.v[5]) : floorf(v.v[5]);
	v.v[6] = v.v[6] < G_F32_ZERO ? ceilf(v.v[6]) : floorf(v.v[6]);

	return v;
}
vec7f32_t Vec7f32_TruncateAway(vec7f32_t v)
{
	v.v[0] = v.v[0] < G_F32_ZERO ? floorf(v.v[0]) : ceilf(v.v[0]);
	v.v[1] = v.v[1] < G_F32_ZERO ? floorf(v.v[1]) : ceilf(v.v[1]);
	v.v[2] = v.v[2] < G_F32_ZERO ? floorf(v.v[2]) : ceilf(v.v[2]);
	v.v[3] = v.v[3] < G_F32_ZERO ? floorf(v.v[3]) : ceilf(v.v[3]);
	v.v[4] = v.v[4] < G_F32_ZERO ? floorf(v.v[4]) : ceilf(v.v[4]);
	v.v[5] = v.v[5] < G_F32_ZERO ? floorf(v.v[5]) : ceilf(v.v[5]);
	v.v[6] = v.v[6] < G_F32_ZERO ? floorf(v.v[6]) : ceilf(v.v[6]);

	return v;
}
vec7f32_t Vec7f32_CmpLT(vec7f32_t v0, vec7f32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] < v1.v[5] ? G_F32_ONE : G_F32_ZERO;
	v0.v[6] = v0.v[6] < v1.v[6] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec7f32_t Vec7f32_CmpLE(vec7f32_t v0, vec7f32_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] <= v1.v[5] ? G_F32_ONE : G_F32_ZERO;
	v0.v[6] = v0.v[6] <= v1.v[6] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec7f32_t Vec7f32_CmpEQ(vec7f32_t v0, vec7f32_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] == v1.v[5] ? G_F32_ONE : G_F32_ZERO;
	v0.v[6] = v0.v[6] == v1.v[6] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec7f32_t Vec7f32_CmpGT(vec7f32_t v0, vec7f32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] > v1.v[5] ? G_F32_ONE : G_F32_ZERO;
	v0.v[6] = v0.v[6] > v1.v[6] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec7f32_t Vec7f32_CmpGE(vec7f32_t v0, vec7f32_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] >= v1.v[5] ? G_F32_ONE : G_F32_ZERO;
	v0.v[6] = v0.v[6] >= v1.v[6] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec7f32_t Vec7f32_CmpNE(vec7f32_t v0, vec7f32_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] != v1.v[5] ? G_F32_ONE : G_F32_ZERO;
	v0.v[6] = v0.v[6] != v1.v[6] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec7f32_t Vec7f32_CmpLTS(vec7f32_t v0, float x)
{
	v0.v[0] = v0.v[0] < x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] < x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] < x ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] < x ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] < x ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] < x ? G_F32_ONE : G_F32_ZERO;
	v0.v[6] = v0.v[6] < x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec7f32_t Vec7f32_CmpLES(vec7f32_t v0, float x)
{
	v0.v[0] = v0.v[0] <= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] <= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[6] = v0.v[6] <= x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec7f32_t Vec7f32_CmpEQS(vec7f32_t v0, float x)
{
	v0.v[0] = v0.v[0] == x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] == x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] == x ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] == x ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] == x ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] == x ? G_F32_ONE : G_F32_ZERO;
	v0.v[6] = v0.v[6] == x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec7f32_t Vec7f32_CmpGTS(vec7f32_t v0, float x)
{
	v0.v[0] = v0.v[0] > x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] > x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] > x ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] > x ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] > x ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] > x ? G_F32_ONE : G_F32_ZERO;
	v0.v[6] = v0.v[6] > x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec7f32_t Vec7f32_CmpGES(vec7f32_t v0, float x)
{
	v0.v[0] = v0.v[0] >= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] >= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[6] = v0.v[6] >= x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec7f32_t Vec7f32_CmpNES(vec7f32_t v0, float x)
{
	v0.v[0] = v0.v[0] != x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] != x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] != x ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] != x ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] != x ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] != x ? G_F32_ONE : G_F32_ZERO;
	v0.v[6] = v0.v[6] != x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec7f32_t Vec7f32_Sign(vec7f32_t v)
{
	v.v[0] = v.v[0] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;
	v.v[1] = v.v[1] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;
	v.v[2] = v.v[2] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;
	v.v[3] = v.v[3] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;
	v.v[4] = v.v[4] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;
	v.v[5] = v.v[5] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;
	v.v[6] = v.v[6] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;

	return v;
}
vec7f32_t Vec7f32_SignPosNeg(vec7f32_t v)
{
	v.v[0] = v.v[0] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;
	v.v[1] = v.v[1] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;
	v.v[2] = v.v[2] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;
	v.v[3] = v.v[3] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;
	v.v[4] = v.v[4] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;
	v.v[5] = v.v[5] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;
	v.v[6] = v.v[6] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;

	return v;
}
vec7f32_t Vec7f32_Zero()
{
	return G_VEC7F32_T_ZERO;
}
vec7f32_t Vec7f32_One()
{
	return G_VEC7F32_T_ONE;
}
vec7f32_t Vec7f32_NegOne()
{
	return Vec7f32_Neg(G_VEC7F32_T_ONE);
}
vec7f32_t Vec7f32_Cross(vec7f32_t v0, vec7f32_t v1, vec7f32_t v2, vec7f32_t v3, vec7f32_t v4, vec7f32_t v5)
{
	vec7f32_t v;
	mat7x7f32_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;
	mat.v[5] = v4;
	mat.v[6] = v5;

	for (i = 0; i < 7; i++)
		v.v[i] = Mat6x6f32_Det(Mat7x7f32_DeleteRowColumn(mat, 0, i));

	return v;
}
vec7f32_t Vec7f32_Lerp(vec7f32_t v0, vec7f32_t v1, vec7f32_t vt)
{
	vec7f32_t v;

	v.v[0] = (G_F32_ONE - vt.v[0]) * v0.v[0] + v1.v[0] * vt.v[0];
	v.v[1] = (G_F32_ONE - vt.v[1]) * v0.v[1] + v1.v[1] * vt.v[1];
	v.v[2] = (G_F32_ONE - vt.v[2]) * v0.v[2] + v1.v[2] * vt.v[2];
	v.v[3] = (G_F32_ONE - vt.v[3]) * v0.v[3] + v1.v[3] * vt.v[3];
	v.v[4] = (G_F32_ONE - vt.v[4]) * v0.v[4] + v1.v[4] * vt.v[4];
	v.v[5] = (G_F32_ONE - vt.v[5]) * v0.v[5] + v1.v[5] * vt.v[5];
	v.v[6] = (G_F32_ONE - vt.v[6]) * v0.v[6] + v1.v[6] * vt.v[6];

	return v;
}
vec7f32_t Vec7f32_LerpS(vec7f32_t v0, vec7f32_t v1, float t)
{
	vec7f32_t v;

	v.v[0] = (G_F32_ONE - t) * v0.v[0] + v1.v[0] * t;
	v.v[1] = (G_F32_ONE - t) * v0.v[1] + v1.v[1] * t;
	v.v[2] = (G_F32_ONE - t) * v0.v[2] + v1.v[2] * t;
	v.v[3] = (G_F32_ONE - t) * v0.v[3] + v1.v[3] * t;
	v.v[4] = (G_F32_ONE - t) * v0.v[4] + v1.v[4] * t;
	v.v[5] = (G_F32_ONE - t) * v0.v[5] + v1.v[5] * t;
	v.v[6] = (G_F32_ONE - t) * v0.v[6] + v1.v[6] * t;

	return v;
}
vec8f32_t Vec7f32_ToVec8f32(vec7f32_t v, float x0)
{
	vec8f32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = v.v[5];
	outv.v[6] = v.v[6];
	outv.v[7] = x0;

	return outv;
}
vec7u64_t Vec7u64_SetComponent(vec7u64_t v, int index, uint64_t value)
{
	v.v[index] = value;

	return v;
}
vec7u64_t Vec7u64_Vec(uint64_t x0, uint64_t x1, uint64_t x2, uint64_t x3, uint64_t x4, uint64_t x5, uint64_t x6)
{
	vec7u64_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;
	v.v[5] = x5;
	v.v[6] = x6;

	return v;
}
vec7u64_t Vec7u64_Add(vec7u64_t v0, vec7u64_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];
	v0.v[5] += v1.v[5];
	v0.v[6] += v1.v[6];

	return v0;
}
vec7u64_t Vec7u64_Sub(vec7u64_t v0, vec7u64_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];
	v0.v[5] -= v1.v[5];
	v0.v[6] -= v1.v[6];

	return v0;
}
uint64_t Vec7u64_GetComponent(vec7u64_t v, int index)
{
	return v.v[index];
}
vec7u64_t Vec7u64_Mul(vec7u64_t v0, vec7u64_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];
	v0.v[5] *= v1.v[5];
	v0.v[6] *= v1.v[6];

	return v0;
}
vec7u64_t Vec7u64_Div(vec7u64_t v0, vec7u64_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];
	v0.v[5] /= v1.v[5];
	v0.v[6] /= v1.v[6];

	return v0;
}
vec7u64_t Vec7u64_Scale(vec7u64_t v, uint64_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;
	v.v[5] *= scale;
	v.v[6] *= scale;

	return v;
}
vec7u64_t Vec7u64_DivScale(vec7u64_t v, uint64_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;
	v.v[5] /= divscale;
	v.v[6] /= divscale;

	return v;
}
vec7u64_t Vec7u64_MA(vec7u64_t v, vec7u64_t dir, uint64_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;
	v.v[5] += dir.v[5] * scale;
	v.v[6] += dir.v[6] * scale;

	return v;
}
vec7u64_t Vec7u64_DA(vec7u64_t v, vec7u64_t dir, uint64_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;
	v.v[5] += dir.v[5] / divscale;
	v.v[6] += dir.v[6] / divscale;

	return v;
}
uint64_t Vec7u64_Dot(vec7u64_t v0, vec7u64_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4] + v0.v[5] * v1.v[5] + v0.v[6] * v1.v[6];
}
uint64_t Vec7u64_LenSq(vec7u64_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4] + v.v[5] * v.v[5] + v.v[6] * v.v[6];
}
uint64_t Vec7u64_Len(vec7u64_t v)
{
	return sqrt(Vec7u64_LenSq(v));
}
vec7u64_t Vec7u64_Mod(vec7u64_t v0, vec7u64_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);
	v0.v[4] = (v0.v[4] % v1.v[4]);
	v0.v[5] = (v0.v[5] % v1.v[5]);
	v0.v[6] = (v0.v[6] % v1.v[6]);

	return v0;
}
vec7u64_t Vec7u64_ModS(vec7u64_t v0, uint64_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);
	v0.v[4] = (v0.v[4] % x);
	v0.v[5] = (v0.v[5] % x);
	v0.v[6] = (v0.v[6] % x);

	return v0;
}
vec7u64_t Vec7u64_Min(vec7u64_t v0, vec7u64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] < v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] < v1.v[6] ? v0.v[6] : v1.v[6];

	return v0;
}
vec7u64_t Vec7u64_Max(vec7u64_t v0, vec7u64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] > v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] > v1.v[6] ? v0.v[6] : v1.v[6];

	return v0;
}
vec7u64_t Vec7u64_MinS(vec7u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] < x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] < x ? v0.v[6] : x;

	return v0;
}
vec7u64_t Vec7u64_MaxS(vec7u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] > x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] > x ? v0.v[6] : x;

	return v0;
}
vec7u64_t Vec7u64_Clamp(vec7u64_t v, vec7u64_t min, vec7u64_t max)
{
	return Vec7u64_Max(Vec7u64_Min(v, max), min);
}
vec7u64_t Vec7u64_ClampS(vec7u64_t v, uint64_t min, uint64_t max)
{
	return Vec7u64_MaxS(Vec7u64_MinS(v, max), min);
}
vec7u64_t Vec7u64_CmpLT(vec7u64_t v0, vec7u64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] < v1.v[5] ? G_U64_ONE : G_U64_ZERO;
	v0.v[6] = v0.v[6] < v1.v[6] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec7u64_t Vec7u64_CmpLE(vec7u64_t v0, vec7u64_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] <= v1.v[5] ? G_U64_ONE : G_U64_ZERO;
	v0.v[6] = v0.v[6] <= v1.v[6] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec7u64_t Vec7u64_CmpEQ(vec7u64_t v0, vec7u64_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] == v1.v[5] ? G_U64_ONE : G_U64_ZERO;
	v0.v[6] = v0.v[6] == v1.v[6] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec7u64_t Vec7u64_CmpGT(vec7u64_t v0, vec7u64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] > v1.v[5] ? G_U64_ONE : G_U64_ZERO;
	v0.v[6] = v0.v[6] > v1.v[6] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec7u64_t Vec7u64_CmpGE(vec7u64_t v0, vec7u64_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] >= v1.v[5] ? G_U64_ONE : G_U64_ZERO;
	v0.v[6] = v0.v[6] >= v1.v[6] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec7u64_t Vec7u64_CmpNE(vec7u64_t v0, vec7u64_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] != v1.v[5] ? G_U64_ONE : G_U64_ZERO;
	v0.v[6] = v0.v[6] != v1.v[6] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec7u64_t Vec7u64_CmpLTS(vec7u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] < x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] < x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] < x ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] < x ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] < x ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] < x ? G_U64_ONE : G_U64_ZERO;
	v0.v[6] = v0.v[6] < x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec7u64_t Vec7u64_CmpLES(vec7u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] <= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[6] = v0.v[6] <= x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec7u64_t Vec7u64_CmpEQS(vec7u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] == x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] == x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] == x ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] == x ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] == x ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] == x ? G_U64_ONE : G_U64_ZERO;
	v0.v[6] = v0.v[6] == x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec7u64_t Vec7u64_CmpGTS(vec7u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] > x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] > x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] > x ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] > x ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] > x ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] > x ? G_U64_ONE : G_U64_ZERO;
	v0.v[6] = v0.v[6] > x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec7u64_t Vec7u64_CmpGES(vec7u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] >= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[6] = v0.v[6] >= x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec7u64_t Vec7u64_CmpNES(vec7u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] != x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] != x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] != x ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] != x ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] != x ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] != x ? G_U64_ONE : G_U64_ZERO;
	v0.v[6] = v0.v[6] != x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec7u64_t Vec7u64_Sign(vec7u64_t v)
{
	v.v[0] = v.v[0] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;
	v.v[1] = v.v[1] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;
	v.v[2] = v.v[2] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;
	v.v[3] = v.v[3] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;
	v.v[4] = v.v[4] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;
	v.v[5] = v.v[5] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;
	v.v[6] = v.v[6] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;

	return v;
}
vec7u64_t Vec7u64_SignPosNeg(vec7u64_t v)
{
	v.v[0] = v.v[0] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;
	v.v[1] = v.v[1] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;
	v.v[2] = v.v[2] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;
	v.v[3] = v.v[3] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;
	v.v[4] = v.v[4] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;
	v.v[5] = v.v[5] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;
	v.v[6] = v.v[6] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;

	return v;
}
vec7u64_t Vec7u64_Zero()
{
	return G_VEC7U64_T_ZERO;
}
vec7u64_t Vec7u64_One()
{
	return G_VEC7U64_T_ONE;
}
vec7u64_t Vec7u64_Cross(vec7u64_t v0, vec7u64_t v1, vec7u64_t v2, vec7u64_t v3, vec7u64_t v4, vec7u64_t v5)
{
	vec7u64_t v;
	mat7x7u64_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;
	mat.v[5] = v4;
	mat.v[6] = v5;

	for (i = 0; i < 7; i++)
		v.v[i] = Mat6x6u64_Det(Mat7x7u64_DeleteRowColumn(mat, 0, i));

	return v;
}
vec8u64_t Vec7u64_ToVec8u64(vec7u64_t v, uint64_t x0)
{
	vec8u64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = v.v[5];
	outv.v[6] = v.v[6];
	outv.v[7] = x0;

	return outv;
}
vec7i64_t Vec7i64_SetComponent(vec7i64_t v, int index, int64_t value)
{
	v.v[index] = value;

	return v;
}
vec7i64_t Vec7i64_Vec(int64_t x0, int64_t x1, int64_t x2, int64_t x3, int64_t x4, int64_t x5, int64_t x6)
{
	vec7i64_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;
	v.v[5] = x5;
	v.v[6] = x6;

	return v;
}
vec7i64_t Vec7i64_Add(vec7i64_t v0, vec7i64_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];
	v0.v[5] += v1.v[5];
	v0.v[6] += v1.v[6];

	return v0;
}
vec7i64_t Vec7i64_Sub(vec7i64_t v0, vec7i64_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];
	v0.v[5] -= v1.v[5];
	v0.v[6] -= v1.v[6];

	return v0;
}
int64_t Vec7i64_GetComponent(vec7i64_t v, int index)
{
	return v.v[index];
}
vec7i64_t Vec7i64_Mul(vec7i64_t v0, vec7i64_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];
	v0.v[5] *= v1.v[5];
	v0.v[6] *= v1.v[6];

	return v0;
}
vec7i64_t Vec7i64_Div(vec7i64_t v0, vec7i64_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];
	v0.v[5] /= v1.v[5];
	v0.v[6] /= v1.v[6];

	return v0;
}
vec7i64_t Vec7i64_Scale(vec7i64_t v, int64_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;
	v.v[5] *= scale;
	v.v[6] *= scale;

	return v;
}
vec7i64_t Vec7i64_DivScale(vec7i64_t v, int64_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;
	v.v[5] /= divscale;
	v.v[6] /= divscale;

	return v;
}
vec7i64_t Vec7i64_MA(vec7i64_t v, vec7i64_t dir, int64_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;
	v.v[5] += dir.v[5] * scale;
	v.v[6] += dir.v[6] * scale;

	return v;
}
vec7i64_t Vec7i64_DA(vec7i64_t v, vec7i64_t dir, int64_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;
	v.v[5] += dir.v[5] / divscale;
	v.v[6] += dir.v[6] / divscale;

	return v;
}
int64_t Vec7i64_Dot(vec7i64_t v0, vec7i64_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4] + v0.v[5] * v1.v[5] + v0.v[6] * v1.v[6];
}
int64_t Vec7i64_LenSq(vec7i64_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4] + v.v[5] * v.v[5] + v.v[6] * v.v[6];
}
int64_t Vec7i64_Len(vec7i64_t v)
{
	return sqrt(Vec7i64_LenSq(v));
}
vec7i64_t Vec7i64_Abs(vec7i64_t v)
{
	v.v[0] = (v.v[0] < 0 ? -v.v[0] : v.v[0]);
	v.v[1] = (v.v[1] < 0 ? -v.v[1] : v.v[1]);
	v.v[2] = (v.v[2] < 0 ? -v.v[2] : v.v[2]);
	v.v[3] = (v.v[3] < 0 ? -v.v[3] : v.v[3]);
	v.v[4] = (v.v[4] < 0 ? -v.v[4] : v.v[4]);
	v.v[5] = (v.v[5] < 0 ? -v.v[5] : v.v[5]);
	v.v[6] = (v.v[6] < 0 ? -v.v[6] : v.v[6]);

	return v;
}
vec7i64_t Vec7i64_Mod(vec7i64_t v0, vec7i64_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);
	v0.v[4] = (v0.v[4] % v1.v[4]);
	v0.v[5] = (v0.v[5] % v1.v[5]);
	v0.v[6] = (v0.v[6] % v1.v[6]);

	return v0;
}
vec7i64_t Vec7i64_ModS(vec7i64_t v0, int64_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);
	v0.v[4] = (v0.v[4] % x);
	v0.v[5] = (v0.v[5] % x);
	v0.v[6] = (v0.v[6] % x);

	return v0;
}
vec7i64_t Vec7i64_Min(vec7i64_t v0, vec7i64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] < v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] < v1.v[6] ? v0.v[6] : v1.v[6];

	return v0;
}
vec7i64_t Vec7i64_Max(vec7i64_t v0, vec7i64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] > v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] > v1.v[6] ? v0.v[6] : v1.v[6];

	return v0;
}
vec7i64_t Vec7i64_MinS(vec7i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] < x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] < x ? v0.v[6] : x;

	return v0;
}
vec7i64_t Vec7i64_MaxS(vec7i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] > x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] > x ? v0.v[6] : x;

	return v0;
}
vec7i64_t Vec7i64_Clamp(vec7i64_t v, vec7i64_t min, vec7i64_t max)
{
	return Vec7i64_Max(Vec7i64_Min(v, max), min);
}
vec7i64_t Vec7i64_ClampS(vec7i64_t v, int64_t min, int64_t max)
{
	return Vec7i64_MaxS(Vec7i64_MinS(v, max), min);
}
vec7i64_t Vec7i64_Neg(vec7i64_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];
	v.v[3] = -v.v[3];
	v.v[4] = -v.v[4];
	v.v[5] = -v.v[5];
	v.v[6] = -v.v[6];

	return v;
}
vec7i64_t Vec7i64_CmpLT(vec7i64_t v0, vec7i64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] < v1.v[5] ? G_I64_ONE : G_I64_ZERO;
	v0.v[6] = v0.v[6] < v1.v[6] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec7i64_t Vec7i64_CmpLE(vec7i64_t v0, vec7i64_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] <= v1.v[5] ? G_I64_ONE : G_I64_ZERO;
	v0.v[6] = v0.v[6] <= v1.v[6] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec7i64_t Vec7i64_CmpEQ(vec7i64_t v0, vec7i64_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] == v1.v[5] ? G_I64_ONE : G_I64_ZERO;
	v0.v[6] = v0.v[6] == v1.v[6] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec7i64_t Vec7i64_CmpGT(vec7i64_t v0, vec7i64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] > v1.v[5] ? G_I64_ONE : G_I64_ZERO;
	v0.v[6] = v0.v[6] > v1.v[6] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec7i64_t Vec7i64_CmpGE(vec7i64_t v0, vec7i64_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] >= v1.v[5] ? G_I64_ONE : G_I64_ZERO;
	v0.v[6] = v0.v[6] >= v1.v[6] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec7i64_t Vec7i64_CmpNE(vec7i64_t v0, vec7i64_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] != v1.v[5] ? G_I64_ONE : G_I64_ZERO;
	v0.v[6] = v0.v[6] != v1.v[6] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec7i64_t Vec7i64_CmpLTS(vec7i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] < x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] < x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] < x ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] < x ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] < x ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] < x ? G_I64_ONE : G_I64_ZERO;
	v0.v[6] = v0.v[6] < x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec7i64_t Vec7i64_CmpLES(vec7i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] <= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[6] = v0.v[6] <= x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec7i64_t Vec7i64_CmpEQS(vec7i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] == x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] == x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] == x ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] == x ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] == x ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] == x ? G_I64_ONE : G_I64_ZERO;
	v0.v[6] = v0.v[6] == x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec7i64_t Vec7i64_CmpGTS(vec7i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] > x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] > x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] > x ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] > x ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] > x ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] > x ? G_I64_ONE : G_I64_ZERO;
	v0.v[6] = v0.v[6] > x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec7i64_t Vec7i64_CmpGES(vec7i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] >= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[6] = v0.v[6] >= x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec7i64_t Vec7i64_CmpNES(vec7i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] != x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] != x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] != x ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] != x ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] != x ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] != x ? G_I64_ONE : G_I64_ZERO;
	v0.v[6] = v0.v[6] != x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec7i64_t Vec7i64_Sign(vec7i64_t v)
{
	v.v[0] = v.v[0] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;
	v.v[1] = v.v[1] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;
	v.v[2] = v.v[2] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;
	v.v[3] = v.v[3] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;
	v.v[4] = v.v[4] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;
	v.v[5] = v.v[5] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;
	v.v[6] = v.v[6] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;

	return v;
}
vec7i64_t Vec7i64_SignPosNeg(vec7i64_t v)
{
	v.v[0] = v.v[0] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;
	v.v[1] = v.v[1] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;
	v.v[2] = v.v[2] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;
	v.v[3] = v.v[3] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;
	v.v[4] = v.v[4] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;
	v.v[5] = v.v[5] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;
	v.v[6] = v.v[6] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;

	return v;
}
vec7i64_t Vec7i64_Zero()
{
	return G_VEC7I64_T_ZERO;
}
vec7i64_t Vec7i64_One()
{
	return G_VEC7I64_T_ONE;
}
vec7i64_t Vec7i64_NegOne()
{
	return Vec7i64_Neg(G_VEC7I64_T_ONE);
}
vec7i64_t Vec7i64_Cross(vec7i64_t v0, vec7i64_t v1, vec7i64_t v2, vec7i64_t v3, vec7i64_t v4, vec7i64_t v5)
{
	vec7i64_t v;
	mat7x7i64_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;
	mat.v[5] = v4;
	mat.v[6] = v5;

	for (i = 0; i < 7; i++)
		v.v[i] = Mat6x6i64_Det(Mat7x7i64_DeleteRowColumn(mat, 0, i));

	return v;
}
vec8i64_t Vec7i64_ToVec8i64(vec7i64_t v, int64_t x0)
{
	vec8i64_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = v.v[5];
	outv.v[6] = v.v[6];
	outv.v[7] = x0;

	return outv;
}
vec7u32_t Vec7u32_SetComponent(vec7u32_t v, int index, uint32_t value)
{
	v.v[index] = value;

	return v;
}
vec7u32_t Vec7u32_Vec(uint32_t x0, uint32_t x1, uint32_t x2, uint32_t x3, uint32_t x4, uint32_t x5, uint32_t x6)
{
	vec7u32_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;
	v.v[5] = x5;
	v.v[6] = x6;

	return v;
}
vec7u32_t Vec7u32_Add(vec7u32_t v0, vec7u32_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];
	v0.v[5] += v1.v[5];
	v0.v[6] += v1.v[6];

	return v0;
}
vec7u32_t Vec7u32_Sub(vec7u32_t v0, vec7u32_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];
	v0.v[5] -= v1.v[5];
	v0.v[6] -= v1.v[6];

	return v0;
}
uint32_t Vec7u32_GetComponent(vec7u32_t v, int index)
{
	return v.v[index];
}
vec7u32_t Vec7u32_Mul(vec7u32_t v0, vec7u32_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];
	v0.v[5] *= v1.v[5];
	v0.v[6] *= v1.v[6];

	return v0;
}
vec7u32_t Vec7u32_Div(vec7u32_t v0, vec7u32_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];
	v0.v[5] /= v1.v[5];
	v0.v[6] /= v1.v[6];

	return v0;
}
vec7u32_t Vec7u32_Scale(vec7u32_t v, uint32_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;
	v.v[5] *= scale;
	v.v[6] *= scale;

	return v;
}
vec7u32_t Vec7u32_DivScale(vec7u32_t v, uint32_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;
	v.v[5] /= divscale;
	v.v[6] /= divscale;

	return v;
}
vec7u32_t Vec7u32_MA(vec7u32_t v, vec7u32_t dir, uint32_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;
	v.v[5] += dir.v[5] * scale;
	v.v[6] += dir.v[6] * scale;

	return v;
}
vec7u32_t Vec7u32_DA(vec7u32_t v, vec7u32_t dir, uint32_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;
	v.v[5] += dir.v[5] / divscale;
	v.v[6] += dir.v[6] / divscale;

	return v;
}
uint32_t Vec7u32_Dot(vec7u32_t v0, vec7u32_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4] + v0.v[5] * v1.v[5] + v0.v[6] * v1.v[6];
}
uint32_t Vec7u32_LenSq(vec7u32_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4] + v.v[5] * v.v[5] + v.v[6] * v.v[6];
}
uint32_t Vec7u32_Len(vec7u32_t v)
{
	return sqrtf(Vec7u32_LenSq(v));
}
vec7u32_t Vec7u32_Mod(vec7u32_t v0, vec7u32_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);
	v0.v[4] = (v0.v[4] % v1.v[4]);
	v0.v[5] = (v0.v[5] % v1.v[5]);
	v0.v[6] = (v0.v[6] % v1.v[6]);

	return v0;
}
vec7u32_t Vec7u32_ModS(vec7u32_t v0, uint32_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);
	v0.v[4] = (v0.v[4] % x);
	v0.v[5] = (v0.v[5] % x);
	v0.v[6] = (v0.v[6] % x);

	return v0;
}
vec7u32_t Vec7u32_Min(vec7u32_t v0, vec7u32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] < v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] < v1.v[6] ? v0.v[6] : v1.v[6];

	return v0;
}
vec7u32_t Vec7u32_Max(vec7u32_t v0, vec7u32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] > v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] > v1.v[6] ? v0.v[6] : v1.v[6];

	return v0;
}
vec7u32_t Vec7u32_MinS(vec7u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] < x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] < x ? v0.v[6] : x;

	return v0;
}
vec7u32_t Vec7u32_MaxS(vec7u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] > x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] > x ? v0.v[6] : x;

	return v0;
}
vec7u32_t Vec7u32_Clamp(vec7u32_t v, vec7u32_t min, vec7u32_t max)
{
	return Vec7u32_Max(Vec7u32_Min(v, max), min);
}
vec7u32_t Vec7u32_ClampS(vec7u32_t v, uint32_t min, uint32_t max)
{
	return Vec7u32_MaxS(Vec7u32_MinS(v, max), min);
}
vec7u32_t Vec7u32_CmpLT(vec7u32_t v0, vec7u32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] < v1.v[5] ? G_U32_ONE : G_U32_ZERO;
	v0.v[6] = v0.v[6] < v1.v[6] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec7u32_t Vec7u32_CmpLE(vec7u32_t v0, vec7u32_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] <= v1.v[5] ? G_U32_ONE : G_U32_ZERO;
	v0.v[6] = v0.v[6] <= v1.v[6] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec7u32_t Vec7u32_CmpEQ(vec7u32_t v0, vec7u32_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] == v1.v[5] ? G_U32_ONE : G_U32_ZERO;
	v0.v[6] = v0.v[6] == v1.v[6] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec7u32_t Vec7u32_CmpGT(vec7u32_t v0, vec7u32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] > v1.v[5] ? G_U32_ONE : G_U32_ZERO;
	v0.v[6] = v0.v[6] > v1.v[6] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec7u32_t Vec7u32_CmpGE(vec7u32_t v0, vec7u32_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] >= v1.v[5] ? G_U32_ONE : G_U32_ZERO;
	v0.v[6] = v0.v[6] >= v1.v[6] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec7u32_t Vec7u32_CmpNE(vec7u32_t v0, vec7u32_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] != v1.v[5] ? G_U32_ONE : G_U32_ZERO;
	v0.v[6] = v0.v[6] != v1.v[6] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec7u32_t Vec7u32_CmpLTS(vec7u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] < x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] < x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] < x ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] < x ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] < x ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] < x ? G_U32_ONE : G_U32_ZERO;
	v0.v[6] = v0.v[6] < x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec7u32_t Vec7u32_CmpLES(vec7u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] <= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[6] = v0.v[6] <= x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec7u32_t Vec7u32_CmpEQS(vec7u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] == x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] == x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] == x ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] == x ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] == x ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] == x ? G_U32_ONE : G_U32_ZERO;
	v0.v[6] = v0.v[6] == x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec7u32_t Vec7u32_CmpGTS(vec7u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] > x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] > x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] > x ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] > x ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] > x ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] > x ? G_U32_ONE : G_U32_ZERO;
	v0.v[6] = v0.v[6] > x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec7u32_t Vec7u32_CmpGES(vec7u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] >= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[6] = v0.v[6] >= x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec7u32_t Vec7u32_CmpNES(vec7u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] != x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] != x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] != x ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] != x ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] != x ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] != x ? G_U32_ONE : G_U32_ZERO;
	v0.v[6] = v0.v[6] != x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec7u32_t Vec7u32_Sign(vec7u32_t v)
{
	v.v[0] = v.v[0] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;
	v.v[1] = v.v[1] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;
	v.v[2] = v.v[2] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;
	v.v[3] = v.v[3] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;
	v.v[4] = v.v[4] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;
	v.v[5] = v.v[5] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;
	v.v[6] = v.v[6] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;

	return v;
}
vec7u32_t Vec7u32_SignPosNeg(vec7u32_t v)
{
	v.v[0] = v.v[0] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;
	v.v[1] = v.v[1] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;
	v.v[2] = v.v[2] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;
	v.v[3] = v.v[3] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;
	v.v[4] = v.v[4] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;
	v.v[5] = v.v[5] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;
	v.v[6] = v.v[6] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;

	return v;
}
vec7u32_t Vec7u32_Zero()
{
	return G_VEC7U32_T_ZERO;
}
vec7u32_t Vec7u32_One()
{
	return G_VEC7U32_T_ONE;
}
vec7u32_t Vec7u32_Cross(vec7u32_t v0, vec7u32_t v1, vec7u32_t v2, vec7u32_t v3, vec7u32_t v4, vec7u32_t v5)
{
	vec7u32_t v;
	mat7x7u32_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;
	mat.v[5] = v4;
	mat.v[6] = v5;

	for (i = 0; i < 7; i++)
		v.v[i] = Mat6x6u32_Det(Mat7x7u32_DeleteRowColumn(mat, 0, i));

	return v;
}
vec8u32_t Vec7u32_ToVec8u32(vec7u32_t v, uint32_t x0)
{
	vec8u32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = v.v[5];
	outv.v[6] = v.v[6];
	outv.v[7] = x0;

	return outv;
}
vec7i32_t Vec7i32_SetComponent(vec7i32_t v, int index, int32_t value)
{
	v.v[index] = value;

	return v;
}
vec7i32_t Vec7i32_Vec(int32_t x0, int32_t x1, int32_t x2, int32_t x3, int32_t x4, int32_t x5, int32_t x6)
{
	vec7i32_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;
	v.v[5] = x5;
	v.v[6] = x6;

	return v;
}
vec7i32_t Vec7i32_Add(vec7i32_t v0, vec7i32_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];
	v0.v[5] += v1.v[5];
	v0.v[6] += v1.v[6];

	return v0;
}
vec7i32_t Vec7i32_Sub(vec7i32_t v0, vec7i32_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];
	v0.v[5] -= v1.v[5];
	v0.v[6] -= v1.v[6];

	return v0;
}
int32_t Vec7i32_GetComponent(vec7i32_t v, int index)
{
	return v.v[index];
}
vec7i32_t Vec7i32_Mul(vec7i32_t v0, vec7i32_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];
	v0.v[5] *= v1.v[5];
	v0.v[6] *= v1.v[6];

	return v0;
}
vec7i32_t Vec7i32_Div(vec7i32_t v0, vec7i32_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];
	v0.v[5] /= v1.v[5];
	v0.v[6] /= v1.v[6];

	return v0;
}
vec7i32_t Vec7i32_Scale(vec7i32_t v, int32_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;
	v.v[5] *= scale;
	v.v[6] *= scale;

	return v;
}
vec7i32_t Vec7i32_DivScale(vec7i32_t v, int32_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;
	v.v[5] /= divscale;
	v.v[6] /= divscale;

	return v;
}
vec7i32_t Vec7i32_MA(vec7i32_t v, vec7i32_t dir, int32_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;
	v.v[5] += dir.v[5] * scale;
	v.v[6] += dir.v[6] * scale;

	return v;
}
vec7i32_t Vec7i32_DA(vec7i32_t v, vec7i32_t dir, int32_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;
	v.v[5] += dir.v[5] / divscale;
	v.v[6] += dir.v[6] / divscale;

	return v;
}
int32_t Vec7i32_Dot(vec7i32_t v0, vec7i32_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4] + v0.v[5] * v1.v[5] + v0.v[6] * v1.v[6];
}
int32_t Vec7i32_LenSq(vec7i32_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4] + v.v[5] * v.v[5] + v.v[6] * v.v[6];
}
int32_t Vec7i32_Len(vec7i32_t v)
{
	return sqrtf(Vec7i32_LenSq(v));
}
vec7i32_t Vec7i32_Abs(vec7i32_t v)
{
	v.v[0] = (v.v[0] < 0 ? -v.v[0] : v.v[0]);
	v.v[1] = (v.v[1] < 0 ? -v.v[1] : v.v[1]);
	v.v[2] = (v.v[2] < 0 ? -v.v[2] : v.v[2]);
	v.v[3] = (v.v[3] < 0 ? -v.v[3] : v.v[3]);
	v.v[4] = (v.v[4] < 0 ? -v.v[4] : v.v[4]);
	v.v[5] = (v.v[5] < 0 ? -v.v[5] : v.v[5]);
	v.v[6] = (v.v[6] < 0 ? -v.v[6] : v.v[6]);

	return v;
}
vec7i32_t Vec7i32_Mod(vec7i32_t v0, vec7i32_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);
	v0.v[4] = (v0.v[4] % v1.v[4]);
	v0.v[5] = (v0.v[5] % v1.v[5]);
	v0.v[6] = (v0.v[6] % v1.v[6]);

	return v0;
}
vec7i32_t Vec7i32_ModS(vec7i32_t v0, int32_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);
	v0.v[4] = (v0.v[4] % x);
	v0.v[5] = (v0.v[5] % x);
	v0.v[6] = (v0.v[6] % x);

	return v0;
}
vec7i32_t Vec7i32_Min(vec7i32_t v0, vec7i32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] < v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] < v1.v[6] ? v0.v[6] : v1.v[6];

	return v0;
}
vec7i32_t Vec7i32_Max(vec7i32_t v0, vec7i32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] > v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] > v1.v[6] ? v0.v[6] : v1.v[6];

	return v0;
}
vec7i32_t Vec7i32_MinS(vec7i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] < x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] < x ? v0.v[6] : x;

	return v0;
}
vec7i32_t Vec7i32_MaxS(vec7i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] > x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] > x ? v0.v[6] : x;

	return v0;
}
vec7i32_t Vec7i32_Clamp(vec7i32_t v, vec7i32_t min, vec7i32_t max)
{
	return Vec7i32_Max(Vec7i32_Min(v, max), min);
}
vec7i32_t Vec7i32_ClampS(vec7i32_t v, int32_t min, int32_t max)
{
	return Vec7i32_MaxS(Vec7i32_MinS(v, max), min);
}
vec7i32_t Vec7i32_Neg(vec7i32_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];
	v.v[3] = -v.v[3];
	v.v[4] = -v.v[4];
	v.v[5] = -v.v[5];
	v.v[6] = -v.v[6];

	return v;
}
vec7i32_t Vec7i32_CmpLT(vec7i32_t v0, vec7i32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] < v1.v[5] ? G_I32_ONE : G_I32_ZERO;
	v0.v[6] = v0.v[6] < v1.v[6] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec7i32_t Vec7i32_CmpLE(vec7i32_t v0, vec7i32_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] <= v1.v[5] ? G_I32_ONE : G_I32_ZERO;
	v0.v[6] = v0.v[6] <= v1.v[6] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec7i32_t Vec7i32_CmpEQ(vec7i32_t v0, vec7i32_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] == v1.v[5] ? G_I32_ONE : G_I32_ZERO;
	v0.v[6] = v0.v[6] == v1.v[6] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec7i32_t Vec7i32_CmpGT(vec7i32_t v0, vec7i32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] > v1.v[5] ? G_I32_ONE : G_I32_ZERO;
	v0.v[6] = v0.v[6] > v1.v[6] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec7i32_t Vec7i32_CmpGE(vec7i32_t v0, vec7i32_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] >= v1.v[5] ? G_I32_ONE : G_I32_ZERO;
	v0.v[6] = v0.v[6] >= v1.v[6] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec7i32_t Vec7i32_CmpNE(vec7i32_t v0, vec7i32_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] != v1.v[5] ? G_I32_ONE : G_I32_ZERO;
	v0.v[6] = v0.v[6] != v1.v[6] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec7i32_t Vec7i32_CmpLTS(vec7i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] < x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] < x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] < x ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] < x ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] < x ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] < x ? G_I32_ONE : G_I32_ZERO;
	v0.v[6] = v0.v[6] < x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec7i32_t Vec7i32_CmpLES(vec7i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] <= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[6] = v0.v[6] <= x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec7i32_t Vec7i32_CmpEQS(vec7i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] == x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] == x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] == x ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] == x ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] == x ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] == x ? G_I32_ONE : G_I32_ZERO;
	v0.v[6] = v0.v[6] == x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec7i32_t Vec7i32_CmpGTS(vec7i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] > x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] > x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] > x ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] > x ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] > x ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] > x ? G_I32_ONE : G_I32_ZERO;
	v0.v[6] = v0.v[6] > x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec7i32_t Vec7i32_CmpGES(vec7i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] >= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[6] = v0.v[6] >= x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec7i32_t Vec7i32_CmpNES(vec7i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] != x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] != x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] != x ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] != x ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] != x ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] != x ? G_I32_ONE : G_I32_ZERO;
	v0.v[6] = v0.v[6] != x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec7i32_t Vec7i32_Sign(vec7i32_t v)
{
	v.v[0] = v.v[0] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;
	v.v[1] = v.v[1] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;
	v.v[2] = v.v[2] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;
	v.v[3] = v.v[3] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;
	v.v[4] = v.v[4] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;
	v.v[5] = v.v[5] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;
	v.v[6] = v.v[6] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;

	return v;
}
vec7i32_t Vec7i32_SignPosNeg(vec7i32_t v)
{
	v.v[0] = v.v[0] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;
	v.v[1] = v.v[1] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;
	v.v[2] = v.v[2] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;
	v.v[3] = v.v[3] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;
	v.v[4] = v.v[4] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;
	v.v[5] = v.v[5] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;
	v.v[6] = v.v[6] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;

	return v;
}
vec7i32_t Vec7i32_Zero()
{
	return G_VEC7I32_T_ZERO;
}
vec7i32_t Vec7i32_One()
{
	return G_VEC7I32_T_ONE;
}
vec7i32_t Vec7i32_NegOne()
{
	return Vec7i32_Neg(G_VEC7I32_T_ONE);
}
vec7i32_t Vec7i32_Cross(vec7i32_t v0, vec7i32_t v1, vec7i32_t v2, vec7i32_t v3, vec7i32_t v4, vec7i32_t v5)
{
	vec7i32_t v;
	mat7x7i32_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;
	mat.v[5] = v4;
	mat.v[6] = v5;

	for (i = 0; i < 7; i++)
		v.v[i] = Mat6x6i32_Det(Mat7x7i32_DeleteRowColumn(mat, 0, i));

	return v;
}
vec8i32_t Vec7i32_ToVec8i32(vec7i32_t v, int32_t x0)
{
	vec8i32_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = v.v[5];
	outv.v[6] = v.v[6];
	outv.v[7] = x0;

	return outv;
}
vec7u16_t Vec7u16_SetComponent(vec7u16_t v, int index, uint16_t value)
{
	v.v[index] = value;

	return v;
}
vec7u16_t Vec7u16_Vec(uint16_t x0, uint16_t x1, uint16_t x2, uint16_t x3, uint16_t x4, uint16_t x5, uint16_t x6)
{
	vec7u16_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;
	v.v[5] = x5;
	v.v[6] = x6;

	return v;
}
vec7u16_t Vec7u16_Add(vec7u16_t v0, vec7u16_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];
	v0.v[5] += v1.v[5];
	v0.v[6] += v1.v[6];

	return v0;
}
vec7u16_t Vec7u16_Sub(vec7u16_t v0, vec7u16_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];
	v0.v[5] -= v1.v[5];
	v0.v[6] -= v1.v[6];

	return v0;
}
uint16_t Vec7u16_GetComponent(vec7u16_t v, int index)
{
	return v.v[index];
}
vec7u16_t Vec7u16_Mul(vec7u16_t v0, vec7u16_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];
	v0.v[5] *= v1.v[5];
	v0.v[6] *= v1.v[6];

	return v0;
}
vec7u16_t Vec7u16_Div(vec7u16_t v0, vec7u16_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];
	v0.v[5] /= v1.v[5];
	v0.v[6] /= v1.v[6];

	return v0;
}
vec7u16_t Vec7u16_Scale(vec7u16_t v, uint16_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;
	v.v[5] *= scale;
	v.v[6] *= scale;

	return v;
}
vec7u16_t Vec7u16_DivScale(vec7u16_t v, uint16_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;
	v.v[5] /= divscale;
	v.v[6] /= divscale;

	return v;
}
vec7u16_t Vec7u16_MA(vec7u16_t v, vec7u16_t dir, uint16_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;
	v.v[5] += dir.v[5] * scale;
	v.v[6] += dir.v[6] * scale;

	return v;
}
vec7u16_t Vec7u16_DA(vec7u16_t v, vec7u16_t dir, uint16_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;
	v.v[5] += dir.v[5] / divscale;
	v.v[6] += dir.v[6] / divscale;

	return v;
}
uint16_t Vec7u16_Dot(vec7u16_t v0, vec7u16_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4] + v0.v[5] * v1.v[5] + v0.v[6] * v1.v[6];
}
uint16_t Vec7u16_LenSq(vec7u16_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4] + v.v[5] * v.v[5] + v.v[6] * v.v[6];
}
uint16_t Vec7u16_Len(vec7u16_t v)
{
	return sqrtf(Vec7u16_LenSq(v));
}
vec7u16_t Vec7u16_Mod(vec7u16_t v0, vec7u16_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);
	v0.v[4] = (v0.v[4] % v1.v[4]);
	v0.v[5] = (v0.v[5] % v1.v[5]);
	v0.v[6] = (v0.v[6] % v1.v[6]);

	return v0;
}
vec7u16_t Vec7u16_ModS(vec7u16_t v0, uint16_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);
	v0.v[4] = (v0.v[4] % x);
	v0.v[5] = (v0.v[5] % x);
	v0.v[6] = (v0.v[6] % x);

	return v0;
}
vec7u16_t Vec7u16_Min(vec7u16_t v0, vec7u16_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] < v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] < v1.v[6] ? v0.v[6] : v1.v[6];

	return v0;
}
vec7u16_t Vec7u16_Max(vec7u16_t v0, vec7u16_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] > v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] > v1.v[6] ? v0.v[6] : v1.v[6];

	return v0;
}
vec7u16_t Vec7u16_MinS(vec7u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] < x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] < x ? v0.v[6] : x;

	return v0;
}
vec7u16_t Vec7u16_MaxS(vec7u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] > x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] > x ? v0.v[6] : x;

	return v0;
}
vec7u16_t Vec7u16_Clamp(vec7u16_t v, vec7u16_t min, vec7u16_t max)
{
	return Vec7u16_Max(Vec7u16_Min(v, max), min);
}
vec7u16_t Vec7u16_ClampS(vec7u16_t v, uint16_t min, uint16_t max)
{
	return Vec7u16_MaxS(Vec7u16_MinS(v, max), min);
}
vec7u16_t Vec7u16_CmpLT(vec7u16_t v0, vec7u16_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] < v1.v[5] ? G_U16_ONE : G_U16_ZERO;
	v0.v[6] = v0.v[6] < v1.v[6] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec7u16_t Vec7u16_CmpLE(vec7u16_t v0, vec7u16_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] <= v1.v[5] ? G_U16_ONE : G_U16_ZERO;
	v0.v[6] = v0.v[6] <= v1.v[6] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec7u16_t Vec7u16_CmpEQ(vec7u16_t v0, vec7u16_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] == v1.v[5] ? G_U16_ONE : G_U16_ZERO;
	v0.v[6] = v0.v[6] == v1.v[6] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec7u16_t Vec7u16_CmpGT(vec7u16_t v0, vec7u16_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] > v1.v[5] ? G_U16_ONE : G_U16_ZERO;
	v0.v[6] = v0.v[6] > v1.v[6] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec7u16_t Vec7u16_CmpGE(vec7u16_t v0, vec7u16_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] >= v1.v[5] ? G_U16_ONE : G_U16_ZERO;
	v0.v[6] = v0.v[6] >= v1.v[6] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec7u16_t Vec7u16_CmpNE(vec7u16_t v0, vec7u16_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] != v1.v[5] ? G_U16_ONE : G_U16_ZERO;
	v0.v[6] = v0.v[6] != v1.v[6] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec7u16_t Vec7u16_CmpLTS(vec7u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] < x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] < x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] < x ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] < x ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] < x ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] < x ? G_U16_ONE : G_U16_ZERO;
	v0.v[6] = v0.v[6] < x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec7u16_t Vec7u16_CmpLES(vec7u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] <= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[6] = v0.v[6] <= x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec7u16_t Vec7u16_CmpEQS(vec7u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] == x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] == x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] == x ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] == x ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] == x ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] == x ? G_U16_ONE : G_U16_ZERO;
	v0.v[6] = v0.v[6] == x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec7u16_t Vec7u16_CmpGTS(vec7u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] > x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] > x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] > x ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] > x ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] > x ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] > x ? G_U16_ONE : G_U16_ZERO;
	v0.v[6] = v0.v[6] > x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec7u16_t Vec7u16_CmpGES(vec7u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] >= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[6] = v0.v[6] >= x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec7u16_t Vec7u16_CmpNES(vec7u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] != x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] != x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] != x ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] != x ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] != x ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] != x ? G_U16_ONE : G_U16_ZERO;
	v0.v[6] = v0.v[6] != x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec7u16_t Vec7u16_Sign(vec7u16_t v)
{
	v.v[0] = v.v[0] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;
	v.v[1] = v.v[1] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;
	v.v[2] = v.v[2] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;
	v.v[3] = v.v[3] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;
	v.v[4] = v.v[4] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;
	v.v[5] = v.v[5] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;
	v.v[6] = v.v[6] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;

	return v;
}
vec7u16_t Vec7u16_SignPosNeg(vec7u16_t v)
{
	v.v[0] = v.v[0] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;
	v.v[1] = v.v[1] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;
	v.v[2] = v.v[2] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;
	v.v[3] = v.v[3] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;
	v.v[4] = v.v[4] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;
	v.v[5] = v.v[5] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;
	v.v[6] = v.v[6] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;

	return v;
}
vec7u16_t Vec7u16_Zero()
{
	return G_VEC7U16_T_ZERO;
}
vec7u16_t Vec7u16_One()
{
	return G_VEC7U16_T_ONE;
}
vec7u16_t Vec7u16_Cross(vec7u16_t v0, vec7u16_t v1, vec7u16_t v2, vec7u16_t v3, vec7u16_t v4, vec7u16_t v5)
{
	vec7u16_t v;
	mat7x7u16_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;
	mat.v[5] = v4;
	mat.v[6] = v5;

	for (i = 0; i < 7; i++)
		v.v[i] = Mat6x6u16_Det(Mat7x7u16_DeleteRowColumn(mat, 0, i));

	return v;
}
vec8u16_t Vec7u16_ToVec8u16(vec7u16_t v, uint16_t x0)
{
	vec8u16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = v.v[5];
	outv.v[6] = v.v[6];
	outv.v[7] = x0;

	return outv;
}
vec7i16_t Vec7i16_SetComponent(vec7i16_t v, int index, int16_t value)
{
	v.v[index] = value;

	return v;
}
vec7i16_t Vec7i16_Vec(int16_t x0, int16_t x1, int16_t x2, int16_t x3, int16_t x4, int16_t x5, int16_t x6)
{
	vec7i16_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;
	v.v[5] = x5;
	v.v[6] = x6;

	return v;
}
vec7i16_t Vec7i16_Add(vec7i16_t v0, vec7i16_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];
	v0.v[5] += v1.v[5];
	v0.v[6] += v1.v[6];

	return v0;
}
vec7i16_t Vec7i16_Sub(vec7i16_t v0, vec7i16_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];
	v0.v[5] -= v1.v[5];
	v0.v[6] -= v1.v[6];

	return v0;
}
int16_t Vec7i16_GetComponent(vec7i16_t v, int index)
{
	return v.v[index];
}
vec7i16_t Vec7i16_Mul(vec7i16_t v0, vec7i16_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];
	v0.v[5] *= v1.v[5];
	v0.v[6] *= v1.v[6];

	return v0;
}
vec7i16_t Vec7i16_Div(vec7i16_t v0, vec7i16_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];
	v0.v[5] /= v1.v[5];
	v0.v[6] /= v1.v[6];

	return v0;
}
vec7i16_t Vec7i16_Scale(vec7i16_t v, int16_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;
	v.v[5] *= scale;
	v.v[6] *= scale;

	return v;
}
vec7i16_t Vec7i16_DivScale(vec7i16_t v, int16_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;
	v.v[5] /= divscale;
	v.v[6] /= divscale;

	return v;
}
vec7i16_t Vec7i16_MA(vec7i16_t v, vec7i16_t dir, int16_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;
	v.v[5] += dir.v[5] * scale;
	v.v[6] += dir.v[6] * scale;

	return v;
}
vec7i16_t Vec7i16_DA(vec7i16_t v, vec7i16_t dir, int16_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;
	v.v[5] += dir.v[5] / divscale;
	v.v[6] += dir.v[6] / divscale;

	return v;
}
int16_t Vec7i16_Dot(vec7i16_t v0, vec7i16_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4] + v0.v[5] * v1.v[5] + v0.v[6] * v1.v[6];
}
int16_t Vec7i16_LenSq(vec7i16_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4] + v.v[5] * v.v[5] + v.v[6] * v.v[6];
}
int16_t Vec7i16_Len(vec7i16_t v)
{
	return sqrtf(Vec7i16_LenSq(v));
}
vec7i16_t Vec7i16_Abs(vec7i16_t v)
{
	v.v[0] = (v.v[0] < 0 ? -v.v[0] : v.v[0]);
	v.v[1] = (v.v[1] < 0 ? -v.v[1] : v.v[1]);
	v.v[2] = (v.v[2] < 0 ? -v.v[2] : v.v[2]);
	v.v[3] = (v.v[3] < 0 ? -v.v[3] : v.v[3]);
	v.v[4] = (v.v[4] < 0 ? -v.v[4] : v.v[4]);
	v.v[5] = (v.v[5] < 0 ? -v.v[5] : v.v[5]);
	v.v[6] = (v.v[6] < 0 ? -v.v[6] : v.v[6]);

	return v;
}
vec7i16_t Vec7i16_Mod(vec7i16_t v0, vec7i16_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);
	v0.v[4] = (v0.v[4] % v1.v[4]);
	v0.v[5] = (v0.v[5] % v1.v[5]);
	v0.v[6] = (v0.v[6] % v1.v[6]);

	return v0;
}
vec7i16_t Vec7i16_ModS(vec7i16_t v0, int16_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);
	v0.v[4] = (v0.v[4] % x);
	v0.v[5] = (v0.v[5] % x);
	v0.v[6] = (v0.v[6] % x);

	return v0;
}
vec7i16_t Vec7i16_Min(vec7i16_t v0, vec7i16_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] < v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] < v1.v[6] ? v0.v[6] : v1.v[6];

	return v0;
}
vec7i16_t Vec7i16_Max(vec7i16_t v0, vec7i16_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] > v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] > v1.v[6] ? v0.v[6] : v1.v[6];

	return v0;
}
vec7i16_t Vec7i16_MinS(vec7i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] < x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] < x ? v0.v[6] : x;

	return v0;
}
vec7i16_t Vec7i16_MaxS(vec7i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] > x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] > x ? v0.v[6] : x;

	return v0;
}
vec7i16_t Vec7i16_Clamp(vec7i16_t v, vec7i16_t min, vec7i16_t max)
{
	return Vec7i16_Max(Vec7i16_Min(v, max), min);
}
vec7i16_t Vec7i16_ClampS(vec7i16_t v, int16_t min, int16_t max)
{
	return Vec7i16_MaxS(Vec7i16_MinS(v, max), min);
}
vec7i16_t Vec7i16_Neg(vec7i16_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];
	v.v[3] = -v.v[3];
	v.v[4] = -v.v[4];
	v.v[5] = -v.v[5];
	v.v[6] = -v.v[6];

	return v;
}
vec7i16_t Vec7i16_CmpLT(vec7i16_t v0, vec7i16_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] < v1.v[5] ? G_I16_ONE : G_I16_ZERO;
	v0.v[6] = v0.v[6] < v1.v[6] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec7i16_t Vec7i16_CmpLE(vec7i16_t v0, vec7i16_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] <= v1.v[5] ? G_I16_ONE : G_I16_ZERO;
	v0.v[6] = v0.v[6] <= v1.v[6] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec7i16_t Vec7i16_CmpEQ(vec7i16_t v0, vec7i16_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] == v1.v[5] ? G_I16_ONE : G_I16_ZERO;
	v0.v[6] = v0.v[6] == v1.v[6] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec7i16_t Vec7i16_CmpGT(vec7i16_t v0, vec7i16_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] > v1.v[5] ? G_I16_ONE : G_I16_ZERO;
	v0.v[6] = v0.v[6] > v1.v[6] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec7i16_t Vec7i16_CmpGE(vec7i16_t v0, vec7i16_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] >= v1.v[5] ? G_I16_ONE : G_I16_ZERO;
	v0.v[6] = v0.v[6] >= v1.v[6] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec7i16_t Vec7i16_CmpNE(vec7i16_t v0, vec7i16_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] != v1.v[5] ? G_I16_ONE : G_I16_ZERO;
	v0.v[6] = v0.v[6] != v1.v[6] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec7i16_t Vec7i16_CmpLTS(vec7i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] < x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] < x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] < x ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] < x ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] < x ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] < x ? G_I16_ONE : G_I16_ZERO;
	v0.v[6] = v0.v[6] < x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec7i16_t Vec7i16_CmpLES(vec7i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] <= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[6] = v0.v[6] <= x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec7i16_t Vec7i16_CmpEQS(vec7i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] == x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] == x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] == x ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] == x ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] == x ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] == x ? G_I16_ONE : G_I16_ZERO;
	v0.v[6] = v0.v[6] == x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec7i16_t Vec7i16_CmpGTS(vec7i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] > x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] > x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] > x ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] > x ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] > x ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] > x ? G_I16_ONE : G_I16_ZERO;
	v0.v[6] = v0.v[6] > x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec7i16_t Vec7i16_CmpGES(vec7i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] >= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[6] = v0.v[6] >= x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec7i16_t Vec7i16_CmpNES(vec7i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] != x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] != x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] != x ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] != x ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] != x ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] != x ? G_I16_ONE : G_I16_ZERO;
	v0.v[6] = v0.v[6] != x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec7i16_t Vec7i16_Sign(vec7i16_t v)
{
	v.v[0] = v.v[0] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;
	v.v[1] = v.v[1] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;
	v.v[2] = v.v[2] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;
	v.v[3] = v.v[3] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;
	v.v[4] = v.v[4] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;
	v.v[5] = v.v[5] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;
	v.v[6] = v.v[6] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;

	return v;
}
vec7i16_t Vec7i16_SignPosNeg(vec7i16_t v)
{
	v.v[0] = v.v[0] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;
	v.v[1] = v.v[1] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;
	v.v[2] = v.v[2] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;
	v.v[3] = v.v[3] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;
	v.v[4] = v.v[4] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;
	v.v[5] = v.v[5] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;
	v.v[6] = v.v[6] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;

	return v;
}
vec7i16_t Vec7i16_Zero()
{
	return G_VEC7I16_T_ZERO;
}
vec7i16_t Vec7i16_One()
{
	return G_VEC7I16_T_ONE;
}
vec7i16_t Vec7i16_NegOne()
{
	return Vec7i16_Neg(G_VEC7I16_T_ONE);
}
vec7i16_t Vec7i16_Cross(vec7i16_t v0, vec7i16_t v1, vec7i16_t v2, vec7i16_t v3, vec7i16_t v4, vec7i16_t v5)
{
	vec7i16_t v;
	mat7x7i16_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;
	mat.v[5] = v4;
	mat.v[6] = v5;

	for (i = 0; i < 7; i++)
		v.v[i] = Mat6x6i16_Det(Mat7x7i16_DeleteRowColumn(mat, 0, i));

	return v;
}
vec8i16_t Vec7i16_ToVec8i16(vec7i16_t v, int16_t x0)
{
	vec8i16_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = v.v[5];
	outv.v[6] = v.v[6];
	outv.v[7] = x0;

	return outv;
}
vec7u8_t Vec7u8_SetComponent(vec7u8_t v, int index, uint8_t value)
{
	v.v[index] = value;

	return v;
}
vec7u8_t Vec7u8_Vec(uint8_t x0, uint8_t x1, uint8_t x2, uint8_t x3, uint8_t x4, uint8_t x5, uint8_t x6)
{
	vec7u8_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;
	v.v[5] = x5;
	v.v[6] = x6;

	return v;
}
vec7u8_t Vec7u8_Add(vec7u8_t v0, vec7u8_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];
	v0.v[5] += v1.v[5];
	v0.v[6] += v1.v[6];

	return v0;
}
vec7u8_t Vec7u8_Sub(vec7u8_t v0, vec7u8_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];
	v0.v[5] -= v1.v[5];
	v0.v[6] -= v1.v[6];

	return v0;
}
uint8_t Vec7u8_GetComponent(vec7u8_t v, int index)
{
	return v.v[index];
}
vec7u8_t Vec7u8_Mul(vec7u8_t v0, vec7u8_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];
	v0.v[5] *= v1.v[5];
	v0.v[6] *= v1.v[6];

	return v0;
}
vec7u8_t Vec7u8_Div(vec7u8_t v0, vec7u8_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];
	v0.v[5] /= v1.v[5];
	v0.v[6] /= v1.v[6];

	return v0;
}
vec7u8_t Vec7u8_Scale(vec7u8_t v, uint8_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;
	v.v[5] *= scale;
	v.v[6] *= scale;

	return v;
}
vec7u8_t Vec7u8_DivScale(vec7u8_t v, uint8_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;
	v.v[5] /= divscale;
	v.v[6] /= divscale;

	return v;
}
vec7u8_t Vec7u8_MA(vec7u8_t v, vec7u8_t dir, uint8_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;
	v.v[5] += dir.v[5] * scale;
	v.v[6] += dir.v[6] * scale;

	return v;
}
vec7u8_t Vec7u8_DA(vec7u8_t v, vec7u8_t dir, uint8_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;
	v.v[5] += dir.v[5] / divscale;
	v.v[6] += dir.v[6] / divscale;

	return v;
}
uint8_t Vec7u8_Dot(vec7u8_t v0, vec7u8_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4] + v0.v[5] * v1.v[5] + v0.v[6] * v1.v[6];
}
uint8_t Vec7u8_LenSq(vec7u8_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4] + v.v[5] * v.v[5] + v.v[6] * v.v[6];
}
uint8_t Vec7u8_Len(vec7u8_t v)
{
	return sqrtf(Vec7u8_LenSq(v));
}
vec7u8_t Vec7u8_Mod(vec7u8_t v0, vec7u8_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);
	v0.v[4] = (v0.v[4] % v1.v[4]);
	v0.v[5] = (v0.v[5] % v1.v[5]);
	v0.v[6] = (v0.v[6] % v1.v[6]);

	return v0;
}
vec7u8_t Vec7u8_ModS(vec7u8_t v0, uint8_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);
	v0.v[4] = (v0.v[4] % x);
	v0.v[5] = (v0.v[5] % x);
	v0.v[6] = (v0.v[6] % x);

	return v0;
}
vec7u8_t Vec7u8_Min(vec7u8_t v0, vec7u8_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] < v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] < v1.v[6] ? v0.v[6] : v1.v[6];

	return v0;
}
vec7u8_t Vec7u8_Max(vec7u8_t v0, vec7u8_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] > v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] > v1.v[6] ? v0.v[6] : v1.v[6];

	return v0;
}
vec7u8_t Vec7u8_MinS(vec7u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] < x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] < x ? v0.v[6] : x;

	return v0;
}
vec7u8_t Vec7u8_MaxS(vec7u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] > x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] > x ? v0.v[6] : x;

	return v0;
}
vec7u8_t Vec7u8_Clamp(vec7u8_t v, vec7u8_t min, vec7u8_t max)
{
	return Vec7u8_Max(Vec7u8_Min(v, max), min);
}
vec7u8_t Vec7u8_ClampS(vec7u8_t v, uint8_t min, uint8_t max)
{
	return Vec7u8_MaxS(Vec7u8_MinS(v, max), min);
}
vec7u8_t Vec7u8_CmpLT(vec7u8_t v0, vec7u8_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] < v1.v[5] ? G_U8_ONE : G_U8_ZERO;
	v0.v[6] = v0.v[6] < v1.v[6] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec7u8_t Vec7u8_CmpLE(vec7u8_t v0, vec7u8_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] <= v1.v[5] ? G_U8_ONE : G_U8_ZERO;
	v0.v[6] = v0.v[6] <= v1.v[6] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec7u8_t Vec7u8_CmpEQ(vec7u8_t v0, vec7u8_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] == v1.v[5] ? G_U8_ONE : G_U8_ZERO;
	v0.v[6] = v0.v[6] == v1.v[6] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec7u8_t Vec7u8_CmpGT(vec7u8_t v0, vec7u8_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] > v1.v[5] ? G_U8_ONE : G_U8_ZERO;
	v0.v[6] = v0.v[6] > v1.v[6] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec7u8_t Vec7u8_CmpGE(vec7u8_t v0, vec7u8_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] >= v1.v[5] ? G_U8_ONE : G_U8_ZERO;
	v0.v[6] = v0.v[6] >= v1.v[6] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec7u8_t Vec7u8_CmpNE(vec7u8_t v0, vec7u8_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] != v1.v[5] ? G_U8_ONE : G_U8_ZERO;
	v0.v[6] = v0.v[6] != v1.v[6] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec7u8_t Vec7u8_CmpLTS(vec7u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] < x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] < x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] < x ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] < x ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] < x ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] < x ? G_U8_ONE : G_U8_ZERO;
	v0.v[6] = v0.v[6] < x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec7u8_t Vec7u8_CmpLES(vec7u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] <= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[6] = v0.v[6] <= x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec7u8_t Vec7u8_CmpEQS(vec7u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] == x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] == x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] == x ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] == x ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] == x ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] == x ? G_U8_ONE : G_U8_ZERO;
	v0.v[6] = v0.v[6] == x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec7u8_t Vec7u8_CmpGTS(vec7u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] > x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] > x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] > x ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] > x ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] > x ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] > x ? G_U8_ONE : G_U8_ZERO;
	v0.v[6] = v0.v[6] > x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec7u8_t Vec7u8_CmpGES(vec7u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] >= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[6] = v0.v[6] >= x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec7u8_t Vec7u8_CmpNES(vec7u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] != x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] != x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] != x ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] != x ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] != x ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] != x ? G_U8_ONE : G_U8_ZERO;
	v0.v[6] = v0.v[6] != x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec7u8_t Vec7u8_Sign(vec7u8_t v)
{
	v.v[0] = v.v[0] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;
	v.v[1] = v.v[1] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;
	v.v[2] = v.v[2] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;
	v.v[3] = v.v[3] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;
	v.v[4] = v.v[4] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;
	v.v[5] = v.v[5] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;
	v.v[6] = v.v[6] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;

	return v;
}
vec7u8_t Vec7u8_SignPosNeg(vec7u8_t v)
{
	v.v[0] = v.v[0] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;
	v.v[1] = v.v[1] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;
	v.v[2] = v.v[2] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;
	v.v[3] = v.v[3] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;
	v.v[4] = v.v[4] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;
	v.v[5] = v.v[5] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;
	v.v[6] = v.v[6] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;

	return v;
}
vec7u8_t Vec7u8_Zero()
{
	return G_VEC7U8_T_ZERO;
}
vec7u8_t Vec7u8_One()
{
	return G_VEC7U8_T_ONE;
}
vec7u8_t Vec7u8_Cross(vec7u8_t v0, vec7u8_t v1, vec7u8_t v2, vec7u8_t v3, vec7u8_t v4, vec7u8_t v5)
{
	vec7u8_t v;
	mat7x7u8_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;
	mat.v[5] = v4;
	mat.v[6] = v5;

	for (i = 0; i < 7; i++)
		v.v[i] = Mat6x6u8_Det(Mat7x7u8_DeleteRowColumn(mat, 0, i));

	return v;
}
vec8u8_t Vec7u8_ToVec8u8(vec7u8_t v, uint8_t x0)
{
	vec8u8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = v.v[5];
	outv.v[6] = v.v[6];
	outv.v[7] = x0;

	return outv;
}
vec7i8_t Vec7i8_SetComponent(vec7i8_t v, int index, int8_t value)
{
	v.v[index] = value;

	return v;
}
vec7i8_t Vec7i8_Vec(int8_t x0, int8_t x1, int8_t x2, int8_t x3, int8_t x4, int8_t x5, int8_t x6)
{
	vec7i8_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;
	v.v[5] = x5;
	v.v[6] = x6;

	return v;
}
vec7i8_t Vec7i8_Add(vec7i8_t v0, vec7i8_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];
	v0.v[5] += v1.v[5];
	v0.v[6] += v1.v[6];

	return v0;
}
vec7i8_t Vec7i8_Sub(vec7i8_t v0, vec7i8_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];
	v0.v[5] -= v1.v[5];
	v0.v[6] -= v1.v[6];

	return v0;
}
int8_t Vec7i8_GetComponent(vec7i8_t v, int index)
{
	return v.v[index];
}
vec7i8_t Vec7i8_Mul(vec7i8_t v0, vec7i8_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];
	v0.v[5] *= v1.v[5];
	v0.v[6] *= v1.v[6];

	return v0;
}
vec7i8_t Vec7i8_Div(vec7i8_t v0, vec7i8_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];
	v0.v[5] /= v1.v[5];
	v0.v[6] /= v1.v[6];

	return v0;
}
vec7i8_t Vec7i8_Scale(vec7i8_t v, int8_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;
	v.v[5] *= scale;
	v.v[6] *= scale;

	return v;
}
vec7i8_t Vec7i8_DivScale(vec7i8_t v, int8_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;
	v.v[5] /= divscale;
	v.v[6] /= divscale;

	return v;
}
vec7i8_t Vec7i8_MA(vec7i8_t v, vec7i8_t dir, int8_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;
	v.v[5] += dir.v[5] * scale;
	v.v[6] += dir.v[6] * scale;

	return v;
}
vec7i8_t Vec7i8_DA(vec7i8_t v, vec7i8_t dir, int8_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;
	v.v[5] += dir.v[5] / divscale;
	v.v[6] += dir.v[6] / divscale;

	return v;
}
int8_t Vec7i8_Dot(vec7i8_t v0, vec7i8_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4] + v0.v[5] * v1.v[5] + v0.v[6] * v1.v[6];
}
int8_t Vec7i8_LenSq(vec7i8_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4] + v.v[5] * v.v[5] + v.v[6] * v.v[6];
}
int8_t Vec7i8_Len(vec7i8_t v)
{
	return sqrtf(Vec7i8_LenSq(v));
}
vec7i8_t Vec7i8_Abs(vec7i8_t v)
{
	v.v[0] = (v.v[0] < 0 ? -v.v[0] : v.v[0]);
	v.v[1] = (v.v[1] < 0 ? -v.v[1] : v.v[1]);
	v.v[2] = (v.v[2] < 0 ? -v.v[2] : v.v[2]);
	v.v[3] = (v.v[3] < 0 ? -v.v[3] : v.v[3]);
	v.v[4] = (v.v[4] < 0 ? -v.v[4] : v.v[4]);
	v.v[5] = (v.v[5] < 0 ? -v.v[5] : v.v[5]);
	v.v[6] = (v.v[6] < 0 ? -v.v[6] : v.v[6]);

	return v;
}
vec7i8_t Vec7i8_Mod(vec7i8_t v0, vec7i8_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);
	v0.v[4] = (v0.v[4] % v1.v[4]);
	v0.v[5] = (v0.v[5] % v1.v[5]);
	v0.v[6] = (v0.v[6] % v1.v[6]);

	return v0;
}
vec7i8_t Vec7i8_ModS(vec7i8_t v0, int8_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);
	v0.v[4] = (v0.v[4] % x);
	v0.v[5] = (v0.v[5] % x);
	v0.v[6] = (v0.v[6] % x);

	return v0;
}
vec7i8_t Vec7i8_Min(vec7i8_t v0, vec7i8_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] < v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] < v1.v[6] ? v0.v[6] : v1.v[6];

	return v0;
}
vec7i8_t Vec7i8_Max(vec7i8_t v0, vec7i8_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] > v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] > v1.v[6] ? v0.v[6] : v1.v[6];

	return v0;
}
vec7i8_t Vec7i8_MinS(vec7i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] < x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] < x ? v0.v[6] : x;

	return v0;
}
vec7i8_t Vec7i8_MaxS(vec7i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] > x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] > x ? v0.v[6] : x;

	return v0;
}
vec7i8_t Vec7i8_Clamp(vec7i8_t v, vec7i8_t min, vec7i8_t max)
{
	return Vec7i8_Max(Vec7i8_Min(v, max), min);
}
vec7i8_t Vec7i8_ClampS(vec7i8_t v, int8_t min, int8_t max)
{
	return Vec7i8_MaxS(Vec7i8_MinS(v, max), min);
}
vec7i8_t Vec7i8_Neg(vec7i8_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];
	v.v[3] = -v.v[3];
	v.v[4] = -v.v[4];
	v.v[5] = -v.v[5];
	v.v[6] = -v.v[6];

	return v;
}
vec7i8_t Vec7i8_CmpLT(vec7i8_t v0, vec7i8_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] < v1.v[5] ? G_I8_ONE : G_I8_ZERO;
	v0.v[6] = v0.v[6] < v1.v[6] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec7i8_t Vec7i8_CmpLE(vec7i8_t v0, vec7i8_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] <= v1.v[5] ? G_I8_ONE : G_I8_ZERO;
	v0.v[6] = v0.v[6] <= v1.v[6] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec7i8_t Vec7i8_CmpEQ(vec7i8_t v0, vec7i8_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] == v1.v[5] ? G_I8_ONE : G_I8_ZERO;
	v0.v[6] = v0.v[6] == v1.v[6] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec7i8_t Vec7i8_CmpGT(vec7i8_t v0, vec7i8_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] > v1.v[5] ? G_I8_ONE : G_I8_ZERO;
	v0.v[6] = v0.v[6] > v1.v[6] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec7i8_t Vec7i8_CmpGE(vec7i8_t v0, vec7i8_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] >= v1.v[5] ? G_I8_ONE : G_I8_ZERO;
	v0.v[6] = v0.v[6] >= v1.v[6] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec7i8_t Vec7i8_CmpNE(vec7i8_t v0, vec7i8_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] != v1.v[5] ? G_I8_ONE : G_I8_ZERO;
	v0.v[6] = v0.v[6] != v1.v[6] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec7i8_t Vec7i8_CmpLTS(vec7i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] < x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] < x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] < x ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] < x ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] < x ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] < x ? G_I8_ONE : G_I8_ZERO;
	v0.v[6] = v0.v[6] < x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec7i8_t Vec7i8_CmpLES(vec7i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] <= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[6] = v0.v[6] <= x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec7i8_t Vec7i8_CmpEQS(vec7i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] == x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] == x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] == x ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] == x ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] == x ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] == x ? G_I8_ONE : G_I8_ZERO;
	v0.v[6] = v0.v[6] == x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec7i8_t Vec7i8_CmpGTS(vec7i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] > x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] > x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] > x ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] > x ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] > x ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] > x ? G_I8_ONE : G_I8_ZERO;
	v0.v[6] = v0.v[6] > x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec7i8_t Vec7i8_CmpGES(vec7i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] >= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[6] = v0.v[6] >= x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec7i8_t Vec7i8_CmpNES(vec7i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] != x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] != x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] != x ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] != x ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] != x ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] != x ? G_I8_ONE : G_I8_ZERO;
	v0.v[6] = v0.v[6] != x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec7i8_t Vec7i8_Sign(vec7i8_t v)
{
	v.v[0] = v.v[0] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;
	v.v[1] = v.v[1] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;
	v.v[2] = v.v[2] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;
	v.v[3] = v.v[3] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;
	v.v[4] = v.v[4] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;
	v.v[5] = v.v[5] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;
	v.v[6] = v.v[6] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;

	return v;
}
vec7i8_t Vec7i8_SignPosNeg(vec7i8_t v)
{
	v.v[0] = v.v[0] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;
	v.v[1] = v.v[1] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;
	v.v[2] = v.v[2] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;
	v.v[3] = v.v[3] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;
	v.v[4] = v.v[4] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;
	v.v[5] = v.v[5] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;
	v.v[6] = v.v[6] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;

	return v;
}
vec7i8_t Vec7i8_Zero()
{
	return G_VEC7I8_T_ZERO;
}
vec7i8_t Vec7i8_One()
{
	return G_VEC7I8_T_ONE;
}
vec7i8_t Vec7i8_NegOne()
{
	return Vec7i8_Neg(G_VEC7I8_T_ONE);
}
vec7i8_t Vec7i8_Cross(vec7i8_t v0, vec7i8_t v1, vec7i8_t v2, vec7i8_t v3, vec7i8_t v4, vec7i8_t v5)
{
	vec7i8_t v;
	mat7x7i8_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;
	mat.v[5] = v4;
	mat.v[6] = v5;

	for (i = 0; i < 7; i++)
		v.v[i] = Mat6x6i8_Det(Mat7x7i8_DeleteRowColumn(mat, 0, i));

	return v;
}
vec8i8_t Vec7i8_ToVec8i8(vec7i8_t v, int8_t x0)
{
	vec8i8_t outv;

	outv.v[0] = v.v[0];
	outv.v[1] = v.v[1];
	outv.v[2] = v.v[2];
	outv.v[3] = v.v[3];
	outv.v[4] = v.v[4];
	outv.v[5] = v.v[5];
	outv.v[6] = v.v[6];
	outv.v[7] = x0;

	return outv;
}
vec8f64_t Vec8f64_SetComponent(vec8f64_t v, int index, double value)
{
	v.v[index] = value;

	return v;
}
vec8f64_t Vec8f64_Vec(double x0, double x1, double x2, double x3, double x4, double x5, double x6, double x7)
{
	vec8f64_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;
	v.v[5] = x5;
	v.v[6] = x6;
	v.v[7] = x7;

	return v;
}
vec8f64_t Vec8f64_Add(vec8f64_t v0, vec8f64_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];
	v0.v[5] += v1.v[5];
	v0.v[6] += v1.v[6];
	v0.v[7] += v1.v[7];

	return v0;
}
vec8f64_t Vec8f64_Sub(vec8f64_t v0, vec8f64_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];
	v0.v[5] -= v1.v[5];
	v0.v[6] -= v1.v[6];
	v0.v[7] -= v1.v[7];

	return v0;
}
double Vec8f64_GetComponent(vec8f64_t v, int index)
{
	return v.v[index];
}
vec8f64_t Vec8f64_Mul(vec8f64_t v0, vec8f64_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];
	v0.v[5] *= v1.v[5];
	v0.v[6] *= v1.v[6];
	v0.v[7] *= v1.v[7];

	return v0;
}
vec8f64_t Vec8f64_Div(vec8f64_t v0, vec8f64_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];
	v0.v[5] /= v1.v[5];
	v0.v[6] /= v1.v[6];
	v0.v[7] /= v1.v[7];

	return v0;
}
vec8f64_t Vec8f64_Scale(vec8f64_t v, double scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;
	v.v[5] *= scale;
	v.v[6] *= scale;
	v.v[7] *= scale;

	return v;
}
vec8f64_t Vec8f64_DivScale(vec8f64_t v, double divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;
	v.v[5] /= divscale;
	v.v[6] /= divscale;
	v.v[7] /= divscale;

	return v;
}
vec8f64_t Vec8f64_MA(vec8f64_t v, vec8f64_t dir, double scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;
	v.v[5] += dir.v[5] * scale;
	v.v[6] += dir.v[6] * scale;
	v.v[7] += dir.v[7] * scale;

	return v;
}
vec8f64_t Vec8f64_DA(vec8f64_t v, vec8f64_t dir, double divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;
	v.v[5] += dir.v[5] / divscale;
	v.v[6] += dir.v[6] / divscale;
	v.v[7] += dir.v[7] / divscale;

	return v;
}
double Vec8f64_Dot(vec8f64_t v0, vec8f64_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4] + v0.v[5] * v1.v[5] + v0.v[6] * v1.v[6] + v0.v[7] * v1.v[7];
}
double Vec8f64_LenSq(vec8f64_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4] + v.v[5] * v.v[5] + v.v[6] * v.v[6] + v.v[7] * v.v[7];
}
double Vec8f64_Len(vec8f64_t v)
{
	return sqrt(Vec8f64_LenSq(v));
}
vec8f64_t Vec8f64_Normalise(vec8f64_t v)
{
	double lensq = Vec8f64_LenSq(v);

	if (lensq == G_F64_ZERO)
		return v;
	else
		return Vec8f64_Scale(v, G_F64_ONE / sqrt(lensq));
}
vec8f64_t Vec8f64_Abs(vec8f64_t v)
{
	v.v[0] = fabs(v.v[0]);
	v.v[1] = fabs(v.v[1]);
	v.v[2] = fabs(v.v[2]);
	v.v[3] = fabs(v.v[3]);
	v.v[4] = fabs(v.v[4]);
	v.v[5] = fabs(v.v[5]);
	v.v[6] = fabs(v.v[6]);
	v.v[7] = fabs(v.v[7]);

	return v;
}
vec8f64_t Vec8f64_Floor(vec8f64_t v)
{
	v.v[0] = floor(v.v[0]);
	v.v[1] = floor(v.v[1]);
	v.v[2] = floor(v.v[2]);
	v.v[3] = floor(v.v[3]);
	v.v[4] = floor(v.v[4]);
	v.v[5] = floor(v.v[5]);
	v.v[6] = floor(v.v[6]);
	v.v[7] = floor(v.v[7]);

	return v;
}
vec8f64_t Vec8f64_Ceil(vec8f64_t v)
{
	v.v[0] = ceil(v.v[0]);
	v.v[1] = ceil(v.v[1]);
	v.v[2] = ceil(v.v[2]);
	v.v[3] = ceil(v.v[3]);
	v.v[4] = ceil(v.v[4]);
	v.v[5] = ceil(v.v[5]);
	v.v[6] = ceil(v.v[6]);
	v.v[7] = ceil(v.v[7]);

	return v;
}
vec8f64_t Vec8f64_Fract(vec8f64_t v)
{
	return Vec8f64_Sub(v, Vec8f64_Floor(v));
}
vec8f64_t Vec8f64_Mod(vec8f64_t v0, vec8f64_t v1)
{
	v0.v[0] = fmod(v0.v[0], v1.v[0]);
	v0.v[1] = fmod(v0.v[1], v1.v[1]);
	v0.v[2] = fmod(v0.v[2], v1.v[2]);
	v0.v[3] = fmod(v0.v[3], v1.v[3]);
	v0.v[4] = fmod(v0.v[4], v1.v[4]);
	v0.v[5] = fmod(v0.v[5], v1.v[5]);
	v0.v[6] = fmod(v0.v[6], v1.v[6]);
	v0.v[7] = fmod(v0.v[7], v1.v[7]);

	return v0;
}
vec8f64_t Vec8f64_ModS(vec8f64_t v0, double x)
{
	v0.v[0] = fmod(v0.v[0], x);
	v0.v[1] = fmod(v0.v[1], x);
	v0.v[2] = fmod(v0.v[2], x);
	v0.v[3] = fmod(v0.v[3], x);
	v0.v[4] = fmod(v0.v[4], x);
	v0.v[5] = fmod(v0.v[5], x);
	v0.v[6] = fmod(v0.v[6], x);
	v0.v[7] = fmod(v0.v[7], x);

	return v0;
}
vec8f64_t Vec8f64_Min(vec8f64_t v0, vec8f64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] < v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] < v1.v[6] ? v0.v[6] : v1.v[6];
	v0.v[7] = v0.v[7] < v1.v[7] ? v0.v[7] : v1.v[7];

	return v0;
}
vec8f64_t Vec8f64_Max(vec8f64_t v0, vec8f64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] > v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] > v1.v[6] ? v0.v[6] : v1.v[6];
	v0.v[7] = v0.v[7] > v1.v[7] ? v0.v[7] : v1.v[7];

	return v0;
}
vec8f64_t Vec8f64_MinS(vec8f64_t v0, double x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] < x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] < x ? v0.v[6] : x;
	v0.v[7] = v0.v[7] < x ? v0.v[7] : x;

	return v0;
}
vec8f64_t Vec8f64_MaxS(vec8f64_t v0, double x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] > x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] > x ? v0.v[6] : x;
	v0.v[7] = v0.v[7] > x ? v0.v[7] : x;

	return v0;
}
vec8f64_t Vec8f64_Clamp(vec8f64_t v, vec8f64_t min, vec8f64_t max)
{
	return Vec8f64_Max(Vec8f64_Min(v, max), min);
}
vec8f64_t Vec8f64_ClampS(vec8f64_t v, double min, double max)
{
	return Vec8f64_MaxS(Vec8f64_MinS(v, max), min);
}
vec8f64_t Vec8f64_Neg(vec8f64_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];
	v.v[3] = -v.v[3];
	v.v[4] = -v.v[4];
	v.v[5] = -v.v[5];
	v.v[6] = -v.v[6];
	v.v[7] = -v.v[7];

	return v;
}
vec8f64_t Vec8f64_Reciprocal(vec8f64_t v)
{
	v.v[0] = G_F64_ONE / v.v[0];
	v.v[1] = G_F64_ONE / v.v[1];
	v.v[2] = G_F64_ONE / v.v[2];
	v.v[3] = G_F64_ONE / v.v[3];
	v.v[4] = G_F64_ONE / v.v[4];
	v.v[5] = G_F64_ONE / v.v[5];
	v.v[6] = G_F64_ONE / v.v[6];
	v.v[7] = G_F64_ONE / v.v[7];

	return v;
}
vec8f64_t Vec8f64_Truncate(vec8f64_t v)
{
	v.v[0] = v.v[0] < G_F64_ZERO ? ceil(v.v[0]) : floor(v.v[0]);
	v.v[1] = v.v[1] < G_F64_ZERO ? ceil(v.v[1]) : floor(v.v[1]);
	v.v[2] = v.v[2] < G_F64_ZERO ? ceil(v.v[2]) : floor(v.v[2]);
	v.v[3] = v.v[3] < G_F64_ZERO ? ceil(v.v[3]) : floor(v.v[3]);
	v.v[4] = v.v[4] < G_F64_ZERO ? ceil(v.v[4]) : floor(v.v[4]);
	v.v[5] = v.v[5] < G_F64_ZERO ? ceil(v.v[5]) : floor(v.v[5]);
	v.v[6] = v.v[6] < G_F64_ZERO ? ceil(v.v[6]) : floor(v.v[6]);
	v.v[7] = v.v[7] < G_F64_ZERO ? ceil(v.v[7]) : floor(v.v[7]);

	return v;
}
vec8f64_t Vec8f64_TruncateAway(vec8f64_t v)
{
	v.v[0] = v.v[0] < G_F64_ZERO ? floor(v.v[0]) : ceil(v.v[0]);
	v.v[1] = v.v[1] < G_F64_ZERO ? floor(v.v[1]) : ceil(v.v[1]);
	v.v[2] = v.v[2] < G_F64_ZERO ? floor(v.v[2]) : ceil(v.v[2]);
	v.v[3] = v.v[3] < G_F64_ZERO ? floor(v.v[3]) : ceil(v.v[3]);
	v.v[4] = v.v[4] < G_F64_ZERO ? floor(v.v[4]) : ceil(v.v[4]);
	v.v[5] = v.v[5] < G_F64_ZERO ? floor(v.v[5]) : ceil(v.v[5]);
	v.v[6] = v.v[6] < G_F64_ZERO ? floor(v.v[6]) : ceil(v.v[6]);
	v.v[7] = v.v[7] < G_F64_ZERO ? floor(v.v[7]) : ceil(v.v[7]);

	return v;
}
vec8f64_t Vec8f64_CmpLT(vec8f64_t v0, vec8f64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] < v1.v[5] ? G_F64_ONE : G_F64_ZERO;
	v0.v[6] = v0.v[6] < v1.v[6] ? G_F64_ONE : G_F64_ZERO;
	v0.v[7] = v0.v[7] < v1.v[7] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec8f64_t Vec8f64_CmpLE(vec8f64_t v0, vec8f64_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] <= v1.v[5] ? G_F64_ONE : G_F64_ZERO;
	v0.v[6] = v0.v[6] <= v1.v[6] ? G_F64_ONE : G_F64_ZERO;
	v0.v[7] = v0.v[7] <= v1.v[7] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec8f64_t Vec8f64_CmpEQ(vec8f64_t v0, vec8f64_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] == v1.v[5] ? G_F64_ONE : G_F64_ZERO;
	v0.v[6] = v0.v[6] == v1.v[6] ? G_F64_ONE : G_F64_ZERO;
	v0.v[7] = v0.v[7] == v1.v[7] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec8f64_t Vec8f64_CmpGT(vec8f64_t v0, vec8f64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] > v1.v[5] ? G_F64_ONE : G_F64_ZERO;
	v0.v[6] = v0.v[6] > v1.v[6] ? G_F64_ONE : G_F64_ZERO;
	v0.v[7] = v0.v[7] > v1.v[7] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec8f64_t Vec8f64_CmpGE(vec8f64_t v0, vec8f64_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] >= v1.v[5] ? G_F64_ONE : G_F64_ZERO;
	v0.v[6] = v0.v[6] >= v1.v[6] ? G_F64_ONE : G_F64_ZERO;
	v0.v[7] = v0.v[7] >= v1.v[7] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec8f64_t Vec8f64_CmpNE(vec8f64_t v0, vec8f64_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] != v1.v[5] ? G_F64_ONE : G_F64_ZERO;
	v0.v[6] = v0.v[6] != v1.v[6] ? G_F64_ONE : G_F64_ZERO;
	v0.v[7] = v0.v[7] != v1.v[7] ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec8f64_t Vec8f64_CmpLTS(vec8f64_t v0, double x)
{
	v0.v[0] = v0.v[0] < x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] < x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] < x ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] < x ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] < x ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] < x ? G_F64_ONE : G_F64_ZERO;
	v0.v[6] = v0.v[6] < x ? G_F64_ONE : G_F64_ZERO;
	v0.v[7] = v0.v[7] < x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec8f64_t Vec8f64_CmpLES(vec8f64_t v0, double x)
{
	v0.v[0] = v0.v[0] <= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] <= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[6] = v0.v[6] <= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[7] = v0.v[7] <= x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec8f64_t Vec8f64_CmpEQS(vec8f64_t v0, double x)
{
	v0.v[0] = v0.v[0] == x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] == x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] == x ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] == x ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] == x ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] == x ? G_F64_ONE : G_F64_ZERO;
	v0.v[6] = v0.v[6] == x ? G_F64_ONE : G_F64_ZERO;
	v0.v[7] = v0.v[7] == x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec8f64_t Vec8f64_CmpGTS(vec8f64_t v0, double x)
{
	v0.v[0] = v0.v[0] > x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] > x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] > x ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] > x ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] > x ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] > x ? G_F64_ONE : G_F64_ZERO;
	v0.v[6] = v0.v[6] > x ? G_F64_ONE : G_F64_ZERO;
	v0.v[7] = v0.v[7] > x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec8f64_t Vec8f64_CmpGES(vec8f64_t v0, double x)
{
	v0.v[0] = v0.v[0] >= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] >= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[6] = v0.v[6] >= x ? G_F64_ONE : G_F64_ZERO;
	v0.v[7] = v0.v[7] >= x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec8f64_t Vec8f64_CmpNES(vec8f64_t v0, double x)
{
	v0.v[0] = v0.v[0] != x ? G_F64_ONE : G_F64_ZERO;
	v0.v[1] = v0.v[1] != x ? G_F64_ONE : G_F64_ZERO;
	v0.v[2] = v0.v[2] != x ? G_F64_ONE : G_F64_ZERO;
	v0.v[3] = v0.v[3] != x ? G_F64_ONE : G_F64_ZERO;
	v0.v[4] = v0.v[4] != x ? G_F64_ONE : G_F64_ZERO;
	v0.v[5] = v0.v[5] != x ? G_F64_ONE : G_F64_ZERO;
	v0.v[6] = v0.v[6] != x ? G_F64_ONE : G_F64_ZERO;
	v0.v[7] = v0.v[7] != x ? G_F64_ONE : G_F64_ZERO;

	return v0;
}
vec8f64_t Vec8f64_Sign(vec8f64_t v)
{
	v.v[0] = v.v[0] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;
	v.v[1] = v.v[1] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;
	v.v[2] = v.v[2] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;
	v.v[3] = v.v[3] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;
	v.v[4] = v.v[4] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;
	v.v[5] = v.v[5] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;
	v.v[6] = v.v[6] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;
	v.v[7] = v.v[7] < G_F64_ZERO ? G_F64_ONE : G_F64_ZERO;

	return v;
}
vec8f64_t Vec8f64_SignPosNeg(vec8f64_t v)
{
	v.v[0] = v.v[0] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;
	v.v[1] = v.v[1] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;
	v.v[2] = v.v[2] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;
	v.v[3] = v.v[3] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;
	v.v[4] = v.v[4] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;
	v.v[5] = v.v[5] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;
	v.v[6] = v.v[6] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;
	v.v[7] = v.v[7] < G_F64_ZERO ? G_F64_NEG_ONE : G_F64_ONE;

	return v;
}
vec8f64_t Vec8f64_Zero()
{
	return G_VEC8F64_T_ZERO;
}
vec8f64_t Vec8f64_One()
{
	return G_VEC8F64_T_ONE;
}
vec8f64_t Vec8f64_NegOne()
{
	return Vec8f64_Neg(G_VEC8F64_T_ONE);
}
vec8f64_t Vec8f64_Cross(vec8f64_t v0, vec8f64_t v1, vec8f64_t v2, vec8f64_t v3, vec8f64_t v4, vec8f64_t v5, vec8f64_t v6)
{
	vec8f64_t v;
	mat8x8f64_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;
	mat.v[5] = v4;
	mat.v[6] = v5;
	mat.v[7] = v6;

	for (i = 0; i < 8; i++)
		v.v[i] = Mat7x7f64_Det(Mat8x8f64_DeleteRowColumn(mat, 0, i));

	return v;
}
vec8f64_t Vec8f64_Lerp(vec8f64_t v0, vec8f64_t v1, vec8f64_t vt)
{
	vec8f64_t v;

	v.v[0] = (G_F64_ONE - vt.v[0]) * v0.v[0] + v1.v[0] * vt.v[0];
	v.v[1] = (G_F64_ONE - vt.v[1]) * v0.v[1] + v1.v[1] * vt.v[1];
	v.v[2] = (G_F64_ONE - vt.v[2]) * v0.v[2] + v1.v[2] * vt.v[2];
	v.v[3] = (G_F64_ONE - vt.v[3]) * v0.v[3] + v1.v[3] * vt.v[3];
	v.v[4] = (G_F64_ONE - vt.v[4]) * v0.v[4] + v1.v[4] * vt.v[4];
	v.v[5] = (G_F64_ONE - vt.v[5]) * v0.v[5] + v1.v[5] * vt.v[5];
	v.v[6] = (G_F64_ONE - vt.v[6]) * v0.v[6] + v1.v[6] * vt.v[6];
	v.v[7] = (G_F64_ONE - vt.v[7]) * v0.v[7] + v1.v[7] * vt.v[7];

	return v;
}
vec8f64_t Vec8f64_LerpS(vec8f64_t v0, vec8f64_t v1, double t)
{
	vec8f64_t v;

	v.v[0] = (G_F64_ONE - t) * v0.v[0] + v1.v[0] * t;
	v.v[1] = (G_F64_ONE - t) * v0.v[1] + v1.v[1] * t;
	v.v[2] = (G_F64_ONE - t) * v0.v[2] + v1.v[2] * t;
	v.v[3] = (G_F64_ONE - t) * v0.v[3] + v1.v[3] * t;
	v.v[4] = (G_F64_ONE - t) * v0.v[4] + v1.v[4] * t;
	v.v[5] = (G_F64_ONE - t) * v0.v[5] + v1.v[5] * t;
	v.v[6] = (G_F64_ONE - t) * v0.v[6] + v1.v[6] * t;
	v.v[7] = (G_F64_ONE - t) * v0.v[7] + v1.v[7] * t;

	return v;
}
vec8f32_t Vec8f32_SetComponent(vec8f32_t v, int index, float value)
{
	v.v[index] = value;

	return v;
}
vec8f32_t Vec8f32_Vec(float x0, float x1, float x2, float x3, float x4, float x5, float x6, float x7)
{
	vec8f32_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;
	v.v[5] = x5;
	v.v[6] = x6;
	v.v[7] = x7;

	return v;
}
vec8f32_t Vec8f32_Add(vec8f32_t v0, vec8f32_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];
	v0.v[5] += v1.v[5];
	v0.v[6] += v1.v[6];
	v0.v[7] += v1.v[7];

	return v0;
}
vec8f32_t Vec8f32_Sub(vec8f32_t v0, vec8f32_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];
	v0.v[5] -= v1.v[5];
	v0.v[6] -= v1.v[6];
	v0.v[7] -= v1.v[7];

	return v0;
}
float Vec8f32_GetComponent(vec8f32_t v, int index)
{
	return v.v[index];
}
vec8f32_t Vec8f32_Mul(vec8f32_t v0, vec8f32_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];
	v0.v[5] *= v1.v[5];
	v0.v[6] *= v1.v[6];
	v0.v[7] *= v1.v[7];

	return v0;
}
vec8f32_t Vec8f32_Div(vec8f32_t v0, vec8f32_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];
	v0.v[5] /= v1.v[5];
	v0.v[6] /= v1.v[6];
	v0.v[7] /= v1.v[7];

	return v0;
}
vec8f32_t Vec8f32_Scale(vec8f32_t v, float scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;
	v.v[5] *= scale;
	v.v[6] *= scale;
	v.v[7] *= scale;

	return v;
}
vec8f32_t Vec8f32_DivScale(vec8f32_t v, float divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;
	v.v[5] /= divscale;
	v.v[6] /= divscale;
	v.v[7] /= divscale;

	return v;
}
vec8f32_t Vec8f32_MA(vec8f32_t v, vec8f32_t dir, float scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;
	v.v[5] += dir.v[5] * scale;
	v.v[6] += dir.v[6] * scale;
	v.v[7] += dir.v[7] * scale;

	return v;
}
vec8f32_t Vec8f32_DA(vec8f32_t v, vec8f32_t dir, float divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;
	v.v[5] += dir.v[5] / divscale;
	v.v[6] += dir.v[6] / divscale;
	v.v[7] += dir.v[7] / divscale;

	return v;
}
float Vec8f32_Dot(vec8f32_t v0, vec8f32_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4] + v0.v[5] * v1.v[5] + v0.v[6] * v1.v[6] + v0.v[7] * v1.v[7];
}
float Vec8f32_LenSq(vec8f32_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4] + v.v[5] * v.v[5] + v.v[6] * v.v[6] + v.v[7] * v.v[7];
}
float Vec8f32_Len(vec8f32_t v)
{
	return sqrtf(Vec8f32_LenSq(v));
}
vec8f32_t Vec8f32_Normalise(vec8f32_t v)
{
	float lensq = Vec8f32_LenSq(v);

	if (lensq == G_F32_ZERO)
		return v;
	else
		return Vec8f32_Scale(v, G_F32_ONE / sqrtf(lensq));
}
vec8f32_t Vec8f32_Abs(vec8f32_t v)
{
	v.v[0] = fabsf(v.v[0]);
	v.v[1] = fabsf(v.v[1]);
	v.v[2] = fabsf(v.v[2]);
	v.v[3] = fabsf(v.v[3]);
	v.v[4] = fabsf(v.v[4]);
	v.v[5] = fabsf(v.v[5]);
	v.v[6] = fabsf(v.v[6]);
	v.v[7] = fabsf(v.v[7]);

	return v;
}
vec8f32_t Vec8f32_Floor(vec8f32_t v)
{
	v.v[0] = floorf(v.v[0]);
	v.v[1] = floorf(v.v[1]);
	v.v[2] = floorf(v.v[2]);
	v.v[3] = floorf(v.v[3]);
	v.v[4] = floorf(v.v[4]);
	v.v[5] = floorf(v.v[5]);
	v.v[6] = floorf(v.v[6]);
	v.v[7] = floorf(v.v[7]);

	return v;
}
vec8f32_t Vec8f32_Ceil(vec8f32_t v)
{
	v.v[0] = ceilf(v.v[0]);
	v.v[1] = ceilf(v.v[1]);
	v.v[2] = ceilf(v.v[2]);
	v.v[3] = ceilf(v.v[3]);
	v.v[4] = ceilf(v.v[4]);
	v.v[5] = ceilf(v.v[5]);
	v.v[6] = ceilf(v.v[6]);
	v.v[7] = ceilf(v.v[7]);

	return v;
}
vec8f32_t Vec8f32_Fract(vec8f32_t v)
{
	return Vec8f32_Sub(v, Vec8f32_Floor(v));
}
vec8f32_t Vec8f32_Mod(vec8f32_t v0, vec8f32_t v1)
{
	v0.v[0] = fmodf(v0.v[0], v1.v[0]);
	v0.v[1] = fmodf(v0.v[1], v1.v[1]);
	v0.v[2] = fmodf(v0.v[2], v1.v[2]);
	v0.v[3] = fmodf(v0.v[3], v1.v[3]);
	v0.v[4] = fmodf(v0.v[4], v1.v[4]);
	v0.v[5] = fmodf(v0.v[5], v1.v[5]);
	v0.v[6] = fmodf(v0.v[6], v1.v[6]);
	v0.v[7] = fmodf(v0.v[7], v1.v[7]);

	return v0;
}
vec8f32_t Vec8f32_ModS(vec8f32_t v0, float x)
{
	v0.v[0] = fmodf(v0.v[0], x);
	v0.v[1] = fmodf(v0.v[1], x);
	v0.v[2] = fmodf(v0.v[2], x);
	v0.v[3] = fmodf(v0.v[3], x);
	v0.v[4] = fmodf(v0.v[4], x);
	v0.v[5] = fmodf(v0.v[5], x);
	v0.v[6] = fmodf(v0.v[6], x);
	v0.v[7] = fmodf(v0.v[7], x);

	return v0;
}
vec8f32_t Vec8f32_Min(vec8f32_t v0, vec8f32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] < v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] < v1.v[6] ? v0.v[6] : v1.v[6];
	v0.v[7] = v0.v[7] < v1.v[7] ? v0.v[7] : v1.v[7];

	return v0;
}
vec8f32_t Vec8f32_Max(vec8f32_t v0, vec8f32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] > v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] > v1.v[6] ? v0.v[6] : v1.v[6];
	v0.v[7] = v0.v[7] > v1.v[7] ? v0.v[7] : v1.v[7];

	return v0;
}
vec8f32_t Vec8f32_MinS(vec8f32_t v0, float x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] < x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] < x ? v0.v[6] : x;
	v0.v[7] = v0.v[7] < x ? v0.v[7] : x;

	return v0;
}
vec8f32_t Vec8f32_MaxS(vec8f32_t v0, float x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] > x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] > x ? v0.v[6] : x;
	v0.v[7] = v0.v[7] > x ? v0.v[7] : x;

	return v0;
}
vec8f32_t Vec8f32_Clamp(vec8f32_t v, vec8f32_t min, vec8f32_t max)
{
	return Vec8f32_Max(Vec8f32_Min(v, max), min);
}
vec8f32_t Vec8f32_ClampS(vec8f32_t v, float min, float max)
{
	return Vec8f32_MaxS(Vec8f32_MinS(v, max), min);
}
vec8f32_t Vec8f32_Neg(vec8f32_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];
	v.v[3] = -v.v[3];
	v.v[4] = -v.v[4];
	v.v[5] = -v.v[5];
	v.v[6] = -v.v[6];
	v.v[7] = -v.v[7];

	return v;
}
vec8f32_t Vec8f32_Reciprocal(vec8f32_t v)
{
	v.v[0] = G_F32_ONE / v.v[0];
	v.v[1] = G_F32_ONE / v.v[1];
	v.v[2] = G_F32_ONE / v.v[2];
	v.v[3] = G_F32_ONE / v.v[3];
	v.v[4] = G_F32_ONE / v.v[4];
	v.v[5] = G_F32_ONE / v.v[5];
	v.v[6] = G_F32_ONE / v.v[6];
	v.v[7] = G_F32_ONE / v.v[7];

	return v;
}
vec8f32_t Vec8f32_Truncate(vec8f32_t v)
{
	v.v[0] = v.v[0] < G_F32_ZERO ? ceilf(v.v[0]) : floorf(v.v[0]);
	v.v[1] = v.v[1] < G_F32_ZERO ? ceilf(v.v[1]) : floorf(v.v[1]);
	v.v[2] = v.v[2] < G_F32_ZERO ? ceilf(v.v[2]) : floorf(v.v[2]);
	v.v[3] = v.v[3] < G_F32_ZERO ? ceilf(v.v[3]) : floorf(v.v[3]);
	v.v[4] = v.v[4] < G_F32_ZERO ? ceilf(v.v[4]) : floorf(v.v[4]);
	v.v[5] = v.v[5] < G_F32_ZERO ? ceilf(v.v[5]) : floorf(v.v[5]);
	v.v[6] = v.v[6] < G_F32_ZERO ? ceilf(v.v[6]) : floorf(v.v[6]);
	v.v[7] = v.v[7] < G_F32_ZERO ? ceilf(v.v[7]) : floorf(v.v[7]);

	return v;
}
vec8f32_t Vec8f32_TruncateAway(vec8f32_t v)
{
	v.v[0] = v.v[0] < G_F32_ZERO ? floorf(v.v[0]) : ceilf(v.v[0]);
	v.v[1] = v.v[1] < G_F32_ZERO ? floorf(v.v[1]) : ceilf(v.v[1]);
	v.v[2] = v.v[2] < G_F32_ZERO ? floorf(v.v[2]) : ceilf(v.v[2]);
	v.v[3] = v.v[3] < G_F32_ZERO ? floorf(v.v[3]) : ceilf(v.v[3]);
	v.v[4] = v.v[4] < G_F32_ZERO ? floorf(v.v[4]) : ceilf(v.v[4]);
	v.v[5] = v.v[5] < G_F32_ZERO ? floorf(v.v[5]) : ceilf(v.v[5]);
	v.v[6] = v.v[6] < G_F32_ZERO ? floorf(v.v[6]) : ceilf(v.v[6]);
	v.v[7] = v.v[7] < G_F32_ZERO ? floorf(v.v[7]) : ceilf(v.v[7]);

	return v;
}
vec8f32_t Vec8f32_CmpLT(vec8f32_t v0, vec8f32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] < v1.v[5] ? G_F32_ONE : G_F32_ZERO;
	v0.v[6] = v0.v[6] < v1.v[6] ? G_F32_ONE : G_F32_ZERO;
	v0.v[7] = v0.v[7] < v1.v[7] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec8f32_t Vec8f32_CmpLE(vec8f32_t v0, vec8f32_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] <= v1.v[5] ? G_F32_ONE : G_F32_ZERO;
	v0.v[6] = v0.v[6] <= v1.v[6] ? G_F32_ONE : G_F32_ZERO;
	v0.v[7] = v0.v[7] <= v1.v[7] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec8f32_t Vec8f32_CmpEQ(vec8f32_t v0, vec8f32_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] == v1.v[5] ? G_F32_ONE : G_F32_ZERO;
	v0.v[6] = v0.v[6] == v1.v[6] ? G_F32_ONE : G_F32_ZERO;
	v0.v[7] = v0.v[7] == v1.v[7] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec8f32_t Vec8f32_CmpGT(vec8f32_t v0, vec8f32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] > v1.v[5] ? G_F32_ONE : G_F32_ZERO;
	v0.v[6] = v0.v[6] > v1.v[6] ? G_F32_ONE : G_F32_ZERO;
	v0.v[7] = v0.v[7] > v1.v[7] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec8f32_t Vec8f32_CmpGE(vec8f32_t v0, vec8f32_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] >= v1.v[5] ? G_F32_ONE : G_F32_ZERO;
	v0.v[6] = v0.v[6] >= v1.v[6] ? G_F32_ONE : G_F32_ZERO;
	v0.v[7] = v0.v[7] >= v1.v[7] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec8f32_t Vec8f32_CmpNE(vec8f32_t v0, vec8f32_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] != v1.v[5] ? G_F32_ONE : G_F32_ZERO;
	v0.v[6] = v0.v[6] != v1.v[6] ? G_F32_ONE : G_F32_ZERO;
	v0.v[7] = v0.v[7] != v1.v[7] ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec8f32_t Vec8f32_CmpLTS(vec8f32_t v0, float x)
{
	v0.v[0] = v0.v[0] < x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] < x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] < x ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] < x ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] < x ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] < x ? G_F32_ONE : G_F32_ZERO;
	v0.v[6] = v0.v[6] < x ? G_F32_ONE : G_F32_ZERO;
	v0.v[7] = v0.v[7] < x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec8f32_t Vec8f32_CmpLES(vec8f32_t v0, float x)
{
	v0.v[0] = v0.v[0] <= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] <= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[6] = v0.v[6] <= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[7] = v0.v[7] <= x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec8f32_t Vec8f32_CmpEQS(vec8f32_t v0, float x)
{
	v0.v[0] = v0.v[0] == x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] == x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] == x ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] == x ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] == x ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] == x ? G_F32_ONE : G_F32_ZERO;
	v0.v[6] = v0.v[6] == x ? G_F32_ONE : G_F32_ZERO;
	v0.v[7] = v0.v[7] == x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec8f32_t Vec8f32_CmpGTS(vec8f32_t v0, float x)
{
	v0.v[0] = v0.v[0] > x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] > x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] > x ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] > x ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] > x ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] > x ? G_F32_ONE : G_F32_ZERO;
	v0.v[6] = v0.v[6] > x ? G_F32_ONE : G_F32_ZERO;
	v0.v[7] = v0.v[7] > x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec8f32_t Vec8f32_CmpGES(vec8f32_t v0, float x)
{
	v0.v[0] = v0.v[0] >= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] >= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[6] = v0.v[6] >= x ? G_F32_ONE : G_F32_ZERO;
	v0.v[7] = v0.v[7] >= x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec8f32_t Vec8f32_CmpNES(vec8f32_t v0, float x)
{
	v0.v[0] = v0.v[0] != x ? G_F32_ONE : G_F32_ZERO;
	v0.v[1] = v0.v[1] != x ? G_F32_ONE : G_F32_ZERO;
	v0.v[2] = v0.v[2] != x ? G_F32_ONE : G_F32_ZERO;
	v0.v[3] = v0.v[3] != x ? G_F32_ONE : G_F32_ZERO;
	v0.v[4] = v0.v[4] != x ? G_F32_ONE : G_F32_ZERO;
	v0.v[5] = v0.v[5] != x ? G_F32_ONE : G_F32_ZERO;
	v0.v[6] = v0.v[6] != x ? G_F32_ONE : G_F32_ZERO;
	v0.v[7] = v0.v[7] != x ? G_F32_ONE : G_F32_ZERO;

	return v0;
}
vec8f32_t Vec8f32_Sign(vec8f32_t v)
{
	v.v[0] = v.v[0] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;
	v.v[1] = v.v[1] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;
	v.v[2] = v.v[2] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;
	v.v[3] = v.v[3] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;
	v.v[4] = v.v[4] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;
	v.v[5] = v.v[5] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;
	v.v[6] = v.v[6] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;
	v.v[7] = v.v[7] < G_F32_ZERO ? G_F32_ONE : G_F32_ZERO;

	return v;
}
vec8f32_t Vec8f32_SignPosNeg(vec8f32_t v)
{
	v.v[0] = v.v[0] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;
	v.v[1] = v.v[1] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;
	v.v[2] = v.v[2] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;
	v.v[3] = v.v[3] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;
	v.v[4] = v.v[4] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;
	v.v[5] = v.v[5] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;
	v.v[6] = v.v[6] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;
	v.v[7] = v.v[7] < G_F32_ZERO ? G_F32_NEG_ONE : G_F32_ONE;

	return v;
}
vec8f32_t Vec8f32_Zero()
{
	return G_VEC8F32_T_ZERO;
}
vec8f32_t Vec8f32_One()
{
	return G_VEC8F32_T_ONE;
}
vec8f32_t Vec8f32_NegOne()
{
	return Vec8f32_Neg(G_VEC8F32_T_ONE);
}
vec8f32_t Vec8f32_Cross(vec8f32_t v0, vec8f32_t v1, vec8f32_t v2, vec8f32_t v3, vec8f32_t v4, vec8f32_t v5, vec8f32_t v6)
{
	vec8f32_t v;
	mat8x8f32_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;
	mat.v[5] = v4;
	mat.v[6] = v5;
	mat.v[7] = v6;

	for (i = 0; i < 8; i++)
		v.v[i] = Mat7x7f32_Det(Mat8x8f32_DeleteRowColumn(mat, 0, i));

	return v;
}
vec8f32_t Vec8f32_Lerp(vec8f32_t v0, vec8f32_t v1, vec8f32_t vt)
{
	vec8f32_t v;

	v.v[0] = (G_F32_ONE - vt.v[0]) * v0.v[0] + v1.v[0] * vt.v[0];
	v.v[1] = (G_F32_ONE - vt.v[1]) * v0.v[1] + v1.v[1] * vt.v[1];
	v.v[2] = (G_F32_ONE - vt.v[2]) * v0.v[2] + v1.v[2] * vt.v[2];
	v.v[3] = (G_F32_ONE - vt.v[3]) * v0.v[3] + v1.v[3] * vt.v[3];
	v.v[4] = (G_F32_ONE - vt.v[4]) * v0.v[4] + v1.v[4] * vt.v[4];
	v.v[5] = (G_F32_ONE - vt.v[5]) * v0.v[5] + v1.v[5] * vt.v[5];
	v.v[6] = (G_F32_ONE - vt.v[6]) * v0.v[6] + v1.v[6] * vt.v[6];
	v.v[7] = (G_F32_ONE - vt.v[7]) * v0.v[7] + v1.v[7] * vt.v[7];

	return v;
}
vec8f32_t Vec8f32_LerpS(vec8f32_t v0, vec8f32_t v1, float t)
{
	vec8f32_t v;

	v.v[0] = (G_F32_ONE - t) * v0.v[0] + v1.v[0] * t;
	v.v[1] = (G_F32_ONE - t) * v0.v[1] + v1.v[1] * t;
	v.v[2] = (G_F32_ONE - t) * v0.v[2] + v1.v[2] * t;
	v.v[3] = (G_F32_ONE - t) * v0.v[3] + v1.v[3] * t;
	v.v[4] = (G_F32_ONE - t) * v0.v[4] + v1.v[4] * t;
	v.v[5] = (G_F32_ONE - t) * v0.v[5] + v1.v[5] * t;
	v.v[6] = (G_F32_ONE - t) * v0.v[6] + v1.v[6] * t;
	v.v[7] = (G_F32_ONE - t) * v0.v[7] + v1.v[7] * t;

	return v;
}
vec8u64_t Vec8u64_SetComponent(vec8u64_t v, int index, uint64_t value)
{
	v.v[index] = value;

	return v;
}
vec8u64_t Vec8u64_Vec(uint64_t x0, uint64_t x1, uint64_t x2, uint64_t x3, uint64_t x4, uint64_t x5, uint64_t x6, uint64_t x7)
{
	vec8u64_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;
	v.v[5] = x5;
	v.v[6] = x6;
	v.v[7] = x7;

	return v;
}
vec8u64_t Vec8u64_Add(vec8u64_t v0, vec8u64_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];
	v0.v[5] += v1.v[5];
	v0.v[6] += v1.v[6];
	v0.v[7] += v1.v[7];

	return v0;
}
vec8u64_t Vec8u64_Sub(vec8u64_t v0, vec8u64_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];
	v0.v[5] -= v1.v[5];
	v0.v[6] -= v1.v[6];
	v0.v[7] -= v1.v[7];

	return v0;
}
uint64_t Vec8u64_GetComponent(vec8u64_t v, int index)
{
	return v.v[index];
}
vec8u64_t Vec8u64_Mul(vec8u64_t v0, vec8u64_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];
	v0.v[5] *= v1.v[5];
	v0.v[6] *= v1.v[6];
	v0.v[7] *= v1.v[7];

	return v0;
}
vec8u64_t Vec8u64_Div(vec8u64_t v0, vec8u64_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];
	v0.v[5] /= v1.v[5];
	v0.v[6] /= v1.v[6];
	v0.v[7] /= v1.v[7];

	return v0;
}
vec8u64_t Vec8u64_Scale(vec8u64_t v, uint64_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;
	v.v[5] *= scale;
	v.v[6] *= scale;
	v.v[7] *= scale;

	return v;
}
vec8u64_t Vec8u64_DivScale(vec8u64_t v, uint64_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;
	v.v[5] /= divscale;
	v.v[6] /= divscale;
	v.v[7] /= divscale;

	return v;
}
vec8u64_t Vec8u64_MA(vec8u64_t v, vec8u64_t dir, uint64_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;
	v.v[5] += dir.v[5] * scale;
	v.v[6] += dir.v[6] * scale;
	v.v[7] += dir.v[7] * scale;

	return v;
}
vec8u64_t Vec8u64_DA(vec8u64_t v, vec8u64_t dir, uint64_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;
	v.v[5] += dir.v[5] / divscale;
	v.v[6] += dir.v[6] / divscale;
	v.v[7] += dir.v[7] / divscale;

	return v;
}
uint64_t Vec8u64_Dot(vec8u64_t v0, vec8u64_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4] + v0.v[5] * v1.v[5] + v0.v[6] * v1.v[6] + v0.v[7] * v1.v[7];
}
uint64_t Vec8u64_LenSq(vec8u64_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4] + v.v[5] * v.v[5] + v.v[6] * v.v[6] + v.v[7] * v.v[7];
}
uint64_t Vec8u64_Len(vec8u64_t v)
{
	return sqrt(Vec8u64_LenSq(v));
}
vec8u64_t Vec8u64_Mod(vec8u64_t v0, vec8u64_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);
	v0.v[4] = (v0.v[4] % v1.v[4]);
	v0.v[5] = (v0.v[5] % v1.v[5]);
	v0.v[6] = (v0.v[6] % v1.v[6]);
	v0.v[7] = (v0.v[7] % v1.v[7]);

	return v0;
}
vec8u64_t Vec8u64_ModS(vec8u64_t v0, uint64_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);
	v0.v[4] = (v0.v[4] % x);
	v0.v[5] = (v0.v[5] % x);
	v0.v[6] = (v0.v[6] % x);
	v0.v[7] = (v0.v[7] % x);

	return v0;
}
vec8u64_t Vec8u64_Min(vec8u64_t v0, vec8u64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] < v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] < v1.v[6] ? v0.v[6] : v1.v[6];
	v0.v[7] = v0.v[7] < v1.v[7] ? v0.v[7] : v1.v[7];

	return v0;
}
vec8u64_t Vec8u64_Max(vec8u64_t v0, vec8u64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] > v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] > v1.v[6] ? v0.v[6] : v1.v[6];
	v0.v[7] = v0.v[7] > v1.v[7] ? v0.v[7] : v1.v[7];

	return v0;
}
vec8u64_t Vec8u64_MinS(vec8u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] < x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] < x ? v0.v[6] : x;
	v0.v[7] = v0.v[7] < x ? v0.v[7] : x;

	return v0;
}
vec8u64_t Vec8u64_MaxS(vec8u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] > x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] > x ? v0.v[6] : x;
	v0.v[7] = v0.v[7] > x ? v0.v[7] : x;

	return v0;
}
vec8u64_t Vec8u64_Clamp(vec8u64_t v, vec8u64_t min, vec8u64_t max)
{
	return Vec8u64_Max(Vec8u64_Min(v, max), min);
}
vec8u64_t Vec8u64_ClampS(vec8u64_t v, uint64_t min, uint64_t max)
{
	return Vec8u64_MaxS(Vec8u64_MinS(v, max), min);
}
vec8u64_t Vec8u64_CmpLT(vec8u64_t v0, vec8u64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] < v1.v[5] ? G_U64_ONE : G_U64_ZERO;
	v0.v[6] = v0.v[6] < v1.v[6] ? G_U64_ONE : G_U64_ZERO;
	v0.v[7] = v0.v[7] < v1.v[7] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec8u64_t Vec8u64_CmpLE(vec8u64_t v0, vec8u64_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] <= v1.v[5] ? G_U64_ONE : G_U64_ZERO;
	v0.v[6] = v0.v[6] <= v1.v[6] ? G_U64_ONE : G_U64_ZERO;
	v0.v[7] = v0.v[7] <= v1.v[7] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec8u64_t Vec8u64_CmpEQ(vec8u64_t v0, vec8u64_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] == v1.v[5] ? G_U64_ONE : G_U64_ZERO;
	v0.v[6] = v0.v[6] == v1.v[6] ? G_U64_ONE : G_U64_ZERO;
	v0.v[7] = v0.v[7] == v1.v[7] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec8u64_t Vec8u64_CmpGT(vec8u64_t v0, vec8u64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] > v1.v[5] ? G_U64_ONE : G_U64_ZERO;
	v0.v[6] = v0.v[6] > v1.v[6] ? G_U64_ONE : G_U64_ZERO;
	v0.v[7] = v0.v[7] > v1.v[7] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec8u64_t Vec8u64_CmpGE(vec8u64_t v0, vec8u64_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] >= v1.v[5] ? G_U64_ONE : G_U64_ZERO;
	v0.v[6] = v0.v[6] >= v1.v[6] ? G_U64_ONE : G_U64_ZERO;
	v0.v[7] = v0.v[7] >= v1.v[7] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec8u64_t Vec8u64_CmpNE(vec8u64_t v0, vec8u64_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] != v1.v[5] ? G_U64_ONE : G_U64_ZERO;
	v0.v[6] = v0.v[6] != v1.v[6] ? G_U64_ONE : G_U64_ZERO;
	v0.v[7] = v0.v[7] != v1.v[7] ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec8u64_t Vec8u64_CmpLTS(vec8u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] < x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] < x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] < x ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] < x ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] < x ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] < x ? G_U64_ONE : G_U64_ZERO;
	v0.v[6] = v0.v[6] < x ? G_U64_ONE : G_U64_ZERO;
	v0.v[7] = v0.v[7] < x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec8u64_t Vec8u64_CmpLES(vec8u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] <= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[6] = v0.v[6] <= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[7] = v0.v[7] <= x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec8u64_t Vec8u64_CmpEQS(vec8u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] == x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] == x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] == x ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] == x ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] == x ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] == x ? G_U64_ONE : G_U64_ZERO;
	v0.v[6] = v0.v[6] == x ? G_U64_ONE : G_U64_ZERO;
	v0.v[7] = v0.v[7] == x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec8u64_t Vec8u64_CmpGTS(vec8u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] > x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] > x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] > x ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] > x ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] > x ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] > x ? G_U64_ONE : G_U64_ZERO;
	v0.v[6] = v0.v[6] > x ? G_U64_ONE : G_U64_ZERO;
	v0.v[7] = v0.v[7] > x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec8u64_t Vec8u64_CmpGES(vec8u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] >= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[6] = v0.v[6] >= x ? G_U64_ONE : G_U64_ZERO;
	v0.v[7] = v0.v[7] >= x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec8u64_t Vec8u64_CmpNES(vec8u64_t v0, uint64_t x)
{
	v0.v[0] = v0.v[0] != x ? G_U64_ONE : G_U64_ZERO;
	v0.v[1] = v0.v[1] != x ? G_U64_ONE : G_U64_ZERO;
	v0.v[2] = v0.v[2] != x ? G_U64_ONE : G_U64_ZERO;
	v0.v[3] = v0.v[3] != x ? G_U64_ONE : G_U64_ZERO;
	v0.v[4] = v0.v[4] != x ? G_U64_ONE : G_U64_ZERO;
	v0.v[5] = v0.v[5] != x ? G_U64_ONE : G_U64_ZERO;
	v0.v[6] = v0.v[6] != x ? G_U64_ONE : G_U64_ZERO;
	v0.v[7] = v0.v[7] != x ? G_U64_ONE : G_U64_ZERO;

	return v0;
}
vec8u64_t Vec8u64_Sign(vec8u64_t v)
{
	v.v[0] = v.v[0] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;
	v.v[1] = v.v[1] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;
	v.v[2] = v.v[2] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;
	v.v[3] = v.v[3] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;
	v.v[4] = v.v[4] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;
	v.v[5] = v.v[5] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;
	v.v[6] = v.v[6] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;
	v.v[7] = v.v[7] < G_U64_ZERO ? G_U64_ONE : G_U64_ZERO;

	return v;
}
vec8u64_t Vec8u64_SignPosNeg(vec8u64_t v)
{
	v.v[0] = v.v[0] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;
	v.v[1] = v.v[1] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;
	v.v[2] = v.v[2] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;
	v.v[3] = v.v[3] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;
	v.v[4] = v.v[4] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;
	v.v[5] = v.v[5] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;
	v.v[6] = v.v[6] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;
	v.v[7] = v.v[7] < G_U64_ZERO ? G_U64_NEG_ONE : G_U64_ONE;

	return v;
}
vec8u64_t Vec8u64_Zero()
{
	return G_VEC8U64_T_ZERO;
}
vec8u64_t Vec8u64_One()
{
	return G_VEC8U64_T_ONE;
}
vec8u64_t Vec8u64_Cross(vec8u64_t v0, vec8u64_t v1, vec8u64_t v2, vec8u64_t v3, vec8u64_t v4, vec8u64_t v5, vec8u64_t v6)
{
	vec8u64_t v;
	mat8x8u64_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;
	mat.v[5] = v4;
	mat.v[6] = v5;
	mat.v[7] = v6;

	for (i = 0; i < 8; i++)
		v.v[i] = Mat7x7u64_Det(Mat8x8u64_DeleteRowColumn(mat, 0, i));

	return v;
}
vec8i64_t Vec8i64_SetComponent(vec8i64_t v, int index, int64_t value)
{
	v.v[index] = value;

	return v;
}
vec8i64_t Vec8i64_Vec(int64_t x0, int64_t x1, int64_t x2, int64_t x3, int64_t x4, int64_t x5, int64_t x6, int64_t x7)
{
	vec8i64_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;
	v.v[5] = x5;
	v.v[6] = x6;
	v.v[7] = x7;

	return v;
}
vec8i64_t Vec8i64_Add(vec8i64_t v0, vec8i64_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];
	v0.v[5] += v1.v[5];
	v0.v[6] += v1.v[6];
	v0.v[7] += v1.v[7];

	return v0;
}
vec8i64_t Vec8i64_Sub(vec8i64_t v0, vec8i64_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];
	v0.v[5] -= v1.v[5];
	v0.v[6] -= v1.v[6];
	v0.v[7] -= v1.v[7];

	return v0;
}
int64_t Vec8i64_GetComponent(vec8i64_t v, int index)
{
	return v.v[index];
}
vec8i64_t Vec8i64_Mul(vec8i64_t v0, vec8i64_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];
	v0.v[5] *= v1.v[5];
	v0.v[6] *= v1.v[6];
	v0.v[7] *= v1.v[7];

	return v0;
}
vec8i64_t Vec8i64_Div(vec8i64_t v0, vec8i64_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];
	v0.v[5] /= v1.v[5];
	v0.v[6] /= v1.v[6];
	v0.v[7] /= v1.v[7];

	return v0;
}
vec8i64_t Vec8i64_Scale(vec8i64_t v, int64_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;
	v.v[5] *= scale;
	v.v[6] *= scale;
	v.v[7] *= scale;

	return v;
}
vec8i64_t Vec8i64_DivScale(vec8i64_t v, int64_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;
	v.v[5] /= divscale;
	v.v[6] /= divscale;
	v.v[7] /= divscale;

	return v;
}
vec8i64_t Vec8i64_MA(vec8i64_t v, vec8i64_t dir, int64_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;
	v.v[5] += dir.v[5] * scale;
	v.v[6] += dir.v[6] * scale;
	v.v[7] += dir.v[7] * scale;

	return v;
}
vec8i64_t Vec8i64_DA(vec8i64_t v, vec8i64_t dir, int64_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;
	v.v[5] += dir.v[5] / divscale;
	v.v[6] += dir.v[6] / divscale;
	v.v[7] += dir.v[7] / divscale;

	return v;
}
int64_t Vec8i64_Dot(vec8i64_t v0, vec8i64_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4] + v0.v[5] * v1.v[5] + v0.v[6] * v1.v[6] + v0.v[7] * v1.v[7];
}
int64_t Vec8i64_LenSq(vec8i64_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4] + v.v[5] * v.v[5] + v.v[6] * v.v[6] + v.v[7] * v.v[7];
}
int64_t Vec8i64_Len(vec8i64_t v)
{
	return sqrt(Vec8i64_LenSq(v));
}
vec8i64_t Vec8i64_Abs(vec8i64_t v)
{
	v.v[0] = (v.v[0] < 0 ? -v.v[0] : v.v[0]);
	v.v[1] = (v.v[1] < 0 ? -v.v[1] : v.v[1]);
	v.v[2] = (v.v[2] < 0 ? -v.v[2] : v.v[2]);
	v.v[3] = (v.v[3] < 0 ? -v.v[3] : v.v[3]);
	v.v[4] = (v.v[4] < 0 ? -v.v[4] : v.v[4]);
	v.v[5] = (v.v[5] < 0 ? -v.v[5] : v.v[5]);
	v.v[6] = (v.v[6] < 0 ? -v.v[6] : v.v[6]);
	v.v[7] = (v.v[7] < 0 ? -v.v[7] : v.v[7]);

	return v;
}
vec8i64_t Vec8i64_Mod(vec8i64_t v0, vec8i64_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);
	v0.v[4] = (v0.v[4] % v1.v[4]);
	v0.v[5] = (v0.v[5] % v1.v[5]);
	v0.v[6] = (v0.v[6] % v1.v[6]);
	v0.v[7] = (v0.v[7] % v1.v[7]);

	return v0;
}
vec8i64_t Vec8i64_ModS(vec8i64_t v0, int64_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);
	v0.v[4] = (v0.v[4] % x);
	v0.v[5] = (v0.v[5] % x);
	v0.v[6] = (v0.v[6] % x);
	v0.v[7] = (v0.v[7] % x);

	return v0;
}
vec8i64_t Vec8i64_Min(vec8i64_t v0, vec8i64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] < v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] < v1.v[6] ? v0.v[6] : v1.v[6];
	v0.v[7] = v0.v[7] < v1.v[7] ? v0.v[7] : v1.v[7];

	return v0;
}
vec8i64_t Vec8i64_Max(vec8i64_t v0, vec8i64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] > v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] > v1.v[6] ? v0.v[6] : v1.v[6];
	v0.v[7] = v0.v[7] > v1.v[7] ? v0.v[7] : v1.v[7];

	return v0;
}
vec8i64_t Vec8i64_MinS(vec8i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] < x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] < x ? v0.v[6] : x;
	v0.v[7] = v0.v[7] < x ? v0.v[7] : x;

	return v0;
}
vec8i64_t Vec8i64_MaxS(vec8i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] > x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] > x ? v0.v[6] : x;
	v0.v[7] = v0.v[7] > x ? v0.v[7] : x;

	return v0;
}
vec8i64_t Vec8i64_Clamp(vec8i64_t v, vec8i64_t min, vec8i64_t max)
{
	return Vec8i64_Max(Vec8i64_Min(v, max), min);
}
vec8i64_t Vec8i64_ClampS(vec8i64_t v, int64_t min, int64_t max)
{
	return Vec8i64_MaxS(Vec8i64_MinS(v, max), min);
}
vec8i64_t Vec8i64_Neg(vec8i64_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];
	v.v[3] = -v.v[3];
	v.v[4] = -v.v[4];
	v.v[5] = -v.v[5];
	v.v[6] = -v.v[6];
	v.v[7] = -v.v[7];

	return v;
}
vec8i64_t Vec8i64_CmpLT(vec8i64_t v0, vec8i64_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] < v1.v[5] ? G_I64_ONE : G_I64_ZERO;
	v0.v[6] = v0.v[6] < v1.v[6] ? G_I64_ONE : G_I64_ZERO;
	v0.v[7] = v0.v[7] < v1.v[7] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec8i64_t Vec8i64_CmpLE(vec8i64_t v0, vec8i64_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] <= v1.v[5] ? G_I64_ONE : G_I64_ZERO;
	v0.v[6] = v0.v[6] <= v1.v[6] ? G_I64_ONE : G_I64_ZERO;
	v0.v[7] = v0.v[7] <= v1.v[7] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec8i64_t Vec8i64_CmpEQ(vec8i64_t v0, vec8i64_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] == v1.v[5] ? G_I64_ONE : G_I64_ZERO;
	v0.v[6] = v0.v[6] == v1.v[6] ? G_I64_ONE : G_I64_ZERO;
	v0.v[7] = v0.v[7] == v1.v[7] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec8i64_t Vec8i64_CmpGT(vec8i64_t v0, vec8i64_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] > v1.v[5] ? G_I64_ONE : G_I64_ZERO;
	v0.v[6] = v0.v[6] > v1.v[6] ? G_I64_ONE : G_I64_ZERO;
	v0.v[7] = v0.v[7] > v1.v[7] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec8i64_t Vec8i64_CmpGE(vec8i64_t v0, vec8i64_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] >= v1.v[5] ? G_I64_ONE : G_I64_ZERO;
	v0.v[6] = v0.v[6] >= v1.v[6] ? G_I64_ONE : G_I64_ZERO;
	v0.v[7] = v0.v[7] >= v1.v[7] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec8i64_t Vec8i64_CmpNE(vec8i64_t v0, vec8i64_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] != v1.v[5] ? G_I64_ONE : G_I64_ZERO;
	v0.v[6] = v0.v[6] != v1.v[6] ? G_I64_ONE : G_I64_ZERO;
	v0.v[7] = v0.v[7] != v1.v[7] ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec8i64_t Vec8i64_CmpLTS(vec8i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] < x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] < x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] < x ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] < x ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] < x ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] < x ? G_I64_ONE : G_I64_ZERO;
	v0.v[6] = v0.v[6] < x ? G_I64_ONE : G_I64_ZERO;
	v0.v[7] = v0.v[7] < x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec8i64_t Vec8i64_CmpLES(vec8i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] <= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[6] = v0.v[6] <= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[7] = v0.v[7] <= x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec8i64_t Vec8i64_CmpEQS(vec8i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] == x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] == x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] == x ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] == x ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] == x ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] == x ? G_I64_ONE : G_I64_ZERO;
	v0.v[6] = v0.v[6] == x ? G_I64_ONE : G_I64_ZERO;
	v0.v[7] = v0.v[7] == x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec8i64_t Vec8i64_CmpGTS(vec8i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] > x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] > x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] > x ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] > x ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] > x ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] > x ? G_I64_ONE : G_I64_ZERO;
	v0.v[6] = v0.v[6] > x ? G_I64_ONE : G_I64_ZERO;
	v0.v[7] = v0.v[7] > x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec8i64_t Vec8i64_CmpGES(vec8i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] >= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[6] = v0.v[6] >= x ? G_I64_ONE : G_I64_ZERO;
	v0.v[7] = v0.v[7] >= x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec8i64_t Vec8i64_CmpNES(vec8i64_t v0, int64_t x)
{
	v0.v[0] = v0.v[0] != x ? G_I64_ONE : G_I64_ZERO;
	v0.v[1] = v0.v[1] != x ? G_I64_ONE : G_I64_ZERO;
	v0.v[2] = v0.v[2] != x ? G_I64_ONE : G_I64_ZERO;
	v0.v[3] = v0.v[3] != x ? G_I64_ONE : G_I64_ZERO;
	v0.v[4] = v0.v[4] != x ? G_I64_ONE : G_I64_ZERO;
	v0.v[5] = v0.v[5] != x ? G_I64_ONE : G_I64_ZERO;
	v0.v[6] = v0.v[6] != x ? G_I64_ONE : G_I64_ZERO;
	v0.v[7] = v0.v[7] != x ? G_I64_ONE : G_I64_ZERO;

	return v0;
}
vec8i64_t Vec8i64_Sign(vec8i64_t v)
{
	v.v[0] = v.v[0] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;
	v.v[1] = v.v[1] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;
	v.v[2] = v.v[2] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;
	v.v[3] = v.v[3] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;
	v.v[4] = v.v[4] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;
	v.v[5] = v.v[5] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;
	v.v[6] = v.v[6] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;
	v.v[7] = v.v[7] < G_I64_ZERO ? G_I64_ONE : G_I64_ZERO;

	return v;
}
vec8i64_t Vec8i64_SignPosNeg(vec8i64_t v)
{
	v.v[0] = v.v[0] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;
	v.v[1] = v.v[1] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;
	v.v[2] = v.v[2] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;
	v.v[3] = v.v[3] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;
	v.v[4] = v.v[4] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;
	v.v[5] = v.v[5] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;
	v.v[6] = v.v[6] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;
	v.v[7] = v.v[7] < G_I64_ZERO ? G_I64_NEG_ONE : G_I64_ONE;

	return v;
}
vec8i64_t Vec8i64_Zero()
{
	return G_VEC8I64_T_ZERO;
}
vec8i64_t Vec8i64_One()
{
	return G_VEC8I64_T_ONE;
}
vec8i64_t Vec8i64_NegOne()
{
	return Vec8i64_Neg(G_VEC8I64_T_ONE);
}
vec8i64_t Vec8i64_Cross(vec8i64_t v0, vec8i64_t v1, vec8i64_t v2, vec8i64_t v3, vec8i64_t v4, vec8i64_t v5, vec8i64_t v6)
{
	vec8i64_t v;
	mat8x8i64_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;
	mat.v[5] = v4;
	mat.v[6] = v5;
	mat.v[7] = v6;

	for (i = 0; i < 8; i++)
		v.v[i] = Mat7x7i64_Det(Mat8x8i64_DeleteRowColumn(mat, 0, i));

	return v;
}
vec8u32_t Vec8u32_SetComponent(vec8u32_t v, int index, uint32_t value)
{
	v.v[index] = value;

	return v;
}
vec8u32_t Vec8u32_Vec(uint32_t x0, uint32_t x1, uint32_t x2, uint32_t x3, uint32_t x4, uint32_t x5, uint32_t x6, uint32_t x7)
{
	vec8u32_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;
	v.v[5] = x5;
	v.v[6] = x6;
	v.v[7] = x7;

	return v;
}
vec8u32_t Vec8u32_Add(vec8u32_t v0, vec8u32_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];
	v0.v[5] += v1.v[5];
	v0.v[6] += v1.v[6];
	v0.v[7] += v1.v[7];

	return v0;
}
vec8u32_t Vec8u32_Sub(vec8u32_t v0, vec8u32_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];
	v0.v[5] -= v1.v[5];
	v0.v[6] -= v1.v[6];
	v0.v[7] -= v1.v[7];

	return v0;
}
uint32_t Vec8u32_GetComponent(vec8u32_t v, int index)
{
	return v.v[index];
}
vec8u32_t Vec8u32_Mul(vec8u32_t v0, vec8u32_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];
	v0.v[5] *= v1.v[5];
	v0.v[6] *= v1.v[6];
	v0.v[7] *= v1.v[7];

	return v0;
}
vec8u32_t Vec8u32_Div(vec8u32_t v0, vec8u32_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];
	v0.v[5] /= v1.v[5];
	v0.v[6] /= v1.v[6];
	v0.v[7] /= v1.v[7];

	return v0;
}
vec8u32_t Vec8u32_Scale(vec8u32_t v, uint32_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;
	v.v[5] *= scale;
	v.v[6] *= scale;
	v.v[7] *= scale;

	return v;
}
vec8u32_t Vec8u32_DivScale(vec8u32_t v, uint32_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;
	v.v[5] /= divscale;
	v.v[6] /= divscale;
	v.v[7] /= divscale;

	return v;
}
vec8u32_t Vec8u32_MA(vec8u32_t v, vec8u32_t dir, uint32_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;
	v.v[5] += dir.v[5] * scale;
	v.v[6] += dir.v[6] * scale;
	v.v[7] += dir.v[7] * scale;

	return v;
}
vec8u32_t Vec8u32_DA(vec8u32_t v, vec8u32_t dir, uint32_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;
	v.v[5] += dir.v[5] / divscale;
	v.v[6] += dir.v[6] / divscale;
	v.v[7] += dir.v[7] / divscale;

	return v;
}
uint32_t Vec8u32_Dot(vec8u32_t v0, vec8u32_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4] + v0.v[5] * v1.v[5] + v0.v[6] * v1.v[6] + v0.v[7] * v1.v[7];
}
uint32_t Vec8u32_LenSq(vec8u32_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4] + v.v[5] * v.v[5] + v.v[6] * v.v[6] + v.v[7] * v.v[7];
}
uint32_t Vec8u32_Len(vec8u32_t v)
{
	return sqrtf(Vec8u32_LenSq(v));
}
vec8u32_t Vec8u32_Mod(vec8u32_t v0, vec8u32_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);
	v0.v[4] = (v0.v[4] % v1.v[4]);
	v0.v[5] = (v0.v[5] % v1.v[5]);
	v0.v[6] = (v0.v[6] % v1.v[6]);
	v0.v[7] = (v0.v[7] % v1.v[7]);

	return v0;
}
vec8u32_t Vec8u32_ModS(vec8u32_t v0, uint32_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);
	v0.v[4] = (v0.v[4] % x);
	v0.v[5] = (v0.v[5] % x);
	v0.v[6] = (v0.v[6] % x);
	v0.v[7] = (v0.v[7] % x);

	return v0;
}
vec8u32_t Vec8u32_Min(vec8u32_t v0, vec8u32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] < v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] < v1.v[6] ? v0.v[6] : v1.v[6];
	v0.v[7] = v0.v[7] < v1.v[7] ? v0.v[7] : v1.v[7];

	return v0;
}
vec8u32_t Vec8u32_Max(vec8u32_t v0, vec8u32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] > v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] > v1.v[6] ? v0.v[6] : v1.v[6];
	v0.v[7] = v0.v[7] > v1.v[7] ? v0.v[7] : v1.v[7];

	return v0;
}
vec8u32_t Vec8u32_MinS(vec8u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] < x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] < x ? v0.v[6] : x;
	v0.v[7] = v0.v[7] < x ? v0.v[7] : x;

	return v0;
}
vec8u32_t Vec8u32_MaxS(vec8u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] > x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] > x ? v0.v[6] : x;
	v0.v[7] = v0.v[7] > x ? v0.v[7] : x;

	return v0;
}
vec8u32_t Vec8u32_Clamp(vec8u32_t v, vec8u32_t min, vec8u32_t max)
{
	return Vec8u32_Max(Vec8u32_Min(v, max), min);
}
vec8u32_t Vec8u32_ClampS(vec8u32_t v, uint32_t min, uint32_t max)
{
	return Vec8u32_MaxS(Vec8u32_MinS(v, max), min);
}
vec8u32_t Vec8u32_CmpLT(vec8u32_t v0, vec8u32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] < v1.v[5] ? G_U32_ONE : G_U32_ZERO;
	v0.v[6] = v0.v[6] < v1.v[6] ? G_U32_ONE : G_U32_ZERO;
	v0.v[7] = v0.v[7] < v1.v[7] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec8u32_t Vec8u32_CmpLE(vec8u32_t v0, vec8u32_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] <= v1.v[5] ? G_U32_ONE : G_U32_ZERO;
	v0.v[6] = v0.v[6] <= v1.v[6] ? G_U32_ONE : G_U32_ZERO;
	v0.v[7] = v0.v[7] <= v1.v[7] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec8u32_t Vec8u32_CmpEQ(vec8u32_t v0, vec8u32_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] == v1.v[5] ? G_U32_ONE : G_U32_ZERO;
	v0.v[6] = v0.v[6] == v1.v[6] ? G_U32_ONE : G_U32_ZERO;
	v0.v[7] = v0.v[7] == v1.v[7] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec8u32_t Vec8u32_CmpGT(vec8u32_t v0, vec8u32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] > v1.v[5] ? G_U32_ONE : G_U32_ZERO;
	v0.v[6] = v0.v[6] > v1.v[6] ? G_U32_ONE : G_U32_ZERO;
	v0.v[7] = v0.v[7] > v1.v[7] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec8u32_t Vec8u32_CmpGE(vec8u32_t v0, vec8u32_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] >= v1.v[5] ? G_U32_ONE : G_U32_ZERO;
	v0.v[6] = v0.v[6] >= v1.v[6] ? G_U32_ONE : G_U32_ZERO;
	v0.v[7] = v0.v[7] >= v1.v[7] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec8u32_t Vec8u32_CmpNE(vec8u32_t v0, vec8u32_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] != v1.v[5] ? G_U32_ONE : G_U32_ZERO;
	v0.v[6] = v0.v[6] != v1.v[6] ? G_U32_ONE : G_U32_ZERO;
	v0.v[7] = v0.v[7] != v1.v[7] ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec8u32_t Vec8u32_CmpLTS(vec8u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] < x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] < x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] < x ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] < x ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] < x ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] < x ? G_U32_ONE : G_U32_ZERO;
	v0.v[6] = v0.v[6] < x ? G_U32_ONE : G_U32_ZERO;
	v0.v[7] = v0.v[7] < x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec8u32_t Vec8u32_CmpLES(vec8u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] <= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[6] = v0.v[6] <= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[7] = v0.v[7] <= x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec8u32_t Vec8u32_CmpEQS(vec8u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] == x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] == x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] == x ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] == x ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] == x ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] == x ? G_U32_ONE : G_U32_ZERO;
	v0.v[6] = v0.v[6] == x ? G_U32_ONE : G_U32_ZERO;
	v0.v[7] = v0.v[7] == x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec8u32_t Vec8u32_CmpGTS(vec8u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] > x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] > x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] > x ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] > x ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] > x ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] > x ? G_U32_ONE : G_U32_ZERO;
	v0.v[6] = v0.v[6] > x ? G_U32_ONE : G_U32_ZERO;
	v0.v[7] = v0.v[7] > x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec8u32_t Vec8u32_CmpGES(vec8u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] >= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[6] = v0.v[6] >= x ? G_U32_ONE : G_U32_ZERO;
	v0.v[7] = v0.v[7] >= x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec8u32_t Vec8u32_CmpNES(vec8u32_t v0, uint32_t x)
{
	v0.v[0] = v0.v[0] != x ? G_U32_ONE : G_U32_ZERO;
	v0.v[1] = v0.v[1] != x ? G_U32_ONE : G_U32_ZERO;
	v0.v[2] = v0.v[2] != x ? G_U32_ONE : G_U32_ZERO;
	v0.v[3] = v0.v[3] != x ? G_U32_ONE : G_U32_ZERO;
	v0.v[4] = v0.v[4] != x ? G_U32_ONE : G_U32_ZERO;
	v0.v[5] = v0.v[5] != x ? G_U32_ONE : G_U32_ZERO;
	v0.v[6] = v0.v[6] != x ? G_U32_ONE : G_U32_ZERO;
	v0.v[7] = v0.v[7] != x ? G_U32_ONE : G_U32_ZERO;

	return v0;
}
vec8u32_t Vec8u32_Sign(vec8u32_t v)
{
	v.v[0] = v.v[0] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;
	v.v[1] = v.v[1] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;
	v.v[2] = v.v[2] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;
	v.v[3] = v.v[3] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;
	v.v[4] = v.v[4] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;
	v.v[5] = v.v[5] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;
	v.v[6] = v.v[6] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;
	v.v[7] = v.v[7] < G_U32_ZERO ? G_U32_ONE : G_U32_ZERO;

	return v;
}
vec8u32_t Vec8u32_SignPosNeg(vec8u32_t v)
{
	v.v[0] = v.v[0] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;
	v.v[1] = v.v[1] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;
	v.v[2] = v.v[2] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;
	v.v[3] = v.v[3] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;
	v.v[4] = v.v[4] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;
	v.v[5] = v.v[5] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;
	v.v[6] = v.v[6] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;
	v.v[7] = v.v[7] < G_U32_ZERO ? G_U32_NEG_ONE : G_U32_ONE;

	return v;
}
vec8u32_t Vec8u32_Zero()
{
	return G_VEC8U32_T_ZERO;
}
vec8u32_t Vec8u32_One()
{
	return G_VEC8U32_T_ONE;
}
vec8u32_t Vec8u32_Cross(vec8u32_t v0, vec8u32_t v1, vec8u32_t v2, vec8u32_t v3, vec8u32_t v4, vec8u32_t v5, vec8u32_t v6)
{
	vec8u32_t v;
	mat8x8u32_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;
	mat.v[5] = v4;
	mat.v[6] = v5;
	mat.v[7] = v6;

	for (i = 0; i < 8; i++)
		v.v[i] = Mat7x7u32_Det(Mat8x8u32_DeleteRowColumn(mat, 0, i));

	return v;
}
vec8i32_t Vec8i32_SetComponent(vec8i32_t v, int index, int32_t value)
{
	v.v[index] = value;

	return v;
}
vec8i32_t Vec8i32_Vec(int32_t x0, int32_t x1, int32_t x2, int32_t x3, int32_t x4, int32_t x5, int32_t x6, int32_t x7)
{
	vec8i32_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;
	v.v[5] = x5;
	v.v[6] = x6;
	v.v[7] = x7;

	return v;
}
vec8i32_t Vec8i32_Add(vec8i32_t v0, vec8i32_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];
	v0.v[5] += v1.v[5];
	v0.v[6] += v1.v[6];
	v0.v[7] += v1.v[7];

	return v0;
}
vec8i32_t Vec8i32_Sub(vec8i32_t v0, vec8i32_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];
	v0.v[5] -= v1.v[5];
	v0.v[6] -= v1.v[6];
	v0.v[7] -= v1.v[7];

	return v0;
}
int32_t Vec8i32_GetComponent(vec8i32_t v, int index)
{
	return v.v[index];
}
vec8i32_t Vec8i32_Mul(vec8i32_t v0, vec8i32_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];
	v0.v[5] *= v1.v[5];
	v0.v[6] *= v1.v[6];
	v0.v[7] *= v1.v[7];

	return v0;
}
vec8i32_t Vec8i32_Div(vec8i32_t v0, vec8i32_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];
	v0.v[5] /= v1.v[5];
	v0.v[6] /= v1.v[6];
	v0.v[7] /= v1.v[7];

	return v0;
}
vec8i32_t Vec8i32_Scale(vec8i32_t v, int32_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;
	v.v[5] *= scale;
	v.v[6] *= scale;
	v.v[7] *= scale;

	return v;
}
vec8i32_t Vec8i32_DivScale(vec8i32_t v, int32_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;
	v.v[5] /= divscale;
	v.v[6] /= divscale;
	v.v[7] /= divscale;

	return v;
}
vec8i32_t Vec8i32_MA(vec8i32_t v, vec8i32_t dir, int32_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;
	v.v[5] += dir.v[5] * scale;
	v.v[6] += dir.v[6] * scale;
	v.v[7] += dir.v[7] * scale;

	return v;
}
vec8i32_t Vec8i32_DA(vec8i32_t v, vec8i32_t dir, int32_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;
	v.v[5] += dir.v[5] / divscale;
	v.v[6] += dir.v[6] / divscale;
	v.v[7] += dir.v[7] / divscale;

	return v;
}
int32_t Vec8i32_Dot(vec8i32_t v0, vec8i32_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4] + v0.v[5] * v1.v[5] + v0.v[6] * v1.v[6] + v0.v[7] * v1.v[7];
}
int32_t Vec8i32_LenSq(vec8i32_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4] + v.v[5] * v.v[5] + v.v[6] * v.v[6] + v.v[7] * v.v[7];
}
int32_t Vec8i32_Len(vec8i32_t v)
{
	return sqrtf(Vec8i32_LenSq(v));
}
vec8i32_t Vec8i32_Abs(vec8i32_t v)
{
	v.v[0] = (v.v[0] < 0 ? -v.v[0] : v.v[0]);
	v.v[1] = (v.v[1] < 0 ? -v.v[1] : v.v[1]);
	v.v[2] = (v.v[2] < 0 ? -v.v[2] : v.v[2]);
	v.v[3] = (v.v[3] < 0 ? -v.v[3] : v.v[3]);
	v.v[4] = (v.v[4] < 0 ? -v.v[4] : v.v[4]);
	v.v[5] = (v.v[5] < 0 ? -v.v[5] : v.v[5]);
	v.v[6] = (v.v[6] < 0 ? -v.v[6] : v.v[6]);
	v.v[7] = (v.v[7] < 0 ? -v.v[7] : v.v[7]);

	return v;
}
vec8i32_t Vec8i32_Mod(vec8i32_t v0, vec8i32_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);
	v0.v[4] = (v0.v[4] % v1.v[4]);
	v0.v[5] = (v0.v[5] % v1.v[5]);
	v0.v[6] = (v0.v[6] % v1.v[6]);
	v0.v[7] = (v0.v[7] % v1.v[7]);

	return v0;
}
vec8i32_t Vec8i32_ModS(vec8i32_t v0, int32_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);
	v0.v[4] = (v0.v[4] % x);
	v0.v[5] = (v0.v[5] % x);
	v0.v[6] = (v0.v[6] % x);
	v0.v[7] = (v0.v[7] % x);

	return v0;
}
vec8i32_t Vec8i32_Min(vec8i32_t v0, vec8i32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] < v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] < v1.v[6] ? v0.v[6] : v1.v[6];
	v0.v[7] = v0.v[7] < v1.v[7] ? v0.v[7] : v1.v[7];

	return v0;
}
vec8i32_t Vec8i32_Max(vec8i32_t v0, vec8i32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] > v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] > v1.v[6] ? v0.v[6] : v1.v[6];
	v0.v[7] = v0.v[7] > v1.v[7] ? v0.v[7] : v1.v[7];

	return v0;
}
vec8i32_t Vec8i32_MinS(vec8i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] < x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] < x ? v0.v[6] : x;
	v0.v[7] = v0.v[7] < x ? v0.v[7] : x;

	return v0;
}
vec8i32_t Vec8i32_MaxS(vec8i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] > x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] > x ? v0.v[6] : x;
	v0.v[7] = v0.v[7] > x ? v0.v[7] : x;

	return v0;
}
vec8i32_t Vec8i32_Clamp(vec8i32_t v, vec8i32_t min, vec8i32_t max)
{
	return Vec8i32_Max(Vec8i32_Min(v, max), min);
}
vec8i32_t Vec8i32_ClampS(vec8i32_t v, int32_t min, int32_t max)
{
	return Vec8i32_MaxS(Vec8i32_MinS(v, max), min);
}
vec8i32_t Vec8i32_Neg(vec8i32_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];
	v.v[3] = -v.v[3];
	v.v[4] = -v.v[4];
	v.v[5] = -v.v[5];
	v.v[6] = -v.v[6];
	v.v[7] = -v.v[7];

	return v;
}
vec8i32_t Vec8i32_CmpLT(vec8i32_t v0, vec8i32_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] < v1.v[5] ? G_I32_ONE : G_I32_ZERO;
	v0.v[6] = v0.v[6] < v1.v[6] ? G_I32_ONE : G_I32_ZERO;
	v0.v[7] = v0.v[7] < v1.v[7] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec8i32_t Vec8i32_CmpLE(vec8i32_t v0, vec8i32_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] <= v1.v[5] ? G_I32_ONE : G_I32_ZERO;
	v0.v[6] = v0.v[6] <= v1.v[6] ? G_I32_ONE : G_I32_ZERO;
	v0.v[7] = v0.v[7] <= v1.v[7] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec8i32_t Vec8i32_CmpEQ(vec8i32_t v0, vec8i32_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] == v1.v[5] ? G_I32_ONE : G_I32_ZERO;
	v0.v[6] = v0.v[6] == v1.v[6] ? G_I32_ONE : G_I32_ZERO;
	v0.v[7] = v0.v[7] == v1.v[7] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec8i32_t Vec8i32_CmpGT(vec8i32_t v0, vec8i32_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] > v1.v[5] ? G_I32_ONE : G_I32_ZERO;
	v0.v[6] = v0.v[6] > v1.v[6] ? G_I32_ONE : G_I32_ZERO;
	v0.v[7] = v0.v[7] > v1.v[7] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec8i32_t Vec8i32_CmpGE(vec8i32_t v0, vec8i32_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] >= v1.v[5] ? G_I32_ONE : G_I32_ZERO;
	v0.v[6] = v0.v[6] >= v1.v[6] ? G_I32_ONE : G_I32_ZERO;
	v0.v[7] = v0.v[7] >= v1.v[7] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec8i32_t Vec8i32_CmpNE(vec8i32_t v0, vec8i32_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] != v1.v[5] ? G_I32_ONE : G_I32_ZERO;
	v0.v[6] = v0.v[6] != v1.v[6] ? G_I32_ONE : G_I32_ZERO;
	v0.v[7] = v0.v[7] != v1.v[7] ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec8i32_t Vec8i32_CmpLTS(vec8i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] < x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] < x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] < x ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] < x ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] < x ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] < x ? G_I32_ONE : G_I32_ZERO;
	v0.v[6] = v0.v[6] < x ? G_I32_ONE : G_I32_ZERO;
	v0.v[7] = v0.v[7] < x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec8i32_t Vec8i32_CmpLES(vec8i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] <= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[6] = v0.v[6] <= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[7] = v0.v[7] <= x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec8i32_t Vec8i32_CmpEQS(vec8i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] == x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] == x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] == x ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] == x ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] == x ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] == x ? G_I32_ONE : G_I32_ZERO;
	v0.v[6] = v0.v[6] == x ? G_I32_ONE : G_I32_ZERO;
	v0.v[7] = v0.v[7] == x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec8i32_t Vec8i32_CmpGTS(vec8i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] > x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] > x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] > x ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] > x ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] > x ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] > x ? G_I32_ONE : G_I32_ZERO;
	v0.v[6] = v0.v[6] > x ? G_I32_ONE : G_I32_ZERO;
	v0.v[7] = v0.v[7] > x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec8i32_t Vec8i32_CmpGES(vec8i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] >= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[6] = v0.v[6] >= x ? G_I32_ONE : G_I32_ZERO;
	v0.v[7] = v0.v[7] >= x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec8i32_t Vec8i32_CmpNES(vec8i32_t v0, int32_t x)
{
	v0.v[0] = v0.v[0] != x ? G_I32_ONE : G_I32_ZERO;
	v0.v[1] = v0.v[1] != x ? G_I32_ONE : G_I32_ZERO;
	v0.v[2] = v0.v[2] != x ? G_I32_ONE : G_I32_ZERO;
	v0.v[3] = v0.v[3] != x ? G_I32_ONE : G_I32_ZERO;
	v0.v[4] = v0.v[4] != x ? G_I32_ONE : G_I32_ZERO;
	v0.v[5] = v0.v[5] != x ? G_I32_ONE : G_I32_ZERO;
	v0.v[6] = v0.v[6] != x ? G_I32_ONE : G_I32_ZERO;
	v0.v[7] = v0.v[7] != x ? G_I32_ONE : G_I32_ZERO;

	return v0;
}
vec8i32_t Vec8i32_Sign(vec8i32_t v)
{
	v.v[0] = v.v[0] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;
	v.v[1] = v.v[1] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;
	v.v[2] = v.v[2] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;
	v.v[3] = v.v[3] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;
	v.v[4] = v.v[4] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;
	v.v[5] = v.v[5] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;
	v.v[6] = v.v[6] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;
	v.v[7] = v.v[7] < G_I32_ZERO ? G_I32_ONE : G_I32_ZERO;

	return v;
}
vec8i32_t Vec8i32_SignPosNeg(vec8i32_t v)
{
	v.v[0] = v.v[0] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;
	v.v[1] = v.v[1] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;
	v.v[2] = v.v[2] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;
	v.v[3] = v.v[3] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;
	v.v[4] = v.v[4] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;
	v.v[5] = v.v[5] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;
	v.v[6] = v.v[6] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;
	v.v[7] = v.v[7] < G_I32_ZERO ? G_I32_NEG_ONE : G_I32_ONE;

	return v;
}
vec8i32_t Vec8i32_Zero()
{
	return G_VEC8I32_T_ZERO;
}
vec8i32_t Vec8i32_One()
{
	return G_VEC8I32_T_ONE;
}
vec8i32_t Vec8i32_NegOne()
{
	return Vec8i32_Neg(G_VEC8I32_T_ONE);
}
vec8i32_t Vec8i32_Cross(vec8i32_t v0, vec8i32_t v1, vec8i32_t v2, vec8i32_t v3, vec8i32_t v4, vec8i32_t v5, vec8i32_t v6)
{
	vec8i32_t v;
	mat8x8i32_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;
	mat.v[5] = v4;
	mat.v[6] = v5;
	mat.v[7] = v6;

	for (i = 0; i < 8; i++)
		v.v[i] = Mat7x7i32_Det(Mat8x8i32_DeleteRowColumn(mat, 0, i));

	return v;
}
vec8u16_t Vec8u16_SetComponent(vec8u16_t v, int index, uint16_t value)
{
	v.v[index] = value;

	return v;
}
vec8u16_t Vec8u16_Vec(uint16_t x0, uint16_t x1, uint16_t x2, uint16_t x3, uint16_t x4, uint16_t x5, uint16_t x6, uint16_t x7)
{
	vec8u16_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;
	v.v[5] = x5;
	v.v[6] = x6;
	v.v[7] = x7;

	return v;
}
vec8u16_t Vec8u16_Add(vec8u16_t v0, vec8u16_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];
	v0.v[5] += v1.v[5];
	v0.v[6] += v1.v[6];
	v0.v[7] += v1.v[7];

	return v0;
}
vec8u16_t Vec8u16_Sub(vec8u16_t v0, vec8u16_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];
	v0.v[5] -= v1.v[5];
	v0.v[6] -= v1.v[6];
	v0.v[7] -= v1.v[7];

	return v0;
}
uint16_t Vec8u16_GetComponent(vec8u16_t v, int index)
{
	return v.v[index];
}
vec8u16_t Vec8u16_Mul(vec8u16_t v0, vec8u16_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];
	v0.v[5] *= v1.v[5];
	v0.v[6] *= v1.v[6];
	v0.v[7] *= v1.v[7];

	return v0;
}
vec8u16_t Vec8u16_Div(vec8u16_t v0, vec8u16_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];
	v0.v[5] /= v1.v[5];
	v0.v[6] /= v1.v[6];
	v0.v[7] /= v1.v[7];

	return v0;
}
vec8u16_t Vec8u16_Scale(vec8u16_t v, uint16_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;
	v.v[5] *= scale;
	v.v[6] *= scale;
	v.v[7] *= scale;

	return v;
}
vec8u16_t Vec8u16_DivScale(vec8u16_t v, uint16_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;
	v.v[5] /= divscale;
	v.v[6] /= divscale;
	v.v[7] /= divscale;

	return v;
}
vec8u16_t Vec8u16_MA(vec8u16_t v, vec8u16_t dir, uint16_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;
	v.v[5] += dir.v[5] * scale;
	v.v[6] += dir.v[6] * scale;
	v.v[7] += dir.v[7] * scale;

	return v;
}
vec8u16_t Vec8u16_DA(vec8u16_t v, vec8u16_t dir, uint16_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;
	v.v[5] += dir.v[5] / divscale;
	v.v[6] += dir.v[6] / divscale;
	v.v[7] += dir.v[7] / divscale;

	return v;
}
uint16_t Vec8u16_Dot(vec8u16_t v0, vec8u16_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4] + v0.v[5] * v1.v[5] + v0.v[6] * v1.v[6] + v0.v[7] * v1.v[7];
}
uint16_t Vec8u16_LenSq(vec8u16_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4] + v.v[5] * v.v[5] + v.v[6] * v.v[6] + v.v[7] * v.v[7];
}
uint16_t Vec8u16_Len(vec8u16_t v)
{
	return sqrtf(Vec8u16_LenSq(v));
}
vec8u16_t Vec8u16_Mod(vec8u16_t v0, vec8u16_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);
	v0.v[4] = (v0.v[4] % v1.v[4]);
	v0.v[5] = (v0.v[5] % v1.v[5]);
	v0.v[6] = (v0.v[6] % v1.v[6]);
	v0.v[7] = (v0.v[7] % v1.v[7]);

	return v0;
}
vec8u16_t Vec8u16_ModS(vec8u16_t v0, uint16_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);
	v0.v[4] = (v0.v[4] % x);
	v0.v[5] = (v0.v[5] % x);
	v0.v[6] = (v0.v[6] % x);
	v0.v[7] = (v0.v[7] % x);

	return v0;
}
vec8u16_t Vec8u16_Min(vec8u16_t v0, vec8u16_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] < v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] < v1.v[6] ? v0.v[6] : v1.v[6];
	v0.v[7] = v0.v[7] < v1.v[7] ? v0.v[7] : v1.v[7];

	return v0;
}
vec8u16_t Vec8u16_Max(vec8u16_t v0, vec8u16_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] > v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] > v1.v[6] ? v0.v[6] : v1.v[6];
	v0.v[7] = v0.v[7] > v1.v[7] ? v0.v[7] : v1.v[7];

	return v0;
}
vec8u16_t Vec8u16_MinS(vec8u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] < x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] < x ? v0.v[6] : x;
	v0.v[7] = v0.v[7] < x ? v0.v[7] : x;

	return v0;
}
vec8u16_t Vec8u16_MaxS(vec8u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] > x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] > x ? v0.v[6] : x;
	v0.v[7] = v0.v[7] > x ? v0.v[7] : x;

	return v0;
}
vec8u16_t Vec8u16_Clamp(vec8u16_t v, vec8u16_t min, vec8u16_t max)
{
	return Vec8u16_Max(Vec8u16_Min(v, max), min);
}
vec8u16_t Vec8u16_ClampS(vec8u16_t v, uint16_t min, uint16_t max)
{
	return Vec8u16_MaxS(Vec8u16_MinS(v, max), min);
}
vec8u16_t Vec8u16_CmpLT(vec8u16_t v0, vec8u16_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] < v1.v[5] ? G_U16_ONE : G_U16_ZERO;
	v0.v[6] = v0.v[6] < v1.v[6] ? G_U16_ONE : G_U16_ZERO;
	v0.v[7] = v0.v[7] < v1.v[7] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec8u16_t Vec8u16_CmpLE(vec8u16_t v0, vec8u16_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] <= v1.v[5] ? G_U16_ONE : G_U16_ZERO;
	v0.v[6] = v0.v[6] <= v1.v[6] ? G_U16_ONE : G_U16_ZERO;
	v0.v[7] = v0.v[7] <= v1.v[7] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec8u16_t Vec8u16_CmpEQ(vec8u16_t v0, vec8u16_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] == v1.v[5] ? G_U16_ONE : G_U16_ZERO;
	v0.v[6] = v0.v[6] == v1.v[6] ? G_U16_ONE : G_U16_ZERO;
	v0.v[7] = v0.v[7] == v1.v[7] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec8u16_t Vec8u16_CmpGT(vec8u16_t v0, vec8u16_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] > v1.v[5] ? G_U16_ONE : G_U16_ZERO;
	v0.v[6] = v0.v[6] > v1.v[6] ? G_U16_ONE : G_U16_ZERO;
	v0.v[7] = v0.v[7] > v1.v[7] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec8u16_t Vec8u16_CmpGE(vec8u16_t v0, vec8u16_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] >= v1.v[5] ? G_U16_ONE : G_U16_ZERO;
	v0.v[6] = v0.v[6] >= v1.v[6] ? G_U16_ONE : G_U16_ZERO;
	v0.v[7] = v0.v[7] >= v1.v[7] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec8u16_t Vec8u16_CmpNE(vec8u16_t v0, vec8u16_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] != v1.v[5] ? G_U16_ONE : G_U16_ZERO;
	v0.v[6] = v0.v[6] != v1.v[6] ? G_U16_ONE : G_U16_ZERO;
	v0.v[7] = v0.v[7] != v1.v[7] ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec8u16_t Vec8u16_CmpLTS(vec8u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] < x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] < x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] < x ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] < x ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] < x ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] < x ? G_U16_ONE : G_U16_ZERO;
	v0.v[6] = v0.v[6] < x ? G_U16_ONE : G_U16_ZERO;
	v0.v[7] = v0.v[7] < x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec8u16_t Vec8u16_CmpLES(vec8u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] <= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[6] = v0.v[6] <= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[7] = v0.v[7] <= x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec8u16_t Vec8u16_CmpEQS(vec8u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] == x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] == x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] == x ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] == x ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] == x ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] == x ? G_U16_ONE : G_U16_ZERO;
	v0.v[6] = v0.v[6] == x ? G_U16_ONE : G_U16_ZERO;
	v0.v[7] = v0.v[7] == x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec8u16_t Vec8u16_CmpGTS(vec8u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] > x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] > x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] > x ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] > x ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] > x ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] > x ? G_U16_ONE : G_U16_ZERO;
	v0.v[6] = v0.v[6] > x ? G_U16_ONE : G_U16_ZERO;
	v0.v[7] = v0.v[7] > x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec8u16_t Vec8u16_CmpGES(vec8u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] >= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[6] = v0.v[6] >= x ? G_U16_ONE : G_U16_ZERO;
	v0.v[7] = v0.v[7] >= x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec8u16_t Vec8u16_CmpNES(vec8u16_t v0, uint16_t x)
{
	v0.v[0] = v0.v[0] != x ? G_U16_ONE : G_U16_ZERO;
	v0.v[1] = v0.v[1] != x ? G_U16_ONE : G_U16_ZERO;
	v0.v[2] = v0.v[2] != x ? G_U16_ONE : G_U16_ZERO;
	v0.v[3] = v0.v[3] != x ? G_U16_ONE : G_U16_ZERO;
	v0.v[4] = v0.v[4] != x ? G_U16_ONE : G_U16_ZERO;
	v0.v[5] = v0.v[5] != x ? G_U16_ONE : G_U16_ZERO;
	v0.v[6] = v0.v[6] != x ? G_U16_ONE : G_U16_ZERO;
	v0.v[7] = v0.v[7] != x ? G_U16_ONE : G_U16_ZERO;

	return v0;
}
vec8u16_t Vec8u16_Sign(vec8u16_t v)
{
	v.v[0] = v.v[0] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;
	v.v[1] = v.v[1] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;
	v.v[2] = v.v[2] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;
	v.v[3] = v.v[3] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;
	v.v[4] = v.v[4] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;
	v.v[5] = v.v[5] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;
	v.v[6] = v.v[6] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;
	v.v[7] = v.v[7] < G_U16_ZERO ? G_U16_ONE : G_U16_ZERO;

	return v;
}
vec8u16_t Vec8u16_SignPosNeg(vec8u16_t v)
{
	v.v[0] = v.v[0] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;
	v.v[1] = v.v[1] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;
	v.v[2] = v.v[2] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;
	v.v[3] = v.v[3] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;
	v.v[4] = v.v[4] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;
	v.v[5] = v.v[5] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;
	v.v[6] = v.v[6] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;
	v.v[7] = v.v[7] < G_U16_ZERO ? G_U16_NEG_ONE : G_U16_ONE;

	return v;
}
vec8u16_t Vec8u16_Zero()
{
	return G_VEC8U16_T_ZERO;
}
vec8u16_t Vec8u16_One()
{
	return G_VEC8U16_T_ONE;
}
vec8u16_t Vec8u16_Cross(vec8u16_t v0, vec8u16_t v1, vec8u16_t v2, vec8u16_t v3, vec8u16_t v4, vec8u16_t v5, vec8u16_t v6)
{
	vec8u16_t v;
	mat8x8u16_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;
	mat.v[5] = v4;
	mat.v[6] = v5;
	mat.v[7] = v6;

	for (i = 0; i < 8; i++)
		v.v[i] = Mat7x7u16_Det(Mat8x8u16_DeleteRowColumn(mat, 0, i));

	return v;
}
vec8i16_t Vec8i16_SetComponent(vec8i16_t v, int index, int16_t value)
{
	v.v[index] = value;

	return v;
}
vec8i16_t Vec8i16_Vec(int16_t x0, int16_t x1, int16_t x2, int16_t x3, int16_t x4, int16_t x5, int16_t x6, int16_t x7)
{
	vec8i16_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;
	v.v[5] = x5;
	v.v[6] = x6;
	v.v[7] = x7;

	return v;
}
vec8i16_t Vec8i16_Add(vec8i16_t v0, vec8i16_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];
	v0.v[5] += v1.v[5];
	v0.v[6] += v1.v[6];
	v0.v[7] += v1.v[7];

	return v0;
}
vec8i16_t Vec8i16_Sub(vec8i16_t v0, vec8i16_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];
	v0.v[5] -= v1.v[5];
	v0.v[6] -= v1.v[6];
	v0.v[7] -= v1.v[7];

	return v0;
}
int16_t Vec8i16_GetComponent(vec8i16_t v, int index)
{
	return v.v[index];
}
vec8i16_t Vec8i16_Mul(vec8i16_t v0, vec8i16_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];
	v0.v[5] *= v1.v[5];
	v0.v[6] *= v1.v[6];
	v0.v[7] *= v1.v[7];

	return v0;
}
vec8i16_t Vec8i16_Div(vec8i16_t v0, vec8i16_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];
	v0.v[5] /= v1.v[5];
	v0.v[6] /= v1.v[6];
	v0.v[7] /= v1.v[7];

	return v0;
}
vec8i16_t Vec8i16_Scale(vec8i16_t v, int16_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;
	v.v[5] *= scale;
	v.v[6] *= scale;
	v.v[7] *= scale;

	return v;
}
vec8i16_t Vec8i16_DivScale(vec8i16_t v, int16_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;
	v.v[5] /= divscale;
	v.v[6] /= divscale;
	v.v[7] /= divscale;

	return v;
}
vec8i16_t Vec8i16_MA(vec8i16_t v, vec8i16_t dir, int16_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;
	v.v[5] += dir.v[5] * scale;
	v.v[6] += dir.v[6] * scale;
	v.v[7] += dir.v[7] * scale;

	return v;
}
vec8i16_t Vec8i16_DA(vec8i16_t v, vec8i16_t dir, int16_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;
	v.v[5] += dir.v[5] / divscale;
	v.v[6] += dir.v[6] / divscale;
	v.v[7] += dir.v[7] / divscale;

	return v;
}
int16_t Vec8i16_Dot(vec8i16_t v0, vec8i16_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4] + v0.v[5] * v1.v[5] + v0.v[6] * v1.v[6] + v0.v[7] * v1.v[7];
}
int16_t Vec8i16_LenSq(vec8i16_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4] + v.v[5] * v.v[5] + v.v[6] * v.v[6] + v.v[7] * v.v[7];
}
int16_t Vec8i16_Len(vec8i16_t v)
{
	return sqrtf(Vec8i16_LenSq(v));
}
vec8i16_t Vec8i16_Abs(vec8i16_t v)
{
	v.v[0] = (v.v[0] < 0 ? -v.v[0] : v.v[0]);
	v.v[1] = (v.v[1] < 0 ? -v.v[1] : v.v[1]);
	v.v[2] = (v.v[2] < 0 ? -v.v[2] : v.v[2]);
	v.v[3] = (v.v[3] < 0 ? -v.v[3] : v.v[3]);
	v.v[4] = (v.v[4] < 0 ? -v.v[4] : v.v[4]);
	v.v[5] = (v.v[5] < 0 ? -v.v[5] : v.v[5]);
	v.v[6] = (v.v[6] < 0 ? -v.v[6] : v.v[6]);
	v.v[7] = (v.v[7] < 0 ? -v.v[7] : v.v[7]);

	return v;
}
vec8i16_t Vec8i16_Mod(vec8i16_t v0, vec8i16_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);
	v0.v[4] = (v0.v[4] % v1.v[4]);
	v0.v[5] = (v0.v[5] % v1.v[5]);
	v0.v[6] = (v0.v[6] % v1.v[6]);
	v0.v[7] = (v0.v[7] % v1.v[7]);

	return v0;
}
vec8i16_t Vec8i16_ModS(vec8i16_t v0, int16_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);
	v0.v[4] = (v0.v[4] % x);
	v0.v[5] = (v0.v[5] % x);
	v0.v[6] = (v0.v[6] % x);
	v0.v[7] = (v0.v[7] % x);

	return v0;
}
vec8i16_t Vec8i16_Min(vec8i16_t v0, vec8i16_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] < v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] < v1.v[6] ? v0.v[6] : v1.v[6];
	v0.v[7] = v0.v[7] < v1.v[7] ? v0.v[7] : v1.v[7];

	return v0;
}
vec8i16_t Vec8i16_Max(vec8i16_t v0, vec8i16_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] > v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] > v1.v[6] ? v0.v[6] : v1.v[6];
	v0.v[7] = v0.v[7] > v1.v[7] ? v0.v[7] : v1.v[7];

	return v0;
}
vec8i16_t Vec8i16_MinS(vec8i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] < x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] < x ? v0.v[6] : x;
	v0.v[7] = v0.v[7] < x ? v0.v[7] : x;

	return v0;
}
vec8i16_t Vec8i16_MaxS(vec8i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] > x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] > x ? v0.v[6] : x;
	v0.v[7] = v0.v[7] > x ? v0.v[7] : x;

	return v0;
}
vec8i16_t Vec8i16_Clamp(vec8i16_t v, vec8i16_t min, vec8i16_t max)
{
	return Vec8i16_Max(Vec8i16_Min(v, max), min);
}
vec8i16_t Vec8i16_ClampS(vec8i16_t v, int16_t min, int16_t max)
{
	return Vec8i16_MaxS(Vec8i16_MinS(v, max), min);
}
vec8i16_t Vec8i16_Neg(vec8i16_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];
	v.v[3] = -v.v[3];
	v.v[4] = -v.v[4];
	v.v[5] = -v.v[5];
	v.v[6] = -v.v[6];
	v.v[7] = -v.v[7];

	return v;
}
vec8i16_t Vec8i16_CmpLT(vec8i16_t v0, vec8i16_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] < v1.v[5] ? G_I16_ONE : G_I16_ZERO;
	v0.v[6] = v0.v[6] < v1.v[6] ? G_I16_ONE : G_I16_ZERO;
	v0.v[7] = v0.v[7] < v1.v[7] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec8i16_t Vec8i16_CmpLE(vec8i16_t v0, vec8i16_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] <= v1.v[5] ? G_I16_ONE : G_I16_ZERO;
	v0.v[6] = v0.v[6] <= v1.v[6] ? G_I16_ONE : G_I16_ZERO;
	v0.v[7] = v0.v[7] <= v1.v[7] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec8i16_t Vec8i16_CmpEQ(vec8i16_t v0, vec8i16_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] == v1.v[5] ? G_I16_ONE : G_I16_ZERO;
	v0.v[6] = v0.v[6] == v1.v[6] ? G_I16_ONE : G_I16_ZERO;
	v0.v[7] = v0.v[7] == v1.v[7] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec8i16_t Vec8i16_CmpGT(vec8i16_t v0, vec8i16_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] > v1.v[5] ? G_I16_ONE : G_I16_ZERO;
	v0.v[6] = v0.v[6] > v1.v[6] ? G_I16_ONE : G_I16_ZERO;
	v0.v[7] = v0.v[7] > v1.v[7] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec8i16_t Vec8i16_CmpGE(vec8i16_t v0, vec8i16_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] >= v1.v[5] ? G_I16_ONE : G_I16_ZERO;
	v0.v[6] = v0.v[6] >= v1.v[6] ? G_I16_ONE : G_I16_ZERO;
	v0.v[7] = v0.v[7] >= v1.v[7] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec8i16_t Vec8i16_CmpNE(vec8i16_t v0, vec8i16_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] != v1.v[5] ? G_I16_ONE : G_I16_ZERO;
	v0.v[6] = v0.v[6] != v1.v[6] ? G_I16_ONE : G_I16_ZERO;
	v0.v[7] = v0.v[7] != v1.v[7] ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec8i16_t Vec8i16_CmpLTS(vec8i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] < x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] < x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] < x ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] < x ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] < x ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] < x ? G_I16_ONE : G_I16_ZERO;
	v0.v[6] = v0.v[6] < x ? G_I16_ONE : G_I16_ZERO;
	v0.v[7] = v0.v[7] < x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec8i16_t Vec8i16_CmpLES(vec8i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] <= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[6] = v0.v[6] <= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[7] = v0.v[7] <= x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec8i16_t Vec8i16_CmpEQS(vec8i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] == x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] == x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] == x ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] == x ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] == x ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] == x ? G_I16_ONE : G_I16_ZERO;
	v0.v[6] = v0.v[6] == x ? G_I16_ONE : G_I16_ZERO;
	v0.v[7] = v0.v[7] == x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec8i16_t Vec8i16_CmpGTS(vec8i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] > x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] > x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] > x ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] > x ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] > x ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] > x ? G_I16_ONE : G_I16_ZERO;
	v0.v[6] = v0.v[6] > x ? G_I16_ONE : G_I16_ZERO;
	v0.v[7] = v0.v[7] > x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec8i16_t Vec8i16_CmpGES(vec8i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] >= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[6] = v0.v[6] >= x ? G_I16_ONE : G_I16_ZERO;
	v0.v[7] = v0.v[7] >= x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec8i16_t Vec8i16_CmpNES(vec8i16_t v0, int16_t x)
{
	v0.v[0] = v0.v[0] != x ? G_I16_ONE : G_I16_ZERO;
	v0.v[1] = v0.v[1] != x ? G_I16_ONE : G_I16_ZERO;
	v0.v[2] = v0.v[2] != x ? G_I16_ONE : G_I16_ZERO;
	v0.v[3] = v0.v[3] != x ? G_I16_ONE : G_I16_ZERO;
	v0.v[4] = v0.v[4] != x ? G_I16_ONE : G_I16_ZERO;
	v0.v[5] = v0.v[5] != x ? G_I16_ONE : G_I16_ZERO;
	v0.v[6] = v0.v[6] != x ? G_I16_ONE : G_I16_ZERO;
	v0.v[7] = v0.v[7] != x ? G_I16_ONE : G_I16_ZERO;

	return v0;
}
vec8i16_t Vec8i16_Sign(vec8i16_t v)
{
	v.v[0] = v.v[0] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;
	v.v[1] = v.v[1] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;
	v.v[2] = v.v[2] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;
	v.v[3] = v.v[3] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;
	v.v[4] = v.v[4] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;
	v.v[5] = v.v[5] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;
	v.v[6] = v.v[6] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;
	v.v[7] = v.v[7] < G_I16_ZERO ? G_I16_ONE : G_I16_ZERO;

	return v;
}
vec8i16_t Vec8i16_SignPosNeg(vec8i16_t v)
{
	v.v[0] = v.v[0] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;
	v.v[1] = v.v[1] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;
	v.v[2] = v.v[2] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;
	v.v[3] = v.v[3] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;
	v.v[4] = v.v[4] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;
	v.v[5] = v.v[5] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;
	v.v[6] = v.v[6] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;
	v.v[7] = v.v[7] < G_I16_ZERO ? G_I16_NEG_ONE : G_I16_ONE;

	return v;
}
vec8i16_t Vec8i16_Zero()
{
	return G_VEC8I16_T_ZERO;
}
vec8i16_t Vec8i16_One()
{
	return G_VEC8I16_T_ONE;
}
vec8i16_t Vec8i16_NegOne()
{
	return Vec8i16_Neg(G_VEC8I16_T_ONE);
}
vec8i16_t Vec8i16_Cross(vec8i16_t v0, vec8i16_t v1, vec8i16_t v2, vec8i16_t v3, vec8i16_t v4, vec8i16_t v5, vec8i16_t v6)
{
	vec8i16_t v;
	mat8x8i16_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;
	mat.v[5] = v4;
	mat.v[6] = v5;
	mat.v[7] = v6;

	for (i = 0; i < 8; i++)
		v.v[i] = Mat7x7i16_Det(Mat8x8i16_DeleteRowColumn(mat, 0, i));

	return v;
}
vec8u8_t Vec8u8_SetComponent(vec8u8_t v, int index, uint8_t value)
{
	v.v[index] = value;

	return v;
}
vec8u8_t Vec8u8_Vec(uint8_t x0, uint8_t x1, uint8_t x2, uint8_t x3, uint8_t x4, uint8_t x5, uint8_t x6, uint8_t x7)
{
	vec8u8_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;
	v.v[5] = x5;
	v.v[6] = x6;
	v.v[7] = x7;

	return v;
}
vec8u8_t Vec8u8_Add(vec8u8_t v0, vec8u8_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];
	v0.v[5] += v1.v[5];
	v0.v[6] += v1.v[6];
	v0.v[7] += v1.v[7];

	return v0;
}
vec8u8_t Vec8u8_Sub(vec8u8_t v0, vec8u8_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];
	v0.v[5] -= v1.v[5];
	v0.v[6] -= v1.v[6];
	v0.v[7] -= v1.v[7];

	return v0;
}
uint8_t Vec8u8_GetComponent(vec8u8_t v, int index)
{
	return v.v[index];
}
vec8u8_t Vec8u8_Mul(vec8u8_t v0, vec8u8_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];
	v0.v[5] *= v1.v[5];
	v0.v[6] *= v1.v[6];
	v0.v[7] *= v1.v[7];

	return v0;
}
vec8u8_t Vec8u8_Div(vec8u8_t v0, vec8u8_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];
	v0.v[5] /= v1.v[5];
	v0.v[6] /= v1.v[6];
	v0.v[7] /= v1.v[7];

	return v0;
}
vec8u8_t Vec8u8_Scale(vec8u8_t v, uint8_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;
	v.v[5] *= scale;
	v.v[6] *= scale;
	v.v[7] *= scale;

	return v;
}
vec8u8_t Vec8u8_DivScale(vec8u8_t v, uint8_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;
	v.v[5] /= divscale;
	v.v[6] /= divscale;
	v.v[7] /= divscale;

	return v;
}
vec8u8_t Vec8u8_MA(vec8u8_t v, vec8u8_t dir, uint8_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;
	v.v[5] += dir.v[5] * scale;
	v.v[6] += dir.v[6] * scale;
	v.v[7] += dir.v[7] * scale;

	return v;
}
vec8u8_t Vec8u8_DA(vec8u8_t v, vec8u8_t dir, uint8_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;
	v.v[5] += dir.v[5] / divscale;
	v.v[6] += dir.v[6] / divscale;
	v.v[7] += dir.v[7] / divscale;

	return v;
}
uint8_t Vec8u8_Dot(vec8u8_t v0, vec8u8_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4] + v0.v[5] * v1.v[5] + v0.v[6] * v1.v[6] + v0.v[7] * v1.v[7];
}
uint8_t Vec8u8_LenSq(vec8u8_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4] + v.v[5] * v.v[5] + v.v[6] * v.v[6] + v.v[7] * v.v[7];
}
uint8_t Vec8u8_Len(vec8u8_t v)
{
	return sqrtf(Vec8u8_LenSq(v));
}
vec8u8_t Vec8u8_Mod(vec8u8_t v0, vec8u8_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);
	v0.v[4] = (v0.v[4] % v1.v[4]);
	v0.v[5] = (v0.v[5] % v1.v[5]);
	v0.v[6] = (v0.v[6] % v1.v[6]);
	v0.v[7] = (v0.v[7] % v1.v[7]);

	return v0;
}
vec8u8_t Vec8u8_ModS(vec8u8_t v0, uint8_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);
	v0.v[4] = (v0.v[4] % x);
	v0.v[5] = (v0.v[5] % x);
	v0.v[6] = (v0.v[6] % x);
	v0.v[7] = (v0.v[7] % x);

	return v0;
}
vec8u8_t Vec8u8_Min(vec8u8_t v0, vec8u8_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] < v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] < v1.v[6] ? v0.v[6] : v1.v[6];
	v0.v[7] = v0.v[7] < v1.v[7] ? v0.v[7] : v1.v[7];

	return v0;
}
vec8u8_t Vec8u8_Max(vec8u8_t v0, vec8u8_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] > v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] > v1.v[6] ? v0.v[6] : v1.v[6];
	v0.v[7] = v0.v[7] > v1.v[7] ? v0.v[7] : v1.v[7];

	return v0;
}
vec8u8_t Vec8u8_MinS(vec8u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] < x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] < x ? v0.v[6] : x;
	v0.v[7] = v0.v[7] < x ? v0.v[7] : x;

	return v0;
}
vec8u8_t Vec8u8_MaxS(vec8u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] > x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] > x ? v0.v[6] : x;
	v0.v[7] = v0.v[7] > x ? v0.v[7] : x;

	return v0;
}
vec8u8_t Vec8u8_Clamp(vec8u8_t v, vec8u8_t min, vec8u8_t max)
{
	return Vec8u8_Max(Vec8u8_Min(v, max), min);
}
vec8u8_t Vec8u8_ClampS(vec8u8_t v, uint8_t min, uint8_t max)
{
	return Vec8u8_MaxS(Vec8u8_MinS(v, max), min);
}
vec8u8_t Vec8u8_CmpLT(vec8u8_t v0, vec8u8_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] < v1.v[5] ? G_U8_ONE : G_U8_ZERO;
	v0.v[6] = v0.v[6] < v1.v[6] ? G_U8_ONE : G_U8_ZERO;
	v0.v[7] = v0.v[7] < v1.v[7] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec8u8_t Vec8u8_CmpLE(vec8u8_t v0, vec8u8_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] <= v1.v[5] ? G_U8_ONE : G_U8_ZERO;
	v0.v[6] = v0.v[6] <= v1.v[6] ? G_U8_ONE : G_U8_ZERO;
	v0.v[7] = v0.v[7] <= v1.v[7] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec8u8_t Vec8u8_CmpEQ(vec8u8_t v0, vec8u8_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] == v1.v[5] ? G_U8_ONE : G_U8_ZERO;
	v0.v[6] = v0.v[6] == v1.v[6] ? G_U8_ONE : G_U8_ZERO;
	v0.v[7] = v0.v[7] == v1.v[7] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec8u8_t Vec8u8_CmpGT(vec8u8_t v0, vec8u8_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] > v1.v[5] ? G_U8_ONE : G_U8_ZERO;
	v0.v[6] = v0.v[6] > v1.v[6] ? G_U8_ONE : G_U8_ZERO;
	v0.v[7] = v0.v[7] > v1.v[7] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec8u8_t Vec8u8_CmpGE(vec8u8_t v0, vec8u8_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] >= v1.v[5] ? G_U8_ONE : G_U8_ZERO;
	v0.v[6] = v0.v[6] >= v1.v[6] ? G_U8_ONE : G_U8_ZERO;
	v0.v[7] = v0.v[7] >= v1.v[7] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec8u8_t Vec8u8_CmpNE(vec8u8_t v0, vec8u8_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] != v1.v[5] ? G_U8_ONE : G_U8_ZERO;
	v0.v[6] = v0.v[6] != v1.v[6] ? G_U8_ONE : G_U8_ZERO;
	v0.v[7] = v0.v[7] != v1.v[7] ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec8u8_t Vec8u8_CmpLTS(vec8u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] < x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] < x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] < x ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] < x ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] < x ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] < x ? G_U8_ONE : G_U8_ZERO;
	v0.v[6] = v0.v[6] < x ? G_U8_ONE : G_U8_ZERO;
	v0.v[7] = v0.v[7] < x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec8u8_t Vec8u8_CmpLES(vec8u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] <= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[6] = v0.v[6] <= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[7] = v0.v[7] <= x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec8u8_t Vec8u8_CmpEQS(vec8u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] == x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] == x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] == x ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] == x ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] == x ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] == x ? G_U8_ONE : G_U8_ZERO;
	v0.v[6] = v0.v[6] == x ? G_U8_ONE : G_U8_ZERO;
	v0.v[7] = v0.v[7] == x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec8u8_t Vec8u8_CmpGTS(vec8u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] > x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] > x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] > x ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] > x ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] > x ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] > x ? G_U8_ONE : G_U8_ZERO;
	v0.v[6] = v0.v[6] > x ? G_U8_ONE : G_U8_ZERO;
	v0.v[7] = v0.v[7] > x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec8u8_t Vec8u8_CmpGES(vec8u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] >= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[6] = v0.v[6] >= x ? G_U8_ONE : G_U8_ZERO;
	v0.v[7] = v0.v[7] >= x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec8u8_t Vec8u8_CmpNES(vec8u8_t v0, uint8_t x)
{
	v0.v[0] = v0.v[0] != x ? G_U8_ONE : G_U8_ZERO;
	v0.v[1] = v0.v[1] != x ? G_U8_ONE : G_U8_ZERO;
	v0.v[2] = v0.v[2] != x ? G_U8_ONE : G_U8_ZERO;
	v0.v[3] = v0.v[3] != x ? G_U8_ONE : G_U8_ZERO;
	v0.v[4] = v0.v[4] != x ? G_U8_ONE : G_U8_ZERO;
	v0.v[5] = v0.v[5] != x ? G_U8_ONE : G_U8_ZERO;
	v0.v[6] = v0.v[6] != x ? G_U8_ONE : G_U8_ZERO;
	v0.v[7] = v0.v[7] != x ? G_U8_ONE : G_U8_ZERO;

	return v0;
}
vec8u8_t Vec8u8_Sign(vec8u8_t v)
{
	v.v[0] = v.v[0] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;
	v.v[1] = v.v[1] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;
	v.v[2] = v.v[2] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;
	v.v[3] = v.v[3] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;
	v.v[4] = v.v[4] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;
	v.v[5] = v.v[5] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;
	v.v[6] = v.v[6] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;
	v.v[7] = v.v[7] < G_U8_ZERO ? G_U8_ONE : G_U8_ZERO;

	return v;
}
vec8u8_t Vec8u8_SignPosNeg(vec8u8_t v)
{
	v.v[0] = v.v[0] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;
	v.v[1] = v.v[1] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;
	v.v[2] = v.v[2] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;
	v.v[3] = v.v[3] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;
	v.v[4] = v.v[4] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;
	v.v[5] = v.v[5] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;
	v.v[6] = v.v[6] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;
	v.v[7] = v.v[7] < G_U8_ZERO ? G_U8_NEG_ONE : G_U8_ONE;

	return v;
}
vec8u8_t Vec8u8_Zero()
{
	return G_VEC8U8_T_ZERO;
}
vec8u8_t Vec8u8_One()
{
	return G_VEC8U8_T_ONE;
}
vec8u8_t Vec8u8_Cross(vec8u8_t v0, vec8u8_t v1, vec8u8_t v2, vec8u8_t v3, vec8u8_t v4, vec8u8_t v5, vec8u8_t v6)
{
	vec8u8_t v;
	mat8x8u8_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;
	mat.v[5] = v4;
	mat.v[6] = v5;
	mat.v[7] = v6;

	for (i = 0; i < 8; i++)
		v.v[i] = Mat7x7u8_Det(Mat8x8u8_DeleteRowColumn(mat, 0, i));

	return v;
}
vec8i8_t Vec8i8_SetComponent(vec8i8_t v, int index, int8_t value)
{
	v.v[index] = value;

	return v;
}
vec8i8_t Vec8i8_Vec(int8_t x0, int8_t x1, int8_t x2, int8_t x3, int8_t x4, int8_t x5, int8_t x6, int8_t x7)
{
	vec8i8_t v;

	v.v[0] = x0;
	v.v[1] = x1;
	v.v[2] = x2;
	v.v[3] = x3;
	v.v[4] = x4;
	v.v[5] = x5;
	v.v[6] = x6;
	v.v[7] = x7;

	return v;
}
vec8i8_t Vec8i8_Add(vec8i8_t v0, vec8i8_t v1)
{
	v0.v[0] += v1.v[0];
	v0.v[1] += v1.v[1];
	v0.v[2] += v1.v[2];
	v0.v[3] += v1.v[3];
	v0.v[4] += v1.v[4];
	v0.v[5] += v1.v[5];
	v0.v[6] += v1.v[6];
	v0.v[7] += v1.v[7];

	return v0;
}
vec8i8_t Vec8i8_Sub(vec8i8_t v0, vec8i8_t v1)
{
	v0.v[0] -= v1.v[0];
	v0.v[1] -= v1.v[1];
	v0.v[2] -= v1.v[2];
	v0.v[3] -= v1.v[3];
	v0.v[4] -= v1.v[4];
	v0.v[5] -= v1.v[5];
	v0.v[6] -= v1.v[6];
	v0.v[7] -= v1.v[7];

	return v0;
}
int8_t Vec8i8_GetComponent(vec8i8_t v, int index)
{
	return v.v[index];
}
vec8i8_t Vec8i8_Mul(vec8i8_t v0, vec8i8_t v1)
{
	v0.v[0] *= v1.v[0];
	v0.v[1] *= v1.v[1];
	v0.v[2] *= v1.v[2];
	v0.v[3] *= v1.v[3];
	v0.v[4] *= v1.v[4];
	v0.v[5] *= v1.v[5];
	v0.v[6] *= v1.v[6];
	v0.v[7] *= v1.v[7];

	return v0;
}
vec8i8_t Vec8i8_Div(vec8i8_t v0, vec8i8_t v1)
{
	v0.v[0] /= v1.v[0];
	v0.v[1] /= v1.v[1];
	v0.v[2] /= v1.v[2];
	v0.v[3] /= v1.v[3];
	v0.v[4] /= v1.v[4];
	v0.v[5] /= v1.v[5];
	v0.v[6] /= v1.v[6];
	v0.v[7] /= v1.v[7];

	return v0;
}
vec8i8_t Vec8i8_Scale(vec8i8_t v, int8_t scale)
{
	v.v[0] *= scale;
	v.v[1] *= scale;
	v.v[2] *= scale;
	v.v[3] *= scale;
	v.v[4] *= scale;
	v.v[5] *= scale;
	v.v[6] *= scale;
	v.v[7] *= scale;

	return v;
}
vec8i8_t Vec8i8_DivScale(vec8i8_t v, int8_t divscale)
{
	v.v[0] /= divscale;
	v.v[1] /= divscale;
	v.v[2] /= divscale;
	v.v[3] /= divscale;
	v.v[4] /= divscale;
	v.v[5] /= divscale;
	v.v[6] /= divscale;
	v.v[7] /= divscale;

	return v;
}
vec8i8_t Vec8i8_MA(vec8i8_t v, vec8i8_t dir, int8_t scale)
{
	v.v[0] += dir.v[0] * scale;
	v.v[1] += dir.v[1] * scale;
	v.v[2] += dir.v[2] * scale;
	v.v[3] += dir.v[3] * scale;
	v.v[4] += dir.v[4] * scale;
	v.v[5] += dir.v[5] * scale;
	v.v[6] += dir.v[6] * scale;
	v.v[7] += dir.v[7] * scale;

	return v;
}
vec8i8_t Vec8i8_DA(vec8i8_t v, vec8i8_t dir, int8_t divscale)
{
	v.v[0] += dir.v[0] / divscale;
	v.v[1] += dir.v[1] / divscale;
	v.v[2] += dir.v[2] / divscale;
	v.v[3] += dir.v[3] / divscale;
	v.v[4] += dir.v[4] / divscale;
	v.v[5] += dir.v[5] / divscale;
	v.v[6] += dir.v[6] / divscale;
	v.v[7] += dir.v[7] / divscale;

	return v;
}
int8_t Vec8i8_Dot(vec8i8_t v0, vec8i8_t v1)
{
	return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1] + v0.v[2] * v1.v[2] + v0.v[3] * v1.v[3] + v0.v[4] * v1.v[4] + v0.v[5] * v1.v[5] + v0.v[6] * v1.v[6] + v0.v[7] * v1.v[7];
}
int8_t Vec8i8_LenSq(vec8i8_t v)
{
	return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2] + v.v[3] * v.v[3] + v.v[4] * v.v[4] + v.v[5] * v.v[5] + v.v[6] * v.v[6] + v.v[7] * v.v[7];
}
int8_t Vec8i8_Len(vec8i8_t v)
{
	return sqrtf(Vec8i8_LenSq(v));
}
vec8i8_t Vec8i8_Abs(vec8i8_t v)
{
	v.v[0] = (v.v[0] < 0 ? -v.v[0] : v.v[0]);
	v.v[1] = (v.v[1] < 0 ? -v.v[1] : v.v[1]);
	v.v[2] = (v.v[2] < 0 ? -v.v[2] : v.v[2]);
	v.v[3] = (v.v[3] < 0 ? -v.v[3] : v.v[3]);
	v.v[4] = (v.v[4] < 0 ? -v.v[4] : v.v[4]);
	v.v[5] = (v.v[5] < 0 ? -v.v[5] : v.v[5]);
	v.v[6] = (v.v[6] < 0 ? -v.v[6] : v.v[6]);
	v.v[7] = (v.v[7] < 0 ? -v.v[7] : v.v[7]);

	return v;
}
vec8i8_t Vec8i8_Mod(vec8i8_t v0, vec8i8_t v1)
{
	v0.v[0] = (v0.v[0] % v1.v[0]);
	v0.v[1] = (v0.v[1] % v1.v[1]);
	v0.v[2] = (v0.v[2] % v1.v[2]);
	v0.v[3] = (v0.v[3] % v1.v[3]);
	v0.v[4] = (v0.v[4] % v1.v[4]);
	v0.v[5] = (v0.v[5] % v1.v[5]);
	v0.v[6] = (v0.v[6] % v1.v[6]);
	v0.v[7] = (v0.v[7] % v1.v[7]);

	return v0;
}
vec8i8_t Vec8i8_ModS(vec8i8_t v0, int8_t x)
{
	v0.v[0] = (v0.v[0] % x);
	v0.v[1] = (v0.v[1] % x);
	v0.v[2] = (v0.v[2] % x);
	v0.v[3] = (v0.v[3] % x);
	v0.v[4] = (v0.v[4] % x);
	v0.v[5] = (v0.v[5] % x);
	v0.v[6] = (v0.v[6] % x);
	v0.v[7] = (v0.v[7] % x);

	return v0;
}
vec8i8_t Vec8i8_Min(vec8i8_t v0, vec8i8_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] < v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] < v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] < v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] < v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] < v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] < v1.v[6] ? v0.v[6] : v1.v[6];
	v0.v[7] = v0.v[7] < v1.v[7] ? v0.v[7] : v1.v[7];

	return v0;
}
vec8i8_t Vec8i8_Max(vec8i8_t v0, vec8i8_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? v0.v[0] : v1.v[0];
	v0.v[1] = v0.v[1] > v1.v[1] ? v0.v[1] : v1.v[1];
	v0.v[2] = v0.v[2] > v1.v[2] ? v0.v[2] : v1.v[2];
	v0.v[3] = v0.v[3] > v1.v[3] ? v0.v[3] : v1.v[3];
	v0.v[4] = v0.v[4] > v1.v[4] ? v0.v[4] : v1.v[4];
	v0.v[5] = v0.v[5] > v1.v[5] ? v0.v[5] : v1.v[5];
	v0.v[6] = v0.v[6] > v1.v[6] ? v0.v[6] : v1.v[6];
	v0.v[7] = v0.v[7] > v1.v[7] ? v0.v[7] : v1.v[7];

	return v0;
}
vec8i8_t Vec8i8_MinS(vec8i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] < x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] < x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] < x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] < x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] < x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] < x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] < x ? v0.v[6] : x;
	v0.v[7] = v0.v[7] < x ? v0.v[7] : x;

	return v0;
}
vec8i8_t Vec8i8_MaxS(vec8i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] > x ? v0.v[0] : x;
	v0.v[1] = v0.v[1] > x ? v0.v[1] : x;
	v0.v[2] = v0.v[2] > x ? v0.v[2] : x;
	v0.v[3] = v0.v[3] > x ? v0.v[3] : x;
	v0.v[4] = v0.v[4] > x ? v0.v[4] : x;
	v0.v[5] = v0.v[5] > x ? v0.v[5] : x;
	v0.v[6] = v0.v[6] > x ? v0.v[6] : x;
	v0.v[7] = v0.v[7] > x ? v0.v[7] : x;

	return v0;
}
vec8i8_t Vec8i8_Clamp(vec8i8_t v, vec8i8_t min, vec8i8_t max)
{
	return Vec8i8_Max(Vec8i8_Min(v, max), min);
}
vec8i8_t Vec8i8_ClampS(vec8i8_t v, int8_t min, int8_t max)
{
	return Vec8i8_MaxS(Vec8i8_MinS(v, max), min);
}
vec8i8_t Vec8i8_Neg(vec8i8_t v)
{
	v.v[0] = -v.v[0];
	v.v[1] = -v.v[1];
	v.v[2] = -v.v[2];
	v.v[3] = -v.v[3];
	v.v[4] = -v.v[4];
	v.v[5] = -v.v[5];
	v.v[6] = -v.v[6];
	v.v[7] = -v.v[7];

	return v;
}
vec8i8_t Vec8i8_CmpLT(vec8i8_t v0, vec8i8_t v1)
{
	v0.v[0] = v0.v[0] < v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] < v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] < v1.v[2] ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] < v1.v[3] ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] < v1.v[4] ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] < v1.v[5] ? G_I8_ONE : G_I8_ZERO;
	v0.v[6] = v0.v[6] < v1.v[6] ? G_I8_ONE : G_I8_ZERO;
	v0.v[7] = v0.v[7] < v1.v[7] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec8i8_t Vec8i8_CmpLE(vec8i8_t v0, vec8i8_t v1)
{
	v0.v[0] = v0.v[0] <= v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] <= v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] <= v1.v[2] ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] <= v1.v[3] ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] <= v1.v[4] ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] <= v1.v[5] ? G_I8_ONE : G_I8_ZERO;
	v0.v[6] = v0.v[6] <= v1.v[6] ? G_I8_ONE : G_I8_ZERO;
	v0.v[7] = v0.v[7] <= v1.v[7] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec8i8_t Vec8i8_CmpEQ(vec8i8_t v0, vec8i8_t v1)
{
	v0.v[0] = v0.v[0] == v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] == v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] == v1.v[2] ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] == v1.v[3] ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] == v1.v[4] ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] == v1.v[5] ? G_I8_ONE : G_I8_ZERO;
	v0.v[6] = v0.v[6] == v1.v[6] ? G_I8_ONE : G_I8_ZERO;
	v0.v[7] = v0.v[7] == v1.v[7] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec8i8_t Vec8i8_CmpGT(vec8i8_t v0, vec8i8_t v1)
{
	v0.v[0] = v0.v[0] > v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] > v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] > v1.v[2] ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] > v1.v[3] ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] > v1.v[4] ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] > v1.v[5] ? G_I8_ONE : G_I8_ZERO;
	v0.v[6] = v0.v[6] > v1.v[6] ? G_I8_ONE : G_I8_ZERO;
	v0.v[7] = v0.v[7] > v1.v[7] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec8i8_t Vec8i8_CmpGE(vec8i8_t v0, vec8i8_t v1)
{
	v0.v[0] = v0.v[0] >= v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] >= v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] >= v1.v[2] ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] >= v1.v[3] ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] >= v1.v[4] ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] >= v1.v[5] ? G_I8_ONE : G_I8_ZERO;
	v0.v[6] = v0.v[6] >= v1.v[6] ? G_I8_ONE : G_I8_ZERO;
	v0.v[7] = v0.v[7] >= v1.v[7] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec8i8_t Vec8i8_CmpNE(vec8i8_t v0, vec8i8_t v1)
{
	v0.v[0] = v0.v[0] != v1.v[0] ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] != v1.v[1] ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] != v1.v[2] ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] != v1.v[3] ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] != v1.v[4] ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] != v1.v[5] ? G_I8_ONE : G_I8_ZERO;
	v0.v[6] = v0.v[6] != v1.v[6] ? G_I8_ONE : G_I8_ZERO;
	v0.v[7] = v0.v[7] != v1.v[7] ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec8i8_t Vec8i8_CmpLTS(vec8i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] < x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] < x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] < x ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] < x ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] < x ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] < x ? G_I8_ONE : G_I8_ZERO;
	v0.v[6] = v0.v[6] < x ? G_I8_ONE : G_I8_ZERO;
	v0.v[7] = v0.v[7] < x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec8i8_t Vec8i8_CmpLES(vec8i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] <= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] <= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] <= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] <= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] <= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] <= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[6] = v0.v[6] <= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[7] = v0.v[7] <= x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec8i8_t Vec8i8_CmpEQS(vec8i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] == x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] == x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] == x ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] == x ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] == x ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] == x ? G_I8_ONE : G_I8_ZERO;
	v0.v[6] = v0.v[6] == x ? G_I8_ONE : G_I8_ZERO;
	v0.v[7] = v0.v[7] == x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec8i8_t Vec8i8_CmpGTS(vec8i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] > x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] > x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] > x ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] > x ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] > x ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] > x ? G_I8_ONE : G_I8_ZERO;
	v0.v[6] = v0.v[6] > x ? G_I8_ONE : G_I8_ZERO;
	v0.v[7] = v0.v[7] > x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec8i8_t Vec8i8_CmpGES(vec8i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] >= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] >= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] >= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] >= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] >= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] >= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[6] = v0.v[6] >= x ? G_I8_ONE : G_I8_ZERO;
	v0.v[7] = v0.v[7] >= x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec8i8_t Vec8i8_CmpNES(vec8i8_t v0, int8_t x)
{
	v0.v[0] = v0.v[0] != x ? G_I8_ONE : G_I8_ZERO;
	v0.v[1] = v0.v[1] != x ? G_I8_ONE : G_I8_ZERO;
	v0.v[2] = v0.v[2] != x ? G_I8_ONE : G_I8_ZERO;
	v0.v[3] = v0.v[3] != x ? G_I8_ONE : G_I8_ZERO;
	v0.v[4] = v0.v[4] != x ? G_I8_ONE : G_I8_ZERO;
	v0.v[5] = v0.v[5] != x ? G_I8_ONE : G_I8_ZERO;
	v0.v[6] = v0.v[6] != x ? G_I8_ONE : G_I8_ZERO;
	v0.v[7] = v0.v[7] != x ? G_I8_ONE : G_I8_ZERO;

	return v0;
}
vec8i8_t Vec8i8_Sign(vec8i8_t v)
{
	v.v[0] = v.v[0] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;
	v.v[1] = v.v[1] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;
	v.v[2] = v.v[2] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;
	v.v[3] = v.v[3] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;
	v.v[4] = v.v[4] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;
	v.v[5] = v.v[5] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;
	v.v[6] = v.v[6] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;
	v.v[7] = v.v[7] < G_I8_ZERO ? G_I8_ONE : G_I8_ZERO;

	return v;
}
vec8i8_t Vec8i8_SignPosNeg(vec8i8_t v)
{
	v.v[0] = v.v[0] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;
	v.v[1] = v.v[1] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;
	v.v[2] = v.v[2] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;
	v.v[3] = v.v[3] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;
	v.v[4] = v.v[4] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;
	v.v[5] = v.v[5] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;
	v.v[6] = v.v[6] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;
	v.v[7] = v.v[7] < G_I8_ZERO ? G_I8_NEG_ONE : G_I8_ONE;

	return v;
}
vec8i8_t Vec8i8_Zero()
{
	return G_VEC8I8_T_ZERO;
}
vec8i8_t Vec8i8_One()
{
	return G_VEC8I8_T_ONE;
}
vec8i8_t Vec8i8_NegOne()
{
	return Vec8i8_Neg(G_VEC8I8_T_ONE);
}
vec8i8_t Vec8i8_Cross(vec8i8_t v0, vec8i8_t v1, vec8i8_t v2, vec8i8_t v3, vec8i8_t v4, vec8i8_t v5, vec8i8_t v6)
{
	vec8i8_t v;
	mat8x8i8_t mat;
	int i;

	mat.v[1] = v0;
	mat.v[2] = v1;
	mat.v[3] = v2;
	mat.v[4] = v3;
	mat.v[5] = v4;
	mat.v[6] = v5;
	mat.v[7] = v6;

	for (i = 0; i < 8; i++)
		v.v[i] = Mat7x7i8_Det(Mat8x8i8_DeleteRowColumn(mat, 0, i));

	return v;
}
vec2f32_t Vec2f64_ToVec2f32(vec2f64_t v)
{
	vec2f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	return outvec;
}
vec2u64_t Vec2f64_ToVec2u64(vec2f64_t v)
{
	vec2u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	return outvec;
}
vec2i64_t Vec2f64_ToVec2i64(vec2f64_t v)
{
	vec2i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	return outvec;
}
vec2u32_t Vec2f64_ToVec2u32(vec2f64_t v)
{
	vec2u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	return outvec;
}
vec2i32_t Vec2f64_ToVec2i32(vec2f64_t v)
{
	vec2i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	return outvec;
}
vec2u16_t Vec2f64_ToVec2u16(vec2f64_t v)
{
	vec2u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	return outvec;
}
vec2i16_t Vec2f64_ToVec2i16(vec2f64_t v)
{
	vec2i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	return outvec;
}
vec2u8_t Vec2f64_ToVec2u8(vec2f64_t v)
{
	vec2u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	return outvec;
}
vec2i8_t Vec2f64_ToVec2i8(vec2f64_t v)
{
	vec2i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	return outvec;
}
vec2f64_t Vec2f32_ToVec2f64(vec2f32_t v)
{
	vec2f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	return outvec;
}
vec2u64_t Vec2f32_ToVec2u64(vec2f32_t v)
{
	vec2u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	return outvec;
}
vec2i64_t Vec2f32_ToVec2i64(vec2f32_t v)
{
	vec2i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	return outvec;
}
vec2u32_t Vec2f32_ToVec2u32(vec2f32_t v)
{
	vec2u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	return outvec;
}
vec2i32_t Vec2f32_ToVec2i32(vec2f32_t v)
{
	vec2i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	return outvec;
}
vec2u16_t Vec2f32_ToVec2u16(vec2f32_t v)
{
	vec2u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	return outvec;
}
vec2i16_t Vec2f32_ToVec2i16(vec2f32_t v)
{
	vec2i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	return outvec;
}
vec2u8_t Vec2f32_ToVec2u8(vec2f32_t v)
{
	vec2u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	return outvec;
}
vec2i8_t Vec2f32_ToVec2i8(vec2f32_t v)
{
	vec2i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	return outvec;
}
vec2f64_t Vec2u64_ToVec2f64(vec2u64_t v)
{
	vec2f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	return outvec;
}
vec2f32_t Vec2u64_ToVec2f32(vec2u64_t v)
{
	vec2f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	return outvec;
}
vec2i64_t Vec2u64_ToVec2i64(vec2u64_t v)
{
	vec2i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	return outvec;
}
vec2u32_t Vec2u64_ToVec2u32(vec2u64_t v)
{
	vec2u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	return outvec;
}
vec2i32_t Vec2u64_ToVec2i32(vec2u64_t v)
{
	vec2i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	return outvec;
}
vec2u16_t Vec2u64_ToVec2u16(vec2u64_t v)
{
	vec2u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	return outvec;
}
vec2i16_t Vec2u64_ToVec2i16(vec2u64_t v)
{
	vec2i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	return outvec;
}
vec2u8_t Vec2u64_ToVec2u8(vec2u64_t v)
{
	vec2u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	return outvec;
}
vec2i8_t Vec2u64_ToVec2i8(vec2u64_t v)
{
	vec2i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	return outvec;
}
vec2f64_t Vec2i64_ToVec2f64(vec2i64_t v)
{
	vec2f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	return outvec;
}
vec2f32_t Vec2i64_ToVec2f32(vec2i64_t v)
{
	vec2f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	return outvec;
}
vec2u64_t Vec2i64_ToVec2u64(vec2i64_t v)
{
	vec2u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	return outvec;
}
vec2u32_t Vec2i64_ToVec2u32(vec2i64_t v)
{
	vec2u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	return outvec;
}
vec2i32_t Vec2i64_ToVec2i32(vec2i64_t v)
{
	vec2i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	return outvec;
}
vec2u16_t Vec2i64_ToVec2u16(vec2i64_t v)
{
	vec2u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	return outvec;
}
vec2i16_t Vec2i64_ToVec2i16(vec2i64_t v)
{
	vec2i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	return outvec;
}
vec2u8_t Vec2i64_ToVec2u8(vec2i64_t v)
{
	vec2u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	return outvec;
}
vec2i8_t Vec2i64_ToVec2i8(vec2i64_t v)
{
	vec2i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	return outvec;
}
vec2f64_t Vec2u32_ToVec2f64(vec2u32_t v)
{
	vec2f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	return outvec;
}
vec2f32_t Vec2u32_ToVec2f32(vec2u32_t v)
{
	vec2f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	return outvec;
}
vec2u64_t Vec2u32_ToVec2u64(vec2u32_t v)
{
	vec2u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	return outvec;
}
vec2i64_t Vec2u32_ToVec2i64(vec2u32_t v)
{
	vec2i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	return outvec;
}
vec2i32_t Vec2u32_ToVec2i32(vec2u32_t v)
{
	vec2i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	return outvec;
}
vec2u16_t Vec2u32_ToVec2u16(vec2u32_t v)
{
	vec2u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	return outvec;
}
vec2i16_t Vec2u32_ToVec2i16(vec2u32_t v)
{
	vec2i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	return outvec;
}
vec2u8_t Vec2u32_ToVec2u8(vec2u32_t v)
{
	vec2u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	return outvec;
}
vec2i8_t Vec2u32_ToVec2i8(vec2u32_t v)
{
	vec2i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	return outvec;
}
vec2f64_t Vec2i32_ToVec2f64(vec2i32_t v)
{
	vec2f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	return outvec;
}
vec2f32_t Vec2i32_ToVec2f32(vec2i32_t v)
{
	vec2f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	return outvec;
}
vec2u64_t Vec2i32_ToVec2u64(vec2i32_t v)
{
	vec2u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	return outvec;
}
vec2i64_t Vec2i32_ToVec2i64(vec2i32_t v)
{
	vec2i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	return outvec;
}
vec2u32_t Vec2i32_ToVec2u32(vec2i32_t v)
{
	vec2u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	return outvec;
}
vec2u16_t Vec2i32_ToVec2u16(vec2i32_t v)
{
	vec2u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	return outvec;
}
vec2i16_t Vec2i32_ToVec2i16(vec2i32_t v)
{
	vec2i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	return outvec;
}
vec2u8_t Vec2i32_ToVec2u8(vec2i32_t v)
{
	vec2u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	return outvec;
}
vec2i8_t Vec2i32_ToVec2i8(vec2i32_t v)
{
	vec2i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	return outvec;
}
vec2f64_t Vec2u16_ToVec2f64(vec2u16_t v)
{
	vec2f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	return outvec;
}
vec2f32_t Vec2u16_ToVec2f32(vec2u16_t v)
{
	vec2f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	return outvec;
}
vec2u64_t Vec2u16_ToVec2u64(vec2u16_t v)
{
	vec2u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	return outvec;
}
vec2i64_t Vec2u16_ToVec2i64(vec2u16_t v)
{
	vec2i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	return outvec;
}
vec2u32_t Vec2u16_ToVec2u32(vec2u16_t v)
{
	vec2u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	return outvec;
}
vec2i32_t Vec2u16_ToVec2i32(vec2u16_t v)
{
	vec2i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	return outvec;
}
vec2i16_t Vec2u16_ToVec2i16(vec2u16_t v)
{
	vec2i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	return outvec;
}
vec2u8_t Vec2u16_ToVec2u8(vec2u16_t v)
{
	vec2u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	return outvec;
}
vec2i8_t Vec2u16_ToVec2i8(vec2u16_t v)
{
	vec2i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	return outvec;
}
vec2f64_t Vec2i16_ToVec2f64(vec2i16_t v)
{
	vec2f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	return outvec;
}
vec2f32_t Vec2i16_ToVec2f32(vec2i16_t v)
{
	vec2f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	return outvec;
}
vec2u64_t Vec2i16_ToVec2u64(vec2i16_t v)
{
	vec2u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	return outvec;
}
vec2i64_t Vec2i16_ToVec2i64(vec2i16_t v)
{
	vec2i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	return outvec;
}
vec2u32_t Vec2i16_ToVec2u32(vec2i16_t v)
{
	vec2u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	return outvec;
}
vec2i32_t Vec2i16_ToVec2i32(vec2i16_t v)
{
	vec2i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	return outvec;
}
vec2u16_t Vec2i16_ToVec2u16(vec2i16_t v)
{
	vec2u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	return outvec;
}
vec2u8_t Vec2i16_ToVec2u8(vec2i16_t v)
{
	vec2u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	return outvec;
}
vec2i8_t Vec2i16_ToVec2i8(vec2i16_t v)
{
	vec2i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	return outvec;
}
vec2f64_t Vec2u8_ToVec2f64(vec2u8_t v)
{
	vec2f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	return outvec;
}
vec2f32_t Vec2u8_ToVec2f32(vec2u8_t v)
{
	vec2f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	return outvec;
}
vec2u64_t Vec2u8_ToVec2u64(vec2u8_t v)
{
	vec2u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	return outvec;
}
vec2i64_t Vec2u8_ToVec2i64(vec2u8_t v)
{
	vec2i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	return outvec;
}
vec2u32_t Vec2u8_ToVec2u32(vec2u8_t v)
{
	vec2u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	return outvec;
}
vec2i32_t Vec2u8_ToVec2i32(vec2u8_t v)
{
	vec2i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	return outvec;
}
vec2u16_t Vec2u8_ToVec2u16(vec2u8_t v)
{
	vec2u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	return outvec;
}
vec2i16_t Vec2u8_ToVec2i16(vec2u8_t v)
{
	vec2i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	return outvec;
}
vec2i8_t Vec2u8_ToVec2i8(vec2u8_t v)
{
	vec2i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	return outvec;
}
vec2f64_t Vec2i8_ToVec2f64(vec2i8_t v)
{
	vec2f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	return outvec;
}
vec2f32_t Vec2i8_ToVec2f32(vec2i8_t v)
{
	vec2f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	return outvec;
}
vec2u64_t Vec2i8_ToVec2u64(vec2i8_t v)
{
	vec2u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	return outvec;
}
vec2i64_t Vec2i8_ToVec2i64(vec2i8_t v)
{
	vec2i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	return outvec;
}
vec2u32_t Vec2i8_ToVec2u32(vec2i8_t v)
{
	vec2u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	return outvec;
}
vec2i32_t Vec2i8_ToVec2i32(vec2i8_t v)
{
	vec2i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	return outvec;
}
vec2u16_t Vec2i8_ToVec2u16(vec2i8_t v)
{
	vec2u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	return outvec;
}
vec2i16_t Vec2i8_ToVec2i16(vec2i8_t v)
{
	vec2i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	return outvec;
}
vec2u8_t Vec2i8_ToVec2u8(vec2i8_t v)
{
	vec2u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	return outvec;
}
vec3f32_t Vec3f64_ToVec3f32(vec3f64_t v)
{
	vec3f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	return outvec;
}
vec3u64_t Vec3f64_ToVec3u64(vec3f64_t v)
{
	vec3u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	return outvec;
}
vec3i64_t Vec3f64_ToVec3i64(vec3f64_t v)
{
	vec3i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	return outvec;
}
vec3u32_t Vec3f64_ToVec3u32(vec3f64_t v)
{
	vec3u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	return outvec;
}
vec3i32_t Vec3f64_ToVec3i32(vec3f64_t v)
{
	vec3i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	return outvec;
}
vec3u16_t Vec3f64_ToVec3u16(vec3f64_t v)
{
	vec3u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	return outvec;
}
vec3i16_t Vec3f64_ToVec3i16(vec3f64_t v)
{
	vec3i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	return outvec;
}
vec3u8_t Vec3f64_ToVec3u8(vec3f64_t v)
{
	vec3u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	return outvec;
}
vec3i8_t Vec3f64_ToVec3i8(vec3f64_t v)
{
	vec3i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	return outvec;
}
vec3f64_t Vec3f32_ToVec3f64(vec3f32_t v)
{
	vec3f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	return outvec;
}
vec3u64_t Vec3f32_ToVec3u64(vec3f32_t v)
{
	vec3u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	return outvec;
}
vec3i64_t Vec3f32_ToVec3i64(vec3f32_t v)
{
	vec3i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	return outvec;
}
vec3u32_t Vec3f32_ToVec3u32(vec3f32_t v)
{
	vec3u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	return outvec;
}
vec3i32_t Vec3f32_ToVec3i32(vec3f32_t v)
{
	vec3i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	return outvec;
}
vec3u16_t Vec3f32_ToVec3u16(vec3f32_t v)
{
	vec3u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	return outvec;
}
vec3i16_t Vec3f32_ToVec3i16(vec3f32_t v)
{
	vec3i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	return outvec;
}
vec3u8_t Vec3f32_ToVec3u8(vec3f32_t v)
{
	vec3u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	return outvec;
}
vec3i8_t Vec3f32_ToVec3i8(vec3f32_t v)
{
	vec3i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	return outvec;
}
vec3f64_t Vec3u64_ToVec3f64(vec3u64_t v)
{
	vec3f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	return outvec;
}
vec3f32_t Vec3u64_ToVec3f32(vec3u64_t v)
{
	vec3f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	return outvec;
}
vec3i64_t Vec3u64_ToVec3i64(vec3u64_t v)
{
	vec3i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	return outvec;
}
vec3u32_t Vec3u64_ToVec3u32(vec3u64_t v)
{
	vec3u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	return outvec;
}
vec3i32_t Vec3u64_ToVec3i32(vec3u64_t v)
{
	vec3i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	return outvec;
}
vec3u16_t Vec3u64_ToVec3u16(vec3u64_t v)
{
	vec3u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	return outvec;
}
vec3i16_t Vec3u64_ToVec3i16(vec3u64_t v)
{
	vec3i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	return outvec;
}
vec3u8_t Vec3u64_ToVec3u8(vec3u64_t v)
{
	vec3u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	return outvec;
}
vec3i8_t Vec3u64_ToVec3i8(vec3u64_t v)
{
	vec3i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	return outvec;
}
vec3f64_t Vec3i64_ToVec3f64(vec3i64_t v)
{
	vec3f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	return outvec;
}
vec3f32_t Vec3i64_ToVec3f32(vec3i64_t v)
{
	vec3f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	return outvec;
}
vec3u64_t Vec3i64_ToVec3u64(vec3i64_t v)
{
	vec3u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	return outvec;
}
vec3u32_t Vec3i64_ToVec3u32(vec3i64_t v)
{
	vec3u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	return outvec;
}
vec3i32_t Vec3i64_ToVec3i32(vec3i64_t v)
{
	vec3i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	return outvec;
}
vec3u16_t Vec3i64_ToVec3u16(vec3i64_t v)
{
	vec3u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	return outvec;
}
vec3i16_t Vec3i64_ToVec3i16(vec3i64_t v)
{
	vec3i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	return outvec;
}
vec3u8_t Vec3i64_ToVec3u8(vec3i64_t v)
{
	vec3u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	return outvec;
}
vec3i8_t Vec3i64_ToVec3i8(vec3i64_t v)
{
	vec3i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	return outvec;
}
vec3f64_t Vec3u32_ToVec3f64(vec3u32_t v)
{
	vec3f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	return outvec;
}
vec3f32_t Vec3u32_ToVec3f32(vec3u32_t v)
{
	vec3f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	return outvec;
}
vec3u64_t Vec3u32_ToVec3u64(vec3u32_t v)
{
	vec3u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	return outvec;
}
vec3i64_t Vec3u32_ToVec3i64(vec3u32_t v)
{
	vec3i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	return outvec;
}
vec3i32_t Vec3u32_ToVec3i32(vec3u32_t v)
{
	vec3i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	return outvec;
}
vec3u16_t Vec3u32_ToVec3u16(vec3u32_t v)
{
	vec3u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	return outvec;
}
vec3i16_t Vec3u32_ToVec3i16(vec3u32_t v)
{
	vec3i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	return outvec;
}
vec3u8_t Vec3u32_ToVec3u8(vec3u32_t v)
{
	vec3u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	return outvec;
}
vec3i8_t Vec3u32_ToVec3i8(vec3u32_t v)
{
	vec3i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	return outvec;
}
vec3f64_t Vec3i32_ToVec3f64(vec3i32_t v)
{
	vec3f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	return outvec;
}
vec3f32_t Vec3i32_ToVec3f32(vec3i32_t v)
{
	vec3f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	return outvec;
}
vec3u64_t Vec3i32_ToVec3u64(vec3i32_t v)
{
	vec3u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	return outvec;
}
vec3i64_t Vec3i32_ToVec3i64(vec3i32_t v)
{
	vec3i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	return outvec;
}
vec3u32_t Vec3i32_ToVec3u32(vec3i32_t v)
{
	vec3u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	return outvec;
}
vec3u16_t Vec3i32_ToVec3u16(vec3i32_t v)
{
	vec3u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	return outvec;
}
vec3i16_t Vec3i32_ToVec3i16(vec3i32_t v)
{
	vec3i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	return outvec;
}
vec3u8_t Vec3i32_ToVec3u8(vec3i32_t v)
{
	vec3u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	return outvec;
}
vec3i8_t Vec3i32_ToVec3i8(vec3i32_t v)
{
	vec3i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	return outvec;
}
vec3f64_t Vec3u16_ToVec3f64(vec3u16_t v)
{
	vec3f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	return outvec;
}
vec3f32_t Vec3u16_ToVec3f32(vec3u16_t v)
{
	vec3f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	return outvec;
}
vec3u64_t Vec3u16_ToVec3u64(vec3u16_t v)
{
	vec3u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	return outvec;
}
vec3i64_t Vec3u16_ToVec3i64(vec3u16_t v)
{
	vec3i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	return outvec;
}
vec3u32_t Vec3u16_ToVec3u32(vec3u16_t v)
{
	vec3u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	return outvec;
}
vec3i32_t Vec3u16_ToVec3i32(vec3u16_t v)
{
	vec3i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	return outvec;
}
vec3i16_t Vec3u16_ToVec3i16(vec3u16_t v)
{
	vec3i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	return outvec;
}
vec3u8_t Vec3u16_ToVec3u8(vec3u16_t v)
{
	vec3u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	return outvec;
}
vec3i8_t Vec3u16_ToVec3i8(vec3u16_t v)
{
	vec3i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	return outvec;
}
vec3f64_t Vec3i16_ToVec3f64(vec3i16_t v)
{
	vec3f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	return outvec;
}
vec3f32_t Vec3i16_ToVec3f32(vec3i16_t v)
{
	vec3f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	return outvec;
}
vec3u64_t Vec3i16_ToVec3u64(vec3i16_t v)
{
	vec3u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	return outvec;
}
vec3i64_t Vec3i16_ToVec3i64(vec3i16_t v)
{
	vec3i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	return outvec;
}
vec3u32_t Vec3i16_ToVec3u32(vec3i16_t v)
{
	vec3u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	return outvec;
}
vec3i32_t Vec3i16_ToVec3i32(vec3i16_t v)
{
	vec3i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	return outvec;
}
vec3u16_t Vec3i16_ToVec3u16(vec3i16_t v)
{
	vec3u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	return outvec;
}
vec3u8_t Vec3i16_ToVec3u8(vec3i16_t v)
{
	vec3u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	return outvec;
}
vec3i8_t Vec3i16_ToVec3i8(vec3i16_t v)
{
	vec3i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	return outvec;
}
vec3f64_t Vec3u8_ToVec3f64(vec3u8_t v)
{
	vec3f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	return outvec;
}
vec3f32_t Vec3u8_ToVec3f32(vec3u8_t v)
{
	vec3f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	return outvec;
}
vec3u64_t Vec3u8_ToVec3u64(vec3u8_t v)
{
	vec3u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	return outvec;
}
vec3i64_t Vec3u8_ToVec3i64(vec3u8_t v)
{
	vec3i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	return outvec;
}
vec3u32_t Vec3u8_ToVec3u32(vec3u8_t v)
{
	vec3u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	return outvec;
}
vec3i32_t Vec3u8_ToVec3i32(vec3u8_t v)
{
	vec3i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	return outvec;
}
vec3u16_t Vec3u8_ToVec3u16(vec3u8_t v)
{
	vec3u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	return outvec;
}
vec3i16_t Vec3u8_ToVec3i16(vec3u8_t v)
{
	vec3i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	return outvec;
}
vec3i8_t Vec3u8_ToVec3i8(vec3u8_t v)
{
	vec3i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	return outvec;
}
vec3f64_t Vec3i8_ToVec3f64(vec3i8_t v)
{
	vec3f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	return outvec;
}
vec3f32_t Vec3i8_ToVec3f32(vec3i8_t v)
{
	vec3f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	return outvec;
}
vec3u64_t Vec3i8_ToVec3u64(vec3i8_t v)
{
	vec3u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	return outvec;
}
vec3i64_t Vec3i8_ToVec3i64(vec3i8_t v)
{
	vec3i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	return outvec;
}
vec3u32_t Vec3i8_ToVec3u32(vec3i8_t v)
{
	vec3u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	return outvec;
}
vec3i32_t Vec3i8_ToVec3i32(vec3i8_t v)
{
	vec3i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	return outvec;
}
vec3u16_t Vec3i8_ToVec3u16(vec3i8_t v)
{
	vec3u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	return outvec;
}
vec3i16_t Vec3i8_ToVec3i16(vec3i8_t v)
{
	vec3i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	return outvec;
}
vec3u8_t Vec3i8_ToVec3u8(vec3i8_t v)
{
	vec3u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	return outvec;
}
vec4f32_t Vec4f64_ToVec4f32(vec4f64_t v)
{
	vec4f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	return outvec;
}
vec4u64_t Vec4f64_ToVec4u64(vec4f64_t v)
{
	vec4u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	return outvec;
}
vec4i64_t Vec4f64_ToVec4i64(vec4f64_t v)
{
	vec4i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	return outvec;
}
vec4u32_t Vec4f64_ToVec4u32(vec4f64_t v)
{
	vec4u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	return outvec;
}
vec4i32_t Vec4f64_ToVec4i32(vec4f64_t v)
{
	vec4i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	return outvec;
}
vec4u16_t Vec4f64_ToVec4u16(vec4f64_t v)
{
	vec4u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	return outvec;
}
vec4i16_t Vec4f64_ToVec4i16(vec4f64_t v)
{
	vec4i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	return outvec;
}
vec4u8_t Vec4f64_ToVec4u8(vec4f64_t v)
{
	vec4u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	return outvec;
}
vec4i8_t Vec4f64_ToVec4i8(vec4f64_t v)
{
	vec4i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	return outvec;
}
vec4f64_t Vec4f32_ToVec4f64(vec4f32_t v)
{
	vec4f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	return outvec;
}
vec4u64_t Vec4f32_ToVec4u64(vec4f32_t v)
{
	vec4u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	return outvec;
}
vec4i64_t Vec4f32_ToVec4i64(vec4f32_t v)
{
	vec4i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	return outvec;
}
vec4u32_t Vec4f32_ToVec4u32(vec4f32_t v)
{
	vec4u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	return outvec;
}
vec4i32_t Vec4f32_ToVec4i32(vec4f32_t v)
{
	vec4i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	return outvec;
}
vec4u16_t Vec4f32_ToVec4u16(vec4f32_t v)
{
	vec4u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	return outvec;
}
vec4i16_t Vec4f32_ToVec4i16(vec4f32_t v)
{
	vec4i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	return outvec;
}
vec4u8_t Vec4f32_ToVec4u8(vec4f32_t v)
{
	vec4u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	return outvec;
}
vec4i8_t Vec4f32_ToVec4i8(vec4f32_t v)
{
	vec4i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	return outvec;
}
vec4f64_t Vec4u64_ToVec4f64(vec4u64_t v)
{
	vec4f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	return outvec;
}
vec4f32_t Vec4u64_ToVec4f32(vec4u64_t v)
{
	vec4f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	return outvec;
}
vec4i64_t Vec4u64_ToVec4i64(vec4u64_t v)
{
	vec4i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	return outvec;
}
vec4u32_t Vec4u64_ToVec4u32(vec4u64_t v)
{
	vec4u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	return outvec;
}
vec4i32_t Vec4u64_ToVec4i32(vec4u64_t v)
{
	vec4i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	return outvec;
}
vec4u16_t Vec4u64_ToVec4u16(vec4u64_t v)
{
	vec4u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	return outvec;
}
vec4i16_t Vec4u64_ToVec4i16(vec4u64_t v)
{
	vec4i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	return outvec;
}
vec4u8_t Vec4u64_ToVec4u8(vec4u64_t v)
{
	vec4u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	return outvec;
}
vec4i8_t Vec4u64_ToVec4i8(vec4u64_t v)
{
	vec4i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	return outvec;
}
vec4f64_t Vec4i64_ToVec4f64(vec4i64_t v)
{
	vec4f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	return outvec;
}
vec4f32_t Vec4i64_ToVec4f32(vec4i64_t v)
{
	vec4f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	return outvec;
}
vec4u64_t Vec4i64_ToVec4u64(vec4i64_t v)
{
	vec4u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	return outvec;
}
vec4u32_t Vec4i64_ToVec4u32(vec4i64_t v)
{
	vec4u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	return outvec;
}
vec4i32_t Vec4i64_ToVec4i32(vec4i64_t v)
{
	vec4i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	return outvec;
}
vec4u16_t Vec4i64_ToVec4u16(vec4i64_t v)
{
	vec4u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	return outvec;
}
vec4i16_t Vec4i64_ToVec4i16(vec4i64_t v)
{
	vec4i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	return outvec;
}
vec4u8_t Vec4i64_ToVec4u8(vec4i64_t v)
{
	vec4u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	return outvec;
}
vec4i8_t Vec4i64_ToVec4i8(vec4i64_t v)
{
	vec4i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	return outvec;
}
vec4f64_t Vec4u32_ToVec4f64(vec4u32_t v)
{
	vec4f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	return outvec;
}
vec4f32_t Vec4u32_ToVec4f32(vec4u32_t v)
{
	vec4f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	return outvec;
}
vec4u64_t Vec4u32_ToVec4u64(vec4u32_t v)
{
	vec4u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	return outvec;
}
vec4i64_t Vec4u32_ToVec4i64(vec4u32_t v)
{
	vec4i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	return outvec;
}
vec4i32_t Vec4u32_ToVec4i32(vec4u32_t v)
{
	vec4i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	return outvec;
}
vec4u16_t Vec4u32_ToVec4u16(vec4u32_t v)
{
	vec4u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	return outvec;
}
vec4i16_t Vec4u32_ToVec4i16(vec4u32_t v)
{
	vec4i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	return outvec;
}
vec4u8_t Vec4u32_ToVec4u8(vec4u32_t v)
{
	vec4u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	return outvec;
}
vec4i8_t Vec4u32_ToVec4i8(vec4u32_t v)
{
	vec4i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	return outvec;
}
vec4f64_t Vec4i32_ToVec4f64(vec4i32_t v)
{
	vec4f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	return outvec;
}
vec4f32_t Vec4i32_ToVec4f32(vec4i32_t v)
{
	vec4f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	return outvec;
}
vec4u64_t Vec4i32_ToVec4u64(vec4i32_t v)
{
	vec4u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	return outvec;
}
vec4i64_t Vec4i32_ToVec4i64(vec4i32_t v)
{
	vec4i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	return outvec;
}
vec4u32_t Vec4i32_ToVec4u32(vec4i32_t v)
{
	vec4u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	return outvec;
}
vec4u16_t Vec4i32_ToVec4u16(vec4i32_t v)
{
	vec4u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	return outvec;
}
vec4i16_t Vec4i32_ToVec4i16(vec4i32_t v)
{
	vec4i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	return outvec;
}
vec4u8_t Vec4i32_ToVec4u8(vec4i32_t v)
{
	vec4u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	return outvec;
}
vec4i8_t Vec4i32_ToVec4i8(vec4i32_t v)
{
	vec4i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	return outvec;
}
vec4f64_t Vec4u16_ToVec4f64(vec4u16_t v)
{
	vec4f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	return outvec;
}
vec4f32_t Vec4u16_ToVec4f32(vec4u16_t v)
{
	vec4f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	return outvec;
}
vec4u64_t Vec4u16_ToVec4u64(vec4u16_t v)
{
	vec4u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	return outvec;
}
vec4i64_t Vec4u16_ToVec4i64(vec4u16_t v)
{
	vec4i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	return outvec;
}
vec4u32_t Vec4u16_ToVec4u32(vec4u16_t v)
{
	vec4u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	return outvec;
}
vec4i32_t Vec4u16_ToVec4i32(vec4u16_t v)
{
	vec4i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	return outvec;
}
vec4i16_t Vec4u16_ToVec4i16(vec4u16_t v)
{
	vec4i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	return outvec;
}
vec4u8_t Vec4u16_ToVec4u8(vec4u16_t v)
{
	vec4u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	return outvec;
}
vec4i8_t Vec4u16_ToVec4i8(vec4u16_t v)
{
	vec4i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	return outvec;
}
vec4f64_t Vec4i16_ToVec4f64(vec4i16_t v)
{
	vec4f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	return outvec;
}
vec4f32_t Vec4i16_ToVec4f32(vec4i16_t v)
{
	vec4f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	return outvec;
}
vec4u64_t Vec4i16_ToVec4u64(vec4i16_t v)
{
	vec4u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	return outvec;
}
vec4i64_t Vec4i16_ToVec4i64(vec4i16_t v)
{
	vec4i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	return outvec;
}
vec4u32_t Vec4i16_ToVec4u32(vec4i16_t v)
{
	vec4u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	return outvec;
}
vec4i32_t Vec4i16_ToVec4i32(vec4i16_t v)
{
	vec4i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	return outvec;
}
vec4u16_t Vec4i16_ToVec4u16(vec4i16_t v)
{
	vec4u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	return outvec;
}
vec4u8_t Vec4i16_ToVec4u8(vec4i16_t v)
{
	vec4u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	return outvec;
}
vec4i8_t Vec4i16_ToVec4i8(vec4i16_t v)
{
	vec4i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	return outvec;
}
vec4f64_t Vec4u8_ToVec4f64(vec4u8_t v)
{
	vec4f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	return outvec;
}
vec4f32_t Vec4u8_ToVec4f32(vec4u8_t v)
{
	vec4f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	return outvec;
}
vec4u64_t Vec4u8_ToVec4u64(vec4u8_t v)
{
	vec4u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	return outvec;
}
vec4i64_t Vec4u8_ToVec4i64(vec4u8_t v)
{
	vec4i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	return outvec;
}
vec4u32_t Vec4u8_ToVec4u32(vec4u8_t v)
{
	vec4u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	return outvec;
}
vec4i32_t Vec4u8_ToVec4i32(vec4u8_t v)
{
	vec4i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	return outvec;
}
vec4u16_t Vec4u8_ToVec4u16(vec4u8_t v)
{
	vec4u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	return outvec;
}
vec4i16_t Vec4u8_ToVec4i16(vec4u8_t v)
{
	vec4i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	return outvec;
}
vec4i8_t Vec4u8_ToVec4i8(vec4u8_t v)
{
	vec4i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	return outvec;
}
vec4f64_t Vec4i8_ToVec4f64(vec4i8_t v)
{
	vec4f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	return outvec;
}
vec4f32_t Vec4i8_ToVec4f32(vec4i8_t v)
{
	vec4f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	return outvec;
}
vec4u64_t Vec4i8_ToVec4u64(vec4i8_t v)
{
	vec4u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	return outvec;
}
vec4i64_t Vec4i8_ToVec4i64(vec4i8_t v)
{
	vec4i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	return outvec;
}
vec4u32_t Vec4i8_ToVec4u32(vec4i8_t v)
{
	vec4u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	return outvec;
}
vec4i32_t Vec4i8_ToVec4i32(vec4i8_t v)
{
	vec4i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	return outvec;
}
vec4u16_t Vec4i8_ToVec4u16(vec4i8_t v)
{
	vec4u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	return outvec;
}
vec4i16_t Vec4i8_ToVec4i16(vec4i8_t v)
{
	vec4i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	return outvec;
}
vec4u8_t Vec4i8_ToVec4u8(vec4i8_t v)
{
	vec4u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	return outvec;
}
vec5f32_t Vec5f64_ToVec5f32(vec5f64_t v)
{
	vec5f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	return outvec;
}
vec5u64_t Vec5f64_ToVec5u64(vec5f64_t v)
{
	vec5u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	return outvec;
}
vec5i64_t Vec5f64_ToVec5i64(vec5f64_t v)
{
	vec5i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	return outvec;
}
vec5u32_t Vec5f64_ToVec5u32(vec5f64_t v)
{
	vec5u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	return outvec;
}
vec5i32_t Vec5f64_ToVec5i32(vec5f64_t v)
{
	vec5i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	return outvec;
}
vec5u16_t Vec5f64_ToVec5u16(vec5f64_t v)
{
	vec5u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	return outvec;
}
vec5i16_t Vec5f64_ToVec5i16(vec5f64_t v)
{
	vec5i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	return outvec;
}
vec5u8_t Vec5f64_ToVec5u8(vec5f64_t v)
{
	vec5u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	return outvec;
}
vec5i8_t Vec5f64_ToVec5i8(vec5f64_t v)
{
	vec5i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	return outvec;
}
vec5f64_t Vec5f32_ToVec5f64(vec5f32_t v)
{
	vec5f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	return outvec;
}
vec5u64_t Vec5f32_ToVec5u64(vec5f32_t v)
{
	vec5u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	return outvec;
}
vec5i64_t Vec5f32_ToVec5i64(vec5f32_t v)
{
	vec5i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	return outvec;
}
vec5u32_t Vec5f32_ToVec5u32(vec5f32_t v)
{
	vec5u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	return outvec;
}
vec5i32_t Vec5f32_ToVec5i32(vec5f32_t v)
{
	vec5i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	return outvec;
}
vec5u16_t Vec5f32_ToVec5u16(vec5f32_t v)
{
	vec5u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	return outvec;
}
vec5i16_t Vec5f32_ToVec5i16(vec5f32_t v)
{
	vec5i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	return outvec;
}
vec5u8_t Vec5f32_ToVec5u8(vec5f32_t v)
{
	vec5u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	return outvec;
}
vec5i8_t Vec5f32_ToVec5i8(vec5f32_t v)
{
	vec5i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	return outvec;
}
vec5f64_t Vec5u64_ToVec5f64(vec5u64_t v)
{
	vec5f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	return outvec;
}
vec5f32_t Vec5u64_ToVec5f32(vec5u64_t v)
{
	vec5f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	return outvec;
}
vec5i64_t Vec5u64_ToVec5i64(vec5u64_t v)
{
	vec5i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	return outvec;
}
vec5u32_t Vec5u64_ToVec5u32(vec5u64_t v)
{
	vec5u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	return outvec;
}
vec5i32_t Vec5u64_ToVec5i32(vec5u64_t v)
{
	vec5i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	return outvec;
}
vec5u16_t Vec5u64_ToVec5u16(vec5u64_t v)
{
	vec5u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	return outvec;
}
vec5i16_t Vec5u64_ToVec5i16(vec5u64_t v)
{
	vec5i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	return outvec;
}
vec5u8_t Vec5u64_ToVec5u8(vec5u64_t v)
{
	vec5u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	return outvec;
}
vec5i8_t Vec5u64_ToVec5i8(vec5u64_t v)
{
	vec5i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	return outvec;
}
vec5f64_t Vec5i64_ToVec5f64(vec5i64_t v)
{
	vec5f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	return outvec;
}
vec5f32_t Vec5i64_ToVec5f32(vec5i64_t v)
{
	vec5f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	return outvec;
}
vec5u64_t Vec5i64_ToVec5u64(vec5i64_t v)
{
	vec5u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	return outvec;
}
vec5u32_t Vec5i64_ToVec5u32(vec5i64_t v)
{
	vec5u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	return outvec;
}
vec5i32_t Vec5i64_ToVec5i32(vec5i64_t v)
{
	vec5i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	return outvec;
}
vec5u16_t Vec5i64_ToVec5u16(vec5i64_t v)
{
	vec5u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	return outvec;
}
vec5i16_t Vec5i64_ToVec5i16(vec5i64_t v)
{
	vec5i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	return outvec;
}
vec5u8_t Vec5i64_ToVec5u8(vec5i64_t v)
{
	vec5u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	return outvec;
}
vec5i8_t Vec5i64_ToVec5i8(vec5i64_t v)
{
	vec5i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	return outvec;
}
vec5f64_t Vec5u32_ToVec5f64(vec5u32_t v)
{
	vec5f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	return outvec;
}
vec5f32_t Vec5u32_ToVec5f32(vec5u32_t v)
{
	vec5f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	return outvec;
}
vec5u64_t Vec5u32_ToVec5u64(vec5u32_t v)
{
	vec5u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	return outvec;
}
vec5i64_t Vec5u32_ToVec5i64(vec5u32_t v)
{
	vec5i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	return outvec;
}
vec5i32_t Vec5u32_ToVec5i32(vec5u32_t v)
{
	vec5i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	return outvec;
}
vec5u16_t Vec5u32_ToVec5u16(vec5u32_t v)
{
	vec5u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	return outvec;
}
vec5i16_t Vec5u32_ToVec5i16(vec5u32_t v)
{
	vec5i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	return outvec;
}
vec5u8_t Vec5u32_ToVec5u8(vec5u32_t v)
{
	vec5u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	return outvec;
}
vec5i8_t Vec5u32_ToVec5i8(vec5u32_t v)
{
	vec5i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	return outvec;
}
vec5f64_t Vec5i32_ToVec5f64(vec5i32_t v)
{
	vec5f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	return outvec;
}
vec5f32_t Vec5i32_ToVec5f32(vec5i32_t v)
{
	vec5f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	return outvec;
}
vec5u64_t Vec5i32_ToVec5u64(vec5i32_t v)
{
	vec5u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	return outvec;
}
vec5i64_t Vec5i32_ToVec5i64(vec5i32_t v)
{
	vec5i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	return outvec;
}
vec5u32_t Vec5i32_ToVec5u32(vec5i32_t v)
{
	vec5u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	return outvec;
}
vec5u16_t Vec5i32_ToVec5u16(vec5i32_t v)
{
	vec5u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	return outvec;
}
vec5i16_t Vec5i32_ToVec5i16(vec5i32_t v)
{
	vec5i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	return outvec;
}
vec5u8_t Vec5i32_ToVec5u8(vec5i32_t v)
{
	vec5u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	return outvec;
}
vec5i8_t Vec5i32_ToVec5i8(vec5i32_t v)
{
	vec5i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	return outvec;
}
vec5f64_t Vec5u16_ToVec5f64(vec5u16_t v)
{
	vec5f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	return outvec;
}
vec5f32_t Vec5u16_ToVec5f32(vec5u16_t v)
{
	vec5f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	return outvec;
}
vec5u64_t Vec5u16_ToVec5u64(vec5u16_t v)
{
	vec5u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	return outvec;
}
vec5i64_t Vec5u16_ToVec5i64(vec5u16_t v)
{
	vec5i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	return outvec;
}
vec5u32_t Vec5u16_ToVec5u32(vec5u16_t v)
{
	vec5u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	return outvec;
}
vec5i32_t Vec5u16_ToVec5i32(vec5u16_t v)
{
	vec5i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	return outvec;
}
vec5i16_t Vec5u16_ToVec5i16(vec5u16_t v)
{
	vec5i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	return outvec;
}
vec5u8_t Vec5u16_ToVec5u8(vec5u16_t v)
{
	vec5u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	return outvec;
}
vec5i8_t Vec5u16_ToVec5i8(vec5u16_t v)
{
	vec5i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	return outvec;
}
vec5f64_t Vec5i16_ToVec5f64(vec5i16_t v)
{
	vec5f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	return outvec;
}
vec5f32_t Vec5i16_ToVec5f32(vec5i16_t v)
{
	vec5f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	return outvec;
}
vec5u64_t Vec5i16_ToVec5u64(vec5i16_t v)
{
	vec5u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	return outvec;
}
vec5i64_t Vec5i16_ToVec5i64(vec5i16_t v)
{
	vec5i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	return outvec;
}
vec5u32_t Vec5i16_ToVec5u32(vec5i16_t v)
{
	vec5u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	return outvec;
}
vec5i32_t Vec5i16_ToVec5i32(vec5i16_t v)
{
	vec5i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	return outvec;
}
vec5u16_t Vec5i16_ToVec5u16(vec5i16_t v)
{
	vec5u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	return outvec;
}
vec5u8_t Vec5i16_ToVec5u8(vec5i16_t v)
{
	vec5u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	return outvec;
}
vec5i8_t Vec5i16_ToVec5i8(vec5i16_t v)
{
	vec5i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	return outvec;
}
vec5f64_t Vec5u8_ToVec5f64(vec5u8_t v)
{
	vec5f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	return outvec;
}
vec5f32_t Vec5u8_ToVec5f32(vec5u8_t v)
{
	vec5f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	return outvec;
}
vec5u64_t Vec5u8_ToVec5u64(vec5u8_t v)
{
	vec5u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	return outvec;
}
vec5i64_t Vec5u8_ToVec5i64(vec5u8_t v)
{
	vec5i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	return outvec;
}
vec5u32_t Vec5u8_ToVec5u32(vec5u8_t v)
{
	vec5u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	return outvec;
}
vec5i32_t Vec5u8_ToVec5i32(vec5u8_t v)
{
	vec5i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	return outvec;
}
vec5u16_t Vec5u8_ToVec5u16(vec5u8_t v)
{
	vec5u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	return outvec;
}
vec5i16_t Vec5u8_ToVec5i16(vec5u8_t v)
{
	vec5i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	return outvec;
}
vec5i8_t Vec5u8_ToVec5i8(vec5u8_t v)
{
	vec5i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	return outvec;
}
vec5f64_t Vec5i8_ToVec5f64(vec5i8_t v)
{
	vec5f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	return outvec;
}
vec5f32_t Vec5i8_ToVec5f32(vec5i8_t v)
{
	vec5f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	return outvec;
}
vec5u64_t Vec5i8_ToVec5u64(vec5i8_t v)
{
	vec5u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	return outvec;
}
vec5i64_t Vec5i8_ToVec5i64(vec5i8_t v)
{
	vec5i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	return outvec;
}
vec5u32_t Vec5i8_ToVec5u32(vec5i8_t v)
{
	vec5u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	return outvec;
}
vec5i32_t Vec5i8_ToVec5i32(vec5i8_t v)
{
	vec5i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	return outvec;
}
vec5u16_t Vec5i8_ToVec5u16(vec5i8_t v)
{
	vec5u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	return outvec;
}
vec5i16_t Vec5i8_ToVec5i16(vec5i8_t v)
{
	vec5i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	return outvec;
}
vec5u8_t Vec5i8_ToVec5u8(vec5i8_t v)
{
	vec5u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	return outvec;
}
vec6f32_t Vec6f64_ToVec6f32(vec6f64_t v)
{
	vec6f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	outvec.v[5] = (float)v.v[5];
	return outvec;
}
vec6u64_t Vec6f64_ToVec6u64(vec6f64_t v)
{
	vec6u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	outvec.v[5] = (uint64_t)v.v[5];
	return outvec;
}
vec6i64_t Vec6f64_ToVec6i64(vec6f64_t v)
{
	vec6i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	outvec.v[5] = (int64_t)v.v[5];
	return outvec;
}
vec6u32_t Vec6f64_ToVec6u32(vec6f64_t v)
{
	vec6u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	outvec.v[5] = (uint32_t)v.v[5];
	return outvec;
}
vec6i32_t Vec6f64_ToVec6i32(vec6f64_t v)
{
	vec6i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	outvec.v[5] = (int32_t)v.v[5];
	return outvec;
}
vec6u16_t Vec6f64_ToVec6u16(vec6f64_t v)
{
	vec6u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	outvec.v[5] = (uint16_t)v.v[5];
	return outvec;
}
vec6i16_t Vec6f64_ToVec6i16(vec6f64_t v)
{
	vec6i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	outvec.v[5] = (int16_t)v.v[5];
	return outvec;
}
vec6u8_t Vec6f64_ToVec6u8(vec6f64_t v)
{
	vec6u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	outvec.v[5] = (uint8_t)v.v[5];
	return outvec;
}
vec6i8_t Vec6f64_ToVec6i8(vec6f64_t v)
{
	vec6i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	outvec.v[5] = (int8_t)v.v[5];
	return outvec;
}
vec6f64_t Vec6f32_ToVec6f64(vec6f32_t v)
{
	vec6f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	outvec.v[5] = (double)v.v[5];
	return outvec;
}
vec6u64_t Vec6f32_ToVec6u64(vec6f32_t v)
{
	vec6u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	outvec.v[5] = (uint64_t)v.v[5];
	return outvec;
}
vec6i64_t Vec6f32_ToVec6i64(vec6f32_t v)
{
	vec6i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	outvec.v[5] = (int64_t)v.v[5];
	return outvec;
}
vec6u32_t Vec6f32_ToVec6u32(vec6f32_t v)
{
	vec6u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	outvec.v[5] = (uint32_t)v.v[5];
	return outvec;
}
vec6i32_t Vec6f32_ToVec6i32(vec6f32_t v)
{
	vec6i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	outvec.v[5] = (int32_t)v.v[5];
	return outvec;
}
vec6u16_t Vec6f32_ToVec6u16(vec6f32_t v)
{
	vec6u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	outvec.v[5] = (uint16_t)v.v[5];
	return outvec;
}
vec6i16_t Vec6f32_ToVec6i16(vec6f32_t v)
{
	vec6i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	outvec.v[5] = (int16_t)v.v[5];
	return outvec;
}
vec6u8_t Vec6f32_ToVec6u8(vec6f32_t v)
{
	vec6u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	outvec.v[5] = (uint8_t)v.v[5];
	return outvec;
}
vec6i8_t Vec6f32_ToVec6i8(vec6f32_t v)
{
	vec6i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	outvec.v[5] = (int8_t)v.v[5];
	return outvec;
}
vec6f64_t Vec6u64_ToVec6f64(vec6u64_t v)
{
	vec6f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	outvec.v[5] = (double)v.v[5];
	return outvec;
}
vec6f32_t Vec6u64_ToVec6f32(vec6u64_t v)
{
	vec6f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	outvec.v[5] = (float)v.v[5];
	return outvec;
}
vec6i64_t Vec6u64_ToVec6i64(vec6u64_t v)
{
	vec6i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	outvec.v[5] = (int64_t)v.v[5];
	return outvec;
}
vec6u32_t Vec6u64_ToVec6u32(vec6u64_t v)
{
	vec6u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	outvec.v[5] = (uint32_t)v.v[5];
	return outvec;
}
vec6i32_t Vec6u64_ToVec6i32(vec6u64_t v)
{
	vec6i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	outvec.v[5] = (int32_t)v.v[5];
	return outvec;
}
vec6u16_t Vec6u64_ToVec6u16(vec6u64_t v)
{
	vec6u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	outvec.v[5] = (uint16_t)v.v[5];
	return outvec;
}
vec6i16_t Vec6u64_ToVec6i16(vec6u64_t v)
{
	vec6i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	outvec.v[5] = (int16_t)v.v[5];
	return outvec;
}
vec6u8_t Vec6u64_ToVec6u8(vec6u64_t v)
{
	vec6u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	outvec.v[5] = (uint8_t)v.v[5];
	return outvec;
}
vec6i8_t Vec6u64_ToVec6i8(vec6u64_t v)
{
	vec6i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	outvec.v[5] = (int8_t)v.v[5];
	return outvec;
}
vec6f64_t Vec6i64_ToVec6f64(vec6i64_t v)
{
	vec6f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	outvec.v[5] = (double)v.v[5];
	return outvec;
}
vec6f32_t Vec6i64_ToVec6f32(vec6i64_t v)
{
	vec6f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	outvec.v[5] = (float)v.v[5];
	return outvec;
}
vec6u64_t Vec6i64_ToVec6u64(vec6i64_t v)
{
	vec6u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	outvec.v[5] = (uint64_t)v.v[5];
	return outvec;
}
vec6u32_t Vec6i64_ToVec6u32(vec6i64_t v)
{
	vec6u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	outvec.v[5] = (uint32_t)v.v[5];
	return outvec;
}
vec6i32_t Vec6i64_ToVec6i32(vec6i64_t v)
{
	vec6i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	outvec.v[5] = (int32_t)v.v[5];
	return outvec;
}
vec6u16_t Vec6i64_ToVec6u16(vec6i64_t v)
{
	vec6u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	outvec.v[5] = (uint16_t)v.v[5];
	return outvec;
}
vec6i16_t Vec6i64_ToVec6i16(vec6i64_t v)
{
	vec6i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	outvec.v[5] = (int16_t)v.v[5];
	return outvec;
}
vec6u8_t Vec6i64_ToVec6u8(vec6i64_t v)
{
	vec6u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	outvec.v[5] = (uint8_t)v.v[5];
	return outvec;
}
vec6i8_t Vec6i64_ToVec6i8(vec6i64_t v)
{
	vec6i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	outvec.v[5] = (int8_t)v.v[5];
	return outvec;
}
vec6f64_t Vec6u32_ToVec6f64(vec6u32_t v)
{
	vec6f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	outvec.v[5] = (double)v.v[5];
	return outvec;
}
vec6f32_t Vec6u32_ToVec6f32(vec6u32_t v)
{
	vec6f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	outvec.v[5] = (float)v.v[5];
	return outvec;
}
vec6u64_t Vec6u32_ToVec6u64(vec6u32_t v)
{
	vec6u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	outvec.v[5] = (uint64_t)v.v[5];
	return outvec;
}
vec6i64_t Vec6u32_ToVec6i64(vec6u32_t v)
{
	vec6i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	outvec.v[5] = (int64_t)v.v[5];
	return outvec;
}
vec6i32_t Vec6u32_ToVec6i32(vec6u32_t v)
{
	vec6i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	outvec.v[5] = (int32_t)v.v[5];
	return outvec;
}
vec6u16_t Vec6u32_ToVec6u16(vec6u32_t v)
{
	vec6u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	outvec.v[5] = (uint16_t)v.v[5];
	return outvec;
}
vec6i16_t Vec6u32_ToVec6i16(vec6u32_t v)
{
	vec6i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	outvec.v[5] = (int16_t)v.v[5];
	return outvec;
}
vec6u8_t Vec6u32_ToVec6u8(vec6u32_t v)
{
	vec6u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	outvec.v[5] = (uint8_t)v.v[5];
	return outvec;
}
vec6i8_t Vec6u32_ToVec6i8(vec6u32_t v)
{
	vec6i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	outvec.v[5] = (int8_t)v.v[5];
	return outvec;
}
vec6f64_t Vec6i32_ToVec6f64(vec6i32_t v)
{
	vec6f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	outvec.v[5] = (double)v.v[5];
	return outvec;
}
vec6f32_t Vec6i32_ToVec6f32(vec6i32_t v)
{
	vec6f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	outvec.v[5] = (float)v.v[5];
	return outvec;
}
vec6u64_t Vec6i32_ToVec6u64(vec6i32_t v)
{
	vec6u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	outvec.v[5] = (uint64_t)v.v[5];
	return outvec;
}
vec6i64_t Vec6i32_ToVec6i64(vec6i32_t v)
{
	vec6i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	outvec.v[5] = (int64_t)v.v[5];
	return outvec;
}
vec6u32_t Vec6i32_ToVec6u32(vec6i32_t v)
{
	vec6u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	outvec.v[5] = (uint32_t)v.v[5];
	return outvec;
}
vec6u16_t Vec6i32_ToVec6u16(vec6i32_t v)
{
	vec6u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	outvec.v[5] = (uint16_t)v.v[5];
	return outvec;
}
vec6i16_t Vec6i32_ToVec6i16(vec6i32_t v)
{
	vec6i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	outvec.v[5] = (int16_t)v.v[5];
	return outvec;
}
vec6u8_t Vec6i32_ToVec6u8(vec6i32_t v)
{
	vec6u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	outvec.v[5] = (uint8_t)v.v[5];
	return outvec;
}
vec6i8_t Vec6i32_ToVec6i8(vec6i32_t v)
{
	vec6i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	outvec.v[5] = (int8_t)v.v[5];
	return outvec;
}
vec6f64_t Vec6u16_ToVec6f64(vec6u16_t v)
{
	vec6f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	outvec.v[5] = (double)v.v[5];
	return outvec;
}
vec6f32_t Vec6u16_ToVec6f32(vec6u16_t v)
{
	vec6f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	outvec.v[5] = (float)v.v[5];
	return outvec;
}
vec6u64_t Vec6u16_ToVec6u64(vec6u16_t v)
{
	vec6u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	outvec.v[5] = (uint64_t)v.v[5];
	return outvec;
}
vec6i64_t Vec6u16_ToVec6i64(vec6u16_t v)
{
	vec6i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	outvec.v[5] = (int64_t)v.v[5];
	return outvec;
}
vec6u32_t Vec6u16_ToVec6u32(vec6u16_t v)
{
	vec6u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	outvec.v[5] = (uint32_t)v.v[5];
	return outvec;
}
vec6i32_t Vec6u16_ToVec6i32(vec6u16_t v)
{
	vec6i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	outvec.v[5] = (int32_t)v.v[5];
	return outvec;
}
vec6i16_t Vec6u16_ToVec6i16(vec6u16_t v)
{
	vec6i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	outvec.v[5] = (int16_t)v.v[5];
	return outvec;
}
vec6u8_t Vec6u16_ToVec6u8(vec6u16_t v)
{
	vec6u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	outvec.v[5] = (uint8_t)v.v[5];
	return outvec;
}
vec6i8_t Vec6u16_ToVec6i8(vec6u16_t v)
{
	vec6i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	outvec.v[5] = (int8_t)v.v[5];
	return outvec;
}
vec6f64_t Vec6i16_ToVec6f64(vec6i16_t v)
{
	vec6f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	outvec.v[5] = (double)v.v[5];
	return outvec;
}
vec6f32_t Vec6i16_ToVec6f32(vec6i16_t v)
{
	vec6f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	outvec.v[5] = (float)v.v[5];
	return outvec;
}
vec6u64_t Vec6i16_ToVec6u64(vec6i16_t v)
{
	vec6u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	outvec.v[5] = (uint64_t)v.v[5];
	return outvec;
}
vec6i64_t Vec6i16_ToVec6i64(vec6i16_t v)
{
	vec6i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	outvec.v[5] = (int64_t)v.v[5];
	return outvec;
}
vec6u32_t Vec6i16_ToVec6u32(vec6i16_t v)
{
	vec6u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	outvec.v[5] = (uint32_t)v.v[5];
	return outvec;
}
vec6i32_t Vec6i16_ToVec6i32(vec6i16_t v)
{
	vec6i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	outvec.v[5] = (int32_t)v.v[5];
	return outvec;
}
vec6u16_t Vec6i16_ToVec6u16(vec6i16_t v)
{
	vec6u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	outvec.v[5] = (uint16_t)v.v[5];
	return outvec;
}
vec6u8_t Vec6i16_ToVec6u8(vec6i16_t v)
{
	vec6u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	outvec.v[5] = (uint8_t)v.v[5];
	return outvec;
}
vec6i8_t Vec6i16_ToVec6i8(vec6i16_t v)
{
	vec6i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	outvec.v[5] = (int8_t)v.v[5];
	return outvec;
}
vec6f64_t Vec6u8_ToVec6f64(vec6u8_t v)
{
	vec6f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	outvec.v[5] = (double)v.v[5];
	return outvec;
}
vec6f32_t Vec6u8_ToVec6f32(vec6u8_t v)
{
	vec6f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	outvec.v[5] = (float)v.v[5];
	return outvec;
}
vec6u64_t Vec6u8_ToVec6u64(vec6u8_t v)
{
	vec6u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	outvec.v[5] = (uint64_t)v.v[5];
	return outvec;
}
vec6i64_t Vec6u8_ToVec6i64(vec6u8_t v)
{
	vec6i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	outvec.v[5] = (int64_t)v.v[5];
	return outvec;
}
vec6u32_t Vec6u8_ToVec6u32(vec6u8_t v)
{
	vec6u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	outvec.v[5] = (uint32_t)v.v[5];
	return outvec;
}
vec6i32_t Vec6u8_ToVec6i32(vec6u8_t v)
{
	vec6i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	outvec.v[5] = (int32_t)v.v[5];
	return outvec;
}
vec6u16_t Vec6u8_ToVec6u16(vec6u8_t v)
{
	vec6u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	outvec.v[5] = (uint16_t)v.v[5];
	return outvec;
}
vec6i16_t Vec6u8_ToVec6i16(vec6u8_t v)
{
	vec6i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	outvec.v[5] = (int16_t)v.v[5];
	return outvec;
}
vec6i8_t Vec6u8_ToVec6i8(vec6u8_t v)
{
	vec6i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	outvec.v[5] = (int8_t)v.v[5];
	return outvec;
}
vec6f64_t Vec6i8_ToVec6f64(vec6i8_t v)
{
	vec6f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	outvec.v[5] = (double)v.v[5];
	return outvec;
}
vec6f32_t Vec6i8_ToVec6f32(vec6i8_t v)
{
	vec6f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	outvec.v[5] = (float)v.v[5];
	return outvec;
}
vec6u64_t Vec6i8_ToVec6u64(vec6i8_t v)
{
	vec6u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	outvec.v[5] = (uint64_t)v.v[5];
	return outvec;
}
vec6i64_t Vec6i8_ToVec6i64(vec6i8_t v)
{
	vec6i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	outvec.v[5] = (int64_t)v.v[5];
	return outvec;
}
vec6u32_t Vec6i8_ToVec6u32(vec6i8_t v)
{
	vec6u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	outvec.v[5] = (uint32_t)v.v[5];
	return outvec;
}
vec6i32_t Vec6i8_ToVec6i32(vec6i8_t v)
{
	vec6i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	outvec.v[5] = (int32_t)v.v[5];
	return outvec;
}
vec6u16_t Vec6i8_ToVec6u16(vec6i8_t v)
{
	vec6u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	outvec.v[5] = (uint16_t)v.v[5];
	return outvec;
}
vec6i16_t Vec6i8_ToVec6i16(vec6i8_t v)
{
	vec6i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	outvec.v[5] = (int16_t)v.v[5];
	return outvec;
}
vec6u8_t Vec6i8_ToVec6u8(vec6i8_t v)
{
	vec6u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	outvec.v[5] = (uint8_t)v.v[5];
	return outvec;
}
vec7f32_t Vec7f64_ToVec7f32(vec7f64_t v)
{
	vec7f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	outvec.v[5] = (float)v.v[5];
	outvec.v[6] = (float)v.v[6];
	return outvec;
}
vec7u64_t Vec7f64_ToVec7u64(vec7f64_t v)
{
	vec7u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	outvec.v[5] = (uint64_t)v.v[5];
	outvec.v[6] = (uint64_t)v.v[6];
	return outvec;
}
vec7i64_t Vec7f64_ToVec7i64(vec7f64_t v)
{
	vec7i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	outvec.v[5] = (int64_t)v.v[5];
	outvec.v[6] = (int64_t)v.v[6];
	return outvec;
}
vec7u32_t Vec7f64_ToVec7u32(vec7f64_t v)
{
	vec7u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	outvec.v[5] = (uint32_t)v.v[5];
	outvec.v[6] = (uint32_t)v.v[6];
	return outvec;
}
vec7i32_t Vec7f64_ToVec7i32(vec7f64_t v)
{
	vec7i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	outvec.v[5] = (int32_t)v.v[5];
	outvec.v[6] = (int32_t)v.v[6];
	return outvec;
}
vec7u16_t Vec7f64_ToVec7u16(vec7f64_t v)
{
	vec7u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	outvec.v[5] = (uint16_t)v.v[5];
	outvec.v[6] = (uint16_t)v.v[6];
	return outvec;
}
vec7i16_t Vec7f64_ToVec7i16(vec7f64_t v)
{
	vec7i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	outvec.v[5] = (int16_t)v.v[5];
	outvec.v[6] = (int16_t)v.v[6];
	return outvec;
}
vec7u8_t Vec7f64_ToVec7u8(vec7f64_t v)
{
	vec7u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	outvec.v[5] = (uint8_t)v.v[5];
	outvec.v[6] = (uint8_t)v.v[6];
	return outvec;
}
vec7i8_t Vec7f64_ToVec7i8(vec7f64_t v)
{
	vec7i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	outvec.v[5] = (int8_t)v.v[5];
	outvec.v[6] = (int8_t)v.v[6];
	return outvec;
}
vec7f64_t Vec7f32_ToVec7f64(vec7f32_t v)
{
	vec7f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	outvec.v[5] = (double)v.v[5];
	outvec.v[6] = (double)v.v[6];
	return outvec;
}
vec7u64_t Vec7f32_ToVec7u64(vec7f32_t v)
{
	vec7u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	outvec.v[5] = (uint64_t)v.v[5];
	outvec.v[6] = (uint64_t)v.v[6];
	return outvec;
}
vec7i64_t Vec7f32_ToVec7i64(vec7f32_t v)
{
	vec7i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	outvec.v[5] = (int64_t)v.v[5];
	outvec.v[6] = (int64_t)v.v[6];
	return outvec;
}
vec7u32_t Vec7f32_ToVec7u32(vec7f32_t v)
{
	vec7u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	outvec.v[5] = (uint32_t)v.v[5];
	outvec.v[6] = (uint32_t)v.v[6];
	return outvec;
}
vec7i32_t Vec7f32_ToVec7i32(vec7f32_t v)
{
	vec7i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	outvec.v[5] = (int32_t)v.v[5];
	outvec.v[6] = (int32_t)v.v[6];
	return outvec;
}
vec7u16_t Vec7f32_ToVec7u16(vec7f32_t v)
{
	vec7u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	outvec.v[5] = (uint16_t)v.v[5];
	outvec.v[6] = (uint16_t)v.v[6];
	return outvec;
}
vec7i16_t Vec7f32_ToVec7i16(vec7f32_t v)
{
	vec7i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	outvec.v[5] = (int16_t)v.v[5];
	outvec.v[6] = (int16_t)v.v[6];
	return outvec;
}
vec7u8_t Vec7f32_ToVec7u8(vec7f32_t v)
{
	vec7u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	outvec.v[5] = (uint8_t)v.v[5];
	outvec.v[6] = (uint8_t)v.v[6];
	return outvec;
}
vec7i8_t Vec7f32_ToVec7i8(vec7f32_t v)
{
	vec7i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	outvec.v[5] = (int8_t)v.v[5];
	outvec.v[6] = (int8_t)v.v[6];
	return outvec;
}
vec7f64_t Vec7u64_ToVec7f64(vec7u64_t v)
{
	vec7f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	outvec.v[5] = (double)v.v[5];
	outvec.v[6] = (double)v.v[6];
	return outvec;
}
vec7f32_t Vec7u64_ToVec7f32(vec7u64_t v)
{
	vec7f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	outvec.v[5] = (float)v.v[5];
	outvec.v[6] = (float)v.v[6];
	return outvec;
}
vec7i64_t Vec7u64_ToVec7i64(vec7u64_t v)
{
	vec7i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	outvec.v[5] = (int64_t)v.v[5];
	outvec.v[6] = (int64_t)v.v[6];
	return outvec;
}
vec7u32_t Vec7u64_ToVec7u32(vec7u64_t v)
{
	vec7u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	outvec.v[5] = (uint32_t)v.v[5];
	outvec.v[6] = (uint32_t)v.v[6];
	return outvec;
}
vec7i32_t Vec7u64_ToVec7i32(vec7u64_t v)
{
	vec7i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	outvec.v[5] = (int32_t)v.v[5];
	outvec.v[6] = (int32_t)v.v[6];
	return outvec;
}
vec7u16_t Vec7u64_ToVec7u16(vec7u64_t v)
{
	vec7u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	outvec.v[5] = (uint16_t)v.v[5];
	outvec.v[6] = (uint16_t)v.v[6];
	return outvec;
}
vec7i16_t Vec7u64_ToVec7i16(vec7u64_t v)
{
	vec7i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	outvec.v[5] = (int16_t)v.v[5];
	outvec.v[6] = (int16_t)v.v[6];
	return outvec;
}
vec7u8_t Vec7u64_ToVec7u8(vec7u64_t v)
{
	vec7u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	outvec.v[5] = (uint8_t)v.v[5];
	outvec.v[6] = (uint8_t)v.v[6];
	return outvec;
}
vec7i8_t Vec7u64_ToVec7i8(vec7u64_t v)
{
	vec7i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	outvec.v[5] = (int8_t)v.v[5];
	outvec.v[6] = (int8_t)v.v[6];
	return outvec;
}
vec7f64_t Vec7i64_ToVec7f64(vec7i64_t v)
{
	vec7f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	outvec.v[5] = (double)v.v[5];
	outvec.v[6] = (double)v.v[6];
	return outvec;
}
vec7f32_t Vec7i64_ToVec7f32(vec7i64_t v)
{
	vec7f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	outvec.v[5] = (float)v.v[5];
	outvec.v[6] = (float)v.v[6];
	return outvec;
}
vec7u64_t Vec7i64_ToVec7u64(vec7i64_t v)
{
	vec7u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	outvec.v[5] = (uint64_t)v.v[5];
	outvec.v[6] = (uint64_t)v.v[6];
	return outvec;
}
vec7u32_t Vec7i64_ToVec7u32(vec7i64_t v)
{
	vec7u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	outvec.v[5] = (uint32_t)v.v[5];
	outvec.v[6] = (uint32_t)v.v[6];
	return outvec;
}
vec7i32_t Vec7i64_ToVec7i32(vec7i64_t v)
{
	vec7i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	outvec.v[5] = (int32_t)v.v[5];
	outvec.v[6] = (int32_t)v.v[6];
	return outvec;
}
vec7u16_t Vec7i64_ToVec7u16(vec7i64_t v)
{
	vec7u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	outvec.v[5] = (uint16_t)v.v[5];
	outvec.v[6] = (uint16_t)v.v[6];
	return outvec;
}
vec7i16_t Vec7i64_ToVec7i16(vec7i64_t v)
{
	vec7i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	outvec.v[5] = (int16_t)v.v[5];
	outvec.v[6] = (int16_t)v.v[6];
	return outvec;
}
vec7u8_t Vec7i64_ToVec7u8(vec7i64_t v)
{
	vec7u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	outvec.v[5] = (uint8_t)v.v[5];
	outvec.v[6] = (uint8_t)v.v[6];
	return outvec;
}
vec7i8_t Vec7i64_ToVec7i8(vec7i64_t v)
{
	vec7i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	outvec.v[5] = (int8_t)v.v[5];
	outvec.v[6] = (int8_t)v.v[6];
	return outvec;
}
vec7f64_t Vec7u32_ToVec7f64(vec7u32_t v)
{
	vec7f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	outvec.v[5] = (double)v.v[5];
	outvec.v[6] = (double)v.v[6];
	return outvec;
}
vec7f32_t Vec7u32_ToVec7f32(vec7u32_t v)
{
	vec7f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	outvec.v[5] = (float)v.v[5];
	outvec.v[6] = (float)v.v[6];
	return outvec;
}
vec7u64_t Vec7u32_ToVec7u64(vec7u32_t v)
{
	vec7u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	outvec.v[5] = (uint64_t)v.v[5];
	outvec.v[6] = (uint64_t)v.v[6];
	return outvec;
}
vec7i64_t Vec7u32_ToVec7i64(vec7u32_t v)
{
	vec7i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	outvec.v[5] = (int64_t)v.v[5];
	outvec.v[6] = (int64_t)v.v[6];
	return outvec;
}
vec7i32_t Vec7u32_ToVec7i32(vec7u32_t v)
{
	vec7i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	outvec.v[5] = (int32_t)v.v[5];
	outvec.v[6] = (int32_t)v.v[6];
	return outvec;
}
vec7u16_t Vec7u32_ToVec7u16(vec7u32_t v)
{
	vec7u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	outvec.v[5] = (uint16_t)v.v[5];
	outvec.v[6] = (uint16_t)v.v[6];
	return outvec;
}
vec7i16_t Vec7u32_ToVec7i16(vec7u32_t v)
{
	vec7i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	outvec.v[5] = (int16_t)v.v[5];
	outvec.v[6] = (int16_t)v.v[6];
	return outvec;
}
vec7u8_t Vec7u32_ToVec7u8(vec7u32_t v)
{
	vec7u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	outvec.v[5] = (uint8_t)v.v[5];
	outvec.v[6] = (uint8_t)v.v[6];
	return outvec;
}
vec7i8_t Vec7u32_ToVec7i8(vec7u32_t v)
{
	vec7i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	outvec.v[5] = (int8_t)v.v[5];
	outvec.v[6] = (int8_t)v.v[6];
	return outvec;
}
vec7f64_t Vec7i32_ToVec7f64(vec7i32_t v)
{
	vec7f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	outvec.v[5] = (double)v.v[5];
	outvec.v[6] = (double)v.v[6];
	return outvec;
}
vec7f32_t Vec7i32_ToVec7f32(vec7i32_t v)
{
	vec7f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	outvec.v[5] = (float)v.v[5];
	outvec.v[6] = (float)v.v[6];
	return outvec;
}
vec7u64_t Vec7i32_ToVec7u64(vec7i32_t v)
{
	vec7u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	outvec.v[5] = (uint64_t)v.v[5];
	outvec.v[6] = (uint64_t)v.v[6];
	return outvec;
}
vec7i64_t Vec7i32_ToVec7i64(vec7i32_t v)
{
	vec7i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	outvec.v[5] = (int64_t)v.v[5];
	outvec.v[6] = (int64_t)v.v[6];
	return outvec;
}
vec7u32_t Vec7i32_ToVec7u32(vec7i32_t v)
{
	vec7u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	outvec.v[5] = (uint32_t)v.v[5];
	outvec.v[6] = (uint32_t)v.v[6];
	return outvec;
}
vec7u16_t Vec7i32_ToVec7u16(vec7i32_t v)
{
	vec7u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	outvec.v[5] = (uint16_t)v.v[5];
	outvec.v[6] = (uint16_t)v.v[6];
	return outvec;
}
vec7i16_t Vec7i32_ToVec7i16(vec7i32_t v)
{
	vec7i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	outvec.v[5] = (int16_t)v.v[5];
	outvec.v[6] = (int16_t)v.v[6];
	return outvec;
}
vec7u8_t Vec7i32_ToVec7u8(vec7i32_t v)
{
	vec7u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	outvec.v[5] = (uint8_t)v.v[5];
	outvec.v[6] = (uint8_t)v.v[6];
	return outvec;
}
vec7i8_t Vec7i32_ToVec7i8(vec7i32_t v)
{
	vec7i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	outvec.v[5] = (int8_t)v.v[5];
	outvec.v[6] = (int8_t)v.v[6];
	return outvec;
}
vec7f64_t Vec7u16_ToVec7f64(vec7u16_t v)
{
	vec7f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	outvec.v[5] = (double)v.v[5];
	outvec.v[6] = (double)v.v[6];
	return outvec;
}
vec7f32_t Vec7u16_ToVec7f32(vec7u16_t v)
{
	vec7f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	outvec.v[5] = (float)v.v[5];
	outvec.v[6] = (float)v.v[6];
	return outvec;
}
vec7u64_t Vec7u16_ToVec7u64(vec7u16_t v)
{
	vec7u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	outvec.v[5] = (uint64_t)v.v[5];
	outvec.v[6] = (uint64_t)v.v[6];
	return outvec;
}
vec7i64_t Vec7u16_ToVec7i64(vec7u16_t v)
{
	vec7i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	outvec.v[5] = (int64_t)v.v[5];
	outvec.v[6] = (int64_t)v.v[6];
	return outvec;
}
vec7u32_t Vec7u16_ToVec7u32(vec7u16_t v)
{
	vec7u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	outvec.v[5] = (uint32_t)v.v[5];
	outvec.v[6] = (uint32_t)v.v[6];
	return outvec;
}
vec7i32_t Vec7u16_ToVec7i32(vec7u16_t v)
{
	vec7i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	outvec.v[5] = (int32_t)v.v[5];
	outvec.v[6] = (int32_t)v.v[6];
	return outvec;
}
vec7i16_t Vec7u16_ToVec7i16(vec7u16_t v)
{
	vec7i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	outvec.v[5] = (int16_t)v.v[5];
	outvec.v[6] = (int16_t)v.v[6];
	return outvec;
}
vec7u8_t Vec7u16_ToVec7u8(vec7u16_t v)
{
	vec7u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	outvec.v[5] = (uint8_t)v.v[5];
	outvec.v[6] = (uint8_t)v.v[6];
	return outvec;
}
vec7i8_t Vec7u16_ToVec7i8(vec7u16_t v)
{
	vec7i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	outvec.v[5] = (int8_t)v.v[5];
	outvec.v[6] = (int8_t)v.v[6];
	return outvec;
}
vec7f64_t Vec7i16_ToVec7f64(vec7i16_t v)
{
	vec7f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	outvec.v[5] = (double)v.v[5];
	outvec.v[6] = (double)v.v[6];
	return outvec;
}
vec7f32_t Vec7i16_ToVec7f32(vec7i16_t v)
{
	vec7f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	outvec.v[5] = (float)v.v[5];
	outvec.v[6] = (float)v.v[6];
	return outvec;
}
vec7u64_t Vec7i16_ToVec7u64(vec7i16_t v)
{
	vec7u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	outvec.v[5] = (uint64_t)v.v[5];
	outvec.v[6] = (uint64_t)v.v[6];
	return outvec;
}
vec7i64_t Vec7i16_ToVec7i64(vec7i16_t v)
{
	vec7i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	outvec.v[5] = (int64_t)v.v[5];
	outvec.v[6] = (int64_t)v.v[6];
	return outvec;
}
vec7u32_t Vec7i16_ToVec7u32(vec7i16_t v)
{
	vec7u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	outvec.v[5] = (uint32_t)v.v[5];
	outvec.v[6] = (uint32_t)v.v[6];
	return outvec;
}
vec7i32_t Vec7i16_ToVec7i32(vec7i16_t v)
{
	vec7i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	outvec.v[5] = (int32_t)v.v[5];
	outvec.v[6] = (int32_t)v.v[6];
	return outvec;
}
vec7u16_t Vec7i16_ToVec7u16(vec7i16_t v)
{
	vec7u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	outvec.v[5] = (uint16_t)v.v[5];
	outvec.v[6] = (uint16_t)v.v[6];
	return outvec;
}
vec7u8_t Vec7i16_ToVec7u8(vec7i16_t v)
{
	vec7u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	outvec.v[5] = (uint8_t)v.v[5];
	outvec.v[6] = (uint8_t)v.v[6];
	return outvec;
}
vec7i8_t Vec7i16_ToVec7i8(vec7i16_t v)
{
	vec7i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	outvec.v[5] = (int8_t)v.v[5];
	outvec.v[6] = (int8_t)v.v[6];
	return outvec;
}
vec7f64_t Vec7u8_ToVec7f64(vec7u8_t v)
{
	vec7f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	outvec.v[5] = (double)v.v[5];
	outvec.v[6] = (double)v.v[6];
	return outvec;
}
vec7f32_t Vec7u8_ToVec7f32(vec7u8_t v)
{
	vec7f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	outvec.v[5] = (float)v.v[5];
	outvec.v[6] = (float)v.v[6];
	return outvec;
}
vec7u64_t Vec7u8_ToVec7u64(vec7u8_t v)
{
	vec7u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	outvec.v[5] = (uint64_t)v.v[5];
	outvec.v[6] = (uint64_t)v.v[6];
	return outvec;
}
vec7i64_t Vec7u8_ToVec7i64(vec7u8_t v)
{
	vec7i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	outvec.v[5] = (int64_t)v.v[5];
	outvec.v[6] = (int64_t)v.v[6];
	return outvec;
}
vec7u32_t Vec7u8_ToVec7u32(vec7u8_t v)
{
	vec7u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	outvec.v[5] = (uint32_t)v.v[5];
	outvec.v[6] = (uint32_t)v.v[6];
	return outvec;
}
vec7i32_t Vec7u8_ToVec7i32(vec7u8_t v)
{
	vec7i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	outvec.v[5] = (int32_t)v.v[5];
	outvec.v[6] = (int32_t)v.v[6];
	return outvec;
}
vec7u16_t Vec7u8_ToVec7u16(vec7u8_t v)
{
	vec7u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	outvec.v[5] = (uint16_t)v.v[5];
	outvec.v[6] = (uint16_t)v.v[6];
	return outvec;
}
vec7i16_t Vec7u8_ToVec7i16(vec7u8_t v)
{
	vec7i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	outvec.v[5] = (int16_t)v.v[5];
	outvec.v[6] = (int16_t)v.v[6];
	return outvec;
}
vec7i8_t Vec7u8_ToVec7i8(vec7u8_t v)
{
	vec7i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	outvec.v[5] = (int8_t)v.v[5];
	outvec.v[6] = (int8_t)v.v[6];
	return outvec;
}
vec7f64_t Vec7i8_ToVec7f64(vec7i8_t v)
{
	vec7f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	outvec.v[5] = (double)v.v[5];
	outvec.v[6] = (double)v.v[6];
	return outvec;
}
vec7f32_t Vec7i8_ToVec7f32(vec7i8_t v)
{
	vec7f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	outvec.v[5] = (float)v.v[5];
	outvec.v[6] = (float)v.v[6];
	return outvec;
}
vec7u64_t Vec7i8_ToVec7u64(vec7i8_t v)
{
	vec7u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	outvec.v[5] = (uint64_t)v.v[5];
	outvec.v[6] = (uint64_t)v.v[6];
	return outvec;
}
vec7i64_t Vec7i8_ToVec7i64(vec7i8_t v)
{
	vec7i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	outvec.v[5] = (int64_t)v.v[5];
	outvec.v[6] = (int64_t)v.v[6];
	return outvec;
}
vec7u32_t Vec7i8_ToVec7u32(vec7i8_t v)
{
	vec7u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	outvec.v[5] = (uint32_t)v.v[5];
	outvec.v[6] = (uint32_t)v.v[6];
	return outvec;
}
vec7i32_t Vec7i8_ToVec7i32(vec7i8_t v)
{
	vec7i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	outvec.v[5] = (int32_t)v.v[5];
	outvec.v[6] = (int32_t)v.v[6];
	return outvec;
}
vec7u16_t Vec7i8_ToVec7u16(vec7i8_t v)
{
	vec7u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	outvec.v[5] = (uint16_t)v.v[5];
	outvec.v[6] = (uint16_t)v.v[6];
	return outvec;
}
vec7i16_t Vec7i8_ToVec7i16(vec7i8_t v)
{
	vec7i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	outvec.v[5] = (int16_t)v.v[5];
	outvec.v[6] = (int16_t)v.v[6];
	return outvec;
}
vec7u8_t Vec7i8_ToVec7u8(vec7i8_t v)
{
	vec7u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	outvec.v[5] = (uint8_t)v.v[5];
	outvec.v[6] = (uint8_t)v.v[6];
	return outvec;
}
vec8f32_t Vec8f64_ToVec8f32(vec8f64_t v)
{
	vec8f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	outvec.v[5] = (float)v.v[5];
	outvec.v[6] = (float)v.v[6];
	outvec.v[7] = (float)v.v[7];
	return outvec;
}
vec8u64_t Vec8f64_ToVec8u64(vec8f64_t v)
{
	vec8u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	outvec.v[5] = (uint64_t)v.v[5];
	outvec.v[6] = (uint64_t)v.v[6];
	outvec.v[7] = (uint64_t)v.v[7];
	return outvec;
}
vec8i64_t Vec8f64_ToVec8i64(vec8f64_t v)
{
	vec8i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	outvec.v[5] = (int64_t)v.v[5];
	outvec.v[6] = (int64_t)v.v[6];
	outvec.v[7] = (int64_t)v.v[7];
	return outvec;
}
vec8u32_t Vec8f64_ToVec8u32(vec8f64_t v)
{
	vec8u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	outvec.v[5] = (uint32_t)v.v[5];
	outvec.v[6] = (uint32_t)v.v[6];
	outvec.v[7] = (uint32_t)v.v[7];
	return outvec;
}
vec8i32_t Vec8f64_ToVec8i32(vec8f64_t v)
{
	vec8i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	outvec.v[5] = (int32_t)v.v[5];
	outvec.v[6] = (int32_t)v.v[6];
	outvec.v[7] = (int32_t)v.v[7];
	return outvec;
}
vec8u16_t Vec8f64_ToVec8u16(vec8f64_t v)
{
	vec8u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	outvec.v[5] = (uint16_t)v.v[5];
	outvec.v[6] = (uint16_t)v.v[6];
	outvec.v[7] = (uint16_t)v.v[7];
	return outvec;
}
vec8i16_t Vec8f64_ToVec8i16(vec8f64_t v)
{
	vec8i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	outvec.v[5] = (int16_t)v.v[5];
	outvec.v[6] = (int16_t)v.v[6];
	outvec.v[7] = (int16_t)v.v[7];
	return outvec;
}
vec8u8_t Vec8f64_ToVec8u8(vec8f64_t v)
{
	vec8u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	outvec.v[5] = (uint8_t)v.v[5];
	outvec.v[6] = (uint8_t)v.v[6];
	outvec.v[7] = (uint8_t)v.v[7];
	return outvec;
}
vec8i8_t Vec8f64_ToVec8i8(vec8f64_t v)
{
	vec8i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	outvec.v[5] = (int8_t)v.v[5];
	outvec.v[6] = (int8_t)v.v[6];
	outvec.v[7] = (int8_t)v.v[7];
	return outvec;
}
vec8f64_t Vec8f32_ToVec8f64(vec8f32_t v)
{
	vec8f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	outvec.v[5] = (double)v.v[5];
	outvec.v[6] = (double)v.v[6];
	outvec.v[7] = (double)v.v[7];
	return outvec;
}
vec8u64_t Vec8f32_ToVec8u64(vec8f32_t v)
{
	vec8u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	outvec.v[5] = (uint64_t)v.v[5];
	outvec.v[6] = (uint64_t)v.v[6];
	outvec.v[7] = (uint64_t)v.v[7];
	return outvec;
}
vec8i64_t Vec8f32_ToVec8i64(vec8f32_t v)
{
	vec8i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	outvec.v[5] = (int64_t)v.v[5];
	outvec.v[6] = (int64_t)v.v[6];
	outvec.v[7] = (int64_t)v.v[7];
	return outvec;
}
vec8u32_t Vec8f32_ToVec8u32(vec8f32_t v)
{
	vec8u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	outvec.v[5] = (uint32_t)v.v[5];
	outvec.v[6] = (uint32_t)v.v[6];
	outvec.v[7] = (uint32_t)v.v[7];
	return outvec;
}
vec8i32_t Vec8f32_ToVec8i32(vec8f32_t v)
{
	vec8i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	outvec.v[5] = (int32_t)v.v[5];
	outvec.v[6] = (int32_t)v.v[6];
	outvec.v[7] = (int32_t)v.v[7];
	return outvec;
}
vec8u16_t Vec8f32_ToVec8u16(vec8f32_t v)
{
	vec8u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	outvec.v[5] = (uint16_t)v.v[5];
	outvec.v[6] = (uint16_t)v.v[6];
	outvec.v[7] = (uint16_t)v.v[7];
	return outvec;
}
vec8i16_t Vec8f32_ToVec8i16(vec8f32_t v)
{
	vec8i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	outvec.v[5] = (int16_t)v.v[5];
	outvec.v[6] = (int16_t)v.v[6];
	outvec.v[7] = (int16_t)v.v[7];
	return outvec;
}
vec8u8_t Vec8f32_ToVec8u8(vec8f32_t v)
{
	vec8u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	outvec.v[5] = (uint8_t)v.v[5];
	outvec.v[6] = (uint8_t)v.v[6];
	outvec.v[7] = (uint8_t)v.v[7];
	return outvec;
}
vec8i8_t Vec8f32_ToVec8i8(vec8f32_t v)
{
	vec8i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	outvec.v[5] = (int8_t)v.v[5];
	outvec.v[6] = (int8_t)v.v[6];
	outvec.v[7] = (int8_t)v.v[7];
	return outvec;
}
vec8f64_t Vec8u64_ToVec8f64(vec8u64_t v)
{
	vec8f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	outvec.v[5] = (double)v.v[5];
	outvec.v[6] = (double)v.v[6];
	outvec.v[7] = (double)v.v[7];
	return outvec;
}
vec8f32_t Vec8u64_ToVec8f32(vec8u64_t v)
{
	vec8f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	outvec.v[5] = (float)v.v[5];
	outvec.v[6] = (float)v.v[6];
	outvec.v[7] = (float)v.v[7];
	return outvec;
}
vec8i64_t Vec8u64_ToVec8i64(vec8u64_t v)
{
	vec8i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	outvec.v[5] = (int64_t)v.v[5];
	outvec.v[6] = (int64_t)v.v[6];
	outvec.v[7] = (int64_t)v.v[7];
	return outvec;
}
vec8u32_t Vec8u64_ToVec8u32(vec8u64_t v)
{
	vec8u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	outvec.v[5] = (uint32_t)v.v[5];
	outvec.v[6] = (uint32_t)v.v[6];
	outvec.v[7] = (uint32_t)v.v[7];
	return outvec;
}
vec8i32_t Vec8u64_ToVec8i32(vec8u64_t v)
{
	vec8i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	outvec.v[5] = (int32_t)v.v[5];
	outvec.v[6] = (int32_t)v.v[6];
	outvec.v[7] = (int32_t)v.v[7];
	return outvec;
}
vec8u16_t Vec8u64_ToVec8u16(vec8u64_t v)
{
	vec8u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	outvec.v[5] = (uint16_t)v.v[5];
	outvec.v[6] = (uint16_t)v.v[6];
	outvec.v[7] = (uint16_t)v.v[7];
	return outvec;
}
vec8i16_t Vec8u64_ToVec8i16(vec8u64_t v)
{
	vec8i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	outvec.v[5] = (int16_t)v.v[5];
	outvec.v[6] = (int16_t)v.v[6];
	outvec.v[7] = (int16_t)v.v[7];
	return outvec;
}
vec8u8_t Vec8u64_ToVec8u8(vec8u64_t v)
{
	vec8u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	outvec.v[5] = (uint8_t)v.v[5];
	outvec.v[6] = (uint8_t)v.v[6];
	outvec.v[7] = (uint8_t)v.v[7];
	return outvec;
}
vec8i8_t Vec8u64_ToVec8i8(vec8u64_t v)
{
	vec8i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	outvec.v[5] = (int8_t)v.v[5];
	outvec.v[6] = (int8_t)v.v[6];
	outvec.v[7] = (int8_t)v.v[7];
	return outvec;
}
vec8f64_t Vec8i64_ToVec8f64(vec8i64_t v)
{
	vec8f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	outvec.v[5] = (double)v.v[5];
	outvec.v[6] = (double)v.v[6];
	outvec.v[7] = (double)v.v[7];
	return outvec;
}
vec8f32_t Vec8i64_ToVec8f32(vec8i64_t v)
{
	vec8f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	outvec.v[5] = (float)v.v[5];
	outvec.v[6] = (float)v.v[6];
	outvec.v[7] = (float)v.v[7];
	return outvec;
}
vec8u64_t Vec8i64_ToVec8u64(vec8i64_t v)
{
	vec8u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	outvec.v[5] = (uint64_t)v.v[5];
	outvec.v[6] = (uint64_t)v.v[6];
	outvec.v[7] = (uint64_t)v.v[7];
	return outvec;
}
vec8u32_t Vec8i64_ToVec8u32(vec8i64_t v)
{
	vec8u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	outvec.v[5] = (uint32_t)v.v[5];
	outvec.v[6] = (uint32_t)v.v[6];
	outvec.v[7] = (uint32_t)v.v[7];
	return outvec;
}
vec8i32_t Vec8i64_ToVec8i32(vec8i64_t v)
{
	vec8i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	outvec.v[5] = (int32_t)v.v[5];
	outvec.v[6] = (int32_t)v.v[6];
	outvec.v[7] = (int32_t)v.v[7];
	return outvec;
}
vec8u16_t Vec8i64_ToVec8u16(vec8i64_t v)
{
	vec8u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	outvec.v[5] = (uint16_t)v.v[5];
	outvec.v[6] = (uint16_t)v.v[6];
	outvec.v[7] = (uint16_t)v.v[7];
	return outvec;
}
vec8i16_t Vec8i64_ToVec8i16(vec8i64_t v)
{
	vec8i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	outvec.v[5] = (int16_t)v.v[5];
	outvec.v[6] = (int16_t)v.v[6];
	outvec.v[7] = (int16_t)v.v[7];
	return outvec;
}
vec8u8_t Vec8i64_ToVec8u8(vec8i64_t v)
{
	vec8u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	outvec.v[5] = (uint8_t)v.v[5];
	outvec.v[6] = (uint8_t)v.v[6];
	outvec.v[7] = (uint8_t)v.v[7];
	return outvec;
}
vec8i8_t Vec8i64_ToVec8i8(vec8i64_t v)
{
	vec8i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	outvec.v[5] = (int8_t)v.v[5];
	outvec.v[6] = (int8_t)v.v[6];
	outvec.v[7] = (int8_t)v.v[7];
	return outvec;
}
vec8f64_t Vec8u32_ToVec8f64(vec8u32_t v)
{
	vec8f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	outvec.v[5] = (double)v.v[5];
	outvec.v[6] = (double)v.v[6];
	outvec.v[7] = (double)v.v[7];
	return outvec;
}
vec8f32_t Vec8u32_ToVec8f32(vec8u32_t v)
{
	vec8f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	outvec.v[5] = (float)v.v[5];
	outvec.v[6] = (float)v.v[6];
	outvec.v[7] = (float)v.v[7];
	return outvec;
}
vec8u64_t Vec8u32_ToVec8u64(vec8u32_t v)
{
	vec8u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	outvec.v[5] = (uint64_t)v.v[5];
	outvec.v[6] = (uint64_t)v.v[6];
	outvec.v[7] = (uint64_t)v.v[7];
	return outvec;
}
vec8i64_t Vec8u32_ToVec8i64(vec8u32_t v)
{
	vec8i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	outvec.v[5] = (int64_t)v.v[5];
	outvec.v[6] = (int64_t)v.v[6];
	outvec.v[7] = (int64_t)v.v[7];
	return outvec;
}
vec8i32_t Vec8u32_ToVec8i32(vec8u32_t v)
{
	vec8i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	outvec.v[5] = (int32_t)v.v[5];
	outvec.v[6] = (int32_t)v.v[6];
	outvec.v[7] = (int32_t)v.v[7];
	return outvec;
}
vec8u16_t Vec8u32_ToVec8u16(vec8u32_t v)
{
	vec8u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	outvec.v[5] = (uint16_t)v.v[5];
	outvec.v[6] = (uint16_t)v.v[6];
	outvec.v[7] = (uint16_t)v.v[7];
	return outvec;
}
vec8i16_t Vec8u32_ToVec8i16(vec8u32_t v)
{
	vec8i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	outvec.v[5] = (int16_t)v.v[5];
	outvec.v[6] = (int16_t)v.v[6];
	outvec.v[7] = (int16_t)v.v[7];
	return outvec;
}
vec8u8_t Vec8u32_ToVec8u8(vec8u32_t v)
{
	vec8u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	outvec.v[5] = (uint8_t)v.v[5];
	outvec.v[6] = (uint8_t)v.v[6];
	outvec.v[7] = (uint8_t)v.v[7];
	return outvec;
}
vec8i8_t Vec8u32_ToVec8i8(vec8u32_t v)
{
	vec8i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	outvec.v[5] = (int8_t)v.v[5];
	outvec.v[6] = (int8_t)v.v[6];
	outvec.v[7] = (int8_t)v.v[7];
	return outvec;
}
vec8f64_t Vec8i32_ToVec8f64(vec8i32_t v)
{
	vec8f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	outvec.v[5] = (double)v.v[5];
	outvec.v[6] = (double)v.v[6];
	outvec.v[7] = (double)v.v[7];
	return outvec;
}
vec8f32_t Vec8i32_ToVec8f32(vec8i32_t v)
{
	vec8f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	outvec.v[5] = (float)v.v[5];
	outvec.v[6] = (float)v.v[6];
	outvec.v[7] = (float)v.v[7];
	return outvec;
}
vec8u64_t Vec8i32_ToVec8u64(vec8i32_t v)
{
	vec8u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	outvec.v[5] = (uint64_t)v.v[5];
	outvec.v[6] = (uint64_t)v.v[6];
	outvec.v[7] = (uint64_t)v.v[7];
	return outvec;
}
vec8i64_t Vec8i32_ToVec8i64(vec8i32_t v)
{
	vec8i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	outvec.v[5] = (int64_t)v.v[5];
	outvec.v[6] = (int64_t)v.v[6];
	outvec.v[7] = (int64_t)v.v[7];
	return outvec;
}
vec8u32_t Vec8i32_ToVec8u32(vec8i32_t v)
{
	vec8u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	outvec.v[5] = (uint32_t)v.v[5];
	outvec.v[6] = (uint32_t)v.v[6];
	outvec.v[7] = (uint32_t)v.v[7];
	return outvec;
}
vec8u16_t Vec8i32_ToVec8u16(vec8i32_t v)
{
	vec8u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	outvec.v[5] = (uint16_t)v.v[5];
	outvec.v[6] = (uint16_t)v.v[6];
	outvec.v[7] = (uint16_t)v.v[7];
	return outvec;
}
vec8i16_t Vec8i32_ToVec8i16(vec8i32_t v)
{
	vec8i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	outvec.v[5] = (int16_t)v.v[5];
	outvec.v[6] = (int16_t)v.v[6];
	outvec.v[7] = (int16_t)v.v[7];
	return outvec;
}
vec8u8_t Vec8i32_ToVec8u8(vec8i32_t v)
{
	vec8u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	outvec.v[5] = (uint8_t)v.v[5];
	outvec.v[6] = (uint8_t)v.v[6];
	outvec.v[7] = (uint8_t)v.v[7];
	return outvec;
}
vec8i8_t Vec8i32_ToVec8i8(vec8i32_t v)
{
	vec8i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	outvec.v[5] = (int8_t)v.v[5];
	outvec.v[6] = (int8_t)v.v[6];
	outvec.v[7] = (int8_t)v.v[7];
	return outvec;
}
vec8f64_t Vec8u16_ToVec8f64(vec8u16_t v)
{
	vec8f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	outvec.v[5] = (double)v.v[5];
	outvec.v[6] = (double)v.v[6];
	outvec.v[7] = (double)v.v[7];
	return outvec;
}
vec8f32_t Vec8u16_ToVec8f32(vec8u16_t v)
{
	vec8f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	outvec.v[5] = (float)v.v[5];
	outvec.v[6] = (float)v.v[6];
	outvec.v[7] = (float)v.v[7];
	return outvec;
}
vec8u64_t Vec8u16_ToVec8u64(vec8u16_t v)
{
	vec8u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	outvec.v[5] = (uint64_t)v.v[5];
	outvec.v[6] = (uint64_t)v.v[6];
	outvec.v[7] = (uint64_t)v.v[7];
	return outvec;
}
vec8i64_t Vec8u16_ToVec8i64(vec8u16_t v)
{
	vec8i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	outvec.v[5] = (int64_t)v.v[5];
	outvec.v[6] = (int64_t)v.v[6];
	outvec.v[7] = (int64_t)v.v[7];
	return outvec;
}
vec8u32_t Vec8u16_ToVec8u32(vec8u16_t v)
{
	vec8u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	outvec.v[5] = (uint32_t)v.v[5];
	outvec.v[6] = (uint32_t)v.v[6];
	outvec.v[7] = (uint32_t)v.v[7];
	return outvec;
}
vec8i32_t Vec8u16_ToVec8i32(vec8u16_t v)
{
	vec8i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	outvec.v[5] = (int32_t)v.v[5];
	outvec.v[6] = (int32_t)v.v[6];
	outvec.v[7] = (int32_t)v.v[7];
	return outvec;
}
vec8i16_t Vec8u16_ToVec8i16(vec8u16_t v)
{
	vec8i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	outvec.v[5] = (int16_t)v.v[5];
	outvec.v[6] = (int16_t)v.v[6];
	outvec.v[7] = (int16_t)v.v[7];
	return outvec;
}
vec8u8_t Vec8u16_ToVec8u8(vec8u16_t v)
{
	vec8u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	outvec.v[5] = (uint8_t)v.v[5];
	outvec.v[6] = (uint8_t)v.v[6];
	outvec.v[7] = (uint8_t)v.v[7];
	return outvec;
}
vec8i8_t Vec8u16_ToVec8i8(vec8u16_t v)
{
	vec8i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	outvec.v[5] = (int8_t)v.v[5];
	outvec.v[6] = (int8_t)v.v[6];
	outvec.v[7] = (int8_t)v.v[7];
	return outvec;
}
vec8f64_t Vec8i16_ToVec8f64(vec8i16_t v)
{
	vec8f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	outvec.v[5] = (double)v.v[5];
	outvec.v[6] = (double)v.v[6];
	outvec.v[7] = (double)v.v[7];
	return outvec;
}
vec8f32_t Vec8i16_ToVec8f32(vec8i16_t v)
{
	vec8f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	outvec.v[5] = (float)v.v[5];
	outvec.v[6] = (float)v.v[6];
	outvec.v[7] = (float)v.v[7];
	return outvec;
}
vec8u64_t Vec8i16_ToVec8u64(vec8i16_t v)
{
	vec8u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	outvec.v[5] = (uint64_t)v.v[5];
	outvec.v[6] = (uint64_t)v.v[6];
	outvec.v[7] = (uint64_t)v.v[7];
	return outvec;
}
vec8i64_t Vec8i16_ToVec8i64(vec8i16_t v)
{
	vec8i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	outvec.v[5] = (int64_t)v.v[5];
	outvec.v[6] = (int64_t)v.v[6];
	outvec.v[7] = (int64_t)v.v[7];
	return outvec;
}
vec8u32_t Vec8i16_ToVec8u32(vec8i16_t v)
{
	vec8u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	outvec.v[5] = (uint32_t)v.v[5];
	outvec.v[6] = (uint32_t)v.v[6];
	outvec.v[7] = (uint32_t)v.v[7];
	return outvec;
}
vec8i32_t Vec8i16_ToVec8i32(vec8i16_t v)
{
	vec8i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	outvec.v[5] = (int32_t)v.v[5];
	outvec.v[6] = (int32_t)v.v[6];
	outvec.v[7] = (int32_t)v.v[7];
	return outvec;
}
vec8u16_t Vec8i16_ToVec8u16(vec8i16_t v)
{
	vec8u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	outvec.v[5] = (uint16_t)v.v[5];
	outvec.v[6] = (uint16_t)v.v[6];
	outvec.v[7] = (uint16_t)v.v[7];
	return outvec;
}
vec8u8_t Vec8i16_ToVec8u8(vec8i16_t v)
{
	vec8u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	outvec.v[5] = (uint8_t)v.v[5];
	outvec.v[6] = (uint8_t)v.v[6];
	outvec.v[7] = (uint8_t)v.v[7];
	return outvec;
}
vec8i8_t Vec8i16_ToVec8i8(vec8i16_t v)
{
	vec8i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	outvec.v[5] = (int8_t)v.v[5];
	outvec.v[6] = (int8_t)v.v[6];
	outvec.v[7] = (int8_t)v.v[7];
	return outvec;
}
vec8f64_t Vec8u8_ToVec8f64(vec8u8_t v)
{
	vec8f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	outvec.v[5] = (double)v.v[5];
	outvec.v[6] = (double)v.v[6];
	outvec.v[7] = (double)v.v[7];
	return outvec;
}
vec8f32_t Vec8u8_ToVec8f32(vec8u8_t v)
{
	vec8f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	outvec.v[5] = (float)v.v[5];
	outvec.v[6] = (float)v.v[6];
	outvec.v[7] = (float)v.v[7];
	return outvec;
}
vec8u64_t Vec8u8_ToVec8u64(vec8u8_t v)
{
	vec8u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	outvec.v[5] = (uint64_t)v.v[5];
	outvec.v[6] = (uint64_t)v.v[6];
	outvec.v[7] = (uint64_t)v.v[7];
	return outvec;
}
vec8i64_t Vec8u8_ToVec8i64(vec8u8_t v)
{
	vec8i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	outvec.v[5] = (int64_t)v.v[5];
	outvec.v[6] = (int64_t)v.v[6];
	outvec.v[7] = (int64_t)v.v[7];
	return outvec;
}
vec8u32_t Vec8u8_ToVec8u32(vec8u8_t v)
{
	vec8u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	outvec.v[5] = (uint32_t)v.v[5];
	outvec.v[6] = (uint32_t)v.v[6];
	outvec.v[7] = (uint32_t)v.v[7];
	return outvec;
}
vec8i32_t Vec8u8_ToVec8i32(vec8u8_t v)
{
	vec8i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	outvec.v[5] = (int32_t)v.v[5];
	outvec.v[6] = (int32_t)v.v[6];
	outvec.v[7] = (int32_t)v.v[7];
	return outvec;
}
vec8u16_t Vec8u8_ToVec8u16(vec8u8_t v)
{
	vec8u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	outvec.v[5] = (uint16_t)v.v[5];
	outvec.v[6] = (uint16_t)v.v[6];
	outvec.v[7] = (uint16_t)v.v[7];
	return outvec;
}
vec8i16_t Vec8u8_ToVec8i16(vec8u8_t v)
{
	vec8i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	outvec.v[5] = (int16_t)v.v[5];
	outvec.v[6] = (int16_t)v.v[6];
	outvec.v[7] = (int16_t)v.v[7];
	return outvec;
}
vec8i8_t Vec8u8_ToVec8i8(vec8u8_t v)
{
	vec8i8_t outvec;
	outvec.v[0] = (int8_t)v.v[0];
	outvec.v[1] = (int8_t)v.v[1];
	outvec.v[2] = (int8_t)v.v[2];
	outvec.v[3] = (int8_t)v.v[3];
	outvec.v[4] = (int8_t)v.v[4];
	outvec.v[5] = (int8_t)v.v[5];
	outvec.v[6] = (int8_t)v.v[6];
	outvec.v[7] = (int8_t)v.v[7];
	return outvec;
}
vec8f64_t Vec8i8_ToVec8f64(vec8i8_t v)
{
	vec8f64_t outvec;
	outvec.v[0] = (double)v.v[0];
	outvec.v[1] = (double)v.v[1];
	outvec.v[2] = (double)v.v[2];
	outvec.v[3] = (double)v.v[3];
	outvec.v[4] = (double)v.v[4];
	outvec.v[5] = (double)v.v[5];
	outvec.v[6] = (double)v.v[6];
	outvec.v[7] = (double)v.v[7];
	return outvec;
}
vec8f32_t Vec8i8_ToVec8f32(vec8i8_t v)
{
	vec8f32_t outvec;
	outvec.v[0] = (float)v.v[0];
	outvec.v[1] = (float)v.v[1];
	outvec.v[2] = (float)v.v[2];
	outvec.v[3] = (float)v.v[3];
	outvec.v[4] = (float)v.v[4];
	outvec.v[5] = (float)v.v[5];
	outvec.v[6] = (float)v.v[6];
	outvec.v[7] = (float)v.v[7];
	return outvec;
}
vec8u64_t Vec8i8_ToVec8u64(vec8i8_t v)
{
	vec8u64_t outvec;
	outvec.v[0] = (uint64_t)v.v[0];
	outvec.v[1] = (uint64_t)v.v[1];
	outvec.v[2] = (uint64_t)v.v[2];
	outvec.v[3] = (uint64_t)v.v[3];
	outvec.v[4] = (uint64_t)v.v[4];
	outvec.v[5] = (uint64_t)v.v[5];
	outvec.v[6] = (uint64_t)v.v[6];
	outvec.v[7] = (uint64_t)v.v[7];
	return outvec;
}
vec8i64_t Vec8i8_ToVec8i64(vec8i8_t v)
{
	vec8i64_t outvec;
	outvec.v[0] = (int64_t)v.v[0];
	outvec.v[1] = (int64_t)v.v[1];
	outvec.v[2] = (int64_t)v.v[2];
	outvec.v[3] = (int64_t)v.v[3];
	outvec.v[4] = (int64_t)v.v[4];
	outvec.v[5] = (int64_t)v.v[5];
	outvec.v[6] = (int64_t)v.v[6];
	outvec.v[7] = (int64_t)v.v[7];
	return outvec;
}
vec8u32_t Vec8i8_ToVec8u32(vec8i8_t v)
{
	vec8u32_t outvec;
	outvec.v[0] = (uint32_t)v.v[0];
	outvec.v[1] = (uint32_t)v.v[1];
	outvec.v[2] = (uint32_t)v.v[2];
	outvec.v[3] = (uint32_t)v.v[3];
	outvec.v[4] = (uint32_t)v.v[4];
	outvec.v[5] = (uint32_t)v.v[5];
	outvec.v[6] = (uint32_t)v.v[6];
	outvec.v[7] = (uint32_t)v.v[7];
	return outvec;
}
vec8i32_t Vec8i8_ToVec8i32(vec8i8_t v)
{
	vec8i32_t outvec;
	outvec.v[0] = (int32_t)v.v[0];
	outvec.v[1] = (int32_t)v.v[1];
	outvec.v[2] = (int32_t)v.v[2];
	outvec.v[3] = (int32_t)v.v[3];
	outvec.v[4] = (int32_t)v.v[4];
	outvec.v[5] = (int32_t)v.v[5];
	outvec.v[6] = (int32_t)v.v[6];
	outvec.v[7] = (int32_t)v.v[7];
	return outvec;
}
vec8u16_t Vec8i8_ToVec8u16(vec8i8_t v)
{
	vec8u16_t outvec;
	outvec.v[0] = (uint16_t)v.v[0];
	outvec.v[1] = (uint16_t)v.v[1];
	outvec.v[2] = (uint16_t)v.v[2];
	outvec.v[3] = (uint16_t)v.v[3];
	outvec.v[4] = (uint16_t)v.v[4];
	outvec.v[5] = (uint16_t)v.v[5];
	outvec.v[6] = (uint16_t)v.v[6];
	outvec.v[7] = (uint16_t)v.v[7];
	return outvec;
}
vec8i16_t Vec8i8_ToVec8i16(vec8i8_t v)
{
	vec8i16_t outvec;
	outvec.v[0] = (int16_t)v.v[0];
	outvec.v[1] = (int16_t)v.v[1];
	outvec.v[2] = (int16_t)v.v[2];
	outvec.v[3] = (int16_t)v.v[3];
	outvec.v[4] = (int16_t)v.v[4];
	outvec.v[5] = (int16_t)v.v[5];
	outvec.v[6] = (int16_t)v.v[6];
	outvec.v[7] = (int16_t)v.v[7];
	return outvec;
}
vec8u8_t Vec8i8_ToVec8u8(vec8i8_t v)
{
	vec8u8_t outvec;
	outvec.v[0] = (uint8_t)v.v[0];
	outvec.v[1] = (uint8_t)v.v[1];
	outvec.v[2] = (uint8_t)v.v[2];
	outvec.v[3] = (uint8_t)v.v[3];
	outvec.v[4] = (uint8_t)v.v[4];
	outvec.v[5] = (uint8_t)v.v[5];
	outvec.v[6] = (uint8_t)v.v[6];
	outvec.v[7] = (uint8_t)v.v[7];
	return outvec;
}
