
#ifndef REGENCY_MOUNTAINBIOME_H
#define REGENCY_MOUNTAINBIOME_H

#include "Biome.h"

namespace regency {
namespace world {
namespace gen {

class MountainBiome : public Biome {
  public:
    MountainBiome(double, double, double, double);

    virtual void generate_tile(unsigned int, unsigned int, double e, double m, TileMap&);
};
}
}
}

#endif // REGENCY_MOUNTAINBIOME_H
