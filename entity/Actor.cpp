
#include <regency/entity/Actor.h>
#include <regency/world/World.h>
#include <regency/Game.h>
#include <SFML/Audio/Sound.hpp>
#include <Assets.h>
#include <iostream>

namespace regency {
namespace entity {

Actor::Actor(world::World& world, Faction *f) : Entity(world), _alert{false}, _faction(f), _alive(true) {
    _punch.setBuffer(Assets::punch1);
    _death.setBuffer(Assets::death);
}

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

        _punch.play();

        return dmg;
    }

    return 0;
}

bool Actor::is_hostile(Actor& other) {
    if (other.is_dead()) {
        return false;
    }

    if (_faction && other._faction) {
        return _faction != other._faction && (!_faction->friendly() || !other._faction->friendly());
    } else if (!other._faction && _faction) {
        return !_faction->friendly();
    } else if (other._faction && !_faction) {
        return !other._faction->friendly();
    } else {
        return false;
    }
}

entity::Faction *Actor::get_faction() {
    return _faction;
}

bool Actor::is_dead() {
    return !_alive;
}

void Actor::die() {
    if (_alive) {
        _alive = false;
        _death.play();

        if (_faction) {
            _faction->decrease_population();
        } else {
            std::cout << "no faction" << std::endl;
        }
    }
}

}
}