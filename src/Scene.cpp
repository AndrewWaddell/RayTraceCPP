#include "../include/Scene.h"
#include "../include/Rays.h"



Scene::Scene() {
    refractiveIndex = 1;
    loopLimit = 1;
};

void Scene::generateDefault(){
    sources.addSource();
    shapes.addShape();
}

void Scene::trace(){
    rays.addSources(sources);
    for (int i = 0; i < loopLimit; ++i) {
        rays.areActive() ? traceStep() : void();
    }
}