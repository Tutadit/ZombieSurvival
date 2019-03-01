#include <stdio.h>
#include <linea.h>
#include <osbind.h>
#include <stdlib.h>


#include "global.h"
#include "t_raster.h"
#include "raster.h"

#define TOTAL_POSITIONS 10
int positions[TOTAL_POSITIONS][2] = {
                               0,0,
                               -4,60,
                               60,-4,
                               635,395,
                               0,624,
                               320,200,
                               0,384,
                               608,120,
                               300,500,
                               80,350
};

void test_raster(UINT32 *base) {

    UINT8 *base8 = (UINT8 *) base;
    UINT16 *base16 = (UINT16 *) base8;

    clear_screen(base);
    test_plot_bitmap_8(base8);
    Cnecin();
    clear_screen(base);
    test_plot_bitmap_16(base16);
    Cnecin();
    clear_screen(base);
    test_plot_bitmap_32(base);
    Cnecin();
}

void test_plot_bitmap_8(UINT8 *base) {
    UINT8 test1[8] = {0x99,0x24,0x42,0x99,0x99,0x42,0x24,0x99};
    int i;
    for(i=0; i < TOTAL_POSITIONS; i++) {
        plot_bitmap_8(base,positions[i][0],positions[i][1],test1,8);
    }
}

void test_plot_bitmap_16(UINT16 *base) {
    UINT16 test1[16] = {
                        0xabd5,
                        0x542a,
                        0xa815,
                        0x500a,
                        0xa005,
                        0x47e2,
                        0x8421,
                        0x85a1,
                        0x85a1,
                        0x8421,
                        0x47e2,
                        0xa005,
                        0x500a,
                        0xa815,
                        0x542a,
                        0xabd5
    };
    int i;
    for(i=0; i < TOTAL_POSITIONS; i++) {
        plot_bitmap_16(base,positions[i][0],positions[i][1],test1,16);
    }
}

void test_plot_bitmap_32(UINT32 *base) {
    UINT32 test1[32] = {
                        0x1ff800,
                        0x20200408,
                        0x50400214,
                        0x20800108,
                        0x1000080,
                        0x2000040,
                        0x4000020,
                        0x8000010,
                        0x107c3e08,
                        0x20442204,
                        0x40442202,
                        0x80442201,
                        0x807c3e01,
                        0x80000001,
                        0x80000001,
                        0x80000001,
                        0x80000001,
                        0x80000001,
                        0x80000001,
                        0x800ff001,
                        0x80081001,
                        0x400ff002,
                        0x200ff004,
                        0x10000008,
                        0x8000010,
                        0x4000020,
                        0x2000040,
                        0x1000080,
                        0x10800108,
                        0x28400214,
                        0x10200408,
                        0x1ff800
    };
    int i;
    for(i=0; i < TOTAL_POSITIONS; i++) {
        plot_bitmap_32(base,positions[i][0],positions[i][1],test1,32);
    }
}
