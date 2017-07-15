
#include "MovementTask.h"

#include "../objectives/LocationObjective.h"

namespace regency {
namespace entity {

MovementTask::MovementTask(Actor& actor, std::pair<int, int> destination)
    : Task(new LocationObjective(destination)), dest(destination), actor(actor) {}

bool MovementTask::perform() {
    if (this->get_objective()->completion(this->actor) == 1) {
        return true;
    }

    std::tuple<int, int, int> loc = this->actor.get_location();

    world::World::Direction d;

    if (std::get<0>(loc) < dest.first) {
        d = world::World::EAST;
    } else if (std::get<0>(loc) > dest.first) {
        d = world::World::WEST;
    } else if (std::get<1>(loc) > dest.second) {
        d = world::World::NORTH;
    } else {
        d = world::World::SOUTH;
    }

    this->actor.move(d);
    return false;
}

std::pair<int, int> MovementTask::find_target() {
    return this->dest;
}
}
}