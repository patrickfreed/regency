
#include <iostream>
#include "DebugWorldGen.h"
#include "../../Defines.h"
#include "biome/GrasslandBiome.h"

void DebugWorldGen::generate(vector<vector<Tile *>> &tiles, sf::Texture &world_map) {
    GrasslandBiome g_biome;

    sf::Uint8 *pixels = new sf::Uint8[WORLD_SIZE * WORLD_SIZE * 4];
    int size = WORLD_SIZE * DUP_FACTOR;

    for (unsigned int x = 0; x < WORLD_SIZE; x++) {
        for (unsigned int y = 0; y < WORLD_SIZE; y++) {
            const Material *mat;

            double e = 0;
            double m = 0;

            if (x < WORLD_SIZE / 2) {
                if (y < WORLD_SIZE / 2) {
                    mat = &Material::SNOW;
                } else {
                    mat = &Material::SALT_WATER;
                }
            } else {
                if (y < WORLD_SIZE / 2) {
                    g_biome.add_tile(x, y, e, m);
                    mat = NULL;
                } else {
                    mat = &Material::SAND;
                }
            }

            if (mat)
                for (unsigned int xx = 0; xx < DUP_FACTOR; xx++) {
                    for (unsigned int yy = 0; yy < DUP_FACTOR; yy++) {
                        unsigned int ax = x * DUP_FACTOR + xx;
                        unsigned int ay = y * DUP_FACTOR + yy;

                        if (tiles[ax][ay]) {
                            tiles[ax][ay]->set_material(mat);
                        } else {
                            tiles[ax][ay] = new Tile(ax, ay, mat, "asdf");
                        }
                    }
                }

            sf::Color color;

            if (x % 100 == 0 || y % 100 == 0) {
                color = sf::Color::Red;
            } else if (!mat) {
                color = sf::Color::Green;
            } else {
                color = mat->get_color();
            }
            pixels[(x + y * WORLD_SIZE) * 4 + 0] = color.r;
            pixels[(x + y * WORLD_SIZE) * 4 + 1] = color.g;
            pixels[(x + y * WORLD_SIZE) * 4 + 2] = color.b;
            pixels[(x + y * WORLD_SIZE) * 4 + 3] = color.a;
        }
    }
    g_biome.generate_regions();

    world_map.update(pixels);
    delete [] pixels;
}
