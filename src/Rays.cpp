#include "../include/Rays.h"

void Rays::addSources(Sources sources){
    // builds a single instance of rays based on all sources in the scene

    numrays = 0;
    while (sources.bucketNotEmpty()) {
        numrays += sources.grabSource().numrays;
    }
    

    blocked.generate(numrays);

};

bool Rays::areActive(){
    // if there are any rays left that haven't hit a blocker, sensor or boundary,
    // then return true
    // once all rays have finished their journey, return false
    return blocked.anyFalse();
};