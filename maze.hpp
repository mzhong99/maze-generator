#ifndef _MAZE_HPP_
#define _MAZE_HPP_

#include <string>
#include <iostream>
#include <sstream>

#include <vector>
#include <stack>
#include <queue>
#include <unordered_set>

#include <algorithm>
#include <cstdint>

#include "grid.hpp"
#include "disjoint_sets.hpp"

#define SET_CONTAINS(s, e) (s.find(e) != s.end())

enum class Tile { Wall, Floor, Start, End, Solution };

// Maze class. Has internal grid for linked graph
// and 2d boolean vector to store result
class Maze {

private:
    Grid grid;
    std::vector<std::vector<Tile>> result;
    uint32_t width, height;
    bool has_valid_solution;

    // helper method for initializing result
    void reset_result();

    void build_floor(const Point& lhs, const Point& rhs);
    uint32_t coordinate_to_index(uint32_t coord);

public:
    Maze();
    Maze(uint32_t width, uint32_t height);
    
    std::vector<std::vector<Tile>> get_result() const;
    
    uint32_t get_width() const;
    uint32_t get_height() const;

    void generate_using_backtracker();
    void generate_using_kruskals();
    void generate_using_prims();
    void generate_using_binary_tree();
    void generate_using_ellers();
    
    void add_solution();
    Tile get_tile_at(uint32_t x, uint32_t y) const;

    friend std::ostream& operator<<(std::ostream& out, const Maze& maze);
    std::string to_string() const;
};

#include "maze.cpp"

#endif // _MAZE_HPP_
