
#include <regency/entity/action/Patrol.h>
#include <regency/world/gen/RandomGenerator.h>

#include <regency/entity/action/Move.h>
#include <regency/entity/action/Follow.h>

namespace regency::entity::action {

Patrol::Patrol(Actor& performer, const world::Region& area) : Action(performer), _area(area), _following(false) {}

bool Patrol::construct_plan() {
    world::gen::RandomGenerator rng_x(_area.get_min_x(), _area.get_max_x());
    world::gen::RandomGenerator rng_y(_area.get_min_y(), _area.get_max_y());

    world::Location target(rng_x.next_int(), rng_y.next_int());
    add_sub_task(std::make_unique<Move>(get_actor(), target));

    return true;
}

Outcome Patrol::perform() {
    Outcome sub_action = Action::perform();
    if (sub_action != Outcome::IN_PROGRESS) {
        if (_following) {
            _following = false;
        }

        construct_plan();
        return Outcome::IN_PROGRESS;
    }

    if (!_following && _area.contains(get_actor().get_location())) {
        world::World& world = get_actor().get_world();
        auto nearby_actors = world.get_nearby_actors(get_actor().get_location(), 5);

        if (nearby_actors.size() > 1) {
            std::shared_ptr<Actor> target;
            for (auto& actor : nearby_actors) {
                if (*actor != get_actor() && _area.contains(actor->get_location())) {
                    target = actor;
                    break;
                }
            }

            if (target) {
                pop_sub_task();
                _following = true;
                Actor& performer = get_actor();
                performer.set_alert(true);
                auto clear_alert = [&performer](Action& f) {
                    performer.set_alert(false);
                };

                _target = &target->get_location();
                auto follow_action = std::make_unique<Follow>(get_actor(), target, _area);
                follow_action->then(clear_alert);
                add_sub_task(std::move(follow_action));
            }
        }
    }

    return Outcome::IN_PROGRESS;
}

world::Region& Patrol::get_action_area() {
    return _area;
}

void Patrol::abort() {
    get_actor().set_alert(false);
}

}