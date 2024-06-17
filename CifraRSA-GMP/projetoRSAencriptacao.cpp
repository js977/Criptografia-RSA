#include <iostream>
#include <cmath>
#include "CifraRSA.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <gmpxx.h>

using namespace std;

int main(int argc, char *argv[]) {
    // Verificar o número de argumentos
    if (argc != 5) {
        std::cerr << "Utilização:\n\t\t projetoDL nome_ficheiro_entrada nome_ficheiro_saida chave1 chave2\n\n";
        return 1;
    }
   mpz_class* chaveP;
    // Gerar chave pública
    mpz_class valor3 = mpz_class(atoi(argv[3]));
    mpz_class valor4 = mpz_class(atoi(argv[4]));
    chaveP = gerarChavePublica(valor3,valor4);

    // Abrir arquivo de entrada para leitura
    fstream fl(argv[1], ios::in);
    if (!fl.is_open()) {
        cerr << "Impossível abrir o arquivo " << argv[1] << endl;
        return 1;
    }

    // Abrir arquivo de saída para escrita
    fstream fe(argv[2], std::ios::out);
    if (!fe.is_open()) {
        cerr << "Impossível criar o arquivo " << argv[2] << endl;
        return 1;
    }

    // Aplicar a Cifra de Deslocamento Linear
    encriptar(chaveP[0], chaveP[1], fl, fe);

    // Fechar os arquivos
    fl.close();
    fe.close();

    delete[] chaveP; // Liberar a memória alocada

    return 0;
}

/*
int main(int argc, char *argv[]){

  // Verificar o número de argumento. Não prossegue se não houverem
  // argumentos em número suficiente, dá uma ajuda e saí
  if(argc!=5) {
    printf("Utilizacao: \n\t\t projectoDL nome_ficheiro_entrada nome_ficheiro_saida chave1 chave2\n\n");
    exit(1);
  }
  
  //fl -> o ficheiro de leitura 
  //fe -> o ficheiro de escrita
 
  //Declarações das variáveis
  char *mensnormal, *menscifrada;
  int ch,caracter,resultado;
  int chave1,chave2,valora,valorb;
  char caracteres[2];
  int* chaveP;
  chaveP=gerarChavePublica(atoi(argv[3]),atoi(argv[4]));
  //copia do ficheiro de entrada
  mensnormal = argv[1];
  
  // funcao atoi() recebe uma string e devolve o inteiro que nela esta
  // representado
  //copia do ficheiro de saida
  menscifrada = argv[2];
  
	std::fstream fl(argv[1], std::ios::in); // Abrir arquivo de entrada para leitura
    if (!fl.is_open()) {
        std::cerr << "Impossível abrir o arquivo "<< argv[1]  << std::endl;
        return 1;
    }

    std::fstream fe(argv[2], std::ios::out); // Abrir arquivo de saída para escrita

    if (!fe.is_open()) {
        std::cerr << "Impossível criar o arquivo " << argv[2] << std::endl;
        return 1;
    }
    // Aplicar a Cifra de Deslocamento Linear
    encriptar(chaveP[0], chaveP[1],fl, fe);

    // Fechar os arquivos
    fl.close();
    fe.close();

    return 0;

}
*/
