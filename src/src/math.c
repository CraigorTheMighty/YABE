#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <complex.h>
#include <immintrin.h>
#include <omp.h>

#include "../inc/math.h"
#include "../inc/memory.h"

#define USE_BUILTIN_FUNCTIONS

#ifdef USE_BUILTIN_FUNCTIONS

#define LZCNT8(x)	return (int)__lzcnt16((uint16_t)x);
#define LZCNT16(x)	return (int)__lzcnt16(x);
#define LZCNT32(x)	return (int)__lzcnt(x);
#define LZCNT64(x)	return (int)__lzcnt64(x);

#define POPCNT8(x)	return (int)__popcnt16((uint16_t)x);
#define POPCNT16(x)	return (int)__popcnt16(x);
#define POPCNT32(x)	return (int)__popcnt(x);
#define POPCNT64(x)	return (int)__popcnt64(x);

#define ROTL8(x, shift)		(x << shift) | (x >> (8 - shift))
#define ROTL16(x, shift)	(x << shift) | (x >> (16 - shift))
#define ROTL32(x, shift)	_rotl(x, shift)
#define ROTL64(x, shift)	_rotl64(x, shift)

#else

#define POPCNT8(x)	x = (x & 0x55) + ((x & 0xAA) >> 1);\
					x = (x & 0x33) + ((x & 0xCC) >> 2);\
					x = (x & 0x0F) + ((x & 0xF0) >> 4);\
					return (int)x;

#define POPCNT16(x)	x = (x & 0x5555) + ((x & 0xAAAA) >> 1);\
					x = (x & 0x3333) + ((x & 0xCCCC) >> 2);\
					x = (x & 0x0F0F) + ((x & 0xF0F0) >> 4);\
					x = (x & 0x00FF) + ((x & 0xFF00) >> 8);\
					return (int)x;

#define POPCNT32(x)	x = (x & 0x55555555) + ((x & 0xAAAAAAAA) >> 1);\
					x = (x & 0x33333333) + ((x & 0xCCCCCCCC) >> 2);\
					x = (x & 0x0F0F0F0F) + ((x & 0xF0F0F0F0) >> 4);\
					x = (x & 0x00FF00FF) + ((x & 0xFF00FF00) >> 8);\
					x = (x & 0x0000FFFF) + ((x & 0xFFFF0000) >> 16);\
					return (int)x;

#define POPCNT64(x)	x = (x & 0x5555555555555555ULL) + ((x & 0xAAAAAAAAAAAAAAAAULL) >> 1);\
					x = (x & 0x3333333333333333ULL) + ((x & 0xCCCCCCCCCCCCCCCCULL) >> 2);\
					x = (x & 0x0F0F0F0F0F0F0F0FULL) + ((x & 0xF0F0F0F0F0F0F0F0ULL) >> 4);\
					x = (x & 0x00FF00FF00FF00FFULL) + ((x & 0xFF00FF00FF00FF00ULL) >> 8);\
					x = (x & 0x0000FFFF0000FFFFULL) + ((x & 0xFFFF0000FFFF0000ULL) >> 16);\
					x = (x & 0x00000000FFFFFFFFULL) + ((x & 0xFFFFFFFF00000000ULL) >> 32);\
					return (int)x;

#define LZCNT8(x)	x = x | (x >> 1);\
				    x = x | (x >> 2);\
					x = x | (x >> 4);\
					return 8 - Math_PopCnt8(x);

#define LZCNT16(x)	x = x | (x >> 1);\
				    x = x | (x >> 2);\
					x = x | (x >> 4);\
					x = x | (x >> 8);\
					return 16 - Math_PopCnt16(x);

#define LZCNT32(x)	x = x | (x >> 1);\
				    x = x | (x >> 2);\
					x = x | (x >> 4);\
					x = x | (x >> 8);\
					x = x | (x >> 16);\
					return 32 - Math_PopCnt32(x);

#define LZCNT64(x)	x = x | (x >> 1);\
				    x = x | (x >> 2);\
					x = x | (x >> 4);\
					x = x | (x >> 8);\
					x = x | (x >> 16);\
					x = x | (x >> 32);\
					return 64 - Math_PopCnt64(x);

#define ROTL8(x, shift)		(x << shift) | (x >> (8 - shift))
#define ROTL16(x, shift)	(x << shift) | (x >> (16 - shift))
#define ROTL32(x, shift)	(x << shift) | (x >> (32 - shift))
#define ROTL64(x, shift)	(x << shift) | (x >> (64 - shift))

#endif

uint8_t Math_SignExtendu8(uint8_t x, int bits)
{
	uint8_t mask;

	if (bits == 8)
		return x;

	mask = 1 << (bits - 1);

	if (x & mask)
		x |= ~(mask - 1);

	return x;
}
uint16_t Math_SignExtendu16(uint16_t x, int bits)
{
	uint16_t mask;

	if (bits == 16)
		return x;

	mask = 1 << (bits - 1);

	if (x & mask)
		x |= ~(mask - 1);

	return x;
}
uint32_t Math_SignExtendu32(uint32_t x, int bits)
{
	uint32_t mask;

	if (bits == 32)
		return x;

	mask = 1 << (bits - 1);

	if (x & mask)
		x |= ~(mask - 1);

	return x;
}
uint64_t Math_SignExtendu64(uint64_t x, int bits)
{
	uint64_t mask;

	if (bits == 64)
		return x;

	mask = 1ULL << (bits - 1);

	if (x & mask)
		x |= ~(mask - 1);

	return x;
}
int8_t Math_SignExtendi8(int8_t x, int bits)
{
	uint8_t mask;

	if (bits == 8)
		return x;

	mask = 1 << (bits - 1);

	if (x & mask)
		x |= ~(mask - 1);

	return x;
}
int16_t Math_SignExtendi16(int16_t x, int bits)
{
	uint16_t mask;

	if (bits == 16)
		return x;

	mask = 1 << (bits - 1);

	if (x & mask)
		x |= ~(mask - 1);

	return x;
}
int32_t Math_SignExtendi32(int32_t x, int bits)
{
	uint32_t mask;

	if (bits == 32)
		return x;

	mask = 1 << (bits - 1);

	if (x & mask)
		x |= ~(mask - 1);

	return x;
}
int64_t Math_SignExtendi64(int64_t x, int bits)
{
	uint64_t mask;

	if (bits == 64)
		return x;

	mask = 1ULL << (bits - 1);

	if (x & mask)
		x |= ~(mask - 1);

	return x;
}


