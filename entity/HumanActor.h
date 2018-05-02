
#ifndef REGENCY_HUMANACTOR_H
#define REGENCY_HUMANACTOR_H

#include <memory>
#include <queue>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Actor.h"
#include "misc/Task.h"

namespace regency {
namespace entity {

class HumanActor : public Actor {
  private:
    // biological stats
    int _hunger;
    int _health;
    int _thirst;
    int _energy;

    // personality
    int _courage;
    int _curiosity;
    int _intelligence;
    int _laziness;
    int _temper;
    int _sociality;

    // skill with tool
    int _axe;
    int _sword;
    int _fishing_rod;
    int _pickaxe;
    int _hammer;

    std::string _name;

    // Work area (affected by _curiosity, _courage)
    std::pair<int, int> _origin;
    int _radius;

    std::queue<std::unique_ptr<task::Task>> task_queue;

    sf::RectangleShape drawable;

    sf::Sprite _sprite;

  public:
    HumanActor(world::World& world);

    virtual void tick();

    virtual sf::Drawable& get_drawable();

    void render(sf::RenderTexture render_texture);
};

}
}
#endif // REGENCY_HUMANACTOR_H
