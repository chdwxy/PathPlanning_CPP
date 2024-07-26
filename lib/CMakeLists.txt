project(lib)

cmake_minimum_required(VERSION 3.15)

add_library(lib)
target_include_directories(lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_sources(lib PRIVATE src/utils.cpp)
set_target_properties(lib
  PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -Werror -g"
)
target_link_libraries(lib PRIVATE project_options project_warnings)
