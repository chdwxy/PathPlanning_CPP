#ifndef ANT_COLONY_H // 防止头文件重复包含
#define ANT_COLONY_H

#include <vector> // 引入标准库vector类

class AntColony { // 定义蚁群算法类
public:
    AntColony(int numAnts, int numCities, double alpha, double beta, double evaporation, double q); // 构造函数，初始化蚁群算法参数
    void initialize(); // 初始化函数
    void optimize(int iterations); // 优化函数，执行指定次数的迭代
    void printBestPath(); // 打印最优路径
    void plot();

private:
    int numAnts; // 蚂蚁数量
    int numCities; // 城市数量
    double alpha; // 信息素重要性因子
    double beta; // 启发式因子重要性因子
    double evaporation; // 信息素挥发率
    double q; // 信息素强度常数
    std::vector<std::vector<double>> pheromones; // 信息素矩阵
    std::vector<std::vector<double>> distances; // 城市距离矩阵
    std::vector<int> bestPath; // 最优路径
    double bestPathLength; // 最优路径长度

    void initializePheromones(); // 初始化信息素矩阵
    void initializeDistances(); // 初始化距离矩阵
    void moveAnts(); // 移动蚂蚁以构建路径
    void updatePheromones(); // 更新信息素
    double calculatePathLength(const std::vector<int>& path); // 计算路径长度
};

#endif // ANT_COLONY_H
