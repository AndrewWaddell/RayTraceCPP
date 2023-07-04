#include "../include/Matrix.h"

Matrix::Matrix() {
    //constructor
};

void Matrix::generate() {
    numRows = 3;
    numCols = 0;
    matrix.resize(numRows, std::vector<double>(numCols));
};


void Matrix::append(Matrix inMat) {
    for (int i=0; i<inMat.numRows;i++) {
        auto inRow = inMat.getRow(i);
        matrix[i].insert(matrix[i].end(), inRow.begin(), inRow.end());
    }
};

std::vector<double> Matrix::getRow(int i) {
    return matrix[i];
};

Matrix Matrix::getCol(int i){
    // outputs the chosen column as a new matrix
};

void Matrix::zeros(int n) {
    matrix[0].resize(n, 0.0);
};

void Matrix::range(int n) {
    matrix.resize(1, std::vector<double>(n));
    for (int i=0;i<n;i++) {
        matrix[0].push_back(i);
    }
};

void Matrix::rotate90(Matrix inMat){
    // I rotate all vectors about the x-axis
    // however if a vector is the x-axis, then I rotate it about the y-axis
    // output is this matrix

    //function

};

void Matrix::cross(Matrix mat1,Matrix mat2){
    // input mat, mat2, output is this
};

void Matrix::inverse() {
    // overwrites existing matrix
};

void Matrix::normCol(){
    // overwrites existing matrix
};

MatrixList Matrix::iterateCol(){
    MatrixList output;
    for (int i=0;i<numCols;i++){
        output.append(getCol(i));
    }
    return output;
};

void Matrix::multiply(Matrix mat1,Matrix mat2){
    // Proper matrix multiply result = A * B
    // number of columns in A must equal number of rows in B
    // output is this matrix, resized
};
