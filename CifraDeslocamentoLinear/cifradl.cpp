#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include "CifraDL.hpp"
#include <fstream>
#include <sstream>
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

using namespace std;


bool ePrimo(int n,int b){//verifica se n e b são primos
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

int conversaoDS_LN(char c){//converte letras ---> numeros
	return c - 'a';
}

char conversaoDS_NL(int num){//Converte numeros em letras
return 97+num;
}
int cifraEncriptar(int a, int b,int num,int modnum){
	return (a*num+b)%modnum;
	}
int cifraDesencriptar(int a, int b,int num,int modnum){
	if(ePrimo(a,26)){
	return ((inversoMultiplicativo(modnum,a)))*(num-b)% modnum;
	}else
	return 0;
	}
	
	void encriptar(int a, int b,fstream& fin,fstream& fout){//Encripta mensagens
	int i=0,aux;
	string linha;
	string nomeMsg;
		while (getline(fin, linha)) {//Obter as linhas do ficheiros
			  while(linha[i]!='\0'){
				aux=conversaoDS_LN(linha[i]);//converter as letras da linha em numeros
				aux=cifraEncriptar(a,b,aux,26);//Aplicação de encriptação
				i+=1;
				if(aux >26){
					aux=aux%26;
				}
				fout << conversaoDS_NL(aux);
			}
			fout << endl;
			i=0;
		}
			fout.close();//fechar ambos os ficheiros
			fin.close();
			
		}

void desencriptar(int a, int b,fstream& fin,fstream& fout){//desencripta mensagens
	
	if(ePrimo(a,26)){//validação da chave
	int i=0,aux;
	//string nomeMsg;
	string linha;
		while (getline(fin, linha))  {//Obter as linhas do ficheiro.txt
			cout<<linha;
			cout<<endl<<"De mili ne";
			  while(linha[i]!='\0'){
				aux=linha[i];
				aux=conversaoDS_LN(linha[i]);
				aux=cifraDesencriptar(a,b,aux,26);//cifra para desencriptar
				while(aux<0){
					aux=aux+26;
				}
				i+=1;
				fout << conversaoDS_NL(aux);
			}
			fout << endl;
			i=0;
		}
		fout.close();
		fin.close();
		
		}
	else{
		cout<<"a não tem inverso multiplicativo modulo 26"<<endl;
	}
}
void quebraCifra(string nome) {
	int k = 0;
	string nomeMsg;
	string linha;
	fstream fd;
	for (int b = 0; b <= 26; b++) {
		for (int a = 1; a <= 26; a++) {
			if(ePrimo(a,26)){
			fstream fin(nome, std::ios::in | std::ios::binary); // abrir o ficheiro
			if (!fin.is_open()) {
				cerr << "Impossível abrir o arquivo " << endl;
				return; // no caso de não conseguir abrir o ficheiro
			}
			k = k + 1;
			nomeMsg = "MensagemDecifrada" + to_string(k) + ".txt";
			fd.open(nomeMsg, std::ios::out);
			if (!fd.is_open()) {
				cerr << "Impossível criar o arquivo " << nomeMsg << endl;
				return; }
			desencriptar(a, b, fin, fd);
			fd.close();
			//fin.clear(); // Clear the stream state
			fin.seekg(0); // Move file pointer to the beginning of the file
			fin.close();}}}
	 // Close the file outside the loops
	 }

