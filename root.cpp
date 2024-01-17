#include "root.h"

#include <functional>
#include <vector>
#include <iostream>
#include <cmath>

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

    while (fabs(f(c)) > eps && i < maxiter) {
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

    std::vector<double> roots;
    double h = (b - a)/subintervals;
    
    for (int i = 0; i < subintervals; i++) {
        double root = bisectionrootfind(f, a + i*h, a + (i + 1)*h, eps, maxiter);
        if (root != 0.0) {
            roots.push_back(root);
        }
    }

    if (roots.size() < minroots) {
        std::cout << "Warning: only " << roots.size() << " roots found.\n";
    }

    return roots;
}

