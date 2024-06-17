#include <iostream>
#include <cmath>
#include "CifraDL.hpp"
#include <fstream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

int main(int argc, char *argv[]){

  // Verificar o número de argumento. Não prossegue se não houverem
  // argumentos em número suficiente, dá uma ajuda e saí
  //fl -> o ficheiro de leitura 
  //fe -> o ficheiro de escrita
  
   if (argc < 2) {
        cerr << "Número insuficiente de argumentos. Uso: nome_do_programa arquivo_entrada" << endl;
        return 1;
    }
    
    // Aplicar a função quebra cifra
    quebraCifra(argv[1]);


    return 0;

}



