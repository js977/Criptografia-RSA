#include <gmp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void S_and_M(mpz_t a,mpz_t n,mpz_t h, mpz_t r) // square and multiply
{
    char * bin = mpz_get_str(NULL,2,h);  
    int i;                               
    mpz_set(r,a); 
    for(i = 1; i < strlen(bin);i++) 
    {                             
        mpz_mul(r,r,r);
        mpz_mod(r,r,n);
        if(bin[i] == '1')
        {
            mpz_mul(r,r,a);
            mpz_mod(r,r,n);
        }
    }
}
//calcula 2^s
void M2Pow(mpz_t s,mpz_t S_pow)
{
  int i = 0;
  mpz_set_ui(S_pow,1); 
  while(mpz_cmp_si(s,i) > 0 ) 
  {
    mpz_mul_ui(S_pow,S_pow,2);
    i++;
  }
}

void Decomp(mpz_t x,mpz_t s,mpz_t t) // Function to decompose  x in 2^s * t
{                                    
    mpz_t y,S_pow;
    mpz_init(y);
    mpz_set_ui(y,0);

    mpz_init(S_pow);

    while(mpz_cmp(y,x)!=0) // while we don't find 2^s * t = x
    {
        mpz_set_ui(t,1); //we restart with t = 1
        mpz_mul(y,S_pow,t);// y = 2^s * t (we test the values)
        while(mpz_cmp(y,x) < 0)// we stop when 2^s * t > x
        {                      
            mpz_add_ui(t,t,2); 
            M2Pow(s,S_pow);
            mpz_mul(y,S_pow,t);
        }
        mpz_add_ui(s,s,1); 
    }

    mpz_sub_ui(s,s,1);
    mpz_clear(y);
    mpz_clear(S_pow);
}

void testFermat(mpz_t n, mpz_t rep)
{
    gmp_randstate_t state; //gera números aleatórios 
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, time(NULL));

    mpz_t i;
    mpz_init(i);
    mpz_set_si(i,1);

    mpz_t n2;
    mpz_init(n2);
    mpz_sub_ui(n2,n,1);

    mpz_t a;
    mpz_init(a);

    mpz_t r;
    mpz_init(r);

    mpz_t n3;
    mpz_init(n3);
    mpz_sub_ui(n3,n,3);

    while(mpz_cmp(i,rep)<=0 && mpz_cmp_si(n,2)!= 0  && mpz_cmp_si(n,3)!=0)
    {
        mpz_urandomm(a,state,n3);
        mpz_add_ui(a,a,2);
        S_and_M(a,n,n2,r);
        if(mpz_cmp_si(r,1)!=0)
        {
            printf("The number is composite \n");
            mpz_clear(i);mpz_clear(n2);
            mpz_clear(a);mpz_clear(r);
            mpz_clear(n3);gmp_randclear(state);
            return ;
        }
        mpz_add_ui(i,i,1);
    }

    printf("The number is prime \n");
    mpz_clear(i);mpz_clear(n2);
    mpz_clear(a);mpz_clear(r);
    mpz_clear(n3);gmp_randclear(state);
}

void Miller_Rabin(mpz_t n, mpz_t rep)
{
    if(mpz_get_ui(n) % 2 == 0)   
    {
        if(mpz_cmp_ui(n,2) == 0)
            printf("The number is prime \n");
        else
            printf("The number is composite \n");
        return;
    }

    int i=1;
    mpz_t a,y,s,t,n1,n2,deux;

    gmp_randstate_t state;    
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, time(NULL));

    mpz_init(a);

    mpz_init(y);

    mpz_init(s);
    mpz_set_ui(s,1);

    mpz_init(deux);
    mpz_set_ui(deux,2);

    mpz_init(t);

    mpz_init(n1);
    mpz_sub_ui(n1,n,1);

    mpz_init(n2);
    mpz_sub_ui(n2,n,2);

    Decomp(n1,s,t);
    mpz_sub_ui(s,s,1);
    while(mpz_cmp_ui(rep,i)>=0)
    {
		//gerar um número inteiro aleatório uniformemente distribuído entre  0 e n1 - 1 (inclusive)
        mpz_urandomm(a,state,n1);
        mpz_add_ui(a,a,1);
        S_and_M(a,n,t,y);
        if(mpz_cmp_si(y,1)!=0 && mpz_cmp(y,n1)!=0) 
        {                                           
            for(int j=1;mpz_cmp_ui(s,j)>=0;j++)
            {
                mpz_set(n2,y);
                S_and_M(y,n,deux,y);//potência modular
                if(mpz_cmp_si(y,1)==0) 
                {
                    printf("The number is composite\n");
                    mpz_clear(a);mpz_clear(y);
                    mpz_clear(s);mpz_clear(t);
                    mpz_clear(n1);mpz_clear(n2);
                    mpz_clear(deux);gmp_randclear(state);
                    return;
                }
                if(mpz_cmp(y,n1)==0) //Si y congrue a -1 mod n on sort de la boucle
                break;
            }
            if(mpz_cmp(y,n1)!=0)  
            {
                printf("The number is composiste \n");
                mpz_clear(a);mpz_clear(y);
                mpz_clear(s);mpz_clear(t);
                mpz_clear(n1);mpz_clear(n2);
                mpz_clear(deux);gmp_randclear(state);
                return;
            }

        }
        i++;
    }
    printf("The number is prime \n");

    mpz_clear(a);mpz_clear(y);
    mpz_clear(s);mpz_clear(t);
    mpz_clear(n1);mpz_clear(n2);
    mpz_clear(deux);gmp_randclear(state);
}

int main()
{
    int t=1;
    mpz_t n;
    mpz_init(n);
    mpz_t rep;
    mpz_init(rep);
    printf("########## Primality test ##########\n");
    while(t==1)
    {
        printf("\n");
        printf("Choose an integer to test : ");
        gmp_scanf("%Zd", &n);
        if(mpz_cmp_ui(n,1)<=0)
        {   
            printf("\n choose an integer bigger than 1 !");
        }
        else
        {
            printf("Choose the number of repetitions : ");
            gmp_scanf("%Zd", &rep);
            printf("#########################################################\n");
            printf("Miller_Rabin : ");
            Miller_Rabin(n,rep);
            printf("\n");
            printf("Fermat : ");
            testFermat(n,rep);
            printf("#########################################################\n");
            printf("tape 1 for an other test !");
            scanf("%d",&t);
        }   
    }
    mpz_clear(n);   
    mpz_clear(rep);
    return 0;
}
