#include "World.h"

#include <chrono>
#include <iostream>
#include <sstream>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include "../Assets.h"
#include "../Mouse.h"
#include "../entity/Actor.h"
#include "../entity/HumanActor.h"

namespace regency {
namespace world {

using std::min;
using std::max;

World::World(std::string name) : name(std::move(name)), tiles(WORLD_SIZE), _zoom_level(ZOOM_LOCAL),
                                 _tiles(Assets::tiles, get_tile_size()),
                                 _trees(Assets::tree_texture, get_tile_size()),
                                 _highlights(Assets::highlights, get_tile_size()){
    // local zoom level 0
    _world_map_texture.create(WINDOW_SIZE, WINDOW_SIZE);
    _world_map_sprite.setTexture(_world_map_texture);
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

                if (t.get_tree().get_type() != TreeType::NONE) {
                    _trees.set_id(x, y, 1);
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

void World::tick() {
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
        _pos.x /= get_tile_size();
        _pos.y /= get_tile_size();

        _pos.x /= 2;
        _pos.y /= 2;

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

sf::Vector2f World::get_vector_from_location(const Location &loc) {

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

} // namespace world
} // namespace regency