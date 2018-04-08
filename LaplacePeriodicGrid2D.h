#ifndef LAPLACE_PERIODICGRID2D_H
#define LAPLACE_PERIODICGRID2D_H

#include <vector>
#include <tuple>
#include "Point.h"
#include "PeriodicGrid2D.h"

class LaplacePeriodicGrid2D {
public:
  PeriodicGrid2D g;
  LaplacePeriodicGrid2D(PeriodicGrid2D& g_);
  ~LaplacePeriodicGrid2D();

  // Rows and Cols for the eigenvalue solver
  int rows();
  int cols();

  // Laplace matrix operatrion
  void perform_op(double *x_in, double *y_out);
  void print(int i, int j);


};

#endif
