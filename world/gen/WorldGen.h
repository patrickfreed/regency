
#ifndef REGENCY_WORLDGEN_H
#define REGENCY_WORLDGEN_H

/*
 * Class for supporting different types of worlds
 * No idea how to define this just yet, will change immensely.
 * Probably define values from disk, e.g. json
 */

#include <vector>

#include <noise/module/perlin.h>

#include "../../Defines.h"
#include "../Tile.h"
#include "../TileMap.h"

namespace regency {
namespace world {
namespace gen {

class WorldGen {
  public:
    virtual void generate(TileMap& tiles, sf::Texture& world_map) = 0;

  protected:
    WorldGen();

    // virtual double elevation(double nx, double ny) = 0;
    double noise(double nx, double ny);

    double m_noise(double nx, double ny);

  private:
    noise::module::Perlin _moisture;
    noise::module::Perlin _gen;
};
}
}
}
#endif // REGENCY_WORLDGEN_H
