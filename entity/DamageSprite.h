#ifndef REGENCY_DAMAGESPRITE_H
#define REGENCY_DAMAGESPRITE_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

namespace regency::entity {
class DamageSprite {
  public:
    explicit DamageSprite(std::string damage, world::Location source, bool crit = false);

    void render(sf::RenderTarget& target, int x, int y);

    bool visible();

    world::Location& get_source();

  private:
    world::Location _source;

    sf::Text _text;

    bool _crit;

    int _alpha;

    float _offset;
    float _x;
    float _direction;
};
}

#endif //REGENCY_DAMAGESPRITE_H
