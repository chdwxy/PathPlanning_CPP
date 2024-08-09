#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <Magick++.h>
#include <iterator>


// Queue Prior for the priority queue implementation
struct QueuePrior {
    std::priority_queue<std::pair<double, std::pair<int, int>>,
                        std::vector<std::pair<double, std::pair<int, int>>>,
                        std::greater<>> pq;

    void put(std::pair<int, int> node, double priority) {
        pq.emplace(priority, node);
    }

    std::pair<int, int> get() {
        auto top = pq.top();
        pq.pop();
        return top.second;
    }

    bool empty() {
        return pq.empty();
    }
};

// Custom hash function for pair<int, int>
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

// Environment class
class Env {
public:
    int x_range = 51; // size of background
    int y_range = 31;
    std::vector<std::pair<int, int>> motions{
        {-1, 0}, {-1, 1}, {0, 1}, {1, 1},
        {1, 0}, {1, -1}, {0, -1}, {-1, -1}
    };
    std::unordered_set<std::pair<int, int>, pair_hash> obs;

    Env() {
        obs = obs_map();
    }

    std::unordered_set<std::pair<int, int>, pair_hash> obs_map() {
        std::unordered_set<std::pair<int, int>, pair_hash> obs;
        for (int i = 0; i < x_range; ++i) {
            obs.emplace(i, 0);
            obs.emplace(i, y_range - 1);
        }
        for (int i = 0; i < y_range; ++i) {
            obs.emplace(0, i);
            obs.emplace(x_range - 1, i);
        }
        for (int i = 10; i < 21; ++i) {
            obs.emplace(i, 15);
        }
        for (int i = 0; i < 15; ++i) {
            obs.emplace(20, i);
        }
        for (int i = 15; i < 30; ++i) {
            obs.emplace(30, i);
        }
        for (int i = 0; i < 16; ++i) {
            obs.emplace(40, i);
        }
        return obs;
    }
};

// LRTA* Algorithm Class
class LrtAStarN {
public:
    int frame_count = 0;
    std::pair<int, int> s_start, s_goal;
    int N;
    std::string heuristic_type;
    Env env;
    std::vector<std::vector<std::pair<int, int>>> visited;
    std::vector<std::vector<std::pair<int, int>>> path;
    std::unordered_map<std::pair<int, int>, double, pair_hash> h_table;

    LrtAStarN(std::pair<int, int> s_start, std::pair<int, int> s_goal, int N, std::string heuristic_type)
        : s_start(s_start), s_goal(s_goal), N(N), heuristic_type(heuristic_type) {
        env = Env();
        h_table = {};
    }

    void init() {
        for (int i = 0; i < env.x_range; ++i) {
            for (int j = 0; j < env.y_range; ++j) {
                h_table[{i, j}] = h({i, j});
            }
        }
    }

    void searching() {
        //  应该是这个地方出了问题
        init();
        auto s_start = this->s_start;

        while (true) {
            auto [OPEN, CLOSED] = AStar(s_start, N);
            std::cout << "A* search result: " << OPEN << std::endl;
            if (OPEN == "FOUND") {
                path.push_back(CLOSED);
                std::cout << "Path found, stopping search." << std::endl;
                break;
            }

            auto h_value = iteration(CLOSED);

            for (const auto& x : h_value) {
                h_table[x.first] = x.second;
            }

            auto [s_next, path_k] = extract_path_in_CLOSE(s_start, h_value);
            path.push_back(path_k);
            s_start = s_next;

            // Draw the current state
            draw_path(path_k);
            std::cout << "Current start node: (" << s_start.first << ", " << s_start.second << ")" << std::endl;
        }

        // After the search is complete, generate the GIF
        create_gif();
    }

    std::pair<std::string, std::vector<std::pair<int, int>>> AStar(std::pair<int, int> x_start, int N) {
        QueuePrior OPEN;
        OPEN.put(x_start, h(x_start));
        std::vector<std::pair<int, int>> CLOSED;
        std::unordered_map<std::pair<int, int>, double, pair_hash> g_table;
        g_table[x_start] = 0;
        g_table[s_goal] = std::numeric_limits<double>::infinity();
        std::unordered_map<std::pair<int, int>, std::pair<int, int>, pair_hash> PARENT;
        PARENT[x_start] = x_start;
        int count = 0;

        while (!OPEN.empty()) {
            count++;
            auto s = OPEN.get();
            CLOSED.push_back(s);

            if (s == s_goal) {
                visited.push_back(CLOSED);
                return {"FOUND", extract_path(x_start, PARENT)};
            }

            for (auto s_n : get_neighbor(s)) {
                if (std::find(CLOSED.begin(), CLOSED.end(), s_n) == CLOSED.end()) {
                    double new_cost = g_table[s] + cost(s, s_n);
                    if (g_table.find(s_n) == g_table.end()) {
                        g_table[s_n] = std::numeric_limits<double>::infinity();
                    }
                    if (new_cost < g_table[s_n]) {
                        g_table[s_n] = new_cost;
                        PARENT[s_n] = s;
                        OPEN.put(s_n, g_table[s_n] + h_table[s_n]);
                    }
                }
            }

            if (count == N) {
                break;
            }
        }

        visited.push_back(CLOSED);
        return {"CONTINUE", CLOSED};
    }

