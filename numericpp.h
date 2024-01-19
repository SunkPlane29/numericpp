#ifndef NUMERICPP_H
#define NUMERICPP_H

//NOTE: this is also a hack to allow the simple compilation of the files and
// then the use by only copying this header and the archive file

#include <vector>
#include <string>
#include <functional>

// ----------------------------
// util_h

unsigned long bin(int, int);
double bin(double, double);
void writedata(std::string, std::vector<std::vector<double>>, int precision=8);

std::vector<double> linspace(double, double, int);
std::vector<double> operator%(std::function<double(double)>, std::vector<double>);
std::vector<double> operator*(std::vector<double>, std::vector<double>);
std::vector<double> operator*(std::vector<double>, double);
std::vector<double> operator*(double, std::vector<double>);
std::vector<double> operator+(std::vector<double>, std::vector<double>);
std::vector<double> operator+(std::vector<double>, double);
std::vector<double> operator+(double, std::vector<double>);
std::vector<double> operator-(std::vector<double>, std::vector<double>);
std::vector<double> operator-(std::vector<double>, double);
std::vector<double> operator-(double, std::vector<double>);
std::vector<double> operator/(std::vector<double>, std::vector<double>);
std::vector<double> operator/(std::vector<double>, double);
std::vector<double> operator^(std::vector<double>, double);

// ----------------------------
// root_h

double bisectionrootfind(std::function<double(double)>, double, double, double eps=1.0e-8, int maxiter=100000);

std::vector<double> bisectionrootfindall(std::function<double(double)>, double, double, int, 
        double eps=1.0e-8, int maxiter=100000, int minroots=0);

// ----------------------------
// gquad_h

double gquad(std::function<double(double)>, double, double, int);

// ----------------------------
// finitediff_h

double finitediff(std::function<double(double)>, double, int, int);

// ----------------------------
// diffsolve_h

using DiffEqSystem = std::function<std::vector<double>(std::vector<double>)>;
using ConditionFunc = std::function<bool(std::vector<double>, int)>;

std::vector<std::vector<double>> solvesystem(DiffEqSystem, std::vector<double>, double, ConditionFunc);

#endif