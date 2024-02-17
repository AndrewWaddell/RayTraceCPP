#include "../include/Scene.h"

int main() {
    
    Scene opticalBench;
    opticalBench.generateDefault(); // initialise default test case
    opticalBench.trace();
    opticalBench.printRays();
    opticalBench.printShape();
    return 0;
};