# 1 "src/zombie.c" 1
# 1 "C:/c68/include/osbind.h" 1
# 1 "C:/c68/include/compiler.h" 1
# 9 "C:/c68/include/osbind.h" 2
# 1 "C:/c68/include/ostruct.h" 1
# 22 "C:/c68/include/ostruct.h"
typedef struct {
    long b_free;
    long b_total;
    long b_secsiz;
    long b_clsiz;
} _DISKINFO;


typedef struct {
  short time;
  short date;
} _DOSTIME;


typedef struct
{
        unsigned char maxlen;
        unsigned char actuallen;
        char    buffer[255];
} _CCONLINE;
# 48 "C:/c68/include/ostruct.h"
typedef struct _dta {
    char 	    dta_buf[21];
    char            dta_attribute;
    unsigned short  dta_time;
    unsigned short  dta_date;
    long            dta_size;
    char            dta_name[14];
} _DTA;
# 98 "C:/c68/include/ostruct.h"
typedef struct {
  short recsiz;
  short clsiz;
  short clsizb;
  short rdlen;
  short fsiz;
  short fatrec;
  short datrec;
  short numcl;
  short bflags;
} _BPB;




typedef struct _md {
    struct _md	*md_next;
    long	 md_start;
    long	 md_length;
    long	 md_owner;
} _MD;


typedef struct {
    _MD *mp_free;
    _MD *mp_used;
    _MD *mp_rover;
} _MPB;
# 141 "C:/c68/include/ostruct.h"
typedef struct {
    char    *ibuf;
    short   ibufsiz;
    volatile short   ibufhd;
    volatile short   ibuftl;
    short   ibuflow;
    short   ibufhi;
} _IOREC;


typedef struct {
	char	topmode;
	char	buttons;
	char	xparam;
	char	yparam;
	short	xmax;
	short	ymax;
	short	xstart;
	short	ystart;
} _PARAM;


typedef struct {
    void    (*midivec)	(void) ;
    void    (*vkbderr)	(void) ;
    void    (*vmiderr)	(void) ;
    void    (*statvec)	(void *) ;
    void    (*mousevec)	(void *) ;
    void    (*clockvec)	(void *) ;
    void    (*joyvec)	(void *) ;
    long    (*midisys)	(void) ;
    long    (*ikbdsys)	(void) ;
    char    kbstate;
} _KBDVECS;


typedef struct {
    void *unshift;
    void *shift;
    void *caps;
} _KEYTAB;


typedef struct
{
        void    *pb_scrptr;
        int     pb_offset;
        int     pb_width;
        int     pb_height;
        int     pb_left;
        int     pb_right;
        int     pb_screz;
        int     pb_prrez;
        void    *pb_colptr;
        int     pb_prtype;
        int     pb_prport;
        void    *pb_mask;
} _PBDEF;
# 17 "C:/c68/include/osbind.h" 2
# 33 "C:/c68/include/osbind.h"
 long _trap_1_w		(short) ;
 long _trap_1_ww	(short,short) ;
 long _trap_1_wl	(short,long) ;
 long _trap_1_wlw	(short,long,short) ;
 long _trap_1_wwll	(short,short,long,long) ;
 long _trap_1_wlww	(short,long,short,short) ;
 long _trap_1_www	(short,short,short) ;
 long _trap_1_wll	(short,long,long) ;
 long _trap_1_wwlll	(short,short,long,long,long) ;
 long _trap_1_wwwll	(short,short,short,long,long) ;
 long _trap_13_wl	(short,long) ;
 long _trap_13_w	(short) ;
 long _trap_13_ww	(short,short) ;
 long _trap_13_www	(short,short,short) ;
 long _trap_13_wwlwww	(short,short,long,short,short,short) ;
 long _trap_13_wwl	(short,short,long) ;
 long _trap_14_wwl	(short,short,long) ;
 long _trap_14_wwll	(short,short,long,long) ;
 long _trap_14_ww	(short,short) ;
 long _trap_14_w	(short) ;
 long _trap_14_wllw	(short,long,long,short) ;
 long _trap_14_wl	(short,long) ;
 long _trap_14_www	(short,short,short) ;
 long _trap_14_wllwwwww (short,long,long,short,short,short,short,short) ;
 long _trap_14_wllwwwwlw (short,long,long,short,short,short,short,long,short) ;
 long _trap_14_wllwwwwwlw (short,long,long,short,short,short,short,short,long,short) ;
 long _trap_14_wwwwwww	(short,short,short,short,short,short,short) ;
 long _trap_14_wlll	(short,long,long,long) ;
 long _trap_14_wllww	(short,long,long,short,short) ;
 long _trap_14_wwwwl	(short,short,short,short,long) ;
 long _trap_14_wwwl	(short,short,short,long) ;
 long _trap_14_wlwlw	(short,long,short,long,short) ;
# 103 "C:/c68/include/osbind.h"
 long _trap_1_ 	(short,...) ;
 long _trap_14_ 	(short,...) ;
 long _trap_13_ 	(short,...) ;
# 1 "src/zombie.c" 2
# 1 "include/global.h" 1



