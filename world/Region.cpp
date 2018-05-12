#include <regency/world/Region.h>

#include <regency/Game.h>

namespace regency::world {

Region::Region(Location a, Location b, bool checks):
        _world(Game::get_instance().get_world()), _a(a), _b(b) {
    _min_x = std::min(_a.get_x(), _b.get_x());
    _min_y = std::min(_a.get_y(), _b.get_y());

    _max_x = std::max(_a.get_x(), _b.get_x());
    _max_y = std::max(_a.get_y(), _b.get_y());

    if (checks) {
        _using_marks = true;
        _marks.resize(size());
    }
}

Region& Region::operator=(const Region& other) {
    _min_x = other._min_x;
    _max_x = other._max_x;

    _a = other._a;
    _b = other._b;

    _using_marks = other._using_marks;
    _marks = other._marks;

    _min_y = other._min_y;
    _max_y = other._max_y;

    return *this;
}

bool Region::contains(const Location& loc) const {
    return _min_x <= loc.get_x() && loc.get_x() <= _max_x &&
           _min_y <= loc.get_y() && loc.get_y() <= _max_y;
}

int Region::get_max_x() {
    return _max_x;
}

int Region::get_min_x() {
    return _min_x;
}

int Region::get_max_y() {
    return _max_y;
}

int Region::get_min_y() {
    return _min_y;
}

int Region::size() {
    return (_max_x - _min_x + 1) * (_max_y - _min_y + 1);
}

bool Region::is_marked(int x, int y)const {
    if (!_using_marks) {
        return false;
    }

    int width = _max_x - _min_x + 1;

    return _marks[(x - _min_x) % width + (y - _min_y) * width];
}

bool Region::is_marked(const Tile &t) {
    return is_marked(t.get_location().get_x(), t.get_location().get_y());
}

void Region::set_marked(int x, int y, bool mark) {
    if (!_using_marks) {
        _marks.resize(size());
        _using_marks = true;
    }

    int width = _max_x - _min_x + 1;

    _marks[(x - _min_x) % width + (y - _min_y) * width] = mark;
}

void Region::set_marked(const Tile &t, bool mark) {
    set_marked(t.get_location().get_x(), t.get_location().get_y(), mark);
}

int Region::get_number_marked() const {
    int num = 0;

    for (int x = _min_x; x <= _max_x; ++x) {
        for (int y = _min_y; y <= _max_y; ++y) {
            if (is_marked(x, y)) {
                ++num;
            }
        }
    }

    return num;
}

Region::RegionIterator Region::begin() const {
    return RegionIterator(*this);
}

Region::RegionIterator Region::end() const {
    RegionIterator it(*this);

    it._y = it._max_y + 1;
    it._x = it._min_x;

    return it;
}

Location Region::get_closest_point(Location other) {
    int x = std::min(std::max(_min_x, other.get_x()), _max_x);
    int y = std::min(std::max(_min_y, other.get_y()), _max_y);

    return Location{x, y};
}

Region::RegionIterator::RegionIterator(const Region& region) {
    _world = &region._world;

    _x = region._min_x;
    _y = region._min_y;

    _min_x = _x;
    _min_y = _y;

    _max_x = region._max_x;
    _max_y = std::max(region._a.get_y(), region._b.get_y());
}

Region::RegionIterator &Region::RegionIterator::operator++() {
    _x++;

    if (_x > _max_x) {
        _x = _min_x;
        _y++;
    }
}

Tile& Region::RegionIterator::operator*() {
    if (!_world || _y > _max_y) {
        throw std::runtime_error("dereferencing end iterator");
    }

    return _world->get_tile(_x, _y);
}

bool Region::RegionIterator::operator==(const Region::RegionIterator &other) const {
    return other._x == _x && other._y == _y && other._world == _world &&
           other._min_x == _min_x && other._max_x == _max_x && other._max_y == _max_y &&
           other._min_y == _min_y;
}

bool Region::RegionIterator::operator!=(const Region::RegionIterator &other) const {
    return !(other == *this);
}
}
