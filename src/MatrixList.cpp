#include "../include/MatrixList.h"

auto MatrixList::begin(){
    return matrices.begin();
};

auto MatrixList::end(){
    return matrices.end();
};

void MatrixList::append(Matrix inMat){
    matrices.push_back(inMat);
};

Matrix MatrixList::get(int i){
    return matrices[i];
};