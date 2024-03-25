
#include <iostream>
#include <vector>
#include <gmpxx.h>

using namespace std;

// Função para verificar se 'a' é um resíduo quadrático módulo 'p' usando o critério de Euler
bool criterioEuler(const mpz_class &a, const mpz_class &p) {
    mpz_class res, pAux;
    // Calcula (p - 1) / 2
    pAux = p - 1;
    pAux /= 2;
    // Calcula a^(p-1)/2 mod p
    mpz_powm(res.get_mpz_t(), a.get_mpz_t(), pAux.get_mpz_t(), p.get_mpz_t());
    // Verifica se o resultado é igual a 1
    return res == 1;
}

// Função para gerar aleatoriamente um valor 'a' entre 1 e 'p'-1

void gerar_a(mpz_class &a, const mpz_class &p) {
    gmp_randstate_t temp;
    gmp_randinit_default(temp);
    static unsigned long seed = 0;
    gmp_randseed_ui(temp, ++seed);
    mpz_class max_value = p - 1;
    mpz_class min_value = 1;
    mpz_class diff = max_value - min_value + 1;
    mpz_class random_value;

    // Se p for igual a 2, defina 'a' como 1
    if (p == 2) {
        a = 1;
    } else {
        // Caso contrário, gere um valor aleatório dentro do intervalo
        mpz_urandomm(random_value.get_mpz_t(), temp, diff.get_mpz_t());
        a = random_value + min_value;
    }

    gmp_randclear(temp);
}


// Função para preencher o vetor 'baseF' com números primos
void baseFatorial(vector<mpz_class> &baseF, int tam, const mpz_class &rep) {
    mpz_class k = 2;
    mpz_class B = 50;
    for (int i = 0; k != B; ++k) {
        int j = 0;
        if (mpz_probab_prime_p(k.get_mpz_t(), rep.get_ui())) {
			//cout<<"k:"<<k<<endl;
            while (j < tam) {
                mpz_class a;
                // Gera um valor 'a' aleatório
					gerar_a(a, k);
					//cout<<"a:"<<a<<endl;
                // Verifica o critério de Euler para 'a' e 'k'
                if (criterioEuler(a, k)) {
                    baseF[i++] = k;
                    break;
                }
                ++j;
            }
        }
    }
}

// Função de crivo
void sieving(const mpz_class &B, const mpz_class &n, const vector<mpz_class> &baseF, int tam, int tamBase, vector<mpz_class> &sievingBase, vector<vector<int>> &expVetor,vector<vector<mpz_class>> &id) {
    mpz_class x, res, resAux, mod2;
    // Calcula a raiz quadrada de 'n'
    x=sqrt(n);
    x += 1;
    
    resAux = 1;
    
    
           // Garante que os vetores em 'id' têm tamanho suficiente
        if (id.size() < 2) {
            id.resize(2);
        }

		if (id[0].size() < static_cast<size_t>(tamBase)) {
			id[0].resize(tamBase);
			}

		if (id[1].size() < static_cast<size_t>(tamBase)) {
				id[1].resize(tamBase);
		}

    
    
    for (int j = 0; j < tamBase; ++j) {
        res=x*x-n;
        resAux=1;
        id[0][j]=res;
        cout<<"residuo:"<<res<<endl;
        for (int i = 0; i < tam; ++i) {
            // Verifica se 'res' é divisível por 'baseF[i]'
            if (mpz_divisible_p(res.get_mpz_t(), baseF[i].get_mpz_t()) != 0 && baseF[i] != 1) {
				cout<<"baseF[i]:"<<baseF[i]<<endl;
                // Incrementa o contador na matriz 'expVetor'
                ++expVetor[j][i];
                resAux *= baseF[i];
                mpz_class pn = baseF[i];
                pn *= pn;
                // Verifica a divisibilidade consecutiva por 'baseF[i]'
                while (mpz_divisible_p(res.get_mpz_t(), pn.get_mpz_t())) {
                    ++expVetor[j][i];
                    resAux *= baseF[i];
                    pn *= baseF[i];
                    cout<<"p^n "<<baseF[i]<<endl;
                }
            }
        }
        // Verifica se 'resAux' é igual a 'res'
        if (resAux == res){
            sievingBase[j] = res;
            id[1][j]=1;
		}
        x += 1;
    }
}

int matrizMod2(vector<vector<mpz_class>> &id,vector<vector<int>> &expVetor,int tamBase, vector<vector<mpz_class>> &exp ){
	
	
	int it=0;;
	int i,j=0,k=0;
	for(i=0;i<tamBase;i++)//Determinar o nº de linhas da matriz
		if(id[1][i])
			it++;
	exp.resize(it, vector<mpz_class>(tamBase, 0));
	
	    for (i = 0; i < tamBase; i++) {
			if(id[1][i]){
				//cout<<"indice:"<<i<<endl;
				for (j = 0; j < 14; j++){
					//cout << expVetor[i][j] << " ";
					exp[k][j]=expVetor[i][j]%2;
					//cout<< exp[k][j] << " ";
					}
					k++;
				//cout << endl;
		}
    }
	
	//for(i=0;i<it;i++){
		//j = 0;
		//if(id[1][j]){
			//while(j<14){
				//cout<<expVetor[i][j]<<" ";
				//exp[k][j]=expVetor[i][j]%2;
				//j++;
			//}
			//cout << endl;
			//}
			//k++;
		//}
		return it;
}
int main() {
    mpz_class B = 50;
    mpz_class n("227179");
    mpz_class rep = 2;

    vector<mpz_class> baseF(15);
    baseFatorial(baseF, 15, rep);

    vector<mpz_class> sievingBase(100);
    for (auto &element : sievingBase)
        element = 1;

    vector<vector<int>> expVetor(100, vector<int>(15, 0));
    vector<vector<mpz_class>> id(2, vector<mpz_class>(15, 0));
	vector<vector<mpz_class>> exp;
	
    sieving(B, n, baseF, 15, 100, sievingBase, expVetor,id);
	int it=matrizMod2(id, expVetor, 100, exp);
    for (int i = 0; i < 100; ++i)
        cout << "Elemento " << i << ": " << sievingBase[i] << endl;

    for (int j = 0; j < 100; ++j) {
        cout << "Linha " << j << ": ";
        for (int i = 0; i < 15; ++i)
            cout << expVetor[j][i] << " ";
        cout << endl;
    }
    
       for (int j = 0; j < 2; ++j) {
        cout << "Linha " << j << ": ";
        for (int i = 0; i < 100; ++i)
            cout <<"i:"<<i<<"  "<< id[j][i] << endl;
        cout << endl;
    }

    for (int i = 0; i < 10; ++i) {
		cout << "Linha: " << i << ": ";
        for (int j = 0; j < 15; ++j)
            cout << exp[i][j] << " ";
        cout << endl;
    }

    return 0;
}
