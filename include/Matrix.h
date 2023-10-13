#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include "../include/MatrixList.h"

class Matrix {
    private:
        std::vector<std::vector<double>> matrix;
        int numRows;
        int numCols;
        bool constructed; // tells us whether we have called the constructor yet
        void reset(Matrix output); // void function output, so reset matrix as output
    public:
        Matrix();
        void generate(); // constructor with 3 rows 0 cols
        void generate(int rows); // constructor with inputted rows and 0 columns
        void generate(int rows,int cols); // constructs empty matrix with specified dimensions.
        void fill(double val); // fill entire matrix with items
        void fillInf(); // fill with infinity
        void append(Matrix inMat); // attach matrix to end as new cols assuming numRows same
        void append(double inVal); // assume row vector. Append to end of vector will be a single value
        void append(int row,double inVal); // append to end of vector on specified row
        void insert(int row,int col,double val); // insert value at specified index
        Matrix getRow(int i); // outputs row at index i
        Matrix getCol(int j); // outputs the chosen column as a new matrix
        void sliceBack(int cols); // deletes cols columns from the end of the matrix
        void insertCol(Matrix col,int i); // replace column at index i with column vector input col
        void zeros(int n); // assume empty row vector, creates n columns of 0
        void range(int n); // assuming empty row vector, punches in values from 0 to n
        void rotate90(Matrix inMat); // rotate all vectors by 90deg in unimportant direction
        void cross(Matrix mat1,Matrix mat2); // cross product mat1 cross mat2
        void inverse(); // calculate the inverse of 3x3 matrix using gaussian elimination
        Matrix identity(); // generates a 3x3 identity matrix
        void rowOperation(int ROW1, int ROW2); //perform guassian elimination via scalar multiple of another row on 3x3
        void rowOperation(int i); // multiply row/col i by scalar
        void replaceRow(Matrix row, int i); // replace row i with row
        void normCol(); // normalise columns in matrix
        MatrixList iterateCol(); // reorganise into matrixList of columns for range based looping
        MatrixList iterateRow(); // same as above but returns matrix rows as column vectors in matrixlist
        void multiply(Matrix A,Matrix B); // performs matrix multiplication
        void multiply(double val); // multiplies scalar with each element
        void add(Matrix inMat); // add each value in inMat to this matrix, store result in this matrix
        void transpose(); // works for matrix and vectors
        double dot(Matrix A, Matrix B); // dot product on two column vectors. must have the same numRows each
        double get(int i,int j); // get a value from within matrix
        void reshape(int newRows,int newCols); // row vector into a matrix with specified rows & Cols. assume numElems=cols*rows
};

#endif