
#include "WorldGen.h"

#include <iostream>

#include "RandomGenerator.h"

namespace regency {
namespace world {
namespace gen {

double WorldGen::noise(double nx, double ny) {
    return fmin(fmax(_gen.GetValue(nx, ny, 0.0) / 2.0 + 0.5, 0.0), 1.0);
}

double WorldGen::m_noise(double nx, double ny) {
    return fmin(fmax(_moisture.GetValue(nx, ny, 0.0) / 2.0 + 0.5, 0.0), 1.0);
}

WorldGen::WorldGen() {
    auto t = time(NULL);
    auto seed_2 = t * t / 12 + 3;

    _gen.SetSeed(t);
    _moisture.SetSeed(seed_2);
}
}
}
}
