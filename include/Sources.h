#ifndef SOURCES_H
#define SOURCES_H

#include <vector>
#include "Source.h"
#include "Matrix.h"
#include <functional>
#include <fstream>
#include <string>

class Sources {
private:
    std::vector<Source> sources;
    int numSources;
    std::string line; // general use string for import
public:
    void importSources(); // from file sources.txt
    Matrix points(); // returns points from all sources concatenated
    Matrix unit(); // returns all units from all sources concatenated
    int numRays(); // returns number of columns between sources
};

#endif
