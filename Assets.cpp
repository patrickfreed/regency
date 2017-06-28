
#include "Assets.h"

sf::Font Assets::font;

enum NameList {
    ISLANDS,
    CONTINENTS
};

const auto names = {
        "islands.txt",
        "continents.txt"
};

std::vector<std::string> get_names(NameList l) {
    return std::vector<std::string>();
}