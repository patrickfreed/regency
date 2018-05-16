
#ifndef REGENCY_FACTIONINFO_H
#define REGENCY_FACTIONINFO_H

#include <regency/entity/Faction.h>
#include <vector>
#include <SFML/Graphics/RenderTarget.hpp>

namespace regency::ui {

class FactionInfo {
  public:
    FactionInfo();

    void set_factions(std::vector<entity::Faction> *factions);

    void render(sf::RenderTarget& target);

    void set_visible(bool v);

  private:
    std::vector<entity::Faction> *_factions;
    bool _visible;
};

}
#endif //REGENCY_FACTIONINFO_H
