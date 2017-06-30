//
// Created by Patrick Freed on 6/29/17.
//

#ifndef TEST_PROJECT_DESERTBIOME_H
#define TEST_PROJECT_DESERTBIOME_H


#include "Biome.h"

class DesertBiome : public Biome {
public:
    DesertBiome(double, double, double, double);
    virtual void generate_tile(unsigned int x, unsigned int y, double e, double m, TileMap& tiles);
};


#endif //TEST_PROJECT_DESERTBIOME_H
