#include <cmath>
#include <iostream>
#include <vector>

#include "Point.h"

// Constructor
Point::Point()
{
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
