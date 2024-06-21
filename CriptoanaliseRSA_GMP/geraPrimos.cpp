// Biblioteca Standard C++
#include <iostream>
#include <string>
#include <cstdlib>     /* atoi */
#include <fstream> // necessário para lidar com os ficheiros

// Biblioteca GMP
#include <gmp.h>
#include <gmpxx.h> 

// Biblioteca do Projecto

using namespace std;


/*
 * Programa para gerar uma lista de primos para efeito de testes dos
 * algoritmos de factorização.
 * Usa  a «mpz_nextprime» da biblioteca GMP para gerar o «próximo primo».
 *
 * --> nome_ficheiro : string - ficheiro com a lista de primos gerada
 * --> p0 : mpz - primeiro primo a ser considerado (tem de ser um número primo)
 * --> q0 : mpz - segundo primo a ser considerado (tem de ser um número primo)
 *   (p0,q0) são o primeiro par de primos da lista de pares de primos;
 * --> factor : int - factor entre primos, distância entre pares de primos
 * <-- o ficheiro de texto com um par de primos por linha
 *
 */ 

int main(int argc, char *argv[]) {

  int i=0; // variável de controlo do ciclo
  
    if (argc < 4) {
        cout << "Número de argumentos insuficiente\n\n";
        cout << "Utilização: ./geraPrimos <nome_ficheiro> <p0> <q0> <factor>\n\n";
        cout << "Por exemplo: ./geraPrimos listaPrimos.txt 3351419 264949 2\n Iria gerar uma lista de 100 pares de primos: (p0,q0), (p1,q1), ... em que p1 >= p0*factor e q1 >= factor \n";
        return 1; // código de erro - Número de argumentos insuficiente
    }

    ofstream ficheiro(argv[1], ofstream::out);

    if (!ficheiro) {
        cout << "Impossivel abrir o ficheiro " << argv[1] << "\n\n";
        return 2; // Código de erro, não é possível abrir o ficheiro para escrita
    }

    int factor;
    mpz_class p, q, n;

    
    mpz_set_str(p.get_mpz_t(), argv[2], 10);
    mpz_set_str(q.get_mpz_t(), argv[3], 10);
    factor = atoi(argv[4]);
    
    while (i<100) {
      ficheiro << p << " " << q << endl;

      p = p*factor;
      q = q*factor;
      
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
