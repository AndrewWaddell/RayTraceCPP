#include "../include/Scene.h"

int main() {
    
    Scene opticalBench;
    opticalBench.generateDefault(); // initialise default test case
    opticalBench.trace();
    opticalBench.printRays();
    opticalBench.printShape();
    opticalBench.saveRays();
    return 0;
};