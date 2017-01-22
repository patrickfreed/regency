
#ifndef TEST_PROJECT_HUMANACTOR_H
#define TEST_PROJECT_HUMANACTOR_H


#include <queue>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Actor.h"
#include "misc/Task.h"

class HumanActor : Actor {
private:
    // personality
    int courage;
    int curiosity;
    int intelligence;
    int laziness;
    int temper;
    int sociality;

    // skill with tool
    int axe;
    int sword;
    int fishing_rod;
    int pickaxe;
    int hammer;

    // Work area (affected by curiosity, courage)
    pair<int, int> origin;
    int radius;

    queue<Task *> task_queue;

    sf::RectangleShape drawable;
public:
    HumanActor(World& world);
    virtual void tick();
    virtual sf::Drawable& get_drawable();
};


#endif //TEST_PROJECT_HUMANACTOR_H
