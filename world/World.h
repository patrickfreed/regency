#ifndef TEST_PROJECT_WORLD_H
#define TEST_PROJECT_WORLD_H

#include <string>
#include <map>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <noise/noise.h>

#include "Tile.h"
#include "../Defines.h"
#include "gen/WorldGen.h"

#define ZOOM_INVALID -1
#define ZOOM_GLOBAL 1
#define ZOOM_LOCAL 2

class World {
private:
    std::string name;
    TileMap tiles;

    int _zoom_level;

    noise::module::Perlin gen;

    sf::Vector2i pos;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::VertexArray tile_map;
    sf::Texture world_map;

    double noise(double nx, double ny);
public:
    enum Direction {NORTH, SOUTH, EAST, WEST};

    World(std::string name);

    World(const World& w) = delete;

    std::string& get_name();

    void generate(WorldGen& generator);

    void render(sf::RenderWindow& window);

    bool move(int x, int y, Direction d);

    void tick();

    void zoom();

    void move_camera(int dx, int dy);

    const std::unique_ptr<Tile>& get_hovered_tile();

    void move_map(int dx, int dy);

    int get_tile_size(int zoom_level = ZOOM_INVALID);
};


#endif //TEST_PROJECT_WORLD_H
