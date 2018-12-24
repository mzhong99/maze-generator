#ifndef _MAZE_GENERATOR_H_
#define _MAZE_GENERATOR_H_

#include <unordered_map>
#include <iostream>
#include <sstream>
#include <string>

#include <functional>
#include <stdexcept>

#include "image.hpp"
#include "maze.hpp"

class MazeGenerator {

private:
    Maze maze;
    std::unordered_map<std::string, void(Maze::*)()> generators;

    void setup_function_map();
    
public:

    MazeGenerator();
    MazeGenerator(uint32_t width, uint32_t height);
    
    void generate(std::string generation_algorithm);
    
    void solve();
    void display() const;

    void print_to(std::string filename) const;
    
    std::string attributes() const;
    std::vector<std::string> get_algorithms();
};

#include "maze_generator.cpp"

#endif // _MAZE_GENERATOR_H_
