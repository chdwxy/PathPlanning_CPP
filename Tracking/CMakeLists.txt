cmake_minimum_required(VERSION 3.21)
project(Planning_and_Tracking)

set(CMAKE_CXX_STANDARD 14)

#include(GNUInstallDirs)
set(PACKAGE_NAME Planning_and_Tracking)


include_directories(/usr/include/python3.10)
include_directories(/usr/local/lib/python3.10/dist-packages/numpy/core/include)

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

find_package(OsqpEigen REQUIRED)

#PID
add_executable(pid_demo PID/main.cpp PID/PID_controller.cpp utils/KinematicModel.cpp)
target_link_libraries(pid_demo PRIVATE Planning_and_Tracking)

# LQR
add_executable(lqr_demo LQR/main.cpp  LQR/LQR.cpp utils/MyReferencePath.cpp utils/KinematicModel.cpp)
target_link_libraries(lqr_demo PRIVATE Planning_and_Tracking)

# mpc控制 osqp待实现
add_executable(mpc_demo MPC/main.cpp  MPC/MPC.cpp utils/KinematicModel.cpp utils/MyReferencePath.cpp )
target_link_libraries(mpc_demo PRIVATE Planning_and_Tracking OsqpEigen::OsqpEigen)

# MPC实现轨迹跟踪，cppad/ipopt 实现
add_executable(mpssc_demo MPSSC/main.cpp MPSSC/MPSSC.cpp)
target_link_libraries(mpssc_demo PRIVATE ipopt Planning_and_Tracking)

#pure pursuit
add_executable(pure_pursuit_demo PurePursuit/main.cpp  PurePursuit/PurePursuit.cpp utils/KinematicModel.cpp)
target_link_libraries(pure_pursuit_demo PRIVATE Planning_and_Tracking)

# 后轮位置反馈控制RWF
add_executable(rear_wheel_feedback_demo RearWheelFeedback/main.cpp  RearWheelFeedback/RWF.cpp utils/MyReferencePath.cpp utils/KinematicModel.cpp)
target_link_libraries(rear_wheel_feedback_demo PRIVATE Planning_and_Tracking)

#stanley
add_executable(stanley_demo Stanley/main.cpp  Stanley/Stanley.cpp utils/KinematicModel.cpp)
target_link_libraries(stanley_demo PRIVATE Planning_and_Tracking)



