#include "../include/Matrix.h"

Matrix::Matrix() {
    //constructor
};

void Matrix::generate() {
    numRows = 3;
    numCols = 0;
    matrix.resize(numRows, std::vector<double>(numCols));
}

void Matrix::append(Matrix inMat) {
    for (int i=0; i<inMat.numRows;i++) {
        auto inRow = inMat.getRow(i);
        matrix[i].insert(matrix[i].end(), inRow.begin(), inRow.end());
    }
}

std::vector<double> Matrix::getRow(int i) {
    return matrix[i];
}