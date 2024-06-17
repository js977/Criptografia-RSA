#ifndef IGD
#define IGD

using namespace std;
int powerMod(int, int, int);// Função para calcular (base^exponent) % modulus 
int conversaoDS_LN(char );//converte letras ---> numeros
char conversaoDS_NL(int );//converte numeros ---> letras
bool ePrimo(int ,int );//verificar mdc de dois numeros
int cifraEncriptar(int,int,int);
int* gerarChavePublica(int ,int );
int* gerarChavePrivada(int , int ,int );
int inversoMultiplicativo(int ,int );
void encriptar(int ,int ,fstream& ,fstream&);
void desencriptar(int,int ,fstream& ,fstream& );

#endif
