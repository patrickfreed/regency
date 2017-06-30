#ifndef TEST_PROJECT_STANDARDWORLDGEN_H
#define TEST_PROJECT_STANDARDWORLDGEN_H


#include "WorldGen.h"
#include "biome/Biome.h"

class StandardWorldGen : public WorldGen {
public:
    StandardWorldGen(std::string name, double water_level);

    virtual void generate(TileMap& tiles, sf::Texture& world_map);

    void add_biome(std::unique_ptr<Biome> &&biome);

    // Not implemented for now, will be used to make custom biomes loaded from file.
    std::unique_ptr<Biome> make_biome(std::string name);
private:
    double _w;

    std::string _name;

    std::vector<std::unique_ptr<Biome>> _subregions;
};


#endif //TEST_PROJECT_STANDARDWORLDGEN_H
