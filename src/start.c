#include <stdio.h>
#include "start.h"

boolean stateBNMO;

void start(TabKata *listGame, Stack* historyGame, Scoreboard *SB) {
    readTxt("config.txt", listGame, historyGame, SB);
    if (!IsEmpty(*listGame)) {
        printf("File konfigurasi sistem berhasil dibaca. BNMO berhasil dijalankan.\n\n");
        stateBNMO = true;
    } else {
        stateBNMO = false;
    }
}