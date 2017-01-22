#ifndef TEST_PROJECT_ENTITY_H
#define TEST_PROJECT_ENTITY_H

#include <string>
#include <SFML/Graphics/Drawable.hpp>
#include "../world/World.h"

using namespace std;

class Entity {
protected:
    int x;
    int y;
    int z;

private:
    string id;
    World& world;

public:
    Entity(World& world);
    size_t operator()(const Entity& e);
    tuple<int, int, int> get_location();
    World& get_world();

    virtual ~Entity() {}
    virtual sf::Drawable& get_drawable() = 0;
};

#endif //TEST_PROJECT_ENTITY_H
