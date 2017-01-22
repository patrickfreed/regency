#ifndef TEST_PROJECT_WORLD_H
#define TEST_PROJECT_WORLD_H

#include <string>
#include <map>
#include <SFML/Graphics/RenderWindow.hpp>
#include <noise/noise.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Tile.h"

using namespace std;

class World {
private:
    string name;
    vector<vector<Tile *>> tiles;

    int zoom_level;
    int tile_size; // tile_size = 10^zoom_level

    noise::module::Perlin gen;

    sf::Vector2i pos;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::VertexArray tile_map;
    sf::Texture world_map;

    double noise(double nx, double ny);
public:
    enum Direction {NORTH, SOUTH, EAST, WEST};

    World(string name);
    string& get_name();
    void generate();

    void render(sf::RenderWindow& window);
    bool move(int x, int y, Direction d);
    void tick();

    void zoom(bool in);
    void move_camera(int dx, int dy);
    Tile *get_hovered_tile();
};


#endif //TEST_PROJECT_WORLD_H
