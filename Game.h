#ifndef REGENCY_GAME_H
#define REGENCY_GAME_H

#include "world/World.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace regency {
class Game {
  public:
    Game();

    void start();

    world::World& get_world();

    static Game GameInstance;

  private:
    void tick();

    sf::RenderWindow _main_window;
    world::World _world;
};
}

#endif // REGENCY_GAME_H
