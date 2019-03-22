#include "global.h"
#include "player_b.h"

const UINT32 PLAYER_DEAD[8] = {
                               0x400800,
                               0x8401000,
                                0x4402000,
                                0x2404000,
                                0x17f8000,
                                0x1e810000,
                                0x13810000,
                                0x1efffc00
};
const UINT32 PLAYER_BODY_WEST[PLAYER_BODY_HEIGHT] = {
                             0x38000,
                             0x28000,
                             0x28000,
                             0x38000,
                             0x10000,
                             0x38000,
                             0x7c000,
                             0xc6000,
                             0xffe000,
                             0x1ce000,
                             0x44000,
                             0x44000,
                             0x7c000,
                             0x28000
                             };

const UINT32 PLAYER_BODY_EAST[PLAYER_BODY_HEIGHT] = {
                              0x38000,
                              0x28000,
                              0x28000,
                              0x38000,
                              0x10000,
                              0x38000,
                              0x7c000,
                              0xc6000,
                              0xffe00,
                              0xe7000,
                              0x44000,
                              0x44000,
                              0x7c000,
                              0x28000
};

const UINT32 PLAYER_BODY_SOUTH[PLAYER_BODY_HEIGHT] = {
                             0x38000,
                             0x28000,
                             0x28000,
                             0x38000,
                             0x10000,
                             0x38000,
                             0x7c000,
                             0xc6000,
                             0xc6000,
                             0xfe000,
                             0x54000,
                             0x44000,
                             0x7c000,
                             0x28000
};

const UINT32 PLAYER_BODY_NORTH[PLAYER_BODY_HEIGHT] = {
                           0x38000,
                           0x28000,
                           0x28000,
                           0x38000,
                           0x10000,
                           0x38000,
                           0x7c000,
                           0xc6000,
                           0xc6000,
                           0x44000,
                           0x44000,
                           0x44000,
                           0x7c000,
                           0x28000
};

const UINT32 PLAYER_BODY_NORTHWEST[PLAYER_BODY_HEIGHT] = {
                               0x38000,
                               0x28000,
                               0x428000,
                               0x238000,
                               0x110000,
                               0xf8000,
                               0xfc000,
                               0xc6000,
                               0x46000,
                               0x44000,
                               0x44000,
                               0x44000,
                               0x7c000,
                               0x28000
};

const UINT32 PLAYER_BODY_NORTHEAST[PLAYER_BODY_HEIGHT] = {
                                0x38000,
                                0x28000,
                                0x28400,
                                0x38800,
                                0x11000,
                                0x3e000,
                                0x7e000,
                                0xc6000,
                                0xc4000,
                                0x44000,
                                0x44000,
                                0x44000,
                                0x7c000,
                                0x28000
};

const UINT32 PLAYER_BODY_SOUTHEAST[PLAYER_BODY_HEIGHT] = {
                                  0x38000,
                                  0x28000,
                                  0x28000,
                                  0x38000,
                                  0x10000,
                                  0x38000,
                                  0x7c000,
                                  0xc6000,
                                  0xc6000,
                                  0xf6000,
                                  0x4c000,
                                  0x44000,
                                  0x7e000,
                                  0x29000
};

const UINT32 PLAYER_BODY_SOUTHWEST[PLAYER_BODY_HEIGHT] = {
                                 0x38000,
                                 0x28000,
                                 0x28000,
                                 0x38000,
                                 0x10000,
                                 0x38000,
                                 0x7c000,
                                 0xc6000,
                                 0xc6000,
                                 0xde000,
                                 0x64000,
                                 0x44000,
                                 0xfc000,
                                 0x128000
};
const UINT32 PLAYER_EAST_STEP_ONE[PLAYER_LEGS_HEIGHT] = {
                                0x2c000,
                                0x24000,
                                0x24000,
                                0x26000,
                                0x30000
};
const UINT32 PLAYER_EAST_STOP[PLAYER_LEGS_HEIGHT] = {
                                  0x28000,
                                  0x28000,
                                  0x28000,
                                  0x28000,
                                  0x3c000
};
const UINT32 PLAYER_EAST_STEP_TWO[PLAYER_LEGS_HEIGHT] = {
                                    0x38000,
                                    0x18000,
                                    0x18000,
                                    0x18000,
                                    0xc000
};
const UINT32 PLAYER_WEST_STEP_ONE[PLAYER_LEGS_HEIGHT] = {
                                 0x68000,
                                 0x48000,
                                 0x48000,
                                 0xc8000,
                                 0x18000
};
const UINT32 PLAYER_WEST_STOP[PLAYER_LEGS_HEIGHT] = {
                                 0x28000,
                                 0x28000,
                                 0x28000,
                                 0x28000,
                                 0x78000
};
const UINT32 PLAYER_WEST_STEP_TWO[PLAYER_LEGS_HEIGHT] = {
                                   0x38000,
                                   0x30000,
                                   0x30000,
                                   0x30000,
                                   0x60000
};

const UINT32 PLAYER_NORTH_STEP_ONE[PLAYER_LEGS_HEIGHT] = {
                                                          0x28000,
                                                          0x28000,
                                                          0x28000,
                                                          0x8000,
                                                          0x8000
};

const UINT32 PLAYER_NORTH_STOP[PLAYER_LEGS_HEIGHT] = {
                             0x28000,
                             0x28000,
                             0x28000,
                             0x28000,
                             0x28000
};

const UINT32 PLAYER_NORTH_STEP_TWO[PLAYER_LEGS_HEIGHT] = {
                               0x28000,
                               0x28000,
                               0x28000,
                               0x20000,
                               0x20000
};


const UINT32 *PLAYER_BODY[8] = {
                         PLAYER_BODY_NORTH,
                         PLAYER_BODY_NORTHWEST,
                         PLAYER_BODY_WEST,
                         PLAYER_BODY_SOUTHWEST,
                         PLAYER_BODY_SOUTH,
                         PLAYER_BODY_SOUTHEAST,
                         PLAYER_BODY_EAST,
                         PLAYER_BODY_NORTHEAST
};

const UINT32 *PLAYER_STEP[4][PLAYER_TOTAL_STEPS] = {
                            {
                             PLAYER_WEST_STEP_ONE,
                             PLAYER_WEST_STOP,
                             PLAYER_WEST_STEP_TWO,
                             PLAYER_WEST_STOP
                            },
                            {
                             PLAYER_NORTH_STEP_ONE,
                             PLAYER_NORTH_STOP,
                             PLAYER_NORTH_STEP_TWO,
                             PLAYER_NORTH_STOP
                            },
                            {
                             PLAYER_EAST_STEP_ONE,
                             PLAYER_EAST_STOP,
                             PLAYER_EAST_STEP_TWO,
                             PLAYER_EAST_STOP
                            },
                            {
                             PLAYER_NORTH_STEP_ONE,
                             PLAYER_NORTH_STOP,
                             PLAYER_NORTH_STEP_TWO,
                             PLAYER_NORTH_STOP
                            }
};