uint8_t Math_CeilPow2u8(uint8_t x)
{
	x--;
	x = x | (x >> 1);
	x = x | (x >> 2);
	x = x | (x >> 4);
	x++;

	return x;
}
uint16_t Math_CeilPow2u16(uint16_t x)
{
	x--;
	x = x | (x >> 1);
	x = x | (x >> 2);
	x = x | (x >> 4);
	x = x | (x >> 8);
	x++;

	return x;
}
uint32_t Math_CeilPow2u32(uint32_t x)
{
	x--;
	x = x | (x >> 1);
	x = x | (x >> 2);
	x = x | (x >> 4);
	x = x | (x >> 8);
	x = x | (x >> 16);
	x++;

	return x;
}
uint64_t Math_CeilPow2u64(uint64_t x)
{
	x--;
	x = x | (x >> 1);
	x = x | (x >> 2);
	x = x | (x >> 4);
	x = x | (x >> 8);
	x = x | (x >> 16);
	x = x | (x >> 32);
	x++;

	return x;
}
uint8_t Math_FloorPow2u8(uint8_t x)
{
	x = x | (x >> 1);
	x = x | (x >> 2);
	x = x | (x >> 4);

	return x - (x >> 1);
}
uint16_t Math_FloorPow2u16(uint16_t x)
{
	x = x | (x >> 1);
	x = x | (x >> 2);
	x = x | (x >> 4);
	x = x | (x >> 8);

	return x - (x >> 1);
}
uint32_t Math_FloorPow2u32(uint32_t x)
{
	x = x | (x >> 1);
	x = x | (x >> 2);
	x = x | (x >> 4);
	x = x | (x >> 8);
	x = x | (x >> 16);

	return x - (x >> 1);
}
uint64_t Math_FloorPow2u64(uint64_t x)
{
	x = x | (x >> 1);
	x = x | (x >> 2);
	x = x | (x >> 4);
	x = x | (x >> 8);
	x = x | (x >> 16);
	x = x | (x >> 32);

	return x - (x >> 1);
}

int Math_PopCnt8(uint8_t x)
{
	POPCNT8(x);
}
int Math_PopCnt16(uint16_t x)
{
	POPCNT16(x);
}
int Math_PopCnt32(uint32_t x)
{
	POPCNT32(x);
}
int Math_PopCnt64(uint64_t x)
{
	POPCNT64(x);
}


int Math_LZCnt8(uint8_t x)
{
	LZCNT8(x);
}
int Math_LZCnt16(uint16_t x)
{
	LZCNT16(x);
}
int Math_LZCnt32(uint32_t x)
{
	LZCNT32(x);
}
int Math_LZCnt64(uint64_t x)
{
	LZCNT64(x);
}

int Math_FloorLog2u8(uint8_t x)
{
	return 7 - Math_LZCnt8(x);
}
int Math_FloorLog2u16(uint16_t x)
{
	return 15 - Math_LZCnt16(x);
}
int Math_FloorLog2u32(uint32_t x)
{
	return 31 - Math_LZCnt32(x);
}
int Math_FloorLog2u64(uint64_t x)
{
	return 63 - Math_LZCnt64(x);
}

int Math_CeilLog2u8(uint8_t x)
{
	return 7 - Math_LZCnt8(x) + (IS_POW2(x) ? 0 : 1);
}
int Math_CeilLog2u16(uint16_t x)
{
	return 15 - Math_LZCnt16(x) + (IS_POW2(x) ? 0 : 1);
}
int Math_CeilLog2u32(uint32_t x)
{
	return 31 - Math_LZCnt32(x) + (IS_POW2(x) ? 0 : 1);
}
int Math_CeilLog2u64(uint64_t x)
{
	return 63 - Math_LZCnt64(x) + (IS_POW2(x) ? 0 : 1);
}

uint64_t Math_RotL64(uint64_t x, int shift)
{
	return ROTL64(x, shift);
}
uint32_t Math_RotL32(uint32_t x, int shift)
{
	return ROTL32(x, shift);
}
uint16_t Math_RotL16(uint16_t x, int shift)
{
	return ROTL16(x, shift);
}
uint8_t Math_RotL8(uint8_t x, int shift)
{
	return ROTL8(x, shift);
}

double Math_Minf64(double x, double y)
{
	return x < y ? x : y;
}
double Math_Maxf64(double x, double y)
{
	return x > y ? x : y;
}
double Math_Clampf64(double x, double min, double max)
{
	return Math_Minf64(Math_Maxf64(x, min), max);
}
double Math_Lerpf64(double a, double b, double t)
{
	return (1.0 - t)*a + b*t;
}

float Math_Minf32(float x, float y)
{
	return x < y ? x : y;
}
float Math_Maxf32(float x, float y)
{
	return x > y ? x : y;
}
float Math_Clampf32(float x, float min, float max)
{
	return Math_Minf32(Math_Maxf32(x, min), max);
}
float Math_Lerpf32(float a, float b, float t)
{
	return (1.0f - t)*a + b*t;
}

