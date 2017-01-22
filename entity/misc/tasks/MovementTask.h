
#ifndef TEST_PROJECT_MOVEMENTTASK_H
#define TEST_PROJECT_MOVEMENTTASK_H


#include "../Task.h"
#include "../../Actor.h"

class MovementTask : public Task {
private:
    pair<int, int> dest;
    Actor& actor;
public:
    MovementTask(Actor& actor, pair<int, int> destination);

    virtual bool perform();
    virtual pair<int, int> find_target();
};


#endif //TEST_PROJECT_MOVEMENTTASK_H
