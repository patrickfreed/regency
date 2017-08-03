
#ifndef REGENCY_FIND_H
#define REGENCY_FIND_H

#include "../Task.h"

namespace regency::entity::task {

class Find : public Task {
  public:
    Find(Actor& a);

    // T get_find();

    world::Location get_find_location();

    virtual Outcome perform();

    virtual bool construct_plan();

  private:
    world::Location _dest;
    int _radius;
};
}

#endif // REGENCY_FIND_H
