#include <cstdio>
#include "../PeriodicGrid2D.h"


int main() {
  int imax = 3, jmax = 3;
    PeriodicGrid2D g(imax, jmax, 1, 1);
    for (int i = -0; i < imax; ++i) {
        for (int j = -0; j < jmax; ++j) {
            Point p = g.getxy(i, j);
            printf("Point i:%d j:%d at x:%f\ty:%f\n", i, j, p.x, p.y);
        }
        printf("\n");
    }
    printf("\n");
    g.print_coords();
    // g.skewx(30*3.14159265/180);
    /*for (int i = 0; i < imax; ++i) {
         for (int j = 0; j < jmax; ++j) {
           double ed01sq = distsq(g.getxy(i, j), g.getxy(i-1, j));
           double ed02sq = distsq(g.getxy(i, j), g.getxy(i-1, j+1));
           double ed03sq = distsq(g.getxy(i, j), g.getxy(i, j+1));
           double ed04sq = distsq(g.getxy(i, j), g.getxy(i+1, j));
           double ed05sq = distsq(g.getxy(i, j), g.getxy(i+1, j-1));
           double ed06sq = distsq(g.getxy(i, j), g.getxy(i, j-1));
           printf("%f %f %f %f %f %f\n", ed01sq, ed02sq, ed03sq, ed04sq, ed05sq, ed06sq);
         }
     }*/

    double d1, d2, d3, d4;
    d1 = distsq(g(0, 0), g(0, 1));
    d2 = distsq(g(0, 0), g(1, 0));
    d3 = distsq(g(1, 0), g(0, 1));
    d4 = distsq(g(2, 2), g(2, 3));

    printf("\n%f %f %f %f", d1, d2, d3, d4);
    //g.print_coords();
}
