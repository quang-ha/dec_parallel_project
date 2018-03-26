#include "Grid2D.hpp"

Grid2D::Grid2D(Point& top_left, Point& bot_right, double x_resolution, double y_resolution) {
    this->x_resolution = x_resolution;
    this->y_resolution = y_resolution;
    double x_step = (bot_right.x - top_left.x)/(x_resolution-1);
    double y_step = (bot_right.y - top_left.x)/(y_resolution-1);
    this->points.resize(x_resolution);
    for (int i=0; i<x_resolution; i++)
      this->points[i].resize(y_resolution);

     for (int i = 0; i < x_resolution; ++i) {
         for (int j = 0; j < y_resolution; ++j) {
             this->points[i][j].set(top_left.x + i*x_step, top_left.y + j*y_step);
         }
     }
}

Grid2D::~Grid2D() {

}

Point& Grid2D::operator()(int i, int j) {
    return this->points[i][j];
}

void Grid2D::set_weights() {
    // Interior points
    for (int i = 1; i < x_resolution - 1; ++i) {
        for (int j = 1; j < y_resolution - 1; ++j) {
            weights
        }
    }
}
