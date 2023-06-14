#ifndef SOURCES_H
#define SOURCES_H

#include <vector>
#include "Source.h"

class Sources {
private:
    std::vector<Source> sources;
public:
    void addSource(const Source& source);
};

#endif
