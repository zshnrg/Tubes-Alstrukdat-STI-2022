#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "skipGame.h"
#include "playGame.h"

/* Implementasi skipGame.h */

void skipGame (Queue* queueGame, Word command) {
    int n = 0, i;
    ElType val;
    srand(time(NULL));

    for (i = 0; i < command.Length; i++) {
        n = n * 10;
        n += command.TabWord[i] - '0';
    }

    printf("Berikut adalah daftar Game-mu\n");
        displayQueue(*queueGame);
        printf("\n\n");
    
    for (i = 0; i < n; i++) {
        Pop(queueGame);
    }

    if(!IsEmptyQ(*queueGame)) {
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
        printf("Tidak ada permainan lagi dalam daftar game-mu.\n\n");
    }
}