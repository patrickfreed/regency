
#ifndef TEST_PROJECT_WATERBIOME_H
#define TEST_PROJECT_WATERBIOME_H


#include "Biome.h"

class WaterBiome : public Biome {
public:
    WaterBiome(double, double, double, double);
    virtual void generate_tile(unsigned int x, unsigned int y, double e, double m, TileMap& tiles);
};


#endif //TEST_PROJECT_WATERBIOME_H
