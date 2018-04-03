#include <cstdio>
#include "Point.h"

int main() {
  Point a(1, 2);
  Point b = a + Point(2, 3);

  printf("Point at %f %f", b.x, b.y);
}
