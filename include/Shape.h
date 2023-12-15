#ifndef SHAPE_H
#define SHAPE_H

#include "../include/Rays.h"
#include "../include/Matrix.h"

class Shape {
    private:
        double refractiveIndex;
        Matrix points; // dimension 1 is x,y,z, dim 2 is each point
        Matrix connectivity; // dimension 1 is each triangle, dim 2 is index for each point
        MatrixList pointsCOB; // points in terms of new basis. Each matrix is for a single ray.
        Matrix pointsCOBSingleRay; // temporary pointsCOB for a single ray, all shape points
        Matrix pointCOB; // temporary array to handle columns of pointsCOBRay
    public:
        void generateDefault();
        void changeOfBasis(Rays rays); // outputs points in terms of new basis from change of basis matrix COB
        bool traceLowRes(Rays rays); // optimisation step. quick check to determine rays are even nearby
        void traceDistance(Rays rays); // find the distance to each shape, for each ray
        Matrix shortestDistances;
        Matrix normals;
        int numPoints; // number of points of shape
};

#endif