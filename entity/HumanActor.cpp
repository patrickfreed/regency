
#include "HumanActor.h"
#include <SFML/Window/Keyboard.hpp>
#include <ctime>
#include <iostream>

#include "../Mouse.h"
#include "misc/tasks/Eat.h"
#include "misc/tasks/Move.h"
#include "../world/gen/RandomGenerator.h"
#include "../Assets.h"

namespace regency {
namespace entity {

void HumanActor::tick() {
    if (this->task_queue.empty()) {
        if (Mouse::is_right_clicked() && Mouse::in_window()) {
            world::Tile& t = get_world().get_hovered_tile();
            world::Location dest = t.get_location();
            std::cout << "new dest: " << dest.str() << std::endl;

            task_queue.push(
                    std::move(std::unique_ptr<task::Move>(new task::Move(*this, dest))));
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
            std::cout << "adding new eat task" << std::endl;
            task_queue.push(std::make_unique<task::Eat>(*this));
        }
    } else {
        task::Task& t = *task_queue.front();

        if (t.do_task() != task::Outcome::IN_PROGRESS) {
            std::cout << get_location().str() << std::endl;
            task_queue.pop();
        }
    }
}

HumanActor::HumanActor(world::World& world) : Actor(world), drawable(sf::Vector2f(10, 10)) {
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

    _sprite.setTexture(Assets::human_placeholder);
}

sf::Drawable& HumanActor::get_drawable() {
    return _sprite;
}

void HumanActor::render(sf::RenderTexture render_texture) {

}
}
}