
#include "GrasslandBiome.h"

#include <iostream>
#include <sstream>

namespace regency {
namespace world {
namespace gen {

void GrasslandBiome::generate_tile(
    unsigned int x, unsigned int y, double e, double m, TileMap& tiles) {
    const Material* material = nullptr;

    int grass = _rnd.next_int();
    if (grass < 25) {
        material = &Material::NORTHERN_TURF;
    } else if (grass < 50) {
        material = &Material::BLUEGRASS;
    } else if (grass < 75) {
        material = &Material::FESCUE;
    } else {
        material = &Material::RYEGRASS;
    }

    std::unique_ptr<Tile> tile = std::make_unique<Tile>(x, y, material, e, m);

    int rnd_tree = _rnd.next_int();
    if (rnd_tree < 5) {
        Tree tree(TreeType::EVERGREEN, 10);
        (*tile).set_tree(tree);
    }

    tiles.set(x, y, std::move(tile));
}

GrasslandBiome::GrasslandBiome(double min_e, double max_e, double min_m, double max_m)
    : Biome("grassland", min_e, max_e, min_m, max_m, NameList::GRASSLANDS) {

    // Functionality of this class pretty much equivalent to generic biome with below
    /*
    const Material *grasses[] = {
        &Material::BLUEGRASS, &Material::NORTHERN_TURF, &Material::FESCUE, &Material::RYEGRASS};

    for (auto grass : grasses) {
        MaterialDefinition m;
        m.material = grass;
        m.e_range = std::make_pair<double, double>(std::move(min_e), std::move(max_e));
        m.m_range = std::make_pair<double, double>(std::move(min_m), std::move(max_m));
        _materials.push_back(m);
    }
     */
}
}
}
}