int64_t Math_Mini64(int64_t x, int64_t y)
{
	return x < y ? x : y;
}
int64_t Math_Maxi64(int64_t x, int64_t y)
{
	return x > y ? x : y;
}
int64_t Math_Clampi64(int64_t x, int64_t min, int64_t max)
{
	return Math_Mini64(Math_Maxi64(x, min), max);
}
int32_t Math_Mini32(int32_t x, int32_t y)
{
	return x < y ? x : y;
}
int32_t Math_Maxi32(int32_t x, int32_t y)
{
	return x > y ? x : y;
}
int32_t Math_Clampi32(int32_t x, int32_t min, int32_t max)
{
	return Math_Mini32(Math_Maxi32(x, min), max);
}
int16_t Math_Mini16(int16_t x, int16_t y)
{
	return x < y ? x : y;
}
int16_t Math_Maxi16(int16_t x, int16_t y)
{
	return x > y ? x : y;
}
int16_t Math_Clampi16(int16_t x, int16_t min, int16_t max)
{
	return Math_Mini16(Math_Maxi16(x, min), max);
}
int8_t Math_Mini8(int8_t x, int8_t y)
{
	return x < y ? x : y;
}
int8_t Math_Maxi8(int8_t x, int8_t y)
{
	return x > y ? x : y;
}
int8_t Math_Clampi8(int8_t x, int8_t min, int8_t max)
{
	return Math_Mini8(Math_Maxi8(x, min), max);
}

uint64_t Math_Minu64(uint64_t x, uint64_t y)
{
	return x < y ? x : y;
}
uint64_t Math_Maxu64(uint64_t x, uint64_t y)
{
	return x > y ? x : y;
}
uint64_t Math_Clampu64(uint64_t x, uint64_t min, uint64_t max)
{
	return Math_Minu64(Math_Maxu64(x, min), max);
}
uint32_t Math_Minu32(uint32_t x, uint32_t y)
{
	return x < y ? x : y;
}
uint32_t Math_Maxu32(uint32_t x, uint32_t y)
{
	return x > y ? x : y;
}
uint32_t Math_Clampu32(uint32_t x, uint32_t min, uint32_t max)
{
	return Math_Minu32(Math_Maxu32(x, min), max);
}
uint16_t Math_Minu16(uint16_t x, uint16_t y)
{
	return x < y ? x : y;
}
uint16_t Math_Maxu16(uint16_t x, uint16_t y)
{
	return x > y ? x : y;
}
uint16_t Math_Clampu16(uint16_t x, uint16_t min, uint16_t max)
{
	return Math_Minu16(Math_Maxu16(x, min), max);
}
uint8_t Math_Minu8(uint8_t x, uint8_t y)
{
	return x < y ? x : y;
}
uint8_t Math_Maxu8(uint8_t x, uint8_t y)
{
	return x > y ? x : y;
}
uint8_t Math_Clampu8(uint8_t x, uint8_t min, uint8_t max)
{
	return Math_Minu8(Math_Maxu8(x, min), max);
}
uint64_t Math_Binomial(int n, int k)
{
	uint64_t ans = 1;
	int j;

	k = k > n - k ? n - k : k;

	for (j = 1; j <= k; j++, n--)
	{
		if(n % j == 0)
			ans *= n / j;
		else if (ans % j == 0)
			ans = (ans / j) * n;
		else
			ans = (ans * n) / j;
	}
	return ans;
}
double Math_GeometricLimitf64(double base, int n)
{
	if (base == 1.0)
		return n * base;
	else
		return (pow(base, 1.0 + (double)n) - 1.0) / (base - 1.0);
}
float Math_GeometricLimitf32(float base, int n)
{
	if (base == 1.0f)
		return n * base;
	else
		return (powf(base, 1.0f + (float)n) - 1.0f) / (base - 1.0f);
}

#define STOP 1.0e-8
#define TINY 1.0e-30

double Math_IncompleteBeta(double x, double a, double b) 
{
	if (x < 0.0 || x > 1.0)
		return -1.0;

	if (x > ( a + 1.0) / (a + b + 2.0)) 
		return (1.0 - Math_IncompleteBeta(1.0 - x, b, a));

	const double lbeta_ab = lgamma(a) + lgamma(b) - lgamma(a + b);
	const double front = exp(log(x) * a + log(1.0 - x) * b - lbeta_ab) / a;

	double f = 1.0, c = 1.0, d = 0.0;

	int i, m;

	for (i = 0; i <= 200; ++i) 
	{
		m = i/2;

		double numerator;

		if (i == 0)
			numerator = 1.0; /*First numerator is 1.0.*/
		else if (i % 2 == 0)
			numerator = (m*(b-m)*x)/((a+2.0*m-1.0)*(a+2.0*m)); /*Even term.*/
		else
			numerator = -((a+m)*(a+b+m)*x)/((a+2.0*m)*(a+2.0*m+1)); /*Odd term.*/

		d = 1.0 + numerator * d;
		if (fabs(d) < TINY) 
			d = TINY;
		d = 1.0 / d;

		c = 1.0 + numerator / c;

		if (fabs(c) < TINY) 
			c = TINY;

		const double cd = c * d;

		f *= cd;

		if (fabs(1.0 - cd) < STOP)
			return front * (f - 1.0);
	}

	return -1.0; /*Needed more loops, did not converge.*/
}

