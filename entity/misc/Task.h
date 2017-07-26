
#ifndef REGENCY_TASK_H
#define REGENCY_TASK_H

#include <utility>

#include "objectives/Objective.h"

namespace regency {
namespace entity {

enum class Outcome { SUCCESS, FAILURE, ABORT, IN_PROGRESS };

class Task {
  private:
    Outcome success() const;

    virtual world::Location find_target() = 0;

    Objective* objective;

  public:
    Task(Objective* obj);

    virtual ~Task() {
        delete objective;
    }

    virtual Outcome perform() = 0;

  protected:
    Objective* get_objective();
    Outcome _success;
};
}
}

#endif // REGENCY_TASK_H
