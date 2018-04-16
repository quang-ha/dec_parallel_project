#ifndef POINT_H
#define POINT_H

#include <cmath>

struct Point{
    double x = 0, y = 0;
    double u = 0;
    Point() : x{0}, y{0} {};
    Point(double x, double y) : x{x}, y{y} {};
    Point(double x, double y, double u) : x{x}, y{y}, u{u} {};
    void setxy(double _x, double _y){
       x = _x;
       y = _y;
    };
};

inline Point operator+(const Point& a, const Point& b) {
    return Point(a.x + b.x, a.y + b.y);
}

inline Point operator-(const Point& a, const Point& b) {
    return Point(a.x - b.x, a.y - b.y);
}

inline double distsq(const Point& a, const Point& b)
{
  double xdistsq = (a.x - b.x)*(a.x - b.x);
  double ydistsq = (a.y - b.y)*(a.y - b.y);
  return xdistsq+ydistsq;
}

inline double area(const Point& a,
		   const Point& b,
		   const Point& c)
{
  return 0.5*std::fabs(a.x*b.y + b.x*c.y + c.x*a.y - a.x*c.y - c.x*b.y - b.x*a.y);
}

#endif
