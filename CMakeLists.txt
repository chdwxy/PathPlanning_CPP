cmake_minimum_required(VERSION 3.21)
project(Planning_and_Tracking)

set(CMAKE_CXX_STANDARD 14)

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

set(CMAKE_PREFIX_PATH "/usr/include/eigen3" ${CMAKE_PREFIX_PATH})
set(CMAKE_PREFIX_PATH "/usr/lib/python3/dsit-packages/cmake" ${CMAKE_PREFIX_PATH})

find_package(Python3 COMPONENTS Interpreter Development NumPy REQUIRED)
include_directories(${Python3_INCLUDE_DIRS} ${Python3_NumPy_INCLUDE_DIRS})


find_package(Python3 REQUIRED)

include_directories(${Python3_INCLUDE_DIRS})

#include(GNUInstallDirs)
set(PACKAGE_NAME Planning_and_Tracking)


# Library target
add_library(Planning_and_Tracking INTERFACE)


# TODO: Use `Development.Embed` component when requiring cmake >= 3.18
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
target_link_libraries(Planning_and_Tracking INTERFACE
        Python3::Python
        Python3::Module
        )
find_package(Python3 COMPONENTS NumPy)
if(Python3_NumPy_FOUND)
    target_link_libraries(Planning_and_Tracking INTERFACE
            Python3::NumPy
            )
else()
    target_compile_definitions(Planning_and_Tracking INTERFACE WITHOUT_NUMPY)
endif()
install(
        TARGETS Planning_and_Tracking
        EXPORT install_targets
)



# add_executable(main main.cpp)
# target_link_libraries(main PRIVATE Planning_and_Tracking)


add_subdirectory(Tracking bin)

add_subdirectory(Planning bin_planning)

