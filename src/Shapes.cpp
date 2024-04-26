#include "../include/Shapes.h"

void Shapes::importShapes(){
    // shapes structure:
    // number of shapes
    // shape 1 name
    // shape 1 blocker boolean
    // shape 1 mirror boolean
    // shape 1 refractive index
    // shape 1 numpoints
    // shape 1 point 1 x
    // shape 1 point 1 y
    // shape 1 point 1 z
    // shape 1 point 2 x
    // ...
    // shape 1 number of triangles
    // shape 1 triangle 1 point 1
    // shape 1 triangle 1 point 2
    // shape 1 triangle 1 point 3
    // shape 1 triangle 2 point 1
    // ...
    // shape 2 name
    // ...
    std::ifstream shapesFile("shapes.txt");
    std::getline(shapesFile, line);
    numShapes = std::stoi(line);
    for (int i=0;i<numShapes;i++){
        Shape newShape;
        std::getline(shapesFile, line);
        newShape.name = line;
        std::getline(shapesFile, line);
        int blockerInt = std::stoi(line);
        newShape.blocker = static_cast<bool>(blockerInt);
        std::getline(shapesFile, line);
        int mirrorInt = std::stoi(line);
        newShape.mirror = static_cast<bool>(mirrorInt);
        std::getline(shapesFile, line);
        newShape.refractiveIndex = std::stod(line);
        std::getline(shapesFile, line);
        newShape.numPoints = std::stoi(line);
        for (int j=0;j<newShape.numPoints;j++){
            std::getline(shapesFile, line);
            double x = std::stod(line);
            std::getline(shapesFile, line);
            double y = std::stod(line);
            std::getline(shapesFile, line);
            double z = std::stod(line);
            newShape.points.append(x,y,z);
        }
        std::getline(shapesFile, line);
        newShape.numTriangles = std::stoi(line);
        for (int j=0;j<newShape.numTriangles;j++){
            std::getline(shapesFile, line);
            double a = std::stod(line);
            std::getline(shapesFile, line);
            double b = std::stod(line);
            std::getline(shapesFile, line);
            double c = std::stod(line);
            newShape.connectivity.append(a,b,c);
        }
        shapes.push_back(newShape);
    }
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