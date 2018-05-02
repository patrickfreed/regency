
#include <cmath>

#include "Location.h"
#include "World.h"

namespace regency {
namespace world {

Location::Location(int x, int y, int z) : _x{x}, _y{y}, _z{z} {}

bool Location::is_valid() const {
    return _x >= 0 && _x < WORLD_SIZE && _y >= 0 && _y < WORLD_SIZE;
}

world::Direction Location::get_direction_to(Location dest) const {
    Direction ew = Direction::NONE;
    Direction ns = Direction::NONE;

    if (_x < dest.get_x()) {
        ew = Direction::EAST;
    } else if (_x > dest.get_x()) {
        ew = Direction::WEST;
    }

    if (_y < dest.get_y()) {
        ns = Direction::NORTH;
    } else if (_y > dest.get_y()) {
        ns = Direction::SOUTH;
    }

    return static_cast<world::Direction>(ns + ew);
}

double Location::distance_to(Location dest, Distance d) const {
    if (d == Distance::EUCLIDEAN) {
        return std::sqrt(std::pow(dest.get_x() - _x, 2) + std::pow(dest.get_y() - _y, 2) +
                         std::pow(dest.get_z() - _z, 2));
    } else if (d == Distance::MANHATTAN) {
        return std::abs(dest.get_x() - _x) + std::abs(dest.get_y() - _y);
    } else {
        return 0;
    }
}

std::string Location::str() const {
    return "{x: " + std::to_string(_x) + ", y: " + std::to_string(_y) + "}";
}

Location Location::get_adjacent(world::Direction d) const {
    int dx = 0;
    int dy = 0;
    Direction ns = Direction::NONE;

    if (d < Direction::NORTH) {
        dy = 0;
    } else if (d < Direction::SOUTH) {
        dy = 1;
        ns = Direction::NORTH;
    } else {
        dy = -1;
        ns = Direction::SOUTH;
    }

    if (d - ns == Direction::WEST) {
        dx = -1;
    } else if (d - ns == Direction::EAST) {
        dx = 1;
    }

    return Location(_x + dx, _y + dy);
}

size_t Location::operator()(const Location& l) const {
    return _x + WORLD_SIZE * _y;
}

bool Location::operator==(const Location& other) const {
    return other._x == _x && other._y == _y;
}

std::size_t LocationHasher::operator()(const Location& k) const {
    return std::hash<int>()(k.get_x() + WORLD_SIZE * k.get_y());
}
} // namespace world
} // namespace regency