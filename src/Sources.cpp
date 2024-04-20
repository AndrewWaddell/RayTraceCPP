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
    // source 1 ray 2 location x
    // etc
    // source 2 name
    // etc
    std::ifstream sourcesFile("sources.txt");
    std::getline(sourcesFile, line);
    numSources = std::stoi(line);
    Matrix importData;
    for (int i=0;i<numSources;i++){
        Source newSource;
        std::getline(sourcesFile, line);
        newSource.name = line;
        std::getline(sourcesFile, line);
        newSource.numRays = std::stoi(line);
        for (int j=0;j<newSource.numRays;j++){
            std::getline(sourcesFile,line);
            double px = std::stod(line);
            std::getline(sourcesFile,line);
            double py = std::stod(line);
            std::getline(sourcesFile,line);
            double pz = std::stod(line);
            std::getline(sourcesFile,line);
            double ux = std::stod(line);
            std::getline(sourcesFile,line);
            double uy = std::stod(line);
            std::getline(sourcesFile,line);
            double uz = std::stod(line);
            newSource.points.append(px,py,pz);
            newSource.unit.append(ux,uy,uz);
        }
        sources.push_back(newSource);
    }
    std::cout << "Points" << std::endl;
    Matrix p1 = points();
    p1.print();
    std::cout << "Units" << std::endl;
    Matrix p2 = unit();
    p2.print();
    int h=0;
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
        matrix.append(source.points);
    }
    return matrix;
};

Matrix Sources::unit() {
    Matrix matrix;
    for (Source source : sources) {
        Matrix test = source.unit;
        matrix.append(source.unit);
    }
    return matrix;
};

int Sources::numRays() {
    int count = 0;
    for (Source source : sources) {
        count += source.numRays;
    }
    return count;
}

