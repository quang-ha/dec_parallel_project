#include "LaplacePeriodicGrid2D.h"

LaplacePeriodicGrid2D::LaplacePeriodicGrid2D(PeriodicGrid2D& _g) : g(_g) {
}
/*=======================================================================*/
LaplacePeriodicGrid2D::~LaplacePeriodicGrid2D() {
}
/*=======================================================================*/
/*=======================================================================*/
int LaplacePeriodicGrid2D::rows()
{
  return this->g.Nx*this->g.Ny;
}
/*=======================================================================*/
int LaplacePeriodicGrid2D::cols()
{
  return this->g.Nx*this->g.Ny;
}
/*=======================================================================*/
void LaplacePeriodicGrid2D::perform_op(double *x_in, double *x_out) {
  // Strides 1D vector into 2D matrix
  for (int i=0; i < this->g.Nx; ++i)
    for (int j=0; j < this->g.Ny; ++j)
      this->g(i, j).u = x_in[i*this->g.Nx + j];

  for (int i = 0; i < this->g.Nx; ++i) {
    for (int j = 0; j < this->g.Ny; ++j) {      
      // Edges frm center.
      double ed01sq = distsq(this->g(i, j), this->g(i-1, j));
      double ed02sq = distsq(this->g(i, j), this->g(i-1, j+1));
      double ed03sq = distsq(this->g(i, j), this->g(i, j+1));
      double ed04sq = distsq(this->g(i, j), this->g(i+1, j));
      double ed05sq = distsq(this->g(i, j), this->g(i+1, j-1));
      double ed06sq = distsq(this->g(i, j), this->g(i, j-1));
      
      double ed12sq = distsq(this->g(i-1, j), this->g(i-1, j+1));
      double ed23sq = distsq(this->g(i-1, j+1), this->g(i, j+1));
      double ed34sq = distsq(this->g(i, j+1), this->g(i+1, j));
      double ed45sq = distsq(this->g(i+1, j), this->g(i+1, j-1));
      double ed56sq = distsq(this->g(i+1, j-1), this->g(i, j-1));
      double ed61sq = distsq(this->g(i, j-1), this->g(i-1, j));
      
      double A012 = area(this->g(i, j), this->g(i-1, j), this->g(i, j+1));
      double A023 = area(this->g(i, j), this->g(i-1, j+1), this->g(i, j+1));
      double A034 = area(this->g(i, j), this->g(i, j+1), this->g(i+1, j));
      double A045 = area(this->g(i, j), this->g(i+1, j), this->g(i+1, j-1));
      double A056 = area(this->g(i, j), this->g(i+1, j-1), this->g(i, j-1));
      double A061 = area(this->g(i, j), this->g(i, j-1), this->g(i-1, j));
      
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
      double central_u = this->g(i, j).u;
      this->g(i, j).u = w01*(central_u - this->g(i-1, j).u) +
	w02*(central_u - this->g(i-1, j+1).u) +
	w03*(central_u - this->g(i, j+1).u) +
	w04*(central_u - this->g(i+1, j).u) +
	w05*(central_u - this->g(i+1, j-1).u) +
	w06*(central_u - this->g(i, j-1).u);
    }
  }
    
  // Strides 2D matrix back into 2D matrix
  for (int i=0; i < this->g.Nx; ++i)
    for (int j=0; j < this->g.Ny; ++j)
      x_out[i*this->g.Nx + j] = this->g(i, j).u;
}

/*=======================================================================*/
