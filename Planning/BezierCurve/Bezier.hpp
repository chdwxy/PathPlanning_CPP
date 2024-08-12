//
// Created by chd on 2024/8/12.
//

#ifndef BEZIER_HPP
#define BEZIER_HPP

#include <iostream>
#include <Eigen/Dense>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;
using namespace Eigen;

double factorial(int n);

Vector2d bezierCommon(vector<Vector2d>Ps,  double t);

Vector2d bezierRecursion(vector<Vector2d>Ps, double t);

#endif //BEZIER_HPP
