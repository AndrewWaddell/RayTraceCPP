#include "../include/Shapes.h"

void Shapes::addShape(){
    Shape newShape;
    newShape.generateDefault();
    // newShape.import();
    shapes.push_back(newShape);
};

int Shapes::size(){
    return shapes.size();
};

std::vector<Shape>::iterator Shapes::begin(){
    return shapes.begin();
};

std::vector<Shape>::iterator Shapes::end(){
    return shapes.end();
};

Shape Shapes::get(int i){
    return shapes[i];
};