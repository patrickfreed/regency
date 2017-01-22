#include <iostream>
#include "../entity/Actor.h"

using namespace std;

Tile::Tile(unsigned int x, unsigned int y, const Material *material, string region_name) : x(x), y(y), to_render(true) {
    this->z = 0;
    this->mat.resize(1);
    this->mat[z] = material;
    this->actor = nullptr;
    this->region_name = region_name;
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

void Tile::set_actor(Actor *actor) {
    this->actor = actor;
    this->pass_actor = true;
}

Actor *Tile::get_actor() {
    return this->actor;
}

void Tile::tick() {
    //long bounds_size = sizeof(this->bounds);

    if (this->actor && !this->pass_actor) {
        this->actor->tick();
    }
    this->pass_actor = false;
}

void Tile::set_material(const Material *material) {
    this->to_render = true;
    this->mat[this->z] = material;
}

void Tile::get_bounds(sf::RectangleShape& bounds) {
    const Material *material = this->mat[z];
    bounds.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    bounds.setPosition(x * TILE_SIZE, y * TILE_SIZE);
}

const Material *Tile::get_material() {
    return this->mat[z];
}

string & Tile::get_region_name() {
    return this->region_name;
}
