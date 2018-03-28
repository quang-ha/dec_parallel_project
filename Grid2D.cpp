#include "Grid2D.h"
#include <cstdio>

Grid2D::Grid2D(Point& top_left, Point& bot_right, int Nx, int Ny) {
  this->Nx = Nx;
  this->Ny = Ny;
  double x_step = (bot_right.x - top_left.x)/(Nx-1.0);
  double y_step = (bot_right.y - top_left.x)/(Ny-1.0);
  this->points.resize(Nx);
  for (int i=0; i<Nx; i++)
    this->points[i].resize(Ny);
  
  for (int i = 0; i < Nx; ++i) {
    for (int j = 0; j < Ny; ++j) {
      this->points[i][j].set(top_left.x + i*x_step, top_left.y + j*y_step);
    }
  }
  
  // this->weights.resize(Nx);
  // for (int i=0; i<Nx; i++)
  //   this->weights[i].resize(Ny);
}

Grid2D::~Grid2D() {
}

Point& Grid2D::operator()(int i, int j) {
  return this->points[i][j];
}
