#include "../include/Source.h"

void Source::generateDefault(){
    // points = {0,1,2},{0,0,0},{0,0,0}
    // unit = {0,0,0},{0,0,0},{1,1,1}

    // the matrix class construction might have to be fairly empty,
    // and setting of the actual values might have to happen as a method
    // the local matrix values in matrix class should be set by a constructor
    numRays = 3;
}

Matrix Source::getPoints() {
    return points;
}

Matrix Source::getUnit() {
    return unit;
}

int Source::getNumRays() {
    return numRays;
}