typedef unsigned char UINT8;
typedef unsigned int UINT16;
typedef unsigned long UINT32;
typedef unsigned int UINT;

typedef unsigned int bool;
# 2 "src/zombie.c" 2
# 1 "include/zombie.h" 1



UINT32 ZombieLeftStop[32] = {
                             0x0,
                             0x0,
                             0x0,
                             0x0,
                             0x0,
                             0x0,
                             0x0,
                             0x0,
                             0x30000,
                             0x48000,
                             0x48000,
                             0x78000,
                             0x10000,
                             0x20000,
                             0x30000,
                             0x7f8000,
                             0x48000,
                             0x1fc8000,
                             0x48000,
                             0x48000,
                             0x48000,
                             0x48000,
                             0x78000,
                             0x48000,
                             0x48000,
                             0x48000,
                             0x48000,
                             0x48000,
                             0x48000,
                             0x48000,
                             0x48000,
                             0x48000
};

UINT32 ZombieLeftStepOne[32] = {
                            0x0,
                            0x0,
                            0x0,
                            0x0,
                            0x0,
                            0x0,
                            0x0,
                            0x0,
                            0x0,
                            0x30000,
                            0x48000,
                            0x48000,
                            0x78000,
                            0x30000,
                            0x30000,
                            0x7f8000,
                            0x48000,
                            0x1fc8000,
                            0x48000,
                            0x48000,
                            0x48000,
                            0x48000,
                            0x78000,
                            0x48000,
                            0xc8000,
                            0x88000,
                            0x88000,
                            0x88000,
                            0x88000,
                            0x88000,
                            0x8000,
                            0x8000
};

UINT32 ZombieLeftStepTwo[32] = {
                            0x0,
                            0x0,
                            0x0,
                            0x0,
                            0x0,
                            0x0,
                            0x0,
                            0x0,
                            0x0,
                            0x30000,
                            0x48000,
                            0x48000,
                            0x78000,
                            0x30000,
                            0x30000,
                            0x7f8000,
                            0x48000,
                            0x1fc8000,
                            0x48000,
                            0x48000,
                            0x48000,
                            0x48000,
                            0x78000,
                            0x48000,
                            0x58000,
                            0x50000,
                            0x50000,
                            0x50000,
                            0x50000,
                            0x50000,
                            0x40000,
                            0x40000
};

UINT32 ZombieRightStop[32] = {
                              0x0,
                              0x0,
                              0x0,
                              0x0,
                              0x0,
                              0x0,
                              0x0,
                              0x0,
                              0x30000,
                              0x48000,
                              0x48000,
                              0x78000,
                              0x20000,
                              0x10000,
                              0x30000,
                              0x7fe00,
                              0x48000,
                              0x4f800,
                              0x48000,
                              0x48000,
                              0x48000,
                              0x48000,
                              0x78000,
                              0x48000,
                              0x48000,
                              0x48000,
                              0x48000,
                              0x48000,
                              0x48000,
                              0x48000,
                              0x48000,
                              0x48000
};

UINT32 ZombieUpStop[32] = {
                           0x0,
                           0x0,
                           0x0,
                           0x0,
                           0x0,
                           0x0,
                           0x0,
                           0x0,
                           0x30000,
                           0x48000,
                           0x48000,
                           0x478800,
                           0x221000,
                           0x112000,
                           0xb4000,
                           0x78000,
                           0x48000,
                           0x48000,
                           0x48000,
                           0x48000,
                           0x48000,
                           0x48000,
                           0x78000,
                           0x48000,
                           0x48000,
                           0x48000,
                           0x48000,
                           0x48000,
                           0x48000,
                           0x48000,
                           0x48000,
                           0x48000
};

UINT32 ZombieDownStop[32] = {
                             0x0,
                             0x0,
                             0x0,
                             0x0,
                             0x0,
                             0x0,
                             0x0,
                             0x0,
                             0x30000,
                             0x48000,
                             0x48000,
                             0x78000,
                             0x20000,
                             0x10000,
                             0x30000,
                             0x78000,
                             0xcc000,
                             0x14a000,
                             0x249000,
                             0x448800,
                             0x48000,
                             0x48000,
                             0x78000,
                             0x48000,
                             0x48000,
                             0x48000,
                             0x48000,
                             0x48000,
                             0x48000,
                             0x48000,
                             0x48000,
                             0x48000
};

void draw_zombie(UINT32 *base, int x, int y, int directionLook, int directionMove, int step );
# 3 "src/zombie.c" 2
# 1 "include/raster.h" 1
# 19 "include/raster.h"
void plot_bitmap_8(UINT8 *base, int x, int y, const UINT8 *bitmap, UINT height);
void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, UINT height);
void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, UINT height);
void plot_bitmap_64(UINT32 *base, int x, int y, const UINT32 *bitmapA, UINT32 *bitmapB, UINT height);
bool within_bounds(UINT base, UINT height, int *x, int *y, UINT *row, UINT *x_shift);
# 4 "src/zombie.c" 2


void draw_zombie( UINT32 *base, int x, int y, int directionLook, int directionMove, int step ) {


}
