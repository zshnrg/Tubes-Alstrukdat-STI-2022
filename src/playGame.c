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
void playGame(TabKata listGame, Queue *queueGame, Stack* historyGame, Scoreboard *SB) {
    int score;
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
            score = rngPlay();
            sleep(3);
        } else if (IsWordEq(play, toKata("Diner DASH"))) {
            printLoading(play);
            score = dinerDashPlay();
            sleep(3);
        } else if (IsWordEq(play, toKata("HANGMAN"))) {
            printLoading(play);
            score = playHangman();
            sleep(3);
        } else if (IsWordEq(play, toKata("TOWER OF HANOI"))) {
            printLoading(play);
            score = playTowerOfHanoi();
            sleep(3);
        } else if (IsWordEq(play, toKata("SNAKE ON METEOR"))) {
            printLoading(play);
            score = playSnakeOnMeteor();
            sleep(3);
        } else if (IsWordEq(play, toKata("ATC GAME"))) {
            printLoading(play);
            score = playAtc();
            sleep(3);
        } else {
            printLoading(play);
            score = rand() % 1000;
            printf("Game over! Skor akhir: %d\n\n", score);
        }

        int Idx = 0;
        for (int i = 0; i < listGame.Neff; i++) {
            if (IsWordEq(listGame.TK[i], play)) Idx = i;
        }

        boolean showScore = false;
        do {
            if (showScore) {
                printf("Skor kamu: %d\n\n", score);
                if (IsMemberSet(SB[Idx].Nama, currentWord)) printf("Nama yang kamu masukkan sudah ada.\n");
            } 
            printf("> Masukan nama: ");
            GetCommand();
            system("cls");
            showScore = true;
        } while ((IsMemberSet(SB[Idx].Nama, currentWord)));
        InsertSet(&(SB[Idx].Nama), currentWord);
        Insert(&(SB[Idx].Score), currentWord, score);
        sortSet(&(SB[Idx]));
        printf("Berhasil menambakan hasil permainan ke Scoreboard.\n\n");

    } else {
        printf("Kamu tidak memiliki antrian Game apapun.\n\n");
    }
}