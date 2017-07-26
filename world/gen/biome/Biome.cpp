
#include "Biome.h"

#include <iostream>
#include <sstream>

namespace regency {
namespace world {
namespace gen {

Biome::Biome(std::string name, double min_e, double max_e, double min_m, double max_m)
    : _e_range(min_e, max_e), _m_range(min_m, max_m), _ds(), name(name), _rnd(1, 100) {}

const std::pair<double, double> Biome::get_elevation_range() {
    return _e_range;
}

const std::pair<double, double> Biome::get_moisture_range() {
    return _m_range;
}

void Biome::add_tile(unsigned int x, unsigned int y, double e, double m, TileMap& tiles) {
    int id = x + y * WORLD_SIZE;

    _ds.make_set(id);

    int xm1 = x - 1 + y * WORLD_SIZE;
    int ym1 = x + (y - 1) * WORLD_SIZE;

    bool contains_xm1 = _ds.contains(xm1);
    bool contains_ym1 = _ds.contains(ym1);

    if (contains_xm1 && contains_ym1) {
        _ds.union_elements(ym1, xm1);
        _ds.union_elements(xm1, id);
    } else if (contains_xm1) {
        _ds.union_elements(id, xm1);
    } else if (contains_ym1) {
        _ds.union_elements(id, ym1);
    }

    generate_tile(x, y, e, m, tiles);
}

void Biome::generate_tile(unsigned int x, unsigned int y, double e, double m, TileMap& tiles) {
    std::vector<MaterialDefinition> options;
    for (auto& mat_def : _materials) {
        auto& e_range = mat_def.e_range;
        auto& m_range = mat_def.m_range;

        if (e > e_range.first && e < e_range.second && m > m_range.first && m < m_range.second) {
            options.push_back(mat_def);
        }
    }

    int chosen = static_cast<int>((double)_rnd.next_int() / 100.0 * (double)(options.size() - 1));
    tiles.set(x, y, std::move(std::make_unique<Tile>(x, y, options[chosen].material, e, m)));
}

void Biome::name_regions(TileMap& tiles) {
    std::cout << "starting tile generation for " << this->get_name() << std::endl;

    int count = 1;

    for (auto pair : _ds.get_sets()) {
        for (auto i : pair.second) {
            int x = i % WORLD_SIZE;
            int y = i / WORLD_SIZE;

            tiles.get(x, y).set_subregion_name(get_name() + std::to_string(count));
        }
        count++;
    }
}

bool Biome::contains(double e, double m) {
    return e >= _e_range.first && e <= _e_range.second && m >= _m_range.first &&
           m <= _m_range.second;
}
} // gen
} // world
} // regency