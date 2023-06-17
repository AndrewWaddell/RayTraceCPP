#include "../include/Sources.h"

Sources::Sources(){
    bucket = 0;
};

void Sources::addSource(const Source& source) {
    sources.push_back(source);
    bucket += 1;
}

void Sources::addSource() {
    // default constructor
    Source newSource;
    newSource.generateDefault();
    sources.push_back(newSource);
    bucket += 1;
}

Source Sources::grabSource() {
    bucket -= 1;
    return sources[bucket];
};

bool Sources::bucketNotEmpty() {
    return bucket>0;
}
