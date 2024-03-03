#include "../include/Rays.h"
#include "../include/Shape.h"
#include "../include/Shapes.h"
#include "../include/Source.h"
#include "../include/Sources.h"


void Rays::addSources(Sources& sources){
    // builds a single instance of rays based on all sources in the scene
    points.generate(sources.points());
    unit.generate(sources.unit());
    numRays = sources.numRays();
    inside.generate(numRays);
    blocked.generate(numRays);
    pointsAcc.append(points);
    unitAcc.append(unit);
    distancesAcc.zeros(numRays);
    origins.range(numRays);
};

bool Rays::areActive(){
    // if there are any rays left that haven't hit a blocker, sensor or boundary,
    // then return true
    // once all rays have finished their journey, return false
    return blocked.anyFalse();
};

void Rays::createNewBasis(){
    // creates non-unique basis for each ray where the third dimension
    // is in the direction of the ray.

    for (int i=0;i<unit.numCols;i++){
        Matrix unitCol = unit.getCol(i);
        orth1.rotate90(unitCol);
        orth2.cross(orth1,unitCol);

        inverse.generate();
        inverse.append(orth1);
        inverse.append(orth2);
        inverse.append(unitCol);

        inverse.inverse();
        inverse.normCol();
        COB.append(inverse);
    }

    for (int i=0;i<numRays;i++){
        pointCOB.generate(3,1);
        pointCOB.multiply(COB.get(i),points.getCol(i));
        pointsCOB.append(pointCOB);
    }
};

int Rays::size(){
    return numRays;
};

void Rays::update(int i,int j,Matrix distances,MatrixList normals,double nSceneIn,Shapes& shapes){
    //setup variables
    d = distances.get(i,j);
    if (std::isinf(d)){
        return;
    }
    normal = normals.getCol(j,i);
    Shape shapeObj = shapes.get(j);
    shape = &shapeObj;
    nShape = shape->refractiveIndex;
    nScene = nSceneIn;
    
    updateRayLocation(i);
    updateRayDirection(i);

    pointsAcc.append(points.getCol(i));
    unitAcc.append(unit.getCol(i));
    distancesAcc.insert(i,d); // we know now distance from previous location
    distancesAcc.append(); // we do not know the distance to the next location
    absorbRay(i);
};

void Rays::updateRayLocation(int i){
    // line equation: p_new = p_old + d * unit
    Matrix p = points.getCol(i);
    Matrix u = unit.getCol(i);
    u.multiply(d);
    p.add(u);
    points.insertCol(p,i);
};

void Rays::updateRayDirection(int i){
    Matrix newUnit;
    flipNormal(i);
    if (shape->mirror){
        newUnit = reflect(i);
    } else {
        newUnit = refract(i);
        inside.insert(i,!inside.get(i));
    }
    unit.insertCol(newUnit,i);
};

void Rays::flipNormal(int i){
    if (cosTheta(i)<0){
        normal.multiply(-1);
    }
}; 

Matrix Rays::refract(int i){
    // v_refract = r*ray + (r*cos(theta1)-cos(theta2)) * n
    // theta1: angle of incidence
    // theta2: angle of refraction
    if (inside.get(i)){
        ratio = nShape/nScene;
    } else {
        ratio = nScene/nShape;
    }
    Matrix vRefract = normal;
    vRefract.multiply(ratio*cosTheta(i)-cosThetaRefract(i));
    Matrix rRay = unit.getCol(i);
    rRay.multiply(ratio);
    vRefract.add(rRay);
    return vRefract;
};

Matrix Rays::reflect(int i){
    // v_reflect = ray + 2 * cos(theta) * n
    // theta: angle of incidence
    Matrix vReflect = normal;
    vReflect.multiply(2*cosTheta(i));
    vReflect.add(unit.getCol(i));
    return vReflect;
};

double Rays::cosThetaRefract(int i){
    // sqrt(1 - r*r * (1 - cosTheta1(l,n)*cosTheta1(l,n)));
    double bracket = 1 - cosTheta(i)*cosTheta(i);
    double radicand = 1 - ratio*ratio*bracket;
    return sqrt(radicand);
};

double Rays::cosTheta(int i){
    // cos(theta) = dot(-n , ray)
    Matrix n = normal;
    n.multiply(-1);
    return n.dot(n,unit.getCol(i));
};

void Rays::absorbRay(int i){
    blocked.insert(i,shape->blocker);
};

void Rays::scaleUnit(){
    distancesAcc.broadcast();
    unitScaled.multiplyPointwise(unitAcc,distancesAcc);
};

void Rays::extend(double len){
    int end = unitAcc.numCols;
    int start = end - unit.numCols;
    for (int i=start;i<end;i++){
        distancesAcc.insert(i,len);
    }
};

Shape Rays::convertToSTL(int res,double radius){
    // res determines number sides on end polygon
    // cylinder end face centres are p0 and p1
    Shape shape;
    shape.points.generate();
    shape.connectivity.generate();
    for (int i=0;i<numRays;i++){
        Matrix p0 = pointsAcc.getCol(i);
        Matrix dir = unitAcc.getCol(i);
        Matrix p1 = unitScaled.getCol(i);
        p1.add(p0);
        Matrix endFace1,endFace2;
        endFace1.ring(res,radius,dir);
        endFace2 = endFace1;
        endFace1.add(p0);
        endFace2.add(p1);
        shape.points.append(endFace1);
        shape.points.append(endFace2);

        // build cm
        Matrix end1,end2,edge1,edge2; // names of triangle sections
        for (int i=0;i<res;i++){
            end1.generate(3,1);
            end1.insert(1,i+2);
            end1.insert(2,i+3);
            
            end2.generate(3,1);
            end2.insert(0,1);
            end2.insert(1,res+i+2);
            end2.insert(2,res+i+3);

            edge1.generate();
            edge1.append(0,i+2);
            edge1.append(1,i+3);
            edge1.append(2,res+i+2);
            
            edge2.generate();
            edge2.append(0,i+3);
            edge2.append(1,res+i+2);
            edge2.append(2,res+i+3);

            if (i==res-1){ // final triangle connects to 1st point
                end1.insert(2,2);
                end2.insert(2,res+2);
                edge1.insert(1,2);
                edge2.insert(0,2);
                edge2.insert(2,res+2);
            }
            shape.connectivity.append(end1);
            shape.connectivity.append(end2);
            shape.connectivity.append(edge1);
            shape.connectivity.append(edge2);
        }
    }
    shape.numPoints = shape.points.numCols;
    shape.numTriangles = shape.connectivity.numCols;
    return shape;
};