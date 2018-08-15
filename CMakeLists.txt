project(tensorboardprotobuf)
cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(tbproto)

add_executable(a main.cpp)
target_include_directories(a PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(a tbproto)
