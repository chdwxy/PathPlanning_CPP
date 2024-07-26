//
// Created by chd on 2024/7/26.
//

#include "DP.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

DP::DP() {
    CreateUDG();
    startVertex = 0;  // 默认起点
    endVertex = 1;    // 默认终点
}

int DP::LocateVex(int v) {
    for (int i = 0; i < G.vexnum; ++i) {
        if (G.vexs[i] == v) return i;
    }
    return -1;
}

void DP::CreateUDG() {
    InitWeights();

    // 设置顶点的二维坐标
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            int index = i * 10 + j;
            G.arr[index][0] = j * 50 + 50; // x坐标
            G.arr[index][1] = i * 50 + 50; // y坐标
        }
    }
}

void DP::InitWeights() {
    srand(static_cast<unsigned int>(time(0)));

    // for (int i = 0; i < MAX_VERTEX_NUM; ++i) {
    //     for (int j = 0; j < MAX_VERTEX_NUM; ++j) {
    //         if (i != j) {
    //             // 在10x10的栅格中，只允许上下左右四个方向的边
    //             int xi = i / 10, yi = i % 10;
    //             int xj = j / 10, yj = j % 10;
    //             if ((abs(xi - xj) == 1 && yi == yj) || (abs(yi - yj) == 1 && xi == xj)) {
    //                 G.d[i][j] = rand() % 10 + 1; // 权重在1到10之间
    //                 cout<<"节点权重为"<<G.d[i][j]<<endl;
    //             } else {
    //                 G.d[i][j] = INFIN;
    //                 cout<<"节点权重为"<<G.d[i][j]<<endl;
    //             }
    //         }
    //     }
    // }
    for (int i = 0; i < MAX_VERTEX_NUM; ++i) {
        int xi = i / 10, yi = i % 10;

        // 设置右边相邻节点的权重
        if (yi + 1 < 10) {
            int j = i + 1;
            G.d[i][j] = G.d[j][i] = rand() % 10 + 1;
        }

        // 设置下边相邻节点的权重
        if (xi + 1 < 10) {
            int j = i + 10;
            G.d[i][j] = G.d[j][i] = rand() % 10 + 1;
        }
    }


}

void DP::PrintGraph() {
    for (int i = 0; i < G.vexnum; ++i) {
        for (int j = 0; j < G.vexnum; ++j) {
            cout << G.d[i][j] << " ";
        }
        cout << endl;
    }
}

void DP::DrawGraph() {
    sf::RenderWindow window(sf::VideoMode(Swidth, Sheight), "Graph");

    vector<int> shortestPath = GetShortestPath(startVertex, endVertex);

    // 加载字体
    sf::Font font;
    if (!font.loadFromFile("/home/shaozeping/coding/Planning_and_Tracking/Planning/DynamicProgramming/Arial.ttf")) {
        cout << "Error loading font" << endl;
        return;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        // 绘制顶点
        for (int i = 0; i < G.vexnum; ++i) {
            sf::CircleShape circle(10);
            circle.setPosition(G.arr[i][0], G.arr[i][1]);
            circle.setFillColor(sf::Color::Green);  // 设置圆圈颜色
            window.draw(circle);

            // // 显示权重
            // sf::Font font;
            // if (!font.loadFromFile("Planning/Arial.ttf")) {
            //     cout << "Error loading font" << endl;
            // }
            sf::Text text;
            text.setFont(font);
            text.setString(to_string(i));
            text.setCharacterSize(12);
            text.setFillColor(sf::Color::White);
            text.setPosition(G.arr[i][0] + 10, G.arr[i][1] - 10);
            window.draw(text);
        
        }

        

        // 绘制边
        for (int i = 0; i < G.vexnum; ++i) {
            for (int j = 0; j < G.vexnum; ++j) {
                if (G.d[i][j] < INFIN && i != j) {
                    sf::Vertex line[] = {
                        sf::Vertex(sf::Vector2f(G.arr[i][0] + 10, G.arr[i][1] + 10)),
                        sf::Vertex(sf::Vector2f(G.arr[j][0] + 10, G.arr[j][1] + 10))
                    };

                    // 检查这条边是否在最短路径中
                    if (find(shortestPath.begin(), shortestPath.end(), i) != shortestPath.end() &&
                        find(shortestPath.begin(), shortestPath.end(), j) != shortestPath.end() &&
                        abs(find(shortestPath.begin(), shortestPath.end(), i) - find(shortestPath.begin(), shortestPath.end(), j)) == 1) {
                        line[0].color = sf::Color::Red;
                        line[1].color = sf::Color::Red;
                    }else {
                        line[0].color = sf::Color::White;
                        line[1].color = sf::Color::White;
                        }

                    window.draw(line, 2, sf::Lines);


                    // 显示边的权重
                    sf::Text weightText;
                    weightText.setFont(font);
                    weightText.setString(to_string(G.d[i][j]));
                    weightText.setCharacterSize(12);
                    weightText.setFillColor(sf::Color::Blue);
                    weightText.setPosition((G.arr[i][0] + G.arr[j][0]) / 2 , (G.arr[i][1] + G.arr[j][1]) / 2 );
                    window.draw(weightText);
                }
            }
        }
        

        window.display();
    }
}

vector<int> DP::GetShortestPath(int start, int end) {
    vector<int> path;
    if (D[start][end] >= INFIN) {
        return path;
    }
    stack<int> s;
    int v = end;
    while (v != start) {
        s.push(v);
        v = P[start][v];
    }
    s.push(start);
    while (!s.empty()) {
        path.push_back(s.top());
        s.pop();
    }
    return path;
}

void DP::DPShortest() {
    for (int i = 0; i < G.vexnum; ++i) {
        for (int j = 0; j < G.vexnum; ++j) {
            D[i][j] = G.d[i][j];
            P[i][j] = (G.d[i][j] < INFIN && i != j) ? i : -1;
        }
    }

    for (int k = 0; k < G.vexnum; ++k) {
        for (int i = 0; i < G.vexnum; ++i) {
            for (int j = 0; j < G.vexnum; ++j) {
                if (D[i][j] > D[i][k] + D[k][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = P[k][j];
                }
            }
        }
    }
}

void DP::PrintMatrix() {
    for (int i = 0; i < G.vexnum; ++i) {
        for (int j = 0; j < G.vexnum; ++j) {
            cout << D[i][j] << " ";
        }
        cout << endl;
    }
}

void DP::ShowResult() {
    // 显示所有最短路径
    for (int i = 0; i < G.vexnum; ++i) {
        for (int j = 0; j < G.vexnum; ++j) {
            if (i != j && D[i][j] < INFIN) {
                cout << "Shortest path from " << i << " to " << j << " is " << D[i][j] << " through ";
                stack<int> path;
                int v = j;
                while (v != i) {
                    path.push(v);
                    v = P[i][v];
                }
                cout << i;
                while (!path.empty()) {
                    cout << " -> " << path.top();
                    path.pop();
                }
                cout << endl;
            }
        }
    }
}

void DP::SetStartEnd(int start, int end) {
    startVertex = start;
    endVertex = end;
}

void DP::PrintShortestPath() {
    vector<int> path = GetShortestPath(startVertex, endVertex);
    if (path.empty()) {
        cout << "No path exists from " << startVertex << " to " << endVertex << endl;
        return;
    }
    cout << "Shortest path from " << startVertex << " to " << endVertex << " is " << D[startVertex][endVertex] << " through ";
    for (size_t i = 0; i < path.size(); ++i) {
        if (i != 0) {
            cout << " -> ";
        }
        cout << path[i];
    }
    cout << endl;
}

