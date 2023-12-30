#ifndef SHAPE_H
#define SHAPE_H


#include "Matrix.h"
#include "MatrixList.h"

class Rays;

class Shape {
    private:
        MatrixList pointsCOB; // points in terms of new basis. Each matrix is for a single ray.
        Matrix pointsCOBSingleRay; // temporary pointsCOB for a single ray, all shape points
        Matrix pointCOB; // temporary array to handle columns of pointsCOBRay
        Matrix distance; // each ray-triangle distance. dims: (rays, triangles). inf if no intersection.
        Matrix distancesCol; // temporary array used in shortestDistances() to contain these values
        int numTriangles; // number of triangles for shape
        bool triangleInterior(Rays& rays,int i,int j); // determine if ray i goes inside triangle j
        bool interiorLowRes(Matrix ABC,Matrix Q); // reject rays that fall outside box hugging triangle. optimise.
        bool checkPolarity(); // do triangles point in the opposite direction?
        bool trianglePointsUpwards(Matrix ABC); // does middle point B in triangle ABC point upwards?
        bool trianglePointsDownwards(Matrix ABC); // does middle point B in triangle ABC point downwards?
        bool trianglePointsFlat(Matrix ABC); // does middle point B in triangle ABC point neither upwards nor downwards?
        bool compareAngles(Matrix angle1, Matrix angle2); // return a1>a2 for angles constructed with 3 points (cols)
        double distanceLinePlane(Rays& rays, int i, int j); // distance from line i at location i to intersection with plane j
        bool rightDirection(double d); // determine if distance d to intersection is in right direction
        Matrix triangleNormal(int j); // determine normal vector of plane for triangle j.
        Matrix Q; // query point used in triangle interior function
        Matrix A; // triangle point used in triangle interior function and triangle normal
        Matrix B; // triangle point used in triangle interior function and triangle normal
        Matrix C; // triangle point used in triangle interior function and triangle normal
        Matrix ABC; // concatenation of A,B,C as above used in triangle interior
        Matrix ACB; // as above
        Matrix AQB; // as above
        Matrix QAB; // as above
        Matrix CAB; // as above
        Matrix ABQ; // as above
        Matrix l; // vector in the direction of Line, magnitude 1. used in distanceLinePlane
        Matrix n; // normal vector of Plane, magnitude 1. Used in distanceLinePlane
        Matrix l0; // current location of ray. Used in distanceLinePlane
        Matrix p0; // any point on the plane. Used in distanceLinePlane
        Matrix AB; // vector used in triangle normal function
        Matrix AC; // vector used in triangle normal function
        Matrix normal; // temporary column vector used in triangle normal function
        Matrix indexPoint(int i, int j); // grab point i from triangle j using connectivity matrix
        Matrix indexPointCOB(int i, int j, int k); // grab point k in basis of ray i from triangle j
    public:
        double refractiveIndex;
        Matrix points; // dimension 1 is x,y,z, dim 2 is each point
        Matrix connectivity; // dimension 1 is triangle point indices, dim 2 is each triangle
        void generateDefault();
        void changeOfBasis(Rays& rays); // outputs points in terms of new basis from change of basis matrix COB
        bool traceLowRes(Rays& rays); // optimisation step. quick check to determine rays are even nearby
        void traceDistance(Rays& rays); // find the distance to each triangle, for each ray
        Matrix shortestDistances(Rays& rays); // column of distances for each ray to closest triangles
        Matrix normals; // for each ray upon each closest triangle. dims: 3 * rays
        int numPoints; // number of points of shape
        bool blocker; // shape property. true if type fully absorbs ray. stop tracing after this shape.
        bool mirror; // shape property. true if rays reflect off shape. false if rays refract through shape.
};

#endif