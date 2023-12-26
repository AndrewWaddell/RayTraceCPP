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

void Matrix::generate(Matrix inMat){
    generate(inMat.numRows,inMat.numCols);
};

void Matrix::fill(double val){
    for (int i=0;i<numRows;i++){
        for (int j=0;j<numCols;j++){
            insert(i,j,val);
        }
    }
};

void Matrix::fillInf(){
    fill(std::numeric_limits<double>::infinity());
}


void Matrix::append(Matrix inMat) {
    if (!constructed){
        generate(inMat.numRows);
    } else {
        for (int i=0; i<inMat.numRows;i++) {
            for (int j=0; j<inMat.numCols;j++){
                append(i,inMat.get(i,j));
            }
        }
        numCols += inMat.numCols;
    }
};

void Matrix::append(double inVal) {
    append(0,inVal);
};

void Matrix::append(int row,double inVal) {
    if (!constructed){
        generate(row);
    }
    matrix[row].push_back(inVal);
};

void Matrix::append(){
    Matrix z;
    z.zeros(numCols);
    z.transpose();
    append(z);
};

void Matrix::construct(Matrix A, Matrix B, Matrix C){
    append(A);
    append(B);
    append(C);
};

void Matrix::insert(int row,int col,double val){
    matrix[row][col] = val;
};

void Matrix::insert(int col,double val){
    insert(0,col,val);
};

Matrix Matrix::getRow(int i) {
    Matrix row;
    row.generate(1);
    for (int j=0;j<numCols;j++){
        row.append(get(i,j));
    }
    return row;
};

Matrix Matrix::getCol(int j){
    Matrix output;
    output.generate(numRows);
    for (int i=0;i<numRows;i++){
        output.append(i,get(i,j));
    }
    return output;
};

void Matrix::insertCol(Matrix col,int j){
    for (int i=0;i<col.numRows;i++){
        insert(i,j,col.get(i));
    }
};

