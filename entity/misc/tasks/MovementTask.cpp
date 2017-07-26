
#include "MovementTask.h"

#include "../../../world/PathFinder.h"
#include "../../../world/World.h"
#include "../objectives/LocationObjective.h"

namespace regency {
namespace entity {

MovementTask::MovementTask(Actor& actor, world::Location destination)
    : Task(new LocationObjective(actor.get_location(), destination)), _dest(destination),
      actor(actor), _pf{actor, actor.get_location(), destination} {}

Outcome MovementTask::perform() {
    if (!_pf.is_finished()) {
        if (!_pf.find_path()) {
            _success = Outcome::FAILURE;
            return _success;
        }
        _pf.get_path();
    }

    if (get_objective()->completion(this->actor) == 1) {
        return Outcome::SUCCESS;
    }

    world::Location loc = actor.get_location();
    world::Location next = _pf.next();
    world::Direction d = loc.get_direction_to(next);
    actor.move(d);

    return Outcome::IN_PROGRESS;
}

world::Location MovementTask::find_target() {
    return _dest;
}
}
}