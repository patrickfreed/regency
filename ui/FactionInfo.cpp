#include <regency/ui/FactionInfo.h>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include <regency/Defines.h>
#include <regency/Assets.h>

#define OFFSET 100.0f

namespace regency::ui {

void regency::ui::FactionInfo::render(sf::RenderTarget& target) {
    if (!_visible || !_factions) {
        return;
    }

    sf::RectangleShape screen;
    screen.setPosition(OFFSET / 2.0f, OFFSET / 2.0f - 20.0f);
    screen.setSize({WINDOW_SIZE - OFFSET, WINDOW_SIZE - OFFSET});
    screen.setFillColor(sf::Color(73, 73, 68));
    screen.setOutlineColor(sf::Color::Black);
    screen.setOutlineThickness(2.0f);
    target.draw(screen);

    auto bounds = screen.getGlobalBounds();

    sf::Text heading;
    heading.setFont(Assets::font);
    heading.setFillColor(sf::Color::White);
    heading.setOutlineColor(sf::Color::Black);
    heading.setOutlineThickness(1.5f);
    heading.setCharacterSize(30);
    heading.setString("Faction Information");

    auto heading_bounds = heading.getGlobalBounds();
    heading.setPosition(bounds.left + bounds.width / 2 - heading_bounds.width / 2, bounds.top + 20);
    target.draw(heading);

    int num = 0;

    float padding = 10;
    float height = (bounds.height - 150) / _factions->size() - padding;
    float width = (bounds.width - 100);
    float start = 100;

    for (entity::Faction& f : *_factions) {
        sf::RectangleShape entry;

        float x = bounds.left + 50;
        float y = bounds.top + start + (padding + height) * num;

        float left_align = x + 10;

        entry.setPosition(x, y);
        entry.setSize({width, height});
        entry.setFillColor(sf::Color(79, 81, 79));
        entry.setOutlineColor(sf::Color(104,104,98));

        target.draw(entry);

        sf::Text name_text;
        name_text.setPosition(left_align, y + 10);
        name_text.setFont(Assets::font);
        name_text.setFillColor(sf::Color::White);
        name_text.setOutlineColor(sf::Color::Black);
        name_text.setOutlineThickness(1.0f);
        name_text.setCharacterSize(25);
        name_text.setString(f.get_name());

        target.draw(name_text);

        float status_vertical = y + 50;
        sf::Text status_text;
        status_text.setPosition(left_align, status_vertical);
        status_text.setFont(Assets::font);
        status_text.setFillColor(sf::Color::White);
        status_text.setOutlineColor(sf::Color::Black);
        status_text.setOutlineThickness(1.0f);
        status_text.setCharacterSize(18);
        status_text.setString("Status:");
        target.draw(status_text);

        auto status_bounds = status_text.getGlobalBounds();
        status_text.setPosition(status_bounds.left + status_bounds.width + 5, status_vertical);

        if (f.get_population() == 0) {
            status_text.setString("Extinct");
        } else if (f.friendly()) {
            status_text.setString("Friendly");
            status_text.setOutlineColor(sf::Color::Green);
        } else {
            status_text.setString("Hostile");
            status_text.setOutlineColor(sf::Color::Red);
        }
        target.draw(status_text);

        status_bounds = status_text.getGlobalBounds();
        status_text.setPosition(left_align, status_bounds.top + 20);
        status_text.setString("Population: " + std::to_string(f.get_population()));
        status_text.setOutlineColor(sf::Color::Black);
        target.draw(status_text);

        status_bounds = status_text.getGlobalBounds();
        float vertical_align = status_bounds.top + 20;
        status_text.setPosition(left_align, vertical_align);
        status_text.setString("Settlements: ");
        target.draw(status_text);

        if (f.get_population() > 0) {
            for (auto& name : f.get_settlments()) {
                status_bounds = status_text.getGlobalBounds();
                status_text.setPosition(status_bounds.left + status_bounds.width, vertical_align);
                status_text.setString(name);
                target.draw(status_text);
            }
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
