
#ifndef REGENCY_LOCATION_H
#define REGENCY_LOCATION_H

#include "../Defines.h"
#include "Direction.h"

#include <string>

namespace regency {
namespace world {

enum class Distance { EUCLIDEAN, MANHATTAN };

class Location {
  public:
    Location(int x = 0, int y = 0, int z = 0);

    int get_x() const {
        return _x;
    }

    int get_y() const {
        return _y;
    }

    int get_z() const {
        return _z;
    }

    bool is_valid() const;

    double distance_to(Location dest, Distance d = Distance::EUCLIDEAN) const;

    world::Direction get_direction_to(Location dest) const;

    Location get_adjacent(world::Direction d) const;

    std::string str() const;

    size_t operator()(const Location& l) const;

    bool operator==(const Location& other) const;

  private:
    friend class Entity;
    friend class World;

    int _x;
    int _y;
    int _z;
};

struct LocationHasher {
  public:
    size_t operator()(const Location& k) const;
};
}
}

#endif // REGENCY_LOCATION_H
