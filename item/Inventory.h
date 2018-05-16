#ifndef REGENCY_INVENTORY_H
#define REGENCY_INVENTORY_H

#include <vector>
#include "Item.h"

namespace regency::item {

class Inventory {
  public:
    Inventory() = default;

    std::vector<Item>::iterator begin();

    std::vector<Item>::iterator end();

  private:
    std::vector<Item> _contents;
};

}

#endif //REGENCY_INVENTORY_H
