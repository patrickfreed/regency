
#include "HumanActor.h"
#include "misc/tasks/MovementTask.h"

void HumanActor::tick() {
    if (this->task_queue.empty()) {
        this->task_queue.push(new MovementTask(*this, make_pair(rand() % 10, rand() % 10)));
    } else {
        Task *t = this->task_queue.front();

        if (t->perform()) {
            task_queue.pop();
            delete t;
        }
    }
}

HumanActor::HumanActor(World& world) : Actor(world), drawable(sf::Vector2f(10, 10)){
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

sf::Drawable &HumanActor::get_drawable() {
    int xx = this->x * TILE_SIZE;
    int yy = this->y * TILE_SIZE;

    this->drawable.setPosition(xx, yy);
    return this->drawable;
}
