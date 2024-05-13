// Biblioteca Standard C++
#include <iostream>
#include <cmath>
#include <limits>
#include <string>
#include <cstdlib>
#include <time.h>
#include <fstream> // necessário para lidar com os ficheiros


// Biblioteca GMP
#include <gmp.h>
#include <gmpxx.h> 
#include <mpfr.h>

// Biblioteca do Projecto
#include "cq.hpp"

using namespace std;

int main(int argc, char** argv) {
	
	string num,ficheiroNome;
	
	
	if (argc < 3) {
	  cout << "Número de argumentos insuficiente\n\n";
	  cout << "Utilização: ./crivoquadratico <n> <nome_ficheiro> \n\n";
	  cout << "Por exemplo: ./crivoquadratico <n> listaPrimos.csv\n\n";
	  return 1; // código de erro - Número de argumentos insuficiente
	}
	
	
	ofstream ficheiro(argv[2], ofstream::out);
	
	if (!ficheiro) {
	  cout << "Impossivel abrir o ficheiro " << argv[1] << "\n\n";
	  return 2; // Código de erro, não é possível abrir o ficheiro para escrita
	}
	
	
	num = argv[1];
	ficheiroNome = argv[2];
	
	mpz_class n=stoi(num,nullptr,10);
	mpz_class p,q;
	
	crivoQuadratico(n,p,q);
	ficheiro << n << " ; " << p << " ; " << q << " ; "; // não muda de linha (vai continuar a escrever
	ficheiro.close(); // fecha o ficheiro;
	
}
