#include <cstdio>
#include <vector>

#include <Eigen/Core>
#include <SymEigsSolver.h>
#include <iostream>
#include <fstream>

#include "LaplacePeriodicGrid2D.h"

#define NX 16 // Number of points in x direction
#define NY 16 // Number of points in Y direction
#define LOW 0.0 // Low boundary
#define HIGH 1.0 // High boundary

int main(int argc, char* argv[])
{
  // The PeriodicGrid2D API has changed and now always starts from the origin.
  PeriodicGrid2D pg(NX, NY, HIGH, HIGH);
  pg.print_coords();
  LaplacePeriodicGrid2D lpg(pg);

  // double x[NX*NY];
  // x[NX/2 + (NY/2)*NX] = 1.0;
  // printf("x \n");
  // for (int i=0; i<NX*NY; i++)
  //   printf("%f ", x[i]);
  // printf("\n");
  
  // double y[NX*NY];
  // lpg.perform_op(x, y);
  // printf("y \n");
  // for (int i=0; i<NX*NY; i++)
  //   printf("%f ", y[i]);
  // printf("\n");
  
  // Large eigenvalue
  Spectra::SymEigsSolver<double, Spectra::LARGEST_ALGE, LaplacePeriodicGrid2D>
    l_eigs(&lpg, 0.5*pg.Ny*pg.Nx, pg.Ny*pg.Nx-1);
  l_eigs.init();
  l_eigs.compute();

  // Large eigenvalue
  Spectra::SymEigsSolver<double, Spectra::SMALLEST_ALGE, LaplacePeriodicGrid2D>
    s_eigs(&lpg, 0.5*pg.Ny*pg.Nx, pg.Ny*pg.Nx-1);
  s_eigs.init();
  s_eigs.compute();
  
  // Writing to file
  std::ofstream outFile;
  outFile.open("eigVals.dat");
  
  // Print out large eigenvalues
  if(l_eigs.info() == Spectra::SUCCESSFUL)
    {
      Eigen::VectorXd l_evalues = l_eigs.eigenvalues();
      outFile << "Eigenvalues found: \n" << l_evalues << "\n";
    }
  else
    outFile << "Large eigenvalues NOT found!\n";
  // Print out small eigenvalues
  if(s_eigs.info() == Spectra::SUCCESSFUL)
    {
      Eigen::VectorXd s_evalues = s_eigs.eigenvalues();
      outFile << s_evalues << "\n";
    }
  else
    outFile << "Small eigenvalues NOT found!\n";
  
  outFile.close();
  
  return 0;
}
