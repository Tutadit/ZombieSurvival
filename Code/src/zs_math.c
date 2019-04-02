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
