
#include <entity/action/Find.h>

#include <iostream>
#include <algorithm>
#include <optional>

#include <world/gen/RandomGenerator.h>
#include <entity/action/Move.h>

namespace regency::entity::action {

Find::Find(Actor& a, world::Region& area, std::function<bool(world::Tile&)> criteria) :
        Action(a, area), _matches(std::move(criteria)) {
    _tiles_checked = get_action_area().get_number_marked();
}

bool Find::construct_plan() {
    _radius = std::max(5, get_action_area().size() / 3);
    Actor& performer = get_actor();

    if (!get_action_area().contains(performer.get_location())) {
        for (world::Tile& t : get_action_area()) {
            if (performer.get_world().is_traversable(t.get_location())) {
                add_sub_task(std::unique_ptr<Action>(new Move(performer, t.get_location())));
                break;
            }
        }

        if (!has_sub_tasks()) {
            return false;
        }
    }

    return true;
}

Outcome Find::perform() {
    if (Action::perform() == Outcome::IN_PROGRESS) {
        return Outcome::IN_PROGRESS;
    }

    world::World& world = get_actor().get_world();
    world::Location& location = get_actor().get_location();
    world::Region& area = get_action_area();

    int start_x = std::min(std::max(area.get_min_x(), location.get_x() - _radius), area.get_max_x());
    int end_x = std::max(std::min(area.get_max_x(), location.get_x() + _radius), area.get_min_x());

    int start_y = std::min(std::max(area.get_min_y(), location.get_y() - _radius), area.get_max_y());
    int end_y = std::max(std::min(area.get_max_y(), location.get_y() + _radius), area.get_min_y());

    // TODO: make this a BFS
    for (int x = start_x; x <= end_x; ++x) {
        for (int y = start_y; y <= end_y; ++y) {
            world::Tile& tile = world.get_tile(x, y);

            if (_matches(tile)) {
                _dest = world::Location(x, y);
                return Outcome::SUCCESS;
            } else if (!area.is_marked(tile)){
                area.set_marked(tile, true);
                _tiles_checked++;
            }
        }
    }

    if (_tiles_checked == area.size()) {
        return Outcome::FAILURE;
    }

    // get random point in radius, move there. Repeat.
    regency::world::gen::RandomGenerator x_rg(start_x, end_x);
    regency::world::gen::RandomGenerator y_rg(start_y, end_y);

    world::Location next_spot{x_rg.next_int(), y_rg.next_int()};

    add_sub_task(std::unique_ptr<Action>(new Move(get_actor(), next_spot)));

    return Outcome::IN_PROGRESS;
}

std::optional<world::Location> Find::get_find_location() {
    return _dest;
}

int Find::tiles_checked() {
    return _tiles_checked;
}
}