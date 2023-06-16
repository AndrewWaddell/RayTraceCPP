#include "../include/Sources.h"



void Sources::addSource(const Source& source) {
    sources.push_back(source);
}

void Sources::addSource() {
    // default constructor
    Source newSource;
    newSource.generateDefault();
    sources.push_back(newSource);
}
