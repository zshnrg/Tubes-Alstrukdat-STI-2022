#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "playGame.h"

void printLoading(Word gameName) {
    printf("Loading "); TulisWord(gameName); printf(" ");
    for (int i = 0; i < 3; i++) {
        printf("."); sleep(1);
    }
    system("cls");
}

// Game yang diload dan game yang dibuat akan dipisah karena perlu ada penanganan game yang sedang maintenance (game yang bukan game RNG, Dine Dash, atau game buatan)
void playGame(Queue *queueGame) {
    ElType val;
    srand(time(NULL));

    // ALGORITMA
    if(!IsEmptyQ(*queueGame)) {
        printf("Berikut adalah daftar Game-mu\n");
        displayQueue(*queueGame);
        printf("\n");

        Word play = (*queueGame).Tab[(*queueGame).HEAD];
        Pop(queueGame);

        if (IsWordEq(play, toKata("RNG"))) {
            printLoading(play);
            rngPlay();
            sleep(3);
        } else if (IsWordEq(play, toKata("Diner DASH"))) {
            printLoading(play);
            dinerDashPlay();
            sleep(3);
        } else if (IsWordEq(play, toKata("DINOSAUR IN EARTH")) || IsWordEq(play, toKata("RISEWOMAN")) || IsWordEq(play, toKata("EIFFEL TOWER"))) {
            printf("Game "); TulisWord(play); printf(" masih dalam maintenance, belum dapat dimainkan. Silahkan pilih game lain.\n\n");
        } else {
            printLoading(play);
            printf("Game over! Skor akhir: %d\n\n", rand());
        }
    } else {
        printf("Kamu tidak memiliki antrian Game apapun.\n\n");
    }
}