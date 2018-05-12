#include <regency/entity/action/Idle.h>

namespace regency::entity::action {

Idle::Idle(Actor& performer) : Action(performer) {}

Outcome Idle::perform() {
    return Outcome::IN_PROGRESS;
}

bool Idle::construct_plan() {
    return true;
}

}
