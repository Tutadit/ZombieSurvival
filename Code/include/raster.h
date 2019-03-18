#ifndef RASTER_ZS
#define RASTER_ZS

#define B8_BITS 8
#define B8_PER_LINE 80
#define B8_DIVIDE_SHIFT 3
#define B8_MODULUS_MASK 0x7

#define B16_BITS 16
#define B16_PER_LINE 40
#define B16_DIVIDE_SHIFT 4
#define B16_MODULUS_MASK 0xF

#define B32_BITS 32
#define B32_PER_LINE 20
#define B32_DIVIDE_SHIFT 5
#define B32_MODULUS_MASK 0x1F

void plot_pixel(UINT8 *base, int x, int y);
void plot_bitmap_8(UINT8 *base, int x, int y, const UINT8 *bitmap, UINT height);
void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, UINT height);
void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, UINT height);
void plot_bitmap_64(UINT32 *base, int x, int y, const UINT32 *bitmapA, UINT32 *bitmapB, UINT height);
bool within_bounds(UINT base, UINT height, int *x, int *y, UINT *row, UINT *x_shift);

#endif
