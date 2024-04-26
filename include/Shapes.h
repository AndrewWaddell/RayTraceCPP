#ifndef SHAPES_H
#define SHAPES_H

#include <vector>
#include "Shape.h"
#include <fstream>

class Shapes {
    private:
        std::vector<Shape> shapes;
        std::string line; // general use string for import
    public:
        void importShapes(); // import shape from txt file generated from python GUI
        void addShape(Shape shape);
        Shape get(int i); // return shape i
        int numShapes;
        std::vector<Shape>::iterator begin(); // vector property
        std::vector<Shape>::iterator end(); // vector property
};

#endif