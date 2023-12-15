#ifndef RAYS_H
#define RAYS_H


#include "Source.h"
#include "Sources.h"
#include "BoolArray.h"
#include "Matrix.h"
#include "MatrixList.h"

class Rays {
    private:
        BoolArray blocked; // has each ray hit a blocker?
        
        Matrix points; // location of each ray
        Matrix unit; // unit vector pointing in the direction of the ray
        BoolArray inside; // are the rays inside a shape
        Matrix pointsAcc; // accumulated points between steps
        Matrix unitAcc; // accumulated unit vectors between steps
        Matrix distancesAcc; // accumulated lengths of each array
        Matrix origins; // index of ray in distancesAcc
        Matrix orth1; // first orthogonal vector
        Matrix orth2; // second orthogonal vector
        Matrix inverse; // used to calculate change of basis
        Matrix unitCol; // a single unit vector, already indexed
        Matrix pointCOB; // pointsCOB but for a single point
    public:
        int numRays; // number of rays are treated as columns in matrices
        void addSources(Sources sources);
        bool areActive();
        void createNewBasis();
        int size();
        MatrixList COB; // change of basis matrix
        Matrix pointsCOB; // points in terms of the change of basis
};

#endif