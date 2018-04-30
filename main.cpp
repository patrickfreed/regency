#include <iostream>

#include "Assets.h"
#include "Game.h"

int main() {
    srand(time(NULL));

    // load assets
    // TODO: load other assets here (names, textures, music)
    regency::Assets::load_assets();

    regency::Game g;
    g.start();

    std::cout << "Bye!" << std::endl;
    return 0;
}