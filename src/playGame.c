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
void playGame(Queue *queueGame, Stack* historyGame) {
    ElType val;
    srand(time(NULL));

    // ALGORITMA
    if(!isEmpty(*queueGame)) {
        printf("Berikut adalah daftar Game-mu\n");
        displayQueue(*queueGame);
        printf("\n");

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
            playHangman();
            sleep(3);
        } else if (IsWordEq(play, toKata("TOWER OF HANOI"))) {
            printLoading(play);
            playTowerOfHanoi();
            sleep(3);
        } else if (IsWordEq(play, toKata("SNAKE ON METEOR"))) {
            printLoading(play);
            playSnakeOnMeteor();
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
        printf("Kamu tidak memiliki antrian Game apapun.\n\n");
    }
}