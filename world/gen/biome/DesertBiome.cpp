//
// Created by Patrick Freed on 6/29/17.
//

#include "DesertBiome.h"

DesertBiome::DesertBiome(double e_min, double e_max, double m_min, double m_max)
    : Biome("desert", e_min, e_max, m_min, m_max) {}

void DesertBiome::generate_tile(
    unsigned int x, unsigned int y, double e, double m, TileMap &tiles) {
    const Material *mat = &Material::SAND;

    insert_into_world(x, y, e, m, mat, tiles);
}