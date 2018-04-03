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
}
/*=======================================================================*/
Grid2D::~Grid2D() {
}
/*=======================================================================*/
int Grid2D::rows()
{
  return this->Nx*this->Ny;
}
/*=======================================================================*/
int Grid2D::cols()
{
  return this->Nx*this->Ny;
}
/*=======================================================================*/
Point& Grid2D::operator()(int i, int j) {
  return this->points[i][j];
}
/*=======================================================================*/
void Grid2D::perform_op(double *x_in, double *y_out)
{  
  double ed01sq, ed02sq, ed03sq, ed04sq, ed05sq, ed06sq;
  double ed12sq, ed23sq, ed34sq, ed45sq, ed56sq, ed61sq;
  double A012, A023, A034, A045, A056, A061;
  double w01, w02, w03, w04, w05, w06;

  // Create the 2D array
  double** u = new double*[this->Ny]; // row
  double** unew = new double*[this->Ny]; // row
  for (int i=0; i <= this->Ny-1; i++) { // column
    u[i] = new double[this->Nx];
    unew[i] = new double[this->Nx];
  } 

  // Strides 1D vector into 2D matrix
  for (int i=0; i <= this->Nx-1; i++)
    for (int j=0; j <= this->Ny-1; j++)
      u[i][j] = x_in[i*this->Nx + j]; 

  // Interior points
  for (int i = 1; i < this->Nx - 1; ++i)
    for (int j = 1; j < this->Ny - 1; ++j) {
      // Point& orig = this->points[i][j];
      // All nearest neighbour edges.
      ed01sq = distsq(this->points[i][j], this->points[i-1][j]);
      ed02sq = distsq(this->points[i][j], this->points[i-1][j+1]);
      ed03sq = distsq(this->points[i][j], this->points[i][j+1]);
      ed04sq = distsq(this->points[i][j], this->points[i+1][j]);
      ed05sq = distsq(this->points[i][j], this->points[i+1][j-1]);
      ed06sq = distsq(this->points[i][j], this->points[i][j-1]);

      // Circum-edges.
      ed12sq = distsq(this->points[i-1][j], this->points[i-1][j+1]);
      ed23sq = distsq(this->points[i-1][j+1], this->points[i][j+1]);
      ed34sq = distsq(this->points[i][j+1], this->points[i+1][j]);
      ed45sq = distsq(this->points[i+1][j], this->points[i+1][j-1]);
      ed56sq = distsq(this->points[i+1][j-1], this->points[i][j-1]);
      ed61sq = distsq(this->points[i][j-1], this->points[i-1][j]);

      // All nearest neighbour triangle areas.
      A012 = area(this->points[i][j], this->points[i-1][j], this->points[i][j+1]);
      A023 = area(this->points[i][j], this->points[i-1][j+1], this->points[i][j+1]);
      A034 = area(this->points[i][j], this->points[i][j+1], this->points[i+1][j]);
      A045 = area(this->points[i][j], this->points[i+1][j], this->points[i+1][j-1]);
      A056 = area(this->points[i][j], this->points[i+1][j-1], this->points[i][j-1]);
      A061 = area(this->points[i][j], this->points[i][j-1], this->points[i-1][j]);

      w01 = (ed06sq + ed61sq - ed01sq)/(8.0*A061) +
	(ed12sq + ed02sq - ed01sq)/(8.0*A012);
      w02 = (ed01sq + ed12sq - ed02sq)/(8.0*A012) +
	(ed23sq + ed03sq - ed02sq)/(8.0*A023);
      w03 = (ed02sq + ed23sq - ed03sq)/(8.0*A023) +
	(ed34sq + ed04sq - ed03sq)/(8.0*A034);
      w04 = (ed03sq + ed34sq - ed04sq)/(8.0*A034) +
	(ed45sq + ed05sq - ed04sq)/(8.0*A045);
      w05 = (ed04sq + ed45sq - ed05sq)/(8.0*A045) +
	(ed56sq + ed06sq - ed05sq)/(8.0*A056);
      w06 = (ed05sq + ed56sq - ed06sq)/(8.0*A056) +
	(ed61sq + ed01sq - ed06sq)/(8.0*A061);

      // Calculate the resulting 2D of the laplace operator
      unew[i][j] = w01*(u[i][j] - u[i-1][j]) +
	w02*(u[i][j] - u[i-1][j+1]) +
	w03*(u[i][j] - u[i][j+1]) +
	w04*(u[i][j] - u[i+1][j]) +
	w05*(u[i][j] - u[i+1][j-1]) +
	w06*(u[i][j] - u[i][j-1]);
    }

    // Top row points
    for (int j = 1; j < this->Ny -1; j++) {
      int i = 0;

      ed01sq = 0;
      ed02sq = 0;
      ed03sq = distsq(this->points[i][j], this->points[i][j+1]);
      ed04sq = distsq(this->points[i][j], this->points[i+1][j]);
      ed05sq = distsq(this->points[i][j], this->points[i+1][j-1]);
      ed06sq = distsq(this->points[i][j], this->points[i][j-1]);

      // Circum-edges.
      ed12sq = 0;
      ed23sq = 0;
      ed34sq = distsq(this->points[i][j+1], this->points[i+1][j]);
      ed45sq = distsq(this->points[i+1][j], this->points[i+1][j-1]);
      ed56sq = distsq(this->points[i+1][j-1], this->points[i][j-1]);
      ed61sq = 0;

      // All nearest neighbour triangle areas.
      A012 = 0;
      A023 = 0;
      A034 = area(this->points[i][j], this->points[i][j+1], this->points[i+1][j]);
      A045 = area(this->points[i][j], this->points[i+1][j], this->points[i+1][j-1]);
      A056 = area(this->points[i][j], this->points[i+1][j-1], this->points[i][j-1]);
      A061 = 0;

      w01 = 0 + 0;
      w02 = 0 + 0;
      w03 = 0 + (ed34sq + ed04sq - ed03sq)/(8.0*A034);
      w04 = (ed03sq + ed34sq - ed04sq)/(8.0*A034) +
	(ed45sq + ed05sq - ed04sq)/(8.0*A045);
      w05 = (ed04sq + ed45sq - ed05sq)/(8.0*A045) +
	(ed56sq + ed06sq - ed05sq)/(8.0*A056);
      w06 = (ed05sq + ed56sq - ed06sq)/(8.0*A056) + 0;

      unew[i][j] = w03*(u[i][j] - u[i][j+1]) +
	w04*(u[i][j] - u[i+1][j]) +
	w05*(u[i][j] - u[i+1][j-1]) +
	w06*(u[i][j] - u[i][j-1]);
    }

    // Bottom row points
    for (int j = 1; j < this->Ny -1; j++) {
      int i = this->Nx - 1;

      ed01sq = distsq(this->points[i][j], this->points[i-1][j]);
      ed02sq = distsq(this->points[i][j], this->points[i-1][j+1]);
      ed03sq = distsq(this->points[i][j], this->points[i][j+1]);
      ed04sq = 0;
      ed05sq = 0;
      ed06sq = distsq(this->points[i][j], this->points[i][j-1]);

      // Circum-edges.
      ed12sq = distsq(this->points[i-1][j], this->points[i-1][j+1]);
      ed23sq = distsq(this->points[i-1][j+1], this->points[i][j+1]);
      ed34sq = 0;
      ed45sq = 0;
      ed56sq = 0;
      ed61sq = distsq(this->points[i][j-1], this->points[i-1][j]);

      // All nearest neighbour triangle areas.
      A012 = area(this->points[i][j], this->points[i-1][j], this->points[i][j+1]);
      A023 = area(this->points[i][j], this->points[i-1][j+1], this->points[i][j+1]);
      A034 = 0;
      A045 = 0;
      A056 = 0;
      A061 = area(this->points[i][j], this->points[i][j-1], this->points[i-1][j]);

      w01 = (ed06sq + ed61sq - ed01sq)/(8.0*A061) +
	(ed12sq + ed02sq - ed01sq)/(8.0*A012);
      w02 = (ed01sq + ed12sq - ed02sq)/(8.0*A012) +
	(ed23sq + ed03sq - ed02sq)/(8.0*A023);
      w03 = (ed02sq + ed23sq - ed03sq)/(8.0*A023) + 0;
      w04 = 0 + 0;
      w05 = 0 + 0;
      w06 = 0 + (ed61sq + ed01sq - ed06sq)/(8.0*A061);

      unew[i][j] = w01*(u[i][j] - u[i-1][j]) +
	w02*(u[i][j] - u[i-1][j+1]) +
	w03*(u[i][j] - u[i][j+1]) +
	w06*(u[i][j] - u[i][j-1]);
    }

    // Leftmost column weights

    for (int i = 1; i < this->Ny - 1; i++) {
      int j = 0;

      ed01sq = distsq(this->points[i][j], this->points[i-1][j]);
      ed02sq = distsq(this->points[i][j], this->points[i-1][j+1]);
      ed03sq = distsq(this->points[i][j], this->points[i][j+1]);
      ed04sq = distsq(this->points[i][j], this->points[i+1][j]);
      ed05sq = 0;
      ed06sq = 0;

      // Circum-edges.
      ed12sq = distsq(this->points[i-1][j], this->points[i-1][j+1]);
      ed23sq = distsq(this->points[i-1][j+1], this->points[i][j+1]);
      ed34sq = distsq(this->points[i][j+1], this->points[i+1][j]);
      ed45sq = 0;
      ed56sq = 0;
      ed61sq = 0;

      // All nearest neighbour triangle areas.
      A012 = area(this->points[i][j], this->points[i-1][j], this->points[i][j+1]);
      A023 = area(this->points[i][j], this->points[i-1][j+1], this->points[i][j+1]);
      A034 = area(this->points[i][j], this->points[i][j+1], this->points[i+1][j]);
      A045 = 0;
      A056 = 0;
      A061 = 0;

      w01 = 0 + (ed12sq + ed02sq - ed01sq)/(8.0*A012);
      w02 = (ed01sq + ed12sq - ed02sq)/(8.0*A012) +
	(ed23sq + ed03sq - ed02sq)/(8.0*A023);
      w03 = (ed02sq + ed23sq - ed03sq)/(8.0*A023) +
	(ed34sq + ed04sq - ed03sq)/(8.0*A034);
      w04 = (ed03sq + ed34sq - ed04sq)/(8.0*A034) + 0;
      w05 = 0 + 0;
      w06 = 0 + 0;

      unew[i][j] = w01*(u[i][j] - u[i-1][j]) +
	w02*(u[i][j] - u[i-1][j+1]) +
	w03*(u[i][j] - u[i][j+1]) +
	w04*(u[i][j] - u[i+1][j]);
    }

    // Rightmost column weights

    for (int i = 1; i < this->Nx -1; i++) {
      int j = this->Ny - 1;

      ed01sq = distsq(this->points[i][j], this->points[i-1][j]);
      ed02sq = 0;
      ed03sq = 0;
      ed04sq = distsq(this->points[i][j], this->points[i+1][j]);
      ed05sq = distsq(this->points[i][j], this->points[i+1][j-1]);
      ed06sq = distsq(this->points[i][j], this->points[i][j-1]);

      // Circum-edges.
      ed12sq = 0;
      ed23sq = 0;
      ed34sq = 0;
      ed45sq = distsq(this->points[i+1][j], this->points[i+1][j-1]);
      ed56sq = distsq(this->points[i+1][j-1], this->points[i][j-1]);
      ed61sq = distsq(this->points[i][j-1], this->points[i-1][j]);

      // All nearest neighbour triangle areas.
      A012 = 0;
      A023 = 0;
      A034 = 0;
      A045 = area(this->points[i][j], this->points[i+1][j], this->points[i+1][j-1]);
      A056 = area(this->points[i][j], this->points[i+1][j-1], this->points[i][j-1]);
      A061 = area(this->points[i][j], this->points[i][j-1], this->points[i-1][j]);

      w01 = (ed06sq + ed61sq - ed01sq)/(8.0*A061) + 0;
      w02 = 0 + 0;
      w03 = 0 + 0;
      w04 = 0 + (ed45sq + ed05sq - ed04sq)/(8.0*A045);
      w05 = (ed04sq + ed45sq - ed05sq)/(8.0*A045) +
	(ed56sq + ed06sq - ed05sq)/(8.0*A056);
      w06 = (ed05sq + ed56sq - ed06sq)/(8.0*A056) +
	(ed61sq + ed01sq - ed06sq)/(8.0*A061);

      unew[i][j] = w01*(u[i][j] - u[i-1][j]) +
	w04*(u[i][j] - u[i+1][j]) +
	w05*(u[i][j] - u[i+1][j-1]) +
	w06*(u[i][j] - u[i][j-1]);
    }

    // ====================== Corner Points.
    // Top left. i = 0, j = 0.
    int i = 0, j = 0;
    ed01sq = 0;
    ed02sq = 0;
    ed03sq = distsq(this->points[i][j], this->points[i][j+1]);
    ed04sq = distsq(this->points[i][j], this->points[i+1][j]);
    ed05sq = 0;
    ed06sq = 0;

    // Circum-edges.
    ed12sq = 0;
    ed23sq = 0;
    ed34sq = distsq(this->points[i][j+1], this->points[i+1][j]);
    ed45sq = 0;
    ed56sq = 0;
    ed61sq = 0;

    // All nearest neighbour triangle areas.
    A012 = 0;
    A023 = 0;
    A034 = area(this->points[i][j], this->points[i][j+1], this->points[i+1][j]);
    A045 = 0;
    A056 = 0;
    A061 = 0;

    w01 = 0;
    w02 = 0;
    w03 = 0 + (ed34sq + ed04sq - ed03sq)/(8.0*A034);
    w04 = (ed03sq + ed34sq - ed04sq)/(8.0*A034) + 0;
    w05 = 0;
    w06 = 0;
    unew[i][j] = w03*(u[i][j] - u[i][j+1]) + w04*(u[i][j] - u[i+1][j]);

    // Top right. i = 0; j = this->Nx - 1
    i = 0; j = this->Ny -1;
    ed01sq = 0;
    ed02sq = 0;
    ed03sq = 0;
    ed04sq = distsq(this->points[i][j], this->points[i+1][j]);
    ed05sq = distsq(this->points[i][j], this->points[i+1][j-1]);
    ed06sq = distsq(this->points[i][j], this->points[i][j-1]);

    // Circum-edges.
    ed12sq = 0;
    ed23sq = 0;
    ed34sq = 0;
    ed45sq = distsq(this->points[i+1][j], this->points[i+1][j-1]);
    ed56sq = distsq(this->points[i+1][j-1], this->points[i][j-1]);
    ed61sq = 0;

    // All nearest neighbour triangle areas.
    A012 = 0;
    A023 = 0;
    A034 = 0;
    A045 = area(this->points[i][j], this->points[i+1][j], this->points[i+1][j-1]);
    A056 = area(this->points[i][j], this->points[i+1][j-1], this->points[i][j-1]);
    A061 = 0;

    w01 = 0;
    w02 = 0;
    w03 = 0;
    w04 = 0 + (ed45sq + ed05sq - ed04sq)/(8.0*A045);
    w05 = (ed04sq + ed45sq - ed05sq)/(8.0*A045) +
      (ed56sq + ed06sq - ed05sq)/(8.0*A056);
    w06 = (ed05sq + ed56sq - ed06sq)/(8.0*A056) + 0;
    unew[i][j] = w04*(u[i][j] - u[i+1][j]) +
      w05*(u[i][j] - u[i+1][j-1]) +
      w06*(u[i][j] - u[i][j-1]);


    // Bot left. i = this->Nx - 1, j = 0;
    i = this->Nx - 1; j = 0;
    ed01sq = distsq(this->points[i][j], this->points[i-1][j]);
    ed02sq = distsq(this->points[i][j], this->points[i-1][j+1]);
    ed03sq = distsq(this->points[i][j], this->points[i][j+1]);
    ed04sq = 0;
    ed05sq = 0;
    ed06sq = 0;

    // Circum-edges.
    ed12sq = distsq(this->points[i-1][j], this->points[i-1][j+1]);
    ed23sq = distsq(this->points[i-1][j+1], this->points[i][j+1]);
    ed34sq = 0;
    ed45sq = 0;
    ed56sq = 0;
    ed61sq = 0;

    // All nearest neighbour triangle areas.
    A012 = area(this->points[i][j], this->points[i-1][j], this->points[i][j+1]);
    A023 = area(this->points[i][j], this->points[i-1][j+1], this->points[i][j+1]);
    A034 = 0;
    A045 = 0;
    A056 = 0;
    A061 = 0;

    w01 = 0 + (ed12sq + ed02sq - ed01sq)/(8.0*A012);
    w02 = (ed01sq + ed12sq - ed02sq)/(8.0*A012) +
      (ed23sq + ed03sq - ed02sq)/(8.0*A023);
    w03 = (ed02sq + ed23sq - ed03sq)/(8.0*A023) + 0;
    w04 = 0;
    w05 = 0;
    w06 = 0;
    unew[i][j] = w01*(u[i][j] - u[i-1][j]) +
      w02*(u[i][j] - u[i-1][j+1]) +
      w03*(u[i][j] - u[i][j+1]) ;

    // Bot right. i = this->Nx -1; j = this->Ny - 1;
    i = this->Nx -1; j = this->Ny - 1;
    ed01sq = distsq(this->points[i][j], this->points[i-1][j]);
    ed02sq = 0;
    ed03sq = 0;
    ed04sq = 0;
    ed05sq = 0;
    ed06sq = distsq(this->points[i][j], this->points[i][j-1]);

    // Circum-edges.
    ed12sq = 0;
    ed23sq = 0;
    ed34sq = 0;
    ed45sq = 0;
    ed56sq = 0;
    ed61sq = distsq(this->points[i][j-1], this->points[i-1][j]);

    // All nearest neighbour triangle areas.
    A012 = 0;
    A023 = 0;
    A034 = 0;
    A045 = 0;
    A056 = 0;
    A061 = area(this->points[i][j], this->points[i][j-1], this->points[i-1][j]);

    w01 = (ed06sq + ed61sq - ed01sq)/(8.0*A061) + 0;
    w02 = 0;
    w03 = 0;
    w04 = 0;
    w05 = 0;
    w06 = 0 + (ed61sq + ed01sq - ed06sq)/(8.0*A061);
    unew[i][j] = w01*(u[i][j] - u[i-1][j]) +
      w06*(u[i][j] - u[i][j-1]);

    // Strides 2D matrix back into 2D matrix
    for (int i=0; i <= this->Nx-1; i++)
      for (int j=0; j <= this->Ny-1; j++)
	y_out[i*this->Nx + j] = unew[i][j];
}
