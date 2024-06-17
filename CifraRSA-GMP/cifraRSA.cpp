#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include "CifraRSA.hpp"
#include <sstream>
#include <gmpxx.h>
//ALFABETO	
/* a --------->0
 * b --------->1
 * c --------->2
 * d --------->3
 * e --------->4
 * f --------->5
 * g --------->6
 * h --------->7
 * i --------->8
 * j --------->9
 * k --------->10
 * l --------->11
 * m --------->12
 * n --------->13
 * o --------->14
 * p --------->15
 * q --------->16
 * r --------->17
 * s --------->18
 * t --------->19
 * u --------->20
 * v --------->21
 * w --------->22
 * x --------->23
 * y --------->24
 * z --------->25
 * " " ------->26
 */
 

#include <iostream>
#include <string>
#include <fstream>
#include <gmpxx.h> // Inclui os cabeçalhos da biblioteca GMP++

// Função para converter caracteres em números
int conversaoDS_LN(char c) {
    return c - 'a';
}

// Função para converter números em caracteres
char conversaoDS_NL(int num) {
    return 'a' + num;
}

// Função para verificar se um número é primo usando a GMP
bool ePrimo(mpz_class n) {
    return mpz_probab_prime_p(n.get_mpz_t(), 25);
}

// Função para calcular o inverso multiplicativo usando a GMP
mpz_class inversoMultiplicativo(mpz_class n, mpz_class b) {
    mpz_class inv;
    mpz_invert(inv.get_mpz_t(), b.get_mpz_t(), n.get_mpz_t());
    return inv;
}

// Função para gerar a chave pública
mpz_class* gerarChavePublica(mpz_class q, mpz_class p) {
    mpz_class* chaveP = new mpz_class[2];
    mpz_class omega_n = (p - 1) * (q - 1);
    mpz_class e,res;
		
    // Encontrar um valor adequado para e
    for (e = 2; e < omega_n; ++e) {
		
        if (ePrimo(e)!=0){
			mpz_gcd(res.get_mpz_t(),e.get_mpz_t(), omega_n.get_mpz_t());
			if(res==1)
				break;
        }
    }

    chaveP[0] = e;
    chaveP[1] = p * q;

    return chaveP;
}

// Função para gerar a chave privada
mpz_class* gerarChavePrivada(mpz_class p, mpz_class q, mpz_class e) {
    mpz_class* chaveP = new mpz_class[2];
    mpz_class omega_n = (p - 1) * (q - 1);

    // Calculando o inverso multiplicativo de e mod omega_n
    chaveP[0] = inversoMultiplicativo(omega_n, e);
    chaveP[1] = p * q;

    return chaveP;
}

// Função para calcular (base^exp) % mod usando a GMP
mpz_class powerMod(mpz_class base, mpz_class exp, mpz_class mod) {
    mpz_class res;
    mpz_powm(res.get_mpz_t(), base.get_mpz_t(), exp.get_mpz_t(), mod.get_mpz_t());
    return res;
}

// Função para encriptar uma mensagem usando a GMP
mpz_class cifraEncriptar(mpz_class e, mpz_class omega_n, mpz_class msg) {
    return powerMod(msg, e, omega_n);
}

// Função para desencriptar uma mensagem usando a GMP
mpz_class cifraDesencriptar(mpz_class d, mpz_class omega_n, mpz_class c) {
    return powerMod(c, d, omega_n);
}

// Função para encriptar o conteúdo de um arquivo de entrada
void encriptar(mpz_class e, mpz_class n, fstream& fin, fstream& fout) {
    string linha;
    while (getline(fin, linha)) {
        for (char& c : linha) {
            int num = conversaoDS_LN(c); // Converter o caractere em número
            mpz_class aux(num);
            mpz_class auxCifra = cifraEncriptar(e, n, aux); // Encriptar o número
            fout << auxCifra << " "; // Escrever o número encriptado no arquivo de saída
        }
        fout << endl; // Adicionar uma quebra de linha após cada linha encriptada
    }
}

