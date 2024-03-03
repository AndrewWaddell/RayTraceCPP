#ifndef SHAPES_H
#define SHAPES_H

#include <vector>
#include "Shape.h"

class Shapes {
    private:
        std::vector<Shape> shapes;
    public:
        void addShape();
        void addShape(Shape shape);
        Shape get(int i); // return shape i
        int size(); // return numShapes
        std::vector<Shape>::iterator begin(); // vector property
        std::vector<Shape>::iterator end(); // vector property
};

#endif