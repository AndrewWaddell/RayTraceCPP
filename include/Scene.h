#ifndef SCENE_H
#define SCENE_H

#include "Rays.h"
#include "Sources.h"
#include "Shapes.h"
#include "Matrix.h"


class Scene {
    private:
        Rays rays;
        Sources sources;
        Shapes shapes;
        double refractiveIndex; // property of scene medium
        int loopLimit; // maximum number of trace steps before stopping trace
        void traceStep();
        Matrix distances;
        MatrixList normals;
    public:
        void generateDefault(); // manual constructor for default scene for testing
        void trace();
};

#endif