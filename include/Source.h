#ifndef SOURCE_H
#define SOURCE_H

#include "Matrix.h"

class Source {
    private:
        Matrix points;
        Matrix unit;
    public:
        void generateDefault();
        int numRays;
};

#endif