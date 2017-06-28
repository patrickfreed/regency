
#ifndef TEST_PROJECT_WORLDGEN_H
#define TEST_PROJECT_WORLDGEN_H

/*
 * Class for supporting different types of worlds
 * No idea how to define this just yet, will change immensely.
 * Probably define values from disk, e.g. json
 */

#include <vector>
#include <noise/module/perlin.h>
#include "../Tile.h"
#include "../../Defines.h"

class WorldGen {
public:
    virtual void generate(TileMap& tiles, sf::Texture& world_map) = 0;
protected:
    //virtual double elevation(double nx, double ny) = 0;
    double noise(double nx, double ny);
    WorldGen();
private:
    noise::module::Perlin _gen;
};

#endif //TEST_PROJECT_WORLDGEN_H
