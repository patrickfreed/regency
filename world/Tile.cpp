#include "Tile.h"

#include <iostream>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include "../entity/Actor.h"
#include "../Assets.h"

namespace regency {
namespace world {

Tile::Tile(int x, int y, const Material *material, double e, double m)
        : Tile(Location{x, y}, material, e, m) {}

Tile::Tile(Location loc, const Material *material, double e, double m)
        : _location(loc), _e(e), _m(m), to_render(true), _tree(TreeType::NONE, 0), _highlight(Highlight::NONE) {
    z = 0;
    mat.resize(1);
    mat[z] = material;
    actor = nullptr;
}

void Tile::render(sf::RenderTexture &window, int x, int y, int zoom_level) {
    if (_tree.get_type() != TreeType::NONE) {
        sf::Sprite sprite;
        sprite.setTexture(regency::Assets::tree_texture);
        sprite.setPosition(x, y);
        window.draw(sprite);
    }
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

void Tile::set_material(const Material *material) {
    this->to_render = true;
    this->mat[this->z] = material;
}

void Tile::get_bounds(sf::RectangleShape &bounds) {
    bounds.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    bounds.setPosition(x * TILE_SIZE, y * TILE_SIZE);
}

const Material *Tile::get_material() const {
    return mat[z];
}

const std::string &Tile::get_region_name() const {
    return region_name;
}

void Tile::set_region_name(const std::string &name) {
    region_name = name;
}

void Tile::set_subregion_name(const std::string &name) {
    _subregion_name = name;
}

double Tile::get_moisture() const {
    return _m;
}

double Tile::get_elevation() const {
    return _e;
}

const std::string &Tile::get_subregion_name() const {
    return _subregion_name;
}

const Location &Tile::get_location() const {
    return _location;
}

void Tile::set_tree(Tree tree) {
    _tree = tree;
}

Tree &Tile::get_tree() {
    return _tree;
}

void Tile::set_highlight(Highlight highlight) {
    _highlight = highlight;
}

Highlight Tile::get_highlight() {
    return _highlight;
}

}
}
