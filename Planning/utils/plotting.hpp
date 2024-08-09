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
                                    // const std::vector<std::vector<std::pair<int,int>>>& visited,
                                    const std::vector<std::pair<int,int>>& visited,
                                    const std::string& title);
    // void animationBiAStar(const std::vector<std::pair<int, int>>& path,
    //                       const std::vector<std::pair<int, int>>& visitedFore,
    //                       const std::vector<std::pair<int, int>>& visitedBack,
    //                       const std::string& title) const;
    void animationBiAStar(const std::vector<std::pair<int, int>>& path1,
                          const std::vector<std::pair<int, int>>& path2,
                          const std::vector<std::pair<int, int>>& path3,
                          const std::vector<std::pair<int, int>>& closed_fore,
                          const std::vector<std::pair<int, int>>& closed_back,
                          const std::string& filename) const;
    void animationBiAStarTest(const std::vector<std::pair<int, int>>& path,
                          const std::vector<std::pair<int, int>>& closed_fore,
                          const std::vector<std::pair<int, int>>& closed_back,
                          const std::string& filename) const;

private:
    std::pair<int, int> s_start, s_goal;
    mutable cv::Mat img;
    int scale=50;
    int rows, cols;

    void drawGrid() const;
    void drawPath(const std::vector<std::pair<int, int>>& path, const cv::Scalar& color) const;
    void drawClosed(const std::vector<std::pair<int, int>>& closed, const cv::Scalar& color) const;

};

#endif // PLOTTING_HPP
