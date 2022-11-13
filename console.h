#ifndef BNMO_CONSOLE_H
#define BNMO_CONSOLE_H

#include <stdio.h>
#include <unistd.h>
#include "./src/adt/array.h"
#include "./src/adt/queue.h"
#include "./src/adt/mesinkata.h"

#include "./src/start.h"
#include "./src/save.h"
#include "./src/load.h"
#include "./src/createGame.h"
#include "./src/listGame.h"
#include "./src/deleteGame.h"
#include "./src/queueGame.h"
#include "./src/playGame.h"
#include "./src/skipGame.h"
#include "./src/quit.h"
#include "./src/help.h"

void menuList(TabKata *listGame, Queue *queueGame);
/* Memilih menu BNMO
    I.S. listGame dan queueGame terdefinisi mungkin kosong
    F.S. Menu dijalankan sesuai dengan input user
*/

#endif
