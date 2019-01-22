#ifndef _POINT_HPP_
#define _POINT_HPP_

#include <cstdint>
#include <string>
#include <sstream>
#include <iostream>

// because i don't want to use std::pair, first/second naming convention is bad
struct Point {
    
    uint32_t x, y;
    
    Point(uint32_t x=0, uint32_t y=0) {
        this->x = x;
        this->y = y;
    }
    
    Point down() const {
        return Point(x, y + 1);
    }
    
    Point up() const {
        return Point(x, y - 1);
    }
    
    Point left() const {
        return Point(x - 1, y);
    }

    Point right() const {
        return Point(x + 1, y);
    }
    
    std::string to_string() const {
        std::stringstream ss;
        ss << "(" << x << ", " << y << ")";
        return ss.str();
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& point) {
        os << point.to_string();
        return os;
    }

};

bool operator==(const Point& lhs, const Point& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator!=(const Point& lhs, const Point& rhs) {
    return !(lhs == rhs);
}
#endif // _POINT_HPP_

