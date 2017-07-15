#include <iostream>

#include "Game.h"
#include "Assets.h"

using namespace std;

int main() {

    // load assets
    // TODO: load other assets here (names, textures, music)
    Assets::font.loadFromFile("../res/font/pixelmix.ttf");

    Game g;
    g.start();

    cout << "Bye!" << endl;
    return 0;
}