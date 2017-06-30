#include "StandardWorldGen.h"

#include <iostream>
#include <sstream>

void StandardWorldGen::generate(TileMap &tiles, sf::Texture &world_map) {
    world_map.create(WORLD_SIZE, WORLD_SIZE);
    sf::Uint8 *pixels = new sf::Uint8[WORLD_SIZE * WORLD_SIZE * 4];

    // Continent components
    DisjointSet ds;
    for (unsigned int y = 0; y < WORLD_SIZE; ++y) {
        for (unsigned int x = 0; x < WORLD_SIZE; ++x) {
            double nx = (double)x / (double)WORLD_SIZE - 0.5,
                   ny = (double)y / (double)WORLD_SIZE - 0.5;

            // TODO: make this configurable
            double e = noise(nx * 2.0, ny * 2.0);
            double m = 0.5 * m_noise(1 * nx, 1 * ny) + 0.25 * m_noise(2 * nx, 2 * ny) +
                       0.25 * m_noise(4 * nx, 2 * ny);

            bool inserted = false;
            for (auto &biome : _subregions) {
                if ((inserted = biome->contains(e, m))) {
                    biome->add_tile(x, y, e, m, tiles);
                    break;
                }
            }

            if (!inserted) {
                throw std::runtime_error("Bad generator spec, missed tile");
            }

            // TODO: update this to something else
            // Generate world map
            const Material *mat = tiles[x][y]->get_material();
            const sf::Color *color;
            if (x % 100 == 0 || y % 100 == 0) {
                color = &sf::Color::Red;
            } else {
                color = &mat->get_color();
            }
            pixels[(x + y * WORLD_SIZE) * 4 + 0] = color->r;
            pixels[(x + y * WORLD_SIZE) * 4 + 1] = color->g;
            pixels[(x + y * WORLD_SIZE) * 4 + 2] = color->b;
            pixels[(x + y * WORLD_SIZE) * 4 + 3] = color->a;

            // TODO: do this continent stuff elsewhere
            int id = x + y * WORLD_SIZE;
            int xm1 = x - 1 + y * WORLD_SIZE;
            int ym1 = x + (y - 1) * WORLD_SIZE;
            ds.make_set(id);

            auto equal = [](const Material *a, const Material *b) {
                return a->is_solid() == b->is_solid();
            };

            if (x > 0 && y > 0) {
                const Material *m1 = tiles[x - 1][y]->get_material();
                const Material *m2 = tiles[x][y - 1]->get_material();

                if (equal(m1, m2) && equal(mat, m1)) {
                    ds.union_elements(ym1, xm1);
                    ds.union_elements(id, xm1);
                } else if (equal(mat, m1)) {
                    ds.union_elements(id, xm1);
                } else if (equal(mat, m2)) {
                    ds.union_elements(id, ym1);
                }
            } else if (x > 0) {
                if (equal(mat, tiles[x - 1][y]->get_material())) {
                    ds.union_elements(id, xm1);
                }
            } else if (y > 0) {
                if (equal(mat, tiles[x][y - 1]->get_material())) {
                    ds.union_elements(id, ym1);
                }
            }
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

    for (auto &r : regions) {
        int sample = *r.second.begin();
        int xs = sample % WORLD_SIZE;
        int ys = sample / WORLD_SIZE;

        bool land = tiles[xs][ys]->get_material()->is_solid();
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

        for (auto i : r.second) {
            int x = i % WORLD_SIZE;
            int y = i / WORLD_SIZE;

            std::unique_ptr<Tile> &t = tiles[x][y];
            t->set_region_name(oss.str());
        }
    }
    std::cout << "done regions" << std::endl;

    world_map.update(pixels);

    delete[] pixels;

    for (auto &biome : _subregions) {
        biome->name_regions(tiles);
    }
}

StandardWorldGen::StandardWorldGen(std::string name, double water_level)
    : _name{name}, _w{water_level} {}

void StandardWorldGen::add_biome(std::unique_ptr<Biome> &&biome) {
    _subregions.push_back(std::move(biome));
}