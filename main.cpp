#include "gquad.h"
#include "root.h"
#include "util.h"

#include <iostream>
#include <cmath>
#include <vector>

int main() {
    // overflow for n > 32
    int nx = 100;
    std::vector<double> x = linspace(-1.0, 1.0, nx);
    std::vector<double> y(x.size());

    for (int i = 0; i <= 5; i++) {
        y = LegendrePolyn(i)%x;
        writedata("legendre" + std::to_string(i) + ".dat", {x, y}, 8);
    }
}