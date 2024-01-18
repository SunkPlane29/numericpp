#ifndef FINITEDIFF_H
#define FINITEDIFF_H

#include <functional>

double finitediff(std::function<double(double)>, double, int, int);

#endif