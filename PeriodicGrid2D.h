#ifndef PERIODICGRID2D_H
#define PERIODICGRID2D_H

#include <vector>
#include <tuple>
#include "Point.h"

class PeriodicGrid2D {
public:
  PeriodicGrid2D(Point& top_left, Point& bot_right, int Nx, int Ny);
  ~PeriodicGrid2D();

  // Rows and Cols for the eigenvalue solver
  int rows();
  int cols();

  // Vector to store points
  std::vector<std::vector<Point>> points;
  /* std::vector<std::vector<double>> weights; */

  // Get points from grid
  Point operator()(int i, int j);


  int Nx, Ny;
  double Lx, Ly;
};

/* void set_weights(Grid2D& g); */

// Returns a matvec the laplacian operator on the grid.
void laplace_op(PeriodicGrid2D &g, double *x_in, double *x_out);

#endif
