#include "gquad.h"

#include <cmath>
#include <functional>
#include <vector>

#include "util.h"

double adapt(double xi, std::function<double(double)> f, double a, double b) {
    return f(((b - a)/2.0)*xi + ((a + b)/2.0))*((b - a)/2.0);
}

double LegendrePolyn(int n, double x) {
    int a = floor(n/2.0);
    double sum = 0.0; 

    for (int k = 0; k <= a; k++) {
        sum += pow(-1.0, k)*bin(n, k)*bin(2*n - 2*k, n)*pow(x, n - 2*k);
    }

    return sum/pow(2.0, n);
}
