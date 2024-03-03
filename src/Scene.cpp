#include "../include/Scene.h"

void Scene::generateDefault(){
    refractiveIndex = 1;
    loopLimit = 1;
    sources.addSource();
    shapes.addShape();
};

void Scene::generateExperiment1(){
    refractiveIndex = 1;
    loopLimit = 1;
    sources.experiment1();
    shapes.addShape();
};

void Scene::trace(){
    rays.addSources(sources);
    for (int i = 0; i < loopLimit; ++i) {
        if (rays.areActive()){
            traceStep();
        }
    }
    rays.extend(1);
    rays.scaleUnit();
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

void Scene::save(){
    // location vectors
    std::ofstream xfile("x.txt");
    for (int j=0;j<rays.pointsAcc.numCols;j++){
        xfile << rays.pointsAcc.get(0,j) << " ";
    }
    std::ofstream yfile("y.txt");
    for (int j=0;j<rays.pointsAcc.numCols;j++){
        yfile << rays.pointsAcc.get(1,j) << " ";
    }
    std::ofstream zfile("z.txt");
    for (int j=0;j<rays.pointsAcc.numCols;j++){
        zfile << rays.pointsAcc.get(2,j) << " ";
    }
    
    // unit vectors
    std::ofstream dxfile("dx.txt");
    for (int j=0;j<rays.unitScaled.numCols;j++){
        dxfile << rays.unitScaled.get(0,j) << " ";
    }
    std::ofstream dyfile("dy.txt");
    for (int j=0;j<rays.unitScaled.numCols;j++){
        dyfile << rays.unitScaled.get(1,j) << " ";
    }
    std::ofstream dzfile("dz.txt");
    for (int j=0;j<rays.unitScaled.numCols;j++){
        dzfile << rays.unitScaled.get(2,j) << " ";
    }

    // shapes

    for (Shape shape : shapes){
        Matrix shapeVecs;
        shapeVecs = shape.convertToVectors();
        for (int j=0;j<shapeVecs.numCols;j++){
            xfile << shapeVecs.get(0,j) << " ";
            yfile << shapeVecs.get(1,j) << " ";
            zfile << shapeVecs.get(2,j) << " ";
            dxfile << shapeVecs.get(3,j) << " ";
            dyfile << shapeVecs.get(4,j) << " ";
            dzfile << shapeVecs.get(5,j) << " ";
        }
    }
};

void Scene::convertToSTL(){
    Shape raysSTL = rays.convertToSTL(4,0.1);
    shapes.addShape(raysSTL);
    // extract cm and points
    // add all shapes
    // combine into megamatrix cm and p
    // index into triangle matrix
    // write to txt file
    // convert txt to stl (can i do this here?)
};