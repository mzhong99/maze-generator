#ifndef _EDGE_HPP_
#define _EDGE_HPP_

#include <cstdint>
#include <string>
#include <sstream>
#include <iostream>

#include "point.hpp"

// this edge is directed and has weight
struct Edge {
    
    Point from, to;
    size_t weight;
    
    Edge(size_t weight=1) {
        this->weight = weight;
    }

    Edge(const Point& from, const Point& to, size_t weight=1) {
        this->from   = from;
        this->to     = to;
        this->weight = weight;
    }

    Edge(Edge& other, size_t weight) {
        this->from   = other.from;
        this->to     = other.to;
        this->weight = weight;
    }

    Edge reverse() const {
        Edge temp   = Edge(to, from);
        temp.weight = weight;
        return temp;
    }

    std::string to_string() const {
        std::stringstream ss;
        ss << from.to_string() << " -> " << to.to_string() << " (" << weight << ")";
        return ss.str();
    }

    friend std::ostream& operator<<(std::ostream& os, const Edge& edge) {
        os << edge.to_string();
        return os;
    }

    bool operator<(const Edge& rhs) const {
        return weight < rhs.weight;
    }

    bool operator>(const Edge& rhs) const {
        return weight > rhs.weight;
    }

    bool operator==(const Edge& rhs) const {
        return weight == rhs.weight;
    }
};


#endif // _EDGE_HPP_
