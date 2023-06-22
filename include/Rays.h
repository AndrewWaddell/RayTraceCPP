#ifndef RAYS_H
#define RAYS_H


#include "Source.h"
#include "Sources.h"
#include "BoolArray.h"
#include "Matrix.h"

class Rays {
    private:
        BoolArray blocked;
        int numRays;
        Matrix points; // location of each ray
        Matrix unit; // unit vector pointing in the direction of the ray
    public:
        void addSources(Sources sources);
        bool areActive();
};

#endif