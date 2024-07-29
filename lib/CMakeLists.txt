# cmake_minimum_required(VERSION 3.10)
# project(MyLib)

# include_directories(include)

# add_library(lib)
# target_include_directories(lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
# target_sources(lib PRIVATE src/utils.cpp)
# set_target_properties(lib
#   PROPERTIES
#     CXX_STANDARD 14
#     CXX_STANDARD_REQUIRED YES
#     CXX_EXTENSIONS NO
#     CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -Werror -g"
# )
# target_link_libraries(lib PRIVATE project_options project_warnings)
# # include_directories(${CMAKE_SOURCE_DIR}/lib/include)

# # cmake_minimum_required(VERSION 3.10)

# # project(LibProject)

# # # Include directories
# # include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# # Source files
# set(SOURCES
#     src/env.cpp
#     src/plotting.cpp
#     src/utils.cpp
# )

# # 指定安装位置
# install(TARGETS mylib DESTINATION lib)


# # Create a static library
# # add_library(libproject STATIC ${LIB_SOURCES})


add_subdirectory(utils)
