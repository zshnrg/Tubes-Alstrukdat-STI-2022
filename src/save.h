#ifndef SAVE_H
#define SAVE_H

#include "./Driver/writeTxt.h"

/* MODUL Save */

void save(TabKata listGame, Word filename);
/*  Menyimpan state game pemain saat ini ke dalam suatu file.
    I.S. File tujuan mungkin sudah ada / belum ada.
    F.S. State game pemain tersimpan dalam suatu file. Jika file sudah ada maka file tersebut akan tergantikan.
*/

#endif