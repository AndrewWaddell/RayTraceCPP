#include "../include/Shapes.h"

void Shapes::addShape(){
    Shape newShape;
    newShape.generateDefault();
    shapes.push_back(newShape);
};

int Shapes::size(){
    return shapes.size();
};

auto Shapes::begin(){
    return shapes.begin();
};

auto Shapes::end(){
    return shapes.end();
};

Shape Shapes::get(int i){
    return shapes[i];
};