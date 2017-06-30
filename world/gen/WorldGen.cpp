

#include "WorldGen.h"
#include "RandomGenerator.h"

#include <iostream>

double WorldGen::noise(double nx, double ny) {
    return fmin(fmax(_gen.GetValue(nx, ny, 0.0) / 2.0 + 0.5, 0.0), 1.0);
}

double WorldGen::m_noise(double nx, double ny) {
    return fmin(fmax(_moisture.GetValue(nx, ny, 0.0) / 2.0 + 0.5, 0.0), 1.0);
}

WorldGen::WorldGen() {
    _gen.SetSeed(time(NULL));

    std::cout << time(NULL) << std::endl;
    std::cout << std::hash<int>{}(time(NULL));

    _moisture.SetSeed(rrandom::get_seed());
}
