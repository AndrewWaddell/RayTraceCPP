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

void Matrix::generate(int rows,int cols){
    generate(rows);
    for (int i;i<rows;i++){
        matrix[i].resize(cols, 0.0);
    }
};

void Matrix::fill(double val){
    for (int i=0;i<numRows;i++){
        for (int j=0;j<numCols;j++){
            insert(i,j,val);
        }
    }
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
    numCols += inMat.numCols;
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

void Matrix::insert(int row,int col,double val){
    matrix[row][col] = val;
}

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
    output.generate(numCols,numRows);
    for (int i=0;i<numRows;i++){
        for (int j=0;j<numCols;j++){
            output.insert(j,i,matrix[i][j]);
        }
    }
    reset(output);
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
    output.reshape(A.numRows,B.numCols);
    reset(output);
};

double Matrix::dot(Matrix A, Matrix B){
    double output = 0;
    for (int i=0;i<A.numRows;i++){
        output += A.get(i,0) * B.get(i,0);
    }
    return output;
};

double Matrix::get(int i, int j){
    return matrix[i][j];
};

void Matrix::reshape(int newRows,int newCols){
    // example output for 3 cols:
    //   i: 0 1 2 3 4 5
    // row: 0 0 0 1 1 1
    // col: 0 1 2 0 1 2
    Matrix output;
    output.generate(newRows,newCols);
    for (int i=0;i<numCols;i++){
        int row = (int) i/numCols;
        int col = i - (row*numCols);
        output.insert(row,col,matrix[0][i]);
    }
    reset(output);
};

void Matrix::reset(Matrix output){
    generate(output.numRows,output.numCols);
    append(output);
}

