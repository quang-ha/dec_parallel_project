#include "PeriodicGrid2D.h"
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
