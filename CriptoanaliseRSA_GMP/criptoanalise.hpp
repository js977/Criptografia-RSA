#ifndef IGD
#define IGD


#include <vector>
#include <gmpxx.h> // Use gmpxx.h para utilizar mpz_class
#include <cmath>

using namespace std;

/*
 * Implementação do crivo de eratóstenes
 * --> n : mpz_class
 * <-- vetor: vector<mpz_class> - array de primos 
 */
void crivo_mpz(const mpz_class &, vector<mpz_class>& );

/*
 * fatoriza n na forma n=p*q, onde p e q são primos
 * --> n : mpz_class - nº para ser fatorizado
 * <-- res : mpz_class - retorna primo res
 */
void metodoDivisao(const mpz_class &, mpz_class &);

/*
 * calcula maximo divisor comum de a e b
 * --> a : mpz_class 
 * --> b : mpz_class
 * <-- res : mpz_class - retorna o máximo divisor comum res
 */
mpz_class mdc(const mpz_class& , const mpz_class& );

/*
 * fatoriza n na forma n=p*q, onde p e q são primos
 * --> n : mpz_class
 * <-- res : mpz_class - retorna o máximo divisor comum res
 */
mpz_class metodoEuclides(const mpz_class& n);

/*
 * fatoriza n na forma n=p*q, onde p e q são primos
 * --> n : mpz_class
 * <-- p : mpz_class - primo tal que p|n
 * <-- q : mpz_class - primo tal que q|n
 */
void metodoFermat(const mpz_class& , mpz_class& , mpz_class& );
#endif
