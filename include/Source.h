#ifndef SOURCE_H
#define SOURCE_H

#include "Matrix.h"

class Source {
    private:
        Matrix points;
        Matrix unit;
        int numRays;
    public:
        void generateDefault();
        void generateSingleRay();
        void generateSquare(Matrix loc, Matrix dir,double width, double density);
        int getNumRays();
        Matrix getPoints();
        Matrix getUnit();
};

#endif