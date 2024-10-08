#include "AntColony.hpp"
#include <iostream>
#include <cmath>
#include <limits>
#include <algorithm>
#include <random>
#include "../../matplotlibcpp.h"

namespace plt = matplotlibcpp;

AntColony::AntColony(int numAnts, int numCities, double alpha, double beta, double evaporation, double q)
    : numAnts(numAnts), numCities(numCities), alpha(alpha), beta(beta), evaporation(evaporation), q(q) {
    initialize();
}

void AntColony::initialize() {
    initializePheromones();
    initializeDistances();
    bestPathLength = std::numeric_limits<double>::max();
}

void AntColony::initializePheromones() {
    pheromones.resize(numCities, std::vector<double>(numCities, 1.0));
}

void AntColony::initializeDistances() {
    distances.resize(numCities, std::vector<double>(numCities));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(1.0, 100.0);

    for (int i = 0; i < numCities; ++i) {
        for (int j = i + 1; j < numCities; ++j) {
            double distance = dis(gen);
            distances[i][j] = distances[j][i] = distance;
        }
    }
}

void AntColony::optimize(int iterations) {
    for (int iter = 0; iter < iterations; ++iter) {
        moveAnts();
        updatePheromones();
        plot();
    }
}

void AntColony::moveAnts() {
    std::vector<int> path(numCities);
    std::iota(path.begin(), path.end(), 0);

    for (int k = 0; k < numAnts; ++k) {
        std::random_shuffle(path.begin(), path.end());
        double pathLength = calculatePathLength(path);

        if (pathLength < bestPathLength) {
            bestPath = path;
            bestPathLength = pathLength;
        }
    }
}

double AntColony::calculatePathLength(const std::vector<int>& path) {
    double length = 0.0;
    for (int i = 0; i < numCities - 1; ++i) {
        length += distances[path[i]][path[i + 1]];
    }
    length += distances[path[numCities - 1]][path[0]];
    return length;
}

void AntColony::updatePheromones() {
    for (auto& row : pheromones) {
        for (auto& pheromone : row) {
            pheromone *= (1.0 - evaporation);
        }
    }

    for (int i = 0; i < numCities - 1; ++i) {
        int from = bestPath[i];
        int to = bestPath[i + 1];
        pheromones[from][to] += q / bestPathLength;
        pheromones[to][from] += q / bestPathLength;
    }
    int from = bestPath[numCities - 1];
    int to = bestPath[0];
    pheromones[from][to] += q / bestPathLength;
    pheromones[to][from] += q / bestPathLength;
}

void AntColony::printBestPath() {
    std::cout << "Best Path: ";
    for (int city : bestPath) {
        std::cout << city << " ";
    }
    std::cout << "\nBest Path Length: " << bestPathLength << std::endl;
}


void AntColony::plot() {
    std::vector<double> x(numCities);
    std::vector<double> y(numCities);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 100.0);

    for (int i = 0; i < numCities; ++i) {
        x[i] = dis(gen);
        y[i] = dis(gen);
    }

    plt::clf();
    plt::plot(x, y, "ro");

    for (int i = 0; i < numCities; ++i) {
        for (int j = 0; j < numCities; ++j) {
            if (i != j) {
                plt::plot({x[i], x[j]}, {y[i], y[j]}, "b-");
            }
        }
    }

    std::vector<double> bestX(numCities);
    std::vector<double> bestY(numCities);
    for (int i = 0; i < numCities; ++i) {
        bestX[i] = x[bestPath[i]];
        bestY[i] = y[bestPath[i]];
    }

    plt::plot(bestX, bestY, "g-");
    plt::pause(0.01);
}