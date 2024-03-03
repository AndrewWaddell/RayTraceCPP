#include "../include/Matrix.h"


void Matrix::generate(int rows) {
    matrix.clear();
    numRows = rows;
    numCols = 0;
    matrix.resize(numRows);
    constructed = true;
};

void Matrix::generate(){
    generate(3);
};

void Matrix::generate(int rows,int cols){
    generate(rows);
    for (int i=0;i<numRows;i++){
        matrix[i].resize(cols, 0.0);
    }
    numCols = cols;
};

void Matrix::generate(Matrix inMat){
    generate(inMat.numRows,inMat.numCols);
    for (int i=0;i<numRows;i++){
        for (int j=0;j<numCols;j++){
            matrix[i][j] = inMat.get(i,j);
        }
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
    fill(std::numeric_limits<double>::infinity());
};


void Matrix::append(Matrix inMat) {
    if (!constructed){
        generate(inMat);
    } else {

        for (int j=0;j<inMat.numCols;j++){
            numCols += 1;
            for (int i=0;i<inMat.numRows;i++){
                append(i,inMat.get(i,j));
            }
        }
    }
};

void Matrix::append(double inVal) {
    append(0,inVal);
};

void Matrix::append(int row,double inVal) {
    if (!constructed){ // assume row==0
        generate(1,1);
        insert(0,0,inVal);
    } else {
        matrix[row].push_back(inVal);
        if (numCols==0){ // formation of column vector
            numCols = 1;
        } else if (numRows==1){ // extend a row vector
            numCols += 1;
        }

    }
};

void Matrix::append(){
    Matrix z;
    z.zeros(numRows);
    z.transpose();
    append(z);
};

void Matrix::pop(int n){
    numCols-=n;
};

void Matrix::insert(int row,int col,double val){
    matrix[row][col] = val;
};

void Matrix::insert(int i,double val){
    if (numRows==1){
        insert(0,i,val);
    } else if (numCols==1){
        insert(i,0,val);
    }
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
    generate(1,n);
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

    generate(rotated);
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

void Matrix::inverse(){
    if (numRows == 2 && numCols==2){
        inverse2x2();
    } else if (numRows==3 && numCols==3){
        inverse3x3();
    }
    else {
        throw std::runtime_error(
            "build invidual inverse functions for each size");
    }
};

void Matrix::inverse2x2(){
    // for matrix in the form
    // [a b]
    // [c d]

    // result is
    //       [ d -b]
    // det * [-c  a]

    double a = get(0,0);
    double b = get(0,1);
    double c = get(1,0);
    double d = get(1,1);

    double det = (a*d - b*c);

    insert(0,0,d);
    insert(0,1,-b);
    insert(1,0,-c);
    insert(1,1,a);
    multiply(1/det);
};

bool Matrix::detZero(){
    // for matrix in the form
    // [a b]
    // [c d]
    double a = get(0,0);
    double b = get(0,1);
    double c = get(1,0);
    double d = get(1,1);

    double det = (a*d - b*c);
    return (det==0);
};

void Matrix::inverse3x3() {
    append(identity());
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
    if (get(ROW2,ROW2)==0){
        swapRows(ROW1,ROW2);
        return;
    }
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

void Matrix::swapRows(int ROW1, int ROW2){
    Matrix row1 = getRow(ROW1);
    Matrix row2 = getRow(ROW2);
    replaceRow(row1,ROW2);
    replaceRow(row2,ROW1);
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
        col.multiply(1/col.magnitude());
        replaceCol(col,j);
    }
};

void Matrix::transpose(){
    Matrix output;
    output.generate(numCols,numRows);
    for (int i=0;i<numRows;i++){
        for (int j=0;j<numCols;j++){
            output.insert(j,i,matrix[i][j]);
        }
    }
    generate(output);
};

void Matrix::multiply(Matrix A,Matrix B){
    // Matrix multiply: result = A * B
    // number of columns in A must equal number of rows in B
    Matrix output;
    for (int i=0;i<A.numRows;i++){
        Matrix row = A.getRow(i);
        for (int j=0;j<B.numCols;j++){
            Matrix col = B.getCol(j);
            output.append(A.dot(row,col));
        }
    }
    output.reshape(A.numRows,B.numCols);
    generate(output);
};

void Matrix::multiply(double val){
    for (int i=0;i<numRows;i++){
        for (int j=0;j<numCols;j++){
            matrix[i][j] *= val;
        }
    }
};

void Matrix::multiplyPointwise(Matrix A,Matrix B){
    generate(A.numRows,A.numCols);
    for (int i=0;i<numRows;i++){
        for (int j=0;j<numCols;j++){
            double val = A.get(i,j)*B.get(i,j);
            insert(i,j,val);
        }
    }
};

void Matrix::add(Matrix inMat){
    if (inMat.numCols == numCols){
        if (inMat.numRows == numRows){
            for (int i=0;i<numRows;i++){
                for (int j=0;j<numCols;j++){
                    matrix[i][j] += inMat.get(i,j);
                }
            }
        }
    } else if (inMat.numRows == numRows){ // inMat is col vector adding to every column of this
        inMat.broadcast(numCols);
        add(inMat);
    }
    
};

void Matrix::subtract(Matrix A,Matrix B){
    generate(B);
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
    int iteratorLimit;
    if (A.numCols==1){
        iteratorLimit = A.numRows;
    } else {
        iteratorLimit = A.numCols;
    }
    for (int i=0;i<iteratorLimit;i++){
        output += A.get(i) * B.get(i);
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
    for (int i=0;i<newRows*newCols;i++){
        int row = i / newCols;
        int col = i % newCols;
        output.insert(row,col,matrix[0][i]);
    }
    generate(output);
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
    auto iterator = std::min_element(vec.begin(),vec.end());
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

double Matrix::magnitude(){
    return sqrt(dot(*this,*this));
};

void Matrix::print(){
    for (int i=0;i<numRows;i++){
        for (int j=0;j<numCols;j++){
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
};

void Matrix::slice(){
    numRows -= 1;
    matrix[numRows].pop_back();
};

void Matrix::broadcast(int len){
    if (numRows==1){ // if row vector
        transpose();
        broadcastCol(len);
        transpose();
    } else if (numCols==1){ // if col vector
        broadcastCol(len);
    }
};

void Matrix::broadcastCol(int len){
    Matrix col = *this;
    for (int i=1;i<len;i++){
        append(col);
    }
};

void Matrix::broadcast(){
    broadcast(3);
};

void Matrix::ring(int n,double r,Matrix dir){
    generate();
    Matrix orth1,orth2; // basis vectors for space (temporary)
    dir.print();
    orth1.rotate90(dir);
    orth1.print();
    orth2.cross(dir,orth1); // producing 000
    orth2.print();
    orth1.normCol();
    orth2.normCol();
    orth1.print();
    orth2.print();

    double pi = 4*atan(1); // (4 * pi/4)
    for (double theta=0;theta<2*pi;theta+=2*pi/n){
        Matrix temp1 = orth1;
        Matrix temp2 = orth2;
        temp1.multiply(r*cos(theta));
        temp2.multiply(r*sin(theta));
        temp1.add(temp2);
        append(temp1);
    }
};