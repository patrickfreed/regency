//
// Created by Patrick on 5/12/2018.
//

#include "FactionInfo.h"
#include <regency/Defines.h>
#include <SFML/Graphics/RectangleShape.hpp>
#include <Assets.h>
#include <SFML/Graphics/Text.hpp>

#define OFFSET 100.0f

namespace regency::ui {

void regency::ui::FactionInfo::render(sf::RenderTarget& target) {
    if (!_visible || !_factions) {
        return;
    }

    sf::RectangleShape screen;
    screen.setPosition(OFFSET / 2.0f, OFFSET / 2.0f);
    screen.setSize({WINDOW_SIZE - OFFSET, WINDOW_SIZE - OFFSET});
    screen.setFillColor(sf::Color(73, 73, 68));
    target.draw(screen);

    auto bounds = screen.getGlobalBounds();

    sf::Text heading;
    heading.setFont(Assets::font);
    heading.setFillColor(sf::Color::White);
    heading.setOutlineColor(sf::Color::Black);
    heading.setOutlineThickness(1.0f);
    heading.setCharacterSize(30);
    heading.setString("Faction Information");

    auto heading_bounds = heading.getGlobalBounds();
    heading.setPosition(bounds.left + bounds.width / 2 - heading_bounds.width / 2, bounds.top + 20);
    target.draw(heading);

    int num = 0;

    float padding = 75;
    float height = (bounds.height - 200) / _factions->size() - padding;
    float width = (bounds.width - 100);
    float start = 100;

    for (entity::Faction& f : *_factions) {
        sf::RectangleShape entry;

        float x = bounds.left + 50;
        float y = bounds.top + start + (padding + height) * num;

        entry.setPosition(x, y);
        entry.setSize({width, height});
        entry.setFillColor(sf::Color(79, 81, 79));
        entry.setOutlineColor(sf::Color(104,104,98));

        target.draw(entry);

        sf::Text name_text;
        name_text.setPosition(x + 10, y + 10);
        name_text.setFont(Assets::font);
        name_text.setFillColor(sf::Color::White);
        name_text.setOutlineColor(sf::Color::Black);
        name_text.setOutlineThickness(1.0f);
        name_text.setCharacterSize(20);
        name_text.setString(f.get_name());

        target.draw(name_text);

        sf::Text status_text;
        status_text.setPosition(x + 10, y + 50);
        status_text.setFont(Assets::font);
        status_text.setFillColor(sf::Color::White);
        status_text.setOutlineColor(sf::Color::Black);
        status_text.setOutlineThickness(1.0f);
        status_text.setCharacterSize(12);
        status_text.setString("Status:");
        target.draw(status_text);

        auto status_bounds = status_text.getGlobalBounds();
        status_text.setPosition(status_bounds.left + status_bounds.width + 5, status_bounds.top);

        if (f.get_population() == 0) {
            status_text.setString("Extinct");
        } else if (f.friendly()) {
            status_text.setString("Friendly");
            status_text.setOutlineColor(sf::Color::Green);
            status_text.setOutlineThickness(0.75f);
        } else {
            status_text.setString("Hostile");
            status_text.setOutlineColor(sf::Color::Red);
        }
        target.draw(status_text);

        for (auto& name : f.get_settlments()) {

        }

        ++num;
    }

    sf::Text sample_text;

    sample_text.setPosition(WINDOW_SIZE / 3, WINDOW_SIZE / 3);
    sample_text.setFont(Assets::font);
    sample_text.setFillColor(sf::Color::White);
    sample_text.setOutlineColor(sf::Color::Black);
    sample_text.setOutlineThickness(1.0f);
    sample_text.setCharacterSize(10);
    target.draw(sample_text);
}

FactionInfo::FactionInfo() : _factions{nullptr} {}

void FactionInfo::set_factions(std::vector<entity::Faction> *factions) {
    _factions = factions;
}

void FactionInfo::set_visible(bool v) {
    _visible = !_visible;
}

}
