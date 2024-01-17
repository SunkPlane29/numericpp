#include "util.h"

#include <bits/stdc++.h>

long min(long a, long b) {return a < b ? a : b;}

long bin(int n, int k) {
    long C[k + 1];
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