void Matrix::sliceBack(int cols){
    for (int i=0;i<numRows;i++){
        for (int j=0;j<cols;j++){
            matrix[i].pop_back();
        }
    }
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

void Matrix::rotate90(Matrix A){
    // I rotate all vectors about the x-axis
    // however if a vector is the x-axis, then I rotate it about the y-axis
    // output is this matrix

    Matrix rotated;

    if (A.isXaxis()){
        rotated.multiply(Ry(),A);
    } else {
        rotated.multiply(Rx(),A);
    }

    reset(rotated);
};

bool Matrix::isXaxis(){
    // assume input is column vector
    // test for [ 1 0 0 ]
    if (get(0,0)!=0){ // 1
        if (get(1,0)==0){ // 0
            if (get(2,0)==0){ // 0
                return true;
            }
        }
    }
    return false;
};

Matrix Matrix::Rx(){
    // 1 0 0
    // 0 0 -1
    // 0 1 0
    Matrix a;
    a.generate(3,3);
    a.insert(0,0,1);
    a.insert(1,2,-1);
    a.insert(2,1,1);
    return a;
};

Matrix Matrix::Ry(){
    // 0 0 1
    // 0 1 0
    //-1 0 0
    Matrix a;
    a.generate(3,3);
    a.insert(0,2,1);
    a.insert(1,1,1);
    a.insert(2,0,-1);
    return a;
};


void Matrix::cross(Matrix mat1,Matrix mat2){
    generate();
    for (int j=0;j<mat1.numCols;j++){
        // setup
        double cx,cy,cz;
        double ax = mat1.get(0,j);
        double ay = mat1.get(1,j);
        double az = mat1.get(2,j);
        double bx = mat2.get(0,j);
        double by = mat2.get(1,j);
        double bz = mat2.get(2,j);

        // perform operation
        cx = ay*bz - az-by;
        cy = az*bx - ax*bz;
        cz = ax*by - ay*bx;

        // store output
        Matrix col;
        col.generate(3,1);
        col.insert(0,0,cx);
        col.insert(1,0,cy);
        col.insert(2,0,cz);
        append(col);
    }
};

void Matrix::inverse() {
    this->append(identity());

    // matrix is currently in the form
    // [ a b c | 1 0 0 ]
    // [ d e f | 0 1 0 ]
    // [ g h i | 0 0 1 ]

    // zero the following letters
    rowOperation(1,0); // d
    rowOperation(2,0); // g
    rowOperation(2,1); // h
    rowOperation(1,2); // f
    rowOperation(0,2); // c
    rowOperation(0,1); // b
    
    // make the following letters 1
    rowOperation(0); // a
    rowOperation(1); // e
    rowOperation(2); // i
    
    // inverse will be where identity started
    shiftLeft(3);
    sliceBack(3);
    numCols=3;
};

Matrix Matrix::identity() {
    Matrix output;
    output.generate(3,3);
    for (int i = 0; i < 3; i++) {
        output.insert(i,i,1);
    }
    return output;
};

void Matrix::rowOperation(int ROW1, int ROW2){
    // row1 + (scalar)*row2 --> row1
    double scalar = -get(ROW1,ROW2)/get(ROW2,ROW2);
    Matrix row1 = getRow(ROW1);
    Matrix row2 = getRow(ROW2);
    row2.multiply(scalar);
    row1.add(row2);
    replaceRow(row1,ROW1);
};

void Matrix::rowOperation(int i){
    double scalar = 1/get(i,i);
    Matrix row = getRow(i);
    row.multiply(scalar);
    replaceRow(row,i);
};

void Matrix::replaceRow(Matrix row, int i){
    for (int j=0;j<numCols;j++){
        insert(i,j,row.get(0,j));
    }
};

void Matrix::replaceCol(Matrix col,int j){
    for (int i=0;i<numRows;i++){
        insert(i,j,col.get(i,0));
    }
};

void Matrix::normCol(){
    for (int j=0;j<numCols;j++){
        Matrix col = getCol(j);
        double summ = col.sum();
        col.multiply(1/summ);
        replaceCol(col,j);
    }
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

void Matrix::multiply(double val){
    for (int i=0;i<numRows;i++){
        for (int j=0;j<numCols;j++){
            matrix[i][j] *= val;
        }
    }
};

void Matrix::add(Matrix inMat){
    // assume both matrices have the same dimensions
    for (int i=0;i<numRows;i++){
        for (int j=0;j<numCols;j++){
            matrix[i][j] += inMat.get(i,j);
        }
    }
};

void Matrix::subtract(Matrix A,Matrix B){
    generate(A);
    add(B);
    multiply(-1);
    add(A);
};

double Matrix::sum(){
    double output;
    for (int i=0;i<numRows;i++){
        for (int j=0;j<numCols;j++){
            output += matrix[i][j];
        }
    }
    return output;
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

double Matrix::get(int i){
    if (numRows==1){
        return get(0,i);
    }
    if (numCols==1){
        return get(i,0);
    }
    throw std::runtime_error("Must be a vector");
    return 0;
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
    generate(output.numRows);
    append(output);
};

void Matrix::shiftLeft(int n){
    for (int i=0;i<numRows;i++){
        for (int j=0;j<numCols;j++){
            matrix[i][j] = matrix[i][j+n];
        }
    }
};

double Matrix::minRow(int i){
    std::vector<double> vec = matrix[i];
    auto iterator = std::max_element(vec.begin(),vec.end());
    return *iterator;
};

double Matrix::maxRow(int i){
    std::vector<double> vec = matrix[i];
    auto iterator = std::max_element(vec.begin(),vec.end());
    return *iterator;
};

int Matrix::minRowIndex(int i){
    std::vector<double> vec = matrix[i];
    auto iterator = std::min_element(vec.begin(),vec.end());
    return std::distance(vec.begin(),iterator);
};

int Matrix::maxRowIndex(int i){
    std::vector<double> vec = matrix[i];
    auto iterator = std::max_element(vec.begin(),vec.end());
    return std::distance(vec.begin(),iterator);
};

double Matrix::signedArea(){
    // calculate using determinant formula
    // also known as a ccw formula
    return determinant2D();
};

double Matrix::determinant2D(){
    double ax = get(0,0);
    double bx = get(0,1);
    double cx = get(0,2);
    double ay = get(1,0);
    double by = get(1,1);
    double cy = get(1,2);
    return (bx - ax)*(cy - ay) - (cx - ax)*(by - ay);
};

double Matrix::cosTheta(){
    // consider vectors A, B. We know:
    // dot(A,B) = |A|*|B|*cos(theta)
    // cos(theta) = dot(A,B) / (|A|*|B|)
    // 2D problem
    Matrix A; // A is from E to D
    Matrix B; // B is from E to F
    Matrix D = getCol(0);
    Matrix E = getCol(1);
    Matrix F = getCol(2);
    A.subtract(D,E);
    B.subtract(F,E);
    A.insert(2,0,0); // ignore 3rd dimension
    B.insert(2,0,0); // ignore 3rd dimension
    return dot(A,B) / (A.magnitude()*B.magnitude());
};

double Matrix::magnitude(){
    double radicand = 0;
    for (int i=0;i<numRows;i++){
        radicand += get(i);
    }
    return sqrt(radicand);
};

void Matrix::print(){
    for (int i=0;i<numRows;i++){
        for (int j=0;j<numCols;j++){
            std::cout << matrix[i][j];
        }
        std::cout << std::endl;
    }
};