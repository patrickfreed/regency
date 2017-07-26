
#include "Mouse.h"

#include <SFML/Window/Mouse.hpp>

namespace regency {

void Mouse::set_window(sf::RenderWindow& w) {
    window = &w;
}

sf::Vector2i Mouse::get_mouse_position() {
    return sf::Mouse::getPosition(*Mouse::window);
}

bool Mouse::in_window() {
    sf::Vector2i mouse_pos = Mouse::get_mouse_position();
    auto window_size = window->getSize();

    return mouse_pos.x >= 0 && mouse_pos.x < window_size.x && mouse_pos.y >= 0 &&
           mouse_pos.y < window_size.y;
}

bool Mouse::is_right_clicked() {
    return sf::Mouse::isButtonPressed(sf::Mouse::Right);
}

sf::RenderWindow* Mouse::window;
}