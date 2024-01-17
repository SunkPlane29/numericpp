#ifndef GQUAD_H
#define GQUAD_H

#include <functional>

double adapt(double, std::function<double(double,double)>, double, double);

double LegendrePolyn(int, double);
std::function<double(double)> LegendrePolyn(int);

#endif