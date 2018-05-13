//
// Created by Patrick on 5/12/2018.
//

#include "ActorInfo.h"
#include <regency/Defines.h>
#include <regency/Assets.h>

namespace regency::ui {

ActorInfo::ActorInfo(regency::entity::HumanActor& actor) : _actor(actor) {}

void ActorInfo::render(sf::RenderTarget& t) {
    sf::RectangleShape screen;
    screen.setPosition(WINDOW_SIZE / 4, WINDOW_SIZE / 4);
    screen.setSize({WINDOW_SIZE / 4, WINDOW_SIZE / 4});
    screen.setFillColor(sf::Color::Black);
    t.draw(screen);

    sf::Text sample_text;

    sample_text.setPosition(WINDOW_SIZE / 3, WINDOW_SIZE / 3);
    sample_text.setFont(Assets::font);
    sample_text.setFillColor(sf::Color::White);
    sample_text.setOutlineColor(sf::Color::Black);
    sample_text.setOutlineThickness(1.0f);
    sample_text.setCharacterSize(10);
    sample_text.setString(_actor.get_name());
    t.draw(sample_text);
}

}