#include <cstdio>
#include "LaplacePeriodicGrid2D.h"

LaplacePeriodicGrid2D::LaplacePeriodicGrid2D(PeriodicGrid2D& _g) : g{_g} {
}
/*=======================================================================*/
LaplacePeriodicGrid2D::~LaplacePeriodicGrid2D() {
}
/*=======================================================================*/
int LaplacePeriodicGrid2D::rows()
{
  return g.Nx*g.Ny;
}
/*=======================================================================*/
int LaplacePeriodicGrid2D::cols()
{
  return g.Nx*g.Ny;
}
/*=======================================================================*/
void LaplacePeriodicGrid2D::perform_op(double *x_in, double *x_out) {
  // Strides 1D vector into 2D matrix
  
  double temp[g.Nx][g.Ny];

  for (int i=0; i < g.Nx; ++i)
    for (int j=0; j < g.Ny; ++j)
      g.setu(i, j, x_in[i*g.Nx + j]);

  // Set up a temporary 2D array to store the update value
  #pragma omp parallel for simd schedule(static) collapse(2)
  for (int i = 0; i < g.Nx; ++i) {
    for (int j = 0; j < g.Ny; ++j) {
      // Edges from center.
      double ed01sq = distsq(g.getxy(i, j), g.getxy(i-1, j));
      double ed02sq = distsq(g.getxy(i, j), g.getxy(i-1, j+1));
      double ed03sq = distsq(g.getxy(i, j), g.getxy(i, j+1));
      double ed04sq = distsq(g.getxy(i, j), g.getxy(i+1, j));
      double ed05sq = distsq(g.getxy(i, j), g.getxy(i+1, j-1));
      double ed06sq = distsq(g.getxy(i, j), g.getxy(i, j-1));

      double ed12sq = distsq(g.getxy(i-1, j), g.getxy(i-1, j+1));
      double ed23sq = distsq(g.getxy(i-1, j+1), g.getxy(i, j+1));
      double ed34sq = distsq(g.getxy(i, j+1), g.getxy(i+1, j));
      double ed45sq = distsq(g.getxy(i+1, j), g.getxy(i+1, j-1));
      double ed56sq = distsq(g.getxy(i+1, j-1), g.getxy(i, j-1));
      double ed61sq = distsq(g.getxy(i, j-1), g.getxy(i-1, j));

      double A012 = area(g.getxy(i, j), g.getxy(i-1, j), g.getxy(i, j+1));
      double A023 = area(g.getxy(i, j), g.getxy(i-1, j+1), g.getxy(i, j+1));
      double A034 = area(g.getxy(i, j), g.getxy(i, j+1), g.getxy(i+1, j));
      double A045 = area(g.getxy(i, j), g.getxy(i+1, j), g.getxy(i+1, j-1));
      double A056 = area(g.getxy(i, j), g.getxy(i+1, j-1), g.getxy(i, j-1));
      double A061 = area(g.getxy(i, j), g.getxy(i, j-1), g.getxy(i-1, j));

      double w01 = (ed06sq + ed61sq - ed01sq)/(8.0*A061) +
	(ed12sq + ed02sq - ed01sq)/(8.0*A012);
      double w02 = (ed01sq + ed12sq - ed02sq)/(8.0*A012) +
	(ed23sq + ed03sq - ed02sq)/(8.0*A023);
      double w03 = (ed02sq + ed23sq - ed03sq)/(8.0*A023) +
	(ed34sq + ed04sq - ed03sq)/(8.0*A034);
      double w04 = (ed03sq + ed34sq - ed04sq)/(8.0*A034) +
	(ed45sq + ed05sq - ed04sq)/(8.0*A045);
      double w05 = (ed04sq + ed45sq - ed05sq)/(8.0*A045) +
	(ed56sq + ed06sq - ed05sq)/(8.0*A056);
      double w06 = (ed05sq + ed56sq - ed06sq)/(8.0*A056) +
	(ed61sq + ed01sq - ed06sq)/(8.0*A061);

      // Calculate the resulting 2D of the laplace operator      
      temp[i][j] = w01*(g(i, j).u - g(i-1, j).u) +
	w02*(g(i, j).u - g(i-1, j+1).u) +
	w03*(g(i, j).u - g(i, j+1).u) +
	w04*(g(i, j).u - g(i+1, j).u) +
	w05*(g(i, j).u - g(i+1, j-1).u) +
	w06*(g(i, j).u - g(i, j-1).u);
    }
  }

  // Strides 2D matrix back into 2D matrix
  for (int i=0; i < g.Nx; ++i)
    for (int j=0; j < g.Ny; ++j)
      {
	g.setu(i, j, temp[i][j]);
	x_out[i*g.Nx + j] = g(i, j).u;
      }
}

/*=======================================================================*/
