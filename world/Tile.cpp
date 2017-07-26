#include "Tile.h"

#include <iostream>

#include "../entity/Actor.h"

namespace regency {
namespace world {

Tile::Tile(Location loc, const Material* material, double e, double m)
    : _location(loc), _e(e), _m(m), to_render(true) {
    z = 0;
    mat.resize(1);
    mat[z] = material;
    actor = nullptr;
}

void Tile::render(sf::RenderWindow& window, int x, int y, int zoom_level) {
    // if (zoom_level == prev_zoom_level && !to_render) return;

    // to_render = false;

    /*
    if (zoom_level == 1) { // default 100x100 tile area
        // int tile_size = WINDOW_SIZE / RENDER_SIZE; // todo dynamic
        unsigned int tile_size = 10;
        unsigned int nx = this->x * tile_size;
        unsigned int ny = this->y * tile_size;
        world_texture.update(this->mat->get_texture(), nx, ny);
    } else {
        sf::Color c = this->mat->get_color();
        sf::Uint8 pixel[4] = {c.r, c.g, c.b, c.a};
        world_texture.update(pixel, 1, 1, x, y);
    }*/

    /*if (zoom_level == 1) {
        this->sprite.setPosition(x, y);
        window.draw(this->sprite);
    }*/
}

void Tile::set_actor(std::shared_ptr<entity::Actor> actor) {
    this->actor = actor;

    this->pass_actor = true;
}

std::shared_ptr<entity::Actor> Tile::get_actor() {
    return actor;
}

void Tile::tick() {
    // long bounds_size = sizeof(this->bounds);

    if (this->actor && !this->pass_actor) {
        // this->actor->tick();
    }
    this->pass_actor = false;
}

void Tile::set_material(const Material* material) {
    this->to_render = true;
    this->mat[this->z] = material;
}

void Tile::get_bounds(sf::RectangleShape& bounds) {
    bounds.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    bounds.setPosition(x * TILE_SIZE, y * TILE_SIZE);
}

const Material* Tile::get_material() const {
    return mat[z];
}

const std::string& Tile::get_region_name() const {
    return region_name;
}

void Tile::set_region_name(const std::string& name) {
    region_name = name;
}

void Tile::set_subregion_name(const std::string& name) {
    _subregion_name = name;
}

double Tile::get_moisture() const {
    return _m;
}

double Tile::get_elevation() const {
    return _e;
}

const std::string& Tile::get_subregion_name() const {
    return _subregion_name;
}

const Location& Tile::get_location() const {
    return _location;
}

Tile::Tile(int x, int y, const Material* material, double e, double m)
    : Tile(Location{x, y}, material, e, m) {}
}
}