
#ifndef TEST_PROJECT_MOUSE_H
#define TEST_PROJECT_MOUSE_H


#include <SFML/System.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Mouse {
private:
    static sf::RenderWindow *window;
public:
    static void set_window(sf::RenderWindow& w);
    static sf::Vector2i get_mouse_position();
};


#endif //TEST_PROJECT_MOUSE_H
