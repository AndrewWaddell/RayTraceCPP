#include "../include/Rays.h"


void Rays::addSources(Sources sources){
    // builds a single instance of rays based on all sources in the scene
    points = sources.points();
    unit = sources.unit();
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

    for (Matrix unitCol : unit.iterateCol()){
        inverse.generate();
        orth1.rotate90(unitCol);
        orth2.cross(orth1,unitCol);

        inverse.append(orth1);
        inverse.append(orth2);
        inverse.append(unitCol);

        inverse.inverse();
        inverse.normCol();
        COB.append(inverse);
    }

    pointsCOB.generate();
    for (int i=0;i<numRays;i++){
        pointCOB.multiply(COB.get(i),points.getCol(i));
        pointsCOB.append(pointCOB);
    }

};

int Rays::size(){
    return numRays;
};