#ifndef SCENE_H
#define SCENE_H

#include "../include/Rays.h"
#include "../include/Sources.h"
#include "../include/Shapes.h"


class Scene {
    private:
        Rays rays;
        Sources sources;
        Shapes shapes;
        double refractiveIndex; // property of scene medium
    public:
        Scene();
        void generateDefault();
};

#endif