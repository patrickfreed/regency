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

    // Values used from generation
    double _e;
    double _m;

    bool pass_actor;
    bool to_render;

    void get_bounds(sf::RectangleShape& bounds_in);

    std::vector<const Material *> mat;
    Actor *actor;

    std::string region_name;
    std::string _subregion_name;
public:
    Tile(unsigned int x, unsigned int y, const Material *material, double e, double m);

    void set_material(const Material *material);
    const Material *get_material();

    void render(sf::RenderWindow& window, int x, int y, int zoom_level);

    void set_actor(Actor *actor);
    Actor *get_actor();

    std::string& get_region_name();
    void set_region_name(const std::string& name);

    const std::string& get_subregion_name() const;
    void set_subregion_name(const std::string& name);

    void tick();

    double get_moisture();
    double get_elevation();
};


#endif //TEST_PROJECT_TILE_H