    std::unordered_map<std::pair<int, int>, double, pair_hash> iteration(std::vector<std::pair<int, int>> CLOSED) {
        std::unordered_map<std::pair<int, int>, double, pair_hash> h_value;
        for (const auto& s : CLOSED) {
            h_value[s] = std::numeric_limits<double>::infinity();
        }

        while (true) {
            auto h_value_rec = h_value;
            for (const auto& s : CLOSED) {
                std::vector<double> h_list;
                for (const auto& s_n : get_neighbor(s)) {
                    if (std::find(CLOSED.begin(), CLOSED.end(), s_n) == CLOSED.end()) {
                        h_list.push_back(cost(s, s_n) + h_table[s_n]);
                    } else {
                        h_list.push_back(cost(s, s_n) + h_value[s_n]);
                    }
                }
                h_value[s] = *std::min_element(h_list.begin(), h_list.end());
            }

            if (h_value == h_value_rec) {
                return h_value;
            }
        }
    }

    std::pair<std::pair<int, int>, std::vector<std::pair<int, int>>> extract_path_in_CLOSE(
        std::pair<int, int> s_start, std::unordered_map<std::pair<int, int>, double, pair_hash> h_value) {
        std::vector<std::pair<int, int>> path = {s_start};
        auto s = s_start;

        while (true) {
            std::unordered_map<std::pair<int, int>, double, pair_hash> h_list;

            for (const auto& s_n : get_neighbor(s)) {
                if (h_value.find(s_n) != h_value.end()) {
                    h_list[s_n] = h_value[s_n];
                } else {
                    h_list[s_n] = h_table[s_n];
                }
            }

            auto s_key = std::min_element(h_list.begin(), h_list.end(),
                                          [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; })
                             ->first;
            path.push_back(s_key);
            std::cout << "Adding node to path: (" << s_key.first << ", " << s_key.second << ")" << std::endl;
            s = s_key;

            if (h_value.find(s_key) == h_value.end()) {
                std::cout << "Returning path with last node: (" << s_key.first << ", " << s_key.second << ")" << std::endl;
                return {s_key, path};
            }
        }
    }

    std::vector<std::pair<int, int>> extract_path(
        std::pair<int, int> s_start, std::unordered_map<std::pair<int, int>, std::pair<int, int>, pair_hash> PARENT) {
        std::vector<std::pair<int, int>> path;
        auto s = s_start;

        while (true) {
            path.push_back(s);
            if (s == s_goal) {
                std::reverse(path.begin(), path.end());
                return path;
            }
            s = PARENT[s];
        }
    }

    std::vector<std::pair<int, int>> get_neighbor(std::pair<int, int> s) {
        std::vector<std::pair<int, int>> result;
        for (auto motion : env.motions) {
            auto s_n = std::make_pair(s.first + motion.first, s.second + motion.second);
            if (env.obs.find(s_n) == env.obs.end()) {
                result.push_back(s_n);
            }
        }
        return result;
    }

    double h(std::pair<int, int> s) {
        return std::abs(s.first - s_goal.first) + std::abs(s.second - s_goal.second);
    }

    double cost(std::pair<int, int> s_start, std::pair<int, int> s_goal) {
        return std::hypot(s_start.first - s_goal.first, s_start.second - s_goal.second);
    }

    // // Custom hash function for pair<int, int>
    // struct pair_hash {
    //     template <class T1, class T2>
    //     std::size_t operator()(const std::pair<T1, T2>& pair) const {
    //         return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    //     }
    // };

    // Function to draw the current path
    // void draw_path(const std::vector<std::pair<int, int>>& path) {
    //     int scale = 20; // Scaling factor to enlarge the image
    //     cv::Mat image(env.y_range * scale, env.x_range * scale, CV_8UC3, cv::Scalar(255, 255, 255));

    //     // Draw obstacles
    //     for (const auto& obs : env.obs) {
    //         cv::rectangle(image, cv::Point(obs.first * scale, obs.second * scale),
    //                       cv::Point((obs.first + 1) * scale, (obs.second + 1) * scale), cv::Scalar(0, 0, 0), -1);
    //     }

