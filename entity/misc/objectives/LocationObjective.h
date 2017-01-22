
#ifndef TEST_PROJECT_LOCATIONOBJECTIVE_H
#define TEST_PROJECT_LOCATIONOBJECTIVE_H


#include <utility>
#include "Objective.h"
#include "../../Actor.h"

class LocationObjective : public Objective {
public:
    LocationObjective(std::pair<int, int> destination);
    virtual float completion(Actor &actor);
private:
    pair<int, int> destination;
};


#endif //TEST_PROJECT_LOCATIONOBJECTIVE_H
