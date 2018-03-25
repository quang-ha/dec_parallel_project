#include "Point.h"

// Constructor
Point::Point()
{
}

Point::Point(double _x, double _y) {
    this->x = _x;
    this->y = _y;
}
// Deconstructor
Point::~Point()
{
}

// Set value
void Point::set(double _x, double _y)
{
  this->x = _x;
  this->y = _y;
}
