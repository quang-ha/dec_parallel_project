#include <stdio.h>
#include <vector>
#include "Point.h"

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

  return 0;
}
