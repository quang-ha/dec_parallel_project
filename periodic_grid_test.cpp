#include <cstdio>
#include "PeriodicGrid2D.hpp"

int main() {
  Point a(0, 0);
  Point b(1, 1);
  PeriodicGrid2D g(a, b, 5, 5);
  auto p = g(5, 5);
  printf("Point at %f %f", p.x, p.y);
}
