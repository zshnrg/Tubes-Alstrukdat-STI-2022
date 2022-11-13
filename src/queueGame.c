#include <stdio.h>
#include "queueGame.h"

void queueGameList(TabKata listGame, Queue *queueGame) {
    int comm;

    printf("Berikut adalah daftar antrian game-mu\n");
    displayQueue(*queueGame);

    printf("\nBerikut adalah daftar game yang tersedia\n");
    TulisIsi(listGame);

    do {
        printf("\nNomor Game yang mau ditambahkan ke antrian: ");
        GetCommand();
        
        comm = 0;
        for (int i = 0; i < currentWord.Length; i++) {
            comm = comm * 10;
            comm += currentWord.TabWord[i] -'0';
        }

        if (comm < 1 || comm > listGame.Neff) {
            printf("Nomor permainan tidak valid, silahkan masukkan nomor game pada list.\n");
        }
    } while (comm < 1 || comm > listGame.Neff);

    enqueue(queueGame, GetElmt(listGame, comm - 1));
    printf("Game berhasil ditambahkan ke dalam daftar antrian.\n\n");

}

