#include "../include/Rays.h"

void Rays::addSources(Sources sources){
    // take all of the sources and combine them into a rays object

    // run algorithm

    blocked.generate(numrays);

};

bool Rays::areActive(){
    // if there are any rays left that haven't hit a blocker, sensor or boundary,
    // then return true
    // once all rays have finished their journey, return false
    return blocked.anyFalse();
};