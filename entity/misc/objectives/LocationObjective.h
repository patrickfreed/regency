
#ifndef REGENCY_LOCATIONOBJECTIVE_H
#define REGENCY_LOCATIONOBJECTIVE_H

#include "../../Actor.h"
#include "Objective.h"
#include <utility>

namespace regency {
namespace entity {

class LocationObjective : public Objective {
  public:
    LocationObjective(std::pair<int, int> destination);

    virtual float completion(Actor& actor);

  private:
    std::pair<int, int> destination;
};
}
}

#endif // REGENCY_LOCATIONOBJECTIVE_H
