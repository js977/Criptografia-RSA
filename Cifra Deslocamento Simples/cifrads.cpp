#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include "CifraDS.hpp"

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

int conversaoDS_LN(char c){//converte letras ---> numeros
	return c - 'a';
}

char conversaoDS_NL(int num){//Converte numeros em letras
return 97+num;
}
int cifraEncriptar(int k,int num,int modnum){
	return (num+k)%modnum;
	}
int cifraDesencriptar(int k,int num,int modnum){
	return (num-k)% modnum;
	}
	void encriptar(int k,fstream& fin,fstream& fout){//Encripta mensagens
		int i=0,aux;
		string linha;
		string nomeMsg;
			while (getline(fin, linha)) {//Obter as linhas do ficheiros
				  while(linha[i]!='\0'){
					aux=conversaoDS_LN(linha[i]);//converter as letras da linha em numeros
					aux=cifraEncriptar(aux,k,26);//Aplicação de encriptação
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

	void desencriptar(int k,fstream& fin,fstream& fout){//desencripta mensagens
		int i=0,aux;
		//string nomeMsg;
		string linha;
			while (getline(fin, linha)){//Obter as linhas do ficheiro.txt
				  while(linha[i]!='\0'){
					aux=linha[i];
					aux=conversaoDS_LN(linha[i]);
					aux=cifraDesencriptar(k,aux,26);//cifra para desencriptar
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


 void quebraCifra(string nome){
	int aux = 0;
	string nomeMsg;
	string linha;
	fstream fd;

	for (int k = 1; k <= 26; k++) {
		fstream fin(nome, std::ios::in | std::ios::binary); // abrir o ficheiro
		if (!fin.is_open()) {
			cerr << "Impossível abrir o arquivo " << endl;
			return; // no caso de não conseguir abrir o ficheiro
		}
		aux = aux + 1;
		nomeMsg = "MensagemDecifrada" + to_string(aux) + ".txt";
		fd.open(nomeMsg, std::ios::out);
		if (!fd.is_open()) {
			cerr << "Impossível criar o arquivo " << nomeMsg << endl;
			return; 
		}

		desencriptar(k, fin, fd);

		fd.close();
		//fin.clear(); // Clear the stream state
		fin.seekg(0); // Move file pointer to the beginning of the file
		fin.close();}}
   
 
