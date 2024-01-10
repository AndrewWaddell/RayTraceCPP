#include "../include/Shape.h"
#include "../include/Rays.h"

void Shape::generateDefault(){
    refractiveIndex = 1.52;
    // points = {1.5,1.5,0,5},{1,-1,1,1},{1,1,0.5,6}
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
    // connectivity = {0,1,2},{0,1,3}
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
        if (d != std::numeric_limits<double>::infinity()){
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
    // if Q lies on edge of triangle, it is considered outside triangle

    // initial setup
    for (int k=0;k<3;k++){ // k is each point A,B,C respectively
        ABC.append(indexPointCOB(i,j,k));
    }
    Q = rays.pointsCOB.getCol(i);

    // optimisation step
    if (!interiorLowRes(ABC,Q)){
        return false;
    }

    // Define A as triangle point with minimum x, B as maximum x, C as other index
    int indexA = ABC.minRowIndex(0);
    int indexB = ABC.maxRowIndex(0);
    int indexC = (indexA+indexB-3)*-1;
    A = ABC.getCol(indexA);
    B = ABC.getCol(indexB);
    C = ABC.getCol(indexC);

    // perform algorithm
    ACB.construct(A,C,B);
    AQB.construct(A,Q,B);
    if (checkPolarity()){
        return false;
    }
    
    // The remaining triangle region is bounded by two angles
    // first angle about A
    QAB.construct(Q,A,B);
    CAB.construct(C,A,B);
    if (compareAngles(QAB,CAB)){
        return false;
    }
    // second angle about B
    ABQ.construct(A,B,Q);
    ABC.construct(A,B,C);
    if (compareAngles(ABQ,ABC)){
        return false;
    }
    // query is bounded by both angles
    return true;
};

bool Shape::interiorLowRes(Matrix ABC,Matrix Q){
    for (int row;row<2;row++){ // only x, y because 2D problem
        if (Q.get(row) > ABC.maxRow(row)){
            return false;
        }
        if (Q.get(row) < ABC.minRow(row)){
            return false;
        }
    }
    return true;
};

bool Shape::checkPolarity(){
    // returns true if they point in the opposite direction. ray misses. not interior.
    if (trianglePointsUpwards(ACB)){
        if (trianglePointsDownwards(AQB)||trianglePointsFlat(AQB)){
            return true;
        }
    } else if (trianglePointsDownwards(ACB)){
        if (trianglePointsUpwards(AQB)||trianglePointsFlat(AQB)){
            return true;
        }
    } else if (trianglePointsFlat(ACB)){
        return true; // triangle is side on, ray skims past
    }
    return false;
};

bool Shape::trianglePointsUpwards(Matrix ABC){
    return ABC.signedArea()>0;
};

bool Shape::trianglePointsDownwards(Matrix ABC){
    return ABC.signedArea()<0;
};

bool Shape::trianglePointsFlat(Matrix ABC){
    return ABC.signedArea() == 0;
};

bool Shape::compareAngles(Matrix angle1, Matrix angle2){
    // works for angles between 0 and 90deg
    // comparing the cos of both angles will allow us to compare both angles
    // cos is decreasing, therefore to determine angle1 > angle2,
    // we flip the sign: cos(angle1) < cos(angle2)
    return angle1.cosTheta() < angle2.cosTheta();
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
    double indexDouble = connectivity.get(i,j);
    int indexInt = int(indexDouble);
    return points.getCol(indexInt);
};

Matrix Shape::indexPointCOB(int i, int j, int k){
    std::cout << "connectivity" << std::endl;
    connectivity.print();
    std::cout << "ray i: ";
    std::cout << i;
    std::cout << ", triangle j: ";
    std::cout << j << std::endl;
    double indexDouble = connectivity.get(j,k);
    int indexInt = int(indexDouble);
    return pointsCOB.get(i).getCol(indexInt);
};