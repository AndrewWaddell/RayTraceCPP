#include "../include/Sources.h"

void Sources::addSource(const Source& source) {
    sources.push_back(source);
}

void Sources::addSource() {
    Source newSource;
    newSource.generateDefault();
    sources.push_back(newSource);
}

Matrix Sources::points() {
    for (Source source : sources) {
        matrix.append(source.getPoints());
    }
    return matrix;
};

Matrix Sources::unit() {
    matrix.generate();
    for (Source source : sources) {
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

