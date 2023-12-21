#ifndef MATRIXLIST_H
#define MATRIXLIST_H

#include <vector>
#include "Matrix.h"

class MatrixList {
    private:
        std::vector<Matrix> matrices;
    public:
        Matrix get(int i); // index matrix at index i
        Matrix getCol(int i, int j); // get col j of matrix i
        void append(Matrix inMat); // add new matrix to the list
        auto begin(); // vector property
        auto end(); // vector property
};


#endif