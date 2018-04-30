
#include "HumanActor.h"
#include <SFML/Window/Keyboard.hpp>
#include <ctime>
#include <iostream>

#include "../Mouse.h"
#include "misc/tasks/Eat.h"
#include "misc/tasks/Move.h"

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
    courage = rand() % 100;
    curiosity = rand() % 100;
    intelligence = rand() % 100;
    laziness = rand() % 100;
    temper = rand() % 100;

    axe = rand() % 100;
    sword = rand() % 100;
    fishing_rod = rand() % 100;
    pickaxe = rand() % 100;
    hammer = rand() % 100;

    health = 100;
    hunger = 0;
    thirst = 0;
    energy = 100;

    origin = {0, 0};
    radius = 5;
}

sf::Drawable& HumanActor::get_drawable() {
    return drawable;
}
}
}