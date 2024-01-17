#ifndef ROOT_H
#define ROOT_H

#include <functional>
#include <vector>

double bisectionrootfind(std::function<double(double)>, double, double, double eps=1.0e-8, int maxiter=100000);

std::vector<double> bisectionrootfindall(std::function<double(double)>, double, double, int, 
        double eps=1.0e-8, int maxiter=100000, int minroots=0);

#endif