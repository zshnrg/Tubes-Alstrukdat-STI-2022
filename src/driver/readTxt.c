#include <stdio.h>
#include "readTxt.h"

/* Implementasi readTxtFile.h */

void readTxt(char* filesrc, TabKata* listGame, List* historyGame) {
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
        // Config file
        STARTWORD(input);
        int numGame = 0;
        for (int i = 0; i < currentWord.Length; i++) {
            numGame *= 10;
            numGame += currentWord.TabWord[i] - '0';
        }
        for (int i = 0; i < numGame; i++) {
            ADVWORD();
            SetEl(listGame, i, currentWord);
        }

        // History game
        ADVWORD();
        if (currentChar != ' ') {
            int lines = 0;
            for (int i = 0; i < currentWord.Length; i++) {
                lines *= 10;
                lines += currentWord.TabWord[i] - '0';
            }
            for (int i = 0; i < lines; i++) {
                ADVWORD();
                InsVLast(historyGame, currentWord);
            }
        }
    }
    fclose(input);
}