#include "../include/Scene.h"
#include "../include/Rays.h"


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
    
};