#include "../include/Sources.h"

void Sources::addSource(Source source) {
    sources.push_back(source);
}

void Sources::addSource() {
    Source newSource;
    newSource.generateDefault();
    addSource(newSource);
}

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

