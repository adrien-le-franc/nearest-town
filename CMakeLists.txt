#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project(Le_Franc_tp2)
cmake_minimum_required(VERSION 2.8)

SET(CMAKE_CXX_FLAGS "-std=c++0x")

aux_source_directory(. SRC_LIST)
add_executable(Le_Franc_tp2 main.cpp tools.h tools.cpp search.h
               villes1/point2d.cpp villes1/town.h villes1/town.cpp
               quadtree/quadtree.h)

add_definitions(-DsrcPath="${CMAKE_CURRENT_SOURCE_DIR}")

