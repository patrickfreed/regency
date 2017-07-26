
#include "HumanActor.h"
#include <ctime>
#include <iostream>

#include "../Mouse.h"
#include "misc/tasks/MovementTask.h"

namespace regency {
namespace entity {

void HumanActor::tick() {
    if (this->task_queue.empty()) {
        if (Mouse::is_right_clicked() && Mouse::in_window()) {
            world::Tile& t = get_world().get_hovered_tile();
            world::Location dest = t.get_location();
            std::cout << "new dest: " << dest.str() << std::endl;

            this->task_queue.push(
                std::move(std::unique_ptr<MovementTask>(new MovementTask(*this, dest))));
        }
    } else {

        Task& t = *task_queue.front();

        if (t.perform() != Outcome::IN_PROGRESS) {
            std::cout << get_location().str() << std::endl;
            task_queue.pop();
        }
    }
}

HumanActor::HumanActor(world::World& world) : Actor(world), drawable(sf::Vector2f(10, 10)) {
    this->courage = rand() % 100;
    this->curiosity = rand() % 100;
    this->intelligence = rand() % 100;
    this->laziness = rand() % 100;
    this->temper = rand() % 100;

    this->axe = rand() % 100;
    this->sword = rand() % 100;
    this->fishing_rod = rand() % 100;
    this->pickaxe = rand() % 100;
    this->hammer = rand() % 100;

    this->origin = {0, 0};
    this->radius = 5;
}

sf::Drawable& HumanActor::get_drawable() {
    return this->drawable;
}
}
}