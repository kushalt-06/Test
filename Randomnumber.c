#include<gmp.h>
#include<time.h>
#include<stdio.h>
int main()
{
    gmp_randstate_t state;
    mpz_t prime;

    gmp_randinit_default(state);
    mpz_init(prime);
    unsigned long seed =time(NULL);

    gmp_randseed_ui(state,seed);   
    mpz_urandomb(prime,state,1024);
    mpz_setbit(prime,1024);
    mpz_nextprime(prime,prime);
    gmp_printf("%Zd",prime);
    
    char *bs =mpz_get_str(NULL,2,prime);
    gmp_printf("%s",bs);

}