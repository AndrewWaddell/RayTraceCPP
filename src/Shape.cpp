#include "../include/Shape.h"

void Shape::generateDefault(){
    refractiveIndex = 1.52;
    // points = {1.5,1.5,0,5},{1,-1,1,1},{1,1,0.5,6}
    // connectivity = {0,1,2},{0,1,3}
    numPoints = 3;
};

void Shape::changeOfBasis(Rays rays){
    for (int i=0;i<rays.numRays;i++){
        Matrix COB = rays.COB.get(i);
        pointsCOBSingleRay.generate();
        for (int j=0;j<numPoints;j++){
            Matrix point = points.getCol(j);
            pointCOB.generate(3,1);
            pointCOB.multiply(COB,point);
            pointsCOBSingleRay.append(pointCOB);
        }
        pointsCOB.append(pointsCOBSingleRay);
    }
};

bool Shape::traceLowRes(Rays rays){
    for (int i=0;i<rays.numRays;i++){
        double x = rays.pointsCOB.get(i,0);
        double y = rays.pointsCOB.get(i,1);
        pointsCOBSingleRay = pointsCOB.get(i);
        double minX = pointsCOBSingleRay.minRow(0);
        double minY = pointsCOBSingleRay.minRow(1);
        double maxX = pointsCOBSingleRay.maxRow(0);
        double maxY = pointsCOBSingleRay.maxRow(1);
        if (x>minX && x<maxX && y>minY && y<maxY){
            return true; // if it works for one ray, trace object
        }
    }
    return false;
};

void Shape::traceDistance(Rays rays){
    
};