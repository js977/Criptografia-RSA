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
  if(argc < 2) {
    printf("Utilizacao: \n\t\t projectoDL nome_ficheiro_entrada nome_ficheiro_saida chave1 \n\n");
    exit(1);
  }
  
  //fl -> o ficheiro de leitura 
  //fe -> o ficheiro de escrita
 
  //copia do ficheiro de entrada
  

  //copia do ficheiro de saida
  
quebraCifra(argv[1]);
    return 0;

}

