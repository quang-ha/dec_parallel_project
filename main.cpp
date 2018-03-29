#include <stdio.h>
#include <vector>
#include "Point.h"
#include "Grid2D.h"

#define N 3 // Number of points in each direction
#define LOW 0.0 // Low boundary
#define HIGH 1.0 // High boundary

void MatOp(Grid2D& g, double* u0, double* u1); // Laplace operation on 2D vector

int main(int argc, char* argv[])
{
  // Trying out the Grid2D object.
  Point a(LOW, LOW);
  Point b(HIGH, HIGH);
  Grid2D g(a, b, N+2, N+2);

  // for (int i=0; i<=N+1; i++)
  //   for (int j=0; j<N+1; j++)
  //       printf("Index i %d j %d and x-coord %f y-coord %f \n",
  // 	       i, j, g(i, j).x, g(i, j).y);

  // Create array of pointers that point to more array
  double* x = new double[N*N];
  double* y = new double[N*N];

  for (int i=0; i<N; i++)
    for (int j=0; j<N; j++)
      x[i*N + j] = i*N + j;

  printf("x \n");
  for (int i=0; i<N*N; i++)
    printf("%f ", x[i]);

  printf("\n");

  MatOp(g, x, y);

  printf("y \n");
  for (int i=0; i<N*N; i++)
    printf("%f ", y[i]);

  printf("\n");

  return 0;
}

/*====================================================================================*/

