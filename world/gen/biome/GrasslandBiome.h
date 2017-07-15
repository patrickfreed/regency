
#ifndef REGENCY_GRASSLAND_H
#define REGENCY_GRASSLAND_H

#include "../RandomGenerator.h"
#include "Biome.h"

namespace regency {
namespace world {
namespace gen {

class GrasslandBiome : public Biome {
  public:
    GrasslandBiome(double, double, double, double);

    virtual void generate_tile(unsigned int x, unsigned int y, double e, double m, TileMap& tiles);
};
}
}
}

#endif // REGENCY_GRASSLAND_H
