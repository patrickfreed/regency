#include "World.h"

#include <sstream>
#include <iostream>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../entity/HumanActor.h"
#include "../Mouse.h"
#include "../Assets.h"
#include "gen/FlatWorldGen.h"

World::World(std::string name) : name(name), tiles() {
    this->texture.loadFromFile("../res/tileset.png");

    this->gen.SetSeed(time(NULL));
    this->zoom_level = 1;
    this->tile_size = 10;

    this->tiles.resize(WORLD_SIZE * DUP_FACTOR);
    for (int x = 0; x < WORLD_SIZE * DUP_FACTOR; x++) {
        this->tiles[x].reserve(WORLD_SIZE * DUP_FACTOR);
    }

    // zoom level 0
    this->world_map.create(WINDOW_SIZE, WINDOW_SIZE);
    this->sprite.setTexture(this->world_map);

    // zoom level 1
    this->pos.x = 0;
    this->pos.y = 0;
    this->tile_map.setPrimitiveType(sf::Quads);
    this->tile_map.resize(RENDER_SIZE * RENDER_SIZE * 4);
    for (int x = 0; x < RENDER_SIZE; ++x) {
        for (int y = 0; y < RENDER_SIZE; ++y) {
            sf::Vertex *quad = &(this->tile_map[(x + y * RENDER_SIZE) * 4]);
            quad[0].position = sf::Vector2f(x * tile_size, y * tile_size);
            quad[1].position = sf::Vector2f((x + 1) * tile_size, y * tile_size);
            quad[2].position = sf::Vector2f((x + 1) * tile_size, (y + 1) * tile_size);
            quad[3].position = sf::Vector2f(x * tile_size, (y + 1) * tile_size);
        }
    }
}

double World::noise(double nx, double ny) {
    return gen.GetValue(nx, ny, 0.0) / 2.0 + 0.5;
}

void World::generate() {
    FlatWorldGen world_gen;
    world_gen.generate(this->tiles, this->world_map);
    int x;
}

/*
void generate_old() {
    this->gen.SetSeed(time(NULL));
    srand((unsigned int) time(NULL));

    sf::Uint8 *pixels = new sf::Uint8[WORLD_SIZE * WORLD_SIZE * 4];
    // texture.create(WORLD_SIZE * 10 * DUP_FACTOR, WORLD_SIZE * 10 * DUP_FACTOR);

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

            Material *mat;

            if (e < 0.26) {
                mat = &Material::SALT_WATER;
            } else if (e < 0.33) {
                mat = &Material::SAND;
            } else if (e > 0.87) {
                mat = &Material::SNOW;
            } else if (e > 0.70) {
                mat = &Material::ROCK;
            } else if (e > 0.65) {
                mat = &Material::ROCKY_DIRT;
            } else {
                if (m > 0.75) {
                    mat = &Material::MUDDY_DIRT; // rain forest

                } else {
                    mat = &Material::DIRT;
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
                        this->tiles[ax][ay] = new Tile(ax, ay, mat);
                    }
                }
            }
        }
    }

    this->world_map.create(WORLD_SIZE, WORLD_SIZE);
    this->world_map.update(pixels);
    this->sprite.setTextureRect(sf::IntRect(0, 0, WINDOW_SIZE, WINDOW_SIZE));

    this->tiles[0][0]->set_actor((Actor *) new HumanActor(*this));

    delete [] pixels;
}
*/
string& World::get_name() {
    return this->name;
}

