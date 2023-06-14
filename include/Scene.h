#ifndef SCENE_H
#define SCENE_H

#include "../include/Rays.h"
#include "../include/Sources.h"

class Scene {
    private:
        Rays rays;
        Sources sources;
        double refractiveIndex; // condition of scene medium
    public:
        Scene();
};

#endif