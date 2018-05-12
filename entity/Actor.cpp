
#include <regency/entity/Actor.h>
#include <regency/world/World.h>
#include <regency/Game.h>

namespace regency {
namespace entity {

Actor::Actor(world::World& world) : Entity(world), _alert{false} {}

bool Actor::move(world::Direction d) {
    sf::Time current_time = Game::get_instance().get_time();

    if ((current_time - _last_movement).asMilliseconds() >= get_time_per_movement()) {
        _last_movement = Game::get_instance().get_time();
        return get_world().move(*this, d);
    }

    return false;
}

void Actor::set_alert(bool alert) {
    _alert = alert;
}

bool Actor::get_alert() {
    return _alert;
}

int Actor::get_damage_dealt(Actor& recipient) {
    return 0;
}

int Actor::attack(Actor& victim) {
    sf::Time current_time = Game::get_instance().get_time();

    if ((current_time - _last_attack).asMilliseconds() >= get_time_per_attack()) {
        int dmg = get_damage_dealt(victim);
        victim.damage(dmg);
        _last_attack = Game::get_instance().get_time();
        return dmg;
    }

    return 0;
}

}
}