#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "resetHistory.h"

void resetHistory(Stack* historyGame) {
    if (!IsEmptyStack(*historyGame)) {
        do {
            printf("APAKAH KAMU YAKIN INGIN MELAKUKAN RESET HISTORY? (Y/N) ");
            GetCommand();
            if (currentWord.Length != 1 || !(IsWordEq(currentWord, toKata("Y")) || IsWordEq(currentWord, toKata("N")))) {
                printf("\nPerintah tidak valid, silahkan masukan ulang perintah.");
                fflush(stdout);
                sleep(1);
                clear();
            }
        } while (currentWord.Length != 1 || !(IsWordEq(currentWord, toKata("Y")) || IsWordEq(currentWord, toKata("N"))));

        if (IsWordEq(currentWord, toKata("Y"))) {
            CreateEmptyStack(historyGame);
            if (IsEmptyStack(*historyGame)) {
                printf("\nHistory berhasil di-reset.\n\n");
            } else {
                printf("\nHistory gagal di-reset karena kesalahan sistem.\n\n");
            }
        } else {
            printf("\nHistory tidak jadi di-reset. ");
            history(*historyGame, toKata("100"));
        }
    } else {
        printf("History game sudah kosong.\n\n");
    }
}