#include "../include/BoolArray.h"

bool BoolArray::anyFalse(){
    found = false;
    for (bool val : vals) {
        if (!val){
            found = true;
        }
    }
    return found;
};

void BoolArray::generate(int size) {
    vals.resize(size, false);
};

bool BoolArray::get(int i){
    return vals[i];
};

void BoolArray::insert(int i,bool val){
    vals[i] = val;
};
