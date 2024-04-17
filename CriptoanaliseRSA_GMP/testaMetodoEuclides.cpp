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
    string temposFactorizacao;

    
    if (argc < 2) {
        cout << "Número de argumentos insuficiente\n\n";
        cout << "Utilização: ./testaMetodoDivisao <lista_primos> <nome_ficheiro_para_escrita>\n\n";
        cout << "Por exemplo: ./testaMetodoDivisao listaPrimos1.lstp resultados.csv\n\n";
        return 1; // código de erro - Número de argumentos insuficiente
    }

    string temposFactorizacao = argv[1];

    ofstream ficheiroCSV(temposFactorizacao.c_str(), ofstream::out);

    if (!ficheiroCSV) {
        cout << "Impossivel abrir o ficheiro " << argv[1] << "\n\n";
        return 2; // Código de erro, não é possível abrir o ficheiro para escrita
    }

    
    mpz_class p, q, n;

    
    mpz_set_str(p.get_mpz_t(), argv[2], 10);
    mpz_set_str(q.get_mpz_t(), argv[3], 10);

    n=p*q;
    

    ficheiro << " ; " << " Método da Divisão " << " ; " <<  " ; " << " Método da Euclides " << " ; " <<  " ; " " Método da Fermat " << " ; " <<  " ; " << endl;
    
    ficheiro << "n" << " ; " << "p" << " ; " << "q" << " ; " << "tempo (ms)" << " ; " << "p" << " ; " << "q" << " ; " << "tempo (ms)" << " ; " << "p" << " ; " << "q" << " ; " << "tempo (ms)" << endl;
    
    int i=0;
    while (i<100) {
        ficheiro << n << " : "; // com ';' final e sem mudar de linha

	
        // Medir o tempo para métodoDivisao
        auto start = high_resolution_clock::now();
        metodoDivisao(n, p);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<std::chrono::milliseconds>(stop - start);

        q = n / p;
        ficheiro << p << " ; " << q << " ; " <<  duration.count() << " ; " ;

        // Medir o tempo para métodoEuclides
        start = high_resolution_clock::now();
        p = metodoEuclides(n);
        stop = high_resolution_clock::now();
        duration = duration_cast<std::chrono::milliseconds>(stop - start);

        q = n / p;
        ficheiro << p << " ; " << q <<  " ; " << duration.count() << " ; " ;

        // Medir o tempo para métodoFermat
        start = high_resolution_clock::now();
        metodoFermat(n, p, q);
        stop = high_resolution_clock::now();
        duration = duration_cast<std::chrono::milliseconds>(stop - start);

        ficheiro << p << " ; " << q << " ; " << duration.count();

        ficheiro << endl;
        mpz_nextprime(p.get_mpz_t(), p.get_mpz_t());
        mpz_nextprime(q.get_mpz_t(), q.get_mpz_t());
        n = p * q;
        i=i+1;
    }

    ficheiro.close();

    return 0;
}
