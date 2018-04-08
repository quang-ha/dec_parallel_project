#include <cstdio>
#include <vector>

#include <Eigen/Core>
#include <SymEigsSolver.h>
#include <iostream>
#include <fstream>

#include "LaplacePeriodicGrid2D.h"

#define NX 8 // Number of points in x direction
#define DXDY 1.15470053838 // Ratio between dx and dy for 60 degree
#define LOW 0.0 // Low boundary
#define HIGH 1.0 // High boundary

int main(int argc, char* argv[])
{
  // The PeriodicGrid2D API has changed and now always starts from the origin.
  PeriodicGrid2D pg(NX, DXDY, HIGH, HIGH);
  pg.print_coords();
  LaplacePeriodicGrid2D lpg(pg);

  Spectra::SymEigsSolver<double, Spectra::LARGEST_ALGE, LaplacePeriodicGrid2D>
    eigs(&lpg, NX*2, NX*4);
  eigs.init();
  eigs.compute();

  // Writing to file
  std::ofstream outFile;
  outFile.open("eigVals.dat");
  if(eigs.info() == Spectra::SUCCESSFUL)
    {
      Eigen::VectorXd evalues = eigs.eigenvalues();
      outFile << "Eigenvalues found: \n" << evalues << "\n";
    }
  else
    outFile << "Eigenvalues NOT found!\n";
  outFile.close();
  
  return 0;
}
