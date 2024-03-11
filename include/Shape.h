#ifndef SHAPE_H
#define SHAPE_H


#include "Matrix.h"
#include "MatrixList.h"
// #include <assimp/Importer.hpp>
// #include <assimp/scene.h>
// #include <assimp/postprocess.h>

class Rays;

class Shape {
    private:
        MatrixList pointsCOB; // points in terms of new basis. Each matrix is for a single ray.
        Matrix pointsCOBSingleRay; // temporary pointsCOB for a single ray, all shape points
        Matrix pointCOB; // temporary array to handle columns of pointsCOBRay
        Matrix distance; // each ray-triangle distance. dims: (rays, triangles). inf if no intersection.
        Matrix distancesCol; // temporary array used in shortestDistances() to contain these values
        bool triangleInterior(Rays& rays,int i,int j); // determine if ray i goes inside triangle j
        double distanceLinePlane(Rays& rays, int i, int j); // distance from line i at location i to intersection with plane j
        bool rightDirection(double d); // determine if distance d to intersection is in right direction
        Matrix triangleNormal(int j); // determine normal vector of plane for triangle j.
        void indexPoints(int j); // prepare commonly used variables for triangle j
        Matrix Q; // query point used in triangle interior function
        Matrix A; // triangle point used in triangle interior function and triangle normal
        Matrix B; // triangle point used in triangle interior function and triangle normal
        Matrix C; // triangle point used in triangle interior function and triangle normal
        Matrix AB; // vector from A to B used in triangle interior and triangle normal
        Matrix AC; // vector from A to C used in triangle interior and triangle normal
        Matrix AQ; // vector from A to Q used in triangle interior and triangle normal
        Matrix BC; // vector from B to C used in convertToVectors
        Matrix COB; // change of basis matrix from basis between bc and xy used in triangle interior
        Matrix Qbc; // point Q with respect to basis bc used in triangle interior
        Matrix l; // vector in the direction of Line, magnitude 1. used in distanceLinePlane
        Matrix n; // normal vector of Plane, magnitude 1. Used in distanceLinePlane
        Matrix l0; // current location of ray. Used in distanceLinePlane
        Matrix p0; // any point on the plane. Used in distanceLinePlane
        Matrix normal; // temporary column vector used in triangle normal function
        Matrix indexPointCOB(int i, int j, int k); // grab point k in basis of ray i from triangle j
        Matrix vecOut; // output for convertToVectors. rows: x,y,z,ux,uy,uz
    public:
        double refractiveIndex;
        Matrix points; // rows are x,y,z, cols are each point
        Matrix connectivity; // rows are triangle point indices, cols are each triangle
        void generateDefault();
        void import();
        void changeOfBasis(Rays& rays); // outputs points in terms of new basis from change of basis matrix COB
        bool traceLowRes(Rays& rays); // optimisation step. quick check to determine rays are even nearby
        void traceDistance(Rays& rays); // find the distance to each triangle, for each ray
        Matrix shortestDistances(Rays& rays); // column of distances for each ray to closest triangles
        Matrix normals; // for each ray upon each closest triangle. dims: 3 * rays
        int numPoints; // number of points of shape
        int numTriangles; // number of triangles for shape
        bool blocker; // shape property. true if type fully absorbs ray. stop tracing after this shape.
        bool mirror; // shape property. true if rays reflect off shape. false if rays refract through shape.
        Matrix convertToVectors(); // draw triangle edges as vectors. rows: x,y,z,ux,uy,uz
        Matrix indexPoint(int i, int j); // grab point i from triangle j using connectivity matrix
};

#endif