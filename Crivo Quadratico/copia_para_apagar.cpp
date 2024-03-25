
#include <iostream>
#include <time.h>
#include <string>
#include <map>
#include <fstream>
#include <gmp.h>
#include <vector>

using namespace std;

// Função para verificar se a é um resíduo quadrático módulo p usando o critério de Euler
bool criteiroEuler(mpz_t a, mpz_t p) {
    
    //Declaração
    mpz_t res,pAux;
    
    //Inicialização
    mpz_init(res);
    mpz_init(pAux);
   
    mpz_set(pAux,p);
    mpz_sub_ui(pAux, p, 1);
    // Pomos exp = (p - 1) / 2
    mpz_div_ui(pAux, pAux, 2); 
    
    // result = a^((p-1)/2) mod p
    mpz_powm(res, a, pAux, p);
    
    //verificar o residuo quadratico
    bool residuo_quadratico = (mpz_cmp_ui(res, 1) == 0);

    mpz_clear(pAux);
    mpz_clear(res);

    return residuo_quadratico;
}
//// Função para gerar aleatoriamente um valor a entre 1 e p-1

void gerar_a(mpz_t a, mpz_t p) {
    gmp_randstate_t temp;
    gmp_randinit_default(temp);

    // Usa diferentes seed a cada chamda
    static unsigned long seed = 0;
    gmp_randseed_ui(temp, ++seed);

    mpz_urandomm(a, temp, p); //gera um valor aleatorio entre 0 e p-1   
    mpz_add_ui(a, a, 1);      // gera um valor aleatório entre 1 e p-1

    gmp_randclear(temp);
} 
void baseFatorial(mpz_t *baseF,int tam,int t ,mpz_t rep){
	
	 // Declaração
    mpz_t k,B;

    // Inicialização
    mpz_init(k);
    mpz_init(B);
    mpz_set_ui(k, 3);
    mpz_set_ui(B, 50);

	for(unsigned long long i = 0; mpz_cmp(k, B) != 0; mpz_add_ui(k, k, 1)){
		int j=0;
		//Verificar se o número é primo
		if (mpz_probab_prime_p(k, mpz_get_ui(rep))){
			while(j<tam){
					//inicializar
					mpz_t a;
					mpz_init(a);
					mpz_set_ui(a,1);
					gerar_a(a,k);
					if(criteiroEuler(a,k)){//aplicar o critério de Euler
						mpz_set(baseF[i],k);
						i++;
						break;
					}
					mpz_clear(a);
				j++;
				}
		}
		}
	}
	

// função crivo
void sieving(mpz_t B,mpz_t n, mpz_t *baseF,int tam,int tamBase,mpz_t *sievingBase,int **expVetor){
	
	//Declaração das variaveis
	mpz_t x,res,resAux,mod2;
	
	//Inicialização das variáveis
	mpz_init(x);
	mpz_init(resAux);
	mpz_init(res);
	mpz_init(mod2);
	mpz_set_ui(mod2,2);
	
	mpz_sqrt(x,n);//calcula a raiz
	mpz_add_ui(x,x,1);
	mpz_set_ui(resAux,1);
	
	
	for(int j=0;j<tamBase;j++){
		
		//Definir valor de x, onde x=(sqrt(n)+j)^2
		mpz_mul(res,x,x);
		mpz_sub(res,res,n);
		mpz_set_ui(resAux,1);
		
		for(int i=0;i<tam;i++){
			
			if(mpz_divisible_p(res,baseF[i])!=0 && mpz_cmp_ui(baseF[i],1)!=0 ){
				
				expVetor[j][i]++;//construir a matriz de fatorização
				mpz_mul(resAux,resAux,baseF[i]);
				
				//Declarar pn
				mpz_t pn;
				mpz_init(pn);
				
				mpz_set(pn,baseF[i]);
				mpz_mul(pn,pn,pn);
				
				while(mpz_divisible_p(res,pn)){
					expVetor[j][i]++;
					mpz_mul(resAux,resAux,baseF[i]);
					mpz_mul(pn,pn,baseF[i]);
					
				}
				}
			}
			if(mpz_cmp(resAux,res)==0)
				mpz_set(sievingBase[j],res);
			mpz_mul_ui(resAux,resAux,2);
			if(mpz_cmp(resAux,res)==0)
				mpz_set(sievingBase[j],res);
			gmp_printf("Elemento x  %Zd\n", x);
			gmp_printf("Elemento sievingBase[j]  %Zd\n", sievingBase[j]);
				
	mpz_add_ui(x,x,1);
	} 
}
int main() {

	unsigned long long tamanho_do_vetor = 14; // Tamanho desejado do vetor

	int **expVetor;
    int linhas = 114;
    int colunas = 14;

    // Aloca memória para as linhas
    expVetor = (int **)malloc(linhas * sizeof(int *));
    if (expVetor == NULL) {
        fprintf(stderr, "Erro ao alocar memória para as linhas da matriz.\n");
        exit(1);
    }

    // Aloca memória para cada coluna
    for (int i = 0; i < linhas; i++) {
        expVetor[i] = (int *)malloc(colunas * sizeof(int));
        if (expVetor[i] == NULL) {
            fprintf(stderr, "Erro ao alocar memória para as colunas da matriz.\n");
            exit(1);
        }
    }

    // Inicializando a matriz
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            expVetor[i][j] = 0;
        }
    }
	
	
    // Aloca dinamicamente um vetor de ponteiros mpz_t
	mpz_t *baseF = (mpz_t *)malloc(tamanho_do_vetor * sizeof(mpz_t));
		if (baseF == NULL) {
			fprintf(stderr, "Erro ao alocar memória.\n");
			exit(1);
		}


    

	mpz_t *sievingBase = (mpz_t *)malloc((tamanho_do_vetor+100) * sizeof(mpz_t));
	if (sievingBase == NULL) {
		fprintf(stderr, "Erro ao alocar memória.\n");
		exit(1);
	}
		
	// Inicializa cada elemento do vetor sievingBase
	for (unsigned long long i = 0; i < (tamanho_do_vetor+100); ++i) {
		mpz_init(sievingBase[i]);
		mpz_set_ui(sievingBase[i], 1);
	}
    
    for (unsigned long long i = 0; i < tamanho_do_vetor; ++i) {
        mpz_init(baseF[i]);
        mpz_set_ui(baseF[i],1);
    }
	
    mpz_t p,a,B,rep,n;
    mpz_init(p);
    mpz_set_ui(p, 13);
    mpz_init(n);
    mpz_init(rep);

    
    
    const char *number_str = "227179";
    mpz_set_str(n, number_str, 10);
    mpz_set_ui(rep, 2);
    
	baseFatorial(baseF,tamanho_do_vetor,10,rep);
	
	int tam=14;
	sieving(B,n,baseF,tam,tam+100,sievingBase,expVetor);
	
	for (unsigned long long i = 0; i < tamanho_do_vetor+100; ++i) {
		gmp_printf("Elemento %llu: %Zd\n", i, sievingBase[i]);
	}
	for(int j=0;j<14;j++){
		cout<<"Linha "<<j<<":";
		for(int i=0;i<14;i++){
			cout<<expVetor[j][i]<<" ";
		 }
		 cout<<endl;
	}
	// Libera a memória alocada
	for (unsigned long long i = 0; i < tamanho_do_vetor+100; ++i) {
		mpz_clear(sievingBase[i]);
	}
	free(sievingBase);
	
    mpz_clear(p); // Libera a memória alocada para n
    mpz_clear(a);
    return 0;
}

