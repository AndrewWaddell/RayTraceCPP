#include "../include/Shapes.h"

void Shapes::addShape(){
    Shape newShape;
    newShape.generateDefault();
    shapes.push_back(newShape);
}