#include <regency/Game.h>

#include <iostream>
#include <sstream>
#include <thread>

#include <regency/Mouse.h>
#include <regency/entity/action/Move.h>
#include <regency/entity/action/Harvest.h>
#include <regency/entity/HumanActor.h>
#include <regency/world/Region.h>
#include <regency/world/gen/StandardWorldGen.h>
#include <regency/world/gen/biome/DesertBiome.h>
#include <regency/world/gen/biome/GrasslandBiome.h>
#include <regency/world/gen/biome/MountainBiome.h>
#include <regency/world/gen/biome/WaterBiome.h>
#include <regency/entity/action/Follow.h>
#include <regency/entity/action/Patrol.h>

namespace regency {

Game::Game() : _world("world_name_placeholder"), _action(Selector::NONE) {}

world::gen::StandardWorldGen get_default_gen() {
    using namespace world::gen;

    StandardWorldGen generator{"basic", DEFAULT_WATER_LEVEL};

    auto grassland = std::make_unique<GrasslandBiome>(DEFAULT_WATER_LEVEL, 0.8, 0.2, 1.0);
    auto water = std::make_unique<WaterBiome>(0.0, DEFAULT_WATER_LEVEL, 0.0, 1.0);
    auto mountain = std::make_unique<MountainBiome>(0.8, 1.0, 0.0, 1.0);
    auto desert = std::make_unique<DesertBiome>(DEFAULT_WATER_LEVEL, 0.8, 0.0, 0.4);

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

    regency::Assets::load_assets();

    world::gen::StandardWorldGen g = get_default_gen();
    _world.generate(g);

    Game::tick();
}



void Game::tick() {
    sf::Event currentEvent;
    sf::Clock clock;

    const world::Location *mark = nullptr;

    while (_main_window.isOpen()) {
        _main_window.clear(sf::Color(255, 0, 0));

        if (_main_window.pollEvent(currentEvent)) {
            switch (currentEvent.type) {
                case sf::Event::Closed:
                    return;
                case sf::Event::KeyPressed:
                    switch (currentEvent.key.code) {
                        case sf::Keyboard::G: {
                            std::cout << "regenerating..." << std::endl;
                            world::gen::StandardWorldGen g = get_default_gen();
                            _world.generate(g);
                            break;
                        }
                        case sf::Keyboard::Z:
                            _world.zoom();
                            break;
                        case sf::Keyboard::B: {
                            world::Location loc;

                            if (Mouse::in_window()) {
                                world::Tile& t = _world.get_hovered_tile();
                                loc = t.get_location();
                            }

                            auto actor = std::make_shared<entity::HumanActor>(_world);
                            _world.spawn(actor, loc);
                            break;
                        }
                        case sf::Keyboard::F: {
                            if (Mouse::in_window() && _focus) {
                                world::Tile& t = _world.get_hovered_tile();
                                auto target = t.get_actor();

                                if (target) {
                                    auto follow_task = std::make_unique<entity::action::Follow>(*_focus, target);
                                    auto& humanactor = dynamic_cast<entity::HumanActor&>(*_focus);
                                    humanactor.assign_task(std::move(follow_task));
                                }
                            }

                            break;
                        }
                        case sf::Keyboard::P: {
                            _action = Selector::PATROL;
                            break;
                        }
                        case sf::Keyboard::H: {
                            _action = Selector::HARVEST;
                            break;
                        }
                        default:
                            break;
                    }
                    break;
                case sf::Event::MouseButtonPressed:
                    switch (currentEvent.mouseButton.button) {
                        case sf::Mouse::Left:
                            if (Mouse::in_window()) {
                                world::Tile& tile = _world.get_hovered_tile();
                                auto tile_actor = tile.get_actor();
                                if (tile_actor) {
                                    focus_entity(tile_actor);
                                } else if (_focus) {
                                    mark = &tile.get_location();
                                }
                            }
                            break;
                        case sf::Mouse::Right:
                            if (_focus && Mouse::in_window()) {
                                world::Tile& tile = _world.get_hovered_tile();

                                auto& actor = dynamic_cast<entity::HumanActor&>(*_focus);

                                auto move = std::make_unique<entity::action::Move>(actor, tile.get_location());
                                actor.assign_task(std::move(move), true);
                            }
                            break;
                        default:
                            break;
                    }
                    break;
                case sf::Event::MouseButtonReleased: {
                    if (!Mouse::in_window()) {
                        break;
                    }

                    if (mark) {
                        auto &actor = dynamic_cast<entity::HumanActor &>(*_focus);

                        world::Tile &hover = _world.get_hovered_tile();
                        const world::Location &other = hover.get_location();

                        world::Region region(*mark, other);

                        if (_action == Selector::HARVEST) {
                            actor.assign_task(std::make_unique<entity::action::Harvest>(actor, region), false);
                        } else if (_action == Selector::PATROL) {
                            actor.assign_task(std::make_unique<entity::action::Patrol>(actor, region));
                        }

                        mark = nullptr;
                    }
                    break;
                }
                default:
                    break;
            }
        }

        if (clock.getElapsedTime().asMilliseconds() >= MS_PER_TICK) {
            _world.tick();
            clock.restart();
        }
        _world.render(_main_window);

        if (mark) {
            if (Mouse::in_window()) {
                world::Tile& hover = _world.get_hovered_tile();
                const world::Location& other = hover.get_location();

                world::Region region(*mark, other);
                for (world::Tile& t : region) {
                    t.set_highlight(world::Highlight::TEMPORARY);
                }
            }
        }

        _main_window.display();
    }
}

world::World& Game::get_world() {
    return _world;
}

sf::Time Game::get_time() {
    return _clock.getElapsedTime();
}

Game& Game::get_instance() {
    static Game instance;

    return instance;
}

void Game::focus_entity(std::shared_ptr<entity::Actor> e) {
    // TODO: not necessarily human actor

    if (_focus) {
        auto& actor = dynamic_cast<entity::HumanActor&>(*_focus);
        actor.set_name_visible(false);

        auto work_area = actor.get_work_area();

        if (work_area) {
            for (world::Tile& t : *work_area) {
                t.set_highlight(world::Highlight::NONE);
            }
        }
    }

    _focus = std::move(e);

    auto& actor = dynamic_cast<entity::HumanActor&>(*_focus);
    actor.set_name_visible(true);

    auto work_area = actor.get_work_area();

    if (work_area) {
        for (world::Tile& t : *work_area) {
            t.set_highlight(world::Highlight::PERMANENT);
        }
    }
}
}