#ifndef SCENE_H
#define SCENE_H

#include "Rays.h"
#include "Sources.h"
#include "Shapes.h"
#include "Matrix.h"
#include "MatrixList.h"
#include <fstream>


class Scene {
    private:
        Rays rays;
        Sources sources;
        Shapes shapes;
        double refractiveIndex; // property of scene medium
        int loopLimit; // maximum number of trace steps before stopping trace
        void traceStep();
        Matrix distances; // to each shape for each ray. dims: (rays * shapes)
        MatrixList normals;
    public:
        void generateDefault(); // manual constructor for default scene for testing
        void trace();
        void printRays();
        void printShape();
        void saveRays();
};

#endif