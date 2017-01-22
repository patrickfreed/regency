#ifndef TEST_PROJECT_GAME_H
#define TEST_PROJECT_GAME_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "world/World.h"

class Game {
public:
    Game();
    void start();
    World get_world();
    static Game GameInstance;

private:
    void tick();
    sf::RenderWindow _main_window;
    World world;
};


#endif //TEST_PROJECT_GAME_H
