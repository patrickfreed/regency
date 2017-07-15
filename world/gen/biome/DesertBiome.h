#ifndef REGENCY_DESERTBIOME_H
#define REGENCY_DESERTBIOME_H

#include "Biome.h"

namespace regency {
namespace world {
namespace gen {

class DesertBiome : public Biome {
  public:
    DesertBiome(double, double, double, double);

    virtual void generate_tile(unsigned int x, unsigned int y, double e, double m, TileMap& tiles);
};
}
}
}
#endif // REGENCY_DESERTBIOME_H
