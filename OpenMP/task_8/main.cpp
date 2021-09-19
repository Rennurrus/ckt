#include <iostream>
#include <vector>
#include "omp.h"

std::vector<double> task8(const int n, const std::vector<double>& A, const std::vector<double>& B) {
    std::vector<double> C(n * n);
    double tmp = 0;
#pragma omp parallel for reduction(+:tmp)
    for (int i = 0; i < n; i++) {
        for (int m = 0; m < n; m++) {
            tmp = 0;
            for (int j = 0; j < n; ++j) {
                tmp += A[n * i + j] * B[n * j + m];
            }
            C[n * i + m] = tmp;
        }
    }
    return C;
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<double> A(n * n);
    std::vector<double> B(n * n);
    for (int i = 0; i < n*n; ++i) {
        std::cin >> A[i];
    }
    for (int i = 0; i < n * n; ++i) {
        std::cin >> B[i];
    }
    std::vector<double> C = task8(n,A,B);
    for (int i = 0; i < n * n; ++i) {
        if (!(i % n) && i)
            std::cout << "\n";
        std::cout << C[i] << ' ';
    }
    std::getchar();
}
