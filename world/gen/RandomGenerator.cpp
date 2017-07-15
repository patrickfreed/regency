
#include "RandomGenerator.h"

namespace rrandom {

RandomGenerator::RandomGenerator(int min, int max) : _device(), generator(_device()), dist(min, max) {}

int RandomGenerator::next_int() {
    return this->dist(this->generator);
}

int get_seed() {
    std::random_device r;
    return r();
}
}