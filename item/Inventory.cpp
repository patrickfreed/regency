#include "Inventory.h"

namespace regency::item {

std::vector<Item>::iterator Inventory::begin() {
    return _contents.begin();
}

std::vector<Item>::iterator Inventory::end() {
    return _contents.end();
}

}
