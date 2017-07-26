
#ifndef REGENCY_ACTOR_H
#define REGENCY_ACTOR_H

#include "Entity.h"

namespace regency {
namespace entity {

class Actor : public Entity {
  public:
    Actor(world::World& world);

    virtual void tick() = 0;

    virtual sf::Drawable& get_drawable() = 0;

    bool move(world::Direction d);
};
}
}

#endif // REGENCY_ACTOR_H
