
#include "Actor.h"
#include "../world/World.h"

namespace regency {
namespace entity {

Actor::Actor(world::World& world) : Entity(world) {}

bool Actor::move(world::Direction d) {
    return _world.move(*this, d);
}
}
}