project(tensorboardprotobuf)
cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_FLAGS "-g -Wall -Werror -std=c++14")

add_subdirectory(tbproto)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_executable(main main.cpp)
target_link_libraries(main tbproto)
