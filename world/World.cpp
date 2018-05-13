#include "World.h"

#include <chrono>
#include <iostream>
#include <sstream>
#include <algorithm>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include "../Assets.h"
#include "../Mouse.h"
#include "../entity/Actor.h"
#include "../entity/HumanActor.h"
#include "Settlement.h"
#include <regency/world/gen/RandomGenerator.h>
#include <world/util/PathFinder.h>
#include <entity/action/Patrol.h>

#define NUM_FACTIONS 5
#define NUM_SETTLEMENTS 5
#define SETTLEMENT_SIZE 30
#define POPULATION_DIVISOR 90
#define SCREEN_SCALE static_cast<float>(WINDOW_SIZE) / WORLD_SIZE

namespace regency {
namespace world {

using std::min;
using std::max;

World::World(std::string name) : name(std::move(name)), tiles(WORLD_SIZE), _zoom_level(ZOOM_LOCAL),
                                 _tiles(Assets::tiles, get_tile_size()),
                                 _trees(Assets::tree_texture, get_tile_size()),
                                 _highlights(Assets::highlights, get_tile_size()){
    // local zoom level 0
    _world_map_texture.create(WORLD_SIZE, WORLD_SIZE);
    _world_map_sprite.setTexture(_world_map_texture);
    _world_map_sprite.setScale(SCREEN_SCALE, SCREEN_SCALE);
    _sprites.create(WINDOW_SIZE, WINDOW_SIZE);

    // global zoom level
    _pos.x = 0;
    _pos.y = 0;
}

void World::generate(gen::WorldGen& generator) {
    tiles.clear();

    // this->tiles.resize(WORLD_SIZE * DUP_FACTOR);
    // for (int x = 0; x < WORLD_SIZE * DUP_FACTOR; x++) {
    //    this->tiles[x].reserve(WORLD_SIZE * DUP_FACTOR);
    //}

    std::cout << "starting world generation..." << std::endl;

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    generator.generate(tiles, _world_map_texture);

    generate_factions();
    generate_settlements();

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    std::cout << "generation completed. elapsed time: " << elapsed_seconds.count() << " second(s)"
              << std::endl;
}

std::string& World::get_name() {
    return name;
}

void World::render(sf::RenderWindow& window) {
    int tile_size = get_tile_size();

    if (_zoom_level == ZOOM_LOCAL) {
        Location focus = get_focus();
        _sprites.clear(sf::Color::Transparent);
        for (int x = 0; x < min(WINDOW_SIZE / tile_size, WORLD_SIZE); x++) {
            for (int y = 0; y < min(WINDOW_SIZE / tile_size, WORLD_SIZE); y++) {
                int xx = x + _pos.x / tile_size;
                int yy = (y + _pos.y / tile_size);

                Tile &t = tiles.get(xx, yy);
                bool is_focus = xx == focus.get_x() && yy == focus.get_y();

                int tile_number = is_focus ? 5 : t.get_material()->get_tile_number();
                // tile_number = t.get_actor() ? 15 : tile_number;

                _tiles.set_id(x, y, tile_number);

                if (t.get_actor()) {
                    entity::Actor &actor = *t.get_actor();
                    actor.render(_sprites, x * tile_size, y * tile_size);
                }

                if (t.get_tree().get_type() == TreeType::EVERGREEN) {
                    _trees.set_id(x, y, 1);
                } else if (t.get_tree().get_type() == TreeType::ELM) {
                    _trees.set_id(x, y, 2);
                } else {
                    _trees.set_id(x, y, 0);
                }

                _highlights.set_id(x, y, static_cast<int>(t.get_highlight()));

                if (t.get_highlight() == Highlight::TEMPORARY) {
                    t.set_highlight(Highlight::NONE);
                }

            }
        }

        _tiles.render(window);
        _trees.render(window);
        _highlights.render(window);

        _sprites.display();
        sf::Sprite entities{_sprites.getTexture()};
        window.draw(entities);

        if (Mouse::in_window()) {
            Tile& hover = get_hovered_tile();
            sf::Text region_name_text;
            region_name_text.setFont(Assets::font);
            region_name_text.setString(hover.get_region_name());
            region_name_text.setPosition(WINDOW_SIZE / 2 - (hover.get_region_name().length() * 10), 20);
            region_name_text.setOutlineColor(sf::Color::Black);
            region_name_text.setOutlineThickness(2.5);
            window.draw(region_name_text);

            region_name_text.setPosition(WINDOW_SIZE / 2 - (hover.get_subregion_name().length() * 10), 55);
            region_name_text.setCharacterSize(25);
            region_name_text.setString(hover.get_subregion_name());
            window.draw(region_name_text);
        }
    } else {
        // this->_world_map_sprite.scale(1.0f, 1.0f);
        // _world_map_sprite.setPosition(static_cast<float>(-_pos.x),
        // static_cast<float>(-_pos.y));
        _world_map_sprite.setTextureRect(sf::Rect<int>(_pos.x, _pos.y, WINDOW_SIZE, WINDOW_SIZE));
        window.draw(_world_map_sprite);

        for (Settlement& s : _settlements) {
            sf::Text settlment_label;

            settlment_label.setPosition(s.get_bounds().get_min_x() * SCREEN_SCALE, s.get_bounds().get_min_y() * SCREEN_SCALE);
            settlment_label.setFont(Assets::font);
            settlment_label.setFillColor(sf::Color::White);

            if (s.get_faction().friendly()) {
                settlment_label.setOutlineColor(sf::Color::Black);
            } else {
                settlment_label.setOutlineColor(sf::Color::Red);
            }
            settlment_label.setOutlineThickness(1.0f);
            settlment_label.setCharacterSize(20);
            settlment_label.setString(s.get_name());

            window.draw(settlment_label);

        }
    }

    /*
    sf::Text pos_text;
    pos_text.setFont(Assets::font);
    pos_text.setString(std::to_string(_pos.x / get_tile_size()) + ", " +
                       std::to_string(_pos.y / get_tile_size()));

    pos_text.setOutlineColor(sf::Color::Black);
    pos_text.setOutlineThickness(2.5);
    window.draw(pos_text);
     */
}

bool World::move(entity::Entity& e, world::Direction d) {
    Location& src = e.get_location();
    Location dst = src.get_adjacent(d);

    if (!dst.is_valid()) {
        std::cout << "bad dst " << dst.str() << std::endl;
        return false;
    }

    Tile& a = get_tile(src);
    Tile& aa = get_tile(dst);

    if (a.get_actor() && !(aa.get_actor())) {
        // std::cout << "moved from " << src.str() << " => " << dst.str() << std::endl;

        aa.set_actor(a.get_actor());
        a.set_actor({});
        src._x = dst.get_x();
        src._y = dst.get_y();
        return true;
    }
    return false;
}

void World::update() {
    if (_zoom_level != ZOOM_LOCAL) {
        return;
    }

    // Camera tick
    int xdiff = 0;
    int ydiff = 0;

    int dist = 10;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        ydiff = -dist;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        ydiff = dist;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        xdiff = -dist;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        xdiff = dist;
    }

