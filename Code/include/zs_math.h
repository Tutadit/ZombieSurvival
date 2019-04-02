#ifndef ZS_MATH
#define ZS_MATH

#include "global.h"

#define ZS_SEED 0x5678

extern UINT16 random_seed;

int abs(int number);
void random_init();
void random_update();
int random(int lower_bound, int upper_boud);
#endif
