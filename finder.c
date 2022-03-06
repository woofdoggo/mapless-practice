#include "cubiomes/finders.h"
#include "cubiomes/generator.h"
#include "cubiomes/layers.h"
#include "cubiomes/util.h"
#include <stdint.h>
#include <stdlib.h>

uint64_t gen_mapless(uint64_t start) {
    Pos pos;

    Generator g;
    setupGenerator(&g, MC_1_16, 0);

    uint64_t seed = start;
    for (; ; seed++) {
        applySeed(&g, 0, seed);

        // get spawn
        Pos spawn = estimateSpawn(&g);
        int rx = spawn.x / 16;
        int rz = spawn.z / 16;

        // check for treasure within 5x5 chunk grid of spawn
        for (int i = -2; i <= 2; i++) {
            for (int j = -2; j <= 2; j++) {
                int cx = rx + i;
                int cz = rz + j;

                // get treasure
                if (!getStructurePos(Treasure, MC_1_16, seed, cx, cz, &pos)) {
                    continue;
                }

                if (!isViableStructurePos(Treasure, &g, pos.x, pos.z, 0)) {
                    continue;
                }

                return seed;
            }
        }
    }
}

int main() {
    srand(time(NULL));

    while (1) {
        uint64_t seed = gen_mapless(rand());
        printf("%" PRId64 "\n", seed);
    }
}
