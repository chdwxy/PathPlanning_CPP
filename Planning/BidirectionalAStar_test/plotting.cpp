// plotting.cpp
#include "plotting.hpp"

Plotting::Plotting(std::pair<int, int> xI, std::pair<int, int> xG) 
    : xI(xI), xG(xG) {
    obs = {{20, 20}, {20, 21}, {20, 22}, {20, 23}, {20, 24},
           {21, 20}, {22, 20}, {23, 20}, {24, 20}};
}

void Plotting::update_obs(const std::vector<std::pair<int, int>>& new_obs) {
    obs = new_obs;
}

void Plotting::animation(const std::vector<std::pair<int, int>>& path, 
                         const std::vector<std::pair<int, int>>& visited, 
                         const std::string& name) {
    plot_grid(name);
    plot_visited(visited);
    plot_path(path);
    cv::imshow(name, img);
    cv::waitKey(0);
}

void Plotting::plot_grid(const std::string& name) {
    img = cv::Mat::zeros(600, 600, CV_8UC3);

    for (auto& ob : obs) {
        cv::rectangle(img, 
                      cv::Point(ob.first * scale + offset, ob.second * scale + offset), 
                      cv::Point(ob.first * scale + offset + scale, ob.second * scale + offset + scale), 
                      cv::Scalar(0, 0, 0), 
                      cv::FILLED);
    }

    cv::circle(img, 
               cv::Point(xI.first * scale + offset + scale / 2, xI.second * scale + offset + scale / 2), 
               scale / 2, 
               cv::Scalar(255, 0, 0), 
               cv::FILLED);

    cv::circle(img, 
               cv::Point(xG.first * scale + offset + scale / 2, xG.second * scale + offset + scale / 2), 
               scale / 2, 
               cv::Scalar(0, 255, 0), 
               cv::FILLED);
}

void Plotting::plot_visited(const std::vector<std::pair<int, int>>& visited) {
    for (auto& v : visited) {
        cv::circle(img, 
                   cv::Point(v.first * scale + offset + scale / 2, v.second * scale + offset + scale / 2), 
                   scale / 4, 
                   cv::Scalar(200, 200, 200), 
                   cv::FILLED);
        cv::imshow("Visited Nodes", img);
        cv::waitKey(1);
    }
}

void Plotting::plot_path(const std::vector<std::pair<int, int>>& path) {
    for (size_t i = 1; i < path.size(); ++i) {
        cv::line(img, 
                 cv::Point(path[i-1].first * scale + offset + scale / 2, path[i-1].second * scale + offset + scale / 2), 
                 cv::Point(path[i].first * scale + offset + scale / 2, path[i].second * scale + offset + scale / 2), 
                 cv::Scalar(0, 0, 255), 
                 2);
    }
    cv::imshow("Path", img);
    cv::waitKey(1);
}
