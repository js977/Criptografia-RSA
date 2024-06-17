#ifndef IGD
#define IGD
#include <fstream> // Incluindo a biblioteca fstream
#include <sstream>
using namespace std;

bool ePrimo(int ,int );//verificar se mdc(a,b)=1
int inversoMultiplicativo(int,int);//Encontrar o inverso multiplicativo
int conversaoDS_LN(char );//converte letra para numero
int cifraEncriptar(int , int,int ,int );//Encripta a letra
int cifraDesencriptar(int , int ,int,int);//Desencripta a letra
void encriptar(int,int,fstream&,fstream&);//encripta o texto
char conversaoDS_NL(int );//converte número para letra
void desencriptar(int a, int b,fstream& ,fstream& );//desencripta o texto
void quebraCifra(string );//quebra a cifra gerando todas as combinações possíveis do texto cifrado
#endif