void MatOp(Grid2D& g, double* u0, double* u1) {
  double ed01sq, ed02sq, ed03sq, ed04sq, ed05sq, ed06sq;
  double ed12sq, ed23sq, ed34sq, ed45sq, ed56sq, ed61sq;
  double A012, A023, A034, A045, A056, A061;
  double w01, w02, w03, w04, w05, w06;

  // Create the 2D array
  double** u = new double*[g.Ny]; // row
  double** unew = new double*[g.Ny]; // row
  for (int i=0; i <= g.Ny-1; i++) { u[i] = new double[g.Nx]; unew[i] = new double[g.Nx];}; // column

  // Strides 1D vector into 2D matrix
  for (int i=0; i <= g.Nx-1; i++)
    {
      for (int j=0; j <= g.Ny-1; j++)
	{
	  // Create periodic case
	  if ((i==0) && (j==0)) // Top left point
	    u[i][j] = u0[(g.Nx-2)*(g.Ny-2) - 1];
	  else if ((i == g.Nx-1) && (j == g.Ny-1)) // Bottom right point
	    u[i][j] = u0[0];
	  else if (i == 0)
	    {
	      if (j == g.Ny - 1) // Top right point
		u[i][j] = u0[(g.Nx-2)*(g.Nx-3)];
	      else // All other point along the top
		u[i][j] = u0[(g.Nx-3)*(g.Nx-2) + j-1];
	    }
	  else if (j == 0)
	    {
	      if (i == g.Nx - 1) // Bottom left point
		u[i][j] = u0[g.Nx-3];
	      else // All other points on the left
		u[i][j] = u0[(g.Nx-2)*i - 1];
	    }
	  else if ((i == g.Nx-1) && (j != 0) && (j != g.Ny-1)) // Bottom row
	    u[i][j] = u0[j-1];
	  else if ((j == g.Ny-1) && (i != 0) && (i != g.Nx-1)) // Right column
	    u[i][j] = u0[(i-1)*(g.Nx-2)];
	  else
	    u[i][j] = u0[(i-1)*(g.Nx-2) + (j-1)]; // All other points
	}
    }

  // Interior points
  for (int i = 1; i < g.Nx - 1; ++i)
    for (int j = 1; j < g.Ny - 1; ++j) {
      // Point& orig = g(i, j);
      // All nearest neighbour edges.
      ed01sq = distsq(g(i, j), g(i-1, j));
      ed02sq = distsq(g(i, j), g(i-1, j+1));
      ed03sq = distsq(g(i, j), g(i, j+1));
      ed04sq = distsq(g(i, j), g(i+1, j));
      ed05sq = distsq(g(i, j), g(i+1, j-1));
      ed06sq = distsq(g(i, j), g(i, j-1));

      // Circum-edges.
      ed12sq = distsq(g(i-1, j), g(i-1, j+1));
      ed23sq = distsq(g(i-1, j+1), g(i, j+1));
      ed34sq = distsq(g(i, j+1), g(i+1, j));
      ed45sq = distsq(g(i+1, j), g(i+1, j-1));
      ed56sq = distsq(g(i+1, j-1), g(i, j-1));
      ed61sq = distsq(g(i, j-1), g(i-1, j));

      // All nearest neighbour triangle areas.
      A012 = area(g(i, j), g(i-1, j), g(i, j+1));
      A023 = area(g(i, j), g(i-1, j+1), g(i, j+1));
      A034 = area(g(i, j), g(i, j+1), g(i+1, j));
      A045 = area(g(i, j), g(i+1, j), g(i+1, j-1));
      A056 = area(g(i, j), g(i+1, j-1), g(i, j-1));
      A061 = area(g(i, j), g(i, j-1), g(i-1, j));

      w01 = (ed06sq + ed61sq - ed01sq)/(8.0*A061) + (ed12sq + ed02sq - ed01sq)/(8.0*A012);
      w02 = (ed01sq + ed12sq - ed02sq)/(8.0*A012) + (ed23sq + ed03sq - ed02sq)/(8.0*A023);
      w03 = (ed02sq + ed23sq - ed03sq)/(8.0*A023) + (ed34sq + ed04sq - ed03sq)/(8.0*A034);
      w04 = (ed03sq + ed34sq - ed04sq)/(8.0*A034) + (ed45sq + ed05sq - ed04sq)/(8.0*A045);
      w05 = (ed04sq + ed45sq - ed05sq)/(8.0*A045) + (ed56sq + ed06sq - ed05sq)/(8.0*A056);
      w06 = (ed05sq + ed56sq - ed06sq)/(8.0*A056) + (ed61sq + ed01sq - ed06sq)/(8.0*A061);

      // Calculate the resulting 2D of the laplace operator
      unew[i][j] = w01*(u[i][j] - u[i-1][j]) +
	w02*(u[i][j] - u[i-1][j+1]) +
	w03*(u[i][j] - u[i][j+1]) +
	w04*(u[i][j] - u[i+1][j]) +
	w05*(u[i][j] - u[i+1][j-1]) +
	w06*(u[i][j] - u[i][j-1]);
    }

    // Top row points
    for (int j = 1; j < g.Ny -1; j++) {
        int i = 0;

        ed01sq = 0;
        ed02sq = 0;
        ed03sq = distsq(g(i, j), g(i, j+1));
        ed04sq = distsq(g(i, j), g(i+1, j));
        ed05sq = distsq(g(i, j), g(i+1, j-1));
        ed06sq = distsq(g(i, j), g(i, j-1));

        // Circum-edges.
        ed12sq = 0;
        ed23sq = 0;
        ed34sq = distsq(g(i, j+1), g(i+1, j));
        ed45sq = distsq(g(i+1, j), g(i+1, j-1));
        ed56sq = distsq(g(i+1, j-1), g(i, j-1));
        ed61sq = 0;

        // All nearest neighbour triangle areas.
        A012 = 0;
        A023 = 0;
        A034 = area(g(i, j), g(i, j+1), g(i+1, j));
        A045 = area(g(i, j), g(i+1, j), g(i+1, j-1));
        A056 = area(g(i, j), g(i+1, j-1), g(i, j-1));
        A061 = 0;

        w01 = 0 + 0;
        w02 = 0 + 0;
        w03 = 0 + (ed34sq + ed04sq - ed03sq)/(8.0*A034);
        w04 = (ed03sq + ed34sq - ed04sq)/(8.0*A034) + (ed45sq + ed05sq - ed04sq)/(8.0*A045);
        w05 = (ed04sq + ed45sq - ed05sq)/(8.0*A045) + (ed56sq + ed06sq - ed05sq)/(8.0*A056);
        w06 = (ed05sq + ed56sq - ed06sq)/(8.0*A056) + 0;

        unew[i][j] = w03*(u[i][j] - u[i][j+1]) +
        w04*(u[i][j] - u[i+1][j]) +
        w05*(u[i][j] - u[i+1][j-1]) +
        w06*(u[i][j] - u[i][j-1]);
    }

    // Bottom row points
    for (int j = 1; j < g.Ny -1; j++) {
        int i = g.Nx - 1;

        ed01sq = distsq(g(i, j), g(i-1, j));
        ed02sq = distsq(g(i, j), g(i-1, j+1));
        ed03sq = distsq(g(i, j), g(i, j+1));
        ed04sq = 0;
        ed05sq = 0;
        ed06sq = distsq(g(i, j), g(i, j-1));

        // Circum-edges.
        ed12sq = distsq(g(i-1, j), g(i-1, j+1));
        ed23sq = distsq(g(i-1, j+1), g(i, j+1));
        ed34sq = 0;
        ed45sq = 0;
        ed56sq = 0;
        ed61sq = distsq(g(i, j-1), g(i-1, j));

        // All nearest neighbour triangle areas.
        A012 = area(g(i, j), g(i-1, j), g(i, j+1));
        A023 = area(g(i, j), g(i-1, j+1), g(i, j+1));
        A034 = 0;
        A045 = 0;
        A056 = 0;
        A061 = area(g(i, j), g(i, j-1), g(i-1, j));

        w01 = (ed06sq + ed61sq - ed01sq)/(8.0*A061) + (ed12sq + ed02sq - ed01sq)/(8.0*A012);
        w02 = (ed01sq + ed12sq - ed02sq)/(8.0*A012) + (ed23sq + ed03sq - ed02sq)/(8.0*A023);
        w03 = (ed02sq + ed23sq - ed03sq)/(8.0*A023) + 0;
        w04 = 0 + 0;
        w05 = 0 + 0;
        w06 = 0 + (ed61sq + ed01sq - ed06sq)/(8.0*A061);

        // TODO: Update output vector.
    }

    // Leftmost column weights

    for (int i = 1; i < g.Ny - 1; i++) {
      int j = 0;

      ed01sq = distsq(g(i, j), g(i-1, j));
      ed02sq = distsq(g(i, j), g(i-1, j+1));
      ed03sq = distsq(g(i, j), g(i, j+1));
      ed04sq = distsq(g(i, j), g(i+1, j));
      ed05sq = 0;
      ed06sq = 0;

      // Circum-edges.
      ed12sq = distsq(g(i-1, j), g(i-1, j+1));
      ed23sq = distsq(g(i-1, j+1), g(i, j+1));
      ed34sq = distsq(g(i, j+1), g(i+1, j));
      ed45sq = 0;
      ed56sq = 0;
      ed61sq = 0;

      // All nearest neighbour triangle areas.
      A012 = area(g(i, j), g(i-1, j), g(i, j+1));
      A023 = area(g(i, j), g(i-1, j+1), g(i, j+1));
      A034 = area(g(i, j), g(i, j+1), g(i+1, j));
      A045 = 0;
      A056 = 0;
      A061 = 0;

      w01 = 0 + (ed12sq + ed02sq - ed01sq)/(8.0*A012);
      w02 = (ed01sq + ed12sq - ed02sq)/(8.0*A012) + (ed23sq + ed03sq - ed02sq)/(8.0*A023);
      w03 = (ed02sq + ed23sq - ed03sq)/(8.0*A023) + (ed34sq + ed04sq - ed03sq)/(8.0*A034);
      w04 = (ed03sq + ed34sq - ed04sq)/(8.0*A034) + 0;
      w05 = 0 + 0;
      w06 = 0 + 0;

      // TODO: Update output vector.
    }

    // Rightmost column weights

    for (int i = 1; i < g.Nx -1; i++) {
      int j = 0;

      ed01sq = distsq(g(i, j), g(i-1, j));
      ed02sq = 0;
      ed03sq = 0;
      ed04sq = distsq(g(i, j), g(i+1, j));
      ed05sq = distsq(g(i, j), g(i+1, j-1));
      ed06sq = distsq(g(i, j), g(i, j-1));

      // Circum-edges.
      ed12sq = 0;
      ed23sq = 0;
      ed34sq = 0;
      ed45sq = distsq(g(i+1, j), g(i+1, j-1));
      ed56sq = distsq(g(i+1, j-1), g(i, j-1));
      ed61sq = distsq(g(i, j-1), g(i-1, j));

      // All nearest neighbour triangle areas.
      A012 = 0;
      A023 = 0;
      A034 = 0;
      A045 = area(g(i, j), g(i+1, j), g(i+1, j-1));
      A056 = area(g(i, j), g(i+1, j-1), g(i, j-1));
      A061 = area(g(i, j), g(i, j-1), g(i-1, j));

      w01 = (ed06sq + ed61sq - ed01sq)/(8.0*A061) + 0;
      w02 = 0 + 0;
      w03 = 0 + 0;
      w04 = 0 + (ed45sq + ed05sq - ed04sq)/(8.0*A045);
      w05 = (ed04sq + ed45sq - ed05sq)/(8.0*A045) + (ed56sq + ed06sq - ed05sq)/(8.0*A056);
      w06 = (ed05sq + ed56sq - ed06sq)/(8.0*A056) + (ed61sq + ed01sq - ed06sq)/(8.0*A061);

      // TODO: Update output vector.
    }

    // ====================== Corner Points.
    // Top left. i = 0, j = 0.
    int i = 0, j = 0;
    ed01sq = 0;
    ed02sq = 0;
    ed03sq = distsq(g(i, j), g(i, j+1));
    ed04sq = distsq(g(i, j), g(i+1, j));
    ed05sq = 0;
    ed06sq = 0;

    // Circum-edges.
    ed12sq = 0;
    ed23sq = 0;
    ed34sq = distsq(g(i, j+1), g(i+1, j));
    ed45sq = 0;
    ed56sq = 0;
    ed61sq = 0;

    // All nearest neighbour triangle areas.
    A012 = 0;
    A023 = 0;
    A034 = area(g(i, j), g(i, j+1), g(i+1, j));
    A045 = 0;
    A056 = 0;
    A061 = 0;

    w01 = 0;
    w02 = 0;
    w03 = 0 + (ed34sq + ed04sq - ed03sq)/(8.0*A034);
    w04 = (ed03sq + ed34sq - ed04sq)/(8.0*A034) + 0;
    w05 = 0;
    w06 = 0;
    // TODO: Update output vector.

    // Top right. i = 0; j = g.Nx - 1
    i = 0; j = g.Ny -1;
    ed01sq = 0;
    ed02sq = 0;
    ed03sq = 0;
    ed04sq = distsq(g(i, j), g(i+1, j));
    ed05sq = distsq(g(i, j), g(i+1, j-1));
    ed06sq = distsq(g(i, j), g(i, j-1));

    // Circum-edges.
    ed12sq = 0;
    ed23sq = 0;
    ed34sq = 0;
    ed45sq = distsq(g(i+1, j), g(i+1, j-1));
    ed56sq = distsq(g(i+1, j-1), g(i, j-1));
    ed61sq = 0;

    // All nearest neighbour triangle areas.
    A012 = 0;
    A023 = 0;
    A034 = 0;
    A045 = area(g(i, j), g(i+1, j), g(i+1, j-1));
    A056 = area(g(i, j), g(i+1, j-1), g(i, j-1));
    A061 = 0;

    w01 = 0;
    w02 = 0;
    w03 = 0;
    w04 = 0 + (ed45sq + ed05sq - ed04sq)/(8.0*A045);
    w05 = (ed04sq + ed45sq - ed05sq)/(8.0*A045) + (ed56sq + ed06sq - ed05sq)/(8.0*A056);
    w06 = (ed05sq + ed56sq - ed06sq)/(8.0*A056) + 0;
    //TODO: Update output vector.


    // Bot left. i = g.Nx - 1, j = 0;
    i = g.Nx - 1; j = 0;
    ed01sq = distsq(g(i, j), g(i-1, j));
    ed02sq = distsq(g(i, j), g(i-1, j+1));
    ed03sq = distsq(g(i, j), g(i, j+1));
    ed04sq = 0;
    ed05sq = 0;
    ed06sq = 0;

    // Circum-edges.
    ed12sq = distsq(g(i-1, j), g(i-1, j+1));
    ed23sq = distsq(g(i-1, j+1), g(i, j+1));
    ed34sq = 0;
    ed45sq = 0;
    ed56sq = 0;
    ed61sq = 0;

    // All nearest neighbour triangle areas.
    A012 = area(g(i, j), g(i-1, j), g(i, j+1));
    A023 = area(g(i, j), g(i-1, j+1), g(i, j+1));
    A034 = 0;
    A045 = 0;
    A056 = 0;
    A061 = 0;

    w01 = 0 + (ed12sq + ed02sq - ed01sq)/(8.0*A012);
    w02 = (ed01sq + ed12sq - ed02sq)/(8.0*A012) + (ed23sq + ed03sq - ed02sq)/(8.0*A023);
    w03 = (ed02sq + ed23sq - ed03sq)/(8.0*A023) + 0;
    w04 = 0;
    w05 = 0;
    w06 = 0;
    // TODO: Update output vector.

    // Bot right. i = g.Nx -1; j = g.Ny - 1;
    i = g.Nx -1; j = g.Ny - 1;
    ed01sq = distsq(g(i, j), g(i-1, j));
    ed02sq = 0;
    ed03sq = 0;
    ed04sq = 0;
    ed05sq = 0;
    ed06sq = distsq(g(i, j), g(i, j-1));

    // Circum-edges.
    ed12sq = 0;
    ed23sq = 0;
    ed34sq = 0;
    ed45sq = 0;
    ed56sq = 0;
    ed61sq = distsq(g(i, j-1), g(i-1, j));

    // All nearest neighbour triangle areas.
    A012 = 0;
    A023 = 0;
    A034 = 0;
    A045 = 0;
    A056 = 0;
    A061 = area(g(i, j), g(i, j-1), g(i-1, j));

    w01 = (ed06sq + ed61sq - ed01sq)/(8.0*A061) + 0;
    w02 = 0;
    w03 = 0;
    w04 = 0;
    w05 = 0;
    w06 = 0 + (ed61sq + ed01sq - ed06sq)/(8.0*A061);
    // TODO: Update output vector.
  // Store the results into y
  for (int i = 1; i < g.Nx - 1; ++i)
    for (int j = 1; j < g.Ny - 1; ++j)
      u1[(i-1)*(g.Nx-2) + (j-1)] = unew[i][j];
}
