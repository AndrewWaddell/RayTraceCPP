#ifndef SHAPE_H
#define SHAPE_H


class Shape {
    private:
        double refractiveIndex;
        Matrix points; // dimension 1 is x,y,z, dim 2 is each point
        Matrix connectivity; // dimension 1 is each triangle, dim 2 is index for each point
        Matrix pointsCOB; // points in terms of new basis (change of basis)
    public:
        void generateDefault();
};

#endif