// Biblioteca Standard C++
#include <iostream>
#include <string>
#include <fstream> // necessário para lidar com os ficheiros

// Biblioteca GMP
#include <gmp.h>
#include <gmpxx.h> 

// Biblioteca do Projecto

using namespace std;

int main(int argc, char *argv[]) {

  int i=0; // variável de controlo do ciclo
  
    if (argc < 3) {
        cout << "Número de argumentos insuficiente\n\n";
        cout << "Utilização: ./geraPrimos <nome_ficheiro> <p0> <q0> \n\n";
        cout << "Por exemplo: ./geraPrimos listaPrimos.csv 104729 52127\n\n";
        return 1; // código de erro - Número de argumentos insuficiente
    }

    ofstream ficheiro(argv[1], ofstream::out);

    if (!ficheiro) {
        cout << "Impossivel abrir o ficheiro " << argv[1] << "\n\n";
        return 2; // Código de erro, não é possível abrir o ficheiro para escrita
    }

    
    mpz_class p, q, n;

    
    mpz_set_str(p.get_mpz_t(), argv[2], 10);
    mpz_set_str(q.get_mpz_t(), argv[3], 10);

    while (i<100) {
      ficheiro << p << " " << q << endl;

      mpz_nextprime(p.get_mpz_t(), p.get_mpz_t());
      mpz_nextprime(q.get_mpz_t(), q.get_mpz_t());

      i=i+1;
    }

    ficheiro.close();

    return 0;
}

/*
listaPrimos0
./geraPrimos listaPrimos0.lstp 83117 91183

listaPrimos1
./geraPrimos listaPrimos1.lstp 122238373 8226451

listaPrimos2
./geraPrimos listaPrimos2.lstp 967901471 22257067463
*/
