//

#ifndef TEST_PROJECT_MATERIAL_H
#define TEST_PROJECT_MATERIAL_H

#include <string>
#include <SFML/Graphics/Color.hpp>
#include <map>
#include <SFML/Graphics/Texture.hpp>

using namespace std;

class Material {
private:
    Material(std::string name, int id, sf::Color color);
    std::string name;
    sf::Color color;
    sf::Texture texture;
    int tile_number;
public:
    std::string get_name();
    const sf::Color& get_color() const;
    sf::Texture& get_texture();
    int get_tile_number() const;

    // Some types
    const static Material ROCK;
    const static Material ROCKY_DIRT;
    const static Material DIRT;
    const static Material SAND;
    const static Material SALT_WATER;
    const static Material MUDDY_DIRT;
    const static Material SNOW;

    static const Material PLACEHOLDER;
    static const Material NORTHERN_TURF;
    static const Material BLUEGRASS;
    static const Material FESCUE;
    static const Material RYEGRASS;
    static const Material CLAY_SOIL;
    static const Material SANDY_SOIL;
    static const Material SILTY_SOIL;
    static const Material PEATY_SOIL;
    static const Material LOAMY_SOIL;
    static const Material CHALKY_SOIL;
};


#endif //TEST_PROJECT_MATERIAL_H
