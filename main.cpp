#include <stdio.h>
#include <vector>
#include "Point.h"
#include "Grid2D.h"

#include <Eigen/Core>
#include <SymEigsSolver.h>
#include <iostream>

#define N 4 // Number of points in each direction
#define LOW 0.0 // Low boundary
#define HIGH 1.0 // High boundary

int main(int argc, char* argv[])
{
  // Trying out the Grid2D object.
  Point a(LOW, LOW);
  Point b(HIGH, HIGH);
  Grid2D g(a, b, N, N);

  // for (int i=0; i<=N+1; i++)
  //   for (int j=0; j<N+1; j++)
  //       printf("Index i %d j %d and x-coord %f y-coord %f \n",
  // 	       i, j, g(i, j).x, g(i, j).y);

  // // Create array of pointers that point to more array
  // double* x = new double[N*N];
  // double* y = new double[N*N];

  // for (int i=0; i<N; i++)
  //   for (int j=0; j<N; j++)
  //     x[i*N + j] = i*N + j;

  // printf("x \n");
  // for (int i=0; i<N*N; i++)
  //   printf("%f ", x[i]);

  // printf("\n");

  // g.perform_op(x, y);

  // printf("y \n");
  // for (int i=0; i<N*N; i++)
  //   printf("%f ", y[i]);

  // printf("\n");

  Spectra::SymEigsSolver<double, Spectra::LARGEST_ALGE, Grid2D> eigs(&g, 8, 16);
  eigs.init();
  eigs.compute();
  
  if(eigs.info() == Spectra::SUCCESSFUL)
    {
      Eigen::VectorXd evalues = eigs.eigenvalues();
      std::cout << "Eigenvalues found:\n" << evalues << std::endl;
    }
  
  return 0;
}
