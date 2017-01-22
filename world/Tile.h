#ifndef TEST_PROJECT_TILE_H
#define TEST_PROJECT_TILE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Material.h"

#define TILE_SIZE 1

class Actor;

class Tile {
private:
    unsigned int x;
    unsigned int y;
    unsigned int z; //ground floor height

    bool pass_actor;
    bool to_render;

    void get_bounds(sf::RectangleShape& bounds_in);

    vector<const Material *> mat;
    Actor *actor;
    string region_name;
    // other stuff...
public:
    Tile(unsigned int x, unsigned int y, const Material *material, string region_name);

    void set_material(const Material *material);
    const Material *get_material();

    void render(sf::RenderWindow& window, int x, int y, int zoom_level);
    void set_actor(Actor *actor);
    Actor *get_actor();

    string& get_region_name();

    void tick();
};


#endif //TEST_PROJECT_TILE_H
