#include <cstdio>
#include <vector>

#include <Eigen/Core>
#include <SymEigsSolver.h>
#include <iostream>

#include "LaplacePeriodicGrid2D.h"

#define NX 16 // Number of points in x direction
#define DXDY 1.15470053838 // Ratio between dx and dy for 60 degree
#define LOW 0.0 // Low boundary
#define HIGH 1.0 // High boundary

int main(int argc, char* argv[])
{
  // The PeriodicGrid2D API has changed and now always starts from the origin.
  PeriodicGrid2D pg(NX, DXDY, HIGH, HIGH);
  LaplacePeriodicGrid2D lpg(pg);

  Spectra::SymEigsSolver<double, Spectra::LARGEST_ALGE, LaplacePeriodicGrid2D>
    eigs(&lpg, 127, 254);
  eigs.init();
  eigs.compute();

  if(eigs.info() == Spectra::SUCCESSFUL)
    {
      Eigen::VectorXd evalues = eigs.eigenvalues();
      std::cout << "Eigenvalues found: \n" << evalues << std::endl;
    }

  return 0;
}
