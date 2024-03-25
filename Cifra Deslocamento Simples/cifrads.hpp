#ifndef IGD
#define IGD

using namespace std;

int conversaoDS_LN(char );//converte letra para numero
int cifraEncriptar(int,int ,int );//Encripta a letra
int cifraDesencriptar(int ,int,int);//Desencripta a letra
void encriptar(int,fstream&,fstream&);//encripta o texto
char conversaoDS_NL(int );//converte número para letra
void desencriptar(int ,fstream& ,fstream& );//desencripta o texto
void quebraCifra(string );//quebra a cifra gerando todas as combinações possíveis do texto cifrado
#endif
