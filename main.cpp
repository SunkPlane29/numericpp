/*
This may look like an important executable file but it's mostly a test file
*/
#include "numericpp.h"

#include <iostream>
#include <vector>
#include <cmath>

int main() {
    int m = 2;
    int n = 2;
    double x0 = 1.0;

    auto f = [](double x){return 3*pow(x, 3.0);}; 

    std::cout << finitediff(f, x0, m, 2) << std::endl;
}