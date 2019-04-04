/*
 * A very simple mathematics module.
 */
#ifndef ZS_MATH
#define ZS_MATH
#include "global.h"

#define ZS_SEED 0x5678
extern UINT16 random_seed;

/*
 * Returns the absolute value of a number
 */
int abs(int number);
/*
 * Initialize the random number generator.
 * Must be called before any call to
 * random
 */
void random_init();
/*
 * Update the random seed. This should be done
 * frequently to obtain truer random numbers
 * however it is not necessary.
 */
void random_update();
/*
 * Returns a random integer between the provided
 * lower bound and upper bound. Updates random
 * after call.
 */
int random(int lower_bound, int upper_boud);
/*
 * Checks if two rectangles collide.
 */
bool collided (int x1, int y1, int h1, int w1,
               int x2, int y2, int h2, int w2);
#endif
