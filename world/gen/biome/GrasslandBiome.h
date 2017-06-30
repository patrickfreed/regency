
#ifndef TEST_PROJECT_GRASSLAND_H
#define TEST_PROJECT_GRASSLAND_H


#include "Biome.h"
#include "../RandomGenerator.h"

class GrasslandBiome : public Biome {
public:
    GrasslandBiome(double, double, double, double);
    virtual void generate_tile(unsigned int x, unsigned int y, double e, double m, TileMap& tiles);
};


#endif //TEST_PROJECT_GRASSLAND_H
