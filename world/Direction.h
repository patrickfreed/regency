
#ifndef REGENCY_DIRECTION_H
#define REGENCY_DIRECTION_H

namespace regency {
namespace world {

enum Direction { NONE, WEST, EAST, NORTH, NORTH_WEST, NORTH_EAST, SOUTH, SOUTH_WEST, SOUTH_EAST };

Direction operator++(const Direction& d);
}
}

#endif // REGENCY_DIRECTION_H
