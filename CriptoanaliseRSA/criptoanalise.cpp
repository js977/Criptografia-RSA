#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include "criptoanalise.hpp"
#include <fstream>
#include <sstream>
#include <chrono>
#include <limits>
using namespace std;
using namespace std::chrono;

void crivo(unsigned long long int  n, unsigned long long int  *vetor){
     int i,j;
     
    //gerar a lista                     
      for (i = 2; i <= n; i++)
         vetor[i] = 1;
      
      i = 2;
      while (i*i <= n)
      {
        /* Marca os multiplos de i.                */
        for (j=i+1; j<=n; j++)
          if (vetor[j]!=0 && j%i ==0)//se i for divisor de j retirarmos j
            vetor[j] = 0;
    
        /* encontrar o próximo primo     */
        for (j = i + 1; vetor[j] == 0 && j <= n; j++);
        i = j;
      }    
      
      /*for(i=2;i<=n;i++){
		cout<<vetor[i]<<" "<<i<<endl;
	 } */
}
//Metodo das divisões

/*
A abordagem consiste em empregar a técnica da fatoração por tentativa
 */

unsigned long long int  metodoDivisao(unsigned long long int  n){
	
	unsigned long long int  *resCrivo = new unsigned long long int [n + 1],i;
	crivo(n,resCrivo);//Determinar os números primos
	for(i=2;i<=n;i++){
		if(resCrivo[i]){//verificar quais dos numeros sao primos
			if((n%i)==0){
				return i;//retornar numero primo
			}
		}
	 }
	 return 0;
}

unsigned long long int  mdc(unsigned long long int  a,unsigned long long int  b) {
  unsigned long long int  temp;
  while ((a % b) > 0) {
    temp= a % b;
    a = b;
    b = temp;
  }
  return b;
}

unsigned long long int  metodoEuclides(unsigned long long int  n){
	unsigned long long int  *resCrivo = new unsigned long long int [n + 1],i,aux,lim,res=1;
	aux=floor(sqrt(n));
	lim=(aux/10)+1;
	unsigned long long int  *resM= new unsigned long long int [aux+1];
	for(i=0;i<=lim;i++){
		resM[i]=1;
		}
	crivo(n,resCrivo);//encontrar os numeros primos
	for(i=2;i<=aux;i++){
		if(resCrivo[i]){
			resM[(i/10)]=i*resM[i/10];//calcular o produto
		}
	}
	i=0;
	while(i<lim){
		if(mdc(resM[i],n)> 1){//verifcar mdc(resM[i],n]
			return mdc(resM[i],n);
		}		
		i++;
	}
	delete[] resCrivo;
	delete[] resM;
	return res;
}

unsigned long long int* metodoFermat(unsigned long long int n){
	long double a,b;
	unsigned long long int *res= new unsigned long long int[2];
	a=floor(sqrt(n))+1;
	b=sqrt(a*a-n);
	//retorna o maior número inteiro menor ou n
	while(abs(b - floor(b)) > std::numeric_limits<long double>::epsilon()){
	a=a+1;//incrementar a
	b=sqrt(a*a-n);//incrementar b
	}
	//calcular p e q
	res[0]=a+b;
	res[1]=a-b;
	return res;
}
