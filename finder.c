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

// on linux with glibc, rand actually did a somewhat acceptable job
// (~700 collisions out of ~150k generated seeds)
//
// when crosscompiling for windows, it is allegedly a lot worse: >95%
// collision rate. thanks to vondraker for reporting this issue o/
//
// this is just a simple xorshift implementation to try and avoid the issue.
// it also generates 64 bit seeds instead of 32 bit, so it should (hopefully)
// be better regardless.

uint64_t rand_x;
uint64_t rand_iter() {
    rand_x ^= (rand_x << 7);
    rand_x ^= (rand_x >> 2);
    rand_x ^= (rand_x << 3);
    return rand_x;
}

int main() {
    srand(time(NULL));
    rand_x = rand();
    rand_iter();

    while (1) {
        uint64_t seed = gen_mapless(rand_iter());
        printf("%" PRId64 "\n", seed);
    }
}
