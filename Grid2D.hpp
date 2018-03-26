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
    std::vector<std::vector<double>> weights;
    double x_resolution, y_resolution;

    Point& operator()(int i, int j);
};

void set_weights(Grid2D& g);
#endif
