
#ifndef REGENCY_PATROL_H
#define REGENCY_PATROL_H

#include <world/Region.h>
#include <entity/HumanActor.h>
#include "Action.h"

namespace regency::entity::action {

class Patrol : public Action {
  public:
    Patrol(Actor& performer, const world::Region& area);

    bool construct_plan() override;

    Outcome perform() override;

    world::Region& get_action_area() override;

    void abort() override;

  private:
    bool _following;

    std::shared_ptr<Actor> _target;

    world::Region _area;
};
}


#endif //REGENCY_PATROL_H
