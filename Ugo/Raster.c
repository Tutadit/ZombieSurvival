#include <Raster.h>

int main()
{
	int x = 0;
    int y = 0;
    UINT8 *base8 = Physbase();
    UINT16 *base16 = (UINT16 *) base8;
    UINT32 *base32 = (UINT32 *) base8;
    UINT8 bullet[8] = {
                       0x0,
                       0x3F,
                       0x40,
                       0xFF,
                       0xFF,
                       0x7F,
                       0x3F,
                       0x0
    };
    UINT16 invader_bitmap[16] = {
                                 0x1008,
                                 0x1998,
                                 0x5bda,
                                 0x2ff4,
                                 0x6bd6,
                                 0xedb7,
                                 0xf7ef,
                                 0xdbdb,
                                 0xbc3d,
                                 0x37ec,
                                 0x67e6,
                                 0x73ce,
                                 0x47e2,
                                 0xe70,
                                 0x1c38,
                                 0x1428
    };

    UINT32 bitmap[32] = {
                         0x0,
                         0x0,
                         0x3f00,
                         0xffc0,
                         0x1ffc0,
                         0x3ffe0,
                         0x3ffe0,
                         0x7def0,
                         0x7def0,
                         0x7fff0,
                         0x3fff0,
                         0xffffc,
                         0xfe9fc,
                         0x7e1f0,
                         0x3ffe0,
                         0xffc0,
                         0x7f80,
                         0x8060,
                         0x18070,
                         0x3fffc,
                         0x3bf9c,
                         0x77fa0,
                         0x77fc0,
                         0xff00,
                         0xc0,
                         0x1c0,
                         0x3c0,
                         0x180,
                         0x180,
                         0x0,
                         0x0,
                         0x0
    };


    printf("\033E\033f\n");     /* blank the screen */
    plot_bitmap_8(base8,3,90,bullet,8);
    plot_bitmap_16(base16,12,34,invader_bitmap,16);
    plot_bitmap_32(base32,89,300,bitmap,32);
    Cnecin();
	return 0;
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
