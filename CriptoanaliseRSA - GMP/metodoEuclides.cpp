#include <iostream>
#include <cmath>
#include "criptoanalise.hpp"
#include <gmpxx.h> 


using namespace std;

int main(){
  mpz_class n,p,q;
 
  n=488754769;
    
  p=metodoEuclides(n);
  
  q = n /p;
  return 0;

}
