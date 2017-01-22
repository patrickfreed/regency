
#ifndef TEST_PROJECT_OBJECTIVE_H
#define TEST_PROJECT_OBJECTIVE_H


#include "../../Actor.h"

class Objective {
public:
    virtual ~Objective() {}
    virtual float completion(Actor &actor) = 0;
};


#endif //TEST_PROJECT_OBJECTIVE_H
