#include <cstdio>
#include "../PeriodicGrid2D.h"


int main() {
    PeriodicGrid2D g(4, 4, 1, 1);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            printf("%f\t%f\n", g(i, j).x, g(i, j).y);
        }
    }
    printf("\n");
    g.skewx(-30*3.14159265/180);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            printf("%f\t%f\n", g(i, j).x, g(i, j).y);
        }
    }

    g.print_coords();
}
