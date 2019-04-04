/*
 * Bitmap Configuration for 'zombie'
 * A zombie can be plotted to look North, South,
 * East and West.
 *
 * It can be stopped or stepped with one leg or
 * the other.
 *
 * ZOMBIE_DIRECTION_STEP is a 2D array of bitmaps arrays,
 * the first dimension of the array is the direction and
 * the second its the step.
 *
 * Global constants are declared for easy use
 */
#ifndef ZOMBIE_ZS
#define ZOMBIE_ZS
#include "global.h"
#define ZOMBIE_HEIGHT 24
#define ZOMBIE_WIDTH 20
#define ZOMBIE_TOTAL_STEPS 4
#define ZOMBIE_STEPS_STOP_NUMBER 1

#define Z_MOVE_W 0
#define Z_MOVE_N 1
#define Z_MOVE_E 2
#define Z_MOVE_S 3

extern const UINT32 ZOMBIE_WEST_STOP[ZOMBIE_HEIGHT];
extern const UINT32 ZOMBIE_WEST_STEP_ONE[ZOMBIE_HEIGHT];
extern const UINT32 ZOMBIE_WEST_STEP_TWO[ZOMBIE_HEIGHT];

extern const UINT32 ZOMBIE_EAST_STOP[ZOMBIE_HEIGHT];
extern const UINT32 ZOMBIE_EAST_STEP_ONE[ZOMBIE_HEIGHT];
extern const UINT32 ZOMBIE_EAST_STEP_TWO[ZOMBIE_HEIGHT];

extern const UINT32 ZOMBIE_NORTH_STOP[ZOMBIE_HEIGHT];
extern const UINT32 ZOMBIE_NORTH_STEP_ONE[ZOMBIE_HEIGHT];
extern const UINT32 ZOMBIE_NORTH_STEP_TWO[ZOMBIE_HEIGHT];

extern const UINT32 ZOMBIE_SOUTH_STOP[ZOMBIE_HEIGHT];
extern const UINT32 ZOMBIE_SOUTH_STEP_ONE[ZOMBIE_HEIGHT];
extern const UINT32 ZOMBIE_SOUTH_STEP_TWO[ZOMBIE_HEIGHT];

extern const UINT32 *ZOMBIE_DIRECTION_STEP[4][ZOMBIE_TOTAL_STEPS];

#endif
