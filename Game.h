#ifndef REGENCY_GAME_H
#define REGENCY_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <regency/world/World.h>

namespace regency {

enum class Selector {
    NONE,
    HARVEST,
    PATROL
};

class Game {
  public:
    static Game& get_instance();

    Game();

    Game(const Game& other) = delete;

    void operator=(const Game& other) = delete;

    void start();

    world::World& get_world();

    sf::Time get_time();

  private:
    void tick();

    // TODO: entity not actor
    void focus_entity(std::shared_ptr<entity::Actor> e);

    sf::RenderWindow _main_window;
    world::World _world;

    std::shared_ptr<entity::Actor> _focus;

    sf::Clock _clock;

    Selector _action;
};
}

#endif // REGENCY_GAME_H
