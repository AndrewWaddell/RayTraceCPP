#include "../include/Source.h"

void Source::generateDefault(){
    // points = [0,1,2]
    //          [0,0,0]
    //          [0,0,0]
    points.generate(3,3);
    points.insert(0,1,1);
    points.insert(0,2,2);
    // unit = [0,0,0]
    //        [0,0,0]
    //        [1,1,1]
    unit.generate(3,3);
    unit.insert(2,0,1);
    unit.insert(2,1,1);
    unit.insert(2,2,1);

    numRays = 3;
};


void Source::generateSquare(Matrix loc, Matrix dir,double width, double density){
    Matrix orth1; // orth1&2 span plane orthogonal to dir (direction)
    Matrix orth2;
    Matrix basis;
    orth1.rotate90(dir);
    orth2.cross(orth1,dir);
    basis.generate();
    basis.append(orth1);
    basis.append(orth2);

    // density is number of rays per square unit
    double raysPerLine = sqrt(density); // consider as an edge of unit square
    double gapBetweenRays = 1/raysPerLine;

    Matrix coordinates;
    coordinates.generate(2);
    Matrix col;
    for (double i=-width/2;i<width/2;i=i+gapBetweenRays){
        for (double j=-width/2;j<width/2;j=j+gapBetweenRays){
            col.generate(2,1);
            col.insert(0,i);
            col.insert(1,j);
            coordinates.append(col);
        }
    }
    numRays = coordinates.numCols;

    points.generate();
    points.multiply(basis,coordinates);
    loc.broadcast(numRays);
    points.add(loc);

    unit = dir;
    unit.broadcast(numRays);
    unit.normCol();
};

