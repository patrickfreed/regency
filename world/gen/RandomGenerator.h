
#ifndef TEST_PROJECT_RANDOMGENERATOR_H
#define TEST_PROJECT_RANDOMGENERATOR_H

#include <random>

namespace rrandom {

class RandomGenerator {
private:
    std::default_random_engine generator;
    std::uniform_int_distribution<int> dist;
public:
    RandomGenerator(int min, int max);

    int next_int();
};

int get_seed();

}

#endif //TEST_PROJECT_RANDOMGENERATOR_H