void World::render(sf::RenderWindow& window) {
    if (zoom_level == 1) {
        for (int x = 0; x < min(WINDOW_SIZE / tile_size, WORLD_SIZE); x++) {
            for (int y = 0; y < min(WINDOW_SIZE / tile_size, WORLD_SIZE); y++) {
                int xx = x + pos.x / tile_size;
                int yy = (y + pos.y / tile_size);

                std::unique_ptr<Tile> &t = tiles[xx][yy];

                int tile_number = t->get_material()->get_tile_number();
                int tu = tile_number % (this->texture.getSize().x / tile_size);
                int tv = tile_number / (this->texture.getSize().x / tile_size);

                sf::Vertex *q = &(this->tile_map[(x + y * RENDER_SIZE) * 4]);
                q[0].texCoords = sf::Vector2f(tu * tile_size, tv * tile_size);
                q[1].texCoords = sf::Vector2f((tu + 1) * tile_size, tv * tile_size);
                q[2].texCoords = sf::Vector2f((tu + 1) * tile_size, (tv + 1) * tile_size);
                q[3].texCoords = sf::Vector2f(tu * tile_size, (tv + 1) * tile_size);
            }
        }

        window.draw(this->tile_map, &this->texture);

        sf::Vector2i mouse = Mouse::get_mouse_position();
        const std::unique_ptr<Tile>& hover = this->get_hovered_tile();
        if (hover) {
            sf::Text region_name_text;
            region_name_text.setFont(Assets::font);
            region_name_text.setString(hover->get_region_name());
            region_name_text.setPosition(WINDOW_SIZE / 2 - (hover->get_region_name().length() * 10), 20);
            region_name_text.setOutlineColor(sf::Color::Black);
            region_name_text.setOutlineThickness(2.5);
            window.draw(region_name_text);
        }
        /*for (int x = 0; x < WINDOW_SIZE / tile_size; x++) {
            for (int y = 0; y < WINDOW_SIZE / tile_size; y++) {
                int xx = x + pos.left / tile_size;
                int yy = (y + pos.top / tile_size);

                ostringstream coords;
                coords << xx << "," << yy;

                Tile *t = tiles[xx][yy];
                t->render(window, x * tile_size, y * tile_size, zoom_level);
            }
        }*/
    } else {
        //this->sprite.scale(1.0f, 1.0f);
        window.draw(this->sprite);
    }
}

bool World::move(int x, int y, World::Direction d) {
    int xdiff = d == WEST ? -1 : (d == EAST ? 1 : 0);
    int ydiff = d == NORTH ? -1 : (d == SOUTH ? 1 : 0);

    std::unique_ptr<Tile>& a = this->tiles[x][y];
    std::unique_ptr<Tile>& aa = this->tiles[x + xdiff][y + ydiff];

    if (a->get_actor() && !(aa->get_actor())) {
        aa->set_actor(a->get_actor());
        a->set_actor(nullptr);
        return true;
    }
    return false;
}

void World::tick() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        if (pos.y > 10) {
            pos.y -= 10;
        }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        if (pos.y + RENDER_SIZE * 10 < WORLD_SIZE * 10 * DUP_FACTOR) {
            pos.y += 10;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        if (pos.x > 10) {
            pos.x -= 10;
        }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        if (pos.x + RENDER_SIZE * 10 < WORLD_SIZE * 10 * DUP_FACTOR) {
            pos.x += 10;
        }
    }
    //this->sprite.setTextureRect(sf::IntRect(left, top, RENDER_SIZE * 10, RENDER_SIZE * 10));

    /*for (int x = 0; x < WORLD_SIZE; x++) {
        for (int y = 0; y < WORLD_SIZE; y++) {
            ostringstream coords;
            coords << x << "," << y;

            Tile *t = tiles[coords.str()];
            t->tick();
        }
    }*/
}

void World::move_camera(int dx, int dy) {
    sf::IntRect rect = this->sprite.getTextureRect();

    int left = rect.left + dx;
    int top = rect.top + dy;

    this->sprite.setTextureRect(sf::IntRect(left, top, WINDOW_SIZE, WINDOW_SIZE));
}

void World::zoom(bool in) {
    if (zoom_level == 0) {
        this->zoom_level += 1;
        tile_size *= 10;

        sf::Vector2i mouse_pos = Mouse::get_mouse_position();

        int left = max(0, mouse_pos.x - mouse_pos.x % 100) * tile_size * DUP_FACTOR;
        int top = max(0, mouse_pos.y - mouse_pos.y % 100) * tile_size * DUP_FACTOR;

        this->pos.x = left;
        this->pos.y = top;
    } else if (zoom_level == 1) {
        zoom_level -= 1;
        tile_size /= 10;
        this->sprite.setTextureRect(sf::IntRect(0, 0, WINDOW_SIZE, WINDOW_SIZE));
    }
}

const std::unique_ptr<Tile>& World::get_hovered_tile() {
    sf::Vector2i mouse_pos = Mouse::get_mouse_position();

    if (zoom_level != 1 || mouse_pos.x < 0 || mouse_pos.x >= min(tile_size*WORLD_SIZE, WINDOW_SIZE) || mouse_pos.y < 0 || mouse_pos.y >= min(tile_size*WORLD_SIZE, WINDOW_SIZE)) {
        return tiles[0][0];
    }

    int xx = this->pos.x / tile_size + mouse_pos.x / tile_size;
    int yy = this->pos.y / tile_size + mouse_pos.y / tile_size;

    return this->tiles[xx][yy];
}
