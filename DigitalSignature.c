#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <gmp.h>
#include <time.h>

void main()
{
    char data[] = "This is test message !";
    size_t length = strlen(data);
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(data, length, hash);
    printf("Hashed value of original message is \n");
    for (int i = 0; i < sizeof(hash); i++)
        printf("%d ", hash[i]);
    printf("\n");

    mpz_t p, q, n, s, e, d, temp, convertedMsgUi;
    mpz_inits(p, q, n, s, e, d, temp, convertedMsgUi, NULL);
    char originalMessageHash[200] = {};

    for (int i = 0; i < sizeof(hash); i++)
    {
        unsigned char num = hash[i];
        char tempstr[4];
        sprintf(tempstr, "%u", num);
        strcat(originalMessageHash, tempstr);
    }
    mpz_set_str(convertedMsgUi, originalMessageHash, 10);

    unsigned long seed;
    seed = time(NULL);
    gmp_randstate_t rstate;
    gmp_randinit_mt(rstate);
    gmp_randseed_ui(rstate, seed);
    mpz_urandomb(p, rstate, 500);
    mpz_nextprime(p, p);
    mpz_urandomb(q, rstate, 500);
    mpz_nextprime(q, q);

    mpz_mul(n, p, q);
    mpz_sub_ui(p, p, 1);
    mpz_sub_ui(q, q, 1);
    mpz_mul(s, p, q);
    mpz_set_ui(e, 2);

    while (mpz_cmp_ui(e, 2) < 0 || (mpz_cmp_ui(temp, 1) != 0))
    {
        mpz_urandomm(e, rstate, s);
        mpz_t c, d;
        mpz_inits(c, d, NULL);
        mpz_set(temp, e);
        mpz_set(d, s);
        while (mpz_cmp_ui(d, 0) != 0)
        {
            mpz_set(c, d);
            mpz_fdiv_r(d, temp, d);
            mpz_set(temp, c);
        }
    }

    mpz_invert(d, e, s);
    mpz_powm(temp, convertedMsgUi, d, n);
    gmp_printf("Encrypted original hashed message is %Zd\n", temp);
    mpz_powm(temp, temp, e, n);
    char dectyptedMsg[200];
    mpz_get_str(dectyptedMsg, 10, temp);

    printf("Enter message received by B\n");
    char receivedMessage[200];
    fgets(receivedMessage, 200, stdin);
    length = strlen(receivedMessage);
    SHA1(receivedMessage, length - 1, hash);
    printf("Hashed value of received message is \n");
    for (int i = 0; i < sizeof(hash); i++)
        printf("%x", hash[i]);
    printf("\n");
    char receivedMessageHash[200] = {};
    for (int i = 0; i < sizeof(hash); i++)
    {
        unsigned char num = hash[i];
        char tempstr[4];
        sprintf(tempstr, "%u", num);
        strcat(receivedMessageHash, tempstr);
    }

    if (strcmp(originalMessageHash, receivedMessageHash) == 0)
    {
        printf("B Accepts the received message ----> Authentication Successful \n");
    }
    else
    {
        printf("B Rejects the received message ---->Authentication Unsuccessful \n");
    }
}
