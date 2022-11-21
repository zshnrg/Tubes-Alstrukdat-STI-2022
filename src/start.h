#ifndef START_BNMO_H
#define START_BNMO_H

#include <stdio.h>
#include "./driver/readTxt.h"

extern boolean stateBNMO;

void start(TabKata *listGame, Stack* historyGame);
/*  Membaca file konfigurasi default yang berisi list game yang dapat dimainkan.
    I.S. StateBNMO bernilai sembarang.
    F.S. File konfigurasi terbaca dan list game bertambah. StateBNMO true.
*/

#endif