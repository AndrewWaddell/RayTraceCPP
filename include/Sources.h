#ifndef SOURCES_H
#define SOURCES_H

#include <vector>
#include "Source.h"

class Sources {
private:
    std::vector<Source> sources;
    int bucket; // keeps track of how many sources are yet to be emptied
    Source grabSource(); // empties each source one by one until bucket is empty
    bool bucketNotEmpty(); // test if all sources have been emptied
    int raysCount;
public:
    Sources();
    void addSource(); // generates default source
    void addSource(const Source& source);
    int count(); // how many rays between all sources
};

#endif
