#ifndef REGENCY_WORLD_H
#define REGENCY_WORLD_H

#include <map>
#include <string>
#include <unordered_map>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include <regency/Defines.h>
#include <regency/entity/Entity.h>
#include <regency/world/Direction.h>
#include <regency/world/Location.h>
#include <regency/world/Tile.h>
#include <regency/world/util/TileMap.h>
#include <regency/world/gen/WorldGen.h>
#include <regency/world/util/RenderLayer.h>

namespace regency {

namespace entity {
class Actor;
}

namespace world {

#define ZOOM_INVALID -1
#define ZOOM_GLOBAL 1
#define ZOOM_LOCAL 2

// Maybe a class in future
typedef struct mat_def {
    const Material* material;
    std::pair<double, double> e_range;
    std::pair<double, double> m_range;
} MaterialDefinition;

class World {
  public:
    explicit World(std::string name);

    World(const World& w) = delete;

    std::string& get_name();

    void generate(world::gen::WorldGen& generator);

    void render(sf::RenderWindow& window);

    bool move(entity::Entity& e, world::Direction d);

    bool spawn(std::shared_ptr<entity::Actor> e, Location location);

    // Game world update
    void tick();

    // UI, camera, menus, etc. update
    void update();

    void zoom();

    void move_camera(int dx, int dy);

    Tile& get_hovered_tile();

    Tile& get_tile(const Location& l);

    Tile& get_tile(int x, int y);

    void move_map(int dx, int dy);

    int get_tile_size(int zoom_level = ZOOM_INVALID);

    Location get_focus();

    std::vector<std::shared_ptr<entity::Actor>> get_nearby_actors(Location l, int radius = 5);

    bool is_traversable(const Location& loc);

    std::optional<world::Location> get_traversable_neighbor(const Location& loc);

    sf::Vector2i get_vector_from_location(const Location& loc);

  private:
    std::string name;

    std::unordered_map<std::string, std::shared_ptr<entity::Entity>> _entities;

    TileMap tiles;

    int _zoom_level;

    sf::RenderTexture _sprites;

    RenderLayer _tiles;
    RenderLayer _trees;
    RenderLayer _highlights;

    sf::Vector2i _pos;
    sf::Sprite _world_map_sprite;
    sf::Texture _world_map_texture;

    int _latest_entity_id;
};
} // namespace world
} // namespace entity

#endif // REGENCY_WORLD_H
