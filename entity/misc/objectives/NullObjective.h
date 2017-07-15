
#ifndef REGENCY_NULLOBJECTIVE_H
#define REGENCY_NULLOBJECTIVE_H

#include "Objective.h"

namespace regency {
namespace entity {

class NullObjective : Objective {
  public:
    virtual float completion();
};
}
}

#endif // REGENCY_NULLOBJECTIVE_H
