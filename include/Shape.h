#ifndef SHAPE_H
#define SHAPE_H

#include "../include/Rays.h"
#include "../include/Matrix.h"

class Shape {
    private:
        double refractiveIndex;
        Matrix points; // dimension 1 is x,y,z, dim 2 is each point
        Matrix connectivity; // dimension 1 is triangle point indices, dim 2 is each triangle
        MatrixList pointsCOB; // points in terms of new basis. Each matrix is for a single ray.
        Matrix pointsCOBSingleRay; // temporary pointsCOB for a single ray, all shape points
        Matrix pointCOB; // temporary array to handle columns of pointsCOBRay
        Matrix distance; // each ray-triangle distance. dims: (rays, triangles). inf if no intersection.
        Matrix distancesCol; // temporary array used in shortestDistances() to contain these values
        int numTriangles; // number of triangles for shape
        bool triangleInterior(Rays rays,int i,int j); // determine if query point i is in triangle j (2D)
        double distanceLinePlane(Rays rays, int i, int j); // distance from line i at location i to intersection with plane j
        bool rightDirection(double d); // determine if distance d to intersection is in right direction
        Matrix triangleNormal(int j); // determine normal vector of plane for triangle j.
        Matrix Q; // query point used in triangle interior function
        Matrix A; // triangle point used in triangle interior function
        Matrix B; // triangle point used in triangle interior function
        Matrix C; // triangle point used in triangle interior function
        Matrix l; // vector in the direction of Line, magnitude 1. used in distanceLinePlane
        Matrix n; // normal vector of Plane, magnitude 1. Used in distanceLinePlane
        Matrix l0; // current location of ray. Used in distanceLinePlane
        Matrix p0; // any point on the plane. Used in distanceLinePlane
        Matrix indexPoint(int i, int j); // grab point i from triangle j using connectivity matrix
    public:
        void generateDefault();
        void changeOfBasis(Rays rays); // outputs points in terms of new basis from change of basis matrix COB
        bool traceLowRes(Rays rays); // optimisation step. quick check to determine rays are even nearby
        void traceDistance(Rays rays); // find the distance to each triangle, for each ray
        Matrix shortestDistances(Rays rays); // column of distances for each ray to closest triangles
        Matrix normals; // for each ray upon each closest triangle. dims: 3 * rays
        int numPoints; // number of points of shape
};

#endif