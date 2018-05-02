#include <cstdio>
#include <vector>

#include <Eigen/Core>
#include <SymEigsSolver.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "LaplacePeriodicGrid2D.h"

#define LOW 0.0 // Low boundary
#define HIGH 1.0 // High boundary

int main(int argc, char* argv[])
{
  // The PeriodicGrid2D API has changed and now always starts from the origin.
  int N = 250; // Number of points per side.
  if (argc > 1)
  	N = std::atoi(argv[1]);
  printf("Grid side size: %d\n", N);
  PeriodicGrid2D pg(N, N, HIGH, HIGH);
  // Slighly moving the points
  double wiggle_mag = 0.08;
  pg.wiggle(wiggle_mag);
  pg.print_coords(wiggle_mag);
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
  // // Large eigenvalue
  // Spectra::SymEigsSolver<double, Spectra::LARGEST_ALGE, LaplacePeriodicGrid2D>
  //   l_eigs(&lpg, 5, 15);
  // l_eigs.init();
  // l_eigs.compute();
  
  // Small eigenvalue
  Spectra::SymEigsSolver<double, Spectra::SMALLEST_ALGE, LaplacePeriodicGrid2D>
    s_eigs(&lpg, 100, 201);
  s_eigs.init();
  s_eigs.compute();

  // Generate file name
  std::ostringstream oss;
  oss << "eigVals_" << N << "_" << N << "_" << wiggle_mag << ".dat";
  std::string outFilename = oss.str();
  // Writing to file
  std::ofstream outFile;
  outFile.open(outFilename);
  
  // // Print out large eigenvalues
  // if(l_eigs.info() == Spectra::SUCCESSFUL)
  //   {
  //     Eigen::VectorXd l_evalues = l_eigs.eigenvalues();
  //     outFile << "Eigenvalues found: \n" << l_evalues << "\n";
  //   }
  // else
  //   outFile << "Large eigenvalues NOT found!\n";
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
