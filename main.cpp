#include <iostream>

#include "Assets.h"
#include "Game.h"

int main() {

    // load assets
    // TODO: load other assets here (names, textures, music)
    regency::Assets::font.loadFromFile("../res/font/pixelmix.ttf");

    regency::Game g;
    g.start();

    std::cout << "Bye!" << std::endl;
    return 0;
}