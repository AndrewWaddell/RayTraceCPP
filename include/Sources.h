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
    std::vector<std::string> sourceNames;
public:
    void addSources(); // generates default source
    void experiment1(); // generate source for experiment 1
    void addSources(Source source);
    Matrix points(); // returns points from all sources concatenated
    Matrix unit(); // returns all units from all sources concatenated
    int numRays(); // returns number of columns between sources
};

#endif
