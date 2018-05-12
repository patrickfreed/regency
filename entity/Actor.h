
#ifndef REGENCY_ACTOR_H
#define REGENCY_ACTOR_H

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <regency/entity/Entity.h>

namespace regency {
namespace entity {

class Actor : public Entity {
  public:
    explicit Actor(world::World& world);

    ~Actor() override = default;

    virtual void tick() = 0;

    virtual void render(sf::RenderTarget& target, int x, int y) = 0;

    virtual sf::Drawable& get_drawable() = 0;

    bool move(world::Direction d);

    virtual sf::Int32 get_time_per_movement() = 0;

    void set_alert(bool alert);

    bool get_alert();

  private:
    sf::Time _last_movement;

    bool _alert;
};
}
}

#endif // REGENCY_ACTOR_H
