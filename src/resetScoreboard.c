#include <stdio.h>
#include <stdlib.h>
#include "resetScoreboard.h"

void resetScoreboard(TabKata listGame, Scoreboard *SB) {
    int n = 0;
    do {
        clear();
        printf("DAFTAR SCOREBOARD\n\n");
        for (int i = 0; i <= listGame.Neff; i++) {
            printf("  %d. ", i);
            if (i == 0) printf("ALL");
            else TulisWord(listGame.TK[i - 1]);
            printf("\n");
        }
        printf("\n");
        if (n < 0 || n > listGame.Neff) printf("Pilihan tidak valid, silahkan masukkan pilihan yang sesuai.\n");
        printf("SCOREBOARD YANG INGIN DIHAPUS: ");
        GetCommand();
        n = 0;
        for (int i = 0; i < currentWord.Length; i++) {
            n *= 10;
            n += currentWord.TabWord[i] -'0';
        }
    } while (n < 0 || n > listGame.Neff);

    
    do {
        printf("\nAPAKAH KAMU YAKIN INGIN MELAKUKAN RESET SCOREBOARD ");
        if (n == 0) printf("ALL: (YA/TIDAK) ");
        else {
            TulisWord(listGame.TK[n - 1]);
            printf(": (YA/TIDAK) ");
        }
        GetCommand();
    } while (!IsWordEq(toKata("YA"), currentWord) && !IsWordEq(toKata("TIDAK"), currentWord));

    if (IsWordEq(toKata("YA"), currentWord)) {
        if (n == 0) {
            for (int i = 0; i < listGame.Neff; i++) {
                while (SB[i].Nama.Count != 0) {
                    Delete(&(SB[i].Score), SB[i].Nama.Elements[0]);
                    DeleteSet(&(SB[i].Nama), SB[i].Nama.Elements[0]);
                }
            }
        } else {
            while (SB[n - 1].Nama.Count != 0) {
                Delete(&(SB[n - 1].Score), SB[n - 1].Nama.Elements[0]);
                DeleteSet(&(SB[n - 1].Nama), SB[n - 1].Nama.Elements[0]);
            }
        }
        clear();
        printf("Scoreboard berhasil di-reset.\n\n");
    } else {
        clear();
        printf("Scoreboard tidak jadi di-reset.\n\n");
    }
}