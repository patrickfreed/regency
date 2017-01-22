#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <sstream>
#include "Game.h"
#include "Mouse.h"
#include "Defines.h"

Game::Game() : world(World("world_name_placeholder")) {
}

void Game::start() {
    _main_window.create(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE, 32), "Midget Castle");
    _main_window.setFramerateLimit(60);
    Mouse::set_window(_main_window);

    // load assets here - for now just Material colors (not textures...)
    // Material::load_colors();

    this->world.generate();
    Game::tick();
}

void Game::tick() {
    sf::Event currentEvent;
    sf::Clock clock;

    sf::Font font;
    font.loadFromFile("../res/font/pixelmix.ttf");

    sf::Text mouse_coords_text;
    mouse_coords_text.setFont(font);
    //mouse_coords_text.setFillColor(sf::Color::White);
    //mouse_coords_text.setCharacterSize(10);
    mouse_coords_text.setPosition(10, 10);

    while(_main_window.isOpen()) {
        _main_window.clear(sf::Color(255, 0, 0));

        if (_main_window.pollEvent(currentEvent)) {
            if (currentEvent.type == sf::Event::Closed) {
                std::cout << "Bye!" << std::endl;
                break;
            } else if (currentEvent.type == sf::Event::KeyPressed) {
                if (currentEvent.key.code == sf::Keyboard::G) {
                    cout << "regenerating...";
                    this->world.generate();
                } else if (currentEvent.key.code == sf::Keyboard::Z) {
                    this->world.zoom(false);
                }
            }
        }

        this->world.tick();
        this->world.render(_main_window);

        sf::Vector2i mouse_coords = Mouse::get_mouse_position();

        ostringstream builder;
        builder << mouse_coords.x << ", " << mouse_coords.y;
        mouse_coords_text.setString(builder.str());

        _main_window.draw(mouse_coords_text);

        _main_window.display();

        //sleep(1);
    }
}

World Game::get_world() {
    return this->world;
}
