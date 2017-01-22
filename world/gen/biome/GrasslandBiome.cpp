
#include <iostream>
#include <sstream>
#include "GrasslandBiome.h"

const Material *GrasslandBiome::get_tile(double e, double m) {
    const Material *material = nullptr;

    int tree = rnd.next_int();
    if (tree < 5) {
        cout << "tree on this tile!" << endl;
    }

    int grass = rnd.next_int();
    if (grass < 25) {
        material = &Material::NORTHERN_TURF;
    } else if (grass < 50) {
        material = &Material::BLUEGRASS;
    } else if (grass < 75) {
        material = &Material::FESCUE;
    } else {
        material = &Material::RYEGRASS;
    }

    return material;
}

GrasslandBiome::GrasslandBiome() : Biome("grassland", 0, 0, 0, 0), rnd(1, 100) {
}
