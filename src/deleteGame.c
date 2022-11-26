#include <stdio.h>
#include "deleteGame.h"

void deleteGame(TabKata *listGame, Queue queueGame, Stack *historyGame) {
    int comm = 0;

    printf("Berikut ini adalah daftar game yang tersedia\n");
    TulisIsi(*listGame);
    printf("\nMasukkan nomor game yang akan dihapus: ");
    GetCommand();

    for (int i = 0; i < currentWord.Length; i++) {
        comm = comm * 10;
        comm += currentWord.TabWord[i] - '0';
    }

    if (comm > 7 && !IsMemberQ(queueGame, (*listGame).TK[comm - 1])) {
        
        Stack temp;
        infotype trf;
        while (!IsEmptyStack(*historyGame)) {
            Pop(historyGame, &trf);
            if (!IsWordEq(trf, (*listGame).TK[comm - 1])) Push(&temp, trf);
        }
        while (!IsEmptyStack(temp)) {
            Pop(&temp, &trf);
            Push(&temp, trf);
        }

        for (int i = comm; i < (*listGame).Neff; i++) {
            SetEl(listGame, i - 1, GetElmt(*listGame, i));
        }
        (*listGame).Neff--;


        printf("Game berhasil dihapus.\n\n");
    } else {
        printf("Game gagal dihapus.\n\n");
    }
}
