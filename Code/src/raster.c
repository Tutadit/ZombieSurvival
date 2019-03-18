#include <stdlib.h>
#include "global.h"
#include "raster.h"

void plot_pixel(UINT8 *base, int x, int y) {
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
        *(base + y * 80 + (x >> 3)) |= 1 << 7 - (x & 7);
}

bool within_bounds(UINT base, UINT height, int *x, int *y, UINT *row, UINT *x_shift) {
    if( *y < 0 && *y > -height) {
        *row = abs(*y);
        *y = 0;
    }
    if ( *x < 0 && *x > -base) {
        *x_shift = abs(*x);
        *x = 0;
    }
    return ( *x >= 0 && *x < SCREEN_WIDTH && *y >= 0 && *y < SCREEN_HEIGHT );
}

void plot_bitmap_8(UINT8 *base, int x, int y, const UINT8 *bitmap, UINT height) {
    UINT8 *src = bitmap;
    UINT8 *dst;
    UINT8 extend_left;
    UINT8 extend_right;
    UINT shift;
    UINT row = 0;
    UINT x_shift = 0;
    UINT block_num = ( abs(x) >> B8_DIVIDE_SHIFT );
    if ( within_bounds(B8_BITS, height,&x,&y, &row, &x_shift) ) {
        dst = base + y * B8_PER_LINE + block_num;
        shift = x & B8_MODULUS_MASK;
        src += row;
        for(; row < height && row + y < SCREEN_HEIGHT; row++) {
            if ( shift && block_num < B8_PER_LINE - 1) {
                extend_left = *src;
                extend_right = *src;
                extend_left = extend_left >> ( shift );
                extend_right = extend_right << ( B8_BITS - shift );
                *dst |= extend_left;
                *(dst+1) |= extend_right;
            } else if (block_num == B8_PER_LINE - 1) {
                *dst |= *src >> shift;
            } else {
                *dst |= *src << x_shift;
            }
            src++;
            dst += B8_PER_LINE;
        }
    }
}

void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, UINT height) {
    UINT16 *src = bitmap;
    UINT16 *dst;
    UINT16 extend_left;
    UINT16 extend_right;
    UINT shift;
    UINT row = 0;
    UINT x_shift = 0;
    UINT block_num = ( abs(x) >> B16_DIVIDE_SHIFT );
    if ( within_bounds(B16_BITS, height,&x,&y, &row, &x_shift) ) {
        dst = base + y * B16_PER_LINE + block_num;
        shift = x & B16_MODULUS_MASK;
        src += row;
        for(; row < height && row + y < SCREEN_HEIGHT; row++) {
            if ( shift && block_num < B16_PER_LINE - 1) {
                extend_left = *src;
                extend_right = *src;
                extend_left = extend_left >> ( shift );
                extend_right = extend_right << ( B16_BITS - shift );
                *dst |= extend_left;
                *(dst+1) |= extend_right;
            } else if (block_num == B16_PER_LINE - 1) {
                *dst |= *src >> shift;
            } else {
                *dst |= *src << x_shift;
            }
            src++;
            dst += B16_PER_LINE;
        }
    }
}

void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, UINT height) {
    UINT32 *src = bitmap;
    UINT32 *dst;
    UINT32 extend_left;
    UINT32 extend_right;
    UINT shift;
    UINT row = 0;
    UINT x_shift = 0;
    UINT block_num = ( abs(x) >> B32_DIVIDE_SHIFT );
    if ( within_bounds(B32_BITS, height,&x,&y, &row, &x_shift) ) {
        dst = base + y * B32_PER_LINE + block_num;
        shift = x & B32_MODULUS_MASK;
        src += row;
        for(; row < height && row + y < SCREEN_HEIGHT; row++) {
            if ( shift && block_num < B32_PER_LINE - 1) {
                extend_left = *src;
                extend_right = *src;
                extend_left = extend_left >> ( shift );
                extend_right = extend_right << ( B32_BITS - shift );
                *dst |= extend_left;
                *(dst+1) |= extend_right;
            } else if (block_num == B32_PER_LINE - 1) {
                *dst |= *src >> shift;
            } else {
                *dst |= *src << x_shift;
            }
            src++;
            dst += B32_PER_LINE;
        }
    }
}

void plot_bitmap_64(UINT32 *base, int x, int y, const UINT32 *bitmapA, UINT32 *bitmapB, UINT height) {
    plot_bitmap_32(base,x,y,bitmapA,height);
    plot_bitmap_32(base,x+32,y,bitmapB,height);
}
