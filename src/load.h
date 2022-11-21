#ifndef LOAD_BNMO_H
#define LOAD_BNMO_H

#include <stdio.h>
#include "./driver/readTxt.h"
#include "start.h"

void load(TabKata *listGame, Stack* historyGame, Word fileName);
/*  Membaca file konfigurasi yang berisi list game yang dapat dimainkan.
    I.S. listGame sudah terdefinisi dan tidak kosong.
    F.S. File konfigurasi terbaca dan list game bertambah.
*/

#endif