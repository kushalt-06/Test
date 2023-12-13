#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
void factorize(mpz_t n) {
    mpz_t divisor;
    mpz_init(divisor);
    mpz_set_ui(divisor, 2);
    while (mpz_cmp_ui(n, 1) > 0) {
        if (mpz_divisible_p(n, divisor)) {
            mpz_divexact(n, n, divisor);
            gmp_printf("%Zd ", divisor);
            while (mpz_divisible_p(n, divisor)) {
                mpz_divexact(n, n, divisor);
            }        }
        mpz_add_ui(divisor, divisor, 1);
    }
    mpz_clear(divisor);
}
int main() {
    mpz_t number;
    mpz_init(number);
    printf("Enter a large positive integer: ");
    gmp_scanf("%Zd", number);
    if (mpz_cmp_ui(number, 1) <= 0) {
        printf("Please enter a positive integer greater than 1.\n");
    } else {
        printf("Distinct prime factors: ");
        factorize(number);
        printf("\n");
    }
    mpz_clear(number);
    return 0;
}
