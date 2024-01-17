/*
The code in this file will contain various function that are useful for
finding roots of functions and systems of equations.
*/
#include "root.h"

#include <functional>
#include <vector>
#include <iostream>
#include <cmath>

//NOTE: there is a better way to do this sort of thing
const double noroot = 0.424242;

bool signchange(std::function<double(double)> f, double a, double b) {
    if (f(a)*f(b) < 0.0) {
        return true;
    } else {
        return false;
    } 
}

// bisectionrootfind finds the root of a function f that must be guaranteed to have
// a change of sign in the interval [a, b] (otherwise returns a noroot value).
// It uses a method of bisection, that is a very stable method that does not rely
// on the derivative of a function and a good initial guess, although it has it's
// drawbacks, such as slow convergence.
double bisectionrootfind(std::function<double(double)> f, double a, double b, 
        double eps, int maxiter) {

    if (!signchange(f, a, b)) {
        //std::cout << "No sign change in interval [" << a << ", " << b << "]\n";
        return noroot;
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

// bisectionrootfindall uses the bisection root finding method above, but subdivides
// the interval in order to find multiple (or all) roots of the function f.
std::vector<double> bisectionrootfindall(std::function<double(double)> f,
        double a, double b, int subintervals, double eps, int maxiter, 
        int minroots) {

    std::vector<double> roots;
    double h = (b - a)/subintervals;
    
    for (int i = 0; i < subintervals; i++) {
        double root = bisectionrootfind(f, a + i*h, a + (i + 1)*h, eps, maxiter);
        if (root != noroot) {
            roots.push_back(root);
        }
    }

    if (roots.size() < minroots) {
        std::cout << "Warning: only " << roots.size() << " roots found.\n";
    }

    return roots;
}