_Fcomplex Math_ComplexAddF(_Fcomplex x, _Fcomplex y)
{
	x._Val[0] += y._Val[0];
	x._Val[1] += y._Val[1];

	return x;
}
_Fcomplex Math_ComplexSubF(_Fcomplex x, _Fcomplex y)
{
	x._Val[0] -= y._Val[0];
	x._Val[1] -= y._Val[1];

	return x;
}
_Fcomplex Math_ComplexMulF(_Fcomplex x, _Fcomplex y)
{
	return _FCmulcc(x, y);
}
_Fcomplex Math_ComplexMulRealF(float x, _Fcomplex y)
{
	return _FCmulcr(y, x);
}
_Fcomplex Math_ComplexFromRealF(float x)
{
	return _FCbuild(x, 0.0f);
}
float Math_ComplexAbsF(_Fcomplex x)
{
	return sqrtf(x._Val[0]*x._Val[0] + x._Val[1]*x._Val[1]);
}
float Math_ComplexAbsSqF(_Fcomplex x)
{
	return (x._Val[0]*x._Val[0] + x._Val[1]*x._Val[1]);
}
_Fcomplex Math_ComplexCbrtF(_Fcomplex x, int root)
{
	const _Fcomplex rotate = {-0.5f, M_SQRT3_DIV2_F};
	const _Fcomplex cpw = {1.0f / 3.0f, 0.0f};

	return Math_ComplexMulF(cpowf(x, cpw), cpowf(rotate, Math_ComplexFromRealF((float)root)));
}

/*
int n = 3;
const double complex two_pi_i = 2.0 * asin(-1.0) * I;
double complex rotate = cexp(two_pi_i / n);
x = cpow(z, 1.0 / n);
for (int k = 0; k < n; k++) 
{
printf("x[%d] is % f + % fi \n", k, creal(x), cimag(x));
x *= rotate;
}
*/


static size_t revbits(size_t v, int J)
{
	size_t r = 0;

	for(int j = 0; j < J; j++) 
		r |= ((v >> j) & 1) << (J - 1 - j);

	return r;
}

static void nop_split_freq(const _Fcomplex *x, _Fcomplex *X, size_t N, int stride)
{
	for(size_t n = 0; n < N/2; n++) 
	{
		X[(2*n+0)*stride] = x[(0/2+n)*stride];
		X[(2*n+1)*stride] = x[(N/2+n)*stride];
	}
}

static void fft_split_freq(const _Fcomplex *x, _Fcomplex *X, size_t N, _Fcomplex phi, float mul, int stride)
{
	_Fcomplex inner = Math_ComplexFromRealF(2*(float)M_PI);
	_Fcomplex c_expc = cexpf(Math_ComplexMulF(inner, Math_ComplexMulF(phi, I)));

	for(size_t n = 0; n < N/2; n++) 
	{
		_Fcomplex x0 = x[(0/2+n)*stride];
		_Fcomplex x1 = x[(N/2+n)*stride];

		X[(2*n+0)*stride] = Math_ComplexMulRealF(mul, Math_ComplexAddF(x0, x1));
		X[(2*n+1)*stride] = Math_ComplexMulF(Math_ComplexMulRealF(mul, Math_ComplexSubF(x0, x1)), c_expc);
	}
}

static int nop_reverse_freq(int b, _Fcomplex *buffers[2], size_t N, int stride)
{
	int J = Math_FloorLog2u32((uint32_t)N);

	for(int j = J-2; j >= 0; j--, b++) 
	{
		size_t delta = N>>j;

		for(size_t n = 0; n < N; n += delta) 
			nop_split_freq(buffers[b&1] + n * stride, buffers[~b&1] + n * stride, delta, stride);
	}

	return b;
}

static int fft_reverse_freq(int b, _Fcomplex *buffers[2], size_t N, float mul, int stride)
{
	int J = Math_FloorLog2u32((uint32_t)N);

	for(int j = J-1; j >= 0; j--, b++) 
	{
		size_t delta = N>>j;

		for(size_t n = 0; n < N; n += delta) 
		{
			_Fcomplex phi = Math_ComplexFromRealF((float)revbits(n/delta, j) / (float)(2 << j));
			fft_split_freq(buffers[b&1] + n * stride, buffers[~b&1] + n * stride, delta, phi, mul, stride);
		}
	}

	return b;
}

static void Math_FFT_Frequency_Internal(_Fcomplex *vector, _Fcomplex *temp_buffer, size_t N, float scale, int stride)
{
	int i;
	_Fcomplex *buffers[2] = {vector, temp_buffer};

	int b = 0;

	b = nop_reverse_freq(b, buffers, N, stride);
	b = fft_reverse_freq(b, buffers, N, scale, stride);
	b = nop_reverse_freq(b, buffers, N, stride);

	if ((b & 1))
		for (i = 0; i < N; i++)
			vector[i*stride] = temp_buffer[i*stride];
}


int Math_FFT_Frequency(_Fcomplex *vector, size_t N)
{
	_Fcomplex *temp_buffer = Mem_Malloc(N * sizeof(_Fcomplex));

	if (!N) 
		return 0;
	if (N & (N-1)) 
		return 1;
	if (!temp_buffer)
		return -1;

	Math_FFT_Frequency_Internal(vector, temp_buffer, N, 1.0f, 1);

	Mem_Free(temp_buffer);

	return 0;
}

static void Math_IFFT_Frequency_Internal(_Fcomplex *vector, _Fcomplex *temp_buffer, size_t N, int stride)
{
	size_t i;

	Math_FFT_Frequency_Internal(vector, temp_buffer, N, 0.5f, stride);

	for (i = 0; i < N; i++)
		temp_buffer[i*stride] = vector[i*stride];

	vector[0] = temp_buffer[0];
	for (i = N - 1; i > 0; i--)
		vector[(N - i)*stride] = temp_buffer[i*stride];
}

int Math_IFFT_Frequency(_Fcomplex *vector, size_t N)
{
	_Fcomplex *temp_buffer = Mem_Malloc(N * sizeof(_Fcomplex));

	if (!N) 
		return 0;
	if (N & (N-1)) 
		return 1;
	if (!temp_buffer)
		return -1;

	Math_IFFT_Frequency_Internal(vector, temp_buffer, N, 1);

	Mem_Free(temp_buffer);

	return 0;
}

