#include "diffsolve.h"

#include <functional>
#include <vector>

#include "util.h"

// nextpoint is the Runge-Kutta 4th order method to calculate the next point in the system solution
std::vector<double> nextpoint(DiffEqSystem f, std::vector<double> point, double h) {
    double tempt = point[0];
    std::vector<double> tempx = std::vector<double>(point.begin() + 1, point.end());

    std::vector<double> kn1 = f(point);
    std::vector<double> kn2 = f(std::vector<double>({tempt + (h/2.0)})&&(tempx + ((h/2.0)*kn1)));
    std::vector<double> kn3 = f(std::vector<double>({tempt + (h/2.0)})&&(tempx + ((h/2.0)*kn2)));
    std::vector<double> kn4 = f(std::vector<double>({tempt + h})&&(tempx + (h*kn3)));
    
    return std::vector<double>({tempt+h})&&(tempx + ((h/6.0)*(kn1 + (2.0*kn2) + (2.0*kn3) + kn4)));
}

std::vector<double> newxn(std::vector<double> xn, double h) {
    return std::vector<double>({xn[0] + h})&&(std::vector<double>(xn.begin() + 1, xn.end()));
}

// solvesystem solves a system of differential equations using the Runge-Kutta 4th order method
// (RK4) and returns a vector of vectors (matrix) of the solution. The RK4 method is better at
// nonlinear systems compared to the Euler (or Newton) method, that would highly depend of the
// step size h being really small. One curiosity about the RK4 method is that when it's used on
// a single equation that does not depend on the independent variable, it's equivalent to the
// Simpson's method of same order for numeric integration.
std::vector<std::vector<double>> solvesystem(DiffEqSystem f,
        std::vector<double> start, double h, ConditionFunc condition) {

    std::vector<std::vector<double>> solution;
    solution.push_back(start);

    std::vector<double> xn = start;
    int i = 1;

    while (condition(newxn(xn, h), i)) {
        xn = nextpoint(f, xn, h);
        solution.push_back(xn);

        i++;
    }

    return solution;
}