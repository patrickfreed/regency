
#include "RandomGenerator.h"

namespace regency {
namespace world {
namespace gen {

std::random_device RandomGenerator::device;
std::default_random_engine RandomGenerator::generator{device()};

RandomGenerator::RandomGenerator(int min, int max) : _dist(min, max) {}

int RandomGenerator::next_int() {
    return _dist(generator);
}

int get_seed() {
    std::random_device r;
    return r();
}
}
}
}