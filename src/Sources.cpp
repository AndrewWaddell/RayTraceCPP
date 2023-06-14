#include "../include/Sources.h"



void Sources::addSource(const Source& source) {
    sources.push_back(source);
}

void Sources::addSource() {
    Source newSource;
    sources.push_back(newSource);
}
