
#include "MountainBiome.h"

namespace regency {
namespace world {
namespace gen {

MountainBiome::MountainBiome(double e_min, double e_max, double m_min, double m_max)
    : Biome("mountain", e_min, e_max, m_min, m_max, NameList::MOUNTAINS) {}

void MountainBiome::generate_tile(
    unsigned int x, unsigned int y, double e, double m, TileMap& tiles) {
    const Material* mat = nullptr;

    if (e > 0.95) {
        mat = &Material::SNOW;
    } else {
        mat = &Material::ROCK;
    }

    std::unique_ptr<Tile> tile = std::make_unique<Tile>(x, y, mat, e, m);
    tiles.set(x, y, std::move(tile));
}
}
}
}
