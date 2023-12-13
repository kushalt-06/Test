#include<stdio.h>
#include<gmp.h>
#include<time.h>
int main()
{
    
    gmp_randstate_t state;
    gmp_randinit_default(state);
    unsigned long seed=time(NULL);
    
    gmp_randseed_ui(state,seed);
    
    mpz_t p,q,r;
    mpz_inits(p,q,r,NULL);
    mpz_set_ui(r,2);

    
    while(1)
    {
        mpz_urandomb(q,state,100);
        
        mpz_nextprime(q,q);
        mpz_mul(p,q,r);
        mpz_add_ui(p,p,1);
        
        int n=mpz_probab_prime_p(p,5);
        if(n!=0)
        {
            break;
        }
    }
    
    mpz_t a,b,c,w;
    mpz_inits(a,b,c,NULL);
    mpz_sub_ui(w,p,1);
    
    while(1==1)
    {
        mpz_urandomm(a,state,w);
        if(mpz_cmp_ui(a,2)<0)
        {
            mpz_add_ui(a,a,2);
        }
        mpz_powm(b,a,q,p);
        mpz_powm(c,a,r,p);
        
        if(mpz_cmp_ui(b,1)!=0 && mpz_cmp_ui(c,1)!=0)
        {
            break;
        }
    }
    mpz_t m,n,x,y,ka,kb;
    mpz_inits(m,n,x,y,ka,kb,NULL);
    
    mpz_urandomb(m,state,10);
    mpz_urandomb(n,state,10);
    
    mpz_powm(x,a,m,p);
    mpz_powm(y,a,n,p);
    
    mpz_powm(ka,x,n,p);
    mpz_powm(kb,y,m,p);
    
    if(mpz_cmp(ka,ka)==0)
    {
        gmp_printf("YES");
        
    }
    else
    {
        gmp_printf("NO");
    }
    gmp_printf("\n%Zd %Zd\n",ka,kb);
    return 0;
}