#include "../include/Scene.h"
#include "../include/gnuplot_i.hpp"


int main() {
    
    Scene opticalBench;
    opticalBench.generateDefault(); // initialise default test case
    opticalBench.trace();
    opticalBench.printRays();
    opticalBench.printShape();

    Gnuplot plotter;

    // Set plot options
    plotter.cmd("set title '3D Vector Plot'");
    plotter.cmd("set xlabel 'X'");
    plotter.cmd("set ylabel 'Y'");
    plotter.cmd("set zlabel 'Z'");

    // Define 3D vector data in the format expected by plot_xyz
    std::vector<double> x{1.0, 4.0};
    std::vector<double> y{2.0, 5.0};
    std::vector<double> z{3.0, 6.0};

    // Plot 3D vectors using plot_xyz
    plotter.plot_xyz(x, y, z, "Vectors");
    
    return 0;
};