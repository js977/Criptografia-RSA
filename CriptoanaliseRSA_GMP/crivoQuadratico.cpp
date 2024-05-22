// Biblioteca Standard C++
#include <iostream>
#include <cmath>
#include <limits>
#include <string>
#include <time.h>

// Biblioteca GMP
#include <gmp.h>
#include <mpfr.h>
#include <gmpxx.h> 

// Biblioteca do Projecto
#include "crivoQuadratico.hpp"



using namespace std;

// Função para verificar se 'a' é um resíduo quadrático módulo 'p' usando o critério de Euler
bool CrivoQuadratico::criterioEuler(const mpz_class &a, const mpz_class &p) {
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

void  CrivoQuadratico::gerar_a(mpz_class &a, const mpz_class &p) {
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

// Função para calcular o ln(x) usando MPFR
double  CrivoQuadratico::ln_mpfr(const mpfr_t x) {
    // Inicializando o objeto result
    mpfr_t result;
    mpfr_init(result);

    // Calculando o logaritmo natural de x
    mpfr_log(result, x, MPFR_RNDN);
	
	double res = mpfr_get_d(result, MPFR_RNDN);

	mpfr_clear(result);
    return res;
}

mpz_class CrivoQuadratico::valorB(const mpfr_t n){
	
	int i=0;
	double temp=ln_mpfr(n),res;
	// Definir a precisão desejada (em bits)
    unsigned int precisao = 256;
    
    //Declarar e inicializar as variaveis
	mpfr_t temp_mpfr;
    mpfr_init(temp_mpfr);
	
	//Converter double para mfpr
    mpfr_set_d(temp_mpfr, temp, MPFR_RNDN);
    //Calcular expoente
	res=0.5*sqrt(temp*ln_mpfr(temp_mpfr));
	
	mpz_class auxB(res);

	mpf_class fB("2.7182",precisao);
	
	//calcular valor de B
	while(i<auxB){
		i=i+1;
		fB=fB*2.71828;
		}
	
	mpz_class B(fB);
	mpfr_clear(temp_mpfr);
	return B;
	}

// Função para preencher o vetor 'baseF' com números primos
vector<mpz_class>  CrivoQuadratico::baseFatorial(const mpz_class &B,const mpz_class &n) {
	
	//Declaração das variaveis
	vector<mpz_class> baseF;
    mpz_class k = 2,rep=2;
    
    
    for (; k != B; ++k) {
		//Verificar se k é primo
        if (mpz_probab_prime_p(k.get_mpz_t(), rep.get_ui())) {
					//verificar se satisfar (n|p)=1(Legendre)
                if (mpz_legendre(n.get_mpz_t(), k.get_mpz_t())==1) {
                    baseF.push_back(k);
               }
            
        }
    }

	return baseF;
}


//Sieving Parrcial: Serve para otimizar o calculo dos residuos



// Função de crivo
void CrivoQuadratico::sievingParcial(const mpz_class &n, const vector<mpz_class> &baseF,vector<vector<int>> &expVetor,vector<vector<mpz_class>> &id,vector<vector<int>> &expVetorX,vector<vector<mpz_class>> &idX,int resiQ) {
   
    
    //Declaração das variaveis
    size_t l,j,t=0,i;
    mpz_class x, res, resAux, mod2;
    int auxExpVetor[baseF.size()];
    
    for(l=0;l<baseF.size();l++)
		auxExpVetor[l]=0;
    // Calcula a raiz quadrada de 'n'
    x=sqrt(n);
    x += 1;
    
    resAux = 1;
    
    //copiar as informções de expVetor para expVetorX
    for(i=0;i<expVetor.size();i++){
		
		for(j=0;j<expVetor[0].size();j++){
			
			expVetorX[i][j]=expVetor[i][j];
			
			}
		}
    //copiar as informções de id para idX
     for(i=0;i<id.size();i++){
		for(j=0;j<id[0].size()-1;j++){
			idX[i][j]=id[i][j];
			
			}
		}  
    for (j = idX[0].size()-1; t<idX[0].size(); ++j) {
        res=x*x-n;
        mpz_mod(res.get_mpz_t(),res.get_mpz_t(),n.get_mpz_t());
        resAux=1;
        
        for(l=0;l<baseF.size();l++)
			auxExpVetor[l]=0;
        
        for (size_t i = 0; i < baseF.size(); ++i) {
			
            // Verifica se 'res' é divisível por 'baseF[i]'
            if (mpz_divisible_p(res.get_mpz_t(), baseF[i].get_mpz_t()) != 0 && baseF[i] != 1) {
				
                // Incrementa o contador na matriz 'expVetor'
                ++auxExpVetor[i];
                resAux *= baseF[i];
                mpz_class pn = baseF[i];
                pn *= pn;
                // Verifica a divisibilidade consecutiva por 'baseF[i]'
                while (mpz_divisible_p(res.get_mpz_t(), pn.get_mpz_t())) {
                    ++auxExpVetor[i];
                    resAux *= baseF[i];
                    pn *= baseF[i];
                }
                
            }
            
        }
        // Verifica se 'resAux' é igual a 'res'
        if (resAux == res){
			for(l=0;l<baseF.size();l++){
				expVetorX[t][l]=auxExpVetor[l];
			}
			
            idX[1][t]=x;
            idX[0][t]=res;
            t=t+1;
		}
        x += 1;
    }
}




// Função de crivo
void CrivoQuadratico::sieving(const mpz_class &B, const mpz_class &n, const vector<mpz_class> &baseF,vector<vector<int>> &expVetor,vector<vector<mpz_class>> &id,int resiQ) {
   
    //Declaração das variaveis
    size_t l,t=0;
    mpz_class x, res, resAux, mod2;
    int auxExpVetor[baseF.size()];
    
    for(l=0;l<baseF.size();l++)
		auxExpVetor[l]=0;
    // Calcula a raiz quadrada de 'n'
    
    
    
    x=sqrt(n);
    x += 1;
    
    resAux = 1;
    
    
           // Garante que os vetores em 'id' têm tamanho suficiente
        if (id.size() < 2) {
            id.resize(2);
        }

		if (id[0].size() < static_cast<size_t>(baseF.size())) {
			id[0].resize(baseF.size());
			}

		if (id[1].size() < static_cast<size_t>(baseF.size())) {
				id[1].resize(baseF.size());
		}

    for (size_t j = 0; t<expVetor.size(); ++j) {
        res=x*x-n;
        mpz_mod(res.get_mpz_t(),res.get_mpz_t(),n.get_mpz_t());
        resAux=1;
        for(l=0;l<baseF.size();l++)
			auxExpVetor[l]=0;
        
        for (size_t i = 0; i < baseF.size(); ++i) {
			
			
            // Verifica se 'res' é divisível por 'baseF[i]'
            if (mpz_divisible_p(res.get_mpz_t(), baseF[i].get_mpz_t()) != 0 && baseF[i] != 1) {
                // Incrementa o contador na matriz 'expVetor'
                ++auxExpVetor[i];
                resAux *= baseF[i];
                mpz_class pn = baseF[i];
                pn *= pn;
                // Verifica a divisibilidade consecutiva por 'baseF[i]'
                while (mpz_divisible_p(res.get_mpz_t(), pn.get_mpz_t())) {
                    ++auxExpVetor[i];
                    resAux *= baseF[i];
                    pn *= baseF[i];
                }
                
            }
            
        }
        // Verifica se 'resAux' é igual a 'res'
        if (resAux == res){
			//cout<<"t:"<<t<<endl;
			for(l=0;l<baseF.size();l++){
				expVetor[t][l]=auxExpVetor[l];
			}
			
            id[1][t]=x;
            id[0][t]=res;
            t=t+1;
		}
        x += 1;
    }
}

void CrivoQuadratico::matrizMod2(vector<vector<mpz_class>> &id,vector<vector<int>> &expVetor,vector<vector<mpz_class>> &exp){
  //Declaração das variaveis
	size_t i,j;
	
	exp.resize(expVetor.size(), vector<mpz_class>(expVetor[0].size(), 0));
	
	    for (i = 0; i < expVetor.size(); i++) {
				for (j = 0; j < expVetor[0].size(); j++){
					exp[i][j]=expVetor[i][j]%2;
					}
			}
}


//Funções para implementar a eliminação de Gauss em GF(2)


// Função para imprimir a matriz
void CrivoQuadratico::printMatrix(const vector<vector<mpz_class>>& matriz) {
    for (const auto& linha : matriz) {
        for (const auto& elemento : linha) {
            cout << elemento << " ";
        }
        cout << endl;
    }
}

// Função para copiar elementos de uma matriz para uma matriz Nx(N+1)
vector<vector<mpz_class>>  CrivoQuadratico::copiarParaMatriz(const vector<vector<mpz_class>>& matriz) {
	//Declaração das variaveis
	size_t i,j;

    // Criar uma matriz aumentada de tamanho Nx(N+1)
    vector<vector<mpz_class>> matriz_aux(matriz.size(), vector<mpz_class> (matriz[0].size()));
    // Copiar os elementos da matriz para a matriz aumentada
    for (i = 0; i < matriz.size(); ++i) {
        for (j = 0; j < matriz[0].size(); ++j) {
            matriz_aux[i][j] = matriz[i][j];
        }
    }

    return matriz_aux;
}


// Função para imprimir um vetor de mpz_class
void CrivoQuadratico::imprimirVetor(const vector<mpz_class>& vetor) {
    for (const auto& elemento : vetor) {
        cout << elemento << " ";
    }
    cout << endl;
}


//Função para transpor uma matriz
vector<vector<mpz_class>> CrivoQuadratico::transporMatriz(const vector<vector<mpz_class>>& matriz) {
    int linhas = matriz.size();
    int colunas = matriz[0].size();

    // Inicializar a matriz transposta com tamanho invertido
    vector<vector<mpz_class>> matriz_transposta(colunas, vector<mpz_class>(linhas));

    // Preencher a matriz transposta
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            matriz_transposta[j][i] = matriz[i][j];
        }
    }

    return matriz_transposta;
}

