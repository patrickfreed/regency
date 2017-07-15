
#include "DesertBiome.h"

namespace regency {
namespace world {
namespace gen {

DesertBiome::DesertBiome(double e_min, double e_max, double m_min, double m_max)
    : Biome("desert", e_min, e_max, m_min, m_max) {}

void DesertBiome::generate_tile(
    unsigned int x, unsigned int y, double e, double m, TileMap& tiles) {
    const Material* mat = &Material::SAND;

    // std::unique_ptr<Tile> tile = std::make_unique<Tile>(x, y, mat, e, m);
    tiles.set(x, y, std::move(std::make_unique<Tile>(x, y, mat, e, m)));
}
}
}
}