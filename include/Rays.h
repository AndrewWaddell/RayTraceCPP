#ifndef RAYS_H
#define RAYS_H


#include "../include/Source.h"
#include "../include/Sources.h"
#include "../include/BoolArray.h"

class Rays {
    private:
        BoolArray blocked;
        int numrays;
    public:
        void addSources(Sources sources);
        bool areActive();
};

#endif