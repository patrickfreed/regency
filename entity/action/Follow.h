
#ifndef REGENCY_FOLLOW_H
#define REGENCY_FOLLOW_H

#include <regency/entity/action/Action.h>
#include <regency/world/Region.h>

namespace regency::entity::action {

class Follow : public Action {
  public:
    Follow(Actor& performer, std::shared_ptr<Actor> target, world::Region bounds = world::Region{});

    Outcome perform() override;

    bool construct_plan() override;

  private:
    std::shared_ptr<Actor> _target;
    world::Location _last_known;
};

}
#endif //REGENCY_FOLLOW_H
