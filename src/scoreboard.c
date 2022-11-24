#include <stdio.h>
#include "scoreboard.h"

void scoreboard(Scoreboard *SB, TabKata listGame) {
    for (int i = 0; i < listGame.Neff; i++) {
        printf("[== SCOREBOARD GAME ");
        TulisWord(listGame.TK[i]);
        printf(" ==]\n");

        int maxLen = 10;
        for (int j = 0; j < SB[i].Nama.Count; j++) {
            if (SB[i].Nama.Elements[j].Length > maxLen) maxLen = SB[i].Nama.Elements[j].Length;
        }
        maxLen += 2;
        
        printf("| NAMA");
        for (int j = 6; j < maxLen + 1; j++) printf(" ");
        printf("| SKOR");
        for (int j = 6; j < 13; j++) printf(" ");
        printf("|\n");

        if (!IsEmptySet(SB[i].Nama)) {
            printf("|");
            for (int j = 0; j < maxLen + 13; j++) printf("-");
            printf("|\n");
            for (int j = 0; j < SB[i].Nama.Count; j++) {
                printf("| ");
                TulisWord(SB[i].Nama.Elements[j]);
                for (int k = SB[i].Nama.Elements[j].Length; k < maxLen - 1; k++) printf(" ");
                printf("| ");
                Word score = intToWord(getValFromIdx(SB[i], j));
                TulisWord(score);
                for (int k = score.Length; k < 11; k++) printf(" ");
                printf("|\n");
            }
        } else {
            for (int j = 0; j < (maxLen - 6) / 2 + 1; j++) printf("-");
            printf(" SCOREBOARD KOSONG ");
            for (int j = 0; j < (maxLen - 6) / 2 + 1; j++) printf("-");
            printf("\n");
        }
        printf("\n");
    }
}

