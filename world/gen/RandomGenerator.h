#ifndef REGENCY_WORLD_GEN_RANDOMGENERATOR_H
#define REGENCY_WORLD_GEN_RANDOMGENERATOR_H

#include <random>

namespace regency {
namespace world {
namespace gen {

class RandomGenerator {
  private:

    static std::default_random_engine generator;
    static std::random_device device;

    std::uniform_int_distribution<int> _dist;

  public:
    RandomGenerator(int min, int max);

    int next_int();
};

int get_seed();
}

}
}

#endif // REGENCY_WORLD_GEN_RANDOMGENERATOR_H
