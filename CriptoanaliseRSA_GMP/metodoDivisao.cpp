#include <iostream>
#include <cmath>
#include "criptoanalise.hpp"
#include <gmpxx.h> 

using namespace std;

int main(){
	mpz_class n(488754769), p, q;

    metodoDivisao(n,p);
    q = n / p;

    return 0;
	
		
}
