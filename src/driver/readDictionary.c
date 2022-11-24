#include <stdio.h>
#include "readDictionary.h"

void readDictionary(char* filesrc, Kamus *K) {
    char dir[50] = "./data/game/";
    int i = 0;
    while (filesrc[i] != '\0') {
        dir[12 + i] = filesrc[i];
        i++;
    }
    dir[12 + i] = '\0';
    
    FILE* input = fopen(dir, "r");
    if (input != NULL) {
        STARTWORD(input);
        while (currentChar != ' ') {
            insertToKamus(K, currentWord);
            ADVWORD();
        }
        insertToKamus(K, currentWord);
    } else {
        printf("File kamus tidak ditemukan. ");
    }
    fclose(input);
}
