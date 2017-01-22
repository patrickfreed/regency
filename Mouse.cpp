
#include <SFML/Window/Mouse.hpp>
#include "Mouse.h"

void Mouse::set_window(sf::RenderWindow &w) {
    window = &w;
}

sf::Vector2i Mouse::get_mouse_position() {
    return sf::Mouse::getPosition(*Mouse::window);
}

sf::RenderWindow *Mouse::window;