
#include "LocationObjective.h"

namespace regency {
namespace entity {

LocationObjective::LocationObjective(std::pair<int, int> destination) : destination(destination) {}

float LocationObjective::completion(Actor& actor) {
    std::tuple<int, int, int> loc = actor.get_location();

    if (std::get<0>(loc) == destination.first && std::get<1>(loc) == destination.second) {
        return 1;
    } else {
        return 0;
    }
}
}
}
