#ifndef SHAPE_H
#define SHAPE_H

#include "Matrix2d.h"

class Shape {
    private:
        double refractiveIndex;
        Matrix2d points; // dimension 1 is x,y,z, dim 2 is each point
        Matrix2d connectivity; // dimension 1 is each triangle, dim 2 is index for each point
        Matrix2d pointsCOB; // points in terms of new basis (change of basis)
    public:
        void generateDefault();
};

#endif