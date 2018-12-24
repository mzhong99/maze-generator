cmake_minimum_required(VERSION 3.5)
project(Maze_Generator CXX)

# require C++11 or newer compiler
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# source code
set(IMAGE_SOURCE image.hpp lodepng.h lodepng.cpp)

set(POINT_SOURCE point.hpp)
set(EDGE_SOURCE edge.hpp)

set(GRID_SOURCE grid.hpp)
set(DISJOINT_SETS_SOURCE disjoint_sets.hpp)

set(MAZE_SOURCE maze.hpp)

set(MAZE_GENERATOR_SOURCE maze_generator.hpp)

# for unit tests
set(TEST_SOURCE unit_tests.cpp)
set(MAIN_SOURCE main.cpp)

ADD_EXECUTABLE(unit-tests catch.hpp ${TEST_SOURCE}
                                    ${IMAGE_SOURCE} 
                                    ${POINT_SOURCE}
                                    ${EDGE_SOURCE}
                                    ${GRID_SOURCE}
                                    ${MAZE_SOURCE}
                                    ${MAZE_GENERATOR_SOURCE})

ADD_EXECUTABLE(maze-generator catch.hpp ${MAIN_SOURCE}
                                        ${IMAGE_SOURCE} 
                                        ${POINT_SOURCE}
                                        ${EDGE_SOURCE}
                                        ${GRID_SOURCE}
                                        ${MAZE_SOURCE}
                                        ${MAZE_GENERATOR_SOURCE})
enable_testing()
add_test(unit-tests unit-tests)

