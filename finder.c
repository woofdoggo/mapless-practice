
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

        // get treasure
        if (!getStructurePos(Treasure, MC_1_16, seed, rx, rz, &pos)) {
            continue;
        }
        
        if (!isViableStructurePos(Treasure, &g, pos.x, pos.z, 0)) {
            continue;
        }

        // check treasure -> spawn distance
        int xd = abs(spawn.x - pos.x);
        int zd = abs(spawn.z - pos.z);
        if (xd + zd < 64) {
            break;
        }
    }

    return seed;
}

int main() {
    while (1) {
        uint64_t seed = gen_mapless(rand());
        printf("%" PRId64 "\n", seed);
    }
}
