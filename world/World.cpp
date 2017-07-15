#include "World.h"

#include <iostream>
#include <sstream>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <chrono>

#include "../Assets.h"
#include "../Mouse.h"
#include "../entity/HumanActor.h"
#include "gen/FlatWorldGen.h"

World::World(std::string name) : name(name), tiles() {
    this->texture.loadFromFile("../res/tileset.png");

    this->gen.SetSeed(static_cast<int32_t>(time(NULL)));
    this->_zoom_level = ZOOM_LOCAL;

    // local zoom level 0
    this->world_map.create(WINDOW_SIZE, WINDOW_SIZE);
    this->sprite.setTexture(this->world_map);

    // global zoom level
    this->pos.x = 0;
    this->pos.y = 0;
    this->tile_map.setPrimitiveType(sf::Quads);
    this->tile_map.resize(RENDER_SIZE * RENDER_SIZE * 4);
    for (int x = 0; x < RENDER_SIZE; ++x) {
        for (int y = 0; y < RENDER_SIZE; ++y) {
            sf::Vertex *quad = &(this->tile_map[(x + y * RENDER_SIZE) * 4]);
            quad[0].position = sf::Vector2f(x * get_tile_size(), y * get_tile_size());
            quad[1].position = sf::Vector2f((x + 1) * get_tile_size(), y * get_tile_size());
            quad[2].position = sf::Vector2f((x + 1) * get_tile_size(), (y + 1) * get_tile_size());
            quad[3].position = sf::Vector2f(x * get_tile_size(), (y + 1) * get_tile_size());
        }
    }
}

double World::noise(double nx, double ny) {
    return gen.GetValue(nx, ny, 0.0) / 2.0 + 0.5;
}

void World::generate(WorldGen &generator) {
    tiles.clear();

    this->tiles.resize(WORLD_SIZE * DUP_FACTOR);
    for (int x = 0; x < WORLD_SIZE * DUP_FACTOR; x++) {
        this->tiles[x].reserve(WORLD_SIZE * DUP_FACTOR);
    }

    std::cout << "starting world generation..." << std::endl;

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    generator.generate(tiles, world_map);

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;

    std::cout << "generation completed. elapsed time: " << elapsed_seconds.count() << " second(s)" << std::endl;
}

string &World::get_name() {
    return this->name;
}

void World::render(sf::RenderWindow &window) {
    if (_zoom_level == ZOOM_LOCAL) {
        for (int x = 0; x < min(WINDOW_SIZE / get_tile_size(), WORLD_SIZE); x++) {
            for (int y = 0; y < min(WINDOW_SIZE / get_tile_size(), WORLD_SIZE); y++) {
                int xx = x + pos.x / get_tile_size();
                int yy = (y + pos.y / get_tile_size());

                std::unique_ptr<Tile> &t = tiles[xx][yy];

                int tile_number = t->get_material()->get_tile_number();
                int tu = tile_number % (this->texture.getSize().x / get_tile_size());
                int tv = tile_number / (this->texture.getSize().x / get_tile_size());

                sf::Vertex *q = &(this->tile_map[(x + y * RENDER_SIZE) * 4]);
                q[0].texCoords = sf::Vector2f(tu * get_tile_size(), tv * get_tile_size());
                q[1].texCoords = sf::Vector2f((tu + 1) * get_tile_size(), tv * get_tile_size());
                q[2].texCoords = sf::Vector2f((tu + 1) * get_tile_size(), (tv + 1) * get_tile_size());
                q[3].texCoords = sf::Vector2f(tu * get_tile_size(), (tv + 1) * get_tile_size());
            }
        }
        window.draw(this->tile_map, &this->texture);

        const std::unique_ptr<Tile>& hover = get_hovered_tile();
        if (hover) {
            sf::Text region_name_text;
            region_name_text.setFont(Assets::font);
            region_name_text.setString(hover->get_region_name());
            region_name_text.setPosition(WINDOW_SIZE / 2 - (hover->get_region_name().length() * 10),
                                         20);
            region_name_text.setOutlineColor(sf::Color::Black);
            region_name_text.setOutlineThickness(2.5);
            window.draw(region_name_text);

            region_name_text.setPosition(
                    WINDOW_SIZE / 2 - (hover->get_subregion_name().length() * 10), 55);
            region_name_text.setCharacterSize(25);
            region_name_text.setString(hover->get_subregion_name());
            window.draw(region_name_text);
        }
    } else {
        // this->sprite.scale(1.0f, 1.0f);
        // sprite.setPosition(static_cast<float>(-pos.x), static_cast<float>(-pos.y));
        sprite.setTextureRect(sf::Rect<int>(pos.x, pos.y, WINDOW_SIZE, WINDOW_SIZE));
        window.draw(sprite);
    }
    sf::Text pos_text;
    pos_text.setFont(Assets::font);
    pos_text.setString(std::to_string(pos.x / get_tile_size()) + ", " + std::to_string(pos.y / get_tile_size()));

    pos_text.setOutlineColor(sf::Color::Black);
    pos_text.setOutlineThickness(2.5);
    window.draw(pos_text);
}

