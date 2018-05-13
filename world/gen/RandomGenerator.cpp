
#include <ctime>
#include "RandomGenerator.h"

namespace regency {
namespace world {
namespace gen {

std::random_device RandomGenerator::device;
std::default_random_engine RandomGenerator::generator{static_cast<long unsigned int>(time(0))};

RandomGenerator::RandomGenerator(int min, int max) : _dist(min, max) {}

int RandomGenerator::next_int() {
    return _dist(generator);
}

std::default_random_engine& RandomGenerator::get_generator() {
    return generator;
}

int get_seed() {
    std::random_device r;
    return r();
}
}
}
}