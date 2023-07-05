#include "../include/Shape.h"

void Shape::generateDefault(){
    refractiveIndex = 1.52;
    // points = {1.5,1.5,0,5},{1,-1,1,1},{1,1,0.5,6}
    // connectivity = {0,1,2},{0,1,3}
};

void Shape::changeOfBasis(Rays rays){

};

bool Shape::traceLowRes(Rays rays){
    
};

void Shape::traceDistance(Rays rays){};