int Math_FFT_FrequencyR(_Fcomplex *vector_out, float *vector_in, size_t N)
{
	int i;

	for (i = 0; i < N; i++)
		vector_out[i] = Math_ComplexFromRealF(vector_in[i]);

	return Math_FFT_Frequency(vector_out, N);
}


int Math_FFT_FrequencyR2D(_Fcomplex *vector_out, float *vector_in, size_t N, int max_threads)
{
	int i;
	_Fcomplex *temp = Mem_Malloc(N*N*sizeof(_Fcomplex)); // TODO: this only needs N entries, not N*N
	int n_threads = max_threads == 0 ? omp_get_max_threads() : max_threads;

	if (!N) 
		return 0;
	if (N & (N - 1)) 
		return 1;
	if (!temp) 
		return -1;

	for (i = 0; i < N*N; i++)
		vector_out[i] = Math_ComplexFromRealF(vector_in[i]);
#pragma omp parallel for num_threads(n_threads)
	for (i = 0; i < N; i++)
		Math_FFT_Frequency_Internal(&vector_out[N*i], &temp[N*i], N, 1.0f, 1);
#pragma omp parallel for num_threads(n_threads)
	for (i = 0; i < N; i++)
		Math_FFT_Frequency_Internal(&vector_out[i], &temp[i], N, 1.0f, (int)N);

	Mem_Free(temp);

	return 0;
}
int Math_IFFT_Frequency2D(_Fcomplex *vector, size_t N, int max_threads)
{
	int i;
	_Fcomplex *temp = Mem_Malloc(N*N*sizeof(_Fcomplex)); // TODO: this only needs N entries, not N*N
	int n_threads = max_threads == 0 ? omp_get_max_threads() : max_threads;

	if (!N) 
		return 0;
	if (N & (N - 1)) 
		return 1;
	if (!temp) 
		return -1;

#pragma omp parallel for num_threads(n_threads)
	for (i = 0; i < N; i++)
		Math_IFFT_Frequency_Internal(&vector[i], &temp[i], N, (int)N);
#pragma omp parallel for num_threads(n_threads)
	for (i = 0; i < N; i++)
		Math_IFFT_Frequency_Internal(&vector[N*i], &temp[N*i], N, 1);

	Mem_Free(temp);

	return 0;
}
static _Fcomplex Math_EvaluateQuartic(_Fcomplex t, float a, float b, float c, float d, float e, float f)
{
	_Fcomplex res[5];

	res[0] = Math_ComplexMulRealF(a, cpowf(t, Math_ComplexFromRealF(4.0f)));
	res[1] = Math_ComplexMulRealF(b, cpowf(t, Math_ComplexFromRealF(3.0f)));
	res[2] = Math_ComplexMulRealF(c, cpowf(t, Math_ComplexFromRealF(2.0f)));
	res[3] = Math_ComplexMulRealF(d, cpowf(t, Math_ComplexFromRealF(1.0f)));
	res[4] = Math_ComplexFromRealF(e - f);

	res[0] = Math_ComplexAddF(res[0], res[1]);
	res[0] = Math_ComplexAddF(res[0], res[2]);
	res[0] = Math_ComplexAddF(res[0], res[3]);
	res[0] = Math_ComplexAddF(res[0], res[4]);

	return res[0];
}
void Math_PolynomialDeg4Solvef32(float *real_roots, _Fcomplex *complex_roots, int *num_real_roots, int *num_complex_roots, float a, float b, float c, float d, float e, float f)
{
	if (a == 0.0f)
		Math_PolynomialDeg3Solvef32(real_roots, complex_roots, num_real_roots, num_complex_roots, b, c, d, e, f);
	else if (e == f)
	{
		Math_PolynomialDeg3Solvef32(real_roots, complex_roots, num_real_roots, num_complex_roots, a, b, c, d, 0.0f);
		(*num_real_roots)++;
		real_roots[*num_real_roots - 1] = 0.0f;
	}
	else if (b == 0.0f && c == 0.0f && d == 0.0f && e == f)
	{
		*num_real_roots = 4;

		real_roots[0] = 0.0f;
		real_roots[1] = 0.0f;
		real_roots[2] = 0.0f;
		real_roots[3] = 0.0f;
	}
	else if (b == 0.0f && c == 0.0f && d == 0.0f)
	{
		if (e - f > 0.0f)
		{
			*num_complex_roots = 4;
			complex_roots[0] = _FCbuild(powf(e - f, 0.25f) / M_SQRT2_F, powf(e - f, 0.25f) / M_SQRT2_F);
			complex_roots[1] = _FCbuild(-powf(e - f, 0.25f) / M_SQRT2_F, powf(e - f, 0.25f) / M_SQRT2_F);
			complex_roots[2] = _FCbuild(powf(e - f, 0.25f) / M_SQRT2_F, -powf(e - f, 0.25f) / M_SQRT2_F);
			complex_roots[3] = _FCbuild(-powf(e - f, 0.25f) / M_SQRT2_F, -powf(e - f, 0.25f) / M_SQRT2_F);
			//for (int i = 0; i < 4; i++)
			//	_cprintf("R %i: %f %fI\n", i, complex_roots[i]._Val[0], complex_roots[i]._Val[1]);
		}
		else
		{
			*num_real_roots = 2;
			*num_complex_roots = 2;

			real_roots[0] = powf(f - e, 0.25f);
			real_roots[1] = -powf(f - e, 0.25f);

			complex_roots[0] = _FCbuild(0.0f, powf(f - e, 0.25f));
			complex_roots[1] = _FCbuild(0.0f, -powf(f - e, 0.25f));

			/*
			for (int i = 0; i < 2; i++)
			_cprintf("R %i: %f\n", i, real_roots[i]);
			for (int i = 0; i < 2; i++)
			_cprintf("R %i: %f %fI\n", i + 2, complex_roots[i]._Val[0], complex_roots[i]._Val[1]);
			*/
		}
	}
	else
	{
		int i;
		float p;
		float q;
		float r;
		float offset;
		int s_r_roots_num;
		int s_c_roots_num;
		float s_r_roots[3];
		_Fcomplex s_c_roots[3];
		_Fcomplex c_res_roots[3];
		_Fcomplex x;
		_Fcomplex y;
		_Fcomplex z;
		_Fcomplex iroot[4];
		float mul = -0.5f;
		/*_Fcomplex res[2][4];
		float sqerr[2];
		float coeff[6];

		coeff[0] = a;
		coeff[1] = b;
		coeff[2] = c;
		coeff[3] = d;
		coeff[4] = e;
		coeff[5] = f;
		*/
		offset = b/(4.0f * a);

		b /= a;
		c /= a;
		d /= a;
		e = (e - f) / a;

		p = (8.0f*c - 3.0f*b*b)/8.0f;
		q = (b*b*b - 4.0f*b*c + 8.0f*d)/8.0f;
		r = (-3.0f*b*b*b*b + 256.0f*e - 64.0f*b*d + 16.0f*b*b*c)/256.0f;

		// TODO: if q == 0, this is automatically handled by the degree 3 solver

		Math_PolynomialDeg3Solvef32(s_r_roots, s_c_roots, &s_r_roots_num, &s_c_roots_num, 1, 2.0f*p, p*p - 4.0f*r, -q*q, 0.0f);

		// Euler's method

		// s_r_roots_num + s_c_roots_num == 3
		for (i = 0; i < s_r_roots_num; i++)
			c_res_roots[i] = Math_ComplexFromRealF(s_r_roots[i]);
		for (i = 0; i < s_c_roots_num; i++)
			c_res_roots[i + s_r_roots_num] = s_c_roots[i];

		x = csqrtf(c_res_roots[0]);
		y = csqrtf(c_res_roots[1]);
		z = csqrtf(c_res_roots[2]);

		// if (x*y*z == -q)

		if (fabsf(Math_ComplexMulF(Math_ComplexMulF(x, y), z)._Val[0] + q) < fabsf(Math_ComplexMulF(Math_ComplexMulF(x, y), z)._Val[0] - q))
			mul = 0.5f;
		else
			mul = -0.5f;

		iroot[0] = Math_ComplexSubF(Math_ComplexMulRealF(mul, Math_ComplexAddF(Math_ComplexAddF(x, y), z)), Math_ComplexFromRealF(offset));
		iroot[1] = Math_ComplexSubF(Math_ComplexMulRealF(mul, Math_ComplexSubF(Math_ComplexSubF(x, y), z)), Math_ComplexFromRealF(offset));
		iroot[2] = Math_ComplexSubF(Math_ComplexMulRealF(mul, Math_ComplexSubF(Math_ComplexSubF(y, x), z)), Math_ComplexFromRealF(offset));
		iroot[3] = Math_ComplexSubF(Math_ComplexMulRealF(mul, Math_ComplexSubF(z, Math_ComplexAddF(x, y))), Math_ComplexFromRealF(offset));

		//for (i = 0; i < 4; i++)
		//	_cprintf("R %i: %f %fI\n", i, iroot[i]._Val[0], iroot[i]._Val[1]);

		/*
		res[0][0] = Math_EvaluateQuartic(iroot[0], coeff[0], coeff[1], coeff[2], coeff[3], coeff[4], coeff[5]);
		res[0][1] = Math_EvaluateQuartic(iroot[1], coeff[0], coeff[1], coeff[2], coeff[3], coeff[4], coeff[5]);
		res[0][2] = Math_EvaluateQuartic(iroot[2], coeff[0], coeff[1], coeff[2], coeff[3], coeff[4], coeff[5]);
		res[0][3] = Math_EvaluateQuartic(iroot[3], coeff[0], coeff[1], coeff[2], coeff[3], coeff[4], coeff[5]);

		res[1][0] = Math_EvaluateQuartic(Math_ComplexMulRealF(-1.0f, iroot[0]), coeff[0], coeff[1], coeff[2], coeff[3], coeff[4], coeff[5]);
		res[1][1] = Math_EvaluateQuartic(Math_ComplexMulRealF(-1.0f, iroot[1]), coeff[0], coeff[1], coeff[2], coeff[3], coeff[4], coeff[5]);
		res[1][2] = Math_EvaluateQuartic(Math_ComplexMulRealF(-1.0f, iroot[2]), coeff[0], coeff[1], coeff[2], coeff[3], coeff[4], coeff[5]);
		res[1][3] = Math_EvaluateQuartic(Math_ComplexMulRealF(-1.0f, iroot[3]), coeff[0], coeff[1], coeff[2], coeff[3], coeff[4], coeff[5]);

		sqerr[0] = Math_ComplexAbsF(res[0][0]) + Math_ComplexAbsF(res[0][1]) + Math_ComplexAbsF(res[0][2]) + Math_ComplexAbsF(res[0][3]);
		sqerr[1] = Math_ComplexAbsF(res[1][0]) + Math_ComplexAbsF(res[1][1]) + Math_ComplexAbsF(res[1][2]) + Math_ComplexAbsF(res[1][3]);

		_cprintf("sq err: %f %f\n", sqerr[0], sqerr[1]);

		for (i = 0; i < 4; i++)
		_cprintf("R %i: %f %fI\n", i, iroot[i]._Val[0], iroot[i]._Val[1]);

		if (sqerr[1] < sqerr[0])
		{
		iroot[0] = Math_ComplexMulRealF(-1.0f, iroot[0]);
		iroot[1] = Math_ComplexMulRealF(-1.0f, iroot[1]);
		iroot[2] = Math_ComplexMulRealF(-1.0f, iroot[2]);
		iroot[3] = Math_ComplexMulRealF(-1.0f, iroot[3]);
		}

		res[0][0] = Math_EvaluateQuartic(iroot[0], coeff[0], coeff[1], coeff[2], coeff[3], coeff[4], coeff[5]);
		res[0][1] = Math_EvaluateQuartic(iroot[1], coeff[0], coeff[1], coeff[2], coeff[3], coeff[4], coeff[5]);
		res[0][2] = Math_EvaluateQuartic(iroot[2], coeff[0], coeff[1], coeff[2], coeff[3], coeff[4], coeff[5]);
		res[0][3] = Math_EvaluateQuartic(iroot[3], coeff[0], coeff[1], coeff[2], coeff[3], coeff[4], coeff[5]);

		sqerr[0] = Math_ComplexAbsF(res[0][0]) + Math_ComplexAbsF(res[0][1]) + Math_ComplexAbsF(res[0][2]) + Math_ComplexAbsF(res[0][3]);

		_cprintf("sq err: %f\n", sqerr[0]);
		*/
		// TODO: <epsilon imaginary part

		/*
		float s_root;

		int q_r_roots_num[2];
		int q_c_roots_num[2];
		float q_r_roots[2][2];
		_Fcomplex q_c_roots[2][2];

		s_root = s_r_roots[0];
		for (i = 1; i < s_r_roots_num; i++)
		s_root = Math_Maxf32(s_root, s_r_roots[i]);
		s_root = sqrtf(s_root);

		Math_PolynomialDeg2Solvef32(q_r_roots[0], q_c_roots[0], &q_r_roots_num[0], &q_c_roots_num[0], 1,  s_root, p/2.0f + (s_root*s_root)/2.0f - q / (2.0f * s_root), 0.0f);
		Math_PolynomialDeg2Solvef32(q_r_roots[1], q_c_roots[1], &q_r_roots_num[1], &q_c_roots_num[1], 1, -s_root, p/2.0f + (s_root*s_root)/2.0f + q / (2.0f * s_root), 0.0f);

		*num_real_roots = q_r_roots_num[0] + q_r_roots_num[1];
		*num_complex_roots = q_c_roots_num[0] + q_c_roots_num[1];

		for (i = 0; i < q_r_roots_num[0]; i++)
		real_roots[i] = q_r_roots[0][i] - offset;
		for (i = 0; i < q_r_roots_num[1]; i++)
		real_roots[i + q_r_roots_num[0]] = q_r_roots[1][i] - offset;

		for (i = 0; i < q_c_roots_num[0]; i++)
		complex_roots[i] = Math_ComplexSubF(q_c_roots[0][i], _FCbuild(offset, 0.0f));
		for (i = 0; i < q_c_roots_num[1]; i++)
		complex_roots[i + q_c_roots_num[0]] = Math_ComplexSubF(q_c_roots[1][i], _FCbuild(offset, 0.0f));
		*/
	}
}

