#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class Matrix {
    private:
        std::vector<std::vector<double>> matrix;
        int numRows;
        int numCols;
    public:
        Matrix();
        void generate(int numRays); // constructor with 3 rows
};

#endif