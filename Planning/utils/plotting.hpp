#ifndef PLOTTING_HPP
#define PLOTTING_HPP

#include <vector>
#include<string>
#include <utility>
#include <opencv2/opencv.hpp>
using namespace std;

class Plotting {
public:
    Plotting(std::pair<int, int> s_start, std::pair<int, int> s_goal);
    void animation_ara_star(const std::vector<std::vector<std::pair<int, int>>>& path, 
                            const std::vector<std::vector<std::pair<int, int>>>& visited, 
                            const std::string& title);
    void plot_path(const std::vector<std::pair<int,int>>& path, 
                                    const std::vector<std::vector<std::pair<int,int>>>& visited,
                                    const std::string& title);
    void animationBiAStar(const std::vector<std::pair<int, int>>& path,
                          const std::vector<std::pair<int, int>>& visitedFore,
                          const std::vector<std::pair<int, int>>& visitedBack,
                          const std::string& title) const;

private:
    std::pair<int, int> s_start, s_goal;
    cv::Mat img;
    int scale;
    int rows, cols;
};

#endif // PLOTTING_HPP
