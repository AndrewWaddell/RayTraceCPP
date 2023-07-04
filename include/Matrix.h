#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include "../include/MatrixList.h"

class Matrix {
    private:
        std::vector<std::vector<double>> matrix;
        int numRows;
        int numCols;
    public:
        Matrix();
        void generate(); // constructor with 3 rows 0 cols
        void append(Matrix inMat); // attach matrix to end as new cols assuming numRows same
        std::vector<double> getRow(int i); // outputs row at index i, exists because matrix is private
        Matrix getCol(int i);
        void zeros(int n); // assume empty row vector, creates n columns of 0
        void range(int n); // assuming empty row vector, punches in values from 0 to n
        void rotate90(Matrix inMat); // rotate all vectors by 90deg in unimportant direction
        void cross(Matrix mat1,Matrix mat2); // cross product mat1 cross mat2
        void inverse(); // calculate the inverse of 3x3 matrix
        void normCol(); // normalise columns in matrix
        MatrixList iterateCol(); // reorganise into matrixList of columns for range based looping
        void multiply(Matrix mat1,Matrix mat2); // performs matrix multiplication
};

#endif