
#include "Entity.h"

namespace regency {
namespace entity {

size_t Entity::operator()(const Entity& e) {
    return std::hash<std::string>()(id);
}

std::tuple<int, int, int> Entity::get_location() {
    return std::tuple<int, int, int>(x, y, z);
}

world::World& Entity::get_world() {
    return _world;
}

Entity::Entity(world::World& world) : x(0), y(0), z(0), _world(world) {}
}
}
