#ifndef SHAPES_H
#define SHAPES_H

#include <vector>
#include "Shape.h"
// #include "MatrixList.h"

class Shapes {
    private:
        std::vector<Shape> shapes;
    public:
        void addShape();
        Shape get(int i); // return shape i
        int size(); // return numShapes
        auto begin(); // vector property
        auto end(); // vector property
};

#endif