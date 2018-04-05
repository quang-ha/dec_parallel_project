#ifndef LAPLACE_PERIODICGRID2D_H
#define LAPLCE_PERIODICGRID2D_H

#include <vector>
#include <tuple>
#include "Point.h"
#include "PeriodicGrid2D.h"

class LaplacePeriodicGrid2D {
public:
  LaplacePeriodicGrid2D(PeriodicGrid2D& _g);
  ~LaplacePeriodicGrid2D();

  // Rows and Cols for the eigenvalue solver
  int rows();
  int cols();

  // Laplace matrix operatrion
  void perform_op(double *x_in, double *y_out);
  
  PeriodicGrid2D g;
};

#endif
