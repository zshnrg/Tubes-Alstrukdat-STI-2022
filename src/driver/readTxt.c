#include <stdio.h>
#include "readTxt.h"

/* Implementasi readTxtFile.h */

void readTxt(char* filesrc, TabKata* listGame) {
    int lines = 0;
    char dir[50] = "./data/";

    int i = 0;
    while (filesrc[i]) {
        dir[7 + i] = filesrc[i];
        i++;
    }
    dir[7 + i] = '\0';
    FILE* input = fopen(dir, "r");
    
    if (input == NULL) {
        printf("File tidak ditemukan. ");
    } else {
        STARTWORD(input);
        for (int i = 0; i < currentWord.Length; i++) {
            lines *= 10;
            lines += currentWord.TabWord[i] - '0';
        }
        for (int i = 0; i < lines; i++) {
            ADVWORD();
            SetEl(listGame, i, currentWord);
        }
    }
    fclose(input);
}