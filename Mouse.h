
#ifndef REGENCY_MOUSE_H
#define REGENCY_MOUSE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System.hpp>

namespace regency {

class Mouse {
  private:
    static sf::RenderWindow* window;

  public:
    static void set_window(sf::RenderWindow& w);

    static sf::Vector2i get_mouse_position();
};
}

#endif // REGENCY_MOUSE_H
