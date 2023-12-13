#include<stdio.h>
#include<gmp.h>
#include<time.h>
int main()
{
    mpz_t mes;
    mpz_init(mes);
    gmp_scanf("%Zd",mes);
    mpz_t p,a,g,y;
    mpz_inits(p,a,g,y,NULL);
    
    // key Generation 
    
    mpz_set_ui(p,1024);
    mpz_set_ui(g,2);
    
    gmp_randstate_t state;
    gmp_randinit_default(state);
    mpz_urandomb(a,state,10);
    
    mpz_powm(y,g,a,p);
    
    // encryption 
    
    mpz_t c1,c2,r,x;
    mpz_urandomm(r,state,p);
    mpz_inits(c1,c2,r,x,NULL);
    
    mpz_powm(c1,g,r,p);
    mpz_powm(c2,y,r,p);
    mpz_mul(c2,c2,mes);
    //Decryption 
     
    mpz_invert(x,c1,p);
    
    mpz_mul(c2,c2,x);
    
    gmp_printf("%Zd",c2);
    return 0;
}
