
#include "LocationObjective.h"

LocationObjective::LocationObjective(pair<int, int> destination) {
    this->destination = destination;
}

float LocationObjective::completion(Actor& actor) {
    tuple<int,int,int> loc = actor.get_location();

    if (get<0>(loc) == this->destination.first && get<1>(loc) == this->destination.second) {
        return 1;
    } else {
        return 0;
    }
}
