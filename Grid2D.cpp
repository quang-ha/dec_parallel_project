#include "Grid2D.hpp"

#include <cstdio>
Grid2D::Grid2D(Point& top_left, Point& bot_right, double x_resolution, double y_resolution) {
    this->x_resolution = x_resolution;
    this->y_resolution = y_resolution;
    double x_step = (bot_right.x - top_left.x)/(x_resolution-1.0);
    double y_step = (bot_right.y - top_left.x)/(y_resolution-1.0);
    this->points.resize(x_resolution);
    for (int i=0; i<x_resolution; i++)
      this->points[i].resize(y_resolution);

     for (int i = 0; i < x_resolution; ++i) {
         for (int j = 0; j < y_resolution; ++j) {
             this->points[i][j].set(top_left.x + i*x_step, top_left.y + j*y_step);
         }
     }

     this->weights.resize(x_resolution);
     for (int i=0; i<x_resolution; i++)
       this->weights[i].resize(y_resolution);
}

Grid2D::~Grid2D() {

}

Point& Grid2D::operator()(int i, int j) {
    return this->points[i][j];
}

void set_weights(Grid2D& g) {
    // Interior points
    for (int i = 1; i < g.x_resolution - 1; ++i) {
        for (int j = 1; j < g.y_resolution - 1; ++j) {
            Point& orig = g(i, j);
            // All nearest neighbour edges.
            double edge01sq = distsq(g(i, j), g(i-1, j));
            double edge02sq = distsq(g(i, j), g(i-1, j+1));
            double edge03sq = distsq(g(i, j), g(i, j+1));
            double edge04sq = distsq(g(i, j), g(i+1, j));
            double edge05sq = distsq(g(i, j), g(i+1, j-1));
            double edge06sq = distsq(g(i, j), g(i, j-1));

            // Circum-edges.
            double edge12sq = distsq(g(i-1, j), g(i-1, j+1));
            double edge23sq = distsq(g(i-1, j+1), g(i, j+1));
            double edge34sq = distsq(g(i, j+1), g(i+1, j));
            double edge45sq = distsq(g(i+1, j), g(i+1, j-1));
            double edge56sq = distsq(g(i+1, j-1), g(i, j-1));
            double edge61sq = distsq(g(i, j-1), g(i-1, j));

            // All nearest neighbour triangle areas.
            double area012 = area(g(i, j), g(i-1, j), g(i, j+1));
            double area023 = area(g(i, j), g(i-1, j+1), g(i, j+1));
            double area034 = area(g(i, j), g(i, j+1), g(i+1, j));
            double area045 = area(g(i, j), g(i+1, j), g(i+1, j-1));
            double area056 = area(g(i, j), g(i+1, j-1), g(i, j-1));
            double area061 = area(g(i, j), g(i, j-1), g(i-1, j));
            // printf("%f\n", area012);
            // printf("%f\n", area023);
            // printf("%f\n", area034);
            // printf("%f\n", area045);
            // printf("%f\n", area056);
            // printf("%f\n", area061);

            double weight01 = (edge06sq + edge61sq - edge01sq)/(8.0*area061) + (edge12sq + edge02sq - edge01sq)/(8.0*area012);
            double weight02 = (edge01sq + edge12sq - edge02sq)/(8.0*area012) + (edge23sq + edge03sq - edge02sq)/(8.0*area023);
            double weight03 = (edge02sq + edge23sq - edge03sq)/(8.0*area023) + (edge34sq + edge04sq - edge03sq)/(8.0*area034);
            double weight04 = (edge03sq + edge34sq - edge04sq)/(8.0*area034) + (edge45sq + edge05sq - edge04sq)/(8.0*area045);
            double weight05 = (edge04sq + edge45sq - edge05sq)/(8.0*area045) + (edge56sq + edge06sq - edge05sq)/(8.0*area056);
            double weight06 = (edge05sq + edge56sq - edge06sq)/(8.0*area056) + (edge61sq + edge01sq - edge06sq)/(8.0*area061);
            // printf("%f\n", weight01);
            // printf("%f\n", weight02);
            // printf("%f\n", weight03);
            // printf("%f\n", weight04);
            // printf("%f\n", weight05);
            // printf("%f\n", weight06);

            g.weights[i][j] = weight01 + weight02 + weight03 + weight04 + weight05 + weight06;
        }
    }
}
