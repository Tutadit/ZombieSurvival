#include "global.h"
#include "zs_math.h"

UINT32 random_seed = 0;

int abs(int number) {
    if (number < 0) {
        number *= -1;
    }
    return number;
}

void random_init() {
    random_seed = SEED;
}

void random_update() {
    random_seed *= 69069L;
	random_seed += 41;
}

int random(int lower_bound, int upper_boud) {
    int random;
    random = random_seed % (upper_boud - lower_bound + 1) + lower_bound;
    random_update();
    return random;
}
