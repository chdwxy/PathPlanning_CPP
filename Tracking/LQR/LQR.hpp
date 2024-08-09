//
// Created by chd on 2024/8/9.
//

#ifndef LQR_HPP
#define LQR_HPP

#define EPS 1.0e-4
#include <Eigen/Dense>
#include <vector>
#include <iostream>
using namespace std;
using namespace Eigen;


class LQRControl {
private:
    int N;

public:
    LQRControl(int n);

    MatrixXd calRicatti(MatrixXd A, MatrixXd B, MatrixXd Q, MatrixXd R);
    double lqrControl(vector<double>robot_state,vector<vector<double>>refer_path, double s0, MatrixXd A, MatrixXd B, MatrixXd Q, MatrixXd R);
};


#endif //LQR_HPP
