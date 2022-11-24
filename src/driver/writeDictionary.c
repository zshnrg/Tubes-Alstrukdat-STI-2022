#include <stdio.h>
#include "writeDictionary.h"

void writeDictionary(char* filename, Kamus K) {
    char dir[50] = "./data/game/";
    int i = 0;
    while (filename[i] != '\0') {
        dir[12 + i] = filename[i];
        i++;
    }
    dir[12 + i] = '\0';
    
    FILE* ouput = fopen(dir, "w");
    for (int i = 0; i < K.Neff; i++) {
        for (int j = 0; j < K.Kata[i].Length; j++) {
            fprintf(ouput, "%c", K.Kata[i].TabWord[j]);
        }
        fprintf(ouput, "\n");
    }
    fprintf(ouput, " ");

    fclose(ouput);
}