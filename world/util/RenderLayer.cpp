#include "RenderLayer.h"
#include "../../Defines.h"

namespace regency {
namespace world {

RenderLayer::RenderLayer(const sf::Texture &texture, int tile_size) : _texture(texture),
                                                                      _tile_size(tile_size) {
    _vertex_array.setPrimitiveType(sf::Quads);
    _vertex_array.resize(RENDER_SIZE * RENDER_SIZE * 4);
    for (int x = 0; x < RENDER_SIZE; ++x) {
        for (int y = 0; y < RENDER_SIZE; ++y) {
            sf::Vertex* quad = &(_vertex_array[(x + y * RENDER_SIZE) * 4]);
            quad[0].position = sf::Vector2f(x * _tile_size, y * _tile_size);
            quad[1].position = sf::Vector2f((x + 1) * _tile_size, y * _tile_size);
            quad[2].position = sf::Vector2f((x + 1) * _tile_size, (y + 1) * _tile_size);
            quad[3].position = sf::Vector2f(x * _tile_size, (y + 1) * _tile_size);
        }
    }
}

void RenderLayer::set_id(int x, int y, int tile_number) {
    int tu = tile_number % (_texture.getSize().x / _tile_size);
    int tv = tile_number / (_texture.getSize().x / _tile_size);

    sf::Vertex* q = &(_vertex_array[(x + y * RENDER_SIZE) * 4]);
    q[0].texCoords = sf::Vector2f(tu * _tile_size, tv * _tile_size);
    q[1].texCoords = sf::Vector2f((tu + 1) * _tile_size, tv * _tile_size);
    q[2].texCoords = sf::Vector2f((tu + 1) * _tile_size, (tv + 1) * _tile_size);
    q[3].texCoords = sf::Vector2f(tu * _tile_size, (tv + 1) * _tile_size);
}

void RenderLayer::render(sf::RenderWindow& window) {
    window.draw(_vertex_array, &_texture);
}

}
}