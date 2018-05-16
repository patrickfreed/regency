#ifndef REGENCY_FACTIONDEFEATED_H
#define REGENCY_FACTIONDEFEATED_H

#include <regency/entity/Faction.h>
#include <vector>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/Sound.hpp>

namespace regency::ui {

class FactionDefeated {
  public:
    explicit FactionDefeated(entity::Faction& f);

    void render(sf::RenderTarget& target);

    void set_visible(bool v);

  private:
    sf::RectangleShape _screen;

    sf::Text _heading;
    sf::Text _body;

    entity::Faction& _faction;
    bool _visible;
};

}
#endif //REGENCY_FACTIONDEFEATED_H
