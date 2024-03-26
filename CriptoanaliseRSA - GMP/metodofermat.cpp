// Biblioteca Standard C++
#include <iostream>
#include <cmath>
#include <limits>

// Biblioteca GMP
#include <gmp.h>
#include <gmpxx.h> 

// Biblioteca do Projecto
#include "criptoanalise.hpp"

using namespace std;

int main() {

    mpz_class n("4509540007616669");
    mpz_class p, q;

    metodoFermat(n, p, q);


    return 0;
}
