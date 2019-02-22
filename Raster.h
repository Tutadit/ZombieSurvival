#include <stdio.h>
#include <linea.h>
#include <osbind.h>
#include <stdlib.h>

typedef unsigned char UINT8;
typedef unsigned int UINT16;
typedef unsigned long UINT32;
typedef unsigned int UINT;

typedef unsigned int bool;
#define true 1
#define false 0

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400

#define B8_BITS 8
#define B8_PER_LINE 80
#define B8_DIVIDE_SHIFT 3
#define B8_MODULUS_MASK 0x0F

#define B16_BITS 16
#define B16_PER_LINE 40
#define B16_DIVIDE_SHIFT 4
#define B16_MODULUS_MASK 0x000F

#define B32_BITS 32
#define B32_PER_LINE 20
#define B32_DIVIDE_SHIFT 5
#define B32_MODULUS_MASK 0x0000000F

void plot_bitmap_8(UINT8 *base, int x, int y, const UINT8 *bitmap, UINT height);
void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, UINT height);
void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, UINT height);
bool within_bounds(UINT base, UINT height, int *x, int *y, UINT *row, UINT *x_shift);
