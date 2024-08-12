//
// Created by chd on 2024/8/12.
//

#ifndef BSPLINE_HPP
#define BSPLINE_HPP
#include <iostream>
#include <Eigen/Dense>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;
using namespace Eigen;

double baseFunction(int i, int k, double u, vector<double>node_vector);

vector<double> u_quasi_uniform(int n,int k);


vector<double> u_piecewise_B_Spline(int n,int k);



#endif //BSPLINE_HPP
