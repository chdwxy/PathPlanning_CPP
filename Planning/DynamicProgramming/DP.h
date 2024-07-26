//
// Created by chd on 2024/7/26.
//

#ifndef DP_H // 防止头文件重复包含
#define DP_H

#pragma once
#include <iostream>
#include <vector>
#include <stack> 
#include <SFML/Graphics.hpp> 
using namespace std;

#define VertexType int    // 图中顶点的数据类型
#define VRType int        // 对于无权图，用 1 或 0 表示是否相邻；对于带权图，表示权值
constexpr auto INFIN = 9999; // 定义无穷大的数值
constexpr auto MAX_VERTEX_NUM = 100; // 顶点的最大个数
// constexpr auto Swidth = 1200;
// constexpr auto Sheight = 800;

// class MGraph // 图的顺序存储结构
// {
// public:
//     MGraph();
//     VertexType vexs[MAX_VERTEX_NUM]; // 一维数组，存储图中顶点数据
//     VRType d[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // 二维数组，记录顶点之间的权值
//     int vexnum = 13; // 记录图的顶点数
//     int arcnum = 0; // 记录图的弧（或边）数

//     int widthSide = 50; // 两边留的距离
//     int widthDis = (Swidth - widthSide * 2) / 5; // 间隔
//     int arr[MAX_VERTEX_NUM][2]; // 顶点的坐标
// };
struct MGraph {
    int vexs[MAX_VERTEX_NUM];  // 顶点列表
    int d[MAX_VERTEX_NUM][MAX_VERTEX_NUM];  // 邻接矩阵
    int vexnum;  // 顶点数量
    int edgnum;  // 边数量
    int arr[MAX_VERTEX_NUM][2];  // 绘图用的顶点位置

    MGraph() {
        vexnum = MAX_VERTEX_NUM;
        edgnum = 0;
        for (int i = 0; i < MAX_VERTEX_NUM; ++i) {
            vexs[i] = i;  // 初始化顶点
            for (int j = 0; j < MAX_VERTEX_NUM; ++j) {
                d[i][j] = (i == j) ? 0 : INFIN;  // 自己到自己的距离为0，其余初始化为无穷大
            }
        }
    }
};

// class DP
// {
// public:
//     DP(); // 默认用给定的图，在这里初始化
//     int LocateVex(VertexType v); // 判断顶点在二维数组中的位置，手动建图时才会用到
//     void CreateUDG(); // 构造有向带权图，默认用给定的图
//     void PrintGraph(); // 打印整个图
//     void DrawGraph(); // 绘制整个图
//     void DPShortest(); // 动态规划求最短路径
//     void PrintMatrix(); // 打印矩阵
//     void ShowResult(); // 显示结果

// public:
//     MGraph G; // 创建图的对象
//     int D[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // 存储顶点间的最小路径
//     int P[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // 记录路径
// };

class DP {
public:
    DP();

    void CreateUDG();
    void PrintGraph();
    void DrawGraph();
    void DPShortest();
    void PrintMatrix();
    void ShowResult();
    void SetStartEnd(int start, int end);
    void PrintShortestPath();

private:
    MGraph G;
    int D[MAX_VERTEX_NUM][MAX_VERTEX_NUM];  // 距离矩阵
    int P[MAX_VERTEX_NUM][MAX_VERTEX_NUM];  // 前驱矩阵
    int Swidth = 800;  // 绘图窗口宽度
    int Sheight = 600;  // 绘图窗口高度
    int startVertex;
    int endVertex;

    int LocateVex(int v);
    void InitWeights();
    vector<int> GetShortestPath(int start, int end);
};


#endif //DP_H