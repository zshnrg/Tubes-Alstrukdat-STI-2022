#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "skipGame.h"
#include "playGame.h"

/* Implementasi skipGame.h */

void skipGame (Queue* queueGame, Stack* historyGame, Word command) {
    int n = 0, i;
    ElType dump;
    srand(time(NULL));

    for (i = 0; i < command.Length; i++) {
        n = n * 10;
        n += command.TabWord[i] - '0';
    }

    printf("Berikut adalah daftar Game-mu\n");
        displayQueue(*queueGame);
        printf("\n\n");

    if (!isEmpty(*queueGame)) { 
        for (i = 0; i < n; i++) {
            dequeue(queueGame, &dump);
        }

        if(!isEmpty(*queueGame)) {
            Word play;
            dequeue(queueGame, &play);
            Push(historyGame, play);

            if (IsWordEq(play, toKata("RNG"))) {
                printLoading(play);
                rngPlay();
                sleep(3);
            } else if (IsWordEq(play, toKata("Diner DASH"))) {
                printLoading(play);
                dinerDashPlay();
                sleep(3);
            } else if (IsWordEq(play, toKata("HANGMAN"))) {
                printLoading(play);

                sleep(3);
            } else if (IsWordEq(play, toKata("TOWER OF HANOI"))) {
                printLoading(play);
                playTowerOfHanoi();
                sleep(3);
            } else if (IsWordEq(play, toKata("SNAKE ON METEOR"))) {
                printLoading(play);

                sleep(3);
            } else if (IsWordEq(play, toKata("ATC GAME"))) {
                printLoading(play);
                playAtc();
                sleep(3);
            } else {
                printLoading(play);
                printf("Game over! Skor akhir: %d\n\n", rand());
            }
        } else {
            printf("Tidak ada permainan lagi dalam daftar Game-mu.\n\n");
        }
    } else {
            printf("Tidak ada permainan lagi dalam daftar Game-mu.\n\n");
    }
}