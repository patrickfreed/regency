
#ifndef REGENCY_LOCATIONOBJECTIVE_H
#define REGENCY_LOCATIONOBJECTIVE_H

#include "../../Actor.h"
#include "Objective.h"
#include <utility>

namespace regency {
namespace entity {

class LocationObjective : public Objective {
  public:
    LocationObjective(world::Location start, world::Location destination);

    virtual double completion(Actor& actor);

  private:
    world::Location destination;
    world::Location _start;
};
}
}

#endif // REGENCY_LOCATIONOBJECTIVE_H