// Função para multiplicar uma matriz Nx(N+1) por um vetor N+1(Para verificar solução)
vector<mpz_class> CrivoQuadratico::multiplicarMatrizVetor(const vector<vector<mpz_class>>& matriz, const vector<mpz_class>& vetor) {
    int numC = vetor.size(),numL=matriz.size();
    vector<mpz_class> resultado(matriz.size(), 0);

    for (int i = 0; i < numL; i++) {
        for (int j = 0; j < numC; j++) {
            resultado[i] += matriz[i][j] * vetor[j];
        }
        resultado[i]=resultado[i]%2;
    }

    return resultado;
}


// Função para somar os elementos de uma linha de uma matriz
mpz_class CrivoQuadratico::somaLinha(const vector<mpz_class>& linha) {
    mpz_class soma = 0;
    for (const auto& elemento : linha) {
        soma += elemento;
    }
    return soma;
}

//Função para ordena as linhas de uma matriz
void CrivoQuadratico::ordenacao(vector<vector<mpz_class>>& A){
  int numLi = A.size(); // número de linhas
  int numCols = A[0].size(); // número de colunas
	
  int j,jmin=numCols+1, i, t, k=0,imax=numLi+1;
  mpz_class somaL;
	
  for (i = 0; i < numLi; i++) {
			
    somaL=somaLinha(A[i]);
    for (j = 0; j < numCols ; j++) {
				
      //Encontrar o pivo da linha i ou todos os elementos da linha são zero
      if (A[i][j]==1||(j==numCols-1 &&somaL==0)) {
					
	//Procurar , no caso de haver, linhas para permutar
	for (t = i + 1; t < numLi; t++) {
	  for (k = 0; k < numCols; k++) {
	    if (k < j||(j==numCols-1 &&somaL==0)) {  // Verificar se k é menor que j
	      if (A[t][k] == 1) {
		if (k < jmin) {
		  jmin = k;
		  imax = t;
		  break;
		}
	      }
	    }
	  }
	}

	if(imax < numLi+1){//Se a linha for encontrada faz a troca
	  swap(A[i],A[imax]);
	  jmin=numCols+1;
	  imax=numLi+1;
	  break;}
	break;
      }
					
					 
					
    }
        
  }
}


