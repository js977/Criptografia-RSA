#include <iostream>
#include <cmath>
#include "criptoanalise.hpp"
#include <limits>
#include <gmp.h>
#include <gmpxx.h> 
using namespace std;
using namespace std::chrono;

int main() {

    mpz_class n("4509540007616669");
    mpz_class p, q;

    metodoFermat(n, p, q);


    return 0;
}
