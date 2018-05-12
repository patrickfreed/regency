
#ifndef REGENCY_MOVEMENTTASK_H
#define REGENCY_MOVEMENTTASK_H

#include <world/util/PathFinder.h>
#include <entity/Actor.h>
#include <entity/action/Action.h>

namespace regency::entity::action {

class Move : public Action {
  private:
    world::Location _dest;

    world::PathFinder _pf;
  public:
    Move(Actor& actor, world::Location destination);

    virtual Outcome perform();

    virtual bool construct_plan() {
        return true;
    }

    virtual world::Location find_target();
};
}

#endif // REGENCY_MOVEMENTTASK_H
