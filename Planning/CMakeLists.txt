cmake_minimum_required(VERSION 3.21)
project(Planning_and_Tracking)

set(CMAKE_CXX_STANDARD 17)


find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

# set(ImageMagick_DIR /usr/include/ImageMagick-6)
find_package(ImageMagick COMPONENTS Magick++ REQUIRED)
include_directories(${ImageMagick_INCLUDE_DIRS})
link_directories(${ImageMagick_LIBRARY_DIRS})
find_package(PkgConfig REQUIRED)
pkg_check_modules(MAGICK REQUIRED ImageMagick)

include_directories(${MAGICK_INCLUDE_DIRS})

# target_link_libraries(${PROJECT_NAME} ${ImageMagick_LIBRARIES})

set(OpenCV_DIR /usr/local/opencv3.4)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# 手动添加 libtiff 库
find_package(TIFF REQUIRED)
include_directories(${TIFF_INCLUDE_DIR})
link_libraries(${TIFF_LIBRARIES})

find_package(Python3 COMPONENTS Interpreter Development NumPy REQUIRED)
include_directories(${Python3_INCLUDE_DIRS} ${Python3_NumPy_INCLUDE_DIRS})
set(CMAKE_PREFIX_PATH "/usr/lib/python3/dsit-packages/cmake" ${CMAKE_PREFIX_PATH})


find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)




# 打印包含路径以验证正确性
# message(STATUS "Include path: ${PROJECT_SOURCE_DIR}/Planning_and_Tracking/lib/include")

# include_directories(${PROJECT_SOURCE_DIR}/lib/include)

# include_directories(${PROJECT_SOURCE_DIR}/Planning_and_Tracking/lib/include)
# include_directories(${CMAKE_SOURCE_DIR}/lib/include)
# add_subdirectory(lib)

# set(CMAKE_PREFIX_PATH "/usr/include/eigen3" ${CMAKE_PREFIX_PATH})



# add_subdirectory(${CMAKE_SOURCE_DIR}/lib  ${CMAKE_BINARY_DIR}/lib_build)

# find_library(MYLIB mylib HINTS ${CMAKE_SOURCE_DIR}/lib/include)
# find_library(UTIL_LIB util HINTS ${CMAKE_SOURCE_DIR}/lib/utils)

# set(CMAKE_PREFIX_PATH "/usr/include/SFML")

# 链接库
# target_link_libraries(AntColony_demo PRIVATE Planning_and_Tracking sfml-graphics sfml-window sfml-system)

# test
add_executable(test_demo test/test.cpp)
target_link_libraries(test_demo PRIVATE Planning_and_Tracking ${OpenCV_LIBS} ${TIFF_LIBRARIES})

# circle_test
add_executable(circle_test_demo test/circle_test.cpp)
target_link_libraries(circle_test_demo PRIVATE Planning_and_Tracking ${OpenCV_LIBS} ${TIFF_LIBRARIES})

# Dijkstra
add_executable(dijkstra_demo Dijkstra/main.cpp Dijkstra/Dijkstra.cpp)
target_link_libraries(dijkstra_demo PRIVATE Planning_and_Tracking)

# AntColony
add_executable(AntColony_demo AntColony/main.cpp AntColony/AntColony.cpp)
target_link_libraries(AntColony_demo PRIVATE Planning_and_Tracking)

# AntColony_OpenCV
# add_executable(AntColony_OpenCV_demo AntColony_OpenCV/main.cpp AntColony_OpenCV/AntColony.cpp AntColony_OpenCV/env.cpp)
add_executable(AntColony_OpenCV_demo AntColony_OpenCV/main.cpp AntColony_OpenCV/AntColony.cpp utils/env.cpp)
target_link_libraries(AntColony_OpenCV_demo PRIVATE Planning_and_Tracking ${OpenCV_LIBS} ${TIFF_LIBRARIES})

# Dynamic Programming
add_executable(DP_demo DynamicProgramming/main.cpp DynamicProgramming/DP.cpp)
target_link_libraries(DP_demo PRIVATE Planning_and_Tracking sfml-audio sfml-graphics sfml-window sfml-system)
# target_link_libraries(Planning_and_Tracking sfml-audio sfml-graphics)

# AStar
add_executable(AStar_demo AStar/AStar.cpp AStar/main.cpp)
target_link_libraries(AStar_demo PRIVATE Planning_and_Tracking)

# jump_point_search
add_executable(JPS_demo JumpPointSearch/JPS.cpp JumpPointSearch/main.cpp utils/utils.hpp utils/utils.cpp utils/planner.hpp)
target_link_libraries(JPS_demo PRIVATE Planning_and_Tracking)

