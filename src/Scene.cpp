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
        if (rays.areActive()){
            traceStep();
        }
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
    if (distances.constructed){
        for (int i=0;i<rays.numRays;i++){
                int j = distances.minRowIndex(i); // closest shape index
                rays.update(i,j,distances,normals,refractiveIndex,shapes);
        }
        rays.distancesAcc.pop(rays.numRays); // no more intersections. remove what was reserved.
    }
};

void Scene::printRays(){
    std::cout << "Print Rays:" << std::endl;
    std::cout << "Points" << std::endl;
    rays.points.print();
    std::cout << "Unit" << std::endl;
    rays.unit.print();
    std::cout << "PointsAcc" << std::endl;
    rays.pointsAcc.print();
    std::cout << "UnitAcc" << std::endl;
    rays.unitAcc.print();
    std::cout << "distancesAcc" << std::endl;
    rays.distancesAcc.print();
};

void Scene::printShape(){
    std::cout << "Print Shape 0:" << std::endl;
    std::cout << "Points" << std::endl;
    shapes.get(0).points.print();
    std::cout << "Connectivity" << std::endl;
    shapes.get(0).connectivity.print();
};