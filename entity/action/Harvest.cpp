#include <entity/action/Harvest.h>

#include <entity/action/Find.h>
#include <entity/action/Move.h>

namespace regency::entity::action {

Harvest::Harvest(Actor& performer, world::Region work_area) :
        Action(performer, work_area), _found_target(false), _tiles_checked{0} {}

Outcome Harvest::perform() {
    if (Action::perform() == Outcome::IN_PROGRESS) {
        return Outcome::IN_PROGRESS;
    }

    if (_found_target) {
        world::Tile& tree_tile = get_actor().get_world().get_tile(_target_loc.get_adjacent(world::Direction::SOUTH));

        tree_tile.set_tree(world::Tree());

        _found_target = false;
        construct_plan();

        return Outcome::IN_PROGRESS;
    }

    return Outcome::SUCCESS;
}

bool Harvest::construct_plan() {
    auto criteria = [](world::Tile& tile) {
        return tile.get_tree().get_type() != world::TreeType::NONE;
    };

    auto assign_target = [criteria, this](Action& f) {
        auto& find = dynamic_cast<Find&>(f);

        if (find.get_status() != Outcome::SUCCESS) {
            return;
        }

        _tiles_checked += find.tiles_checked();
        _found_target = true;
        _target_loc = find.get_find_location()->get_adjacent(world::Direction::NORTH);
        set_action_area(find.get_action_area());

        auto verify_move = [this](Action& f) {
            if (f.get_status() != Outcome::SUCCESS) {
                _found_target = false;
            }
        };

        auto move_task = std::unique_ptr<Action>(new Move(get_actor(), _target_loc));
        move_task->then(verify_move);
        add_sub_task(std::move(move_task));
    };

    auto find_task = std::unique_ptr<Action>(new Find(get_actor(), get_action_area(), criteria));
    find_task->then(assign_target);
    add_sub_task(std::move(find_task));

    return true;
}
}