void CrivoQuadratico::gaussEliminationMod2(vector<vector<mpz_class>>& A) {
    int numLi = A.size(); // número de linhas
    int numCols = A[0].size(); // número de colunas
	int j;

	ordenacao(A);

    for (int i = 0; i < numLi; i++) {
        //cout<<"i:"<<i<<endl;
        for (j = 0; j < numCols; j++) { // Procurar pivo na coluna i
            if (A[i][j] == 1)
                break;
        }
        if (A[i][j]){//se encontrar o pivo
        for (int k = i+1; k < numLi; k++) {
            if (A[k][j]) { // Se encontrar outra linha com pivo na mesma coluna
                for (int t = 0; t < numCols; t++) { // Somar as linhas
                    A[k][t] = (A[k][t]+A[i][t])%2;
                }
            }
        }
        ordenacao(A);
	}
    }
}


int CrivoQuadratico::backSolucao(vector<vector<mpz_class>>& A, vector<mpz_class>& x,int nSol) {
    int numL = static_cast<int>(A.size()),numC=A[0].size(), i, j, t,nLivre=0; // número de colunas
    mpz_class res = somaLinha(A[numL - 2]); // Calcula a soma da linha N-2

    // Inicializar x
    if (res == 1 && A[numL - 2][numC - 1] == 1) {
        x[numC - 1] = 0;
    }
    
    // Procurar as variáveis livres
    for (int i = 0; i < static_cast<int>(A.size()); ++i) {
        for (int j = 0; j < static_cast<int>(A[0].size()); ++j) {
            if (A[i][j] == 1) {
                x[j] = -1;
                break; // Sai do loop interno após encontrar o primeiro pivô na linha
            }
        }
    }

    for (i = 0; i < numC; i++){
		if (x[i] != -1){
		//Esta incognita livre vai gerar a solução a ser testada 
			x[i] = 0;
			if(nLivre==nSol){
				x[i]=1;}
			nLivre=nLivre+1;
		}

		}

    // Calcular a partir da última equação até a primeira
    for (i = numL - 2; i >= 0; i--) {
        for (j = 0; j < static_cast<int>(A[i].size()); j++) {
            if (A[i][j] == 1) {
				x[j]=0;
				t=j+1;
				while (t < static_cast<int>(A[i].size())) {
					// Subtraímos todos os valores do LHS, exceto o coeficiente da variável
					x[j] = ((x[j]%2) + ((A[i][t] * x[t])%2))%2;
					
					t++;
				}
                break; // Sai do loop interno após encontrar o primeiro pivô na linha
            }
        }
        
        // Inicializar j para i+1, uma vez que a matriz é triangular superior
        
    
        x[i] = x[i] % 2;
    }
    return nLivre;
    
}

