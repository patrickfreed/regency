#ifndef REGENCY_ENTITY_H
#define REGENCY_ENTITY_H

#include <regency/world/Location.h>

#include <string>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace regency {

namespace world {
class World;
}

namespace entity {

class Entity {
  public:
    explicit Entity(world::World& world);

    virtual ~Entity() = default;

    virtual bool operator==(const Entity& other);

    virtual bool operator!=(const Entity& other);

    size_t operator()(const Entity& e);

    world::Location& get_location();

    world::World& get_world();

    virtual sf::Drawable& get_drawable() = 0;

    int get_id();

    friend class world::World;

  private:
    world::World& _world;
    world::Location _location;
    std::string id;
    int _id;
};
}
}
#endif // REGENCY_ENTITY_H
