
#include "RandomGenerator.h"

namespace regency {
namespace world {
namespace gen {

RandomGenerator::RandomGenerator(int min, int max)
    : _device(), generator(_device()), dist(min, max) {}

int RandomGenerator::next_int() {
    return this->dist(this->generator);
}

int get_seed() {
    std::random_device r;
    return r();
}
}
}
}