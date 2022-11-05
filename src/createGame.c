#include <stdio.h>
#include <stdlib.h>
#include "createGame.h"

void createGame(TabKata *listGame) {
    system("cls");
    printf("Masukkan nama game yang akan ditambahkan: ");
    GetCommand();
    if (!IsMember(*listGame, currentWord)) {
        SetEl(listGame, (*listGame).Neff, currentWord);
        if (IsWordEq(currentWord, GetElmt(*listGame, GetLastIdx(*listGame)))) {
            printf("Game berhasil ditambahkan.\n\n");
        } else {
            printf("Game gagal ditambahkan. Kapasitas BNMO sudah penuh.\n\n");
        }
    } else {
        printf("Game sudah ada.\n\n");
    }
}