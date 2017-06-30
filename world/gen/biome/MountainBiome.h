
#ifndef TEST_PROJECT_MOUNTAINBIOME_H
#define TEST_PROJECT_MOUNTAINBIOME_H


#include "Biome.h"

class MountainBiome : public Biome {
public:
    MountainBiome(double, double, double, double);
    virtual void generate_tile(unsigned int, unsigned int, double e, double m, TileMap&);
};


#endif //TEST_PROJECT_MOUNTAINBIOME_H
