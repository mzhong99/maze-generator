#ifndef _DISJOINT_SETS_HPP_
#define _DISJOINT_SETS_HPP_

#include <vector>
#include <cstdint>

#include "point.hpp"

class DisjointSets {
private:
    uint32_t width, height;
    size_t number_of_sets;
    std::vector<std::vector<size_t>> sets;
    
    void fill_sets();

public:
    DisjointSets();
    DisjointSets(uint32_t width, uint32_t height);

    // add p2 to the set that has p1
    void join(const Point& p1, const Point& p2);
    bool is_joined(const Point& p1, const Point& p2) const;
    size_t find(const Point& point) const;
    std::vector<Point> elements(const size_t set_number) const;

    uint32_t get_width() const;
    uint32_t get_height() const;
};

#include "disjoint_sets.cpp"

#endif
