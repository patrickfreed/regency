#ifndef REGENCY_WORLD_H
#define REGENCY_WORLD_H

#include <map>
#include <string>
#include <unordered_map>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <noise/noise.h>

#include "../Defines.h"
#include "../entity/Entity.h"
#include "Direction.h"
#include "Location.h"
#include "Tile.h"
#include "TileMap.h"
#include "gen/WorldGen.h"

namespace regency {

namespace entity {
class Actor;
}

namespace world {

#define ZOOM_INVALID -1
#define ZOOM_GLOBAL 1
#define ZOOM_LOCAL 2

// Maybe a class in future
// typedef std::vector<std::vector<std::unique_ptr<Tile>>> TileMap;

// Maybe a class in future
typedef struct mat_def {
    const Material* material;
    std::pair<double, double> e_range;
    std::pair<double, double> m_range;
} MaterialDefinition;

class World {
  private:
    std::string name;
    std::unordered_map<std::string, std::shared_ptr<entity::Entity>> _entities;
    TileMap tiles;

    int _zoom_level;

    noise::module::Perlin gen;

    sf::Vector2i pos;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::VertexArray tile_map;
    sf::Texture world_map;

  public:
    World(std::string name);

    World(const World& w) = delete;

    std::string& get_name();

    void generate(world::gen::WorldGen& generator);

    void render(sf::RenderWindow& window);

    bool move(entity::Entity& e, world::Direction d);

    void spawn(std::shared_ptr<entity::Actor> e);

    void tick();

    void zoom();

    void move_camera(int dx, int dy);

    Tile& get_hovered_tile();

    Tile& get_tile(const Location& l);

    Tile& get_tile(int x, int y);

    void move_map(int dx, int dy);

    int get_tile_size(int zoom_level = ZOOM_INVALID);

    Location get_focus();

    std::vector<std::shared_ptr<entity::Actor>> get_nearby_actors(Location l, int radius = 5);
};
} // namespace world
} // namespace entity

#endif // REGENCY_WORLD_H
