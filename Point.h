#ifndef POINT_HPP
#define POINT_HPP

#include <cmath>
#include <stdlib.h>
#include <iostream>
class Point
{
public:
    Point();
    Point(double _x, double _y);
    ~Point();
    double x, y;
    void set(double _x, double _y);
};

inline double dist(const Point& a, const Point& b)
{
  double xdistsq = (a.x - b.x)*(a.x - b.x);
  double ydistsq = (a.y - b.y)*(a.y - b.y);
  return sqrt(xdistsq+ydistsq);
}

inline double area(const Point& a,
		   const Point& b,
		   const Point& c)
{
    return 0.5*abs(a.x*b.y + b.x*c.y + c.x*a.y - a.x*c.y - c.x*b.y - b.x*a.y);
}

#endif