/*
 * Raster libary
 */
#ifndef RASTER_ZS
#define RASTER_ZS

#include "global.h"

#define VIDEO_BASE 0x3F8000
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

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400


void hbl_isr();
void vbl_isr();
/*
 * Returns the video base address.
 */
UINT32 *get_video_base();
/*
 * Sets the video base with the provided address
 */
void set_video_base(UINT32 *base);
/*
 * Clears the whole frame buffer.
 */
void clear_screen(UINT32 *base);
/*
 * Plots the given character array at the
 * provided location.
 */
void plot_chars(UINT8 *base, int x, int y, char *chars, int size);
/*
 * Plots the provided number at the provided location.
 * Note: won't plot negative sign.
 */
void plot_number(UINT8 *base, int x, int y, int number);
/*
 * Plots a pixel at the provided location
 */
void plot_pixel(UINT8 *base, int x, int y);
/*
 * Plots the provided 8bit bitmap at the desired
 * location
 */
void plot_bitmap_8(UINT8 *base, int x, int y, UINT8 *bitmap, UINT height);
/*
 * Plots the provided 16-bit bitmap at the desired
 * location
 */
void plot_bitmap_16(UINT16 *base, int x, int y, UINT16 *bitmap, UINT height);
/*
 * Plots the provided 32-bit bitmap at the desired
 * location
 */
void plot_bitmap_32(UINT32 *base, int x, int y, UINT32 *bitmap, UINT height);
/*
 * Plots the provided 64-bit bitmap at the desired
 * location.
 * Note: a 64-bit bitmap is 2 32-bit bitmaps welded together side
 * by side.
 */
void plot_bitmap_64(UINT32 *base, int x, int y, UINT32 *bitmapA, UINT32 *bitmapB, UINT height);
/*
 * Helper function to assure position of plotting is within bounds
 */
bool within_bounds(UINT base, UINT height, int *x, int *y, UINT *row, UINT *x_shift);
/*
 * Helper function to get the total number of diits of
 * a number.
 */
int number_of_digits(int num);

#endif
