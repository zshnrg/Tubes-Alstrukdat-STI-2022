#include <stdio.h>
#include "save.h"
#include "./Driver/writeTxt.h"

/* Implementasi save.h */

void save(TabKata listGame, Word fileName) {
    FILE* target;
    char dir[50] = "./data/";
    
    for (int i = 0; i < fileName.Length; i++) {
        dir[7 + i] = fileName.TabWord[i];
    }
    dir[7 + fileName.Length] = '\0';
    
    writeTxt(dir, listGame);
    
    target = fopen(dir, "r");
    if (target != NULL) {
        printf("Save file berhasil disimpan.\n\n");
    } else {
        printf("Save file gagal disimpan.\n\n");
    }
    fclose(target);
}