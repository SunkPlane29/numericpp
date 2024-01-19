/*
The code in this file will contain various utility function such as binomial
coefficient calculation or data file outputting.
*/
#include "util.h"

#include <bits/stdc++.h>
#include <fstream>
#include <iostream>

long min(long a, long b) {return a < b ? a : b;}

// Binomial coefficient calculation from 
// https://www.geeksforgeeks.org/space-and-time-efficient-binomial-coefficient/
unsigned long bin(int n, int k) {
    unsigned long C[k + 1];
    memset(C, 0, sizeof(C));
 
    C[0] = 1; // nC0 is 1
 
    for (int i = 1; i <= n; i++) {
       
        // Compute next row of pascal triangle using
        // the previous row
        for (int j = min(i, k); j > 0; j--)
            C[j] = C[j] + C[j - 1];
    }
    return C[k];
}

double bin(double n, double k) {
    return double(bin(int(n), int(k)));
}

bool samesize(std::vector<std::vector<double>> data) {
    int size = data[0].size();
    for (int i = 1; i < data.size(); i++) {
        if (data[i].size() != size) {
            return false;
        }
    }
    return true;
}

// writedata each vector in data as a column in a data file that will be a delimited file
// with the delimiter being a space 
void writedata(std::string filename, std::vector<std::vector<double>> data, int precision) {
    if (!samesize(data)) {
        std::cout << "Data vectors are not the same size\n";
        return;
    }

    std::ofstream file;
    file.open(filename);

    for (int i = 0; i < data[0].size(); i++) {
        for (int j = 0; j < data.size(); j++) {
            file << std::setprecision(precision) << std::scientific << data[j][i] << ' '; 
        }
        file << '\n';
    }

    file.close();
}

// linspace returns a vector of n equally spaced points between a and b
std::vector<double> linspace(double a, double b, int n) {
    std::vector<double> x(n);
    double dx = (b - a)/(n - 1);
    for (int i = 0; i < n; i++) {
        x[i] = a + i*dx;
    }
    return x;
}

// ----------------------------
//
// OPERATOR OVERLOADING CODE
//
// ----------------------------

std::vector<double> operator%(std::function<double(double)> f, std::vector<double> x) {
    std::vector<double> y(x.size());
    for (int i = 0; i < x.size(); i++) {
        y[i] = f(x[i]);
    }
    return y;
}

std::vector<double> operator&&(std::vector<double> x, std::vector<double> y) {
    std::vector<double> z(x.begin(), x.end());
    z.insert(z.end(), y.begin(), y.end());
    return z;
}

std::vector<double> operator*(std::vector<double> x, std::vector<double> y) {
    std::vector<double> z(x.size());
    for (int i = 0; i < x.size(); i++) {
        z[i] = x[i]*y[i];
    }
    return z;
}

std::vector<double> operator*(std::vector<double> x, double y) {
    std::vector<double> z(x.size());
    for (int i = 0; i < x.size(); i++) {
        z[i] = x[i]*y;
    }
    return z;
}

std::vector<double> operator*(double y, std::vector<double> x) {
    std::vector<double> z(x.size());
    for (int i = 0; i < x.size(); i++) {
        z[i] = x[i]*y;
    }
    return z;
}

std::vector<double> operator+(std::vector<double> x, std::vector<double> y) {
    std::vector<double> z(x.size());
    for (int i = 0; i < x.size(); i++) {
        z[i] = x[i] + y[i];
    }
    return z;
}

std::vector<double> operator+(std::vector<double> x, double y) {
    std::vector<double> z(x.size());
    for (int i = 0; i < x.size(); i++) {
        z[i] = x[i] + y;
    }
    return z;
}

std::vector<double> operator+(double y, std::vector<double> x) {
    std::vector<double> z(x.size());
    for (int i = 0; i < x.size(); i++) {
        z[i] = x[i] + y;
    }
    return z;
}

std::vector<double> operator-(std::vector<double> x, std::vector<double> y) {
    std::vector<double> z(x.size());
    for (int i = 0; i < x.size(); i++) {
        z[i] = x[i] - y[i];
    }
    return z;
}

std::vector<double> operator-(std::vector<double> x, double y) {
    std::vector<double> z(x.size());
    for (int i = 0; i < x.size(); i++) {
        z[i] = x[i] - y;
    }
    return z;
}

std::vector<double> operator-(double y, std::vector<double> x) {
    std::vector<double> z(x.size());
    for (int i = 0; i < x.size(); i++) {
        z[i] = y - x[i];
    }
    return z;
}

std::vector<double> operator/(std::vector<double> x, std::vector<double> y) {
    std::vector<double> z(x.size());
    for (int i = 0; i < x.size(); i++) {
        z[i] = x[i]/y[i];
    }
    return z;
}

std::vector<double> operator/(std::vector<double> x, double y) {
    std::vector<double> z(x.size());
    for (int i = 0; i < x.size(); i++) {
        z[i] = x[i]/y;
    }
    return z;
}

std::vector<double> operator^(std::vector<double> x, double y) {
    std::vector<double> z(x.size());
    for (int i = 0; i < x.size(); i++) {
        z[i] = pow(x[i], y);
    }
    return z;
}