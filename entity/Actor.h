
#ifndef REGENCY_ACTOR_H
#define REGENCY_ACTOR_H

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <regency/entity/Entity.h>
#include <SFML/Audio/Sound.hpp>
#include "Faction.h"

namespace regency {
namespace entity {

class Actor : public Entity {
  public:
    explicit Actor(world::World& world, Faction *faction);

    ~Actor() override = default;

    virtual void tick() = 0;

    virtual void render(sf::RenderTarget& target, int x, int y) = 0;

    virtual sf::Drawable& get_drawable() = 0;

    bool move(world::Direction d);

    virtual sf::Int32 get_time_per_movement() = 0;

    virtual sf::Int32 get_time_per_attack() = 0;

    void set_alert(bool alert);

    bool get_alert();

    virtual int attack(Actor& victim);

    virtual int get_damage_dealt(Actor& recipient);

    virtual int damage(int amount) = 0;

    bool is_hostile(Actor& other);

    entity::Faction *get_faction();

    bool is_dead();

    void die();

  private:
    sf::Sound _punch;
    sf::Sound _death;

    sf::Time _last_movement;
    sf::Time _last_attack;

    bool _alert;
    bool _alive;

    entity::Faction *_faction;
};
}
}

#endif // REGENCY_ACTOR_H
