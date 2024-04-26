#include "../include/Scene.h"

int main() {
    
    Scene opticalBench;
    opticalBench.importScene();
    opticalBench.trace();
    opticalBench.convertToSTL();
    opticalBench.save();
    // opticalBench.printShapes();
    return 0;
};