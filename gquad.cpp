#include "gquad.h"

double adapt(double xi, double f(double), double a, double b) {
    return f(((b - a)/2.0)*xi + ((a + b)/2.0))*((b - a)/2.0);
}