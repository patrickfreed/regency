#include "Entity.h"

namespace regency {
namespace entity {

Entity::Entity(world::World& world) : _world(world), _location() {}

size_t Entity::operator()(const Entity& e) {
    return std::hash<std::string>()(id);
}

world::Location& Entity::get_location() {
    return _location;
}

world::World& Entity::get_world() {
    return _world;
}

} // namespace entity
} // namespace regency
