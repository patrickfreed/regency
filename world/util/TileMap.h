
#ifndef REGENCY_TILEMAP_H
#define REGENCY_TILEMAP_H

#include "../Tile.h"

namespace regency {
namespace world {

class TileMap {
  public:
    TileMap(std::uint64_t size);

    Tile& get(uint64_t x, uint64_t y);

    void set(uint64_t x, uint64_t y, std::unique_ptr<Tile>&& tile);

    void clear();

  private:
    std::uint64_t _size;
    std::vector<std::unique_ptr<world::Tile>> _tiles;
};
}
}

#endif // REGENCY_TILEMAP_H
