#include <gmp.h>
#include <stdio.h>
#include <time.h>

int ft(const mpz_t a, mpz_t b) {
    if (mpz_cmp_ui(a, 1) <= 0) {
        return 0;
    }
    if (mpz_cmp_ui(a, 2) <= 0) {
        return 1;
    }

    gmp_randstate_t state;
    gmp_randinit_default(state);
    mpz_t x, y, r;
    mpz_inits(x, y, r, NULL);
    mpz_sub_ui(x, a, 1);

    for (int i = 0; i < mpz_get_ui(b); i++) {
        mpz_urandomm(y, state, x);
        mpz_powm(r, y, x, a);

        if (mpz_cmp_ui(r, 1) != 0) {
            return 0;
        }
    }

    return 1;
}

int main() {
    mpz_t a, b;
    mpz_inits(a, b, NULL);

    gmp_scanf("%Zd", a);
    gmp_scanf("%Zd", b);

    if (ft(a, b) > 0) {
        gmp_printf("YES\n");
    } else {
        gmp_printf("NO\n");
    }

    return 0;
}
