#include <iostream>
#include <cmath>
#include "CifraDS.hpp"
#include <fstream>
#include <string>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]){

  // Verificar o número de argumento. Não prossegue se não houverem
  // argumentos em número suficiente, dá uma ajuda e saí
  if(argc!=4) {
    printf("Utilizacao: \n\t\t projectoDL nome_ficheiro_entrada nome_ficheiro_saida chave1 \n\n");
    exit(1);
  }
  
  //fl -> o ficheiro de leitura 
  //fe -> o ficheiro de escrita
 
  //copia do ficheiro de entrada
  

  //copia do ficheiro de saida
  
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
    encriptar(atoi(argv[3]),fl, fe);  // funcao atoi() recebe uma string e devolve o inteiro que nela esta
  // representado

    // Fechar os arquivos
    fl.close();
    fe.close();

    return 0;

}
