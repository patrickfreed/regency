
#include "MountainBiome.h"

MountainBiome::MountainBiome() : Biome("mountain", 0, 0, 0, 0) {}

const Material *MountainBiome::get_tile(double e, double m) {
    if (e > 0.9) {
        return &Material::SNOW;
    } else {
        return &Material::ROCK;
    }
}

