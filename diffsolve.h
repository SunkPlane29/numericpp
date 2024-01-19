#ifndef DIFFSOLVE_H
#define DIFFSOLVE_H

#include <functional>
#include <vector>

using DiffEqSystem = std::function<std::vector<double>(std::vector<double>)>;
using ConditionFunc = std::function<bool(std::vector<double>, int)>;

std::vector<std::vector<double>> solvesystem(DiffEqSystem, std::vector<double>, double, ConditionFunc);

#endif