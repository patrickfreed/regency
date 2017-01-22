
#ifndef TEST_PROJECT_DEBUGWORLDGEN_H
#define TEST_PROJECT_DEBUGWORLDGEN_H


#include "WorldGen.h"

class DebugWorldGen : public WorldGen {
public:
    virtual void generate(vector<vector<Tile *>>& tiles, sf::Texture& world_map);
};


#endif //TEST_PROJECT_DEBUGWORLDGEN_H
