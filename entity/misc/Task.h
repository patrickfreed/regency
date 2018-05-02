
#ifndef REGENCY_TASK_H
#define REGENCY_TASK_H

#include <functional>
#include <memory>
#include <queue>
#include <utility>
#include <vector>

#include "objectives/Objective.h"

namespace regency::entity::task {

enum class Outcome { SUCCESS, FAILURE, ABORT, IN_PROGRESS, SETUP };

class Task {
  public:
    Task(Actor& performer);

    virtual ~Task() = default;

    virtual bool construct_plan() = 0;

    Outcome do_task();

    Outcome status() const;

    void on_success(std::function<void(Task& t)> f);

  protected:
    Actor& performer;

    virtual Outcome perform() = 0;

    bool has_sub_tasks();
    Task& get_sub_task();
    void pop_sub_task();
    void add_sub_task(std::unique_ptr<Task>&& t);

    Objective* get_objective();
    Outcome _status;

  private:
    std::function<void(Task& t)> _trailer;

    std::queue<std::unique_ptr<Task>> _sub_tasks;

    // virtual world::Location find_target();

    Objective* objective;
};
}

#endif // REGENCY_TASK_H
