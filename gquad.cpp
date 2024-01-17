#include "gquad.h"

#include <cmath>
#include <functional>
#include <vector>

#include "util.h"
#include "root.h"

std::function<double(double)> adapt(std::function<double(double)> f, double a, double b) {
    return [f, a, b](double xi) {return f((b - a)*xi/2.0 + (b + a)/2.0)*((b - a)/2.0);};
}

#include <stdexcept>

/*!
 * @brief Calculates the binomial coefficient indexed by n and k
 *
 * This implementation is based on the algorithm described here: http://blog.plover.com/math/choose.html
 * and the relevant follow-up: http://blog.plover.com/math/choose-2.html
 *
 * @param n                     The number of elements
 * @param k                     The number of elements in each subset
 * @return                      The number of k-element subsets in a n-element set
 *
 * @throw std::overflow_error   If the computation caused an overflow
 */
uint64_t bc(uint64_t n, uint64_t k)
{
    if (k > n)
        return 0;

    if (n - k < k)
        k = n - k;

    uint64_t r = 1;

    for (uint64_t d = 1; d <= k; d++)
    {
        uint64_t mult = n;

        bool divided = true;

        if (mult % d == 0)
            mult /= d;
        else if (r % d == 0)
            r /= d;
        else
            divided = false;

        const uint64_t r_mult = r * mult;
        if (r_mult / mult != r)
            throw std::overflow_error("Overflow");

        r = r_mult;

        if (!divided)
            r /= d;

        n--;
    }

    return r;
}

double LegendrePolyn(int n, double x) {
    int a = floor(n/2.0);
    double sum = 0.0; 

    for (int k = 0; k <= a; k++) {
        sum += pow(-1.0, k)*bin(n, k)*bin(2*n - 2*k, n)*pow(x, n - 2*k);
    }

    return sum/pow(2.0, n);
}

std::function<double(double)> LegendrePolyn(int n) {
    return [n](double x) {return LegendrePolyn(n, x);};
}

std::vector<double> getpoints(int n) {
    auto f = LegendrePolyn(n);
    double a = -1.0; double b = 1.0;
    int subintervals = n;
    int minroots = n;
    
    std::vector<double> roots = bisectionrootfindall(f, a, b, subintervals, 
            1.0e-8, 100000, minroots);

    if (n % 2 != 0) {
        roots[roots.size()/2] = 0.0;
    }

    return roots;
}

double LegendrePolynDeriv(int n, double x) {
    int imax = floor(n/2.0);
    if (n % 2 == 0) {
        imax -= 1;
    }

    double sum = 0.0;

    for (int k = 0; k <= imax; k++) {
        sum += pow(-1.0, k)*bin(n, k)*bin(2*n - 2*k, n)*(n - 2*k)*pow(x, n - 2*k - 1);
    }

    return sum/pow(2.0, n);
}

std::function<double(double)> LegendrePolynDeriv(int n) {
    return [n](double x) {return LegendrePolynDeriv(n, x);};
}

double getweight(int n, double x) {
    return 2.0/((1.0 - pow(x, 2.0))*pow(LegendrePolynDeriv(n, x), 2.0));
}

std::vector<double> getweights(std::vector<double> points, int n) {
    std::vector<double> weights(points.size());
    for (int i = 0; i < points.size(); i++) {
        weights[i] = getweight(n, points[i]);
    }

    return weights;
}

double quadsum(std::function<double(double)> f, std::vector<double> points, 
        std::vector<double> weights) {
    double sum = 0.0;
    for (int i = 0; i < points.size(); i++) {
        sum += weights[i]*f(points[i]);
    }

    return sum;
}

double gquad(std::function<double(double)> f, double a, double b, int n) {
    std::vector<double> points = getpoints(n);
    std::vector<double> weights = getweights(points, n);

    if (a == -1.0 && b == 1.0) {
        return quadsum(f, points, weights);
    } else {
        return quadsum(adapt(f, a, b), points, weights);
    }
}