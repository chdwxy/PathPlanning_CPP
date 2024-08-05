#include "AntColony.hpp"

int main() {
    int numAnts = 10;
    int numCities = 5;
    double alpha = 1.0;
    double beta = 2.0;
    double evaporation = 0.5;
    double q = 100.0;
    int iterations = 100;

    AntColony colony(numAnts, numCities, alpha, beta, evaporation, q);
    colony.optimize(iterations);
    colony.printBestPath();

    // cv::waitKey(0);

    return 0;
}
