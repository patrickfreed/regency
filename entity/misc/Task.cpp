
#include "Task.h"

namespace regency {
namespace entity {

Task::Task(Objective* obj) : objective(obj) {}

Objective* Task::get_objective() {
    return this->objective;
}
}
}