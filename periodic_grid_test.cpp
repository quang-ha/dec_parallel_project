#include <cstdio>
#include "PeriodicGrid2D.hpp"

int main() {
  Point a(0, 0);
  Point b(1, 1);
  PeriodicGrid2D g(a, b, 3, 3);
  printf("Point at %f %f", g(3, 3).x, g(3,3).y);
}
