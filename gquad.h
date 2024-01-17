#ifndef GQUAD_H
#define GQUAD_H

#include <functional>
#include <vector>

double adapt(double, std::function<double(double,double)>, double, double);

double LegendrePolyn(int, double);
std::function<double(double)> LegendrePolyn(int);
std::vector<double> getpoints(int);

#endif