vector<mpz_class> somarVetores(const vector<mpz_class>& vetor1, const vector<int>& vetor2) {
    
    // Verifica se os vetores têm o mesmo tamanho
    if (vetor1.size() != vetor2.size()) {
        // No caso de não terem
        throw invalid_argument("Os vetores devem ter o mesmo tamanho para serem somados.");
    }

    // Cria um vetor para armazenar a soma
    vector<mpz_class> resultado(vetor1.size());

    // Soma os elementos correspondentes dos vetores
    for (size_t i = 0; i < vetor1.size(); ++i) {
        resultado[i] = vetor1[i] + vetor2[i];
    }

    return resultado;
}


mpz_class CrivoQuadratico::yValor(vector<mpz_class> &baseF,const mpz_class &n, vector<vector<int>> &expVetor,const vector<vector<mpz_class>>& id,vector<mpz_class>& x){
	
	//Declaração das variaveis
	mpz_class y=1,auxRes,aux;
    int i,j,N_id=x.size();
	bool yCheck;
	vector<mpz_class> yVetor(expVetor[0].size(), mpz_class(0));
	
	//Passa os residuos e x_i de acordo com a solucao encontrada

	for (j = 0; j < N_id; ++j) {
		if (x[j] == 1) {
			// Procurar o índice do residuo
			auxRes = id[0][j];
				yVetor = somarVetores(yVetor, expVetor[j]);
				}
			}
	
	//vericar se todos os elementos de yVetor são pares
	
	i=0;
	yCheck=true;
	
	//Verificar se algum dos expoentes dos residuos é impar
	while (i < N_id && !yCheck) {
		if (yVetor[i]%2==1) {
			yCheck = false;
		} else {
			i++;
		}
	}
		
	i=0;
	int auxL=expVetor[0].size();
	if(yCheck==true){
		//Dividir os exponetes por 2
		while(i<auxL){
			yVetor[i]=yVetor[i]/2;
			mpz_pow_ui(aux.get_mpz_t(), baseF[i].get_mpz_t(), yVetor[i].get_si());
			y=aux*y;
			mpz_mod(y.get_mpz_t(),y.get_mpz_t(),n.get_mpz_t());
			i=i+1;
			}
			
	}
		else{
			throw invalid_argument("ERRO:expoente impar");
			}
	
	return y;

}


// Função para calcular o MDC usando o algoritmo de Euclides
mpz_class CrivoQuadratico::mdc(const mpz_class& a, const mpz_class& b) {
    mpz_class temp_a = a;
    mpz_class temp_b = b;
    mpz_class tmp;
    
    while (temp_a % temp_b > 0) {
        tmp = temp_a % temp_b ;
        temp_a = temp_b;
        temp_b = tmp;
        //cout << "temp_a/b: " << temp_a << " " << temp_b << endl;
    }
    return temp_b;
}


