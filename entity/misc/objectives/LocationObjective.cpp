
#include "LocationObjective.h"

namespace regency {
namespace entity {

LocationObjective::LocationObjective(world::Location start, world::Location destination)
    : _start(start), destination(destination) {}

double LocationObjective::completion(Actor& actor) {
    auto distance = actor.get_location().distance_to(destination);
    auto start_distance = _start.distance_to(destination);
    auto ratio = distance / start_distance;
    return 1.0 - ratio;
}
}
}
