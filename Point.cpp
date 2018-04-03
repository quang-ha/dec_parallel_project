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

Point Point::operator+(Point&& other) {
  Point result(this->x + other.x, this->y + other.y);
  return result;
}

Point Point::operator-(Point& other) {
  Point result(this->x - other.x, this->y - other.y);
  return result;
}
