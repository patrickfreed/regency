
#ifndef REGENCY_MOVEMENTTASK_H
#define REGENCY_MOVEMENTTASK_H

#include "../../Actor.h"
#include "../Task.h"

namespace regency {
namespace entity {

class MovementTask : public Task {
  private:
    std::pair<int, int> dest;
    Actor& actor;

  public:
    MovementTask(Actor& actor, std::pair<int, int> destination);

    virtual bool perform();

    virtual std::pair<int, int> find_target();
};
}
}

#endif // REGENCY_MOVEMENTTASK_H
