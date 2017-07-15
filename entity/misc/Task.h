
#ifndef REGENCY_TASK_H
#define REGENCY_TASK_H

#include <utility>

#include "objectives/Objective.h"

namespace regency {
namespace entity {

class Task {
  private:
    virtual std::pair<int, int> find_target() = 0;

    Objective* objective;

  public:
    Task(Objective* obj);

    virtual ~Task() {
        delete objective;
    }

    virtual bool perform() = 0;

  protected:
    Objective* get_objective();
};
}
}

#endif // REGENCY_TASK_H
