#include <iostream>
#include <cmath>
#include "criptoanalise.hpp"
#include <chrono>
#include <limits>

using namespace std;
using namespace std::chrono;

int main(){
	unsigned long long int  n;
    n = 701123;
    //bool aux=abs(b - floor(b)) > std::numeric_limits<long double>::epsilon();
    //cout<<aux<<endl;
    
    auto start = high_resolution_clock::now(); // Marca o início da execução
    unsigned long long int *res = metodoFermat(n);
    auto stop = high_resolution_clock::now(); // Marca o fim da execução

    auto duration = duration_cast<milliseconds>(stop - start); // Calcula a duração em milissegundos
    double durationSeconds = duration.count() / 1000.0; // Converte milissegundos para segundos
	cout << "Resultado: a = " << res[0] << ", b = " << res[1] << endl;
    cout << "Tempo de execucao: " << durationSeconds << " segundos" << endl;

	delete[] res;
    return 0;
	
		
}

