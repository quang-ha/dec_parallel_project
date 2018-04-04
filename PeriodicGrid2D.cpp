#include "PeriodicGrid2D.hpp"
#include <cstdio>

PeriodicGrid2D::PeriodicGrid2D(Point& top_left, Point& bot_right, int Nx, int Ny) {
  this->Nx = Nx;
  this->Ny = Ny;
  this->Lx = bot_right.x - top_left.x;
  this->Ly = bot_right.y - top_left.y;
  double dLx = (bot_right.x - top_left.x)/(Nx-1.0);
  double dLy = (bot_right.y - top_left.x)/(Ny-1.0);

  this->points.resize(Nx);
  for (int i=0; i<Nx; i++)
    this->points[i].resize(Ny);

  for (int i = 0; i < Nx; ++i) {
    for (int j = 0; j < Ny; ++j) {
      this->points[i][j].set(top_left.x + i*dLx, top_left.y + j*dLy);
    }
  }
}
/*=======================================================================*/
PeriodicGrid2D::~PeriodicGrid2D() {
}
/*=======================================================================*/
int PeriodicGrid2D::rows()
{
  return this->Nx*this->Ny;
}
/*=======================================================================*/
int PeriodicGrid2D::cols()
{
  return this->Nx*this->Ny;
}
/*=======================================================================*/
Point PeriodicGrid2D::operator()(int i, int j) {

  // These bools might be useful in wrapping the physical coordinates around.
  double wrapped_x_offset = 0, wrapped_y_offset = 0;
  Point result;
    // Wrapping around i = Nx -1
  if (i > this->Nx - 1) {
    i = i%(this->Nx - 1);
    wrapped_x_offset = this->Lx;
  }
  else if (i < 0) {
    i = i%(this->Nx - 1) + Nx;
    wrapped_x_offset = - this->Lx;
  }
  if (j > this->Ny - 1) {
    j = j%(this->Ny - 1);
    wrapped_y_offset = this->Ly;
  }
  else if (j < 0) {
    j = j%(this->Ny - 1) + Ny;
    wrapped_y_offset = - this->Ly;
  }
  if (wrapped_x_offset == 0 && wrapped_y_offset == 0)
    return this->points[i][j];
  else
    return this->points[i][j] + Point(wrapped_x_offset, wrapped_y_offset);

}

void laplace_op(PeriodicGrid2D &g, double *x_in, double *x_out) {

  // Strides 1D vector into 2D matrix
  for (int i=0; i < g.Nx; ++i)
    for (int j=0; j < g.Ny; ++j)
      g(i, j).u = x_in[i*g.Nx + j];

  for (int i = 0; i < g.Nx; ++i) {
    for (int j = 0; j < g.Ny; ++j) {

      // Edges frm center.
      double ed01sq = distsq(g(i, j), g(i-1, j));
      double ed02sq = distsq(g(i, j), g(i-1, j+1));
      double ed03sq = distsq(g(i, j), g(i, j+1));
      double ed04sq = distsq(g(i, j), g(i+1, j));
      double ed05sq = distsq(g(i, j), g(i+1, j-1));
      double ed06sq = distsq(g(i, j), g(i, j-1));

      double ed12sq = distsq(g(i-1, j), g(i-1, j+1));
      double ed23sq = distsq(g(i-1, j+1), g(i, j+1));
      double ed34sq = distsq(g(i, j+1), g(i+1, j));
      double ed45sq = distsq(g(i+1, j), g(i+1, j-1));
      double ed56sq = distsq(g(i+1, j-1), g(i, j-1));
      double ed61sq = distsq(g(i, j-1), g(i-1, j));

      double A012 = area(g(i, j), g(i-1, j), g(i, j+1));
      double A023 = area(g(i, j), g(i-1, j+1), g(i, j+1));
      double A034 = area(g(i, j), g(i, j+1), g(i+1, j));
      double A045 = area(g(i, j), g(i+1, j), g(i+1, j-1));
      double A056 = area(g(i, j), g(i+1, j-1), g(i, j-1));
      double A061 = area(g(i, j), g(i, j-1), g(i-1, j));

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
  double central_u = g(i, j).u
  g(i, j).u = w01*(central_u - g(i-1, j).u) +
w02*(central_u - g(i-1, j+1).u) +
w03*(central_u - g(i, j+1).u) +
w04*(central_u - g(i+1, j).u) +
w05*(central_u - g(i+1, j-1).u) +
w06*(central_u - g(i, j-1).u);

    }
  }


  // Strides 2D matrix back into 2D matrix
  for (int i=0; i < g.Nx; ++i)
    for (int j=0; j < g.Ny; ++j)
      x_out[i*g.Nx + j] = g(i, j).u;

}
