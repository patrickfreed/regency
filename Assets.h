
#ifndef REGENCY_ASSETS_H
#define REGENCY_ASSETS_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio.hpp>

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
    FACTIONS = 8,
    SETTLEMENTS = 9,
};

class Assets {
  public:
    static sf::Font font;

    static sf::Texture tree_texture;
    static sf::Texture tiles;
    static sf::Texture human_placeholder;
    static sf::Texture highlights;
    static sf::Texture alert;
    static sf::Texture bones;

    static sf::SoundBuffer punch1;
    static sf::SoundBuffer death;
    static sf::SoundBuffer victory;

    static bool render_names;

    static void load_assets();
    static std::string reserve_name(NameList type);

  private:
    static std::vector<std::vector<std::string>> _name_lists;
};
}
#endif // REGENCY_ASSETS_H
