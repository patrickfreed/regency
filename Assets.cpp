
#include <fstream>
#include <iostream>

#include "Assets.h"
#include "world/gen/RandomGenerator.h"

namespace regency {

sf::Font Assets::font;
sf::Texture Assets::tree_texture;
sf::Texture Assets::tiles;
sf::Texture Assets::highlights;
sf::Texture Assets::human_placeholder;
sf::Texture Assets::alert;
sf::Texture Assets::bones;

sf::SoundBuffer Assets::punch1;
sf::SoundBuffer Assets::death;
sf::SoundBuffer Assets::victory;

std::vector<std::vector<std::string>> Assets::_name_lists{};

bool Assets::render_names{true};

const std::vector<std::string> names = {
        "islands.txt",
        "continents.txt",
        "people.txt",
        "oceans.txt",
        "lakes.txt",
        "deserts.txt",
        "grasslands.txt",
        "mountains.txt",
        "factions.txt",
        "settlements.txt"
};

void read_to_vector(std::string filename, std::vector<std::string>& out) {
    std::ifstream file(filename);

    if (file.bad() || file.eof()) {
        std::cout << "can't open " << filename << std::endl;
    }

    for (std::string line; std::getline(file, line);) {
        out.push_back(line);
    }
}

void Assets::load_assets() {
    std::cout << "Loading assets...";

    font.loadFromFile("../res/font/pixelmix.ttf");
    tree_texture.loadFromFile("../res/tree.png");
    tiles.loadFromFile("../res/tileset.png");
    human_placeholder.loadFromFile("../res/human.png");
    highlights.loadFromFile("../res/highlights.png");
    alert.loadFromFile("../res/alert.png");
    bones.loadFromFile("../res/skeleton.png");

    punch1.loadFromFile("../res/sound/punch1.ogg");
    death.loadFromFile("../res/sound/death.wav");
    victory.loadFromFile("../res/sound/victory.wav");

    for (int x = 0; x < names.size(); x++) {
        std::vector<std::string> list;
        read_to_vector("../res/names/" + names[x], list);
        std::shuffle(list.begin(), list.end(), world::gen::RandomGenerator::get_generator());
        _name_lists.push_back(list);
    }

    std::cout << "Done." << std::endl;
}

std::string Assets::reserve_name(NameList type) {
    if (type == NameList::NONE) {
        return "";
    }

    // return "placeholder";

    std::vector<std::string>& list = _name_lists[static_cast<int>(type)];

    std::string name = list.back();
    list.pop_back();

    return name;

}

std::vector<std::string> get_names(NameList l) {
    return std::vector<std::string>();
}
}