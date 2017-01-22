
#ifndef TEST_PROJECT_RADIALISLANDGEN_H
#define TEST_PROJECT_RADIALISLANDGEN_H


#include "WorldGen.h"

class RadialIslandGen : public WorldGen {
public:
    void generate(vector<vector<Tile *>>& tiles, sf::Texture& world_map);
};


#endif //TEST_PROJECT_RADIALISLANDGEN_H
