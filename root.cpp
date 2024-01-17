#include "root.h"

#include <functional>
#include <vector>
#include <iostream>

bool signchange(std::function<double(double)> f, double a, double b) {
    if (f(a)*f(b) < 0.0) {
        return true;
    } else {
        return false;
    } 
}

double bisectionrootfind(std::function<double(double)> f, double a, double b, 
        double eps, int maxiter) {

    if (!signchange(f, a, b)) {
        std::cout << "No sign change in interval [" << a << ", " << b << "]\n";
        return 0.0;
    }

    double c = (a + b)/2.0;
    int i = 0;

    // print loop conditions
    std::cout << abs(f(c)) << " > " << eps << " && " << i << " < " << maxiter << '\n';

    while (abs(f(c)) > eps && i < maxiter) {
        if (signchange(f, a, c)) {
            b = c;
        } else {
            a = c;
        }
        c = (a + b)/2.0;
        i++;
    }

    return c;
}

std::vector<double> bisectionrootfindall(std::function<double(double)> f,
        double a, double b, int subintervals, double eps, int maxiter, 
        int minroots) {

    return std::vector<double>();
}

