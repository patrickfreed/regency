
#include <entity/action/Action.h>

#include <functional>
#include <iostream>

namespace regency::entity::action {

Action::Action(Actor& actor, world::Region area) :
        _performer(actor), _status{Outcome::SETUP}, _trailer{[](Action& t) {}}, _area(area) {}

Objective* Action::get_objective() {
    return this->objective;
}

void Action::add_sub_task(std::unique_ptr<Action>&& t) {
    _sub_tasks.push(std::move(t));
}

bool Action::has_sub_tasks() {
    return !_sub_tasks.empty();
}

Action& Action::get_sub_task() {
    return *_sub_tasks.front();
}

void Action::pop_sub_task() {
    return _sub_tasks.pop();
}

// Public methods below

void Action::then(std::function<void(class Action &t)> f) {
    _trailer = std::move(f);
}

Outcome Action::do_action() {
    if (_status == Outcome::SETUP) {
        if (!construct_plan()) {
            _status = Outcome::FAILURE;
        } else {
            _status = Outcome::IN_PROGRESS;
        }
    } else if (_status == Outcome::IN_PROGRESS) {
        if ((_status = perform()) != Outcome::IN_PROGRESS) {
            _trailer(*this);
        }
    }
    return _status;
}

Actor &Action::get_actor() {
    return _performer;
}

Outcome Action::get_status() const {
    return _status;
}

Outcome Action::perform() {
    if (has_sub_tasks()) {
        Action& t = get_sub_task();

        Outcome o = t.do_action();
        if (o != Outcome::IN_PROGRESS) {
            pop_sub_task();

            if (!has_sub_tasks()) {
                return o;
            }
        }

        return Outcome::IN_PROGRESS;
    }

    return Outcome::SUCCESS;
}

std::string Action::outcome_to_string(Outcome o) {
    switch (o) {
        case Outcome::SUCCESS: return "SUCCESS";
        case Outcome::IN_PROGRESS: return "IN_PROGRESS";
        case Outcome::FAILURE: return "FAILURE";
        case Outcome::ABORT: return "ABORT";
        case Outcome::SETUP: return "SETUP";
    }
}

world::Region& Action::get_action_area() {
    return _area;
}

void Action::set_action_area(world::Region& other) {
    _area = other;
}

void Action::abort() {}
}