#include <iostream>
#include <cmath>

void encontrarValores(unsigned long long int n) {
    long double a = floor(sqrt(n)) + 1;
    long double b = sqrt(a * a - n);

    while (std::abs(b - floor(b)) > std::numeric_limits<long double>::epsilon()) {
        a = a + 1;
        b = sqrt(a * a - n);
    }

    std::cout << "Para n = " << n << ", os valores são:" << std::endl;
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
}

int main() {
    unsigned long long int n = 128228613281;
    encontrarValores(n);

    return 0;
}

