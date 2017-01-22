
#include "Task.h"

Task::Task(Objective *obj) : objective(obj) {
}

Objective *Task::get_objective() {
    return this->objective;
}
