#ifndef REGENCY_WORLD_GEN_RANDOMGENERATOR_H
#define REGENCY_WORLD_GEN_RANDOMGENERATOR_H

#include <random>

namespace regency {
namespace world {
namespace gen {

class RandomGenerator {
  private:
    std::random_device _device;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> dist;

  public:
    RandomGenerator(int min, int max);

    int next_int();
};

int get_seed();
}
}
}

#endif // REGENCY_WORLD_GEN_RANDOMGENERATOR_H
