#include "../include/Sources.h"

void Sources::addSources() {
    std::ifstream sourcesFile("sources.txt");
    // sources structure:
    // number of sources (e.g. 2)
    // source 1 name
    // source 1 numrays
    // source 1 ray 1 location x
    // source 1 ray 1 location y
    // source 1 ray 1 direction
    // source 2 name
    // source 1 - numrays
    // etc
    std::string line;
    std::getline(sourcesFile, line);
    numSources = std::stoi(line);

    for (int i=0;i<numSources;i++){
        Source newSource;
        std::getline(sourcesFile, line);
        newSource.setName(line);
        std::getline(sourcesFile, line);
        newSource.setNumRays(std::stoi(line));
        for (int i=0;i<newSource.getNumRays();i++){
            std::getline(sourcesFile, line);
            
            std::stod(line)
            std::getline(sourcesFile, line);
        }
        

    }

    for (int i=0;i<numSources;i++){
        // sources.push_back(newSource);
        std::getline(sourcesFile, line);
    }
    
    

    
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
    // addSource(newSource);
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

