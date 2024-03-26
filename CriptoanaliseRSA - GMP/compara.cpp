/*
 * Programa para comparar os diferente métodos de Criptoanálise da cifra RSA
 */

#include <iostream>
#include <vector>
#include <cmath>

// Use gmpxx.h para utilizar mpz_class
#include <gmpxx.h> 


using namespace std;

int main() {

  // ciclo que gera ns e os passa 
  string n = "4509540007616669";

  // fixa tempo
  string comando = "./metodoFermat " + n + ";";
  // calcula tempo
  
  system(comando.c_str());
  
  return 0;
}


/*

compara ciclo de geração de ns
e chamada dos diferentes métodos
cálcula os tempos

---cada método recebe o n na linha de comando e escreve os p q



*/
