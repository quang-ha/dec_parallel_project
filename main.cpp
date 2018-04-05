#include <stdio.h>
#include <vector>
#include "Point.h"
#include "PeriodicGrid2D.h"
#include "LaplacePeriodicGrid2D.h"

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
  // Grid2D g(a, b, N, N);
  PeriodicGrid2D pg(a, b, N, N);
  LaplacePeriodicGrid2D lpg(pg);

  double x[N*N];
  for (int i=0; i<N*N; i++)
    x[i] = i;
  printf("x \n");
  for (int i=0; i<N*N; i++)
    printf("%f ", x[i]);
  printf("\n");
  
  double y[N*N];
  lpg.perform_op(x, y);
  printf("y \n");
  for (int i=0; i<N*N; i++)
    printf("%f ", y[i]);
  printf("\n");
  
  // Spectra::SymEigsSolver<double, Spectra::LARGEST_ALGE, LaplacePeriodicGrid2D>
  //   eigs(&lpg, 15, 16);
  // eigs.init();
  // eigs.compute();
  
  // if(eigs.info() == Spectra::SUCCESSFUL)
  //   {
  //     Eigen::VectorXd evalues = eigs.eigenvalues();
  //     std::cout << "Eigenvalues found: \n" << evalues << std::endl;
  //   }
  
  return 0;
}
