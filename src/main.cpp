#include "../include/Scene.h"

int main() {
    
    Scene opticalBench;
    // opticalBench.generateDefault(); // initialise default test case
    opticalBench.importScene();
    // opticalBench.generateExperiment1();
    opticalBench.trace();
    opticalBench.convertToSTL();
    opticalBench.save();
    // opticalBench.printShapes();
    return 0;
};