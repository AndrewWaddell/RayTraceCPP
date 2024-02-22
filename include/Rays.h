#ifndef RAYS_H
#define RAYS_H



#include "BoolArray.h"
#include "Matrix.h"
#include "MatrixList.h"

class Shapes;
class Shape;
class Sources;

class Rays {
    private:
        BoolArray inside; // are the rays inside a shape
        Matrix origins; // index of ray in distancesAcc
        Matrix orth1; // first orthogonal vector
        Matrix orth2; // second orthogonal vector
        Matrix inverse; // used to calculate change of basis
        Matrix unitCol; // a single unit vector, already indexed
        Matrix pointCOB; // pointsCOB but for a single point
        double d; // distance to next intersection. used in update()
        Matrix normal; // normal of intersecting plane. used in update()
        Shape* shape; // temporary reference to shape used in update()
        double nShape; // refractive index of shape. used in update()
        double nScene; // refractive index of scene, of atmosphere surrounding shapes. used in update()
        double ratio; // ratio of refractive indices n1/n2 as ray passes through boundary
        Matrix refract(int i); // implement Snell's law for ray i refracting at plane described by "normal"
        Matrix reflect(int i); // calculate mirror bounce of ray i onto plane described by "normal"
        void updateRayLocation(int i); // replace ray i location with next intersection location
        void updateRayDirection(int i); // replace ray i direction with the reflected/refracted direction
        void flipNormal(int i); // normal must point in direction of incoming ray. flip if necessary.
        double cosTheta(int i); // calculates cos of angle using vector dot product
        double cosThetaRefract(int i); // calculate cos of angle of refraction
        void absorbRay(int i); // absorb ray i into blocker. stop ray from propagating onwards
    public:
        int numRays; // number of rays are treated as columns in matrices
        Matrix points; // location of each ray
        Matrix unit; // unit vector pointing in the direction of the ray
        Matrix pointsAcc; // accumulated points between steps
        Matrix unitAcc; // accumulated unit vectors between steps
        Matrix distancesAcc; // accumulated lengths of each array
        Matrix unitScaled; // scaled unit vectors for plotting
        void addSources(Sources& sources);
        bool areActive();
        void createNewBasis();
        int size();
        MatrixList COB; // change of basis matrix
        Matrix pointsCOB; // points in terms of the change of basis
        BoolArray blocked; // has each ray hit a blocker?
        void update(int i,int j,Matrix distances,MatrixList normals,double nScene,Shapes& shapes);// update ray i at int with shape j
        void scaleUnit(); // scales each unit vector to corresponding distance
        void extend(double len); // give distance len to all vectors after final intersections
};

#endif