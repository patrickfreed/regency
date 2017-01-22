#include <iostream>
#include <SFML/Network.hpp>
#include "Game.h"
#include "Assets.h"

using namespace std;

int main() {
    cout << "header code here" << endl;

    // load assets
    Assets::font.loadFromFile("../res/font/pixelmix.ttf");

    Game g;
    g.start();

    cout << "trailer code here" << endl;
    return 0;
}