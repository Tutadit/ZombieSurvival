#include <stdio.h>
#include <linea.h>
#include <osbind.h>
#include <stdlib.h>

#include "global.h"
#include "t_runner.h"
#include "t_raster.h"
#include "t_player.h"
#include "t_render.h"

int main() {

    UINT32 *base = Physbase();
    test_raster(base);
    test_player(base);
    test_zombie(base);
    test_renderer(base);

	return 0;
}
