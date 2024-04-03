
// Biblioteca Standard C++
#include <iostream>
#include <cmath>
#include <limits>
#include <string>
#include <fstream> // necessário para lidar com os ficheiros

// Biblioteca GMP
#include <gmp.h>
#include <gmpxx.h> 

// Biblioteca do Projecto
#include "criptoanalise.hpp"

#define TAM_MAX_N 4840

// Função crivo_mpz

//crivo de eratóstenes

void crivo_mpz(const mpz_class &n, vector<mpz_class>& vetor) {
    mpz_class i, j, aux, resto, q,temp;
    int t = 0;

    // Inicialização
    i = 2;
    j = 2;
    temp = sqrt(n);
    // Gerar a lista
    while (j <= temp ) {
        aux = sqrt(j);
        q = j;
        i = 2;
        while (i <= aux )  {
			
            resto = j % i;
            if (resto == 0) {
                q = q / i;
            }
            i = i + 1;
        }
        if (q == j) {
            vetor.push_back(j);
            t++;
        }
        j = j + 1;
    }
}


void metodoDivisao(const mpz_class &n, mpz_class &res) {
	cout<<"n divisao:"<<n<<endl;
    vector<mpz_class> vetor;
    mpz_class aux, s;
    size_t t = 0; // Alteração de int para size_t

    // Chamada da função crivo_mpz para
    // determinar os números primos

    crivo_mpz(n, vetor);

    while (t < vetor.size()) {
        mpz_mod(aux.get_mpz_t(), n.get_mpz_t(), vetor[t].get_mpz_t());
        if (aux == 0) {//a|n então a é o primo que pretendemos
            res = vetor[t];
            return;
        }
        t++;
        res = 0;
    }
}

//
mpz_class mdc(const mpz_class& a, const mpz_class& b) {
    mpz_class temp_a = a;
    mpz_class temp_b = b;
    mpz_class tmp;
    
    while (temp_a % temp_b > 0) {
        tmp = temp_a % temp_b ;
        temp_a = temp_b;
        temp_b = tmp;
        //cout << "temp_a/b: " << temp_a << " " << temp_b << endl;
    }
    return temp_b;
}

mpz_class metodoEuclides(const mpz_class& n){
	vector<mpz_class> resCrivo;
	vector<mpz_class> resM;
	mpz_class aux,lim,res=1,resAux;
	size_t i;

	aux=sqrt(n);
	lim=(aux/10)+1;

	resM.resize(lim.get_ui() + 1);
	for(i=0;i<=lim;i++){
		resM[i]=1;
		}
	crivo_mpz(n,resCrivo);//encontrar os numeros primos

	for(i=0;i<resCrivo.size();i++){
			resM[resCrivo[i].get_ui()/10] = resCrivo[i]*resM[resCrivo[i].get_ui()/10]; // calcular o produto

	}
	i=0;
	while(i<lim){
		if(mdc(resM[i],n)> 1){//verificar mdc(resM[i],n]
			return mdc(resM[i],n);
		}		
		i++;
	}
	return res;
}

void metodoFermat(const mpz_class& n, mpz_class& p, mpz_class& q) {
    mpz_class a, b;
    a = sqrt(n) + 1;
    b = sqrt(a * a - n);

    while (b * b != a * a - n) {//Verificar se b é um inteiro
        a = a + 1;
        b = sqrt(a * a - n);
    }

    p = a + b;
    q = a - b;
}

/*
int main() {
    mpz_class n("123456789012345678901234567890");
    mpz_class* resultado = metodoFermat(n);
    std::cout << "p: " << resultado[0] << std::endl;
    std::cout << "q: " << resultado[1] << std::endl;
    delete[] resultado;
    return 0;
}
* */

/*
int main() {
    

    mpz_class n("4509540007616669");
    
    mpz_class b;
    mpz_class resultado = metodoEuclides(n);
    cout << "Resultado: " << resultado <<endl;
    return 0;
}
*/
/*
int main() {
    mpz_class n("4509540007616669");
    mpz_class res;
    metodoDivisao(n, res);
    gmp_printf("res %Zd\n", res.get_mpz_t());
    return 0;
}
*/ 

/*
int main() {
    //mpz_class n=210528952589;
    mpz_class n("4509540007616669");
    mpz_class p, q;

    metodoFermat(n, p, q);

    std::cout << "p = " << p << std::endl;
    std::cout << "q = " << q << std::endl;

    return 0;
}
*/
