#include "gquad.h"

#include <iostream>

int main() {
    // overflow for n > 32
    int n = 32;
    double x = 1.0;

    std::cout << LegendrePolyn(n, x) << "\n";
}