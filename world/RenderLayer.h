//
// Created by Patrick on 4/26/2018.
//

#ifndef REGENCY_RENDERLAYER_H
#define REGENCY_RENDERLAYER_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace regency{
namespace world{

class RenderLayer {
  private:
    const sf::Texture& _texture;
    sf::VertexArray _vertex_array;
    int _tile_size;

  public:
    RenderLayer(const sf::Texture &texture, int tile_size);

    void set_id(int x, int y, int id);

    void render(sf::RenderWindow& window);
};

}
}

#endif //REGENCY_RENDERLAYER_H
