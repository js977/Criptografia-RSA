#include <iostream>
#include <cmath>
#include "criptoanalise.hpp"
#include <chrono>


using namespace std;
using namespace std::chrono;

int main(){
	unsigned long long int   n,p,q;
    n=488754769;
    //p=metodoEuclides(n);
    //cout << "p:" << p << endl;
    auto start = high_resolution_clock::now(); // Marca o início da execução
    p=metodoEuclides(n);
    auto stop = high_resolution_clock::now(); // Marca o fim da execução

    auto duration = duration_cast<milliseconds>(stop - start); // Calcula a duração em milissegundos
    double durationSeconds = duration.count() / 1000.0; // Converte milissegundos para segundos
	q = n /p;
    cout << "p:" << p << endl;
    cout << "q:" << q << endl;
    cout << "Tempo de execucao: " << durationSeconds << " segundos" << endl;


    return 0;
	
		
}
