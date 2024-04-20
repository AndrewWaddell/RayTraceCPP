#ifndef SOURCE_H
#define SOURCE_H

#include "Matrix.h"
#include "fstream"
#include "string"

class Source {
    public:
        std::string name;
        Matrix points;
        Matrix unit;
        int numRays;
        void generateDefault();
        void generateSquare(Matrix loc, Matrix dir,double width, double density);
};

#endif