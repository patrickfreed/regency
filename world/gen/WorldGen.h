
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

using namespace std;

class WorldGen {
protected:
    WorldGen();
private:
    noise::module::Perlin gen;
public:
    virtual void generate(vector<vector<Tile *>>& tiles, sf::Texture& world_map) = 0;
    double noise(double nx, double ny);
};


#endif //TEST_PROJECT_WORLDGEN_H
