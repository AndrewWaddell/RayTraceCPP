#ifndef RAYS_H
#define RAYS_H


#include "Source.h"
#include "Sources.h"
#include "BoolArray.h"
#include "Matrix.h"

class Rays {
    private:
        BoolArray blocked; // has each ray hit a blocker?
        int numRays; // number of rays are treated as columns in matrices
        Matrix points; // location of each ray
        Matrix unit; // unit vector pointing in the direction of the ray
        BoolArray inside; // are the rays inside a shape
        Matrix pointsAcc; // accumulated points between steps
        Matrix unitAcc; // accumulated unit vectors between steps
    public:
        void addSources(Sources sources);
        bool areActive();
};

#endif