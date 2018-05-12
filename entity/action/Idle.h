
#ifndef REGENCY_IDLE_H
#define REGENCY_IDLE_H

#include <regency/entity/action/Action.h>
#include <entity/Actor.h>

namespace regency::entity::action {

class Idle : public Action {
  public:
    Idle(Actor& performer);

    Outcome perform() override;

    bool construct_plan() override;
};

}

#endif //REGENCY_IDLE_H
