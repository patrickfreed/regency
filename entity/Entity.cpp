
#include "Entity.h"

size_t Entity::operator()(const Entity &e) {
    return hash<string>()(this->id);
}

tuple<int, int, int> Entity::get_location() {
    return tuple<int,int,int>(x, y, z);
}

World &Entity::get_world() {
    return this->world;
}

Entity::Entity(World &world) : x(0), y(0), z(0), world(world) {

}

