
#ifndef REGENCY_WATERBIOME_H
#define REGENCY_WATERBIOME_H

#include "Biome.h"

namespace regency {
namespace world {
namespace gen {

class WaterBiome : public Biome {
  public:
    WaterBiome(double, double, double, double);

    virtual void generate_tile(unsigned int x, unsigned int y, double e, double m, TileMap& tiles);
};
}
}
}

#endif // REGENCY_WATERBIOME_H
