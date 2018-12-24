#ifndef _GRID_HPP_
#define _GRID_HPP_

#include <vector>
#include <unordered_set>

#include <algorithm>
#include <stdexcept>
#include <cstdint>

#define SET_CONTAINS(s, e) (s.find(e) != s.end())

#include "edge.hpp"
#include "point.hpp"

// Adjacency matrix representation of grid. 
// Indexed as adjacency[x][y]
class Grid {

private:

    std::vector<std::vector<std::vector<Edge>>> adjacency, randomized_adjacency;
    uint32_t width, height;

    bool preconditions_met();
    void setup_adjacency();
    void setup_randomized_adjacency();

public:
    Grid();
    Grid(uint32_t width, uint32_t height);
    
    std::vector<Edge> get_randomized_edges();
    std::vector<std::vector<std::vector<Edge>>> get_randomized_adjacency();

    uint32_t get_width();
    uint32_t get_height();

    // unweighted, only list of accessible neighbors
    std::vector<Point> get_neighbors_of(uint32_t x, uint32_t y);
};

#include "grid.cpp"

#endif // _GRID_HPP_
