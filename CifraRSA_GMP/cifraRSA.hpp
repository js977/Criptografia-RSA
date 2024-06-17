#ifndef IGD
#define IGD
#include <gmpxx.h>
using namespace std;

/*
 * Função para calcular (base^exponent) % modulus 
 * --> base : mpz_class 
 * --> exp : mpz_class - expoente
 * --> mod : mpz_class - modulus
 * <-- res : mpz_class - retorna (base^exponent) % modulus 
 */

mpz_class powerMod(mpz_class, mpz_class, mpz_class);
/*
 * Função para gerar a chave pública
 * --> p : mpz_class - nº primo
 * --> q : mpz_class - nº primo
 * <-- res : mpz_class - chave publica
 */
mpz_class* gerarChavePublica(mpz_class , mpz_class );

/*
 * Função para gerar a chave privada
 * --> p : mpz_class - nº primo
 * --> q : mpz_class - nº primo
 * --> e : mpz_class - 1 < e < phi(n) tal que seja primo relativamante a
 * phi(n)
 * <-- res : mpz_class - chave privada
 */

mpz_class* gerarChavePrivada(mpz_class , mpz_class , mpz_class );

/*
 * Função para encriptar o conteúdo de um arquivo de entrada
 * --> e : mpz_class 
 * --> n : mpz_class 
 * --> fin : fstream - nome do ficheiro texto de entrada
 * <-- fout : fstream - nome do ficheiro texto de saída
 */
void encriptar(mpz_class , mpz_class ,fstream& ,fstream& );

/*
 * Função para desencriptar o conteúdo de um arquivo de entrada
 * --> d : mpz_class 
 * --> n : mpz_class
 * --> fin : fstream - nome do ficheiro de entrada
 * <-- fout : fstream - nome do ficheiro de saida
 */
void desencriptar(mpz_class , mpz_class ,fstream& ,fstream&);
#endif
