#include <iostream>
#include "Material.h"

Material::Material(std::string name, int id, sf::Color c, bool water) : name(name), color(c), texture(), _water(water) {
    /* if (!texture.loadFromFile("../res/material_" + name + ".png")) {
        cout << "failed to load texture for " << name << endl;
    }*/
    this->tile_number = id;
}

const std::string& Material::get_name() {
    return this->name;
}

const sf::Color& Material::get_color() const {
    return this->color;
}

const sf::Texture& Material::get_texture() {
    return (this->texture);
}

int Material::get_tile_number() const {
    return this->tile_number;
}

bool Material::is_solid() const {
    return !_water;
}

// Grasses
const Material Material::NORTHERN_TURF("northern_turf", 1, sf::Color::Green);
const Material Material::BLUEGRASS("bluegrass", 2, sf::Color::Green);
const Material Material::FESCUE("fescue", 3, sf::Color::Green);
const Material Material::RYEGRASS("ryegrass", 4, sf::Color::Green);

// Soils
const Material Material::CLAY_SOIL("clay_soil", 5, sf::Color(170, 76, 35));
const Material Material::SANDY_SOIL("sandy_soil", 6, sf::Color(170, 76, 35));
const Material Material::SILTY_SOIL("silty_soil", 7, sf::Color(170, 76, 35));
const Material Material::PEATY_SOIL("peaty_soil", 8, sf::Color::Black);
const Material Material::CHALKY_SOIL("chalky_soil", 9, sf::Color(170, 76, 35));
const Material Material::LOAMY_SOIL("loamy_soil", 10, sf::Color(170, 76, 35));

// Misc
const Material Material::SAND("sand", 11, sf::Color(234, 216, 82));
const Material Material::SALT_WATER("salt_water", 12, sf::Color(0, 0, 150), true);
const Material Material::ROCK("rock", 13, sf::Color(128, 128, 128));
const Material Material::SNOW("snow", 14, sf::Color(255, 255, 255));
