#include "../include/Scene.h"

int main() {
    
    Scene opticalBench;
    opticalBench.importScene();
    opticalBench.trace();
    opticalBench.convertToSTL();
    return 0;
};