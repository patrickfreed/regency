
#ifndef TEST_PROJECT_TASK_H
#define TEST_PROJECT_TASK_H

#include <utility>
#include "objectives/Objective.h"

using namespace std;

class Task {
private:
    virtual pair<int, int> find_target() = 0;
    Objective *objective;

public:
    Task(Objective *obj);
    virtual ~Task(){ delete objective; }

    virtual bool perform() = 0;

protected:
    Objective *get_objective();
};


#endif //TEST_PROJECT_TASK_H
