#ifndef REGENCY_HARVEST_H
#define REGENCY_HARVEST_H

#include <entity/action/Action.h>
#include <world/Region.h>

namespace regency::entity::action {

class Harvest : public Action {
  public:
    Harvest(Actor& performer, world::Region work_area);

    Outcome perform() override;

    bool construct_plan() override;

  private:
    bool _found_target;
    int _tiles_checked;

    world::Location _target_loc;
};
}

#endif //REGENCY_HARVEST_H
