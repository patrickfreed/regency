#include "Direction.h"

namespace regency {
namespace world {

Direction operator++(const Direction& d) {
    if (d == SOUTH_EAST) {
        return NONE;
    }

    int id = static_cast<int>(d);
    return static_cast<Direction>(++id);
}
}
}
