#include "../include/Matrix.h"

Matrix::Matrix() {
    //constructor
};


void Matrix::generate(){
    generate(3);
}

void Matrix::generate(int rows) {
    numRows = rows;
    numCols = 0;
    matrix.resize(numRows, std::vector<double>(numCols));
    constructed = true;
};

void Matrix::fill(double val){
    // implementation
};

void Matrix::fillInf(){
    fill(1/0.0);
}


void Matrix::append(Matrix inMat) {
    if (!constructed){
        generate(inMat.numRows);
    }
    for (int i=0; i<inMat.numRows;i++) {
        auto inRow = inMat.getRow(i);
        matrix[i].insert(matrix[i].end(), inRow.begin(), inRow.end());
    }
};

void Matrix::append(double inVal) {
    if (!constructed){
        generate(1);
    }
    matrix[0].push_back(inVal);
};

void Matrix::append(int row,double inVal) {
    if (!constructed){
        generate(row);
    }
    matrix[row].push_back(inVal);
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

MatrixList Matrix::iterateRow(){
    MatrixList output;
    Matrix row;
    for (std::vector<double> rowVec : matrix){
        // turn vector into matrix
        row.generate(1);
        for (double val : rowVec){
            row.append(val);
        }
        // turn row into column
        row.transpose();
        output.append(row.getCol(0));
    }
    return output;
};

void Matrix::transpose(){
    Matrix output;
    if (numRows==1){ // make row into column
        output.generate(numCols);
        for (int i=0;i<numCols;i++){
            output.append(i,matrix[0][i]);
        }
    }
    else if (numCols==1) { // make column into row
        output.generate(1);
        for (int i=0;i<numRows;i++){
            output.append(matrix[i][0]);
        }
    }
    else { // matrix
        output.generate(numRows,numCols);
        for (Matrix col : iterateCol()){
            // do this later
        }
    }
    generate(numCols,numRows);
    append(output);
};

void Matrix::multiply(Matrix A,Matrix B){
    // Matrix multiply: result = A * B
    // number of columns in A must equal number of rows in B
    // output is this matrix, resized to rows from A and cols from B
    Matrix output;
    output.generate(1);
    for (Matrix row : A.iterateRow()) {
        for (Matrix col : B.iterateCol()) {
            output.append(output.dot(row,col));
        }
    }
    output.reshape(B.numCols);
};

double Matrix::dot(Matrix A, Matrix B){
    double output = 0;
    for (int i=0;i<A.numRows;i++){
        output += A.get(i,0) * A.get(i,0);
    }
    return output;
};

double Matrix::get(int i, int j){
    return matrix[i][j];
};

void Matrix::reshape(int newCols){
    for (int i=0;i<numCols;i++){
        
    }
};

