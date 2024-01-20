/*
This may look like an important executable file but it's mostly a test file
*/
#include "numericpp.h"

#include <iostream>
#include <vector>
#include <cmath>

int main() {
    double alpha = 0.01;
    double beta = 0.02;
    double x0 = 20.0;
    double y0 = 20.0; 

    DiffEqSystem f = [alpha, beta](std::vector<double> x) {
        return std::vector<double>({
            x[1]*(1 - (alpha*x[2])),
            x[2]*((beta*x[1]) - 1)
        });
    };

    double maxt = 15.0;

    ConditionFunc condition = [maxt](std::vector<double> x, int i) {
        return x[0] < maxt && i < 100000;
    };

    double h = 0.01;
    std::vector<double> initialpoint = {0.0, x0, y0};

    std::vector<std::vector<double>> solution = solvesystem(f, initialpoint, h, condition);
    solution = transpose(solution);
    writedata("preypredatorsol.dat", solution, 8); 
}