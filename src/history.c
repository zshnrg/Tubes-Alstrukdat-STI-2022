#include <stdio.h>
#include "history.h"

void history(List historyGame, Word Command) {
    int n = 0;
    for (int i = 0; i < Command.Length; i++) {
        n *= 10;
        n += Command.TabWord[i] - '0';
    }
    if (n <= 0) {
        printf("Jumlah perintah history tidak valid.\n\n");
    } else {
        if (IsEmptyList(historyGame)) {
            printf("Belum ada Game yang pernah dimainkan.\n\n");
        } else {
            printf("Berikut adalah daftar Game yang telah dimainkan\n");
            int count = 1;
            address P = First(historyGame);
            while (P != NULL && count <= n) {
                printf("  %d. ", count);
                TulisWord(Info(P));
                P = Next(P);
                count++;
                printf("\n");
            }
            printf("\n");
        }
    }
}