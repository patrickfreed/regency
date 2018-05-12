
#ifndef REGENCY_TASK_H
#define REGENCY_TASK_H

#include <functional>
#include <memory>
#include <queue>
#include <utility>
#include <vector>

#include <regency/entity/action/objectives/Objective.h>
#include <regency/world/Region.h>

namespace regency::entity::action {

enum class Outcome { SUCCESS, FAILURE, ABORT, IN_PROGRESS, SETUP };

class Action {
  public:
    static std::string outcome_to_string(Outcome o);

    explicit Action(Actor& performer, world::Region area = world::Region());

    Action(const Action& other) = delete;

    void operator=(const Action& other) = delete;

    virtual ~Action() = default;

    virtual bool construct_plan() = 0;

    Actor& get_actor();

    Outcome do_action();

    Outcome get_status() const;

    virtual void abort();

    void then(std::function<void(Action &t)> f);

    virtual world::Region& get_action_area();

    void set_action_area(world::Region& other);

  protected:
    virtual Outcome perform();

    bool has_sub_tasks();

    Action& get_sub_task();

    void pop_sub_task();

    void add_sub_task(std::unique_ptr<Action>&& t);

    Objective* get_objective();

  private:
    std::function<void(Action& t)> _trailer;

    std::queue<std::unique_ptr<Action>> _sub_tasks;

    Outcome _status;

    Actor& _performer;

    Objective* objective;

    world::Region _area;
};
}

#endif // REGENCY_TASK_H
