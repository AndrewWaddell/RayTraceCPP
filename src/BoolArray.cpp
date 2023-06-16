#include "../include/BoolArray.h"

bool BoolArray::anyFalse(){
    found = false;
    for (bool val : vals) {
        val ? void() : found = true;
    }
    return found;
};

void BoolArray::generate(int size) {
    vals.resize(size, false);
};


