
#include "RandomGenerator.h"

RandomGenerator::RandomGenerator(int min, int max) : dist(min, max) {
}

int RandomGenerator::next_int() {
    return this->dist(this->generator);
}
