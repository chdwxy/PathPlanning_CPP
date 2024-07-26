//
// Created by chd on 2024/7/26.
//

#include <iostream>
#include "DP.hpp"

// int main() {
//     DP dp;
//     // dp.PrintGraph();
//     // dp.DPShortest();
//     // dp.PrintMatrix();
//     // dp.ShowResult();
//     // dp.DrawGraph();
//     dp.CreateUDG(); // 构造有向带权图，默认用给定的图
//     dp.PrintGraph(); // 打印整个图
//     dp.DrawGraph(); // 绘制整个图
//     dp.DPShortest(); // 动态规划求最短路径
//     dp.PrintMatrix(); // 打印矩阵
//     dp.ShowResult(); // 显示结果

//     return 0;
// }

int main() {
    DP dp;
    dp.CreateUDG();
    dp.DPShortest();
    dp.PrintMatrix();
    dp.SetStartEnd(0, 99);   // 设置起点为0，终点为3
    dp.PrintShortestPath();
    dp.ShowResult();
    dp.DrawGraph();
    return 0;
}
