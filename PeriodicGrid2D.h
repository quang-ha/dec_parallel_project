#ifndef PERIODIC_GRID_H
#define PERIODIC_GRID_H

#include <cmath>
#include <vector>
#include <random>
#include <cstdio>

#include "Point.h"

using std::vector;

struct PeriodicGrid2D {
  int Nx, Ny;
  double Lx, Ly;
  vector<vector<Point>> data;
  double dLx, dLy;
  PeriodicGrid2D(int nx, double ny, double lenx, double leny) {
    Nx = nx;
    Ny = ny;
    Lx = lenx;
    Ly = 0.866025404*leny;
    dLx = Lx/(nx-1);
    dLy = Ly/(ny-1); // Calculate dLy using the ratio dx/dy
    printf("Lx: %f and Ly: %f\n", Lx, Ly);
    // Add random noise
    //std::default_random_engine generator(1234); // seed number
    //std::normal_distribution<double> dist(0.0, 1.0); // mean and std

    for (int i = 0; i < Nx; ++i) {
      data.push_back(vector<Point>(Ny));
      for (int j = 0; j < Ny; ++j) {
	       // data[i][j] = Point(i*dLx + j*0.5*dLx, j*1.73205/2dLy);
	       data[i][j] = Point(i*dLx + j*0.5*dLx, j*dLy);
      }
    }
  }

  Point getxy(int i, int j) {
      /* This function gets the x and y values of the Point object at position
	 (i, j) in the PeriodicGrid2D object. It wraps around, offseting
	 coordinates as required. So if you have a 3x3 grid, accessing (3, 3)
	 will take you to (1, 1). This is a GETTER. It will NOT give you direct
	 access to the grid point, but a copied Point object which you can use to
	 do Point ops on.*/

    Point result;
    Point offset;
    // Wrapping around i = Nx -1
    int xwrap = 0, ywrap = 0;
    // Checking for wraparound.
    if (i > Nx - 1) {
      xwrap = 1;
    }
    else if (i < 0) {
      xwrap = -1   ;
    }
    if (j > Ny - 1) {
      ywrap = 1;
    }
    else if (j < 0) {
      ywrap = -1;
    }
    if (!xwrap && !ywrap) {// No wrap. Point is interior.
      return data[i][j];
    }
    /* Convention followed:
    X axis goes from origin DOWNWARDS.
    Y axis goes from origin RIGHTWARDS.
    This is done so we can imagine X and Y indices (i and j) conventionally
    as array locations. So moving along the X axis is going downwards, and
    moving along Y is rightwards.
     */
    // Top and bottom edges
    if (xwrap !=0 && ywrap == 0) {
      if (xwrap == 1) { // Went around bot edge.
          offset = data[1][j] - data[0][j];
          result = data[Nx - 1][j] + offset;
          result.u = data[1][j].u;
          return result;
      }
      if (xwrap == -1) { // Went around top edge.
        offset = data[Nx - 2][j] - data[Nx - 1][j];
        result = data[0][j] + offset;
        result.u = data[Nx - 2][j].u;
        return result;
      }
    }
    // Left and right edges.
    if (xwrap == 0 && ywrap != 0) {
        if (ywrap == 1) { // Went around right edge.
            offset = data[i][1] - data[i][0];
            result = data[i][Ny - 1] + offset;
            result.u = data[i][1].u;
            return result;
        }
        if (ywrap == -1) { // Went around left edge.
          offset = data[i][Ny - 2] - data[i][Ny - 1];
          result = data[i][0] + offset;
          result.u = data[i][Ny - 2].u;
          return result;
        }
    }

    // Bot right corner. [1]
    if (xwrap == 1 && ywrap == 1) {
        offset = data[1][1] - data[0][0];
        result = data[Nx - 1][Ny - 1] + offset;
        result.u = data[1][1].u;
        return result;
    }
    // Bot left corner. [2]
    if (xwrap == 1 && ywrap == -1) {
        offset = data[1][Ny - 2] - data[0][Ny - 1];
        result = data[Nx - 1][0] + offset;
        result.u = data[1][Ny - 2].u;
        return result;
    }

    // Top right corner. [3]
    if (xwrap == -1 && ywrap == 1) {
        offset = data[Nx - 2][1] - data[Nx - 1][0];
        result = data[0][Nx - 1] + offset;
        result.u = data[Nx - 2][1].u;
        return result;
    }

    // Top left corner. [4]
    if (xwrap == -1 && ywrap == -1) {
        offset = data[Nx - 2][Ny - 2] - data[Nx - 1][Ny - 1];
        result = data[0][0] + offset;
        result.u = data[Nx - 2][Ny - 2].u;
        return result;
    }
}

  void setu(int i, int j, double u) {
    /* This function sets the u values of the Point object at position
       (i, j) in the PeriodicGrid2D object. It wraps around without offseting
       coordinates. So if you have a 3x3 grid, accessing (3, 3) will take you to
       (1, 1), and give you direct access to the Point's u variable.

       This is different from the getter, which may create a separate object to
       reflect the coordinate offset, which is required for grid calculations.*/
    // Wrapping around i = Nx -1
    if (i > Nx - 1) {
      i = i%Nx;
    }
    else if (i < 0) {
      i = (i+Nx)%Nx;
    }
    if (j > Ny - 1) {
      j = j%Ny;
    }
    else if (j < 0) {
      j = (j+Ny)%Ny;
    }
    data[i][j].u= u;
  }


  void skewx(double theta) {
      // Negative skews in degrees makes it move the way we want.
      // Skew after making the grid. I think this should work even for randomly
      // moved points, since only the individual point positions matter.
      double relative_x_offset = std::tan(theta);
      double relative_y_offset = 0;
      for (int i = 0; i < Nx; ++i) {
          for (int j = 0; j < Ny; ++j) {
              data[i][j].y += relative_x_offset*(data[i][j].x);
          }
      }
  }

  Point operator()(int i, int j) {
    /* Simple accessor operator that implements a simple wraparound. -1 wraps
       around the back of the index. Going over the maximum element index wraps
       around the front. This can be used to SET coordinate and u values. To GET
       values, esp. coordinate values, use the getxy method. That will return the
       coordinates of the point _with_ the proper offsets required for weight
       calculations.*/
    if (i > Nx - 1) {
      i = i%Nx;
    }
    else if (i < 0) {
      i = (i+Nx)%Nx;
    }
    if (j > Ny - 1) {
      j = j%Ny;
    }
    else if (j < 0) {
      j = (j+Ny)%Ny;
    }

    return data[i][j];
  }
  // Print the point coordinates out to a file
  void print_coords() {
    FILE * pfile;
    pfile = fopen("coords.dat", "w");
    fprintf(pfile, "Nx \t Ny \n");
    fprintf(pfile, "x-coord \t y-coord \n");

    fprintf(pfile, "%d \t %d \n", Nx, Ny);
    for (int i = 0; i < Nx; ++i)
      for (int j = 0; j < Ny; ++j)
	fprintf(pfile, "%f %f \n", data[i][j].x, data[i][j].y);

    fclose(pfile);
  }
};
#endif
