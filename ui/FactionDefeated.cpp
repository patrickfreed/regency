
#include "FactionDefeated.h"
#include <regency/Assets.h>
#include <SFML/Graphics/RectangleShape.hpp>
#include <regency/Defines.h>
#include <SFML/Graphics/Text.hpp>

#define OFFSET 300.0f

namespace regency::ui {

FactionDefeated::FactionDefeated(entity::Faction& f) : _faction(f) {
    _screen.setPosition(OFFSET / 2.0f, OFFSET / 2.0f);
    _screen.setSize({WINDOW_SIZE - OFFSET, WINDOW_SIZE - OFFSET});
    _screen.setFillColor(sf::Color(73, 73, 68));

    auto bounds = _screen.getGlobalBounds();

    _heading.setFont(Assets::font);
    _heading.setFillColor(sf::Color::White);
    _heading.setOutlineColor(sf::Color::Black);
    _heading.setOutlineThickness(1.0f);
    _heading.setCharacterSize(30);
    _heading.setString("FACTION DEFEATED");

    auto heading_bounds = _heading.getGlobalBounds();
    _heading.setPosition(bounds.left + bounds.width / 2 - heading_bounds.width / 2, bounds.top + 20);

    heading_bounds = _heading.getGlobalBounds();
    std::string body_string =
            "With their final defeat at " +
            _faction.get_settlments()[0] +
            // " by the hands of the " +
            // _faction.get_defeater()->get_name() +
            ", \n\t\tthe " + _faction.get_name() +
            " \n have been extinguished from these lands.";

    _body.setFont(Assets::font);
    _body.setFillColor(sf::Color::White);
    _body.setOutlineColor(sf::Color::Black);
    _body.setOutlineThickness(1.0f);
    _body.setCharacterSize(20);
    _body.setString(body_string);
    _body.setPosition(heading_bounds.left - 100, heading_bounds.top + 100);
}

void FactionDefeated::render(sf::RenderTarget& target) {
    target.draw(_screen);
    target.draw(_heading);
    target.draw(_body);
}
}
