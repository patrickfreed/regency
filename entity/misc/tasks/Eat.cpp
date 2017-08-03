
#include "Eat.h"
#include "Find.h"
#include "Move.h"
#include <iostream>

namespace regency::entity::task {

Eat::Eat(regency::entity::Actor& a) : Task(a) {}

Outcome Eat::perform() {
    if (has_sub_tasks()) {
        Task& t = get_sub_task();

        if (t.do_task() != Outcome::IN_PROGRESS) {
            pop_sub_task();
        }

        return Outcome::IN_PROGRESS;
    }

    // actually eat
    return Outcome::SUCCESS;
}

bool Eat::construct_plan() {
    std::unique_ptr<Find> ff = std::make_unique<Find>(performer);

    auto go_to_food = [this](Task& f) {
        Find& find = dynamic_cast<Find&>(f);

        std::cout << "in onsuccess" << std::endl;

        if (f.status() == Outcome::SUCCESS) {
            add_sub_task(std::make_unique<Move>(performer, find.get_find_location()));
        }
    };

    ff->on_success(go_to_food);
    add_sub_task(std::move(ff));

    return true;
}
}