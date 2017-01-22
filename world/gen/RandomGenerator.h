
#ifndef TEST_PROJECT_RANDOMGENERATOR_H
#define TEST_PROJECT_RANDOMGENERATOR_H

#include <random>

using namespace std;

class RandomGenerator {
private:
    default_random_engine generator;
    uniform_int_distribution<int> dist;
public:
    RandomGenerator(int min, int max);
    int next_int();
};


#endif //TEST_PROJECT_RANDOMGENERATOR_H
