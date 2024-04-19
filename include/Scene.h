#ifndef SCENE_H
#define SCENE_H

#include "Rays.h"
#include "Sources.h"
#include "Shapes.h"
#include "Matrix.h"
#include "MatrixList.h"
#include <fstream>
#include <string>


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
        void generateExperiment1();
        void importScene();
        double getSceneData(int item); // grab data from text file, indexed as item starting from 0
        void trace();
        void printRays();
        void printShapes();
        void convertToSTL(); // converts scene into stl model for visualisation
        void save();
};

#endif