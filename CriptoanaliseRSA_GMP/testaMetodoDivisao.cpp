// Biblioteca Standard C++
#include <iostream>
#include <cmath>
#include <limits>
#include <string>
#include <fstream> // necessário para lidar com os ficheiros
#include <chrono> // Para medir o tempo

// Biblioteca GMP
#include <gmp.h>
#include <gmpxx.h> 

// Biblioteca do Projecto
#include "criptoanalise.hpp"

using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[]) {
    
    if (argc < 3) {
        cout << "Número de argumentos insuficiente\n\n";
        cout << "Utilização: ./testaMetodoDivisao <lista_primos> <nome_ficheiro_para_escrita>\n\n";
        cout << "Por exemplo: ./testaMetodoDivisao listaPrimos1.lstp resultados.csv\n\n";
        return(1); // código de erro - Número de argumentos insuficiente
    }

    ifstream ficheiroLP(argv[1], ofstream::in);
    
    if (!ficheiroLP) {
        cout << "Impossivel abrir o ficheiro " << argv[1] << "\n\n";
        return(2); // Código de erro, não é possível abrir o ficheiro para leitura
    }
    
    ofstream ficheiroCSV(argv[2], ofstream::out);

    if (!ficheiroCSV) {
        cout << "Impossivel abrir o ficheiro " << argv[2] << "\n\n";
        return(3); // Código de erro, não é possível abrir o ficheiro para escrita
    }

    mpz_class p, q, n;
    int i=0;
    
    ficheiroCSV <<  " ; " << " Método da Divisão " << " ; " <<  " ; " << endl;
    ficheiroCSV << "n" << " ; " << "p" << " ; " << "q" << " ; " << "tempo (ms)" << endl;
    
    while (i<100) {
      ficheiroLP >> p >> q;

      n=p*q;

      // Medir o tempo para métodoDivisao
      auto start = high_resolution_clock::now();
      metodoDivisao(n, p);
      auto stop = high_resolution_clock::now();
      auto duration = duration_cast<std::chrono::milliseconds>(stop - start);
      
      q = n / p;
      ficheiroCSV << n << " ; " << p << " ; " << q << " ; " <<  duration.count() << endl;
      i=i+1;
    }

    ficheiroCSV.close();

    return 0;
}
