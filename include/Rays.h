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
        Matrix points;
    public:
        void addSources(Sources sources);
        bool areActive();
};

#endif