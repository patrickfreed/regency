
#include "WaterBiome.h"

WaterBiome::WaterBiome(double e_min, double e_max, double m_min, double m_max)
    : Biome("water", e_min, e_max, m_min, m_max) {}

void WaterBiome::generate_tile(unsigned int x, unsigned int y, double e, double m, TileMap &tiles) {
    const Material *mat = nullptr;

    if (fabs(e - _e_range.second) < 0.025) {
        mat = &Material::SAND;
    } else {
        mat = &Material::SALT_WATER;
    }

    insert_into_world(x, y, e, m, mat, tiles);
}
