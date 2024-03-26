// Biblioteca Standard C++
#include <iostream>
#include <cmath>
#include <limits>
#include <string>

// Biblioteca GMP
#include <gmp.h>
#include <gmpxx.h> 

// Biblioteca do Projecto
#include "criptoanalise.hpp"

using namespace std;

int main(int argc, char** argv) {

  if (argc < 2) {
    cout << "número de argumentos insuficiente\n\n";
    cout << "Usar: ./metodoFermat 4509540007616669\n";
    return(1);
  }

  string sn =argv[1];

  cout << sn;
  
  mpz_class n("4509540007616669");
  mpz_class p, q;
  
  metodoFermat(n, p, q);
  
  cout << "método de Fermat : " << p << "\t " << q;
  
  return 0;
}
