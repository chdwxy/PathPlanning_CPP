// plotting.h
#ifndef PLOTTING_H
#define PLOTTING_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <utility>

class Plotting {
public:
    Plotting(std::pair<int, int> xI, std::pair<int, int> xG);

    void update_obs(const std::vector<std::pair<int, int>>& obs);
    void animation(const std::vector<std::pair<int, int>>& path, 
                   const std::vector<std::pair<int, int>>& visited, 
                   const std::string& name);

private:
    void plot_grid(const std::string& name);
    void plot_visited(const std::vector<std::pair<int, int>>& visited);
    void plot_path(const std::vector<std::pair<int, int>>& path);

    std::pair<int, int> xI, xG;
    std::vector<std::pair<int, int>> obs;
    int scale = 10;
    int offset = 50;
    cv::Mat img;
};

#endif // PLOTTING_H
