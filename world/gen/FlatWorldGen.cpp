
#include "FlatWorldGen.h"

#include <iostream>
#include <sstream>

#include "../DisjointSet.h"
#include "biome/GrasslandBiome.h"

namespace regency {
namespace world {
namespace gen {

void FlatWorldGen::generate(TileMap& tiles, sf::Texture& world_map) {
    world_map.create(WORLD_SIZE, WORLD_SIZE);
    sf::Uint8* pixels = new sf::Uint8[WORLD_SIZE * WORLD_SIZE * 4];

    DisjointSet ds;

    // Elevations
    const double WATER_CUTOFF = 0.4;
    const double MOUNTAIN_CUTOFF = 0.8;
    const double MOUNTAIN_PEAK_CUTOFF = 0.9;

    // Moistures
    const double JUNGLE_CUTOFF = 0.7;
    const double DESERT_CUTOFF = 0.3;

    RandomGenerator rnd(1, 100);

    for (unsigned int y = 0; y < WORLD_SIZE; ++y) {
        for (unsigned int x = 0; x < WORLD_SIZE; ++x) {
            const Material* mat;

            double nx = (double)x / (double)WORLD_SIZE - 0.5,
                   ny = (double)y / (double)WORLD_SIZE - 0.5;

            double e = noise(nx * 2.0, ny * 2.0);
            double m = 0.5 * m_noise(1 * nx, 1 * ny) + 0.5 * m_noise(2 * nx, 2 * ny) +
                       0.25 * m_noise(4 * nx, 2 * ny);

            if (e > MOUNTAIN_PEAK_CUTOFF) {
                mat = &Material::SNOW;
            } else if (e > MOUNTAIN_CUTOFF) {
                mat = &Material::ROCK;
            } else if (e > WATER_CUTOFF) {
                int grass = rnd.next_int();

                if (e - WATER_CUTOFF < 0.025) {
                    mat = &Material::SAND;
                } else if (m > JUNGLE_CUTOFF) {
                    mat = &Material::BLUEGRASS;
                } else if (m < DESERT_CUTOFF) {
                    mat = &Material::SAND;
                } else {
                    if (grass < 25) {
                        mat = &Material::NORTHERN_TURF;
                    } else if (grass < 50) {
                        mat = &Material::NORTHERN_TURF;
                    } else if (grass < 75) {
                        mat = &Material::FESCUE;
                    } else {
                        mat = &Material::RYEGRASS;
                    }
                }
            } else {
                mat = &Material::SALT_WATER;
            }

            // Generate world map
            sf::Color color;
            if (x % 100 == 0 || y % 100 == 0) {
                color = sf::Color::Red;
                // color = mat->get_color();
            } else {
                color = mat->get_color();
            }
            pixels[(x + y * WORLD_SIZE) * 4 + 0] = color.r;
            pixels[(x + y * WORLD_SIZE) * 4 + 1] = color.g;
            pixels[(x + y * WORLD_SIZE) * 4 + 2] = color.b;
            pixels[(x + y * WORLD_SIZE) * 4 + 3] = color.a;

            // TODO: replace strict material equivalence with land/water equivalence
            int xdiff = x ? 1 : 0;
            int ydiff = y ? 1 : 0;

            int id = x + y * WORLD_SIZE;
            int xm1 = x - 1 + y * WORLD_SIZE;
            int ym1 = x + (y - 1) * WORLD_SIZE;
            ds.make_set(id);

            auto equal = [](const Material* a, const Material* b) {
                return a->is_solid() == b->is_solid();
            };

            /*
            if (xdiff > 0 && ydiff > 0) {
                const Material* m1 = tiles[x - 1][y]->get_material();
                const Material* m2 = tiles[x][y - 1]->get_material();

                if (equal(m1, m2) && equal(mat, m1)) {
                    ds.union_elements(ym1, xm1);
                    ds.union_elements(id, xm1);
                } else if (equal(mat, m1)) {
                    ds.union_elements(id, xm1);
                } else if (equal(mat, m2)) {
                    ds.union_elements(id, ym1);
                }
            } else if (xdiff > 0) {
                if (equal(mat, tiles[x - 1][y]->get_material())) {
                    ds.union_elements(id, xm1);
                }
            } else if (ydiff > 0) {
                if (equal(mat, tiles[x][y - 1]->get_material())) {
                    ds.union_elements(id, ym1);
                }
            }

            tiles[x].insert(tiles[x].begin() + y,
                            std::move(std::make_unique<Tile>(x, y, mat, e, m)));
                            */
        }
    }

    std::cout << "done generation." << std::endl;
    std::cout << "identifying regions..." << std::endl;

    auto regions = ds.get_sets();
    int r_counter = 0;

    // regions
    int ocean = 1;
    int pond = 1;
    int lake = 1;
    int continent = 1;
    int island = 1;

    // subregions
    int forest = 1;
    int desert = 1;
    int mountain = 1;

    auto similarity = [](Tile& t1, Tile& t2) {
        double score = 1.0;

        score -= fabs(t1.get_moisture() - t2.get_moisture());
        score -= fabs(t1.get_elevation() - t2.get_elevation());

        score -= t1.get_material()->is_solid() == t2.get_material()->is_solid() ? 0 : 10;

        return score > 0.9;
    };

    DisjointSet r_ds;
    for (auto& r : regions) {
        int sample = *r.second.begin();
        int xs = sample % WORLD_SIZE;
        int ys = sample / WORLD_SIZE;

        bool land = tiles.get(xs, ys)->get_material()->is_solid();
        std::ostringstream oss;
        if (!land) {
            if (r.second.size() >= OCEAN_SIZE) {
                oss << "Ocean " << ocean++;
            } else if (r.second.size() >= LAKE_SIZE) {
                oss << "Lake " << lake++;
            } else {
                oss << "Pond " << pond++;
            }
        } else {
            if (r.second.size() >= CONTINENT_SIZE) {
                oss << "Continent " << continent++;
            } else {
                oss << "Island " << island++;
            }
        }
        /*
                for (auto i : r.second) {
                    int x = i % WORLD_SIZE;
                    int y = i / WORLD_SIZE;

                    r_ds.make_set(i);

                    Tile t = *tiles[x][y];

                    tiles[x][y]->set_region_name(oss.str());

                    const double SIMILARITY = 0.9;

                    if (x > 0 && y > 0) {
                        Tile& m1 = *tiles[x - 1][y];
                        Tile& m2 = *tiles[x][y - 1];

                        if (similarity(m1, m2) && similarity(t, m1)) {
                            ds.union_elements(i - 1, i + WORLD_SIZE);
                            ds.union_elements(i, i + 1);
                        } else if (similarity(t, m1)) {
                            ds.union_elements(i, i - 1);
                        } else if (similarity(t, m2)) {
                            ds.union_elements(i, i - WORLD_SIZE);
                        }
                    } else if (x > 0) {
                        if (similarity(t, *tiles[x - 1][y])) {
                            ds.union_elements(i, i - 1);
                        }
                    } else if (y) {
                        if (similarity(t, *tiles[x][y - 1])) {
                            ds.union_elements(i, i - WORLD_SIZE);
                        }
                    }
                }
                */
        r_counter++;
    }
    std::cout << "done regions" << std::endl;

    std::cout << "making sub regions" << std::endl;

    auto sub_regions = r_ds.get_sets();
    int sub_counter = 1;

    for (auto& r : regions) {
        int sample = *r.second.begin();
        int xs = sample % WORLD_SIZE;
        int ys = sample / WORLD_SIZE;

        std::string name = "sub_region" + std::to_string(sub_counter++);
        for (auto& i : r.second) {
            int x = i % WORLD_SIZE;
            int y = i / WORLD_SIZE;

            tiles.get(x, y)->set_subregion_name(name);
        }
    }

    world_map.update(pixels);

    delete[] pixels;
}
}
}
}
