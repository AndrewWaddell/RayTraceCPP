#include "../include/Shape.h"
#include "../include/Rays.h"

void Shape::generateDefault(){
    refractiveIndex = 1.52;
    // points = [1.5  1.5  0    5]
    //          [1   -1    1    1]
    //          [1    1    0.5  6]
    points.generate(3,4);
    points.insert(0,0,1.5);
    points.insert(0,1,1.5);
    points.insert(0,2,0);
    points.insert(0,3,5);
    points.insert(1,0,1);
    points.insert(1,1,-1);
    points.insert(1,2,1);
    points.insert(1,3,1);
    points.insert(2,0,1);
    points.insert(2,1,1);
    points.insert(2,2,0.5);
    points.insert(2,3,6);
    // connectivity = [0,1,2]
    //                [0,1,3]
    connectivity.generate(2,3);
    connectivity.insert(0,0,2);
    connectivity.insert(0,1,1);
    connectivity.insert(0,2,2);
    connectivity.insert(1,0,0);
    connectivity.insert(1,1,1);
    connectivity.insert(1,2,3);
    numPoints = 3;
    numTriangles = 2;
};

void Shape::changeOfBasis(Rays& rays){
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

bool Shape::traceLowRes(Rays& rays){
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

void Shape::traceDistance(Rays& rays){
    distance.generate(rays.numRays,numTriangles);
    distance.fillInf();
    for (int i=0;i<rays.numRays;i++){
        if (rays.blocked.get(i)){
            continue;
        }
        for (int j=0;j<numTriangles;j++){
            if (triangleInterior(rays,i,j)){
                double d = distanceLinePlane(rays,i,j);
                if (rightDirection(d)){
                    distance.insert(i,j,d);
                }
            }
        }
    }
};

Matrix Shape::shortestDistances(Rays& rays){
    distancesCol.generate(rays.numRays);
    normals.generate();
    for (int i=0;i<rays.numRays;i++){
        int j = distance.minRowIndex(i); // closest triangle index
        double d = distance.get(i,j);
        if (std::isinf(d)){
            distancesCol.append(i,d);
            normals.append(triangleNormal(j));
        } else { // if ray doesn't intersect
            distancesCol.append(i,0);
            normals.append();
        }
    }
    return distancesCol;
};


bool Shape::triangleInterior(Rays& rays,int i,int j){
    // 2D problem
    // test whether query point Q lies within triangle constructed by points A,B,C
    // if Q lies on edge of triangle, it is considered inside triangle

    A = indexPointCOB(i,j,0);
    B = indexPointCOB(i,j,1);
    C = indexPointCOB(i,j,2);

    AB.subtract(B,A);
    AC.subtract(C,A);

    // keep as 2D problem
    AB.slice();
    AC.slice();

    // consider the basis made by AB and AC. We call it basis bc
    // note the current basis we shall call xy

    COB.generate(2);
    COB.append(AB);
    COB.append(AC); // COB currently from bc to xy
    if (COB.detZero()){ //triangle is side-on
        return false;
    }

    COB.inverse(); // COB currently from xy to bc

    // Q is currently with respect to basis xy
    Q = rays.pointsCOB.getCol(i);
    // find Q wrt basis bc
    Qbc.multiply(COB,Q);
    // we denote the components of this vector [b c]
    // b,c are the scalars of Q in terms of triangle sides AB and AC
    // such that Q = b*AB + c*AC
    // therefor for Q interior we require:
    // b>0, c>0, a+b<1
    // I call these truth values t1, t2, t3
    
    bool t1 = Qbc.get(0) >= 0;
    bool t2 = Qbc.get(1) >= 0;
    bool t3 = Qbc.get(0) + Qbc.get(1) <= 0;

    if (t1 && t2 & t3){
        return true;
    }

    return false;
};


double Shape::distanceLinePlane(Rays& rays, int i, int j){
    // find distance d from l0 to point of intersection of Line with Plane
    // Line: set of points s where s = l0 + l*d
    // Plane: set of points s where dot( (s - p0) , n) = 0
    
    // How we solve for d:
    // substitute s_Line into s_Plane
    // dot( ((l0 + l*d) - p0) , n ) = 0
    // dot(l0-p0,n)=dot(-l*d,n)
    // d = dot(p0-l0,n) / dot(l,n)

    l0 = rays.points.getCol(i);
    l = rays.unit.getCol(i);
    p0 = indexPoint(i,j);
    n = triangleNormal(j);

    Matrix difference;
    difference.subtract(p0,l0);
    double numerator = p0.dot(difference,n);
    double denominator = p0.dot(l,n);
    return numerator/denominator;
};

bool Shape::rightDirection(double d){
    return d>0;
};

Matrix Shape::triangleNormal(int j){
    // we connect triangle points A,B,C into two vectors
    // plane is spanned by these vectors: AB,AC
    // cross product AB and AC to get normal of plane
    A = indexPoint(0,j);
    B = indexPoint(1,j);
    C = indexPoint(2,j);

    AB.subtract(B,A);
    AC.subtract(C,A);
    normal.cross(AB,AC);
    normal.normCol();
    return normal;
};

Matrix Shape::indexPoint(int i, int j){
    double indexDouble = connectivity.get(j,i);
    int indexInt = int(indexDouble);
    return points.getCol(indexInt);
};

Matrix Shape::indexPointCOB(int i, int j, int k){
    double indexDouble = connectivity.get(j,k);
    int indexInt = int(indexDouble);
    return pointsCOB.get(i).getCol(indexInt);
};