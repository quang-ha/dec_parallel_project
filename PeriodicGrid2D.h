#ifndef PERIODIC_GRID_H
#define PERIODIC_GRID_H

#include <vector>

#include "Point.h"

using std::vector;

struct PeriodicGrid2D {
    int Nx, Ny;
    double Lx, Ly;
    vector<vector<Point>> data;
    PeriodicGrid2D(int nx, double dxdy, double lenx, double leny) {
        Nx = nx;
        Lx = lenx;
        Ly = leny;
        double dLx = lenx/(nx-1);
        double dLy = dLx/dxdy; // Calculate dLy using the ratio dx/dy
	Ny = (int)((Ly/dLy) + 1);

        for (int i = 0; i < Nx; ++i) {
          data.push_back(vector<Point>(Ny));
            for (int j = 0; j < Ny; ++j) {
                data[i][j] = Point(i*dLx, j*dLy);
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

      double wrapped_x_offset = 0, wrapped_y_offset = 0;
      Point result;
        // Wrapping around i = Nx -1
      if (i > Nx - 1) {
        i = i%(Nx - 1);
        wrapped_x_offset = Lx;
      }
      else if (i < 0) {
        i = i%(Nx - 1) + Nx - 1;
        wrapped_x_offset = - Lx;
      }
      if (j > Ny - 1) {
        j = j%(Ny - 1);
        wrapped_y_offset = Ly;
      }
      else if (j < 0) {
        j = j%(Ny - 1) + Ny - 1;
        wrapped_y_offset = - Ly;
      }
      if (wrapped_x_offset == 0 && wrapped_y_offset == 0)
        return data[i][j];
      else
        return data[i][j] + Point(wrapped_x_offset, wrapped_y_offset);
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
        i = i%(Nx - 1);
      }
      else if (i < 0) {
        i = i%(Nx - 1) + Nx - 1;
      }
      if (j > Ny - 1) {
        j = j%(Ny - 1);
      }
      else if (j < 0) {
        j = j%(Ny - 1) + Ny - 1;
      }
      data[i][j].u= u;
    }


    Point operator()(int i, int j) {
    /* Simple accessor operator that implements a simple wraparound. -1 wraps
    around the back of the index. Going over the maximum element index wraps
    around the front. This can be used to SET coordinate and u values. To GET
    values, esp. coordinate values, use the getxy method. That will return the
    coordinates of the point _with_ the proper offsets required for weight
    calculations.*/
      if (i > Nx - 1) {
        i = i%(Nx - 1);
      }
      else if (i < 0) {
        i = i%(Nx - 1) + Nx - 1;
      }
      if (j > Ny - 1) {
        j = j%(Ny - 1);
      }
      else if (j < 0) {
        j = j%(Ny - 1) + Ny - 1;
      }

      return data[i][j];
    }
};
#endif
