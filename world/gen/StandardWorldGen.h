#ifndef REGENCY_STANDARDWORLDGEN_H
#define REGENCY_STANDARDWORLDGEN_H

#include "WorldGen.h"
#include "biome/Biome.h"

namespace regency {
namespace world {
namespace gen {

class StandardWorldGen : public WorldGen {
  public:
    StandardWorldGen(std::string name, double water_level);

    virtual void generate(TileMap& tiles, sf::Texture& world_map);

    void add_biome(std::unique_ptr<Biome>&& biome);

    std::vector<std::unique_ptr<Biome>>& get_subregions();

    // Not implemented for now, will be used to make custom biomes loaded from
    // file.
    std::unique_ptr<Biome> make_biome(std::string name);

  private:
    double _w;

    std::string _name;

    std::vector<std::unique_ptr<Biome>> _subregions;
};
}
}
}

#endif // REGENCY_STANDARDWORLDGEN_H
