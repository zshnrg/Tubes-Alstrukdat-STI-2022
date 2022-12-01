#include <stdio.h>
#include <unistd.h>
#include "readTxt.h"

/* Implementasi readTxtFile.h */

void readTxt(char* filesrc, TabKata* listGame, Stack* historyGame, Scoreboard *SB) {
    Stack inv; CreateEmptyStack(&inv);
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
        infotype temp;
        if (currentChar != ' ') {
            int lines = 0;
            for (int i = 0; i < currentWord.Length; i++) {
                lines *= 10;
                lines += currentWord.TabWord[i] - '0';
            }
            for (int i = 0; i < lines; i++) {
                ADVWORD();
                Push(&inv, currentWord);
            }
            while (!IsEmptyStack(inv)) {
                Pop(&inv, &temp);
                Push(historyGame, temp);
            }
        }

        // Scoreboard
        ADVWORD();
        if (currentChar != ' ') {
            for (int i = 0; i < numGame; i ++) {
                int lines = 0;
                for (int i = 0; i < currentWord.Length; i++) {
                    lines *= 10;
                    lines += currentWord.TabWord[i] - '0';
                }
                for (int j = 0; j < lines; j++) {
                    ADVWORD();
                    InsertSet(&(SB[i]).Nama, AccessCommand(currentWord, 0));
                    int score = 0;
                    Word scr = AccessCommand(currentWord, 1);
                    for (int k = 0; k < scr.Length; k++) {
                        score *= 10;
                        score += scr.TabWord[k] - '0';
                    }
                    Insert(&(SB[i]).Score, AccessCommand(currentWord, 0), score);
                }
                sortSet(&(SB[i]));
                ADVWORD();
            }
        }
    }
    fclose(input);
}