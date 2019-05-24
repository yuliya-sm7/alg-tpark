cmake_minimum_required(VERSION 3.14)
project(1dz)

set(CMAKE_CXX_STANDARD 14)

add_executable(1dz main.cpp CListGraph.cpp CListGraph.h IGraph.h)