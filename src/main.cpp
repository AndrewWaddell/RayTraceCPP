#include "../include/Scene.h"

int main() {
    
    Scene opticalBench;
    opticalBench.generateExperiment1(); // initialise default test case
    opticalBench.trace();
    // opticalBench.save();
    opticalBench.convertToSTL();
    return 0;
};