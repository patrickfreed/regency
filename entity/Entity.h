#ifndef REGENCY_ENTITY_H
#define REGENCY_ENTITY_H

#include "../world/World.h"
#include <SFML/Graphics/Drawable.hpp>
#include <string>

namespace regency {
namespace entity {

class Entity {
  protected:
    int x;
    int y;
    int z;

  private:
    std::string id;
    world::World& _world;

  public:
    Entity(world::World& world);

    size_t operator()(const Entity& e);

    std::tuple<int, int, int> get_location();

    world::World& get_world();

    virtual ~Entity() {}

    virtual sf::Drawable& get_drawable() = 0;
};
}
}
#endif // REGENCY_ENTITY_H
