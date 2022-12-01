#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "skipGame.h"
#include "playGame.h"

/* Implementasi skipGame.h */

void skipGame (TabKata listGame, Queue* queueGame, Stack* historyGame, Scoreboard *SB, Word command) {
    int score;
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

            printLoading(play);
            if (IsWordEq(play, toKata("RNG"))) {
                score = rngPlay();
                sleep(3);
            } else if (IsWordEq(play, toKata("Diner DASH"))) {
                score = dinerDashPlay();
                sleep(3);
            } else if (IsWordEq(play, toKata("HANGMAN"))) {
                score = playHangman();
                sleep(3);
            } else if (IsWordEq(play, toKata("TOWER OF HANOI"))) {
                score = playTowerOfHanoi();
                sleep(3);
            } else if (IsWordEq(play, toKata("SNAKE ON METEOR"))) {
                score = playSnakeOnMeteor();
                sleep(3);
            } else if (IsWordEq(play, toKata("ATC GAME"))) {
                score = playAtc();
                sleep(3);
            } else if (IsWordEq(play, toKata("THE GLASS GAME"))) {
                score = playTheGlassGame();
                sleep(3);
            } else {
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
                clear();
                showScore = true;
            } while ((IsMemberSet(SB[Idx].Nama, currentWord)));
            InsertSet(&(SB[Idx].Nama), currentWord);
            Insert(&(SB[Idx].Score), currentWord, score);
            sortSet(&(SB[Idx]));
            printf("Berhasil menambakan hasil permainan ke Scoreboard.\n\n");
            
        } else {
            printf("Tidak ada permainan lagi dalam daftar Game-mu.\n\n");
        }
    } else {
            printf("Tidak ada permainan lagi dalam daftar Game-mu.\n\n");
    }
}