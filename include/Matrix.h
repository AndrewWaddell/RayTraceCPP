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
        void generate(); // constructor with 3 rows 0 cols
        void append(Matrix inMat); // attach matrix to end as new cols assuming numRows same
        std::vector<double> getRow(int i); // outputs row at index i, exists because matrix is private
        void zeros(int n); // assume empty row vector, creates n columns of 0
        void range(int n); // assuming empty row vector, punches in values from 0 to n
};

#endif