#include "../include/Sources.h"

void Sources::addSource(Source source) {
    sources.push_back(source);
};

void Sources::addSource() {
    Source newSource;
    // newSource.generateDefault();
    newSource.generateSingleRay();
    addSource(newSource);
};

void Sources::experiment1(){
    Source newSource;
    Matrix location;
    // [ 3.5 ]
    // [ 0.5 ]
    // [ -1  ]
    location.generate(3,1);
    location.insert(0,3.5);
    location.insert(1,0.5);
    location.insert(2,-1);
    Matrix direction;
    // [ -0.6 ]
    // [ 0.3 ]
    // [ 1 ]
    direction.generate(3,1);
    direction.insert(0,-0.6);
    direction.insert(1,0.3);
    direction.insert(2,1);
    newSource.generateSquare(location,direction,2,10);
    addSource(newSource);
};

Matrix Sources::points() {
    Matrix matrix;
    for (Source source : sources) {
        matrix.append(source.getPoints());
    }
    return matrix;
};

Matrix Sources::unit() {
    Matrix matrix;
    for (Source source : sources) {
        Matrix test = source.getUnit();
        matrix.append(source.getUnit());
    }
    return matrix;
};

int Sources::numRays() {
    int count = 0;
    for (Source source : sources) {
        count += source.getNumRays();
    }
    return count;
}

