
#include <regency/entity/HumanActor.h>

#include <iostream>

#include <SFML/Window/Keyboard.hpp>

#include <regency/Mouse.h>
#include <regency/entity/action/Eat.h>
#include <regency/entity/action/Move.h>
#include <regency/world/gen/RandomGenerator.h>
#include <regency/Assets.h>
#include <Game.h>

namespace regency {
namespace entity {

HumanActor::HumanActor(world::World& world) : Actor(world) {
    world::gen::RandomGenerator rng{0, 100};

    _courage = rng.next_int();
    _curiosity = rng.next_int();
    _intelligence = rng.next_int();
    _laziness = rng.next_int();
    _temper = rng.next_int();

    _axe = rng.next_int();
    _sword = rng.next_int();
    _fishing_rod = rng.next_int();
    _pickaxe = rng.next_int();
    _hammer = rng.next_int();

    _health = 100;
    _hunger = 0;
    _thirst = 0;
    _energy = 100;

    _origin = {0, 0};
    _radius = 5;

    _name = Assets::reserve_name(NameList::PEOPLE);
    _show_name = false;

    _sprite.setTexture(Assets::human_placeholder);

    _text.setString(_name);
    _text.setFont(Assets::font);
    _text.setCharacterSize(12);
    _text.setOutlineColor(sf::Color::Red);
    _text.setOutlineThickness(1.0);

    _recent_damage = 0;
}

void HumanActor::tick() {
    if (!_task_queue.empty()) {
        action::Action& t = *_task_queue.front();

        if (t.do_action() != action::Outcome::IN_PROGRESS) {
            pop_task();

            if (_show_name && !_task_queue.empty()) {
                action::Action& next = *_task_queue.front();

                for (world::Tile& tile : next.get_action_area()) {
                    tile.set_highlight(world::Highlight::PERMANENT);
                }
            }
        }
    }
}

sf::Drawable& HumanActor::get_drawable() {
    return _sprite;
}

const std::string& HumanActor::get_name() const {
    return _name;
}

void HumanActor::render(sf::RenderTarget& target, int x, int y) {
    _sprite.setPosition(x, y);

    if (_recent_damage > 0) {
        DamageSprite dsprite(_recent_damage, get_location());
        _recent_damage = 0;
        _damages.push_front(std::move(dsprite));
        _sprite.setColor(sf::Color::Red);
    } else {
        target.draw(_sprite);
    }

    world::World& world = get_world();

    // sf::IntRect tile_rect(x, y, world.get_tile_size(), world.get_tile_size());
    if (_show_name) {
        sf::FloatRect bounds = _text.getGlobalBounds();
        _text.setPosition(x - bounds.width / 2 + 5, y - 15);
        target.draw(_text);
    }

    if (get_alert()) {
        sf::Sprite alert{Assets::alert};
        alert.setPosition(x, y - 20);
        target.draw(alert);
    }

    while (!_damages.empty() && !_damages.front().visible()) {
        _damages.pop_front();
    }

    for (auto& damage_text : _damages) {
        sf::Vector2i coords = get_world().get_vector_from_location(damage_text.get_source());
        damage_text.render(target, coords.x, coords.y);
    }

    if (_damages.empty()) {
        _sprite.setColor(sf::Color::White);
    }
}

void HumanActor::assign_task(std::unique_ptr<action::Action>&& task, bool override) {
    if (override) {
        pop_task();
    }

    if (_show_name && _task_queue.empty()) {
        for (world::Tile& tile : task->get_action_area()) {
            tile.set_highlight(world::Highlight::PERMANENT);
        }
    }
    _task_queue.push(std::move(task));
}

void HumanActor::set_name_visible(bool name) {
    _show_name = name;
}

sf::Int32 HumanActor::get_time_per_movement() {
    return 100;
}

std::optional<world::Region> HumanActor::get_work_area() {
    if (!_task_queue.empty()) {
        return _task_queue.front()->get_action_area();
    }

    return {};
}

void HumanActor::pop_task() {
    if (_task_queue.empty()) {
        return;
    }

    if (_show_name) {
        for (world::Tile& tile : _task_queue.front()->get_action_area()) {
            tile.set_highlight(world::Highlight::NONE);
        }
    }

    _task_queue.front()->abort();
    _task_queue.pop();
}

int HumanActor::damage(int amount) {
    _health -= amount;
    _recent_damage += amount;

    return _health;
}

int HumanActor::get_damage_dealt(Actor& recipient) {
    world::gen::RandomGenerator rnd{_sword / 2, _sword};
    int middle = rnd.next_int();

    float temper_modifier = std::max(1.0f, (_temper / 100.0f) * 2.0f);

    middle = static_cast<int>(middle * temper_modifier);

    return middle;

}

sf::Int32 HumanActor::get_time_per_attack() {
    return 500;
}

}
}