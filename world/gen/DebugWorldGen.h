
#ifndef REGENCY_DEBUGWORLDGEN_H
#define REGENCY_DEBUGWORLDGEN_H

#include "WorldGen.h"

class DebugWorldGen : public WorldGen {
  public:
    virtual void generate(vector<vector<Tile*>>& tiles, sf::Texture& world_map);
};

#endif // REGENCY_DEBUGWORLDGEN_H
