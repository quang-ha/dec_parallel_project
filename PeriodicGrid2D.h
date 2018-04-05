#ifndef PERIODICGRID2D_H
#define PERIODICGRID2D_H

#include <vector>
#include <tuple>
#include "Point.h"

class PeriodicGrid2D {
public:
  PeriodicGrid2D(Point& top_left, Point& bot_right, int Nx, int Ny);
  ~PeriodicGrid2D();

  // Vector to store points
  std::vector<std::vector<Point>> points;

  // Get points from grid
  Point operator()(int i, int j);
  
  int Nx, Ny;
  double Lx, Ly;
};

#endif
