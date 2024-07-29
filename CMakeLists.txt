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
add_subdirectory(lib)
add_subdirectory(Planning bin_planning)

file( GLOB LIB_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/a_star.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/dijkstra.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/rrt_star.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/rrt.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/lpa_star.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/d_star_lite.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/ant_colony.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/genetic_algorithm.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/jump_point_search.cpp
)

foreach(file ${LIB_SOURCES})
    get_filename_component(ouput_file ${file} NAME_WE)
    add_executable(${ouput_file})
    target_include_directories(${ouput_file} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_sources(${ouput_file} PRIVATE ${file})
    target_compile_options (${ouput_file}  PRIVATE -O3)
    target_link_libraries(${ouput_file} PRIVATE utils project_options project_warnings)
  endforeach(file ${LIB_SOURCES})