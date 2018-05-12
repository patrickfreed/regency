
#include <entity/action/Move.h>
#include <iostream>

namespace regency::entity::action {

Move::Move(Actor& actor, world::Location destination)
    : Action(actor, {destination, destination}), _dest(destination), _pf{actor.get_location(), destination} {
}

Outcome Move::perform() {
    if (!_pf.is_finished()) {
        if (!_pf.find_path()) {
            return Outcome::FAILURE;
        }
        _pf.get_path();
    }

    if (!_pf.has_next()) {
        if (get_actor().get_location() == _dest) {
            return Outcome::SUCCESS;
        } else {
            return Outcome::FAILURE;
        }
    }

    world::Location loc = get_actor().get_location();
    world::Location next = _pf.peek();
    world::Direction d = loc.get_direction_to(next);

    if (get_actor().move(d)) {
        _pf.next();
    } else {
        world::World& world = get_actor().get_world();
        if (!world.is_traversable(next)) {
            std::cout << "obstacle, re doing pathfind" << std::endl;
            _pf = world::PathFinder(get_actor().get_location(), _dest);
        }
    }

    return Outcome::IN_PROGRESS;
}

world::Location Move::find_target() {
    return _dest;
}
}