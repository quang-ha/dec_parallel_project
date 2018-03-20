#ifndef point_hpp
#define point_hpp

#include <cmath>

class Point {
public:
    double x, y;
    Point(double x, double y);
};

inline double dist(const Point& a, const Point& b) {
    double xdistsq = (a.x - b.x)*(a.x - b.x);
    double ydistsq = (a.y - b.y)*(a.y - b.y);
    // std::cout << xdistsq << '\t' << ydistsq << '\t';
    return sqrt(xdistsq+ydistsq);
}

inline double area(const Point& a, const Point& b, const Point& c) {
    return 0.5 * abs( a.x*b.y + b.x*c.y + c.x*a.y - a.x*c.y - c.x*b.y - b.x*a.y);
}
#endif
