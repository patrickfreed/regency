
#ifndef REGENCY_BIOME_H
#define REGENCY_BIOME_H

/*
 * Like world gen, I want this to eventually to be read from json like file
 */

#include <string>
#include <unordered_map>
#include <unordered_set>

#include "../../../Defines.h"
#include "../../DisjointSet.h"
#include "../../Tile.h"
#include "../../World.h"
#include "../RandomGenerator.h"

namespace regency {
namespace world {
namespace gen {

class Biome {
  private:
    std::string name;

    DisjointSet _ds;

  public:
    std::string& get_name() {
        return name;
    }

    const std::pair<double, double> get_elevation_range();

    const std::pair<double, double> get_moisture_range();

    bool contains(double e, double m);

    void add_tile(unsigned int x, unsigned int y, double e, double m, TileMap& tiles);

    virtual void name_regions(TileMap& tiles);

  protected:
    Biome(std::string name, double min_e, double max_e, double min_m, double max_m);

    virtual void generate_tile(unsigned int x, unsigned int y, double e, double m, TileMap& tiles);

    std::vector<MaterialDefinition> _materials;

    RandomGenerator _rnd;

    const std::pair<double, double> _e_range;
    const std::pair<double, double> _m_range;
};
}
}
}

#endif // REGENCY_BIOME_H
