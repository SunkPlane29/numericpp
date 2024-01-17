#include "gquad.h"
#include "root.h"
#include "util.h"

#include <iostream>
#include <cmath>
#include <vector>

int main() {
    // overflow for n > 32
    int n = 5;
    std::vector<double> roots =  getpoints(n);

    for (int i = 0; i < roots.size(); i++) {
        std::cout << "Root " << i << ": " << roots[i] << "\n";
    }
}