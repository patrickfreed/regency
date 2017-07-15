
#include "Actor.h"

namespace regency {
namespace entity {

void Actor::move(world::World::Direction d) {
    if (this->get_world().move(this->x, this->y, d)) {
        int x_diff = d == world::World::WEST ? -1 : (d == world::World::EAST ? 1 : 0);
        int y_diff = d == world::World::NORTH ? -1 : (d == world::World::SOUTH ? 1 : 0);

        x += x_diff;
        y += y_diff;
    }
}

Actor::Actor(world::World& world) : Entity(world) {}
}
}