#include <iostream>
#include <cmath>
#include "criptoanalise.hpp"
#include <gmpxx.h> 


using namespace std;

int main(){
	unsigned long long int   n,p,q;
	
    n=488754769;
    
    p=metodoEuclides(n);
    
	q = n /p;
    return 0;
	
		
}