void Math_PolynomialDeg3Solvef32(float *real_roots, _Fcomplex *complex_roots, int *num_real_roots, int *num_complex_roots, float a, float b, float c, float d, float e)
{
	if (a == 0.0f)
		Math_PolynomialDeg2Solvef32(real_roots, complex_roots, num_real_roots, num_complex_roots, b, c, d, e);
	else if (d == e)
	{
		Math_PolynomialDeg2Solvef32(real_roots, complex_roots, num_real_roots, num_complex_roots, a, b, c, 0.0f);
		(*num_real_roots)++;
		real_roots[*num_real_roots - 1] = 0.0f;
	}
	else
	{
		float disc;
		float q;
		float r;
		float inter;
		float s; 
		float t;
		float base;
		float r_cr;

		b /= a;
		c /= a;
		d /= a;

		q = (3.0f * c - (b * b)) / 9.0f;
		r = -(27.0f * d) + b * (9.0f * c - 2.0f * (b * b));
		r /= 54.0f;

		disc = q * q * q + r * r;	

		base = b / 3.0f;

		if (disc > 0.0f) // 1 real root and 2 complex roots
		{
			s = r + sqrtf(disc);
			s = (s < 0.0f) ? -powf(-s, (1.0f / 3.0f)) : powf(s, (1.0f / 3.0f));
			t = r - sqrtf(disc);
			t = (t < 0.0f) ? -powf(-t, (1.0f / 3.0f)) : powf(t, (1.0f / 3.0f));

			real_roots[0] = s + t - base;

			base += (s + t) / 2.0f;

			complex_roots[0] = _FCbuild(-base, sqrtf(3.0f) * (s - t) / 2.0f);
			complex_roots[1] = _FCbuild(-base, -sqrtf(3.0f) * (s - t) / 2.0f);

			*num_real_roots = 1;
			*num_complex_roots = 2;
		}
		else if (disc == 0.0f) // 3 real roots, at least one multiple root
		{
			r_cr = (r < 0.0f) ? -powf(-r, 1.0f / 3.0f) : powf(r, 1.0f / 3.0f);

			real_roots[0] = -base + 2.0f * r_cr;
			real_roots[1] = -(r_cr + base);
			real_roots[2] = -(r_cr + base);

			*num_real_roots = 3;
			*num_complex_roots = 0;
		}
		else // 3 real roots
		{
			q = -q;
			inter = q * q * q;
			inter = acosf(r / sqrtf(inter));
			r_cr = 2.0f * sqrtf(q);

			real_roots[0] = -base + r_cr * cosf(inter / 3.0f);
			real_roots[1] = -base + r_cr * cosf((inter + 2.0f * M_PI_F) / 3.0f);
			real_roots[2] = -base + r_cr * cosf((inter + 4.0f * M_PI_F) / 3.0f);

			*num_real_roots = 3;
			*num_complex_roots = 0;
		}
	}
}

