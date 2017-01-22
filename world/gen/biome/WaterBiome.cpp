
#include <sstream>
#include "WaterBiome.h"

WaterBiome::WaterBiome() : Biome("water", 0, 0, 0, 0) {
}

const Material *WaterBiome::get_tile(double e, double m) {
    return &Material::SALT_WATER;
}

/*void WaterBiome::generate_regions(vector<vector<Tile *>> &tiles) {
    unsigned int ocean = 0;
    unsigned int lake = 0;

    for (auto it = regions.begin(); it != regions.end(); ++it) {
        ostringstream name;
        Region *r = *it;


        if (r->size() > 50) {
            name << "Ocean " << ++ocean;
        } else {
            name << "Lake " << ++lake;
        }

        for (int t = 0; t < r->size(); t++) {
            ostringstream r_name;

            TileInfo t_info = (*r)[t];

            unsigned int x = t_info.first.first;
            unsigned int y = t_info.first.second;

            double e = t_info.second.first;
            double m = t_info.second.second;

            tiles[x][y] = new Tile(x, y, this->get_tile(e, m), name.str());
        }
    }
}*/
