#include "../include/Scene.h"
#include "../include/Rays.h"



Scene::Scene() {
    refractiveIndex = 1;
};

void Scene::generateDefault(){
    sources.addSource();
}