#include <stdio.h>
#include <unistd.h>
#include "quit.h"

void quit(TabKata listGame) {
    do {
        printf("Apakah ingin melakukan save sebelum keluar? (YES/NO): ");
        GetCommand();
    } while (!IsWordEq(toKata("YES"), currentWord) && !IsWordEq(toKata("NO"), currentWord));

    if (IsWordEq(toKata("YES"), currentWord)) {
        printf("Masukkan nama file: ");
        GetCommand();
        printf("\n");
        save(listGame, currentWord);
    } else {printf("\n");}
    printf("Anda keluar dari game BNMO.\nBye bye ");
    for (int i = 0; i < 3; i++) {
        printf("."); sleep(1);
    }
    stateBNMO = false;
}