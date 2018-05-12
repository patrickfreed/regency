#include <iostream>

#include <regency/Game.h>

int main() {
    regency::Game& game = regency::Game::get_instance();
    game.start();

    std::cout << "Bye!" << std::endl;
    return 0;
}