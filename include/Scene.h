#ifndef SCENE_H
#define SCENE_H

#include "../include/Rays.h"
#include "../include/Sources.h"
#include "../include/Shapes.h"


class Scene {
    private:
        Rays rays;
        Sources sources;
        Shapes shapes;
        double refractiveIndex; // property of scene medium
        int loopLimit; // maximum number of trace steps before stopping trace
        void traceStep();
    public:
        void generateDefault(); // manual constructor for default scene for testing
        void trace();
};

#endif