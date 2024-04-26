#ifndef SOURCE_H
#define SOURCE_H

#include "Matrix.h"

class Source {
    public:
        std::string name;
        Matrix points;
        Matrix unit;
        int numRays;
};

#endif