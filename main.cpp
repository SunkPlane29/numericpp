#include "gquad.h"

#include <iostream>
#include <vector>

int main() {
    // overflow for n > 32
    int n = 5;
    std::vector<double> points = getpoints(n);
    std::vector<double> weights = getweights(points, n);

    for (int i = 0; i < points.size(); i++) {
        std::cout << "x_i = " << points[i] << ", w_i = " << weights[i] << '\n';
    } 
}