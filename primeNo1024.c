#include<stdio.h>
#include<gmp.h>

int main() {

    mpz_t prime;
    gmp_randstate_t state;
    
    mpz_init(prime);
    gmp_randinit_default(state);
    
    gmp_randseed_ui(state, 323256789);
    mpz_urandomb(prime, state, 1024);
    mpz_setbit(prime, 1023);
    mpz_nextprime(prime, prime);
    
    gmp_printf("Generated prime number: %Zx\n", prime);
    mpz_clear(prime);
    gmp_randclear(state);
    
    return 0;
}