    int nx = _pos.x + xdiff;
    int ny = _pos.y + ydiff;

    _pos.x = min(max(0, nx), (WORLD_SIZE - VIEW_DISTANCE) * get_tile_size());
    _pos.y = min(max(0, ny), (WORLD_SIZE - VIEW_DISTANCE) * get_tile_size());
}

void World::tick() {
    // Game logic tick
    Location focus = get_focus();

    auto nearby_actors = get_nearby_actors(focus, 51);
    for (auto&& actor : nearby_actors) {
        actor->tick();
    }
}

void World::move_map(int dx, int dy) {
    sf::IntRect rect = this->_world_map_sprite.getTextureRect();

    int left = rect.left + dx;
    int top = rect.top + dy;

    if (left >= 0 && left < WORLD_SIZE - WINDOW_SIZE && top >= 0 && top < WORLD_SIZE - WINDOW_SIZE)
        this->_world_map_sprite.setTextureRect(sf::IntRect(left, top, WINDOW_SIZE, WINDOW_SIZE));
}

void World::move_camera(int dx, int dy) {
    if (_pos.x + dx + RENDER_SIZE * get_tile_size() < WORLD_SIZE * get_tile_size() * DUP_FACTOR) {
        _pos.x += dx;
    }

    if (_pos.y + dy + RENDER_SIZE * get_tile_size() < WORLD_SIZE * get_tile_size() * DUP_FACTOR) {
        _pos.y += dy;
    }
}

void World::zoom() {
    if (_zoom_level == ZOOM_GLOBAL) {
        _zoom_level = ZOOM_LOCAL;

        sf::Vector2i mouse_pos = Mouse::get_mouse_position();

        int left = (mouse_pos.x + _pos.x) / 100 * 100 * get_tile_size();
        int top = (mouse_pos.y + _pos.y) / 100 * 100 * get_tile_size();

        // int left = _pos.x + max(0, mouse_pos.x - mouse_pos.x % 100) *
        // get_tile_size() *
        // DUP_FACTOR;
        // int top = _pos.y + max(0, mouse_pos.y - mouse_pos.y % 100) *
        // get_tile_size() * DUP_FACTOR;

        _pos.x = left;
        _pos.y = top;
    } else if (_zoom_level == ZOOM_LOCAL) {
        _pos.x = 0;
        _pos.y = 0;

        //_pos.x /= get_tile_size();
        //_pos.y /= get_tile_size();

        //_pos.x /= 2;
        //_pos.y /= 2;

        _zoom_level = ZOOM_GLOBAL;
    }
}

Tile& World::get_hovered_tile() {
    sf::Vector2i mouse_pos = Mouse::get_mouse_position();

    if (mouse_pos.x < 0 || mouse_pos.x > WINDOW_SIZE || mouse_pos.y < 0 ||
        mouse_pos.y > WINDOW_SIZE) {
        throw std::runtime_error("Mouse position out of frame.");
    }

    int xx = _pos.x / get_tile_size() + mouse_pos.x / get_tile_size();
    int yy = _pos.y / get_tile_size() + mouse_pos.y / get_tile_size();

    return tiles.get(xx, yy);
}

Tile& World::get_tile(int x, int y) {
    return tiles.get(x, y);
}

Tile& World::get_tile(const Location& l) {
    if (!l.is_valid()) {
        throw std::runtime_error("invalid location in get_tile: " + l.str());
    }

    return get_tile(l.get_x(), l.get_y());
}

int World::get_tile_size(int zoom_level) {
    if (zoom_level == ZOOM_LOCAL) {
        return 10;
    } else if (zoom_level == ZOOM_GLOBAL) {
        return 1;
    } else {
        return get_tile_size(_zoom_level);
    }
}

bool World::spawn(std::shared_ptr<entity::Actor> e, Location location) {
    if (!location.is_valid()) {
        return false;
    }

    Tile& tile = get_tile(location);

    if (!tile.get_actor()) {
        e->_location._x = location.get_x();
        e->_location._y = location.get_y();
        e->_id = ++_latest_entity_id;
        tile.set_actor(std::move(e));

        return true;
    }

    return false;
}

Location World::get_focus() {
    return Location(_pos.x / get_tile_size() + WINDOW_SIZE / 2 / get_tile_size(),
                    _pos.y / get_tile_size() + WINDOW_SIZE / 2 / get_tile_size());
}

std::vector<std::shared_ptr<entity::Actor>> World::get_nearby_actors(Location l, int radius) {
    std::vector<std::shared_ptr<entity::Actor>> actors;

    int xs = max(0, l.get_x() - radius);
    int ys = max(0, l.get_y() - radius);

    int xe = min(WORLD_SIZE, l.get_x() + radius);
    int ye = min(WORLD_SIZE, l.get_y() + radius);

    for (int x = xs; x < xe; ++x) {
        for (int y = ys; y < ye; ++y) {
            Tile& tile = get_tile(x, y);

            if (tile.get_actor()) {
                actors.push_back(tile.get_actor());
            }
        }
    }

    return actors;
}

bool World::is_traversable(const Location& loc) {
    Tile& tile = get_tile(loc);

    return tile.get_material()->is_solid() && tile.get_elevation() < 0.8
           && tile.get_tree().get_type() == TreeType::NONE && !tile.get_actor();
}

sf::Vector2i World::get_vector_from_location(const Location& loc) {
    int tile_size = get_tile_size();

    return {loc.get_x() * tile_size - _pos.x, loc.get_y() * tile_size - _pos.y};
}

std::optional<Location> World::get_traversable_neighbor(const Location& loc) {
    for (auto d : {Direction::NORTH, Direction::SOUTH, Direction::EAST, Direction::WEST}) {
        Location adj = loc.get_adjacent(d);
        if (is_traversable(adj)) {
            return adj;
        }
    }

    return {};
}

void World::generate_factions() {
    for (int x = 0; x < NUM_FACTIONS; ++x) {
        entity::Faction f(Assets::reserve_name(NameList::FACTIONS));
        _factions.push_back(f);
    }
}

void World::generate_settlements() {
    int towns = 0;
    gen::RandomGenerator rnd_x(0, WORLD_SIZE - SETTLEMENT_SIZE);
    gen::RandomGenerator rnd_y(0, WORLD_SIZE - SETTLEMENT_SIZE);

    while (towns < NUM_SETTLEMENTS) {
        int num_traversable = 0;

        Location origin(rnd_x.next_int(), rnd_y.next_int());
        Location opposite(origin.get_x() + SETTLEMENT_SIZE, origin.get_y() + SETTLEMENT_SIZE);

        Region r(origin, opposite);

        bool overlap = false;
        for (Settlement& s : _settlements) {
            if (r.intersects(s.get_bounds())) {
                overlap = true;
                break;
            }
        }

        if (overlap) {
            continue;
        }

        std::vector<Location> traversables;
        std::vector<Location> west_border;
        std::vector<Location> east_border;
        std::vector<Location> south_border;
        std::vector<Location> north_border;
        traversables.reserve(1000);

        for (Tile& t : r) {
            Location loc = t.get_location();

            if (is_traversable(loc)) {
                num_traversable++;
                traversables.push_back(t.get_location());

                if (loc.get_x() == r.get_min_x()) {
                    west_border.push_back(t.get_location());
                } else if (loc.get_x() == r.get_max_x()) {
                    east_border.push_back(t.get_location());
                } else if (loc.get_y() == r.get_min_y()) {
                    north_border.push_back(t.get_location());
                } else if (loc.get_y() == r.get_max_y()) {
                    south_border.push_back(t.get_location());
                }
            }
        }

        std::vector<std::vector<Location>*> borders = {&south_border, &east_border, &west_border, &north_border};

        if (num_traversable > r.size() / 2 && !north_border.empty() && !south_border.empty() && !east_border.empty() && !west_border.empty()) {
            Settlement settlement(Assets::reserve_name(NameList::SETTLEMENTS), r, _factions[towns]);
            int population = num_traversable / POPULATION_DIVISOR;

            std::shuffle(std::begin(traversables), std::end(traversables), gen::RandomGenerator::get_generator());

            std::shuffle(std::begin(north_border), std::end(north_border), gen::RandomGenerator::get_generator());
            std::shuffle(std::begin(south_border), std::end(south_border), gen::RandomGenerator::get_generator());
            std::shuffle(std::begin(west_border), std::end(west_border), gen::RandomGenerator::get_generator());
            std::shuffle(std::begin(east_border), std::end(east_border), gen::RandomGenerator::get_generator());

            auto north = north_border.back();
            auto east = east_border.back();
            auto west = west_border.back();
            auto south = south_border.back();

            const Material *road_material = &Material::SILTY_SOIL;

            PathFinder ne{north, east};
            PathFinder nw{north, west};
            PathFinder se{south, east};
            PathFinder sw{south, west};
            // PathFinder ew{east, west};

            auto paths = {&ne, &nw, &se, &sw};
            auto directions = {Direction::NORTH, Direction::SOUTH, Direction::EAST, Direction::WEST};

            // Main roads
            for (auto pff : paths) {
                if (pff->find_path()) {
                    pff->get_path();

                    while (pff->has_next()) {
                        Location next = pff->next();
                        Tile& t = get_tile(next);
                        t.set_material(road_material);

                        for (Direction d : directions) {
                            auto n_loc = next.get_adjacent(d);

                            if (n_loc.is_valid()) {
                                Tile& neighbor = get_tile(next.get_adjacent(d));
                                neighbor.set_material(road_material);
                                neighbor.set_tree(Tree());
                            }
                        }
                    }
                }
            }

            std::vector<Location> houses;

            // Spawn people, build houses
            while(population > 0 && !traversables.empty()) {
                bool spawned = false;
                auto resident = std::make_shared<entity::HumanActor>(*this, &_factions[towns]);
                _factions[towns].increase_population();

                while (!spawned && !traversables.empty()) {
                    Location l = traversables.back();
                    traversables.pop_back();

                    Tile& t = get_tile(l);

                    if (t.get_material() == road_material) {
                        continue;
                    }

                    spawn(resident, l);
                    resident->assign_task(std::make_unique<entity::action::Patrol>(*resident, r));
                    spawned = true;
                    population--;
                }

                bool house = false;
                while (!house && !traversables.empty()) {
                    Location l = traversables.back();
                    traversables.pop_back();

                    Tile&t = get_tile(l);

                    if (t.get_material() == road_material) {
                        continue;
                    }

                    // t.set_material(&Material::PLACEHOLDER);
                    t.set_tree(Tree(TreeType::ELM, 10));
                    houses.push_back(l);
                    house = true;
                }
            }

            // std::cout << "getting path copies" << std::endl;
            auto sw_path = sw.get_path_copy();
            auto nw_path = nw.get_path_copy();
            auto ne_path = ne.get_path_copy();
            auto se_path = se.get_path_copy();

            for (Location l : houses) {
                bool is_south = l.get_y() > (r.get_min_y() + r.get_max_y()) / 2;
                std::vector<Location> *path = nullptr;

                // std::cout << "getting quadrant" << std::endl;
                if (l.get_x() > (r.get_max_x() + r.get_min_x()) / 2) {
                    if (is_south) {
                        path = &se_path;
                    } else {
                        path = &ne_path;
                    }
                } else {
                    if (is_south) {
                        path = &sw_path;
                    } else {
                        path = &nw_path;
                    }
                }

                // std::cout << "shuffling" << std::endl;
                std::shuffle(path->begin(), path->end(), gen::RandomGenerator::get_generator());

                // std::cout << "getting end" << std::endl;
                Location target = path->back();

                // std::cout << "constructing pathfinder" << std::endl;
                PathFinder connector(l, target);
                // std::cout << "finding path" << std::endl;
                if (connector.find_path()) {
                    // std::cout << "found path, getting" << std::endl;

                    connector.get_path();

                    // std::cout << "got poth, setting material" << std::endl;
                    while (connector.has_next()) {
                        Location next = connector.next();
                        Tile& t = get_tile(next);
                        t.set_material(road_material);
                        t.set_tree(Tree());
                    }
                }

            }

            auto *map_update = new sf::Uint8[r.size() * 4];
            for (int x = r.get_min_x(); x <= r.get_max_x(); x++) {
                for (int y = r.get_min_y(); y <= r.get_max_y(); y++) {
                    int xx = x - r.get_min_x();
                    int yy = y - r.get_min_y();
                    const sf::Color *color;
                    if (x % 100 == 0 || y % 100 == 0) {
                        color = &sf::Color::Red;
                    } else {
                        color = &get_tile(x, y).get_material()->get_color();
                    }
                    map_update[(xx + yy * r.get_width()) * 4 + 0] = color->r;
                    map_update[(xx + yy * r.get_width()) * 4 + 1] = color->g;
                    map_update[(xx + yy * r.get_width()) * 4 + 2] = color->b;
                    map_update[(xx + yy * r.get_width()) * 4 + 3] = color->a;
                }
            }
            _world_map_texture.update(map_update, r.get_width(), r.get_height(), r.get_min_x(), r.get_min_y());
            delete [] map_update;

            _settlements.push_back(std::move(settlement));
            ++towns;
        }
    }
}

std::vector<entity::Faction>& World::get_factions() {
    return _factions;
}

} // namespace world
} // namespace regency