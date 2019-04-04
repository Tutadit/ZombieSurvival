#include "global.h"
#include "zs_math.h"

UINT16 random_seed = 0;

int abs(int number) {
    if (number < 0) {
        number *= -1;
    }
    return number;
}

void random_init() {
    random_seed = ZS_SEED;
}

void random_update() {
    random_seed *= 43;
	random_seed += 41;
}

int random(int lower_bound, int upper_boud) {
    int random = 0;
    random = random_seed % (upper_boud - lower_bound + 1) + lower_bound;
    random_update();
    return random;
}

bool collided (int x1, int y1, int h1, int w1, int x2, int y2, int h2, int w2) {
    bool collided = false;
    if (x1 <= x2 + w2 &&
        x1 + w1 >= x2 &&
        y1 <= y2 + h2 &&
        y1 + h1 >= y2) {
        collided = true;
    }
    return collided;
}
