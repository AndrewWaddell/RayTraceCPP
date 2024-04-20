#include "../include/Sources.h"

void Sources::importSources() {
    // sources structure:
    // number of sources
    // source 1 name
    // source 1 numrays
    // source 1 ray 1 location x
    // source 1 ray 1 location y
    // source 1 ray 1 location z
    // source 1 ray 1 unit x
    // source 1 ray 1 unit y
    // source 1 ray 1 unit z
    // source 2 name
    // etc
    std::ifstream sourcesFile("sources.txt");
    std::getline(sourcesFile, line);
    numSources = std::stoi(line);
    for (int i=0;i<numSources;i++){
        Source newSource;
        std::getline(sourcesFile, line);
        newSource.name = line;
        std::getline(sourcesFile, line);
        newSource.numRays = std::stoi(line);
        for (int i=0;i<newSource.numRays;i++){
            Matrix importData;
            for (int j=0;j<3;j++){
                std::getline(sourcesFile,line);
                double dataDouble = std::stod(line);
                importData.append(dataDouble);
            }
            newSource.points.append(importData);
            importData.generate();
            for (int j=0;j<3;j++){
                std::getline(sourcesFile,line);
                double dataDouble = std::stod(line);
                importData.append(dataDouble);
            }
            newSource.unit.append(importData);
        }
        sources.push_back(newSource);
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

