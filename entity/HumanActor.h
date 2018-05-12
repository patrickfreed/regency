
#ifndef REGENCY_HUMANACTOR_H
#define REGENCY_HUMANACTOR_H

#include <memory>
#include <queue>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <entity/Actor.h>
#include <entity/action/Action.h>
#include <regency/entity/DamageSprite.h>

namespace regency {
namespace entity {

class HumanActor : public Actor {
  private:
    void pop_task();

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

    int _recent_damage;

    bool _show_name;
    std::string _name;

    // Work area (affected by _curiosity, _courage)
    std::pair<int, int> _origin;
    int _radius;

    std::queue<std::unique_ptr<action::Action>> _task_queue;

    sf::Text _text;
    sf::Sprite _sprite;

    std::deque<DamageSprite> _damages;

    sf::Time _last_attack;

  public:
    explicit HumanActor(world::World& world);

    HumanActor(const HumanActor& other) = delete;

    void operator=(const HumanActor& other) = delete;

    void tick() override;

    sf::Drawable& get_drawable() override;

    const std::string& get_name() const;

    void render(sf::RenderTarget& target, int x, int y) override;

    void assign_task(std::unique_ptr<action::Action>&& t, bool override = false);

    void set_name_visible(bool name);

    sf::Int32 get_time_per_movement() override;

    sf::Int32 get_time_per_attack() override;

    std::optional<world::Region> get_work_area();

    int get_damage_dealt(Actor& recipient) override;

    int damage(int amount) override;
};

}
}
#endif // REGENCY_HUMANACTOR_H
