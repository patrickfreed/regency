
#ifndef REGENCY_HUMANACTOR_H
#define REGENCY_HUMANACTOR_H

#include <memory>
#include <queue>

#include <SFML/Graphics/RectangleShape.hpp>

#include "Actor.h"
#include "misc/Task.h"

namespace regency {
namespace entity {

class HumanActor : public Actor {
  private:
    // biological stats
    int hunger;
    int health;
    int thirst;
    int energy;

    // personality
    int courage;
    int curiosity;
    int intelligence;
    int laziness;
    int temper;
    int sociality;

    // skill with tool
    int axe;
    int sword;
    int fishing_rod;
    int pickaxe;
    int hammer;

    // Work area (affected by curiosity, courage)
    std::pair<int, int> origin;
    int radius;

    std::queue<std::unique_ptr<task::Task>> task_queue;

    sf::RectangleShape drawable;

  public:
    HumanActor(world::World& world);

    virtual void tick();

    virtual sf::Drawable& get_drawable();
};
}
}

#endif // REGENCY_HUMANACTOR_H
