#include <stdio.h>
#include <linea.h>
#include <osbind.h>
#include <stdlib.h>

#include "global.h"
#include "t_runner.h"
#include "t_raster.h"
#include "t_player.h"

int main() {

    UINT32 *base = Physbase();
    test_raster(base);
    test_player(base);

	return 0;
}
