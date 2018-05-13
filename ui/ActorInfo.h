
#ifndef REGENCY_ACTORINFO_H
#define REGENCY_ACTORINFO_H

#include <regency/entity/HumanActor.h>

namespace regency::ui {

class ActorInfo {
  public:
    ActorInfo(entity::HumanActor& actor);

    void render(sf::RenderTarget& t);

  private:
    entity::HumanActor& _actor;
};

}


#endif //REGENCY_ACTORINFO_H
