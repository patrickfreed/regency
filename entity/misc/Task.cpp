
#include "Task.h"

namespace regency::entity::task {

Task::Task(Actor& actor) : performer(actor), _status{Outcome::SETUP}, _trailer{[](Task& t) {}} {}

Objective* Task::get_objective() {
    return this->objective;
}

Outcome Task::status() const {
    return _status;
}

void Task::add_sub_task(std::unique_ptr<Task>&& t) {
    _sub_tasks.push(std::move(t));
}

bool Task::has_sub_tasks() {
    return !_sub_tasks.empty();
}

Task& Task::get_sub_task() {
    return *_sub_tasks.front();
}

void Task::pop_sub_task() {
    return _sub_tasks.pop();
}

void Task::on_success(std::function<void(Task& t)> f) {
    _trailer = f;
}

Outcome Task::do_task() {
    if (_status == Outcome::SETUP) {
        if (!construct_plan()) {
            _status = Outcome::FAILURE;
        } else {
            _status = Outcome::IN_PROGRESS;
        }
    } else if (_status == Outcome::IN_PROGRESS) {
        if ((_status = perform()) == Outcome::SUCCESS) {
            _trailer(*this);
        }
    }
    return _status;
}
}