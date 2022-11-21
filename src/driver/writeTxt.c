#include <stdio.h>
#include "writeTxt.h"

/* Implementasi writeTxtFile.h */
void writeTxt(char* filetarget, TabKata listGame, List historyGame) {
    FILE *file;

    file = fopen(filetarget, "w");

    // Writing game list
    fprintf(file, "%d\n", NbElmt(listGame));
    for (int i = 0; i < NbElmt(listGame); i++) {
        for (int j = 0; j < listGame.TK[i].Length; j++) {
            fprintf(file, "%c", listGame.TK[i].TabWord[j]);
        }
        fprintf(file, "\n");
    }

    // Writing game history
    int nHistory = NumberElmt(historyGame); 
    fprintf(file, "%d\n", nHistory);
    address P = First(historyGame);
    while (P != NULL) {
        for (int j = 0; j < Info(P).Length; j++) {
            fprintf(file, "%c", Info(P).TabWord[j]);
        }
        P = Next(P);
        fprintf(file, "\n");
    }
    fprintf(file, " ");

    fclose(file);
}