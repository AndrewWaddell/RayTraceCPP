#include "../include/Scene.h"

int main() {
    
    Scene opticalBench;
    opticalBench.generateDefault(); // initialise default test case
    opticalBench.trace();
    // opticalBench.save();
    opticalBench.convertToSTL();
    opticalBench.save();
    // opticalBench.printShapes();
    return 0;
};