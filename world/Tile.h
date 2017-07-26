#ifndef REGENCY_WORLD_TILE_H
#define REGENCY_WORLD_TILE_H

#include "Location.h"
#include "Material.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

namespace regency {
namespace entity {
class Actor;
}

namespace world {

#define TILE_SIZE 1

// class Actor;

class Tile {
  private:
    Location _location;

    unsigned int x;
    unsigned int y;
    unsigned int z; // ground floor height

    // Values used from generation
    double _e;
    double _m;

    bool pass_actor;
    bool to_render;

    void get_bounds(sf::RectangleShape& bounds_in);

    std::vector<const Material*> mat;
    std::shared_ptr<entity::Actor> actor;

    std::string region_name;
    std::string _subregion_name;

  public:
    Tile(int x, int y, const Material* material, double e, double m);

    Tile(Location loc, const Material* material, double e, double m);

    void set_material(const Material* material);

    const Material* get_material() const;

    void render(sf::RenderWindow& window, int x, int y, int zoom_level);

    void set_actor(std::shared_ptr<entity::Actor> actor = {});

    std::shared_ptr<entity::Actor> get_actor();

    const std::string& get_region_name() const;

    void set_region_name(const std::string& name);

    const std::string& get_subregion_name() const;

    void set_subregion_name(const std::string& name);

    void tick();

    double get_moisture() const;

    double get_elevation() const;

    const Location& get_location() const;
};
}
}

#endif // REGENCY_WORLD_TILE_H