// Função para desencriptar o conteúdo de um arquivo de entrada
void desencriptar(mpz_class d, mpz_class n, std::fstream& fin, std::fstream& fout) {
    string linha;
    while (getline(fin, linha)) {
        istringstream linhaAux(linha);
        mpz_class auxCifra;
        while (linhaAux >> auxCifra) {
            mpz_class auxDesencriptado = cifraDesencriptar(d, n, auxCifra); // Desencriptar o número
            char c = conversaoDS_NL(auxDesencriptado.get_si()); // Converter o número de volta para caractere
            fout << c; // Escrever o caractere desencriptado no arquivo de saída
        }
        fout << endl; // Adicionar uma quebra de linha após cada linha desencriptada
    }
}
 
using namespace std;
/*
int main() {
   mpz_class* chaveP;
    // Gerar chave pública
    mpz_class valor3 = mpz_class(10003199);
    mpz_class valor4 = mpz_class("100000004987");
    chaveP = gerarChavePublica(valor3,valor4);

    // Abrir arquivo de entrada para leitura
    fstream fl("mensagem.txt", ios::in);
    if (!fl.is_open()) {
        cerr << "Impossível abrir o arquivo " << "mensgem1.txt" << endl;
        return 1;
    }

    // Abrir arquivo de saída para escrita
    fstream fe("mensgemCF1.txt", std::ios::out);
    if (!fe.is_open()) {
        cerr << "Impossível criar o arquivo " << "mensgemCF1.txt" << endl;
        return 1;
    }

    // Aplicar a Cifra de Deslocamento Linear
    encriptar(chaveP[0], chaveP[1], fl, fe);

    // Fechar os arquivos
    fl.close();
    fe.close();

    delete[] chaveP; // Liberar a memória alocada

    return 0;
}
*/
 

int main(){

  // Verificar o número de argumento. Não prossegue se não houverem
  // argumentos em número suficiente, dá uma ajuda e saí
  
  //fl -> o ficheiro de leitura 
  //fe -> o ficheiro de escrita
 
  //Declarações das variáveis
  char *mensnormal, *menscifrada;
  mpz_class p(10003199),q("100000004987");
  mpz_class* chaveP;
  mpz_class* chavePv;
  chaveP=gerarChavePublica(p,q);
  //chavePv=gerarChavePublica(atoi(argv[3]),atoi(argv[4]));
  chavePv=gerarChavePrivada(p,q,chaveP[0]);
  
  
  
  //copia do ficheiro de entrada
  //mensnormal = argv[1];

  //copia do ficheiro de saida
  //menscifrada = argv[2];
  
	fstream fl("mensgemCF1.txt", std::ios::in); // Abrir arquivo de entrada para leitura
    if (!fl.is_open()) {
        cerr << "Impossível abrir o arquivo "<< "mensgemCF1.txt"<< std::endl;
        return 1;
    }

    fstream fe("mensagemDF1.txt", std::ios::out); // Abrir arquivo de saída para escrita

    if (!fe.is_open()) {
        cerr << "Impossível criar o arquivo " << "mensagemDF1.txt" << endl;
        return 1;
    }
    // Aplicar a Cifra de Deslocamento Linear
    desencriptar(chavePv[0],chavePv[1] ,fl, fe);

    // Fechar os arquivos
    fl.close();
    fe.close();

    return 0;

} 

