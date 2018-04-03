#ifndef POINT_H
#define POINT_H

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
  Point operator+(Point&& other);
  Point operator-(Point& other);
};

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
