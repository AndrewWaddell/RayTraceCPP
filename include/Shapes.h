#ifndef SHAPES_H
#define SHAPES_H

#include "Shape.h"
#include "Matrix2d.h"

class Shapes {
    private:
        Matrix2d points; // dimension 1 is x,y,z, dim 2 is each point
        Matrix2d connectivity; // dimension 1 is each triangle, dim 2 is index for each point
        Matrix2d pointsCOB; // points in terms of new basis (change of basis)
};

#endif