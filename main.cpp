#include <stdio.h>
#include <vector>
#include "Point.h"
#include "Grid2D.h"
#include "PeriodicGrid2D.h"

#include <Eigen/Core>
#include <SymEigsSolver.h>
#include <iostream>

#define N 10 // Number of points in each direction
#define LOW 0.0 // Low boundary
#define HIGH 1.0 // High boundary

int main(int argc, char* argv[])
{
  // Trying out the Grid2D object.
  Point a(LOW, LOW);
  Point b(HIGH, HIGH);
  Grid2D g(a, b, N, N);
  PeriodicGrid2D pg(a, b, N, N);

  Spectra::SymEigsSolver<double, Spectra::LARGEST_ALGE, Grid2D> eigs(&g, 15, 16);
  eigs.init();
  eigs.compute();
  
  if(eigs.info() == Spectra::SUCCESSFUL)
    {
      Eigen::VectorXd evalues = eigs.eigenvalues();
      std::cout << "Eigenvalues found: \n" << evalues << std::endl;
    }
  
  return 0;
}
