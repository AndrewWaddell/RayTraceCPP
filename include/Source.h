#ifndef SOURCE_H
#define SOURCE_H

#include "Matrix.h"
#include "fstream"
#include "string"

class Source {
    private:
        std::string name;
        Matrix points;
        Matrix unit;
        int numRays;
        int pointsCount; // how many times have we appended the first column
        bool firstColumn(); // are we inserting the first column of data
    public:
        void setName(std::string nameIn);
        void setNumRays(int numraysIn);
        void appendPoints(int dim,double val);
        void generateDefault();
        void generateSingleRay();
        void generateSquare(Matrix loc, Matrix dir,double width, double density);
        int getNumRays();
        Matrix getPoints();
        Matrix getUnit();
};

#endif