
#include <regency/entity/action/Eat.h>

#include <regency/entity/action/Find.h>
#include <regency/entity/action/Move.h>

namespace regency::entity::action {

Eat::Eat(regency::entity::Actor& a) : Action(a) {}

Outcome Eat::perform() {
    if (has_sub_tasks()) {
        Action& t = get_sub_task();

        if (t.do_action() != Outcome::IN_PROGRESS) {
            pop_sub_task();
        }

        return Outcome::IN_PROGRESS;
    }

    // actually eat
    return Outcome::SUCCESS;
}

bool Eat::construct_plan() {
    //std::unique_ptr<Find> ff = std::make_unique<Find>(_performer);

    auto go_to_food = [this](Action& f) {
        auto& find = dynamic_cast<Find&>(f);

        // std::cout << "in onsuccess" << std::endl;

        if (f.get_status() == Outcome::SUCCESS) {
            //add_sub_task(std::make_unique<Move>(_performer, find.get_find_location()));
        }
    };

    // ff->then(go_to_food);
    //add_sub_task(std::move(ff));

    return true;
}
}