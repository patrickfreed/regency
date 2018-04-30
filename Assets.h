
#ifndef REGENCY_ASSETS_H
#define REGENCY_ASSETS_H

#include <SFML/Graphics/Font.hpp>

namespace regency {

enum class NameList {
    NONE = -1,
    ISLANDS = 0,
    CONTINENTS = 1,
    PEOPLE = 2,
    OCEANS = 3,
    LAKES = 4,
    DESERTS = 5,
    GRASSLANDS = 6,
    MOUNTAINS = 7,
};

class Assets {
  public:
    static sf::Font font;
    static sf::Texture tree_texture;
    static sf::Texture tiles;

    static void load_assets();
    static std::string reserve_name(NameList type);

  private:
    static std::vector<std::vector<std::string>> _name_lists;
};
}
#endif // REGENCY_ASSETS_H
