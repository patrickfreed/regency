#include "Entity.h"

namespace regency {
namespace entity {

Entity::Entity(world::World& world) : _world(world), _id(-1) {}

size_t Entity::operator()(const Entity& e) {
    return std::hash<std::string>()(id);
}

world::Location& Entity::get_location() {
    return _location;
}

world::World& Entity::get_world() {
    return _world;
}

int Entity::get_id() {
    return _id;
}

bool Entity::operator==(const Entity& other) {
    if (_id == -1) {
        return false;
    }

    return _id == other._id;
}

bool Entity::operator!=(const Entity& other) {
    return !(*this == other);
}

} // namespace entity
} // namespace regency
