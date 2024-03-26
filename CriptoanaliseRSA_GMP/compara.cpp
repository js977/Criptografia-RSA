/*
 * Programa para comparar os diferente métodos de Criptoanálise da cifra RSA
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

// Use gmpxx.h para utilizar mpz_class
#include <gmpxx.h> 


using namespace std;

int main(int argc, char *argv[]) {

  string temposFactorizacao; // string que vai conter o nome do ficheiro
  
  if (argc < 2) {
    cout << "Número de argumentos insuficiente\n\n";
    cout << "Utilização: ./compara <nome_ficheiro_para_escrita>\n\n";
    return (1); // código de erro - Número de argumentos insuficiente
  }

  temposFactorizacao = argv[1];

  //abrir o ficheiro CSV com os tempos de factorização, modo escrita
  ofstream ficheiro( temposFactorizacao.c_str(),  ofstream::out) ; // out -- escrita

  if(! ficheiro){
    cout << "Impossivel abrir o ficheiro " << argv[1] << "\n\n";
    return(2); // Código de erro, não é possível abrir o ficheiro para escrita
  }
  
  // escreve no ficheiro o n ; p ; q
  int p = 29207, q = 37579, n = 1097569853;

  ficheiro << n << " ; " << p << " ; " << q << " ; "; // com ';' final e sem mudar de linha

  ficheiro.close(); // fecha o ficheiro;
  
  /* ciclo que gera ns e os passa ... modificar para ser um ciclo
   * /

  /*
   * Agora chama os diversos métodos, os quais vão escrever dados no ficheiro
   * sem mudar de linha;
   */
  // chama o método de Fermat com o 'n' e o nome do ficheiro
  string comando = "./metodoFermat " + to_string(n) + " " + temposFactorizacao + ";";

  system(comando.c_str()); // o método escreve: t1 ; p ; q ; --- com ';' final e sem mudar de linha

  // o outro métodos (divisão, Euclides, Fermat)

  // vai fechar a linha
  
  // re-abrir o ficheiro CSV com os tempos de factorização, modo escrita no fim
  ficheiro.open( temposFactorizacao.c_str(),  ofstream::app) ; // app --- append
  ficheiro << endl;
  ficheiro.close(); // volta a fechar o ficheiro;

  // fim do ciclo 
  
  return 0;
}


/*

compara ciclo de geração de ns
e chamada dos diferentes métodos
cálcula os tempos

---cada método recebe o n na linha de comando e escreve os p q



*/
