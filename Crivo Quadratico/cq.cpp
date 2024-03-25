#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include "cq.hpp"
#include <gmp.h>
#include <time.h>

using namespace std;


/*
void decN(mpz_t n,mpz_t d, mpz_t s){
	
	mpz_t resto;
	mpz_set_ui(s,0);
	
	//Inicialização
	mpz_init(resto);
	mpz_init(d);
	mpz_set(d,n);
	
	mpz_mod_ui(resto,d,2);
	//decompoe n-1 em 2^s e d 
	while(mpz_cmp_si(resto,1)!=0){
		mpz_add_ui(s,s,1);
		mpz_cdiv_q_ui(d, d, 2);
		mpz_mod_ui(resto,d,2);
		}
	mpz_clear(resto);
}

void potenciaMod(mpz_t a, mpz_t n, mpz_t mod, mpz_t res) {
	
	//Declaração
    mpz_t temp;
    
    //Inicialização
    mpz_init(temp);  
    
    mpz_set(temp, n); 
    mpz_set_ui(res, 1);  

    while (mpz_cmp_ui(temp, 0) > 0) {  // Enquanto temp for maior que zero
        if (mpz_odd_p(temp)) {  // Se temp for ímpar
            mpz_mul(res, res, a);  
            mpz_mod(res, res, mod); 
        }
        mpz_div_ui(temp, temp, 2);  // Dividir temp por 2
        mpz_mul(a, a, a);  
        mpz_mod(a, a, mod);  
    }

    mpz_clear(temp);  // Liberar memória alocada para temp
}

bool miller_rabin(mpz_t n, mpz_t rep) {
    mpz_t d, s, resto, a, nAux, x, y, nMinusOne,nMinusTwo,n2;
    // Inicialização
    mpz_init(d);
    mpz_init(s);
    mpz_init(resto);
    mpz_init(a);
    mpz_init(x);
    mpz_init(y);
    mpz_init(n2);
    mpz_init(nAux);
    mpz_init(nMinusOne);
    mpz_init(nMinusTwo);
    mpz_set_ui(nMinusOne, 1);
    mpz_set_ui(nMinusOne, 2);
    // Gerar número aleatório
    gmp_randstate_t temp;
    gmp_randinit_mt(temp);
    gmp_randseed_ui(temp, time(NULL));
    
    // Decrementar n
    mpz_sub_ui(nAux, n, 1);
    
    mpz_mod_ui(resto, n, 2);
    
    mpz_set_ui(n2,2);
    
    // Se n for par então é composto
    if (mpz_cmp_ui(resto, 0) == 0) {
        mpz_clear(d);
        mpz_clear(s);
        mpz_clear(resto);
        mpz_clear(a);
        mpz_clear(x);
        mpz_clear(y);
        mpz_clear(nAux);
        mpz_clear(nMinusOne);
        return false;
    }
    
    decN(n, d, s);
    
    while(mpz_cmp_ui(rep,0)>0)
    {
		//gerar um número inteiro aleatório uniformemente distribuído entre  0 e n1 - 1 (inclusive)
        mpz_urandomm(a,temp,nMinusOne);
        mpz_add_ui(a,a,1);
        potenciaMod(a, d, n, x);
        if(mpz_cmp_si(x,1)!=0 && mpz_cmp(x,nMinusOne)!=0) //Verificar x==1 || x==n-1
        {                                           
            while(mpz_cmp_ui(s,0)>0)
            {
                potenciaMod(x, n2, n, x);//potência modular
                //Se x == 1 retorna false.
                //se x == n-1 retorna true. 
                if(mpz_cmp_si(x,1)==0) 
                {
                    return 0;
                }
                if(mpz_cmp(x,nMinusOne)==0)
                break;
                mpz_sub_ui(rep,rep,1);
            }
            if(mpz_cmp(x,nMinusOne)!=0)  
            {

                return 0;
            }

        }
        mpz_sub_ui(rep,rep,1);
    }
    return 1;
}
*/
