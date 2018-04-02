#ifndef GRID2D_H
#define GRID2D_H

#include <vector>
#include <tuple>
#include "Point.h"

class Grid2D {
public:
  Grid2D(Point& top_left, Point& bot_right, int Nx, int Ny);
  ~Grid2D();

  // Vector to store points
  std::vector<std::vector<Point>> points;
  /* std::vector<std::vector<double>> weights; */
  int Nx, Ny;

  // Get points from grid
  Point& operator()(int i, int j);

  // Laplace matrix operatrion
  void perform_op(double *x_in, double *y_out); 
};

/* void set_weights(Grid2D& g); */
#endif
