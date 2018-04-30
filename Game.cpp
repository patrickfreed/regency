#include "Game.h"
#include "Mouse.h"
#include "entity/HumanActor.h"
#include "world/gen/StandardWorldGen.h"
#include "world/gen/biome/DesertBiome.h"
#include "world/gen/biome/GrasslandBiome.h"
#include "world/gen/biome/MountainBiome.h"
#include "world/gen/biome/WaterBiome.h"

#include <iostream>
#include <memory>
#include <sstream>
#include <thread>

namespace regency {

Game::Game() : _world("world_name_placeholder") {}

world::gen::StandardWorldGen get_default_gen() {
    using namespace world::gen;

    StandardWorldGen generator{"basic", DEFAULT_WATER_LEVEL};

    std::unique_ptr<Biome> grassland(new GrasslandBiome(DEFAULT_WATER_LEVEL, 0.8, 0.2, 1.0));

    std::unique_ptr<WaterBiome> water =
        std::make_unique<WaterBiome>(0.0, DEFAULT_WATER_LEVEL, 0.0, 1.0);

    std::unique_ptr<MountainBiome> mountain = std::make_unique<MountainBiome>(0.8, 1.0, 0.0, 1.0);

    std::unique_ptr<DesertBiome> desert =
        std::make_unique<DesertBiome>(DEFAULT_WATER_LEVEL, 0.8, 0.0, 0.4);

    generator.add_biome(std::move(grassland));
    generator.add_biome(std::move(water));
    generator.add_biome(std::move(mountain));
    generator.add_biome(std::move(desert));

    return generator;
}

void Game::start() {
    _main_window.create(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE, 32), "Regency");
    _main_window.setFramerateLimit(60);
    Mouse::set_window(_main_window);

    // load assets here - for now just Material colors (not textures...)
    // Material::load_colors();

    world::gen::StandardWorldGen g = get_default_gen();
    _world.generate(g);

    Game::tick();
}

void Game::tick() {
    sf::Event currentEvent;
    sf::Clock clock;

    sf::Font font;
    font.loadFromFile("../res/font/pixelmix.ttf");

    sf::Text mouse_coords_text;
    mouse_coords_text.setFont(font);
    // mouse_coords_text.setFillColor(sf::Color::White);
    // mouse_coords_text.setCharacterSize(10);
    mouse_coords_text.setPosition(10, 10);

    while (_main_window.isOpen()) {
        _main_window.clear(sf::Color(255, 0, 0));

        if (_main_window.pollEvent(currentEvent)) {
            if (currentEvent.type == sf::Event::Closed) {
                break;
            } else if (currentEvent.type == sf::Event::KeyPressed) {
                if (currentEvent.key.code == sf::Keyboard::G) {
                    std::cout << "regenerating..." << std::endl;
                    world::gen::StandardWorldGen g = get_default_gen();
                    _world.generate(g);
                } else if (currentEvent.key.code == sf::Keyboard::Z) {
                    _world.zoom();
                } else if (currentEvent.key.code == sf::Keyboard::B) {
                    std::shared_ptr<entity::HumanActor> actor =
                        std::make_shared<entity::HumanActor>(_world);
                    _world.spawn(actor);
                }
            }
        }

        _world.tick();
        _world.render(_main_window);

        sf::Vector2i mouse_coords = Mouse::get_mouse_position();

        std::ostringstream builder;
        builder << mouse_coords.x << ", " << mouse_coords.y;
        mouse_coords_text.setString(builder.str());

        // _main_window.draw(mouse_coords_text);

        _main_window.display();
    }
}

world::World& Game::get_world() {
    return _world;
}
}