/*
using namespace std;

int conversaoDS_LN(char c){//converte letras ---> numeros
	return c - 'a';
}

char conversaoDS_NL(int num) {
        return 'a' + num; // Adiciona o número ao caractere 'a'

}

bool ePrimo(int n,int b){//verifica se n e b são primos
	//Inicializar os valores
	int  n0=n;
	int t0=0;
	int t=1;
	int q=n0/b;
	int r=n0-q*b;
	int temp;
	
	while(r > 0){
		temp=t0 -q*t;
		if (temp >=0)
			temp=temp%n;
		else
			temp=n-((-temp)%n);
		
	//Atualização dos valores
	t0=t;
	t=temp;
	n0=b;
	b=r;
	q=n0/b;
	r=n0-q*b;
}
	if(b==1)
		return 1;
	else
		return 0;
	
}

int inversoMultiplicativo(int n,int b){//calcula o inverso multiplicativo de b mod n
	//inicializar os valores
	int  n0=n;
	int t0=0;
	int t=1;
	int q=n0/b;
	int r=n0-q*b;
	int temp;
	
	while(r > 0){
		temp=t0 -q*t;
		if (temp >=0)
			temp=temp%n;
		else
			temp=n-((-temp)%n);
		
	//Atualização dos valores
	t0=t;
	t=temp;
	n0=b;
	b=r;
	q=n0/b;
	r=n0-q*b;
}
	if(b==1)
		return t;
	else
		return 0;
	
}

int* gerarChavePublica(int q,int p){
	 
	int* chaveP = (int*)malloc(2 * sizeof(int)); // Aloca dinamicamente um array de 2 inteiros
    int omega_n=(p-1)*(q-1);
    if (chaveP == NULL) {
        // Se a alocação falhar
        return NULL;
    }
	//chaveP[1]=(p-1)*(q-1);
	chaveP[1]=p*q;
	//calcular e -->pequeno para melhorar a encriptação
	for(int i=2;i<omega_n;i++){
		
		if(ePrimo(i,omega_n)){
			chaveP[0]=i;
			break;
		}
		}
		return chaveP;
	}
int* gerarChavePrivada(int p, int q,int e){
	// Aloca dinamicamente um array de 2 inteiros
		int* chaveP = (int*)malloc(2 * sizeof(int)); 
    
    if (chaveP == NULL) {
        // Se a alocação falhar
        return NULL;
    }
	chaveP[0]=inversoMultiplicativo((p-1)*(q-1),e);
	chaveP[1]=p*q;
	return chaveP;
}
// Função para calcular (base^exponent) % modulus 
int powerMod(int base, int exp, int mod) {
													
    int res = 1;
    base = base % mod;
// Reduz a base para um valor dentro do módulo 
    while (exp > 0) {
        if (exp % 2 == 1) {
			// Multiplica o resultado pelo valor atual da base e faz o módulo em relação a modulus
			
            res = (res * base) % mod;
        }

        exp = exp/2 ;
        base = (base * base) % mod;
    }

    return res;
}

int cifraEncriptar(int e, int omega_n, int msg) {
    int res = powerMod(msg, e, omega_n);
    return res;
}


int cifraDesencriptar(int d, int omega_n, int c) {
    int res = powerMod(c, d, omega_n);
    return res;
}


void encriptar(int e,int n,fstream& fin,fstream& fout){
int i=0,aux;
string linha;
string nomeMsg;
	while (getline(fin, linha)) {//Obter as linhas do ficheiros
		  while(linha[i]!='\0'){
			aux=conversaoDS_LN(linha[i]);//converter as letras da linha em numeros
			aux=cifraEncriptar(e,n,aux);//Aplicação de encriptação
			i+=1;
			if(aux > n){
				aux=aux%(n);}
			fout <<aux<<" ";}
		fout << endl;
		i=0;}
fout.close();//fechar ambos os ficheiros
fin.close();}


void desencriptar(int d,int n,fstream& fin,fstream& fout){
	int i=0,aux;
	string nomeMsg;
	string linha;
        while (getline(fin, linha)) {//Obter as linhas do ficheiros
			  istringstream linhaAux(linha);
			  while(linhaAux >> aux){
				aux=cifraEncriptar(d,n,aux);//Aplicação de encriptação
				i+=1;
				if(aux > (n)){
					aux=aux%(n);
				}
				fout << conversaoDS_NL(aux);
			}
			fout << endl;
			i=0;
        }
        fin.close();//fechar ambos os ficheiros
        fout.close();
}
*/
