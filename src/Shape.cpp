#include "../include/Shape.h"

void Shape::generateDefault(){
    refractiveIndex = 1.52;
    // points = {1.5,1.5,0,5},{1,-1,1,1},{1,1,0.5,6}
    // connectivity = {0,1,2},{0,1,3}
    numPoints = 3;
    numTriangles = 2;
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
    distance.generate(rays.numRays,numTriangles);
    distance.fillInf();
    for (int i=0;i<rays.numRays;i++){
        for (int j=0;j<numTriangles;j++){
            if (rays.blocked.get(i)){
                continue;
            }
            if (triangleInterior()){
                double d = distanceLinePlane();
                if (rightDirection(d)){
                    distance.insert(i,j,d);
                }
            }
        }
    }
};

Matrix Shape::shortestDistances(Rays rays){
    distancesCol.generate(rays.numRays);
    normals.generate();
    for (int i=0;i<rays.numRays;i++){
        int j; // closest triangle index
        j = distance.minRowIndex(i);
        distancesCol.append(i,distance.get(i,j));
        // while we know the closest triangle, we calculate the corresponding normal
        normals.append(triangleNormal(j));
    }
    return distancesCol;
};


bool Shape::triangleInterior(Rays rays,int i,int j){
    // 2D problem
    // test whether query point Q lies within triangle constructed by points A,B,C
};

double Shape::distanceLinePlane(Rays rays, int i, int j){
    // find distance d from l0 to point of intersection of Line with Plane
    // Line: set of points s where s = l0 + l*d
    // Plane: set of points s where dot( (s - p0) , n) = 0
    
    // How we solve for d:
    // substitute s_Line into s_Plane
    // dot( ((l0 + l*d) - p0) , n ) = 0
    // dot(l0-p0,n)=dot(-l*d,n)
    // d = dot(p0-l0,n) / dot(l,n)

    l = rays.unit.getCol(i);
    n = connectivity // i think i should swap axes for connectivity. i hesitate to index it here

};

bool Shape::rightDirection(double d){
    return d>0;
};

Matrix Shape::triangleNormal(int i){};