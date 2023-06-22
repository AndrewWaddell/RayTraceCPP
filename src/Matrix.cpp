#include "../include/Matrix.h"

Matrix::Matrix() {
    //constructor
};

void Matrix::generate(int numColsIn) {
    numRows = 3;
    numCols = numColsIn;
    matrix.resize(numRows, std::vector<double>(numCols));
}