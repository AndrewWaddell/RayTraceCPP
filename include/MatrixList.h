#ifndef MATRIXLIST_H
#define MATRIXLIST_H

#include <vector>
#include "Matrix.h"

class MatrixList {
    private:
        std::vector<std::vector<Matrix>> matrices;
    public:
        Matrix get(int i); // index matrix at index i
        void append(Matrix inMat);
        auto begin(); // vector property
        auto end(); // vector property
};


#endif