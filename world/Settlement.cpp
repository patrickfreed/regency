#include <regency/world/Settlement.h>

namespace regency::world {

Settlement::Settlement(std::string name, Region bounds, entity::Faction& faction) :
        _name(std::move(name)), _bounds(bounds), _faction(&faction) {}

Region& Settlement::get_bounds() {
    return _bounds;
}

std::string& Settlement::get_name() {
    return _name;
}

entity::Faction& Settlement::get_faction() {
    return *_faction;
}

}