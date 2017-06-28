
#ifndef TEST_PROJECT_FLATWORLDGEN_H
#define TEST_PROJECT_FLATWORLDGEN_H


#include "WorldGen.h"

class FlatWorldGen : public WorldGen {
public:
    virtual void generate(TileMap& tiles, sf::Texture& world_map);
};


#endif //TEST_PROJECT_FLATWORLDGEN_H
