
#include <iostream>
#include "FlatWorldGen.h"
#include "../../Defines.h"
#include "biome/GrasslandBiome.h"
#include "biome/WaterBiome.h"
#include "biome/MountainBiome.h"

void FlatWorldGen::generate(vector<vector<Tile *>> &tiles, sf::Texture &world_map) {
    GrasslandBiome g_biome;
    WaterBiome w_biome;
    MountainBiome m_biome;

    world_map.create(WORLD_SIZE, WORLD_SIZE);
    sf::Uint8 *pixels = new sf::Uint8[WORLD_SIZE * WORLD_SIZE * 4];
    int size = WORLD_SIZE * DUP_FACTOR;
    const double WATER_CUTOFF = 0.4;
    const double MOUNTAIN_CUTOFF = 0.8;

    for (unsigned int y = 0; y < WORLD_SIZE; ++y) {
        for (unsigned int x = 0; x < WORLD_SIZE; ++x) {
            const Material *mat;

            double nx = (double)x/WORLD_SIZE - 0.5, ny = (double)y/WORLD_SIZE - 0.5;

            double e = noise(nx * 2.0, ny * 2.0);
            double m = 0;

            if (e > MOUNTAIN_CUTOFF) {
                m_biome.add_tile(x, y, e, 0);
                mat = &Material::ROCK;
            } else if (e > WATER_CUTOFF) {
                g_biome.add_tile(x, y, e, 0);
                mat = &Material::RYEGRASS;
            } else {
                w_biome.add_tile(x, y, e, 0);
                mat = &Material::SALT_WATER;
            }

            sf::Color color;
            if (x % 100 == 0 || y % 100 == 0) {
                color = sf::Color::Red;
                //color = mat->get_color();
            } else {
                color = mat->get_color();
            }
            pixels[(x + y * WORLD_SIZE) * 4 + 0] = color.r;
            pixels[(x + y * WORLD_SIZE) * 4 + 1] = color.g;
            pixels[(x + y * WORLD_SIZE) * 4 + 2] = color.b;
            pixels[(x + y * WORLD_SIZE) * 4 + 3] = color.a;

            //tiles[x][y] = new Tile(x, y, mat, "asdf");

            double part = (double) (x + y*WORLD_SIZE) / (WORLD_SIZE * WORLD_SIZE);
            int percent = (int)(part * 100);
            if (percent && percent % 10 == 0) {
                //cout << percent << endl;
            }
        }
    }
    cout << "done tiles\n";
    m_biome.generate_tiles(tiles);
    g_biome.generate_tiles(tiles);
    w_biome.generate_tiles(tiles);

    world_map.update(pixels);
    delete [] pixels;
}
