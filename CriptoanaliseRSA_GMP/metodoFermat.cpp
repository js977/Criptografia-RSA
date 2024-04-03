// Biblioteca Standard C++
#include <iostream>
#include <cmath>
#include <limits>
#include <string>
#include <fstream> // necessário para lidar com os ficheiros

// Biblioteca GMP
#include <gmp.h>
#include <gmpxx.h> 

// Biblioteca do Projecto
#include "criptoanalise.hpp"

using namespace std;

int main(int argc, char** argv) {

  string temposFactorizacao; // string que vai conter o nome do ficheiro
  string sn; // o 'n'
  
  if (argc < 3) {
    cout << "número de argumentos insuficiente\n\n";
    cout << "Usar: ./metodoFermat <n> <nome_ficheiro_saida>\n";
    return(1);
  }

  sn = argv[1];
  temposFactorizacao = argv[2];

  //abrir o ficheiro CSV com os tempos de factorização, modo continuação de escrita (append)
  ofstream ficheiroFermat(temposFactorizacao.c_str(),  ofstream::app) ; // app -- append


  if(! ficheiroFermat){
    cout << "Impossivel abrir o ficheiro " << argv[2] << "\n\n";
    return(2); // Código de erro, não é possível abrir o ficheiro para continuação de escrita
  }

  //  cout << sn << temposFactorizacao << endl;

  
  mpz_class n=stoi(sn,nullptr,10);
  mpz_class p, q;

  int tempo = 0; // modificar para os procedimentos correctos quanto ao tempo
  
  metodoFermat(n, p, q);
  
  ficheiroFermat << tempo << " ; " << p << " ; " << q << " ; "; // não muda de linha (vai continuar a escrever
  ficheiroFermat.close(); // fecha o ficheiro;
  
  return 0;
}
