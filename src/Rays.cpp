#include "../include/Rays.h"

void Rays::addSources(Sources sources){
    // builds a single instance of rays based on all sources in the scene
    points = sources.points();
    unit = sources.unit();
    numRays = sources.numRays();
    inside.generate(numRays);
    blocked.generate(numRays);
    pointsAcc.generate();
    pointsAcc.append(points);
    unitAcc.generate();
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