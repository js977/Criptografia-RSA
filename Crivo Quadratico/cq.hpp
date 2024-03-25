#ifndef IGD
#define IGD

using namespace std;

/*
 * Encontrar números primos menor ou igual B(FALTA METER B) tal que
 * existem a_i satisfazendo a_i^2 congrente a n
 * --> n1 : int - tamanho do vetor
 * --> n2 : int - nº de números aleatórios gerados
 * <-- baseF : base fatorial : vetor de primos até B
 */
void baseFatorial(vector<mpz_class> &, int , const mpz_class &);

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
void sieving(const mpz_class &, const mpz_class &, const vector<mpz_class> &, int , int , vector<mpz_class> &, vector<vector<int>> &expVetor,vector<vector<mpz_class>> &);

/*
 * Transforma a matra A em matriz B=A(mod 2)
 * --> expVetor : vector<vector<int>> - matriz (mod 2)
 * --> tamBase : int - nº de colunas da matriz id
 * <-- exp : vector<vector<mpz_class>> - matriz (mod 2)
 */
int matrizMod2(vector<vector<mpz_class>> &,vector<vector<int>> &,int , vector<vector<mpz_class>> &);
#endif
