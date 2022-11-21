#include <stdio.h>
#include "start.h"

boolean stateBNMO;

void start(TabKata *listGame, Stack* historyGame) {
    readTxt("config.txt", listGame, historyGame);
    if (!IsEmpty(*listGame)) {
        printf("File konfigurasi sistem berhasil dibaca. BNMO berhasil dijalankan.\n\n");
        stateBNMO = true;
    } else {
        stateBNMO = false;
    }
}