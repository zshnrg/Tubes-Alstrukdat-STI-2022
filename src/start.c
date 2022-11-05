#include <stdio.h>
#include "start.h"

boolean stateBNMO;

void start(TabKata *listGame) {
    readTxt("config.txt", listGame);
    if (!IsEmpty(*listGame)) {
        printf("File konfigurasi sistem berhasil dibaca. BNMO berhasil dijalankan.\n\n");
        stateBNMO = true;
    } else {
        stateBNMO = false;
    }
}