void Math_PolynomialDeg3Solvef64(double *real_roots, _Dcomplex *complex_roots, int *num_real_roots, int *num_complex_roots, double a, double b, double c, double d, double e)
{
	if (a == 0.0f)
		Math_PolynomialDeg2Solvef64(real_roots, complex_roots, num_real_roots, num_complex_roots, b, c, d, e);
	else if (d == e)
	{
		Math_PolynomialDeg2Solvef64(real_roots, complex_roots, num_real_roots, num_complex_roots, a, b, c, 0.0f);
		(*num_real_roots)++;
		real_roots[*num_real_roots - 1] = 0.0f;
	}
	else
	{
		double disc;
		double q;
		double r;
		double inter;
		double s; 
		double t;
		double base;
		double r_cr;

		b /= a;
		c /= a;
		d /= a;

		q = (3.0 * c - (b * b)) / 9.0;
		r = -(27.0 * d) + b * (9.0 * c - 2.0 * (b * b));
		r /= 54.0;

		disc = q * q * q + r * r;	

		base = b / 3.0;

		if (disc > 0.0) // 1 real root and 2 complex roots
		{
			s = r + sqrt(disc);
			s = (s < 0.0) ? -pow(-s, (1.0 / 3.0)) : pow(s, (1.0 / 3.0));
			t = r - sqrt(disc);
			t = (t < 0.0) ? -pow(-t, (1.0 / 3.0)) : pow(t, (1.0 / 3.0));

			real_roots[0] = s + t - base;

			base += (s + t) / 2.0;

			complex_roots[0] = _Cbuild(-base, sqrt(3.0) * (s - t) / 2.0);
			complex_roots[1] = _Cbuild(-base, -sqrt(3.0) * (s - t) / 2.0);

			*num_real_roots = 1;
			*num_complex_roots = 2;
		}
		else if (disc == 0.0) // 3 real roots, at least one multiple root
		{
			r_cr = (r < 0.0) ? -pow(-r, 1.0 / 3.0) : pow(r, 1.0 / 3.0);

			real_roots[0] = -base + 2.0 * r_cr;
			real_roots[1] = -(r_cr + base);
			real_roots[2] = -(r_cr + base);

			*num_real_roots = 3;
			*num_complex_roots = 0;
		}
		else // 3 real roots
		{
			q = -q;
			inter = q * q * q;
			inter = acos(r / sqrt(inter));
			r_cr = 2.0 * sqrt(q);

			real_roots[0] = -base + r_cr * cos(inter / 3.0);
			real_roots[1] = -base + r_cr * cos((inter + 2.0 * M_PI) / 3.0);
			real_roots[2] = -base + r_cr * cos((inter + 4.0 * M_PI) / 3.0);

			*num_real_roots = 3;
			*num_complex_roots = 0;
		}
	}
}


