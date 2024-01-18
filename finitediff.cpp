#include "finitediff.h"

#include <functional>
#include <limits>
#include <vector>
#include <cmath>

// makegrid creates a vector grid around x0 with spacing h and length N
// that also includes x0 if N is odd
std::vector<double> makegrid(double x0, double h, int n) {
    int N = 2*n + 1;
    std::vector<double> grid(N);

    for (int i = 0; i < N; i++) {
        grid[i] = x0 + (i - n)*h;
    }
    
    return grid;
}

// The optimal way of doing these derivatives would involve calculating the coefficients
// on runtime, but, it is too much of a hassle, specially without any other helper functions
// like system solving and matrix operations. 
std::vector<std::vector<std::vector<double>>> finitediffcoeff = {
    {
        {-1./2., 0., 1./2.},
        {1./12., -2./3., 0., 2./3., -1./12.},
        {-1./60., 3./20., -3./4., 0., 3./4., -3./20., 1./60.},
        {1./280., -4./105., 1./5., -4./5., 0., 4./5., -1./5., 4./105., -1./280.}
    },
    {
        {1., -2., 1.},
        {-1./12., 4./3., -5./2., 4./3., -1./12.},
        {1./90., -3./20., 3./2., -49./18., 3./2., -3./20., 1./90.},
        {-1./560., 8./315., -1./5., 8./5., -205./72., 8./5., -1./5., 8./315., -1./560.}
    },
    {
        {-1./2., 1., 0., -1., 1./2.},
        {1./8., -1., 13./8., 0., -13./8., 1., -1./8.},
        {-7./240., 3./10., -169./120., 61./30., 0., -61./30., 169./120., -3./10., 7./240.},
    },
    {
        {1., -4., 6., -4., 1.},
        {-1./6., 2., -13./2., 28./3., -13./2., 2., -1./6.},
        {7./240., -2./5., 169./60., -122./15., 91./8., -122./15., 169./60., -2./5., 7./240.}   
    },
    {
        {-1./2., 2., -5./2., 0., 5./2., -2., 1./2.},
        {1./6., -3./2., 13./3., -29./6., 0., 29./6., -13./3., 3./2., -1./6.},
        {-13./288., 19./36., -87./32., 13./2., -323./48., 0., 323./48., -13./2., 87./32., -19./36., 13./288.}
    },
    {
        {1., -6., 15., -20., 15., -6., 1.},
        {-1./4., 3., -13., 29., -75./2., 29., -13., 3., -1./4.},
        {13./240., -19./24., 87./16., -39./2., 323./8., -1023./20., 323./8., -39./2., 87./16., -19./24., 13./240.}
    }
};

// finitediff computes the finite difference approximation of the mth derivative
// of f at x0 using 2n + 1 points. There is some limitation though, the maximum value
// of m is 6 (order of derivative) and the maximum value of n is 4 for the first and 
// second derivatives and 3 for the third until 6th derivatives.
double finitediff(std::function<double(double)> f, double x0, int m, int n) {
    double eps = 1.0e-3; 

    std::vector<double> alpha = makegrid(x0, eps, n);
    std::vector<double> coeff = finitediffcoeff[m - 1][n - 1];

    double sum = 0.0;

    for (int i = 0; i < 2*n + 1; i++) {
        sum += coeff[i]*f(alpha[i]);
    }

    return sum/pow(eps, m);
}