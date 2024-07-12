#include "AntColony.h" // 包含蚁群算法头文件

int main() {
    int numAnts = 10; // 设置蚂蚁数量
    int numCities = 5; // 设置城市数量
    double alpha = 1.0; // 设置信息素重要性因子
    double beta = 2.0; // 设置启发式因子重要性因子
    double evaporation = 0.5; // 设置信息素挥发率
    double q = 100.0; // 设置信息素强度常数
    int iterations = 100; // 设置迭代次数

    AntColony colony(numAnts, numCities, alpha, beta, evaporation, q); // 创建蚁群算法对象并初始化
    colony.optimize(iterations); // 运行优化算法
    colony.printBestPath(); // 打印最优路径

    return 0; // 返回0，表示程序成功执行
}
