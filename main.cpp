#include "gquad.h"

#include <iostream>
#include <vector>
#include <cmath>

int main() {
    //NOTE: overflow for n > 32
    //NOTE:  code not running or taking too much to run for n > 26
    int n = 26;
    auto f = [](double x) {return pow(x, 3.0);};
    double a = 0.0;
    double b = 1.0;

    std::cout << "Integral value: " << gquad(f, a, b, n) << '\n';
}