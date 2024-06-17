#include <iostream>
#include <cmath>
#include "CifraRSA.hpp"
#include <fstream>
#include <string>
#include <fstream>

using namespace std;

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
  int p,q;
  int* chaveP;
  int* chavePv;
  p=atoi(argv[3]);
  q=atoi(argv[4]);
  chaveP=gerarChavePublica(atoi(argv[3]),atoi(argv[4]));
  chavePv=gerarChavePublica(atoi(argv[3]),atoi(argv[4]));
  chavePv=gerarChavePrivada(p,q,chaveP[0]);
  //copia do ficheiro de entrada
  mensnormal = argv[1];

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
    desencriptar(chavePv[0],chavePv[1] ,fl, fe);

    // Fechar os arquivos
    fl.close();
    fe.close();

    return 0;

}

