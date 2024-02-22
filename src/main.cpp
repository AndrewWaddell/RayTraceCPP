#include "../include/Scene.h"

int main() {
    
    Scene opticalBench;
    opticalBench.generateDefault(); // initialise default test case
    opticalBench.trace();
    opticalBench.save();
    return 0;
};