    //     // Draw the path
    //     for (size_t i = 1; i < path.size(); ++i) {
    //         cv::line(image, cv::Point(path[i - 1].first * scale + scale / 2, path[i - 1].second * scale + scale / 2),
    //                  cv::Point(path[i].first * scale + scale / 2, path[i].second * scale + scale / 2),
    //                  cv::Scalar(0, 0, 255), 2);
    //     }

    //     // Draw start and goal points
    //     cv::circle(image, cv::Point(s_start.first * scale + scale / 2, s_start.second * scale + scale / 2), scale / 2,
    //                cv::Scalar(0, 255, 0), -1);
    //     cv::circle(image, cv::Point(s_goal.first * scale + scale / 2, s_goal.second * scale + scale / 2), scale / 2,
    //                cv::Scalar(255, 0, 0), -1);

    //     // Save each frame as an image
    //     static int frame_count = 0;
    //     std::string filename = "frame_" + std::to_string(frame_count++) + ".png";
    //     cv::imwrite(filename, image);
    //     std::cout<<"输出图片中"<<std::endl;
    // }

    // // Function to create GIF from saved frames
    // void create_gif() {
    //     Magick::InitializeMagick(nullptr);
    //     std::vector<Magick::Image> frames;
    //     static int frame_count = 0;
    //     for (int i = 0; i < frame_count; ++i) {
    //         std::string filename = "frame_" + std::to_string(i) + ".png";
    //         std::cout<<"输出动图图片中"<<std::endl;
    //         Magick::Image frame;
    //         frame.read(filename);
    //         frame.animationDelay(10); // Adjust delay for the animation
    //         frames.push_back(frame);
    //     }

    //     // Save GIF
    //     Magick::writeImages(frames.begin(), frames.end(), "lrta_star.gif");
    //     std::cout<<"输出动图中"<<std::endl;
    // }

    void draw_path(const std::vector<std::pair<int, int>>& path) {
        int scale = 20; // Scaling factor to enlarge the image
        cv::Mat image(env.y_range * scale, env.x_range * scale, CV_8UC3, cv::Scalar(255, 255, 255));

        // Draw obstacles
        for (const auto& obs : env.obs) {
            cv::rectangle(image, cv::Point(obs.first * scale, obs.second * scale),
                          cv::Point((obs.first + 1) * scale, (obs.second + 1) * scale), cv::Scalar(0, 0, 0), -1);
        }

        // Draw the path
        for (size_t i = 1; i < path.size(); ++i) {
            cv::line(image, cv::Point(path[i - 1].first * scale + scale / 2, path[i - 1].second * scale + scale / 2),
                     cv::Point(path[i].first * scale + scale / 2, path[i].second * scale + scale / 2),
                     cv::Scalar(0, 0, 255), 2);
        }

        // Draw start and goal points
        cv::circle(image, cv::Point(s_start.first * scale + scale / 2, s_start.second * scale + scale / 2), scale / 2,
                   cv::Scalar(0, 255, 0), -1);
        cv::circle(image, cv::Point(s_goal.first * scale + scale / 2, s_goal.second * scale + scale / 2), scale / 2,
                   cv::Scalar(255, 0, 0), -1);

        // Save each frame as an image
        // std::string filename = "frame_" + std::to_string(frame_count++) + ".png";
        // cv::imwrite(filename, image);
        // std::cout << "输出图片中: " << filename << std::endl;

        static int frame_count = 0;
        std::string filename = "frame_" + std::to_string(frame_count) + ".png";
        std::cout << "Saving frame: " << filename << std::endl;
        cv::imwrite(filename, image);
        
        frame_count++;
        std::cout << "Current frame count: " << frame_count << std::endl;
    }

    // Function to create GIF from saved frames
    void create_gif() {
        Magick::InitializeMagick(nullptr);
        std::vector<Magick::Image> frames;
        std::cout << "Creating GIF from " << frame_count << " frames." << std::endl;

        for (int i = 0; i < frame_count; ++i) {
            std::string filename = "frame_" + std::to_string(i) + ".png";
            std::cout << "Reading frame: " << filename << std::endl;
            Magick::Image frame;
            frame.read(filename);
            frame.animationDelay(10); // Adjust delay for the animation
            frames.push_back(frame);
        }

        // Save GIF
        std::string gif_filename = "lrta_star.gif";
        std::cout << "Saving GIF: " << gif_filename << std::endl;
        Magick::writeImages(frames.begin(), frames.end(), "lrta_star.gif");
        std::cout << "输出动图中: lrta_star.gif" << std::endl;
    }

};

int main() {
    std::pair<int, int> start = {5, 5};
    std::pair<int, int> goal = {45, 25};
    int N = 100;

    LrtAStarN lrta(start, goal, N, "manhattan");
    lrta.searching();

    return 0;
}
