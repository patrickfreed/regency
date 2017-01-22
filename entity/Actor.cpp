
#include "Actor.h"

void Actor::move(World::Direction d) {
    if (this->get_world().move(this->x, this->y, d)) {
        int x_diff = d == World::WEST ? -1 : (d == World::EAST ? 1 : 0);
        int y_diff = d == World::NORTH ? -1 : (d == World::SOUTH ? 1 : 0);

        x += x_diff;
        y += y_diff;
    }
}

Actor::Actor(World &world) : Entity(world) {
}
