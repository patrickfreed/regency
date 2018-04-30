#include "Tree.h"

int regency::world::Tree::get_height() {
    return _height;
}

regency::world::TreeType regency::world::Tree::get_type() {
    return _type;
}

regency::world::Tree::Tree(regency::world::TreeType type, int height) : _type{type}, _height{height} {
}
