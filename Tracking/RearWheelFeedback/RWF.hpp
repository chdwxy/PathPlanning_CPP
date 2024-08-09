//
// Created by chd on 2024/8/10.
//

#ifndef RWF_HPP
#define RWF_HPP
#include <iostream>
#include <vector>
#include<cmath>
#include <algorithm>
using namespace std;

#define PI 3.1415926

class RearWheelFeedback {
private:
    double Kpsi,  K2,  L ;//利亚普诺夫相关系数，最后一个为机器人轴距
public:
    RearWheelFeedback(double Kpsi, double K2, double L);
    static double normalizeAngle(double angle);
    double rearWheelFeedbackControl(vector<double>robot_state, double e, double k, double ref_psi);

};


#endif //RWF_HPP
