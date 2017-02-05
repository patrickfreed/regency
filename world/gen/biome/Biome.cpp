
#include <sstream>
#include <iostream>
#include "Biome.h"
#include "../../../Defines.h"

Biome::Biome(string name, double min_e, double max_e, double min_m, double max_m) : e_range(min_e, max_e), m_range(min_m, max_m) {
    this->name = name;
}

const pair<double, double> Biome::get_elevation_range() {
    return this->e_range;
}

const pair<double, double> Biome::get_moisture_range() {
    return this->m_range;
}

void Biome::add_tile(unsigned int x, unsigned int y, double e, double m) {
    ostringstream oss;
    oss << x << "," << y;

    this->tile_infos.insert(make_pair(make_pair(x, y), make_pair(e, m)));
}

void Biome::generate_regions() {
    cout << "starting region generation" << this->name << endl;

    unordered_set<CoordinatePair, pair_hash> coords;

    for (auto it = this->tile_infos.begin(); it != this->tile_infos.end(); ++it) {
        CoordinatePair coord = it->first;
        coords.insert(coord);
    }
    cout << "done coords set\n";

    while (coords.size()) {
        //vector<TileInfo> region;
        unique_ptr<Region> region(new Region);
        CoordinatePair root = *coords.begin();
        unordered_set<CoordinatePair, pair_hash> to_check;

        to_check.insert(root);
        coords.erase(root);

        while (to_check.size()) {
            CoordinatePair next = *(to_check.begin());

            int x = next.first;
            int y = next.second;

            to_check.erase(next);
            region->tile_info.push_back(make_pair(make_pair(x, y), tile_infos[next]));

            CoordinatePair check = make_pair(x, y);

            for (unsigned int xx = max(x - 1, 0); xx <= min(x + 1, WORLD_SIZE); xx++) {
                for (unsigned int yy = max(y - 1, 0); yy <= min(y + 1, WORLD_SIZE); yy++) {
                    if (xx == x && yy == y) continue;

                    check.first = xx;
                    check.second = yy;

                    if (coords.find(check) != coords.end()) {
                        to_check.insert(check);
                        coords.erase(check);
                    }
                }
            }
        }

        this->get_region_name(*region);
        regs.push_back(move(region));
    }
    cout << "done region creation\n";
}

void Biome::generate_tiles(vector<vector<Tile *>> &tiles) {
    if (!this->regions.size()) {
        this->generate_regions();
    }

    cout << "starting tile generation for " << this->get_name() << "\n";

    for (auto it = regs.begin(); it != regs.end(); ++it) {
        Region& region = **it;
        vector<TileInfo>& region_tiles = region.tile_info;

        for (int t = 0; t < region_tiles.size(); t++) {
            TileInfo t_info = region_tiles[t];

            unsigned int x = t_info.first.first;
            unsigned int y = t_info.first.second;

            double e = t_info.second.first;
            double m = t_info.second.second;

            tiles[x][y] = new Tile(x, y, this->get_tile(e, m), region.name);
       }
    }
    cout << "done tile generation\n";
}

Biome::~Biome() {
    for (auto it = this->regions.begin(); it != regions.end(); ++it) {
        for (auto r = (*it)->begin(); r != (*it)->end(); ++r) {
            delete (*r);
        }
        delete (*it);
    }
}

string& Biome::get_region_name(Region& region) {
    region.name = this->get_name();
    return region.name;
}