# LPAStar
add_executable(LPAStar_demo LPAStar/LPAStar.cpp LPAStar/main.cpp utils/utils.hpp utils/utils.cpp utils/planner.hpp)
target_link_libraries(LPAStar_demo PRIVATE Planning_and_Tracking)

# ARAStar
add_executable(ARAStar_demo ARAStar/arastar.cpp ARAStar/main.cpp utils/env.hpp utils/env.cpp utils/plotting.hpp utils/plotting.cpp)
target_link_libraries(ARAStar_demo PRIVATE Planning_and_Tracking ${OpenCV_LIBS} ${TIFF_LIBRARIES})

# ARAStar_OpenCV
add_executable(ARAStar_OpenCV_demo ARAStar_OpenCV/arastar.cpp ARAStar_OpenCV/main.cpp utils/env.cpp)
target_link_libraries(ARAStar_OpenCV_demo PRIVATE Planning_and_Tracking ${OpenCV_LIBS} ${TIFF_LIBRARIES})

# BidirectionalAStar
add_executable(B_AStar_demo BidirectionalAStar/B_AStar.cpp BidirectionalAStar/main.cpp utils/env.cpp utils/plotting.cpp)
target_link_libraries(B_AStar_demo PRIVATE Planning_and_Tracking ${OpenCV_LIBS} ${TIFF_LIBRARIES})

# BidirectionalAStar_test
add_executable(B_AStar_test_demo BidirectionalAStar_test/bidirectional_a_star.cpp BidirectionalAStar_test/main.cpp BidirectionalAStar_test/env.cpp utils/plotting.cpp)
target_link_libraries(B_AStar_test_demo PRIVATE Planning_and_Tracking ${OpenCV_LIBS} ${TIFF_LIBRARIES})

# # LRTAStar
# add_executable(LRTAStar_demo LRTAStar/LRTAStar.cpp LRTAStar/main.cpp utils/env.cpp utils/plotting.cpp)
# target_link_libraries(LRTAStar_demo PRIVATE Planning_and_Tracking ${OpenCV_LIBS} ${TIFF_LIBRARIES})

# LRTAStar_test
add_definitions(-DMAGICKCORE_QUANTUM_DEPTH=16)
add_definitions(-DMAGICKCORE_HDRI_ENABLE=1)
add_executable(LRTAStar_test_demo LRTAStar_test/test.cpp)
target_link_libraries(LRTAStar_test_demo PRIVATE Planning_and_Tracking /usr/local/lib/libMagickCore-7.Q16HDRI.so
/usr/local/lib/libMagickWand-7.Q16HDRI.so ${OpenCV_LIBS} ${TIFF_LIBRARIES} ${ImageMagick_LIBRARIES})

# 人工势场法
add_executable(apf_demo ArtificalPotentialField/main.cpp ArtificalPotentialField/APF.cpp)
target_link_libraries(apf_demo PRIVATE Planning_and_Tracking)

# bezier
add_executable(bezier_demo BezierCurve/main.cpp BezierCurve/Bezier.cpp)
target_link_libraries(bezier_demo PRIVATE Planning_and_Tracking)

# B-spline
add_executable(bspline_demo BSpline/main.cpp BSpline/BSpline.cpp)
target_link_libraries(bspline_demo PRIVATE Planning_and_Tracking)

# 曲线插值
add_executable(curve_demo Curve_interpolation/main.cpp )
target_link_libraries(curve_demo PRIVATE Planning_and_Tracking)

# 动态窗口法
add_executable(dwa_demo Dynamic_Window_Approach/main.cpp Dynamic_Window_Approach/DWA.cpp)
target_link_libraries(dwa_demo PRIVATE Planning_and_Tracking)

# RRT
add_executable(rrt_demo RRT/main.cpp RRT/RRT.cpp utils/geometry_utils.hpp)
target_link_libraries(rrt_demo PRIVATE Planning_and_Tracking)

# RRT_connect
add_executable(rrt_connect_demo RRT_connect/main.cpp RRT_connect/RRT_connect.cpp utils/geometry_utils.hpp)
target_link_libraries(rrt_connect_demo PRIVATE Planning_and_Tracking)

# RRT_star
add_executable(rrt_star_demo RRT_Star/main.cpp RRT_Star/RRT_Star.cpp RRT/RRT.cpp)
target_link_libraries(rrt_star_demo PRIVATE Planning_and_Tracking)

# RS曲线
add_executable(rs_demo ReedsShepp/main.cpp ReedsShepp/ReedsShepp.cpp)
target_link_libraries(rs_demo PRIVATE Planning_and_Tracking)

# Dubins曲线
add_executable(dubins_demo Dubins/main.cpp Dubins/Dubins.cpp)
target_link_libraries(dubins_demo PRIVATE Planning_and_Tracking)