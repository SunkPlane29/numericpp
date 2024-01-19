#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <string>
#include <functional>

unsigned long bin(int, int);
double bin(double, double);
void writedata(std::string, std::vector<std::vector<double>>, int precision=8);

std::vector<double> linspace(double, double, int);
std::vector<double> operator%(std::function<double(double)>, std::vector<double>);
std::vector<double> operator&&(std::vector<double>, std::vector<double>);
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

#endif