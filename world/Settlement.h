
#ifndef REGENCY_SETTLEMENT_H
#define REGENCY_SETTLEMENT_H

#include <regency/world/Region.h>
#include <entity/Faction.h>

namespace regency::world {

class Settlement {
  public:
    Settlement(std::string name, Region bounds, entity::Faction& faction);

    Region& get_bounds();

    std::string& get_name();

    entity::Faction& get_faction();

  private:
    std::string _name;

    entity::Faction *_faction;

    Region _bounds;
};
}

#endif //REGENCY_SETTLEMENT_H
