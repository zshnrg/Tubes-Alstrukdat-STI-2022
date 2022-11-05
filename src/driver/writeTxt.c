#include <stdio.h>
#include "writeTxt.h"

/* Implementasi writeTxtFile.h */
void writeTxt(char* filetarget, TabKata listGame) {
    FILE *file;

    file = fopen(filetarget, "w");

    fprintf(file, "%d\n", NbElmt(listGame));
    for (int i = 0; i < NbElmt(listGame); i++) {
        for (int j = 0; j < listGame.TK[i].Length; j++) {
            fprintf(file, "%c", listGame.TK[i].TabWord[j]);
        }
        fprintf(file, "\n");
    }
    fprintf(file, " ");

    fclose(file);
}