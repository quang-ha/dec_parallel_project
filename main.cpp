#include <stdio.h>
#include <vector>

#include "Point.h"
#include "Grid2D.hpp"
#define N 4 // Number of points in each direction
#define LOW 0.0 // Boundary
#define HIGH 1.0

int main(int argc, char* argv[])
{
  // Generate a vector of points
  std::vector<std::vector<Point>> mesh2D;

  // Set up sizes. (N x N)
  mesh2D.resize(N);
  for (int i=0; i<N; i++)
    mesh2D[i].resize(N);

  // Populate with values
  for (int i=0; i<N; i++)
    for (int j=0; j<N; j++)
      {
	mesh2D[i][j].set(LOW + (double)(HIGH/N)*i,
			 LOW + (double)(HIGH/N)*j) ;
      }

  // Let's print them out to check
  for (int i=0; i<N; i++)
    for (int j=0; j<N; j++)
      printf("Index i %d j %d and x-coord %f y-coord %f \n",
	     i, j, mesh2D[i][j].x, mesh2D[i][j].y);

    // Trying out the Grid2D object.
    printf("\n");
    Point a(LOW, LOW);
    Point b(HIGH, HIGH);
    Grid2D g(a, b, N, N);
    for (int i=0; i<N; i++)
      for (int j=0; j<N; j++)
        printf("Index i %d j %d and x-coord %f y-coord %f \n",
           i, j, g(i, j).x, g(i, j).y);

  return 0;
}
