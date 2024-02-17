#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>


class Matrix {
    private:
        std::vector<std::vector<double>> matrix;
        Matrix Rx(); // generate rotation matrix 90deg about x axis
        Matrix Ry(); // generate rotation matrix 90deg about y axis
        bool isXaxis(); // determines whether inputed vector is in line with the x axis
        void rowOperation(int ROW1, int ROW2); //perform guassian elimination via scalar multiple of another row on 3x3
        void rowOperation(int i); // multiply row/col i by scalar
        void swapRows(int ROW1, int ROW2); // row operation in guassian elimination
        void shiftLeft(int n); // move columns left by n values to compress matrix. overwrites earlier cols. leaves outer cols.
        void sliceBack(int cols); // deletes cols columns from the end of the matrix
    public:
        bool constructed; // tells us whether we have called the constructor yet
        void generate(int rows); // default constructor with rows and 0 columns. every matrix starts here.
        void generate(); // shortcut constructor for 3 rows 0 cols
        void generate(int rows,int cols); // constructs empty matrix with specified dimensions.
        void generate(Matrix inMat); // constructs this matrix identical to inMat.
        void fill(double val); // fill entire matrix with items
        void fillInf(); // fill with infinity
        void append(Matrix inMat); // attach matrix to end as new cols assuming numRows same
        void append(double inVal); // assume row vector. Append to end of vector will be a single value
        void append(int row,double inVal); // append to end of vector on specified row
        void append(); // append a column of zeros to matrix
        void pop(int n); // remove n columns from back of matrix
        void insert(int row,int col,double val); // insert value at specified index
        void insert(int col,double val); // insert when matrix is a row vector
        Matrix getRow(int i); // outputs row at index i
        Matrix getCol(int j); // outputs the chosen column as a new matrix
        void insertCol(Matrix col,int j); // replace column at index j with column vector input col
        void zeros(int n); // assume empty row vector, creates n columns of 0
        void range(int n); // assuming empty row vector, punches in values from 0 to n
        void rotate90(Matrix inMat); // rotate all vectors by 90deg in unimportant direction
        void cross(Matrix mat1,Matrix mat2); // cross product mat1 (n cols) cross mat2 (n cols), output this. 3 rows.
        void inverse(); // calculates the inverse of any size matrix
        void inverse2x2(); // calculates the inverse of a 2x2 matrix
        bool detZero(); // returns if determinant is zero for 2x2 matrix
        void inverse3x3(); // calculate the inverse of 3x3 matrix using gaussian elimination
        Matrix identity(); // generates a 3x3 identity matrix
        void replaceRow(Matrix row, int i); // replace row i with row
        void replaceCol(Matrix col,int j); // replace col j with col
        void normCol(); // normalise columns in matrix
        void multiply(Matrix A,Matrix B); // performs matrix multiplication
        void multiply(double val); // multiplies scalar with each element
        void add(Matrix inMat); // add each value in inMat to this matrix, store result in this matrix
        void subtract(Matrix A, Matrix B); // subtract (A-B) each matrix element and store in this.
        double sum(); // adds all matrix elements into a single number
        void transpose(); // works for matrix and vectors
        double dot(Matrix A, Matrix B); // dot product on two vectors (col or row). must have the same numRows each
        double get(int i,int j); // get a value from within matrix
        double get(int i); // if matrix is a vector (row or col), then only index the ith element from the top or from the left
        void reshape(int newRows,int newCols); // row vector into a matrix with specified rows & Cols. assume numElems=cols*rows
        double minRow(int i); // gives the minimum value along row i
        double maxRow(int i); // gives the maximum value along row i
        int minRowIndex(int i); // gives the index of the minimum value along row i
        int maxRowIndex(int i); // gives the index of the maximum value along row i
        double magnitude(); // find magnitude of vector
        void print(); // print matrix to the screen for testing
        int numRows;
        int numCols;
        void slice(); // convert 3D column vector to 2D
};

#endif