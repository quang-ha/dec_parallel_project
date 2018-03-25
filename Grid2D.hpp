#ifndef GRID2D_HPP
#define GRID2D_HPP
#include <vector>
#include <tuple>
#include "Point.h"

class Grid2D {
public:
    Grid2D(Point& top_left, Point& bot_right, double x_resolution, double y_resolution);
    ~Grid2D();
    std::vector<std::vector<Point>> points;
    Point& operator()(int i, int j);
};
#endif
