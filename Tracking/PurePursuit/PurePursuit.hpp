//
// Created by chd on 2024/8/10.
//

#ifndef PUREPURSUIT_HPP
#define PUREPURSUIT_HPP
#include <iostream>
#include <vector>
#include<cmath>
#include <algorithm>

using namespace std;
class PurePursuit {
public:
    double calTargetIndex(vector<double>robot_state, vector<vector<double>>refer_path, double l_d);

    double purePursuitControl(vector<double>robot_state, vector<double>current_ref_point,double l_d, double psi, double L);
};


#endif //PUREPURSUIT_HPP
