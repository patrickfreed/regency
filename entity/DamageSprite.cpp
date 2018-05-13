
#include <world/gen/RandomGenerator.h>
#include <Assets.h>
#include <world/Location.h>
#include "DamageSprite.h"

namespace regency::entity {

DamageSprite::DamageSprite(std::string damage, world::Location source, bool crit) : _crit(crit), _source{source} {
    world::gen::RandomGenerator rnd{0, 100};
    if (rnd.next_int() < 50) {
        _direction = -1;
    } else {
        _direction = 1;
    }

    _text.setFont(Assets::font);
    _text.setCharacterSize(12);
    _text.setOutlineColor(sf::Color::Black);
    _text.setOutlineThickness(1.0);

    _text.setString(damage);
    _x = 0.0f;
    _offset = -20.0f;
    _alpha = 500;
}

void DamageSprite::render(sf::RenderTarget& target, int x, int y) {
    _text.setPosition(x + _x * 3.0f, y + _offset + _x*_x);

    _x += _direction * 0.15;

    target.draw(_text);
    _alpha -= 5;

    if (_alpha <= 0) {
        return;
    }

    _text.setFillColor(sf::Color(255, 255, 255, std::min(_alpha, 255)));
    _text.setOutlineColor(sf::Color(0, 0, 0, std::min(_alpha, 255)));
}

bool DamageSprite::visible() {
    return _alpha > 0;
}

world::Location& DamageSprite::get_source() {
    return _source;
}

}