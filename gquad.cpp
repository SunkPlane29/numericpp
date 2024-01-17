/*
The code in this file will contain a Gauss-Legendre quadrature implementation.
Together with the functions necessary in order to implement this quadrature, like
calculating Legendre polynomials, roots of these polynomials and weights associated
with these roots.
*/
#include "gquad.h"

#include <cmath>
#include <functional>
#include <vector>

#include "util.h"
#include "root.h"

// adapt takes the function f that is integrated in the arbitrary interval [a, b]
// and returns a function that is integrated in the interval [-1, 1]
std::function<double(double)> adapt(std::function<double(double)> f, double a, double b) {
    return [f, a, b](double xi) {return f((b - a)*xi/2.0 + (b + a)/2.0)*((b - a)/2.0);};
}

// LegendrePolyn returns the Legendre Polynomial of order n calculated at the point x
double LegendrePolyn(int n, double x) {
    int a = floor(n/2.0);
    double sum = 0.0; 

    for (int k = 0; k <= a; k++) {
        sum += pow(-1.0, k)*bin(n, k)*bin(2*n - 2*k, n)*pow(x, n - 2*k);
    }

    return sum/pow(2.0, n);
}

// LegendrePolyn returns the Legendre Polynomial of order n as a function of x
std::function<double(double)> LegendrePolyn(int n) {
    return [n](double x) {return LegendrePolyn(n, x);};
}

// getpoints returns the roots of the Legendre Polynomial of order n, such
// points are the points at which a function is evaluated for the Gauss-Legendre
// quadrature
std::vector<double> getpoints(int n) {
    auto f = LegendrePolyn(n);
    double a = -1.0; double b = 1.0;
    //TODO: was supposed to be n, but had to make a hack to make it work
    int subintervals = 5*n;
    int minroots = n;
    
    std::vector<double> roots = bisectionrootfindall(f, a, b, subintervals, 
            1.0e-8, 100000, minroots);

    if (n % 2 != 0) {
        roots[roots.size()/2] = 0.0;
    }

    return roots;
}

// LegendrePolynDeriv returns the derivative of the Legendre Polynomial of order n
// calculated at the point x
double LegendrePolynDeriv(int n, double x) {
    int imax = floor(n/2.0);
    if (n % 2 == 0) {
        imax -= 1;
    }

    double sum = 0.0;

    for (int k = 0; k <= imax; k++) {
        sum += pow(-1.0, k)*bin(n, k)*bin(2*n - 2*k, n)*(n - 2*k)*pow(x, n - 2*k - 1);
    }

    return sum/pow(2.0, n);
}

// LegendrePolynDeriv returns the derivative of the Legendre Polynomial of order n
// as a function of x
std::function<double(double)> LegendrePolynDeriv(int n) {
    return [n](double x) {return LegendrePolynDeriv(n, x);};
}

// getweight returns the weight associated with the point x for the Gauss-Legendre
// quadrature of order n
double getweight(int n, double x) {
    return 2.0/((1.0 - pow(x, 2.0))*pow(LegendrePolynDeriv(n, x), 2.0));
}

// getweights returns the weights associated with the points in the vector points
// for the Gauss-Legendre quadrature of order n
std::vector<double> getweights(std::vector<double> points, int n) {
    std::vector<double> weights(points.size());
    for (int i = 0; i < points.size(); i++) {
        weights[i] = getweight(n, points[i]);
    }

    return weights;
}

double quadsum(std::function<double(double)> f, std::vector<double> points, 
        std::vector<double> weights) {
    double sum = 0.0;
    for (int i = 0; i < points.size(); i++) {
        sum += weights[i]*f(points[i]);
    }

    return sum;
}

// gquad return the value of the integral of the function f, integrated in the interval
// [a, b] using the Gauss-Legendre quadrature of order n
double gquad(std::function<double(double)> f, double a, double b, int n) {
    std::vector<double> points = getpoints(n);
    std::vector<double> weights = getweights(points, n);

    if (a == -1.0 && b == 1.0) {
        return quadsum(f, points, weights);
    } else {
        return quadsum(adapt(f, a, b), points, weights);
    }
}