mpz_class CrivoQuadratico::solucaoPrimo(vector<vector<mpz_class>>& exp,vector<mpz_class> &baseF,const mpz_class &n, vector<vector<int>> &expVetor,const vector<vector<mpz_class>>& id){
	mpz_class a=1,y=1,r=1;
	vector<vector<mpz_class>> matriz = copiarParaMatriz(exp);
	// Transpor a matriz
	vector<vector<mpz_class>> matrizT = transporMatriz(matriz);
	vector<vector<mpz_class>> auxMatrizT = transporMatriz(matriz);
    
    int Nn=matrizT[0].size(),status=0,fStatus=0;
	
	//Aplicar a aeliminacao de Gauss a matrizT
	gaussEliminationMod2(matrizT);
	
	//array para armazenar as soluções
	vector<mpz_class> x(Nn); 
	fStatus=backSolucao(matrizT,x,status);

	do{
		fStatus=backSolucao(matrizT,x,status);
		//cout<<"DE MILI NE"<<endl;
		y=yValor(baseF,n,expVetor,id,x);
		//cout<<"DE MILI NE2"<<endl;
		
		//Passa os residuos e x_i de acordo com a solucao encontrada
		//vector<vector<mpz_class>> x_iResiduos = vetorSolucao(id,Nn,tamResi);
		
		//Faz a multiplicacao da matriz com o veter solucao
		vector<mpz_class> res=multiplicarMatrizVetor(auxMatrizT,x);
		mpz_class somaL=somaLinha(res);
		
		if(somaL==0){
			
			for ( int j = 0; j < Nn; ++j){

				if(x[j]==1){
					a=a*id[1][j];
					mpz_mod(a.get_mpz_t(),a.get_mpz_t(),n.get_mpz_t());

					}
				
		}		
		
		a=a-y;
				mpz_mod(a.get_mpz_t(),a.get_mpz_t(),n.get_mpz_t());
				r=gcd(a,n);

				
		}
		else{
			cout<<"Solução errada!!"<<endl;
		}
		if(r!=1&&r!=n)
			return r;
	status=status+1;
	a=1;
	}while(status<fStatus);

	return r;
	
}


void CrivoQuadratico::crivoQuadratico(const mpz_class &n,mpz_class &p, mpz_class &q){
	
  p=1,q=1;
	
    // Definir a precisão 
    mpfr_set_default_prec(256);
	
	
	
	//int argc, char *argv[]
	mpz_t n_temp;
    mpz_init(n_temp);
    mpz_set(n_temp, n.get_mpz_t());

    // Declar variáveis do tipo mpfr_t
    mpfr_t n_fr;

    // Inicializar a variável
    mpfr_init(n_fr);
	mpfr_set_z(n_fr, n_temp, MPFR_RNDN);
	

	//calcular B
    mpz_class B =valorB(n_fr),r=1;
	vector<mpz_class> baseF=baseFatorial(B,n);

	int h=baseF.size()+1,t=0,resiQ=50;
	
	//Declaração das vaiaveis para o primeiro teste do crivo
	vector<vector<int>> expVetor(h+t, vector<int>(baseF.size(), 0));
	vector<vector<mpz_class>> id(2, vector<mpz_class>(h+t, 0));
	vector<vector<mpz_class>> exp;
	sieving(B, n, baseF,expVetor,id,t);
	matrizMod2(id, expVetor,exp);

	//Calcular a solução 
	p=solucaoPrimo(exp,baseF,n,expVetor,id);
	
	//Verificar se a solução é não trivial
	if(p!=1&&p!=n){
		q=n/p;}
		//ficheiro <<n<<":"<<"    "<<pAux<<"    "<<qAux<<endl;
		
	
	while (p== 1 || p == n) {
		
    // Declaração de matrizes para os testes seguintes
    t = t + 1;

    vector<vector<int>> expVetorX(h + t, vector<int>(baseF.size(), 0));
    vector<vector<mpz_class>> idX(2, vector<mpz_class>(h + t, 0));
    vector<vector<mpz_class>> expX;

    // Calcular as matrizes declaradas anteriormente
    sievingParcial(n, baseF, expVetor, id, expVetorX, idX, resiQ);
    matrizMod2(idX, expVetorX, expX);


    // Calcular a solução obtida
    p = solucaoPrimo(expX, baseF, n, expVetorX, idX);

    // Verificar se a solução obtida é não trivial
    
    if (p == 1 || p== n) {
        if (q != 1 && q != n) {
            p = n / q;
            // ficheiro <<n<<":"<<"    "<<pAux<<"    "<<qAux<<endl;
        }
    }

    // Liberar memória alocada dinamicamente
    expVetorX.clear();
    idX.clear();
    expX.clear();

}
	q=n/p;
	expVetor.clear();
    id.clear();
    exp.clear();
	
	
	};

