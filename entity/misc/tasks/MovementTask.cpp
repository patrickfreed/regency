
#include "MovementTask.h"
#include "../objectives/LocationObjective.h"

bool MovementTask::perform() {
    if (this->get_objective()->completion(this->actor) == 1) {
        return true;
    }

    tuple<int,int,int> loc = this->actor.get_location();

    World::Direction d;

    if (get<0>(loc) < dest.first) {
        d = World::EAST;
    } else if (get<0>(loc) > dest.first) {
        d = World::WEST;
    } else if (get<1>(loc) > dest.second) {
        d = World::NORTH;
    } else {
        d = World::SOUTH;
    }

    this->actor.move(d);
    return false;
}

pair<int, int> MovementTask::find_target() {
    return this->dest;
}

MovementTask::MovementTask(Actor &actor, pair<int, int> destination) : Task(new LocationObjective(destination)), dest(destination), actor(actor) {
}
