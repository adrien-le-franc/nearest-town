set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
cmake_minimum_required(VERSION 2.6)

project (villes_les_plus_proches)

# add_executable (villes main.cpp town.cpp
# 	        point2d.cpp square.cpp quadrant.cpp neighbors.cpp)
# rm main.cpp square.cpp quadrant.cpp neighbors.cpp

add_executable (test_villes example.cpp town.cpp  town.h point2d.cpp point2d.h neighbors.h square.h quadrant.h)

add_definitions(-DsrcPath="${CMAKE_CURRENT_SOURCE_DIR}")
