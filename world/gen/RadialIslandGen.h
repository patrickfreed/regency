
#ifndef REGENCY_RADIALISLANDGEN_H
#define REGENCY_RADIALISLANDGEN_H

#include "WorldGen.h"

class RadialIslandGen : public WorldGen {
  public:
    void generate(vector<vector<Tile*>>& tiles, sf::Texture& world_map);
};

#endif // REGENCY_RADIALISLANDGEN_H