/*
void CrivoQuadratico::decN(mpz_t n,mpz_t d, mpz_t s){
	
	mpz_t resto;
	mpz_set_ui(s,0);
	
	//Inicialização
	mpz_init(resto);
	mpz_init(d);
	mpz_set(d,n);
	
	mpz_mod_ui(resto,d,2);
	//decompoe n-1 em 2^s e d 
	while(mpz_cmp_si(resto,1)!=0){
		mpz_add_ui(s,s,1);
		mpz_cdiv_q_ui(d, d, 2);
		mpz_mod_ui(resto,d,2);
		}
	mpz_clear(resto);
}

void CrivoQuadratico::potenciaMod(mpz_t a, mpz_t n, mpz_t mod, mpz_t res) {
	
	//Declaração
    mpz_t temp;
    
    //Inicialização
    mpz_init(temp);  
    
    mpz_set(temp, n); 
    mpz_set_ui(res, 1);  

    while (mpz_cmp_ui(temp, 0) > 0) {  // Enquanto temp for maior que zero
        if (mpz_odd_p(temp)) {  // Se temp for ímpar
            mpz_mul(res, res, a);  
            mpz_mod(res, res, mod); 
        }
        mpz_div_ui(temp, temp, 2);  // Dividir temp por 2
        mpz_mul(a, a, a);  
        mpz_mod(a, a, mod);  
    }

    mpz_clear(temp);  // Liberar memória alocada para temp
}

bool miller_rabin(mpz_t n, mpz_t rep) {
    mpz_t d, s, resto, a, nAux, x, y, nMinusOne,nMinusTwo,n2;
    // Inicialização
    mpz_init(d);
    mpz_init(s);
    mpz_init(resto);
    mpz_init(a);
    mpz_init(x);
    mpz_init(y);
    mpz_init(n2);
    mpz_init(nAux);
    mpz_init(nMinusOne);
    mpz_init(nMinusTwo);
    mpz_set_ui(nMinusOne, 1);
    mpz_set_ui(nMinusOne, 2);
    // Gerar número aleatório
    gmp_randstate_t temp;
    gmp_randinit_mt(temp);
    gmp_randseed_ui(temp, time(NULL));
    
    // Decrementar n
    mpz_sub_ui(nAux, n, 1);
    
    mpz_mod_ui(resto, n, 2);
    
    mpz_set_ui(n2,2);
    
    // Se n for par então é composto
    if (mpz_cmp_ui(resto, 0) == 0) {
        mpz_clear(d);
        mpz_clear(s);
        mpz_clear(resto);
        mpz_clear(a);
        mpz_clear(x);
        mpz_clear(y);
        mpz_clear(nAux);
        mpz_clear(nMinusOne);
        return false;
    }
    
    decN(n, d, s);
    
    while(mpz_cmp_ui(rep,0)>0)
    {
		//gerar um número inteiro aleatório uniformemente distribuído entre  0 e n1 - 1 (inclusive)
        mpz_urandomm(a,temp,nMinusOne);
        mpz_add_ui(a,a,1);
        potenciaMod(a, d, n, x);
        if(mpz_cmp_si(x,1)!=0 && mpz_cmp(x,nMinusOne)!=0) //Verificar x==1 || x==n-1
        {                                           
            while(mpz_cmp_ui(s,0)>0)
            {
                potenciaMod(x, n2, n, x);//potência modular
                //Se x == 1 retorna false.
                //se x == n-1 retorna true. 
                if(mpz_cmp_si(x,1)==0) 
                {
                    return 0;
                }
                if(mpz_cmp(x,nMinusOne)==0)
                break;
                mpz_sub_ui(rep,rep,1);
            }
            if(mpz_cmp(x,nMinusOne)!=0)  
            {

                return 0;
            }

        }
        mpz_sub_ui(rep,rep,1);
    }
    return 1;
}
*/
