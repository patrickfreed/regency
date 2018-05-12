
#ifndef REGENCY_EAT_H
#define REGENCY_EAT_H

#include <entity/action/Action.h>

namespace regency::entity::action {

class Eat : public Action {
  public:
    explicit Eat(Actor& a);

    virtual Outcome perform();

    bool construct_plan();
};
}

#endif // REGENCY_EAT_H
