
#include "Move.h"

#include "../objectives/LocationObjective.h"

namespace regency::entity::task {

Move::Move(Actor& actor, world::Location destination)
    : Task(actor), _dest(destination), actor(actor), _pf{actor, actor.get_location(), destination} {
}

Outcome Move::perform() {
    if (!_pf.is_finished()) {
        if (!_pf.find_path()) {
            _status = Outcome::FAILURE;
            return _status;
        }
        _pf.get_path();
    }

    if (!_pf.has_next()) {
        if (actor.get_location() == _dest) {
            return _status = Outcome::SUCCESS;
        } else {
            return _status = Outcome::FAILURE;
        }
    }

    world::Location loc = actor.get_location();
    world::Location next = _pf.next();
    world::Direction d = loc.get_direction_to(next);
    actor.move(d);

    return Outcome::IN_PROGRESS;
}

world::Location Move::find_target() {
    return _dest;
}
}