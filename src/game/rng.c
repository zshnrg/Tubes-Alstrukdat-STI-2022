#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "rng.h"

void rngPlay() {
    system("cls");
    srand(time(NULL));
    int n;

    int X = rand() % rand();
    printf("RNG Telah dimulai. Uji keberuntungan Anda dengan menebak X.\n");
    do {
        n = 0;
        GetCommand();
        for (int i = 0; i < currentWord.Length; i++) {
            n = n * 10;
            n += currentWord.TabWord[i] - '0';
        }
        if (n > X) printf("Lebih kecil\n");
        else if (n < X) printf("Lebih besar\n");
        else {
            system("cls");
            printf("Ya, X adalah %d.\n\n", n);
        }
    } while (n != X);
}