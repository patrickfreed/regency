
#ifndef REGENCY_OBJECTIVE_H
#define REGENCY_OBJECTIVE_H

#include "../../Actor.h"

namespace regency {
namespace entity {

class Objective {
  public:
    virtual ~Objective() {}

    virtual float completion(Actor& actor) = 0;
};
}
}

#endif // REGENCY_OBJECTIVE_H
