#ifndef GRID2D_H
#define GRID2D_H

#include <vector>
#include <tuple>
#include "Point.h"

class Grid2D {
public:
  Grid2D(Point& top_left, Point& bot_right, int Nx, int Ny);
  ~Grid2D();
  
  std::vector<std::vector<Point>> points;
  /* std::vector<std::vector<double>> weights; */
  int Nx, Ny;
  
  Point& operator()(int i, int j);
};

/* void set_weights(Grid2D& g); */
#endif
