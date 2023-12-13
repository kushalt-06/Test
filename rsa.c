#include<stdio.h>
#include<gmp.h>
#include<time.h>
void main()
{
    mpz_t p,q,n,s,e,d,temp,m;
    mpz_inits(p,q,n,s,e,d,temp,m,NULL);
    gmp_printf("Enter the message to encrypt: ");
    gmp_scanf("%Zd",m);
    unsigned long seed=time(NULL);
    gmp_randstate_t rstate;
    gmp_randinit_mt(rstate);
    gmp_randseed_ui(rstate, seed);
    mpz_urandomb(p, rstate, 1024);
    mpz_nextprime(p,p);
    mpz_urandomb(q, rstate, 1024);
    mpz_nextprime(q,q);
    gmp_printf("\nFirst Random generated prime numbers is %Zd :\n",p);
    gmp_printf("\nSecond Random generated prime numbers is %Zd :\n",q);
    mpz_mul(n,p,q);
    mpz_sub_ui(p,p,1);
    mpz_sub_ui(q,q,1);
    mpz_mul(s,p,q);
    mpz_urandomb(e,rstate,512);
    mpz_add_ui(e,e,2);
    
    while(1)
    {
       mpz_t tmp;
       mpz_init(tmp);
       mpz_gcd(tmp,e,s);
       if(mpz_cmp_ui(tmp,1)!=0)
       {
           mpz_add_ui(e,e,1);
       }
        else
        {
            break;
        }
    }
    
    gmp_printf("\nPublic key is (%Zd)\n",e);
    mpz_invert(d,e,s);
    gmp_printf("\nprivate key is (%Zd)\n",d);
    mpz_powm(temp,m,e,n);
    gmp_printf("\ncipher value is %Zd\n",temp);
    mpz_powm(temp,temp,d,n);
    gmp_printf("\nfter decryption message is %Zd\n",temp);
}
