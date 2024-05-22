#ifndef IGD
#define IGD


// Biblioteca Standard C++
#include <cmath>
#include <vector>
#include <limits>
#include <string>

// Biblioteca GMP
#include <gmp.h>
#include <gmpxx.h> 
#include <mpfr.h>


using namespace std;

/*
 * Encontrar números primos menor ou igual B(FALTA METER B) tal que
 * existem a_i satisfazendo a_i^2 congrente a n
 * --> n1 : int - tamanho do vetor
 * --> n2 : int - nº de números aleatórios gerados
 * <-- baseF : base fatorial : vetor de primos até B
 */
vector<mpz_class> baseFatorial( const mpz_class &,const mpz_class &);

/*
 * Criva a sequencia (x^2 - n), onde x=y,y+1,y+2,.... e y=menor inteiro 
 * que é maior ou igual à sqrt(n)
 * --> B : mpz_class - limite para os nº primos pretendidos
 * --> n : mpz_class - número que pretendemos fatorizar
 * --> baseF : <vector> - vetor de primos
 * --> tam : int - nº de números aleatórios gerados
 * --> tamBase : int - tamnanho da base 
 * <-- sievingBase : vector<mpz_class> - vetor com residuos quadraticos 
 * <-- id : vector<vector<int>> - matriz com os indices dos residuos quadraticos
 */
void sieving(const mpz_class &, const mpz_class &, const vector<mpz_class> &,vector<vector<int>> &,vector<vector<mpz_class>> &,int );

/*
 *Calcular o valor de p tal que p|n
 * --> baseF : vector<pmz_class> - vetor cujo os elementos são a base fatorial 
 * -->  expVetor: vector<vector<int>>:matriz cujos os elementos são os expoentes dos residuos;
 * --> id: vector<vector<mpz_class>>: matriz cujos os elementos são os expoentes dos residuos (mod 2)
 * --> n: mpz_class: valor que pretendemos fatorizar
 * --> baseFX : vector<pmz_class> - vetor cujo os elementos são a NOVA base fatorial 
 * -->  expVetorX: vector<vector<int>>:NOVA matriz cujos os elementos são os expoentes dos residuos;
 * --> idX: vector<vector<mpz_class>>: NOVA matriz cujos os elementos são os expoentes dos residuos (mod 2)
 * <-- y : retorna y tal que x^2 congruente y^2 (mod n)
 */

void sievingParcial(const mpz_class &, const vector<mpz_class> &,vector<vector<int>> &,vector<vector<mpz_class>> &,vector<vector<int>> &,vector<vector<mpz_class>> &,int);
/*
 * Transforma a matra A em matriz B=A(mod 2)
 * --> expVetor : vector<vector<int>> - matriz (mod 2)
 * --> tamBase : int - nº de colunas da matriz id
 * <-- exp : vector<vector<mpz_class>> - matriz (mod 2)
 */
void matrizMod2(vector<vector<mpz_class>> &,vector<vector<int>> &, vector<vector<mpz_class>> &);



/*
 * Encontrar a matriz U em GF(2)
 * --> A : vector<vector<mpz_class>> - matriz (mod 2)
 * <-- A : vector<vector<mpz_class>> - matriz (mod 2)
 */
void gaussEliminationMod2(vector<vector<mpz_class>>& );

/*
 *Calcular o solução de Ux=0
 * --> A : vector<vector<pmz_class>> - matriz (mod 2)
 * --> x : vector<pmz_class> - vetor de solução
 * <-- x : vector<mpz_class> - vetor (mod 2)
 */
int backSolucao(vector<vector<mpz_class>>& , vector<mpz_class>&,int );

/*
 *Função para transpor uma matriz
 * --> A : vector<vector<pmz_class>> - matriz (mod 2)
 * <-- x : vector<mpz_class> - transposta de 'matriz' (mod 2)
 */

vector<vector<mpz_class>> transporMatriz(const vector<vector<mpz_class>>& );

/*
 *Função para imprimir uma matriz
 * --> A : vector<vector<pmz_class>> - matriz (mod 2)
 */
void printMatrix(const vector<vector<mpz_class>>& );

/*
 *Função para imprimir um vetor
 * --> v : vector<vector<pmz_class>> - vetor (mod 2)
 */
void imprimirVetor(const vector<mpz_class>& vetor);

/*
 *Função para copiar os elementos de uma matriz
 * --> Matriz A : vector<vector<pmz_class>> - matri< A (mod 2)
 * <-- Matriz B : vector<vector<pmz_class>> - matri< (mod 2) (N+1)*N, onde N é o número de colunas de A
 */

vector<vector<mpz_class>> copiarParaMatriz(const vector<vector<mpz_class>>&);

/*
 *Função para multiplicar uma matriz Nx(N+1) por um vetor N+1(Para verificar solução)
 * --> matriz : vector<vector<pmz_class>> - matriz (mod 2)
 * --> vetor : vector<pmz_class> - vetor de solução
 * <-- vetor : vector<mpz_class> - vetor (mod 2)
 */

vector<mpz_class> multiplicarMatrizVetor(const vector<vector<mpz_class>>& , const vector<mpz_class>& );
/*
 *Função para copiar os elementos de uma matriz para um vetor solucao
 * --> v : vector<vector<pmz_class>> - vetor (mod 2)
 */
vector<vector<mpz_class>> vetorSolucao(const vector<vector<mpz_class>>& , int ,int); 

/*
 *Calcular o valor de y, onde x^2 congruente y^2 (mod n)
 * --> baseF : vector<pmz_class> - vetor cujo os elementos são a base fatorial 
 * -->  expVetor: vector<vector<int>>:matriz cujos os elementos são os expoentes dos residuos;
 * --> id: vector<vector<mpz_class>>: matriz cujos os elementos são os expoentes dos residuos (mod 2)
 * <-- y : retorna y tal que x^2 congruente y^2 (mod n)
 */

mpz_class yValor(vector<mpz_class> &,const mpz_class &, vector<vector<int>> &,const vector<vector<mpz_class>>& ,vector<mpz_class>& );

/*
 *Calcular o valor de p tal que p|n
 * --> baseF : vector<pmz_class> - vetor cujo os elementos são a base fatorial 
 * -->  expVetor: vector<vector<int>>:matriz cujos os elementos são os expoentes dos residuos;
 * --> id: vector<vector<mpz_class>>: matriz cujos os elementos são os expoentes dos residuos (mod 2)
 * --> n: mpz_class: valor que pretendemos fatorizar
 * <-- y : retorna y tal que x^2 congruente y^2 (mod n)
 */

mpz_class solucaoPrimo(vector<vector<mpz_class>>& ,vector<mpz_class> &,const mpz_class &, vector<vector<int>> &,const vector<vector<mpz_class>>&);

/*
 *Calcular B
 * --> n :mpfr_t : valor que pretendemos fatorizar
 * <-- B :mpz_class: retorna B
 */

mpz_class valorB(const mpfr_t );
/*
 * --> n: mpz_class: valor que pretendemos fatorizar
 * <-- p : mpz_class: valor de retorno
 * <-- q : mpz_class: valor de retorno
 */

void crivoQuadratico(const mpz_class &,mpz_class &, mpz_class &);

#endif