void Math_PolynomialDeg2Solvef32(float *real_roots, _Fcomplex *complex_roots, int *num_real_roots, int *num_complex_roots, float a, float b, float c, float d)
{
	if (a == 0.0f)
	{
		*num_real_roots = 1;
		*num_complex_roots = 0;
		real_roots[0] = Math_PolynomialDeg1Solvef32(b, c, d);
	}
	else
	{
		float disc;

		c = c - d;

		disc = b*b - 4.0f*a*c;

		if (disc == 0.0f)
		{
			*num_real_roots = 2;
			*num_complex_roots = 0;
			real_roots[0] = -b / (2.0f * a);
			real_roots[1] = -b / (2.0f * a);
		}
		else if (disc > 0.0f)
		{
			*num_real_roots = 2;
			*num_complex_roots = 0;
			real_roots[0] = (-b - sqrtf(disc)) / (2.0f * a);
			real_roots[1] = (-b + sqrtf(disc)) / (2.0f * a);
		}
		else
		{
			*num_real_roots = 0;
			*num_complex_roots = 2;
			complex_roots[0] = _FCbuild(-b / (2.0f * a), -sqrtf(-disc) / (2.0f * a));
			complex_roots[1] = _FCbuild(-b / (2.0f * a), sqrtf(-disc) / (2.0f * a));
		}
	}
}
void Math_PolynomialDeg2Solvef64(double *real_roots, _Dcomplex *complex_roots, int *num_real_roots, int *num_complex_roots, double a, double b, double c, double d)
{
	if (a == 0.0f)
	{
		*num_real_roots = 1;
		*num_complex_roots = 0;
		real_roots[0] = Math_PolynomialDeg1Solvef64(b, c, d);
	}
	else
	{
		float disc;

		c = c - d;

		disc = (float)(b*b - 4.0*a*c);

		if (disc == 0.0f)
		{
			*num_real_roots = 2;
			*num_complex_roots = 0;
			real_roots[0] = -b / (2.0 * a);
			real_roots[1] = -b / (2.0 * a);
		}
		else if (disc > 0.0f)
		{
			*num_real_roots = 2;
			*num_complex_roots = 0;
			real_roots[0] = (-b - sqrt(disc)) / (2.0 * a);
			real_roots[1] = (-b + sqrt(disc)) / (2.0 * a);
		}
		else
		{
			*num_real_roots = 0;
			*num_complex_roots = 2;
			complex_roots[0] = _Cbuild(-b / (2.0 * a), -sqrt(-disc) / (2.0 * a));
			complex_roots[1] = _Cbuild(-b / (2.0 * a), sqrt(-disc) / (2.0 * a));
		}
	}
}
float Math_PolynomialDeg1Solvef32(float a, float b, float c)
{
	if (a == 0.0f)
		return 0.0f;
	else
		return (c - b) / a;
}
double Math_PolynomialDeg1Solvef64(double a, double b, double c)
{
	if (a == 0.0)
		return 0.0;
	else
		return (c - b) / a;
}
uint64_t Math_Factorialu64(int n)
{
	uint64_t res = n;
	uint64_t i;

	if (n > 20)
		return 0;
	if (n < 2)
		return 1;

	for (i = n - 1; i > 1; i--)
		res *= i;

	return res;
}