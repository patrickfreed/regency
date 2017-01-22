
#include "RadialIslandGen.h"
#include "../../Defines.h"

void RadialIslandGen::generate(vector<vector<Tile *>> &tiles, sf::Texture& world_map) {
    sf::Uint8 *pixels = new sf::Uint8[WORLD_SIZE * WORLD_SIZE * 4];

    for (int x = 0; x < WORLD_SIZE; x++) {
        for (int y = 0; y < WORLD_SIZE; y++) {
            double nx = (double) x / (double) WORLD_SIZE - 0.5;
            double ny = (double) y / (double) WORLD_SIZE - 0.5;

            double global_frequency_modifier = 2.0;

            nx *= global_frequency_modifier;
            ny *= global_frequency_modifier;

            double e = 1 * noise(5.0 * nx, 5.0 * ny)
                       + 0.5 * noise(5.5 * nx, 5.5 * ny)
                       + 0.25 * noise(6.0 * nx, 6.0 * ny);
            //e = pow(e, 2.29);
            e /= 1.75;

            double center = WORLD_SIZE / 2.0;

            double a = 0.23;
            double b = 0.005;
            double c = 0.80;
            double d = sqrt(pow((double) x - center, 2) + pow((double) y - center + 5, 2));

            e = e + a - b * pow(d, c);

            double m = noise(nx, ny) + 0.5 * noise(2 * nx, 2 * ny) + 0.25 * noise(4 * nx, 2 * ny);
            m /= 1.75;

            const Material *mat;

            if (e < 0.26) {
                mat = &Material::SALT_WATER;
            } else if (e < 0.33) {
                mat = &Material::SAND;
            } else if (e > 0.87) {
                mat = &Material::SNOW;
            } else if (e > 0.70) {
                mat = &Material::ROCK;
            } else if (e > 0.65) {
                mat = &Material::ROCK;
            } else {
                if (m > 0.75) {
                    mat = &Material::NORTHERN_TURF; // rain forest

                } else {
                    mat = &Material::NORTHERN_TURF;
                }
            }

            sf::Color color;

            if (x % 100 == 0 || y % 100 == 0) {
                color = sf::Color::Red;
            } else {
                color = mat->get_color();
            }
            pixels[(x + y * WORLD_SIZE) * 4 + 0] = color.r;
            pixels[(x + y * WORLD_SIZE) * 4 + 1] = color.g;
            pixels[(x + y * WORLD_SIZE) * 4 + 2] = color.b;
            pixels[(x + y * WORLD_SIZE) * 4 + 3] = color.a;

            for (int xx = 0; xx < DUP_FACTOR; xx++) {
                for (int yy = 0; yy < DUP_FACTOR; yy++) {
                    int ax = x * DUP_FACTOR + xx;
                    int ay = y * DUP_FACTOR + yy;

                    if (tiles[ax][ay]) {
                        tiles[ax][ay]->set_material(mat);
                    } else {
                        tiles[ax][ay] = new Tile(ax, ay, mat, "");
                    }
                }
            }
        }
    }

    world_map.update(pixels);

    delete [] pixels;
}
