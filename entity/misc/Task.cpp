
#include "Task.h"

namespace regency {
namespace entity {

Task::Task(Objective* obj) : objective(obj), _success{Outcome::IN_PROGRESS} {}

Objective* Task::get_objective() {
    return this->objective;
}

Outcome Task::success() const {
    return _success;
}
}
}