#ifndef REGENCY_FLATWORLDGEN_H
#define REGENCY_FLATWORLDGEN_H

#include "WorldGen.h"

namespace regency {
namespace world {
namespace gen {

class FlatWorldGen : public WorldGen {
  public:
    virtual void generate(TileMap& tiles, sf::Texture& world_map);
};
}
}
}

#endif // REGENCY_FLATWORLDGEN_H
