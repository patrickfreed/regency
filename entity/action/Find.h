
#ifndef REGENCY_FIND_H
#define REGENCY_FIND_H

#include <optional>

#include <entity/action/Action.h>
#include <world/Tile.h>
#include <world/Region.h>

namespace regency::entity::action {

class Find : public Action {
  public:
    Find(Actor& a, world::Region& area, std::function<bool(world::Tile&)> matches);

    std::optional<world::Location> get_find_location();

    int tiles_checked();

    Outcome perform() override;

    bool construct_plan() override;

  private:
    world::Location _dest;

    int _radius;
    int _tiles_checked;

    std::function<bool(world::Tile&)> _matches;
};
}

#endif // REGENCY_FIND_H
