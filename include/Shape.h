#ifndef SHAPE_H
#define SHAPE_H

#include "../include/Rays.h"
#include "../include/Matrix.h"

class Shape {
    private:
        double refractiveIndex;
        Matrix points; // dimension 1 is x,y,z, dim 2 is each point
        Matrix connectivity; // dimension 1 is each triangle, dim 2 is index for each point
        Matrix pointsCOB; // points in terms of new basis (change of basis)
    public:
        void generateDefault();
        void changeOfBasis(Rays rays); // outputs points in terms of new basis from change of basis matrix COB
        bool traceLowRes(Rays rays); // optimisation step. quick check to determine rays are even nearby
        void traceDistance(Rays rays); // find the distance to each shape, for each ray
        Matrix shortestDistances;
        Matrix normals;
};

#endif