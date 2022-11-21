#include <stdio.h>
#include "writeTxt.h"

/* Implementasi writeTxtFile.h */
void writeTxt(char* filetarget, TabKata listGame, Stack historyGame) {
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
    int nHistory = NbElmtStack(historyGame); 
    infotype temp;
    fprintf(file, "%d\n", nHistory);
    while (!IsEmptyStack(historyGame)) {
        Pop(&historyGame, &temp);
        for (int j = 0; j < temp.Length; j++) {
            fprintf(file, "%c", temp.TabWord[j]);
        }
        fprintf(file, "\n");
    }
    fprintf(file, " ");

    fclose(file);
}