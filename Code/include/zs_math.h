#ifndef ZS_MATH
#define ZS_MATH
#include "global.h"

#define SEED 0x12345678

extern UINT32 random_seed;

int abs(int number);
void random_init();
void random_update();
int random(int lower_bound, int upper_boud);
#endif
