
#include "MountainBiome.h"

MountainBiome::MountainBiome(double e_min, double e_max, double m_min, double m_max)
    : Biome("mountain", e_min, e_max, m_min, m_max) {}

void MountainBiome::generate_tile(
    unsigned int x, unsigned int y, double e, double m, TileMap &tiles) {
    const Material *mat = nullptr;

    if (e > 0.95) {
        mat = &Material::SNOW;
    } else {
        mat = &Material::ROCK;
    }

    insert_into_world(x, y, e, m, mat, tiles);
}
