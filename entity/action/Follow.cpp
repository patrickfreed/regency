
#include <regency/entity/action/Follow.h>
#include <regency/entity/Actor.h>
#include <regency/entity/action/Move.h>
#include <regency/entity/action/Idle.h>

#include <iostream>

namespace regency::entity::action {

Follow::Follow(Actor& performer, std::shared_ptr<Actor> target, world::Region bounds) :
        Action(performer, bounds), _target(std::move(target)) {}

Outcome Follow::perform() {
    if (_last_known != _target->get_location()) {
        std::cout << "target moved, popping idle or move task" << std::endl;
        pop_sub_task();
        if (!construct_plan()) {
            return Outcome::FAILURE;
        }
    }

    if (Action::perform() == Outcome::SUCCESS) {
        add_sub_task(std::make_unique<Idle>(get_actor()));
        std::cout << "got there, assigning idle" << std::endl;
    }

    return Outcome::IN_PROGRESS;
}

bool Follow::construct_plan() {
    if (!get_action_area().contains(_target->get_location())) {
        std::cout << "target not in bounds" << std::endl;
        return false;
    }

    _last_known = _target->get_location();
    auto dest = get_actor().get_world().get_traversable_neighbor(_last_known);

    if (dest) {
        add_sub_task(std::make_unique<Move>(get_actor(), *dest));
        return true;
    }

    std::cout << "no traversables" << std::endl;
    return false;
}
}