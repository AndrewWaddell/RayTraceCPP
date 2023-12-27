#include "../include/Scene.h"

void Scene::generateDefault(){
    refractiveIndex = 1;
    loopLimit = 1;
    sources.addSource();
    shapes.addShape();
};

void Scene::trace(){
    rays.addSources(sources);
    for (int i = 0; i < loopLimit; ++i) {
        rays.areActive() ? traceStep() : void();
    }
};

void Scene::traceStep(){
    // executes a single step within the trace. All rays bounce to the next shape.
    rays.createNewBasis();
    for (Shape shape : shapes) {
        shape.changeOfBasis(rays);
        if (shape.traceLowRes(rays)){
            shape.traceDistance(rays);
            distances.append(shape.shortestDistances(rays));
            normals.append(shape.normals);
        }
    }
    for (int i=0;i<rays.numRays;i++){
        int j = distances.minRowIndex(i); // closest shape index
        rays.update(i,j,distances,normals,refractiveIndex,shapes);
    }
};