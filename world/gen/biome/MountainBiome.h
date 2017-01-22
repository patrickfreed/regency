
#ifndef TEST_PROJECT_MOUNTAINBIOME_H
#define TEST_PROJECT_MOUNTAINBIOME_H


#include "Biome.h"

class MountainBiome : public Biome {
public:
    MountainBiome();
    virtual const Material *get_tile(double e, double m);
};


#endif //TEST_PROJECT_MOUNTAINBIOME_H
