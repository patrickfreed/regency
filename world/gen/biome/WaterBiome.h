
#ifndef TEST_PROJECT_WATERBIOME_H
#define TEST_PROJECT_WATERBIOME_H


#include "Biome.h"

class WaterBiome : public Biome {
public:
    WaterBiome();
    const Material *get_tile(double e, double m);
    //void generate_regions(vector<vector<Tile *>>& tiles);
};


#endif //TEST_PROJECT_WATERBIOME_H
