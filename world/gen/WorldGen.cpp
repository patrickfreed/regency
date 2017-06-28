
#include "WorldGen.h"

double WorldGen::noise(double nx, double ny) {
    return _gen.GetValue(nx, ny, 0.0) / 2.0 + 0.5;
}

WorldGen::WorldGen() {
    this->_gen.SetSeed(time(NULL));
}
