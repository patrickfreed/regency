
#ifndef TEST_PROJECT_ACTOR_H
#define TEST_PROJECT_ACTOR_H

#include "Entity.h"

class Actor : public Entity {
public:
    Actor(World& world);
    virtual void tick() = 0;
    virtual sf::Drawable& get_drawable() = 0;
    void move(World::Direction d);
};


#endif //TEST_PROJECT_ACTOR_H
