
#include "TileMap.h"

namespace regency {
namespace world {

TileMap::TileMap(std::uint64_t size) : _size(size) {
    _tiles.reserve(size * size);
}

std::unique_ptr<Tile>& TileMap::get(uint64_t x, uint64_t y) {
    return _tiles[x + y * _size];
}

void TileMap::set(uint64_t x, uint64_t y, std::unique_ptr<Tile>&& tile) {
    _tiles.insert(_tiles.begin() + x + y * _size, std::move(tile));
}

void TileMap::clear() {
    _tiles.clear();
}
}
}