bool World::move(int x, int y, World::Direction d) {
    int xdiff = d == WEST ? -1 : (d == EAST ? 1 : 0);
    int ydiff = d == NORTH ? -1 : (d == SOUTH ? 1 : 0);

    std::unique_ptr<Tile> &a = this->tiles[x][y];
    std::unique_ptr<Tile> &aa = this->tiles[x + xdiff][y + ydiff];

    if (a->get_actor() && !(aa->get_actor())) {
        aa->set_actor(a->get_actor());
        a->set_actor(nullptr);
        return true;
    }
    return false;
}

void World::tick() {
    int xdiff = 0;
    int ydiff = 0;

    int dist = 10;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        ydiff = -dist;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        ydiff = dist;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        xdiff = -dist;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        xdiff = dist;
    }

    int nx = pos.x + xdiff;
    int ny = pos.y + ydiff;

    pos.x = min(max(0, nx), (WORLD_SIZE - VIEW_DISTANCE) * get_tile_size());
    pos.y = min(max(0, ny), (WORLD_SIZE - VIEW_DISTANCE) * get_tile_size());
}

void World::move_map(int dx, int dy) {
    sf::IntRect rect = this->sprite.getTextureRect();

    int left = rect.left + dx;
    int top = rect.top + dy;

    if (left >= 0 && left < WORLD_SIZE - WINDOW_SIZE && top >= 0 && top < WORLD_SIZE - WINDOW_SIZE)
        this->sprite.setTextureRect(sf::IntRect(left, top, WINDOW_SIZE, WINDOW_SIZE));
}

void World::move_camera(int dx, int dy) {
    if (pos.x + dx + RENDER_SIZE * get_tile_size() < WORLD_SIZE * get_tile_size() * DUP_FACTOR) {
        pos.x += dx;
    }

    if (pos.y + dy + RENDER_SIZE * get_tile_size() < WORLD_SIZE * get_tile_size() * DUP_FACTOR) {
        pos.y += dy;
    }
}

void World::zoom() {
    if (_zoom_level == ZOOM_GLOBAL) {
        _zoom_level = ZOOM_LOCAL;

        sf::Vector2i mouse_pos = Mouse::get_mouse_position();

        int left = (mouse_pos.x + pos.x) / 100 * 100 * get_tile_size();
        int top = (mouse_pos.y + pos.y) / 100 * 100 * get_tile_size();

        //int left = pos.x + max(0, mouse_pos.x - mouse_pos.x % 100) * get_tile_size() * DUP_FACTOR;
        //int top = pos.y + max(0, mouse_pos.y - mouse_pos.y % 100) * get_tile_size() * DUP_FACTOR;

        pos.x = left;
        pos.y = top;
    } else if (_zoom_level == ZOOM_LOCAL) {
        pos.x /= get_tile_size();
        pos.y /= get_tile_size();

        pos.x /= 2;
        pos.y /= 2;

        _zoom_level = ZOOM_GLOBAL;
    }
}

const std::unique_ptr<Tile> &World::get_hovered_tile() {
    sf::Vector2i mouse_pos = Mouse::get_mouse_position();

    if (mouse_pos.x < 0 || mouse_pos.x > WINDOW_SIZE || mouse_pos.y < 0 || mouse_pos.y > WINDOW_SIZE) {
        return tiles[0][0];
    }

    int xx = pos.x / get_tile_size() + mouse_pos.x / get_tile_size();
    int yy = pos.y / get_tile_size() + mouse_pos.y / get_tile_size();

    return this->tiles[xx][yy];
}

int World::get_tile_size(int zoom_level) {
    if (zoom_level == ZOOM_LOCAL) {
        return 10;
    } else if (zoom_level == ZOOM_GLOBAL) {
        return 1;
    } else {
        return get_tile_size(_zoom_level);
    }
}
