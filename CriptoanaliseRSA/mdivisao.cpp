#include <iostream>
#include <cmath>
#include "criptoanalise.hpp"
#include <chrono>


using namespace std;
using namespace std::chrono;
/*
void crivo(int n, int *vetor){
     int i,j;
     
    //gerar a lista                     
      for (i = 2; i <= n; i++)
         vetor[i] = 1;
      
      i = 2;
      while (i*i <= n)
      {
        
        for (j=i+1; j<=n; j++)
          if (vetor[j]!=0 && j%i ==0)//se i for divisor de j retirarmos j
            vetor[j] = 0;
    
        
        for (j = i + 1; vetor[j] == 0 && j <= n; j++);
        i = j;
      }      
}

int metodoDivisao(int n){
	
	int *resCrivo = new int[n + 1],i;
	crivo(n, resCrivo);
	for(i=2;i<=sqrt(n);i++){
		if(resCrivo[i]){
			if((n%i)==0){
				return i;
			}
		}
	 }
	 delete[] resCrivo; // Liberar memória alocada dinamicamente
	 return 0;
}*/
int main(){
	unsigned long long int  n;
	unsigned long long int  resp, resq;
    //n=488754769;
    n=488754769;

    auto start = high_resolution_clock::now(); // Marca o início da execução
    resp = metodoDivisao(n);
    auto stop = high_resolution_clock::now(); // Marca o fim da execução

    auto duration = duration_cast<milliseconds>(stop - start); // Calcula a duração em milissegundos
    double durationSeconds = duration.count() / 1000.0; // Converte milissegundos para segundos

    cout << "Tempo de execucao: " << durationSeconds << " segundos" << endl;

    resq = n / resp;
    cout << "p:" << resp << endl;
    cout << "q:" << resq << endl;

    return 0;
	
		
}
