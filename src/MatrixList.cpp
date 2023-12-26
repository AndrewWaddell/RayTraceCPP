#include "../include/MatrixList.h"

std::vector<Matrix>::iterator MatrixList::begin(){
    return matrices.begin();
};

std::vector<Matrix>::iterator MatrixList::end(){
    return matrices.end();
};

void MatrixList::append(Matrix inMat){
    matrices.push_back(inMat);
};

Matrix MatrixList::get(int i){
    return matrices[i];
};

Matrix MatrixList::getCol(int i,int j){
    return get(i).getCol(j);
};