//
// Created by chh3213 on 2022/11/25.
//

#ifndef NORMALIZEANGLE_HPP
#define NORMALIZEANGLE_HPP

#define PI 3.1415926

/**
 * 角度归一化
 * @param angle
 * @return
 */
double normalizeAngle(double angle) {
    while(angle>PI){
        angle-=2.0*PI;
    }
    while(angle<-PI){
        angle+=2.0*PI;
    }
    return angle;
}
#endif //NORMALIZEANGLE_HPP
