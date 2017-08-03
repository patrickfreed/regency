
#ifndef REGENCY_EAT_H
#define REGENCY_EAT_H

#include "../Task.h"

namespace regency::entity::task {
class Eat : public Task {
  public:
    Eat(Actor& a);

    virtual Outcome perform();

    bool construct_plan();
};
}

#endif // REGENCY_EAT_H
