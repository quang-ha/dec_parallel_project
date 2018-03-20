#include <iostream>
#include "Point.hpp"
int main() {
    Point a(0, 0);
    Point b(0, 5);
    Point c(6, 0);
    double d_ab = dist(b, c);
    double ar_abc = area(a, b, c);
    std::cout << a.x << '\t' << a.y << '\t' << d_ab << '\t' << ar_abc;
}
