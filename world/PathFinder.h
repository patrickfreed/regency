
#ifndef REGENCY_PATHFINDER_H
#define REGENCY_PATHFINDER_H

#include <list>
#include <unordered_set>
#include <unordered_set>

#include "../entity/Actor.h"
#include "Location.h"
#include "World.h"

namespace regency {
namespace world {

class PathFinder {
  public:
    PathFinder(entity::Actor& actor, const Location& start, const Location& dest);

    bool find_path();

    std::list<regency::world::Location>::iterator get_path();

    bool is_finished();

    Location next();

  private:
    entity::Actor& _actor;

    Location _src;
    Location _dst;

    std::list<Location> _path;

    std::unordered_set<Location, LocationHasher> _closed;
    std::unordered_set<Location, LocationHasher> _open;

    std::unordered_map<Location, double, LocationHasher> _g_score;
    std::unordered_map<Location, double, LocationHasher> _f_score;
    std::unordered_map<Location, Location, LocationHasher> _from;

    bool _finished;
};
}
}

#endif // REGENCY_PATHFINDER_H
