
#include "RandomGenerator.h"

namespace rrandom {

RandomGenerator::RandomGenerator(int min, int max) : dist(min, max) {}

int RandomGenerator::next_int() {
    return this->dist(this->generator);
}

int get_seed() {
    int ret = 0;

    FILE *urand = fopen("/dev/urandom", "r");
    if (fread(&ret, 1, 4, urand) != 4) {
        ret = -1;
    }
    fclose(urand);
    return ret;
}
}