#ifndef REGENCY_ENTITY_H
#define REGENCY_ENTITY_H

#include "../world/Location.h"

#include <string>

#include <SFML/Graphics/Drawable.hpp>

namespace regency {

namespace world {
class World;
}

namespace entity {

class Entity {
  protected:
    world::World& _world;

  private:
    world::Location _location;
    std::string id;

  public:
    Entity(world::World& world);

    virtual ~Entity() = default;

    size_t operator()(const Entity& e);

    world::Location& get_location();

    world::World& get_world();

    virtual sf::Drawable& get_drawable() = 0;
};
}
}
#endif // REGENCY_ENTITY_H
