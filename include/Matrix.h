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
        std::vector<double> getRow(int i); // outputs row at index i
};

#endif