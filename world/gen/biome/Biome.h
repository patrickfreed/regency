
#ifndef TEST_PROJECT_BIOME_H
#define TEST_PROJECT_BIOME_H

/*
 * Like world gen, I want this to eventually to be read from json like file
 */

#include <string>
#include <unordered_map>
#include <unordered_set>

#include "../../Tile.h"
#include "../../DisjointSet.h"
#include "../../../Defines.h"
#include "../RandomGenerator.h"

class Biome {
private:
    std::string name;

    DisjointSet _ds;

public:
    std::string& get_name() { return name; }

    const std::pair<double, double> get_elevation_range();
    const std::pair<double, double> get_moisture_range();

    bool contains(double e, double m);

    void add_tile(unsigned int x, unsigned int y, double e, double m, TileMap& tiles);

    virtual void name_regions(TileMap& tiles);
protected:
    Biome(std::string name, double min_e, double max_e, double min_m, double max_m);

    virtual void generate_tile(unsigned int x, unsigned int y, double e, double m, TileMap& tiles);

    void insert_into_world(unsigned int x, unsigned int y, double e, double m, const Material *mat, TileMap& tiles);

    std::vector<MaterialDefinition> _materials;

    rrandom::RandomGenerator _rnd;

    const std::pair<double, double> _e_range;
    const std::pair<double, double> _m_range;
};

#endif //TEST_PROJECT_BIOME_H
