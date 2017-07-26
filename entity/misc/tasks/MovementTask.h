
#ifndef REGENCY_MOVEMENTTASK_H
#define REGENCY_MOVEMENTTASK_H

#include <list>

#include "../../../world/PathFinder.h"
#include "../../Actor.h"
#include "../Task.h"

namespace regency {
namespace entity {

class MovementTask : public Task {
  private:
    world::Location _dest;

    // TODO: think about moving this into actor?
    world::PathFinder _pf;

    Actor& actor;

  public:
    MovementTask(Actor& actor, world::Location destination);

    virtual Outcome perform();

    virtual world::Location find_target();
};
}
}

#endif // REGENCY_MOVEMENTTASK_H
