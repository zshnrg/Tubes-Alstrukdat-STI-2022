#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "rng.h"

int rngPlay() {
    clear();
    srand(time(NULL));

    printGuideRnG();

    int n;
    int score = 101;

    int X = rand() % 101;
    printf("RNG Telah dimulai. Uji keberuntungan Anda dengan menebak X.\nClue: X berada di antara 0-100\n");
    do {
        n = 0;
        printf("\nTebakan > ");
        GetCommand();
        for (int i = 0; i < currentWord.Length; i++) {
            n = n * 10;
            n += currentWord.TabWord[i] - '0';
        }
        clear();
        if (n > X) {
            printf("Tebakan salah! X lebih kecil dari %d\n", n);
        } else if (n < X) {
            printf("Tebakan salah! X lebih besar dari %d\n", n);
        } else {
            clear();
            printf("Selamat tebakanmu benar!\nX adalah %d.\n\n", n);
        }
        if (score > 10) score--;
    } while (n != X);
    printf("Skor permainan: %d\n\n", score);
    return score;
}

void printGuideRnG() {
    for (int i = 8; i > 0; i--) {
        printf("\n ______         _______      _______                                     \n|   __ \\.-----.|     __|    |     __|.--.--.-----.-----.-----.-----.----.\n|      <|     ||    |  |    |    |  ||  |  |  -__|__ --|__ --|  -__|   _|\n|___|__||__|__||_______|    |_______||_____|_____|_____|_____|_____|__|  \n                                                                        \n========================== Petunjuk Permainan ==========================\n\n1. Pada permainan ini kamu diminta untuk menebak sebuah angka yang\n   diciptakan secara acak.\n2. Angka yang perlu ditebak merupakan bilangan bulat antara 1-100.\n3. Sistem akan memberi tau apakah angka tebakanmu lebih besar atau lebih\n   Kecil dari angka sebenarnya.\n4. Permainan akan berakhir ketika kamu berhasil menebak angka sebenarnya.\n\n========================================================================\n\nPermainan akan dimulai dalam %d ...", i);
        fflush(stdout); sleep(1);
        clear();
    }
}