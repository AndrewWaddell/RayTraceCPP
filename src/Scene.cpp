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

void Scene::saveRays(){
    std::ofstream pointsfile("points.txt");
    for (int i=0;i<rays.points.numRows;i++){
        for (int j=0;j<rays.points.numCols;j++){
            pointsfile << rays.points.get(i,j) << " ";
        }
        pointsfile << std::endl;
    }
    std::ofstream unitfile("unit.txt");
    for (int i=0;i<rays.unit.numRows;i++){
        for (int j=0;j<rays.unit.numCols;j++){
            unitfile << rays.unit.get(i,j) << " ";
        }
        unitfile << std::endl;
    }
    std::ofstream pointsaccfile("pointsacc.txt");
    for (int i=0;i<rays.pointsAcc.numRows;i++){
        for (int j=0;j<rays.pointsAcc.numCols;j++){
            pointsaccfile << rays.pointsAcc.get(i,j) << " ";
        }
        pointsaccfile << std::endl;
    }
    std::ofstream unitaccfile("unitacc.txt");
    for (int i=0;i<rays.unitAcc.numRows;i++){
        for (int j=0;j<rays.unitAcc.numCols;j++){
            unitaccfile << rays.unitAcc.get(i,j) << " ";
        }
        unitaccfile << std::endl;
    }
    std::ofstream distancesAccfile("distancesAcc.txt");
    for (int i=0;i<rays.distancesAcc.numRows;i++){
        for (int j=0;j<rays.distancesAcc.numCols;j++){
            distancesAccfile << rays.distancesAcc.get(i,j) << " ";
        }
        distancesAccfile << std::endl;
    }
};