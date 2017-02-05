
#ifndef TEST_PROJECT_GRASSLAND_H
#define TEST_PROJECT_GRASSLAND_H


#include "Biome.h"
#include "../RandomGenerator.h"

class GrasslandBiome : public Biome {
public:
    GrasslandBiome();
    const Material *get_tile(double e, double m);

private:
    RandomGenerator rnd;
};


#endif //TEST_PROJECT_GRASSLAND_H
