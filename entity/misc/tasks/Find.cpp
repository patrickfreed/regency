
#include "Find.h"
#include "../../../world/World.h"
#include "../../../world/gen/RandomGenerator.h"
#include "Move.h"
#include <iostream>

namespace regency::entity::task {

Find::Find(regency::entity::Actor& a) : Task(a) {
    construct_plan();
}

bool Find::construct_plan() {
    // figure out radius

    _radius = 25;

    return true;
}

Outcome Find::perform() {
    if (has_sub_tasks()) {
        Task& t = get_sub_task();

        if (t.do_task() != Outcome::IN_PROGRESS) {
            pop_sub_task();
        }

        return Outcome::IN_PROGRESS;
    }

    world::World& world = performer.get_world();
    world::Location& location = performer.get_location();

    int start_x = std::max(0, location.get_x() - _radius);
    int end_x = std::min(WORLD_SIZE, location.get_x() + _radius);

    int start_y = std::max(0, location.get_y() - _radius);
    int end_y = std::min(WORLD_SIZE, location.get_y() + _radius);

    // TODO: make this a BFS
    for (int x = start_x; x < end_x; ++x) {
        for (int y = start_y; y < end_y; ++y) {
            if (world.get_tile(x, y).get_material() == &world::Material::SAND) {
                std::cout << "found it!" << std::endl;

                _dest = world::Location(x, y);
                _status = Outcome::SUCCESS;
                return _status;
            }
        }
    }

    // get random point in radius, move there. Repeat.
    regency::world::gen::RandomGenerator x_rg(start_x, end_x);
    regency::world::gen::RandomGenerator y_rg(start_y, end_y);

    world::Location next_spot{x_rg.next_int(), y_rg.next_int()};

    add_sub_task((std::make_unique<task::Move>(performer, next_spot)));

    return Outcome::IN_PROGRESS;
}

world::Location Find::get_find_location() {
    if (_status != Outcome::SUCCESS) {
        throw std::runtime_error("Haven't found anything.");
    }

    return _dest;
}
}