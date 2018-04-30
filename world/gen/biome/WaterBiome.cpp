
#include "WaterBiome.h"

namespace regency {
namespace world {
namespace gen {

WaterBiome::WaterBiome(double e_min, double e_max, double m_min, double m_max)
    : Biome("water", e_min, e_max, m_min, m_max, NameList::NONE) {}

void WaterBiome::generate_tile(unsigned int x, unsigned int y, double e, double m, TileMap& tiles) {
    const Material* mat = nullptr;

    if (fabs(e - _e_range.second) < 0.025) {
        mat = &Material::SAND;
    } else {
        mat = &Material::SALT_WATER;
    }

    std::unique_ptr<Tile> tile = std::make_unique<Tile>(x, y, mat, e, m);
    tiles.set(x, y, std::move(tile));
}
}
}
}
