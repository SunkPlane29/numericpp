#include "gquad.h"

#include <iostream>
#include <vector>
#include <cmath>

int main() {
    // overflow for n > 32
    int n = 5;
    auto f = [](double x) {return pow(x, 2.0);};
    double a = 3.0;
    double b = 45.0;

    std::cout << "Integral value: " << gquad(f, a, b, n) << '\n';
}