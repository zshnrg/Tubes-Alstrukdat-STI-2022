#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "playGame.h"

void printLoading(Word gameName) {
    printf("Loading "); TulisWord(gameName); printf(" ");
    for (int i = 0; i < 3; i++) {
        printf("."); fflush(stdout); sleep(1);
    }
    clear();
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
        boolean isNameValid;
        do {
            if (showScore) {
                printf("Skor kamu: %d\n\n", score);
                if (IsMemberSet(SB[Idx].Nama, currentWord)) printf("Nama yang kamu masukkan sudah ada.\n");
                if (!isNameValid) printf("Nama tidak boleh mengandung karakter <spasi>.\n");
            } 
            printf("> Masukan nama: ");
            GetCommand();

            isNameValid = currentWord.Length > 0;
            for (int i = 0; i < currentWord.Length; i++) {
                if (currentWord.TabWord[i] == ' ') isNameValid = false;
            }
            
            clear();
            showScore = true;
        } while ((IsMemberSet(SB[Idx].Nama, currentWord)) || !isNameValid);
        InsertSet(&(SB[Idx].Nama), currentWord);
        Insert(&(SB[Idx].Score), currentWord, score);
        sortSet(&(SB[Idx]));
        printf("Berhasil menambakan hasil permainan ke Scoreboard.\n\n");

    } else {
        printf("Kamu tidak memiliki antrian Game apapun.\n\n");
    }
}