
#include "PathFinder.h"

#include <iostream>

namespace regency {
namespace world {

PathFinder::PathFinder(entity::Actor& actor,
                       const regency::world::Location& start,
                       const regency::world::Location& dest)
    : _actor{actor}, _src{start}, _dst{dest}, _finished{false} {}

bool PathFinder::find_path() {
    World& world = _actor.get_world();

    if (!world.is_traversable(_dst)) {
        return false;
    }

    _open.insert(_src);

    auto get = [](std::unordered_map<Location, double, LocationHasher>& map, const Location& key) {
        if (map.find(key) != map.end()) {
            return map[key];
        } else {
            return 10000.0;
        }
    };

    auto hueristic = [](Location& start, Location& goal) {
        return start.distance_to(goal, Distance::MANHATTAN);
    };

    _g_score[_src] = 0;
    _f_score[_src] = hueristic(_src, _dst);
    _from[_src] = _src;

    auto lowest = [this, get]() {
        double low = 100000;
        Location low_loc;

        for (auto& node : _open) {
            double score = get(_f_score, node);

            if (score < low) {
                low_loc = node;
                low = score;
            }
        }

        _closed.insert(low_loc);
        _open.erase(_open.find(low_loc));
        return low_loc;
    };

    while (!_open.empty()) {
        Location current = lowest();

        if (current == _dst) {
            std::cout << "finished path" << std::endl;
            _finished = true;
            return true;
        }

        for (int di = 1; di <= Direction::SOUTH_EAST; ++di) {
            Direction d = static_cast<Direction>(di);

            Location neighbor = current.get_adjacent(d);

            if (!neighbor.is_valid()) {
                continue;
            }

            Tile& neighbor_tile = world.get_tile(neighbor);

            if (_closed.find(neighbor) != _closed.end() || !world.is_traversable(neighbor)) {
                continue;
            }

            if (_open.find(neighbor) == _open.end()) {
                _open.insert(neighbor);
            }

            double g = _g_score[current] + current.distance_to(neighbor); // 1
            if (g > get(_g_score, neighbor)) {
                continue;
            }

            _from[neighbor] = current;
            _g_score[neighbor] = g;
            _f_score[neighbor] = g + hueristic(neighbor, _dst);
        }
    }

    return false;
}

std::list<Location>::iterator PathFinder::get_path() {
    if (!_finished) {
        throw std::runtime_error("Not finished path yet");
    }

    if (_path.empty()) {
        Location current = _dst;

        do {
            _path.push_back(current);
            current = _from[current];
        } while (!(current == _src));
    }

    return _path.begin();
}

bool PathFinder::is_finished() {
    return _finished;
}

Location PathFinder::next() {
    if (!is_finished()) {
        throw std::runtime_error("no path");
    }

    if (!has_next()) {
        throw std::runtime_error("path exhausted");
    }

    Location l = _path.back();
    _path.pop_back();
    // TODO: check if possible to move to here

    return l;
}

bool PathFinder::has_next() {
    return _path.size() > 0;
}
}
}
